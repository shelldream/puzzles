/**
    计算大数阶乘
    author:Xiaojun Huang
    Date:2015.09.15
*/

#include <iostream>
using namespace std;

void multiply(int* result, int& k, int m)
{
    for(int i = 0; i <= k;i++)
    {
        result[i] *= m;
    }
    for(int i = 0; i<= k;i++)
    {
        int tmp = result[i];
        result[i] = 0;
        int j = i;
        while(tmp)
        {
            result[j++] += tmp%10;
            tmp /= 10;
            if(j > k && tmp)
                k = j;
        }
    }
}

void print_result(int* result)
{
    int i = 99999;
    while(result[i] == 0)
        i--;
    while(i >= 0)
        cout<<result[i--];
    cout<<endl;
}
int main()
{
    int n;
    cin>>n;
    int result[100000] = {1};
    int k = 0;
    for(int i = 1;i <= n;i++)
        multiply(result, k, i);
    print_result(result);
}
