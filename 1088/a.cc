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

const int MAX = 100;
int hmap[MAX][MAX];
int dp[MAX][MAX];
int r;
int c;

int bfs(int i, int j) {
  if (dp[i][j] != 0) return dp[i][j];
  dp[i][j] = 1;
  if (j + 1 < c && hmap[i][j] > hmap[i][j + 1]) {
    if (dp[i][j + 1]) {
      dp[i][j] = max(dp[i][j], dp[i][j + 1] + 1);
    } else {
      dp[i][j] = max(dp[i][j], bfs(i, j + 1) + 1);
    }
  }

  if (i + 1 < r && hmap[i][j] > hmap[i + 1][j]) {
    if (dp[i + 1][j]) {
      dp[i][j] = max(dp[i][j], dp[i + 1][j] + 1);
    } else {
      dp[i][j] = max(dp[i][j], bfs(i + 1, j) + 1);
    }
  }

  if (j - 1 >= 0 && hmap[i][j] > hmap[i][j - 1]) {
    if (dp[i][j - 1]) {
      dp[i][j] = max(dp[i][j], dp[i][j - 1] + 1);
    } else {
      dp[i][j] = max(dp[i][j], bfs(i, j - 1) + 1);
    }
  }

  if (i - 1 >= 0 && hmap[i][j] > hmap[i - 1][j]) {
    if (dp[i - 1][j]) {
      dp[i][j] = max(dp[i][j], dp[i - 1][j] + 1);
    } else {
      dp[i][j] = max(dp[i][j], bfs(i - 1, j) + 1);
    }
  }

  return dp[i][j];
}

int solve() {
  int ans = 0;
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      bfs(i, j);
      ans = max(ans, dp[i][j]);
    }
  }

  return ans;
}

/*
 * DP(i,j) = max(DP(i,j-1), DP(i,j+1), DP(i-1,j), DP(i+1,j)) + 1
 */
int main() {
  // toggle off the synchronization of all the C++ standard
  // stream with their corresponding standard C streams
  ios_base::sync_with_stdio(false);
  // do not guarantee flushing of std::cout before std::cin accepts an input
  cin.tie(NULL);

#ifdef LOCAL
  fstream cin("in.txt");
#endif

  cin >> r >> c;
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      cin >> hmap[i][j];
    }
  }

  memset(dp, 0, sizeof(dp));
  cout << solve() << endl;
  return 0;
}
