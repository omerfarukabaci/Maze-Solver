#define SIZE 25
typedef struct d{
	int x;
	int y;
	int right;
	int left;
	int down;
	int up;
	int camefrom;
}StackDataType, position;

struct Stack{
	StackDataType element[SIZE];
	int top;
	void create();
	void push(StackDataType);
	StackDataType pop();
	bool isempty();
};


