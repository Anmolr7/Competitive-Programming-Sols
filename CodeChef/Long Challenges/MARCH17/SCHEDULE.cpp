#include<bits/stdc++.h>
using namespace std;
vector<int> blocks;
int k,ans;
bool chk(int y)
{
    int i,x,sum=0;
    for(i=blocks.size()-1;i>=0;i--)
    {
        if(blocks[i]<=y)
            break;
        else
        {
            x=(blocks[i]-y)/(y+1);
            if(((y+1)*x)!=(blocks[i]-y))
                x++;
            sum+=x;
            if(sum>k)
                break;
        }
    }
    if(sum>k)
        return false;
    else
        return true;
}

void bsearch(int lo, int hi)
{
    //printf("lo=%d hi=%d\n",lo,hi);
    if(lo>hi)
        return;
    int mid = lo + (hi-lo)/2;
    if(chk(mid))
    {
        ans=mid;
        bsearch(lo,mid-1);
    }
    else
    {
        bsearch(mid+1,hi);
    }
}

int main()
{
    //freopen("TASK.in","r",stdin);freopen("TASK2.out","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,cnt1,cnt2,i;
        blocks.clear();
        scanf("%d%d",&n,&k);
        string str;
        cin>>str;
        cnt1=0;cnt2=0;

        for(i=0;i<n;i++)
        {
            if(i&1)
            {
                cnt1+=((str[i]-'0')^1);
                cnt2+=((str[i]-'0')^0);
            }
            else
            {
                cnt2+=((str[i]-'0')^1);
                cnt1+=((str[i]-'0')^0);
            }
        }
        if(min(cnt1,cnt2)<=k)
        {
            printf("1\n");
            continue;
        }

        int tmp=1;
        for(i=1;i<n;i++)
        {
            if(str[i]==str[i-1])
                tmp++;
            else
            {
                blocks.push_back(tmp);
                tmp=1;
            }
        }
        blocks.push_back(tmp);

        sort(blocks.begin(),blocks.end());
        ans=blocks[blocks.size()-1];
        bsearch(2,blocks[blocks.size()-1]);
        printf("%d\n",ans);
    }
}
