#ifndef __DOUBLELIST_H__
#define __DOUBLELIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define ARRAY_X 25
#define ARRAY_Y 50
struct ott_data_info {      
    long id;
	char cmd[ARRAY_X];
    char data[ARRAY_Y];
};


typedef struct doublelist{

      struct ott_data_info data;
      struct doublelist *next,*prev;
}double_list,*double_plist;

extern void init_doublelist(double_plist *L);
extern void insert_doublelist(double_plist p,double_plist pnew);
extern void insert_doublelist_tail(double_plist h,double_plist pnew);
extern void del_doublelist(double_plist p);
extern bool isempty_doublelist(double_plist l);
extern void show_doublelist(double_plist l);
extern int cmd_search_doublelist(double_plist l, char *str);
extern void release_doublelist(double_plist *l);
extern void create_doublelist(double_plist l, double_plist pnew);
extern void free_head(double_plist* pList);
extern void destroy_doublelist(double_plist* phead);
#endif
