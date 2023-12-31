#include<cstdio>//非存储型KD树+备份数组 
#include<algorithm>
#define sq(x) (x)*(x)
using namespace std;
typedef long long LL;
const int N=100010;
const LL inf=1e18;
int idx,k=2;
 
struct Node{
    int x[2];
    bool operator<(const Node &b)const{
        return x[idx]<b.x[idx];
    }
}a[N],p[N];//备份数组 

LL ans;

struct KD_Tree{
	LL dis(Node p,Node q){
		LL ret=0;
	    for(int i=0;i<k;i++)
	        ret+=sq((LL)p.x[i]-q.x[i]);//坑点！注意类型转换 
	    return ret?ret:inf;
	}
	
    void build(int l,int r,int dep){
        if(l>r) return;
        int mid=(l+r)>>1;
        idx=dep%k;
        nth_element(a+l,a+mid,a+r+1);//注意！对原始序列有改变，因此用p[]复制一份 
        build(l,mid-1,dep+1);
        build(mid+1,r,dep+1);
    }
 
	void query(int l,int r,int dep,Node p){
	    if(l>r) return;
	    int mid=(l+r)>>1,dim=dep%k;	
	    LL dist=dis(a[mid],p);
	    if(dist<ans)
			ans=dist;
		LL rd=sq((LL)p.x[dim]-a[mid].x[dim]);
		if(p.x[dim]<a[mid].x[dim]){
			query(l,mid-1,dep+1,p);
	    	if(rd<ans)
	    		query(mid+1,r,dep+1,p);
		}
		else{
			query(mid+1,r,dep+1,p);
	    	if(rd<ans)
	    		query(l,mid-1,dep+1,p);
		}	
	}
}KDT;
 
int main(){
    int T,n;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=0;i<n;i++){
            for(int j=0;j<k;j++)
                scanf("%d",&p[i].x[j]);
            a[i]=p[i];
        }
        KDT.build(0,n-1,0);
        for(int i=0;i<n;i++){
    		ans=inf;
			KDT.query(0,n-1,0,p[i]);
        	printf("%I64lld\n",ans);
		}       
    }
    return 0;
}
