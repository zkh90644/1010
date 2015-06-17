#pragma once
#include <iostream>
class Block
{
public:
	int red, green, blue;	//���÷�����ɫ
	int type;				//���÷������࣬Ĭ��Ϊ0����û���κ���ɫ��

	int width, height;		//���÷���߶ȺͿ�ȡ�

	POINT pos;				//���÷���Ĭ�����Ͻǵ�λ�á�
	POINT basic;			//ԭʼλ�á�

	Block();
	~Block();

	void setColor(int r, int g, int b);
	void setPosition(int tmpx, int tmpy);
	void setBasic(int tmpx, int tmpy);
	void resetPosition();

	void Clear();
	void changeType(int r,int g,int b);
	void ChangeSize(int tmpwidth, int tmpheight);
	
	POINT getPoint();
	void getColor(int &r,int &g,int &b);
	int getType();
	int getWidth();
	int getHeight();

	void drawBlock();

};

Block::Block()
{
	setColor(225, 225, 225);
	type = 0;
	setPosition(0, 0);
	ChangeSize(0, 0);

}

Block::~Block()
{
}

void Block::setColor(int r, int g, int b){
	red = r;
	green = g;
	blue = b;
}

void Block::setPosition(int tmpx, int tmpy){
	this->pos.x = tmpx;
	this->pos.y = tmpy;
}

void Block::Clear(){
	type = 0;
	setColor(225, 225, 225);
}

void Block::changeType(int r = 255,int g = 255,int b = 255){
	if (type == 1)
		Clear();
	else
	{
		type = 1;
		setColor(r, g, b);
	}
}


void Block::ChangeSize(int tmpw, int tmph){
	width = tmpw;
	height = tmph;
}

void Block::getColor(int &tr, int &tg, int &tb){
	tr = red;
	tg = green;
	tb = blue;
}

POINT Block::getPoint(){
	POINT tmpp;
	tmpp.x = pos.x;
	tmpp.y = pos.y;
	return tmpp;
}

int Block::getType(){
	return type;
}

int Block::getWidth(){
	return width;
}

int Block::getHeight(){
	return height;
}
void Block::setBasic(int tmpx,int tmpy){
	basic.x = tmpx;
	basic.y = tmpy;
}

void Block::resetPosition(){
	pos = basic;
}