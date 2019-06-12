#include "math.h"
#include <iostream>
#include "Point.h"
using namespace std;
/*  This function is called by the Windows function DispatchMessage()  */
void draw8Pixels(HDC hdc, int xc,int yc,int x, int y, COLORREF rgb)
{
    SetPixel(hdc, (x)+xc, y+yc, rgb);
    SetPixel(hdc, (x)+xc, -y+yc, rgb);
    SetPixel(hdc, (-y)+xc, x+yc, rgb);
    SetPixel(hdc, (-y)+xc, -x+yc, rgb);
    SetPixel(hdc, (-x)+xc, -y+yc, rgb);
    SetPixel(hdc, (-x)+xc, y+yc, rgb);
    SetPixel(hdc, (y)+xc, -x+yc, rgb);
    SetPixel(hdc, (y)+xc, x+yc, rgb);
}
int Round(double x)
{
    return (int)(x + 0.5);
}

void drawCircleDirect(HDC hdc,Point pc,Point p2, COLORREF rgb)
{
    int r = max(abs(p2.x - pc.x),abs(p2.y-pc.y));
    int x  =r;
    int y = 0 ;
    int R2=r*r;
    draw8Pixels(hdc,pc.x,pc.y,x,y,rgb);
    while(x>y)
    {
        y++;
        x=Round(sqrt((double)(R2-y*y)));
        draw8Pixels(hdc,pc.x,pc.y,x,y,rgb);
        // cout<<"y is "<<y<<" x "<<x<<endl;
    }
}
void drawCircleNotIterative(HDC hdc,Point pc,Point p2, COLORREF rgb)
{
    int r = max(abs(p2.x - pc.x),abs(p2.y-pc.y));
    cout<<"not iterative"<<endl;
    double theta = 0;
    int x;
    int y;
    // double dtheta = (double) 1/r;
    double dtheta = 0.001;
    ///version without using 8pixels
    while(theta <2*3.14)
    {
        x = pc.x+round(r  * cos(theta));
        y = pc.y+round(r  * sin(theta));
        theta+=dtheta;
        SetPixel(hdc, (x), y, rgb);
    }
}

void drawCircleNotIterative8(HDC hdc,Point pc,Point p2, COLORREF rgb)
{
    int r = max(abs(p2.x - pc.x),abs(p2.y-pc.y));
    double theta = 0;
    int x=r;
    int y=0;

    // double dtheta = (double) 1/r;
    ///version using 8pixels
    double dtheta =(double) 1/10000;
    while(x>y)
    {
        x = round(r  * cos(theta));
        y = round(r  * sin(theta));
        theta+=dtheta;;
        draw8Pixels( hdc,  pc.x, pc.y, x,  y,  rgb);
    }
}

void drawCircleIterative(HDC hdc, Point pc,Point p2,COLORREF rgb)
{
    int r = max(abs(p2.x - pc.x),abs(p2.y-pc.y));
    double x =r, y=0;
    double dtheta = 1.0/r;
    double cd = cos(dtheta),sd = sin(dtheta);
    draw8Pixels(hdc,pc.x,pc.y,r,0,rgb);

    while(x>y)
    {
        double x1 =(x * cd - y * sd);
        y = (x * sd + y * cd );
        x =x1;;
        draw8Pixels(hdc,pc.x,pc.y,round(x),round(y),rgb);
    }
}
void drawCircleMidPoint1(HDC hdc, Point pc,Point p2, COLORREF rgb)
{
    int r = max(abs(p2.x - pc.x),abs(p2.y-pc.y));
    int d = 1 - r ;
    int x = 0 ;
    int y =  r;
    draw8Pixels(hdc,pc.x,pc.y,0,r,rgb);
    while(x<y)
    {
        if (d>0)
        {
            y--;
            d+=2*(x - y ) + 5;
        }
        else
        {
            d+= 2 * x + 3;
        }
        x++;
        draw8Pixels(hdc,pc.x,pc.y,x,y,rgb);

    }

}



void drawCircleMidPoint2(HDC hdc, Point pc,Point p2, COLORREF rgb)
{
    int r = max(abs(p2.x - pc.x),abs(p2.y-pc.y));
    int x = 0, y = r ;
    int d = 1 -r;
    int c1 = -2 * r + 5, c2 = 3;
    draw8Pixels(hdc,pc.x,pc.y,0,r,rgb);
    while(x<y)
    {
        if (d>0)
        {
            y--;
            d+=c1;
            c1+=4;
        }
        else
        {
            d+=c2;
            c1+=2;
        }
        x++;
        c2+=2;
        draw8Pixels(hdc,pc.x,pc.y,x,y,rgb);
    }
}
