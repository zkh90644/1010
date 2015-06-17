#pragma once
#include <ctime>
#include <cmath>

#define TYPE_1 0		//����
#define TYPE_2 1		//�۵�
#define TYPE_3 2		//������
#define TYPE_NULL -1	//û��ͼ��

class Bigsquare
{
public:
	Block arr[5][5];		//����������25�����
	POINT pos;				//���ϽǵĶ�λ��Ϊpos
	POINT basic;			//�����ʼλ�á�
	int type;				//�ڲ���ܵ����͡�
	int colorr, colorg, colorb;	//�󷽿���ʵ�ʵ���ɫ��
	int blockNum;
	int model;		//�������͵����ӣ��Ӷ������ܷ������������жϡ���type = TYPE_1��ʱ��0-3Ϊ���ĳ���2-5��4-7Ϊ��ĳ���2-5����Ϊ1�϶���λ�÷Ž�ȥ���ʲ����ǡ�
					//��TYPE_2��ʱ��0-3Ϊ3Ϊ�̵�4������4-7Ϊ4�����ķ���
					//��TYPE_3��ʱ��1Ϊ2*2�������Σ�0Ϊ3*3�������Ρ�

	Bigsquare(int,int);
	Bigsquare();
	~Bigsquare();
	void drawSquare(HDC);
	void clear();			//��մ���е�����С�飬����type = TYPE_NULL
	void reset();			//�����ع�����λ��
	int randomStyle(int);
	bool isInBigSquare(int, int);
	void moveSquare(int dx, int dy);
	bool beSet(Background&);
	void setBasic(int,int);

};

Bigsquare::Bigsquare()
{
	//beclick = false;
	pos.x = basic.x = 0;
	pos.y = basic.y = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			arr[i][j].setColor(225, 225, 225);
			arr[i][j].setPosition((pos.x + 31 * i), (pos.y + 31 * j));
			arr[i][j].setBasic((pos.x + 31 * i), (pos.y + 31 * j));
			arr[i][j].ChangeSize(30, 30);
		}
	}
	model = 0;
	type = TYPE_NULL; 
	blockNum = 0;
}

Bigsquare::Bigsquare(int x = 0,int y = 0)
{
	//beclick = false;
	pos.x = basic.x = x;
	pos.y = basic.y = y;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			arr[i][j].setColor(225, 225, 225);
			arr[i][j].setPosition((pos.x + 31 * i), (pos.y + 31 * j));
			arr[i][j].setBasic((pos.x + 31 * i), (pos.y + 31 * j));
			arr[i][j].ChangeSize(30, 30);
		}
	}
	model = 0;
	type = TYPE_NULL; 
	blockNum = 0;
}

void Bigsquare::setBasic(int x, int y){
	pos.x = basic.x = x;
	pos.y = basic.y = y;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			arr[i][j].setPosition((pos.x + 31 * i), (pos.y + 31 * j));
			arr[i][j].setBasic((pos.x + 31 * i), (pos.y + 31 * j));
		}
	}
}

Bigsquare::~Bigsquare()
{
}

void Bigsquare::drawSquare(HDC hdc){
	HBRUSH hbrush;
	HPEN hpen;
	hpen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	SelectObject(hdc, hpen);

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (arr[i][j].type != 0){
				hbrush = CreateSolidBrush(RGB(arr[i][j].red, arr[i][j].green, arr[i][j].blue));
				SelectObject(hdc, hbrush);
				RoundRect(hdc, arr[i][j].pos.x, arr[i][j].pos.y, arr[i][j].pos.x + 30, arr[i][j].pos.y + 30, 7, 7);
				DeleteObject(hbrush);
			}
		}
	}
	DeleteObject(hpen);
}

