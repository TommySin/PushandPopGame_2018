#include <iostream>
#include <cassert>

using namespace std;
template <class Type>struct node {
	Type data;
	node<Type> *next;
};
template <class Type> class LinkedList {
	friend ostream& operator<<(ostream&, const LinkedList<Type>&);
public:
	const LinkedList<Type>& operator= (const LinkedList<Type>&) const;
	LinkedList();
	LinkedList(const LinkedList<Type>&);
	~LinkedList();
	void push_front(const Type &);
	void push_back(const Type &);
	void pop_front();
	void pop_back();
	Type front() const;
	Type back() const;
	bool empty() const;
	int size() const;
	void print() const;

	Type get(int n) const;
	void destroyList();
private:
	node<Type> *head;
	node<Type> *tail;
	int count;
	void copyList(const LinkedList<Type> &);

};

template <class Type>
LinkedList<Type>::LinkedList() {
	head = NULL;
	tail = NULL;
	count = 0;
}

template <class Type>
bool LinkedList<Type>::empty() const {
	return count == 0;
}

template <class Type>
int LinkedList<Type>::size() const {
	return count - 1;
}

template <class Type>
void LinkedList<Type>::push_front(const Type& item) {
	node<Type> *newNode = new node<Type>;
	newNode->data = item;
	newNode->next = head;
	if (empty())
		head = tail = newNode;
	else
		head = newNode;
	count++;
}

template <class Type>
void LinkedList<Type>::push_back(const Type& item) {
	node<Type> *newNode = new node<Type>;
	newNode->data = item;
	newNode->next = NULL;
	if (empty())
		head = tail = newNode;
	else {
		tail->next = newNode;
		tail = newNode;
	}
	count++;
}

template <class Type>
Type LinkedList<Type>::front() const {
	return head->data;
}


template <class Type>
Type LinkedList<Type>::back() const {
	return tail->data;
}

template <class Type>
void LinkedList<Type>::pop_front() {
	assert(!empty());
	node<Type> *temp = head;

	if (count == 1)
		head = tail = NULL;
	else
		head = head->next;
	count--;
}

template <class Type>
void LinkedList<Type>::pop_back() {
	assert(!empty());
	if (count == 1)
		head = tail = NULL;
	else {
		node<Type> *current = head;
		while (current->next != tail) {
			current = current->next;
		}
		tail = current;
		delete current->next;
		tail->next = NULL;
	}
	count--;
}

template <class Type>
void LinkedList<Type>::print()  const {
	cout << "[ ";
	node<Type> *current;
	current = head;
	while (current != NULL) {
		cout << current->data << " ";
		current = current->next;
	}
	cout << "]";
}

template <class Type> const LinkedList<Type>& LinkedList<Type>::operator= (const LinkedList<Type>& otherList) const {
	if (this != &otherList) copyList(otherList);
	return *this;
}

template <class Type>
void LinkedList<Type>::destroyList() {
	node<Type> *temp; // pointer for deallocation
	while (head != NULL) {
		temp = head;
		head = head->next;
		delete temp;
	}
	tail = NULL; // set last to NULL
	count = 0;
}


template <class Type>
LinkedList<Type>::~LinkedList() {
	destroyList();
}


template <class Type>
void LinkedList<Type>::copyList(const LinkedList<Type>& otherList) {
	node<Type> *newNode;
	node<Type> *current;
	if (head != NULL) destroyList();
	if (otherList.head == NULL) {
		head = tail = NULL;
		count = 0;
	}
	else {
		current = otherList.head;
		count = otherList.count;
		head = new node<Type>;
		head->data = current->data;
		head->next = NULL;
		tail = head;
		current = current->next;
		while (current != NULL) {
			newNode->data = current->data;
			newNode->next = NULL;
			tail->next = newNode;
			tail = newNode;
			current = current->next;
		}
	}
}


template <class Type>
LinkedList<Type>::LinkedList
(const LinkedList<Type>& otherList) {
	head = NULL;
	copyList(otherList);
}


template <class Type> ostream& operator<<(ostream& os, const LinkedList<Type>& list) {
	os << "[ ";
	node<Type> *current; //pointer for traversal
	current = list.head; //set current to point to head
	while (current != NULL) { // loop till end of list
		os << current->data << " ";
		current = current->next;
	}
	os << "]";
	return os;
}

template <class Type>
Type LinkedList<Type>::get(int n) const {
	node<Type> *curr;
	curr = head;
	cout << curr->data;
}


