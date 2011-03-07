#include <stdio.h>

#include "netbench_printer_tool.h"


char *netbench_printer_tool_bandwidth(
	char *buff,
	unsigned int buffsize,
	double bw
)
{
	static char bytechar[] = { ' ', 'K', 'M', 'G' };
	unsigned int i;

	i = 0;
	while (bw > 1)
	{
		bw /= 1024;
		i++;
	}
	snprintf(buff,buffsize,"%.2f%cB/s",bw*1024,bytechar[i-1]);
	return buff;
}
