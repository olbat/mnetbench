#ifndef _NETBENCH_TEST_TYPE_H
#define _NETBENCH_TEST_TYPE_H

enum netbench_test_type
{
	NETBENCH_TEST_LATENCY,
	NETBENCH_TEST_BANDWIDTH,
	NETBENCH_TEST_NONE
};

char *netbench_test_type_name(enum netbench_test_type type);

#endif
