/*
Developed By Gaosx
大作业要求中的对局删除功能
原理是把不需要删除的部分写入另外一个文件(GS.csv)，删除原文件(GameStep.csv)，然后重命名
*/
#include<bits/stdc++.h>
#include<Windows.h>
#pragma GCC optimize("Ofast,no-stack-protector")
using namespace std;
short ReaD(){//输入一个数
	char c=getchar();short k=1;
	while(c<'0'||c>'9'){
		if(c=='-')k=-1;
		if(c==EOF)return -101;
		c=getchar();
	}
	short r=0;
	while(c>='0'&&c<='9'){
		r=r*10+(c^48);
		c=getchar();
	}
	return k*r;
}
unordered_map<int,bool> mp;
int main(){
	printf("需要删除第几轮的对局记录(可输入多组数据，以0结束)：");
	for(short i=ReaD();i;i=ReaD())mp[i]=1;
	freopen("GameStep.csv","r",stdin);//打开对局记录
	freopen("GS.csv","w",stdout);//打开输出文件
	short t=ReaD(),n=1;
	while(t&&t!=-101)t=ReaD();
	while(t!=-101){
		if(mp.find(n)==mp.end())printf("%hd\n",t);
		short x=ReaD(),y=ReaD();
		while(y>=0){
			if(mp.find(n)==mp.end())printf("%hd,%hd\n",x,y);
			x=ReaD();y=ReaD();
		}
		if(mp.find(n)==mp.end())printf("%hd,%hd\n",x,y);
		t=ReaD();
		if(t)break;
		n++;
	}
	freopen("CON","r",stdin);
	freopen("CON","w",stdout);
	system("del GameStep.csv");//删除
	system("rename GS.csv GameStep.csv");//重命名
	printf("清除成功 ");
	system("pause");
	return 0;
}
