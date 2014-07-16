#include<stdio.h>

#define MaxVal 999999
#define n 5

// ���Ŷ���������ʵ�ֲ���
void optimal_BST(int root[][n+1], double w[][n+2], double e[][n+2], double p[], double q[])
{
	// ��ʼ��ֻ���������������
	int i = 1;
	int j = 0;
	int k = 0;
	int len = 1;
	double temp = 0;

	for ( i = 1; i <= n + 1; i++)
	{
		w[i][i - 1] = q[i - 1];
		e[i][i - 1] = q[i - 1];
	}

	// ���µ��ϣ��������𲽼���
	for ( len = 1; len <= n; len++)
	{
		for ( i = 1; i <= n - len + 1; i++)
		{
			j = i + len - 1;
			e[i][j] = MaxVal;
			w[i][j] = w[i][j - 1] + p[j] + q[j];
			// ��ȡ��С���۵������ĸ�
			for ( k = i; k <= j; k++)
			{
				temp = e[i][k - 1] + e[k + 1][j] + w[i][j];
				if (temp < e[i][j])
				{
					e[i][j] = temp;
					root[i][j] = k;
				}
			}
		}
	}
}

//������Ŷ������������������ĸ�
void printRoot(int root[][n+1])
{
	int i = 1;
	int j = 1;
	printf("�������ĸ���\n");
	for ( i = 1; i <= n; i++)
	{
		for ( j = 1; j <= n; j++)
		{
			printf("%d ", root[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

//���������ӡ���Ŷ����������Ľṹ
void printOptimal_BST(int root[][n+1], int i, int j, int r)
{
	int rootChild = root[i][j];//�������ڵ�
	if (rootChild == root[1][n])
	{
		//����������ĸ�
		printf("K%d�Ǹ�\n", rootChild);
		printOptimal_BST(root, i, rootChild - 1, rootChild);
		printOptimal_BST(root, rootChild + 1, j, rootChild);
		return;
	}
	
	// �ݹ�ĳ���
	if (j < i - 1)
	{
		return;
	}
	else if (j == i - 1)//��������ڵ�
	{
		if (j < r)
		{
			printf("d%d��k%d������\n", j, r);
		}
		else
		{
			printf("d%d��k%d���Һ���\n", j, r);
		}
			
		return;
	}
	else//�����ڲ����
	{
		if (rootChild < r)
		{
			printf("k%d��k%d������\n", rootChild, r);
		}
		else
		{
			printf("k%d��k%d���Һ���\n", rootChild, r);
		}
	}

	printOptimal_BST(root, i, rootChild - 1, rootChild);
	printOptimal_BST(root, rootChild + 1, j, rootChild);
}

int main()
{
	
	// ��Ÿ��ڵ㱻�������ĸ���
	double p[n + 1] = { -1, 0.15, 0.1, 0.05, 0.1, 0.2 };
	// �������ڵ㱻�������ĸ���
	double q[n + 1] = { 0.05, 0.1, 0.05, 0.05, 0.05, 0.1 };
	//��Ÿ��ڵ�Ķ�ά���飬����ֻʹ�������������Ǿ���
	int root[n + 1][n + 1] = {0};
	// �������������ܺ�
	double w[n + 2][n + 2] = {0};
	// ������������������
	double e[n + 2][n + 2] = {0};

	// ���Ŷ���������
	optimal_BST(root, w, e, p, q);
	// ��ӡ���ڵ�
	printRoot(root);
	printf("���Ŷ������ṹ:\n");
	// ��ӡ������
	printOptimal_BST(root, 1, n, -1);
}