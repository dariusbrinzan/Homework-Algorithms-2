#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

ifstream fin("fortificatii.in");
ofstream fout("fortificatii.out");

#define inf 2e18
#define max 1e18
const int max_cities = 1e+5;

vector<vector<pair<int, int> > > v(max_cities);
// am vectorul de distante pentru alg lui djkstra
// unde initializez totul cu infinit
vector<long> dist(max_cities, inf);
// vector de rute
vector<long> graph_routes;
int n, m, k, b;

priority_queue<pair<long, long> > p_queue;
// boolean care imi returneaza nodurile care sunt de tip barbar
bool is_barbarian[max_cities];
// algoritmul lui dijkstra folosind un priority queue
// inspirat din lab + geeks
void dijkstra(int start){
    dist[start] = 0;
    p_queue.push(make_pair(0, start));
    while (p_queue.empty() == 0){
        int u = p_queue.top().second;
        p_queue.pop();
        for (auto x : v[u]){
            if (dist[x.second] > dist[u] + x.first){
                dist[x.second] = dist[u] + x.first;
                // adaug in coada mea doar nodurile care practic
                // nu sunt barbare
                if (is_barbarian[x.second] == 0) {
                    p_queue.push(make_pair(-dist[x.second], x.second));
                }
            }
        }
    }
    return;
}

bool check_binary(long k, long mid) {
    bool ok = 0;
    for (auto route : graph_routes) {
        if (k > mid - route || k == mid - route)
            k -= mid - route;
        else if (route > mid)
            return ok ? 1 : 0;
        else
            return ok ? 0 : 1;
    }
    return ok;
}

long binary_search(long left, long right) {
    long result = 0;
    while (left <= right) {
        long mid = (left + right) / 2;
        if (check_binary(k, mid))
            right = mid - 1;
        else {
            left = mid + 1;
            result = mid;
        }
    }
    return result;
}


int main() {
    long left = 0, right = max;
    fin >> n >> m >> k;
    // numarul de localitati barbare
    fin >> b;
    for (int i = 1; i <= b; ++i) {
        int barb;
        fin >> barb;
        is_barbarian[barb] = 1;
    }
    // rutele x - y -> costul aferent - cost
    for (int i = 1; i <= m; ++i) {
        int x, y, cost;
        fin >> x >> y >> cost;
        // aici practic fac muchia de la x - y de cost - cost
        v[y].push_back(make_pair(cost, x));
        v[x].push_back(make_pair(cost, y));
    }
    // apelez algoritmul lui dijkstra din nodul 1 - capitala
    dijkstra(1);
    // parcurg localitatile (nodurile) si
    // tratez rutele cand exista practic muchie intre
    // 2 noduri de tip barbar si adaug rutele
    // care nu contin 2 noduri barbare
    for (int i = 1; i <= n; ++i) {
        if (is_barbarian[i] == 0)
            continue;
        for (auto nodes : v[i]) {
            if (is_barbarian[nodes.second])
                continue;
            graph_routes.push_back(dist[nodes.second] + nodes.first);
        }
    }
    sort(graph_routes.begin(), graph_routes.end());
    fout << binary_search(left, right) << endl;
    return 0;
}
