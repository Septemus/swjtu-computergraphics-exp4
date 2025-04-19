#pragma once
template<typename T>
class ListItem {
public:
	T value;
	ListItem<T>* next;
	ListItem(T value) :value(value) {
		next = NULL;
	}
	ListItem() {
		next = NULL;
	}
};

template<typename T>
class MyList {
public:
	ListItem<T>* head;
	MyList() {
		head = new ListItem<T>();
	}
	~MyList() {
		ListItem<T>* ptr = head;
		ListItem<T>* last = NULL;
		while (ptr->next) {
			last = ptr;
			ptr = ptr->next;
			delete last;
		}
		delete ptr;
	}
	MyList<T>* fork() {
		MyList<T>* ret = new MyList<T>();
		ListItem<T>* ptr = head;
		while (ptr->next) {
			ret->push(ptr->next->value);
			ptr = ptr->next;
		}
		return ret;
	}
	ListItem<T>* getRear() {
		ListItem<T>* ptr = head;
		while (ptr->next) {
			ptr = ptr->next;
		}
		return ptr;
	}
	void push(ListItem<T>* li) {
		ListItem<T>* rear = getRear();
		;		rear->next = li;
	}
	void push(T value) {
		ListItem<T>* rear = getRear();
		rear->next = new ListItem<T>(value);
	}
};