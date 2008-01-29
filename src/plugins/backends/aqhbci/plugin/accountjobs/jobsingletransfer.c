/***************************************************************************
 $RCSfile$
                             -------------------
    cvs         : $Id$
    begin       : Mon Mar 01 2004
    copyright   : (C) 2004 by Martin Preuss
    email       : martin@libchipcard.de

 ***************************************************************************
 *          Please see toplevel file COPYING for license details           *
 ***************************************************************************/


#ifdef HAVE_CONFIG_H
# include <config.h>
#endif


#include "jobsingletransfer_p.h"
#include "job_l.h"
#include "aqhbci_l.h"
#include "accountjob_l.h"
#include <gwenhywfar/debug.h>
#include <gwenhywfar/misc.h>
#include <gwenhywfar/inherit.h>
#include <gwenhywfar/dbio.h>
#include <gwenhywfar/text.h>

#include <aqbanking/jobsingletransfer.h>
#include <aqbanking/jobsingletransfer_be.h>
#include <aqbanking/jobsingledebitnote_be.h>
#include <aqbanking/jobinternaltransfer_be.h>
#include <aqbanking/jobcreatesto_be.h>
#include <aqbanking/jobmodifysto_be.h>
#include <aqbanking/jobdeletesto_be.h>
#include <aqbanking/jobcreatedatedtransfer_be.h>
#include <aqbanking/jobmodifydatedtransfer_be.h>
#include <aqbanking/jobdeletedatedtransfer_be.h>
#include <aqbanking/job_be.h>

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>


GWEN_INHERIT(AH_JOB, AH_JOB_SINGLETRANSFER);



/* --------------------------------------------------------------- FUNCTION */
AH_JOB *AH_Job_SingleTransfer_new(AB_USER *u,
				  AB_ACCOUNT *account) {
  AH_JOB *j;

  j=AH_Job_SingleTransferBase_new(u, account, AB_Job_TypeTransfer);
  if (j)
    AH_Job_SetChallengeClass(j, 10);
  return j;
}



/* --------------------------------------------------------------- FUNCTION */
AH_JOB *AH_Job_SingleDebitNote_new(AB_USER *u,
                                   AB_ACCOUNT *account) {
  AH_JOB *j;

  j=AH_Job_SingleTransferBase_new(u, account, AB_Job_TypeDebitNote);
  if (j)
    AH_Job_SetChallengeClass(j, 10);
  return j;
}



/* --------------------------------------------------------------- FUNCTION */
AH_JOB *AH_Job_CreateStandingOrder_new(AB_USER *u,
                                       AB_ACCOUNT *account) {
  AH_JOB *j;

  j=AH_Job_SingleTransferBase_new(u, account,
				  AB_Job_TypeCreateStandingOrder);
  if (j)
    AH_Job_SetChallengeClass(j, 10);
  return j;
}



/* --------------------------------------------------------------- FUNCTION */
AH_JOB *AH_Job_ModifyStandingOrder_new(AB_USER *u,
                                       AB_ACCOUNT *account) {
  AH_JOB *j;

  j=AH_Job_SingleTransferBase_new(u, account,
				  AB_Job_TypeModifyStandingOrder);
  if (j)
    AH_Job_SetChallengeClass(j, 10);
  return j;
}



/* --------------------------------------------------------------- FUNCTION */
AH_JOB *AH_Job_DeleteStandingOrder_new(AB_USER *u,
                                       AB_ACCOUNT *account) {
  AH_JOB *j;

  j=AH_Job_SingleTransferBase_new(u, account,
				  AB_Job_TypeDeleteStandingOrder);
  if (j)
    AH_Job_SetChallengeClass(j, 10);
  return j;
}



/* --------------------------------------------------------------- FUNCTION */
AH_JOB *AH_Job_CreateDatedTransfer_new(AB_USER *u,
                                       AB_ACCOUNT *account) {
  AH_JOB *j;

  j=AH_Job_SingleTransferBase_new(u, account,
				  AB_Job_TypeCreateDatedTransfer);
  if (j)
    AH_Job_SetChallengeClass(j, 10);
  return j;
}



/* --------------------------------------------------------------- FUNCTION */
AH_JOB *AH_Job_ModifyDatedTransfer_new(AB_USER *u,
                                       AB_ACCOUNT *account) {
  AH_JOB *j;

  j=AH_Job_SingleTransferBase_new(u, account,
				  AB_Job_TypeModifyDatedTransfer);
  if (j)
    AH_Job_SetChallengeClass(j, 10);
  return j;
}



/* --------------------------------------------------------------- FUNCTION */
AH_JOB *AH_Job_DeleteDatedTransfer_new(AB_USER *u,
                                       AB_ACCOUNT *account) {
  AH_JOB *j;

  j=AH_Job_SingleTransferBase_new(u, account,
				  AB_Job_TypeDeleteDatedTransfer);
  if (j)
    AH_Job_SetChallengeClass(j, 10);
  return j;
}



/* --------------------------------------------------------------- FUNCTION */
AH_JOB *AH_Job_InternalTransfer_new(AB_USER *u,
                                    AB_ACCOUNT *account) {
  AH_JOB *j;

  j=AH_Job_SingleTransferBase_new(u, account,
				  AB_Job_TypeInternalTransfer);
  if (j)
    AH_Job_SetChallengeClass(j, 10);
  return j;
}



/* --------------------------------------------------------------- FUNCTION */
AH_JOB *AH_Job_SingleTransferBase_new(AB_USER *u,
                                      AB_ACCOUNT *account,
                                      AB_JOB_TYPE jobType) {
  AH_JOB *j;
  AH_JOB_SINGLETRANSFER *aj;
  GWEN_DB_NODE *dbArgs;

  switch(jobType) {
  case AB_Job_TypeTransfer:
    j=AH_AccountJob_new("JobSingleTransfer", u, account);
    break;
  case AB_Job_TypeDebitNote:
    j=AH_AccountJob_new("JobSingleDebitNote", u, account);
    break;
  case AB_Job_TypeCreateStandingOrder:
    j=AH_AccountJob_new("JobCreateStandingOrder", u, account);
    break;
  case AB_Job_TypeModifyStandingOrder:
    j=AH_AccountJob_new("JobModifyStandingOrder", u, account);
    break;
  case AB_Job_TypeDeleteStandingOrder:
    j=AH_AccountJob_new("JobDeleteStandingOrder", u, account);
    break;
  case AB_Job_TypeCreateDatedTransfer:
    j=AH_AccountJob_new("JobCreateDatedTransfer", u, account);
    break;
  case AB_Job_TypeModifyDatedTransfer:
    j=AH_AccountJob_new("JobModifyDatedTransfer", u, account);
    break;
  case AB_Job_TypeDeleteDatedTransfer:
    j=AH_AccountJob_new("JobDeleteDatedTransfer", u, account);
    break;
  case AB_Job_TypeInternalTransfer:
    j=AH_AccountJob_new("JobInternalTransfer", u, account);
    break;
  default:
    DBG_ERROR(AQHBCI_LOGDOMAIN, "Unknown job type %d", jobType);
    j=0;
  }

  if (!j)
    return 0;

  GWEN_NEW_OBJECT(AH_JOB_SINGLETRANSFER, aj);
  GWEN_INHERIT_SETDATA(AH_JOB, AH_JOB_SINGLETRANSFER, j, aj,
                       AH_Job_SingleTransfer_FreeData);
  aj->jobType=jobType;
  /* overwrite some virtual functions */
  AH_Job_SetProcessFn(j, AH_Job_SingleTransfer_Process);
  AH_Job_SetExchangeFn(j, AH_Job_SingleTransfer_Exchange);

  /* set some known arguments */
  dbArgs=AH_Job_GetArguments(j);
  assert(dbArgs);


  return j;
}



