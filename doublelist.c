#include "doublelist.h"


#define CHECK_POINTER(p1) \
	if(NULL == (p1)) \
    { \
        printf("[%s(%d)]Null Pointer: p1(%p)!\n", __func__, __LINE__, p1); \
        return; \
    } 
	
#define CHECK_DOUBLE_POINTER(p1, p2) \
	if(NULL == (p1) || NULL == (p2)) \
    { \
        printf("[%s(%d)]Null Pointer: p1(%p) p2(%p)!\n", __func__, __LINE__, p1, p2); \
        return;\
    } 

//初始化头结点
void init_doublelist(double_plist *L)
{
      //1.申请空间
      *L = (double_plist)calloc(1,sizeof(double_list));
      if(NULL == *L){
	    perror("[sun]==========calloc");
	    return ;
      }
      //2.2.头结点的next和prev都指向当前结点
      (*L)->next = *L;
      (*L)->prev = *L;
}

//h的前面插入pnew
void insert_doublelist_tail(double_plist h,double_plist pnew)
{
	CHECK_DOUBLE_POINTER(h, pnew);
	pnew->prev = h->prev;
	h->prev->next = pnew;
	pnew->next = h;
	h->prev = pnew;
}

//h的后面插入pnew
void insert_doublelist(double_plist h,double_plist pnew)
{
	
	  CHECK_DOUBLE_POINTER(h, pnew);
      pnew->next = h->next;
      h->next->prev = pnew;
      pnew->prev = h;
      h->next = pnew;
}

//删除单个结点
void del_doublelist(double_plist p)
{
	CHECK_POINTER(p);
	p->next->prev = p->prev;
	p->prev->next = p->next;
	p->next = NULL;
	p->prev = NULL;
	free(p);
}

//释放空间(删除除头结点以外的所有结点)
void release_doublelist(double_plist *l)
{   
	
	CHECK_POINTER(*l);
    double_plist p, ptem;
    for(p = (*l)->next; p != (*l); p = ptem)
    {
		ptem = p->next;
		p->next = NULL;
		p->prev = NULL;
        free(p);				
    }
	(*l)->next = (*l);
	(*l)->prev = (*l);
}


//判断链表是否为空
bool isempty_doublelist(double_plist l)
{
	
	  if(NULL == l) 
	  { 
		  printf("[%s(%d)]Null Pointer: l(%p)!\n", __func__, __LINE__, l); 
		  return false; 
	  } 
      if(l->next == l)
	    return true;
      else
	    return false;
}

//遍历
void show_doublelist(double_plist l)
{
	
	  CHECK_POINTER(l);
      double_plist p;
      printf("==========show_doublelist==========\n");
      for(p = l->next; p != l; p = p->next)
      {
	    printf("%ld\t%s\t%s\t",p->data.id,p->data.cmd,p->data.data);
        printf("\n");
      }
}

//查找
int cmd_search_doublelist(double_plist l, char *str)
{   
	
	if(NULL == l) 
    { 
        printf("[%s(%d)]Null Pointer: l(%p)!\n", __func__, __LINE__, l); 
        return -1; 
    } 
    double_plist p;
    for(p = l->next; p != l; p = p->next)
    {
	    if(0 == strcmp(p->data.cmd,str))
	    {
            return p->data.id;
        }
        else
            continue;           
    }
    return -1;
}

//创建双向循环链表
void create_doublelist(double_plist l, double_plist pnew)
{
	
	CHECK_POINTER(l);
    pnew = (double_plist)calloc(1,sizeof(double_list));
    if(NULL == pnew)
    {
	   perror("==========malloc");
	   return ;
    }
  
}
//只释放头结点
void free_head(double_plist* pList)
{
	
	CHECK_POINTER(pList);
	(*pList)->next = NULL;
	(*pList)->prev = NULL;
	free(*pList);
	(*pList) = NULL;
}
//销毁所有结点
void destroy_doublelist(double_plist* phead)
{
	CHECK_POINTER(phead);
	release_doublelist(phead);
	
	CHECK_POINTER(phead);
	free_head(phead);
}


