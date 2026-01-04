#include <iostream>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

// Sort
// Quick Sort
int partition(int a[], int l, int r) {
    // Bước 1: Tìm  pivot và i
    int pivot = a[r];
    int i = l - 1;

    // Bước 2: Duyệt trong mảng kiểm tra phần tử nào nhỏ hơn pivot thì đổi chỗ ++i
    for (int j = l; j < r; j++)
        if (a[j] <= pivot)
            swap(a[++i], a[j]);

    // Bước 3: Đổi chỗ pivot với phần tử i+1
    swap(a[i + 1], a[r]);
    return i + 1;
}

void quickSort(int a[], int l, int r) {
    if (l < r) {
        int p = partition(a, l, r);
        quickSort(a, l, p - 1);
        quickSort(a, p + 1, r);
    }
}

// Merge Sort

void merge(int a[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Mảng tạm
    int* L = new int[n1];
    int* R = new int[n2];

    // Sao chép dữ liệu
    for (int i = 0; i < n1; i++)
        L[i] = a[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = a[mid + 1 + j];

    int i = 0, j = 0, k = left;

    // Trộn lại vào mảng a
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }

    // Sao chép phần còn lại
    while (i < n1)
        a[k++] = L[i++];
    while (j < n2)
        a[k++] = R[j++];
}

// Hàm Merge Sort
void mergeSort(int a[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(a, left, mid);
        mergeSort(a, mid + 1, right);

        merge(a, left, mid, right);
    }
}

// Bảng băm

long long hashString(const char* s) {
    // Bước 1: Khai báo hằng số
    const long long M = 1000000009;
    const long long p = 31;

    // Bước 2: Khai báo giá trị hashvalue và p_pow
    long long hashvalue = 0;
    long long p_pow = 1;

    // Bước 3: Duyệt từng phần từ  và cộng dồn
    for (int i = 0; s[i] != '\0'; i++) {
        hashvalue = (hashvalue + (s[i] * p_pow) % M) % M;
        p_pow = (p_pow * p) % M;
    }

    // Bước 4: Trả về từng hashValue ko âm
    return (hashvalue + M) % M;
}

void Insert(vector<char*>& table, int n, const char* s) {
    // Bước 1: Tìm vị trí index trong bảng
    int index = hashString(s) % n;
    int start = index;

    // Bước 2: Dùng while kiểm tra xem vị trí đó có trống ko, và vị trí đó đã được chèn chưa

    while (table[index] != nullptr &&
        strcmp(table[index], s) != 0) {

        index = (index + 1) % n;
        if (index == start)
            return; // bảng đầy
    }

    // Bước 3: Nếu vị trí đó trống thì chèn vào vị trí đó
    if (table[index] == nullptr) {
        table[index] = new char[strlen(s) + 1];
        strcpy_s(table[index], strlen(s) + 1, s);
    }
}

int Search(vector<char*>& table, int n, const char* s) {
   // Bước 1: Tìm index
    int index = hashString(s) % n;
    int start = index;

    // Bước 2: Kiểm tra xem vị trí đó có trống ko, 
    while (table[index] != nullptr) {
        // Kiểm tra xem vị trí đó có giống kết quả cần tìm ko
        if (strcmp(table[index], s) == 0)
            return index;

        index = (index + 1) % n;

        if (index == start)
            break;
    }
    return -1;
}

vector<char*> createHashTable(vector<char*>& input, int n) {
    // Bước 1: Khởi tạo bảng có giá trị NULL
    vector<char*> table(n, nullptr);
    // Bước 2: Thêm từng phần tử char* vào bảng băm
    for (char* s : input) {
        Insert(table, n, s);
    }
    // Trả về bảng băm
    return table;
}
char* to_String(int n) {
    if (n == 0) {
        char* s = new char[2];
        s[0] = '0'; s[1] = '\0';
        return s;
    }

    char tmp[20];
    int len = 0;

    while (n > 0) {
        tmp[len++] = char('0' + n % 10);
        n /= 10;
    }

    char* res = new char[len + 1];
    for (int i = 0; i < len; i++)
        res[i] = tmp[len - 1 - i];

    res[len] = '\0';
    return res;
}
// Đồ thị
// Dijkstra cơ bản
void dijkstra(int start, const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX); // khoảng cách từ start
    vector<bool> visited(n, false); // đã duyệt chưa
    vector<int> parent(n, -1); // để lưu đường đi

    dist[start] = 0;

    for (int i = 0; i < n; i++) {
        // Tìm đỉnh chưa duyệt có khoảng cách nhỏ nhất
        int u = -1;
        int minDist = INT_MAX;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }

        if (u == -1) break; // không còn đỉnh nào

        visited[u] = true;

        // Cập nhật khoảng cách các đỉnh kề
        for (int v = 0; v < n; v++) {
            if (graph[u][v] > 0 && !visited[v]) { // có cạnh u->v
                if (dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    // In khoảng cách
    cout << "Khoang cach tu dinh " << start << " den cac dinh:\n";
    for (int i = 0; i < n; i++) {
        if (dist[i] == INT_MAX)
            cout << "Dinh " << i << ": khong the den\n";
        else
            cout << "Dinh " << i << ": " << dist[i] << "\n";
    }

    // In đường đi
    cout << "\nDuong di ngan nhat:\n";
    for (int i = 0; i < n; i++) {
        if (i == start || dist[i] == INT_MAX) continue;
        cout << "Tu " << start << " den " << i << ": ";
        vector<int> path;
        for (int v = i; v != -1; v = parent[v]) path.push_back(v);
        for (int j = path.size() - 1; j >= 0; j--) {
            cout << path[j];
            if (j > 0) cout << " -> ";
        }
        cout << "\n";
    }
}

/*



// Bước 1: Định nghĩa cạnh trong danh sách kề
struct Edge {
    int to;
    long long weight;
};
// Bước 2: Định nghĩa node trong Heap
struct HeapNode {
    int vertex;
    long long dist;
};
// Bước 3: Định nghĩa MinHeap với 4 phương thức: Khởi tạo, empty, push, pop
class MinHeap {
public:
    // Bước 3.1: Core của heap là một vector
    vector<HeapNode> heap;
    // Bước 3.2: Định nghĩa phương thức khởi tạo để tạo 1 base-index

    MinHeap() {
        heap.push_back({ 0, 0 }); // dummy node để 1-based index
    }
    // Bước 3.3: Viết phương thức empty kết hợp với kiểm tra kích thước cả 1-based index
    bool empty() {
        return heap.size() == 1;
    }
    // Bước 3.4: Viết phương thức push ( thêm vào sau và swap ra đằng trước)
    void push(HeapNode node) {
        heap.push_back(node);
        int i = heap.size() - 1;
        while (i > 1 && heap[i].dist < heap[i / 2].dist) {
            swap(heap[i], heap[i / 2]);
            i /= 2;
        }
    }
    // Bước 3.5: Viết phương thức pop ( lấy phần tử số 1 ra rồi  rồi swap ra sau)
    HeapNode pop() {
        HeapNode top = heap[1];
        heap[1] = heap.back();
        heap.pop_back();
        int i = 1;
        while (true) {
            int left = i * 2;
            int right = i * 2 + 1;
            int smallest = i;
            if (left < heap.size() && heap[left].dist < heap[smallest].dist)
                smallest = left;
            if (right < heap.size() && heap[right].dist < heap[smallest].dist)
                smallest = right;
            if (smallest == i) break;
            swap(heap[i], heap[smallest]);
            i = smallest;
        }
        return top;
    }
};
*/

struct Edge {
    int to;
    long long weight;
};
struct HeapNode {
    int vertex;
    long long dist;
};

class MinHeap {
public:
    vector<HeapNode>heap;

    MinHeap() {
        heap.push_back({ 0,0 });
    }

    bool empty() {
        return heap.size() == 1;
    }

    void push(HeapNode s) {
        heap.push_back(s);
        int i = heap.size() - 1;

        while (i > 1 && heap[i].dist < heap[i / 2].dist) {
            swap(heap[i], heap[i / 2]);
            i = i / 2;
        }

    }

    HeapNode pop() {
        HeapNode top = heap[1];
        heap[1] = heap.back();
        heap.pop_back();

        int i = 1;
        while (true) {
            int left = i * 2;
            int right = 2 * i + 1;
            int smallest = i;

            if (left < heap.size() && heap[left].dist < heap[smallest].dist) {
                smallest = left;
            }
            if (right < heap.size() && heap[right].dist < heap[smallest].dist) {
                smallest = right;
            }
            if (smallest == i) break;

            swap(heap[smallest], heap[i]);
            i = smallest;
        }
        return top;
    }
};
/*


void test01() {
    // Bước 1: Khởi tạo biến để lưu những con số tổng quát
    int n, m, s;
    cin >> n >> m >> s;
    // Bước 2: Nhận dữ liệu đầu vào và lưu vào danh sách kề
    vector<vector<Edge>> graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        graph[u].push_back({ v, w });
    }

    // Bước 3: Khởi tạo vector để lưu khoảng cách hiện tại từ đỉnh s đến đỉnh hiện tại
    const long long INF = 1e18;
    vector<long long> dist(n + 1, INF);
    dist[s] = 0;

    // Bước 4: Khởi tạo MinHeap và thêm phần tử đầu tiên vào
    MinHeap pq;
    pq.push({ s, 0 });

    // Bước 5: Bắt đầu chạy while và thực hiện thuật toán
    while (!pq.empty()) {
        // Bước 5.1: Lấy từng phần tử đầu tiên ra
        HeapNode node = pq.pop();
        int u = node.vertex;
        long long d = node.dist;

        //Bước 5.2: Kiểm tra xem node đó đã cũ chưa
        if (d > dist[u]) continue; // bỏ qua node cũ hơn

        // Bước 5.3: Duyệt qua những phần tử đính với đỉnh top đó, cập nhật trọng số min và thêm vào MinHeap
        for (auto e : graph[u]) {
            int v = e.to;
            long long w = e.weight;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({ v, dist[v] });
            }
        }
    }
    //Bước 6: Duyệt qua từng đỉnh và in ra khoảng cách từ s đến đỉnh đó
    for (int i = 1; i <= n; ++i) {
        if (dist[i] == INF) cout << -1 << " ";
        else cout << dist[i] << " ";
    }
    cout << endl;
}
*/
void test01() {
    int n, m, s;
    cin >> n >> m >> s;
    
    vector<vector<Edge>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        graph[u].push_back({ v,w });
    }

    const long long INF = 1e18;
    vector<long long > dist(n + 1,INF);

    dist[s] = 0;
    MinHeap pq;
    pq.push({ s,0 });

    while (!pq.empty()) {
        HeapNode node = pq.pop();
        int u = node.vertex;
        long long d = node.dist;

        if (d > dist[u]) continue;

        for (auto e : graph[u]) {
            int v = e.to;
            long long w = e.weight;

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({ v,dist[v] });
            }
        }
    }


    for (int i = 1; i <= n; i++) {
    
        if (dist[i] == INF) cout << -1 << " ";
        else cout << dist[i] << " ";
    
    }
}
/*
void test02() {
    // Bước 1: Khởi tạo biến để nhận các tham số tổng quát
    int n, m, s;
    cin >> n >> m >> s;
    
    // Bước 2: Khởi tạo danh sách kề để nhận các dữ liệu đầu vào
    vector<vector<Edge>> graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        graph[u].push_back({ v, w });
        graph[v].push_back({ u, w }); // vì vô hướng
    }
    // Bước 3: Khởi tạo minCost để lưu giá trị nhỏ nhất của 1 đỉnh để thêm vào cây khung. Đồng thời khởi tạo mảng kiểm tra xem đã ở trong cây khung chưa
    const long long INF = 1e18;
    vector<long long> minCost(n + 1, INF);
    vector<bool> inMST(n + 1, false);

    // Bước 4: Khởi tạo MinHeap và thêm phần tử đầu tiên vào MinHeap
    minCost[s] = 0;
    MinHeap pq;
    pq.push({ s, 0 });

    //Bước 6: Tạo biến để đếm tổng weight  và số lượng đỉnh
    long long totalWeight = 0;
    int count = 0; // đếm số đỉnh trong MST


    // Bước 7: Thực hiện thuật toán Prim để tìm cây khung nhỏ nhất
    while (!pq.empty()) {
        // Bước 7.1: Lấy phần tử đầu tiên ra
        HeapNode node = pq.pop();
        int u = node.vertex;
        long long cost = node.dist;
        // Bước 7.2: Kiểm tra xem đã nằm trong cây khung chưa
        if (inMST[u]) continue;
        // Bước 7.3: Thêm vào cây khung và tăng số lượng các biến đếm
        inMST[u] = true;
        totalWeight += cost;
        count++;
        // Bước 7.4: Duyêt qua từng phần tử đính với đỉnh hiện tại,  nếu nó chưa nằm trong cây khung và và giá trị cost  > w thực của nó thì thêm vào MinHeap
        for (auto e : graph[u]) {
            int v = e.to;
            long long w = e.weight;
            if (!inMST[v] && minCost[v] > w) {
                minCost[v] = w;
                pq.push({ v, w });
            }
        }
    }
    // Bước 8: In ra các giá trị tổng
    if (count == n) cout << totalWeight << endl;
    else cout << -1 << endl; // đồ thị không liên thông
}
*/
void test02() {
    int n, m,s;
    cin >> n >> m >> s;

    vector<vector<Edge>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        graph[u].push_back({ v,w });
        graph[v].push_back({ u,w });
    }

    const long long INF = 1e18;
    vector<long long> minCost(n + 1, INF);
    vector<bool>inMST(n + 1, false);

    minCost[s] = 0;
    MinHeap pq;
    pq.push({ s,0 });

    long long totalCost = 0;
    int count = 0;

    while (!pq.empty()) {
        HeapNode node = pq.pop();
        int u = node.vertex;
        long long d = node.dist;

        if (inMST[u]) continue;

        inMST[u] = true;
        totalCost += d;
        count++;

        for (auto e : graph[u]) {
            int v = e.to;
            long long w = e.weight;
            if (!inMST[v] && minCost[v] > w) {
                minCost[v] = w;
                pq.push({ v,minCost[v] });
            }
        }
    }

    if (count == n) cout << totalCost << " ";
    else cout << -1;

}
/*
void test04() {
    int n, m;
    cin >> n >> m;
    vector<vector<Edge>> adj(n + 1); // danh sách kề

    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({ v, w });
        adj[v].push_back({ u, w }); // đồ thị vô hướng
    }

    vector<long long> dist(n + 1, 1e18);
    vector<int> parent(n + 1, -1);
    dist[1] = 0;

    MinHeap pq;
    pq.push({ 1, 0 });

    while (!pq.empty()) {
        HeapNode hn = pq.pop();
        int u = hn.vertex;
        long long d = hn.dist;
        if (d > dist[u]) continue; // đã có khoảng cách tốt hơn
        for (auto e : adj[u]) {
            int v = e.to;
            long long w = e.weight;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({ v, dist[v] });
            }
        }
    }

    if (dist[n] == 1e18) {
        cout << -1 << endl; // không có đường đi
    }
    else {
        // xây dựng đường đi từ 1 -> n
        vector<int> path;
        int cur = n;
        while (cur != -1) {
            path.push_back(cur);
            cur = parent[cur];
        }
        // đảo đường đi từ 1 -> n
        for (int i = path.size() - 1; i >= 0; --i) {
            cout << path[i] << " ";
        }
        cout << endl;
    }
}
*/
void test04() {
    int n, m;
    cin >> n >> m;

    vector<vector<Edge>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        graph[u].push_back({ v,w });
    }

    const long long INF = 1e18;
    vector<long long> dist(n + 1, INF);
    vector<int> parent(n + 1, -1);

    dist[1] = 0;
    MinHeap pq;
    pq.push({ 1,0 });

    while (!pq.empty()) {
        HeapNode node = pq.pop();
        int u = node.vertex;
        long long d = node.dist;

        if (d > dist[u]) continue;

        for (auto e : graph[u]) {
            int v = e.to;
            long long w = e.weight;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({ v,dist[v] });
                parent[v] = u;
            }
        }
    }

    if (dist[n] == INF) {
        cout << -1;
    }
    else {
        int cur = n;
        vector<int> path;
        while (cur != -1) {
            path.push_back(cur);
            cur = parent[cur];
        }

        for (int i = path.size() - 1; i >= 0; i--) {
            cout << path[i] << " ";
        }
    }
}



