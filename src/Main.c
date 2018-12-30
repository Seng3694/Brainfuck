#include "Node.h"
#include "Stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Node* parse(const char* str);
static Node* parse_string(const char* str);
static void run(Node* root);

int main(int argc, char** argv)
{
	if (argc == 2)
	{
		Node* root = parse(argv[1]);
		if (!root)
		{
			puts("error while parsing\n");
		}
		else
		{
			run(root);
			Node_Destroy(root);
		}
	}

	return 0;
}

static Node* parse(const char* str)
{
	FILE* file = fopen(str, "r");
	Node* root = NULL;

	if (file)
	{
		fseek(file, 0, SEEK_END);
		long size = ftell(file);
		char* content = malloc(size + 1);
		fseek(file, 0, SEEK_SET);
		fread(content, 1, size, file);
		content[size] = '\0';
		fclose(file);
		root = parse_string(content);
		free(content);
	}
	else
	{
		root = parse_string(str);
	}

	return root;
}

static Node* parse_string(const char* str)
{
	Stack* stack = Stack_Create(); 
	size_t length = strlen(str);
	Node* root = NULL;
	Node* current = NULL;

	for (size_t i = 0; i < length; ++i)
	{
		char c = str[i];
		switch (c)
		{
		case '>':
			if (root == NULL)
			{
				root = Node_Create();
				current = root;
				current->type = NODE_TYPE_MEM_ADD;
				current->arg = 1;
			}
			else if (current->type == NODE_TYPE_MEM_ADD)
			{
				current->arg++;
			}
			else
			{
				current->next = Node_Create();
				current = current->next;
				current->arg = 1;
				current->type = NODE_TYPE_MEM_ADD;
			}
			break;
		case '<':
			if (root == NULL)
			{
				root = Node_Create();
				current = root;
				current->type = NODE_TYPE_MEM_ADD;
				current->arg = -1;
			}
			else if (current->type == NODE_TYPE_MEM_ADD)
			{
				current->arg--;
			}
			else
			{
				current->next = Node_Create();
				current = current->next;
				current->arg = -1;
				current->type = NODE_TYPE_MEM_ADD;
			}
			break;
		case '+':
			if (root == NULL)
			{
				root = Node_Create();
				current = root;
				current->type = NODE_TYPE_ADD;
				current->arg = 1;
			}
			else if (current->type == NODE_TYPE_ADD)
			{
				current->arg++;
			}
			else
			{
				current->next = Node_Create();
				current = current->next;
				current->arg = 1;
				current->type = NODE_TYPE_ADD;
			}
			break;
		case '-':
			if (root == NULL)
			{
				root = Node_Create();
				current = root;
				current->type = NODE_TYPE_ADD;
				current->arg = -1;
			}
			else if (current->type == NODE_TYPE_ADD)
			{
				current->arg--;
			}
			else
			{
				current->next = Node_Create();
				current = current->next;
				current->arg = -1;
				current->type = NODE_TYPE_ADD;
			}
			break;
		case '.':
			if (root == NULL)
			{
				root = Node_Create();
				current = root;
				current->type = NODE_TYPE_PRINT;
			}
			else
			{
				current->next = Node_Create();
				current = current->next;
				current->type = NODE_TYPE_PRINT;
			}
			break;
		case ',':
			if (root == NULL)
			{
				root = Node_Create();
				current = root;
				current->type = NODE_TYPE_INPUT;
			}
			else
			{
				current->next = Node_Create();
				current = current->next;
				current->type = NODE_TYPE_INPUT;
			}
			break;
		case '[':
			if (root == NULL)
			{
				while ((c = str[++i]) != ']');
			}
			else
			{
				current->next = Node_Create();
				current = current->next;
				current->type = NODE_TYPE_JEZ;
				Stack_Push(stack, current);
			}
			break;
		case ']':
			if (root == NULL)
			{
				Stack_Destroy(stack);
				return NULL;
			}
			else
			{
				Node* openingNode = Stack_Pop(stack);
				if (openingNode == NULL)
				{
					Stack_Destroy(stack);
					Node_Destroy(root);
					return NULL;
				}

				current->next = Node_Create();
				current = current->next;
				current->arg = (ARG_TYPE)openingNode;
				current->type = NODE_TYPE_JNZ;
				openingNode->arg = (ARG_TYPE)current;
			}
			break;
		}
	}
	
	Stack_Destroy(stack);
	return root;
}

static void run(Node* root)
{
	unsigned char memory[30000] = { 0 };
	unsigned int pointer = 0;
	Node* current = root;
	while (current != NULL)
	{
		switch (current->type)
		{
		case NODE_TYPE_ADD:
			memory[pointer] += current->arg;
			break;
		case NODE_TYPE_MEM_ADD:
			pointer += current->arg;
			break;
		case NODE_TYPE_JEZ:
			if (memory[pointer] == 0)
				current = (Node*)current->arg;
			break;
		case NODE_TYPE_JNZ:
			if (memory[pointer] != 0)
				current = (Node*)current->arg;
			break;
		case NODE_TYPE_PRINT:
			putchar(memory[pointer]);
			break;
		case NODE_TYPE_INPUT:
		{
			char c;
			while ((c = getchar()) == '\n' || c == EOF);
			memory[pointer] = c;
			break;
		}
		}

		current = current->next;
	}
}
