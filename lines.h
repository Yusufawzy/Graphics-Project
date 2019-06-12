#include "math.h"
#include "point.h"
#include <iostream>
using namespace std;


void drawLineParametric(HDC hdc, Point p1,Point p2, COLORREF rgb)
{
    Point p;
    double t = 0;
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int x, y;
    // double dt = 1/(max(dx,dy)+1);
    for (; t <= 1; t += 0.001)
    {
        x = roundd(p1.x + t * dx);
        y = roundd(p1.y + t * dy);
        SetPixel(hdc, x, y, rgb);
    }
}
void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
void drawLineNaiive(HDC hdc,  Point p1,Point p2,COLORREF rgb)
{
    int dy = p2.y - p1.y;
    int dx = p2.x - p1.x;
    int x;
    int y;
    if (abs(dx) > abs(dy))
    {
        if (p1.x > p2.x)
        {
            swap(p1.x, p2.x);
            swap(p1.y, p2.y);
        }
        double m = (double)dy / dx;
        for (int x = p1.x; x <= p2.x; x++)
        {
            y = roundd(p1.y + (x - p1.x) * m);
            SetPixel(hdc, x, y, rgb);
        }
    }
    else

    {
        if (p1.y > p2.y)
        {
            swap(p1.x, p2.x);
            swap(p1.y, p2.y);
        }
        double im = (double)dx / dy;
        for (int y = p1.y; y <= p2.y; y++)
        {
            x = roundd(p1.x + (y - p1.y) * im);
            SetPixel(hdc, x, y, rgb);
        }
    }
}
void drawLineSimpleDDA(HDC hdc, Point p1,Point p2,COLORREF rgb)
{
    int dy = p2.y - p1.y;
    int dx = p2.x - p1.x;

    if (abs(dx) > abs(dy))
    {
        int xinc = dx > 0 ? 1 : -1;
        double y = p1.y;
        double yinc = (double)dy / dx * xinc;
        for (int x = p1.x; x != p2.x; x += xinc)
        {
            SetPixel(hdc, x, roundd(y), rgb);
            y += yinc;
        }
    }
    else
    {
        int yinc = dy > 0 ? 1 : -1;
        double x = p1.x;
        double xinc = (double)dx / dy * yinc;
        for (int y = p1.y; y != p2.y; y += yinc)
        {
            x += xinc;
            SetPixel(hdc, roundd(x), y, rgb);
        }
    }
}
void drawLineIntDDAFinal(HDC hdc, Point p1,Point p2, COLORREF rgb)
{
    int dy = p2.y - p1.y;
    int dx = p2.x - p1.x;
    int x;
    int y;
    double m = (double)dy / dx;
///    double im = (double)dx / dy;
    dy = abs(dy);
    dx = abs(dx);
    int e;
    if (dx > dy)
    {
        if (p1.x > p2.x)
        {
            swap(p1.x, p2.x);
            swap(p1.y, p2.y);
        }
        x = p1.x;
        y = p1.y;
        SetPixel(hdc, x, y, rgb);
        if (m >= 0 && m <= 1)
        {
            cout << "First condition" << endl;
            e = 2 * dy - dx; //multiply by 2 dx
            while (x != p2.x)
            {
                x++;
                if (e >= 0)
                {
                    y++;
                    e -= (2 * dx);
                }
                e += (2 * dy);
                SetPixel(hdc, x, y, rgb);
            }
        }
        else if (m <= 0 && -1 <= m)
        {
            cout << "Fourth condition" << endl;

            e = 2 * dy - dx;
            while (x != p2.x)
            {
                x++;
                if (e <= 0)
                {
                    y--;
                    e += 2 * dx;
                }
                e -= 2 * dy;

                SetPixel(hdc, x, y, rgb);
            }
        }
    }
    //34an 5las fe el rasm mn al 2awl ab2a sha8al kda al p1.x hya ally so8yra w madam slope is +ve ubyba al y++
    else
    {
        if (p1.y > p2.y)
        {
            swap(p1.x, p2.x);
            swap(p1.y, p2.y);
        }
        x = p1.x;
        y = p1.y;
        SetPixel(hdc, x, y, rgb);
        if (m > 1)
        {
            cout << "Second condition" << endl;
            e = 2 * dx - dy;
            while (y != p2.y)
            {
                y++;
                if (e >= 0)
                {
                    x++;
                    e -= 2 * dy;
                }
                e += 2 * dx;

                SetPixel(hdc, x, y, rgb);
            }
        }
        else if (m <= -1)
        {
            cout << "Third condition" << endl;
            x = p1.x;
            y = p1.y;
            e = 2 * dx - dy;
            while (y != p2.y)
            {
                y++;
                if (e <= 0)
                {
                    x--;
                    e += 2 * dy;
                }
                e -= 2 * dx;

                SetPixel(hdc, x, y, rgb);
            }
        }
    }
}