/* --------------------------------------------------------------- FUNCTION */
void GWENHYWFAR_CB AH_Job_SingleTransfer_FreeData(void *bp, void *p){
  AH_JOB_SINGLETRANSFER *aj;

  aj=(AH_JOB_SINGLETRANSFER*)p;
  free(aj->fiid);
  free(aj->oldFiid);

  GWEN_FREE_OBJECT(aj);
}



/* --------------------------------------------------------------- FUNCTION */
const char *AH_Job_SingleTransfer_GetFiid(AH_JOB *j) {
  AH_JOB_SINGLETRANSFER *aj;

  assert(j);
  aj=GWEN_INHERIT_GETDATA(AH_JOB, AH_JOB_SINGLETRANSFER, j);
  assert(aj);

  return aj->fiid;
}



/* --------------------------------------------------------------- FUNCTION */
const char *AH_Job_SingleTransfer_GetOldFiid(AH_JOB *j) {
  AH_JOB_SINGLETRANSFER *aj;

  assert(j);
  aj=GWEN_INHERIT_GETDATA(AH_JOB, AH_JOB_SINGLETRANSFER, j);
  assert(aj);

  return aj->oldFiid;
}



/* --------------------------------------------------------------- FUNCTION */
int AH_Job_SingleTransfer_Process(AH_JOB *j, AB_IMEXPORTER_CONTEXT *ctx,
				  uint32_t guiid){
  AH_JOB_SINGLETRANSFER *aj;
  GWEN_DB_NODE *dbResponses;
  GWEN_DB_NODE *dbCurr;

  assert(j);
  aj=GWEN_INHERIT_GETDATA(AH_JOB, AH_JOB_SINGLETRANSFER, j);
  assert(aj);
  DBG_INFO(AQHBCI_LOGDOMAIN, "Processing %s",
           AB_Job_Type2Char(aj->jobType));
  dbResponses=AH_Job_GetResponses(j);
  assert(dbResponses);

  switch(aj->jobType) {
  case AB_Job_TypeTransfer:
  case AB_Job_TypeDebitNote:
  case AB_Job_TypeDeleteStandingOrder:
  case AB_Job_TypeDeleteDatedTransfer:
  case AB_Job_TypeInternalTransfer:
    dbCurr=GWEN_DB_GetFirstGroup(dbResponses);
    while(dbCurr) {
      int rv;
  
      rv=AH_Job_CheckEncryption(j, dbCurr);
      if (rv) {
	DBG_INFO(AQHBCI_LOGDOMAIN, "Compromised security (encryption)");
	AH_Job_SetStatus(j, AH_JobStatusError);
	return rv;
      }
      rv=AH_Job_CheckSignature(j, dbCurr);
      if (rv) {
	DBG_INFO(AQHBCI_LOGDOMAIN, "Compromised security (signature)");
	AH_Job_SetStatus(j, AH_JobStatusError);
	return rv;
      }
      dbCurr=GWEN_DB_GetNextGroup(dbCurr);
    }
    break;

  case AB_Job_TypeCreateStandingOrder:
    /* search for "CreateStandingOrderResponse" */
    dbCurr=GWEN_DB_GetFirstGroup(dbResponses);
    while(dbCurr) {
      GWEN_DB_NODE *dbXA;
      int rv;
  
      rv=AH_Job_CheckEncryption(j, dbCurr);
      if (rv) {
	DBG_INFO(AQHBCI_LOGDOMAIN, "Compromised security (encryption)");
	AH_Job_SetStatus(j, AH_JobStatusError);
	return rv;
      }
      rv=AH_Job_CheckSignature(j, dbCurr);
      if (rv) {
	DBG_INFO(AQHBCI_LOGDOMAIN, "Compromised security (signature)");
	AH_Job_SetStatus(j, AH_JobStatusError);
	return rv;
      }
  
      dbXA=GWEN_DB_GetGroup(dbCurr, GWEN_PATH_FLAGS_NAMEMUSTEXIST,
			    "data/CreateStandingOrderResponse");
      if (dbXA) {
	const char *s;

	s=GWEN_DB_GetCharValue(dbXA, "referenceId", 0, 0);
	if (s) {
	  free(aj->fiid);
	  aj->fiid=strdup(s);
	}
      } /* if "standingOrderResponse" */
      dbCurr=GWEN_DB_GetNextGroup(dbCurr);
    }
    break;

  case AB_Job_TypeModifyStandingOrder:
    /* search for "ModifyStandingOrderResponse" */
    dbCurr=GWEN_DB_GetFirstGroup(dbResponses);
    while(dbCurr) {
      GWEN_DB_NODE *dbXA;
      int rv;
  
      rv=AH_Job_CheckEncryption(j, dbCurr);
      if (rv) {
	DBG_INFO(AQHBCI_LOGDOMAIN, "Compromised security (encryption)");
	AH_Job_SetStatus(j, AH_JobStatusError);
	return rv;
      }
      rv=AH_Job_CheckSignature(j, dbCurr);
      if (rv) {
	DBG_INFO(AQHBCI_LOGDOMAIN, "Compromised security (signature)");
	AH_Job_SetStatus(j, AH_JobStatusError);
	return rv;
      }
  
      dbXA=GWEN_DB_GetGroup(dbCurr, GWEN_PATH_FLAGS_NAMEMUSTEXIST,
			    "data/ModifyStandingOrderResponse");
      if (dbXA) {
	const char *s;

	s=GWEN_DB_GetCharValue(dbXA, "referenceIdOld", 0, 0);
	if (s) {
	  free(aj->oldFiid);
	  aj->oldFiid=strdup(s);
	}
	s=GWEN_DB_GetCharValue(dbXA, "referenceIdNew", 0, 0);
	if (s) {
	  free(aj->fiid);
	  aj->fiid=strdup(s);
	}
      } /* if "standingOrderResponse" */
      dbCurr=GWEN_DB_GetNextGroup(dbCurr);
    }
    break;

  case AB_Job_TypeCreateDatedTransfer:
    /* search for "CreateDatedTransferResponse" */
    dbCurr=GWEN_DB_GetFirstGroup(dbResponses);
    while(dbCurr) {
      GWEN_DB_NODE *dbXA;
      int rv;
  
      rv=AH_Job_CheckEncryption(j, dbCurr);
      if (rv) {
	DBG_INFO(AQHBCI_LOGDOMAIN, "Compromised security (encryption)");
	AH_Job_SetStatus(j, AH_JobStatusError);
	return rv;
      }
      rv=AH_Job_CheckSignature(j, dbCurr);
      if (rv) {
	DBG_INFO(AQHBCI_LOGDOMAIN, "Compromised security (signature)");
	AH_Job_SetStatus(j, AH_JobStatusError);
	return rv;
      }
  
      dbXA=GWEN_DB_GetGroup(dbCurr, GWEN_PATH_FLAGS_NAMEMUSTEXIST,
			    "data/CreateDatedTransferResponse");
      if (dbXA) {
	const char *s;

	s=GWEN_DB_GetCharValue(dbXA, "referenceId", 0, 0);
	if (s) {
	  free(aj->fiid);
	  aj->fiid=strdup(s);
	}
      } /* if "standingOrderResponse" */
      dbCurr=GWEN_DB_GetNextGroup(dbCurr);
    }
    break;

  case AB_Job_TypeModifyDatedTransfer:
    /* search for "ModifyDatedTransferResponse" */
    dbCurr=GWEN_DB_GetFirstGroup(dbResponses);
    while(dbCurr) {
      GWEN_DB_NODE *dbXA;
      int rv;
  
      rv=AH_Job_CheckEncryption(j, dbCurr);
      if (rv) {
	DBG_INFO(AQHBCI_LOGDOMAIN, "Compromised security (encryption)");
	AH_Job_SetStatus(j, AH_JobStatusError);
	return rv;
      }
      rv=AH_Job_CheckSignature(j, dbCurr);
      if (rv) {
	DBG_INFO(AQHBCI_LOGDOMAIN, "Compromised security (signature)");
	AH_Job_SetStatus(j, AH_JobStatusError);
	return rv;
      }
  
      dbXA=GWEN_DB_GetGroup(dbCurr, GWEN_PATH_FLAGS_NAMEMUSTEXIST,
			    "data/ModifyDatedTransferResponse");
      if (dbXA) {
	const char *s;

	s=GWEN_DB_GetCharValue(dbXA, "referenceIdOld", 0, 0);
	if (s) {
	  free(aj->oldFiid);
	  aj->oldFiid=strdup(s);
	}
	s=GWEN_DB_GetCharValue(dbXA, "referenceIdNew", 0, 0);
	if (s) {
	  free(aj->fiid);
	  aj->fiid=strdup(s);
	}
      } /* if "standingOrderResponse" */
      dbCurr=GWEN_DB_GetNextGroup(dbCurr);
    }
    break;

  default:
    DBG_ERROR(AQHBCI_LOGDOMAIN,
              "Unhandled job type %d", aj->jobType);
    return -1;
  }

  return 0;
}



