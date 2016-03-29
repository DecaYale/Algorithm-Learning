#pragma once 
#include <iostream>
#include <vector>
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
	Graph(std::ifstream & In)
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
	
	int V(){return v;}
	int E(){return e;}
	void addEdge(int v, int w)
	{
		adjList[v].push_back(w);
		adjList[w].push_back(v);
		e++;
	}
	std::vector<int> adj(int v)
	{
		return adjList[v];
	}
	string toString()
	{
		std::stringstream ss;
		ss<<v;
		string s = ss.str()+string(" vertices, ");
		ss.str("");ss<<e;
		s += ss.str() + string(" edges\n") ;
		//	s	+= e+ " edges\n";
		for(int vi=0; vi<v; vi++)
		{
			ss.str("");ss<<vi;
			s += ss.str()+string(": ");
			for(int wi=0;wi<adjList[vi].size();wi++ ) 
			{
				//std::stringstream ss;
				ss.str("");ss<<wi;
				s += ss.str() + string(" ");
			}
			s += string("\n");
		}
		return s;
	}


};