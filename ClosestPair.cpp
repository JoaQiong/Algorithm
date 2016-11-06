#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
//定义Point类
class Point
{
public:
    Point(double xx=0.0, double yy=0.0){
        x=xx;
        y=yy;
    }
    double getX() const
    {
        return x;
    }
    double getY() const
    {
        return y;
    }
    //友元函数实现运算符重载
    friend ostream& operator<<(ostream& out, const Point& p);

private:
    double x,y;
};

ostream& operator<<(ostream& out, const Point& p)
{
    out<<"P("<<p.getX()<<","<<p.getY()<<")";
    return out;
}


double Distance(const Point& s, const Point& t)    //计算两点之间的距离
{
    double squarex = ( s.getX() - t.getX() ) * ( s.getX() - t.getX() );
    double squarey = ( s.getY() - t.getY() ) * ( s.getY() - t.getY() );
    return sqrt( squarex + squarey );
}

bool ComparePoint(const Point& p1, const Point& p2)   //比较两点，进行排序
{
    if( fabs(p1.getX() - p2.getX()) < 0.0000000001)   //若x相等，则比较y
        return (p1.getY() < p2.getY());
    return (p1.getX() < p2.getX());
}

double EnumClosestPair(const Point * p, int num)  //少量枚举找出最近点对
{
    double distance=Distance(p[0], p[1]);
    int start = 0;
    int end = 1;
    for (int i=0; i<num; i++)
    {
        for (int j=i+1; j<num; j++)
        {
            if ( Distance(p[i], p[j]) < distance )
            {
                distance = Distance(p[i], p[j]);
                start = i;
                end = j;
            }
        }
    }
    return distance;
}

double FindClosestPair(const Point * p, int num)  //使用分治法找出最近点对
{
    double dL, dR, d, midXVal;

    if(num<2){
        cout<<"your input is error,please try again!"<<endl; //因为最近点对至少有两个点
    }
    if (num < 4)//因为下面dL和dR的计算至少需要4个点，所以3个点时可以枚举出最近距离
    {
        return EnumClosestPair(p, num);
    }

    //按x坐标排序后，以中间的x将左右两边的点分离开来
    int mid = 0;
    mid = (num+1)/2;
    dL = FindClosestPair(p, mid);
    dR = FindClosestPair(p+mid, (num-mid));
    d = dL < dR ? dL : dR;   //取左边最近点对和右边最近点对距离的较小者来确定条带距离

    midXVal = p[mid].getX();

    //找出在条带距离范围内的点
    int stripStart = 0;
    int stripEnd = num-1;
    for (int i=0; i<num-1; i++)
    {
        if ( (p[i].getX() < midXVal-d) && (p[i+1].getX() >= midXVal-d) )
            stripStart = i+1;
        if ( (p[i].getX() <= midXVal+d) && (p[i+1].getX() > midXVal+d) )
            stripEnd = i;
    }
    int start = 0;
    int end = 1;
    //将条带距离范围内的点进行比较
    for (int i=stripStart; i<stripEnd; i++)
    {
        for (int j=i+1; j<stripEnd; j++)
        {
            if (p[j].getY()-p[i].getY() > d)   //通过对y的比较，进一步减少一些不满足条件的点对的比较
            break;
            if ( Distance(p[i], p[j]) < d )
            {
                d = Distance(p[i], p[j]);
                start = i;
                end = j;
            }
        }
    }
    if (start!=0 || end!=0){
        cout << "The closest pair is: " << p[start+1] << ", " << p[end+1] <<""<<endl;
    }
    cout << "the distance is: " << d <<endl;
    return d;
}

int main()
{
    Point p[] = {Point(2,3), Point(4,3), Point(4,6), Point(5,7), Point(4,3)};
    int size = sizeof(p)/sizeof(p[0]);
    sort(p, p+size, ComparePoint);    //将所有点对排序
    FindClosestPair(p, size);

    return 0;
}
