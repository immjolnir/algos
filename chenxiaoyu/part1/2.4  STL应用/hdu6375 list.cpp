#include<cstdio>
#include<list>
using namespace std;
const int maxn=15e4+10;
int n,m;
list<int> d[maxn];

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar());
	for(;ch>='0'&&ch<='9';ch=getchar()) x=x*10+ch-'0';
}

int main(){
	while(~scanf("%d%d",&n,&m)){
		for(int i=1;i<=n;i++)
			d[i].clear();
		int k,u,v,w;
		while(m--){
			read(k);
			switch(k){
			case 1:
				read(u),read(w),read(v);
				if(w==0)
					d[u].push_front(v);
				else
					d[u].push_back(v);
				break;	
			case 2:
				read(u),read(w);
				if(d[u].empty())
					printf("-1\n");
				else{
					if(w==0){
						printf("%d\n",d[u].front());
						d[u].pop_front();
					}
					else{
						printf("%d\n",d[u].back());
						d[u].pop_back();
					}
				}
				break;
			case 3:
				read(u),read(v),read(w);
				if(w)
					d[v].reverse();
				d[u].splice(d[u].end(),d[v]);//splice拼接函数会自动清空v，常数时间 
				break;
			}
		}
	}
	return 0;
}
