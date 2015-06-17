#pragma once
class Background
{
public:
	Block arr[10][10];
	POINT pos;	//ȷ�������������λ�á�
	Background();
	~Background();
	void drawBack(HDC);
	void liquidate(int& score);
	void clear();

private:

};

Background::Background()
{
	pos.x = 80;					//�ֻ���Ļ��СΪ640,400
	pos.y = 100;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			arr[i][j].setColor(225, 225, 225);
			arr[i][j].setPosition((pos.x + 31 * i), (pos.y + 31 * j));
			arr[i][j].ChangeSize(30, 30); 
		}
	}
}

Background::~Background()
{
}

//���Ʊ���
void Background::drawBack(HDC hdc){
	HPEN hpen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	SelectObject(hdc, hpen);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{	
			HBRUSH hbrush;
			hbrush = CreateSolidBrush(RGB(arr[i][j].red, arr[i][j].green, arr[i][j].blue));
			SelectObject(hdc, hbrush);
			RoundRect(hdc, arr[i][j].pos.x, arr[i][j].pos.y, arr[i][j].pos.x + 30, arr[i][j].pos.y + 30, 7, 7);
			DeleteObject(hbrush);
		}
	}
	DeleteObject(hpen);
}

void Background::liquidate(int &score){
	int arr_flag[2][10];		//0Ϊ�У�1Ϊ�С�
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			arr_flag[i][j] = 1;
		}
	}

	//���ж�ÿһ���Ƿ����������
	for (i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (arr[i][j].type == 0)
			{
				arr_flag[0][i] = 0;
				break;
			}
		}
	}
	//�ж���
	for (i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (arr[j][i].type == 0)
			{
				arr_flag[1][i] = 0;
				break;
			}
		}
	}

	//������
	for (i = 0; i < 10; i++)
	{
		if (arr_flag[0][i] == 1)
		{
			for (int j = 0; j < 10; j++)
			{
				arr[i][j].Clear();
			}
		}
	}
	//������
	for (i = 0; i < 10; i++)
	{
		if (arr_flag[1][i] == 1)
		{
			for (int j = 0; j < 10; j++)
			{
				arr[j][i].Clear();
			}
		}
	}


	for (i = 0; i < 2; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (arr_flag[i][j] == 1)
			{
				score += 10;
			}
		}
	}
}

void Background::clear(){
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			arr[i][j].Clear();
		}
	}
}