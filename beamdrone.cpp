#include <fstream>
#include <iostream>
#include <queue>
#include <algorithm>

#define MAX 1000

std::ifstream fin("beamdrone.in");
std::ofstream fout("beamdrone.out");

struct Tile {
    int x,y;
    Tile operator+(Tile other) {
        return {x + other.x, y + other.y};
    }
    bool operator==(Tile other) {
        return x == other.x && y == other.y;
    }
};

struct QElem {
    Tile old;
    Tile curr;
    int weight;
};

constexpr Tile dir[]{
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0},
};

int N, M;
char a[MAX][MAX];
Tile drone, finish;

int BFS() {
    auto cmp = [](QElem& a, QElem& b) {
        return a.weight > b.weight;
    };
    std::priority_queue<QElem, std::vector<QElem>, decltype(cmp)> Q(cmp);
    Q.push({drone, drone, 0});
    while (!Q.empty()) {
        QElem el = Q.top();
        Q.pop();
        if (a[el.curr.y][el.curr.x] != '.') {
            continue;
        }
        a[el.curr.y][el.curr.x] = 'O';
        if (el.curr == finish) {
            return el.weight;
        }
        for (int i = 0; i < 4; ++i) {
            Tile newPos = el.curr + dir[i];
            if (newPos.x < 0 || newPos.x >= M ||
                newPos.y < 0 || newPos.y >= N) {
                continue;
            }
            if (a[newPos.y][newPos.x] != '.') {
                continue;
            }
            Q.push({el.curr, newPos, el.weight + (
                el.old.x != newPos.x && el.old.y != newPos.y
            )});
        }
    }
    return -1;
}

int main() {
    fin >> N >> M;
    fin >> drone.y >> drone.x;
    fin >> finish.y >> finish.x;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            fin >> a[i][j];
        }
    }
    fout << BFS();
}
