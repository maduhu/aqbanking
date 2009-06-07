/***************************************************************************
 $RCSfile$
 -------------------
 cvs         : $Id: import.c 764 2006-01-13 14:00:00Z cstim $
 begin       : Tue May 03 2005
 copyright   : (C) 2005 by Martin Preuss
 email       : martin@libchipcard.de

 ***************************************************************************
 *          Please see toplevel file COPYING for license details           *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "globals.h"
#include <gwenhywfar/text.h>
#include <gwenhywfar/io_file.h>
#include <gwenhywfar/iomanager.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>



static
int import(AB_BANKING *ab,
	   GWEN_DB_NODE *dbArgs,
	   int argc,
	   char **argv) {
  GWEN_DB_NODE *db;
  int rv;
  const char *ctxFile;
  const char *inFile;
  const char *importerName;
  const char *profileName;
  const char *profileFile;
  const char *bankId;
  const char *accountId;
  AB_IMEXPORTER *importer;
  GWEN_DB_NODE *dbProfiles;
  GWEN_DB_NODE *dbProfile;
  GWEN_DB_NODE *dbCtx;
  AB_IMEXPORTER_CONTEXT *ctx=0;
#ifdef WITH_AQFINANCE
  int useDb;
  int transfers;
#endif
  int fd;
  const GWEN_ARGS args[]={
  {
    GWEN_ARGS_FLAGS_HAS_ARGUMENT, /* flags */
    GWEN_ArgsType_Char,            /* type */
    "ctxFile",                    /* name */
    0,                            /* minnum */
    1,                            /* maxnum */
    "c",                          /* short option */
    "ctxfile",                    /* long option */
    "Specify the file to store the context in",   /* short description */
    "Specify the file to store the context in"      /* long description */
  },
  {
    GWEN_ARGS_FLAGS_HAS_ARGUMENT, /* flags */
    GWEN_ArgsType_Char,            /* type */
    "inFile",                     /* name */
    0,                            /* minnum */
    1,                            /* maxnum */
    "f",                          /* short option */
    "infile",                    /* long option */
    "Specify the file to read the data from",   /* short description */
    "Specify the file to read the data from"      /* long description */
  },
  {
    GWEN_ARGS_FLAGS_HAS_ARGUMENT, /* flags */
    GWEN_ArgsType_Char,            /* type */
    "importerName",               /* name */
    0,                            /* minnum */
    1,                            /* maxnum */
    0,                            /* short option */
    "importer",                    /* long option */
    "Specify the importer to use",   /* short description */
    "Specify the importer to use"      /* long description */
  },
  {
    GWEN_ARGS_FLAGS_HAS_ARGUMENT, /* flags */
    GWEN_ArgsType_Char,            /* type */
    "profileName",                /* name */
    0,                            /* minnum */
    1,                            /* maxnum */
    0,                            /* short option */
    "profile",                    /* long option */
    "Specify the export profile to use",   /* short description */
    "Specify the export profile to use"      /* long description */
  },
  {
    GWEN_ARGS_FLAGS_HAS_ARGUMENT, /* flags */
    GWEN_ArgsType_Char,            /* type */
    "profileFile",                /* name */
    0,                            /* minnum */
    1,                            /* maxnum */
    0,                            /* short option */
    "profile-file",               /* long option */
    "Specify the file to load the export profile from",/* short description */
    "Specify the file to load the export profile from" /* long description */
  },
  {
    GWEN_ARGS_FLAGS_HAS_ARGUMENT, /* flags */
    GWEN_ArgsType_Char,            /* type */
    "bankId",                     /* name */
    0,                            /* minnum */
    1,                            /* maxnum */
    "b",                          /* short option */
    "bank",                       /* long option */
    "overwrite the bank code",      /* short description */
    "overwrite the bank code"       /* long description */
  },
  {
    GWEN_ARGS_FLAGS_HAS_ARGUMENT, /* flags */
    GWEN_ArgsType_Char,            /* type */
    "accountId",                  /* name */
    0,                            /* minnum */
    1,                            /* maxnum */
    "a",                          /* short option */
    "account",                    /* long option */
    "overwrite the account number",     /* short description */
    "overwrite the account number"      /* long description */
  },
#ifdef WITH_AQFINANCE
  {
    0,                
    GWEN_ArgsType_Int,
    "usedb",
    0,  
    1,  
    0, 
    "usedb",
    "store transfer in internal database",
    "store transfer in internal database"
  },
  {
    0,                
    GWEN_ArgsType_Int,
    "transfers",
    0,  
    1,  
    0, 
    "transfers",
    "store in transfer table of internal database",
    "store in transfer table of internal database"
  },
