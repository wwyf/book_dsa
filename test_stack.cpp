#include<iostream>

using namespace std;

template<typename T>
struct Node 
{
		T data;
		Node *next;
		Node(T item, Node *_next = NULL):data(item),next(_next){}	
		Node():Node(0) {}
};

template<typename T>
class Stack{
public:
	Stack(){
		top_node = NULL;
		count = 0;
	}
	Stack(const Stack & rhs){
		Node<T> *new_cpy = NULL, *new_top = NULL, *old_top = rhs.top_node;
		if (!rhs.empty()){
			new_cpy = new_top = new Node<T>(old_top->data);
			while (new_cpy->next){
				old_top = old_top->next;
				new_cpy = new Node<T>(old_top->data);
				new_cpy = new_cpy->next;
			}
		}
		top_node = new_top;
		count = rhs.size();
	}
	void push(T item){
		Node<T> *new_node = new Node<T>(item,top_node);
		top_node = new_node;
		count++;
	}
	
	T top() const{
		if (empty()){
			cout << "This stack is empty" << endl;
			return -1;
		}
		return top_node->data;
	}	

	void pop() {
		if (empty()){
			cout << "This stack is empty" << endl;
			return ;
		}
		Node<T> *del_node = top_node;
		top_node = top_node->next;
		delete del_node;
		count--;
		return ;
	}

	bool empty() const{
		return !count;
	}

	int size(){
		return count;
	}

	const Stack & operator=(const Stack & rhs){
		Node<T> *new_cpy = NULL,*new_top = NULL, *old_top = rhs.top_node;
		if (!rhs.empty()){
			new_cpy = new_top = new Node<T>(old_top->data);
			while (old_top->next){
				old_top = old_top->next;
				new_cpy->next = new Node<T>(old_top->data);
				new_cpy = new_cpy->next;
			}
		}
		clear();
		top_node = new_top;
		count = rhs.size();
	}

	void clear(){
		while(empty()){
			pop();
		}
		top_node = NULL;
		count = 0;
	}
	void print() const {
		Node<T> *cur_node = top_node;
		while (cur_node){
			cout << cur_node->data << endl;
			cur_node = cur_node->next;
		}
		cout << endl;
	}
private:
	Node<T> *top_node;
	int count;
};


int main(){
	Stack<int> test;
	for (int i = 0; i < 10; i++){
		test.push(i);
	}

	test.print();
	for (int i = 0; i < 11; i++){
		cout << test.top() << " !!";
		test.pop();
		test.print();
	}


	return 0;
}