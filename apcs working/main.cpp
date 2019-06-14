#include <iostream>
#include <vector>
#include <memory.h>
#include <queue>

using namespace std;
struct work{
    queue<pair<int ,int> > subtask;
    int fin_time ,curr_time;
}task[200];
int m_avai[200];
int machines ,works;

inline bool all_done() {
    for(int i = 0;i < works;i++) if(!task[i].subtask.empty()) return false;
    return true;
}

inline void sche_subtask() {
    int best_idx = -1 ,best_value = (1LL << 31) - 1;
    pair<int ,int> job;
    for(int i = 0;i < works;i++) {
        if(task[i].subtask.empty()) continue;
        job = task[i].subtask.front();
        int start_time = max(task[i].curr_time ,m_avai[job.first]) + job.second;
        if(best_value > start_time) {
            best_value = start_time;
            best_idx = i;
        }
    }

    job = task[best_idx].subtask.front();
    task[best_idx].subtask.pop();
    task[best_idx].curr_time = m_avai[job.first] = max(task[best_idx].curr_time ,m_avai[job.first]) + job.second;
    if(task[best_idx].subtask.empty()) task[best_idx].fin_time = task[best_idx].curr_time;
}

int main()
{
    int i ,mcode ,req_t ,subtasks ,ans;
    while(cin >> machines >> works) {
        memset(task ,0 ,sizeof(task)) ,memset(m_avai ,0 ,sizeof(m_avai));
        for(i = 0;i < works;i++) {
            cin >> subtasks;
            task[i].subtask = queue<pair<int ,int> >();
            while(subtasks--) {
                 cin >> mcode >> req_t;
                 task[i].subtask.push(pair<int ,int>(mcode ,req_t));
            }
            task[i].fin_time = task[i].curr_time = 0;
        }

        while(!all_done()) {
            sche_subtask();
        }

        for(ans = i = 0;i < works;i++) ans += task[i].fin_time;
        cout << ans << endl;
    }
}

/*
3 3
2
2 4 1 1
3
0 2 2 2 0 1
1
0 7
*/

/*
2 3
1
0 4
1
1 5
1
1 3
*/

// well ,i passed the testing data.
// so i regard it as i passed.
