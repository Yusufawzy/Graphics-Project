#include <vector>
#include "Rec.h"

#include <tchar.h>
#include <windows.h>
void drawRectangle(HDC hdc,Rec r,COLORREF rgb)
{
    drawLineMidPoint( hdc,r.xLeft,r.yTop,r.xRight,r.yTop,rgb);
    drawLineMidPoint( hdc,r.xLeft,r.yBottom,r.xRight,r.yBottom,rgb);
    drawLineMidPoint( hdc,r.xRight,r.yTop,r.xRight,r.yBottom,rgb);
    drawLineMidPoint( hdc,r.xLeft,r.yBottom,r.xLeft,r.yTop,rgb);
}

union OutCode
{
    unsigned All:4;
    struct
    {
        unsigned left:1,right : 1,top:1,bottom :1;
    };
};
OutCode getOutCode(double x,double y,Rec r)
{
    OutCode out ;
    out.All = 0;
    if (x<r.xLeft)out.left = 1;
    else if (x>r.xRight)out.right = 1;
    if (y<r.yTop) out.top = 1;
    else if (y>r.yBottom)out.bottom=1;
    return out;
}
void vIntersect(double x1,double y1,double x2,double y2,int xEdge,double &xIntersect,double &yIntersect)
{
    xIntersect = xEdge;
    yIntersect= y1 +((y2-y1)*(xEdge-x1))/(x2-x1);
}
void hIntersect(double x1,double y1,double x2,double y2,int yEdge,double &xIntersect,double &yIntersect)
{
    yIntersect = yEdge;
    xIntersect=x1 +((x2-x1)*(yEdge-y1))/(y2-y1);
}


