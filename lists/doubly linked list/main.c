#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int data;
	struct node* next;
	struct node* prev;
} node;

typedef struct doubly_linked_list
{
	node* root;
	node* tail;
	int length;
} doubly_linked_list;

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

void append_node(doubly_linked_list* list, int data)
{
	node* temp = create_node();
	if(!temp)
		return;
	if(!list->tail)
	{
		list->root = list->tail = temp;
		list->length++;
		temp->data = data;
		return;
	}
	temp->prev = list->tail;
	temp->data = data;
	list->tail->next = temp;
	list->tail = temp;
	list->length++;
}

void prepend_node(doubly_linked_list* list, int data)
{
	node* temp = create_node();
	if(temp == NULL)
		return;
	list->length++;
	temp->next = list->root;
	temp->data = data;
	temp->prev = NULL;
	if(!list->root)
	{
		list->root = list->tail = temp;
		return;
	}
	list->root->prev = temp;
	list->root = temp;
}

void insert_node(doubly_linked_list* list, int pos, int data)
{
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
	node* iter = list->root;
	if(temp == NULL)
		return;
	for(int i = 0; i < pos - 1; i++)
		iter = iter->next;
	temp->next = iter->next;
	temp->prev = iter;
	iter->next = temp;
	temp->data = data;
	list->length++;
	if(!temp->next)
		return;
	temp->next->prev = temp;
}

void pop_node(doubly_linked_list* list)
{
	if(list->root == NULL)
	{
		printf("%s\n", "Error: List is empty!");
		return;
	}
	node* temp = list->root;
	while(temp->next->next != NULL)
		temp = temp->next;
	list->tail = temp;
	printf("%d\n", temp->next->data);
	free(temp->next);
	list->tail->next = NULL;
	list->length--;
}

void dequeue_node(doubly_linked_list* list)
{
	if(list->root == NULL)
	{
		printf("%s\n", "Error: List is empty!");
		return;
	}
	node* temp = list->root;
	list->root = list->root->next;
	printf("%d\n", temp->data);
	free(temp);
	if(list->root == NULL)
	{
		list->tail = NULL;
		list->length--;
		return;
	}
	list->root->prev = NULL;
	list->length--;
}

void delete_node(doubly_linked_list* list, int pos)
{
	if(list->root == NULL)
	{
		printf("Error: List is empty!\n");
		return;
	}
	if(pos < 0 || pos >= list->length)
	{
		printf("Error: Invalid Index\n");
		return;
	}
	if(pos == list->length - 1)
	{
		pop_node(list);
		return;
	}
	if(pos == 0)
	{
		dequeue_node(list);
		return;
	}
	node* temp = list->root;
	for(int i = 1; i < pos; i++)
		temp = temp->next;
	node* temp2 = temp->next;
	temp->next = temp->next->next;
	temp->next->prev = temp;
	printf("%d\n", temp2->data);
	free(temp2);
	list->length--;
}

void delete_node_data(doubly_linked_list* list, int data)
{
	node* temp = list->root;
	if(temp == NULL)
	{
		printf("Error: List is empty\n");
		return;
	}
	if(temp->data == data)
		dequeue_node(list);
	while(temp->next != NULL && temp->next->data != data)
		temp = temp->next;
	if(temp->next == NULL)
	{
		printf("Error: Value not found!\n");
		return;
	}
	node* temp2 = temp->next;
	temp->next = temp->next->next;
	if(list->tail == temp2)
		list->tail = temp;
	temp->next->prev = temp;
	printf("%d\n", temp2->data);
	free(temp2);
	list->length--;
}

doubly_linked_list* create_list()
{
	doubly_linked_list* temp = (doubly_linked_list*)malloc(sizeof(doubly_linked_list));
	if(temp == NULL)
	{
		printf("Error: Heap memory exhausted\n");
		return NULL;
	}
	temp->root = NULL;
	int length = 0;
	temp->tail = NULL;
	return temp;
}

doubly_linked_list* create_long_list(int length)
{
	if(length == 0)
		return NULL;
	doubly_linked_list* list = create_list();
	int data;
	printf("Enter the list :-\n");
	scanf("%d", &data);
	list->root = create_node();
	if(list->root == NULL)
		return NULL;
	list->tail = list->root;
	list->length++;
	list->root->data = data;
	for(int i = 0; i < length - 1; i++)
	{
		scanf("%d", &data);
		append_node(list, data);
	}
	return list;
}

void print_list(doubly_linked_list* list, int mode)
{
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
	printf("%d", temp->data);
	temp = temp->next;
	while(temp != NULL)
	{
		printf("<---> %d ", temp->data);
		temp = temp->next;
	}
	printf("\n\n\n");
}

void reverse(doubly_linked_list* list)
{
	node* temp = list->root;
	node* temp2 = temp->prev;
	while(temp->next)
	{
		temp->prev = temp->next;
		temp->next = temp2;
		temp = temp->prev;
		temp2 = temp->prev;
	}
	temp2 = temp->prev;
	temp->next = temp2;
	temp->prev = NULL;
	temp2 = list->root;
	list->root = list->tail;
	list->tail = temp2;
}

int main()
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
			list = create_long_list(1);
			break;
		case 2:
			printf("Enter the length: ");
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
	return 0;
}