#endif
  {
    GWEN_ARGS_FLAGS_HELP | GWEN_ARGS_FLAGS_LAST, /* flags */
    GWEN_ArgsType_Int,             /* type */
    "help",                       /* name */
    0,                            /* minnum */
    0,                            /* maxnum */
    "h",                          /* short option */
    "help",                       /* long option */
    "Show this help screen",      /* short description */
    "Show this help screen"       /* long description */
  }
  };

  db=GWEN_DB_GetGroup(dbArgs, GWEN_DB_FLAGS_DEFAULT, "local");
  rv=GWEN_Args_Check(argc, argv, 1,
                     0 /*GWEN_ARGS_MODE_ALLOW_FREEPARAM*/,
                     args,
                     db);
  if (rv==GWEN_ARGS_RESULT_ERROR) {
    fprintf(stderr, "ERROR: Could not parse arguments\n");
    return 1;
  }
  else if (rv==GWEN_ARGS_RESULT_HELP) {
    GWEN_BUFFER *ubuf;

    ubuf=GWEN_Buffer_new(0, 1024, 0, 1);
    if (GWEN_Args_Usage(args, ubuf, GWEN_ArgsOutType_Txt)) {
      fprintf(stderr, "ERROR: Could not create help string\n");
      return 1;
    }
    fprintf(stderr, "%s\n", GWEN_Buffer_GetStart(ubuf));
    GWEN_Buffer_free(ubuf);
    return 0;
  }

  bankId=GWEN_DB_GetCharValue(db, "bankId", 0, 0);
  accountId=GWEN_DB_GetCharValue(db, "accountId", 0, 0);
  importerName=GWEN_DB_GetCharValue(db, "importerName", 0, "csv");
  profileName=GWEN_DB_GetCharValue(db, "profileName", 0, "default");
  profileFile=GWEN_DB_GetCharValue(db, "profileFile", 0, 0);
  ctxFile=GWEN_DB_GetCharValue(db, "ctxfile", 0, 0);
#ifdef WITH_AQFINANCE
  useDb=GWEN_DB_GetIntValue(db, "usedb", 0, 0);
  if (useDb && ctxFile) {
    fprintf(stderr, "Option \"-c\" doesn't work with \"--usedb\"\n");
    return 1;
  }
  transfers=GWEN_DB_GetIntValue(db, "transfers", 0, 0);
#endif

  rv=AB_Banking_Init(ab);
  if (rv) {
    DBG_ERROR(0, "Error on init (%d)", rv);
    return 2;
  }

  rv=AB_Banking_OnlineInit(ab, 0);
  if (rv) {
    DBG_ERROR(0, "Error on init (%d)", rv);
    return 2;
  }

  /* get import module */
  importer=AB_Banking_GetImExporter(ab, importerName);
  if (!importer) {
    DBG_ERROR(0, "Import module \"%s\" not found", importerName);
    return 3;
  }

  /* get profiles */
  if (profileFile) {
    dbProfiles=GWEN_DB_Group_new("profiles");
    if (GWEN_DB_ReadFile(dbProfiles, profileFile,
                         GWEN_DB_FLAGS_DEFAULT |
			 GWEN_PATH_FLAGS_CREATE_GROUP,
			 0,
			 2000)) {
      DBG_ERROR(0, "Error reading profiles from \"%s\"",
                profileFile);
      return 3;
    }
  }
  else {
    dbProfiles=AB_Banking_GetImExporterProfiles(ab, importerName);
  }

  /* select profile */
  dbProfile=GWEN_DB_GetFirstGroup(dbProfiles);
  while(dbProfile) {
    const char *name;

    name=GWEN_DB_GetCharValue(dbProfile, "name", 0, 0);
    assert(name);
    if (strcasecmp(name, profileName)==0)
      break;
    dbProfile=GWEN_DB_GetNextGroup(dbProfile);
  }
  if (!dbProfile) {
    DBG_ERROR(0,
	      "Profile \"%s\" for importer \"%s\" not found",
              profileName, importerName);
    return 3;
  }

  /* import new context */
  ctx=AB_ImExporterContext_new();

  inFile=GWEN_DB_GetCharValue(db, "inFile", 0, 0);
  if (inFile==0)
    fd=fileno(stdin);
  else
    fd=open(inFile, O_RDONLY);
  if (fd<0) {
    DBG_ERROR(0, "Error selecting input file: %s",
	      strerror(errno));
    AB_ImExporterContext_free(ctx);
    GWEN_DB_Group_free(dbProfiles);
    return 4;
  }
  else {
    GWEN_IO_LAYER *io;

    io=GWEN_Io_LayerFile_new(fd, -1);
    GWEN_Io_Layer_AddFlags(io, GWEN_IO_LAYER_FLAGS_DONTCLOSE);
    rv=GWEN_Io_Manager_RegisterLayer(io);
    if (rv<0) {
      DBG_ERROR(0, "Error registering io layer (%d)", rv);
      GWEN_Io_Layer_free(io);
      AB_ImExporterContext_free(ctx);
      GWEN_DB_Group_free(dbProfiles);
      return 4;
    }

    rv=AB_ImExporter_Import(importer,
			    ctx,
                            io,
			    dbProfile,
			    0);
    if (rv<0) {
      DBG_ERROR(0, "Error exporting data (%d)", rv);
      GWEN_Io_Layer_free(io);
      AB_ImExporterContext_free(ctx);
      GWEN_DB_Group_free(dbProfiles);
      return 4;
    }

    rv=GWEN_Io_Layer_DisconnectRecursively(io, NULL, 0, 0, 2000);
    if (rv<0) {
      DBG_ERROR(0, "Error flushing (%d)", rv);
      GWEN_Io_Layer_free(io);
      AB_ImExporterContext_free(ctx);
      GWEN_DB_Group_free(dbProfiles);
      return 4;
    }
    GWEN_Io_Layer_free(io);

  }
  GWEN_DB_Group_free(dbProfiles);

  /* adjust local account id if requested */
  if (bankId || accountId) {
    AB_IMEXPORTER_ACCOUNTINFO *iea;

    iea=AB_ImExporterContext_GetFirstAccountInfo(ctx);
    while(iea) {
      if (bankId)
        AB_ImExporterAccountInfo_SetBankCode(iea, bankId);
      if (accountId)
        AB_ImExporterAccountInfo_SetAccountNumber(iea, accountId);
      iea=AB_ImExporterContext_GetNextAccountInfo(ctx);
    } /* while */
  }

