#ifndef SERIAL_DEVICE_H
#define SERIAL_DEVICE_H


    #include <stdint.h>
    #include <stdbool.h>

    typedef uint8_t             UINT8;
    typedef uint32_t            UINT32;

    typedef enum {
        B0,B9600,B19200,B115200
    } baudrate_t;

    typedef enum {MODEM_LW,GPS,HPM,DEBUG1,DEBUG2} serial_t;

    /**
     * Initializes the library to work with specified serial port
     * @param comPort
     * @param baudRate
     * @param dataBits
     * @param parity
     * @return True on success
     */
    bool
    SerialDevice_Open(const char   *comPort,
                      baudrate_t    baudRate,   //115200, siempre.
                      int           dataBits,   //8, siempre.
                      UINT8         parity);    //Ninguna, siempre.

    /**
     * Close
     *
     * @Summary
     * close serial device
     *
     * @return
     * True on sucess
     */
    bool
    SerialDevice_Close();

    /**
     * SendByte
     * @brief send single byte
     * @param txByte
     * @return Bytes sent or -1 if communication error
     */
    int
    SerialDevice_SendByte(UINT8 txByte);

    /**
     * SendData
     * @brief: send data
     */
    int
    SerialDevice_SendData(UINT8    *txBuffer,
                          UINT8     txLength);

    /**
     * ReadData
     * @brief: read data
     */
    int
    SerialDevice_ReadData(UINT8    *rxBuffer,
                          int       rxBufferSize);


#endif // SERIAL_DEVICE_H
