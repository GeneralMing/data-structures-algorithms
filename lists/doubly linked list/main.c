#include<stdio.h>
#include<stdlib.h>

// Typical sturcture of a node in doubly linked list
typedef struct node
{
	int data;
	struct node* next;
	struct node* prev;
} node;


// The wrapper for the linked list which contains details of the list
typedef struct doubly_linked_list
{
	node* root;
	node* tail;
	int length;
} doubly_linked_list;

// Returns a pointer to the new node created. Initializes the data to zero.
node* create_node()
{
	node* temp = (node*)malloc(sizeof(node));
	
	if(temp == NULL)
	{
		printf("Error: Heap memory exhausted\n");
		return NULL;
	}

	temp->data = 0;
	
	temp->next = NULL;
	temp->prev = NULL;
	
	return temp;
}


// Appends a node to the end of the list
void append_node(doubly_linked_list* list, int data)
{
	node* temp = create_node();
	
	// Returns on error
	if(!temp)
		return;
	
	// If list is empty
	if(!list->tail)
	{
		list->root = list->tail = temp;
		list->length++;
		temp->data = data;
		return;
	}

	// If a node already exists
	temp->prev = list->tail;
	temp->data = data;

	list->tail->next = temp;
	list->tail = temp;
	
	list->length++;
}

// Places a node at the beginning of the list
void prepend_node(doubly_linked_list* list, int data)
{
	node* temp = create_node();
	
	// Returns on error
	if(!temp)
		return;

	// Sets the newly created node pointers before attaching
	temp->next = list->root;
	temp->data = data;
	temp->prev = NULL;

	// If list is empty
	if(!list->root)
	{
		list->root = list->tail = temp;
		list->length++;
		return;
	}

	// If list is not empty
	list->root->prev = temp;
	list->root = temp;

	list->length++;
}

// Inserts a node to given a position [0, length] (index is taken as an argument)
void insert_node(doubly_linked_list* list, int pos, int data)
{
	// The following 'if' statements make use of our previous functions to insert nodes

	// Returns error on bad index
	if(pos < 0 || pos > list->length)
	{
		printf("Error: Invalid index\n");
		return;
	}
	if(list->length == 0 || pos == list->length)
	{
		append_node(list, data);
		return;
	}
	if(pos == 0)
	{
		prepend_node(list, data);
		return;
	}

	node* temp = create_node();

	// List iterator
	node* iter = list->root;

	// Returns on error
	if(!temp)
		return;

	for(int i = 0; i < pos - 1; i++)
		iter = iter->next;
	
	// Setting node values
	temp->next = iter->next;
	temp->prev = iter;
	temp->data = data;

	// Setting current iterator node values
	iter->next = temp;
	if(!temp->next)
		return;
	temp->next->prev = temp;

	list->length++;
}


// Removes the node at the end of the list
void pop_node(doubly_linked_list* list)
{
	int p;
	// Check if list is empty
	printf("null: %p\n", NULL);
	printf("root: %p\n", list->root);
	printf("tail: %p\n", list->tail);
	if(list->root == NULL)
	{
		printf("%s\n", "Error: List is empty!");
		return;
	}

	// Created an iterator to go to the end of the list
	node* temp = list->root;
	while(temp->next != NULL)
		temp = temp->next;
	
	// Reset the tail to the previous node
	list->tail = temp->prev;

	p = temp->data;
	printf("%d\n", p);

	// Deallocate the memory given to it
	free(temp);

	// Updating the current pointers
	if(list->tail != NULL)
		list->tail->next = NULL;
	list->length--;
	if(list->length == 0)
		list->root = list->tail = NULL;

	return;
}

// Removes a node from the front of the list
void dequeue_node(doubly_linked_list* list)
{
	int p;
	// Check if list is empty
	if(list->root == NULL)
	{
		printf("%s\n", "Error: List is empty!");
		return;
	}

	node* temp = list->root;
	list->root = list->root->next;
	
	p = temp->data;
	printf("%d\n", temp->data);
	
	// Deallocate memory to delete node
	free(temp);

	// Reset tail and root if the list is empty after dequeuing
	if(list->root == NULL)
	{
		list->tail = NULL;
		list->length--;
		return;
	}
	// Adjust the pointers to the new values after dequeuing
	list->root->prev = NULL;
	list->length--;
	if(list->length == 0)
		list->root = list->tail = NULL;
	return;
}

