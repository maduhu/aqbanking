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

#ifndef QBANKING_QBCFGMODUL_H
#define QBANKING_QBCFGMODUL_H


#include <aqbanking/banking.h>
#include <gwenhywfar/plugin.h>

#include <qstring.h>


#define QBCFGMODULE_FLAGS_CAN_CREATE_USER    0x00000001
#define QBCFGMODULE_FLAGS_CAN_CREATE_ACCOUNT 0x00000002


class QBCfgTabPageUser;
class QBCfgTabPageAccount;
class QBanking;
class QWidget;


class QBCfgModule;


typedef QBCfgModule* (*QBCFGMODULE_FACTORY_FN)(QBanking *qb);


class QBCfgModule {
  friend class QBanking;
private:
  QBanking *_qbanking;
  QString _name;
  GWEN_PLUGIN *_plugin;
  GWEN_TYPE_UINT32 _flags;

  void setPlugin(GWEN_PLUGIN *pl);
  GWEN_PLUGIN *getPlugin();

public:
  QBCfgModule(QBanking *qb, const QString &name);
  virtual ~QBCfgModule();

  const QString &getName() const;

  GWEN_TYPE_UINT32 getFlags() const;
  void setFlags(GWEN_TYPE_UINT32 fl);

  virtual QBCfgTabPageUser *getEditUserPage(AB_USER *u, QWidget *parent=0);
  virtual QBCfgTabPageAccount *getEditAccountPage(AB_ACCOUNT *a,
                                                  QWidget *parent=0);
  virtual int createNewUser(QWidget *parent=0);
  virtual int createNewAccount(QWidget *parent=0);

  QBanking *getBanking();
};

#endif

