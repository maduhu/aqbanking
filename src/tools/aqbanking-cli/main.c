/***************************************************************************
 begin       : Tue May 03 2005
 copyright   : (C) 2005 by Martin Preuss
 email       : martin@libchipcard.de

 ***************************************************************************
 *          Please see toplevel file COPYING for license details           *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <gwenhywfar/logger.h>
#include <gwenhywfar/db.h>
#include <gwenhywfar/debug.h>
#include <gwenhywfar/cgui.h>

#include <gwenhywfar/gwenhywfar.h>
#include <gwenhywfar/logger.h>
#include <gwenhywfar/debug.h>
#include <aqbanking/banking.h>
#include <gwenhywfar/directory.h>

#include "globals.h"


#include "af_utils.c"
#include "dbinit.c"
#include "dbrecontrans.c"
#include "dblisttrans.c"
#include "dblisttransfers.c"
#include "chkacc.c"
#include "chkiban.c"
#include "debitnote.c"
#include "debitnotes.c"
#include "import.c"
#include "listaccs.c"
#include "listbal.c"
#include "listtrans.c"
#include "listtransfers.c"
#include "request.c"
#include "senddtazv.c"
#include "transfer.c"
#include "transfers.c"
#include "util.c"
#include "versions.c"
#include "addtransaction.c"
#include "fillgaps.c"
#include "updateconf.c"



int main(int argc, char **argv) {
  GWEN_DB_NODE *db;
  const char *cmd;
  int rv;
  AB_BANKING *ab;
  GWEN_GUI *gui;
  int nonInteractive=0;
  const char *pinFile;
  const char *cfgDir;
  const GWEN_ARGS args[]={
  {
    GWEN_ARGS_FLAGS_HAS_ARGUMENT, /* flags */
    GWEN_ArgsType_Char,           /* type */
    "cfgdir",                     /* name */
    0,                            /* minnum */
    1,                            /* maxnum */
    "D",                          /* short option */
    "cfgdir",                     /* long option */
    I18S("Specify the configuration folder"),
    I18S("Specify the configuration folder")
  },
  {
    0,                            /* flags */
    GWEN_ArgsType_Int,            /* type */
    "nonInteractive",             /* name */
    0,                            /* minnum */
    1,                            /* maxnum */
    "n",                          /* short option */
    "noninteractive",             /* long option */
    "Select non-interactive mode",/* short description */
    "Select non-interactive mode.\n"        /* long description */
    "This automatically returns a confirmative answer to any non-critical\n"
    "message."
  },
  {
    GWEN_ARGS_FLAGS_HAS_ARGUMENT, /* flags */
    GWEN_ArgsType_Char,           /* type */
    "pinfile",                    /* name */
    0,                            /* minnum */
    1,                            /* maxnum */
    "P",                          /* short option */
    "pinfile",                    /* long option */
    "Specify the PIN file",       /* short description */
    "Specify the PIN file"        /* long description */
  },
  {
    GWEN_ARGS_FLAGS_HELP | GWEN_ARGS_FLAGS_LAST, /* flags */
    GWEN_ArgsType_Int,            /* type */
    "help",                       /* name */
    0,                            /* minnum */
    0,                            /* maxnum */
    "h",                          /* short option */
    "help",
    I18S("Show this help screen. For help on commands, "
	 "run aqbanking-cli <COMMAND> --help."),
    I18S("Show this help screen. For help on commands, run aqbanking-cli <COMMAND> --help.")
  }
  };

  rv=GWEN_Init();
  if (rv) {
    fprintf(stderr, "ERROR: Unable to init Gwen.\n");
    exit(2);
  }

  GWEN_Logger_Open(0, "aqbanking-cli", 0,
		   GWEN_LoggerType_Console,
		   GWEN_LoggerFacility_User);
  GWEN_Logger_SetLevel(0, GWEN_LoggerLevel_Warning);

  rv=GWEN_I18N_BindTextDomain_Dir(PACKAGE, LOCALEDIR);
  if (rv) {
    DBG_ERROR(0, "Could not bind textdomain (%d)", rv);
  }
  else {
    rv=GWEN_I18N_BindTextDomain_Codeset(PACKAGE, "UTF-8");
    if (rv) {
      DBG_ERROR(0, "Could not set codeset (%d)", rv);
    }
  }

  db=GWEN_DB_Group_new("arguments");
  rv=GWEN_Args_Check(argc, argv, 1,
		     GWEN_ARGS_MODE_ALLOW_FREEPARAM |
		     GWEN_ARGS_MODE_STOP_AT_FREEPARAM,
		     args,
		     db);
  if (rv==GWEN_ARGS_RESULT_ERROR) {
    fprintf(stderr, "ERROR: Could not parse arguments main\n");
    return 1;
  }
  else if (rv==GWEN_ARGS_RESULT_HELP) {
    GWEN_BUFFER *ubuf;

    ubuf=GWEN_Buffer_new(0, 1024, 0, 1);
    GWEN_Buffer_AppendString(ubuf,
                             I18N("Usage: "));
    GWEN_Buffer_AppendString(ubuf, argv[0]);
    GWEN_Buffer_AppendString(ubuf,
                             I18N(" [GLOBAL OPTIONS] COMMAND "
                                  "[LOCAL OPTIONS]\n"));
    GWEN_Buffer_AppendString(ubuf,
                             I18N("\nGlobal Options:\n"));
    if (GWEN_Args_Usage(args, ubuf, GWEN_ArgsOutType_Txt)) {
      fprintf(stderr, "ERROR: Could not create help string\n");
      return 1;
    }
    GWEN_Buffer_AppendString(ubuf,
                             I18N("\nCommands:\n"));
    GWEN_Buffer_AppendString(ubuf, " senddtazv:\n");
    GWEN_Buffer_AppendString(ubuf,
			     I18N("   Sends a DTAZV file to the bank\n"));
    GWEN_Buffer_AppendString(ubuf, " listaccs\n");
    GWEN_Buffer_AppendString(ubuf,
			     I18N("   Prints the list of accounts\n"));

    GWEN_Buffer_AppendString(ubuf, " listbal\n");
    GWEN_Buffer_AppendString(ubuf,
                             I18N("  Export balances from a  "
				  "context file.\n"));

    GWEN_Buffer_AppendString(ubuf, " listtrans\n");
    GWEN_Buffer_AppendString(ubuf,
			     I18N("  Export transactions from a "
				  "context file.\n"));

    GWEN_Buffer_AppendString(ubuf, " request\n");
    GWEN_Buffer_AppendString(ubuf,
                             I18N("   Requests transactions, "
				  "  balances, standing orders etc.\n"));

    GWEN_Buffer_AppendString(ubuf, " chkacc\n");
    GWEN_Buffer_AppendString(ubuf,
			     I18N("   Check a combination of bank id and "
				  "account number\n"));

    GWEN_Buffer_AppendString(ubuf, " chkiban\n");
    GWEN_Buffer_AppendString(ubuf,
			     I18N("   Check an IBAN\n"));

    GWEN_Buffer_AppendString(ubuf, "\n");

    fprintf(stderr, "%s\n", GWEN_Buffer_GetStart(ubuf));
    GWEN_Buffer_free(ubuf);
    return 0;
  }
  if (rv) {
    argc-=rv-1;
    argv+=rv-1;
  }

  nonInteractive=GWEN_DB_GetIntValue(db, "nonInteractive", 0, 0);
  cfgDir=GWEN_DB_GetCharValue(db, "cfgdir", 0, 0);

  cmd=GWEN_DB_GetCharValue(db, "params", 0, 0);
  if (!cmd) {
    fprintf(stderr, "ERROR: Command needed.\n");
    return 1;
  }

  gui=GWEN_Gui_CGui_new();
  GWEN_Gui_CGui_SetCharSet(gui, "ISO-8859-15");
  GWEN_Gui_CGui_SetIsNonInteractive(gui, nonInteractive);

  pinFile=GWEN_DB_GetCharValue(db, "pinFile", 0, NULL);
  if (pinFile) {
    GWEN_DB_NODE *dbPins;

    dbPins=GWEN_DB_Group_new("pins");
    if (GWEN_DB_ReadFile(dbPins, pinFile,
			 GWEN_DB_FLAGS_DEFAULT |
			 GWEN_PATH_FLAGS_CREATE_GROUP,
			 0, 20000)) {
      fprintf(stderr, "Error reading pinfile \"%s\"\n", pinFile);
      return 2;
    }
    GWEN_Gui_CGui_SetPasswordDb(gui, dbPins, 1);
  }
				    
  GWEN_Gui_SetGui(gui);

  ab=AB_Banking_new("aqbanking-cli", cfgDir, 0);

  if (strcasecmp(cmd, "senddtazv")==0) {
    rv=sendDtazv(ab, db, argc, argv);
  }
  else if (strcasecmp(cmd, "listaccs")==0) {
    rv=listAccs(ab, db, argc, argv);
  }
  else if (strcasecmp(cmd, "listbal")==0) {
    rv=listBal(ab, db, argc, argv);
  }
  else if (strcasecmp(cmd, "listtrans")==0) {
    rv=listTrans(ab, db, argc, argv);
  }
  else if (strcasecmp(cmd, "request")==0) {
    rv=request(ab, db, argc, argv);
  }
  else if (strcasecmp(cmd, "chkacc")==0) {
    rv=chkAcc(ab, db, argc, argv);
  }
  else if (strcasecmp(cmd, "chkiban")==0) {
    rv=chkIban(ab, db, argc, argv);
  }
  else if (strcasecmp(cmd, "import")==0) {
    rv=import(ab, db, argc, argv);
  }
  else if (strcasecmp(cmd, "transfers")==0) {
    rv=transfers(ab, db, argc, argv);
  }
  else if (strcasecmp(cmd, "transfer")==0) {
    rv=transfer(ab, db, argc, argv);
  }
  else if (strcasecmp(cmd, "listtransfers")==0) {
    rv=listTransfers(ab, db, argc, argv);
  }
  else if (strcasecmp(cmd, "debitnote")==0) {
    rv=debitNote(ab, db, argc, argv);
  }
  else if (strcasecmp(cmd, "debitnotes")==0) {
    rv=debitNotes(ab, db, argc, argv);
  }
  else if (strcasecmp(cmd, "versions")==0) {
    rv=versions(ab, db, argc, argv);
  }
  else if (strcasecmp(cmd, "addtrans")==0) {
    rv=addTransaction(ab, db, argc, argv);
  }
  else if (strcasecmp(cmd, "fillgaps")==0) {
    rv=fillGaps(ab, db, argc, argv);
  }
  else if (strcasecmp(cmd, "updateconf")==0) {
    rv=updateConf(ab, db, argc, argv);
  }
  else if (strcasecmp(cmd, "dbinit")==0) {
#ifdef WITH_AQFINANCE
    rv=dbInit(ab, db, argc, argv);
#else
    fprintf(stderr, "ERROR: Support for AqFinance not built-in.\n");
    rv=1;
#endif
  }
  else if (strcasecmp(cmd, "dbrecon")==0) {
#ifdef WITH_AQFINANCE
    rv=dbReconTrans(ab, db, argc, argv);
#else
    fprintf(stderr, "ERROR: Support for AqFinance not built-in.\n");
    rv=1;
#endif
  }
  else if (strcasecmp(cmd, "dblisttrans")==0) {
#ifdef WITH_AQFINANCE
    rv=dblistTrans(ab, db, argc, argv);
#else
    fprintf(stderr, "ERROR: Support for AqFinance not built-in.\n");
    rv=1;
#endif
  }
  else if (strcasecmp(cmd, "dblisttransfers")==0) {
#ifdef WITH_AQFINANCE
    rv=dblistTransfers(ab, db, argc, argv);
#else
    fprintf(stderr, "ERROR: Support for AqFinance not built-in.\n");
    rv=1;
#endif
  }
  else {
    fprintf(stderr, "ERROR: Unknown command \"%s\".\n", cmd);
    rv=1;
  }

  return rv;
}