// Test

void Merge(int* a, int left, int mid, int right) {
    // Bước 1: Tính số lượng phần tử
    int n1 = mid - left + 1;
    int n2 = right - mid;
    //Bước 2: Tạo mảng tạm
    int* L = new int[n1];
    int* R = new int[n2];

    // Bước 3: Sao chép dữ liệu vào mảng tạm
    for (int i = 0; i < n1; i++) {
        L[i] = a[left + i];
   }

    for (int j = 0; j < n2; j++) {
        R[j] = a[mid + 1 + j];
    }
    
    // Bước 4: Trộn mảng
    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            a[k++] = L[i++];
        }
        else {
            a[k++] = R[j++];
        }
    }

    // Bước 5: Sao chép phần còn lại vào mảng
    while (i < n1) {
        a[k++] = L[i++];
    }
    while (j < n2) {
        a[k++] = R[j++];
    }
}

void MergerSort(int* a, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        MergerSort(a, left, mid);
        MergerSort(a, mid + 1, right);
        
        Merge(a, left, mid, right);
    }
}

int Partition(int* a, int left, int right) {
    int pivot = a[right];
    int i = left - 1;

    for (int j = left ; j < right; j++) {
        if (a[j] <= pivot) {
            swap(a[++i], a[j]);
        }
    }

    swap(a[i + 1], a[right]);
    return i + 1;
}

