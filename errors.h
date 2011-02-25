#ifndef _ERRORS_H
#define _ERRORS_H

#include <stdio.h>

#define ERR_SET_MSG(STR,MSG) \
snprintf(STR,sizeof(STR),"%s (%s:%d)",MSG,__FILE__,__LINE__);

#endif