void drawLineMidPoint(HDC hdc, Point p1,Point p2,COLORREF rgb)
{
    int dx = p2.x - p1.x ;
    int dy = p2.y - p1.y ;
    int x,y ;
    double m = (double) dy / dx;

    if (abs(dx)>abs(dy))
    {
        if (p1.x>p2.x)
        {
            swap(p1.x,p2.x);
            swap(p1.y,p2.y);
            dx*=-1;
            dy*=-1;
        }
        x=p1.x;
        y=p1.y;
        if (m>=0 && m<=1)
        {
            cout<<"first condition"<<endl;
            int d = dx  -2 * dy;
            int d1 = 2 *(dx - dy);
            int d2 = -2 * dy;
            SetPixel(hdc,x,y, rgb);
            while(x!=p2.x)
            {
                x++;
                if(d<0)
                {
                    d+=d1;
                    y++;
                }
                else
                    d+=d2;
                SetPixel(hdc,x,y, rgb);
            }
        }
        else if (-1 <= m&&m<=0  )
        {
            cout<<"Fourth Condition"<<endl;
            int d =-1* dx -2 * dy;;
            int d1 =-2 * dx - 2 * dy;
            int d2 = -2 * dy;
            while(x!=p2.x)
            {
                x++;
                if (d>0)
                {
                    y--;
                    d+=d1 ;
                }
                else d+=d2;
                SetPixel(hdc,x,y, rgb);
            }
        }
    }
    else
    {
        if (p1.y>p2.y)
        {
            swap(p1.x,p2.x);
            swap(p1.y,p2.y);
            dx*=-1;
            dy*=-1;
        }
        x=p1.x;
        y=p1.y;
        if (m>1)
        {
            cout<<"Second Condition"<<endl;
            int d = 2*dx - dy ;
            int d1 = 2*(dx - dy );
            int d2 = 2 * dx;
            while(y!=p2.y)
            {
                y++;
                if (d>0)
                {
                    d+=d1;
                    x++;
                }
                else
                {
                    d+=d2;
                }
                SetPixel(hdc,x,y, rgb);
            }
        }
        else if (m<=-1)
        {
            cout<<"Third Condition"<<endl;
            int d = 2*dx + dy;
            int d1 =2 *(dx + dy);
            int d2 = 2 *dx;
            SetPixel(hdc,x,y, rgb);
            cout<<"X initial is "<<x<<endl;
            while(y!=p2.y)
            {
                y++;
                if (d<0)
                {
                    d+=d1;
                    x--;
                }
                else d+=d2;
                SetPixel(hdc,x,y, rgb);
            }
        }
    }
}

void drawLineMidPoint(HDC hdc,int x1,int y1,int x2,int y2,COLORREF rgb)
{
    Point p1,p2;
    p1.x = x1,p2.x=x2,p1.y=y1,p2.y=y2;
    drawLineMidPoint(hdc,p1,p2,rgb);
}
