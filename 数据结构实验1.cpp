/*
 @lizzy_0323
 FOR
 TIANLU
 翻版必究
 TODO：
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
const double eps = 1e-8;
#define N 50
#define value(a,b) ((fabs((a) - (b)))<(eps)) 
typedef struct H{
    double coef;
    double expn;
    struct H *next;
}HLink;
static int Is0 = 0;
//用于创建链表
void Build(HLink *H)
{
    int i = 0;
    char a;
    //用于读取错误输入
    char wrong[100];
    HLink *p,*pend = NULL; 
    while(a != '#')
    {
        if((p = (HLink *)malloc(sizeof(HLink))) == NULL) 
        {
            printf("内存分配失败！");
            exit(0);
        }
        if(H->next == NULL)  
        {
            H->next = p;   
            pend = p;    
        }
        else     
        {
            pend->next = p;    
            pend = p;           
        }
        printf("请输入第%d项的次数：", i + 1);
        while(!(scanf("%lf", &p->expn)))
        {
            fgets(wrong,N,stdin);    
            printf("请以正确的格式录入");
        }
        fgets(wrong,N,stdin);
        printf("请输入第%d项的系数为：",i + 1);
        while(!(scanf("%lf", &p->coef)))
        {
            fgets(wrong,N,stdin);    
            printf("请以正确的格式录入");
        }
        fgets(wrong,N,stdin);
        printf("是否还要继续输入？（#号结束）");
        a = getchar();  //读取用户输入
        fgets(wrong,N,stdin);
        i++;
    }
    p->next = NULL;
}
//节点形式输出
void OutOnenode(HLink *H)
{
    HLink *p = NULL;    
    if(H->next == NULL)
    {
        if(Is0 == 0)
        {
            printf("当前多项式为空");
        }
        else
        {
            printf("次数为：0 系数为：0\n\n");
        }
    }
    p = H->next;      
    while(p != NULL)
    {
        printf("次数为:%.2f,系数为：%.2f\n\n",p->expn, p->coef);
        p = p->next;  
    }
}
//以多项式格式输出
void Output(HLink *H)
{
    HLink *p = NULL;    
    if(H->next == NULL)
    {
        if(Is0 == 0)
        {
            printf("当前多项式为空！");
        }
        else
        {
            printf("0");
        }
        return;
    }
    p = H->next;      
    if(value(p->expn,1))  
    {
        if(value(p->coef,1))  
        {
            printf("x");    
        }
        else if(value(p->coef,-1)) 
        {
           printf("-x");
        }
        else
        {
            printf("%.2fx",p->coef);
        }
    }
    else if(value(p->expn,0)) 
    {
        printf("%.2f",p->coef);
    }
    else
    {
        if(value(p->coef,1)) 
        {
            printf("x^%.2f",p->expn);  
        }
        else if(value(p->coef,-1)) 
        {
           printf("-x^%.2f",p->expn);
        }
        else
        {
            printf("%.2fx^%.2f",p->coef, p->expn);
        }
    }
    p = p->next;    
    while(p != NULL) 
    {
        if(p->coef > 0)  
        {
            printf("+"); 
            if(value(p->expn,1))
            {
                if(value(p->coef,1))
                {
                    printf("x");
                }
                else
                {
                    printf("%.2fx",p->coef);
                }
            }
            else if(value(p->expn,0))
            {
                printf("%.2f",p->coef);
            }
            else
            {
                if(value(p->coef,1))
                {
                    printf("x^%.2f",p->expn);
                }
                else
                {
                    printf("%.2fx^%.2f",p->coef,p->expn);
                }
            }
        }
        else    //如果系数为小于0
        {
            printf("-"); 
            if(value(p->expn,1))
            {
                if(value(p->coef,-1))
                {
                    printf("x");
                }
                else
                {
                    printf("%.2fx",(-(p->coef)));
                }
            }
            else if(value(p->expn,0))
            {
                printf("%.2f",(-(p->coef)));
            }
            else
            {
                if(value(p->coef,-1))
                {
                    printf("x^%.2f",p->expn);
                }
                else
                {
                    printf("%.2fx^%.2f",(-(p->coef)), p->expn); 
                }
            }
        }
        p = p->next;
    }
}
//相加函数
void AddNode(HLink *H,HLink H1,HLink H2)
{
    HLink *p,*q,*temp,*pend = NULL;
    if(H1.next == NULL && H2.next == NULL)  
    {
        return;
    }
    p = H1.next;
    q = H2.next;
    while(p && q)
    {
        //为临时节点分配内存
        if((temp = (HLink *)malloc(sizeof(HLink))) == NULL) 
        {
            printf("内存分配失败！");
            exit(0);
        }
        //如果当前节点为空
        if(H->next == NULL)
        {
            H->next = temp;
            pend = temp;
        }
        if(p->expn > q->expn)
        {
            *temp = *p;
            p = p->next;
        }
        else if(p->expn == q->expn)
        {
            *temp = *p;
            temp->coef = p->coef + q->coef;
            p = p->next;
            q = q->next;
        }
        else
        {
            *temp = *q;
            q = q->next;
        }
        pend->next = temp;
        pend = temp;
    }
    while(p) 
    {
        if((temp = (HLink *)malloc(sizeof(HLink))) == NULL) 
        {
            printf("内存分配失败！");
            exit(0);
        }
        *temp= *p;
        if(H->next == NULL) 
        {
            H->next =temp;
        }
        else
        {
            pend->next = temp;
        }
        pend = temp;
        p = p->next;
    }
    while(q)    
    {
        if((temp = (HLink *)malloc(sizeof(HLink))) == NULL) 
        {
            printf("内存分配失败！");
            exit(0);
        }
        *temp = *q;
        if(H->next == NULL)
        {
            H->next = temp;
        }
        else
        {
            pend->next = temp;
        }
        pend = temp;
        q = q->next;
    }
    temp->next = NULL; 
}
//相乘函数
void MultH(HLink *H,HLink H1,HLink H2)
{
    HLink *p,*q,*r,*pend = NULL;
    q = H1.next;
    //如果有空节点，直接返回
    if(H1.next == NULL || H2.next == NULL)
    {
        return;
    }
    while(q)
    {
        r = H2.next;
        while(r)
        {
            if((p = (HLink *)malloc(sizeof(HLink))) == NULL) 
            {
                printf("内存分配失败！");
                exit(0);
            }
            if(H->next == NULL)
            {
                H->next = p; 
                pend = p; 
            }
            else 
            {
                pend->next = p;    
                pend = p;          
            }
            p->expn = r->expn + q->expn;     
            p->coef = (r->coef) * (q->coef);  
            r = r->next;    
        }
        q = q->next; 
    }
    p->next = NULL; 
}
//合并函数
void Union(HLink *H)
{
    HLink *now,*pend,*p = NULL;
    if(H->next == NULL) 
    {
        return;
    }
    now = H->next;
    pend = now->next;
    while(pend)
    {
        if(now->expn == pend->expn) 
        {
            now->coef += pend->coef;   
            p = pend;                    
            pend = pend->next;        
            now->next = pend;           
            free(p);                       
        }
        else    
        {
            now = now->next;     
            pend = pend->next;
        }
    }
}
//多项式排序函数
void Swap(HLink *H)
{
    HLink *pre, *p, *pend,*phead=H->next;
    //如果当前多项式为空
    if(H->next == NULL)
    {
        return;
    }
    p=phead->next; 
    phead->next = NULL;   
    //当前节点不为空
    while(p != NULL)
    {
        pend = p->next;      
        pre = H;     
        while(pre->next != NULL && ((pre->next->expn) > (p->expn)))   
        {
            pre = pre->next;
        }
        p->next = pre->next;  
        pre->next = p;       
        p = pend;   
    }
}
//检查是否有清零的函数
void Check0(HLink *H)
{
    HLink *pre,*p,*pend = NULL; 
    pre = H;
    p = H->next;
    while(p != NULL)
    {
        if(p->coef == 0)  
        {
            pre->next = p->next;
            pend = p;
            p = p->next;
            free(pend);
            Is0 = 1;
        }
        else   
        {
            p = p->next;
            pre = pre->next;
        }
    }
}
//清除多项式函数
void Check(HLink *H)
{
    HLink *p,*pend = NULL;
    p = H->next;
    while(p)
    {
        pend = p;
        p = p->next;
        free(pend);
    }
    H->next = NULL;
}
//用于显示菜单
void Menu()
{
    printf("请输入序号选择功能：\n");
    printf("1、录入新的多项式\n");
    printf("2、显示多项式各项次数为和对应系数\n");
    printf("3、输出多项式表达式\n");
    printf("4、多项式加法\n");
    printf("5、多项式乘法\n");
    printf("0、退出\n");
}
//主函数
int main()
{
    int  button;
    int j = 0;   
    double expn;    
    char pend[100];    
    int index[100] = {0};   
    //指针数组
    HLink *pt[100] = {NULL};  
    HLink *H1,*H2,*q,*r,*e = NULL; 
    //对指针进行初始化
    H1 = (HLink *)malloc(sizeof(HLink));
    H1->next = NULL;
    H2 = (HLink *)malloc(sizeof(HLink));
    H2->next = NULL;
    q = (HLink *)malloc(sizeof(HLink));
    q->next = NULL;
    e = (HLink *)malloc(sizeof(HLink));
    e->next = NULL;
    while(1)
    {
        //打印菜单
        Menu();
        scanf("%d", &button);
        switch(button)
        {
        case 1:
            {
                char a;
                for(int index = 0;index < j;index++)
                {
                    Check(pt[index]); 
                }
                j = 0; 
                //读取用户输入
                do 
                {
                    if((pt[j] = (HLink *)malloc(sizeof(HLink))) == NULL) 
                    {
                        printf("内存分配失败！");  //如果分配失败
                        exit(0);
                    }
                    pt[j]->next = NULL;  
                    printf("当前为第%d个多项式\n",j + 1); 
                    Build(pt[j]);  
                    Check0(pt[j]);    
                    Swap(pt[j]);         
                    Union(pt[j]);  
                    j++; 
                    printf("是否还要继续录入？（#号结束)");
                    a = getchar();
                    fgets(pend,N,stdin);
                } while(a != '#');   //输入#时结束
                printf("\n");
                break;
            }
        case 2:
            {
                if(j == 0 && H1->next == NULL && H2->next ==NULL)
                {
                    printf("没有录入任何数据!\n");
                }
                else
                {
                    for(int k = 0;k < j;k++)
                    {
                        printf("----当前为第%d个多项式--------\n",k+1);
                        OutOnenode(pt[k]);
                    }
                    if(H1->next != NULL)
                    {
                        printf("--------多项式1为--------\n");
                        OutOnenode(H1);
                    }
                    if(H2->next != NULL)
                    {
                        printf("--------多项式2为--------\n");
                        OutOnenode(H2);
                    }
                }
                break;
            }
        case 3:
            {
                if(j == 0 && H1->next == NULL && H2->next ==NULL)
                {
                    printf("没有录入任何数据!\n");
                }
                else
                {
                    for(int k = 0;k < j;k++)
                    {
                        printf("-----第%d个多项式--------\n",k+1);
                        Output(pt[k]);
                    }
                    if(H1->next != NULL)
                    {
                        printf("--------多项式1为--------\n");
                        Output(H1);
                    }
                    if(H2->next != NULL)
                    {
                        printf("--------多项式2为--------\n");
                        Output(H2);
                    }
                }
                break;
            }
        case 4:
            {
                if(j == 0)
                {
                    printf("当前无多项式录入！\n");
                    break;
                }
                printf("当前共有%d个多项式\n",j);
                int k;
                for(k = 0;k < j;k++)
                {
                    printf("第%d个多项式：",k + 1);
                    Output(pt[k]);
                    printf("\n");
                }
                printf("请输入需要相加的多项式序号,输入0后结束:");
                k = 0;
                Check(q);
                while(index[k] != 0)
                {
                    if(k % 2 == 0)
                    {
                        Check(H1);
                        AddNode(H1,*q,*pt[index[k] - 1]);
                        Check0(H1);    
                    }
                    else
                    {
                        Check(q);
                        AddNode(q,*H1,*pt[index[k] - 1]);
                        Check0(q);    
                    }
                    k++;
                }
                if(k % 2 == 0)
                {
                    Check(H1);
                    H1->next = q->next;
                }
                else
                {
                    Check(q);
                }
                printf("--------相加后的多项式为--------\n");
                Output(H1);
                break;
            }
        case 5:
            {
                int k = 0;
                if(j == 0)
                {
                    printf("当前无多项式录入!\n");
                    break;
                }
                printf("当前共有%d个多项式",j);
                for(k = 0;k < j;k++)
                {
                    printf("第%d个多项式：",k + 1);
                    Output(pt[k]);
                    printf("\n");
                }
                printf("请输入需要相乘的多项式序号，(输入0后结束输入):");
                k = 0;
                if(index[0] == 0) 
                {
                    printf("当前没有选择多项式\n");
                    break;
                }
                Check(e);
                if((r = (HLink *)malloc(sizeof(HLink))) == NULL) 
                {
                    printf("内存分配失败！");
                    exit(0);
                }
                r->expn = 0;
                r->coef = 1;
                e->next = r;
                r->next = NULL;
                k = 0;
                while(index[k] != 0)
                {
                    if(k % 2 == 0)
                    {
                        Check(H2);
                        MultH(H2,*e,*pt[index[k] - 1]);
                        Swap(H2);         
                        Union(H2);        
                    }
                    else
                    {
                        Check(e);
                        MultH(e,*H2,*pt[index[k] - 1]);
                        Swap(e);         
                        Union(e);        
                    }
                    k++;
                }
                if(k % 2 == 0)
                {
                    Check(H2);
                    H2->next = e->next;
                }
                else
                {
                    Check(e);
                }
                printf("-------相乘后的多项式为--------\n");
                Output(H2);
                break;
            }
        case 0:
        {
            printf("程序已安全退出\n");
            exit(0);
            break;
        }
        default:
        {
        printf("输入错误，请重新输入！\n\n");
        break;
        }
        }
    }
    return 0;
}








