/*
Developed By Gaosx
2023.09.27开始实现棋盘类
2023.09.30实现第一个算法（估值）
2023.10.08完成第一个算法的优化
2023.11.04完成第二个算法（极大极小搜索+Alpha-Beta剪枝）
2023.11.09增加了一些常数优化
2023.12.08增加棋盘大小的自定义
2023.12.16更新了棋盘类的哈希函数
*/
#include<bits/stdc++.h>
#ifndef FiveChessSize
#define FiveChessSize 15
#endif
//FiveChessSize为棋盘的边长，可以修改为5~181之间的任意正整数值
namespace FiveChess{
	class chessboard{//棋盘类
		private:
			short b[FiveChessSize][FiveChessSize];
			inline void find(const int &x,const short &l,int &p,int &n){//在棋盘中寻找特定棋形(平衡三进制编码)
				for(short i=0;i+l<=FiveChessSize;i++){
					for(short j=0;j+l<=FiveChessSize;j++){
						int ans=0;
						for(short k=0;k<l;k++)ans=ans*3+b[i+k][j+k];
						if(ans==x)p++;
						else if(ans==-x)n++;
						ans=0;
						for(short k=l-1;k>=0;k--)ans=ans*3+b[i+k][j+k];
						if(ans==x)p++;
						else if(ans==-x)n++;
						ans=0;
						for(short k=0;k<l;k++)ans=ans*3+b[i+l-1-k][j+k];
						if(ans==x)p++;
						else if(ans==-x)n++;
						ans=0;
						for(short k=0;k<l;k++)ans=ans*3+b[i+k][j+l-1-k];
						if(ans==x)p++;
						else if(ans==-x)n++;
					}
				}
				for(short i=0;i+l<=FiveChessSize;i++){
					for(short j=0;j<FiveChessSize;j++){
						int ans=0;
						for(short k=0;k<l;k++)ans=ans*3+b[i+k][j];
						if(ans==x)p++;
						else if(ans==-x)n++;
						ans=0;
						for(short k=0;k<l;k++)ans=ans*3+b[j][i+k];
						if(ans==x)p++;
						else if(ans==-x)n++;
						ans=0;
						for(short k=l-1;k>=0;k--)ans=ans*3+b[i+k][j];
						if(ans==x)p++;
						else if(ans==-x)n++;
						ans=0;
						for(short k=l-1;k>=0;k--)ans=ans*3+b[j][i+k];
						if(ans==x)p++;
						else if(ans==-x)n++;
					}
				}
			}
			inline void find(const short &X1,const short &X2,const short &Y1,const short &Y2,const int &x,const short &l,int &p,int &n){//在[X1,X2),[Y1,Y2)寻找特定棋形(平衡三进制编码)
				for(short i=X1;i+l<=X2;i++){
					for(short j=Y1;j+l<=Y2;j++){
						int ans=0;
						for(short k=0;k<l;k++)ans=ans*3+b[i+k][j+k];
						if(ans==x)p++;
						else if(ans==-x)n++;
						ans=0;
						for(short k=l-1;k>=0;k--)ans=ans*3+b[i+k][j+k];
						if(ans==x)p++;
						else if(ans==-x)n++;
						ans=0;
						for(short k=0;k<l;k++)ans=ans*3+b[i+l-1-k][j+k];
						if(ans==x)p++;
						else if(ans==-x)n++;
						ans=0;
						for(short k=0;k<l;k++)ans=ans*3+b[i+k][j+l-1-k];
						if(ans==x)p++;
						else if(ans==-x)n++;
					}
				}
				for(short i=X1;i+l<=X2;i++){
					for(short j=Y1;j<Y2;j++){
						int ans=0;
						for(short k=0;k<l;k++)ans=ans*3+b[i+k][j];
						if(ans==x)p++;
						else if(ans==-x)n++;
						ans=0;
						for(short k=l-1;k>=0;k--)ans=ans*3+b[i+k][j];
						if(ans==x)p++;
						else if(ans==-x)n++;
						ans=0;
					}
				}
				for(short i=X1;i<X2;i++){
					for(short j=Y1;j+l<=Y2;j++){
						int ans=0;
						for(short k=0;k<l;k++)ans=ans*3+b[i][j+k];
						if(ans==x)p++;
						else if(ans==-x)n++;
						ans=0;
						for(short k=l-1;k>=0;k--)ans=ans*3+b[i][j+k];
						if(ans==x)p++;
						else if(ans==-x)n++;
						ans=0;
					}
				}
			}
		public:
			chessboard(){//棋盘初始化(全空)
				memset(b,0,sizeof(b));
			}
			void restart(){//棋盘重置(全空)
				memset(b,0,sizeof(b));
			}
			inline short operator()(const unsigned short x,const unsigned short y){//一个位置的棋子种类(-1为白子，1为黑子)
				return (x>=FiveChessSize||y>=FiveChessSize)?0:b[x][y];
			}
			inline bool can_put(const unsigned short x,const unsigned short y){//判断是否可落子
				return (x>=FiveChessSize||y>=FiveChessSize)?0:(b[x][y]==0?1:0);
			}
			inline void put(const unsigned short x,const unsigned short y,const short i){//落子
				if(can_put(x,y))b[x][y]=i;
			}
			short NobodyWin(){//判断游戏是否结束，黑方赢返回1，白方赢返回-1，游戏未结束返回0
				int p=0,n=0;
				find(121,5,p,n);
				if(p!=0)return 1;
				if(n!=0)return -1;
				return 0;
			}
			inline unsigned short empty_position(){//空位数量
				unsigned short a=0;
				for(unsigned short x=0;x<FiveChessSize;x++)for(unsigned short y=0;y<FiveChessSize;y++)if(b[x][y]==0)a++;
				return a;
			}
			void output_screen(){//输出棋盘至屏幕
				putchar(' ');putchar(' ');
				for(unsigned short j=0;j<FiveChessSize;j++){
					if(j<10)printf("  %hd",j);
					else if(j>99)printf("%hd",j);
					else printf(" %hd",j);
				}
				putchar('\n');
				for(unsigned short i=0;i<FiveChessSize;i++){
					if(i<10)printf("  %hd",i);
					else if(i>99)printf("%hd",i);
					else printf(" %hd",i);
					for(unsigned short j=0;j<FiveChessSize;j++){
						putchar(' ');
						switch(b[i][j]){
							case 0:
								putchar(' ');//用空格表示空位
								break;
							case 1:
								putchar('1');//用'1'表示黑子
								break;
							case -1:
								putchar('0');//用'0'表示白子
						}
						putchar(' ');
					}
					putchar('\n');
				}
				putchar('\n');
			}
			friend bool operator==(chessboard x,chessboard y);
			friend bool operator!=(chessboard x,chessboard y);
			friend class chessAI_static;
			friend class chessAI_dfs_static;
			friend struct hashChess;
	};
	struct hashChess{//棋盘状态哈希(unordered_map使用)
		int operator()(const chessboard &cb)const{
			return cb.b[FiveChessSize>>1][FiveChessSize>>1]+cb.b[(FiveChessSize>>1)-1][FiveChessSize>>1]+cb.b[FiveChessSize>>1][(FiveChessSize>>1)-1]+cb.b[(FiveChessSize>>1)-1][(FiveChessSize>>1)-1]\
			+((cb.b[FiveChessSize>>2][FiveChessSize>>2]+cb.b[FiveChessSize-(FiveChessSize>>2)][FiveChessSize-(FiveChessSize>>2)]+cb.b[FiveChessSize-(FiveChessSize>>2)-1][FiveChessSize-(FiveChessSize>>2)-1])<<1)\
			+((cb.b[FiveChessSize>>1][FiveChessSize>>2]+cb.b[FiveChessSize>>2][FiveChessSize>>1]+cb.b[FiveChessSize-5][FiveChessSize-5])<<2)\
			+((cb.b[FiveChessSize>>1][FiveChessSize-(FiveChessSize>>2)]+cb.b[FiveChessSize-(FiveChessSize>>2)][FiveChessSize>>1])<<3)\
			+((cb.b[FiveChessSize>>2][FiveChessSize-(FiveChessSize>>2)]+cb.b[FiveChessSize-(FiveChessSize>>2)][FiveChessSize>>2])<<4)\
			+((cb.b[0][0]+cb.b[1][1]+cb.b[2][2]+cb.b[3][3]+cb.b[4][4])<<5)\
			+((cb.b[FiveChessSize-1][FiveChessSize-1]+cb.b[FiveChessSize-2][FiveChessSize-2]+cb.b[FiveChessSize-3][FiveChessSize-3])<<6)\
			+((cb.b[FiveChessSize-1][0]+cb.b[0][FiveChessSize-1]+cb.b[1][FiveChessSize-1]+cb.b[FiveChessSize-1][1]+cb.b[2][FiveChessSize-1]+cb.b[FiveChessSize-1][2]+cb.b[3][FiveChessSize-1]+cb.b[FiveChessSize-1][3]+cb.b[4][FiveChessSize-1]+cb.b[FiveChessSize-1][4])<<7)\
			+((cb.b[FiveChessSize-2][0]+cb.b[0][FiveChessSize-2]+cb.b[1][FiveChessSize-2]+cb.b[FiveChessSize-2][1]+cb.b[2][FiveChessSize-2]+cb.b[FiveChessSize-2][2]+cb.b[3][FiveChessSize-2]+cb.b[FiveChessSize-2][3]+cb.b[4][FiveChessSize-2]+cb.b[FiveChessSize-2][4])<<8)\
			+((cb.b[0][FiveChessSize>>2]+cb.b[FiveChessSize>>2][0]+cb.b[1][FiveChessSize>>2]+cb.b[FiveChessSize>>2][1]+cb.b[2][FiveChessSize>>2]+cb.b[FiveChessSize>>2][2]+cb.b[3][FiveChessSize>>2]+cb.b[FiveChessSize>>2][3]+cb.b[4][FiveChessSize>>2]+cb.b[FiveChessSize>>2][4])<<9)\
			+((cb.b[0][FiveChessSize>>1]+cb.b[FiveChessSize>>1][0]+cb.b[1][FiveChessSize>>1]+cb.b[FiveChessSize>>1][1]+cb.b[2][FiveChessSize>>1]+cb.b[FiveChessSize>>1][2]+cb.b[3][FiveChessSize>>1]+cb.b[FiveChessSize>>1][3]+cb.b[4][FiveChessSize>>1]+cb.b[FiveChessSize>>1][4])<<10)\
			+((cb.b[FiveChessSize>>1][FiveChessSize-2]+cb.b[FiveChessSize-2][FiveChessSize>>1]+cb.b[FiveChessSize>>1][FiveChessSize-1]+cb.b[FiveChessSize-1][FiveChessSize>>1])<<11)\
			+((cb.b[(FiveChessSize>>1)-1][FiveChessSize>>2]+cb.b[FiveChessSize>>2][(FiveChessSize>>1)-1])<<12)\
			+((cb.b[(FiveChessSize>>2)+1][FiveChessSize>>2]+cb.b[FiveChessSize>>2][(FiveChessSize>>2)+1])<<13)\
			+((cb.b[(FiveChessSize>>2)+1][(FiveChessSize>>2)+1]+cb.b[(FiveChessSize>>2)-1][(FiveChessSize>>2)-1])<<14)\
			+((cb.b[(FiveChessSize>>2)+1][(FiveChessSize>>1)-1]+cb.b[(FiveChessSize>>1)-1][(FiveChessSize>>2)+1]+cb.b[(FiveChessSize>>2)+1][(FiveChessSize>>1)-1]+cb.b[(FiveChessSize>>1)-1][(FiveChessSize>>2)+1])<<15)\
			+((cb.b[(FiveChessSize>>2)+1][FiveChessSize>>1]+cb.b[FiveChessSize>>1][(FiveChessSize>>2)+1])<<16)\
			+((cb.b[(FiveChessSize>>3)+1][(FiveChessSize>>3)+1]+cb.b[FiveChessSize>>3][FiveChessSize>>3])<<17)\
			+((cb.b[FiveChessSize>>3][(FiveChessSize>>3)+1]+cb.b[(FiveChessSize>>3)+1][FiveChessSize>>3])<<18)\
			+((cb.b[0][1]+cb.b[1][0]+cb.b[1][2]+cb.b[2][1]+cb.b[2][3]+cb.b[3][2]+cb.b[3][4]+cb.b[4][3])<<19)\
			+((cb.b[0][2]+cb.b[0][3]+cb.b[2][0]+cb.b[3][0]+cb.b[1][3]+cb.b[3][1]+cb.b[1][4]+cb.b[4][1]+cb.b[0][4]+cb.b[4][0])<<20)\
			+((cb.b[FiveChessSize-1][FiveChessSize-2]+cb.b[FiveChessSize-2][FiveChessSize-1]+cb.b[FiveChessSize-1][FiveChessSize-3]+cb.b[FiveChessSize-3][FiveChessSize-1]+cb.b[FiveChessSize-3][FiveChessSize-2]+cb.b[FiveChessSize-2][FiveChessSize-3])<<21)\
			+((cb.b[FiveChessSize>>3][FiveChessSize>>2]+cb.b[FiveChessSize>>2][FiveChessSize>>3]+cb.b[FiveChessSize>>3][(FiveChessSize>>2)-1]+cb.b[(FiveChessSize>>2)-1][FiveChessSize>>3]+cb.b[FiveChessSize>>3][(FiveChessSize>>2)+1]+cb.b[(FiveChessSize>>2)+1][FiveChessSize>>3]+cb.b[FiveChessSize>>2][(FiveChessSize>>3)+1]+cb.b[(FiveChessSize>>3)+1][FiveChessSize>>2])<<22)\
			+((cb.b[FiveChessSize>>3][(FiveChessSize>>1)-1]+cb.b[(FiveChessSize>>1)-1][FiveChessSize>>3]+cb.b[FiveChessSize>>3][FiveChessSize>>1]+cb.b[FiveChessSize>>1][FiveChessSize>>3]+cb.b[FiveChessSize>>1][(FiveChessSize>>3)+1]+cb.b[(FiveChessSize>>3)+1][FiveChessSize>>1])<<23)\
			+((cb.b[FiveChessSize-(FiveChessSize>>3)-1][FiveChessSize>>1]+cb.b[FiveChessSize>>1][FiveChessSize-(FiveChessSize>>3)-1]+cb.b[FiveChessSize-(FiveChessSize>>3)-1][FiveChessSize>>2]+cb.b[FiveChessSize>>2][FiveChessSize-(FiveChessSize>>3)-1])<<24)\
			+((cb.b[FiveChessSize-(FiveChessSize>>3)-1][0]+cb.b[0][FiveChessSize-(FiveChessSize>>3)-1]+cb.b[1][FiveChessSize-(FiveChessSize>>3)-1]+cb.b[FiveChessSize-(FiveChessSize>>3)-1][1]+cb.b[2][FiveChessSize-(FiveChessSize>>3)-1]+cb.b[FiveChessSize-(FiveChessSize>>3)-1][2]+cb.b[FiveChessSize-(FiveChessSize>>3)-1][3]+cb.b[3][FiveChessSize-(FiveChessSize>>3)-1]+cb.b[FiveChessSize-(FiveChessSize>>3)-1][4]+cb.b[4][FiveChessSize-(FiveChessSize>>3)-1])<<25)\
			+((cb.b[FiveChessSize>>3][0]+cb.b[0][FiveChessSize>>3]+cb.b[1][FiveChessSize>>3]+cb.b[FiveChessSize>>3][1]+cb.b[2][FiveChessSize>>3]+cb.b[FiveChessSize>>3][2]+cb.b[FiveChessSize>>3][3]+cb.b[FiveChessSize>>3][3]+cb.b[FiveChessSize>>3][4]+cb.b[4][FiveChessSize>>3])<<26)\
			+((cb.b[(FiveChessSize>>3)+1][0]+cb.b[0][(FiveChessSize>>3)+1]+cb.b[1][(FiveChessSize>>3)+1]+cb.b[(FiveChessSize>>3)+1][1]+cb.b[2][(FiveChessSize>>3)+1]+cb.b[(FiveChessSize>>3)+1][2]+cb.b[(FiveChessSize>>3)+1][3]+cb.b[3][(FiveChessSize>>3)+1]+cb.b[4][(FiveChessSize>>3)+1]+cb.b[(FiveChessSize>>3)+1][4])<<27)\
			+((cb.b[FiveChessSize-(FiveChessSize>>2)][FiveChessSize>>3]+cb.b[FiveChessSize>>3][FiveChessSize-(FiveChessSize>>2)]+cb.b[FiveChessSize-(FiveChessSize>>2)-1][FiveChessSize>>3]+cb.b[FiveChessSize>>3][FiveChessSize-(FiveChessSize>>2)-1])<<28)\
			+((cb.b[FiveChessSize-(FiveChessSize>>2)][(FiveChessSize>>3)+1]+cb.b[(FiveChessSize>>3)+1][FiveChessSize-(FiveChessSize>>2)]+cb.b[FiveChessSize-(FiveChessSize>>2)-1][(FiveChessSize>>3)+1]+cb.b[(FiveChessSize>>3)+1][FiveChessSize-(FiveChessSize>>2)-1])<<29)\
			+(cb.b[FiveChessSize-(FiveChessSize>>3)-1][FiveChessSize-(FiveChessSize>>3)-1]<<30);
		}
	};
	bool operator==(chessboard x,chessboard y){//判断两个棋盘是否相同
		for(unsigned short i=0;i<FiveChessSize;i++)for(unsigned short j=0;j<FiveChessSize;j++)if(x.b[i][j]!=y.b[i][j])return 0;
		return 1;
	}
	bool operator!=(chessboard x,chessboard y){//判断两个棋盘是否不同
		for(unsigned short i=0;i<FiveChessSize;i++)for(unsigned short j=0;j<FiveChessSize;j++)if(x.b[i][j]!=y.b[i][j])return 1;
		return 0;
	}
	class chessAI_static{//静态评估落子算法
		protected:
			long long myK,enemyK,success5[2],success4[2],half4[2],success3[2],half3[2],success2[2],half2[2];
			/*myK和enemyK分别代表自己的棋子与对方的棋子的权重
			其余分别代表估值函数中自己和对方的五成、活四、冲四、活三、眠三、活二、眠二情况对应的权重*/
			short r;//棋子颜色，1为黑，-1为白
		public:
			chessAI_static(short R){//初始化(1为黑，-1为白)
				r=R;
			}
			chessAI_static(){
				r=0;
			}
			void set(){//设置权重(从ChessboardValue.txt文件中读取)
				std::ifstream inp;
				inp.open("Value\\ChessboardValue.txt",std::ios::in);
				inp>>myK>>enemyK>>success5[0]>>success5[1]>>success4[0]>>success4[1]>>half4[0]>>half4[1]>>success3[0]>>success3[1]>>half3[0]>>half3[1]>>success2[0]>>success2[1]>>half2[0]>>half2[1];
				inp.close();
			}
			void set(char *s){//设置权重(从自定义文件中读取)
				std::ifstream inp;
				inp.open(s,std::ios::in); 
				inp>>myK>>enemyK>>success5[0]>>success5[1]>>success4[0]>>success4[1]>>half4[0]>>half4[1]>>success3[0]>>success3[1]>>half3[0]>>half3[1]>>success2[0]>>success2[1]>>half2[0]>>half2[1];
				inp.close();
			}
		protected:
			inline long long value(chessboard &cb){//棋盘整体估值函数
				int p=0,n=0;
				cb.find(121,5,p,n);
				long long ret=r==1?(p*success5[0]-n*success5[1]):(n*success5[0]-p*success5[1]);
				p=0;n=0;
				cb.find(120,6,p,n);
				ret+=r==1?(p*success4[0]-n*success4[1]):(n*success4[0]-p*success4[1]);
				p=-(p<<1);n=-(n<<1);
				cb.find(112,5,p,n);
				p>>=1;n>>=1;
				cb.find(120,5,p,n);
				cb.find(94,5,p,n);
				ret+=r==1?(p*half4[0]-n*half4[1]):(n*half4[0]-p*half4[1]);
				p=0;n=0;
				cb.find(117,7,p,n);
				p=-p;n=-n;
				cb.find(117,6,p,n);
				cb.find(111,6,p,n);
				ret+=r==1?(p*success3[0]-n*success3[1]):(n*success3[0]-p*success3[1]);
				p=-(p<<1);n=-(n<<1);
				cb.find(39,5,p,n);
				p>>=1;n>>=1;
				cb.find(117,5,p,n);
				cb.find(111,5,p,n);
				cb.find(93,5,p,n);
				cb.find(91,5,p,n);
				ret+=r==1?(p*half3[0]-n*half3[1]):(n*half3[0]-p*half3[1]);
				p=0;n=0;
				cb.find(108,8,p,n);
				cb.find(90,7,p,n);
				p=-(p<<1);n=-(n<<1);
				cb.find(84,6,p,n);
				cb.find(36,6,p,n);
				p>>=1;n>>=1;
				cb.find(108,6,p,n);
				cb.find(90,6,p,n);
				ret+=r==1?(p*success2[0]-n*success2[1]):(n*success2[0]-p*success2[1]);
				p=-p;n=-n;
				cb.find(90,5,p,n);
				cb.find(36,5,p,n);
				cb.find(108,5,p,n);
				cb.find(84,5,p,n);
				p<<=1;n<<=1;
				cb.find(30,5,p,n);
				cb.find(82,5,p,n);
				p>>=1;n>>=1;
				ret+=r==1?(p*half2[0]-n*half2[1]):(n*half2[0]-p*half2[1]);
				p=0;n=0;
				cb.find(9,5,p,n);
				p<<=1;n<<=1;
				cb.find(3,5,p,n);
				p<<=1;n<<=1;
				cb.find(1,5,p,n);
				ret+=r==-1?(n-p):(p-n);
				return ret;
			}
			inline long long value(chessboard &cb,short &x,short &y){//落子(x,y)估值函数
				int p=0,n=0;
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,121,5,p,n);
				long long ret=r==1?(p*success5[0]-n*success5[1]):(n*success5[0]-p*success5[1]);
				p=0;n=0;
				cb.find(x>5?x-5:0,x+6<FiveChessSize?x+6:FiveChessSize,y>5?y-5:0,y+6<FiveChessSize?y+6:FiveChessSize,120,6,p,n);
				ret+=r==1?(p*success4[0]-n*success4[1]):(n*success4[0]-p*success4[1]);
				p=-(p<<1);n=-(n<<1);
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,112,5,p,n);
				p>>=1;n>>=1;
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,120,5,p,n);
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,94,5,p,n);
				ret+=r==1?(p*half4[0]-n*half4[1]):(n*half4[0]-p*half4[1]);
				p=0;n=0;
				cb.find(x>6?x-6:0,x+7<FiveChessSize?x+7:FiveChessSize,y>6?y-6:0,y+7<FiveChessSize?y+7:FiveChessSize,117,7,p,n);
				p=-p;n=-n;
				cb.find(x>5?x-5:0,x+6<FiveChessSize?x+6:FiveChessSize,y>5?y-5:0,y+6<FiveChessSize?y+6:FiveChessSize,117,6,p,n);
				cb.find(x>5?x-5:0,x+6<FiveChessSize?x+6:FiveChessSize,y>5?y-5:0,y+6<FiveChessSize?y+6:FiveChessSize,111,6,p,n);
				ret+=r==1?(p*success3[0]-n*success3[1]):(n*success3[0]-p*success3[1]);
				p=-(p<<1);n=-(n<<1);
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,39,5,p,n);
				p>>=1;n>>=1;
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,117,5,p,n);
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,111,5,p,n);
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,93,5,p,n);
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,91,5,p,n);
				ret+=r==1?(p*half3[0]-n*half3[1]):(n*half3[0]-p*half3[1]);
				p=0;n=0;
				cb.find(x>7?x-7:0,x+8<FiveChessSize?x+8:FiveChessSize,y>7?y-7:0,y+8<FiveChessSize?y+8:FiveChessSize,108,8,p,n);
				cb.find(x>6?x-6:0,x+7<FiveChessSize?x+7:FiveChessSize,y>6?y-6:0,y+7<FiveChessSize?y+7:FiveChessSize,90,7,p,n);
				p=-(p<<1);n=-(n<<1);
				cb.find(x>5?x-5:0,x+6<FiveChessSize?x+6:FiveChessSize,y>5?y-5:0,y+6<FiveChessSize?y+6:FiveChessSize,84,6,p,n);
				cb.find(x>5?x-5:0,x+6<FiveChessSize?x+6:FiveChessSize,y>5?y-5:0,y+6<FiveChessSize?y+6:FiveChessSize,36,6,p,n);
				p>>=1;n>>=1;
				cb.find(x>5?x-5:0,x+6<FiveChessSize?x+6:FiveChessSize,y>5?y-5:0,y+6<FiveChessSize?y+6:FiveChessSize,108,6,p,n);
				cb.find(x>5?x-5:0,x+6<FiveChessSize?x+6:FiveChessSize,y>5?y-5:0,y+6<FiveChessSize?y+6:FiveChessSize,90,6,p,n);
				ret+=r==1?(p*success2[0]-n*success2[1]):(n*success2[0]-p*success2[1]);
				p=-p;n=-n;
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,90,5,p,n);
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,36,5,p,n);
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,108,5,p,n);
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,84,5,p,n);
				p<<=1;n<<=1;
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,30,5,p,n);
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,82,5,p,n);
				p>>=1;n>>=1;
				ret+=r==1?(p*half2[0]-n*half2[1]):(n*half2[0]-p*half2[1]);
				p=0;n=0;
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,9,5,p,n);
				p<<=1;n<<=1;
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,3,5,p,n);
				p<<=1;n<<=1;
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,1,5,p,n);
				ret+=r==-1?(n-p):(p-n);
				return ret;
			}
		public:
			std::pair<unsigned short,unsigned short> put(chessboard cb){//基于静态估值函数评估进行落子
				long long val=-9223372036854775807,t;
				unsigned short X,Y;
				srand(rand()+time(0));
				for(unsigned short x=0;x<FiveChessSize;x++)for(unsigned short y=0;y<FiveChessSize;y++)
					if(cb.b[x][y]==0){
						t=value(cb,x,y)*(enemyK-myK);
						cb.b[x][y]=r;
						t+=value(cb,x,y)*myK;
						cb.b[x][y]=-r;
						t-=value(cb,x,y)*enemyK;
						if(t>val){
							val=t;
							X=x;
							Y=y;
						}
						else if(t==val&&(rand()&1)){
							X=x;
							Y=y;
						}
						cb.b[x][y]=0;
					}
				return std::make_pair(X,Y);
			}
	};
	class chessAI_dfs_static:public chessAI_static{//基于静态评估函数剪枝的深度优先搜索
		public:
			chessAI_dfs_static(short R){//初始化(1为黑，-1为白)
				r=R;
			}
			chessAI_dfs_static(){
				r=0;
			}
		private:
			inline long long value_enemy(chessboard &cb){//对方棋盘整体估值函数
				int p=0,n=0;
				cb.find(121,5,p,n);
				long long ret=r==-1?(p*success5[0]-n*success5[1]):(n*success5[0]-p*success5[1]);
				p=0;n=0;
				cb.find(120,6,p,n);
				ret+=r==-1?(p*success4[0]-n*success4[1]):(n*success4[0]-p*success4[1]);
				p=-(p<<1);n=-(n<<1);
				cb.find(112,5,p,n);
				p>>=1;n>>=1;
				cb.find(120,5,p,n);
				cb.find(94,5,p,n);
				ret+=r==-1?(p*half4[0]-n*half4[1]):(n*half4[0]-p*half4[1]);
				p=0;n=0;
				cb.find(117,7,p,n);
				p=-p;n=-n;
				cb.find(117,6,p,n);
				cb.find(111,6,p,n);
				ret+=r==-1?(p*success3[0]-n*success3[1]):(n*success3[0]-p*success3[1]);
				p=-(p<<1);n=-(n<<1);
				cb.find(39,5,p,n);
				p>>=1;n>>=1;
				cb.find(117,5,p,n);
				cb.find(111,5,p,n);
				cb.find(93,5,p,n);
				cb.find(91,5,p,n);
				ret+=r==-1?(p*half3[0]-n*half3[1]):(n*half3[0]-p*half3[1]);
				p=0;n=0;
				cb.find(108,8,p,n);
				cb.find(90,7,p,n);
				p=-(p<<1);n=-(n<<1);
				cb.find(84,6,p,n);
				cb.find(36,6,p,n);
				p>>=1;n>>=1;
				cb.find(108,6,p,n);
				cb.find(90,6,p,n);
				ret+=r==-1?(p*success2[0]-n*success2[1]):(n*success2[0]-p*success2[1]);
				p=-p;n=-n;
				cb.find(90,5,p,n);
				cb.find(36,5,p,n);
				cb.find(108,5,p,n);
				cb.find(84,5,p,n);
				p<<=1;n<<=1;
				cb.find(30,5,p,n);
				cb.find(82,5,p,n);
				p>>=1;n>>=1;
				ret+=r==-1?(p*half2[0]-n*half2[1]):(n*half2[0]-p*half2[1]);
				p=0;n=0;
				cb.find(9,5,p,n);
				p<<=1;n<<=1;
				cb.find(3,5,p,n);
				p<<=1;n<<=1;
				cb.find(1,5,p,n);
				ret+=r==1?(n-p):(p-n);
				return ret;
			}
			inline long long value_enemy(chessboard &cb,unsigned short &x,unsigned short &y){//落子(x,y)对方估值函数
				int p=0,n=0;
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,121,5,p,n);
				long long ret=r==-1?(p*success5[0]-n*success5[1]):(n*success5[0]-p*success5[1]);
				p=0;n=0;
				cb.find(x>5?x-5:0,x+6<FiveChessSize?x+6:FiveChessSize,y>5?y-5:0,y+6<FiveChessSize?y+6:FiveChessSize,120,6,p,n);
				ret+=r==-1?(p*success4[0]-n*success4[1]):(n*success4[0]-p*success4[1]);
				p=-(p<<1);n=-(n<<1);
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,112,5,p,n);
				p>>=1;n>>=1;
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,120,5,p,n);
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,94,5,p,n);
				ret+=r==-1?(p*half4[0]-n*half4[1]):(n*half4[0]-p*half4[1]);
				p=0;n=0;
				cb.find(x>6?x-6:0,x+7<FiveChessSize?x+7:FiveChessSize,y>6?y-6:0,y+7<FiveChessSize?y+7:FiveChessSize,117,7,p,n);
				p=-p;n=-n;
				cb.find(x>5?x-5:0,x+6<FiveChessSize?x+6:FiveChessSize,y>5?y-5:0,y+6<FiveChessSize?y+6:FiveChessSize,117,6,p,n);
				cb.find(x>5?x-5:0,x+6<FiveChessSize?x+6:FiveChessSize,y>5?y-5:0,y+6<FiveChessSize?y+6:FiveChessSize,111,6,p,n);
				ret+=r==-1?(p*success3[0]-n*success3[1]):(n*success3[0]-p*success3[1]);
				p=-(p<<1);n=-(n<<1);
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,39,5,p,n);
				p>>=1;n>>=1;
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,117,5,p,n);
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,111,5,p,n);
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,93,5,p,n);
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,91,5,p,n);
				ret+=r==-1?(p*half3[0]-n*half3[1]):(n*half3[0]-p*half3[1]);
				p=0;n=0;
				cb.find(x>7?x-7:0,x+8<FiveChessSize?x+8:FiveChessSize,y>7?y-7:0,y+8<FiveChessSize?y+8:FiveChessSize,108,8,p,n);
				cb.find(x>6?x-6:0,x+7<FiveChessSize?x+7:FiveChessSize,y>6?y-6:0,y+7<FiveChessSize?y+7:FiveChessSize,90,7,p,n);
				p=-(p<<1);n=-(n<<1);
				cb.find(x>5?x-5:0,x+6<FiveChessSize?x+6:FiveChessSize,y>5?y-5:0,y+6<FiveChessSize?y+6:FiveChessSize,84,6,p,n);
				cb.find(x>5?x-5:0,x+6<FiveChessSize?x+6:FiveChessSize,y>5?y-5:0,y+6<FiveChessSize?y+6:FiveChessSize,36,6,p,n);
				p>>=1;n>>=1;
				cb.find(x>5?x-5:0,x+6<FiveChessSize?x+6:FiveChessSize,y>5?y-5:0,y+6<FiveChessSize?y+6:FiveChessSize,108,6,p,n);
				cb.find(x>5?x-5:0,x+6<FiveChessSize?x+6:FiveChessSize,y>5?y-5:0,y+6<FiveChessSize?y+6:FiveChessSize,90,6,p,n);
				ret+=r==-1?(p*success2[0]-n*success2[1]):(n*success2[0]-p*success2[1]);
				p=-p;n=-n;
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,90,5,p,n);
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,36,5,p,n);
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,108,5,p,n);
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,84,5,p,n);
				p<<=1;n<<=1;
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,30,5,p,n);
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,82,5,p,n);
				p>>=1;n>>=1;
				ret+=r==-1?(p*half2[0]-n*half2[1]):(n*half2[0]-p*half2[1]);
				p=0;n=0;
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,9,5,p,n);
				p<<=1;n<<=1;
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,3,5,p,n);
				p<<=1;n<<=1;
				cb.find(x>4?x-4:0,x+5<FiveChessSize?x+5:FiveChessSize,y>4?y-4:0,y+5<FiveChessSize?y+5:FiveChessSize,1,5,p,n);
				ret+=r==1?(n-p):(p-n);
				return ret;
			}
			long long MySearch(chessboard cb,std::unordered_map<chessboard,long long,hashChess> &mp,unsigned short deep,unsigned short ep,long long large,long long small);//深度优先搜索-我方落子
			long long EnemySearch(chessboard cb,std::unordered_map<chessboard,long long,hashChess> &mp,unsigned short deep,unsigned short ep,long long large,long long small);//深度优先搜索-对方落子
		public:
			std::pair<unsigned short,unsigned short> put(chessboard cb){//基于深度优先搜索和静态估值函数进行落子
				unsigned short ep=cb.empty_position()-1,d=ep>4?4:2,num=8>ep?ep+1:9;//ep:空位数量,d:搜索深度,num:分支数量
				if(ep<=3||ep>=FiveChessSize*FiveChessSize-3){
					if(ep==FiveChessSize*FiveChessSize-1)return std::make_pair((unsigned short)(FiveChessSize>>1),(unsigned short)(FiveChessSize>>1));//第一步落在棋盘中间
					return chessAI_static::put(cb);//除了第一步之外的前三步和最后三步直接使用静态估值函数落子
				}
				chessboard search[9];
				long long v,searchVal[9]={-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807};
				std::pair<unsigned short,unsigned short> searchPair[9];
				srand(rand()+time(0));
				for(unsigned short x=0;x<FiveChessSize;x++)for(unsigned short y=0;y<FiveChessSize;y++)//遍历棋盘，寻找较优的搜索点
					if(cb.b[x][y]==0){
						v=value(cb,x,y)*(enemyK-myK);
						cb.b[x][y]=-r;
						v-=value(cb,x,y)*enemyK;
						cb.b[x][y]=r;
						v+=value(cb,x,y)*myK;
						for(short i=0;i<num;i++)if(v>searchVal[i]||(v==searchVal[i]&&rand()&1)){
							for(short j=num-1;j>i;j--){
								searchVal[j]=searchVal[j-1];
								search[j]=search[j-1];
								searchPair[j]=searchPair[j-1];
							}
							searchVal[i]=v;
							search[i]=cb;
							searchPair[i]=std::make_pair(x,y);
							break;
						}
						cb.b[x][y]=0;
					}
				std::unordered_map<chessboard,long long,hashChess> mp;//哈希表(判断重复)
				srand(rand()+time(0));
				v=EnemySearch(search[0],mp,d,ep,-9223372036854775807,9223372036854775807);
				unsigned short i=0;long long n;
				for(unsigned short j=1;j<num;j++){//循环，取最大值
					n=EnemySearch(search[j],mp,d,ep,v,9223372036854775807);
					if(n>v){
						v=n;i=j;
					}
				}
				return searchPair[i];
			}
	};
	long long chessAI_dfs_static::MySearch(chessboard cb,std::unordered_map<chessboard,long long,hashChess> &mp,unsigned short deep,unsigned short ep,long long large,long long small){//深度优先搜索-我方落子
		if(mp.find(cb)!=mp.end())return mp[cb];//查重(如果棋盘状态已经在哈希表中存在，则返回)
		long long Val=value(cb);
		if(Val>=success5[0]||Val<=-success5[1]){//如果已经存在五成，则返回
			mp[cb]=Val<<11;
			return Val<<11;
		}
		if(deep<=1){//叶子节点
			long long val=-9223372036854775807,t;
			unsigned short X,Y;
			for(unsigned short x=0;x<FiveChessSize;x++)for(unsigned short y=0;y<FiveChessSize;y++)
				if(cb.b[x][y]==0){
					t=value(cb,x,y)*(enemyK-myK);
					cb.b[x][y]=r;
					t+=value(cb,x,y)*myK;
					cb.b[x][y]=-r;
					t-=value(cb,x,y)*enemyK;
					if(t>val){
						val=t;
						X=x;
						Y=y;
					}
					cb.b[x][y]=0;
				}
			cb.b[X][Y]=r;
			Val+=value(cb,X,Y);
			cb.b[X][Y]=0;
			Val-=value(cb,X,Y);
			mp[cb]=Val;
			return Val;
		}
		unsigned short num=ep<9?ep:9;//搜索分支数量
		long long t,searchVal[9]={-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807};
		chessboard search[9];
		deep--;ep--;
		for(unsigned short x=0;x<FiveChessSize;x++)for(unsigned short y=0;y<FiveChessSize;y++)//遍历棋盘，寻找较优的搜索点
			if(cb.b[x][y]==0){
				t=value(cb,x,y)*(enemyK-myK);
				cb.b[x][y]=-r;
				t-=value(cb,x,y)*enemyK;
				cb.b[x][y]=r;
				t+=value(cb,x,y)*myK;
				for(short i=0;i<num;i++)if(t>searchVal[i]||(t==searchVal[i]&&rand()&1)){
					for(short j=num-1;j>i;j--){
						searchVal[j]=searchVal[j-1];
						search[j]=search[j-1];
					}
					searchVal[i]=t;
					search[i]=cb;
					break;
				}
				cb.b[x][y]=0;
			}
		t=EnemySearch(search[0],mp,deep,ep,large,small);
		if(t>=small||t>success5[0]){//Beta剪枝+胜利局面
			mp[cb]=t;
			return t;
		}
		if(t>large)large=t;
		for(unsigned short i=1;i<num;i++){
			Val=EnemySearch(search[i],mp,deep,ep,large,small);
			if(t<Val){
				if(Val>=small||Val>success5[0]){//Beta剪枝+胜利局面
					mp[cb]=Val;
					return Val;
				}
				if(Val>large)large=Val;
				t=Val;
			}
		}
		mp[cb]=t;
		return t;
	}
	long long chessAI_dfs_static::EnemySearch(chessboard cb,std::unordered_map<chessboard,long long,hashChess> &mp,unsigned short deep,unsigned short ep,long long large,long long small){//深度优先搜索-对方落子
		if(mp.find(cb)!=mp.end())return mp[cb];//查重(如果棋盘状态已经在哈希表中存在，则返回)
		long long Val=value_enemy(cb);
		if(Val>=success5[0]||Val<=-success5[1]){//如果已经存在五成，则返回
			mp[cb]=-Val<<11;
			return -Val<<11;
		}
		unsigned short num=ep<9?ep:9;//搜索分支数量
		long long t,searchVal[9]={-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807};
		chessboard search[9];
		deep--;ep--;
		for(unsigned short x=0;x<FiveChessSize;x++)for(unsigned short y=0;y<FiveChessSize;y++)//遍历棋盘，寻找较优的搜索点
			if(cb.b[x][y]==0){
				t=(Val-value_enemy(cb,x,y))*(myK-enemyK);
				cb.b[x][y]=r;
				t-=value_enemy(cb,x,y)*enemyK;
				cb.b[x][y]=-r;
				t+=value_enemy(cb,x,y)*myK;
				for(short i=0;i<num;i++)if(t>searchVal[i]||(t==searchVal[i]&&rand()&1)){
					for(short j=num-1;j>i;j--){
						searchVal[j]=searchVal[j-1];
						search[j]=search[j-1];
					}
					searchVal[i]=t;
					search[i]=cb;
					break;
				}
				cb.b[x][y]=0;
			}
		t=MySearch(search[0],mp,deep,ep,large,small);
		if(t<=large||t<-success5[1]){//Alpha剪枝+胜利局面
			mp[cb]=t;
			return t;
		}
		if(t<small)small=t;
		for(unsigned short i=1;i<num;i++){
			Val=MySearch(search[i],mp,deep,ep,large,small);
			if(t>Val){
				if(Val<=large||Val<-success5[1]){//Alpha剪枝+胜利局面
					mp[cb]=Val;
					return Val;
				}
				if(Val<small)small=Val;
				t=Val;
			}
		}
		mp[cb]=t;
		return t;
	}
}
