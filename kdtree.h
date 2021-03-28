#ifndef _KDTREE
#define _KDTREE

#include "kdnode.h"
#include "pointcloud.h"
#include <stack>
#include <cmath>

template <class T>
class Kdtree{
    private:
        KdNode<T>* root;
        size_t num_pts;
        size_t total_dim;
        
        
    public:
        Kdtree(){
            this->root = nullptr;
            this->total_dim = 0;
            this->num_pts = 0;
        }

        Kdtree(PointCloud<T>& pc, size_t dim){
            this->total_dim = dim;
            this->num_pts = pc.get_size();
            this->root = this->make_tree(pc,0, this->num_pts, 0);
        }
        
        // Copy Constructor
        Kdtree(const Kdtree<T>& kd){
            this->total_dim = kd.total_dim;
            this->num_pts = kd.num_pts;
            this->root = new KdNode<T>;
            if(kd.root == nullptr){
                this->root = nullptr;
                return;
            }

            copy_tree(kd);
            
        }

        // Assignment Operator
        Kdtree<T>& operator = (const Kdtree<T>& kd){
            if(this == &kd)
                return *this;

            this->total_dim = kd.total_dim;
            this->num_pts = kd.num_pts;

            if(this->root == nullptr)
                this->root = new KdNode<T>;
            copy_tree(kd);

            return *this;
        }
        
        // Generate Kd Tree Routine
        KdNode<T>* make_tree(PointCloud<T>& pc, size_t l, size_t r, size_t dim){
            
            if(l >= r)
                return nullptr;
                
            KdNode<T>* curr_node = new KdNode<T>;
            
            //auto begin = pnts + l;
            //auto end = begin + r - l;

            //sort(begin, end, Comparator<T>(dim));
            pc.sort_pc(l,r, dim);

            size_t idx = (r-l)/2 + l;
            curr_node->p = pc.get_dim(idx);
            
            curr_node->left  = make_tree(pc, l , idx , (dim + 1) % this->total_dim);
            curr_node->right = make_tree(pc, idx + 1, r, (dim + 1) % this->total_dim);
            
            return curr_node;
        }
        
        void find_dist(KdNode<T>* node, const Point<T>& p, double& min_dist, Point<T>& nearest_point, size_t dim){
            if(node == nullptr)
                return;
                
            double curr_dis = p.distance(node->p);
            if(curr_dis < min_dist){
                min_dist = curr_dis;
                nearest_point = node->p;
            }           

            if(p.get_dim(dim) < node->p.get_dim(dim)){
                find_dist(node->left, p, min_dist, nearest_point, (dim + 1)% this->total_dim);
                
                double poss_min_dist = (node->p.get_dim(dim) - p.get_dim(dim))*(node->p.get_dim(dim) - p.get_dim(dim));
                if(min_dist > poss_min_dist)
                    find_dist(node->right, p, min_dist, nearest_point, (dim + 1)% this->total_dim);
            }
            else{
                find_dist(node->right, p, min_dist, nearest_point, (dim + 1)% this->total_dim);
                
                double poss_min_dist = (p.get_dim(dim) - node->p.get_dim(dim))*(p.get_dim(dim) - node->p.get_dim(dim));
                if(min_dist > poss_min_dist)
                    find_dist(node->left, p, min_dist, nearest_point, (dim + 1)% this->total_dim);
                
            }            
            return;
        }
        
        Point<T> nn(const Point<T>& p){
            double min_dist = 1e9;
            KdNode<T>* node = root;
            Point<T> nearest_point;

            find_dist(node, p, min_dist, nearest_point, 0);
                        
            return nearest_point;
        }
        
        void inorder(){
            KdNode<T>* temp = this->root;
            std::stack<KdNode<T>*> s;
            
            std::cout<<"Inorder start"<<std::endl;
            while(temp != nullptr || !s.empty()){
                while(temp != nullptr){
                    s.push(temp);
                    temp = temp->left;
                }
                
                temp = s.top();
                s.pop();
                temp->p.print_Point();
                temp = temp->right;
            }
            std::cout<<"Inorder End"<<std::endl;
        }
        
        void delete_node(KdNode<T>* node){
            //cout<<"Deleting Nodes"<<endl;
            if(node){
                delete_node(node->left);
                delete_node(node->right);
                delete node;
            }
        }
        
        ~Kdtree(){
            delete_node(this->root);
        }

    private:
        void copy_tree(const Kdtree<T>& kd){

            KdNode<T>* temp = this->root;
            const KdNode<T>* copy = kd.root;
            std::stack<const KdNode<T>*> s;
            std::stack<KdNode<T>*> t;
            while(copy != nullptr || !s.empty()){
                while(copy != nullptr){
                    s.push(copy);
                    t.push(temp);
                    temp->p = copy->p;

                    copy = copy->left;

                    if(copy != nullptr){
                        temp->left = new KdNode<T>;
                        temp = temp->left;
                    }
                    
                }

                copy = s.top();
                temp = t.top();
                s.pop();
                t.pop();
                copy = copy->right;
                if(copy != nullptr){
                    temp->right = new KdNode<T>;
                    temp = temp->right;
                }

            }
            temp = nullptr;
            delete temp;
        }

        
};

#endif