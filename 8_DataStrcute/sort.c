#include <stdio.h>
#include <string.h>

/*
 *description:快速排序
 * */
//排序后按从小到大输出

using namespace std;
typedef struct  
{
	int key;
	int other;  //记录其他数据域
	int next;
}RecType;

RecType S[number+1];

int Partirion(RecType R[],int l,int h)
{
	//交换记录子序列R[1..h]中的记录，使枢纽记录交换到正确的位置，并返回其所在的位置
	int i=l;
	int j=h;              //用变量i,j记录待排序记录的首尾位置
	R[0]=R[i];            //以子表的第一个记录作为枢轴，将其暂存到记录R[0]中
	int x=R[i].key;       //用变量x存放枢纽记录的关键字
	while (i<j)
	{
		//从表的两端交替地向中间扫描
		while (i<j&&R[j].key>=x)
		{
			j--;
		}
		R[i]=R[j];          //将比枢纽小的记录移到低端
		while (i<j&&R[i].key<=x)
		{
			i++;
		}
		R[j]=R[i];          //将比枢纽大的记录移到高端
	}
	R[i]=R[0];              //枢纽记录到位
	return i;               //返回枢纽位置
}


void QuickSort(RecType R[],int s,int t)
{
	//对记录序列R[s..t]进行快速排序
	if (s<t)
	{
		int k,i;
		k=Partirion(R,s,t);
		QuickSort(R,s,k-1);
		QuickSort(R,k+1,t);
		cout<<"QuickSort:\n";
		for(i=2;i<=t;i++)
			cout<<setw(4)<<R[i].key;
		cout<<endl;
	}
}

int _tmain()
{
	RecType SL[100];
	int n;
	cout<<"QuickSort.cpp运行结果:\n";
	int b[100],i;
	srand(time(0));
	cout<<"输入待排序元素个数n:";cin>>n;
	for(i=1;i<n;i++)
	{
		b[i]=rand()%100;
		SL[i].key=b[i];
	}
	cout<<"排序前数组:\n";
	for(i=1;i<n;i++)
		cout<<setw(4)<<b[i];
	cout<<endl;
	QuickSort(SL,1,n);
	cout<<"排序后数组:\n";
	for(i=2;i<=n;i++)
		cout<<setw(4)<<SL[i].key;
	cout<<endl;
	system("pause");   
}

/*
 *description:冒泡排序
 * */


/*
 *description:选择排序
 * */
//排序后按从小到大输出
using namespace std;
typedef struct 
{
	int key;
	int other; //记录其他数据域
	int next;
}RecType;
RecType S[number+1];
void SelectSort(RecType R[],int n)
{
	//对记录序列R[1..n]进行直接选择排序
	for (int i=1;i<n;i++)
	{
		int k=i;
		for (int j=i+1;j<=n;j++)
		{
			if (R[k].key>R[j].key)
			{k=j;}
		}
	if (i!=k)
	{
		RecType temp;
		temp=R[i];
		R[i]=R[k];
		R[k]=temp;
	}
	}
}
int _tmain()
{
	RecType SL[100];
	int n;
	cout<<"SelectSort.cpp运行结果:\n";
	int b[100],i;
	srand(time(0));
	cout<<"输入待排序元素个数n:";
	cin>>n;
	for(i=1;i<n;i++)
	{
		b[i]=rand()%100;
		SL[i].key=b[i];
	}
	cout<<"排序前数组:\n";
	for(i=1;i<n;i++)cout<<setw(4)<<b[i];
	cout<<endl;SelectSort(SL,n);
	cout<<"排序后数组:\n";
	for(i=2;i<=n;i++)
		cout<<setw(4)<<SL[i].key;
	cout<<endl;
	system("pause"); 
}
int main(int argc, const char *argv[])
{
	
	return 0;
}