int Bigsquare::randomStyle(int r1 = (unsigned)time(0)){
	srand(r1);
	int j = 0;
	//for (int i = 0; i < 3; i++)
	//{
		type = rand() % 3;		//�жϳ���ͼ�ε�����
		if (type == TYPE_1){
			int num = rand() % 9;	//0Ϊ1��-����1Ϊ2��-����2Ϊ3��-����3Ϊ4��-����4Ϊ5��-����5Ϊ2�ᣬ6Ϊ3�ᣬ7Ϊ4�ᣬ8Ϊ5�ᡣ
			model = num - 1;
			switch (num)
			{
			case 0:
				this->arr[2][2].changeType(125, 142, 212);
				colorr = 125;
				colorg = 142;
				colorb = 212;
				blockNum = 1;
				break;
			case 1:
				this->arr[2][1].changeType(254, 198, 61);
				this->arr[2][2].changeType(254, 198, 61);
				colorr = 254;
				colorg = 198;
				colorb = 61;
				blockNum = 2;
				break;
			case 2:
				for (j = 1; j < 4; j++)
				{
					this->arr[2][j].changeType(236, 149, 72);
				}
				colorr = 236;
				colorg = 149;
				colorb = 72;
				blockNum = 3;
				break;
			case 3:
				for (j = 0; j < 4; j++)
				{
					this->arr[2][j].changeType(230, 106, 130);
				}
				colorr = 230;
				colorg = 106;
				colorb = 130;
				blockNum = 4;
				break;
			case 4:
				for (j = 0; j < 5; j++)
				{
					this->arr[2][j].changeType(218, 101, 84);
				}
				colorr = 218;
				colorg = 101;
				colorb = 84;
				blockNum = 5;
				break;
			case 5:
				this->arr[1][2].changeType(254, 198, 61);
				this->arr[2][2].changeType(254, 198, 61);
				colorr = 254;
				colorg = 198;
				colorb = 61;
				blockNum = 2;
				break;
			case 6:
				for (j = 1; j < 4; j++)
				{
					this->arr[j][2].changeType(236, 149, 72);
				}
				colorr = 236;
				colorg = 149;
				colorb = 72; 
				blockNum = 3;
				break;
			case 7:
				for (j = 0; j < 4; j++)
				{
					this->arr[j][2].changeType(230, 106, 130);
				}
				colorr = 230;
				colorg = 106;
				colorb = 130;
				blockNum = 4;
				break;
			case 8:
				for (j = 0; j < 5; j++)
				{
					this->arr[j][2].changeType(218, 101, 84);
				}
				colorr = 218;
				colorg = 101;
				colorb = 84;
				blockNum = 5;
				break;
			}
		}
		else if (type == TYPE_2)
		{
			int num = rand() % 2;//�жϳ���
			int j = rand() % 4;	//�жϷ���
			model = num * 4 + j;
			switch (num)
			{
			case 0:
				this->arr[2][2].changeType(87, 203, 132);
				switch (j)
				{
				case 0:
					this->arr[2][1].changeType(87, 203, 132);
					this->arr[3][2].changeType(87, 203, 132);
					break;
				case 1:
					this->arr[2][1].changeType(87, 203, 132);
					this->arr[1][2].changeType(87, 203, 132);
					break;
				case 2:
					this->arr[3][2].changeType(87, 203, 132);
					this->arr[2][3].changeType(87, 203, 132);
					break;
				case 3:
					this->arr[1][2].changeType(87, 203, 132);
					this->arr[2][3].changeType(87, 203, 132);
					break;
				}
				colorr = 87;
				colorg = 203;
				colorb = 132; 
				blockNum = 3;
				break;
			case 1:
				switch (j)
				{
				case 0:
					this->arr[1][1].changeType(90, 190, 226);
					this->arr[1][2].changeType(90, 190, 226);
					this->arr[1][3].changeType(90, 190, 226);
					this->arr[2][3].changeType(90, 190, 226);
					this->arr[3][3].changeType(90, 190, 226);
					break;
				case 1:
					this->arr[3][1].changeType(90, 190, 226);
					this->arr[3][2].changeType(90, 190, 226);
					this->arr[3][3].changeType(90, 190, 226);
					this->arr[2][3].changeType(90, 190, 226);
					this->arr[1][3].changeType(90, 190, 226);
					break;
				case 2:
					this->arr[1][3].changeType(90, 190, 226);
					this->arr[1][2].changeType(90, 190, 226);
					this->arr[1][1].changeType(90, 190, 226);
					this->arr[2][1].changeType(90, 190, 226);
					this->arr[3][1].changeType(90, 190, 226);
					break;
				case 3:
					this->arr[3][2].changeType(90, 190, 226);
					this->arr[3][3].changeType(90, 190, 226);
					this->arr[2][1].changeType(90, 190, 226);
					this->arr[1][1].changeType(90, 190, 226);
					this->arr[3][1].changeType(90, 190, 226);
					break;
				}
				colorr = 90;
				colorg = 190;
				colorb = 226; 
				blockNum = 5;
				break;
			}
		}
		else
		{
			int num = rand() % 2;
			int j = 0;
			model = num;
			switch (num)
			{
			case 0:
				for (j = 1; j < 4; j++)
				{
					for (int k = 1; k < 4; k++)
					{
						this->arr[j][k].changeType(76, 212, 174);
					}
				}
				colorr = 76;
				colorg = 212;
				colorb = 174;
				blockNum = 9;
				break;
			case 1:
				for (j = 1; j < 3; j++)
				{
					for (int k = 1; k < 3; k++)
					{
						this->arr[j][k].changeType(152,220,83);
					}
				}
				colorr = 152;
				colorg = 220;
				colorb = 83;
				blockNum = 4;
				break;
			}
		}
	//}
		return rand();
}
void Bigsquare::clear(){
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			arr[i][j].Clear();
		}
	}
	colorr = 225;
	colorg = 225;
	colorb = 225;
	type = TYPE_NULL;
	pos = basic;
	blockNum = 0;
}

