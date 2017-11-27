//#include <iostream>
//using namespace std;

enum Balance_factor{
    left_higher, 
    equal_height,
    right_higher
};

enum Error_code{
    success,
    duplicate_error
};

template <class T>
struct AVL_Node{
    T _data;
    AVL_Node<T>* _left;
    AVL_Node<T>* _right;
    Balance_factor _balance;
    AVL_Node(){
        _data = 0;
        _left = NULL;
        _right = NULL;   
    }
    AVL_Node(T data, AVL_Node<T> * left = NULL, AVL_Node<T> * right = NULL){
        _data = data;
        _left = left;
        _right = right;
    }
    void set_balance(Balance_factor b){
        _balance = b;
    }
    Balance_factor get_balance() const{
        return _balance;
    }
};

template <typename T>
class AVL_Tree{
public:
    Error_code insert(const T & new_data);
    Error_code remove(const T & old_data);
private:
    AVL_Node<T> * _root;
};


template <typename T>
Error_code AVL_Tree<T>::insert(const T & new_data){
    bool taller;
    return avl_insert(_root, new_data, taller);
}

template <typename T>
Error_code AVL_Tree<T>::avl_insert(AVL_Node<T> * & sub_root, const T & new_data, bool & taller){
    Error_code result = success;
    if (sub_root == NULL){
        sub_root = new AVL_Node<T>(new_data);
        taller = true;
    }
    else if (new_data == sub_root->_data){
        result = duplicate_error;
        taller = false;
    }
    else if (new_data < sub_root->_data){
        result = avl_insert(sub_root->_left, new_data, taller);
        if (taller == true)
            switch (sub_root->get_balance()) {
                case left_higher:
                    left_balance(sub_root);// TODO:
                    taller = false;
                    break;
                case equal_height:
                    sub_root->set_balance(left_higher);
                    break;
                case right_higher:
                    sub_root->set_balance(equal_height);
                    taller = false;
                    break;
            }
    }
    else {   // insert in the right subtree
        result = avl_insert(sub_root->_right, new_data, taller);
        if (taller == true)
            switch(sub_root->get_balance()){
                case left_higher:
                    sub_root->set_balance(equal_height);
                    taller = false;
                    break;
                case equal_height:
                    sub_root->set_balance(right_higher);
                    break;
                case right_higher:
                    right_balance(sub_root); // TODO:
                    taller = false;
                    break;
            }
    }
    return result;
}

template <typename T>
void AVL_Tree<T>::rotate_left(AVL_Node<T> *& sub_root){
    if (sub_root == NUL || sub_root->_right == NULL)
        cout << "WARNING" << endl;
    else {
        AVL_Node<T> * right_tree = sub_root->_right;
        sub_root->_right = right_tree->_left;
        right_tree->left = sub_root;
        sub_root = right_tree;
    }
}

template <typename T>
void AVL_Tree::rotate_left(AVL_Tree<T> * & sub_root){
    if (sub_root == NULL ||)
}