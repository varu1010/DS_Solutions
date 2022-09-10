/* Use this Queue class
class Queue {
	Queue (int capacity)
	int size()
	boolean isEmpty()
	int front()
	int back()
	void push(int element)
	void pop()
};
*/
// Implement the Stack class
// Implement the Stack class
class Stack {
public:
	Queue *q;
	Stack (int capacity) {
		q = new Queue(capacity);
	}
	bool isEmpty() {
		return(q->isEmpty());
	}
	
	int size() {
		return(q->size());
	}
	
	int top() {
		return(q->front());
	}
	
	void push(int element) {
		q->push(element);
		for(int i = 1; i < q->size(); i++) {
			q->push(q->front());
			q->pop();
		}
	}
	
	void pop() {
		q->pop();
	}
};
// using 2 queues
// Implement the Stack class
/*
class Stack {
private:
	int top_elm;
	Queue *q1, *q2;
public:
	
	Stack (int capacity) {
		q1 = new Queue(capacity);
		q2 = new Queue(capacity);
		top_elm = -1;
	}

	bool isEmpty() {
		return(q1->isEmpty());
	}
	
	int size() {
		return(q1->size());
	}
	
	int top() {
	if(q1->isEmpty())
			return -1;
		
		while(!q1->isEmpty())
		{
			q2->push(q1->front());
			if(q1->size() == 1)
				top_elm = q1->front();
			q1->pop();
			
		}
		
		while(!q2->isEmpty())
		{
			q1->push(q2->front());
			q2->pop();
		}
		return top_elm;
	}
	
	void push(int element) {
		q1->push(element);
	}
	
	void pop() {
		if(q1->isEmpty())
			return;
		
		while(!q1->isEmpty())
		{
			if(q1->size() == 1)
			{
				q1->pop();
				break;
			}
			q2->push(q1->front());
			q1->pop();

		}
		
		
		while(!q2->isEmpty())
		{
			q1->push(q2->front());
			q2->pop();
		}
		
	}
};
*/
