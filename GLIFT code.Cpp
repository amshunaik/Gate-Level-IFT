#include<iostream>
#include<bits/stdc++.h>
#include<map>
#include<vector>
using namespace std;
// code for truth table
int p;
int NOT(int a){
    return (!a);
}
int AND(int a,int b){
    return (a&&b);
}
int OR(int a,int b){
    return (a||b);
}
int XOR(int a,int b){
    if((a==0&&b==0)||(a==1&&b==1)){
        return 0;
    }
    else{
        return 1;
    }
}
int NAND(int a,int b){
    return !(a&&b);
}
int NOR(int a,int b){
    return !(a||b);
}
//code for getting tainted output for each gate
int tainted_NOT(int at){
    return at;
}
int tainted_AND(int a,int b,int at,int bt){
    p=((a&&bt)||(b&&at)||(at&&bt));
    return p;
}
int tainted_NAND(int a,int b,int at,int bt){
    p=((a&&bt)||(b&&at)||(at&&bt));
    return p;
}
int tainted_XOR(int a,int b,int at,int bt){
    return (at||bt);
}
int tainted_OR(int a,int b,int at,int bt){
    int a1,b1;
    a==0?a=1:a=0;
    b==0?b=1:b=0;
    
    p=((a&&bt)||(b&&at)||(bt&&at));
    return p;
}
int tainted_NOR(int a,int b,int at,int bt){
    int a1,b1;
    a==0?a=1:a=0;
    b==0?b=1:b=0;
    
    p=((a&&bt)||(b&&at)||(bt&&at));
    return p;
}
// code for getting output(o) and tainted output(ot).
//for NOT gate
int calc_not_o(string f2,string f3,string f4,map<string,int>uno){
    if(f3=="NOT"){
        return NOT(uno[f4]);
    }
}
int calc_not_ot(string f2,string f3,string f4,map<string,int>taint){
    if(f3=="NOT"){
        return tainted_NOT(taint[f4]);
    }
    
}
//other gates -AND,OR, XOR,NAND,NOR
int calc_o(string x,int x1,int x2){
    if(x=="AND"){
        return AND(x1,x2);
    }
    if(x=="OR"){
        return OR(x1,x2);
    }
    if(x=="XOR"){
        return XOR(x1,x2);
    }
    if(x=="NAND"){
        return NAND(x1,x2);
    }
    if(x=="NOR"){
        return NOR(x1,x2);
    }
}
int calc_ot(string x,int x1,int x2,int j2,int j3 ){
    if(x=="AND"){
        
        return tainted_AND(x1,x2,j2,j3);
    }
    if(x=="OR"){
        return tainted_OR(x1,x2,j2,j3);
    }
    if(x=="XOR"){
        return tainted_XOR(x1,x2,j2,j3);
    }
    if(x=="NAND"){
        return tainted_NAND(x1,x2,j2,j3);
    }
    if(x=="NOR"){
        return tainted_NOR(x1,x2,j2,j3);
    }
    //cout<<ot<<"\n";
    
}
//code of find position of string in vector<string>
int get(string s2,vector<string>l1){
    for(int i=0;i<l1.size();i++){
        if(s2==l1[i]){
            return i;
        }
    }
}
// bool function to find if string z present in vector<string> given in code
bool present(string z,vector<string>h){
    for(int i=0;i<h.size();i++){
        if(z==h[i]){
            true;
            break;
        }
        else{
            false;
        }
    }
}
//recursion loop to store values of string and o,ot in js and jn.
int u,v;
void rec(string s2,vector<string>js,vector<pair<int,int>>jn,vector<string>i1,map<string,int>m,vector<string>h1,map<string,int>uno,map<string,int>taint){
    if(!present(s2,i1)){
        //int y4=get(s2,i1);
        int y5=get(s2,h1);                             
        if((m[h1[y5+2]]==1)&&(m[h1[y5+3]]==1)){
            u=calc_o(h1[y5+1],uno[h1[y5+2]],uno[h1[y5+3]]);
            v=calc_ot(h1[y5+1],uno[h1[y5+2]],uno[h1[y5+3]],taint[h1[y5+2]],taint[h1[y5+3]]);             
            js.push_back(h1[y5]);
            jn.push_back(make_pair(u,v));
            m[h1[y5]]=-1;
            m[h1[y5+1]]=-1;
            m[h1[y5+2]]=-1;
            m[h1[y5+3]]=-1;                           
            
            
        }
      
        
        if((m[i1[y5+2]]==0)||(m[i1[y5+2]]==2)){
            rec(i1[y5+2],js,jn,i1,m,h1,uno,taint);
        }
        if(m[i1[y5+3]]==0||m[i1[y5+3]]==2){
            rec(i1[y5+3],js,jn,i1,m,h1,uno,taint);
        }
    }
}
 
