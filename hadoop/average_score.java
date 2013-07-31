import java.io.IOException;
import java.util.StringTokenizer;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.GenericOptionsParser;

public class Score {

  public static class Map 
       extends Mapper<Object, Text, Text, IntWritable>{
      
    public void map(Object key, Text value, Context context
                    ) throws IOException, InterruptedException {
        String line = new String(value.getBytes(), 0, value.getLength(), "gbk");//value.toString();
	      System.out.println( line );
	      StringTokenizer itr = new StringTokenizer(line, "\n");
	      while (itr.hasMoreTokens()) {
	    	StringTokenizer ltr = new StringTokenizer(itr.nextToken());
	    	String name = ltr.nextToken();
	    	String strScore = ltr.nextToken();
	    	Text text = new Text(name);
	    	int scoreInt = Integer.parseInt(strScore);
	    	context.write(text, new IntWritable(scoreInt));
      }
    }
  }
  /*public static class Combin extends Reducer<Text, IntWritable, Text, IntWritable>{
	  public void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException{
		  int sum = 0;
		  int count = 0;
		  for (IntWritable itr : values) {
			sum += itr.get();
			++count;
		 }
		 context.write(key, new Text(sum + "," + count));
	  }
  }*/
  public static class Reduce 
       extends Reducer<Text,IntWritable,Text,IntWritable> {

    public void reduce(Text key, Iterable<IntWritable> values, 
                       Context context
                       ) throws IOException, InterruptedException {
      int sum = 0;
      int count = 0;
      for (IntWritable val : values) {
        sum += val.get();
        ++count;
      }
      int average = (int)sum/count;
      context.write(key, new IntWritable(average));
    }
  }

  public static void main(String[] args) throws Exception {
    Configuration conf = new Configuration();
    String[] otherArgs = new GenericOptionsParser(conf, args).getRemainingArgs();
    if (otherArgs.length != 2) {
      System.err.println("Usage: wordcount <in> <out>");
      System.exit(2);
    }
    Job job = new Job(conf, "word count");
    job.setJarByClass(Score.class);
    job.setMapperClass(Map.class);
    //job.setCombinerClass(Reduce.class);
    job.setReducerClass(Reduce.class);
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(IntWritable.class);
    FileInputFormat.addInputPath(job, new Path(otherArgs[0]));
    FileOutputFormat.setOutputPath(job, new Path(otherArgs[1]));
    System.exit(job.waitForCompletion(true) ? 0 : 1);
  }
}
