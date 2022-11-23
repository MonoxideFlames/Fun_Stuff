//
//  DoubleStack.h
//  CPPProject
//
//  Created by Adith Talupuru on 11/22/22.
//

#ifndef DoubleStack_h
#define DoubleStack_h
#include <iostream>
template<typename T>
class DoubleStack {
public:
	unsigned int front;//maximum value is capacity. grows downward. full stack
	unsigned int back;//minimum value is 0. grows upward. empty stack
	T* arr;
	unsigned int capacity;
	unsigned int maxCapacity;
	
	DoubleStack(unsigned int cap = 8): front(0), maxCapacity(4096){
		cap--;
		cap |= (cap >> 1);
		cap |= (cap >> 2);
		cap |= (cap >> 4);
		cap |= (cap >> 8);
		cap |= (cap >> 16);
		cap++;
		
		capacity = cap;
		back = cap;
		arr = new T[capacity];
	}
	DoubleStack(const DoubleStack& other){
		arr = new T[other.capacity];
		front = 0;
		back = other.capacity;
		capacity = other.capacity;
		maxCapacity = other.maxCapacity;
		
		for(unsigned int i = 0; i < capacity; i++){//copy the elements over
			arr[i] = other.arr[i];
		}
	}
	~DoubleStack(){
		delete[] arr;
	}
	void pushBack(T data){
		if(front == back){
			if(capacity == maxCapacity){
				return;
			}
			grow();
		}
		arr[--back] = data;//full stack
	}
	void pushFront(T data){
		if(front == back){
			if(capacity == maxCapacity){
				return;
			}
			grow();
		}
		arr[front++] = data;//empty stack
	}
	unsigned int size(){
		return front + (capacity - back);
	}
	unsigned int backSize(){
		return (capacity - back);
	}
	unsigned int frontSize(){
		return front;
	}
	T getFront(){
		if(front == 0){
			std::cout << "EMPTY STACK";
			return arr[0];
		}
		return arr[front - 1];
	}
	T getBack(){
		if(back == capacity){
			std::cout << "EMPTY STACK";
			return arr[capacity - 1];
		}
		return arr[back];
	}
	T popFront(){
		unsigned int size = (front + (capacity - back));
		if((size > 8) && (size <= (capacity >> 2))){
			trim();
		}
		if(front == 0){
			std::cout << "Empty Stack!";
			return arr[front];
		}
		return arr[--front];//empty stack
	}
	T popBack(){
		unsigned int size = (front + (capacity - back));
		if((size > 8) && (size <= (capacity >> 2))){
			trim();
		}
		if(back == capacity){
			std::cout << "Empty Stack!";
			return arr[back - 1];
		}
		return arr[back++]; //full stack
	}
private:
	void grow(){
		T* newArr = new T[capacity << 1];
		for(unsigned int i = 0; i < front; i++){
			newArr[i] = arr[i];
		}
		for(unsigned int i = capacity - 1, j = (capacity << 1) - 1; i > back; i--, j--){
			newArr[j] = arr[i];
		}
		newArr[back + capacity] = arr[back];//back could be zero, so we need to go this route
		
		back += capacity;//since we basically got a capacity's worth of free addresses below back.
		capacity = capacity << 1;
		delete[] arr;
		arr = newArr;
	}
	void trim() {
		T* newArr = new T[capacity >> 2];
		for(unsigned int i = 0; i < front; i++){
			newArr[i] = arr[i];
		}
		for(unsigned int i = capacity - 1, j = (capacity >> 2) - 1; i >= back; i--, j--){//back is guaranteed to be nonzero here.
			newArr[j] = arr[i];
		}
		back -= ((capacity * 3) >> 2);//we lost 3/4 capacity's worth of addresses below back
		capacity = capacity >> 2;
		delete[] arr;
		arr = newArr;
	}
};
#endif /* DoubleStack_h */
