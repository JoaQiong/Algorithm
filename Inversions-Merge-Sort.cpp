#include <iostream>
#include<fstream>
#include<string>
#include<stdio.h>
using namespace std;
double Sort_and_Count(int array[],int left,int right);
double Merge_and_Count(int array[],int left,int mid,int right);
int main(){
    ifstream in("Q8.txt");
    string s;
    int array[100000];      //��ΪQ8.txt��100000��
    int i;
    double res=0;

    for(i=0;i<100000;i++){
      getline(in,s);
      //cout<<s<<endl;
      sscanf(s.c_str(),"%D",array+i);   //�����ж�����ַ���ת����int������
      //cout<<array[i]<<endl;
    }

    res=Sort_and_Count(array,0,99999);
    cout<<res<<endl;
    return 0;
}

//
double Sort_and_Count(int array[],int left,int right){
    double tmp1,tmp2,result;
    int mid;
    mid=(left+right)/2;
    result=0;

    if(left==right) return result;    //��Ҫ�ģ����ֻ��һ��Ԫ�أ���ô��Ԫ�ؾ���һ�����ź�������У��������
                                    //�����ֹһ��Ԫ�أ����ǰһ��ͺ�һ��ֱ�ݹ���ù鲢��������������
    tmp1=Sort_and_Count(array,left,mid);  //�����������
    tmp2=Sort_and_Count(array,mid+1,right);  //�ұ���������
    //���ź�����������й鲢��������������������е�����
    //���ﴫ��mid+1����ΪMerge�������ߵı���i�ĳ�ʼֵΪleft���ּ��贫��Ϊleft=mid=0,right=1;
    //�򲻽�ȥ��һ��whileѭ�����бȽ�,ֱ�ӽ��������while��Ĭ��array[0]��array[1]С�����³���
    result=Merge_and_Count(array,left,mid+1,right);
    return tmp1+tmp2+result;  //�ܵ���������
}

//������������
//�ϲ��������ź�����������midΪ��ֵ��array���������ű�
double Merge_and_Count(int array[],int left,int mid,int right){
     int i,j;
     int k;
     int *temp=new int[right-left+1];
     double rc=0;

     //������������p<q����a[p]>a[q]
     int p;
     int q=mid;
     for(p=left;p<mid;++p){
         while(q<=right&&array[p]>array[q])
             ++q;
         rc+=q-mid;         //�ұߵı����������������ĸ���
     }

     //��������кϲ�
     i=left;
     j=mid;
     k=0;

     while(i<mid&&j<=right){
         if(array[i]<=array[j]) temp[k++]=array[i++];
         else temp[k++]=array[j++];
     }
     while(i<mid) temp[k++]=array[i++];       //��ߵļ�¼û�н���
     while(j<=right) temp[k++]=array[j++];   //�ұߵļ�¼û�н���

     //����array�±�ķ�ΧӦ��left---right
     for(i=0,k=left;k<=right;)                            //����ʱ�������ֵ�ͻ�array��
         array[k++]=temp[i++];

    delete [] temp;

    return rc;
}

