#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node *next;
} NODE;

void output(NODE *, int);
void change(int n, int m, NODE *head)

void output(NODE *head, int kk)
{
	int k = 0;

	printf("0.");
	while (head->next != NULL && k < kk)
	{
		printf("%d", head->next->data);
		head = head->next;
		k++;
	}
	printf("\n");
}

int main()
{
	int n, m, k;
	NODE *head;

	scanf("%d%d%d", &n, &m, &k);
	head = (NODE *)malloc(sizeof(NODE));
	head->next = NULL;
	head->data = -1;
	change(n, m, head);
	output(head, k);
	return 0;
}
void change(int n, int m, node *head)
{
	NODE *q = (NODE *)malloc(sizeof(NODE));
	q = head;
	int s[100000] = {0}, y[100000] = {0};
	int i = 0;
	int flag = 0;
	while (n * 10 / m >= 0)
	{
		NODE *p = (NODE *)malloc(sizeof(NODE));
		p->data = n * 10 / m;
		p->next = NULL;
		q->next = p;
		q = q->next;
		s[i] = n * 10 / m;
		y[i] = n * 10 % m;
		i++;
		n = n * 10 % m;
		if (n == 0)
		{
			q->next = NULL;
			break;
		}
		for (int j = 0; j < i - 1; j++)
		{
			if (s[j] == s[i - 1] && y[j] == y[i - 1])
			{
				q = head;
				for (int l = 0; l < j + 1; l++)
				{
					q = q->next;
				}
				NODE *r = (NODE *)malloc(sizeof(NODE));
				r = head;
				for (int l = 0; l < i - 1; l++)
				{
					r = r->next;
				}
				r->next = q;
				flag = 1;
				break;
			}
		}
		if (flag)
			break;
	}
}