/*
 @lizzy_0323
 FOR
 TIANLU
 翻版必究
 TODO：
 */
#include <cstdlib>
#include<stdio.h>
#include<string.h>
#define N 50
char wrong[N];//用于储存错误输入
char c1[N][N], c2[N][N];//用于储存两个字符串
void Out()
{
	printf("请问您是否要现在退出程序？\n");
	printf("1-是 2-不是\n");
	int t;//用于判断用户当前是否要进行退出
	scanf("%d",&t);
	if(t==1)
	{
		printf("程序已安全退出\n");
		exit(0);
	}
	else
	{
		return;
	}
	
}
void Menu()
{
	printf("*****************************\n");
	printf("1.输入主串，子串和匹配起始位置\n");
	printf("2.朴素的模式匹配算法\n");
	printf("3.KMP算法(Next[])\n");
	printf("4.KMP算法(Nextval[])\n");
	printf("5.修改主串或者子串\n");
	printf("6-删除字符串\n");
	printf("0.退出管理系统\n");
	printf("*****************************\n");
}
void getString2(int c)
{
	fgets(c2[c],20,stdin);
	int i=strlen(c2[c]);
	if(c2[c][i-1]=='\n') //因为最后一行没有回车符
    {
        c2[c][i-1]='\0';
	}
}
void getString1(int c)
{
	fgets(c1[c],20,stdin);
	int i=strlen(c2[c]);
	if(c1[c][i-1]=='\n') //因为最后一行没有回车符
    {
        c1[c][i-1]='\0';
	}
}
//朴素的模式匹配算法
int BF(char* a, char* b, int pos)
{
	int length1, length2;
	length1 = strlen(a)-1;
	length2 = strlen(b)-1;
	int i = pos, j = 0, k = 0;
	int count = 1;//记录比较次数
	bool is1 = true;
	bool isIn=true;
	int num[N];
	for (i = 0; i <= length2; i++)//先为num数组赋0
	{
		num[i] = 0;
	}
	i = 0;
	printf("当前主串是%s\n", a);
	printf("当前子串是%s\n", b);
	while (i <= length1  && j <= length2 )//如果匹配没到末尾
	{
		if (count == 1 && is1 == true)
		{
			printf("当前为第%d趟\n", count);
		}
		num[j] += 1;
		if (a[i] == b[j])//如果当前字符匹配相同，继续匹配后续字符
		{
			printf("%c,%c\n", a[i], b[j]);
			i++;
			j++;
			is1 = false;
			isIn=true;
		}
		else
		{
			printf("%c,%c\n", a[i], b[j]);
			i = i - j + 1;
			j = 0;//回到初始位置
			isIn=false;
			if(a[i]!='\0'&&a[i]!='\n')
			{
			count++;
			printf("当前为第%d趟\n", count);
			}
			//printf("当前为第%d趟\n", count);
		}
	}
	printf("匹配结束\n");
	for (k = 0; k <= length2; k++)//先为num数组赋0
	{
		printf("模式串第%d个字符匹配的次数是%d\n", k+1, num[k]);
	}
	if (j >= length2&&isIn==true)//匹配成功
	{
		printf("匹配总趟数是%d\n", count);
		return i - length2;//返回匹配成功的位置
	}
	else
	{
		printf("匹配总趟数是%d\n", count);
		return 0;
	}
}
//获取next数组
void Get_next(char* b, int* next)
{
	int j = 0, k = -1;
	next[j] = k;
	int length = strlen(b)-1;
	while (j <= length)
	{
		if (k == -1 || b[j] == b[k])//如果回到了第一个字符或匹配成功
		{
			j++;
			k++;
			next[j] = k;
		}
		else//如果匹配失败
		{
			k = next[k];
		}
	}
	return;
}
//获取nextval数组
void Get_nextval(char* b, int* nextval)
{
	int j = 0, k = -1;
	nextval[j] = k;
	int length = strlen(b)-1;
	while (j<=length)
	{
		if (k == -1 || b[j] == b[k])//如果回到了第一个字符或匹配成功
		{
			j++;
			k++;
			if (b[j] != b[k])
			{
				nextval[j] = k;
			}
			else
			{
				nextval[j] = nextval[k];
			}
		}
		else//如果匹配失败
		{
			k = nextval[k];
		}
	}
	return;
}
//KMP算法
int KMP(char* a, char* b, int pos)
{
	int length1, length2;
	length1 = strlen(a)-1;
	length2 = strlen(b)-1;
	int i = pos, j = 0, k = 0;
	int next[N];//定义一个next数组
	int num[N];
	bool is1 = true;
	bool isIn=true;
	printf("当前主串是%s\n", a);
	printf("当前子串是%s\n", b);
	Get_next(b, next);
	int count = 1;//记录比较次数
	for (i = 0; i <=length2; i++)//先为num数组赋0
	{
		num[i] = 0;
	}
	i = 0;
	while (i <= length1 && j <= length2 )//如果匹配没到末尾
	{
		if (count == 1 && is1 == true)
		{
			printf("当前为第%d趟\n", count);
		}
		if (j == -1 || a[i] == b[j])//如果当前字符匹配相同或第一位就不同，继续匹配后续字符
		{
			if (j != -1)
			{
				num[j] += 1;
				printf("%c,%c\n", a[i], b[j]);
			}
			else
			{
				num[0] += 1;
			}
			i++;
			j++;
			is1 = false;
			isIn=true;
		}
		else
		{
			printf("%c,%c\n", a[i], b[j]);
			j = next[j];//回到数组指向的位置
			isIn=false;
			if(a[i]!='\0'&&a[i]!='\n')
			{
			count++;
			printf("当前为第%d趟\n", count);
			}
		}
	}
	printf("匹配结束\n");
	for (k = 0; k <=length2; k++)
	{
		printf("模式串第%d个字符匹配的次数是%d\n", k+1, num[k]);
	}
	if (j >= length2&&isIn==true)//匹配成功
	{
		printf("匹配总趟数是%d\n", count);
		return i - length2;//返回匹配成功的位置
	}
	else
	{
		printf("匹配总趟数是%d\n", count);
		return 0;
	}
}
//改进的KMP算法
int KMP_Nextval(char* a, char* b, int pos)
{
	int length1, length2;
	length1 = strlen(a) - 1;
	length2 = strlen(b) - 1;
	int i = pos, j = 0, k = 0;
	int nextval[N];//定义一个next数组
	int num[N];
	bool isIn=true;
	bool is1 = true;
	printf("当前主串是%s\n", a);
	printf("当前子串是%s\n", b);
	Get_nextval(b, nextval);
	int count = 1;//记录比较次数
	for (i = 0; i <= length2; i++)//先为num数组赋0
	{
		num[i] = 0;
	}
	i = 0;
	while (i <= length1 && j <= length2)//如果匹配没到末尾
	{
		if (count == 1 && is1 == true)
		{
			printf("当前为第%d趟\n", count);
		}
		if (j == -1 || a[i] == b[j])//如果当前字符匹配相同或第一位就不同，继续匹配后续字符
		{
			if (j != -1)
			{
				num[j] += 1;
				printf("%c,%c\n", a[i], b[j]);
			}
			else
			{
				num[0] += 1;
			}
			i++;
			j++;
			is1 = false;
			isIn=true;
		}
		else
		{
			printf("%c,%c\n", a[i], b[j]);
			j = nextval[j];//回到数组指向的位置
			isIn=false;
			if(a[i]!='\0'&&a[i]!='\n')
			{
			count++;
			printf("当前为第%d趟\n", count);
			}
		}
	}
	printf("匹配结束\n");
	for (k = 0; k <= length2; k++)//先为num数组赋0
	{
		printf("模式串第%d个字符匹配的次数是%d\n", k + 1, num[k]);
	}
	if (j >= length2&&isIn==true)//匹配成功
	{
		printf("匹配总趟数是%d\n", count);
		return i - length2;//返回匹配成功的位置
	}
	else
	{
		printf("匹配总趟数是%d\n", count);
		return 0;
	}
}
//用于删除字符串
void Delete()
{
	int button;
	printf("请输入要删除的字符串类型\n");
	printf("1-主串 2-子串\n");
	while (scanf("%d", &button) != 1)
	{
		fgets(wrong,20,stdin);
		printf("输入不合法，请重新输入\n");
	}
	//如果删除主串
	if(button==1)
	{
	printf("请输入要删除的主串位置\n");
	while (scanf("%d", &button) != 1)
	{
		fgets(wrong,20,stdin);
		printf("输入不合法，请重新输入\n");
	}
	c1[button][0]='\0';
	}
	//如果删除子串
	if(button==2)
	{
	printf("请输入要删除的子串位置\n");
	while (scanf("%d", &button) != 1)
	{
		fgets(wrong,20,stdin);
		printf("输入不合法，请重新输入\n");
	}
	c2[button][0]='\0';
	}
}
int main()
{
	//显示用户菜单
	int button;

	int index = 1;//用于储存匹配起始位置
	int ans1=0, ans2=0, ans3=0;
	int a = 0;
	int x = 0;
	while (a < 100)//继续循环的条件
	{
		Menu();
		while (scanf("%d", &button) != 1)
		{
			fgets(wrong,20,stdin);
			printf("输入不合法，请重新输入\n");
		}
		switch (button)
		{
		case(0):
			printf("管理系统已退出!\n");
			a = 100;
			break;
		case(1):
			printf("请输入要储存的位置(1-100)\n");
			while (scanf("%d", &x) != 1)
			{
				fgets(wrong,20,stdin);
				printf("输入不合法，请重新输入\n");
			}
			getchar();
			printf("请输入主串\n");
			getString1(x);
			printf("请输入子串\n");
			getString2(x);
			while (strlen(c1[x]) < strlen(c2[x]))//如果子串长度大于主串
			{
				printf("子串长度大于主串，请重新输入正确的子串和主串\n");
				printf("请输入主串\n");
				scanf("%s", c1[x], 100);
				printf("请输入子串\n");
				getString2(x);
			}
			printf("请输入匹配起始位置\n");
			while ((scanf("%d", &index) != 1))//如果输入错误或者匹配位置大于主串位置
			{
				printf("请输入正确的起始位置\n");
				fgets(wrong,20,stdin);
			}
			if(index>strlen(c1[x]))
			{
			printf("匹配位置大于主串长度请输入正确的起始位置\n");
			while ((scanf("%d", &index) != 1))//如果输入错误或者匹配位置大于主串位置
			{
				printf("请输入正确的起始位置\n");
				fgets(wrong,20,stdin);
			}
			}
			Out();
			break;
		case(2):
			printf("请输入要进行匹配字符串的位置(1-100)\n");
			while (scanf("%d", &x) != 1)
			{
				fgets(wrong,20,stdin);
				printf("输入不合法，请重新输入\n");
			}
			while (strlen(c1[x])>N)
			{
				printf("您输入的位置当前无字符串储存\n");
				printf("请重新输入要进行匹配的位置(1-100)\n");
				while (scanf("%d", &x) != 1)
				{
					fgets(wrong,20,stdin);
					printf("输入不合法，请重新输入\n");
				}
			}
			ans1 = BF(c1[x], c2[x], index - 1);
			if (ans1 == 0)
			{
				printf("匹配失败\n");
			}
			else
			{
				printf("匹配成功，成功的位置序号是%d\n", ans1);
			}
			Out();
			break;
		case(3):
			printf("请输入要进行匹配的位置(1-100)\n");
			while (scanf("%d", &x) != 1)
			{
				fgets(wrong,20,stdin);
				printf("输入不合法，请重新输入\n");
			}
			if (strlen(c1[x]) >= 1)//如果有字符
			{
				ans2 = KMP(c1[x], c2[x], index - 1);
			}
			else
			{
				printf("您输入的位置当前无字符串储存\n");
				break;
			}
			if (ans2 == 0)
			{
				printf("匹配失败\n");
			}
			else
			{
				printf("匹配成功，成功的位置序号是%d\n", ans2);
			}
			Out();
			break;
		case(4):
			printf("请输入要进行匹配的位置(1-100)\n");
			while (scanf("%d", &x) != 1)
			{
				fgets(wrong,20,stdin);
				printf("输入不合法，请重新输入\n");
			}
			if (strlen(c1[x]) >= 1)//如果有字符，进行匹配
			{
				ans3 = KMP_Nextval(c1[x], c2[x], index - 1);
			}
			else
			{
				printf("您输入的位置当前无字符串储存\n");
				break;
			}
			if (ans3 == 0)
			{
				printf("匹配失败\n");
			}
			else
			{
				printf("匹配成功，成功的位置序号是%d\n", ans3);
			}
			Out();
			break;
		case(5):
		{
			printf("请输入要修改的串类型\n");
			printf("1-主串，2-子串\n");
			int b,c;
			while (scanf("%d", &b) != 1)
			{
				fgets(wrong,20,stdin);
				printf("输入不合法，请重新输入\n");
			}
			if(b==1)
			{
				printf("请输入要修改的主串位置\n");
				while (scanf("%d", &c) != 1)
			    {
				fgets(wrong,20,stdin);
				printf("输入不合法，请重新输入\n");
			    }
				printf("请输入修改后的字符串\n");
				getchar();
				getString1(c);
				break;
			}
			if(b==2)
			{
				printf("请输入要修改的子串位置\n");
				while (scanf("%d", &c) != 1)
			    {
				fgets(wrong,20,stdin);
				printf("输入不合法，请重新输入\n");
			    }
				printf("请输入修改后的字符串\n");
				getchar();
				getString2(c);
				break;
			}
			else
			{
				printf("当前无修改操作\n");
			}
			Out();
			break;
		}
		case(6):
		{
			Delete();
			break;
		}
		default:
			printf("无对应选项，请重新输入\n");
		    break;
		}
	}
	return 0;
}

