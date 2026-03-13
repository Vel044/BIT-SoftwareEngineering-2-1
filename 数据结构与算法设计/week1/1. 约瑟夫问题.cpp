#include <bits/stdc++.h>
using namespace std;
int n,k,m,a[100000],i,j,t;
int main()
{
    scanf("%d,%d,%d",&n,&k,&m);
    if(n<1||k<1||m<1){
		printf("n,m,k must bigger than 0.\n");
		return 0;
	}
	if(k>n){
		printf("k should not bigger than n.\n");
		return 0;
	}
	i=k;
	while(t<n){
		if(a[i]==0){
			j++;
			if(j==m){
				a[i]=1;
				j=0;
				if(t<n-1){
					if((t+1)%10==0 &&t!=0)
						printf("%d\n",i);
						else printf("%d ",i);
				}
				else printf("%d\n",i);
				t++;
			}
		}
		i=i%n+1;
	}
	return 0; 
}
