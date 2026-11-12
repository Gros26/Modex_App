#include "modex.h"

using namespace std;


bool next(vector<int> &e) {
    int i = e.size() - 1;
    while(i >= 0 && e[i] == 1) {
        e[i] = 0;
        i--;
    }

    if(i < 0)
        return false;

    e[i] = 1;

    return true;
}

vector<Agent> modify_copy(vector<Agent> agents, vector<int> &e) {
    for(int i = 0; i < e.size(); i++) {
        if(e[i] == 1)
            agents[i].opinion = 0;
    }

    return agents;
}


ModexResult modexFB(Network &rs) {
    vector<int> e(rs.agents.size(), 0);
    vector<int> best_e = e;
    double effort_ = 0; // no hay uno mejor o peor, solo esfuerzos que sirven. El problema no pide usar menos effort o asi
    double best_ext = ext(rs);

    do {
        double aux = effort(rs, e);
        if(aux <= rs.r_max) {
            vector<Agent> new_agents = modify_copy(rs.agents, e);
            Network net; net.agents = new_agents;
            double new_ext = ext(net);

            if(best_ext > new_ext) {
                best_ext = new_ext;
                best_e = e;
                effort_ = aux;
            }
        }

    } while(next(e));


    return {best_e, effort_, best_ext};
}

