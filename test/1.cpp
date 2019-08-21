#include<vector>
#include<iostream>

using namespace std;

vector<int> spiralOrder(const vector<vector<int> > &A) {
    int m=A.size(),n=A[0].size();
    vector<int> v;
    int L=0,R=n-1,U=0,D=m-1;
    int dir = 0;
    
    while(L<=R && U<=D){
        if(dir==0){
            for(int i=L;i<=R;i++){
                v.push_back(A[U][i]);
            }
            U++;
        }
        if(dir==1){
            for(int i=U;i<=D;i++){
                v.push_back(A[i][R]);
            }
            R--;
        }
        if(dir==2){
            for(int i=R;i>=L;i--){
                v.push_back(A[D][i]);
            }
            D--;
        }
        if(dir==3){
            for(int i=D;i>=U;i--){
                v.push_back(A[i][L]);
            }
            L++;
        }
        dir+=1;
        dir%=4;
    }
}


int main(){
    int x,y,p,q;
    cin>>x>>y;

    vector<vector<int>> v;
    int a[x*y];
    v.resize(x);
    for(p=0;p<x;p++){
        v[p].resize(y);
        for(q=0;q<y;q++){
            cin>>v[p][q];
        }
    }
    vector<int> s=spiralOrder(v);
    return 0;
}

