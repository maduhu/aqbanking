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


#ifndef AH_JOBGETTRANSACTIONS_P_H
#define AH_JOBGETTRANSACTIONS_P_H


#include <aqhbci/jobgettransactions.h>
#include <gwenhywfar/db.h>


typedef struct AH_JOB_GETTRANSACTIONS AH_JOB_GETTRANSACTIONS;
struct AH_JOB_GETTRANSACTIONS {
  AB_TRANSACTION_LIST2 *bookedTransactions;
  AB_TRANSACTION_LIST2 *notedTransactions;
  AB_ACCOUNT_STATUS_LIST2 *notedBalances;
};
static void AH_Job_GetTransactions_FreeData(void *bp, void *p);
static int AH_Job_GetTransactions_Process(AH_JOB *j);
static int AH_Job_GetTransactions_Exchange(AH_JOB *j, AB_JOB *bj,
                                           AH_JOB_EXCHANGE_MODE m);

static int
  AH_Job_GetTransactions__ReadTransactions(AH_JOB *j,
                                           const char *docType,
                                           GWEN_BUFFER *buf,
                                           AB_TRANSACTION_LIST2 *tl,
                                           AB_ACCOUNT_STATUS_LIST2 *asl);



#endif /* AH_JOBGETTRANSACTIONS_P_H */


