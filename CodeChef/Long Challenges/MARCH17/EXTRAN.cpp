#include<bits/stdc++.h>
using namespace std;

int main()
{
    int t,n,i,x;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        vector<int> vec;
        for(i=0;i<n;i++)
        {
            scanf("%d",&x);
            vec.push_back(x);
        }
        sort(vec.begin(),vec.end());
        int ans=-1;

        for(i=2;i<n-2;i++)
        {
                if((vec[i]-vec[i-1]==1)&&(vec[i+1]-vec[i]==1))
                {
                    continue;
                }
                else
                {
                    ans=vec[i];
                    break;
                }
        }
        if(ans==-1)
        {
            if(vec[1]-vec[0]!=1)
                ans=vec[0];
            else if (vec[n-1]-vec[n-2]!=1)
                ans=vec[n-1];
        }
        printf("%d\n",ans);
    }
}
