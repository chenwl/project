/*****************************************************************
 *  �ļ���      ��dsf_sfyz
 *  �ļ�����    ������ʵʱ���ո�������֤��һЩ����
 *  �����      ��Chenwl
 *  ����ʱ��    ��2003/8/6
 *  �汾        : 1.0
 *  --------------------------------------------------
 *      ʱ��                �޸���      ע��
 *      2003/8/6           Chenwl      ����
 *	2004/08/06         Chenwl      ��֤��Ϊ���ۣ������Թ����֣���ǰֻ��һ��)
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
 *  �� �� ��:YzProc
 *  ��������: ��Ȩ����
 *  �� �� ��:chenwl
 *  ����:    
 *    
 *  �� �� ֵ: SUCCESS �ɹ�
 *    FAIL    ʧ��
 *  �����Զ��庯��:
 *  �����Ҫ:
 *  ȫ�ֱ���:
 *  �޸ĵ�ȫ�ֱ���:
 *  ���ʱ��: 2008/09/24
 *  ����޸�ʱ��:   2008/09/24
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
   	TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:--------------�ʺż�鿪ʼ------------------",__FILE__,__LINE__ );
  	/************��ʼ������***********************/
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
	
		PGetStr("GOLD2",aczZhangh,sizeof(aczZhangh));     /*�ʺ�*/
		PGetStr("GOLD37",aczJilubh,sizeof(aczJilubh));		/*�������ˮ*/
		PGetStr("GOLD42",aczUserno,sizeof(aczUserno));		/*������û�����*/
		PGetStr("GOLD48",aczFujshj,sizeof(aczFujshj));		/*�������ݣ��û����֤����|*/
		strncpy(aczTemp,aczFujshj,3);
		iLen=atoi(aczTemp);
		strncpy(aczZhjhao,aczFujshj+3,iLen);
		PGetStr("GOLD104",aczJioylb,sizeof(aczJioylb));		/*�������*/
		
		
     	
 		TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:�ʺ�[%s]", __FILE__,__LINE__,aczZhangh);
 		TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:�������ˮ[%s]", __FILE__,__LINE__,aczJilubh); 
 		TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:������û�����[%s]", __FILE__,__LINE__,aczUserno); 
    TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:��������[%s]", __FILE__,__LINE__,aczFujshj);     
		TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:֤������[%s]", __FILE__,__LINE__,aczZhjhao);     
		TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:�������[%s]", __FILE__,__LINE__,aczJioylb);     
    
    
		if (strncmp(aczJioylb,"JQ",2)!=0)
  	{
    	TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:�������Ϊ��Ȩ[%s]", __FILE__,__LINE__,aczJioylb);     
			PPutStr("GOLD39","12");	 /*��Ч����*/							
	    return FAIL;
  	}
   
    
 	

     		/*��ѯ�ʻ�����*/
		PPutStr("KHZHLX","");
		PPutStr("KEHUZH",aczZhangh);

		iRetCode=FLC_RunAtTrByName("tchst_chx");
		if ( iRetCode <0 )
		{
			TRC_Trace(1, 3, aczLogFile, "YzProc��ѯ�ͻ���Ϣ��[%d]",__FILE__,__LINE__,iRetCode );	
			PPutStr("GOLD39","96");	 /*ͨѶʧ��*/			
			
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
		��������7702����
		ȡ����Ӧ�Ŀͻ���Ϣ
		***************************************/
		PPutStr("KEHUZH",aczZhangh);
		PPutStr("MMJYFS","0");
		PPutStr("JIOYMM","");
		iRetCode=FLC_RunAtTrByName("ssdsf_khjy");
		if ( iRetCode <0 )
		{
				TRC_Trace(1, 3, aczLogFile, "YzProc��ѯ�ͻ���Ϣ��[%d]",__FILE__,__LINE__,iRetCode );	
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
			PPutStr("GOLD39",aczStatus);	 /*��Ч����*/	
			TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:aczStatus[%s]",__FILE__,__LINE__,aczStatus );	
			return FAIL;
			
		}
			
		/*��ȡ7702������Ϣ*/

		PGetStr("KEHHAO",aczKehhao,sizeof(aczKehhao));  /* �ͻ���   */
		PGetStr("KEHUXM",aczKehuxm,sizeof(aczKehuxm));  /* �ͻ����� */

		PGetStr("GUOJII",aczguojii,sizeof(aczguojii));  /* ����     */
		PGetStr("ZHJNZL",aczZhjnzl,sizeof(aczZhjnzl));  /* ֤������ */
		PGetStr("ZHJHAO",aczzjzjho,sizeof(aczzjzjho));  /* ֤������ */
		PGetStr("DIZHII",aczDizhii,sizeof(aczDizhii));  /* ��ַ     */
		PGetStr("LXDIAH",aczLxdian,sizeof(aczLxdian));  /* ��ϵ�绰 */
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
					TRC_Trace(1, 3, aczLogFile, "YzProc��ѯ�ͻ���Ϣ��[%d]",__FILE__,__LINE__,iRetCode );	
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
				PPutStr("GOLD39",aczStatus);	 /*��Ч����*/	
				TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:aczStatus[%s]",__FILE__,__LINE__,aczStatus );	
				return FAIL;
				
			}
			
			/*��ȡ0106������Ϣ*/

			/* ��POOL����ȡ������� */
                      iLen=PGetMem("F01061",aczPkt,sizeof(aczPkt));

                      /* ���ñ�������� */
                     iRetCode=APP_PUB_UnpackForm('0',aczPkt,iLen);
                      if ( iRetCode<0 )
                      {
				PPutStr("GOLD39","96");	 /*��Ч����*/	
				return FAIL;
                      }

                      /* ȡ���������� */
                      PGetMem("F01061_Rows",&iRows,sizeof(int));

                      /* ʹ�ñ������ */
                      for (i=0;i<iRows;i++)
                      {

				memset(aczKehhao,0,sizeof(aczKehhao));
				sprintf(aczSuff,"_%d",i);
				POOL_SetGetSuff(aczSuff);       /* ����POOL����������׺ */
				PGetStr("QIYEDM",aczzjzjho,sizeof(aczzjzjho));/*��֯��������*/
				//TPL_Trace(4,__FILE__,__LINE__,"QIYEDM=[%s]",aczzjzjho);

				POOL_SetGetSuff("");    /* ���POOL����������׺���ǳ���Ҫ�������˳�ʱ�벻Ҫ���� */

                               
                        }
			

		}
		    
	    	

		
			
		if (0!=strcmp(aczzjzjho,aczZhjhao))
		{
				TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:֤���Ų���",__FILE__,__LINE__ );
				PPutStr("GOLD39","12");	 /*��Ч����*/	
				return FAIL;
			  	
		}	
		PPutStr("GOLD39","00");	
		strcpy(stTccontract.aczDanwdm,DSF_DANWDM); /*��λ����*/
		strcpy(stTccontract.aczHuobdh,"00");/*����*/
		strcpy(stTccontract.aczDsdfdm,"441"); /*���*/
		strcpy(stTccontract.aczXinzhh,aczZhangh);/*�˺�*/
		strcpy(stTccontract.aczCjiobh,aczJilubh);/*�������ˮ��*/
		PGetStr("TPU_SysDate",stTccontract.aczSqngrq,sizeof(stTccontract.aczSqngrq));/*��������*/
		strcpy(stTccontract.aczJiluzt,"0"); /*��¼״̬*/
		iRetCode = tccontract_Insert((char*)&stTccontract,1);
		if (iRetCode <0)
		{
			PPutStr("GOLD39","96");	
			return FAIL;
		}
	
		
    
     
     
		TRC_Trace(1, 3, aczLogFile, "YzProc[%s][%d]:--------------�ʺż�����------------------",__FILE__,__LINE__ );

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
 *  �� �� ��:RunLog
 *  ��������: ȡ��־�ļ�
 *  �� �� ��:chenwl
 *  ����:
 *
 *  �� �� ֵ: SUCCESS �ɹ�
 *    FAIL    ʧ��
 *  �����Զ��庯��:
 *  �����Ҫ:
 *  ȫ�ֱ���:
 *  �޸ĵ�ȫ�ֱ���:
 *  ���ʱ��: 2006/02/20
 *  ����޸�ʱ��:   2006/02/20
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
