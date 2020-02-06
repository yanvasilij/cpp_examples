
#include <stdio.h>
#include <hw/i2c.h>
#include <devctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

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

int main(int argc, char **argv)
{
    int i2ch;
    i2c_driver_info_t i2c_driver_info;
    i2c_speed_mode_t speed_mode;
    uint8_t send_str[2] = {'1', '2'};

    printf("i2c test started!\n");

    i2ch = open("/dev/i2c0", O_RDWR);



    while (1)
    {
        I2cWrite_(i2ch, 0x00, send_str, 2);
        sleep(1);
    }

    return 0;
}
