/*
Developed By Gaosx
2023.09.29��������ѵ���Ļ������ܣ����ǻ���Ҫ�ֶ���������������÷ֽ�����ֶ����ݵ÷ֽ���ɾ����
2023.11.10����˳����Ż�������Ҫÿ�ֶ�ս�����ļ��ж�ȡȨ�أ���ʡ��ʱ��
2023.11.26ʵ�����Զ�ɾ�����������Ĳ���
˼·��
��"ChessboardValue.txt"�ĵ����ŵ����ݻ����ϣ�����һЩ���ֵ�������������ĸ�Ȩ���ĵ���
����������ĵ��е�����ΪȨ�صľ�̬�����㷨���಩�ģ�ͳ�Ʒ���������=ʤ������-ʧ�ܾ�������ȡ���������Ϊ�µ�Ȩ���ĵ���ɾ�������ļ���
����ʵ�Ǵ�AI�Ľ����㷨�л�ȡ����С�
*/
#include<bits/stdc++.h>
#include"����.h"
#pragma GCC optimize("Ofast,-fpeephole2,-falign-loops,-falign-jumps,-falign-labels,-falign-functions,no-stack-protector",3)
using namespace std;
FiveChess::chessboard m;
FiveChess::chessAI_static player1[5]={FiveChess::chessAI_static(1),FiveChess::chessAI_static(1),FiveChess::chessAI_static(1),FiveChess::chessAI_static(1),FiveChess::chessAI_static(1)},player2[5]={FiveChess::chessAI_static(-1),FiveChess::chessAI_static(-1),FiveChess::chessAI_static(-1),FiveChess::chessAI_static(-1),FiveChess::chessAI_static(-1)};
const char dele[5][40]={"del Value\\ChessboardValue1.txt","del Value\\ChessboardValue2.txt","del Value\\ChessboardValue3.txt","del Value\\ChessboardValue4.txt","del Value\\ChessboardValue.txt"};//ɾ��ָ��
const char rena[4][60]={"rename Value\\ChessboardValue1.txt ChessboardValue.txt","rename Value\\ChessboardValue2.txt ChessboardValue.txt","rename Value\\ChessboardValue3.txt ChessboardValue.txt","rename Value\\ChessboardValue4.txt ChessboardValue.txt"};//������ָ��
char s[5][36]={"Value\\ChessboardValue1.txt","Value\\ChessboardValue2.txt","Value\\ChessboardValue3.txt","Value\\ChessboardValue4.txt","Value\\ChessboardValue.txt"};//Ȩ���ĵ�����
inline short StartTest(short i,short j){//���Զ�ս
	m.restart();
	short step=0;
	srand(rand()+time(0));
	while(step<225){
		pair<short,short> s=player1[i].put(m);
		m.put(s.first,s.second,1);
		if(m.NobodyWin())return 1;
		if(step==224)return 0;
		step+=2;
		s=player2[j].put(m);
		m.put(s.first,s.second,-1);
		if(m.NobodyWin())return -1;
	}
	return 0;
}
int sc[5];
int main(){
	srand(time(0));
	int TT,TTT;
	printf("ѵ��������");
	scanf("%d",&TT);
	printf("ÿ�ֶԾ�����");
	scanf("%d",&TTT);
	while(TT--){
		memset(sc,0,sizeof(sc));
		freopen("Value\\ChessboardValue.txt","r",stdin);
		int p1,p2;
		long long t[7][2];
		scanf("%d%d",&p1,&p2);
		for(int j=0;j<7;j++)scanf("%lld%lld",&t[j][0],&t[j][1]);
		freopen("CON","r",stdin);
		ofstream o[4];
		for(int i=0;i<4;i++)o[i].open(s[i],ios::out);
		srand(rand()+time(0));
		for(int i=0;i<4;i++)
			o[i]<<(p1+((rand()&31)+(rand()&127))*(rand()&1?1:-1)+((rand()&63)+(rand()&255))*(rand()&1?1:-1))<<' '<<(p2+((rand()&31)+(rand()&127))*(rand()&1?1:-1)+((rand()&63)+(rand()&255))*(rand()&1?1:-1))<<endl;
		srand(rand()+time(0));
		for(int i=0;i<4;i++){
			for(int j=0;j<7;j++)
				o[i]<<(t[j][0]+(rand()&1?1:-1)*(j<=1?rand()*rand():rand())*(j<4?rand():rand()&31))<<' '<<(t[j][1]+(rand()&1?1:-1)*(j<=1?rand()*rand():rand())*(j<4?rand():rand()&31))<<endl;
			o[i].close();
		}
		for(short i=0;i<5;i++){//��ʼ��
			player1[i].set(s[i]);
			player2[i].set(s[i]);
		}
		for(int T=0;T<TTT;T++)for(short i=0;i<5;i++)for(short j=0;j<5;j++)if(i!=j){
			short ans=StartTest(i,j)-StartTest(j,i);
			sc[i]+=ans;sc[j]-=ans;
		}
		int maxi=4;
		for(int i=0;i<4;i++)if(sc[i]>sc[maxi])maxi=i;//ȡ���ֵ
		for(int i=0;i<5;i++)if(i!=maxi)system(dele[i]);//ɾ��
		if(maxi<4)system(rena[maxi]);//������
	}
	return 0;
}
