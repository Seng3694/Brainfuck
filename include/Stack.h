#ifndef BRAINFUCK_STACK_H
#define BRAINFUCK_STACK_H

#include "Node.h"

typedef struct Stack Stack;

/**
* \brief Creates a new node stack. Can hold up to 256 nodes.
* \return The created stack.
*/
Stack* Stack_Create();
/**
* \brief Destroys the stack and frees memory.
* \param stack The stack to destroy.
*/
void Stack_Destroy(Stack* stack);

/**
* \brief Pushes a new node to the stack.
* Undefined behavior when pushing to a stack which is already full.
* \param stack The stack to push the value to.
* \param node The node to push to the stack.
*/
void Stack_Push(Stack* stack, Node* node);
/**
* \brief Removes the top node of the stack and returns it.
* \param stack The stack to pop from.
* \return The popped node. Is NULL if there are no items.
*/
Node* Stack_Pop(Stack* stack);

#endif
