#include <iostream>
#include<vector>
using namespace std;
const int INF = 1e9;

/*
// Anna, Slyatoans and map
void test01() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // Nhập ma trận kề
    vector<vector<int>> graph(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for (int j = 1; j <= n; j++) {
            graph[i][j] = (s[j - 1] == '1') ? 1 : INF;
        }
        graph[i][i] = 0;
    }

    // Floyd-Warshall: tính khoảng cách ngắn nhất giữa mọi cặp đỉnh
    vector<vector<int>> dist = graph;
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    // Nhập đường đi p
    int m;
    cin >> m;
    vector<int> p(m);
    for (int i = 0; i < m; i++) cin >> p[i];

    // Rút gọn p thành dãy con tốt ngắn nhất
    vector<int> v;
    v.push_back(p[0]);
    int last_idx = 0; // vị trí đỉnh cuối cùng được giữ trong v

    for (int i = 1; i < m; i++) {
        // Khoảng cách thực tế trong p
        int actual_steps = i - last_idx;
        // Khoảng cách ngắn nhất trong đồ thị
        int shortest = dist[p[last_idx]][p[i]];

        if (actual_steps > shortest) {
            // Đỉnh trước đó bắt buộc giữ
            v.push_back(p[i - 1]);
            last_idx = i - 1;
        }
    }

    // Luôn thêm đỉnh cuối
    if (v.back() != p[m - 1]) v.push_back(p[m - 1]);

    // In kết quả
    cout << v.size() << "\n";
    for (int i = 0; i < v.size(); i++) {
        if (i > 0) cout << " ";
        cout << v[i];
    }
    cout << "\n";

    
}







struct Cell {
    int x, y;
};

int dx[8] = { -1,-1,-1,0,0,1,1,1 };
int dy[8] = { -1,0,1,-1,1,-1,0,1 };
void test02() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long x0, y0, x1, y1;
    cin >> x0 >> y0 >> x1 >> y1;

    int n;
    cin >> n;

    vector<Cell> allowed;
    for (int i = 0; i < n; i++) {
        long long r, a, b;
        cin >> r >> a >> b;
        for (long long c = a; c <= b; c++) {
            allowed.push_back({ (int)r, (int)c });
        }
    }

    int S = allowed.size();
    vector<vector<int>> neighbors(S);

    // Tạo danh sách kề: hai ô kề nhau nếu cách ≤1 hàng và ≤1 cột
    for (int i = 0; i < S; i++) {
        for (int j = i + 1; j < S; j++) {
            if (abs(allowed[i].x - allowed[j].x) <= 1 && abs(allowed[i].y - allowed[j].y) <= 1) {
                neighbors[i].push_back(j);
                neighbors[j].push_back(i);
            }
        }
    }

    // Tìm chỉ số ô bắt đầu và kết thúc
    int start_idx = -1, end_idx = -1;
    for (int i = 0; i < S; i++) {
        if (allowed[i].x == x0 && allowed[i].y == y0) start_idx = i;
        if (allowed[i].x == x1 && allowed[i].y == y1) end_idx = i;
    }

    if (start_idx == -1 || end_idx == -1) {
        cout << -1 << "\n";
        return ;
    }

    // BFS
    vector<int> dist(S, -1);
    vector<int> visited(S, 0);
    vector<int> q;
    int head = 0;

    q.push_back(start_idx);
    visited[start_idx] = 1;
    dist[start_idx] = 0;

    while (head < q.size()) {
        int curr = q[head++];
        if (curr == end_idx) break;

        for (int i = 0; i < neighbors[curr].size(); i++) {
            int nxt = neighbors[curr][i];
            if (!visited[nxt]) {
                visited[nxt] = 1;
                dist[nxt] = dist[curr] + 1;
                q.push_back(nxt);
            }
        }
    }

    cout << dist[end_idx] << "\n"; // -1 nếu không đến được
}










//  Road in Berland
void test03(){
 ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // Nhập ma trận khoảng cách ban đầu
    vector<vector<int>> d(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> d[i][j];

    int k;
    cin >> k;

    vector<int> a(k), b(k), c(k);
    for (int i = 0; i < k; i++) {
        cin >> a[i] >> b[i] >> c[i];
        a[i]--; // chuyển về index 0-based
        b[i]--;
    }

    // Tính tổng khoảng cách ban đầu giữa tất cả cặp i<j
    long long total = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            total += d[i][j];

    vector<long long> res; // lưu kết quả sau mỗi đường

    // Xử lý từng con đường mới
    for (int road = 0; road < k; road++) {
        int u = a[road];
        int v = b[road];
        int w = c[road];

        // Cập nhật ma trận khoảng cách nếu đường mới rút ngắn đường đi
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int newDist = d[i][j];
                newDist = min(newDist, d[i][u] + w + d[v][j]);
                newDist = min(newDist, d[i][v] + w + d[u][j]);

                if (newDist < d[i][j]) {
                    total -= (d[i][j] - newDist); // trừ phần giảm
                    d[i][j] = d[j][i] = newDist; // cập nhật
                }
            }
        }

        res.push_back(total); // lưu tổng sau đường này
    }

    // In kết quả
    for (size_t i = 0; i < res.size(); i++) {
        if (i > 0) cout << " ";
        cout << res[i];
    }
    cout << "\n";


}

// Greg Graph
void test03(){
 ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<vector<long long>> adj(n, vector<long long>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> adj[i][j];
        }
    }

    vector<int> order(n);
    for (int i = 0; i < n; i++) {
        cin >> order[i];
        order[i]--; // Convert to 0-indexed
    }

    vector<long long> results;
    vector<bool> active(n, false);
    vector<vector<long long>> dist = adj;

    // Process in reverse order
    for (int step = n - 1; step >= 0; step--) {
        int k = order[step];
        active[k] = true;

        // Update shortest paths using vertex k as intermediate
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }

        // Calculate sum of shortest paths between active vertices
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            if (!active[i]) continue;
            for (int j = 0; j < n; j++) {
                if (!active[j]) continue;
                sum += dist[i][j];
            }
        }

        results.push_back(sum);
    }

    // Print results in reverse order
    for (int i = n - 1; i >= 0; i--) {
        cout << results[i];
        if (i > 0) cout << " ";
    }
    cout << endl;

}
*/
// King path
void test02() {
    int x0, y0, x1, y1;
    cin >> x0 >> y0 >> x1 >> y1;

    int n;
    cin >> n;

    vector<pair<int, int>> allowed;

    for (int i = 0; i < n; i++) {
        int r, a, b;
        cin >> r >> a >> b;
        for (int j = a; j <= b; j++) {
            allowed.push_back(make_pair(r, j));
        }
    }

    vector<pair<pair<int, int>, int>> queue;
    vector<pair<int, int>> visited;

    queue.push_back(make_pair(make_pair(x0, y0), 0));
    visited.push_back(make_pair(x0, y0));

    int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    for (int idx = 0; idx < queue.size(); idx++) {
        int x = queue[idx].first.first;
        int y = queue[idx].first.second;
        int dist = queue[idx].second;

        if (x == x1 && y == y1) {
            cout << dist << endl;
            return 0;
        }

        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            bool ok = false;
            for (int j = 0; j < allowed.size(); j++) {
                if (allowed[j].first == nx && allowed[j].second == ny) {
                    ok = true;
                    break;
                }
            }
            if (!ok) continue;

            bool vis = false;
            for (int j = 0; j < visited.size(); j++) {
                if (visited[j].first == nx && visited[j].second == ny) {
                    vis = true;
                    break;
                }
            }
            if (vis) continue;

            visited.push_back(make_pair(nx, ny));
            queue.push_back(make_pair(make_pair(nx, ny), dist + 1));
        }
    }

    cout << -1 << endl;

}


int main() {
 
    return 0;
}