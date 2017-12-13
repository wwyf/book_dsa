#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int max(int a, int b){
    return (a>b)?a:b;
}


template<typename T>
struct Node{
    T entry_;
    Node* left_;
    Node* right_;
    int height_;

    Node(){}
    Node(T entry, 
        Node* left = NULL, 
        Node* right = NULL, 
        int height = 1
    ):
    entry_(entry),left_(left), right_(right), height_(height){}
    
    int get_height(){
        return height_;
    }
    void set_height(int height){
        height_ = height;
    }

    // 更新该节点以及所有子节点的高度
    void update_height(){
        // cout << " ! " << entry_ << endl;
        if (left_ != NULL) left_->update_height();
        if (right_ != NULL) right_->update_height();
        int left_height = (left_ == NULL)?1:left_->get_height();
        int right_height = (right_ == NULL)?1:right_->get_height();
        height_ = max(left_height, right_height)+1;
    }
};

template <typename T>
class AvlTree{
public:
    AvlTree(){
        root_ = NULL;
    }

    Node<T> * SingleRightRotate(Node<T> * sub_root){
        if (sub_root != NULL && sub_root->left_ != NULL){
            Node<T> * new_root = sub_root->left_;
            sub_root->left_ = new_root->right_;
            new_root->right_ = sub_root;
            return  new_root;
        }
        return sub_root;
    }

    Node<T> * LeftRightRotate(Node<T> * sub_root){
        sub_root->left_ = SingleLeftRotate(sub_root->left_);
        return SingleRightRotate(sub_root);
    }

    Node<T> * SingleLeftRotate(Node<T> * sub_root){
        if (sub_root != NULL && sub_root->right_ != NULL){
            Node<T> * new_root = sub_root->right_;
            sub_root->right_ = new_root->left_;
            new_root->left_ = sub_root;
            return new_root;
        }
        return sub_root;
    }

    Node<T> * RightLeftRotate(Node<T> * sub_root){
        sub_root->right_ = SingleRightRotate(sub_root->right_);
        return SingleLeftRotate(sub_root);
    }

    int height(Node<T> * sub_root){
        int h;
        if (sub_root == NULL)
            h = 1;
        else {
            int left_height = height(sub_root->left_);
            int right_height = height(sub_root->right_);
            h = max(left_height, right_height)+1;
        }
        return h;
    }


    int get_balance(Node<T> * sub_root){
        // if (sub_root == NULL)
        //     return 0;
        // return height(sub_root->left_)-height(sub_root->right_);

        int left_height = (sub_root->left_ == NULL)?1:sub_root->left_->get_height();
        int right_height = (sub_root->right_ == NULL)?1:sub_root->right_->get_height();
        return left_height - right_height;
    }

    void insert(T entry){
        root_ = AvlInsert(root_, entry);
    }

    Node<T>* AvlInsert(Node<T> * sub_root, T entry){
        if (sub_root == NULL){
            sub_root = new Node<T>(entry);
            return sub_root;
        }

        if (entry < sub_root->entry_)
            sub_root->left_ = AvlInsert(sub_root->left_, entry);
        else if (entry > sub_root->entry_)
            sub_root->right_ = AvlInsert(sub_root->right_, entry);
        else
            return sub_root;

        sub_root->update_height();// 更新该节点以及子节点的高度
        int balance = get_balance(sub_root);

        // left left
        if (balance > 1 && entry < sub_root->left_->entry_)
            return SingleRightRotate(sub_root);
        
        // right right
        if (balance < -1 && entry > sub_root->right_->entry_)
            return SingleLeftRotate(sub_root);
        
        // left right
        if (balance > 1 && entry > sub_root->left_->entry_)
            return LeftRightRotate(sub_root);
        
        // right left
        if (balance < -1 && entry < sub_root->right_->entry_)
            return RightLeftRotate(sub_root);

        return sub_root;

    }

