#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
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

	Digraph reverse()
	{
		Digraph R = Digraph(m_v);

		for(int v=0; v<m_v; v++)
		{
			std::vector<int> adj_v = adjList[v];
			for(int j =0; j<adj_v.size(); j++)
			{
				R.addEdge(adj_v.at(j), v);
			}
		}
		return R;
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
		//±È¿˙…≠¡÷
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