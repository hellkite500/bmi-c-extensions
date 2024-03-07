/**
 * @file extra_extension.h
 * @author Nels Frazier (nfrazier@lynker.com)
 * @brief A sample BMI extension for "extra" functionality and/or data
 * @version 0.1
 * @date 2024-03-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef BMI_EXTRA_EXTENSION_H
#define BMI_EXTRA_EXTENSION_H
#include "bmi.h"

#define EXTRA_VERSION "v0.0.0"

/**
 * @brief Returns extension version C string
 * 
 * @return char* 
 */
char* bmi_extra_version();
extern int get_extra(struct Bmi*, int*);

/**
 * @brief Example extension intended to return a C string
 *        of "extra" information from a BMI model
 * 
 */
typedef struct Bmi_extra {
    /**
     * @brief Pointer to "extra" data this extension may use
     * 
     */
    void* data;
    
    /**
     * @brief BMI extension extra function
     * 
     * @param self The core BMI instance
     * 
     */
    int (*get_extra)(struct Bmi *self, int *extra);

    /**
     * @brief Return the extensions version C string
     * 
     */
    char* (*get_extension_version)();
} Bmi_extra;

#endif
