/*****************************************************************
 *  文件名      ：dsf_sfyz
 *  文件功能    ：深圳实时代收付户名验证的一些函数
 *  编程者      ：Chenwl
 *  初作时间    ：2003/8/6
 *  版本        : 1.0
 *  --------------------------------------------------
 *      时间                修改者      注释
 *      2003/8/6           Chenwl      创建
 *	2004/08/06         Chenwl      验证分为存折，卡，对公三种（以前只是一种)
 *****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "pool.h"
#include "dai.h"
#include "tpulib.h"


#include "tccontract_T.h"
#define TAIL_LEN 10
extern char aczLogFile[100];
#define DSF_RetMapFile  "ssdsfretmap"
#define DSF_DANWDM "SZPOWER"
#define DSF_MAX_RETMAP  100

/*****************************************************************
 *  函 数 名:YzProc
 *  函数功能: 鉴权交易
 *  编 程 者:chenwl
 *  参数:    
 *    
 *  返 回 值: SUCCESS 成功
 *    FAIL    失败
 *  调用自定义函数:
 *  处理概要:
 *  全局变量:
 *  修改的全局变量:
 *  完成时间: 2008/09/24
 *  最后修改时间:   2008/09/24
*****************************************************************/
int YzProc()
{
		char aczTemp[100];
		char aczZhangh[30];
		char aczJilubh[30];
		char aczUserno[30];
		char aczFujshj[60];
		char aczZhjhao[30];
		char aczJioylb[3];
		char aczRetCode[20];
		char aczRetMsg[60];
		char aczStatus[20];
		
		char aczKehhao[20];
		char aczKehuxm[60];
		char aczguojii[60];
		char aczZhjnzl[10];
		char aczzjzjho[60];
		char aczDizhii[60];
		char aczLxdian[30];
		char aczKhzhlx[2];
		char aczPkt[2048];
		char aczSuff[20];		
		int iRows;
		int i;

		TTccontract stTccontract;


		
		
		int iLen;
		int iRetCode;
	
		RunLog();
	
	
    
		/*====================UserCode Begin====================*/
   	TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:--------------帐号检查开始------------------",__FILE__,__LINE__ );
  	/************初始化变量***********************/
		memset(aczZhangh,0,sizeof(aczZhangh));
		memset(aczJilubh,0,sizeof(aczJilubh));
		memset(aczUserno,0,sizeof(aczUserno));
		memset(aczFujshj,0,sizeof(aczFujshj));
		memset(aczZhjhao,0,sizeof(aczZhjhao));
		memset(aczJioylb,0,sizeof(aczJioylb));
		memset(aczRetCode,0,sizeof(aczRetCode));
		memset(aczRetMsg,0,sizeof(aczRetMsg));
		memset(aczStatus,0,sizeof(aczStatus));
		memset(aczKehhao,0,sizeof(aczKehhao));
		memset(aczKehuxm,0,sizeof(aczKehuxm));
		memset(aczguojii,0,sizeof(aczguojii));
		memset(aczZhjnzl,0,sizeof(aczZhjnzl));
		memset(aczzjzjho,0,sizeof(aczzjzjho));
		memset(aczDizhii,0,sizeof(aczDizhii));
		memset(aczLxdian,0,sizeof(aczLxdian));
		memset(aczKhzhlx,0,sizeof(aczKhzhlx));		
		memset(aczPkt,0,sizeof(aczPkt));			
		memset(aczSuff,0,sizeof(aczSuff));		
		memset((char*)&stTccontract,0,sizeof(stTccontract));
	
		PGetStr("GOLD2",aczZhangh,sizeof(aczZhangh));     /*帐号*/
		PGetStr("GOLD37",aczJilubh,sizeof(aczJilubh));		/*供电局流水*/
		PGetStr("GOLD42",aczUserno,sizeof(aczUserno));		/*供电局用户代码*/
		PGetStr("GOLD48",aczFujshj,sizeof(aczFujshj));		/*附加数据，用户身份证号码|*/
		strncpy(aczTemp,aczFujshj,3);
		iLen=atoi(aczTemp);
		strncpy(aczZhjhao,aczFujshj+3,iLen);
		PGetStr("GOLD104",aczJioylb,sizeof(aczJioylb));		/*交易类别*/
		
		
     	
 		TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:帐号[%s]", __FILE__,__LINE__,aczZhangh);
 		TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:供电局流水[%s]", __FILE__,__LINE__,aczJilubh); 
 		TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:供电局用户代码[%s]", __FILE__,__LINE__,aczUserno); 
    TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:附加数据[%s]", __FILE__,__LINE__,aczFujshj);     
		TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:证件号码[%s]", __FILE__,__LINE__,aczZhjhao);     
		TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:交易类别[%s]", __FILE__,__LINE__,aczJioylb);     
    
    
		if (strncmp(aczJioylb,"JQ",2)!=0)
  	{
    	TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:交易类别不为鉴权[%s]", __FILE__,__LINE__,aczJioylb);     
			PPutStr("GOLD39","12");	 /*无效交易*/							
	    return FAIL;
  	}
   
    
 	

     		/*查询帐户类型*/
		PPutStr("KHZHLX","");
		PPutStr("KEHUZH",aczZhangh);

		iRetCode=FLC_RunAtTrByName("tchst_chx");
		if ( iRetCode <0 )
		{
			TRC_Trace(1, 3, aczLogFile, "YzProc查询客户信息错[%d]",__FILE__,__LINE__,iRetCode );	
			PPutStr("GOLD39","96");	 /*通讯失败*/			
			
			return FAIL;
		}
		PGetStr("TPU_RetCode",aczRetCode,sizeof(aczRetCode));
		TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:TPU_RetCode[%s]",__FILE__,__LINE__,aczRetCode );	
		if ( 0!=strcmp(aczRetCode,"AAAAAAA"))
		{
				TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:TPU_RetCode[%s]",__FILE__,__LINE__,aczRetCode );	
				PGetStr("TPU_RetMsg",aczRetMsg,sizeof(aczRetMsg));
				TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:TPU_RetMsg[%s]",__FILE__,__LINE__,aczRetMsg );
				dsf_kf_MapRetCode(aczRetCode,aczStatus);
				TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:aczStatus[%s]",__FILE__,__LINE__,aczStatus );	
			
		
		}
		
		
		PGetStr("KHZHLX",aczKhzhlx,sizeof(aczKhzhlx));

		TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:KHZHLX[%s]",__FILE__,__LINE__,aczTemp );	
		PPutStr("KHZHLX",aczKhzhlx);
			
		//tchst_chx
	  	
		/***************************************
		调用主机7702交易
		取得响应的客户信息
		***************************************/
		PPutStr("KEHUZH",aczZhangh);
		PPutStr("MMJYFS","0");
		PPutStr("JIOYMM","");
		iRetCode=FLC_RunAtTrByName("ssdsf_khjy");
		if ( iRetCode <0 )
		{
				TRC_Trace(1, 3, aczLogFile, "YzProc查询客户信息错[%d]",__FILE__,__LINE__,iRetCode );	
				return FAIL;
		}
		PGetStr("TPU_RetCode",aczRetCode,sizeof(aczRetCode));
		TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:TPU_RetCode[%s]",__FILE__,__LINE__,aczRetCode );	
		if ( 0!=strcmp(aczRetCode,"AAAAAAA"))
		{
			TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:TPU_RetCode[%s]",__FILE__,__LINE__,aczRetCode );	
			PGetStr("TPU_RetMsg",aczRetMsg,sizeof(aczRetMsg));
			TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:TPU_RetMsg[%s]",__FILE__,__LINE__,aczRetMsg );
			dsf_kf_MapRetCode(aczRetCode,aczStatus);
			PPutStr("GOLD39",aczStatus);	 /*无效交易*/	
			TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:aczStatus[%s]",__FILE__,__LINE__,aczStatus );	
			return FAIL;
			
		}
			
		/*获取7702返回信息*/

		PGetStr("KEHHAO",aczKehhao,sizeof(aczKehhao));  /* 客户号   */
		PGetStr("KEHUXM",aczKehuxm,sizeof(aczKehuxm));  /* 客户姓名 */

		PGetStr("GUOJII",aczguojii,sizeof(aczguojii));  /* 国籍     */
		PGetStr("ZHJNZL",aczZhjnzl,sizeof(aczZhjnzl));  /* 证件种类 */
		PGetStr("ZHJHAO",aczzjzjho,sizeof(aczzjzjho));  /* 证件号码 */
		PGetStr("DIZHII",aczDizhii,sizeof(aczDizhii));  /* 地址     */
		PGetStr("LXDIAH",aczLxdian,sizeof(aczLxdian));  /* 联系电话 */
		TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:aczKehhao[%s]",__FILE__,__LINE__,aczKehhao );
		TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:aczKehuxm[%s]",__FILE__,__LINE__,aczKehuxm );
		TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:aczguojii[%s]",__FILE__,__LINE__,aczguojii );
		TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:aczZhjnzl[%s]",__FILE__,__LINE__,aczZhjnzl );
		TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:aczzjzjho[%s]",__FILE__,__LINE__,aczzjzjho );
		TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:aczDizhii[%s]",__FILE__,__LINE__,aczDizhii );
		TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:aczLxdian[%s]",__FILE__,__LINE__,aczLxdian );
		if (aczKhzhlx[0]=='0')
		{
			PPutStr("KEHHAO",aczKehhao);
		
			iRetCode=FLC_RunAtTrByName("ssdsf_0106");
			if ( iRetCode <0 )
			{
					TRC_Trace(1, 3, aczLogFile, "YzProc查询客户信息错[%d]",__FILE__,__LINE__,iRetCode );	
					return FAIL;
			}
			PGetStr("TPU_RetCode",aczRetCode,sizeof(aczRetCode));
			TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:TPU_RetCode[%s]",__FILE__,__LINE__,aczRetCode );	
			if ( 0!=strcmp(aczRetCode,"AAAAAAA"))
			{
				TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:TPU_RetCode[%s]",__FILE__,__LINE__,aczRetCode );	
				PGetStr("TPU_RetMsg",aczRetMsg,sizeof(aczRetMsg));
				TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:TPU_RetMsg[%s]",__FILE__,__LINE__,aczRetMsg );
				dsf_kf_MapRetCode(aczRetCode,aczStatus);
				PPutStr("GOLD39",aczStatus);	 /*无效交易*/	
				TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:aczStatus[%s]",__FILE__,__LINE__,aczStatus );	
				return FAIL;
				
			}
			
			/*获取0106返回信息*/

			/* 从POOL池中取出表格报文 */
                      iLen=PGetMem("F01061",aczPkt,sizeof(aczPkt));

                      /* 调用表格拆包函数 */
                     iRetCode=APP_PUB_UnpackForm('0',aczPkt,iLen);
                      if ( iRetCode<0 )
                      {
				PPutStr("GOLD39","96");	 /*无效交易*/	
				return FAIL;
                      }

                      /* 取出表格的行数 */
                      PGetMem("F01061_Rows",&iRows,sizeof(int));

                      /* 使用表格数据 */
                      for (i=0;i<iRows;i++)
                      {

				memset(aczKehhao,0,sizeof(aczKehhao));
				sprintf(aczSuff,"_%d",i);
				POOL_SetGetSuff(aczSuff);       /* 设置POOL池数据名后缀 */
				PGetStr("QIYEDM",aczzjzjho,sizeof(aczzjzjho));/*组织机构代码*/
				//TPL_Trace(4,__FILE__,__LINE__,"QIYEDM=[%s]",aczzjzjho);

				POOL_SetGetSuff("");    /* 清除POOL池数据名后缀，非常重要，出错退出时请不要忘记 */

                               
                        }
			

		}
		    
	    	

		
			
		if (0!=strcmp(aczzjzjho,aczZhjhao))
		{
				TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:证件号不符",__FILE__,__LINE__ );
				PPutStr("GOLD39","12");	 /*无效交易*/	
				return FAIL;
			  	
		}	
		PPutStr("GOLD39","00");	
		strcpy(stTccontract.aczDanwdm,DSF_DANWDM); /*单位代码*/
		strcpy(stTccontract.aczHuobdh,"00");/*币种*/
		strcpy(stTccontract.aczDsdfdm,"441"); /*电费*/
		strcpy(stTccontract.aczXinzhh,aczZhangh);/*账号*/
		strcpy(stTccontract.aczCjiobh,aczJilubh);/*供电局流水号*/
		PGetStr("TPU_SysDate",stTccontract.aczSqngrq,sizeof(stTccontract.aczSqngrq));/*申请日期*/
		strcpy(stTccontract.aczJiluzt,"0"); /*记录状态*/
		iRetCode = tccontract_Insert((char*)&stTccontract,1);
		if (iRetCode <0)
		{
			PPutStr("GOLD39","96");	
			return FAIL;
		}
	
		
    
     
     
		TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:--------------帐号检查结束------------------",__FILE__,__LINE__ );

		return 0;
}
int dsf_kf_MapRetCode(char *c_pczHostRetCode,char *c_pczRhRetCode)
{
        static time_t   tLastModify=0;
        static int      iRetCount=0;
        static char     aczHostRet[DSF_MAX_RETMAP][32];
        static char     aczRhRet[DSF_MAX_RETMAP][32];
        char    aczFullFile[128];
        struct stat     stStat;
        FILE    *fpFile;
        char    aczLine[256];
        int             i;

        sprintf(aczFullFile,"%s/etc/%s",getenv("IPPBASE"),DSF_RetMapFile);
        TRC_Trace(1,3,aczLogFile," dsf_kf_MapRetCode:c_pczHostRetCode[%s]",c_pczHostRetCode);
        TRC_Trace(1,3,aczLogFile," dsf_kf_MapRetCode:aczFullFile[%s]",aczFullFile);
        if ( stat(aczFullFile,&stStat)==0 && (stStat.st_mtime-tLastModify)>=3 )
        {
                fpFile=fopen(aczFullFile,"r");
                if ( fpFile==NULL )
                {
                        TRC_Trace(1,3,aczLogFile," dsf_kf_MapRetCode:fopen fail[%d][%s]",errno,aczFullFile);
                        /*TRC_Trace(g_iTrcLevel,6,g_aczTrcFile,
                                        "[%s:%d],fopen fail(%d,%s)",
                                        __FILE__,__LINE__,errno,aczFullFile);*/
                        return FAIL;
                }

                while ( 1 )
                {
                	if ( fgets(aczLine,256,fpFile)==NULL )
                                break;

                     if ( aczLine[0]=='#' || aczLine[0]=='\0' || aczLine[0]=='\n' ||
                                        aczLine[0]==' ' || aczLine[0]=='\t' )
                                continue;
											sscanf(aczLine,"%s %s",aczHostRet[iRetCount],aczRhRet[iRetCount]);
                     	iRetCount++;
                     	if ( iRetCount>=DSF_MAX_RETMAP )
                     		break;
                }			

                fclose(fpFile);

                tLastModify=stStat.st_mtime;
        }

        for (i=0;i<iRetCount;i++)
        {
                if ( strcmp(c_pczHostRetCode,aczHostRet[i])==0 )
                {
                        strcpy(c_pczRhRetCode,aczRhRet[i]);
                        c_pczRhRetCode[3]='\0';
                        TRC_Trace(1,3,aczLogFile," dsf_kf_MapRetCode:c_pczRhRetCode[%s]",c_pczRhRetCode);
                        return SUCCESS;
                }
        }

        strcpy(c_pczRhRetCode,"M04");
        TRC_Trace(1,3,aczLogFile," dsf_kf_MapRetCode:c_pczRhRetCode[%s]",c_pczRhRetCode);
        TRC_Trace(1,3,aczLogFile," dsf_kf_MapRetCode:EB_2004_MapRetCode[%s]","end");
        c_pczRhRetCode[3]='\0';
        return SUCCESS;
}
/*****************************************************************
 *  函 数 名:RunLog
 *  函数功能: 取日志文件
 *  编 程 者:chenwl
 *  参数:
 *
 *  返 回 值: SUCCESS 成功
 *    FAIL    失败
 *  调用自定义函数:
 *  处理概要:
 *  全局变量:
 *  修改的全局变量:
 *  完成时间: 2006/02/20
 *  最后修改时间:   2006/02/20
*****************************************************************/
int RunLog()
{
	struct tm *ptr;
	time_t lt;
	char str[80];
	lt=time(NULL);
	ptr=localtime(&lt);
	strftime(str,100,"%Y%m%d",ptr);
	
	
	sprintf(aczLogFile,"%s/dldsfyz%s.log",getenv("RUNLOG"),str);
	

	return 0;
}
