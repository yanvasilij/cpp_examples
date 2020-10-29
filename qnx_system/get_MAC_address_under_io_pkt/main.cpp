#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if_dl.h>
#include <ifaddrs.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv)
{
	struct ifaddrs *ifaphead;
	unsigned char * if_mac;
	int found = 0;
	struct ifaddrs *ifap;
	struct sockaddr_dl *sdl = NULL;

	if (argc < 2)
	{
		fprintf(stderr,"usage:\n");
		fprintf(stderr,"\t %s <interface name>\n",argv[0]);
		exit(1);
	}

	if (getifaddrs(&ifaphead) != 0)
	{
		perror("get_if_name: getifaddrs() failed");
		exit(1);
	}

	for (ifap = ifaphead; ifap && !found; ifap = ifap->ifa_next)
	{
		if ((ifap->ifa_addr->sa_family == AF_LINK))
		{
			if (strlen(ifap->ifa_name) == strlen(argv[1]))
				if (strcmp(ifap->ifa_name,argv[1]) == 0)
				{
					found = 1;
					sdl = (struct sockaddr_dl *)ifap->ifa_addr;
					if (sdl)
					{
						/* I was returning this from a function before converting
						 * this snippet, which is why I make a copy here on the heap */
						if_mac = (unsigned char*)malloc(sdl->sdl_alen);
						memcpy(if_mac, LLADDR(sdl), sdl->sdl_alen);
					}
				}
		}
	}
	if (!found)
	{
		fprintf (stderr,"Can't find interface %s.\n",argv[1]);
		if(ifaphead)
			freeifaddrs(ifaphead);
		exit(1);
	}

	fprintf (stdout, "%02X%02X%02X%02X%02X%02X\n",
			if_mac[0] , if_mac[1] , if_mac[2] ,
			if_mac[3] , if_mac[4] , if_mac[5] );

	if(ifaphead)
		freeifaddrs(ifaphead);

	exit(0);
}
