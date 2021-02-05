#include <algorithm>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define f first
#define s second

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;

int mp[3][3];
int buf[50];
char input[11];
int limit;
int finished;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
char op[] = {'u', 'r', 'd', 'l'};

int h(int x, int y) {
  int v = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (i != x || j != y) {
        v += abs(i - (mp[i][j] - 1) / 3);
        v += abs(j - ((mp[i][j] - 1) % 3));
      }
    }
  }
  return v;
}

int dfs(int x, int y, int step, int pre) {
  int hn = h(x, y);
  if (hn == 0) {
    finished = 1;
    return step;
  }
  if (hn + step > limit) return hn + step;
  int minn = INT_MAX;
  for (int i = 0; i < 4; i++) {
    if (abs(i - pre) == 2) continue;
    int xx = x + dx[i];
    int yy = y + dy[i];
    if (xx < 0 || xx > 2 || yy < 0 || yy > 2) continue;
    buf[step] = i;
    swap(mp[x][y], mp[xx][yy]);
    int tmp = dfs(xx, yy, step + 1, i);
    if (finished) return tmp;
    minn = min(tmp, minn);
    swap(mp[x][y], mp[xx][yy]);
  }
  return minn;
}

void IDA_star(int x, int y) {
  finished = 0;
  memset(buf, -1, sizeof(buf));
  while (finished == 0 && limit <= 36) limit = dfs(x, y, 0, -10);

  if (finished) {
    for (int i = 0; i < limit; i++) cout << op[buf[i]];
    cout << endl;
  } else {
    cout << "unsolvable" << endl;
  }
}

bool valid(int mp[3][3]) {
  int seq[8];
  int k = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if (mp[i][j] != 9)
        seq[k++] = mp[i][j];

  int cantorNum = 0;
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < i; j++)
      if (seq[j] > seq[i]) cantorNum++;

  return (cantorNum % 2) == 0;
}

int main() {
  // toggle off the synchronization of all the C++ standard
  // stream with their corresponding standard C streams
  ios_base::sync_with_stdio(false);
  // do not guarantee flushing of std::cout before std::cin accepts an input
  cin.tie(NULL);

#ifdef LOCAL
  fstream cin("in.txt");
#endif

  for (int i = 0; i < 9; i++) cin >> input[i];

  int t = 0;
  int x;
  int y;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (input[t] == 'x') {
        mp[i][j] = 9;
        x = i;
        y = j;
        t++;
      } else
        mp[i][j] = input[t++] - '0';
    }
  }

  int limit = h(x, y);
  if (limit == 0) {
    cout << endl;
    return 0;
  }

  if (valid(mp))
    IDA_star(x, y);

  return 0;
}
