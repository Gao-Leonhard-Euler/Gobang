/*
Developed By Gaosx
������Ϸ�������򲿷�
�ڱ���ʱ��Ҫ��������"-leasyx"
*/ 
#include<bits/stdc++.h>
#include<Windows.h>
#include"ͼ�λ�����.h"
#pragma GCC optimize("Ofast,-fpeephole2,-falign-loops,-falign-jumps,-falign-labels,-fthread-jumps,-freorder-blocks,-falign-functions,no-stack-protector,-foptimize-sibling-calls,-fdelete-null-pointer-checks",3)
using namespace std;
FiveChess::chessboard m;
FiveChess::visual_chessboard cbm;
short chAI[2];
FiveChess::chessAI_dfs_static Player1(1),Player2(-1);
FiveChess::chessAI_static player1(1),player2(-1);
bool isYes(){//�ж������Ƿ�Ϊ'Y'��'y'
	char c=getchar();
	while(c!='Y'&&c!='N'&&c!='y'&&c!='n')c=getchar();
	return c=='Y'||c=='y';
}
unsigned short ReaD(){//����һ����
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
	ofstream outp;outp.open("GameStep.csv",std::ios::app);//����Ծּ�¼��GameStep.csv
	outp<<0<<endl;
	unsigned int bl=0,wh=0;
	while(1){
		system("cls");
		srand(time(0)+rand());
		printf("�����Ƿ�Ϊ����(Y/N):");
		chAI[0]=isYes();
		if(chAI[0]){
			printf("�Ƿ�ѡ����Ѷ�(Y/N):");
			chAI[0]=isYes()?1:-1;
			player1.set();Player1.set();
		}
		printf("�����Ƿ�Ϊ����(Y/N):");
		chAI[1]=isYes();
		if(chAI[1]){
			printf("�Ƿ�ѡ����Ѷ�(Y/N):");
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
				cbm.get(x,y);//�������� 
				while(m.can_put(x,y)==0)//�ж������Ƿ�Ϸ�
					cbm.get(x,y);
			}
			m.put(x,y,1);cbm.draw(x,y,1);
			outp<<x<<','<<y<<endl;
			if(m.NobodyWin()){//�������ʤ��
				Sleep(2000);closegraph();//�ر�����
				system("cls");
				printf("����ʤ\n\n\n");
				outp<<"1,-1\n";
				bl++;
				break;
			}
			if(step==224)break;//����������������˳�
			step+=2;//�Ʋ�
			if(chAI[1]){
				pair<short,short> s=chAI[1]==1?player2.put(m):Player2.put(m);
				x=s.first;y=s.second;
			}
			else{
				cbm.get(x,y);//�������� 
				while(m.can_put(x,y)==0)//�ж������Ƿ�Ϸ�
					cbm.get(x,y);
			}
			m.put(x,y,-1);cbm.draw(x,y,-1);
			outp<<x<<','<<y<<endl;
			if(m.NobodyWin()){//�������ʤ��
				Sleep(2000);closegraph();//�ر�����
				system("cls");
				printf("����ʤ\n\n\n");
				outp<<"-1,-1\n";
				wh++;
				break;
			}
		}
		if(m.NobodyWin()==0){
			Sleep(2000);closegraph();//�ر�����
			system("cls");
			printf("ƽ��\n\n\n");
			outp<<"0,-1\n";
		}
		printf("����Ӯ������%d\n����Ӯ������%d\n\n\n�Ƿ�����һ��(Y/N):",bl,wh);
		if(!isYes())return 0;
		else outp<<0<<endl;
	}
	return 0;
}
