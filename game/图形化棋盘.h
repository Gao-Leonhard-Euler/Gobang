/*
Developed By Gaosx
2023.11.09����ѧϰ��easyX��򵥵�һ���ֹ��ܲ�����������
2023.11.26�޸�����Ϣ������δ��յ�bug����ʼ��ʱ������һ��flushmessage();��
�����һ��ʮ�ֲִڵ�15*15��С�����������̵�ͼ�λ����棬�ƺ���Щ���ڼ�ª��
����Ŀʹ�õ���2022���easyX
*/
#include"����.h"
#include<graphics.h>
#include<conio.h>
namespace FiveChess{
	struct visual_chessboard{
		void init(){//��ʼ��
			initgraph(700,700);
			for(int i=40,j=-1;j<14;i+=40){
				outtextxy(i,5,(++j)<10?(48+j):49);
				outtextxy(5,i,j<10?(48+j):49);
				if(j>=10)outtextxy(10,i,38+j);
				line(i+5,30,i+5,620);
				line(30,i+5,620,i+5);
			}
			for(int i=445,j=-1;j<4;i+=40)outtextxy(i,5,++j+48);
			HWND hWnd=GetHWnd();SetWindowText(hWnd,"������");
			flushmessage();
		}
		void get(short &x,short &y){//��ȡ���������
			ExMessage m=getmessage(EX_MOUSE);
			while(!(m.lbutton||m.rbutton||m.mbutton))m=getmessage(EX_MOUSE);
			x=(m.x+20)/40-1;y=(m.y+20)/40-1;
		}
		void draw(short x,short y,short t){//����
			setfillcolor(t==1?BLACK:WHITE);
			fillcircle(x*40+45,y*40+45,10);
		}
		void close(){
			closegraph();
		}
	};
}
