#include<stdio.h>
#include<stdlib.h>

typedef struct queue
{
	int arr[100];
	int size;
	int front;
	int rear;
} queue;

void queue_init(queue* q)
{
	q->size = 0;
	q->front = 0;
	q->rear = 0;
}

void enqueue(queue* q, int data)
{
	if (q->rear == 100)
	{
		printf("Error: Queue Overflow\n");
		return;
	}
	q->arr[q->rear++] = data;
	q->size++;
}

void dequeue(queue* q)
{
	if (q->rear == 0)
	{
		printf("Error: Queue Underflow\n");
		return;
	}
	printf("%d\n", q->arr[q->front]);
	for(int i = 0; i < q->rear - 1; i++)
		q->arr[i] = q->arr[i+1];
	q->rear--;
	q->size--;
}

void peek(queue* q)
{
	if (q->size == 0)
	{
		printf("Error: Queue is empty!\n");
		return;
	}
	printf("%d\n", q->arr[q->front]);
}

void swap(int* a, int* b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void queue_reverse(queue* q)
{
    for(int i = 0; i <= (q->rear-1)/2; i++)
        swap(&q->arr[i], &q->arr[q->rear - i - 1]);
}

void queue_insert(queue* q, int n)
{
	int inp;
    printf("Enter the elements:-\n");
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &inp);
        enqueue(q, inp);
    }
}

int main()
{
    printf("Data structure name: Array queue\nPick your option from below.\n");
	int inp1, length, data;
	queue q[100];
    queue_init(&q[0]);
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
			queue_init(&q[pos]);
			break;
		case 2:
			printf("Enter the size of the queue: ");
			scanf("%d", &length);
            pos++;
			queue_insert(&q[pos], length);
			break;
		case 3:
            peek(&q[pos]);
			break;
		case 4:
			printf("Enter the element you wish to push: ");
            scanf("%d", &data);
            enqueue(&q[pos], data);
			break;
		case 5:
			dequeue(&q[pos]);
			break;
		case 6:
            queue_reverse(&q[pos]);
			break;
        case 7:
            printf("Enter the queue number to be used: ");
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