/* --------------------------------------------------------------- FUNCTION */
int AH_Job_SingleTransfer__ValidateTransfer(AB_JOB *bj,
					    AH_JOB *mj,
					    AB_TRANSACTION *t) {
  const GWEN_STRINGLIST *sl;
  int maxn;
  int maxs;
  int n;
  const char *s;
  AH_JOB_SINGLETRANSFER *aj;
  const AB_TRANSACTION_LIMITS *lim;

  assert(mj);
  aj=GWEN_INHERIT_GETDATA(AH_JOB, AH_JOB_SINGLETRANSFER, mj);
  assert(aj);

  switch(aj->jobType) {
  case AB_Job_TypeTransfer:
    lim=AB_JobSingleTransfer_GetFieldLimits(bj);
    break;
  case AB_Job_TypeDebitNote:
    lim=AB_JobSingleDebitNote_GetFieldLimits(bj);
    break;
  case AB_Job_TypeCreateStandingOrder:
    lim=AB_JobCreateStandingOrder_GetFieldLimits(bj);
    break;
  case AB_Job_TypeModifyStandingOrder:
    lim=AB_JobModifyStandingOrder_GetFieldLimits(bj);
    break;
  case AB_Job_TypeDeleteStandingOrder:
    lim=AB_JobDeleteStandingOrder_GetFieldLimits(bj);
    break;
  case AB_Job_TypeCreateDatedTransfer:
    lim=AB_JobCreateDatedTransfer_GetFieldLimits(bj);
    break;
  case AB_Job_TypeModifyDatedTransfer:
    lim=AB_JobModifyDatedTransfer_GetFieldLimits(bj);
    break;
  case AB_Job_TypeDeleteDatedTransfer:
    lim=AB_JobDeleteDatedTransfer_GetFieldLimits(bj);
    break;
  case AB_Job_TypeInternalTransfer:
    lim=AB_JobInternalTransfer_GetFieldLimits(bj);
    break;
  default:
    DBG_ERROR(AQHBCI_LOGDOMAIN,
              "Unhandled job type %d", aj->jobType);
    return -1;
  }

  /* check purpose */
  if (lim) {
    maxn=AB_TransactionLimits_GetMaxLinesPurpose(lim);
    maxs=AB_TransactionLimits_GetMaxLenPurpose(lim);
  }
  else {
    maxn=0;
    maxs=0;
  }
  sl=AB_Transaction_GetPurpose(t);
  n=0;
  if (sl) {
    GWEN_STRINGLISTENTRY *se;
    GWEN_STRINGLIST *nsl;
    const char *p;

    nsl=GWEN_StringList_new();
    se=GWEN_StringList_FirstEntry(sl);
    while(se) {
      p=GWEN_StringListEntry_Data(se);
      if (p && *p) {
	char *np;
	int l;
	GWEN_BUFFER *tbuf;

	n++;
	if (maxn && n>maxn) {
	  DBG_ERROR(AQHBCI_LOGDOMAIN,
		    "Too many purpose lines (%d>%d)", n, maxn);
	  GWEN_StringList_free(nsl);
	  return GWEN_ERROR_INVALID;
	}
	tbuf=GWEN_Buffer_new(0, maxs, 0, 1);
	AB_ImExporter_Utf8ToDta(p, -1, tbuf);
	l=GWEN_Buffer_GetUsedBytes(tbuf);
	if (l>maxs) {
	  DBG_ERROR(AQHBCI_LOGDOMAIN,
		    "Too many chars in purpose line %d (%d>%d)", n, l, maxs);
	  GWEN_StringList_free(nsl);
	  return GWEN_ERROR_INVALID;
	}
	np=(char*)GWEN_Memory_malloc(l+1);
	memmove(np, GWEN_Buffer_GetStart(tbuf), l+1);
	GWEN_Buffer_free(tbuf);
	/* let string list take the newly alllocated string */
	GWEN_StringList_AppendString(nsl, np, 1, 0);
      }
      se=GWEN_StringListEntry_Next(se);
    } /* while */
    AB_Transaction_SetPurpose(t, nsl);
  }
  if (!n) {
    DBG_ERROR(AQHBCI_LOGDOMAIN, "No purpose lines");
    return GWEN_ERROR_INVALID;
  }

  /* check remote name */
  if (lim) {
    maxn=AB_TransactionLimits_GetMaxLinesRemoteName(lim);
    maxs=AB_TransactionLimits_GetMaxLenRemoteName(lim);
  }
  else {
    maxn=0;
    maxs=0;
  }
  sl=AB_Transaction_GetRemoteName(t);
  n=0;
  if (sl) {
    GWEN_STRINGLISTENTRY *se;
    GWEN_STRINGLIST *nsl;
    const char *p;

    nsl=GWEN_StringList_new();
    se=GWEN_StringList_FirstEntry(sl);
    while(se) {
      p=GWEN_StringListEntry_Data(se);
      if (p && *p) {
	char *np;
	int l;
        GWEN_BUFFER *tbuf;

	n++;
	if (maxn && n>maxn) {
	  DBG_ERROR(AQHBCI_LOGDOMAIN,
		    "Too many remote name lines (%d>%d)",
		    n, maxn);
          GWEN_StringList_free(nsl);
	  return GWEN_ERROR_INVALID;
	}
	tbuf=GWEN_Buffer_new(0, maxs, 0, 1);
        AB_ImExporter_Utf8ToDta(p, -1, tbuf);
	l=GWEN_Buffer_GetUsedBytes(tbuf);
	if (l>maxs) {
	  DBG_ERROR(AQHBCI_LOGDOMAIN,
		   "Too many chars in remote name line %d (%d>%d)",
		   n, l, maxs);
          GWEN_StringList_free(nsl);
	  return GWEN_ERROR_INVALID;
	}
	np=(char*)GWEN_Memory_malloc(l+1);
	memmove(np, GWEN_Buffer_GetStart(tbuf), l+1);
	GWEN_Buffer_free(tbuf);
	/* let string list take the newly alllocated string */
	GWEN_StringList_AppendString(nsl, np, 1, 0);
      }
      se=GWEN_StringListEntry_Next(se);
    } /* while */
    AB_Transaction_SetRemoteName(t, nsl);
  }
  if (!n) {
    DBG_ERROR(AQHBCI_LOGDOMAIN, "No remote name lines");
    return GWEN_ERROR_INVALID;
  }

  /* check local name */
  s=AB_Transaction_GetLocalName(t);
  if (!s) {
    AB_ACCOUNT *a;

    DBG_WARN(AQHBCI_LOGDOMAIN,
	     "No local name, filling in");
    a=AB_Job_GetAccount(bj);
    assert(a);
    s=AB_Account_GetOwnerName(a);
    if (!s) {
      DBG_ERROR(AQHBCI_LOGDOMAIN,
		"No owner name in account, giving up");
      return GWEN_ERROR_INVALID;
    }
    AB_Transaction_SetLocalName(t, s);
  }

  /* check local bank code */
  s=AB_Transaction_GetLocalBankCode(t);
  if (!s) {
    AB_ACCOUNT *a;

    DBG_WARN(AQHBCI_LOGDOMAIN,
	     "No local bank code, filling in");
    a=AH_AccountJob_GetAccount(mj);
    assert(a);
    s=AB_Account_GetBankCode(a);
    assert(s);
    AB_Transaction_SetLocalBankCode(t, s);
  }

  /* check local account number */
  s=AB_Transaction_GetLocalAccountNumber(t);
  if (!s) {
    AB_ACCOUNT *a;

    DBG_WARN(AQHBCI_LOGDOMAIN,
	     "No local account number, filling in");
    a=AH_AccountJob_GetAccount(mj);
    assert(a);
    s=AB_Account_GetAccountNumber(a);
    assert(s);
    AB_Transaction_SetLocalAccountNumber(t, s);
  }

  /* check local account suffix */
  s=AB_Transaction_GetLocalSuffix(t);
  if (!s) {
    AB_ACCOUNT *a;

    DBG_INFO(AQHBCI_LOGDOMAIN,
	     "No local suffix, filling in (if possible)");
    a=AH_AccountJob_GetAccount(mj);
    assert(a);
    s=AH_Account_GetSuffix(a);
    if (s)
      AB_Transaction_SetLocalSuffix(t, s);
  }

  /* check text key */
  if (lim) {
    if (GWEN_StringList_Count(AB_TransactionLimits_GetValuesTextKey(lim))){
      char numbuf[32];

      n=AB_Transaction_GetTextKey(t);
      if (n==0) {
        switch(aj->jobType) {
        case AB_Job_TypeDebitNote:
          n=5;  /* "Lastschrift" */
          break;
        case AB_Job_TypeTransfer:
        case AB_Job_TypeCreateStandingOrder:
        case AB_Job_TypeModifyStandingOrder:
        case AB_Job_TypeDeleteStandingOrder:
        case AB_Job_TypeInternalTransfer:
        default:
          n=51; /* "Ueberweisung" */
          break;
        }
        AB_Transaction_SetTextKey(t, n);
      }

      snprintf(numbuf, sizeof(numbuf), "%d", n);
      if (!AB_TransactionLimits_HasValuesTextKey(lim, numbuf)) {
	DBG_ERROR(AQHBCI_LOGDOMAIN, "Text key \"%s\" not supported by bank",
		  numbuf);
	return GWEN_ERROR_INVALID;
      }
    }
  }

  if (lim) {
    const GWEN_TIME *ti;

    switch(aj->jobType) {
    case AB_Job_TypeCreateStandingOrder:
    case AB_Job_TypeModifyStandingOrder:
    case AB_Job_TypeDeleteStandingOrder:
      /* additional checks for standing orders */

      /* check period */
      if (AB_Transaction_GetPeriod(t)==AB_Transaction_PeriodMonthly) {
        const GWEN_STRINGLIST *sl;

        /* check cycle */
        sl=AB_TransactionLimits_GetValuesCycleMonth(lim);
        if (GWEN_StringList_Count(sl)){
          char numbuf[32];

          n=AB_Transaction_GetCycle(t);
          if (n==0) {
            DBG_ERROR(AQHBCI_LOGDOMAIN,
                      "No cycle given");
            return GWEN_ERROR_INVALID;
          }

          snprintf(numbuf, sizeof(numbuf), "%d", n);
          if (!AB_TransactionLimits_HasValuesCycleMonth(lim, numbuf) &&
              !AB_TransactionLimits_HasValuesCycleMonth(lim, "0")) {
            DBG_ERROR(AQHBCI_LOGDOMAIN,
                      "Month day \"%s\" not supported by bank",
                      numbuf);
            return GWEN_ERROR_INVALID;
          }
        }

        /* check execution day */
        sl=AB_TransactionLimits_GetValuesExecutionDayMonth(lim);
        if (GWEN_StringList_Count(sl)){
          char numbuf[32];

          n=AB_Transaction_GetExecutionDay(t);
          if (n==0) {
            DBG_ERROR(AQHBCI_LOGDOMAIN,
                      "No execution day given");
            return GWEN_ERROR_INVALID;
          }

          snprintf(numbuf, sizeof(numbuf), "%d", n);
          if (!AB_TransactionLimits_HasValuesExecutionDayMonth(lim, numbuf) &&
              !AB_TransactionLimits_HasValuesExecutionDayMonth(lim, "0")) {
            DBG_ERROR(AQHBCI_LOGDOMAIN,
                      "Execution month day \"%s\" not supported by bank",
                      numbuf);
            return GWEN_ERROR_INVALID;
          }
        } /* if there are limits */
      }
      else if (AB_Transaction_GetPeriod(t)==AB_Transaction_PeriodWeekly) {
        const GWEN_STRINGLIST *sl;

        /* check cycle */
        sl=AB_TransactionLimits_GetValuesCycleWeek(lim);
        if (GWEN_StringList_Count(sl)) {
          char numbuf[32];

          n=AB_Transaction_GetCycle(t);
          if (n==0) {
            DBG_ERROR(AQHBCI_LOGDOMAIN,
                      "No cycle given");
            return GWEN_ERROR_INVALID;
          }

          snprintf(numbuf, sizeof(numbuf), "%d", n);
          if (!AB_TransactionLimits_HasValuesCycleWeek(lim, numbuf) &&
              !AB_TransactionLimits_HasValuesCycleWeek(lim, "0")) {
            DBG_ERROR(AQHBCI_LOGDOMAIN,
                      "Week day \"%s\" not supported by bank",
                      numbuf);
            return GWEN_ERROR_INVALID;
          }
        } /* if there are limits */

        /* check execution day */
        sl=AB_TransactionLimits_GetValuesExecutionDayWeek(lim);
        if (GWEN_StringList_Count(sl)){
          char numbuf[32];

          n=AB_Transaction_GetExecutionDay(t);
          if (n==0) {
            DBG_ERROR(AQHBCI_LOGDOMAIN,
                      "No execution day given");
            return GWEN_ERROR_INVALID;
          }

          snprintf(numbuf, sizeof(numbuf), "%d", n);
          if (!AB_TransactionLimits_HasValuesExecutionDayWeek(lim, numbuf) &&
              !AB_TransactionLimits_HasValuesExecutionDayWeek(lim, "0")) {
            DBG_ERROR(AQHBCI_LOGDOMAIN,
                      "Execution month day \"%s\" not supported by bank",
                      numbuf);
            return GWEN_ERROR_INVALID;
          }
        } /* if there are limits */
      }
      else {
        DBG_ERROR(AQHBCI_LOGDOMAIN,
                  "Unsupported period %d", AB_Transaction_GetPeriod(t));
        return GWEN_ERROR_INVALID;
      }

      /* check setup times */
      ti=AB_Transaction_GetFirstExecutionDate(t);
      if (ti && aj->jobType==AB_Job_TypeCreateStandingOrder) {
	GWEN_TIME *currDate;
        int dt;

        currDate=GWEN_CurrentTime();
        assert(currDate);
        dt=((int)GWEN_Time_DiffSeconds(ti, currDate))/(60*60*24);
        GWEN_Time_free(currDate);


        /* check minimum setup time */
        n=AB_TransactionLimits_GetMinValueSetupTime(lim);
        if (n && dt<n) {
          DBG_ERROR(AQHBCI_LOGDOMAIN,
                    "Minimum setup time violated");
          return GWEN_ERROR_INVALID;
        }

        /* check maximum setup time */
        n=AB_TransactionLimits_GetMaxValueSetupTime(lim);
        if (n && dt>n) {
          DBG_ERROR(AQHBCI_LOGDOMAIN,
                    "Maximum setup time violated");
          return GWEN_ERROR_INVALID;
        }
      }
      break;

    case AB_Job_TypeCreateDatedTransfer:
    case AB_Job_TypeModifyDatedTransfer:
      /* check setup times */
      ti=AB_Transaction_GetDate(t);
      if (ti) {
        GWEN_TIME *currDate;
        int dt;

        currDate=GWEN_CurrentTime();
        assert(currDate);
        dt=((int)GWEN_Time_DiffSeconds(ti, currDate))/(60*60*24);
        GWEN_Time_free(currDate);

        /* check minimum setup time */
        n=AB_TransactionLimits_GetMinValueSetupTime(lim);
        if (n && dt<n) {
          DBG_ERROR(AQHBCI_LOGDOMAIN,
                    "Minimum setup time violated");
          return GWEN_ERROR_INVALID;
        }

        /* check maximum setup time */
        n=AB_TransactionLimits_GetMaxValueSetupTime(lim);
        if (n && dt>n) {
          DBG_ERROR(AQHBCI_LOGDOMAIN,
                    "Maximum setup time violated");
          return GWEN_ERROR_INVALID;
        }
      }
      break;

    case AB_Job_TypeDeleteDatedTransfer:
      break;

      /* --------------- add more jobs here ---------------------- */

    default:
      break;
    } /* switch */
  }
  return 0;
}



