#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

#define SERIAL_PORT_PATH        "/dev/ttyAMA0"

struct termios g_tty;
int g_fd;

typedef uint8_t             UINT8;
typedef uint32_t            UINT32;

static int file_open_and_get_descriptor(const char *fname) {
    int fd;

    fd = open(fname, O_RDWR | O_NONBLOCK);
    if(fd < 0) {
        printf("Could not open file %s...%d\r\n",fname,fd);
    }
    return fd;
}

static void open_serial_port(void) {
    g_fd = file_open_and_get_descriptor(SERIAL_PORT_PATH);
    if(g_fd < 0) {
        printf("Something went wrong while opening the port...\r\n");
        exit(EXIT_FAILURE);
    }
}

static void configure_serial_port(void) {
    if(tcgetattr(g_fd, &g_tty)) {
        printf("Something went wrong while getting port attributes...\r\n");
        exit(EXIT_FAILURE);
    }

    cfsetispeed(&g_tty,B115200);
    cfsetospeed(&g_tty,B115200);

    cfmakeraw(&g_tty);

    if(tcsetattr(g_fd,TCSANOW,&g_tty)) {
        printf("Something went wrong while setting port attributes...\r\n");
        exit(EXIT_FAILURE);
    }
}

static void close_serial_port(void) {
    file_close(g_fd);
}

static int file_write_data(int fd, UINT8 *TxBuffer, UINT8 txLenght) {
    return write(fd,TxBuffer,txLenght);
}

static int file_read_data(int fd, UINT8 *rxBuffer, UINT8 rxBufferSize) {
    return read(fd,rxBuffer,rxBufferSize);
}

static void perform_write(int g_fd, UINT8 *TxBuffer, UINT8 txLenght) {
    file_write_data(g_fd,TxBuffer,txLenght);
    sleep(1);
    printf("\r\nThe data was send!\r\n");
}

static void perform_read(int g_fd, UINT8 *rxBuffer, UINT8 rxBufferSize) {
    file_read_data(g_fd,rxBuffer,rxBufferSize);
    sleep(1);

    printf("\r\nThe data loopback was successful!\r\n");
}



bool
SerialDevice_Open(const char   *comPort,
                  UINT32        baudRate,
                  int           dataBits,
                  UINT8         parity);  
{
    open_serial_port();
    configure_serial_port();
} 

bool
SerialDevice_Close()
{
    close_serial_port();
}

int
SerialDevice_SendData(UINT8 *TxBuffer, UINT8 txLength)
{ 
    perform_write();
}

int
SerialDevice_ReadData(UINT8 *rxBuffer, int rxBufferSize)
{
    perform_read();
}