void QuickSort(int* a, int l, int r) {
    if (l < r) {
        int partition = Partition(a, l, r);
        QuickSort(a, l, partition-1);
        QuickSort(a, partition + 1,r);
    }
}

long long Hash(char* s) {
    long long M = 1e9 + 9;
    long long p = 31;

    long long hashValue = 0;
    long long p_pow = 1;

    for (int i = 0; s[i] != '\0'; i++) {
        hashValue = (hashValue + p_pow % M) % M;
        p_pow = (p_pow * p) % M;
    }

    return (hashValue + M) % M;
}

void Insert2(vector<char*> &table, int n,char* s) {
    int index = Hash(s) % n;
    int start = index;

    while (table[index] != NULL && strcmp(table[index], s) != 0) {
        index = (index + 1) % n;
        if (index == start) {
            return;
        }
    }

    if (table[index] == NULL) {
        table[index] = new char[strlen(s) + 1];
        strcpy_s(table[index], strlen(s) + 1, s);
    }
}

int Search2(vector<char*>table, int n, char* s) {
    int index = Hash(s) % n;
    int start = index;

    while (table[index] != NULL) {
        if (strcmp(table[index], s) == 0) {
            return index;
        }
        index = index + 1;
        if (index == start) {
            break;
        }
    }

    return -1;
}

