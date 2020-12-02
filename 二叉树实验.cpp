/**
 @lizzy_0323
 TODO：
 1.求根到某一节点的路径
 2.当没有二叉树储存时该如何判断
 */
#include <iostream>
#include <stdlib.h>
#include<string.h>
#include<vector>
#define N 50
using namespace std;
int a[N];
static int num1=0,num2=0,num3=0;//用于计算
//定义树结构
struct TreeNode {
	struct TreeNode * LeftNode;
	string data;
	struct TreeNode * RightNode;
};
//用于判断输入是否正确
int  Judgeint(int x)
{
	int i;
	char wrong[N];
	while (1)
	{
		if (scanf("%d", &i) == 0)
		{
			printf("输入错误请 重新输入 Error类型为 : %d\n", x);
			fgets(wrong,N,stdin);
		}
		else
		{
			return i;
		}
	}
}
//用于显示菜单
void Menu()
{
	printf("____________________________________________\n");
	printf("| 1.创建二叉树                              |\n");
	printf("| 2.添加节点                                |\n");
	printf("| 3.打印前序遍历结果                        |\n");
	printf("| 4.打印中序遍历结果                        |\n");
	printf("| 5.打印后序遍历结果                        |\n");
	printf("| 6.打印层序遍历结果                        |\n");
	printf("| 7.求根到给定节点的路径                    |\n");
    printf("| 8.退出                                    |\n");
	printf("|___________________________________________|\n");
	return;
}
//添加节点
void AddNode(TreeNode ** tree, string value)
{
	if (*tree == NULL)
	{
		//为指针节点分配一段地址
		*tree = (TreeNode*)malloc(sizeof(TreeNode));
		if (*tree != NULL)
		{
			(*tree)->LeftNode = NULL;
			(*tree)->data=value;
			(*tree)->RightNode = NULL;
		}
		else
		{
			printf("内存分配失败\n");
		}
	}
	else
	{
		if (value < (*tree)->data)
			AddNode(&((*tree)->LeftNode), value);
		if (value > (*tree)->data)
			AddNode(&((*tree)->RightNode), value);
	}
}
//创建二叉树
void CreatTree(TreeNode **Tree)
{
	string x;
    int num=0;
    printf("请输入该二叉树的节点个数(1-20)\n");
    num=Judgeint(1);
    while(num>20)
    {
        printf("请重新输入该二叉树的节点个数(1-20)\n");
        num=Judgeint(1);   
    }
    //*Tree=NULL;
    for(int i=0;i<num;i++)
    {
		x.resize(N);
        printf("请输入节点\n");
        scanf("%s",&x[0]);
	    AddNode(Tree, x);
    }
	printf("创建完成\n");
}
//先序遍历
void FirPut(TreeNode * tree)
{
	if (tree == NULL)
	{
		if(num1==0)
		{
			printf("该二叉树没有节点储存\n");
		}
		return;
	}
	num1++;
	printf("%s ", (tree->data).c_str());
	FirPut(tree->LeftNode);
	FirPut(tree->RightNode);
}
//中序遍历
void SecPut(TreeNode * tree)
{
	if (tree == NULL)
	{
		if(num2==0)
		{
			printf("该二叉树没有节点储存\n");
		}
		return;
	}
	num2++;
	SecPut(tree->LeftNode);
	printf("%s ", (tree->data).c_str());
	SecPut(tree->RightNode);
}
//后序遍历
void ThrPut(TreeNode * tree)
{
	if (tree == NULL)
	{
		if(num3==0)
		{
			printf("该二叉树没有节点储存\n");
		}
		return;
	}
	num3++;
	ThrPut(tree->LeftNode);
	ThrPut(tree->RightNode);
	printf("%s ", (tree->data).c_str());
} 
//层序遍历
void LevPut(TreeNode * tree)
{
	//定义队列结构
    struct Queue
   {
	TreeNode * data;
	struct Queue * Next;
   };
	Queue *phead, *pend, *pnew;
	phead = (Queue*)malloc(sizeof(Queue));
	phead->data = tree;
	phead->Next = NULL;
	pend = phead;
	do
	{
		TreeNode * Temp = NULL;
		Temp = phead->data;
		//head = head->Next;
		if (Temp->LeftNode != NULL)
		{
			//申请一个临时节点
			pnew = (Queue*)malloc(sizeof(Queue));
			pnew->data = NULL;
			pnew->Next = NULL;
			pnew->data = Temp->LeftNode;
			pend->Next = pnew;
			pend = pend->Next;
		}
		if (Temp->RightNode != NULL)
		{
			pnew = (Queue*)malloc(sizeof(Queue));
			pnew->data = NULL;
			pnew->Next = NULL;
			pnew->data = Temp->RightNode;
			pend->Next = pnew;
			pend = pend->Next;
		}
		printf("%s ", Temp->data.c_str());
		//头节点出队
		phead = phead->Next;
	} while (phead != NULL);
}
//用于判断是哪棵树
int  WhichTree()
{
    printf("请输入要进行操作的二叉树位置(1-20)\n");
    int index=Judgeint(1);
    while(index>20)
    {
        printf("请重新输入要进行操作的二叉树位置(1-20)\n");
        index=Judgeint(1);
    }
    return index;
}
//求根节点到该节点的路径
bool ShowPath(TreeNode*tree,string value)
{
	TreeNode * Node = tree;
	int i=0;
	while (Node != NULL && Node->data != value)
	{
		if (value < Node->data)
		{
			Node = Node->LeftNode;
			a[i]=1;
		}
		else
		{
			Node = Node->RightNode;
			a[i]=2;
		}
		i++;
	}
	if (Node == NULL)
		return false;
	else
		return true;
}
//主函数部分
int main()
{
	TreeNode * tree[N]={NULL};//定义一个树的数组
	int x;
    int index;
	while (1)
	{
        Menu();
		switch (Judgeint(1))
		{
		case 1: 
		{
			CreatTree(&tree[index=WhichTree()]);
			break;
		}
		case 2:	
        {
            string i;
			index=WhichTree();
			printf("请输入要插入节点的值\n");
			i=Judgeint(2);
			AddNode(&tree[index], i);
			break;
        }
		case 3:
        {
			printf("前序遍历 ：");
			FirPut(tree[index=WhichTree()]);
			printf("\n");
			break;
        }
		case 4:
        {
            printf("中序遍历 : ");
			SecPut(tree[index=WhichTree()]);
			printf("\n");
			break;
        }
		case 5:
        {
            printf("后序遍历 : ");
			ThrPut(tree[index=WhichTree()]);
			printf("\n");
			break;
        }
		case 6:
        {
            printf("层序遍历 : ");
			LevPut(tree[index=WhichTree()]);
			printf("\n");
			break;
        }
		case 7:
        {
			int j=0;
			string newData;
			index=WhichTree();
			printf("请输入要查找的节点所存储的数据\n");
			newData.resize(N);
			scanf("%s",&newData[0]);
			if(ShowPath(tree[index],newData))//如果查找成功
			{
				printf("以下为路径\n");
				for(int i=0;a[i]!=0;i++)
				{
					cout<<tree[index]->data<<endl;
					if(a[i]==1)//如果指向左端
					{

						tree[index]=tree[index]->LeftNode;
					}
					if(a[i]==2)//如果指向右端
					{
						tree[index]=tree[index]->RightNode;
					}
				}
				cout<<tree[index]->data<<endl;
			}
			else
			{
				printf("未查找到该节点\n");
			}
			break;	
        }
        case 8:
        {
            printf("程序已安全退出\n");
           	exit(0);
			break;
        }
		default:
			printf("输入错误 请重新输入 \n");
			break;
		}
	}
}