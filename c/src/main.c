//#define _XOPEN_SOURCE 500
//#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define AC_STATUS_FILE "/sys/class/power_supply/ACAD/online"
#define BATTERY_STATUS_FILE "/sys/class/power_supply/BAT1/capacity"
#define BATTERY_SHUTDOWN_LEVEL 15
#define CHECK_SECONDS 60

const char shutdowncmd[] = "/sbin/shutdown";
char * const shutdownarg[] = {"shutdown", "-h", "now", NULL};

/* void printusage() */
/* { */
/* 	puts("USAGE:\nbern-auto-shutdown [-n]\n\tthe \"-n\" option causes the process to not fork out ionto a daemon"); */
/* 	return; */
/* } */

int main(int argc, char *argv[])
{
	int fd;
	char capacity[4];
	ssize_t readretval;
	int batlevel;

	(void)argc;
	(void)argv;
	/* if ((!argc)||(argc > 2)||((argc == 2)&&(strncmp("-n", argc[1])))) */
	/* { */
	/* 	printusage(); */
	/* 	return 1; */
	/* } */

	/* if (argc != 2) */
	/* { */
		
	/* } */
	while (1)
	{
		fd = open(AC_STATUS_FILE, O_RDONLY);
		if (fd == -1)
		{
			perror("open ac file");
			return 1;
		}
		readretval = read(fd, capacity, 1);
		if (!readretval)
		{
			puts("failed to read frm ac status file");
			return 1;
		}
		close(fd);
		if (capacity[0] == '0')
		{
			fd = open(BATTERY_STATUS_FILE, O_RDONLY);
			if (fd == -1)
			{
				perror("open capacity file");
				return 1;
			}
			readretval = read(fd, capacity, 3);
			if (readretval == -1)
			{
				perror("read");
				return 1;
			}
			close(fd);
			capacity[readretval] = 0;
			batlevel = atoi(capacity);
			//printf("battery level %i%%\n", batlevel);
			if (batlevel < BATTERY_SHUTDOWN_LEVEL)
			{
				execv(shutdowncmd, shutdownarg);
			}
		}
		sleep(CHECK_SECONDS);
	}

}
