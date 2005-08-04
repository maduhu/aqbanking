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


#ifndef AQBANKING_ERROR_H
#define AQBANKING_ERROR_H

/** @FIXME: disabled until next release of GnuCash */
#define AQBANKING_NOWARN_DEPRECATED


#ifdef __declspec
# if BUILDING_AQBANKING_DLL
#  define AQBANKING_API __declspec (dllexport)
# else /* Not BUILDING_AQBANKING_DLL */
#  define AQBANKING_API __declspec (dllimport)
# endif /* Not BUILDING_AQBANKING_DLL */
#else
# define AQBANKING_API
#endif

#ifndef AQBANKING_NOWARN_DEPRECATED
# ifdef __GNUC__
#  define AQBANKING_DEPRECATED __attribute((__deprecated__))
# else
#  define AQBANKING_DEPRECATED
# endif
# else
#  define AQBANKING_DEPRECATED
#endif

#define AQBANKING_LOGDOMAIN "aqbanking"


/** @defgroup AB_ERROR (Error Codes)
 * @ingroup AB_C_INTERFACE
 */
/*@{*/
#define AB_ERROR_SUCCESS           0
#define AB_ERROR_GENERIC         (-1)
#define AB_ERROR_NOT_SUPPORTED   (-2)
#define AB_ERROR_NOT_AVAILABLE   (-3)
#define AB_ERROR_BAD_CONFIG_FILE (-4)
#define AB_ERROR_INVALID         (-5)
#define AB_ERROR_NETWORK         (-6)
#define AB_ERROR_NOT_FOUND       (-7)
#define AB_ERROR_EMPTY           (-8)
#define AB_ERROR_USER_ABORT      (-9)
#define AB_ERROR_FOUND           (-10)
#define AB_ERROR_NO_DATA         (-11)
#define AB_ERROR_NOFN            (-12)
#define AB_ERROR_UNKNOWN_ACCOUNT (-13)
#define AB_ERROR_NOT_INIT        (-14)
#define AB_ERROR_SECURITY        (-15)
#define AB_ERROR_BAD_DATA        (-16)
#define AB_ERROR_UNKNOWN         (-17)
#define AB_ERROR_ABORTED         (-18)
#define AB_ERROR_DEFAULT_VALUE   (-19)

#define AB_ERROR_USER1           (-128)
#define AB_ERROR_USER2           (-129)
#define AB_ERROR_USER3           (-130)
#define AB_ERROR_USER4           (-131)
/*@}*/




#endif /* AQBANKING_ERROR_H */


