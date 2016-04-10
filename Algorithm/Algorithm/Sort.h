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
	void exch(std::vector<T> & a ,int i, int j)
	{
		T tmp = a[i];
		a[i] = a[j];
		a[j] = tmp;
	}
	bool isSorted(std::vector<T> a)
	{
		for(std::vector<T> ::iterator iter = ++a.begin();iter != a.end();iter++)
		{
			if( (*iter),*(--iter) ) return false;

		}
		return true;
	}
	//选择排序
	void Selection(std::vector<T> & a)
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
	//插入排序
	void Insertion(std::vector<T> & a)
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
	void Shell(std::vector<T> & a)
	{
		int N = a.size();
		//...
	}

	//归并排序
	void merge(std::vector<T> & a ,std::vector<T> & aux, int lo, int mid, int hi)//[lo..mid] 和[mid+1..hi]
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
	void mSort(std::vector<T> & a, std::vector<T> & aux, int lo, int hi)
	{
		if (lo >= hi) return;
		int mid = lo + (hi -lo)/2;//(lo+hi)/2;
		mSort(a,aux,lo,mid);
		mSort(a,aux,mid+1,hi);//mSort(a,aux,mid,hi);
		merge(a,aux,lo,mid,hi);

	}
	void MergeSort(std::vector<T>& a )
	{
		std::vector <T> * aux = new std::vector <T>(a.size());
		mSort(a,*aux,0,a.size()-1);
		//for (int i=0;i<aux->size();i++)
		//	a[i] = (*aux)[i];
		delete aux;
	}
	
	void MergeSortBU(std::vector<T> & a)
	{
		int N = a.size();
		std::vector<T> * aux = new std::vector<T>( N );
		for(int sz = 1; sz< N; sz = sz + sz)//for(int sz = 1; sz<= N/2; sz = sz + sz)//注意(N+1)/2,N 奇偶不同时，+1保证merge所有部分
		{
			for(int lo = 0; lo<N - sz; lo += sz+sz)
			{	
				merge(a,*aux,lo,lo+sz-1,min(lo+sz+sz-1,N-1));
			}
		}

		delete aux;
	}

	//快速排序
	int  partition(std::vector<T> & a, int lo, int hi)
	{
		T q = a[lo];
		int i=lo,j=hi+1;
		while(1)
		{
			//if (i>=j) break;

			/*if (a[i] < q) i++;
			else if (a[j] > q) j++;
			else exch(a,i,j);*/

			while( a[++i] < q && i<hi);
			while( a[--j] > q && j>lo);
			if ( i>=j ) break;
			exch(a,i,j); 

		}
		exch(a,lo,j); //注意返回j 而非 i 二者交叉进入对方领域
		return j;
	}
	void qSort(std::vector<T> & a,int lo,int hi)
	{
		if (lo>=hi) return;

		int j = partition(a, lo, hi);
		qSort(a, lo, j-1);//qSort(a, lo, j);
		qSort(a, j+1, hi);

	}
	void QuickSort(std::vector<T> & a)
	{
		qSort(a,0,a.size()-1);
	}

	//堆排序
	void buildHeap(std::vector<T> & a)
	{
		int N = a.size()-1;//首元素无效
		for(int i= N/2; i>0;i--)
		{
			sink(a,i,N);
		}
	}
	void swim(std::vector<T> & a,int i,int N)//N = a.size()-1
	{
		while(i/2 > 0)
		{
			int j = i/2;
			if (a[j]<a[i]) exch(a,i,j);
			else break;

			i=j;
		}
	}
	void sink(std::vector<T> & a,int i, int N)
	{
		while(2*i<=N)//while(2*i<N)
		{
			int j = 2*i;
			if (j<N && a[j]<a[j+1]) j++; //if (a[j] < a[j+1]) j++; 
			
			/*if (a[i]<a[j]) 
			{
				exch(a,i,j);
				i=j;
			}*/
			if (a[i]>=a[j]) break;
			exch(a,i,j);
			i=j;
		}
	}
	void HeapSort(std::vector<T> & a)
	{
		int N = a.size();
		buildHeap(a);
		while(N>1)
		{
			exch(a,1,N--);
			sink(a,1,N);
		}

	}

//test
	void test()
	{
		CSort<int> s;
		std::cout<<"Please input some integers:"<<std::endl;
		int input;
		std::vector<int> buf;
		std::vector<int> buf2;
		std::vector<int> buf3;
		std::vector<int> buf4;
		std::vector<int> buf5;
		std::vector<int> buf6;
		buf6.push_back(0);
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
			buf4.push_back(input);
			buf5.push_back(input);
			buf6.push_back(input);
		}
		s.Selection(buf);
		s.Insertion(buf2);
		s.MergeSort(buf3);
		s.MergeSortBU(buf4);
		s.QuickSort(buf5);
		s.QuickSort(buf6);
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
		std::cout<<"\nresult of merge sort bottom to up: "<<'\n';
		for(int i=0; i < buf4.size();i++)
		{
			std::cout<<buf4.at(i)<<' ';
		}

		std::cout<<"\nresult of quick sort: "<<'\n';
		for(int i=0; i < buf5.size();i++)
		{
			std::cout<<buf5.at(i)<<' ';
		}
		std::cout<<"\nresult of heap sort: "<<'\n';
		for(int i=0; i < buf6.size();i++)
		{
			std::cout<<buf6.at(i)<<' ';
		}

		std::cout<<endl;

		system("pause");
	}
};