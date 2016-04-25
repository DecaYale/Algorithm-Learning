#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <sstream>
class Digraph
{
private:
	int m_v;
	int m_e;
	std::vector<int> * adjList;

public:
	Digraph(){};
	Digraph(int v):m_v(v),m_e(0)
	{
		adjList = new std::vector<int> [v];

	}
	Digraph(std::istream & In)
	{
		int vn,en;
		In>>vn>>en;

		adjList =(std::vector<int> * )new std::vector<int> [vn];
		m_v = vn;
		m_e = 0;
		for(int i=0;i<en;i++)
		{
			int vi,wi;
			In>>vi>>wi;
			addEdge(vi,wi);
		}
	}
	void build(std::istream & In)
	{
		int vn,en;
		In>>vn>>en;

		adjList =(std::vector<int> * )new std::vector<int> [vn];
		m_v = vn;
		m_e = 0;
		for(int i=0;i<en;i++)
		{
			int vi,wi;
			In>>vi>>wi;
			addEdge(vi,wi);
		}
	}
	void addEdge(int v, int w)
	{
		adjList[v].push_back(w);
		m_e++;
	}

	int V()const{ return m_v; }
	int E()const{ return m_e; }
	
	std::vector<int > adj(int v) const 
	{
		return adjList[v];
	}

	Digraph reverse()const
	{
		Digraph * R = new Digraph(m_v);

		for(int v=0; v<m_v; v++)
		{
			std::vector<int> adj_v = adjList[v];
			for(int j =0; j<adj_v.size(); j++)
			{
				R->addEdge(adj_v.at(j), v);
			}
		}
		return *R;
	}

	std::string toString()
	{
		std::stringstream ss;
		ss<<m_v;
		std::string s = ss.str()+std::string(" vertices, ");
		ss.str("");ss<<m_e;
		s += ss.str() + std::string(" edges\n") ;
		//	s	+= e+ " edges\n";
		for(int vi=0; vi<m_v; vi++)
		{
			ss.str("");ss<<vi;
			s += ss.str()+std::string(": ");
			for(int wi=0;wi<adjList[vi].size();wi++ ) 
			{
				//std::stringstream ss;
				ss.str("");ss<<adjList[vi].at(wi);
				s += ss.str() + std::string(" ");
			}
			s += std::string("\n");
		}
		return s;
	}

	void test()
	{
		std::ifstream infile;
		infile.open("data/tinyDG.txt");
		if (infile.is_open())
		{
			Digraph g(infile);
			std::string gs = g.toString();
			std::cout<<gs<<std::endl;
		}
		infile.close();

		Digraph gg;
		infile.open("data/tinyDG.txt");
		if (infile.is_open())
		{
			gg.build(infile);
		}
		std::string gs = gg.toString();
		std::cout<<gs<<std::endl;

		Digraph rg = gg.reverse();
		std::cout<<"The reversed graph:\n"<<rg.toString() <<std::endl;
	}
};


class DirectedDFS
{
private:
	bool * marked;
	//vector<int> * adjList;
public:
	DirectedDFS();
	DirectedDFS(Digraph G, int s)
	{
		marked = new bool[G.V()];
		memset(marked,false,sizeof(bool) * G.V());
		dfs(G,s);
	}

	void dfs(Digraph G, int v)
	{
		marked[v] = true;
		std::vector<int> adj_v = G.adj(v);
		for(int i=0; i<adj_v.size(); i++)
		{
			int w = adj_v.at(i);
			if (!marked[w])
			{
				dfs(G,w);
			}
		}
		
	}

	////print the node id can be reached from s
	//void print()
	//{
	//	for(int i=0; i<connectedID.size(); i++)
	//	{
	//		std::cout<<connectedID.at(i)<<" ";
	//	}
	//	std::cout<< std::endl;
	//}
	//void test()
	//{
	//	std::ifstream infile;
	//	Digraph g;
	//	infile.open("data/tinyDG.txt");
	//	if (infile.is_open()) g.build(infile);
	//	std::string gs = g.toString();
	//	std::cout<<gs<<std::endl;

	//	int s = 7;
	//	DepthFirstSearch Dfs(g,s);
	//	std::cout<<	" nodes can be reached from node "<<s<<":"<< std::endl;

	//	//print the node id 
	//	Dfs.print();
	//}

};

//寻找有向环
class DirectedCycle
{
private: 
	bool * marked;
	bool * onstack;
	int * edgeTo;
	std::stack<int > cycle;
public:
	DirectedCycle(){};
	DirectedCycle(const Digraph & G)
	{
		marked = new bool[G.V()];
		memset(marked,false,sizeof(bool) * G.V());
		onstack = new bool[G.V()];
		memset(onstack,false,sizeof(bool) * G.V());
		edgeTo = new int[G.V()];
		memset(edgeTo,-1,sizeof(int) * G.V());
		//遍历森林
		for(int v=0; v<G.V(); v++)
			if (!marked[v]) dfs(G,v);

	}
	void dfs(const Digraph G ,int v)
	{
		marked[v] = true;
		std::vector<int> adj_v = G.adj(v);

		for(int i=0; i<adj_v.size(); i++)
		{
			int w = adj_v.at(i);
			onstack[w] = true;
			if (hasCycle())
			{
				return;
			}
			if (!marked[w])
			{
				edgeTo[w] = v;
				dfs(G,w);
			}
			else if (onstack[w])
			{
				for(int x=v; x!=w; x= edgeTo[x])
				{
					cycle.push(x);
				}
				cycle.push(w);
				cycle.push(v);

			}

		}
		onstack[v] = false;

	}

