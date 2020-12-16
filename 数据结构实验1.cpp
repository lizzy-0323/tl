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
//用于表示浮点数可以接受的最小精度差值
const double eps = 1e-8;
//用于读取错误输入
 char wrong[100];
#define N 50
//用于比较浮点数
#define value(a,b) ((fabs((a) - (b)))<(eps)) 
//多项式节点的结构体定义
typedef struct H{
    double coef;
    double expn;
    struct H *next;
}HLink;
static int Is0 = 0;
//用于创建多项式
void Build(HLink *H)
{
    int i = 0;
    char a='y';
    HLink *p,*pend = NULL; 
    while(a != 'n'&&a!='N')
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
        printf("是否还要继续输入？y or n\n");
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
        //如果系数大于0
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
void Add(HLink *H,HLink H1,HLink H2)
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
            //相乘操作
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
void Delete(HLink *H)
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
    //用于次数的比较 
    double expn;  
    char pend[100];    
    int index[100] = {0};   
    //指针数组
    HLink *pt[100] = {NULL};  
//分别用于，加法，乘法，加法临时，乘法临时
    HLink *H1,*H2,*p3,*p4,*e = NULL; 
    //对指针进行初始化
    H1 = (HLink *)malloc(sizeof(HLink));
    H1->next = NULL;
    H2 = (HLink *)malloc(sizeof(HLink));
    H2->next = NULL;
    p3 = (HLink *)malloc(sizeof(HLink));
    p3->next = NULL;
    e = (HLink *)malloc(sizeof(HLink));
    e->next = NULL;
    while(1)
    {
        //打印菜单
        Menu();
        //检查用户输入是否有误
        while(scanf("%d", &button)!=1)
        {
            printf("输入错误，请重新输入\n");
            fgets(wrong,N,stdin);
        }
        switch(button)
        {
        case 1:
            {
                char a;
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
                    printf("是否录入下一个多项式？y or n\n");
                    a = getchar();
                    fgets(pend,N,stdin);
                } while(a =='Y'||a=='y'); 
                //显示已经建立的多项式
                break;
            }
        case 2:
            {
                //如果无多项式储存
                if(j == 0 && H1->next == NULL && H2->next ==NULL)
                {
                    printf("当前无多项式录入\n");
                }
                else
                {
                    for(int k = 0;k < j;k++)
                    {
                        printf("\n----当前为第%d个多项式--------\n",k+1);
                        OutOnenode(pt[k]);//以节点形式输出
                    }
                    if(H1->next != NULL)
                    {
                        printf("--------多项式为--------\n");
                        OutOnenode(H1);
                    }
                    if(H2->next != NULL)
                    {
                        printf("--------多项式为--------\n");
                        OutOnenode(H2);
                    }
                }
                break;
            }
        case 3:
        {
                //如果无多项式储存                
                if(j == 0 && H1->next == NULL && H2->next ==NULL)
                {
                    printf("当前无多项式录入\n");
                }
                else
                {
                    for(int k = 0;k < j;k++)
                    {
                        printf("\n-----第%d个多项式为--------\n",k+1);
                        Output(pt[k]);
                    }
                    if(H1->next != NULL)
                    {
                        printf("--------多项式为--------\n");
                        Output(H1);
                    }
                    if(H2->next != NULL)
                    {
                        printf("--------多项式为--------\n");
                        Output(H2);
                    }
                }
                break;
            }
        case 4:
            {
//如果无节点
                if(j == 0)
                {
                    printf("当前无多项式录入，不启用该功能！\n");
                    break;
                }
                int k=0;
                printf("请输入需要相加的多项式序号,输入0结束:\n");
                do
                {
                    while(!scanf("%d", &index[k]) || index[k] < 0 || index[k] > j)
                    {
                        printf("请正确输入\n");
                        fgets(wrong,N,stdin);
                    }
                    fgets(wrong,N,stdin);
                    k++;
                }while(index[k-1] != 0);
                k=0;
                Delete(p3);
                //从第一个数据开始
                while(index[k] != 0)
                {
                    if(k % 2 == 0)
                    {
                        Delete(H1);
                        Add(H1,*p3,*pt[index[k] - 1]);
                        Check0(H1);    
                    }
                    else
                    {
                        Delete(p3);
                        Add(p3,*H1,*pt[index[k] - 1]);
                        Check0(p3);    
                    }
                    k++;
                }
                if(k % 2 == 0)
                {
                    Delete(H1);
                    H1->next = p3->next;
                }
                else
                {
                    Delete(p3);
                }
                printf("-------相加后的多项式为--------\n");
                Output(H1);
                break;
            }
        case 5:
            {
                int k = 0;
//如果无节点
                if(j == 0)
                {
                    printf("当前无多项式录入，不启用该功能!\n");
                    break;
                }
                printf("当前共有%d个多项式\n",j);
                printf("请输入需要相乘的多项式序号，输入0结束\n");
                k=0;
                do
                {
                    while(!scanf("%d", &index[k]) || index[k] < 0 || index[k] > j)
                    {
                        printf("请正确输入\n");
                        fgets(wrong,N,stdin);
                    }
                    fgets(wrong,N,stdin);
                    k++;
                }while(index[k-1] != 0);
                if(index[0] == 0) 
                {
                    printf("当前没有选择多项式\n");
                    break;
                }
                Delete(e);
                if((p4 = (HLink *)malloc(sizeof(HLink))) == NULL) 
                {
                    printf("内存分配失败！");
                    exit(0);
                }
                p4->expn = 0;
                p4->coef = 1;
                e->next = p4;
                p4->next = NULL;
                k = 0;
                while(index[k] != 0)
                {
                    if(k % 2 == 0)
                    {
                        Delete(H2);
                        MultH(H2,*e,*pt[index[k] - 1]);
                        Swap(H2);         
                        Union(H2);        
                    }
                    else
                    {
                        Delete(e);
                        MultH(e,*H2,*pt[index[k] - 1]);
                        Swap(e);         
                        Union(e);        
                    }
                    k++;
                }
                if(k % 2 == 0)
                {
                    Delete(H2);
                    H2->next = e->next;
                }
                else
                {
                    Delete(e);
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








