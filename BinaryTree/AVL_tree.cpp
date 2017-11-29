#include <iostream>
#include <queue>
using namespace std;

enum Balance_factor{
    left_higher, 
    equal_height,
    right_higher
};

enum Error_code{
    success,
    duplicate_error,
    not_found
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
    AVL_Node(T data, AVL_Node<T> * left = NULL, AVL_Node<T> * right = NULL,
                Balance_factor b = equal_height){
        _data = data;
        _left = left;
        _right = right;
        _balance = b;
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
    AVL_Tree(){
        _root = NULL;
    }
    void traverse_preorder(void (*visit)(const T &)){
        preorder(_root, visit);
    }
    void traverse_inorder(void (*visit)(const T &)){
        inorder(_root, visit);
    }
    void traverse_postorder(void (*visit)(const T &)){
        postorder(_root, visit);
    }
    void traverse_bfsorder(void (*visit)(const T & )){
        bfsorder(_root, visit);
    }
    void preorder(AVL_Node<T> * sub_root, void (*visit)(const T &));
    void inorder(AVL_Node<T> * sub_root, void (*visit)(const T &));
    void postorder(AVL_Node<T> * sub_root, void (*visit)(const T &));
    void bfsorder(AVL_Node<T> * sub_root, void (*visit)(const T &));
    Error_code insert(const T & new_data);
    Error_code avl_insert(AVL_Node<T> * & sub_root, const T & new_data, bool & taller);
    Error_code remove(const T & old_data);
    Error_code remove_avl(AVL_Node<T> *&sub_root,const T &target, bool &shorter);
    Error_code remove_avl_right(AVL_Node<T> *&sub_root,const T & target, bool &shorter);
    Error_code remove_avl_left(AVL_Node<T> *&sub_root,const T & target, bool &shorter);
    
    void rotate_left(AVL_Node<T> * & sub_root);
    void rotate_right(AVL_Node<T> * & sub_root);
    void right_balance(AVL_Node<T> * & sub_root);
    void left_balance(AVL_Node<T> *& sub_root);

    AVL_Node<T> * get_root(){
        return _root;
    }
private:
    AVL_Node<T> * _root;
};

template <typename T>
void AVL_Tree<T>::preorder(AVL_Node<T> * sub_root, void (*visit)(const T &)){
    if (sub_root){
        visit(sub_root->_data);
        preorder(sub_root->_left, visit);
        preorder(sub_root->_right, visit);
    }
}

template <typename T>
void AVL_Tree<T>::inorder(AVL_Node<T> * sub_root, void (*visit)(const T &)){
    if (sub_root){
        inorder(sub_root->_left, visit);
        visit(sub_root->_data);
        inorder(sub_root->_right, visit);
    }
}

template <typename T>
void AVL_Tree<T>::postorder(AVL_Node<T> * sub_root, void (*visit)(const T &)){
    if (sub_root){
        postorder(sub_root->_left, visit);
        postorder(sub_root->_right, visit);
        visit(sub_root->_data);
    }
}

template <typename T>
void AVL_Tree<T>::bfsorder(AVL_Node<T> * sub_root, void (*visit)(const T &)){
    queue<AVL_Node<T> *> node_queue;
    node_queue.push(sub_root);
    while(!node_queue.empty()){
        AVL_Node<T> * cur_node = node_queue.front();
        node_queue.pop();
        if (cur_node){
            visit(cur_node->_data);
            node_queue.push(cur_node->_left);
            node_queue.push(cur_node->_right);
        }
        else {
            cout << "NULL ";
        }
    }

}

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
                    right_balance(sub_root);
                    taller = false;
                    break;
            }
    }
    return result;
}

template<typename T>
Error_code AVL_Tree<T>::remove(const T & old_data){
    bool shorter = true;
    return remove_avl(_root, old_data, shorter);
}

