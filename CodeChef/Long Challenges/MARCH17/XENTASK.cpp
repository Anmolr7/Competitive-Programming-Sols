#include<bits/stdc++.h>
using namespace std;

int main()
{
    int t,n,i,x,sum1,sum2;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        sum1=0;sum2=0;
        for(i=0;i<n;i++)
        {
            scanf("%d",&x);
            if(i&1)
                sum1+=x;
            else
                sum2+=x;
        }
        for(i=0;i<n;i++)
        {
            scanf("%d",&x);
            if(i&1)
                sum2+=x;
            else
                sum1+=x;
        }
        printf("%d\n",min(sum1,sum2));
    }
}
