#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
using namespace std;

//定义游戏界面高和宽
#define High 20  
#define Width 50
//定义一个变量，用于储存移动方向
int moveDirection;
//定义食物的坐标
int food_x, food_y;
//定义一个二维数组，初始化为零
int canvas[High][Width] = { 0 };
//定义一个整型，储存分数
int score = 0;
//函数的声明
void initsnake();
void show();
void updateWithoutInput();
void updateWithInput();
void gotoxy(int x, int y);
void moveSnakeByDirection();

//主函数
void main()
{
	//首先生成游戏界面
	initsnake();
	//使用循环不断更新
	while (1)
	{
		show();
		updateWithoutInput();
		updateWithInput();
	}
	system("pause");
}

//将游戏初始化，生成游戏界面
void initsnake()
{
	int i, j;
	//生成垂直方向边框
	for (i = 0; i < High; i++)
	{
		canvas[i][0] = -1;
		canvas[i][Width - 1] = -1;
	}
	//生成水平方向边框
	for (j = 0; j < Width; j++)
	{
		canvas[0][j] = -1;
		canvas[High - 1][j] = -1;
	}
	//在正中间生成蛇头
	canvas[High / 2][Width / 2] = 1;
	//在蛇头水平方向上生成蛇身
	for (i = 1; i <= 4; i++) {
		canvas[High / 2][Width / 2 - i] = i + 1;
	}

	//上下左右四个移动方向
	moveDirection = 4;

	//随机在边框内生成食物
	//为在边框内，横纵坐标应大于2，小于边框减3
	food_x = rand() % (High - 3) + 2;
	food_y = rand() % (Width - 3) + 2;
	canvas[food_x][food_y] = -2;
}

//游戏元素的显示与刷新
void show()
{
	system("cls");
	//从（0，0）开始输出
	gotoxy(0, 0);
	int i, j;
	for (i = 0; i < High; i++)
	{
		for (j = 0; j < Width; j++)
		{
			//数组元素为0时，为空白区域
			if (canvas[i][j] == 0)
				cout << " ";
			//数组元素为-1时，为边框
			else if (canvas[i][j] == -1)
				cout << "#";
			//数组元素为1时，为蛇头
			else if (canvas[i][j] == 1)
				cout << "@";
			//数组元素为大于1时，为蛇身
			else if (canvas[i][j] > 1)
				cout << "*";
			//数组元素为-2时，为食物
			else if (canvas[i][j] == -2)
				cout << "+";
		}
		printf("\n");
	}
	//0-5分速度较慢
	if (score <= 5) {
		Sleep(300);
	}
	//5-10分速度加快
	else if (score > 5 && score <= 10) {
		Sleep(200);
	}
	//10分以上速度再加快
	else if (score > 10 && score <= 15) {
		Sleep(100);
	}
	//15分以上速度再加快
	else if (score > 15) {
		Sleep(50);
	}
}

//控制输出的坐标
void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//标准输出一个句柄
	COORD pos;//表示一个字符在控制台屏幕上的坐标
	pos.X = x;
	pos.Y = y;
	//定位光标位置
	SetConsoleCursorPosition(handle, pos);
}

