/* This file is auto-generated from "cellphoneproduct.xml" by the typemaker
   tool of Gwenhywfar. 
   Do not edit this file -- all changes will be lost! */
#ifndef CELLPHONEPRODUCT_H
#define CELLPHONEPRODUCT_H

/** @page P_AB_CELLPHONE_PRODUCT_PUBLIC AB_CellPhoneProduct (public)
This page describes the properties of AB_CELLPHONE_PRODUCT
@anchor AB_CELLPHONE_PRODUCT_Id
<h3>Id</h3>
<p>
Id assigned by the backend.</p>
<p>
Set this property with @ref AB_CellPhoneProduct_SetId, 
get it with @ref AB_CellPhoneProduct_GetId
</p>

@anchor AB_CELLPHONE_PRODUCT_ProviderName
<h3>ProviderName</h3>
<p>
Name of the provider.</p>
<p>
Set this property with @ref AB_CellPhoneProduct_SetProviderName, 
get it with @ref AB_CellPhoneProduct_GetProviderName
</p>

@anchor AB_CELLPHONE_PRODUCT_ProductName
<h3>ProductName</h3>
<p>
Name of the product.</p>
<p>
Set this property with @ref AB_CellPhoneProduct_SetProductName, 
get it with @ref AB_CellPhoneProduct_GetProductName
</p>

@anchor AB_CELLPHONE_PRODUCT_AllowFreeValue
<h3>AllowFreeValue</h3>
<p>
</p>
<p>
Set this property with @ref AB_CellPhoneProduct_SetAllowFreeValue, 
get it with @ref AB_CellPhoneProduct_GetAllowFreeValue
</p>

@anchor AB_CELLPHONE_PRODUCT_MinimumValue
<h3>MinimumValue</h3>
<p>
This field contains the minimum value which can be loaded onto the prepaid card. This value can be empty (or non-existent) for some backends and banks.</p>
<p>
Set this property with @ref AB_CellPhoneProduct_SetMinimumValue, 
get it with @ref AB_CellPhoneProduct_GetMinimumValue
</p>

@anchor AB_CELLPHONE_PRODUCT_MaximumValue
<h3>MaximumValue</h3>
<p>
This field contains the maximum value which can be loaded onto the prepaid card. This value can be empty (or non-existent) for some backends and banks.</p>
<p>
Set this property with @ref AB_CellPhoneProduct_SetMaximumValue, 
get it with @ref AB_CellPhoneProduct_GetMaximumValue
</p>

@anchor AB_CELLPHONE_PRODUCT_Values
<h3>Values</h3>
<p>
This is the list of allowed values. This list might be empty!</p>
<p>
Set this property with @ref AB_CellPhoneProduct_SetValues, 
get it with @ref AB_CellPhoneProduct_GetValues
</p>

*/
#ifdef __cplusplus
extern "C" {
#endif

typedef struct AB_CELLPHONE_PRODUCT AB_CELLPHONE_PRODUCT;

#ifdef __cplusplus
} /* __cplusplus */
#endif

#include <gwenhywfar/db.h>
#include <gwenhywfar/misc.h>
#include <gwenhywfar/list2.h>
/* headers */
#include <gwenhywfar/types.h>
#include <aqbanking/error.h>
#include <aqbanking/value.h>