/* --------------------------------------------------------------- FUNCTION */
int AH_Job_SingleTransfer_Exchange(AH_JOB *j, AB_JOB *bj,
				   AH_JOB_EXCHANGE_MODE m,
				   uint32_t guiid){
  AH_JOB_SINGLETRANSFER *aj;

  DBG_INFO(AQHBCI_LOGDOMAIN, "Exchanging (%d)", m);

  assert(j);
  aj=GWEN_INHERIT_GETDATA(AH_JOB, AH_JOB_SINGLETRANSFER, j);
  assert(aj);

  if (aj->jobType!=AB_Job_GetType(bj)) {
    DBG_ERROR(AQHBCI_LOGDOMAIN,
              "Different job types");
    return GWEN_ERROR_INVALID;
  }

  switch(m) {
  case AH_Job_ExchangeModeParams: {
    GWEN_DB_NODE *dbParams;
    GWEN_DB_NODE *dbTk;
    AB_TRANSACTION_LIMITS *lim;
    const char *s;
    int i;

    dbParams=AH_Job_GetParams(j);
    DBG_DEBUG(AQHBCI_LOGDOMAIN, "Have this parameters to exchange:");
    if (GWEN_Logger_GetLevel(AQHBCI_LOGDOMAIN)>=GWEN_LoggerLevel_Debug)
      GWEN_DB_Dump(dbParams, stderr, 2);

    /* read limits */
    lim=AB_TransactionLimits_new();
    AB_TransactionLimits_SetMaxLenPurpose(lim, 27);
    AB_TransactionLimits_SetMaxLenRemoteName(lim, 27);
    AB_TransactionLimits_SetMaxLinesRemoteName(lim, 2);

    i=GWEN_DB_GetIntValue(dbParams, "maxpurposeLines", 0, 0);
    AB_TransactionLimits_SetMaxLinesPurpose(lim, i);

    /* read text keys */
    dbTk=GWEN_DB_GetGroup(dbParams, GWEN_PATH_FLAGS_NAMEMUSTEXIST, "textkey");
    if (dbTk) {
      for (i=0; ; i++) {
	int k;
	char numbuf[16];

	k=GWEN_DB_GetIntValue(dbTk, "key", i, -1);
	if (k==-1)
	  break;
	snprintf(numbuf, sizeof(numbuf), "%d", k);
	AB_TransactionLimits_AddValuesTextKey(lim, numbuf, 0);
      }
      GWEN_StringList_Sort(AB_TransactionLimits_GetValuesTextKey(lim),
                           1, GWEN_StringList_SortModeInt);
    }

    /* some special limits for standing order jobs */
    switch(aj->jobType) {
    case AB_Job_TypeCreateStandingOrder:
    case AB_Job_TypeModifyStandingOrder:
    case AB_Job_TypeDeleteStandingOrder:
      s=GWEN_DB_GetCharValue(dbParams, "AllowedTurnusMonths", 0, 0);
      if (s && *s) {
        AB_TransactionLimits_SetAllowMonthly(lim, 1);
	while(*s) {
	  char buf[3];
          const char *x;

          buf[2]=0;
          strncpy(buf, s, 2);
          x=buf;
          if (*x=='0')
            x++;

	  AB_TransactionLimits_AddValuesCycleMonth(lim, x, 0);
	  s+=2;
        } /* while */
        GWEN_StringList_Sort(AB_TransactionLimits_GetValuesCycleMonth(lim),
                             1, GWEN_StringList_SortModeInt);
      }
      else
	AB_TransactionLimits_SetAllowMonthly(lim, -1);

      s=GWEN_DB_GetCharValue(dbParams, "AllowedMonthDays", 0, 0);
      if (s && *s) {
	while(*s) {
	  char buf[3];
          const char *x;

          buf[2]=0;
          strncpy(buf, s, 2);
          x=buf;
          if (*x=='0')
            x++;
	  AB_TransactionLimits_AddValuesExecutionDayMonth(lim, x, 0);
	  s+=2;
	} /* while */
        GWEN_StringList_Sort(AB_TransactionLimits_GetValuesExecutionDayMonth(lim),
                             1, GWEN_StringList_SortModeInt);
      }

      s=GWEN_DB_GetCharValue(dbParams, "AllowedTurnusWeeks", 0, 0);
      if (s && *s) {
	AB_TransactionLimits_SetAllowWeekly(lim, 1);
	while(*s) {
          char buf[3];
          const char *x;

          buf[2]=0;
          strncpy(buf, s, 2);
          x=buf;
          if (*x=='0')
            x++;
          AB_TransactionLimits_AddValuesCycleWeek(lim, x, 0);
	  s+=2;
	} /* while */
        GWEN_StringList_Sort(AB_TransactionLimits_GetValuesCycleWeek(lim),
                             1, GWEN_StringList_SortModeInt);
      }
      else
	AB_TransactionLimits_SetAllowWeekly(lim, -1);

      s=GWEN_DB_GetCharValue(dbParams, "AllowedWeekDays", 0, 0);
      if (s && *s) {
	while(*s) {
	  char buf[3];
          const char *x;

          buf[2]=0;
          strncpy(buf, s, 2);
          x=buf;
          if (*x=='0')
            x++;
          AB_TransactionLimits_AddValuesExecutionDayWeek(lim, x, 0);
	  s+=2;
	} /* while */
        GWEN_StringList_Sort(AB_TransactionLimits_GetValuesExecutionDayWeek(lim),
                             1, GWEN_StringList_SortModeInt);
      }

      i=GWEN_DB_GetIntValue(dbParams, "minDelay", 0, 0);
      AB_TransactionLimits_SetMinValueSetupTime(lim, i);

      i=GWEN_DB_GetIntValue(dbParams, "maxDelay", 0, 0);
      AB_TransactionLimits_SetMaxValueSetupTime(lim, i);

      s=GWEN_DB_GetCharValue(dbParams, "AllowChgOtherAccount", 0, "");
      if (*s=='J') i=1;
      else if (*s=='N') i=-1;
      else i=0;
      AB_TransactionLimits_SetAllowChangeRecipientAccount(lim, i);

      s=GWEN_DB_GetCharValue(dbParams, "AllowChgOtherName", 0, "");
      if (*s=='J') i=1;
      else if (*s=='N') i=-1;
      else i=0;
      AB_TransactionLimits_SetAllowChangeRecipientName(lim, i);

      s=GWEN_DB_GetCharValue(dbParams, "AllowChgValue", 0, "");
      if (*s=='J') i=1;
      else if (*s=='N') i=-1;
      else i=0;
      AB_TransactionLimits_SetAllowChangeValue(lim, i);

      s=GWEN_DB_GetCharValue(dbParams, "AllowChgTextKey", 0, "");
      if (*s=='J') i=1;
      else if (*s=='N') i=-1;
      else i=0;
      AB_TransactionLimits_SetAllowChangeTextKey(lim, i);

      s=GWEN_DB_GetCharValue(dbParams, "AllowChgPurpose", 0, "");
      if (*s=='J') i=1;
      else if (*s=='N') i=-1;
      else i=0;
      AB_TransactionLimits_SetAllowChangePurpose(lim, i);

      s=GWEN_DB_GetCharValue(dbParams, "AllowChgFirstDate", 0, "");
      if (*s=='J') i=1;
      else if (*s=='N') i=-1;
      else i=0;
      AB_TransactionLimits_SetAllowChangeFirstExecutionDate(lim, i);

      s=GWEN_DB_GetCharValue(dbParams, "AllowChgUnit", 0, "");
      if (*s=='J') i=1;
      else if (*s=='N') i=-1;
      else i=0;
      AB_TransactionLimits_SetAllowChangePeriod(lim, i);

      s=GWEN_DB_GetCharValue(dbParams, "AllowChgTurnus", 0, "");
      if (*s=='J') i=1;
      else if (*s=='N') i=-1;
      else i=0;
      AB_TransactionLimits_SetAllowChangeCycle(lim, i);

      s=GWEN_DB_GetCharValue(dbParams, "AllowChgDay", 0, "");
      if (*s=='J') i=1;
      else if (*s=='N') i=-1;
      else i=0;
      AB_TransactionLimits_SetAllowChangeExecutionDay(lim, i);

      s=GWEN_DB_GetCharValue(dbParams, "AllowChgLastDate", 0, "");
      if (*s=='J') i=1;
      else if (*s=='N') i=-1;
      else i=0;
      AB_TransactionLimits_SetAllowChangeLastExecutionDate(lim, i);
      break;

    case AB_Job_TypeCreateDatedTransfer:
    case AB_Job_TypeModifyDatedTransfer:
      i=GWEN_DB_GetIntValue(dbParams, "minDelay", 0, 0);
      AB_TransactionLimits_SetMinValueSetupTime(lim, i);

      i=GWEN_DB_GetIntValue(dbParams, "maxDelay", 0, 0);
      AB_TransactionLimits_SetMaxValueSetupTime(lim, i);
      break;

    default:
      break;
    }

    /* store field limits */
    switch(aj->jobType) {
    case AB_Job_TypeTransfer:
      AB_JobSingleTransfer_SetFieldLimits(bj, lim);
      break;
    case AB_Job_TypeDebitNote:
      AB_JobSingleDebitNote_SetFieldLimits(bj, lim);
      break;
    case AB_Job_TypeCreateStandingOrder:
      AB_JobCreateStandingOrder_SetFieldLimits(bj, lim);
      break;
    case AB_Job_TypeModifyStandingOrder:
      AB_JobModifyStandingOrder_SetFieldLimits(bj, lim);
      break;
    case AB_Job_TypeDeleteStandingOrder:
      AB_JobDeleteStandingOrder_SetFieldLimits(bj, lim);
      break;
    case AB_Job_TypeCreateDatedTransfer:
      AB_JobCreateDatedTransfer_SetFieldLimits(bj, lim);
      break;
    case AB_Job_TypeModifyDatedTransfer:
      AB_JobModifyDatedTransfer_SetFieldLimits(bj, lim);
      break;
    case AB_Job_TypeDeleteDatedTransfer:
      AB_JobDeleteDatedTransfer_SetFieldLimits(bj, lim);
      break;
    case AB_Job_TypeInternalTransfer:
      AB_JobInternalTransfer_SetFieldLimits(bj, lim);
      break;
    default:
      DBG_ERROR(AQHBCI_LOGDOMAIN,
                "Unhandled job type %d", aj->jobType);
      return -1;
    }

    return 0;
  }

  case AH_Job_ExchangeModeArgs: {
    GWEN_DB_NODE *dbArgs;
    const AB_TRANSACTION *ot;
    const AB_VALUE *v;

    dbArgs=AH_Job_GetArguments(j);
    assert(dbArgs);
    switch(aj->jobType) {
    case AB_Job_TypeTransfer:
      ot=AB_JobSingleTransfer_GetTransaction(bj);
      break;
    case AB_Job_TypeDebitNote:
      ot=AB_JobSingleDebitNote_GetTransaction(bj);
      break;
    case AB_Job_TypeCreateStandingOrder:
      ot=AB_JobCreateStandingOrder_GetTransaction(bj);
      break;
    case AB_Job_TypeModifyStandingOrder:
      ot=AB_JobModifyStandingOrder_GetTransaction(bj);
      break;
    case AB_Job_TypeDeleteStandingOrder:
      ot=AB_JobDeleteStandingOrder_GetTransaction(bj);
      break;
    case AB_Job_TypeCreateDatedTransfer:
      ot=AB_JobCreateDatedTransfer_GetTransaction(bj);
      break;
    case AB_Job_TypeModifyDatedTransfer:
      ot=AB_JobModifyDatedTransfer_GetTransaction(bj);
      break;
    case AB_Job_TypeDeleteDatedTransfer:
      ot=AB_JobDeleteDatedTransfer_GetTransaction(bj);
      break;
    case AB_Job_TypeInternalTransfer:
      ot=AB_JobInternalTransfer_GetTransaction(bj);
      break;
    default:
      DBG_ERROR(AQHBCI_LOGDOMAIN,
                "Unhandled job type %d", aj->jobType);
      return GWEN_ERROR_INVALID;
    }

    if (ot) {
      GWEN_DB_NODE *dbT;
      const char *p;
      const GWEN_STRINGLIST *sl;
      AB_TRANSACTION *t;
      const GWEN_TIME *ti;

      t=AB_Transaction_dup(ot);
      assert(t);
      if (AH_Job_SingleTransfer__ValidateTransfer(bj, j, t)) {
	DBG_ERROR(AQHBCI_LOGDOMAIN,
		  "Invalid transaction");
	AB_Job_SetStatus(bj, AB_Job_StatusError);
	return GWEN_ERROR_INVALID;
      }
      /* store the validated transaction back into application job,
       * to allow the application to recognize answers to this job later */
      switch(aj->jobType) {
      case AB_Job_TypeTransfer:
        AB_JobSingleTransfer_SetTransaction(bj, t);
        break;
      case AB_Job_TypeDebitNote:
        AB_JobSingleDebitNote_SetTransaction(bj, t);
        break;
      case AB_Job_TypeCreateStandingOrder:
        AB_JobCreateStandingOrder_SetTransaction(bj, t);
        break;
      case AB_Job_TypeModifyStandingOrder:
        AB_JobModifyStandingOrder_SetTransaction(bj, t);
        break;
      case AB_Job_TypeDeleteStandingOrder:
        AB_JobDeleteStandingOrder_SetTransaction(bj, t);
        break;
      case AB_Job_TypeCreateDatedTransfer:
        AB_JobCreateDatedTransfer_SetTransaction(bj, t);
        break;
      case AB_Job_TypeModifyDatedTransfer:
        AB_JobModifyDatedTransfer_SetTransaction(bj, t);
        break;
      case AB_Job_TypeDeleteDatedTransfer:
        AB_JobDeleteDatedTransfer_SetTransaction(bj, t);
        break;
      case AB_Job_TypeInternalTransfer:
        AB_JobInternalTransfer_SetTransaction(bj, t);
        break;
      default:
        DBG_ERROR(AQHBCI_LOGDOMAIN,
                  "Unhandled job type %d", aj->jobType);
        return GWEN_ERROR_INVALID;
      }

      dbT=GWEN_DB_GetGroup(dbArgs, GWEN_DB_FLAGS_OVERWRITE_GROUPS,
                           "transaction");
      assert(dbT);

      /* store transaction */
      GWEN_DB_SetIntValue(dbT, GWEN_DB_FLAGS_OVERWRITE_VARS,
			  "ourAccount/country", 280);
      GWEN_DB_SetCharValue(dbT, GWEN_DB_FLAGS_OVERWRITE_VARS,
			   "ourAccount/bankCode",
			   AB_Transaction_GetLocalBankCode(t));
      GWEN_DB_SetCharValue(dbT, GWEN_DB_FLAGS_OVERWRITE_VARS,
                           "ourAccount/accountId",
                           AB_Transaction_GetLocalAccountNumber(t));

      p=AB_Transaction_GetLocalSuffix(t);
      if (p)
	GWEN_DB_SetCharValue(dbT, GWEN_DB_FLAGS_OVERWRITE_VARS,
			     "ourAccount/accountsubid", p);
      GWEN_DB_SetCharValue(dbT, GWEN_DB_FLAGS_OVERWRITE_VARS,
			   "name",
			   AB_Transaction_GetLocalName(t));

      GWEN_DB_SetIntValue(dbT, GWEN_DB_FLAGS_OVERWRITE_VARS,
			  "otherAccount/country",
                          280);
      GWEN_DB_SetCharValue(dbT, GWEN_DB_FLAGS_OVERWRITE_VARS,
			   "otherAccount/bankCode",
			   AB_Transaction_GetRemoteBankCode(t));
      GWEN_DB_SetCharValue(dbT, GWEN_DB_FLAGS_OVERWRITE_VARS,
                           "otherAccount/accountId",
                           AB_Transaction_GetRemoteAccountNumber(t));

      sl=AB_Transaction_GetRemoteName(t);
      if (sl) {
	GWEN_STRINGLISTENTRY *se;

	se=GWEN_StringList_FirstEntry(sl);
	GWEN_DB_DeleteVar(dbT, "otherName");
	while(se) {
	  p=GWEN_StringListEntry_Data(se);
	  if (p)
	    GWEN_DB_SetCharValue(dbT, GWEN_DB_FLAGS_DEFAULT,
				 "otherName", p);
	  se=GWEN_StringListEntry_Next(se);
	} /* while */
      }

      v=AB_Transaction_GetValue(t);
      if (v) {
	GWEN_DB_NODE *dbV;
        GWEN_BUFFER *nbuf;
        char *p;
        const char *s;
        int l;

	dbV=GWEN_DB_GetGroup(dbT, GWEN_DB_FLAGS_OVERWRITE_GROUPS, "value");
        assert(dbV);

	nbuf=GWEN_Buffer_new(0, 32, 0, 1);
	if (GWEN_Text_DoubleToBuffer(AB_Value_GetValueAsDouble(v),
				     nbuf)) {
	  DBG_ERROR(AQHBCI_LOGDOMAIN, "Buffer overflow");
          GWEN_Buffer_free(nbuf);
	  abort();
	}

	l=GWEN_Buffer_GetUsedBytes(nbuf);
	if (!l) {
	  DBG_ERROR(AQHBCI_LOGDOMAIN, "Error in conversion");
	  GWEN_Buffer_free(nbuf);
	  abort();
        }

        /* replace "C" comma with "DE" comma, remove thousand's comma */
        p=GWEN_Buffer_GetStart(nbuf);
        s=p;
        while(*s) {
          if (*s=='.') {
            *p=',';
            p++;
          }
          else if (*s!=',') {
            *p=*s;
            p++;
          }
          s++;
        } /* while */
        *p=0;

	if (strchr(GWEN_Buffer_GetStart(nbuf), ',')) {
	  /* kill all trailing '0' behind the comma */
	  p=GWEN_Buffer_GetStart(nbuf)+l;
	  while(l--) {
	    --p;
            if (*p=='0')
              *p=0;
            else
              break;
          }
	}
	else
	  GWEN_Buffer_AppendString(nbuf, ",");

	/* store value */
	GWEN_DB_SetCharValue(dbV, GWEN_DB_FLAGS_OVERWRITE_VARS,
                             "value",
			     GWEN_Buffer_GetStart(nbuf));
	GWEN_Buffer_free(nbuf);

	s=AB_Value_GetCurrency(v);
        if (!s)
          s="EUR";
        GWEN_DB_SetCharValue(dbV, GWEN_DB_FLAGS_OVERWRITE_VARS,
                             "currency", s);
      } /* if value */

      GWEN_DB_SetIntValue(dbT, GWEN_DB_FLAGS_OVERWRITE_VARS,
			  "textKey",
			  AB_Transaction_GetTextKey(t));

      sl=AB_Transaction_GetPurpose(t);
      if (sl) {
	GWEN_STRINGLISTENTRY *se;

	se=GWEN_StringList_FirstEntry(sl);
	GWEN_DB_DeleteVar(dbT, "purpose");
	while(se) {
	  p=GWEN_StringListEntry_Data(se);
	  if (p)
	    GWEN_DB_SetCharValue(dbT, GWEN_DB_FLAGS_DEFAULT,
				 "purpose", p);
	  se=GWEN_StringListEntry_Next(se);
	} /* while */
      }

      switch(aj->jobType) {
      case AB_Job_TypeCreateStandingOrder:
      case AB_Job_TypeModifyStandingOrder:
      case AB_Job_TypeDeleteStandingOrder:
        /* additional data for standing orders */

	  /* first execution date */
	ti=AB_Transaction_GetFirstExecutionDate(t);
	if (ti) {
	  GWEN_BUFFER *tbuf;

	  tbuf=GWEN_Buffer_new(0, 16, 0, 1);
	  GWEN_Time_toString(ti, "YYYYMMDD", tbuf);
	  GWEN_DB_SetCharValue(dbT,
			       GWEN_DB_FLAGS_OVERWRITE_VARS,
			       "special/xfirstExecutionDate",
			       GWEN_Buffer_GetStart(tbuf));
	  GWEN_Buffer_free(tbuf);
	}

#if 0
	/* don't ever set lastExecutionDate */
	/* lastExecutionDate */
	ti=AB_Transaction_GetLastExecutionDate(t);
	if (ti) {
	  GWEN_BUFFER *tbuf;

	  tbuf=GWEN_Buffer_new(0, 16, 0, 1);
	  GWEN_Time_toString(ti, "YYYYMMDD", tbuf);
	  GWEN_DB_SetCharValue(dbT,
			       GWEN_DB_FLAGS_OVERWRITE_VARS,
			       "special/xlastExecutionDate",
			       GWEN_Buffer_GetStart(tbuf));
	  GWEN_Buffer_free(tbuf);
	}
#endif

#if 0
	/* don't ever set nextExecutionDate */
	if (aj->jobType==AB_Job_TypeCreateStandingOrder) {
	  /* nextExecutionDate */
	  ti=AB_Transaction_GetNextExecutionDate(t);
	  if (ti) {
	    GWEN_BUFFER *tbuf;
  
	    tbuf=GWEN_Buffer_new(0, 16, 0, 1);
	    GWEN_Time_toString(ti, "YYYYMMDD", tbuf);
	    GWEN_DB_SetCharValue(dbT,
				 GWEN_DB_FLAGS_OVERWRITE_VARS,
				 "special/xnextExecutionDate",
				 GWEN_Buffer_GetStart(tbuf));
	    GWEN_Buffer_free(tbuf);
	  }
	}
#endif

        /* period */
        switch(AB_Transaction_GetPeriod(t)) {
        case AB_Transaction_PeriodMonthly: p="M"; break;
        case AB_Transaction_PeriodWeekly:  p="W"; break;
        default:
          DBG_ERROR(AQHBCI_LOGDOMAIN, "Unsupported period %d",
                    AB_Transaction_GetPeriod(t));
          return GWEN_ERROR_INVALID;
        }
        GWEN_DB_SetCharValue(dbT,
                             GWEN_DB_FLAGS_OVERWRITE_VARS,
                             "special/xperiod",
                             p);

        /* cycle */
        GWEN_DB_SetIntValue(dbT,
                            GWEN_DB_FLAGS_OVERWRITE_VARS,
                            "special/cycle",
                            AB_Transaction_GetCycle(t));

        /* execution day */
        GWEN_DB_SetIntValue(dbT,
                            GWEN_DB_FLAGS_OVERWRITE_VARS,
                            "special/executionDay",
                            AB_Transaction_GetExecutionDay(t));

        /* fiid */
	p=AB_Transaction_GetFiId(t);
        if (p)
	  GWEN_DB_SetCharValue(dbT, GWEN_DB_FLAGS_OVERWRITE_VARS,
			       "fiid", p);
        break;

      case AB_Job_TypeCreateDatedTransfer:
      case AB_Job_TypeModifyDatedTransfer:
      case AB_Job_TypeDeleteDatedTransfer:
        /* fiid */
	p=AB_Transaction_GetFiId(t);
        if (p)
	  GWEN_DB_SetCharValue(dbT, GWEN_DB_FLAGS_OVERWRITE_VARS,
			       "fiid", p);

        /* date */
        ti=AB_Transaction_GetDate(t);
        if (ti) {
	  GWEN_BUFFER *tbuf;

	  tbuf=GWEN_Buffer_new(0, 16, 0, 1);
	  GWEN_Time_toString(ti, "YYYYMMDD", tbuf);
	  GWEN_DB_SetCharValue(dbT,
			       GWEN_DB_FLAGS_OVERWRITE_VARS,
			       "xdate",
			       GWEN_Buffer_GetStart(tbuf));
	  GWEN_Buffer_free(tbuf);
	}

	break;

        /* --------------- add more jobs here -------------- */

      default:
        break;
      } /* switch */

    }
    else {
      DBG_ERROR(AQHBCI_LOGDOMAIN, "No transaction");
      AB_Job_SetStatus(bj, AB_Job_StatusError);
      return GWEN_ERROR_NO_DATA;
    }
    return 0;
  }

  case AH_Job_ExchangeModeResults: {
    AH_RESULT_LIST *rl;
    AH_RESULT *r;
    int has10;
    int has20;
    const AB_TRANSACTION *ot;

    rl=AH_Job_GetSegResults(j);
    assert(rl);

    r=AH_Result_List_First(rl);
    if (!r) {
      DBG_ERROR(AQHBCI_LOGDOMAIN, "No segment results");
      AB_Job_SetStatus(bj, AB_Job_StatusError);
      /* return GWEN_ERROR_NO_DATA; */
      return 0;
    }
    has10=0;
    has20=0;
    while(r) {
      int rcode;

      rcode=AH_Result_GetCode(r);
      if (rcode <=19)
	has10=1;
      else if (rcode>=20 && rcode <=29)
	has20=1;
      r=AH_Result_List_Next(r);
    }

    if (has20) {
      AB_Job_SetStatus(bj, AB_Job_StatusFinished);
      DBG_INFO(AQHBCI_LOGDOMAIN, "Job finished");
    }
    else if (has10) {
      switch(aj->jobType) {
      case AB_Job_TypeTransfer:
      case AB_Job_TypeDebitNote:
      case AB_Job_TypeInternalTransfer:
	AB_Job_SetStatus(bj, AB_Job_StatusPending);
	DBG_INFO(AQHBCI_LOGDOMAIN, "Job pending");
	break;
      case AB_Job_TypeCreateStandingOrder:
      case AB_Job_TypeModifyStandingOrder:
      case AB_Job_TypeDeleteStandingOrder:
      case AB_Job_TypeCreateDatedTransfer:
      case AB_Job_TypeModifyDatedTransfer:
      case AB_Job_TypeDeleteDatedTransfer:
	AB_Job_SetStatus(bj, AB_Job_StatusFinished);
	DBG_INFO(AQHBCI_LOGDOMAIN, "Job finished");
	break;
      default:
	DBG_ERROR(AQHBCI_LOGDOMAIN, "Unknown job type %d", aj->jobType);
	abort();
      }
    }
    else {
      DBG_INFO(AQHBCI_LOGDOMAIN,
	       "Error status (neither 0010 nor 0020)");
      AB_Job_SetStatus(bj, AB_Job_StatusError);
    }

    switch(aj->jobType) {
    case AB_Job_TypeTransfer:
    case AB_Job_TypeDebitNote:
    case AB_Job_TypeInternalTransfer:
      break;

    case AB_Job_TypeCreateStandingOrder:
      ot=AB_JobCreateStandingOrder_GetTransaction(bj);
      if (ot && aj->fiid) {
	AB_TRANSACTION *t;

	t=AB_Transaction_dup(ot);
	AB_Transaction_SetFiId(t, aj->fiid);
	AB_JobCreateStandingOrder_SetTransaction(bj, t);
      }
      break;

    case AB_Job_TypeModifyStandingOrder:
      ot=AB_JobModifyStandingOrder_GetTransaction(bj);
      if (ot && aj->fiid) {
	AB_TRANSACTION *t;

	t=AB_Transaction_dup(ot);
	AB_Transaction_SetFiId(t, aj->fiid);
	AB_JobModifyStandingOrder_SetTransaction(bj, t);
      }
      break;

    case AB_Job_TypeDeleteStandingOrder:
      break;

    case AB_Job_TypeCreateDatedTransfer:
      ot=AB_JobCreateDatedTransfer_GetTransaction(bj);
      if (ot && aj->fiid) {
	AB_TRANSACTION *t;

	t=AB_Transaction_dup(ot);
	AB_Transaction_SetFiId(t, aj->fiid);
	AB_JobCreateDatedTransfer_SetTransaction(bj, t);
      }
      break;

    case AB_Job_TypeModifyDatedTransfer:
      ot=AB_JobModifyDatedTransfer_GetTransaction(bj);
      if (ot && aj->fiid) {
	AB_TRANSACTION *t;

	t=AB_Transaction_dup(ot);
	AB_Transaction_SetFiId(t, aj->fiid);
	AB_JobModifyDatedTransfer_SetTransaction(bj, t);
      }
      break;

    case AB_Job_TypeDeleteDatedTransfer:
      break;

    default:
      DBG_ERROR(AQHBCI_LOGDOMAIN,
                "Unhandled job type %d", aj->jobType);
      return -1;
    }

    return 0;
  }

  default:
    DBG_NOTICE(AQHBCI_LOGDOMAIN, "Unsupported exchange mode");
    return GWEN_ERROR_NOT_SUPPORTED;
  } /* switch */
}