// Delete a node at a given position [0, length] (index is taken as an argument)
void delete_node(doubly_linked_list* list, int pos)
{
	// Check if the list empty
	if(list->root == NULL)
	{
		printf("Error: List is empty!\n");
		return;
	}

	// Check if the correct index has been passed
	if(pos < 0 || pos >= list->length)
	{
		printf("Error: Invalid Index\n");
		return;
	}

	// Call an existing function to delete if the index specified is the last index
	if(pos == list->length - 1)
	{
		pop_node(list);
		return;
	}

	// Call an existing function to delete if the index passed is the first index
	if(pos == 0)
	{
		dequeue_node(list);
		return;
	}

	// Create an iterator to go through the nodes to the position
	node* temp = list->root;
	for(int i = 1; i < pos; i++)
		temp = temp->next;

	// New pointer variable to the node being deleted
	node* temp2 = temp->next;
	
	// Updating the node values
	temp->next = temp->next->next;
	temp->next->prev = temp;

	printf("%d\n", temp2->data);
	
	// Deallocate memory to delete node
	free(temp2);

	list->length--;
	if(list->length == 0)
		list->root = list->tail = NULL;
	return;
}

// Deletes a node based on the 'data' argument. Deletes only the occurance
void delete_node_data(doubly_linked_list* list, int data)
{
	node* temp = list->root;
	//Check if the list is empty
	if(temp == NULL)
	{
		printf("Error: List is empty\n");
		return;
	}

	// Delete if the node is root
	if(temp->data == data)
		dequeue_node(list);
	// Iterate till the node is found
	while(temp->next != NULL && temp->next->data != data)
		temp = temp->next;

	/* Check if the iterator reached the end of the list
	   and did not find the node*/
	if(temp->next == NULL)
	{
		printf("Error: Value not found!\n");
		return;
	}

	node* temp2 = temp->next;
	// Update the node and list pointers for deletion
	temp->next = temp->next->next;

	if(list->tail == temp2)
		list->tail = temp;
	
	temp->next->prev = temp;
	
	printf("%d\n", temp2->data);
	//Deallocate the memory given to the node
	free(temp2);
	list->length--;
	if(list->length == 0)
		list->root = list->tail = NULL;
	return;
}

// Creates a list wrapper and returns a pointer to it
doubly_linked_list* create_list()
{
	doubly_linked_list* temp = (doubly_linked_list*)malloc(sizeof(doubly_linked_list));
	
	// Check if malloc returns error on memory request
	if(temp == NULL)
	{
		printf("Error: Heap memory exhausted\n");
		return NULL;
	}
	// Initialize the list values
	temp->root = NULL;
	temp->length = 0;
	temp->tail = NULL;
	return temp;
}

doubly_linked_list* create_long_list(int length)
{
	// Create list wrapper
	int data;
	doubly_linked_list* list = create_list();
	
	// Check if the list has to be empty
	if(length == 0)
		return list;

	// Take in only one node
	scanf("%d", &data);

	list->root = create_node();
	
	// Check if node was created
	if(list->root == NULL)
		return NULL;
	
	// Initialize list values
	list->tail = list->root;
	list->length++;
	list->root->data = data;
	
	// Take in the rest of the inputs if any
	for(int i = 0; i < length - 1; i++)
	{
		scanf("%d", &data);
		append_node(list, data);
	}
	return list;
}

// Prints the list based on the requirement mentioned in mode
/*
	0: Prints the data at the top of the list
	1: Prints the data at the bottom of the list
	2: Prints the length of the list
	if anything else, it prints the entire list
*/
void print_list(doubly_linked_list* list, int mode)
{
	// Check if the list is empty
	if(list->root == NULL)
	{
		printf("List is empty!\n");
		return;
	}

	if(mode == 0)
	{
		printf("%d\n", list->root->data);
		return;
	}
	if(mode == 1)
	{
		printf("%d\n", list->tail->data);
		return;
	}
	if(mode == 2)
	{
		printf("%d\n", list->length);
		return;
	}

	node* temp = list->root;
	printf("%d ", temp->data);
	temp = temp->next;
	while(temp != NULL)
	{
		printf("<---> %d ", temp->data);
		temp = temp->next;
	}
	printf("\n");
}


