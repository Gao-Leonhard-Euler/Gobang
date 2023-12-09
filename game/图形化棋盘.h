/*
Developed By Gaosx
2023.11.09快速学习了easyX最简单的一部分功能并完成了这个库
2023.11.26修复了消息缓冲区未清空的bug（初始化时增加了一行flushmessage();）
完成了一个十分粗糙的15*15大小的五子棋棋盘的图形化界面，似乎有些过于简陋了
本项目使用的是2022版的easyX
*/
#include"棋盘.h"
#include<graphics.h>
#include<conio.h>
namespace FiveChess{
	struct visual_chessboard{
		void init(){//初始化
			initgraph(700,700);
			for(int i=40,j=-1;j<14;i+=40){
				outtextxy(i,5,(++j)<10?(48+j):49);
				outtextxy(5,i,j<10?(48+j):49);
				if(j>=10)outtextxy(10,i,38+j);
				line(i+5,30,i+5,620);
				line(30,i+5,620,i+5);
			}
			for(int i=445,j=-1;j<4;i+=40)outtextxy(i,5,++j+48);
			HWND hWnd=GetHWnd();SetWindowText(hWnd,"五子棋");
			flushmessage();
		}
		void get(short &x,short &y){//获取鼠标点击坐标
			ExMessage m=getmessage(EX_MOUSE);
			while(!(m.lbutton||m.rbutton||m.mbutton))m=getmessage(EX_MOUSE);
			x=(m.x+20)/40-1;y=(m.y+20)/40-1;
		}
		void draw(short x,short y,short t){//落子
			setfillcolor(t==1?BLACK:WHITE);
			fillcircle(x*40+45,y*40+45,10);
		}
		void close(){
			closegraph();
		}
	};
}
