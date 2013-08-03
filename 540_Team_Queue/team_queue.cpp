#include <cstdio>
#include <vector>
#include <list>
#include <cassert>

using namespace std;

const int team_max = 1000;
const int elem_max = 1000000;

vector<int> which_team(elem_max);
vector<list<int> > team_queue(team_max);
// On every update of teams_queue, update team_present
list<int> teams_queue;
vector<bool> team_present(team_max);

void doScenario() {
    int elem, team;
    char buffer[10];
    while(true) {
        scanf("%s ", buffer);
        switch(buffer[0]) {
            case 'E':
                scanf("%d\n", &elem);
                team = which_team[elem];
                if(!team_present[team]) {
                    teams_queue.push_back(team);
                    team_present[team] = true;
                }
                team_queue[team].push_back(elem);
                break;
            case 'D':
                assert(!teams_queue.empty());
                team = teams_queue.front();
                assert(!team_queue[team].empty());
                printf("%d\n",team_queue[team].front());
                fflush(stdout);
                team_queue[team].pop_front();
                if(team_queue[team].empty()) {
                    teams_queue.pop_front();
                    team_present[team] = false;
                }
                break;
            case 'S':
                return;
        }
    }
}

int main(int argc, char *argv[]) {
    int scenario = 0;
    while(true) {
        scenario++;
        int nteams;
        if(scanf("%d\n", &nteams) != 1)
            return 0;
        if(nteams == 0)
            return 0;
        teams_queue.clear();
        for(int team=0; team < nteams; team++) {
            team_queue[team].clear();
            team_present[team] = false;
            int nelems;
            scanf("%d ", &nelems);
            while(nelems--) {
                int elem;
                scanf("%d ", &elem);
                which_team[elem] = team;
            }
        }
        printf("Scenario #%d\n", scenario);
        doScenario();
        putchar('\n');
    }
}


