/**
 * @file bmi_extensions.h
 * @author Nels Frazier (nfrazier@lynker.com)
 * @brief Managed BMI extensions interface.
 * @version 0.1
 * @date 2024-03-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/*
 * These are BMI exentension functions developed to support the NGen modeling framework
 */

#ifndef BMI_EXTENSIONS_H
#define BMI_EXTENSIONS_H

#if defined(__cplusplus)
extern "C" {
#endif

#define BMI_MAX_LOCATION_NAME (2048) //Custom string buffer length

#ifndef NULL
#define NULL (0)
#endif

#include "bmi.h"
#include "extra_extension.h"

/**
 * Experimental generic extension interface
 **/

/**
 * @brief Enumeration of extensions
 * 
 */
enum ExtensionType{ NONE, EXTRA};

/**
 * @brief A *private* extension struct which will hold the extension
 *        struct/object in use by an @ref Extension
 * 
 */
typedef union _extension{
    Bmi_extra extra;
} _extension;

/**
 * @brief Public Extension struct used for type erasure of extensions
 * 
 */
typedef struct Extension{
    enum ExtensionType type;
    _extension extension;
    void* ext;
} Extension;

/**
 * @brief Create an extension struct by type
 * 
 * @param extension Pointer to an Extension struct to populate
 * @param type Supported extenion type to create
 * @return void* Type erased pointer to the correct extension structure based on @p type
 */
extern void* create_extension(Extension* extension, enum ExtensionType type);

/**
 * @brief Get the extension object
 * 
 * @param extension Pointer to Extension struct to retrieve the underlying _extension stuct from
 * @return void* Type erased pointer to the correct extension structure based on @p Extension.type
 */
extern void* get_extension(Extension* extension);

/**
 * @brief Currently un-implemented, but could be used by external
 *        components (frameworks) to associate known extensions
 *        with a BMI model instance.
 * 
 * @param extension 
 * @return int 
 */
extern int register_bmi_extension(Extension* extension); //Method 1

/*
 * Method 2
 */
extern int register_bmi_extension2(Extension* extension);
#if defined(__cplusplus)
}
#endif

#endif