template <class T>
Error_code AVL_Tree<T>::remove_avl(AVL_Node<T> *&sub_root,const T &target, bool &shorter)
{
    AVL_Node<T> *temp;
    if (sub_root == NULL){
        shorter = false;
        return not_found;
    }
    else if (target < sub_root->_data)
        return remove_avl_left(sub_root, target, shorter);
    else if (target > sub_root->_data)
        return remove_avl_right(sub_root, target, shorter);
    else if (sub_root->_left == NULL)
    {                    // Found target: delete current node.
        temp = sub_root; // Move right subtree up to delete node.
        sub_root = sub_root->_right;
        delete temp;
        shorter = true;
    }
    else if (sub_root->_right == NULL)
    {
        temp = sub_root; // Move left subtree up to delete node.
        sub_root = sub_root->_left;
        delete temp;
        shorter = true;
    }
    else if (sub_root->get_balance() == left_higher)
    {
        // Neither subtree is empty; delete from the taller.
        temp = sub_root->_left;
        // Find predecessor of target and delete it from left tree.
        while (temp->_right != NULL)
            temp = temp->_right;
        sub_root->_data = temp->_data;
        remove_avl_left(sub_root, temp->_data, shorter);
    }
    else
    { // Find successor of target and delete from right.
        temp = sub_root->_right;
        while (temp->_left != NULL)
            temp = temp->_left;
        sub_root->_data = temp->_data;
        remove_avl_right(sub_root, temp->_data, shorter);
    }
    return success;
}
template <class T>
Error_code AVL_Tree<T>::remove_avl_right(AVL_Node<T> *&sub_root,const T & target, bool &shorter)
{
    Error_code result = remove_avl(sub_root->_right, target, shorter);
    if (shorter == true)
        switch (sub_root->get_balance())
        {
        case equal_height: // case 1 in text
            sub_root->set_balance(left_higher);
            shorter = false;
            break;
        case right_higher: // case 2 in text
            sub_root->set_balance(equal_height);
            break;
        case left_higher:
            // case 3 in text: shortened shorter subtree; must rotate
            AVL_Node<T> *temp = sub_root->_left;
            switch (temp->get_balance())
            {
            case equal_height: // case 3a
                temp->set_balance(right_higher);
                rotate_right(sub_root);
                shorter = false;
                break;
            case left_higher: // case 3b
                sub_root->set_balance(equal_height);
                temp->set_balance(equal_height);
                rotate_right(sub_root);
                break;
            case right_higher: // case 3c; requires double rotation
                AVL_Node<T> *temp_right = temp->_right;
                switch (temp_right->get_balance())
                {
                case equal_height:
                    sub_root->set_balance(equal_height);
                    temp->set_balance(equal_height);
                    break;
                case left_higher:
                    sub_root->set_balance(right_higher);
                    temp->set_balance(equal_height);
                    break;
                case right_higher:
                    sub_root->set_balance(equal_height);
                    temp->set_balance(left_higher);
                    break;
                }
                temp_right->set_balance(equal_height);
                rotate_left(sub_root->_left);
                rotate_right(sub_root);
                break;
            }
        }
    return result;
}
template <class T>
Error_code AVL_Tree<T>::remove_avl_left(AVL_Node<T>
                                                 *&sub_root,
                                             const T &target, bool &shorter)
{
    Error_code result = remove_avl(sub_root->_left, target, shorter);
    if (shorter == true)
        switch (sub_root->get_balance())
        {
        case equal_height: // case 1 in text
            sub_root->set_balance(right_higher);
            shorter = false;
            break;
        case left_higher: // case 2 in text
            sub_root->set_balance(equal_height);
            break;
        case right_higher:
            // case 3 in text: shortened shorter subtree; must rotate
            AVL_Node<T> *temp = sub_root->_right;
            switch (temp->get_balance())
            {
            case equal_height: // case 3a
                temp->set_balance(left_higher);
                rotate_left(sub_root);
                shorter = false;
                break;
            case right_higher: // case 3b
                sub_root->set_balance(equal_height);
                temp->set_balance(equal_height);
                rotate_left(sub_root);
                break;
            case left_higher: // case 3c; requires double rotation
                AVL_Node<T> *temp_left = temp->_left;
                switch (temp_left->get_balance())
                {
                case equal_height:
                    sub_root->set_balance(equal_height);
                    temp->set_balance(equal_height);
                    break;
                case right_higher:
                    sub_root->set_balance(left_higher);
                    temp->set_balance(equal_height);
                    break;
                case left_higher:
                    sub_root->set_balance(equal_height);
                    temp->set_balance(right_higher);
                    break;
                }
                temp_left->set_balance(equal_height);
                rotate_right(sub_root->_right);
                rotate_left(sub_root);
                break;
            }
        }
    return result;
}

    template <typename T>
    void AVL_Tree<T>::rotate_left(AVL_Node<T> * &sub_root)
    {
        if (sub_root == NULL || sub_root->_right == NULL)
            cout << "WARNING" << endl;
        else
        {
            AVL_Node<T> *right_tree = sub_root->_right;
            sub_root->_right = right_tree->_left;
            right_tree->_left = sub_root;
            sub_root = right_tree;
        }
    }

    template <typename T>
    void AVL_Tree<T>::rotate_right(AVL_Node<T> * &sub_root)
    {
        if (sub_root == NULL || sub_root->_left == NULL)
            cout << "WARNING" << endl;
        else
        {
            AVL_Node<T> *left_tree = sub_root->_left;
            sub_root->_left = left_tree->_right;
            left_tree->_right = sub_root;
            sub_root = left_tree;
        }
    }

  template <typename T>
    void AVL_Tree<T>::right_balance(AVL_Node<T> * &sub_root)
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
        AVL_Node<T> *&right_tree = sub_root->_right;
        switch (right_tree->get_balance())
        {
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
                    break;
                case right_higher:
                    sub_root->set_balance(left_higher);
                    right_tree->set_balance(equal_height);
                    break;
            }// 这里还是有点疑问的，具体的我画了个图方便理解
            sub_tree->set_balance(equal_height);
            rotate_right(right_tree);
            rotate_left(sub_root);
            break;
    }
}