// Reverses the list completely
void reverse(doubly_linked_list* list)
{
	node* temp = list->root;
	node* temp2 = temp->prev;

	// Reverses the pointer at every node until the end
	while(temp->next)
	{
		temp->prev = temp->next;
		temp->next = temp2;
		temp = temp->prev;
		temp2 = temp->prev;
	}
	// The last node has to be reset seperately
	temp2 = temp->prev;
	temp->next = temp2;
	temp->prev = NULL;
	temp2 = list->root;

	// Update the list details
	list->root = list->tail;
	list->tail = temp2;
	return;
}

int main(int argc, char** argv)
{
	if(argc > 0)
	{
		if(argv[1])
		{
			int inp1, length, pos, data;
			doubly_linked_list* list;
			do
			{
				scanf("%d", &inp1);
				switch (inp1)
				{
					case 1:
						list = create_list();
						break;
					case 2:
						scanf("%d", &length);
						list = create_long_list(length);
						break;
					case 3:
						print_list(list, 3);
						break;
					case 4:
						print_list(list, 0);
						break;
					case 5:
						print_list(list, 1);
						break;
					case 6:
						scanf("%d", &pos);
						scanf("%d", &data);
						insert_node(list, pos, data);
						break;
					case 7:
						scanf("%d", &data);
						append_node(list, data);
						break;
					case 8:
						scanf("%d", &data);
						prepend_node(list, data);
						break;
					case 9:
						pop_node(list);
						break;
					case 10:
						dequeue_node(list);
						break;
					case 11:
						scanf("%d", &pos);
						delete_node(list, pos);
						break;
					case 12:
						scanf("%d", &data);
						delete_node_data(list, data);
						break;
					case 13:
						reverse(list);
						break;
					default:
						inp1 = 0;
						break;
				}
			} while (inp1);
		}
	}
	
	else
	{
		printf("Data structure name: Doubly Linked List\nPick your option from below.\n");
		int inp1, length, pos, data;
		doubly_linked_list* list;
		do
		{
			printf("1. Create an empty list.\n");
			printf("2. Create a long list.\n");
			printf("3. Print the list.\n");
			printf("4. Print the first node of the list.\n");
			printf("5. Print the last node of the list.\n");
			printf("6. Insert a new node at a particular position.\n");
			printf("7. Append a node.\n");
			printf("8. Prepend a node.\n");
			printf("9. Pop a list.\n");
			printf("10. Dequeue a node.\n");
			printf("11. Delete a node at a particular position.\n");
			printf("12. Delete a node with some particular data.\n");
			printf("13. Reverse the list.\n");
			printf("Enter any other number to exit.\n");
			printf("==# : ");
			scanf("%d", &inp1);
			switch (inp1)
			{
				case 1:
					list = create_list();
					break;
				case 2:
					printf("Enter the length: ");
					scanf("%d", &length);
					printf("Enter the list :-\n");
					list = create_long_list(length);
					break;
				case 3:
					print_list(list, 3);
					break;
				case 4:
					print_list(list, 0);
					break;
				case 5:
					print_list(list, 1);
					break;
				case 6:
					printf("Enter the position: ");
					scanf("%d", &pos);
					printf("Enter the data: ");
					scanf("%d", &data);
					insert_node(list, pos, data);
					break;
				case 7:
					printf("Enter the data: ");
					scanf("%d", &data);
					append_node(list, data);
					break;
				case 8:
					printf("Enter the data: ");
					scanf("%d", &data);
					prepend_node(list, data);
					break;
				case 9:
					pop_node(list);
					break;
				case 10:
					dequeue_node(list);
					break;
				case 11:
					printf("Enter the position: ");
					scanf("%d", &pos);
					delete_node(list, pos);
					break;
				case 12:
					printf("Enter the data: ");
					scanf("%d", &data);
					delete_node_data(list, data);
					break;
				case 13:
					reverse(list);
					break;
				default:
					inp1 = 0;
					break;
			}
		} while (inp1);
	}

	return 0;
}