void cohenSthurland(HDC hdc,int xs,int ys,int xe,int ye,Rec r )
{
    drawLineMidPoint( hdc,xs,ys,xe,ye,RGB(200,200,200));
    double x1=xs,y1 = ys,y2 = ye,x2=xe;
///Start by getting the intersection to see if outside or hetta hetta
    OutCode out1 = getOutCode(x1,y1,r);
    OutCode out2 = getOutCode(x2,y2,r);
///First cond talma huma altneen msh fe nfs al ganeb
///Second cond talam fe wa7da mnhum lsa out == 1 y2ba lazm no2ssaha
    while (!(out1.All & out2.All) && (out1.All || out2.All))
    {

        double xIntersect,yIntersect ; //temp variables
        if (out1.All!=0)
        {
            if (out1.left) vIntersect(x1,y1,x2,y2,r.xLeft,xIntersect,yIntersect);
            else if (out1.top) hIntersect(x1,y1,x2,y2,r.yTop,xIntersect,yIntersect);
            else if (out1.right) vIntersect(x1,y1,x2,y2,r.xRight,xIntersect,yIntersect);
            else hIntersect(x1,y1,x2,y2,r.yBottom,xIntersect,yIntersect);

            x1  = xIntersect,y1 = yIntersect;
            out1 = getOutCode(x1,y1,r);///The new outcode after ma 5alas 2att3na al start point
        }
        else   ///Don't enter the both in same time,kol loop just justtt han5o4 fe one condition and all others are just elses
        {
            if (out2.left) vIntersect(x1,y1,x2,y2,r.xLeft,xIntersect,yIntersect);
            else if (out2.top) hIntersect(x1,y1,x2,y2,r.yTop,xIntersect,yIntersect);
            else if (out2.right) vIntersect(x1,y1,x2,y2,r.xRight,xIntersect,yIntersect);
            else hIntersect(x1,y1,x2,y2,r.yBottom,xIntersect,yIntersect);

            x2  = xIntersect,y2 = yIntersect;
            out2 = getOutCode(x2,y2,r);///The new outcode after ma 5alas 2att3na al start point
        }

    }
    if (!out1.All && !out2.All)
    {
        cout<<"heyyyyyyyyyyyyyyyyyyyyyy"<<endl;
        ///If both are zeros then keda 5las the whole inside you can draw the line yalla b2a
        drawLineMidPoint( hdc,roundd(x1),roundd(y1),roundd(x2),roundd(y2),RGB(0,0,0));

    }
}
bool checkIn(Point p1,int edge,int type)
{
///type = 1 -> left , 2->top , 3-> right , 4-> bottom
    if (type==1)
    {
        return p1.x >= edge ;
    }

    else if (type == 2)
    {
        return p1.y >=edge;
    }
    else if (type ==3)
    {

        return p1.x <=edge;
    }
    else if (type ==4)
    {
        return p1.y <=edge;
    }
    return false;
}
vector<Point> ClipWithEdge(vector<Point> PVertices,int edge,int type)
{
    ///Type will tell me if I am clipping edge left,right,top or bottom
    vector <Point> res;
    int n = PVertices.size();
    Point p1 = PVertices[n-1],p2,pIntersect;
    double xIntersect,yIntersect;
    bool check1 = checkIn(p1,edge,type);
    for(int i = 0 ; i < n; i++)
    {
        p2 = PVertices[i];
        bool check2 = checkIn(p2,edge,type);
        if (check1 && check2)
        {
            ///Intersection will be also done based on the given type H or V
            res.push_back(p2);
        }
        else if (check1 && !check2)
        {
            /// add the intersection madam mahy msh mwgoda
            if (type ==1 || type == 3)
            {
                vIntersect(p1.x,p1.y,p2.x,p2.y,edge,xIntersect,yIntersect);
            }
            else if (type == 2 || type == 4)
            {
                hIntersect(p1.x,p1.y,p2.x,p2.y,edge,xIntersect,yIntersect);

            }
            pIntersect.x = xIntersect,pIntersect.y = yIntersect;
            res.push_back(pIntersect);
        }
        else if (!check1 && check2)
        {
            if (type ==1 || type == 3)
            {
                vIntersect(p1.x,p1.y,p2.x,p2.y,edge,xIntersect,yIntersect);
            }
            else if (type == 2 || type == 4)
            {
                hIntersect(p1.x,p1.y,p2.x,p2.y,edge,xIntersect,yIntersect);

            }
            pIntersect.x = xIntersect,pIntersect.y = yIntersect;
            res.push_back(pIntersect);
            res.push_back(p2);
        }
        p1 =p2;
        check1 = check2;
    }
    return res;
}
///type = 1 -> left , 2->top , 3-> right , 4-> bottom
void sutherlandHodgman(HDC hdc,vector <Point> points,Rec r)
{
    vector <Point> saved = points;
    ///Start by drawing the Full Polygon
    Point p1 = points[points.size()-1],p2,p3,p4;
    for(int i = 0; i<points.size(); i++)
    {
        p2 = points[i];
        drawLineMidPoint( hdc,p1,p2,RGB(0,0,0));
        p1 = p2;
    }

    points =  ClipWithEdge(points,r.xLeft,1);
    points =  ClipWithEdge(points,r.yTop,2);
    points =  ClipWithEdge(points,r.xRight,3);
    points =  ClipWithEdge(points,r.yBottom,4);

    Sleep(1000);
    cout<<"Start Clipping"<<endl;
    p1 = saved[saved.size()-1];
    for(int i = 0; i<saved.size(); i++)
    {

        p2 = saved[i];
        drawLineMidPoint( hdc,p1,p2,RGB(200,200,200));
        p1 = p2;
    }


    p1 = points[points.size()-1];
    for(int i = 0; i<points.size(); i++)
    {
        Sleep(1000);
        p2 = points[i];
        drawLineMidPoint( hdc,p1,p2,RGB(0,0,0));
        p1 = p2;
    }
}

/*
 else if (clipping)
        {
            HDC hdc = GetDC(hwnd);
            if(n==-1)
            {
                n=7;
                cnt=0;
                arrX = new int[n+1];
                arrY = new int[n+1];
                ///These arrays to put results of the polygon into it
            }

            if(cnt!=n)
            {
                ///take points from the user till the count is n

                if(cnt==0)
                {

                    rec.xLeft = LOWORD(lParam);
                    rec.yBottom = HIWORD(lParam);

                    cout<<"xRight,yTop\n";
                }
                else if(cnt==1)
                {

                    rec.xRight = LOWORD(lParam);
                    rec.yTop = HIWORD(lParam);
                    drawRectangle(hdc,rec,rgb);

                }
                else if(cnt==2)
                {
                    x1 = LOWORD(lParam);
                    y1 = HIWORD(lParam);
                    cout<<y1<<" "<<x1<<endl;
                }
                else if(cnt==3)
                {
                    x2 = LOWORD(lParam);
                    y2 = HIWORD(lParam);
                    drawLineMidPoint( hdc,x1,y1,x2,y2,rgb);
                    cout<<y2<<" "<<x2<<endl;
                }

                cnt++;
                if(cnt>1) cout<<cnt-1<<endl;

            }
            if (cnt==n)

            {
                arrX[n] = 0;
                arrY[n] =0;


                cout<<"ALL POINTS HAVE BEEN TAKEN"<<endl;
                cohenSthurland(hdc,x1,y1,x2,y2,rec);
                cnt=0;
                n=-1;

            }
            ReleaseDC(hwnd,hdc);

        }*/