bool Bigsquare::isInBigSquare(int x, int y){
	if (x >= pos.x&&x <= pos.x + 5 * (arr[0][0].width + 1))
	{
		if (y>pos.y&&y < pos.y + 5 * (arr[0][0].height + 1))
		{
			//beclick = true;
			return true;
		}
	}
	return false;
}

void Bigsquare::moveSquare(int dx, int dy){
	pos.x += dx;
	pos.y += dy;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			arr[i][j].setPosition(arr[i][j].pos.x + dx, arr[i][j].pos.y + dy);
		}
	}
}

void Bigsquare::reset(){
	pos = basic;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			arr[i][j].resetPosition();
		}
	}
}
bool Bigsquare::beSet(Background &bg){
	bool flag = true, flagx = true, flagy = true;		//�ж��Ƿ�Ӱ�ϵĵ��Ƿ���ֵ
	POINT arr_p[9] = { { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } };
	POINT abspoint,d;
	d.x = abs(pos.x - bg.pos.x) % 31;
	d.y = abs(pos.y - bg.pos.y) % 31;
	int k = 0;
	//ȷ����һ���Ӧ��x��
	if (d.x>15)
	{
		for (int i = 0; i < 5; i++)
		{
			if (!flagx)
			{
				break;
			}
			for (int j = 0; j < 5; j++)
			{
				if (arr[i][j].type != 0)
				{
					abspoint.x = arr[i][j].pos.x + d.x;
					if (abspoint.x >= bg.pos.x && abspoint.x <= bg.pos.x + (10) * 31)
					{
						arr_p[k].x = (abspoint.x - bg.pos.x) / 31;
						k++;
					}
					else
					{
						flagx = false;
					}
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (!flagx)
				{
					break;
				}
				if (arr[i][j].type != 0)
				{
					abspoint.x = arr[i][j].pos.x + d.x;
					if (abspoint.x >= bg.pos.x && abspoint.x <= bg.pos.x + (10) * 31)
					{
						arr_p[k].x = (abspoint.x - bg.pos.x) / 31;
						k++;
					}
					else
					{
						flagx = false;
					}
				}
			}
		}
	}

	k = 0;
	if (d.y>15)
	{
		for (int i = 0; i < 5; i++)
		{
			if (!flagy)
			{
				break;
			}
			for (int j = 0; j < 5; j++)
			{
				if (arr[i][j].type != 0)
				{
					abspoint.y = arr[i][j].pos.y + d.y;
					if (abspoint.y >= bg.pos.y && abspoint.y <= bg.pos.y + (10) * 31)
					{
						arr_p[k].y = (abspoint.y - bg.pos.y) / 31;
						k++;
					}
					else
					{
						flagy = false;
					}
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			if (!flagy)
			{
				break;
			}
			for (int j = 0; j < 5; j++)
			{
				if (arr[i][j].type != 0)
				{
					abspoint.y = arr[i][j].pos.y + d.y;
					if (abspoint.y >= bg.pos.y && abspoint.y <= bg.pos.y + (10) * 31)
					{
						arr_p[k].y = (abspoint.y - bg.pos.y) / 31;
						k++;
					}
					else
					{
						flagy = false;
					}
				}
			}
		}
	}

	if (flagx&&flagy)
	{
		for (int i = 0; i < 9; i++)
		{
			if (arr_p[i].x != -1){
				if (bg.arr[arr_p[i].x][arr_p[i].y].type != 0)
				{
					flag = false;
					break;
				}
			}
		}

		if (flag)
		{
			for (int i = 0; i < 9; i++)
			{
				if (arr_p[i].x != -1)
				{
					bg.arr[arr_p[i].x][arr_p[i].y].type = 1;
					bg.arr[arr_p[i].x][arr_p[i].y].red = colorr;
					bg.arr[arr_p[i].x][arr_p[i].y].green = colorg;
					bg.arr[arr_p[i].x][arr_p[i].y].blue = colorb;
				}
			}
		}
		return flag;
	}

	return false;
}