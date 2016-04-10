#pragma once 
#include <iostream>
#include <vector>
#include <stack>
#include <queue>

#include <string>
#include <sstream>

//definition of undirected graph 
class Graph
{
private:
	int v;//number of vertices
	int e;
	std::vector<int> * adjList;

public:
	//Graph(int V)//build a undirected graph with V vertices and no edge
	//{
	//	adjList =new std::vector<int> [V];
	//}
	Graph(){ v=0; e=0; adjList = NULL; }
	Graph(std::istream & In)
	{
		int vn,en;
		In>>vn>>en;

		adjList =(std::vector<int> * )new std::vector<int> [vn];
		v = vn;
		e = 0;
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

		if(adjList != NULL) delete [] adjList;

		adjList =(std::vector<int> * )new std::vector<int> [vn];
		v = vn;
		e = 0;
		for(int i=0;i<en;i++)
		{
			int vi,wi;
			In>>vi>>wi;
			addEdge(vi,wi);
		}
	}

	
	int V()const {return v;}
	int E()const {return e;}
	void addEdge(int v, int w)
	{
		adjList[v].push_back(w);
		adjList[w].push_back(v);
		e++;
	}
	std::vector<int> adj(int v) const
	{
		return adjList[v];
	}
	std::string toString()
	{
		std::stringstream ss;
		ss<<v;
		std::string s = ss.str()+std::string(" vertices, ");
		ss.str("");ss<<e;
		s += ss.str() + std::string(" edges\n") ;
		//	s	+= e+ " edges\n";
		for(int vi=0; vi<v; vi++)
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
		infile.open("data/tinyG.txt");
		if (infile.is_open())
		{
			Graph g(infile);
			std::string gs = g.toString();
			std::cout<<gs<<std::endl;
		}
		infile.close();

		Graph gg;
		infile.open("data/tinyG.txt");
		if (infile.is_open())
		{
			gg.build(infile);
		}
		std::string gs = gg.toString();
		std::cout<<gs<<std::endl;


	}

};


class DepthFirstSearch
{
private: 
	bool *marked;
	int count; //the number of nodes can be reached from s
	std::vector<int> connectedID;
public:
	DepthFirstSearch(){}
	DepthFirstSearch(const Graph & G, int s)
	{
		marked = new bool[G.V()];
		memset(marked,0,sizeof(bool) * G.V());
		count = 0;
		dfs(G,s);
	}

	void dfs(const Graph & G,int s)
	{
		if( marked[s]) return;

		marked[s] = true;///
		connectedID.push_back(s);
		count ++;
		std::vector<int> s_adj = G.adj(s);
		for(int i=0; i<s_adj.size(); i++)
		{
			dfs(G,s_adj.at(i) );
		}
	}
	int Count()const	//return the number of nodes can be reached by s
	{
		return count;
	}

	//print the node id can be reached from s
	void print()
	{
		for(int i=0; i<connectedID.size(); i++)
		{
			std::cout<<connectedID.at(i)<<" ";
		}
		std::cout<< std::endl;
	}

	void test()
	{
		std::ifstream infile;
		Graph g;
		infile.open("data/tinyG.txt");
		if (infile.is_open()) g.build(infile);
		std::string gs = g.toString();
		std::cout<<gs<<std::endl;

		int s = 7;
		DepthFirstSearch Dfs(g,s);
		std::cout<<Dfs.Count()<<" nodes can be reached from node "<<s<<":"<< std::endl;
		
		//print the node id 
		Dfs.print();
	}
};


class DepthFirstPaths
{
private: 
	bool *marked;
	int * edgeTo;
	int s;
	int count; //the number of nodes can be reached from s
	std::vector<int> connectedID;
public:
	DepthFirstPaths(){}
	DepthFirstPaths(const Graph & G, int s)
	{
		marked = new bool[G.V()];
		edgeTo = new int[G.V()];
		memset(marked,0,sizeof(bool) * G.V());
		memset(edgeTo,-1,sizeof(int) * G.V());
		DepthFirstPaths::s = s;
		count = 0;
		dfs(G,s);
	}

	void dfs(const Graph & G,int s)
	{
		if( marked[s]) return;

		marked[s] = true;///
		//edgeTo[s] = s;			//connectedID.push_back(s);
		count ++;
		std::vector<int> s_adj = G.adj(s);
		for(int i=0; i<s_adj.size(); i++)
		{
			int v = s_adj.at(i);
			if(!marked[v])
			{
				edgeTo[v] = s; 
				dfs(G,v );
			}
			
		}
	}
	int Count()const	//return the number of nodes can be reached by s
	{
		return count;
	}
	bool hasPathTo(int v)
	{
		return marked[v];
	}
	
