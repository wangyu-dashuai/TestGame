#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ROW 3
#define MAX_COL 3

void init(char chessBoard[MAX_ROW][MAX_COL]){ 
	//把数组中的每一个元素都设为空格
	for (int row = 0; row < MAX_ROW; row++){
		for (int col = 0; col < MAX_COL; col++){
			chessBoard[row][col] = ' ';
		}
	}

}
int menu(){
	printf("============\n");
	printf("1.开始游戏\n");
	printf("0.结束游戏\n");
	printf("============\n");
	printf("请输入您的选择：");
	int choice = 0;
	scanf("%d", &choice);
	return choice;
}
void printChessBoard(char chessBoard[MAX_ROW][MAX_COL]){
	//把棋盘打印出来
	//for (int row = 0; row < MAX_ROW; row++){
	//	for (int col = 0; col < MAX_COL; col++){
	//		//注意：使用%c来打印字符
	//		printf("%c",chessBoard[row][col]);
	//	}
	//	printf("\n");
	//}
	//上面的代码虽然能运行出来 但都是空格，看起来不太方便 可以进行优化
	//最好能让元素有边框
	printf("+-+-+-+\n");
	for (int row = 0; row < MAX_ROW; row++){
		printf("|%c|%c|%c|\n",chessBoard[row][0],chessBoard[row][1],chessBoard[row][2]);
		printf("+-+-+-+\n");
	}
}
//让玩家落子，通过控制台输入行和列坐标的方式实现
void playerMove(char chessBoard[MAX_ROW][MAX_COL]){
	while (1){
		printf("请玩家输入坐标(row col)");
		int row = 0;
		int col = 0;
		scanf("%d %d", &row, &col);
		//一定要检验玩家输入的坐标是否合法
		if (row<0 || row>=MAX_ROW || col<0 || col>=MAX_COL){
			//非法情况，此时应该让玩家重新输入
			printf("您的坐标不在合法范围内[0,2]\n");
			continue;
		}
		//检验玩家落子处是否有子了
		if (chessBoard[row][col] != ' '){
			printf("您输入的位置坐标已经有子了\n");
			continue;
		}
		//此时真正落子了
		chessBoard[row][col]= 'x';
		break;
	}
}
//电脑落子
//让电脑随机生成一组行和列
void computerMove(char chessBoard[MAX_ROW][MAX_COL]){
	while (1){
		int row = rand() % MAX_ROW;
		int col = rand() % MAX_COL;
		if (chessBoard[row][col] != ' '){
			//需要保证随机数不能是已经有子的位置
			continue;
		}
		chessBoard[row][col] = 'o';
		break;
	}
}
int isFull(char chessBoard[MAX_ROW][MAX_COL]){
	//找空格，如果找不到就是满了
	for (int row = 0; row < MAX_ROW; row++){
		for (int col = 0; col < MAX_COL; col++){
			if (chessBoard[row][col] == ' '){
				//如果找到空格 说明没满
				return 0;
			}
		}
	}
	return 1;
}
//此处约定返回结果的含义
//'x'表示玩家获胜
//'o'表示电脑获胜
//' '表示胜负未分
//'q'表示和棋
char isWin(char chessBoard[MAX_ROW][MAX_COL]){
	//判定所有的行
	for (int row = 0; row < MAX_ROW; row++){
		if (chessBoard[row][0] != ' ' && chessBoard[row][0] == chessBoard[row][1]
			&& chessBoard[row][1] == chessBoard[row][2]){
			return chessBoard[row][0];
		}
	}
	//判定所有的列
	for (int col = 0; col < MAX_COL; col++){
		if (chessBoard[0][col] != ' ' && chessBoard[0][col] == chessBoard[1][col]
			&& chessBoard[1][col] == chessBoard[2][col]){
			return chessBoard[1][col];
		}	
	}
	//判定两个对角线
	if (chessBoard[0][0] != ' ' && chessBoard[0][0] == chessBoard[1][1]
		&& chessBoard[1][1] == chessBoard[2][2])
		return chessBoard[0][0];
	if (chessBoard[0][2] != ' ' && chessBoard[0][2] == chessBoard[1][1]
		&& chessBoard[1][1] == chessBoard[2][0]){
		return chessBoard[0][2];
	}
	
	//判断是否和棋
	//看棋盘中是否还有剩余空间
	if (isFull(chessBoard)){
		return 'q';
	}
	return ' ';
}
void game(){
	//三子棋一局游戏的基本流程
	//1.创建一个棋盘并初始化
	char chessBoard[MAX_ROW][MAX_COL] = { 0 };
	init(chessBoard);
	char winner = ' ';
	while (1){
		//2.打印棋盘
		printChessBoard(chessBoard);
		//3.玩家落子（通过输入行和列坐标的方式落子）
		playerMove(chessBoard);
		//4.判断胜负关系
		winner = isWin(chessBoard);
		if (winner != ' '){
			break;
		}
		//5.电脑落子（随机位置落子）
		computerMove(chessBoard);
		//6.判断胜负关系
		winner = isWin(chessBoard);
		if (winner != ' '){
			break;
		}
	}
	//7.返回步骤2继续执行
	printChessBoard(chessBoard);
	if (winner == 'x') {
		printf("恭喜您, 您赢了!\n");
	}
	else if (winner == 'o') {
		printf("很遗憾, 您连人工智障都下不过!\n");
	}
	else {
		printf("很遗憾, 您和人工智障五五开!\n");
	}
}
int main(){
	//此处通过简单的交互菜单和玩家交互进行开始一局游戏
	//此处使用强制类型转换，把time_t转换为unsigned int
	srand((unsigned int)time(0));
	while (1){
		int choice = menu();
		if (choice == 1){
			game();
		}
		else if (choice == 0){
			printf("GoodBye!\n");
			break;
		}
	}
	system("pause");
	return 0;
}