template<typename T>
void AVL_Tree<T>::left_balance(AVL_Node<T> *& sub_root){
    AVL_Node<T> *& left_tree = sub_root->_left;
    switch(left_tree->get_balance()){
        case equal_height:
            cout << "WARNING" << endl;
            break;
        case left_higher:// 这种情形是固定的，只能是书本的那种情形，T2的高度是固定的
            sub_root->set_balance(equal_height);
            left_tree->set_balance(equal_height);
            rotate_right(sub_root);
            break;
        case right_higher:
            AVL_Node<T> * sub_tree = left_tree->_right;
            switch(sub_tree->get_balance()){
                case right_higher:
                   left_tree->set_balance(left_higher);
                   sub_root->set_balance(equal_height);
                    break;
                case equal_height:
                    left_tree->set_balance(equal_height);
                    sub_root->set_balance(equal_height);  
                    break;
                case left_higher:
                    left_tree->set_balance(equal_height);
                    sub_root->set_balance(right_higher);
                    break;
            }
            sub_tree->set_balance(equal_height);
            rotate_left(left_tree);
            rotate_right(sub_root);
            break;   
       }
}


void print(const int & a){
    cout << a << " ";
}

int main(){
    AVL_Tree<int> test;
    test.insert(5);
    for (int i = 2; i < 10; i++){
        if (test.insert(i) == duplicate_error)
            cout << "duplicate_error";
        test.traverse_inorder(print);
        cout << endl;
        cout << "current root is " << test.get_root()->_data << endl;
        cout << "!!!  ";
        test.traverse_bfsorder(print);
        cout << endl;
    }
    for (int i = 11; i > 2; i--){
        cout << "delete node " << i << endl;
        if (test.remove(i) == not_found)
            cout << "not_found error";
        test.traverse_inorder(print);
        cout << endl;
        cout << "current root is " << test.get_root()->_data << endl;
        cout << "!!!  ";
        test.traverse_bfsorder(print);
        cout << endl;
    }
    return 0;
}