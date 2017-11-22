#include <iostream>
using namespace std;

enum Error_code{
    success,
    failed,
    not_present
};

template <typename T>
struct Node{
    T _data;
    Node *_left;
    Node *_right;
    Node(T data, Node* left = NULL, Node* right = NULL):_data(data), _left(left), _right(right){}
};

template <typename T >
class Binary_tree{
public:
    Binary_tree(){
        _root = NULL;
    }
    
    Error_code insert(T new_entry){
        return search_and_insert(new_entry, _root);
    }
    Error_code search_and_insert(T new_entry, Node<T> * &root){
        if(root == NULL) {
            root = new Node<T>(new_entry);// need to update the father
            return success;
        }
        else {
            if (root->_data == new_entry) return failed;
            else {
                if (root->_data < new_entry)
                    return search_and_insert(new_entry, root->_right);
                else
                    return search_and_insert(new_entry, root->_left);
            }
        }

    }

    // Node<T> * search_for_node(T search_entry, Node<T> * sub_root) const{
    //     if (sub_root == NULL)
    //         return NULL;
    //     else if (search_entry == sub_root->_data)
    //         return sub_root;
    //     else if (search_entry < sub_root->_data)
    //         return search_for_node(search_entry, sub_root->_left);
    //     else
    //         return search_for_node(search_entry, sub_root->_right);
    // }

    Node<T> * search_for_node(T search_entry, Node<T> * sub_root) const{
        Node<T> * cur_node = sub_root;
        while(cur_node){
            if (search_entry == cur_node->_data)
                return cur_node;
            else if (search_entry < cur_node->_data)    
                cur_node = cur_node->_left;
            else 
                cur_node = cur_node->_right;
        }
        return NULL;
    }

    Error_code remove_root(Node<T> * &sub_root){
        if (sub_root == NULL) return not_present;
        Node<T>* to_delete = sub_root;
        if (sub_root->_left == NULL) sub_root = sub_root->_right;
        else if (sub_root->_right == NULL) sub_root = sub_root->_left;
        else {
            to_delete = sub_root->_left;
            Node<T> * parent = sub_root;
            while (to_delete->_right){
                parent = to_delete;
                to_delete = to_delete->_right;
            }
            sub_root->_data = to_delete->_data;
            if (parent == sub_root)
                sub_root->_left = to_delete->_left;
            else
                parent->_right = to_delete->_left;
        }
        delete to_delete;
        return success;
    }

    Error_code search_and_destory(T search_entry, Node<T> *& sub_root){
        if (sub_root == NULL || sub_root->_data == search_entry)
            return remove_root(sub_root);
        else if (search_entry < sub_root->_data)
            return search_and_destory(search_entry, sub_root->_left);
        else
            return search_and_destory(search_entry, sub_root->_right);
    }

    Error_code remove(T search_entry){
        return search_and_destory(search_entry, _root);
    }

    void preorder(void (*visit)(Node<T>*), Node<T> * root){
        if (root != NULL){
            visit(root);
            preorder(visit, root->_left);
            preorder(visit, root->_right);
        }
    }

    void inorder(void (*visit)(Node<T>*), Node<T> *root){
        if (root != NULL){
            inorder(visit, root->_left);
            visit(root);
            inorder(visit, root->_right);
        }
    }

    void postorder(void (*visit)(Node<T>*), Node<T> *root){
        if (root != NULL){
            postorder(visit, root->_left);
            postorder(visit, root->_right);
            visit(root);
        }
    }

    Node<T> * get_root(){
        return _root;
    }
private:
    Node<T> *_root;
};

template <typename T >
void print(Node<T> * cur_node){
    cout << cur_node->_data << " ";
}

int main(){
    Binary_tree<int> t;
    t.insert(10);
    for (int i = 5; i < 15; i++){
        cout << t.insert(i) << endl;
        t.inorder(print, t.get_root());
        cout << endl;
    }
    Node<int>* to_delete = t.search_for_node(12, t.get_root());
    t.remove(12);
    t.inorder(print, t.get_root());
    return 0;
}




