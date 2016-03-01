#include "stdio.h"
#include <iostream>
using namespace std;
#include "Queue.h"
#include "Quick_Union.h"
#include "Sort.h"
#if 1
int main()
{
	CSort<int> s;
	s.test();
}
#elif 1

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