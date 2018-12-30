#include "Stack.h"
#include "Node.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Stack
{
	Node** items;
	unsigned char count;
};

Stack* Stack_Create()
{
	Stack* stack = malloc(sizeof(Stack));
	assert(stack);
	stack->count = 0;
	stack->items = malloc(sizeof(Node*) * 0x100);
	assert(stack->items);
	return stack;
}

void Stack_Destroy(Stack* stack)
{
	stack->count = 0;
	free(stack->items);
	free(stack);
}

void Stack_Push(Stack* stack, Node* node)
{
	stack->items[stack->count] = node;
	stack->count++;
}

Node* Stack_Pop(Stack* stack)
{
	if (stack->count == 0)
		return NULL;
	stack->count--;
	Node* node = stack->items[stack->count];
	stack->items[stack->count] = NULL;
	return node;
}
