#include "bmi_extensions.h"

void* create_extension(Extension* extension, enum ExtensionType type)
{
    extension->type = type;
    if(type == EXTRA)
    {
        //Always include the version function definition, maintained by the
        //extension lib
        extension->extension.extra.get_extension_version = bmi_extra_version;
        /*
        * Method 5, use the linker to discover functions, makes registration
        * unrequired.  
        * 
        * TODO
        * Think about what this does in dynamic loading scenarios...
        * 
        * Requires functions NOT to access any global state, and only use state in passed
        * parameters!!! 
        * (and what about thread safety??? probably even worse with the BMI* arg,
        * but similar argument with global state/context likely applies)
        */
        extension->extension.extra.get_extra = get_extra;
        return (void*) &extension->extension.extra;
    }
    extension->type = NONE;
    return NULL;
}

void* get_extension(Extension* extension)
{
    if(extension->type == EXTRA)
    {
        return (void*) &extension->extension.extra;
    }
    return NULL;
}