#include "CmBurnServer.h"

//int is_send = 0;//是否发送全局buf的标志，0 表示不发送；1 表示发送
#undef BUFSIZ
#define BUFSIZ 8192
   /*分析并存储接收到数据*/
void data_analysis(char *fdbuf, double_plist plist_data)
{
    char  *str1, *str2, *token, *subtoken;
    char *saveptr1, *saveptr2;
    int i, j, segmentsnum;
    
    if (0 == strlen(fdbuf))
    {
       fprintf(stderr, "[sun]==========data_analysis error! buf length is 0\t fdbuf:%s\n",fdbuf);
       return ;
    }
    segmentsnum = segments_calculate(fdbuf, STRTOKEN1);  
     printf("[sun]==========segmentsnum = %d\n",segmentsnum);   
    //用链表存储数据
    double_plist pnew = NULL;
    printf("[sun]==========The data analysis results:\n");
    for (i = 0,  str1 = fdbuf; ; i++, str1 = NULL)
    {
       token = strtok_r(str1, STRTOKEN1, &saveptr1);
       if (token == NULL)
           break;
       //printf("[sun]==========%d: %s\n", i, token); 
       pnew = (double_plist)calloc(1,sizeof(double_list));
        if(NULL == pnew)
        {
    	   perror("[sun]==========calloc");
    	   return ;
        }
       for (j = 0, str2 = token; ; j++, str2 = NULL)
       {
           subtoken = strtok_r(str2, STRTOKEN2, &saveptr2);
           if (subtoken == NULL)
               break;
           //printf("[sun] --> %d  %s\n", j,subtoken);
           if(j == 0 && (*subtoken) != '\r' && (*subtoken) != '\n')
           {                 
               strncpy(pnew->data.cmd, subtoken, sizeof(pnew->data.cmd) - 1);
               pnew->data.id = myatoi(subtoken);
           }
           else if(j == 1)
           {               
               strncpy(pnew->data.data, subtoken, sizeof(pnew->data.data) - 1);
               //printf("[sun]==========pnew->data.data = %s\n",pnew->data.data);
           }
           
           //将pnew结点插入到链表中
           insert_doublelist_tail(plist_data, pnew);
       }
       
    }
    show_doublelist(plist_data);
 }

/*自定义的字符串转整形，为保证ID的唯一性*/
long myatoi(char *s)
{   
    long n = 0;
	 if (*s == '0')
	 {//首字符为0时，适用于MAC
		 s++;
		 n = 39;
	 }
	 else if(*s == 'A')
	 {//适用于AP
		 if (*(s + 3) == '\0')
		 {
			 n = 39;
		 }
	 }
	 while(*s != '\0')
	 {
		 if(*s <= 'M')
		 {
			 n += *s;
		 }
		 else
		 {
			 n += *s * 2;
		 }
		 s++;
	 }

    return n;
}

/*计算数据段数*/
int segments_calculate(char *buf, char *str)
 {
    int i, num = 0;
    for(i = 0; buf[i] != '\0' && i < strlen(buf); i++)
    {   
        if(buf[i] == ',')
            num++;
        
    }
    return num;
 }

