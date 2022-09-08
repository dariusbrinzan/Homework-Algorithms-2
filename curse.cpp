#include <fstream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

ifstream fin("curse.in");
ofstream fout("curse.out");

int N, M, A, ROOT;
vector<int> ADJ[10005];
bool hasPathToIt[10005];

void BFS() {
    queue<int> Q;
    Q.push(ROOT);
    int weights[10005];
    int parents[10005];
    parents[ROOT] = 0;
    memset(weights, 127, M * sizeof(int));
    while (!Q.empty()) {
        int node = Q.front();
        Q.pop();
        for (int i: ADJ[node]) {
            if (weights[node] + 1 > weights[i]) {
                weights[i] = weights[node] + 1;
                parents[i] = node;
                Q.push(i);
            }
        }
    }
    int cnt = 0;
    for (int i = 1; i <= M; ++i) {
        if (ADJ[i].empty()) {
            weights[cnt++] = i;
            while (parents[i]) {
                weights[cnt++] = parents[i];
                i = parents[i];
            }
            break;
        }
    }
    for (int i = cnt - 1; i >= 0; --i) {
        fout << weights[i] << ' ';
    }
}

int main() {
    fin >> N >> M >> A;
    int lastLine[21]{};
    for (int i = 0; i < A; ++i) {
        int line[21];
        bool ok = true;
        for (int j = 0; j < N ; ++j) {
            fin >> line[j];
            if (ok) {
                if (line[j] != lastLine[j]) {
                    ADJ[lastLine[j]].push_back(line[j]);
                    hasPathToIt[line[j]] = true;
                }
            }
            if (line[j] != lastLine[j]) {
                ok = false;
            }
            lastLine[j] = line[j];
        }
    }
    for (int i = 1; i <= M; ++i) {
        if (!hasPathToIt[i]) {
            ROOT = i;
            break;
        }
    }
    BFS();
}
