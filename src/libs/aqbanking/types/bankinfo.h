/* This file is auto-generated from "bankinfo.xml" by the typemaker
   tool of Gwenhywfar. 
   Do not edit this file -- all changes will be lost! */
#ifndef BANKINFO_H
#define BANKINFO_H

/** @page P_AB_BANKINFO_PUBLIC AB_BankInfo (public)
This page describes the properties of AB_BANKINFO
@anchor AB_BANKINFO_Country
<h3>Country</h3>
<p>
</p>
<p>
Set this property with @ref AB_BankInfo_SetCountry, 
get it with @ref AB_BankInfo_GetCountry
</p>

@anchor AB_BANKINFO_BranchId
<h3>BranchId</h3>
<p>
</p>
<p>
Set this property with @ref AB_BankInfo_SetBranchId, 
get it with @ref AB_BankInfo_GetBranchId
</p>

@anchor AB_BANKINFO_BankId
<h3>BankId</h3>
<p>
</p>
<p>
Set this property with @ref AB_BankInfo_SetBankId, 
get it with @ref AB_BankInfo_GetBankId
</p>

@anchor AB_BANKINFO_Bic
<h3>Bic</h3>
<p>
</p>
<p>
Set this property with @ref AB_BankInfo_SetBic, 
get it with @ref AB_BankInfo_GetBic
</p>

@anchor AB_BANKINFO_BankName
<h3>BankName</h3>
<p>
</p>
<p>
Set this property with @ref AB_BankInfo_SetBankName, 
get it with @ref AB_BankInfo_GetBankName
</p>

@anchor AB_BANKINFO_Location
<h3>Location</h3>
<p>
</p>
<p>
Set this property with @ref AB_BankInfo_SetLocation, 
get it with @ref AB_BankInfo_GetLocation
</p>

@anchor AB_BANKINFO_Street
<h3>Street</h3>
<p>
</p>
<p>
Set this property with @ref AB_BankInfo_SetStreet, 
get it with @ref AB_BankInfo_GetStreet
</p>

@anchor AB_BANKINFO_Zipcode
<h3>Zipcode</h3>
<p>
</p>
<p>
Set this property with @ref AB_BankInfo_SetZipcode, 
get it with @ref AB_BankInfo_GetZipcode
</p>

@anchor AB_BANKINFO_City
<h3>City</h3>
<p>
</p>
<p>
Set this property with @ref AB_BankInfo_SetCity, 
get it with @ref AB_BankInfo_GetCity
</p>

@anchor AB_BANKINFO_Region
<h3>Region</h3>
<p>
</p>
<p>
Set this property with @ref AB_BankInfo_SetRegion, 
get it with @ref AB_BankInfo_GetRegion
</p>

@anchor AB_BANKINFO_Phone
<h3>Phone</h3>
<p>
</p>
<p>
Set this property with @ref AB_BankInfo_SetPhone, 
get it with @ref AB_BankInfo_GetPhone
</p>

@anchor AB_BANKINFO_Fax
<h3>Fax</h3>
<p>
</p>
<p>
Set this property with @ref AB_BankInfo_SetFax, 
get it with @ref AB_BankInfo_GetFax
</p>

@anchor AB_BANKINFO_Email
<h3>Email</h3>
<p>
</p>
<p>
Set this property with @ref AB_BankInfo_SetEmail, 
get it with @ref AB_BankInfo_GetEmail
</p>

@anchor AB_BANKINFO_Website
<h3>Website</h3>
<p>
</p>
<p>
Set this property with @ref AB_BankInfo_SetWebsite, 
get it with @ref AB_BankInfo_GetWebsite
</p>

@anchor AB_BANKINFO_Services
<h3>Services</h3>
<p>
This is the list of known servises of this bank. This object remains the owner of lists returned via @ref AB_BankInfo_GetServices.</p>
<p>
Set this property with @ref AB_BankInfo_SetServices, 
get it with @ref AB_BankInfo_GetServices
</p>

*/
#ifdef __cplusplus
extern "C" {
#endif

typedef struct AB_BANKINFO AB_BANKINFO;

#ifdef __cplusplus
} /* __cplusplus */
#endif