//控制蛇的移动
void moveSnakeByDirection()
{
	int i, j;

	//扫描边框内所有元素
	for (i = 1; i < High - 1; i++)
		for (j = 1; j < Width - 1; j++)
			//将所有大于0的元素加1
			if (canvas[i][j] > 0)
				canvas[i][j]++;
	//定义旧蛇尾，旧蛇头的坐标
	int oldTail_i, oldTail_j, oldHead_i, oldHead_j;
	int max = 0;
	//扫描边框内所有元素
	for (i = 1; i < High - 1; i++)
		for (j = 1; j < Width - 1; j++)
			//元素值大于0的为蛇
			if (canvas[i][j] > 0)
			{
				//元素值最大的为旧蛇尾
				if (max < canvas[i][j])
				{
					max = canvas[i][j];
					oldTail_i = i;
					oldTail_j = j;
				}
				//元素值为2的是旧蛇头
				if (canvas[i][j] == 2)
				{
					oldHead_i = i;
					oldHead_j = j;
				}
			}
	//定义新蛇头坐标
	int newHead_i, newHead_j;

	//根据移动方向改变旧蛇头坐标
	//方向为1，向上移动时，纵坐标减一，横坐标不变
	if (moveDirection == 1)
	{
		newHead_i = oldHead_i - 1;
		newHead_j = oldHead_j;
	}
	//方向为2，向下移动时，纵坐标加一，横坐标不变
	if (moveDirection == 2)
	{
		newHead_i = oldHead_i + 1;
		newHead_j = oldHead_j;
	}
	//方向为3，向左移动时，纵坐标不变，横坐标减一
	if (moveDirection == 3)
	{
		newHead_i = oldHead_i;
		newHead_j = oldHead_j - 1;
	}
	//方向为4，向下移动时，纵坐标不变，横坐标加一
	if (moveDirection == 4)
	{
		newHead_i = oldHead_i;
		newHead_j = oldHead_j + 1;
	}

	//如果新蛇头碰到食物
	if (canvas[newHead_i][newHead_j] == -2)
	{
		//删除食物
		canvas[food_x][food_y] = 0;
		//随机在边框内生成食物
		food_x = rand() % (High - 3) + 2;
		food_y = rand() % (Width - 3) + 2;
		canvas[food_x][food_y] = -2;
		score++;
	}
	//否则删除旧蛇尾
	else
		canvas[oldTail_i][oldTail_j] = 0;

	//如果新蛇头碰到蛇身(旧蛇头后面一段除外)或碰到边框，游戏失败
	if (canvas[newHead_i][newHead_j] > 3 || (canvas[newHead_i][newHead_j] > 0 && canvas[newHead_i][newHead_j] < 3) || canvas[newHead_i][newHead_j] == -1)
	{
		printf("游戏失败！\n");
		cout << "总得分：" << score << endl;
		Sleep(1000);
		system("pause");
		exit(0);
	}
	//蛇头向反方向移动时，应继续向前移动
	else if (canvas[newHead_i][newHead_j] == 3) {
		//向下移动时，按w，蛇头继续向下
		if (moveDirection == 1)
		{
			newHead_i = newHead_i + 2;
		}
		//向上移动时，按s，蛇头继续向上
		if (moveDirection == 2)
		{
			newHead_i = newHead_i - 2;
		}
		//向右移动时，按a，蛇头继续向右
		if (moveDirection == 3)
		{
			newHead_j = newHead_j + 2;
		}
		//向左移动时，按d，蛇头继续向左
		if (moveDirection == 4)
		{
			newHead_j = newHead_j - 2;
		}
		canvas[newHead_i][newHead_j] = 1;
	}
	//否则输出新蛇头
	else {
		canvas[newHead_i][newHead_j] = 1;
	}

}

//不需要输入的更新
void updateWithoutInput()
{
	//控制蛇的移动函数
	moveSnakeByDirection();
	cout << "游戏玩法：";
	cout << "得分：" << score << endl;

}

//需要有输入的更新
void updateWithInput()
{
	char input;
	//判断是否有键盘输入
	if (_kbhit())
	{
		//读取一个字符，但不显示在屏幕上
		input = _getch();
		//如果输入w，将移动方向变为1，调用蛇的移动函数
		if (input == 'w')
		{
			moveDirection = 1;
			moveSnakeByDirection();
		}
		//如果输入s，将移动方向变为2，调用蛇的移动函数
		else if (input == 's')
		{
			moveDirection = 2;
			moveSnakeByDirection();
		}
		//如果输入a，将移动方向变为3，调用蛇的移动函数
		else if (input == 'a')
		{
			moveDirection = 3;
			moveSnakeByDirection();
		}
		//如果输入d，将移动方向变为4，调用蛇的移动函数
		else if (input == 'd')
		{
			moveDirection = 4;
			moveSnakeByDirection();
		}
	}
}


