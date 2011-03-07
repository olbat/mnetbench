#ifndef _NETBENCH_TIME_H
#define _NETBENCH_TIME_H

#include <sys/time.h>

int timeval_subtract (struct timeval *result, struct timeval *x, struct timeval *y);

#endif