vector<char*> createHashTable2(vector<char* > input, int n) {
    vector<char* > table(n, NULL);

    for (char* a : input) {
        Insert2(table, n, a);
    }

    return table;
}
// Lấy 1 mảng string bằng char *
void test() {
    int m;
    cin >> m;

    vector<char*> input;

    for (int i = 0; i < m; i++) {
        char tmp[100];       // buffer tạm
        cin >> tmp;

        char* s = new char[strlen(tmp) + 1];
        strcpy_s(s, strlen(tmp) + 1, tmp);

        input.push_back(s);
    }
}
void printHashTable(vector<char*>& table) {
    for (int i = 0; i < table.size(); i++) {
        cout << i << ": ";
        if (table[i] != nullptr)
            cout << table[i];
        else
            cout << "NULL";
        cout << endl;
    }
}
void test2() {
    int m;
    cout << "Nhap so chuoi: ";
    cin >> m;

    vector<char*> input;

    // Nhập m chuỗi
    for (int i = 0; i < m; i++) {
        char temp[100];
        cin >> temp;

        char* s = new char[strlen(temp) + 1];
        strcpy_s(s, strlen(temp) + 1, temp);
        input.push_back(s);
    }

    int n = 2 * m + 1;   // kích thước bảng băm (thường chọn > m)
    vector<char*> table = createHashTable2(input, n);

    // In bảng băm
    cout << "\nBang bam:\n";
    printHashTable(table);

    // Test tìm kiếm
    char key[100];
    cout << "\nNhap chuoi can tim: ";
    cin >> key;

    int pos = Search2(table, n, key);
    if (pos != -1)
        cout << "Tim thay tai vi tri: " << pos << endl;
    else
        cout << "Khong tim thay\n";

    // Giải phóng bộ nhớ
    for (char* s : input) delete[] s;
    for (char* s : table) delete[] s;
}


vector<vector<int>> adj;
vector<bool> visited;

void BFS(int start) {
   // Bước 1L Tạo queue và thêm phần tử đầu tiên vào
   queue<int> q;
    q.push(start);
    visited[start] = true;
    // Bước 2: Thực hiện while
    while (!q.empty()) {
   // Bước 2.1: Lấy phần tử đầu tiên ra
        int u = q.front();
        q.pop();
        cout << u << " "; // xử lý node
        // Duyệt từng đỉnh đính với phần từ đầu tiên và kiểm tra đã thăm chưa
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}
void DFS(int u) {
    visited[u] = true;
    cout << u << " "; // xử lý node, ví dụ in ra
    for (int v : adj[u]) {
        if (!visited[v]) {
            DFS(v);
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;

    adj.resize(n + 1);
    visited.resize(n + 1, false);

    for (int i = 0; i < m; i++) {
        int u, v,w;
        cin >> u >> v>> w;
        adj[u].push_back(v);
        adj[v].push_back(u); // bỏ dòng này nếu đồ thị có hướng
    }

    int start;
    cin >> start;
    BFS(start);

    return 0;
}

