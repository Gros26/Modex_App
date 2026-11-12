#pragma once
#include <string>
#include "modex.h"

using namespace std;

Network inputParser(const string &text);

string outputParser(const ModexResult &r);