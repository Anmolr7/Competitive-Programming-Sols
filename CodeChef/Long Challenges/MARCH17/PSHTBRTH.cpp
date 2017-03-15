#include<bits/stdc++.h>
#define pb push_back
using namespace std;

vector<int> rects;
int p2[16];
int grn[65600];

// Code for segment tree copied from http://www.geeksforgeeks.org/segment-tree-set-1-sum-of-given-range/
// A utility function to get the middle index from corner indexes.
int getMid(int s, int e) {  return s + (e -s)/2;  }

/*  A recursive function to get the sum of values in given range
    of the array. The following are parameters for this function.

    st    --> Pointer to segment tree
    si    --> Index of current node in the segment tree. Initially
              0 is passed as root is always at index 0
    ss & se  --> Starting and ending indexes of the segment represented
                 by current node, i.e., st[si]
    qs & qe  --> Starting and ending indexes of query range */
int getSumUtil(int *st, int ss, int se, int qs, int qe, int si)
{
    // If segment of this node is a part of given range, then return
    // the sum of the segment
    if (qs <= ss && qe >= se)
        return st[si];

    // If segment of this node is outside the given range
    if (se < qs || ss > qe)
        return 0;

    // If a part of this segment overlaps with the given range
    int mid = getMid(ss, se);
    return getSumUtil(st, ss, mid, qs, qe, 2*si+1) ^
           getSumUtil(st, mid+1, se, qs, qe, 2*si+2);
}

/* A recursive function to update the nodes which have the given
   index in their range. The following are parameters
    st, si, ss and se are same as getSumUtil()
    i    --> index of the element to be updated. This index is
             in input array.
   diff --> Value to be added to all nodes which have i in range */
void updateValueUtil(int *st, int ss, int se, int i, int diff, int si)
{
    // Base Case: If the input index lies outside the range of
    // this segment
    if (i < ss || i > se)
        return;

    // If the input index is in range of this node, then update
    // the value of the node and its children
    st[si] = st[si] ^ diff;
    if (se != ss)
    {
        int mid = getMid(ss, se);
        updateValueUtil(st, ss, mid, i, diff, 2*si + 1);
        updateValueUtil(st, mid+1, se, i, diff, 2*si + 2);
    }
}

// The function to update a value in input array and segment tree.
// It uses updateValueUtil() to update the value in segment tree
void updateValue(int arr[], int *st, int n, int i, int new_val)
{
    // Get the difference between new value and old value
    int diff = new_val ^ arr[i];

    // Update the value in array
    arr[i] = new_val;

    // Update the values of nodes in segment tree
    updateValueUtil(st, 0, n-1, i, diff, 0);
}

// Return sum of elements in range from index qs (quey start)
// to qe (query end).  It mainly uses getSumUtil()
int getSum(int *st, int n, int qs, int qe)
{
    // Check for erroneous input values
    if (qs < 0 || qe > n-1 || qs > qe)
    {
        printf("Invalid Input");
        return -1;
    }

    return getSumUtil(st, 0, n-1, qs, qe, 0);
}

// A recursive function that constructs Segment Tree for array[ss..se].
// si is index of current node in segment tree st
int constructSTUtil(int arr[], int ss, int se, int *st, int si)
{
    // If there is one element in array, store it in current node of
    // segment tree and return
    if (ss == se)
    {
        st[si] = arr[ss];
        return arr[ss];
    }

    // If there are more than one elements, then recur for left and
    // right subtrees and store the sum of values in this node
    int mid = getMid(ss, se);
    st[si] =  constructSTUtil(arr, ss, mid, st, si*2+1) ^
              constructSTUtil(arr, mid+1, se, st, si*2+2);
    return st[si];
}

/* Function to construct segment tree from given array. This function
   allocates memory for segment tree and calls constructSTUtil() to
   fill the allocated memory */
int *constructST(int arr[], int n)
{
    // Allocate memory for segment tree

    //Height of segment tree
    int x = (int)(ceil(log2(n)));

    //Maximum size of segment tree
    int max_size = 2*(int)pow(2, x) - 1;

    // Allocate memory
    int *st = new int[max_size];

    // Fill the allocated memory st
    constructSTUtil(arr, 0, n-1, st, 0);

    // Return the constructed segment tree
    return st;
}

void pre()
{
    int a,b,c,d,i,j;

    p2[0]=1;
    for(i=1;i<16;i++)
    {
        p2[i]=p2[i-1] << 1;
    }

    for(a=3;a>=0;a--)
    {
        for(b=3;b>=0;b--)
        {
            for(c=a;c>=0;c--)
            {
                for(d=b;d>=0;d--)
                {
                    int tmp=0;
                    for(j=a;j>=c;j--)
                    {
                        for(i=b;i>=d;i--)
                        {
                            tmp |= 1 << ((i*4)+j);
                        }
                    }
                    rects.pb(tmp);
                    //bitset<16> x(tmp);
                    //printf("from (%d,%d) to (%d,%d) ",a,b,c,d);
                    //cout << x <<endl;
                }
            }
        }
    }
    //cout << rects.size() << endl;

    grn[0]=0;
    for(i=1;i<65600;i++)
    {
        grn[i]=-1;
    }
}

int grundy(int x)
{
    //bitset<16> asd(x);
    //cout << "grundy " << asd <<endl;
    if(grn[x]!=-1)
        return grn[x];

    int tmp[20],i,curr;
    memset(tmp,0,sizeof(tmp));
    for(i=0;i<100;i++)
    {
        //bitset<16> zzz(rects[i]);;
        //cout << "\twith " << zzz <<endl;
        curr=rects[i];
        if((x&curr) == curr)
        {
            tmp[grundy(x^curr)]=1;
        }
    }
    for(i=0;i<20;i++)
    {
        if(tmp[i]==0)
            break;
    }
    grn[x]=i;
    return grn[x];
}

int main()
{
    pre();
    int t,n,m,k,i,j,tmp,cnt,ch,l,r,ans;
    scanf("%d",&t);
    while(t--)
    {
        string str;
        scanf("%d%d",&n,&m);
        int arr[n];
        for(k=0;k<n;k++)
        {
            tmp=0;
            cnt=15;
            for(i=0;i<4;i++)
            {
                cin>>str;
                for(j=0;j<4;j++)
                {
                    if(str[j]=='1')
                        tmp |= p2[cnt];
                    cnt--;
                }
            }
            arr[k]=grundy(tmp);
        }

        int *st = constructST(arr, n);

        for(k=0;k<m;k++)
        {
            scanf("%d",&ch);
            if(ch==1)
            {
                scanf("%d%d",&l,&r);
                ans=getSum(st, n, l-1, r-1);
                if(ans==0)
                    printf("Lotsy\n");
                else
                    printf("Pishty\n");
            }
            else
            {
                scanf("%d",&l);

                tmp=0;
                cnt=15;
                for(i=0;i<4;i++)
                {
                    cin>>str;
                    for(j=0;j<4;j++)
                    {
                        if(str[j]=='1')
                            tmp |= p2[cnt];
                        cnt--;
                    }
                }
                updateValue(arr, st, n, l-1, grundy(tmp));
            }
        }
    }
}
