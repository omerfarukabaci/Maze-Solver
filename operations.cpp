#include "stack.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstring>

using namespace std;

void Stack::create(){
	top = 0;
}
void Stack::push(StackDataType newelement){
	element[top++] = newelement;
}
StackDataType Stack::pop(){
	return element[--top];
}
bool Stack::isempty(){
	return (top == 0);
}
