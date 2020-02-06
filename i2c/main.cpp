
#include <iostream>
#include <memory>

#include <hw/inout.h>
#include <stdio.h>

#include <stdlib.h>
#include <stdio.h>
#include <hw/inout.h>
#include <sys/neutrino.h>
#include <stdint.h>
#include <sys/mman.h>

typedef unsigned char u8;

/* Standard definition with offset 1 */
union frame {
	struct {
	    u8	 canid1;
	    u8	 canid2;
	    u8	 canid3;
	    u8	 canid4;
	    u8   canxdata[8];
	} extframe;
	struct {
	    u8	 canid1;
	    u8	 canid2;
	    u8   candata[8];
	} stdframe;
};


typedef struct canregs {
	u8	canmode;		/* 0 */
	u8	cancmd;
	u8	canstat;
	u8	canirq;
	u8	canirq_enable;
	u8	reserved1;		/* 5 */
	u8	cantim0;
	u8	cantim1;
	u8	canoutc;
	u8	cantest;
	u8	reserved2;		/* 10 */
	u8	arbitrationlost;	/* read only */
	u8	errorcode;		/* read only */
	u8	errorwarninglimit;
	u8	rxerror;
	u8	txerror;		/* 15 */
	u8	frameinfo;
	union   frame frame;
	u8	reserved3;
	u8	canrxbufferadr		/* 30 */;
	u8	canclk;
} __attribute__((packed)) canregs_t;


int main(int argc, char **argv)
{
	//if( (can_base_addr = (canregs_t *) mmap_device_io(31, base_addr )) == (canregs_t *) MAP_DEVICE_FAILED  )
	//{
	//		perror("MAP_DEVICE_FAILED");
	//		exit(EXIT_FAILURE);
	//}
	//printf("Base address 0x%04x\n", (unsigned int) can_base_addr);
	ThreadCtl( _NTO_TCTL_IO, 0 );

	unsigned char preg = in8( (0xC20) );
 	printf("canmode: 0x%02x\n",  preg);

	preg = in8( (0xC20) + 1);
 	printf("canmode: 0x%02x\n",  preg);

 	preg = in8( (0xC20) + 2);
 	printf("canmode: 0x%02x\n",  preg);

	preg = in8( (0xC20) + 3);
 	printf("canmode: 0x%02x\n",  preg);

	return 0;
}
