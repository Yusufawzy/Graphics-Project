#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include "menuh.h"
#include "circles.h"
#include "ellipse.h"
#include "lines.h"
#include "curves.h"
#include "fstream"
#include "clipping.h"
#include "Rec.h"
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);



int id;

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");
int WINAPI WinMain (HINSTANCE hThisInstance,HINSTANCE hPrevInstance,LPSTR lpszArgument,int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = MAKEINTRESOURCE(ID);                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               _T("Code::Blocks Template Windows App"),       /* Title Text */
               WS_OVERLAPPEDWINDOW, /* default window */
               CW_USEDEFAULT,       /* Windows decides the position */
               CW_USEDEFAULT,       /* where the window ends up on the screen */
               600,                 /* The programs width */
               600,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

class Drawing
{
public:
    string name;
    vector<Point> points;
};
vector <Drawing> drawings;
int x1,y1,x2,n=-1,cnt = 0;
Point p1,p2,p3,p4,p5;
Rec rec;
COLORREF rgb = RGB(0,0,0);


bool lparam=false,lnaiive=false,lsimple=false,lInt=false,lmidpoint=false;
bool cdirect  = false, cparam8 = false,cparamIterative=false,cparam=false,cmidpoint1=false,cmidpoint2=false;
bool eldirect=false,elpolarno = false,elpolaryes=false,elmidpoint=false;
bool cuquadratic = false,cuquadraticbezier=false,cuhermite=false,cubezier1=false,cubezier2=false,cusplines=false;
bool clipping = false,save = false, load = false, exitt = false;
vector <Point> points;
int *arrX,*arrY;
void saveToFile()
{
    ofstream ff;
    ff.open ("drawings.txt");
    int sizee = drawings.size();
    for(int i = 0; i < sizee; i++)
    {
        cout<<"Action name: "<<drawings[i].name<<endl;
        ff << drawings[i].name;
        ff << " ";
        ff << drawings[i].points.size();
        ff << " ";
        for(int j=0; j< drawings[i].points.size(); j++)
        {
            cout<<"Point "<<j+1<<": ("<<drawings[i].points[j].x<<","<<drawings[i].points[j].y<<") "<<endl;
            ff << drawings[i].points[j].x<<" "<< drawings[i].points[j].y<< " ";
        }
    }
    ff.close();


}
void drawAny(Drawing d, HWND hwnd)
{
    HDC hdc = GetDC(hwnd);
    cout<<"Action >> "<<d.name<<endl;
    if (d.name =="drawLineIntDDAFinal" )drawLineIntDDAFinal(hdc,d.points[0],d.points[1],rgb);
    else if (d.name =="drawLineParametric" )drawLineParametric(hdc,d.points[0],d.points[1],rgb);
    else if (d.name =="drawLineParametric" )drawLineParametric(hdc,d.points[0],d.points[1],rgb);
    else if (d.name =="drawLineNaiive" )drawLineNaiive(hdc,d.points[0],d.points[1],rgb);
    else if (d.name =="drawLineSimpleDDA" )drawLineSimpleDDA(hdc,d.points[0],d.points[1],rgb);
    else if (d.name =="drawLineMidPoint" )drawLineMidPoint(hdc,d.points[0],d.points[1],rgb);
    else if (d.name =="drawCircleDirect" )drawCircleDirect(hdc,d.points[0],d.points[1],rgb);
    else if (d.name =="drawCircleNotIterative" )drawCircleNotIterative(hdc,d.points[0],d.points[1],rgb);
    else if (d.name =="drawCircleNotIterative8" )drawCircleNotIterative8(hdc,d.points[0],d.points[1],rgb);
    else if (d.name =="drawCircleIterative" )drawCircleIterative(hdc,d.points[0],d.points[1],rgb);
    else if (d.name =="drawCircleMidPoint1" )drawCircleMidPoint1(hdc,d.points[0],d.points[1],rgb);
    else if (d.name =="drawCircleMidPoint2" )drawCircleMidPoint2(hdc,d.points[0],d.points[1],rgb);
    else if (d.name =="drawEllipseDirect" )drawEllipseDirect(hdc,d.points[0],d.points[1],d.points[2],rgb);
    else if (d.name =="drawEllipsePolar" )drawEllipsePolar(hdc,d.points[0],d.points[1],d.points[2],rgb);
    else if (d.name =="drawEllipsePolarIterative" )drawEllipsePolarIterative(hdc,d.points[0],d.points[1],d.points[2],rgb);
    else if (d.name =="drawEllipseMidPoint" )drawEllipseMidPoint(hdc,d.points[0],d.points[1],d.points[2],rgb);
    else if (d.name =="drawQuadraticCurve" )drawQuadraticCurve(hdc,d.points[0],d.points[1],d.points[2],rgb);
    else if (d.name =="drawBezierQuadraticCurve" )drawBezierQuadraticCurve(hdc,d.points[0],d.points[1],d.points[2],rgb);
    else if (d.name =="drawCubicHermite" )drawCubicHermite(hdc,d.points[0],d.points[1],d.points[2],d.points[3],rgb);
    else if (d.name =="drawCubicBezier1" )drawCubicBezier1(hdc,d.points[0],d.points[1],d.points[2],d.points[3],rgb);
    else if (d.name =="drawCubicBezier2" )drawCubicBezier2(hdc,d.points[0],d.points[1],d.points[2],d.points[3],rgb);
    else if (d.name =="drawSplines" )drawSplines(hdc,d.points,7,0.5,rgb);

///just na2es al splines and the clippings



    ReleaseDC(hwnd,hdc);
}
void loadFromFile(HWND hwnd)
{
    int sizee;
    ifstream fin("drawings.txt");
    vector<Drawing> drawings;
    if ( !fin.is_open())
    {
        cout << "Doens't Exist"<<endl;
    }
    else
    {
        while(!fin.eof())
        {
            Drawing d;
            int sz;
            fin >> d.name;
            if(fin.eof())
                break;
            fin >> sizee;
            for(int i=0; i<sizee; i++)
            {
                Point point;
                fin >> point.x;
                fin >> point.y;
                d.points.push_back(point);
            }
            drawings.push_back(d);
        }
        fin.close();

        for(int i=0; i<drawings.size(); i++)
            drawAny(drawings[i],hwnd);
    }
}

void add(string name,vector<Point> points)
{
    Drawing d ;
    d.name = name;
    d.points  = points;
    drawings.push_back(d);
    cout<<"ahu 3mlna add ahu To "<<d.name<<endl;
}
void setAll()
{
    lparam=false,lnaiive=false,lsimple=false,lInt=false,lmidpoint=false;
    cdirect  = false,  cparam8 = false,cparamIterative=false,cparam=false,cmidpoint1=false,cmidpoint2=false;
    eldirect=false,elpolarno = false,elpolaryes=false,elmidpoint=false;
    cuquadratic = false,cuquadraticbezier=false,cuhermite=false,cubezier1=false,cubezier2=false,cusplines=false;
    clipping = false,save = false, load = false, exitt = false;
    points.clear();
}
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
    case WM_COMMAND:
        id = LOWORD(wParam);
        switch (id)
        {
        case MY_SAVE :
            setAll();
            save=true;
            break;
        case MY_LOAD:
            setAll();
            load = true;
            break;
        case MY_EXIT:
            exit(0);
            break;
        case MY_LINE_INT_DDA:
            setAll();
            lInt = true;
            break;
        case MY_LINE_MIDPOINT:
            setAll();
            lmidpoint=true;
            break;
        case MY_LINE_NAIIVE:
            setAll();
            lnaiive = true;
            break;
        case MY_LINE_PARAMETRIC:
            setAll();
            lparam=true;
            break;
        case MY_LINE_SIMPLE_DDA:
            setAll();
            lsimple=true;
            break;
        case MY_CIRCLE_DIRECT:
            setAll();
            cdirect=true;
            break;
        case MY_CIRCLE_PARAMETRIC:
            setAll();
            cparam=true;
            break;
        case MY_CIRCLE_PARAMETRIC8:
            setAll();
            cparam8=true;
            break;
        case MY_CIRCLE_ITERATIVE:
            setAll();
            cparamIterative=true;
            break;
        case MY_CIRCLE_MIDPOINT1:
            setAll();
            cmidpoint1=true;
            break;
        case MY_CIRCLE_MIDPOINT2:
            setAll();
            cmidpoint2=true;
            break;
        case MY_ELLIPSE_DIRECT:
            setAll();
            eldirect=true;
            break;
        case MY_ELLIPSE_POLAR_NO:
            setAll();
            elpolarno=true;
            break;
        case MY_ELLIPSE_POLAR_YES:
            setAll();
            elpolaryes=true;
            break;
        case MY_ELLIPSE_MIDPOINT:
            setAll();
            elmidpoint=true;
            break;
        case MY_BEZIER_QUADRATIC_CURVE:
            setAll();
            cuquadraticbezier=true;
            break;
        case MY_QUADRATIC_CURVE:
            setAll();
            cuquadratic=true;
            break;

        case MY_HERMITE_CURVE:
            setAll();
            cuhermite=true;
            break;

        case MY_BEZIER_CURVE1:
            setAll();
            cubezier1=true;
            break;
        case MY_BEZIER_CURVE2:
            setAll();
            cubezier2=true;
            break;
        case MY_SPLINES:
            setAll();

            cusplines=true;
            break;
        case MY_CLIPPING:
            clipping = true;
            cout<<"xLeft,yBottom\n";
            break;
        }
        break;
    case WM_LBUTTONUP:
        if (cnt==0&& !cusplines && !clipping)
        {
            points.clear();
            cout<<"First"<<endl;
            p1.x = LOWORD(lParam);
            p1.y = HIWORD(lParam);
            points.push_back(p1);
            cnt++;
        }
        else if (cnt==1 && !cusplines && !clipping)
        {
            cout<<"Second"<<endl;
            p2.x = LOWORD(lParam);
            p2.y = HIWORD(lParam);
            points.push_back(p2);
            cnt++;
        }
        else if (cnt==2&& !cusplines && !clipping)
        {
            cout<<"Third"<<endl;
            p3.x = LOWORD(lParam);
            p3.y = HIWORD(lParam);
            points.push_back(p3);
            cnt++;
        }
        else if (cnt==3&& !cusplines && !clipping)
        {

            cout<<"Fourth"<<endl;
            p4.x = LOWORD(lParam);
            p4.y = HIWORD(lParam);
            points.push_back(p4);
            cnt++;
        }
        ///Calling Functions Starts from Hereeeeee
        if (save)
        {
            saveToFile();
            cnt=0;
        }
        else if (load)
        {
            loadFromFile(hwnd);
            cnt = 0;
        }
        else if (exitt)
        {
            exit(0);
        }
        else if (lInt && cnt>=2)
        {
            HDC hdc = GetDC(hwnd);
            drawLineIntDDAFinal(hdc,p1,p2,rgb);
            add("drawLineIntDDAFinal",points);
            ReleaseDC(hwnd,hdc);
            cnt=0;
        }
        else if (lparam && cnt>=2)
        {
            HDC hdc = GetDC(hwnd);
            cnt=0;
            drawLineParametric(hdc,p1,p2,rgb);
            add("drawLineParametric",points);
            ReleaseDC(hwnd,hdc);
        }
        else if (lnaiive && cnt>=2)
        {
            HDC hdc = GetDC(hwnd);
            cnt=0;
            drawLineNaiive(hdc,p1,p2,rgb);
            add("drawLineNaiive",points);
            ReleaseDC(hwnd,hdc);
        }
        else if (lsimple && cnt>=2)
        {
            HDC hdc = GetDC(hwnd);
            cnt=0;
            drawLineSimpleDDA(hdc,p1,p2,rgb);
            add("drawLineSimpleDDA",points);
            ReleaseDC(hwnd,hdc);
        }
        else if (lmidpoint && cnt>=2)
        {
            HDC hdc = GetDC(hwnd);
            cnt=0;
            drawLineMidPoint(hdc,p1,p2,rgb);
            add("drawLineMidPoint",points);
            ReleaseDC(hwnd,hdc);
        }

        else if (cdirect && cnt>=2)
        {
            HDC hdc = GetDC(hwnd);
            cnt=0;
            drawCircleDirect(hdc,p1,p2,rgb);
            add("drawCircleDirect",points);
            ReleaseDC(hwnd,hdc);
        }
        else if (cparam && cnt>=2)
        {
            HDC hdc = GetDC(hwnd);
            cnt=0;
            drawCircleNotIterative(hdc,p1,p2,rgb);
            add("drawCircleNotIterative",points);
            ReleaseDC(hwnd,hdc);
        }
        else if (cparam8 && cnt>=2)
        {
            HDC hdc = GetDC(hwnd);
            cnt=0;
            drawCircleNotIterative8(hdc,p1,p2,rgb);
            add("drawCircleNotIterative8",points);
            ReleaseDC(hwnd,hdc);
        }
        else if (cparamIterative && cnt>=2)
        {
            HDC hdc = GetDC(hwnd);
            cnt=0;
            drawCircleIterative(hdc,p1,p2,rgb);
            add("drawCircleIterative",points);
            ReleaseDC(hwnd,hdc);
        }
        else if (cmidpoint1 && cnt>=2)
        {
            HDC hdc = GetDC(hwnd);
            cnt=0;
            drawCircleMidPoint1(hdc,p1,p2,rgb);
            add("drawCircleMidPoint1",points);
            ReleaseDC(hwnd,hdc);
        }
        else if (cmidpoint2 && cnt>=2)
        {
            HDC hdc = GetDC(hwnd);
            cnt=0;
            drawCircleMidPoint2(hdc,p1,p2,rgb);
            add("drawCircleMidPoint2",points);
            ReleaseDC(hwnd,hdc);
        }
        else if (eldirect && cnt>=3)
        {
            HDC hdc = GetDC(hwnd);
            cnt=0;
            drawEllipseDirect(hdc,p1,p2,p3,rgb);
            add("drawEllipseDirect",points);
            ReleaseDC(hwnd,hdc);
        }
        else if (elpolarno && cnt>=3)
        {
            HDC hdc = GetDC(hwnd);
            cnt=0;
            drawEllipsePolar(hdc,p1,p2,p3,rgb);
            add("drawEllipsePolar",points);
            ReleaseDC(hwnd,hdc);
        }
        else if (elpolaryes && cnt>=3)
        {
            HDC hdc = GetDC(hwnd);
            cnt=0;
            drawEllipsePolarIterative(hdc,p1,p2,p3,rgb);
            add("drawEllipsePolarIterative",points);
            ReleaseDC(hwnd,hdc);
        }
        else if (elmidpoint && cnt>=3)
        {
            HDC hdc = GetDC(hwnd);
            cnt=0;
            drawEllipseMidPoint(hdc,p1,p2,p3,rgb);
            add("drawEllipseMidPoint",points);
            ReleaseDC(hwnd,hdc);
        }
        else if (cuquadratic && cnt>=3)
        {
            HDC hdc = GetDC(hwnd);
            cnt=0;
            drawQuadraticCurve(hdc,p1,p2,p3,rgb);
            add("drawQuadraticCurve",points);
            ReleaseDC(hwnd,hdc);
        }
        else if (cuquadraticbezier && cnt>=3)
        {
            HDC hdc = GetDC(hwnd);
            cnt=0;
            drawBezierQuadraticCurve(hdc,p1,p2,p3,rgb);
            add("drawBezierQuadraticCurve",points);
            ReleaseDC(hwnd,hdc);
        }
        else if ( cuhermite&& cnt>=4)
        {
            HDC hdc = GetDC(hwnd);
            cnt=0;
            drawCubicHermite(hdc,p1,p2,p3,p4,rgb);
            add("drawCubicHermite",points);
            ReleaseDC(hwnd,hdc);
        }
        else if (cubezier1 && cnt>=4)
        {
            HDC hdc = GetDC(hwnd);
            cnt=0;
            drawCubicBezier1(hdc,p1,p2,p3,p4,rgb);
            add("drawCubicBezier1",points);
            ReleaseDC(hwnd,hdc);
        }
        else if (cubezier2 && cnt>=4)
        {
            HDC hdc = GetDC(hwnd);
            cnt=0;
            drawCubicBezier2(hdc,p1,p2,p3,p4,rgb);
            add("drawCubicBezier2",points);
            ReleaseDC(hwnd,hdc);
        }
        else if (cusplines)
        {
            Point p ;
            if(n==-1)
            {
                n=6;
                cnt=0;
                points.clear();
                ///first time to enter splines so take the initial number of points
            }

            if(cnt!=n)
            {
                ///take points from the user till the count is n
                p.x = LOWORD(lParam);
                p.y = HIWORD(lParam);
                points.push_back(p);
                cnt++;
                cout<<cnt<<endl;
            }
            if (cnt==n)

            {
                p.x = 0;p.y=0;
                points.push_back(p);
                HDC hdc = GetDC(hwnd);
                cout<<"ALL POINTS HAVE BEEN TAKEN"<<endl;
                drawSplines( hdc, points, n+1, 0.5,rgb);
                add("drawSplines",points);
                cout<<"done"<<endl;
                cnt=0;
                n=-1;
                points.clear();
                ReleaseDC(hwnd,hdc);
            }

        }
        else if (clipping)
        {
            HDC hdc = GetDC(hwnd);
            if(n==-1)
            {
                n=7;
                cnt=0;
            }

            if(cnt!=n)
            {

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
                else
                {
                    p1.x = LOWORD(lParam);
                    p1.y = HIWORD(lParam);
                    points.push_back(p1);
                }
                cnt++;
                if(cnt>1) cout<<cnt-1<<endl;

            }
            if (cnt==n)

            {
                cout<<"ALL POINTS HAVE BEEN TAKEN"<<endl;
                sutherlandHodgman( hdc, points,rec);

                ///The last two points of rectangle will be in the points
                points.clear();
                cnt=0;
                n=-1;
            }
            ReleaseDC(hwnd,hdc);
        }

        break;
    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
