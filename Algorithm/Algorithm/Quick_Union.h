#pragma once
#include <iostream>
#include <iomanip>
class WeightedQuickUnionUF
{
private:
	int * id;
	int * sz;
	int count;	//连通分量数量

public:
	WeightedQuickUnionUF()
	{

	}

	WeightedQuickUnionUF(int N)
	{
		count = N;
		id = new int[N];
		for(int i=0; i<N; i++) id[i] = i;
		sz = new int[N];
		for(int i=0; i<N; i++) sz[i] = 1;
		
	}
	int getCount(){return count;}

	bool connected(int p,int q)
	{
		return find(p) == find(q);
	}

	int find(int p)//查p所属的连通分量
	{
		while(p != id[p]) p = id[p];

		return p;
	}
	void Union (int p, int q)//合并p, q 所属的连通分量
	{
		int i = find(p);
		int j = find(q);
		
		if (i==j) return;//!!

		if( sz[i] < sz[j] ) 
		{
			id[i] = j;
			sz[j] += sz[i];
		}
		else 
		{
			id[j] = i;
			sz[i] += sz[j];
		}
		
		count --;

	}

	void test()
	{
		int N = 10;
		WeightedQuickUnionUF wqu(N);
		wqu.Union(1,9);
		wqu.Union(3,6);
		wqu.Union(9,8);

		std::cout<<std::setw(7)<<"label"<<std::setw(7)<<"id"<<std::setw(7)<<"size"<<'\n';
		for(int i=0; i<N; i++)
		{
			std::cout<<std::setw(7)<<i<<std::setw(7)<<wqu.find(i)<<std::setw(7)<<wqu.sz[i]<<std::endl;
		}
		system("pause");
	}


};

