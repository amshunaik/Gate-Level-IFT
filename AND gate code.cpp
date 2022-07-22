#include<iostream>
#include<bits/stdc++.h>
#include<map>
using namespace std;

// getting output ot
int tainted(int a,int b,int at,int bt){
    
    if(a==1&&bt==1){
        return 1;
    }
    else if(b==1&&at==1){
        return 1;
    }
    else if(at==1&&bt==1){
        return 1;
    }
    else{
        return 0;
    }
}
//AND gate truth table.
//for getting output o
int land(int a,int b){
    if(a==1&&b==1){
        return 1;
    }
    else{
        return 0;
    }
}


int main(){
    // taing input a,b,at,bt;
    int a,b;
    cin>>a>>b;
    int at,bt;
    cin>>at>>bt;
    int o= land(a,b);
    int ot=tainted(a,b,at,bt);
    
    // created a map of vector and int
    //int vector stored {a,b,at,bt,o} and int int -value of ot.
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