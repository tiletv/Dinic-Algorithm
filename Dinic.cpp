#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

struct edge{
	int v, rev;
	long long flow,cap;
	edge(int aa,int bb,long cc,long long dd) : v(aa),rev(bb),flow(cc),cap(dd) {}
};

template<int DN> struct Dinic{
	vector<edge> adj[DN];
	int level[DN];
	int used[DN];

	void addEdge(int u,int v,long long Cap){
		edge a(v,adj[v].size(),0,Cap);
		edge b(u,adj[u].size(),0,0);
		adj[u].push_back(a);
		adj[v].push_back(b);
	}

	bool bfs(int s,int t){
		for(int i = 0; i < DN; i++){
			level[i] = -1;
		}

		queue<int> q;
		level[s] = 0;
		q.push(s);
		while(!q.empty()){
			int u = q.front();
			q.pop();
			for(edge e: adj[u]){
				if(level[e.v]<0 && e.flow < e.cap){
					level[e.v] = level[u] + 1;
					q.push(e.v);
				}
			}
		}

		return level[t] >= 0;
	}

	long long dfs(int u,int t,long long flow){
		if(u==t){
			return flow;
		}

		for(int &i = used[u]; i < adj[u].size(); i++){
			edge &e = adj[u][i];
			if(level[e.v] == level[u]+1 && e.flow < e.cap){
				long long c_flow = dfs(e.v,t,min(flow,e.cap-e.flow));
				if(c_flow > 0){
					e.flow += c_flow;
					adj[e.v][e.rev].flow -=  c_flow;
					return c_flow;
				}
			}
		}

		return 0;
	}

	long long maxflow(int s,int t){
		if(s==t){
			return -1;
		}

		long long t_flow = 0;
		while(bfs(s,t)){
			for(int i = 0; i < DN; i++){
				used[i] = 0;
			}
			while(long long c_flow = dfs(s,t,INT_MAX)){
				t_flow += c_flow;
			}
		}

		return t_flow;
	}
};


int main(){
	Dinic<10> D;
	D = Dinic<10>();

    D.addEdge(0, 1, 16 ); 
    D.addEdge(0, 2, 13 ); 
    D.addEdge(1, 2, 10 ); 
    D.addEdge(1, 3, 12 ); 
    D.addEdge(2, 1, 4 ); 
    D.addEdge(2, 4, 14); 
    D.addEdge(3, 2, 9 ); 
    D.addEdge(3, 5, 20 ); 
   	D.addEdge(4, 3, 7 ); 
    D.addEdge(4, 5, 4); 

    cout << "Maximum flow " << D.maxflow(0, 5)<<endl;;

	return 0;
}