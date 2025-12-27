#include <iostream>
#include <vector>
#include <algorithm>
#include <map>


using namespace std;

struct Edge {
    int u, v, id;
};

struct Node {
    int id;
    int degree;
    vector<int> edges;
};

int N, S, M, P;
vector<Edge> all_queries;
vector<int> ans;
vector<bool> visited_edge;
vector<int> edge_mapping;

void find_euler(int u, vector<vector<pair<int, int>>>& adj, vector<int>& tour, vector<bool>& used) {
    vector<int> stack;
    stack.push_back(u);
    
    while (!stack.empty()) {
        int curr = stack.back();
        if (adj[curr].empty()) {
            tour.push_back(curr);
            stack.pop_back();
        } else {
            pair<int, int> edge = adj[curr].back();
            adj[curr].pop_back();
            if (!used[edge.second]) {
                used[edge.second] = true;
                stack.push_back(edge.first);
                edge_mapping.push_back(edge.second); 
            }
        }
    }
}

void solve(vector<int>& edge_indices, int left_deg, int k_start, int k_end) {
    if (edge_indices.empty()) return;
    if (k_start == k_end) {
        for (int idx : edge_indices) {
            ans[all_queries[idx].id] = k_start;
        }
        return;
    }

    int max_node = 0;
    for (int idx : edge_indices) {
        max_node = max(max_node, max(all_queries[idx].u, all_queries[idx].v));
    }

    vector<vector<pair<int, int>>> adj(max_node + 1);
    vector<int> degree(max_node + 1, 0);

    for (int i = 0; i < edge_indices.size(); ++i) {
        int idx = edge_indices[i];
        int u = all_queries[idx].u;
        int v = all_queries[idx].v;
        adj[u].push_back({v, i}); 
        adj[v].push_back({u, i});
        degree[u]++;
        degree[v]++;
    }

    vector<int> l_edges, r_edges;
    vector<bool> local_used(edge_indices.size(), false);
    
    for (int i = 0; i <= max_node; ++i) {
        if (degree[i] % 2 != 0) {
            
        }
    }

    for (int i = 0; i <= max_node; ++i) {
        if (!adj[i].empty()) {
            vector<int> tour_nodes;
            edge_mapping.clear();
            
            vector<int> stack;
            stack.push_back(i);

            while(!stack.empty()){
                int u_curr = stack.back();
                bool found = false;
                while(!adj[u_curr].empty()){
                    pair<int,int> e = adj[u_curr].back();
                    adj[u_curr].pop_back();
                    if(!local_used[e.second]){
                        local_used[e.second] = true;
                        stack.push_back(e.first);
                        
                        if(l_edges.size() <= r_edges.size()) 
                            l_edges.push_back(edge_indices[e.second]);
                        else 
                            r_edges.push_back(edge_indices[e.second]);
                        found = true;
                        break;
                    }
                }
                if(!found){
                    stack.pop_back();
                }
            }
        }
    }

    int mid = k_start + (k_end - k_start) / 2;
    solve(l_edges, left_deg / 2, k_start, mid);
    solve(r_edges, left_deg / 2, mid + 1, k_end);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> N >> S >> M >> P)) return 0;
    
    int T;
    cin >> T; 
    while (T--) {
        int D; 
        cin >> D; 
        
        all_queries.clear();
        ans.resize(D);
        vector<int> indices;
        
        for (int i = 0; i < D; ++i) {
            int u_g, u_p, v_g, v_p;
            cin >> u_g >> u_p >> v_g >> v_p;
            
            all_queries.push_back({u_g, v_g + N, i});
            indices.push_back(i);
        }

        int max_deg = 0;
        map<int, int> deg_count;
        for(const auto& e : all_queries) {
            deg_count[e.u]++;
            deg_count[e.v]++;
        }
        for(auto const& [key, val] : deg_count) {
            max_deg = max(max_deg, val);
        }

        int k_pow2 = 1;
        while(k_pow2 < max_deg) k_pow2 *= 2;
        
        int dummy_idx = D;
        vector<int> current_indices = indices;
        
        solve(current_indices, k_pow2, 0, k_pow2 - 1);

        for (int i = 0; i < D; ++i) {
            int spine = ans[i];
            
            if (spine >= M) spine = 0; 
            cout << spine / (M/2) << " " << spine % (M/2) << "\n";
        }
    }
    return 0;
}