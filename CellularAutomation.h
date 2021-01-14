#ifndef CellularAutomation_H
#define CellularAutomation_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include "VtkData.h"

class CellularAutomation
{
private:
    int k;
    int r;
    int m;
    int N; // space size
    std::vector<int> bin; // binary number for CA1D
    std::vector<double> state; // state number
    std::vector<double> finalstate; // state to vtk
    std::vector<Vec3> coord; // 2D coordinates
    std::vector<std::vector<int>> cell;
public:
    CellularAutomation(int k, int r, int N);
    CellularAutomation(int N);
    std::vector<Vec3> getPoint();
    std::vector<std::vector<int>> getCellNumber();
    std::vector<double> cellular1D(int rulenum);
    std::vector<double> gameOfLife(int iter);    
    ~CellularAutomation();
};

#endif