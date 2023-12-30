#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
using namespace std;

//������Ϸ����ߺͿ�
#define High 20  
#define Width 50
//����һ�����������ڴ����ƶ�����
int moveDirection;
//����ʳ�������
int food_x, food_y;
//����һ����ά���飬��ʼ��Ϊ��
int canvas[High][Width] = { 0 };
//����һ�����ͣ��������
int score = 0;
//����������
void initsnake();
void show();
void updateWithoutInput();
void updateWithInput();
void gotoxy(int x, int y);
void moveSnakeByDirection();

//������
void main()
{
	//����������Ϸ����
	initsnake();
	//ʹ��ѭ�����ϸ���
	while (1)
	{
		show();
		updateWithoutInput();
		updateWithInput();
	}
	system("pause");
}

//����Ϸ��ʼ����������Ϸ����
void initsnake()
{
	int i, j;
	//���ɴ�ֱ����߿�
	for (i = 0; i < High; i++)
	{
		canvas[i][0] = -1;
		canvas[i][Width - 1] = -1;
	}
	//����ˮƽ����߿�
	for (j = 0; j < Width; j++)
	{
		canvas[0][j] = -1;
		canvas[High - 1][j] = -1;
	}
	//�����м�������ͷ
	canvas[High / 2][Width / 2] = 1;
	//����ͷˮƽ��������������
	for (i = 1; i <= 4; i++) {
		canvas[High / 2][Width / 2 - i] = i + 1;
	}

	//���������ĸ��ƶ�����
	moveDirection = 4;

	//����ڱ߿�������ʳ��
	//Ϊ�ڱ߿��ڣ���������Ӧ����2��С�ڱ߿��3
	food_x = rand() % (High - 3) + 2;
	food_y = rand() % (Width - 3) + 2;
	canvas[food_x][food_y] = -2;
}

//��ϷԪ�ص���ʾ��ˢ��
void show()
{
	system("cls");
	//�ӣ�0��0����ʼ���
	gotoxy(0, 0);
	int i, j;
	for (i = 0; i < High; i++)
	{
		for (j = 0; j < Width; j++)
		{
			//����Ԫ��Ϊ0ʱ��Ϊ�հ�����
			if (canvas[i][j] == 0)
				cout << " ";
			//����Ԫ��Ϊ-1ʱ��Ϊ�߿�
			else if (canvas[i][j] == -1)
				cout << "#";
			//����Ԫ��Ϊ1ʱ��Ϊ��ͷ
			else if (canvas[i][j] == 1)
				cout << "@";
			//����Ԫ��Ϊ����1ʱ��Ϊ����
			else if (canvas[i][j] > 1)
				cout << "*";
			//����Ԫ��Ϊ-2ʱ��Ϊʳ��
			else if (canvas[i][j] == -2)
				cout << "+";
		}
		printf("\n");
	}
	//0-5���ٶȽ���
	if (score <= 5) {
		Sleep(300);
	}
	//5-10���ٶȼӿ�
	else if (score > 5 && score <= 10) {
		Sleep(200);
	}
	//10�������ٶ��ټӿ�
	else if (score > 10 && score <= 15) {
		Sleep(100);
	}
	//15�������ٶ��ټӿ�
	else if (score > 15) {
		Sleep(50);
	}
}

//�������������
void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//��׼���һ�����
	COORD pos;//��ʾһ���ַ��ڿ���̨��Ļ�ϵ�����
	pos.X = x;
	pos.Y = y;
	//��λ���λ��
	SetConsoleCursorPosition(handle, pos);
}

