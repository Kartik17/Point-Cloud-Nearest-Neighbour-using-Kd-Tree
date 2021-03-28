#include "pointcloud.h"
#include "kdtree.h"
#include <vector>
int main()
{   
    size_t dim = 3;
    // Construct Point cloud from bin file , with XYZI
    PointCloud<float> pc1("test_bin.bin", dim, true);
    // Kdtree using pointcloud
    Kdtree<float> twotree(pc1, dim);
    // Search for NN of this point
    float p1[] = {32,51,12};
    Point<float> point1(p1,dim);
    twotree.nn(point1).print_Point();


    dim = 2;
    std::vector<std::vector<float> > arr = {{1,0},{1,1},{1,2},{1,3},{1,4},{1,5},{1,6},{1,7},{1,8},{1,9},{1,10},{1,11},{1,12},{1,13},{1,14},{1,15},{1,16},{1,17}};
    // Construct Point cloud from bin file , with XYZI
    PointCloud<float> pc2(arr, dim);
    // Kdtree using pointcloud
    Kdtree<float> twotree2(pc2, dim);
    // Search for NN of this point
    float p2[] = {0,7};
    Point<float> point2(p2,dim);
    twotree2.nn(point2).print_Point();

    return 0;
}
