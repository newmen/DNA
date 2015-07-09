#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <math.h>

class DNK
{
 private:
  int nums;
  int x0,y0;
  int r,rx,ry;
  float k;
  float beta;

  unsigned char bColor,tColor,lColor;

 public:
  DNK(int x,int y,int r,int rT,int nums,float k,float alfa,float beta);
  void SetColors(unsigned char bColor,unsigned char tColor,unsigned char lColor);
  void Build(float step) const;
  void Rotate() const;

  void Squire(int side,int r) const;
};

DNK::DNK(int x,int y,int r,int rT,int nums,float k,float alfa=0,float beta=0)
{
  this->x0 = x;
  this->y0 = y;
  this->r = r;
  this->rx = rT;
  this->ry = rT*sin(alfa);
  this->nums = nums;
  this->k = k;
  this->beta = beta;

  bColor = 2;
  tColor = 10;
  lColor = 8;

//  Build();
}

void DNK::SetColors(unsigned char bColor,unsigned char tColor,unsigned char lColor)
{
  this->bColor = bColor;
  this->tColor = tColor;
  this->lColor = lColor;
}

void DNK::Build(float step) const
{
  int i;
  int x,y;
  int x1,y1,x2,y2;

  x = x0-sin(beta)*k*nums*r/2;
  y = y0+cos(beta)*k*nums*r/2;

  for(i=0;i<nums;i++)
  {
    x1 = x+rx*cos(step)*cos(beta)+ry*sin(step)*sin(beta);
    y1 = y+ry*sin(step)*cos(beta)+rx*cos(step)*sin(beta);

    x2 = x+rx*cos(step+M_PI)*cos(beta)+ry*sin(step+M_PI)*sin(beta);
    y2 = y+ry*sin(step+M_PI)*cos(beta)+rx*cos(step+M_PI)*sin(beta);

    if(sin(step+M_PI) > sin(step))
    {
      setcolor(bColor);
      circle(x2,y2,r*(1+18*sin(step+M_PI)/rx));

      setcolor(lColor);
      line(x1,y1,x2,y2);
      putpixel(x,y,0);

      setcolor(tColor);
      circle(x1,y1,r*(1+18*sin(step)/rx));
    }
    else
    {
      setcolor(bColor);
      circle(x1,y1,r*(1+18*sin(step)/rx));

      setcolor(lColor);
      line(x1,y1,x2,y2);
      putpixel(x,y,0);

      setcolor(tColor);
      circle(x2,y2,r*(1+18*sin(step+M_PI)/rx));
    }


//    line(x0+cos(step)*rx*0.888,y+sin(step)*ry*0.888/5,x0+cos(step+M_PI)*rx*0.888,y2+sin(step+M_PI)*ry*0.888/5);
//    setcolor(15);
//    circle(x0,y0,5);
//    ellipse(x,y,0,360,rx,ry);

    step += 2.2*M_PI/rx;

    x += k*r*sin(beta);
    y -= k*r*cos(beta);

//    delay(20);
  }
}

void DNK::Rotate() const
{
  float i = 0;

  while(!kbhit())
  {
    Build(i);

    i += 2*M_PI/rx;

    delay(30);
    cleardevice();
  }
}

void DNK::Squire(int side,int rr=0) const
{
  int x,y;
  int mside;

  x = x0+sin(beta)*rr;
  y = y0-cos(beta)*rr;

  mside = side/2;

  setcolor(15);

//  line(x,0,x,getmaxy());
//  line(0,y,getmaxx(),y);
//  line(x0,y0,x,y);

  line(x-mside,y-mside,x-mside,y+mside);
  line(x-mside,y+mside,x+mside,y+mside);
  line(x+mside,y+mside,x+mside,y-mside);
  line(x+mside,y-mside,x-mside,y-mside);
}


void ppp(int);

int main()
{
  int gdriver = DETECT;
  int gmode;
  int errorcode;

  int x,y;

  initgraph(&gdriver,&gmode,"D:\\TC30\\BGI\\");
  errorcode = graphresult();

  if(errorcode != grOk)
  {
    cprintf("Error: %d",errorcode);
    getch();
    return 0;
  }

  x = getmaxx()/2;
  y = getmaxy()/2;

  DNK part(x-10,y-20,13,72,14,2,M_PI/4,M_PI/5);
  part.SetColors(4,12,9);

  DNK global1(x+280,y-20,2,16,51,4,M_PI/10);
  DNK global2(x-30,y+220,2,16,69,4,M_PI/10,-M_PI/2);
//  DNK small(x+282,y+219,12,3,2,4,4,M_PI/5);

//  DNK my2(x,y,16,4,2,50,4,M_PI/4);
//  DNK my3(x,y,88,22,11,18,1.333,M_PI/5);

//  my3.Build(0);
//  getch();

//  my3.Rotate();

  float i = 0;

  while(!kbhit())
  {
    part.Build(0.9*i);
    global1.Build(0.6*i);
    global2.Build(0.6*i);
//    small.Build(0.9*i);

//    part.Squire(400);
//    global1.Squire(60,-50);
//    global.Squire();

    i += 2*M_PI/54;

    delay(25);
    cleardevice();
  }

//  getch();
  closegraph();

//  ppp(25);
//  ppp(26);
//  getch();
  return 0;
}

void ppp(int i)
{
  double k=M_PI/i;
  cprintf("%d, %2.17e\r\nsin = %2.17e\r\ncos = %2.17e\r\n",i,k,sin(k),cos(k));
}