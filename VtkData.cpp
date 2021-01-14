#include "vtkData.h"

#include <iostream>
#include <fstream>

void VtkData::setPoints ( const std::vector< Vec3 > points )
{
    const int priorLength = points.size();
    
    this->points = points;
    
    if ( priorLength != 0 && priorLength != this->points.size() )
    {
        std::cout << "VtkData::setPoints(...) => WARNING:" << std::endl;
        std::cout << "    New number of points does not match old number." << std::endl;
        std::cout << "    (sizeOld = " << priorLength << ") != (sizeNew = " << this->points.size() << ")" <<  std::endl;
        std::cout << "    => All other fields are reset!" << std::endl;
        
        this->cells.clear();
        
        this->scalarPointData.clear();
        this->vectorPointData.clear();
    }
}

void VtkData::setCells ( const std::vector< std::vector< int > > cells )
{
    for ( auto& cell : cells )
    {
        for ( auto& pointIndex : cell )
        {
            if ( pointIndex >= this->points.size() )
            {
                std::cerr << "VtkData::setCells(...) => ERROR:";
                std::cerr << "    The cell list contains at least one point index that exceeds the number of points." << std::endl;
                std::cerr << "    (pointIndex = " << pointIndex << ") >= (sizePoints = " << this->points.size() << ")" <<  std::endl;
                std::cerr << "    => The cell list is not set!" << std::endl;
                
                return;
            }
        }
    }
    
    this->cells = cells;
}

void VtkData::setScalarPointData ( const std::vector< double > scalarPointData )
{
    if ( scalarPointData.size() != this->points.size() )
    {
        std::cerr << "VtkData::setScalarPointData(...) => ERROR:";
        std::cerr << "    The point data list has a different size than the point list." << std::endl;
        std::cerr << "    (sizePoints = " << this->points.size() << ") != (sizePointData = " << scalarPointData.size() << ")" <<  std::endl;
        std::cerr << "    => The point data list is not set!" << std::endl;
        
        return;
    }
    
    this->scalarPointData = scalarPointData;
}

void VtkData::setVectorPointData( const std::vector< Vec3 > vectorPointData )
{
    if ( vectorPointData.size() != this->points.size() )
    {
        std::cerr << "VtkData::setVectorPointData(...) => ERROR:";
        std::cerr << "    The point data list has a different size than the point list." << std::endl;
        std::cerr << "    (sizePoints = " << this->points.size() << ") != (sizePointData = " << vectorPointData.size() << ")" <<  std::endl;
        std::cerr << "    => The point data list is not set!" << std::endl;
        
        return;
    }
    
    this->vectorPointData = vectorPointData;
}

void VtkData::writeVtkFile( const std::string filename, const bool verbose ) const
{
    if ( verbose ) std::cout << "VtkData::writeVtkFile( " << filename << " )" << std::endl;
    
    ///////////////////////////////////////////////////////////////////////////
    
    std::ofstream file( filename );
    
    if ( !file.is_open() )	
    {
        std::cerr << "VtkData::writeVtkFile(...) => ERROR:";
        std::cerr << "    The file " << filename << " cannot be opened." << std::endl;
        std::cerr << "    A possible reason could be, that the directory in which the file should be created does not exist." <<  std::endl;
        std::cerr << "    => The file is not written!" << std::endl;
        
        return;
    }

    ///////////////////////////////////////////////////////////////////////////

	file << "# vtk DataFile Version 1.0" << std::endl;
	file << "generated by the vtkData class used for the APL course at TU Braunschweig" << std::endl;
	file << "ASCII" << std::endl;
	file << "DATASET UNSTRUCTURED_GRID" << std::endl;
    
    ///////////////////////////////////////////////////////////////////////////
    
	file << "POINTS " << this->points.size() << " double" << std::endl;
    
    for ( auto& point : this->points )
    {
        file << point.x << " " << point.y << " " << point.z << " " << std::endl;
    }
    
    ///////////////////////////////////////////////////////////////////////////
        
    int numberOfCellEntries = 0;
    
    for ( auto& cell : this->cells ) numberOfCellEntries += 1 + cell.size();
        
    file << "CELLS " << this->cells.size() << " " << numberOfCellEntries << std::endl;
    
    for ( auto& cell : this->cells )
    {
        file << cell.size() << " ";
        
        for ( auto& pointIndex : cell )
		{
			file << pointIndex << " ";
		}
        
        file << std::endl;
    }
    
    file << "CELL_TYPES " << this->cells.size() << std::endl;
    
    for ( auto& cell : this->cells )
	{
		if (cell.size() == 1) file << 1 << std::endl;
		if (cell.size() == 2) file << 3 << std::endl;
		if (cell.size() == 3) file << 5 << std::endl;
		if (cell.size() == 4) file << 9 << std::endl;
	}
    
    ///////////////////////////////////////////////////////////////////////////
        
    if ( this->scalarPointData.size() != 0 || this->vectorPointData.size() != 0 )
        
    file << "POINT_DATA " << this->points.size() << std::endl;
        
    if ( this->scalarPointData.size() != 0 )
    {
        file << "SCALARS scalarData double" << std::endl;
        file << "LOOKUP_TABLE default" << std::endl;

        for ( auto& scalar : this->scalarPointData )
        {
            file << scalar << std::endl;
        }
    }
    
    ///////////////////////////////////////////////////////////////////////////
        
    if ( this->vectorPointData.size() != 0 )
    {
        file << "VECTORS vectorData double" << std::endl;

        for ( auto& vector : this->vectorPointData )
        {
            file << vector.x << " " << vector.y << " " << vector.z << std::endl;
        }
    }
    
    ///////////////////////////////////////////////////////////////////////////
        
    file.close();
    
    if( verbose ) std::cout << "    => done" << std::endl;
}

void VtkData::setPrintWarnings( const bool printWarnings )
{
    this->printWarnings = printWarnings;
}






















