#ifndef _POINTCLOUD
#define _POINTCLOUD
#include "compare.h"
#include "point.h"
#include <algorithm>
#include <fstream>
#include <vector>

template<typename T>
class PointCloud
{
private:
    size_t dim;
    size_t num_points;
    Point<T>* points;

public:
    PointCloud(){
        this->dim = 0;
        this->num_points = 0;
        this->points = nullptr;
    }

    PointCloud(const std::vector<std::vector<T>> arr, const size_t& dim){
        this->dim = dim;
        this->num_points = arr.size();
        this->points = new Point<T>[this->num_points];

        for(size_t i = 0; i < this->num_points; ++i){
            this->points[i] = Point<T>(arr[i], this->dim); 
        }
    }

    PointCloud(const std::string& filepath, const size_t& dim, const bool& is_intensity = false){
        this->dim = dim;
        this->num_points = 0;

        std::ifstream input(filepath.c_str(),std::ios::in | std::ios::binary);
        if(!input){
            std::cerr<<"\nThe file was not succesfully opened"<<"\nPlease check that the file currenty exits.";
            exit(1);
        }

        input.seekg(0, std::ios::end);
        if(is_intensity)
            this->num_points = (size_t) input.tellg() / ((this->dim + 1)*sizeof(float));
        else
            this->num_points = (size_t) input.tellg() / ((this->dim)*sizeof(float));
        input.seekg(0, std::ios::beg);
        this->points = new Point<T>[this->num_points];

        for (size_t i = 0; i < this->num_points; ++i){

            float temp_pts[this->dim];
            float temp;
            input.read((char *) &temp_pts, this->dim*sizeof(float));
            input.read((char *) &temp, sizeof(float));
            this->points[i] = Point<T>(temp_pts, this->dim);  
        }

        input.close();
    }

    size_t get_size() const{
        return this->num_points;
    }

    Point<T> get_dim (size_t idx) const{
        return this->points[idx];
    }

    void sort_pc(const size_t& l, const size_t& r, const size_t& dim){
        auto begin = this->points + l;
        auto end   = begin + r - l;
        std::sort(begin, end, Comparator<T>(dim));
    }


    ~PointCloud(){
        //cout<<"Check"<<endl;
        delete [] this->points;
    }
    
};

#endif