# include<iostream>
# include<cstdio>
# include<windows.h>
# include<conio.h>
# include<cmath>
# include<cstdlib> 
# include<vector> 
# include<utility>
using namespace std;
class NODE;
class Point;

void drawline(Point *, Point *, char *);
void drawline(Point &, Point &, char *);
void drawline(Point , Point , char * );
void drawline(int, int, int, int, char *);
int fourfive(float);
void print(int , int , char* );
void gotoxy(int, int);

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

class Line
{
public :
	Point *fir, *sec;
	Line(Point *fir, Point *sec)
	{
		if (fir->x > sec->x)
		{
			this->fir = sec;
			this->sec = fir;
		}
		else if(fir->x < sec->x)
		{
			this->fir = fir;
			this->sec = sec;
		}
		else
		{
			if (fir->y >sec->y)
			{
				this->fir = sec;
				this->sec = fir;
			}
			else
			{
				this->fir = fir;
				this->sec = sec;
			}
		}
	}
	void onDraw(char * sign = "x")
	{
		drawline(fir, sec, sign);
	}
	void show()
	{
		printf("(%d, %d)->(%d, %d)\n", fir->x, fir->y, sec->x, sec->y);
	}
}; 

class NODE
{
public :
	Point *date;
	NODE *pre;
	NODE *next;
};


class Geom
{
private :
	class Nline
	{
	public :
		Line *date;
		Nline *next;
	};
	class NET
	{
	public :
		int xMax;//when scanner larger than yMax, quit to scanner this line
		int yMin;//when start to scanner this line, it start from xMin
		float dy;//step of y increase
		NET *next;
	};
	
	class AET
	{
	public :
		float y;//now y pos
		float dy;//step of y increase
		int xMax;//when to quit
		AET *next;
	};
	
	void insertLineByX(Line *line)
	{
		//printf("(%d, %d) -> (%d, %d)\n", line->fir->x, line->fir->y, line->sec->x, line->sec->y);
		Nline *newline = new Nline;
		newline->date = line;
		newline->next = NULL;
		Nline *q = linelist;
		Nline *p = linelist->next;
		while(p != NULL)
		{
			if (p->date->fir->x > newline->date->fir->x)
			{
				break;
			}
			else if(p->date->fir->x == newline->date->fir->x)
			{
				if (p->date->fir->y > newline->date->fir->y)
				{
					break;
				}
				else if (p->date->fir->y == newline->date->fir->y)
				{
					if(p->date->sec->x >= newline->date->sec->x)
					{
						break;
					}
				}
			}
			q = p;
			p = p->next;
		}
		newline->next = q->next;
		q->next = newline;
	}
public :
	
	NODE *list;
	Nline *linelist;
	int xmax;
	int xmin;
	Geom()
	{
		linelist = new Nline;
		linelist->date = NULL;
		linelist->next = NULL;
		xmax = xmin = -1;
		list = new NODE();
		list->next = NULL;
		list->pre = NULL;
	}
	
	void showline()
	{
		Nline *p = linelist->next;
		int i = 0;
		while (p != NULL)
		{
			printf("%d : (%d, %d) -> (%d, %d)\n", i++, p->date->fir->x, p->date->fir->y, p->date->sec->x, p->date->sec->y);
			p = p->next;
		}
	}
	
	void addNode(int x, int y)
	{
		if (xmax == -1&& xmin == -1)
		{
			xmax = xmin = x;
		}
		else
		{
			if (x > xmax)
			{
				xmax = x;
			}
			else if(x < xmin)
			{
				xmin = x;
			}
		}
		NODE *newpoint = new NODE();
		newpoint->date = new Point(x, y);
		newpoint->next = list->next;
		newpoint->pre = list;
		if (list->next)
		{
			list->next->pre = newpoint;
		}
		list->next = newpoint;
	}
	
	void createline()
	{
		linelist = new Nline;
		linelist->next = NULL;
		NODE *p = list->next;
		if (p == NULL)
		{
			return;
		}
		while (p->next != NULL)
		{
			//printf("%d, %d\n", p->date->x, p->date->y);
			insertLineByX(new Line(p->date, p->next->date));
			p = p->next;
		}
		insertLineByX(new Line(list->next->date, p->date));
	}
	
	void Border(char *sign = "x")
	{
		NODE *p;
		p = list->next;
		if (p == NULL)
		{
			printf("No point");
			return;
		}
		while (p->next != NULL)
		{
			drawline(p->date, p->next->date, sign);
			p = p->next;
		}
		drawline(p->date, list->next->date, sign);
	}
	
