#include "../../include/visualization/treenode2vtk.h"

void treeNodesTovtk(std::vector<ot::TreeNode>& nodes,int mpi_rank,std::string vtk_file_name)
{
  
  //std::sort(nodes.begin(),nodes.end());
  std::cout<<"vtk TreeNode started"<<std::endl;
  std::ostringstream convert;
  convert<<vtk_file_name<<"_"<<mpi_rank<<".vtk";
  vtk_file_name=convert.str();
  std::ofstream myfile;
  myfile.open(vtk_file_name.c_str());
  
  myfile<<"# vtk DataFile Version 2.0"<<std::endl;
  myfile<<"DENDRO OCTREES"<<std::endl;
  myfile<<"ASCII"<<std::endl;
  myfile<<"DATASET UNSTRUCTURED_GRID"<<std::endl;
  
  int dim=nodes[0].getDim();
  
  int unit_points=1<<dim;
  int num_verticies=nodes.size()*(unit_points);
  int num_cells=nodes.size();
 
  
  myfile<<"POINTS "<<num_verticies<<" float"<<std::endl;
  
  if(dim ==2)
  {
    
  }else if (dim==3)
  {
    unsigned int len;
    unsigned int xl,yl,zl;
    int num_feilddata=2;
    
    int num_cells_elements=num_cells*unit_points +num_cells;
    
    for(int i=0;i<nodes.size();i++)
    {
	len=1<<(nodes[i].getMaxDepth()-nodes[i].getLevel());
	xl=nodes[i].getX();
	yl=nodes[i].getY();
	zl=nodes[i].getZ();
	
	myfile<<xl<<" "<<yl<<" "<<zl<<std::endl;
	myfile<<(xl+len)<<" "<<yl<<" "<<zl<<std::endl;
	myfile<<(xl+len)<<" "<<(yl+len)<<" "<<zl<<std::endl;
	myfile<<xl<<" "<<(yl+len)<<" "<<zl<<std::endl;
	
	myfile<<xl<<" "<<yl<<" "<<(zl+len)<<std::endl;
	myfile<<(xl+len)<<" "<<yl<<" "<<(zl+len)<<std::endl;
	myfile<<(xl+len)<<" "<<(yl+len)<<" "<<(zl+len)<<std::endl;
	myfile<<xl<<" "<<(yl+len)<<" "<<(zl+len)<<std::endl;
	
    }
    
    myfile<<"CELLS "<<nodes.size()<<" "<<num_cells_elements<<std::endl;
    
    for(int i=0;i<num_cells;i++)
    {
      myfile<<unit_points<<" ";
      for(int j=0;j<unit_points;j++)
      {
	myfile<<(i*unit_points+j)<<" ";
      }
      myfile<<std::endl;
    }
    
    myfile<<"CELL_TYPES "<<num_cells<<std::endl;
    for(int i=0;i<num_cells;i++)
    {
      myfile<<VTK_HEXAHEDRON<<std::endl;
    }
       
    //myfile<<"CELL_DATA "<<num_cells<<std::endl;
    //myfile<<"POINT_DATA "<<(num_cells*unit_points)<<std::endl;
    myfile<<"FIELD FieldData "<<num_feilddata<<std::endl;
    myfile<<"cell_level "<<num_cells<<" 1"<<" int"<<std::endl;
    for(int i=0;i<nodes.size();i++)
      myfile<<nodes[i].getLevel()<<std::endl;
    
    myfile<<"mpi_rank "<<num_cells<<" "<<" int"<<std::endl;
    for(int i=0;i<nodes.size();i++)
      myfile<<mpi_rank<<std::endl;
    
  }
  
  myfile.close();
  
  
  
}