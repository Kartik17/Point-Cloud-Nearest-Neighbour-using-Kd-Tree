#ifndef _KDNODE
#define _KDNODE

template <class T>
struct KdNode{
  Point<T>* p;
  KdNode* left;
  KdNode* right;

  KdNode(){
  	p = nullptr;
    left  = nullptr;
    right = nullptr;
  }

  ~KdNode(){
  	delete p;
  }
  
};

#endif