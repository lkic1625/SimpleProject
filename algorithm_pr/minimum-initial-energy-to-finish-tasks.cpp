#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minimumEffort(vector<vector<int>>& tasks) {
        sort(tasks.begin(), tasks.end(), [](const vector<int>& lv, const vector<int>& rv) -> bool {
            int lDiff = lv[1] - lv[0];
            int rDiff = rv[1] - rv[0];

            return lDiff != rDiff ? lDiff < rDiff : lv[1] < rv[1];
        });

        int ans = 0;
        for (const auto &task: tasks) {
            if (ans + task[0] < task[1]) {
                ans = task[1];
            } else {
                ans += task[0];
            }
        }

        return ans;
    }
};
