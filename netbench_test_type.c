#include "netbench_test_type.h"

char *netbench_test_type_name(enum netbench_test_type type)
{
	char *ret;

	switch (type)
	{
	case NETBENCH_TEST_LATENCY:
		ret = "Latency";
		break;
	case NETBENCH_TEST_BANDWIDTH:
		ret = "Bandwidth";
		break;
	default:
		ret = "Unknown";
		break;
	}

	return ret;
}
