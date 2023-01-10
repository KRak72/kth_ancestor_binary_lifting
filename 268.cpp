#include<bits/stdc++.h>
using namespace std;
#define ll long long

void dfs(ll node,ll par,vector<ll>adj[],vector<vector<ll>>&up,ll level,vector<ll>&lvl){
  up[node][0]=par;
  lvl[node]=level;
  
  // 2^x = 2^(x-1) + 2^(x-1)
  for(ll i=1;i<20;i++){
    if(up[node][i-1]==-1){
      up[node][i]=-1;
    }
    else{
      up[node][i]= up[up[node][i-1]][i-1];
    }
    
  }

  for(auto it:adj[node]){
    if(it!=par){
    dfs(it,node,adj,up,level+1,lvl);
    }
  }

}

ll update(ll node,vector<vector<ll>> &up,ll k){
  for(ll i=19;i>=0;i--){
    if(1<<i & k){
      node=up[node][i];
    }
  }

  return node;
}

int main(){
  ll n,q;
  cin>>n>>q;

  vector<ll>adj[n+1];
  vector<ll>vec(n-1);

  for(ll i=0;i<n-1;i++){
    cin>>vec[i];
    adj[i+2].push_back(vec[i]);
    adj[vec[i]].push_back(i+2);
  }

  vector<vector<ll>>up(n+1,vector<ll>(20,-1));
  vector<ll>lvl(n+1,-1);
  dfs(1,-1,adj,up,0,lvl);
 

  while(q--){
    ll a,b;
    cin>>a>>b;

    if(lvl[a]-lvl[b]>=0){
      ll k=lvl[a]-lvl[b];
      a=update(a,up,k);

    }
    else{
      ll k=lvl[b]-lvl[a];
      b=update(b,up,k);
    }

    for(ll i=19;i>=0;i--){
      ll temp1=up[a][i];
      ll temp2=up[b][i];

      if(temp1!=temp2){
        a=temp1;
        b=temp2;
      }
    }
    
    if(a==b){
      cout<<a<<endl;
    }
    else{
    cout<<up[a][0]<<endl;
    }


  }

   return 0;
}