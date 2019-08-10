#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int data;
	struct node* next;
} node;

typedef struct stack
{
	node* root;
	node* top;
	int size;
	int limit;
} stack;

node* create_node()
{
	node* temp = (node*)malloc(sizeof(node));
	if(temp == NULL)
	{
		printf("Error: Heap Memory Exhausted.\n");
		return NULL;
	}
	temp->data = 0;
	temp->next = NULL;
	return temp;
}

stack* create_stack()
{
	stack* stk;
	stk = (stack*)malloc(sizeof(stack));
	stk->root = NULL;
	stk->top = NULL;
	stk->size = 0;
	stk->limit = 100;
	return stk;
}

void stack_insert(stack* stk, int n)
{
	stack* st;
	st = create_stack();
	*stk = *st;
	int inp;
    printf("Enter the elements:-\n");
    stk->root = stk->top = create_node();
    if(stk->root == NULL)
    	return;
    scanf("%d", &inp);
    stk->root->data = inp;
    stk->size++;
    node* temp = stk->root;
    for(int i = 0; i < n - 1; i++)
    {
        scanf("%d", &inp);
        temp->next = create_node();
        if(temp->next == NULL)
        	break;
        temp->next->data = inp;
        temp = temp->next;
        stk->top = temp;
        stk->size++;
    }
    stk->top->next = NULL;
}

void push(stack* stk, int data)
{
	if(stk->size == stk->limit)
	{
		printf("Error: Stack Overflow!\n");
		return;
	}
	node* temp = create_node();
	if(temp == NULL)
		return;
	if(stk->size == 0)
	{
		stk->root = stk->top = temp;
		temp->data = data;
		stk->size++;
		return;
	}
	temp->data = data;
	stk->top->next = temp;
	stk->size++;
	stk->top = temp;
}

void pop(stack* stk)
{
	if(stk->size == 0)
	{
		printf("Error: Stack Underflow!\n");
		return;
	}
	printf("%d\n", stk->top->data);
	node* temp = stk->root;
	if(stk->size == 1)
	{
		free(temp);
		stk->root = stk->top = NULL;
		stk->size--;
		return;
	}
	while(temp->next->next != NULL)
		temp = temp->next;
	free(temp->next);
	stk->top = temp;
	temp->next = NULL;
	stk->size--;
}

void peek(stack* stk)
{
	if(stk->top == NULL)
	{
		printf("Error: Stack is empty.\n");
		return;
	}
	printf("%d\n", stk->top->data);
}

void reverse(stack* stk)
{
	node* temp = stk->root;
	node* prev = NULL;
	node* next = NULL;
	while(temp != NULL)
	{
		next = temp->next;
		temp->next = prev;
		prev = temp;
		temp = next;
	}
	temp = stk->top;
	stk->top = stk->root;
	stk->root = temp;
}

int main()
{
    printf("Data structure name: Dynamic Stack\nPick your option from below.\n");
	int inp1, length, data;
	stack* stk[100];
	stk[0] = create_stack();
    int pos = 0;
	do
	{
		printf("\n\n");
		printf("1. Create an empty stack.\n");
        printf("   [In case of using multiple stacks, input the stack number you are using\n    by choosing stack number option. By default stack numbers start with 1]\n");
		printf("2. Create a continuous stack.\n");
		printf("3. Peek the stack.\n");
		printf("4. Push the stack.\n");
		printf("5. Pop the stack.\n");
		printf("6. Reverse the stack.\n");
        printf("7. Select stack number.\n");
        printf("8. Display current stack number.\n");
		printf("Enter any other number to exit.\n");
		printf("==# : ");
		scanf("%d", &inp1);
		printf("\n\n");
		switch (inp1)
		{
		case 1:
            pos++;
			stk[pos] = create_stack();
			break;
		case 2:
			printf("Enter the size of the stack: ");
			scanf("%d", &length);
            pos++;
			stack_insert(stk[pos], length);
			break;
		case 3:
            peek(stk[pos]);
			break;
		case 4:
			printf("Enter the element you wish to push: ");
            scanf("%d", &data);
            push(stk[pos], data);
			break;
		case 5:
			pop(stk[pos]);
			break;
		case 6:
            reverse(stk[pos]);
			break;
        case 7:
            printf("Enter the stack number to be used: ");
            scanf("%d",&pos);
            pos -= 1;
            break;
        case 8:
            printf("%d\n", pos + 1);
            break;
		default:
			inp1 = 0;
			break;
		}
	} while (inp1);
	return 0;
}