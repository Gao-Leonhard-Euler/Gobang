# 五子棋

这是一个计算导论与程序设计课的课程大作业。
本readme文档主要介绍了两个头文件和四个程序的主要功能及落子算法的实现。

## 棋盘.h

宏定义

```cpp
#define FiveChessSize 15
//棋盘的边长，可以依据需求修改为5~181之间的任意正整数值

#define SearchNum 9
//SearchNum为搜索的分支数，可以修改为你想要的值，推荐值为9

#define SearchDep 6
//SearchNum为搜索的深度-1，可以修改为你想要的偶数，推荐值为4
```

命名空间：FiveChess

棋盘类：chessboard

```cpp
    void restart();
    //将棋盘重置为全空

    bool can_put(unsigned short x,unsigned short y);
    //判断坐标(x,y)是否可以落子

    short operator()(unsigned short x,unsigned short y);
    //一个位置的棋子种类(-1为白子，1为黑子)

    void put(unsigned short x,unsigned short y,short i);
    //在坐标(x,y)落子，i=1表示落黑子，i=-1表示落白子

    short NobodyWin();
    //判断是否有人获胜，白子胜返回-1，黑子胜返回1，否则返回0

    unsigned short empty_position();
    //返回棋盘上的空位数量

    void output_screen()
    //输出棋盘至屏幕
```

静态评估算法类：chessAI_static

```cpp
    chessAI_static(short R);
    //初始化(R=1为黑子，R=-1为白子)

    void set();
    //从ChessboardValue.txt文件中读取估值函数参数

    void set(char *s);
    //从自定义文件中读取估值函数参数

    std::pair<unsigned short,unsigned short> put(chessboard cb);
    //给出一个棋盘，求估值函数得出的最佳落子坐标
```

极大极小搜索算法类：chessAI_dfs_static

```cpp
    chessAI_dfs_static(short R);
    //初始化(R=1为黑子，R=-1为白子)

    void set();
    //从ChessboardValue.txt文件中读取估值函数参数

    void set(char *s);
    //从自定义文件中读取估值函数参数

    std::pair<unsigned short,unsigned short> put(chessboard cb);
    //给出一个棋盘，求深度优先搜索得出的最佳落子坐标
```

## 落子算法实现方法

### 静态评估

静态估值函数：

给敌我每种棋形各赋一个权重，统计全棋盘上双方棋形并求和，得出估值函数的值。

五成\
1 1 1 1 1 平衡三进制编码121

活四\
0 1 1 1 1 0 平衡三进制编码120

冲四\
1 1 1 1 0 平衡三进制编码120\
1 1 0 1 1 平衡三进制编码112\
1 0 1 1 1 平衡三进制编码94

活三\
0 1 1 1 0 0 平衡三进制编码117\
0 1 1 0 1 0 平衡三进制编码111

眠三\
1 1 1 0 0 平衡三进制编码117\
1 1 0 1 0 平衡三进制编码111\
1 0 1 1 0 平衡三进制编码93\
1 0 1 0 1 平衡三进制编码91\
0 1 1 1 0 平衡三进制编码39

活二\
0 0 1 1 0 0 平衡三进制编码36\
0 1 0 1 0 0 平衡三进制编码90\
0 1 0 0 1 0 平衡三进制编码84\
0 1 1 0 0 0 平衡三进制编码108

眠二\
1 1 0 0 0 平衡三进制编码108\
1 0 1 0 0 平衡三进制编码90\
0 1 0 1 0 平衡三进制编码30\
0 1 1 0 0 平衡三进制编码36\
1 0 0 1 0 平衡三进制编码84\
1 0 0 0 1 平衡三进制编码82

```chessAI_static::value()```利用```chessboard::find()```函数在棋盘中寻找对应的情况数量并和预设的各个情况的权重相乘得出估值。\
```chessAI_static::put()```每次选取估值最大点落子。

### 极大极小搜索

搜索树上的节点分为两种，一种取子节点的极小值（称为极小节点），另一种取极大值（称为极大节点）。除搜索树根节点外，极小节点的父节点是极大节点，极大节点的父节点是极小节点。\
搜索时限定深度，如果游戏结束或搜索达到限定深度时返回。

极小节点使用```chessAI_dfs_static::EnemySearch()```实现；\
极大节点使用```chessAI_dfs_static::MySearch()```实现。

#### 搜索算法优化

##### 哈希表

搜索时可能会遇到重复的局面，使用STL中的```unordered_map```哈希表进行判断，防止重复搜索浪费时间。头文件中的```struct hashChess```为哈希函数。

##### Alpha-Beta剪枝

如果一个极小节点存在一个子节点的值比拥有相同父节点的极小节点的值更小，那么就没必要对这个节点进行继续搜索；\
如果一个极大节点存在一个子节点的值比拥有相同父节点的极大节点的值更大，那么也没必要对这个节点进行继续搜索。

## 图形化棋盘.h

使用EasyX图形库实现棋盘的图形化展示功能。
**仅支持**$15\times15$**大小的棋盘。**

图形化结构体：visual_chessboard

```cpp
    void init();
    //初始化，输出空白棋盘
    void get(short &x,short &y);
    //获取鼠标点击坐标最接近棋盘上的哪个点
    void draw(short x,short y,short t);
    //落子，t=1时落黑子，否则落白子
```

## Game

包含了人机对战、人人对战、机机对战三个模式，有Easy（采用静态评估算法）和Hard（极大极小搜索算法）两个难度，游戏过程保存在"GameStep.csv"文件。
**仅支持**$15\times15$**大小的棋盘。**

## 回放

读取"GameStep.csv"文件，指定放映速度进行对局回放，可以连续进行多局的回放。
**仅支持**$15\times15$**大小的棋盘。**

## 删除对局记录

删除"GameStep.csv"中指定的一局或多局记录信息。

## 权重文档

"ChessboardValue.txt"存放估值函数使用的权重数据，共16个数。

前2个数分别表示落子时这个位置对敌方的重要性对决策的影响和对己方的重要性对决策的影响，两数的比或许可以决定落子算法更偏向于进攻还是防守。

接下来14个数分别存放自己各个棋形对决策的重要性和敌方各个棋形的威慑性。（棋形指的是上文说到的五成、活四、冲四、活三、眠三、活二、眠二）

## 随机训练

每一轮训练都是在"ChessboardValue.txt"文档里存放的数据基础上，加上一些随机值，创建出另外四个权重文档，让以这五个文档中的数据为权重的静态评估算法互相博弈，统计分数（分数=胜利局数-失败局数），取分数最大者为新的权重文档，删除其他文件。

## License

本项目采用**CC BY-SA 4.0**知识共享许可协议。如需了解该协议，请查阅[https://creativecommons.org/licenses/by-sa/4.0/deed.zh-hans](https://creativecommons.org/licenses/by-sa/4.0/deed.zh-hans)\
This work is licensed under CC BY-SA 4.0. To view a copy of this license, visit [http://creativecommons.org/licenses/by-sa/4.0/](http://creativecommons.org/licenses/by-sa/4.0/)
