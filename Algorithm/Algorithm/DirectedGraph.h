#pragma once

#include <iostream>
#include <vector>
#include <fstream>

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

	int V(){ return m_v; }
	int E(){ return m_e; }
	
	std::vector<int > adj(int v)
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