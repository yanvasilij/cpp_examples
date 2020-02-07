
#include <stdio.h>
#include <hw/i2c.h>
#include <devctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

int  I2cWrite_(int fd, uint8_t Address , uint8_t *pBuffer, uint32_t NbData)
{
    i2c_send_t hdr;
    iov_t sv[2];
    int status;

    hdr.slave.addr = Address >> 1;
    hdr.slave.fmt = I2C_ADDRFMT_7BIT;
    hdr.len = NbData;
    hdr.stop = 1;

    SETIOV(&sv[0], &hdr, sizeof(hdr));
    SETIOV(&sv[1], pBuffer, NbData);
    status = devctlv(fd, DCMD_I2C_SEND, 2, 0, sv, NULL, NULL);

    return status;
}

void testI2c (int fd)
{
    struct dataBuf {
        i2c_send_t header;
        unsigned char data[256];
    };

    struct dataBuf dev_data;

    memset(dev_data.data, 0, sizeof(dev_data.data));
    dev_data.header.slave.addr = 0x40; // address of factory config information
    dev_data.header.slave.fmt = I2C_ADDRFMT_7BIT;
    dev_data.header.len = 2; //  1
    dev_data.header.stop = 1;
    dev_data.data[0] = 0x20; //register address
    dev_data.data[1] = 143; //the data to write

    devctl(fd, DCMD_I2C_SEND, &dev_data, sizeof(dev_data), NULL );
}

int main(int argc, char **argv)
{
    int i2ch;
    i2c_driver_info_t i2c_driver_info;
    i2c_speed_mode_t speed_mode = I2C_SPEED_STANDARD;
    uint8_t send_str[2] = {'1', '2'};

    printf("i2c test started!\n");


    i2ch = open("/dev/i2c0", O_RDWR);

    devctl(i2ch, DCMD_I2C_SET_BUS_SPEED, &speed_mode, sizeof(i2c_speed_mode_t), NULL );

    devctl(i2ch, DCMD_I2C_DRIVER_INFO, &i2c_driver_info, sizeof(i2c_driver_info), NULL );
    printf("addr_mode %d speed_mode %d\n", i2c_driver_info.addr_mode, i2c_driver_info.speed_mode);


    while (1)
    {
        I2cWrite_(i2ch, 0x00, send_str, 2);
        //testI2c(i2ch);
        devctl(i2ch, DCMD_I2C_DRIVER_INFO, &i2c_driver_info, sizeof(i2c_driver_info), NULL );
        printf("addr_mode %d speed_mode %d\n", i2c_driver_info.addr_mode, i2c_driver_info.speed_mode);
        sleep(1);
    }

    return 0;
}
