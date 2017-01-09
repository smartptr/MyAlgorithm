/*
 * author: cuizhigang
 * date: 20170104
 * function: 利用GA算法解决TSP问题
 */

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
using namespace std;

const int city_num = 10; //城市个数
const int unit_num = 100; //种群个数
int ps = 10; //变异概率(1-100,浮点数转整数)
const int maxiter = 500; 

//城市间距离映射 最优解权值=10
int map_data[10][10];
struct Unit
{
	int path[city_num];
	int length;	
};

bool comparetor(const Unit& p, const Unit& q)
{
	return p.length < q.length;
}

class Group
{
public:
	Unit group[unit_num];
	Unit best;
	int best_gen;
	Group()
	{
		best.length = 0x3f3f3f3f;
		best_gen = 0;
		for(int i = 0; i < unit_num; i++)
		{
			bool flag[city_num] = {};
			for(int j = 0; j < city_num; j++)
			{
				int t_city = rand() % city_num;
				//cout<< t_city<<endl;
				while(flag[t_city])
					t_city = rand() % city_num;
				group[i].path[j] = t_city;
				flag[t_city] = true;
			}
		}
		//cout<<"test"<<endl;
	}

	//适量度函数
	void access()
	{
		for(int k = 0; k < unit_num; k++)
		{
			int tmp = 0;
			for(int i = 1; i < city_num; i++)
			{
				tmp += map_data[group[k].path[i-1]][group[k].path[i]];
			}
			tmp += map_data[group[k].path[city_num-1]][group[k].path[0]];
			group[k].length = tmp;
		}
	}
	
	//根据评估结果进行排序
	void unit_sort()
	{
		sort(group, group + unit_num, comparetor);
	}
	
	//交叉
	Unit cross(const Unit& father, const Unit& mather)
	{
		int l = rand() % city_num;
		int r = rand() % city_num;
		if(l > r)
			swap(l, r);
		bool flag[city_num] = {};
		for(int i = l; i <= r; i++)
		{
			flag[father.path[i]] = true;
		}
		Unit son;	
		int pos = 0;
		for(int i = 0; i < l; i++)
		{
			while(flag[mather.path[pos]])
				++pos;
			son.path[i] = mather.path[pos++];
		}
		for(int i = l; i <= r; i++)
		{
			son.path[i] = father.path[i];
		}
		for(int i = r + 1; i < city_num; i++)
		{
			while(flag[mather.path[pos]])
				++pos;
			son.path[i] = mather.path[pos++];
		}
		//cout<<pos<<endl;
		return son;
	}
	
	//突变
	void mutation(Unit& t)
	{
		int p = rand() % 100;
		if(p > ps)
			return ;
		int one = rand() % city_num;
		int two = rand() % city_num;
		while(two == one)
			two = rand() % city_num;
		//cout<<one<<two<<endl;
		swap(t.path[one], t.path[two]);
	}

	//打印
	void print()
	{
		for(int i = 0; i < unit_num; i++)
		{
			printf("第%d个个体，路径信息：", i);
			for(int j = 0; j < city_num; j++)
				printf("%d ", group[i].path[j]);
			printf(";总权值：%d;\n", group[i].length);	
		}
		printf("最优个体，路径信息：");
		for(int j = 0; j < city_num; j++)
			printf("%d ", group[0].path[j]);
		printf(";总权值：%d;\n", group[0].length);
	}
	
	//进化过程
	void work()
	{
		for(int i = 0; i < maxiter; i++)
		{
			if(i > 30)
				ps *= 3;
			access();
			unit_sort();
			if(best.length > group[0].length)
			{
				memcpy(&best, &group[0], sizeof(group[0]));
				best_gen = i;
			}
			for(int j = 0; j + 2 < city_num; j++)
			{
				group[j+2] = cross(group[j], group[j+1]);
			}
			for(int j = 0; j < city_num; j++)
				mutation(group[j]);	
		}
	}
};
