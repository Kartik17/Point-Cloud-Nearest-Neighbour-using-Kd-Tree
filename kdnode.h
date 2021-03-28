#ifndef _KDNODE
#define _KDNODE

template <class T>
struct KdNode{
  Point<T> p;
  KdNode* left;
  KdNode* right;

  KdNode(){
    left  = nullptr;
    right = nullptr;
  }

  ~KdNode(){
  }
  
};

#endif