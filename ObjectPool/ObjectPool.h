#pragma once
#include "singletonBase.h"

template <typename T>
struct Node 
{
	Node<T>* prevNode;
	Node<T>* nextNode;
	T data;
};

template <typename T>
class ObjectPool : public singletonBase<ObjectPool<T>>{
private:
	Node<T>* poolHead;
	Node<T>* poolTail;
	Node<T>* lockHead;
	Node<T>* lockTail;
	int poolSize;
	int lockSize;
	int maxPoolSize;
public:
	//ObjectPool() 초기값 부여
	ObjectPool() {
		poolHead = nullptr;
		poolTail = nullptr;
		lockHead = nullptr;
		lockTail = nullptr;
		poolSize = 0;
		lockSize = 0;
		maxPoolSize = 0;
	}
	~ObjectPool() {

	}
	//void Init(int inputSize) inputSize만큼 미리 할당
	void Init(int inputSize) {
		maxPoolSize = inputSize;
		for (int i = 0; i < inputSize; i++) {
			createNode();
		}
	}
	//void createNode 새로운 노드 생성
	void createNode() {
 		Node<T>* tempNode = new Node<T>;

		if (poolHead == nullptr) {
			tempNode->nextNode = nullptr;
			tempNode->prevNode = nullptr;
			poolHead = tempNode;
			poolTail = tempNode;
		}
		else {
			tempNode->prevNode = poolTail;
			tempNode->nextNode = nullptr;
			poolTail->nextNode = tempNode;
			poolTail = tempNode;
		}
		poolSize++;
	}
	//T* getObject() 오브젝트 풀의 노드 데이터의 주소를 콜한 대상에게 반환
	T* getObject() {
		Node<T>* getTemp;
		if (poolHead == nullptr) {
			createNode();
		}

		getTemp = poolHead;

		if (poolHead == poolTail) {
			poolHead = nullptr;
			poolTail = nullptr;
		}
		else {
			poolHead = poolHead->nextNode;
		}

		if (lockHead == nullptr) {
			getTemp->prevNode = nullptr;
			getTemp->nextNode = nullptr;
			lockHead = getTemp;
			lockTail = getTemp;
		}
		else {
			getTemp->prevNode = lockTail;
			getTemp->nextNode = nullptr;
			lockTail->nextNode = getTemp;
			lockTail = getTemp;
		}
		poolSize--;
		lockSize++;
		return &(getTemp->data);
	}
	//void returnObject(T* inputData) 반환된 노드 데이터의 주소를 풀로 복귀
	void returnObject(T* inputData) {
		Node<T>* returnTemp = FindNode(inputData, lockHead);
		
		if (lockHead == nullptr) {

		}

		if (returnTemp == lockHead) {
			lockHead = lockHead->nextNode;
			if(lockHead!= nullptr)lockHead->prevNode = nullptr;
		}
		else if (returnTemp == lockTail) {
			lockTail = lockTail->prevNode;
			lockTail->nextNode = nullptr;
		}
		else {
			returnTemp->nextNode->prevNode = returnTemp->prevNode;
			returnTemp->prevNode->nextNode = returnTemp->nextNode;
		}
		
		if(poolHead == nullptr){
			returnTemp->prevNode = nullptr;
			returnTemp->nextNode = nullptr;
			poolHead = returnTemp;
			poolTail = returnTemp;
		}
		else {
			returnTemp->prevNode = poolTail;
			returnTemp->nextNode = nullptr;
			poolTail->nextNode = returnTemp;
			poolTail = returnTemp;
		}
		poolSize++;
		lockSize--;
	}
	//Node<T>* FindNode(T* inputData, Node<T>* listHead) listHead에 해당하는 리스트의 모든 원소를 순회하여 inputData와 일치하는 Data를 가진 노드를 검색
	Node<T>* FindNode(T* inputData, Node<T>* listHead) {
		Node<T>* iter = listHead;
		while (true) {
			if (iter == nullptr) {
				return nullptr;
			}
			else if (&(iter->data) == inputData) {
				return iter;
			}
			iter = iter->nextNode;
		}
	}
	//디버그용 poolList Size gether
	int GetPoolSize() {
		return poolSize;
	}
	//디버그용 lockList Size gether
	int GetLockSize() {
		return lockSize;
	}
	int ActualPoolSize() {
		return GetListSize(poolHead);
	}
	int ActualLockSize() {
		return GetListSize(lockHead);
	}
	int GetListSize(Node<T>* listhead) {
		Node<T>* iter = listhead;
		int cnt = 0;
		while (true) {
			if (iter == nullptr) {
				break;
			}
			else {
				cnt++;
			}
			iter = iter->nextNode;
		}
		return cnt;
	}
};