#include <string.h>
#include <stdio.h>
void version_message_helper(char* name, char* expected, char* version, char* buff)
{
    strcpy(buff, name);
    char* msg = strcat(buff, " version returned ");
    msg = strcat(buff, version);
    msg = strcat(buff, ", expected ");
    msg = strcat(buff, expected );
}