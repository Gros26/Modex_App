#include "./modex.h"
#include <cmath>

using namespace std;

double effort(const Network &network, const vector<int> &strategy) {
    double ans = 0;
    int size = network.agents.size();

    for(int i = 0; i < size; i++) {
        const Agent &agent = network.agents[i];
        int new_opinion = strategy[i] == 1 ? 0 : agent.opinion;
        int difference_opinions = abs(agent.opinion - new_opinion);
        double receptivity = (1.0 - agent.receptivity);
        double influence = agent.influence;
        ans += (ceil((double) difference_opinions * receptivity * influence));
    }

    return ans;
}

double ext(const Network &network) {
    int size = network.agents.size();
    double sum = 0;
    for(int i = 0; i < size; i++) {
        const Agent &agent = network.agents[i];
        int opinion = agent.opinion;
        double influece = agent.influence;
        sum += ((opinion * opinion) * influece);
    }

    return (sqrt(sum) / (double) size);
}