# include<iostream>
# include<cstdio>
# include<windows.h>
# include<conio.h>
# include<cmath>
# include<cstdlib> 
using namespace std;

void gotoxy(int , int);
void print(int, int, char *);
void drawline(int , int , int , int , char *);
int fourfive(float );
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

class Circle
{
public :
	Point * centerPos;
	int a;
	int b;
	Circle()
	{
		centerPos = new Point(0, 0);
		a = b = 0;
	}
	Circle(Point * pos, int a, int b = -1)
	{
		centerPos = pos;
		this->a = a > 0 ? a : -a;
		if (b < 0)
		{
			this->b = a;
		}
		else
		{
			this->b = b;
		}
	}
	Circle(int x, int y, int a, int b = -1)
	{
		centerPos = new Point(x, y);
		this->a = a > 0 ? a : -a;
		if (b < 0)
		{
			this->b = a;
		}
		else
		{
			this->b = b;
		}
	}
	int w;
	void onDraw(char * sign = "o")
	{
		int penX = 0, penY = b;
		int nextX = penX + 1, nextY = 0;
		float step = (float)b * b / (a * a);
		float e = -0.5;
		
		for (; nextX <= a; nextX++)
		{
			nextY = getY(nextX);
			p4line(penX, penY, nextX, nextY, sign);
			gotoxy(0, w++);
			printf("%d, %d, %d, %d", penX, penY, nextX, nextY);
			penX = nextX;
			penY = nextY;
		}
	}
private :
	
	int getY(int x)
	{
		float k = (float)b / a;
		k = k * sqrt(a * a - x * x);
		printf("  %f", k);
		return fourfive(k);
	}
	
	void p4line(int a, int b, int c, int d, char * sign)
	{
		drawline(centerPos->x + a, centerPos->y + b, centerPos->x + c, centerPos->y + d, sign);
		drawline(centerPos->x + a, centerPos->y - b, centerPos->x + c, centerPos->y - d, sign);
		drawline(centerPos->x - a, centerPos->y + b, centerPos->x - c, centerPos->y + d, sign);
		drawline(centerPos->x - a, centerPos->y - b, centerPos->x - c, centerPos->y - d, sign);
	}
	
	void p4point(int x, int y, char * sign)
	{
		print(centerPos->x + x, centerPos->y + y, sign);
		print(centerPos->x + x, centerPos->y - y, sign);
		print(centerPos->x - x, centerPos->y + y, sign);
		print(centerPos->x - x, centerPos->y - y, sign);
		/*
		print(centerPos->x + y, centerPos->y + x, sign);
		print(centerPos->x - y, centerPos->y + x, sign);
		print(centerPos->x + y, centerPos->y - x, sign);
		print(centerPos->x - y, centerPos->y - x, sign);
		*/
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

int fourfive(float a)
{
	float b = (int) a + 0.5;
	return (int)(a >= b ? b + 0.5: b - 0.5);
}

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
	}
	Sleep(100);
}

int main(void)
{
	printf("%d, %d, %d, %d", fourfive(1.0), fourfive(1.3), fourfive(1.5), fourfive(1.9));
	getch();
	Circle * cir = new Circle(25, 30, 9, 12);
	cir->onDraw();
	gotoxy(0, 0);
	//printf("%d, %d, %d, %d", cir->centerPos->x, cir->centerPos->y, cir->a, cir->b);
	getch();
	return 0;
}
/**/

