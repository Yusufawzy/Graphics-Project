#include <vector>

void multiplyMatrixVector(int mat[],int vec[],int res[],int n)
{
    for(int i = 0 ; i < n ; i++)
    {
        res[i] = 0;
        for (int j = 0 ; j < n ; j++)
        {
            res[i]+= mat[i*n+j]*vec[j];
        }
    }
}

void drawQuadraticCurve(HDC hdc,Point p0,Point p05,Point p1,COLORREF rgb)
{
    int xArr[] = {p0.x,p05.x,p1.x}, yArr[] = {p0.y,p05.y,p1.y};
    int mat[ ] = {1,0,0,   -3,4,-1,    2,-4,2};
    int coArrX[3],coArrY[3];
    multiplyMatrixVector(mat,xArr,coArrX,3);;
    multiplyMatrixVector(mat,yArr,coArrY,3);;

    int x, y;
    for(double  t = 0 ; t <=1 ; t+=0.0001)
    {
        x = coArrX[0] + coArrX[1]*t + coArrX[2]*t*t;
        y = coArrY[0] + coArrY[1]*t + coArrY[2]*t*t;

        SetPixel(hdc,x,y,rgb);
    }
}
void drawBezierQuadraticCurve(HDC hdc,Point p0,Point p05,Point p1,COLORREF rgb)
{
    int xArr[] = {p0.x,p05.x,p1.x}, yArr[] = {p0.y,p05.y,p1.y};
    int mat[ ] = {1,0,0,-2,2,0,1,-2,1};
    int coArrX[3],coArrY[3];
    multiplyMatrixVector(mat,xArr,coArrX,3);;
    multiplyMatrixVector(mat,yArr,coArrY,3);;

    int x, y;
    for(double  t = 0 ; t <=1 ; t+=0.0001)
    {
        x = coArrX[0] + coArrX[1]*t + coArrX[2]*t*t;
        y = coArrY[0] + coArrY[1]*t + coArrY[2]*t*t;

        SetPixel(hdc,x,y,rgb);
    }
}
void drawCubicHermite(HDC hdc,Point p0,Point s0,Point p1,Point s1,COLORREF rgb)
{
    int n = 4;
    int xArr[] = {p0.x,s0.x,p1.x,s1.x}, yArr[] = {p0.y,s0.y,p1.y,s1.y};
    int mat[] = {2,1,-2,1, -3,-2,3,-1, 0,1,0,0,   1,0,0,0   };
    int coArrX[n],coArrY[n];
    multiplyMatrixVector(mat,xArr,coArrX,n);;
    multiplyMatrixVector(mat,yArr,coArrY,n);
    double x, y;
    for(double  t = 0 ; t <=1 ; t+=0.0001)
    {
        x = coArrX[3] + coArrX[2]*t + coArrX[1]*t*t+coArrX[0]*t*t*t;
        y = coArrY[3] + coArrY[2]*t + coArrY[1]*t*t+coArrY[0]*t*t*t;

        SetPixel(hdc,round(x),round(y),rgb);
    }
}

void drawCubicBezier1(HDC hdc,Point p0,Point p1,Point p2,Point p3,COLORREF rgb)
{
    int n = 4;
    int xArr[] = {p0.x,p1.x,p2.x,p3.x},yArr[] = {p0.y,p1.y,p2.y,p3.y};
    int mat[] = { -1,3,-3,1,  3,-6,3,0, -3,3,0,0,  1,0,0,0  };
    int coArrX[n],coArrY[n];
    ///Na5od balna w a7na bnrsm in el third point dy msh btkon bltrteb zy ally fato but btkon ta7t w b3dkda fo2
    multiplyMatrixVector(mat,xArr,coArrX,n);;
    multiplyMatrixVector(mat,yArr,coArrY,n);
    double x, y;
    for(double  t = 0 ; t <=1 ; t+=0.0001)
    {
        x = coArrX[3] + coArrX[2]*t + coArrX[1]*t*t+coArrX[0]*t*t*t;
        y = coArrY[3] + coArrY[2]*t + coArrY[1]*t*t+coArrY[0]*t*t*t;

        SetPixel(hdc,round(x),round(y),rgb);
    }
}
void drawCubicBezier2(HDC hdc,Point p0,Point p1,Point p2,Point p3,COLORREF rgb)
{
    Point s0,s1 ;
    s0.x = 3 * (p1.x-p0.x), s0.y = 3 * (p1.y - p0.y),s1.x = 3 * (p3.x-p2.x), s1.y = 3 * (p3.y-p2.y) ;
    drawCubicHermite(hdc,p0,s0,p3,s1,rgb);
}
void drawSplines(HDC hdc,vector <Point> points,int n, double c,COLORREF rgb)
{
    double c1 = 1-c;
    Point s0,s1,p0,p1;
    s0.x =c1*(points[2].x - points[0].x), s0.y =  c1*(points[2].y - points[0].y) ;
    for (int i = 1 ; i<n-1; i++)
    {
        p0.x = points[i-1].x,p0.y = points[i-1].y;
        p1.x = points[i].x, p1.y = points[i].y;
        s1.x = c1*(points[i+1].x-points[i-1].x),s1.y=c1*(points[i+1].y-points[i-1].y);

        drawCubicHermite(hdc,p0,s0,p1,s1,rgb);
        p0 = p1;
    }
}
