#include "Node.h"

#include <assert.h>
#include <stdlib.h>

Node* Node_Create(void)
{
	Node* node = malloc(sizeof(Node));
	assert(node);
	node->next = NULL;
	node->arg = 0;
	return node;
}

void Node_Destroy(Node* node)
{
	Node* current = node;
	Node* before = NULL;

	while (current != NULL)
	{
		before = current;
		current = current->next;
		free(before);
	}
}