#ifdef __cplusplus
extern "C" {
#endif


GWEN_LIST_FUNCTION_LIB_DEFS(AB_CELLPHONE_PRODUCT, AB_CellPhoneProduct, AQBANKING_API)
AQBANKING_API AB_CELLPHONE_PRODUCT_LIST *AB_CellPhoneProduct_List_dup(const AB_CELLPHONE_PRODUCT_LIST *stl);

GWEN_LIST2_FUNCTION_LIB_DEFS(AB_CELLPHONE_PRODUCT, AB_CellPhoneProduct, AQBANKING_API)

/** Destroys all objects stored in the given LIST2 and the list itself
*/
AQBANKING_API void AB_CellPhoneProduct_List2_freeAll(AB_CELLPHONE_PRODUCT_LIST2 *stl);

/** Creates a new object.
*/
AQBANKING_API AB_CELLPHONE_PRODUCT *AB_CellPhoneProduct_new(void);
/** Creates an object from the data in the given GWEN_DB_NODE
*/
AQBANKING_API AB_CELLPHONE_PRODUCT *AB_CellPhoneProduct_fromDb(GWEN_DB_NODE *db);
/** Creates and returns a deep copy of thegiven object.
*/
AQBANKING_API AB_CELLPHONE_PRODUCT *AB_CellPhoneProduct_dup(const AB_CELLPHONE_PRODUCT*st);
/** Destroys the given object.
*/
AQBANKING_API void AB_CellPhoneProduct_free(AB_CELLPHONE_PRODUCT *st);
/** Increments the usage counter of the given object, so an additional free() is needed to destroy the object.
*/
AQBANKING_API void AB_CellPhoneProduct_Attach(AB_CELLPHONE_PRODUCT *st);
/** Reads data from a GWEN_DB.
*/
AQBANKING_API int AB_CellPhoneProduct_ReadDb(AB_CELLPHONE_PRODUCT *st, GWEN_DB_NODE *db);
/** Stores an object in the given GWEN_DB_NODE
*/
AQBANKING_API int AB_CellPhoneProduct_toDb(const AB_CELLPHONE_PRODUCT*st, GWEN_DB_NODE *db);
/** Returns 0 if this object has not been modified, !=0 otherwise
*/
AQBANKING_API int AB_CellPhoneProduct_IsModified(const AB_CELLPHONE_PRODUCT *st);
/** Sets the modified state of the given object
*/
AQBANKING_API void AB_CellPhoneProduct_SetModified(AB_CELLPHONE_PRODUCT *st, int i);

/**
* Returns the property @ref AB_CELLPHONE_PRODUCT_Id
*/
AQBANKING_API const char *AB_CellPhoneProduct_GetId(const AB_CELLPHONE_PRODUCT *el);
/**
* Set the property @ref AB_CELLPHONE_PRODUCT_Id
*/
AQBANKING_API void AB_CellPhoneProduct_SetId(AB_CELLPHONE_PRODUCT *el, const char *d);

/**
* Returns the property @ref AB_CELLPHONE_PRODUCT_ProviderName
*/
AQBANKING_API const char *AB_CellPhoneProduct_GetProviderName(const AB_CELLPHONE_PRODUCT *el);
/**
* Set the property @ref AB_CELLPHONE_PRODUCT_ProviderName
*/
AQBANKING_API void AB_CellPhoneProduct_SetProviderName(AB_CELLPHONE_PRODUCT *el, const char *d);

/**
* Returns the property @ref AB_CELLPHONE_PRODUCT_ProductName
*/
AQBANKING_API const char *AB_CellPhoneProduct_GetProductName(const AB_CELLPHONE_PRODUCT *el);
/**
* Set the property @ref AB_CELLPHONE_PRODUCT_ProductName
*/
AQBANKING_API void AB_CellPhoneProduct_SetProductName(AB_CELLPHONE_PRODUCT *el, const char *d);

/**
* Returns the property @ref AB_CELLPHONE_PRODUCT_AllowFreeValue
*/
AQBANKING_API int AB_CellPhoneProduct_GetAllowFreeValue(const AB_CELLPHONE_PRODUCT *el);
/**
* Set the property @ref AB_CELLPHONE_PRODUCT_AllowFreeValue
*/
AQBANKING_API void AB_CellPhoneProduct_SetAllowFreeValue(AB_CELLPHONE_PRODUCT *el, int d);

/**
* Returns the property @ref AB_CELLPHONE_PRODUCT_MinimumValue
*/
AQBANKING_API const AB_VALUE *AB_CellPhoneProduct_GetMinimumValue(const AB_CELLPHONE_PRODUCT *el);
/**
* Set the property @ref AB_CELLPHONE_PRODUCT_MinimumValue
*/
AQBANKING_API void AB_CellPhoneProduct_SetMinimumValue(AB_CELLPHONE_PRODUCT *el, const AB_VALUE *d);

/**
* Returns the property @ref AB_CELLPHONE_PRODUCT_MaximumValue
*/
AQBANKING_API const AB_VALUE *AB_CellPhoneProduct_GetMaximumValue(const AB_CELLPHONE_PRODUCT *el);
/**
* Set the property @ref AB_CELLPHONE_PRODUCT_MaximumValue
*/
AQBANKING_API void AB_CellPhoneProduct_SetMaximumValue(AB_CELLPHONE_PRODUCT *el, const AB_VALUE *d);

/**
* Returns the property @ref AB_CELLPHONE_PRODUCT_Values
*/
AQBANKING_API AB_VALUE_LIST *AB_CellPhoneProduct_GetValues(const AB_CELLPHONE_PRODUCT *el);
/**
* Set the property @ref AB_CELLPHONE_PRODUCT_Values
*/
AQBANKING_API void AB_CellPhoneProduct_SetValues(AB_CELLPHONE_PRODUCT *el, AB_VALUE_LIST *d);


#ifdef __cplusplus
} /* __cplusplus */
#endif


#endif /* CELLPHONEPRODUCT_H */
