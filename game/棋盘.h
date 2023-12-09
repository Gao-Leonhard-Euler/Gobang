/*
Developed By Gaosx
2023.09.27��ʼʵ��������
2023.09.30ʵ�ֵ�һ���㷨����ֵ��
2023.10.08��ɵ�һ���㷨���Ż�
2023.11.04��ɵڶ����㷨������С����+Alpha-Beta��֦��
2023.11.09������һЩ�����Ż�
2023.12.08�������̴�С���Զ���
*/
#include<bits/stdc++.h>
#ifndef FiveChessSize
#define FiveChessSize 15
#endif
//FiveChessSizeΪ���̵ı߳��������޸�Ϊ5~181֮�������������ֵ
namespace FiveChess{
	class chessboard{//������
		private:
			short b[FiveChessSize][FiveChessSize];
			inline void find(int x,short l,int &p,int &n){//��������Ѱ���ض�����(ƽ�������Ʊ���)
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
			inline void find(short X1,short X2,short Y1,short Y2,int x,short l,int &p,int &n){//��[X1,X2),[Y1,Y2)Ѱ���ض�����(ƽ�������Ʊ���)
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
			chessboard(){//���̳�ʼ��(ȫ��)
				memset(b,0,sizeof(b));
			}
			void restart(){//��������(ȫ��)
				memset(b,0,sizeof(b));
			}
			short operator()(unsigned short x,unsigned short y){//һ��λ�õ���������(-1Ϊ���ӣ�1Ϊ����)
				return (x>=FiveChessSize||y>=FiveChessSize)?0:b[x][y];
			}
			bool can_put(unsigned short x,unsigned short y){//�ж��Ƿ������
				return (x>=FiveChessSize||y>=FiveChessSize)?0:(b[x][y]==0?1:0);
			}
			void put(unsigned short x,unsigned short y,short i){//����
				if(can_put(x,y))b[x][y]=i;
			}
			short NobodyWin(){//�ж���Ϸ�Ƿ�������ڷ�Ӯ����1���׷�Ӯ����-1����Ϸδ��������0
				int p=0,n=0;
				find(121,5,p,n);
				if(p!=0)return 1;
				if(n!=0)return -1;
				return 0;
			}
			inline unsigned short empty_position(){//��λ����
				unsigned short a=0;
				for(unsigned short x=0;x<FiveChessSize;x++)for(unsigned short y=0;y<FiveChessSize;y++)if(b[x][y]==0)a++;
				return a;
			}
			void output_screen(){//�����������Ļ
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
								putchar(' ');//�ÿո��ʾ��λ
								break;
							case 1:
								putchar('1');//��'1'��ʾ����
								break;
							case -1:
								putchar('0');//��'0'��ʾ����
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
	struct hashChess{//����״̬��ϣ(unordered_mapʹ��)
		int operator()(const chessboard cb)const{
			return cb.b[FiveChessSize>>1][FiveChessSize>>1]+(cb.b[FiveChessSize>>2][FiveChessSize>>2]<<2)+(cb.b[FiveChessSize-(FiveChessSize>>2)][FiveChessSize-(FiveChessSize>>2)]<<4)+(cb.b[FiveChessSize>>1][FiveChessSize>>2]<<6)+(cb.b[FiveChessSize>>2][FiveChessSize>>1]<<8)+(cb.b[FiveChessSize>>1][FiveChessSize-(FiveChessSize>>2)]<<10)+(cb.b[FiveChessSize-(FiveChessSize>>2)][FiveChessSize>>1]<<12)+(cb.b[FiveChessSize>>2][FiveChessSize-(FiveChessSize>>2)]<<14)+(cb.b[FiveChessSize-(FiveChessSize>>2)][FiveChessSize>>2]<<16)+(cb.b[0][0]<<18)+(cb.b[FiveChessSize-1][FiveChessSize-1]<<20)+(cb.b[FiveChessSize-1][0]<<22)+(cb.b[0][FiveChessSize-1]<<24)+(cb.b[1][FiveChessSize>>1]<<28)+(cb.b[FiveChessSize>>1][1]<<30)+(cb.b[1][1]<<1)+(cb.b[FiveChessSize-1][1]<<3)+(cb.b[1][FiveChessSize-1]<<5)+(cb.b[0][FiveChessSize>>1]<<7)+(cb.b[FiveChessSize>>1][0]<<9)+(cb.b[FiveChessSize>>1][FiveChessSize-1]<<11)+(cb.b[FiveChessSize-1][FiveChessSize>>1]<<13);
		}
	};
	bool operator==(chessboard x,chessboard y){//�ж����������Ƿ���ͬ
		for(unsigned short i=0;i<FiveChessSize;i++)for(unsigned short j=0;j<FiveChessSize;j++)if(x.b[i][j]!=y.b[i][j])return 0;
		return 1;
	}
	bool operator!=(chessboard x,chessboard y){//�ж����������Ƿ�ͬ
		for(unsigned short i=0;i<FiveChessSize;i++)for(unsigned short j=0;j<FiveChessSize;j++)if(x.b[i][j]!=y.b[i][j])return 1;
		return 0;
	}
	class chessAI_static{//��̬���������㷨
		protected:
			long long myK,enemyK,success5[2],success4[2],half4[2],success3[2],half3[2],success2[2],half2[2];
			/*myK��enemyK�ֱ�����Լ���������Է������ӵ�Ȩ��
			����ֱ�����ֵ�������Լ��ͶԷ�����ɡ����ġ����ġ�������������������߶������Ӧ��Ȩ��*/
			short r;//������ɫ��1Ϊ�ڣ�-1Ϊ��
		public:
			chessAI_static(short R){//��ʼ��(1Ϊ�ڣ�-1Ϊ��)
				r=R;
			}
			chessAI_static(){
				r=0;
			}
			void set(){//����Ȩ��(��ChessboardValue.txt�ļ��ж�ȡ)
				std::ifstream inp;
				inp.open("Value\\ChessboardValue.txt",std::ios::in);
				inp>>myK>>enemyK>>success5[0]>>success5[1]>>success4[0]>>success4[1]>>half4[0]>>half4[1]>>success3[0]>>success3[1]>>half3[0]>>half3[1]>>success2[0]>>success2[1]>>half2[0]>>half2[1];
				inp.close();
			}
			void set(char *s){//����Ȩ��(���Զ����ļ��ж�ȡ)
				std::ifstream inp;
				inp.open(s,std::ios::in); 
				inp>>myK>>enemyK>>success5[0]>>success5[1]>>success4[0]>>success4[1]>>half4[0]>>half4[1]>>success3[0]>>success3[1]>>half3[0]>>half3[1]>>success2[0]>>success2[1]>>half2[0]>>half2[1];
				inp.close();
			}
		protected:
			inline long long value(chessboard cb){//���������ֵ����
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
			inline long long value(chessboard cb,short x,short y){//����(x,y)��ֵ����
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
			std::pair<unsigned short,unsigned short> put(chessboard cb){//���ھ�̬��ֵ����������������
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
	class chessAI_dfs_static:public chessAI_static{//���ھ�̬����������֦�������������
		public:
			chessAI_dfs_static(short R){//��ʼ��(1Ϊ�ڣ�-1Ϊ��)
				r=R;
			}
			chessAI_dfs_static(){
				r=0;
			}
		private:
			inline long long value_enemy(chessboard cb){//�Է����������ֵ����
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
			inline long long value_enemy(chessboard cb,unsigned short x,unsigned short y){//����(x,y)�Է���ֵ����
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
			long long MySearch(chessboard cb,std::unordered_map<chessboard,long long,hashChess> &mp,unsigned short deep,unsigned short ep,long long large,long long small);//�����������-�ҷ�����
			long long EnemySearch(chessboard cb,std::unordered_map<chessboard,long long,hashChess> &mp,unsigned short deep,unsigned short ep,long long large,long long small);//�����������-�Է�����
		public:
			std::pair<unsigned short,unsigned short> put(chessboard cb){//����������������;�̬��ֵ������������
				unsigned short ep=cb.empty_position()-1,d=ep>4?4:2,num=8>ep?ep+1:9;//ep:��λ����,d:�������,num:��֧����
				if(ep<=3||ep>=222){
					if(ep==224)return std::make_pair((unsigned short)(FiveChessSize>>1),(unsigned short)(FiveChessSize>>1));//��һ�����������м�
					return chessAI_static::put(cb);//���˵�һ��֮���ǰ�������������ֱ��ʹ�þ�̬��ֵ��������
				}
				chessboard search[9];
				long long v,searchVal[9]={-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807};
				std::pair<unsigned short,unsigned short> searchPair[9];
				srand(rand()+time(0));
				for(unsigned short x=0;x<FiveChessSize;x++)for(unsigned short y=0;y<FiveChessSize;y++)//�������̣�Ѱ�ҽ��ŵ�������
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
				std::unordered_map<chessboard,long long,hashChess> mp;//��ϣ��(�ж��ظ�)
				srand(rand()+time(0));
				v=EnemySearch(search[0],mp,d,ep,-9223372036854775807,9223372036854775807);
				unsigned short i=0;long long n;
				for(unsigned short j=1;j<num;j++){//ѭ����ȡ���ֵ
					n=EnemySearch(search[j],mp,d,ep,v,9223372036854775807);
					if(n>v){
						v=n;i=j;
					}
				}
				return searchPair[i];
			}
	};
	long long chessAI_dfs_static::MySearch(chessboard cb,std::unordered_map<chessboard,long long,hashChess> &mp,unsigned short deep,unsigned short ep,long long large,long long small){//�����������-�ҷ�����
		if(mp.find(cb)!=mp.end())return mp[cb];//����(�������״̬�Ѿ��ڹ�ϣ���д��ڣ��򷵻�)
		long long Val=value(cb);
		if(Val>=success5[0]||Val<=-success5[1]){//����Ѿ�������ɣ��򷵻�
			mp[cb]=Val<<11;
			return Val<<11;
		}
		if(deep<=1){//Ҷ�ӽڵ�
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
		unsigned short num=ep<9?ep:9;//������֧����
		long long t,searchVal[9]={-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807};
		chessboard search[9];
		deep--;ep--;
		for(unsigned short x=0;x<FiveChessSize;x++)for(unsigned short y=0;y<FiveChessSize;y++)//�������̣�Ѱ�ҽ��ŵ�������
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
		if(t>=small||t>success5[0]){//Beta��֦+ʤ������
			mp[cb]=t;
			return t;
		}
		if(t>large)large=t;
		for(unsigned short i=1;i<num;i++){
			Val=EnemySearch(search[i],mp,deep,ep,large,small);
			if(t<Val){
				if(Val>=small||Val>success5[0]){//Beta��֦+ʤ������
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
	long long chessAI_dfs_static::EnemySearch(chessboard cb,std::unordered_map<chessboard,long long,hashChess> &mp,unsigned short deep,unsigned short ep,long long large,long long small){//�����������-�Է�����
		if(mp.find(cb)!=mp.end())return mp[cb];//����(�������״̬�Ѿ��ڹ�ϣ���д��ڣ��򷵻�)
		long long Val=value_enemy(cb);
		if(Val>=success5[0]||Val<=-success5[1]){//����Ѿ�������ɣ��򷵻�
			mp[cb]=-Val<<11;
			return -Val<<11;
		}
		unsigned short num=ep<9?ep:9;//������֧����
		long long t,searchVal[9]={-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807,-9223372036854775807};
		chessboard search[9];
		deep--;ep--;
		for(unsigned short x=0;x<FiveChessSize;x++)for(unsigned short y=0;y<FiveChessSize;y++)//�������̣�Ѱ�ҽ��ŵ�������
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
		if(t<=large||t<-success5[1]){//Alpha��֦+ʤ������
			mp[cb]=t;
			return t;
		}
		if(t<small)small=t;
		for(unsigned short i=1;i<num;i++){
			Val=MySearch(search[i],mp,deep,ep,large,small);
			if(t>Val){
				if(Val<=large||Val<-success5[1]){//Alpha��֦+ʤ������
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