#include <gwenhywfar/db.h>
#include <gwenhywfar/misc.h>
#include <gwenhywfar/list2.h>
/* headers */
#include <gwenhywfar/types.h>
#include <aqbanking/error.h>
#include <aqbanking/bankinfoservice.h>

#ifdef __cplusplus
extern "C" {
#endif


GWEN_LIST_FUNCTION_LIB_DEFS(AB_BANKINFO, AB_BankInfo, AQBANKING_API)
AQBANKING_API AB_BANKINFO_LIST *AB_BankInfo_List_dup(const AB_BANKINFO_LIST *stl);

GWEN_LIST2_FUNCTION_LIB_DEFS(AB_BANKINFO, AB_BankInfo, AQBANKING_API)

/** Destroys all objects stored in the given LIST2 and the list itself
*/
AQBANKING_API void AB_BankInfo_List2_freeAll(AB_BANKINFO_LIST2 *stl);

/** Creates a new object.
*/
AQBANKING_API AB_BANKINFO *AB_BankInfo_new();
/** Creates an object from the data in the given GWEN_DB_NODE
*/
AQBANKING_API AB_BANKINFO *AB_BankInfo_fromDb(GWEN_DB_NODE *db);
/** Creates and returns a deep copy of thegiven object.
*/
AQBANKING_API AB_BANKINFO *AB_BankInfo_dup(const AB_BANKINFO*st);
/** Destroys the given object.
*/
AQBANKING_API void AB_BankInfo_free(AB_BANKINFO *st);
/** Increments the usage counter of the given object, so an additional free() is needed to destroy the object.
*/
AQBANKING_API void AB_BankInfo_Attach(AB_BANKINFO *st);
/** Reads data from a GWEN_DB.
*/
AQBANKING_API int AB_BankInfo_ReadDb(AB_BANKINFO *st, GWEN_DB_NODE *db);
/** Stores an object in the given GWEN_DB_NODE
*/
AQBANKING_API int AB_BankInfo_toDb(const AB_BANKINFO*st, GWEN_DB_NODE *db);
/** Returns 0 if this object has not been modified, !=0 otherwise
*/
AQBANKING_API int AB_BankInfo_IsModified(const AB_BANKINFO *st);
/** Sets the modified state of the given object
*/
AQBANKING_API void AB_BankInfo_SetModified(AB_BANKINFO *st, int i);

/**
* Returns the property @ref AB_BANKINFO_Country
*/
AQBANKING_API const char *AB_BankInfo_GetCountry(const AB_BANKINFO *el);
/**
* Set the property @ref AB_BANKINFO_Country
*/
AQBANKING_API void AB_BankInfo_SetCountry(AB_BANKINFO *el, const char *d);

/**
* Returns the property @ref AB_BANKINFO_BranchId
*/
AQBANKING_API const char *AB_BankInfo_GetBranchId(const AB_BANKINFO *el);
/**
* Set the property @ref AB_BANKINFO_BranchId
*/
AQBANKING_API void AB_BankInfo_SetBranchId(AB_BANKINFO *el, const char *d);

/**
* Returns the property @ref AB_BANKINFO_BankId
*/
AQBANKING_API const char *AB_BankInfo_GetBankId(const AB_BANKINFO *el);
/**
* Set the property @ref AB_BANKINFO_BankId
*/
AQBANKING_API void AB_BankInfo_SetBankId(AB_BANKINFO *el, const char *d);

/**
* Returns the property @ref AB_BANKINFO_Bic
*/
AQBANKING_API const char *AB_BankInfo_GetBic(const AB_BANKINFO *el);
/**
* Set the property @ref AB_BANKINFO_Bic
*/
AQBANKING_API void AB_BankInfo_SetBic(AB_BANKINFO *el, const char *d);

/**
* Returns the property @ref AB_BANKINFO_BankName
*/
AQBANKING_API const char *AB_BankInfo_GetBankName(const AB_BANKINFO *el);
/**
* Set the property @ref AB_BANKINFO_BankName
*/
AQBANKING_API void AB_BankInfo_SetBankName(AB_BANKINFO *el, const char *d);

/**
* Returns the property @ref AB_BANKINFO_Location
*/
AQBANKING_API const char *AB_BankInfo_GetLocation(const AB_BANKINFO *el);
/**
* Set the property @ref AB_BANKINFO_Location
*/
AQBANKING_API void AB_BankInfo_SetLocation(AB_BANKINFO *el, const char *d);

/**
* Returns the property @ref AB_BANKINFO_Street
*/
AQBANKING_API const char *AB_BankInfo_GetStreet(const AB_BANKINFO *el);
/**
* Set the property @ref AB_BANKINFO_Street
*/
AQBANKING_API void AB_BankInfo_SetStreet(AB_BANKINFO *el, const char *d);

/**
* Returns the property @ref AB_BANKINFO_Zipcode
*/
AQBANKING_API const char *AB_BankInfo_GetZipcode(const AB_BANKINFO *el);
/**
* Set the property @ref AB_BANKINFO_Zipcode
*/
AQBANKING_API void AB_BankInfo_SetZipcode(AB_BANKINFO *el, const char *d);

/**
* Returns the property @ref AB_BANKINFO_City
*/
AQBANKING_API const char *AB_BankInfo_GetCity(const AB_BANKINFO *el);
/**
* Set the property @ref AB_BANKINFO_City
*/
AQBANKING_API void AB_BankInfo_SetCity(AB_BANKINFO *el, const char *d);

/**
* Returns the property @ref AB_BANKINFO_Region
*/
AQBANKING_API const char *AB_BankInfo_GetRegion(const AB_BANKINFO *el);
/**
* Set the property @ref AB_BANKINFO_Region
*/
AQBANKING_API void AB_BankInfo_SetRegion(AB_BANKINFO *el, const char *d);

/**
* Returns the property @ref AB_BANKINFO_Phone
*/
AQBANKING_API const char *AB_BankInfo_GetPhone(const AB_BANKINFO *el);
/**
* Set the property @ref AB_BANKINFO_Phone
*/
AQBANKING_API void AB_BankInfo_SetPhone(AB_BANKINFO *el, const char *d);

/**
* Returns the property @ref AB_BANKINFO_Fax
*/
AQBANKING_API const char *AB_BankInfo_GetFax(const AB_BANKINFO *el);
/**
* Set the property @ref AB_BANKINFO_Fax
*/
AQBANKING_API void AB_BankInfo_SetFax(AB_BANKINFO *el, const char *d);

/**
* Returns the property @ref AB_BANKINFO_Email
*/
AQBANKING_API const char *AB_BankInfo_GetEmail(const AB_BANKINFO *el);
/**
* Set the property @ref AB_BANKINFO_Email
*/
AQBANKING_API void AB_BankInfo_SetEmail(AB_BANKINFO *el, const char *d);

/**
* Returns the property @ref AB_BANKINFO_Website
*/
AQBANKING_API const char *AB_BankInfo_GetWebsite(const AB_BANKINFO *el);
/**
* Set the property @ref AB_BANKINFO_Website
*/
AQBANKING_API void AB_BankInfo_SetWebsite(AB_BANKINFO *el, const char *d);

/**
* Returns the property @ref AB_BANKINFO_Services
*/
AQBANKING_API AB_BANKINFO_SERVICE_LIST *AB_BankInfo_GetServices(const AB_BANKINFO *el);
/**
* Set the property @ref AB_BANKINFO_Services
*/
AQBANKING_API void AB_BankInfo_SetServices(AB_BANKINFO *el, AB_BANKINFO_SERVICE_LIST *d);


#ifdef __cplusplus
} /* __cplusplus */
#endif


#endif /* BANKINFO_H */
