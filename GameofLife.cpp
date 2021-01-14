#include "CellularAutomation.h"

int main()
{
    CellularAutomation gol(100);

    VtkData golvtk;
    golvtk.setPoints(gol.getPoint());
    golvtk.setCells(gol.getCellNumber());
    golvtk.setScalarPointData(gol.gameOfLife(150));

    golvtk.writeVtkFile("GameofLife.vtk");
    return 0;
}