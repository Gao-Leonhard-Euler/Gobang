/*
Developed By Gaosx
大作业要求中的对局回放功能
在编译时需要加入命令"-leasyx"
*/
#include<bits/stdc++.h>
#include<Windows.h>
#include"图形化棋盘.h"
#pragma GCC optimize("Ofast,no-stack-protector")
using namespace std;
FiveChess::visual_chessboard cbm;
FiveChess::chessboard cb;
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
int main(){
	short l,r;
	printf("两步之间播放延时(单位：毫秒)：");l=ReaD();
	printf("两局之间播放延时(单位：毫秒)：");r=ReaD();
	freopen("GameStep.csv","r",stdin);//打开对局记录
	short t=ReaD();
	while(t&&t!=-101)t=ReaD();
	while(t!=-101){
		system("cls");cbm.init();cb.restart();
		short x=ReaD(),y=ReaD(),i=1;
		while(y>=0){
			if(!cb.can_put(x,y)){//出现错误
				closegraph();freopen("CON","r",stdin);
				printf("error\n\n");system("Pause");return 0;
			}
			cbm.draw(x,y,i);cb.put(x,y,i);
			i=-i;
			Sleep(l);
			x=ReaD();y=ReaD();
		}
		Sleep(r/2);closegraph();
		if(y!=-1){//出现错误
			freopen("CON","r",stdin);printf("error\n\n");system("Pause");return 0;
		}
		switch(x){
			case 1://1表示黑子胜
				printf("\n黑子胜\n\n");break;
			case -1://-1表示白子胜
				printf("\n白子胜\n\n");break;
			case 0://0表示平局
				printf("\n平局\n\n");break;
			default://其它情况为出现错误
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
