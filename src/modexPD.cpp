#include "modex.h"
#include <algorithm>
#include <cmath>
#include <vector>


ModexResult modexPD(Network &rs) {
    int n = rs.agents.size();
    int capacity = rs.r_max;

    vector<int> costs(n);
    vector<double> benefits(n);

    for(int i = 0; i < n; i++) {
        const Agent &agent = rs.agents[i];

        costs[i] = ceil(abs(agent.opinion) * (1.0 - agent.receptivity) * agent.influence);
        benefits[i] = (agent.opinion * agent.opinion) * agent.influence;
    }
    // estados dp[i][b] = 
    vector<vector<double>> dp(n+1, vector<double>(capacity + 1, 0.0));

    for(int i = 1; i <= n; i++) {
        for(int budget = 0; budget <= capacity; budget++) {
            dp[i][budget] = dp[i-1][budget]; //no tomo

            if(costs[i-1] <= budget) {
                double withAgent = dp[i-1][budget - costs[i-1]] + benefits[i-1]; // lo tomo?
                dp[i][budget] = max(dp[i][budget], withAgent);
            }
        }
    }

    //reconstruir
    vector<int> strategy(n, 0);
    int remaining = capacity;

    for(int i = n; i >= 1; i--) {
        if(dp[i][remaining] != dp[i-1][remaining]) { 
            strategy[i-1] = 1;
            remaining -= costs[i-1];
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