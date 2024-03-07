/**
 * @file extra_extension.c
 * @author Nels Frazier (nfrazier@lynker.com)
 * @brief A sample BMI extension for "extra" functionality and/or data
 * @version 0.1
 * @date 2024-03-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "extra_extension.h"

char* bmi_extra_version()
{
    static char version[] = EXTRA_VERSION;
    return version;
}
