#ifndef __CMBURNSERVER_H__
#define __CMBURNSERVER_H__
 
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
 
#include <errno.h>
 
#include <sys/types.h>     
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <ctype.h>

//for ecos add
#include <netdb.h>
//for ecos add end

#include "doublelist.h"

//CM做服务器的端口号和地址 
#define SERV_PORT 49252	
#define PORT 10011
#define SERV_IP "192.168.0.1"

//WIFI密码的最小长度
#define Wifi80211DefaultkeyMinLEN 8


/***********************************
 OTT客户端请求测试结果         
***********************************/
#define TESTRESULT "TestResult"  // OTT向CM请求路由器测试结果
#define LEDTEST "LedTest"


/***********************************
 OTT客户端发送最终产品的测试结论      
***********************************/
#define TESTOK "TestOK"		
#define TESTNG "TestNG"


/***********************************
 OTT客户端接收  烧录/校验  信息成功
 #define RECEIVEROK "Receiver:OK"
***********************************/




/***********************************
CM服务器向OTT客户端返回测试结果      
***********************************/

#define APBUTTONTESTOK "ApButtonTestOK"  // 发送AP按键测试结果
#define APBUTTONTESTNG "ApButtonTestNG"


#define MODEMTESTOK "ModemTestOK"       //发送猫上线测试结果
#define MODEMTESTNG "ModemTestNG"

#define ROUTERTESTOK "RouterTestOK"     //发送路由器的测试结果
#define ROUTERTESTNG "RouterTestNG"

#define RESETBUTTONTESTOK "ResetButtonTestOK"   //发送路由器重置按键测试结果
#define RESETBUTTONTESTNG "ResetButtonTestNG"

/***********************************
CM服务器向OTT客户端返回烧录/校验结果
#define CHECKCM "checkCM"

***********************************/





#define QUIT_STR "CloseSocket"  //关闭网络连接





//数据分割标志位
#define STRTOKEN1 ","
#define STRTOKEN2 "-"
 
#define MAX_NAME_LEN 64
struct client_info {
//    struct list_head list;
    int newfd;
    struct sockaddr_in cin;
    char cli_name[MAX_NAME_LEN];
//...
};


/* NOYE:
	请小心处理这个枚举，他们的每一个成员值都是由自定义的算法计算而来，
	如果要加入新的成员，请直接通过烧录程序发送，然后在串口打印中寻找
	类似于以下的信息：
	==========show_doublelist==========
	748     Burn
	88      01      8C7D500BDD1E
	90      03      8C7D500BDD2E
	92      05      8C7D500BDD3E
	313     AP1     8C7D500BDD4E
	724     WIFIPW  HWEUBCB
	0

	请不要担心最后一行的0值，他是OTT发送过来的换行符，我在字符串拆分
	时是以【，】作为分割的，所以换行符也存入了链表，但在遍历链表处理
	指令时，我做了过滤处理。
	
	表中的第一列便是这个枚举的成员值，请对比AP1和WIFIPW你便会发现规律。
	如果新加入的枚举成员值与先前成员值冲突，最好修改新加入的字段内容，这是一个
	简单而有效的处理冲突方法，比如新加入一个WIFIPW和原来的任何一个成员冲突，
	请修改WIFIPW为其他字符直至其不与原成员值冲突为止。另外比较麻烦的做法是
	去修改CmBurnServer.c中的myatoi函数，这是一个非常麻烦的事情，需要你小心翼翼
	地去检查所有用到此枚举的代码，并验证其功能是否一一正常。
*/
	
enum cmd_id{//此ID号与链表中的ID号一一对应，但不包括基ID，如MAC_BASE,AP0_BASE,SN_BASE等

    //猫和路由的MAC
    MAC0_BASE = 87,
    MAC1,
    MAC2,
    MAC3,
    MAC4,
    MAC5,
    MAC6,
    MAC7,
    MAC8,
    MAC9,   
    MAC10,
    MAC11,  
    MAC12,   
    MAC13,
    MAC14,   
    MAC15,
    MAC16,//103

    //WIFI的MAC
    AP0_BASE = 312,
    AP1,
    AP2,
    AP3,
    AP4,
    AP5,
    AP6,
    AP7,
    AP8,
    AP9,
    AP10,
    AP11,
    AP12,
    AP13,
    AP14,
    AP15,//327

    //SN
    SN0_BASE = 370,
    SN1,
    SN2,
    SN3,//373

	//Wifi80211Defaultkey
    WIFIPW = 724,
    
    //OTT指令   
    Burn = 748,    
    TestNG  = 1059,
    TestOK  = 1065,
    CheckCM =  1164,
    LedTest  = 1310,//LED灯闪烁
    TestResult  = 2110,//请求路由器测试结果

};

#define SIZE_T  2//比较命令前两个字母
#define MA "MA"
#define AP "AP"
#define SN "SN"

void data_analysis(char *fdbuf, double_plist plist_data);
void mac_toupper(char *s);
long myatoi(char *s);
int segments_calculate(char *buf, char *str);



#endif
