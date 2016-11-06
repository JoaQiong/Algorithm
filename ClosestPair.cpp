#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
//����Point��
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
    //��Ԫ����ʵ�����������
    friend ostream& operator<<(ostream& out, const Point& p);

private:
    double x,y;
};

ostream& operator<<(ostream& out, const Point& p)
{
    out<<"P("<<p.getX()<<","<<p.getY()<<")";
    return out;
}


double Distance(const Point& s, const Point& t)    //��������֮��ľ���
{
    double squarex = ( s.getX() - t.getX() ) * ( s.getX() - t.getX() );
    double squarey = ( s.getY() - t.getY() ) * ( s.getY() - t.getY() );
    return sqrt( squarex + squarey );
}

bool ComparePoint(const Point& p1, const Point& p2)   //�Ƚ����㣬��������
{
    if( fabs(p1.getX() - p2.getX()) < 0.0000000001)   //��x��ȣ���Ƚ�y
        return (p1.getY() < p2.getY());
    return (p1.getX() < p2.getX());
}

double EnumClosestPair(const Point * p, int num)  //����ö���ҳ�������
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

double FindClosestPair(const Point * p, int num)  //ʹ�÷��η��ҳ�������
{
    double dL, dR, d, midXVal;

    if(num<2){
        cout<<"your input is error,please try again!"<<endl; //��Ϊ������������������
    }
    if (num < 4)//��Ϊ����dL��dR�ļ���������Ҫ4���㣬����3����ʱ����ö�ٳ��������
    {
        return EnumClosestPair(p, num);
    }

    //��x������������м��x���������ߵĵ���뿪��
    int mid = 0;
    mid = (num+1)/2;
    dL = FindClosestPair(p, mid);
    dR = FindClosestPair(p+mid, (num-mid));
    d = dL < dR ? dL : dR;   //ȡ��������Ժ��ұ������Ծ���Ľ�С����ȷ����������

    midXVal = p[mid].getX();

    //�ҳ����������뷶Χ�ڵĵ�
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
    //���������뷶Χ�ڵĵ���бȽ�
    for (int i=stripStart; i<stripEnd; i++)
    {
        for (int j=i+1; j<stripEnd; j++)
        {
            if (p[j].getY()-p[i].getY() > d)   //ͨ����y�ıȽϣ���һ������һЩ�����������ĵ�ԵıȽ�
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
    sort(p, p+size, ComparePoint);    //�����е������
    FindClosestPair(p, size);

    return 0;
}
