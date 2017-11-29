#include <iostream>
using namespace std;

enum Error_code{
    success,
    duplicate_error,
    not_found,
    is_null
};

template< typename T>
struct Node{
    T _data;
    Node<T> * _left;
    Node<T> * _right;
    Node(T data, Node<T> * left = NULL, Node<T> * right = NULL):_data(data),_left(left), _right(right){}
};

template <typename T>
class Binary_tree{
public:
    Binary_tree(){
        _root = NULL;
    }
    Node<T> * search_for_node(Node<T> * sub_root,const T & entry){
        if (sub_root == NULL) return NULL;
        if (entry < sub_root->_data){
            return search_for_node(sub_root->_left, entry);
        }
        else if ( entry > sub_root->_data){
            return search_for_node(sub_root->_right, entry);
        }
        else {
            return sub_root;
        }
    }   
    Error_code search_and_insert(Node<T> *& sub_root, const T & entry){
        if (sub_root == NULL){
            sub_root = new Node<T>(entry);
            return success;
        }
        else if (entry < sub_root->_data){
            return search_and_insert(sub_root->_left, entry);
        }
        else if (entry > sub_root->_data){
            return search_and_insert(sub_root->_right, entry);
        }
        else {
            return duplicate_error;
        }
    } 
    Error_code remove_root(Node<T> * & sub_root){
        if (sub_root == NULL)
            return is_null;
        Node<T> * to_delete = sub_root;
        if (sub_root->_left == NULL)
            sub_root = sub_root->_right;
        else if (sub_root->_right == NULL){
            sub_root = sub_root->_left;
        }
        else {
            Node<T> * parent = sub_root;
            to_delete = sub_root->_left;
            while (to_delete->_right){
                parent = to_delete;
                to_delete = to_delete->_right;
            }
            sub_root->_data = to_delete->_data;
            if (parent == sub_root){
                sub_root->_left = to_delete->_left;
            }
            else {
                parent->_right = to_delete->_left;
            }
        }
        delete to_delete;
        return success;        
    }
    Error_code search_and_destory(Node<T> *& sub_root, const T & entry){
        if (sub_root == NULL){
            return not_found;
        }
        else if (entry < sub_root->_data){
            return search_and_destory(sub_root->_left, entry);
        }
        else if (entry > sub_root->_data){
            return search_and_destory(sub_root->_right, entry);
        }
        else {
            return remove_root(sub_root);
        }
    }

    Error_code insert(const T & entry){
        return search_and_insert(_root, entry);
    }

    Error_code remove(const T & entry){
        return search_and_destory (_root, entry);
    }
    void inorder(Node<T> * sub_root, void (*visit)(const T &)){
        if (sub_root != NULL){
            inorder(sub_root->_left, visit);
            visit(sub_root->_data);
            inorder(sub_root->_right, visit);
        }
    }
    void preorder(Node<T> * sub_root, void (*visit)(const T &)){
        if (sub_root != NULL){
            visit(sub_root->_data);
            preorder(sub_root->_left);
            preorder(sub_root->_right);
        }
    }
    Node<T> * get_root(){
        return _root;
    }
private:
    Node<T>* _root;
};

void print(const int & a){
    cout << a << " ";
}

int main(){
    Binary_tree<int> t;
    for (int i = 10; i > 0; i--){
        t.insert(i);
        t.inorder(t.get_root(), print);
        cout << endl;
    }
    for (int i = 0; i < 10; i++){
        if (t.remove(i) == not_found)
            cout << "not_found error";
        t.inorder(t.get_root(), print);
        cout << endl;
    }
    cout << "!" << endl;
    return 0;
}