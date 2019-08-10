#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int data;
	struct node* next;
} node;

typedef struct queue
{
	node* front;
	node* rear;
	int size;
	int limit;
} queue;


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

queue* create_queue()
{
	queue* q;
	q = (queue*)malloc(sizeof(queue));
	q->front = NULL;
	q->rear = NULL;
	q->size = 0;
	q->limit = 100;
	return q;
}

void queue_insert(queue* q, int n)
{
	queue* ka;
	ka = create_queue();
	*q = *ka;
	int inp;
    printf("Enter the elements:-\n");
    q->front = q->rear = create_node();
    if(q->front == NULL)
    	return;
    scanf("%d", &inp);
    q->front->data = inp;
    q->size++;
    node* temp = q->front;
    for(int i = 0; i < n - 1; i++)
    {
        scanf("%d", &inp);
        temp->next = create_node();
        if(temp->next == NULL)
        	break;
        temp->next->data = inp;
        temp = temp->next;
        q->rear = temp;
        q->size++;
    }
    q->rear->next = NULL;
}

void enqueue(queue* q, int data)
{
	if(q->size == q->limit)
	{
		printf("Error: Queue Overflow!\n");
		return;
	}
	node* temp = create_node();
	if(temp == NULL)
		return;
	if(q->size == 0)
	{
		q->front = q->rear = temp;
		temp->data = data;
		q->size++;
		return;
	}
	temp->data = data;
	q->rear->next = temp;
	q->size++;
	q->rear = temp;
}

void dequeue(queue* q)
{
	if(q->size == 0)
	{
		printf("Error: Queue Underflow!\n");
		return;
	}
	printf("%d\n", q->front->data);
	node* temp = q->front;
	q->front = q->front->next;
	q->size--;
	free(temp);
}

void peek(queue* q)
{
	if(q->size == 0)
	{
		printf("Error: Queue is empty!\n");
		return;
	}
	printf("%d\n", q->front->data);
}

void reverse(queue* q)
{
	node* temp = q->front;
	node* prev = NULL;
	node* next = NULL;
	while(temp != NULL)
	{
		next = temp->next;
		temp->next = prev;
		prev = temp;
		temp = next;
	}
	temp = q->rear;
	q->rear = q->front;
	q->front = temp;
}

int main()
{
	printf("Data structure name: Dynamic queue\nPick your option from below.\n");
	int inp1, length, data;
	queue* q[100];
	q[0] = create_queue();
    int pos = 0;
	do
	{
		printf("\n\n");
		printf("1. Create an empty queue.\n");
        printf("   [In case of using multiple queues, input the queue number you are using\n    by choosing queue number option. By default queue numbers start with 1]\n");
		printf("2. Create a continuous queue.\n");
		printf("3. Peek the queue.\n");
		printf("4. Enqueue the queue.\n");
		printf("5. Dequeue the queue.\n");
		printf("6. Reverse the queue.\n");
        printf("7. Select queue number.\n");
        printf("8. Display current queue number.\n");
		printf("Enter any other number to exit.\n");
		printf("==# : ");
		scanf("%d", &inp1);
		printf("\n\n");
		switch (inp1)
		{
		case 1:
            pos++;
			q[pos] = create_queue();
			break;
		case 2:
			printf("Enter the size of the queue: ");
			scanf("%d", &length);
            pos++;
			queue_insert(q[pos], length);
			break;
		case 3:
            peek(q[pos]);
			break;
		case 4:
			printf("Enter the element you wish to enqueue: ");
            scanf("%d", &data);
            enqueue(q[pos], data);
			break;
		case 5:
			dequeue(q[pos]);
			break;
		case 6:
            reverse(q[pos]);
			break;
        case 7:
            printf("Enter the queue number to be used: ");
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