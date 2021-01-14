#include "CellularAutomation.h"

int main()
{
    CellularAutomation ca1d(2, 1, 200);

    VtkData ca1dvtk;
    ca1dvtk.setPoints(ca1d.getPoint());
    ca1dvtk.setCells(ca1d.getCellNumber());
    ca1dvtk.setScalarPointData(ca1d.cellular1D(22));

    ca1dvtk.writeVtkFile("CA1D.vtk");
    return 0;
}