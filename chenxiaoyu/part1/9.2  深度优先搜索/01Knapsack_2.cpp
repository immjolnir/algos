#include<iostream>
#include<algorithm>//sort函数需要该头文件 
using namespace std;
const int M=105;
int i,j,n,W;//n表示n个物品，W表示背包的容量
double w[M],v[M];//w[i] 表示第i个物品的重量，v[i] 表示第i个物品的价值
bool x[M];  //x[i]表示第i个物品是否放入背包
double cw;   //当前重量
double cp;   //当前价值
double bestp;  //当前最优价值
bool bestx[M]; //当前最优解

double Bound(int i){//计算上界（即将剩余物品装满剩余的背包容量时所能获得的最大价值）
    //i表示剩余物品为第i~n种物品
    double cleft=W-cw;//剩余容量
    double brp=0.0;
    while(i<=n&&w[i]<cleft){
        cleft-=w[i];
        brp+=v[i];
        i++;
    }
    if(i<=n)//装满背包
        brp+=v[i]/w[i]*cleft;
    return cp+brp;
}

void Backtrack(int t){//用于搜索空间数，t表示当前扩展结点在第t层
    if(t>n){//已经到达叶子结点
        for(j=1;j<=n;j++)
            bestx[j]=x[j];
        bestp=cp;//保存当前最优解
        return ;
    }
    if(cw+w[t]<=W){//如果满足限制条件则搜索左子树
        x[t]=1;
        cw+=w[t];
        cp+=v[t];
        Backtrack(t+1);
        cw-=w[t];
        cp-=v[t];
    }
    if(Bound(t+1)>bestp){//如果满足限制条件则搜索右子树
        x[t]=0;
        Backtrack(t+1);
    }
}

struct Object{//定义物品结构体，包含物品序号和单位重量价值
    int id; //物品序号
    double d;//单位重量价值
};

bool cmp(Object a1,Object a2){//按照物品单位重量价值由大到小排序
    return a1.d>a2.d;
}

void Knapsack(int W,int n){
    double sumw=0; //用来统计所有物品的总重量
    double sumv=0; //用来统计所有物品的总价值
    Object Q[n];   //物品结构体类型,用于按单位重量价值(价值/重量比)排序
    double a[n+1],b[n+1];//辅助数组,用于把排序后的重量和价值赋值给原来的重量价值数组
    for(i=1;i<=n;i++){
        Q[i-1].id=i;
        Q[i-1].d=1.0*v[i]/w[i];
        sumv+=v[i];
        sumw+=w[i];
    }
    if(sumw<=W){
        bestp=sumv;
        cout<<"放入背包的物品最大价值为: "<<bestp<<endl;
        cout<<"所有的物品均放入背包。";
        return;
    }
    sort(Q,Q+n,cmp);
    for(i=1;i<=n;i++){
        a[i]=w[Q[i-1].id];//把排序后的数据传递过去
        b[i]=v[Q[i-1].id];
    }
    for(i=1;i<=n;i++){
        w[i]=a[i];//把排序后的数据传递过去
        v[i]=b[i];
        //cout<<"排序后的重量和价值为: "<<w[i]<<"  "<<v[i]<<endl;
    }
    Backtrack(1);
    cout<<"放入背包的物品最大价值为: "<<bestp<<endl;
    cout<<"放入背包的物品序号为: ";
    for(i=1;i<=n;i++){
        if(bestx[i]==1)
			cout<<Q[i-1].id<<" ";
    }
    cout<<endl;
}

int main(){
    cout<<"请输入物品的个数n和背包的容量W:";
    cin>>n>>W;
    cout<<"请依次输入每个物品的重量w和价值v,用空格分开:"<<endl;
    for(i=1;i<=n;i++)
        cin>>w[i]>>v[i];
    Knapsack(W,n);
    return 0;
}
/*测试数据
4 10
2 6
5 3
4 5
2 4
*/
