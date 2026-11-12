#include "modex.h"
#include <algorithm>
#include <cmath>
#include <vector>
#include <limits>


using namespace std;

struct GreedyCandidate {
    int index; // pos original
    int cost; // cuanto me cuesta moderarlo
    double benefit; // lo que me reduce al extrem
    double ratio; // benefit / cost
};

bool cmp(const GreedyCandidate &a, const GreedyCandidate &b) {
    if (a.ratio != b.ratio) {
        return a.ratio > b.ratio;
    }

    if (a.benefit != b.benefit) {
        return a.benefit > b.benefit;
    }

    return a.index < b.index;
}

ModexResult modexV(Network &rs) {
    int n = rs.agents.size();

    vector<GreedyCandidate> candidates;
    vector<int> strategy(n, 0);

    for(int i = 0; i < n; i++) {
        Agent &agent = rs.agents[i];
        int cost = ceil(abs(agent.opinion) * (1.0 - agent.receptivity) * agent.influence);

        double benefit = agent.opinion * agent.opinion * agent.influence;
        // si el costo es 0 entonces lo pongo para que me de un ratio infinito,  de otra manera calculo
        double ratio = cost == 0 ? numeric_limits<double>::infinity() : benefit / cost;

        candidates.push_back({i, cost, benefit, ratio});
    }

    //ordeno para procesarlos 
    sort(candidates.begin(), candidates.end(), cmp);
    int remaining = rs.r_max;

    //empiezo a coger
    for(const GreedyCandidate &candidate : candidates) {
        if(candidate.cost <= remaining) {
            strategy[candidate.index] = 1;
            remaining -= candidate.cost;
        }
    }

    Network moderated = rs;

    for(int i = 0; i < n; i++) {
        if(strategy[i] == 1) {
            moderated.agents[i].opinion = 0;
        }
    }

    return {
        strategy,
        effort(rs, strategy),
        ext(moderated)
    };
}