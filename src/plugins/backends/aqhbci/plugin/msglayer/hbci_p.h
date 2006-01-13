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


#ifndef GWHBCI_HBCI_P_H
#define GWHBCI_HBCI_P_H

#include "hbci_l.h"
#include <aqhbci/message.h>

#define AH_REGKEY_PATHS       "Software\\AqHbci\\Paths"
#define AH_REGKEY_XMLDATADIR  "xmldatadir"

#define AH_PM_LIBNAME       "aqhbci"
#define AH_PM_XMLDATADIR    "xmldatadir"


#define AH_HBCI_DEFAULT_CONNECT_TIMEOUT 30
#define AH_HBCI_DEFAULT_TRANSFER_TIMEOUT 60


struct AH_HBCI {
  GWEN_INHERIT_ELEMENT(AH_HBCI);

  AB_BANKING *banking;
  AB_PROVIDER *provider;

  char *productName;
  char *productVersion;

  GWEN_XMLNODE *defs;

  AH_MEDIUM_LIST *activeMedia;

  GWEN_TYPE_UINT32 counter;
  AH_MEDIUM *currentMedium;
  GWEN_TYPE_UINT32 lastMediumId;

  GWEN_DB_NODE *sharedRuntimeData;

  int transferTimeout;
  int connectTimeout;

};



static int AH_HBCI_SaveSettings(const char *path, GWEN_DB_NODE *db);

#if 0
static GWEN_DB_NODE *AH_HBCI_LoadSettings(const char *path);
#endif


static int AH_HBCI_AddDefinitions(AH_HBCI *hbci, GWEN_XMLNODE *node);
static GWEN_XMLNODE *AH_HBCI_LoadDefaultXmlFiles(const AH_HBCI *hbci);

static int AH_HBCI__LoadMedia(AH_HBCI *hbci, GWEN_DB_NODE *db);
static int AH_HBCI__SaveMedia(AH_HBCI *hbci, GWEN_DB_NODE *db);

static int AH_HBCI__AddMedium(AH_HBCI *hbci, AH_MEDIUM *m);


#endif /* GWHBCI_HBCI_P_H */



