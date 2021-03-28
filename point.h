#ifndef _POINT
#define _POINT
#include <iostream>
#include <vector>
template <class T>
class Point{
    private:
        size_t dim;
        T* point;
        
    public:    
        Point(){
            point = nullptr;
            dim = 0;
        }

        Point(const std::vector<T>& pnt, const size_t& d){
            
            point = new T[d];
            dim = d;
            for(size_t i=0; i<dim; ++i)
                point[i] = pnt[i];
        }
    
        Point(const T* pnt, const size_t& d){
            
            point = new T[d];
            dim = d;
            for(size_t i=0; i<dim; ++i)
                point[i] = pnt[i];
        }
        
        Point(const Point<T>& p){
            this->dim = p.dim;
            this->point = new T[this->dim];
            copy_point(p);
        }
        
        Point& operator = (const Point<T>& p){
            if(this == &p)
                return *this;
            
            this->dim = p.dim;
            if(this->point == nullptr)
                this->point = new T[this->dim];
            copy_point(p);
            
            return *this;
        }

        T get_dim(const size_t& dim) const{
            return this->point[dim];
        }
        
        double distance(const Point<T>& p) const{
            double min_dist = 0.0;
            if(this->dim != p.dim)
                exit( 1 );
            
            for(size_t i=0; i<this->dim; ++i)
               min_dist += (this->point[i] - p.point[i])*(this->point[i] - p.point[i]);
        
            return min_dist;
            
        }  
        
        void print_Point() {
            std::cout<<"(";
            for(size_t i = 0; i< dim; ++i)
                std::cout<<point[i]<<",";
            std::cout<<")"<<std::endl;
        }
        
        ~Point(){
            
            delete [] point;

        }

    private:
    	void copy_point(const Point<T>& p){
            for(size_t i=0; i<dim; ++i)
                this->point[i] = p.point[i];
        }
        
};


#endif //_POINT