#ifndef BRAINFUCK_NODE_H
#define BRAINFUCK_NODE_H

#define NODE_TYPE_ADD     (unsigned char)0 /**< + and - */
#define NODE_TYPE_MEM_ADD (unsigned char)1 /**< < and > */
#define NODE_TYPE_JEZ     (unsigned char)2 /**< "jump equal zero" => "[" */
#define NODE_TYPE_JNZ     (unsigned char)3 /**< "jump not zero" => "]" */
#define NODE_TYPE_PRINT   (unsigned char)4 /**< . */
#define NODE_TYPE_INPUT   (unsigned char)5 /**< , */

/**
* Because the argument used in a node can be a pointer address we have to make sure
* we can hold addresses on both x86 and x64 architectures.
*/
#ifdef ENV_64
typedef long long ARG_TYPE;
#elif ENV_86
typedef long ARG_TYPE;
#endif

/**
* \brief The Node struct.
* Holds information depending on the node type:
* - ADD: how much to add to the address the memory pointer is pointing to
* - MEM_ADD: how much to add to the memory pointer
* - JEZ: the address to jump to if the value is zero
* - JNZ: the address to jump to if the value is not zero
*/
typedef struct Node 
{
	struct Node* next;  /**< Next node to execute */
	ARG_TYPE arg;       /**< Type dependant argument */
	unsigned char type; /**< The node type */
} Node;

/**
* \brief Creates a new node.
* \return Returns the created node.
*/
Node* Node_Create(void);
/**
* \brief Destroys the node and frees memory.
* \param node The node to destroy.
*/
void Node_Destroy(Node* node);

#endif
