#include<bits/stdc++.h>
using namespace std;
int lor(int a,int b){
    if(a==0&&b==0){
        return 0;
    }
    else{
        return 1;
    }
}
int tainted(int a,int b,int at,int bt){
    int a1,b1;
    if(a==0){
        a1=1;
    }
    else{
        a1=0;
    }
    if(b==0){
        b1=1;
    }
    else{
        b1=0;
    }
    int p=a1*bt+b1*at+bt*at;
    if(p>0){
        return 1;
    }
    else{
        return 0;
    }
}
int main(){
    int a,b,at,bt;
    cin>>a>>b>>at>>bt;
    int o=lor(a,b);
    int ot=tainted(a,b,at,bt);
    map<vector<int>,int>m;
    m.insert({{a,b,at,bt,o},ot});
    
    //printing the output.
    for(auto it=m.begin();it!=m.end();it++){
        
        for(auto u=it->first.begin();u!=it->first.end();u++){
            cout<<*u;
        }
        cout<<" ";
        cout<<it->second<<" ";  
    }
    
}

