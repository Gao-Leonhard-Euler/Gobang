/*
Developed By Gaosx
这是游戏的主程序部分
在编译时需要加入命令"-leasyx"
*/ 
#include<bits/stdc++.h>
#include<Windows.h>
#include"图形化棋盘.h"
#pragma GCC optimize("Ofast,-fpeephole2,-falign-loops,-falign-jumps,-falign-labels,-fthread-jumps,-freorder-blocks,-falign-functions,no-stack-protector,-foptimize-sibling-calls,-fdelete-null-pointer-checks",3)
using namespace std;
FiveChess::chessboard m;
FiveChess::visual_chessboard cbm;
short chAI[2];
FiveChess::chessAI_dfs_static Player1(1),Player2(-1);
FiveChess::chessAI_static player1(1),player2(-1);
bool isYes(){//判断输入是否为'Y'或'y'
	char c=getchar();
	while(c!='Y'&&c!='N'&&c!='y'&&c!='n')c=getchar();
	return c=='Y'||c=='y';
}
unsigned short ReaD(){//输入一个数
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	unsigned short r=0;
	while(c>='0'&&c<='9'){
		r=r*10+(c^48);
		c=getchar();
	}
	return r;
}
int main(){
	srand(time(0));
	ofstream outp;outp.open("GameStep.csv",std::ios::app);//输出对局记录至GameStep.csv
	outp<<0<<endl;
	unsigned int bl=0,wh=0;
	while(1){
		system("cls");
		srand(time(0)+rand());
		printf("黑子是否为电脑(Y/N):");
		chAI[0]=isYes();
		if(chAI[0]){
			printf("是否选择简单难度(Y/N):");
			chAI[0]=isYes()?1:-1;
			player1.set();Player1.set();
		}
		printf("白子是否为电脑(Y/N):");
		chAI[1]=isYes();
		if(chAI[1]){
			printf("是否选择简单难度(Y/N):");
			chAI[1]=isYes()?1:-1;
			player2.set();Player2.set();
		}
		short step=0;
		m.restart();
		cbm.init();
		short x,y;
		while(step<225){
			if(chAI[0]){
				pair<short,short> s=chAI[0]==1?player1.put(m):Player1.put(m);
				x=s.first;y=s.second;
			}
			else{
				cbm.get(x,y);//输入坐标 
				while(m.can_put(x,y)==0)//判断坐标是否合法
					cbm.get(x,y);
			}
			m.put(x,y,1);cbm.draw(x,y,1);
			outp<<x<<','<<y<<endl;
			if(m.NobodyWin()){//如果黑子胜利
				Sleep(2000);closegraph();//关闭棋盘
				system("cls");
				printf("黑子胜\n\n\n");
				outp<<"1,-1\n";
				bl++;
				break;
			}
			if(step==224)break;//如果棋盘已满，则退出
			step+=2;//计步
			if(chAI[1]){
				pair<short,short> s=chAI[1]==1?player2.put(m):Player2.put(m);
				x=s.first;y=s.second;
			}
			else{
				cbm.get(x,y);//输入坐标 
				while(m.can_put(x,y)==0)//判断坐标是否合法
					cbm.get(x,y);
			}
			m.put(x,y,-1);cbm.draw(x,y,-1);
			outp<<x<<','<<y<<endl;
			if(m.NobodyWin()){//如果黑子胜利
				Sleep(2000);closegraph();//关闭棋盘
				system("cls");
				printf("白子胜\n\n\n");
				outp<<"-1,-1\n";
				wh++;
				break;
			}
		}
		if(m.NobodyWin()==0){
			Sleep(2000);closegraph();//关闭棋盘
			system("cls");
			printf("平局\n\n\n");
			outp<<"0,-1\n";
		}
		printf("黑子赢局数：%d\n白子赢局数：%d\n\n\n是否开启下一局(Y/N):",bl,wh);
		if(!isYes())return 0;
		else outp<<0<<endl;
	}
	return 0;
}