#ifdef WITH_AQFINANCE
  if (!useDb) {
#endif
    /* write context */
    dbCtx=GWEN_DB_Group_new("context");
    if (AB_ImExporterContext_toDb(ctx, dbCtx)) {
      DBG_ERROR(0, "Error writing context to db");
      return 4;
    }
    if (ctxFile==0)
      fd=fileno(stdout);
    else
      fd=open(ctxFile, O_RDWR|O_CREAT|O_TRUNC,
	      S_IRUSR | S_IWUSR
#ifdef S_IRGRP
	      | S_IRGRP
#endif
#ifdef S_IWGRP
	      | S_IWGRP
#endif
	     );
    if (fd<0) {
      DBG_ERROR(0, "Error selecting output file: %s",
		strerror(errno));
      AB_ImExporterContext_free(ctx);
      return 4;
    }
    else {
      GWEN_DB_NODE *dbCtx;
      int rv;

      dbCtx=GWEN_DB_Group_new("context");
      rv=AB_ImExporterContext_toDb(ctx, dbCtx);
      if (rv<0) {
	DBG_ERROR(0, "Error writing context to db (%d)", rv);
	GWEN_DB_Group_free(dbCtx);
	AB_ImExporterContext_free(ctx);
	AB_Banking_OnlineFini(ab, 0);
	AB_Banking_Fini(ab);
	return 4;
      }

      rv=GWEN_DB_WriteToFd(dbCtx, fd,
			   GWEN_DB_FLAGS_DEFAULT,
			   0,
			   2000);
      if (rv<0) {
	DBG_ERROR(0, "Error writing context (%d)", rv);
	GWEN_DB_Group_free(dbCtx);
	AB_ImExporterContext_free(ctx);
	if (ctxFile)
	  close(fd);
	AB_Banking_OnlineFini(ab, 0);
	AB_Banking_Fini(ab);
	return 4;
      }

      if (ctxFile) {
	if (close(fd)) {
	  DBG_ERROR(0, "Error writing context (%d)", rv);
	  GWEN_DB_Group_free(dbCtx);
	  AB_ImExporterContext_free(ctx);
	  AB_Banking_OnlineFini(ab, 0);
	  AB_Banking_Fini(ab);
	  return 4;
	}
      }

      GWEN_DB_Group_free(dbCtx);
    }
#ifdef WITH_AQFINANCE
  }
  else {
    rv=AFM_import_statements(ab, ctx);
    if (rv<0) {
      DBG_ERROR(0, "Unable to store transfer to DB (%d)", rv);
      AB_ImExporterContext_free(ctx);
      AB_Banking_OnlineFini(ab, 0);
      AB_Banking_Fini(ab);
      return 4;
    }
  }
#endif
  AB_ImExporterContext_free(ctx);

  /* that's is */
  rv=AB_Banking_OnlineFini(ab, 0);
  if (rv) {
    fprintf(stderr, "ERROR: Error on deinit (%d)\n", rv);
    AB_Banking_Fini(ab);
    return 5;
  }

  rv=AB_Banking_Fini(ab);
  if (rv) {
    fprintf(stderr, "ERROR: Error on deinit (%d)\n", rv);
    return 5;
  }

  return 0;
}





