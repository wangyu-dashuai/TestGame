#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ROW 3
#define MAX_COL 3

void init(char chessBoard[MAX_ROW][MAX_COL]){ 
	//�������е�ÿһ��Ԫ�ض���Ϊ�ո�
	for (int row = 0; row < MAX_ROW; row++){
		for (int col = 0; col < MAX_COL; col++){
			chessBoard[row][col] = ' ';
		}
	}

}
int menu(){
	printf("============\n");
	printf("1.��ʼ��Ϸ\n");
	printf("0.������Ϸ\n");
	printf("============\n");
	printf("����������ѡ��");
	int choice = 0;
	scanf("%d", &choice);
	return choice;
}
void printChessBoard(char chessBoard[MAX_ROW][MAX_COL]){
	//�����̴�ӡ����
	//for (int row = 0; row < MAX_ROW; row++){
	//	for (int col = 0; col < MAX_COL; col++){
	//		//ע�⣺ʹ��%c����ӡ�ַ�
	//		printf("%c",chessBoard[row][col]);
	//	}
	//	printf("\n");
	//}
	//����Ĵ�����Ȼ�����г��� �����ǿո񣬿�������̫���� ���Խ����Ż�
	//�������Ԫ���б߿�
	printf("+-+-+-+\n");
	for (int row = 0; row < MAX_ROW; row++){
		printf("|%c|%c|%c|\n",chessBoard[row][0],chessBoard[row][1],chessBoard[row][2]);
		printf("+-+-+-+\n");
	}
}
//��������ӣ�ͨ������̨�����к�������ķ�ʽʵ��
void playerMove(char chessBoard[MAX_ROW][MAX_COL]){
	while (1){
		printf("�������������(row col)");
		int row = 0;
		int col = 0;
		scanf("%d %d", &row, &col);
		//һ��Ҫ�����������������Ƿ�Ϸ�
		if (row<0 || row>=MAX_ROW || col<0 || col>=MAX_COL){
			//�Ƿ��������ʱӦ���������������
			printf("�������겻�ںϷ���Χ��[0,2]\n");
			continue;
		}
		//����������Ӵ��Ƿ�������
		if (chessBoard[row][col] != ' '){
			printf("�������λ�������Ѿ�������\n");
			continue;
		}
		//��ʱ����������
		chessBoard[row][col]= 'x';
		break;
	}
}
//��������
//�õ����������һ���к���
void computerMove(char chessBoard[MAX_ROW][MAX_COL]){
	while (1){
		int row = rand() % MAX_ROW;
		int col = rand() % MAX_COL;
		if (chessBoard[row][col] != ' '){
			//��Ҫ��֤������������Ѿ����ӵ�λ��
			continue;
		}
		chessBoard[row][col] = 'o';
		break;
	}
}
int isFull(char chessBoard[MAX_ROW][MAX_COL]){
	//�ҿո�����Ҳ�����������
	for (int row = 0; row < MAX_ROW; row++){
		for (int col = 0; col < MAX_COL; col++){
			if (chessBoard[row][col] == ' '){
				//����ҵ��ո� ˵��û��
				return 0;
			}
		}
	}
	return 1;
}
//�˴�Լ�����ؽ���ĺ���
//'x'��ʾ��һ�ʤ
//'o'��ʾ���Ի�ʤ
//' '��ʾʤ��δ��
//'q'��ʾ����
char isWin(char chessBoard[MAX_ROW][MAX_COL]){
	//�ж����е���
	for (int row = 0; row < MAX_ROW; row++){
		if (chessBoard[row][0] != ' ' && chessBoard[row][0] == chessBoard[row][1]
			&& chessBoard[row][1] == chessBoard[row][2]){
			return chessBoard[row][0];
		}
	}
	//�ж����е���
	for (int col = 0; col < MAX_COL; col++){
		if (chessBoard[0][col] != ' ' && chessBoard[0][col] == chessBoard[1][col]
			&& chessBoard[1][col] == chessBoard[2][col]){
			return chessBoard[1][col];
		}	
	}
	//�ж������Խ���
	if (chessBoard[0][0] != ' ' && chessBoard[0][0] == chessBoard[1][1]
		&& chessBoard[1][1] == chessBoard[2][2])
		return chessBoard[0][0];
	if (chessBoard[0][2] != ' ' && chessBoard[0][2] == chessBoard[1][1]
		&& chessBoard[1][1] == chessBoard[2][0]){
		return chessBoard[0][2];
	}
	
	//�ж��Ƿ����
	//���������Ƿ���ʣ��ռ�
	if (isFull(chessBoard)){
		return 'q';
	}
	return ' ';
}
void game(){
	//������һ����Ϸ�Ļ�������
	//1.����һ�����̲���ʼ��
	char chessBoard[MAX_ROW][MAX_COL] = { 0 };
	init(chessBoard);
	char winner = ' ';
	while (1){
		//2.��ӡ����
		printChessBoard(chessBoard);
		//3.������ӣ�ͨ�������к�������ķ�ʽ���ӣ�
		playerMove(chessBoard);
		//4.�ж�ʤ����ϵ
		winner = isWin(chessBoard);
		if (winner != ' '){
			break;
		}
		//5.�������ӣ����λ�����ӣ�
		computerMove(chessBoard);
		//6.�ж�ʤ����ϵ
		winner = isWin(chessBoard);
		if (winner != ' '){
			break;
		}
	}
	//7.���ز���2����ִ��
	printChessBoard(chessBoard);
	if (winner == 'x') {
		printf("��ϲ��, ��Ӯ��!\n");
	}
	else if (winner == 'o') {
		printf("���ź�, �����˹����϶��²���!\n");
	}
	else {
		printf("���ź�, �����˹��������忪!\n");
	}
}
int main(){
	//�˴�ͨ���򵥵Ľ����˵�����ҽ������п�ʼһ����Ϸ
	//�˴�ʹ��ǿ������ת������time_tת��Ϊunsigned int
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