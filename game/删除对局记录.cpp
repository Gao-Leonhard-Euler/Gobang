/*
Developed By Gaosx
����ҵҪ���еĶԾ�ɾ������
ԭ���ǰѲ���Ҫɾ���Ĳ���д������һ���ļ�(GS.csv)��ɾ��ԭ�ļ�(GameStep.csv)��Ȼ��������
*/
#include<bits/stdc++.h>
#include<Windows.h>
#pragma GCC optimize("Ofast,no-stack-protector")
using namespace std;
short ReaD(){//����һ����
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
	printf("��Ҫɾ���ڼ��ֵĶԾּ�¼(������������ݣ���0����)��");
	for(short i=ReaD();i;i=ReaD())mp[i]=1;
	freopen("GameStep.csv","r",stdin);//�򿪶Ծּ�¼
	freopen("GS.csv","w",stdout);//������ļ�
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
	system("del GameStep.csv");//ɾ��
	system("rename GS.csv GameStep.csv");//������
	printf("����ɹ� ");
	system("pause");
	return 0;
}
