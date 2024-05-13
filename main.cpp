#include <bits/stdc++.h>
#define int64 uint64_t
using namespace std;
using namespace chrono;
typedef long long ll;
const int runningtime=1000;
const int range_of_n[] = {10,50,100,200,300,400,500,1000};
const int range_of_k[] = {10,50,100,200,300,400,500,1000};
double dp[1005][1005];
double ticket[1005][1005];
double times=0;
double cishu=0;

template<class T>

int length(T& arr)
{
    //cout << sizeof(arr[0]) << endl;
    //cout << sizeof(arr) << endl;
    return sizeof(arr) / sizeof(arr[0]);
}

double fix_price(int n, int k){
    return 1.0-(double)k/(double)n;
}

double f(double a, double b, double t) {
    return (1-t) * (a + t) + (t) * b;
    // -t^2 - num[i-1][j-1]*t + t + num[i-1][j-1] + num[i-1][j] * t;
    // -t^2 + (num[i-1][j] + 1 - num[i-1][j-1]) * t + num[i-1][j-1];
    // t = (num[i-1][j] + 1 - num[i-1][j-1])/2;
    //

}
double generate_price(){
    dp[1][1]=0.25;
    //for(int i=2;i<=1000;i++){
    //    dp[i][1]=(1+dp[i-1][1]*dp[i-1][1])/2;
    //}
    for(int i=1;i<=1000;i++){
        for(int j=1;j<=1000;j++) {
            ticket[i][j] = (dp[i - 1][j] + 1 - dp[i - 1][j - 1]) / 2;
            dp[i][j] = f(dp[i-1][j-1], dp[i-1][j], ticket[i][j]);
        }
    }

}

double draw_value(){
    random_device rd;
    // 使用随机数种子初始化伪随机数生成器
    mt19937 gen(rd());
    // 定义分布范围为[0, 1]之间的浮点数
    uniform_real_distribution<> dis(0.0, 1.0);

    // 生成随机数
   return  dis(gen);
}

double fixed_re(double *bits, int n, int k){
    int sale=0;
    double fix= fix_price(n,k);
    for(int i=0;i<n;i++){
        if(bits[i]>=fix){
            sale++;
        }
        if(sale>=k) break;
    }
    return fix* (double) sale;
}

double optimal_re(double *bits, int n, int k){
    double re=0;
    int sale=0;
    for(int i=0;i<n;i++){
        if(bits[i]>= ticket[n-i][k-sale]){
            re+=ticket[n-i][k-sale];
            sale++;
        }
        if(sale>=k) break;
    }
    return re;
}

void run(int n, int k){
    double re1=0, re2=0;
    for(int tt=0;tt<runningtime;tt++){
        double bits[n];
        for(int i=0;i<n;i++)    bits[i]=draw_value();
        re1+= fixed_re(bits,n,k);
        re2+= optimal_re(bits,n,k);
    }
//    cout<<setprecision(5)<<"For "<<n<<" customer and "<<k<<" ticket, using basic strategy with average revenue "
//    <<re1/runningtime<<", and using optimal strategy with average revenue "<<re2/runningtime<<",expect "<<dp[n][k]<<endl;
    cout<<n<<","<<k<<","<<re1/runningtime<<","<<re2/runningtime<<endl;
}



int main() {
    generate_price();
    for(int i=0;i<length(range_of_n);i++){
        for(int j=0;j<length(range_of_k);j++) {
            if(range_of_n[i]/2<range_of_k[j]) continue;
            run(range_of_n[i],range_of_k[j]);
        }
    }
//    cout << "   ";
//    for (int i = 0; i < 10; i++) {
//        cout << setw(10) << i << " ";
//    }
//    cout << endl;
//
//    for (int i = 0; i < 10; i++) {
//        cout << i << " ";
//        for (int j = 0; j < 10; j++)
//            cout << setw(10) << dp[i][j] << " ";
//        cout << endl;
//    }
    return 0;
}