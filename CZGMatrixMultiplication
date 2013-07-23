import java.io.IOException;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.GenericOptionsParser;

public class CZGMatrixMultiplication {

  //mapper
	public static class MatrixMap extends Mapper<Object, Text, Text, Text>{
		private Text map_key = new Text();
		private Text map_value = new Text();
		
		int rows = 300;
		int cols = 500;
		String fileTarget;
		String i,j,k; //矩阵M的i行j列，矩阵N的j行k列
		String value_ij; //(i,j)处的值
		String value_jk; //(j,k)处的值
		public void map(Object key, Text value, Context context) throws IOException, InterruptedException{
			String terms[] = value.toString().split("#");
			//System.out.println("test&&&&&&&&&&&&&&&&&&&&&");
			fileTarget = terms[0];
			//System.out.println("11");
			if(fileTarget.equals("M"))
			{
				i = terms[1];
				j = terms[2];
				value_ij = terms[3];
				for(int c = 1; c <= cols; ++c)
				{
					map_key.set(i+"#"+String.valueOf(c));
					map_value.set("M"+ "#" + j + "#" + value_ij);
					context.write(map_key, map_value);
				}
			}
			else {
				j = terms[1];
				k = terms[2];
				value_jk = terms[3];
				for(int r = 1; r <= rows; ++r)
				{
					map_key.set(String.valueOf(r)+"#"+k);
					map_value.set("N"+ "#" + j + "#" + value_jk);
					context.write(map_key, map_value);
				}
			}
		}
	}
	
	//reducer
	public static class MatrixReduce extends Reducer<Text, Text, Text, Text>{
		private Text reduce_value = new Text();
		int cols = 150;
		int Mij[] = new int[cols+1];
		int Njk[] = new int[cols+1];
		String fileTaget;
		int sum;
		public void reduce(Text key, Iterable<Text> values, Context context) throws IOException, InterruptedException
		{
			sum = 0;
			for (Text val: values)
			{
				String terms[] = val.toString().split("#");
				fileTaget = terms[0];
				int j = Integer.parseInt(terms[1]);
				if (fileTaget.equals("M")){
					Mij[j] = Integer.parseInt(terms[2]);
				}
				else {
					Njk[j] = Integer.parseInt(terms[2]);
				}
			}
			for(int c = 1; c <= cols; ++c)
			{
				sum += Mij[c] * Njk[c];
			}
			reduce_value.set(String.valueOf(sum));
			context.write(key, reduce_value);
		}
	}
	/**
	 * @param args
	 * @throws ClassNotFoundException 
	 * @throws InterruptedException 
	 */
	public static void main(String[] args) throws Exception {
		// TODO Auto-generated method stub
		Configuration conf = new Configuration();
	    String[] otherArgs = new GenericOptionsParser(conf, args).getRemainingArgs();
	    if (otherArgs.length != 2) {
	    	System.err.println("Usage: MartrixMultiplication <in> <out>");
	    	System.exit(2);
	    }
	    Job job = new Job(conf, "MartrixMultiplication");
	    job.setJarByClass(CZGMatrixMultiplication.class);
	    job.setMapperClass(MatrixMap.class);
	    //System.out.println("test################");
	    //job.setCombinerClass(Reduce.class);
	    job.setReducerClass(MatrixReduce.class);
	    
	    job.setOutputKeyClass(Text.class);
	    job.setOutputValueClass(Text.class);
	    //System.out.println("test$$$$$$$$$$$$$$$$$$$$$$");
	    FileInputFormat.addInputPath(job, new Path(otherArgs[0]));
	    FileOutputFormat.setOutputPath(job, new Path(otherArgs[1]));
	    //System.out.println("test!!!!!!!!!!!!!!!!!!!!!!!");
	    System.exit(job.waitForCompletion(true) ? 0 : 1);
	}
}
