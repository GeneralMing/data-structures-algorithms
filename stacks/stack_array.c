#include<stdio.h>
#include<stdlib.h>

typedef struct stack
{
    int arr[100];
    int top;
    int size;
} stack;

void pop(stack* stk)
{
    if(!stk->size)
    {
        printf("Error: Underflow detected. The stack is empty!\n");
        return;
    }
    else
    {
        int a = stk->arr[stk->top--];
        stk->size--;
        printf("%d\n", a);
    }
}

void push(stack* stk, int data)
{
    if(stk->size > 99)
    {
        printf("Error: Overflow detected. Stack is full!\n");
        return;
    }
    else
    {
        stk->arr[++stk->top] = data;
        stk->size++;
    }
}

void stack_init(stack* stk)
{
    stk->size = 0;
    stk->top = -1;
}

void peek(stack* stk)
{
    if(stk->top == -1)
    {
        printf("Error: Stack is empty!\n");
        return;
    }
    printf("%d\n", stk->arr[stk->top]);
}

void stack_insert(stack* stk, int n)
{
    int inp;
    printf("Enter the elements:-\n");
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &inp);
        stk->arr[++stk->top] = inp;
        stk->size++;
    }
}
void swap(int* a, int* b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void stack_reverse(stack* stk)
{
    for(int i = 0; i <= stk->top/2; i++)
        swap(&stk->arr[i], &stk->arr[stk->top - i]);
}

int main()
{
    printf("Data structure name: Array Stack\nPick your option from below.\n");
	int inp1, length, data;
	stack stk[100];
    stack_init(&stk[0]);
    int pos = 0;
	do
	{
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
		switch (inp1)
		{
		case 1:
            pos++;
			stack_init(&stk[pos]);
			break;
		case 2:
			printf("Enter the size of the stack: ");
			scanf("%d", &length);
            pos++;
			stack_insert(&stk[pos], length);
			break;
		case 3:
            peek(&stk[pos]);
			break;
		case 4:
			printf("Enter the element you wish to push: ");
            scanf("%d", &data);
            push(&stk[pos], data);
			break;
		case 5:
			pop(&stk[pos]);
			break;
		case 6:
            stack_reverse(&stk[pos]);
			break;
        case 7:
            printf("Enter the stack number to be used: ");
            scanf("%d",&pos);
            pos-=1;
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