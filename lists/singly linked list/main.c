#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int data;
	struct node* next;
} node;

typedef struct singly_linked_list
{
	node* root;
	int length;
	node* tail;
} singly_linked_list;

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
	return temp;
}

void append_node(singly_linked_list* list, int data)
{
	if(list->root == NULL)
	{
		list->root = create_node();
		if(list->root == NULL)
			return;
		list->tail = list->root;
		list->root->data = data;
		list->length++;
		return;
	}
	list->tail->next = create_node();
	if(list->tail->next == NULL)
		return;
	list->length++;
	list->tail->next->data = data;
	list->tail = list->tail->next;
}

void prepend_node(singly_linked_list* list, int data)
{
	node* temp = create_node();
	if(temp == NULL)
		return;
	list->length++;
	temp->next = list->root;
	list->root = temp;
	temp->data = data;
	if(list->length == 1)
		list->tail = list->root;
}

void insert_node(singly_linked_list* list, int pos, int data)
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
	node* iter = list->root;
	node* temp;
	for(int i = 0; i < pos - 1; i++)
		iter = iter->next;
	temp = create_node();
	if(temp == NULL)
		return;
	temp->next = iter->next;
	temp->data = data;
	iter->next = temp;
	list->length++;
}

void pop_node(singly_linked_list* list)
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

void dequeue_node(singly_linked_list* list)
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
		list->tail = NULL;
	list->length--;
}

void delete_node(singly_linked_list* list, int pos)
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
	printf("%d\n", temp2->data);
	free(temp2);
	list->length--;
}

void delete_node_data(singly_linked_list* list, int data)
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
	printf("%d\n", temp2->data);
	free(temp2);
	list->length--;
}

singly_linked_list* create_list()
{
	singly_linked_list* temp = (singly_linked_list*)malloc(sizeof(singly_linked_list));
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

singly_linked_list* create_long_list(int length)
{
	if(length == 0)
		return NULL;
	singly_linked_list* list = create_list();
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

void print_list(singly_linked_list* list, int mode)
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
		printf("---> %d ", temp->data);
		temp = temp->next;
	}
	printf("\n\n\n");
}

void reverse(singly_linked_list* list)
{
	node* temp = list->root;
	node* prev = NULL;
	node* next = NULL;
	while(temp != NULL)
	{
		next = temp->next;
		temp->next = prev;
		prev = temp;
		temp = next;
	}
	temp = list->tail;
	list->tail = list->root;
	list->root = temp;
}

int main()
{
	printf("Data structure name: Singly Linked List\nPick your option from below.\n");
	int inp1, length, pos, data;
	singly_linked_list* list;
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