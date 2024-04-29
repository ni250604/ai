#include <bits/stdc++.h> 
using namespace std; 


void selectionSort() 
{ 
	int n;
	cout<<"Enter no of elements :";
	cin>>n;
	vector<int> arr(n);
	cout<<"Enter the elements :";
	for(int i=0; i<n; i++)  cin>>arr[i];
	int i, j, min_idx; 
	for (i = 0; i < n - 1; i++) { 
		min_idx = i; 
		for (j = i + 1; j < n; j++) { 
			if (arr[j] < arr[min_idx]) 				min_idx = j; 
		} 
		if (min_idx != i) 			swap(arr[min_idx], arr[i]); 
	} 
	cout<<"Sorted array :";
	for (i = 0; i < n; i++) 		cout << arr[i] << " "; 
	cout<<endl;
} 

int minKey(int key[], bool mstSet[], int n)
{
    int min = INT_MAX, min_index;
 
    for (int i = 0; i < n; i++)
        if (mstSet[i] == false && key[i] < min)            min = key[i], min_index = i;
    return min_index;
}

void Prims(){
	// int n;;
	// cout<<"Enter no of node :";
	// cin>>n;
	// int parent[n];
    // int key[n];
    // bool mstSet[n];
	// int graph[n][n]= { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
    //                    { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
	// 				   { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
	// 				   { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
	// 				   { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
	// 				   { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
	// 				   { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
	// 				   { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
	// 				   { 0, 0, 2, 0, 0, 0, 6, 7, 0 },
    //                     };

    int n,m,x,y,wt;
    cout<<"Enter no of nodes, Edges: ";
    cin>>n>>m;
    cout<<"Enter edge,weight: ";
    vector<vector<int>> graph(n,vector<int>(n,0));
    int parent[n];
    int key[n];
    bool mstSet[n];
    for(int i=0;i<m;i++){
        cin>>x>>y>>wt;
        graph[x][y]=wt;
        graph[y][x]=wt;
    }
 
    for (int i = 0; i < n; i++)        key[i] = INT_MAX, mstSet[i] = false;
    key[0] = 0;
    parent[0] = -1;
 
    for (int count = 0; count < n - 1; count++) {
        int u = minKey(key, mstSet, n);
        mstSet[u] = true;
		//path[count]=u;

        for (int i = 0; i < n; i++){
			if (graph[u][i] && mstSet[i] == false && graph[u][i] < key[i])
                parent[i] = u, key[i] = graph[u][i];
		}
            
    }
	//for(auto it:path)	cout<<it<<"->";
	cout<<endl;
	int cost=0;

    cout << "Edge \tWeight\n";
    for (int i = 1; i < n; i++){
		cout << parent[i] << " - " << i << " \t"<< graph[i][parent[i]] << " \n";
		cost+=graph[i][parent[i]];
	}
	cout<<"Min_cost = "<<cost<<endl;
        
}

const int MAX = 1e6-1;
int root[MAX];
pair <long long, pair<int, int> > p[MAX];

int parent(int a)                                                       
{
    while(root[a] != a)
    {
        root[a] = root[root[a]];
        a = root[a];
    }
    return a;
}

void union_find(int a, int b)                                         
{
    int d = parent(a);
    int e = parent(b);
    root[d] = root[e];
}


void Kruskal(){
    //const int nodes = 4, edges = 5;
    int nodes,edges,start,end,weight;
    cout<<"Enter no of nodes, Edges: ";
    cin>>nodes>>edges;

	//int x, y;
    //long long weight;
    for(int i = 0;i < MAX;++i)              root[i] = i;

    cout<<"Enter weight, Edge:\n";
    for(int i=0;i<edges; i++){
        cin>>weight>>start>>end;
        p[i]={weight,{start,end}};
    }
    
    // p[0] = make_pair(10, make_pair(0, 1));
    // p[1] = make_pair(18, make_pair(1, 2));
    // p[2] = make_pair(13, make_pair(2, 3));
    // p[3] = make_pair(21, make_pair(0, 2));
    // p[4] = make_pair(22, make_pair(1, 3));
    sort(p, p + edges);                                             
    
	int a, b;
    long long cost, minCost = 0;
    for(int i = 0 ; i < edges ; ++i)
    {
        a = p[i].second.first;
        b = p[i].second.second;
        cost = p[i].first;
        if(parent(a) != parent(b))                                  
        {
            minCost += cost;
            union_find(a, b);
        }
    }
	cout<<"Min_cost = "<<minCost<<endl;
}

int const N=1e5;
vector<pair<int,int>>g[N];
int ar[N];
int mod=1000000007;
const int INF=1e9+10;

void Dijkstra(){
	int n,m;
	cout<<"No of nodes, edges: ";
    cin>>n>>m;
	cout<<"Enter edge, weight :";
    for(int i=0;i<m;i++){
        int x,y,wt;
        cin>>x>>y>>wt;
        g[x].push_back({y,wt});
        g[y].push_back({x,wt});
    }
	int s=1;

	vector<int>vis(N,0);
    vector<int>dist(N,INF);
    multiset<pair<int,int>>st;
    st.insert({0,s});
    dist[s]=0;
 
    while(st.size()>0){
        auto it=*(st.begin());
        int v=it.second;
        int d=it.first;
        st.erase(st.begin());
        if(vis[v]) continue;
        vis[v]=1;
        for(auto c : g[v]){
            int c_v=c.first;
            int wt=c.second;
            if(dist[v]+wt<dist[c_v]){
                dist[c_v]=dist[v]+wt;
                st.insert({dist[c_v],c_v});  
            }
        }
        
    }
    for(int i =1;i<=n;i++){
        cout<<"distance between "<<s<<" and "<<i<<" is "<<dist[i]<<endl;
    }
}


int main() 
{
	int choice;
	while(1){

		cout<<"\n1.selection sort\n2.Prims\n3.Kruskal\n4.Dijkstra\n\nEnter choice :";
		cin>>choice;
		switch(choice){
			case 1:		
				selectionSort();  
				break;
			case 2:
				Prims();
				break;
			case 3:
				Kruskal();
				break;
			case 4:
				Dijkstra();
				break;
			default: 
				break;
		}
	}
	return 0; 
} 

