/***************************************************************************
 $RCSfile$
 -------------------
 begin       : Wed Jan 09 2008
 copyright   : (C) 2008 by Martin Preuss
 email       : martin@libchipcard.de

 ***************************************************************************
 *          Please see toplevel file COPYING for license details           *
 ***************************************************************************/





int AO_Provider__AddAccountInfoReq(AB_PROVIDER *pro,
				   uint32_t guiid,
				   GWEN_BUFFER *buf) {
  int rv;

  GWEN_Buffer_AppendString(buf, "<ACCTINFORQ>");
  GWEN_Buffer_AppendString(buf, "<DTACCTUP>19700101000000");
  GWEN_Buffer_AppendString(buf, "</ACCTINFORQ>");

  /* wrap into request */
  rv=AO_Provider__WrapRequest(pro, "SIGNUP", "ACCTINFO", buf);
  if (rv<0) {
    DBG_INFO(AQOFXCONNECT_LOGDOMAIN, "here (%d)", rv);
    return rv;
  }

  return 0;
}








