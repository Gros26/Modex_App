#include "parser.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include <fstream>

using namespace std;


vector<string> cleanInput(const string &text)
{
    vector<string> lines;
    istringstream in(text);
    string line;
    while (getline(in, line)) {
        for (char& c : line)
            if (c == ',' || c == ';' || c == '\t' || c == '\r') c = ' ';
        if (line.find_first_not_of(' ') != string::npos)
            lines.push_back(line);
    }
    return lines;
}


Network inputParser(const string &path)
{
    ifstream in(path);
    if (!in) throw std::runtime_error("No se pudo abrir el archivo.");

    Network rs;
    int n;
    in >> n;

    rs.agents.resize(n);
    char coma;
    for (int i = 0; i < n; i++) {
        in >> rs.agents[i].opinion >> coma >> rs.agents[i].receptivity >> coma >> rs.agents[i].influence;
    }
    in >> rs.r_max;

    if (!in) throw std::runtime_error("Formato de entrada inválido.");
    return rs;
}

string outputParser(const ModexResult &r) {
    string ans = "";
    ans += to_string(r.extremism) + "\n";
    ans += to_string(r.effort) + "\n";
    int size = r.strategy.size();

    for(int i = 0; i < size; i++) {
        ans += to_string(r.strategy[i]) + "\n";
    }

    return ans;
}

//std::string formatearSalida(const Resultado& r)
//{
  //  std::ostringstream out;
    //out << std::fixed << std::setprecision(2) << r.ext << "\n";
//    out << r.esfuerzo << "\n";
  //  for (int x : r.e)
    //    out << x << "\n";
  //  return out.str();
//}