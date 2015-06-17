#pragma once
class Background
{
public:
	Block arr[10][10];
	POINT pos;	//确定背景整个框的位置。
	Background();
	~Background();
	void drawBack(HDC);
	void liquidate(int& score);
	void clear();

private:

};

Background::Background()
{
	pos.x = 80;					//手机屏幕大小为640,400
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

//绘制背景
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
	int arr_flag[2][10];		//0为列，1为行。
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			arr_flag[i][j] = 1;
		}
	}

	//先判断每一列是否可以消除。
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
	//判断行
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

	//清理列
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
	//清理行
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