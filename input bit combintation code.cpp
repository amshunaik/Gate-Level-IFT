
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int main(){
    int g;
    cin>>g;
    
    int c=pow(2,g);
    int d=c;
    vector<int>v{0,1};
    //cout<<c<<"\n";
    int h=0;
    int a[c][g];
    int x=0;
    for(int i=0;i<g;i++){
        c=c/2;
        //cout<<c<<"\n";
        
        int j=0;
        while(x<c&&j<d){
          if(h%2==0){
            a[j][i]=v[0];
            j++;
          }
          else{
            a[j][i]=v[1];
            j++;
          }
          if(x<c){
            x++;
          }
          if(x>=c){
            x=0;
            h++;
          }
          
          
        }
    }
    for(int i=0;i<d;i++){
       for(int j=0;j<g;j++){
        
          cout<<a[i][j]<<" ";
       }
       cout<<"\n";
    }
    
    cout<<"\n";
    vector<int>uno;
    vector<int>taint;
    int w=0;
    for(int t1=0;t1<d;t1++){
        uno.clear();
        int i=0;
        for(int t3=0;t3<g;t3++){
            uno.push_back(a[t1][t3]);
        }
        for(int y=0;y<d;y++){
            cout<<"\n";
            taint.clear();
    
            
            
            while(i<i+1){
                for(int j=0;j<g;j++){
                  taint.push_back(a[i][j]);
                }
                i++;
                break;
            }
            
        
            for(int h2=0;h2<g;h2++){
                cout<<uno[h2]<<" ";
                
            }
            //cout<<"\n";
            for(int y1=0;y1<g;y1++){
                cout<<taint[y1]<<" ";
            }
            cout<<"\n";
        }
    }
}





