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
		//...
	}

	//πÈ≤¢≈≈–Ú
	void merge(vector<T> & a ,vector<T> & aux, int lo, int mid, int hi)//[lo..mid] ∫Õ[mid+1..hi]
	{
		int i = lo,j =mid+1;

		for (int k=lo;k<=hi;k++)//!!
		{
			aux[k] = a[k];
		}
		for(int k=lo; k <= hi; k++)
		{
			if (i>mid) a[k] = aux[j++];
			else if (j>hi) a[k] = aux[i++];
			else if ( less(aux[i],aux[j]) ) a[k] = aux[i++];
			else a[k] = aux[j++];
		}
	}
	void mSort(vector<T> & a, vector<T> & aux, int lo, int hi)
	{
		if (lo >= hi) return;
		int mid = lo + (hi -lo)/2;//(lo+hi)/2;
		mSort(a,aux,lo,mid);
		mSort(a,aux,mid+1,hi);//mSort(a,aux,mid,hi);
		merge(a,aux,lo,mid,hi);

	}
	void MergeSort(vector<T>& a )
	{
		vector <T> * aux = new vector <T>(a.size());
		mSort(a,*aux,0,a.size()-1);
		//for (int i=0;i<aux->size();i++)
		//	a[i] = (*aux)[i];
		delete aux;
	}
	


	void test()
	{
		CSort<int> s;
		std::cout<<"Please input some integers:"<<std::endl;
		int input;
		vector<int> buf;
		vector<int> buf2;
		vector<int> buf3;
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
			buf3.push_back(input);
		}
		s.Selection(buf);
		s.Insertion(buf2);
		s.MergeSort(buf3);
		std::cout<<"result of selection sort: "<<'\n';
		for(int i=0; i < buf.size();i++)
		{
			std::cout<<buf.at(i)<<' ';
		}

		std::cout<<"\nresult of insertion sort: "<<'\n';
		for(int i=0; i < buf2.size();i++)
		{
			std::cout<<buf2.at(i)<<' ';
		}
		std::cout<<"\nresult of merge sort: "<<'\n';
		for(int i=0; i < buf3.size();i++)
		{
			std::cout<<buf3.at(i)<<' ';
		}

		std::cout<<endl;

		system("pause");
	}
};