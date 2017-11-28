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
Error_code AVL_Tree<T>::avl_insert(AVL_Node<T> * & sub_root, const T & new_data, bool & taller)
/* taller is true : the height of tree increased
将一个新节点插入到avl树
当成功插入时，保证该树的左右子树是符合avl树的性质的
若树的高度有变化，则开始检查当前根节点的avl树是否符合avl树的性质
并更新当前根节点的平衡因子
 */
{
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
                case left_higher: // 保证左子树的高度只比右子树的高度多2
                    left_balance(sub_root);// TODO:
                    // 在经过调整后，该子树的高度一定会与插入前的一致，不会对之后的造成影响。
                    taller = false;
                    break;
                case equal_height:
                    sub_root->set_balance(left_higher);
                    // taller = true; 保证了前提是taller=true，在这种条件下以sub_root为根的树高度变化了，所以就是true
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
    if (sub_root == NULL || sub_root->_right == NULL)
        cout << "WARNING" << endl;
    else {
        AVL_Node<T> * right_tree = sub_root->_right;
        sub_root->_right = right_tree->_left;
        right_tree->_left = sub_root;
        sub_root = right_tree;
    }
}

template <typename T>
void AVL_Tree::rotate_right(AVL_Tree<T> * & sub_root){
    if (sub_root == NULL || sub_root->_left == NULL)
        cout << "WARNING" << endl;
    else {
        AVL_Node<T> * left_tree = sub_root->_left;
        sub_root->_left = left_tree->_right;
        left_tree->_right = sub_root;
        sub_root = left_tree;
    }
}

template <typename T>
void AVL_Tree<T>::right_balance(AVL_Node<T> * & sub_root)
/*
    pre:
        在当前根节点为左低右高，右子树根节点也左低右高的前提下
        还往右子树插入了一个新点，"而且使得树的高度增加"
        树开始不平衡，需要该函数来调整
        此时：右子树的高度比左子树高度多2
    return:
        调整好的树，高度与添加节点前一致，也就是相当于高度不变。
        并且该树满足avl树的定义
 */
{
    AVL_Node<T> *& right_tree = sub_root->_right;
    switch(right_tree->get_balance()){
        case right_higher:// 在原来右子树的右子树高度多1的情况下树的高度还增加了，必定是因为插到了右子树，导致不平衡
            sub_root->set_balance(equal_height);
            right_tree->set_balance(equal_height);
            rotate_left(sub_root);
            break;
        case equal_height:// 树的高度不会变，不可能调用这个
            cout << "WARNING" << endl;
            break;
        case left_higher: // 插入到了右子树的左子树，右子树的左子树的高度增加1，不平衡
            AVL_Node<T> * sub_tree = right_tree->_left;
            switch(sub_tree->get_balance()){
                case equal_height:
                    sub_root->set_balance(equal_height);
                    right_tree->set_balance(equal_height);
                    break;
                case left_higher:
                    sub_root->set_balance(equal_height);
                    right_tree->set_balance(right_higher);
                    break
                case right_heigher:
                    sub_root->set_balance(left_higher);
                    right_tree->set_balance(equal_height);
                    break;
            }// 这里还是有点疑问的，具体的我画了个图方便理解
            sub_tree->set_balance(euqal_height);
            rotate_right(right_tree);
            rotate_left(sub_root);
            break;
    }
}

template<typename T>
void AVL_Tree<T>::left_balance(AVL_Node<T> *& sub_root){
    AVL_Node<T> *& left_tree = sub_root->_left;
    switch(left_tree->get_balance()){
        case right_higher:
            AVL_Node<T> * sub_tree = left_tree->_right;
            switch(sub_tree->get_balance()){
                case right_higher:

                    break;
                case equal_height:  

                    break;
                case left_higher:

                    break;
            }
            sub_root->set_balance(equal_height);
            rotate_left(left_tree);
            rotate_right(sub_root);
            break;
        case equal_height:
            cout << "WARNING" << endl;
            break;
        case left_higher:// 这种情形是固定的，只能是书本的那种情形，T2的高度是固定的
            sub_root->set_balance(equal_height);
            left_tree->set_balance(equal_height);
            rotate_right(sub_root);
            break;
    }
}