	void Fill(char *sign = "F")
	{
		
		createline();
		int scannum = xmax - xmin + 1;
		//cout << scannum << " scannum " << endl;
		NET *netlist = new NET[scannum];
		for (int i = 0; i < scannum; i++)
		{
			netlist[i].next = NULL;
		}
		int count = 0;
		Nline *p = linelist->next;
		while (p != NULL)
		{
			//p->date->show();
			NET *newnet = new NET;
			newnet->xMax = p->date->sec->x;
			newnet->yMin = p->date->fir->y;
			int dx = p->date->sec->x - p->date->fir->x;
			int dy = p->date->sec->y - p->date->fir->y;
			if (dx)
			{
				newnet->dy = (float)dy / dx;
			}
			else
			{
				newnet->dy = dy;
			}
			newnet->next = NULL;
			//printf("NET : %d, %d, %f\n", newnet->xMax, newnet->yMin, newnet->dy);
			int i = p->date->fir->x - xmin;
			NET *t = &netlist[i];
			if (t->next == NULL)
			{
				t->next = newnet;
			} 
			else
			{
				while (t->next != NULL)
				{
					if (t->next->yMin > newnet->yMin)
					{
						break;
					}
					else if (t->next->yMin == newnet->yMin)
					{
						if (t->next->dy > newnet->dy)
						{
							break;
						}
					}
					t = t->next;
				}
				newnet->next = t->next;
				t->next = newnet;
			}
			p = p->next;
		}
		AET *aetlist = new AET;
		aetlist->next = NULL; 
		for (int i = 0; i < scannum; i++)
		{
			//cout << i << " : " << endl;
			AET *q = aetlist;
			AET *p = aetlist->next;
			while (p != NULL)
			{
				p->y += p->dy;
				//printf("<AET: now %.2f, dy %.2f, xMax %d>\n ", p->y, p->dy, p->xMax);
				if (i + xmin > p->xMax)
				{
					q->next = p->next;
					p = p->next;
				}
				else
				{
					q = p;
					p = p->next;
				}
			}
			p = aetlist->next;
				//	getch();
			while (p != NULL&& p->next != NULL)
			{
				int sta = fourfive(p->y);
				int end = fourfive(p->next->y);
				gotoxy(50, count++);
				//printf("%d", end - sta);
				if (end < sta)
				{
					int t = end;
					end = sta;
					sta = t;
				}
				for (int j = sta; j <= end; j++)
				{
					gotoxy(0, 0);
					//printf("%d, %d\t", i + xmin, j);
					print(i+xmin, j, sign);
					//getch();
				}
				//getch();
				cout << endl;
				p = p->next->next;
			}
			
			NET *t = netlist[i].next;
			while (t != NULL)
			{
				AET * newaet = new AET;
				newaet->y = t->yMin;
				newaet->dy = t->dy;
				newaet->xMax = t->xMax;
				newaet->next = NULL;
				AET *p = aetlist;
				//printf("(%d, %d, %f) ==> \n", t->xMax, t->yMin, t->dy);
				while (p->next != NULL)
				{
					if (p->next->y >= newaet->y)
					{
						break;
					}
					p = p->next;
				}
				newaet->next = p->next;
				p->next = newaet;
				t = t->next;
			} 
			
		//	p = aetlist->next;
		//	while (p != NULL)
			{
				
				//printf("<AET: now %d, dy %.2f, xMax %d>\n ", p->y, p->dy, p->xMax);
				
		//		p = p->next;
			}
		}
		/*
		cout << "ddd" << endl;
		for (int i = 0; i < scannum; i++)
		{
			NET *t = netlist[i].next;
			cout << i << " : ";
			while (t != NULL)
			{
				printf("(%d, %d, %f) ==> ", t->xMax, t->yMin, t->dy);
				t = t->next;
			}
			cout << endl;
		}
		*/
	}
	void onDraw(char *border, char *fill)
	{
		Fill(fill);
		Border(border);
	}
};

int fourfive(float a)
{
	float b = (int)a + 0.5;
	return (int)(b + (a > b ? 0.5 : -0.5)); 
}

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
	Sleep(10);
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
		//Sleep(100);
	}
}

void drawline(Point *a, Point *b, char * sign = "0")
{
	drawline(a->x, a->y, b->x, b->y, sign);
}

void drawline(Point &a, Point &b, char * sign = "0")
{
	drawline(a.x, a.y, b.x, b.y, sign);
}

void drawline(Point a, Point b, char * sign = "0")
{
	drawline(a.x, a.y, b.x, b.y, sign);
}

int main(void)
{
	getch();
	Geom *geom1 = new Geom();
	geom1->addNode(15, 15);
	geom1->addNode(15, 30);
	geom1->addNode(30, 30);
	geom1->addNode(30, 15);
	geom1->onDraw(".", "r");
	
	Geom *geom2 = new Geom();
	geom2->addNode(15, 15);
	geom2->addNode(20, 10);
	geom2->addNode(35, 10);
	geom2->addNode(30, 15);
	geom2->onDraw(".", "g");
	
	Geom *geom3 = new Geom();
	geom3->addNode(35, 10);
	geom3->addNode(35, 25);
	geom3->addNode(30, 30);
	geom3->addNode(30, 15);
	geom3->onDraw(".", "b");
	gotoxy(0, 0);
	
	getch();
	return 0;
}
/*
	geom->addNode(0, 0);
	geom->addNode(6, 0);
	geom->addNode(15, 5);
	geom->addNode(7, 10);
	geom->addNode(5, 6);
	
	geom->addNode(0, 0);
	geom->addNode(15, 10);
	geom->addNode(15, 15);
	geom->addNode(0, 10);
	geom->addNode(6, 6);
*/