	bool hasCycle()
	{
		return cycle.size() != 0;
	}
	std::stack<int> Cycle()
	{
		return cycle;
	}

	void test()
	{
		std::ifstream infile;
		infile.open("data/tinyDG.txt");

		Digraph gg;
		if (infile.is_open())
		{
			gg.build(infile);
		}
		std::string gs = gg.toString();
		std::cout<<gs<<std::endl;

		DirectedCycle dc(gg);

		std::cout<<"The input Digraph has cycles?(bool) "<<dc.hasCycle()<<std::endl;
		std::cout<<"The first cycle that has been found is: "<<std::endl;
		std::stack<int> cyc = dc.Cycle();
		for(;cyc.size()!=0;cyc.pop())
		{
			std::cout<<cyc.top()<<' ';
		}
		std::cout<<'\n';
		system("pause");
	}
};


class DepthFirstOrder
{
private:
	bool * marked;
	std::queue<int> pre;
	std::queue<int> post;
	std::stack<int> reversePost;
	//vector<int> * adjList;
public:
	DepthFirstOrder(){};
	DepthFirstOrder(const Digraph & G)
	{
		marked = new bool[G.V()];
		memset(marked,false,sizeof(bool) * G.V());
		for(int v=0; v<G.V(); v++)
		{
			if (!marked[v]) dfs(G,v);
		}
		
	}

	void dfs(Digraph G, int v)
	{
		pre.push(v);
		marked[v] = true;
		std::vector<int> adj_v = G.adj(v);
		for(int i=0; i<adj_v.size(); i++)
		{
			int w = adj_v.at(i);
			if (!marked[w])
			{
				dfs(G,w);
			}
		}
		post.push(v);
		reversePost.push(v);

	}
	std::queue<int> Pre()
	{
		return pre;
	}
	std::queue<int> Post()
	{
		return post;
	}
	std::stack<int> ReversePost()
	{
		return reversePost;
	}

};

//算法4.5 拓扑排序
class Topological
{
private:
	std::stack<int> order;
public:
	Topological(const Digraph & G)
	{
		DirectedCycle * cyclefinder = new DirectedCycle(G);
		if (! cyclefinder->hasCycle())
		{
			DepthFirstOrder * dfo = new DepthFirstOrder(G);
			order = dfo->ReversePost();
		}
	}

	std::stack<int> Order()
	{
		return order;
	}
	bool isDAG()
	{
		return order.size() != 0;
	}

	void test()
	{
		std::ifstream infile;
		infile.open("data/tinyDG.txt");

		Digraph gg;
		if (infile.is_open())
		{
			gg.build(infile);
		}
		std::string gs = gg.toString();
		std::cout<<gs<<std::endl;

		DirectedCycle dc(gg);

		std::cout<<"The input Digraph has cycles?(bool) "<<dc.hasCycle()<<std::endl;
		std::cout<<"The first cycle that has been found is: "<<std::endl;
		std::stack<int> cyc = dc.Cycle();
		for(;cyc.size()!=0;cyc.pop())
		{
			std::cout<<cyc.top()<<' ';
		}
		std::cout<<'\n';
		system("pause");
	}
};

//计算强连通分量的Kosaraju算法
class KosarajuSCC
{
private:
	int * id;
	bool * marked;
	int count;

public:
	KosarajuSCC(){};
	KosarajuSCC(const Digraph & G):count(0)
	{
		id = new int[G.V()];
		memset(id, -1, sizeof(int) * G.V());
		marked = new bool[G.V()];
		memset(marked,false, sizeof(bool)*G.V());
		
		DepthFirstOrder * order = new DepthFirstOrder(G.reverse()); ///
		std::stack<int> reversePost = order->ReversePost();
		while(!reversePost.empty())
		{
			int v = reversePost.top();
			reversePost.pop();

			if (!marked[v])
			{
				dfs(G, v); count++;
			}
			
		}

	}
	void dfs(const Digraph & G, int v)
	{

		marked[v] = true;
		id[v] = count;

		std::vector<int> adj_v = G.adj(v);
		for(int i=0; i<adj_v.size(); i++)
		{
			int w = adj_v.at(i);
			if (!marked[w])
			{
				dfs(G, w);
			}
		}
	}
	bool stronglyConnected(int v, int w)
	{
		return id[v] == id[w];
	}
	int Id(int v)
	{
		return id[v];
	}
	int Count()
	{
		return count;
	}

	void test()
	{
		std::ifstream infile;
		infile.open("data/tinyDG.txt");

		Digraph gg;
		if (infile.is_open())
		{
			gg.build(infile);
		}
		else exit(1);
		std::string gs = gg.toString();
		std::cout<<gs<<std::endl;

		KosarajuSCC kscc(gg);


		std::cout<<"The input Digraph has "<<kscc.Count()<<" strongly connected componets."<<std::endl;
		std::cout<<"The strongly connected componets include: "<<std::endl;
		
		for(int idi=0; idi<kscc.Count(); idi++)
		{
			for(int i=0; i<gg.V(); i++)
			{
				if (kscc.Id(i) == idi)
				{
					std::cout<<i<<" ";
				}
			}
			std::cout<<"\n";
		}
		//std::cout<<'\n';
		system("pause");
	}
	
};