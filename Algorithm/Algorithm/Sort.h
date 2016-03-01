#pragma once
#include <vector>

template <typename T>
class CSort
{
//private:
//	T * a;
public:
	//CSort(vector<T> a);
	bool less(T a, T b)
	{
		return a < b;
	}
	void exch(vector<T> & a ,int i, int j)
	{
		T tmp = a[i];
		a[i] = a[j];
		a[j] = tmp;
	}
	bool isSorted(vector<T> a)
	{
		for(vector<T> ::iterator iter = ++a.begin();iter != a.end();iter++)
		{
			if( (*iter),*(--iter) ) return false;

		}
		return true;
	}
	//—°‘Ò≈≈–Ú
	void Selection(vector<T> & a)
	{
		for(int i=0;i<a.size();i++)
		{
			int min = i;
			for(int j=i+1;j<a.size();j++)
			{
				 if ( less(a[j],a[min]) )
				 {
					min = j;
				 }
			}
			exch(a,min,i);
		}
	}
	//≤Â»Î≈≈–Ú
	void Insertion(vector<T> & a)
	{
		int N = a.size();
		for(int i=1; i<N; i++)
		{
			for(int j=i; j>0; j--)
			{
				if ( less(a[j],a[j-1]) ) exch(a,j,j-1);
			}
		}
	}

	//shell sort
	void Shell(vector<T> & a)
	{
		int N = a.size();
		
	}

	void test()
	{
		CSort<int> s;
		std::cout<<"Please input some integers:"<<std::endl;
		int input;
		vector<int> buf;
		vector<int> buf2;

		//buf.push_back(10);
		//buf.push_back(4);
		//buf.push_back(1);
		//buf.push_back(13);
		//buf.push_back(30);
		//buf.push_back(33);
		while(std::cin>>input)
		{
			buf.push_back(input);
			buf2.push_back(input);
		}
		s.Selection(buf);
		s.Insertion(buf2);
		std::cout<<"result of selection sort: "<<'\n';
		for(int i=0; i < buf.size();i++)
		{
			std::cout<<buf.at(i)<<' ';
		}

		std::cout<<"result of insertion sort: "<<'\n';
		for(int i=0; i < buf2.size();i++)
		{
			std::cout<<buf2.at(i)<<' ';
		}

		std::cout<<endl;

		system("pause");
	}
};