//�����ߵ��ƶ�
void moveSnakeByDirection()
{
	int i, j;

	//ɨ��߿�������Ԫ��
	for (i = 1; i < High - 1; i++)
		for (j = 1; j < Width - 1; j++)
			//�����д���0��Ԫ�ؼ�1
			if (canvas[i][j] > 0)
				canvas[i][j]++;
	//�������β������ͷ������
	int oldTail_i, oldTail_j, oldHead_i, oldHead_j;
	int max = 0;
	//ɨ��߿�������Ԫ��
	for (i = 1; i < High - 1; i++)
		for (j = 1; j < Width - 1; j++)
			//Ԫ��ֵ����0��Ϊ��
			if (canvas[i][j] > 0)
			{
				//Ԫ��ֵ����Ϊ����β
				if (max < canvas[i][j])
				{
					max = canvas[i][j];
					oldTail_i = i;
					oldTail_j = j;
				}
				//Ԫ��ֵΪ2���Ǿ���ͷ
				if (canvas[i][j] == 2)
				{
					oldHead_i = i;
					oldHead_j = j;
				}
			}
	//��������ͷ����
	int newHead_i, newHead_j;

	//�����ƶ�����ı����ͷ����
	//����Ϊ1�������ƶ�ʱ���������һ�������겻��
	if (moveDirection == 1)
	{
		newHead_i = oldHead_i - 1;
		newHead_j = oldHead_j;
	}
	//����Ϊ2�������ƶ�ʱ���������һ�������겻��
	if (moveDirection == 2)
	{
		newHead_i = oldHead_i + 1;
		newHead_j = oldHead_j;
	}
	//����Ϊ3�������ƶ�ʱ�������겻�䣬�������һ
	if (moveDirection == 3)
	{
		newHead_i = oldHead_i;
		newHead_j = oldHead_j - 1;
	}
	//����Ϊ4�������ƶ�ʱ�������겻�䣬�������һ
	if (moveDirection == 4)
	{
		newHead_i = oldHead_i;
		newHead_j = oldHead_j + 1;
	}

	//�������ͷ����ʳ��
	if (canvas[newHead_i][newHead_j] == -2)
	{
		//ɾ��ʳ��
		canvas[food_x][food_y] = 0;
		//����ڱ߿�������ʳ��
		food_x = rand() % (High - 3) + 2;
		food_y = rand() % (Width - 3) + 2;
		canvas[food_x][food_y] = -2;
		score++;
	}
	//����ɾ������β
	else
		canvas[oldTail_i][oldTail_j] = 0;

	//�������ͷ��������(����ͷ����һ�γ���)�������߿���Ϸʧ��
	if (canvas[newHead_i][newHead_j] > 3 || (canvas[newHead_i][newHead_j] > 0 && canvas[newHead_i][newHead_j] < 3) || canvas[newHead_i][newHead_j] == -1)
	{
		printf("��Ϸʧ�ܣ�\n");
		cout << "�ܵ÷֣�" << score << endl;
		Sleep(1000);
		system("pause");
		exit(0);
	}
	//��ͷ�򷴷����ƶ�ʱ��Ӧ������ǰ�ƶ�
	else if (canvas[newHead_i][newHead_j] == 3) {
		//�����ƶ�ʱ����w����ͷ��������
		if (moveDirection == 1)
		{
			newHead_i = newHead_i + 2;
		}
		//�����ƶ�ʱ����s����ͷ��������
		if (moveDirection == 2)
		{
			newHead_i = newHead_i - 2;
		}
		//�����ƶ�ʱ����a����ͷ��������
		if (moveDirection == 3)
		{
			newHead_j = newHead_j + 2;
		}
		//�����ƶ�ʱ����d����ͷ��������
		if (moveDirection == 4)
		{
			newHead_j = newHead_j - 2;
		}
		canvas[newHead_i][newHead_j] = 1;
	}
	//�����������ͷ
	else {
		canvas[newHead_i][newHead_j] = 1;
	}

}

//����Ҫ����ĸ���
void updateWithoutInput()
{
	//�����ߵ��ƶ�����
	moveSnakeByDirection();
	cout << "��Ϸ�淨��";
	cout << "�÷֣�" << score << endl;

}

//��Ҫ������ĸ���
void updateWithInput()
{
	char input;
	//�ж��Ƿ��м�������
	if (_kbhit())
	{
		//��ȡһ���ַ���������ʾ����Ļ��
		input = _getch();
		//�������w�����ƶ������Ϊ1�������ߵ��ƶ�����
		if (input == 'w')
		{
			moveDirection = 1;
			moveSnakeByDirection();
		}
		//�������s�����ƶ������Ϊ2�������ߵ��ƶ�����
		else if (input == 's')
		{
			moveDirection = 2;
			moveSnakeByDirection();
		}
		//�������a�����ƶ������Ϊ3�������ߵ��ƶ�����
		else if (input == 'a')
		{
			moveDirection = 3;
			moveSnakeByDirection();
		}
		//�������d�����ƶ������Ϊ4�������ߵ��ƶ�����
		else if (input == 'd')
		{
			moveDirection = 4;
			moveSnakeByDirection();
		}
	}
}


