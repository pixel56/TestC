#include<stdio.h>

#define MaxVal 999999
#define n 5

// 最优二叉搜索数实现部分
void optimal_BST(int root[][n+1], double w[][n+2], double e[][n+2], double p[], double q[])
{
	// 初始化只包括虚拟键的子树
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

	// 由下到上，由左到右逐步计算
	for ( len = 1; len <= n; len++)
	{
		for ( i = 1; i <= n - len + 1; i++)
		{
			j = i + len - 1;
			e[i][j] = MaxVal;
			w[i][j] = w[i][j - 1] + p[j] + q[j];
			// 求取最小代价的子树的根
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

//输出最优二叉搜索树所有子树的根
void printRoot(int root[][n+1])
{
	int i = 1;
	int j = 1;
	printf("各子树的根：\n");
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

//先序遍历打印最优二叉搜索树的结构
void printOptimal_BST(int root[][n+1], int i, int j, int r)
{
	int rootChild = root[i][j];//子树根节点
	if (rootChild == root[1][n])
	{
		//输出整棵树的根
		printf("K%d是根\n", rootChild);
		printOptimal_BST(root, i, rootChild - 1, rootChild);
		printOptimal_BST(root, rootChild + 1, j, rootChild);
		return;
	}
	
	// 递归的出口
	if (j < i - 1)
	{
		return;
	}
	else if (j == i - 1)//遇到虚拟节点
	{
		if (j < r)
		{
			printf("d%d是k%d的左孩子\n", j, r);
		}
		else
		{
			printf("d%d是k%d的右孩子\n", j, r);
		}
			
		return;
	}
	else//遇到内部结点
	{
		if (rootChild < r)
		{
			printf("k%d是k%d的左孩子\n", rootChild, r);
		}
		else
		{
			printf("k%d是k%d的右孩子\n", rootChild, r);
		}
	}

	printOptimal_BST(root, i, rootChild - 1, rootChild);
	printOptimal_BST(root, rootChild + 1, j, rootChild);
}

int main()
{
	
	// 存放根节点被搜索到的概率
	double p[n + 1] = { -1, 0.15, 0.1, 0.05, 0.1, 0.2 };
	// 存放虚拟节点被搜索到的概率
	double q[n + 1] = { 0.05, 0.1, 0.05, 0.05, 0.05, 0.1 };
	//存放根节点的二维数组，这里只使用了它的上三角矩阵
	int root[n + 1][n + 1] = {0};
	// 所有子树概率总和
	double w[n + 2][n + 2] = {0};
	// 所有子树的期望代价
	double e[n + 2][n + 2] = {0};

	// 最优二叉搜索树
	optimal_BST(root, w, e, p, q);
	// 打印根节点
	printRoot(root);
	printf("最优二叉树结构:\n");
	// 打印整棵树
	printOptimal_BST(root, 1, n, -1);
}