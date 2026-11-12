#pragma once

#include <vector>

using namespace std;

struct Agent {
    int opinion;
    double receptivity;
    double influence;
};

struct Network {
    vector<Agent> agents;
    int r_max;
};

struct ModexResult {
    vector<int> strategy;
    double effort;
    double extremism;
};

double effort(const Network &network, const vector<int> &strategy);
double ext(const Network &network);

ModexResult modexFB(Network &rs);
ModexResult modexV(Network &rs);
ModexResult modexPD(Network &rs);