	std::stack<int> pathTo(int v)
	{
		std::stack<int> path;
 		if (!hasPathTo(v)) return path; 

		for(int x=v; x != s; x = edgeTo[x])
		{
			path.push(x);
		}
		path.push(s);

		return path;
	}
	
	void test()
	{
		std::ifstream infile;
		Graph g;
		infile.open("data/tinyG.txt");
		if (infile.is_open()) g.build(infile);
		std::string gs = g.toString();
		std::cout<<gs<<std::endl;

		int s = 0;
		DepthFirstPaths Dfp(g,s);
		std::cout<<Dfp.Count()<<" nodes can be reached from node "<<s<<":"<< std::endl;

		//print the node id 
		int v = 6;
		std::stack<int> p = Dfp.pathTo(v);
		std::cout<<"The path to node "<<v<<": "<<std::endl;
		while(! p.empty())
		{
			std::cout<< p.top()<<" ";
			p.pop();
		}
		std::cout<<std::endl;
	}

};

class BreathFirstPaths
{
private:
	bool * marked;
	int	 * edgeTo;
	int s ;
	int count;
	std::queue<int> Queue;
public:
	BreathFirstPaths(){};
	BreathFirstPaths(const Graph & G,int s):s(s),count(0)
	{
		marked = new bool [G.V()];
		memset(marked,false,sizeof(bool) * G.V());
		edgeTo = new int [G.V()];
		memset(edgeTo,-1,sizeof(int) * G.V());

		
		bfs(G,s);
	}
	void bfs(const Graph & G, int s)
	{
		marked[s] = true;
		edgeTo[s] = s;//
		Queue.push(s);
		
		while(! Queue.empty())
		{
			int f = Queue.front();
			Queue.pop();
			count ++;

			std::vector<int> s_adj = G.adj(f);
			for(int i=0; i< s_adj.size();i++ )
			{
				int w = s_adj.at(i);
				if (! marked[w])
				{
					marked[w] = true;
					edgeTo[w] = f;
					Queue.push(w);

				}
			}
		}
		
	}

	bool hasPathTo(int v)
	{
		return marked[v];
	}
	std::stack<int> pathTo(int v)
	{
		std::stack<int> path;
		for(int x=v; x != s; x=edgeTo[x])
		{
			path.push(x);
		}
		path.push(s);

		return path;
	}
	int  Count()const {return count; }

	void test()
	{
		std::ifstream infile;
		Graph g;
		infile.open("data/tinyG.txt");
		if (infile.is_open()) g.build(infile);
		std::string gs = g.toString();
		std::cout<<gs<<std::endl;

		int s = 0;
		BreathFirstPaths Bfp(g,s);
		std::cout<<Bfp.Count()<<" nodes can be reached from node "<<s<<":"<< std::endl;

		//print the node id 
		int v = 6;
		std::stack<int> p = Bfp.pathTo(v);
		std::cout<<"The path to node "<<v<<": "<<std::endl;
		while(! p.empty())
		{
			std::cout<< p.top()<<" ";
			p.pop();
		}
		std::cout<<std::endl;
	}

};



class CC //Connected Component
{
private:
	bool * marked;
	int  * id;
	int count; // 连通分量数目

public:
	CC (){};
	CC( const Graph & G):count(0)
	{
		marked = new bool[G.V()];
		memset(marked,0,sizeof(bool) * G.V());
		id = new int [G.V()];
		memset(id,-1,sizeof(int) * G.V());

		for(int s=0; s<G.V(); s++)
		{
			if (!marked[s])
			{
				//marked[s] = true;
				count ++;
				dfs(G,s);
				//count ++;//
			}
		}
	}

	void dfs(const Graph & G,int s)
	{
		marked[s] = true;
		id[s] = count; //count 从1开始
		std::vector<int> s_adj = G.adj(s) ;
		for(int i = 0; i<s_adj.size(); i++)
		{
			int w = s_adj.at(i);
			if (!marked[w])
			{
				//id[w] = count;
				dfs(G,w);
			}
		}
	}

	bool connected(int v, int w)
	{	return id[v] == id[w]; }
	
	int ID(int v) 
	{ return id[v] ;}

	int Count()
	{ return count; }


	void test()
	{
		std::ifstream infile;
		Graph g;
		infile.open("data/tinyG.txt");
		if (infile.is_open()) g.build(infile);
		std::string gs = g.toString();
		std::cout<<gs<<std::endl;

		int s = 0;
		CC cc(g);
		std::cout<<"There are "<<cc.Count()<<" connected components in the graph."<<std::endl;

		//print the node id 
		int v = 6;
		
		std::cout<<"The CC containing node "<<v<<": "<<std::endl;
		for(int i=0; i<g.V(); i++)
		{

			if (cc.connected(v,i))
			{
				std::cout<< i<<" ";
		
			}
				
		}
		std::cout<<std::endl;
	}
	

};