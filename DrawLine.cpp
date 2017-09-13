# include<iostream>
# include<cstdio>
# include<windows.h>
# include<conio.h>
# include<cmath>
# include<cstdlib> 
using namespace std;
class Point
{
public :
	int x, y;
	Point(int x = 0, int y = 0)
	{
		this->x = x;
		this->y = y;
	}
};

void drawline(Point , Point , char * );

class Club
{
public :
	Point *corner[8];
	
	Club(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int x5, int y5, int x6, int y6, int x7, int y7)
	{
		corner[0] = new Point(x0, y0);
		corner[1] = new Point(x1, y1);
		corner[2] = new Point(x2, y2);
		corner[3] = new Point(x3, y3);
		corner[4] = new Point(x4, y4);
		corner[5] = new Point(x5, y5);
		corner[6] = new Point(x6, y6);
		corner[7] = new Point(x7, y7);
	}
	
	Club(int list[16])
	{
		for (int i = 0; i < 8; i++)
		{
			corner[i] = new Point(list[i * 2], list[i * 2 + 1]);
		}
	}
	
	Club(Point *list)
	{
		for (int i = 0; i < 8; i++)
		{
			corner[i] = &list[i];
		}
	}
	
	void draw(void)
	{
		drawline(*corner[7], *corner[6], "x");
		drawline(*corner[7], *corner[4], "x");
		drawline(*corner[6], *corner[5], "x");
		drawline(*corner[5], *corner[4], "x");
		drawline(*corner[7], *corner[3], "x");
		drawline(*corner[6], *corner[2], "x");
		drawline(*corner[5], *corner[1], "x");
		drawline(*corner[4], *corner[0], "x");
		drawline(*corner[3], *corner[2], "x");
		drawline(*corner[3], *corner[0], "x");
		drawline(*corner[2], *corner[1], "x");
		drawline(*corner[1], *corner[0], "x");
	}
};

void gotoxy(int x, int y) 
{
    int xx=0x0b;
    HANDLE hOutput;
    COORD loc;
    loc.X = x;
    loc.Y = y;
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput, loc);
    return;
}

void print(int x, int y, char* c = "0")
{
	gotoxy(2 * x, y);
	printf("%s", c);
}
/*
	 -->+x
	|
	v
	+y
*/

void drawline(int x1, int y1, int x2, int y2, char * sign = "0")
{
	print(x1, y1, sign);
	//print(x2, y2, sign);
	int dx = x1 - x2;
	int dy = y1 - y2;
	int ax1, ay1, ax2, ay2;
	int flag;
	float fm, m, e = -0.5;
	if (abs(dx) < abs(dy))
	{
		int t = x1;
		x1 = y1;
		y1 = t;
		t = x2;
		x2 = y2;
		y2 = t;
		fm = fabs((float)dx / dy);
		flag = -1;
	}
	else
	{
		flag = 1;
		fm = fabs((float)dy / dx);
	}
	dx = abs(x1 - x2);
	dy = abs(y1 - y2);
	int dicx = x1 > x2? -1:1;
	int dicy = y1 > y2? -1:1;
	int j = y1;
	for (int i = 1; i <= dx; i++)
	{
		e += fm;
		if (e > 0)
		{
			e -= 1;
			j += dicy;
		}
		if (flag < 0)
		{
			print(j, i * dicx + x1, sign);
		}
		else
		{
			print(i * dicx + x1, j, sign);
		}
		//Sleep(1);
	}
}

void drawline(Point a, Point b, char * sign = "0")
{
	drawline(a.x, a.y, b.x, b.y, sign);
}

int main(void)
{
	int i, j;
	for (i = 0; i < 5; i++)
	{
		gotoxy(10, 10);
		printf("%d", 5 - i);
		Sleep(100);
	}
	//drawline(25, 25, 10, 0);
	char a[2] = {'0', '\0'};
	
	j = 0;
	for (i = 0; i < 50; i++, j++)
	{
		a[0] = j % 26 + 'a';
		drawline(25, 25, i, 0, a); 
	}
	
	for (i = 0; i < 50; i++, j++)
	{
		a[0] = j % 26 + 'a';
		drawline(25, 25, 50, i, a); 
	}
	
	for (i = 50; i > -1; i--, j++)
	{
		a[0] = j % 26 + 'a';
		drawline(25, 25, i, 50, a); 
	}
	for (i = 50; i > -1; i--, j++)
	{
		a[0] = j % 26 + 'a';
		drawline(25, 25, 0, i, a); 
	}
	for (i = 22; i <= 28; i++)
	{
		print(20, i, "                    ");
	}
	/*
	drawline(0, 0, 60, 0, "-");
	drawline(60, 0, 60, 50, "|");
	drawline(60, 50, 0, 50, "-");
	drawline(0, 50, 0, 0, "|");
	drawline(30, 20, 30, 0, "0");
	drawline(31, 20, 35, 0, "1");
	drawline(32, 21, 60, 15, "2");
	drawline(33, 21, 60, 21, "3");
	drawline(33, 22, 50, 26, "4");
	drawline(32, 23, 40, 40, "5");
	drawline(31, 23, 31, 50, "6");
	drawline(30, 24, 25, 40, "7");
	drawline(29, 23, 0, 28, "8");
	drawline(28, 22, 0, 22, "9");
	drawline(27, 21, 0, 16, "A");*//*
	drawline(27, 20, 20, 0, "B");
	system("cls");
	Club clue(10, 20, 30, 20, 30, 10, 10, 10,  15, 15, 35, 15, 35, 5, 15, 5);
	clue.draw();
	*/
	gotoxy(0, 0);
	getch();
	return 0;
}
/*
*/
