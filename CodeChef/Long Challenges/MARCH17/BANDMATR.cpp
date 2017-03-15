#include<bits/stdc++.h>
using namespace std;

int st[501];

void prec()
{
    st[0]=0;
    int i;
    for(i=1;i<501;i++)
    {
        st[i]=st[i-1]+i;
    }
}

int main()
{
    prec();
    int t,n,cnt,i,j,x,ans;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        cnt=0;
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                scanf("%d",&x);
                if(x==0)
                    cnt++;
            }
        }
        cnt >>= 1;
        ans=-1;
        for(i=1;i<n;i++)
        {
            if(cnt<st[i])
                break;
        }
        ans=i-1;
        ans = n - ans - 1;
        printf("%d\n",ans);
    }
}
