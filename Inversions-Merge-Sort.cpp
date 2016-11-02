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
    int array[100000];      //因为Q8.txt有100000行
    int i;
    double res=0;

    for(i=0;i<100000;i++){
      getline(in,s);
      //cout<<s<<endl;
      sscanf(s.c_str(),"%D",array+i);   //将按行读入的字符串转化成int型数据
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

    if(left==right) return result;    //必要的，如果只有一个元素，那么该元素就是一个已排好序的序列，排序结束
                                    //如果不止一个元素，则对前一半和后一半分别递归调用归并排序函数进行排序
    tmp1=Sort_and_Count(array,left,mid);  //左边逆序数对
    tmp2=Sort_and_Count(array,mid+1,right);  //右边逆序数对
    //将排好序的两个序列归并起来，就完成了整个序列的排序
    //这里传入mid+1是因为Merge里遍历左边的变量i的初始值为left，现假设传入为left=mid=0,right=1;
    //则不进去第一个while循环进行比较,直接进入第三个while，默认array[0]比array[1]小，导致出错
    result=Merge_and_Count(array,left,mid+1,right);
    return tmp1+tmp2+result;  //总的逆序数对
}

//计算逆序数对
//合并两个已排好序的有序表，以mid为中值将array看成是两张表
double Merge_and_Count(int array[],int left,int mid,int right){
     int i,j;
     int k;
     int *temp=new int[right-left+1];
     double rc=0;

     //逆序数对满足p<q并且a[p]>a[q]
     int p;
     int q=mid;
     for(p=left;p<mid;++p){
         while(q<=right&&array[p]>array[q])
             ++q;
         rc+=q-mid;         //右边的表中满足条件的数的个数
     }

     //对两表进行合并
     i=left;
     j=mid;
     k=0;

     while(i<mid&&j<=right){
         if(array[i]<=array[j]) temp[k++]=array[i++];
         else temp[k++]=array[j++];
     }
     while(i<mid) temp[k++]=array[i++];       //左边的记录没有结束
     while(j<=right) temp[k++]=array[j++];   //右边的记录没有结束

     //这里array下标的范围应是left---right
     for(i=0,k=left;k<=right;)                            //将临时数组里的值送回array中
         array[k++]=temp[i++];

    delete [] temp;

    return rc;
}

