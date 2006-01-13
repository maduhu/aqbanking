/* This file is auto-generated from "split.xml" by the typemaker
   tool of Gwenhywfar. 
   Do not edit this file -- all changes will be lost! */
#ifndef SPLIT_P_H
#define SPLIT_P_H

#include "split_l.h"


struct AB_SPLIT {
  GWEN_INHERIT_ELEMENT(AB_SPLIT)
  GWEN_LIST_ELEMENT(AB_SPLIT)
  int _usage;
  int _modified;

  char *country;
  char *bankCode;
  char *branchId;
  char *accountNumber;
  char *suffix;
  GWEN_STRINGLIST *name;
  AB_VALUE *value;
  GWEN_STRINGLIST *purpose;
  GWEN_STRINGLIST *category;
};



/** @name Account Info
 *
This group contains information about the remote account.*/
/*@{*/







/*@}*/

/** @name Value
*/
/*@{*/

/*@}*/




#endif /* SPLIT_P_H */
