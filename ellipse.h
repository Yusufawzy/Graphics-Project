#include "math.h"
#include <iostream>
#include "Point.h"
using namespace std;
void swap(int& xs, int& ys, int& xe, int& ye)
{
    int temp = xs;
    xs = xe;
    xe = temp;
    temp = ys;
    ys = ye;
    ye = temp;
}
int roundd(double num)
{
    return (int)(num + 0.5);
}
/*  This function is called by the Windows function DispatchMessage()  */
void draw4Pixels(HDC hdc, int xc, int yc, int x, int y, COLORREF color)
{
    SetPixel(hdc, xc + x, yc + y, color);
    SetPixel(hdc, xc + x, yc - y, color);
    SetPixel(hdc, xc - x, yc - y, color);
    SetPixel(hdc, xc - x, yc + y, color);
}
void drawEllipseDirect(HDC hdc, Point pc, Point p2,Point p3, COLORREF rgb)
{
    int  a = abs(pc.x-p2.x);
    int   b = abs(pc.y-p3.y);

    double x = a ;
    double y = 0 ;
    double a2 = a*a;
    double b2 = b*b;
    draw4Pixels(hdc,pc.x,pc.y,a,0,rgb);

    while((b2*x)>(a2*y))

    {
        y++;
        x = sqrt((double)(a2* ( 1-((y*y)/(b2))  )));
        draw4Pixels(hdc,pc.x,pc.y,roundd(x),roundd(y),rgb);
    }
    x = 0 ;
    y = b ;
    while((b2*x)<(a2*y))
    {
        x++;
        y = sqrt((double)(b2* ( 1-((x*x)/(a2))  )));
        draw4Pixels(hdc,pc.x,pc.y,roundd(x),roundd(y),rgb);
    }

}
void drawEllipsePolar(HDC hdc, Point pc, Point p2,Point p3,  COLORREF rgb)
{
    int  a = abs(pc.x-p2.x);
    int   b = abs(pc.y-p3.y);

    double x = a ;
    double y = 0 ;
    double theta = 0 ;
    double dtheta = 0.0001;
    while(theta<=1.57)
    {
        x = a * cos (theta);
        y = b * sin (theta);
        theta+=dtheta;
        draw4Pixels(hdc,pc.x,pc.y,roundd(x),roundd(y),rgb);
    }
}
void drawEllipsePolarIterative(HDC hdc, Point pc, Point p2,Point p3,  COLORREF rgb)
{
    int  a = abs(pc.x-p2.x);
    int   b = abs(pc.y-p3.y);

    double x = a ;
    double y = 0 ;
    double dtheta = 0.0001;
    double cd = cos(dtheta),sd=sin(dtheta);
    draw4Pixels(hdc,pc.x,pc.y,roundd(x),roundd(y),rgb);
    while( x>=0 )
    {
        double x1 = x *cd - (a* y *sd)/ b ;
        y = y * cd + (b*x*sd)/a;
        x = x1;
        draw4Pixels(hdc,pc.x,pc.y,roundd(x),roundd(y),rgb);
    }
}

void drawEllipseMidPoint(HDC hdc,Point pc, Point p2,Point p3,COLORREF rgb)
{
    int  a = abs(pc.x-p2.x);
    int  b = abs(pc.y-p3.y);


    double y = b, x = 0,a2 = a*a,b2 = b*b ;
    int d = b2 - a2 * b + 0.25 * a2;
    draw4Pixels(hdc,pc.x,pc.y,roundd(x),roundd(y),rgb);
    while(b2*x<=a2*y)
    {
        x++;
        if (d>0)
        {
            y--;
            d+= b2* (2*x+3) + a2* (-2* y + 2 );
        }
        else
        {
            d+= b2* (2*x+3);
        }
        draw4Pixels(hdc,pc.x,pc.y,roundd(x),roundd(y),rgb);
    }
    d = (x+0.5) * (x+0.5) * b2 + a2 * (y - 1)*(y-1) - a2 * b2;
    draw4Pixels(hdc,pc.x,pc.y,roundd(x),roundd(y),rgb);
    while(y!=0)
    {
        y--;
        if (d>0)
        {
            d+=a2 * (-2*y+3);
        }
        else
        {
            x++;
            d += b2 *(2*x+2) + a2 * (-2*y+3);
        }
        draw4Pixels(hdc,pc.x,pc.y,roundd(x),roundd(y),rgb);
    }
}
