#include "stdio.h"
#include <iostream>
#include <fstream>
#include <string>

#include "Queue.h"
#include "Quick_Union.h"
#include "Sort.h"
#include "UndirectedGraph.h"
#include "DirectedGraph.h"
using namespace std;


#if 1
int main()
{
	DirectedCycle Dc;
	Dc.test();
}
#elif 1
int main()
{
	Digraph Dg;
	Dg.test();
	
	system("pause");
}

#elif 1
int main(int argc, char ** arg)
{
	DepthFirstSearch Dfs;
	Dfs.test();

	DepthFirstPaths Dfp;
	Dfp.test();

	BreathFirstPaths Bfp;
	Bfp.test();

	CC cc;
	cc.test();
	system("pause");
}
#elif 1
int main()
{
	ifstream infile("data/tinyG.txt");
	if (infile.is_open())
	{
		Graph g(infile);
		string gs = g.toString();
		cout<<gs<<endl;
	}
	/*Graph g;
	g.test();*/
	system("pause");
}
#elif 1
//test sort algorithms
int main()
{
	CSort<int> s;
	s.test();
}
#elif 1
//test quick union 
int main()
{
	WeightedQuickUnionUF a(10);
	a.test();
}

#elif 0
int main()
{
	char input[100];
	char  test[] = {'1','2','3','4','5','6','7'};
	/*while( EOF != scanf("%s",input) )
	{
		printf("%s\n",input);
	}*/
	Queue<char> q;
	for(int i=0; i<7; i++)
	{
		q.enqueue(test[i]);
	}
	while(q.size())
	{
		char tmp = q.dequeue();
		printf("%c\n",tmp);
	}

	system("pause");
	return 0;
}

#endif