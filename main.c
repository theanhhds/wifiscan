#include "wifiscan.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	while (1)
	{
		system(CMD);
		read_data();
		sleep(1);
	}
}