    Node<T> * maxValueNode(Node<T> * sub_root){
        Node<T> * cur_node = sub_root;
        while (cur_node->right_ != NULL){
            cur_node = cur_node->right_;
        }
        return cur_node;
    }

    void my_delete(T key){
        root_ = AvlDelete(root_, key);
    }

    Node<T> * AvlDelete(Node<T> * sub_root, T key){
        if (sub_root == NULL)
            return sub_root;
        
        if (key < sub_root->entry_)
            sub_root->left_ = AvlDelete(sub_root->left_, key);
        else if (key > sub_root->entry_)
            sub_root->right_ = AvlDelete(sub_root->right_, key);
        
        else {
            if ((sub_root->left_ == NULL) || (sub_root->right_ == NULL)){
                Node<T> * to_delete = sub_root->left_ ? sub_root->left_ : sub_root->right_;

                if (to_delete == NULL){
                    to_delete = sub_root;
                    sub_root = NULL;
                }
                else 
                    *sub_root = *to_delete;
                delete to_delete;
            }
            else {
                Node<T> * to_delete = maxValueNode(sub_root->left_);
                sub_root->entry_ = to_delete->entry_;
                sub_root->left_ = AvlDelete(sub_root->left_, to_delete->entry_);
            }
        }

        if (sub_root == NULL){
            return sub_root;
        }

        sub_root->update_height();
        int balance = get_balance(sub_root);

        // left left
        if (balance > 1 && get_balance(sub_root->left_) >= 0 )// 注意等号
            return SingleRightRotate(sub_root);
        // left right
        if (balance > 1 && get_balance(sub_root->left_) < 0 ){
            return LeftRightRotate(sub_root);
        }

        if (balance < -1 && get_balance(sub_root->right_) <= 0){
            return SingleLeftRotate(sub_root);
        }

        if (balance < -1 && get_balance(sub_root->right_) > 0){
            return RightLeftRotate(sub_root);
        }

        return sub_root;
    }


    void PrintInOrder(Node<T> * root){
        if (root != NULL){
            PrintInOrder(root->left_);
            cout << root->entry_ << " ";
            PrintInOrder(root->right_);
        }
    }


    void PrintTree(Node<T> * sub_root, int level){
        if (sub_root != NULL){
            PrintTree(sub_root->left_, level+1);
            for (int i = 0; i < level; i++)
                cout << "        |";
            // cout <<sub_root->height_ << "|" << sub_root->entry_ << "|" << get_balance(sub_root) << endl;
            cout << sub_root->entry_ << endl;
            PrintTree(sub_root->right_, level+1);
        }
        else {
            for (int i = 0; i < level; i++)
                cout << "        |";
            cout << "NULL" << endl;
        }
    }

    void print(){
        PrintTree(root_, 0);
    }
    bool IsAvlTree(Node<T> * sub_root){
        if (sub_root == NULL)
            return true;
        if (IsAvlTree(sub_root->left_) && IsAvlTree(sub_root->right_)){
            int left_height = height(sub_root->left_);
            int right_height = height(sub_root->right_);
            int balance = left_height - right_height;
            if (-1 <= balance && balance <= 1) 
                return true;
            else 
                return false;
        }
        // else one of the sub tree is not an avl tree
        return false;
    }

    Node<T> * get_root(){
        return root_;
    }

private:
    Node<T> * root_;
};





int main(){
    AvlTree<int> t;
    srand(time(0));
    for (int i = 0; i < 200; i++){
        t.insert(rand()%100);
        if (!t.IsAvlTree(t.get_root())) {
            t.print();
            cout << "WARNING" << endl;
            break;
            cout << "----------------------------------" << endl;
        }
    }

    for (int i = 0; i < 200; i++){
        int num = rand() % 100;
        t.my_delete(num);
        if (!t.IsAvlTree(t.get_root())) {
            cout << "!!!" << num << "!!!!" << endl;
            t.print();
            cout << "WARNING" << endl;
            break;
            cout << "----------------------------------" << endl;
        }
    }

    return 0;
}