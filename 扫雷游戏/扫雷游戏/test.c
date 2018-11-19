#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define MAX_ROW 10
#define MAX_COL 10
#define DEFAULT_MINE_COUNT 10

char show_map[MAX_ROW + 2][MAX_COL + 2];
char mine_map[MAX_ROW + 2][MAX_COL + 2];

int Menu() {
	printf("=================\n");
	printf("1.开始游戏\n");
	printf("0.退出游戏\n");
	printf("=================\n");
	int choice = 0;
	scanf("%d", &choice);
	return choice;
}

void Init(char show_map[MAX_ROW + 2][MAX_COL + 2], char mine_map[MAX_ROW + 2][MAX_COL + 2]) {
	srand((unsigned int)time(0));
	for (int row = 0; row < MAX_ROW + 2; ++row) {
		for (int col = 0; col < MAX_COL + 2; ++col) {
			show_map[row][col] = '*';
		}
	}
	for (int row = 0; row < MAX_ROW + 2; ++row) {
		for (int col = 0; col < MAX_COL + 2; ++col) {
			mine_map[row][col] = '0';
		}
	}
	int mine_count = DEFAULT_MINE_COUNT;
	while (mine_count > 0) {
		int row = rand() % 10 + 1;
		int col = rand() % 10 + 1;
		if (mine_map[row][col] == '1') {
			continue;
		}
		mine_map[row][col] = '1';
		--mine_count;
	}
}

void DisplayMap(char map[MAX_ROW + 2][MAX_COL + 2]) {
	printf("    ");
	for (int i = 1; i <= MAX_COL; ++i) {
		printf("%d ", i);
	}
	printf("\n");
	for (int i = 1; i <= MAX_COL; ++i) {
		printf("---");
	}
	printf("\n");
	for (int row = 1; row <= MAX_COL; ++row) {
		printf("%02d| ", row);
		for (int col = 1; col <= MAX_COL; ++col) {
			printf("%c ", map[row][col]);
		}
		printf("\n");
	}
}

int Mine_cnt(int row, int col) {
	int count = 0;
	if (mine_map[row - 1][col] == '1') {
		count++;
	}
	if (mine_map[row - 1][col - 1] == '1') {
		count++;
	}
	if (mine_map[row - 1][col + 1] == '1') {
		count++;
	}
	if (mine_map[row][col - 1] == '1') {
		count++;
	}
	if (mine_map[row][col + 1] == '1') {
		count++;
	}
	if (mine_map[row + 1][col - 1] == '1') {
		count++;
	}
	if (mine_map[row + 1][col] == '1') {
		count++;
	}
	if (mine_map[row + 1][col + 1] == '1') {
		count++;
	}
	return count;
}

void Open_map(int row, int col) {
	if (show_map[row][col] == '*' && mine_map[row][col] == '0') {
		if (Mine_cnt(row, col) != 0) {
			show_map[row][col] = Mine_cnt(row,col) + '0';
		}
		else {
			show_map[row][col] = ' ';
			Open_map(row - 1, col - 1);
			Open_map(row - 1, col);
			Open_map(row - 1, col + 1);
			Open_map(row , col - 1);
			Open_map(row , col + 1);
			Open_map(row + 1, col - 1);
			Open_map(row + 1, col);
			Open_map(row + 1, col + 1);
		}
	}
}
int Blank_cnt(int row,int col) {
	int blank_cnt = 0;
	for (row = 1; row <= MAX_ROW; ++row) {
		for (col = 1; col <= MAX_COL; ++col) {
			if (show_map[row][col] == '*') {
				++blank_cnt;
			}
		}
	}
	return blank_cnt;
}
void Game() {
	
	Init(show_map, mine_map);
	DisplayMap(show_map);
	while (1) {
		int row, col;
		printf("请输入坐标:");
		scanf("%d %d", &row, &col);
		if (row <= 0 || row > MAX_ROW || col <= 0 || col > MAX_COL) {
			printf("您的输入不合法,请重新输入!\n");
			continue;
		}
		if (mine_map[row][col] == '1') {
			printf("踩到地雷,游戏结束!\n");
			DisplayMap(mine_map);
			break;
		}
	
		Open_map(row, col);
		DisplayMap(show_map);
		Blank_cnt(row, col);
		if (Blank_cnt(row, col) == MAX_ROW * MAX_COL - DEFAULT_MINE_COUNT) {
			printf("恭喜您扫雷成功!\n");
			DisplayMap(mine_map);
			break;
		}
	}
}

void Start() {
	while (1) {
		int choice = Menu();
		if (choice == 0) {
			break;
		}
		Game();
	}
}

int main() {
	Start();
	system("pause");
	return 0;
}

	