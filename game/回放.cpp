/*
Developed By Gaosx
����ҵҪ���еĶԾֻطŹ���
�ڱ���ʱ��Ҫ��������"-leasyx"
*/
#include<bits/stdc++.h>
#include<Windows.h>
#include"ͼ�λ�����.h"
#pragma GCC optimize("Ofast,no-stack-protector")
using namespace std;
FiveChess::visual_chessboard cbm;
FiveChess::chessboard cb;
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
int main(){
	short l,r;
	printf("����֮�䲥����ʱ(��λ������)��");l=ReaD();
	printf("����֮�䲥����ʱ(��λ������)��");r=ReaD();
	freopen("GameStep.csv","r",stdin);//�򿪶Ծּ�¼
	short t=ReaD();
	while(t&&t!=-101)t=ReaD();
	while(t!=-101){
		system("cls");cbm.init();cb.restart();
		short x=ReaD(),y=ReaD(),i=1;
		while(y>=0){
			if(!cb.can_put(x,y)){//���ִ���
				closegraph();freopen("CON","r",stdin);
				printf("error\n\n");system("Pause");return 0;
			}
			cbm.draw(x,y,i);cb.put(x,y,i);
			i=-i;
			Sleep(l);
			x=ReaD();y=ReaD();
		}
		Sleep(r/2);closegraph();
		if(y!=-1){//���ִ���
			freopen("CON","r",stdin);printf("error\n\n");system("Pause");return 0;
		}
		switch(x){
			case 1://1��ʾ����ʤ
				printf("\n����ʤ\n\n");break;
			case -1://-1��ʾ����ʤ
				printf("\n����ʤ\n\n");break;
			case 0://0��ʾƽ��
				printf("\nƽ��\n\n");break;
			default://�������Ϊ���ִ���
				freopen("CON","r",stdin);printf("error\n\n");system("Pause");return 0;
		}
		t=ReaD();
		if(t)break;
		Sleep(r/2);
	}
	freopen("CON","r",stdin);
	system("pause");
	return 0;
}
