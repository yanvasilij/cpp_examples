
#include <stdio.h>
#include <hw/i2c.h>
#include <devctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

#include <pthread.h>
#include <iostream>
#include <sys/neutrino.h>


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <hw/i2c.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
i2c_addr_t slave;

int  i2c_write (int fd, uint8_t Address , uint8_t *pBuffer, uint32_t NbData)
{

    int status, i;
    struct {

        i2c_send_t hdr; /* Message header */
        uint8_t bytes[8]; /* Transmit buffer with (optional) extra space */

    } omsg;

    struct {

        i2c_recv_t hdr; /* Message header */
        uint8_t bytes[16]; /* Receive buffer */

    } imsg;

    omsg.hdr.slave = slave;
    omsg.hdr.len = NbData;
    omsg.hdr.stop = 1;
    omsg.bytes[0] = pBuffer[0];
    omsg.bytes[1] = pBuffer[1];

//    for (i=1; i<NbData; i++)
//        omsg.bytes[i+1] = pBuffer[i];

    status = devctl(fd, DCMD_I2C_SEND, &omsg,
                    sizeof(omsg.hdr) + omsg.hdr.len, NULL);

//   usleep(20000);
//   for (i = 0; i< 16; i++)
//       imsg.bytes[i] = 0x0;
//
//   imsg.hdr.slave = slave;
//   imsg.hdr.len = NbData;
//   imsg.hdr.stop = 0;
//   for (i=0; i<NbData; i++)
//       imsg.bytes[i] = pBuffer[i];
//
//   status = devctl(fd, DCMD_I2C_SEND, &imsg,
//                   sizeof(imsg.hdr) + imsg.hdr.len, NULL);
    if (status != 0)
    {
        printf ("error %s\n", strerror(status));
        return -1;
    }

    return 0;
}

int hdc1000_i2c_read (int fd, uint8_t addr, uint8_t* data, int len)
{

    int status, i;
    struct {

        i2c_send_t hdr; /* Message header */
        uint8_t bytes[8]; /* Transmit buffer with (optional) extra space */

    } omsg;

    struct {

        i2c_recv_t hdr; /* Message header */
        uint8_t bytes[16]; /* Receive buffer */

    } imsg;

    omsg.hdr.slave = slave;
    omsg.hdr.len = 1;
    omsg.hdr.stop = 0;
    omsg.bytes[0] = addr;
    status = devctl(fd, DCMD_I2C_SEND, &omsg,
                    sizeof(omsg.hdr) + omsg.hdr.len, NULL);

    usleep(20000);
    for (i = 0; i< 16; i++)
        imsg.bytes[i] = 0x0;

    imsg.hdr.slave = slave;
    imsg.hdr.len = len;
    imsg.hdr.stop = 1;
    status = devctl(fd, DCMD_I2C_RECV, &imsg,
                    sizeof(imsg.hdr) + imsg.hdr.len, NULL);
    if (status != 0)
    {
        printf("read error\n");
        return -1;
    }


    if(data != NULL)
    {
        for (i = 0; i< len; i++)
            data[i] = imsg.bytes[i];
    }

    return 0;

}

int main(int argc, char **argv)
{
    int i2ch;
    i2c_driver_info_t i2c_driver_info;
    i2c_speed_mode_t speed_mode;
    uint8_t send_str[4] = {0x00, 0x00, 0x00, 0x00}, rx_buf[4];

    ThreadCtl( _NTO_TCTL_IO, 0 );

    printf("i2c test started!\n");

    i2ch = open("/dev/i2c2", O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);

    slave.addr = 0x3C;
    slave.fmt = I2C_ADDRFMT_7BIT;
    devctl(i2ch, DCMD_I2C_SET_SLAVE_ADDR, &slave, sizeof(slave), NULL);

    hdc1000_i2c_read(i2ch, 0x00, send_str, 3);

    printf("read value: 0x%x 0x%x 0x%x\n", send_str[0], send_str[1], send_str[2]);

    send_str[0] = 0x03;
    i2c_write(i2ch, 0x20, send_str, 1);

    hdc1000_i2c_read(i2ch, 0x20, send_str, 1);
    printf("read value: 0x%x\n", send_str[0]);

    send_str[0] = 0x01;
    i2c_write(i2ch, 0x0A, send_str, 1);

    hdc1000_i2c_read(i2ch, 0x0A, send_str, 1);
    printf("read value: 0x%x\n", send_str[0]);

    //   send_str[0] = 0x0A;
 //   send_str[1] = 0xFF;
 //   i2c_write(i2ch, 0x20, send_str, 2);

 //   while (1)
 //   {
 //   	send_str[1]++;
 //   	i2c_write(i2ch, 0x20, send_str, 2);
 //   	usleep(500000);

 //       hdc1000_i2c_read(i2ch, 0x0A, rx_buf, 1);
 //       printf("rx buf: 0x%x\n", rx_buf[0]);
 //   }

//    while (1)
//    {
//        //i2c_write(i2ch, 0x00, send_str, 2);
//        hdc1000_i2c_read(i2ch, 0x40, send_str, 2);
//
//        //send_str[0] = 0x0A;
//        //send_str[1] = 0xFF;
//        //i2c_write(i2ch, 0x20, send_str, 2);
//        //sleep(1);
//        //send_str[0] = 0x0A;
//        //send_str[1] = 0x00;
//        //i2c_write(i2ch, 0x20, send_str, 2);
//        sleep(1);
//    }

    return 0;
}