// finding position of string 
int find(int h4,vector<string>o1,vector<string>js){
    for(int y4=0;y4<js.size();y4++){
        if(o1[h4]==js[y4]){
            return y4;
        }
    }
}


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
      
    string s;
    //input value from user
    vector<string>i1;
    for(int i=0;i<g;i++){
        cout<<"input-";
        cin>>s;
        i1.push_back(s);
    }
    //////////////////
    //output value from user
    int out;
    cin>>out;
    vector<string>o1;
    for(int i=0;i<out;i++){
        cout<<"output-";
        cin>>s;
        o1.push_back(s);
    }
    
    map<string,int>m;
    //no of not gates
    int invert;
    cout<<"inverters-";
    cin>>invert;
    invert=invert*3;
    //circuit involving not gates
    vector<string>vert;
    cout<<"invert circut-";
    for(int i=0;i<invert;i++){
      
        
        cin>>s;
        vert.push_back(s);
        if(present(s,i1)){
            m.insert({s,1});
        }
        if(present(s,o1)){
            m.insert({s,2});
        }
        else{
            m.insert({s,0});
        }
        //cout<<s<<" "<<m[s];
        //cout<<"\n";
    }
    ///////
    for(int i=0;i<vert.size();i++){
        cout<<vert[i]<<" ";
    }
    cout<<"\n";
    ////////
    // no of normal gates(in which not gate not present)
    int gates;
    cout<<"Gates-";
    cin>>gates;
    gates=gates*4;
    vector<string>h1;
    cout<<"normal gates-";
    for(int i=0;i<gates;i++){
       
        cin>>s;
        h1.push_back(s);
        if(present(s,i1)){
            m.insert({s,1});
        }
        if(present(s,o1)){
            m.insert({s,2});
        }
        else{
            m.insert({s,0});
        }
        //cout<<s<<" "<<m[s];
        //cout<<"\n";
    }
    for(int i=0;i<h1.size();i++){
        cout<<h1[i]<<" ";
    }
    cout<<"\n";
    
    
    int n=0;
    map<string,int>uno;
    map<string,int>taint;
    
    int w=0;
    for(int t1=0;t1<d;t1++){
        uno.clear();
        w=0;
        for(int t3=0;t3<g;t3++){
            uno.insert({i1[t3],a[t1][t3]});
        }
        for(int y=0;y<d;y++){
            cout<<"\n";
            taint.clear();
    
            
            
            while(w<w+1){
                for(int y1=0;y1<g;y1++){
                      taint.insert({i1[y1],a[w][y1]});
                }
                w++;
                break;
            }
            vector<string>js;
            vector<pair<int,int>>jn;
            ////////////////
            int o;
            int ot;
            for(int i=0;i<invert;i+=3){
                if(m[vert[i+2]]==1){
                    js.push_back(vert[i]);
                    
                    o=calc_not_o(vert[i],vert[i+1],vert[i+2],uno);
                    ot=calc_not_ot(vert[i],vert[i+1],vert[i+2],taint);
                    
                    jn.push_back(make_pair(o,ot));
                    m[vert[i]]=-1;
                    m[vert[i+1]]=1;
                    m[vert[i+2]]=1;
                }
                if(m[vert[i+2]]==0||m[vert[i+2]]==2){
                    rec(vert[i+2],js,jn,i1,m,h1,uno,taint);                                   
                    
                }
            }
            for(int i=0;i<gates;i+=4){
                
                if(m[h1[i+2]]==-1&&m[h1[i+3]]==1){
                    int w5=get(h1[i+2],js);
                    js.push_back(h1[i]);
                    o=calc_o (h1[i+1],jn[w5].first,uno[h1[i+3]]);
                    ot=calc_ot(h1[i+1],jn[w5].first,uno[h1[i+3]],jn[w5].second,taint[h1[i+3]]);
                    jn.push_back(make_pair(o,ot));
                                                                                                        
                }
                if(m[h1[i+3]]==-1&&m[h1[i+2]]==1){
                    int w5=get(h1[i+3],js);
                    js.push_back(h1[i]);
                    o=calc_o(h1[i+1],uno[h1[i+2]],jn[w5].first);
                    ot=calc_ot(h1[i+1],uno[h1[i+2]],jn[w5].first,taint[h1[i+2]],jn[w5].second);
                    jn.push_back(make_pair(o,ot));
                }
                if(m[h1[i+2]]==-1&&m[h1[i+3]]==-1){
                    int w5=get(h1[i+2],js);
                    int w6=get(h1[i+3],js);
                    js.push_back(h1[i]);
                    o=calc_o (h1[i+1],jn[w5].first,jn[w6].first);
                    ot=calc_ot(h1[i+1],jn[w5].first,jn[w6].first,jn[w5].second,jn[w6].second);
                    jn.push_back(make_pair(o,ot));
                                                                                                        
                }
                
                if(m[h1[i+2]]==1&&m[h1[i+3]]==1){
                    js.push_back(h1[i]);
                    o=calc_o(h1[i+1],uno[h1[i+2]],uno[h1[i+3]]);
                    ot=calc_ot(h1[i+1],uno[h1[i+2]],uno[h1[i+3]],taint[h1[i+2]],taint[h1[i+3]]);
                    jn.push_back(make_pair(o,ot));
                    m[h1[i]]=-1;
                    m[h1[i+1]]=1;                                    
                    m[h1[i+2]]=1;
                    m[h1[i+3]]=1;
                }
                
                
                if((m[h1[i+2]]==0||m[h1[i+2]]==2)){
                    
                    rec(h1[i+2],js,jn,i1,m,h1,uno,taint);
                }
                if(m[h1[i+3]]==0||m[h1[i+3]]==2){
                    rec(h1[i+3],js,jn,i1,m,h1,uno,taint);
                    
                }
                
            }
            for(int h2=0;h2<g;h2++){
                cout<<uno[i1[h2]]<<" ";
            }
            for(int h3=0;h3<g;h3++){
                cout<<taint[i1[h3]]<<" ";
            }
            for(int h4=0;h4<out;h4++){
                int q4=find(h4,o1,js);
                cout<<jn[q4].first<<" "<<jn[q4].second<<" ";
            }
            cout<<"\n";
        }
    }
}
