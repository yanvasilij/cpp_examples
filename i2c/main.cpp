
#include <stdio.h>
#include <hw/i2c.h>
#include <devctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>


static int I2cWriteMemory_(int fd, uint8_t DeviceId, uint8_t Address, uint32_t NbData, uint8_t MemoryAddress)
{
    i2c_send_t hdr;
    int status;
    iov_t sv[3];


    hdr.slave.addr = Address >> 1;
    hdr.slave.fmt = I2C_ADDRFMT_7BIT;
    hdr.len = NbData + sizeof(MemoryAddress);
    hdr.stop = 1;

    SETIOV(&sv[0], &hdr, sizeof(hdr));
    SETIOV(&sv[1], &MemoryAddress, sizeof(MemoryAddress));
    SETIOV(&sv[2], pBuffer, NbData);
    status = devctlv(fd, DCMD_I2C_SEND, 3, 0, sv, NULL, NULL);

    return status;
}

int main(int argc, char **argv)
{
    int i2ch;
    i2c_driver_info_t i2c_driver_info;
    i2c_speed_mode_t speed_mode;
    i2c_send_t send_data;
    char send_str[2] = {'1', '2'};

    printf("i2c test started!\n");

    i2ch = open("/dev/i2c0", O_RDWR);


    devctl(i2ch, DCMD_I2C_DRIVER_INFO, &i2c_driver_info, sizeof(i2c_driver_info_t), NULL);
    printf("speed_mode: %d addr_mode: %d\n", i2c_driver_info.speed_mode, i2c_driver_info.addr_mode);

    while (1)
    {
        devctl(i2ch, DCMD_I2C_SEND, send_str, 2, NULL);
        sleep(1);
    }

    return 0;
}
