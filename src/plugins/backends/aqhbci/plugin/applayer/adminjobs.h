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


#ifndef AH_ADMINJOBS_H
#define AH_ADMINJOBS_H


#include <gwenhywfar/crypt.h>
#include <aqhbci/job.h>
#include <aqhbci/account.h>

#ifdef __cplusplus
extern "C" {
#endif



/* __________________________________________________________________________
 * AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
 *                             AH_Job_GetKeys
 * YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY
 */


AH_JOB *AH_Job_GetKeys_new(AH_CUSTOMER *cu);
GWEN_CRYPTKEY *AH_Job_GetKeys_GetSignKey(const AH_JOB *j);
GWEN_CRYPTKEY *AH_Job_GetKeys_GetCryptKey(const AH_JOB *j);





/* __________________________________________________________________________
 * AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
 *                             AH_Job_SendKeys
 * YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY
 */


AH_JOB *AH_Job_SendKeys_new(AH_CUSTOMER *cu,
                            const GWEN_CRYPTKEY *cryptKey,
                            const GWEN_CRYPTKEY *signKey);






/* __________________________________________________________________________
 * AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
 *                             AH_Job_GetSysId
 * YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY
 */

AH_JOB *AH_Job_GetSysId_new(AH_CUSTOMER *cu);

const char *AH_Job_GetSysId_GetSysId(AH_JOB *j);






/* __________________________________________________________________________
 * AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
 *                             AH_Job_UpdateBank
 * YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY
 */

AH_JOB *AH_Job_UpdateBank_new(AH_CUSTOMER *cu);

/**
 * Returns a list of accounts found by this job. This list might be empty
 * (meaning the server did not send an account list).
 * The jobs remains the owner of that list and all its members.
 * Please note that the accounts returned are just local copies to be
 * inspected by the application (most likely the setup wizard).
 * You can not use any of these accounts directly for account jobs !
 */
AH_ACCOUNT_LIST2 *AH_Job_UpdateBank_GetAccountList(const AH_JOB *j);

/**
 * Returns a list of accounts found by this job. This list might be empty
 * (meaning the server did not send an account list).
 * The jobs is no longer the owner of that list and all its members, instead
 * the caller becomes the new owner thus leaving him responsible for
 * calling @ref AH_Account_List2_freeAll on that list.
 * Please note that the accounts returned are just local copies to be
 * inspected by the application (most likely the setup wizard).
 * You can not use any of these accounts directly for account jobs !
 */
AH_ACCOUNT_LIST2 *AH_Job_UpdateBank_TakeAccountList(AH_JOB *j);






/* __________________________________________________________________________
 * AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
 *                             AH_Job_TestVersion
 * YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY
 */


typedef enum {
  AH_JobTestVersion_ResultUnknown=0,
  AH_JobTestVersion_ResultNotSupported,
  AH_JobTestVersion_ResultMaybeSupported,
  AH_JobTestVersion_ResultSupported
} AH_JOB_TESTVERSION_RESULT;


AH_JOB *AH_Job_TestVersion_new(AH_CUSTOMER *cu, int anon);
AH_JOB_TESTVERSION_RESULT AH_Job_TestVersion_GetResult(const AH_JOB *j);



/* __________________________________________________________________________
 * AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
 *                             AH_Job_GetStatus
 * YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY
 */

AH_JOB *AH_Job_GetStatus_new(AH_CUSTOMER *cu,
                             const GWEN_TIME *fromDate,
                             const GWEN_TIME *toDate);
AH_RESULT_LIST *AH_Job_GetStatus_GetResults(const AH_JOB *j);


#ifdef __cplusplus
}
#endif


#endif /* AH_ADMINJOBS_H */
