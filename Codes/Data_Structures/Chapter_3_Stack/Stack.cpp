# include<iostream> 

typedef int ElementType;

class Stack{
	public:
		Stack(){
			size = 0;
		}
		bool empty(){
			return (size==0);
		}
		ElementType peek(){
			return elements[size-1];
		}
		ElementType push(ElementType value){
			return elements[size++] = value;
		}
		ElementType pop(){
//			Following 3 lines is for debug usage
//			return elements[--size];
			ElementType t = elements[--size];
			elements[size] = -1;
			return t;
		}
		int getSize(){
			return size;
		}
	private:
		int elements[100];
		int size;
};

int main(){
	Stack stack;
	for (int i = 0; i < 10; i++){
		stack.push(i);
	}
	while(!stack.empty())
	    std::cout << stack.pop() << " ";
	return 0;
}

