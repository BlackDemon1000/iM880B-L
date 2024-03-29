/*
 * File:        WiMOD_LoRaWAN_API.h
 * Abstract:    API Layer of LoRaWAN Host Controller Interface
 * Version:     0.1
 * Date:        18.05.2016
 * Disclaimer:  This example code is provided by IMST GmbH on an "AS IS"
 *              basis without any warranties.
 *
 * Modified on 22 de agosto de 2017, 07:03 PM
 * Based on IMST Document: WiMOD LoraWAN HCI PDF ver 1.13
 */

#ifndef WIMOD_LORAWAN_API_H
#define WIMOD_LORAWAN_API_H

#ifdef	__cplusplus
extern "C" {
#endif

    //--------------------------------------------------------------------------
    //  Include Files
    //--------------------------------------------------------------------------

    #include <stdint.h>
    #include <stdbool.h>
    #include "hci_stack.h"

    //--------------------------------------------------------------------------
    //  General Declarations
    //--------------------------------------------------------------------------

    typedef uint8_t     UINT8;
    typedef uint16_t    UINT16;
    typedef uint32_t    UINT32;

    // helper struct for ID -> string conversion
    typedef struct
    {
        int         ID;
        const char *String;
    }TIDString;

    typedef volatile enum {NET_IDLE,CONNECTING,ACTIVE} LWstat;
    typedef volatile bool flag_t;

    ////Endpoint (SAP) Identifier
    #define DEVMGMT_ID  DEVMGMT_SAP_ID  //WiMOD LoraWAN HCI PDF ver 1.13
    #define DEVMGMT_SAP_ID  0x01
    #define LORAWAN_ID  LORAWAN_SAP_ID  //WiMOD LoraWAN HCI PDF ver 1.13
    #define LORAWAN_SAP_ID  0x10
    ////Device Management SAP Message Identifier:

    // Status Identifier
    #define DEVMGMT_STATUS_OK                   0x00
    #define DEVMGMT_STATUS_ERROR                0x01
    #define DEVMGMT_STATUS_CMD_NOT_SUPPORTED    0x02
    #define DEVMGMT_STATUS_WRONG_PARAMETER      0x03
    #define DEVMGMT_STATUS_WRONG_DEVICE_MODE    0x04

    // Message Identifier                         | value | PayloadOctets | WiMOD LoraWAN HCI PDF version
    #define DEVMGMT_MSG_PING_REQ                    0x01    //0
    #define DEVMGMT_MSG_PING_RSP                    0x02    //1

    #define DEVMGMT_MSG_RESET_REQ                   0x07    //0
    #define DEVMGMT_MSG_RESET_RSP                   0x08    //1

    #define DEVMGMT_MSG_GET_DEVICE_INFO_REQ         0x03    //0
    #define DEVMGMT_MSG_GET_DEVICE_INFO_RSP         0x04    //10

    #define DEVMGMT_MSG_GET_FW_INFO_REQ             0x05    //0                     1.13
    #define DEVMGMT_MSG_GET_FW_VERSION_REQ          DEVMGMT_MSG_GET_FW_INFO_REQ //DEPRECATED
    #define DEVMGMT_MSG_GET_FW_INFO_RSP             0x06    //1+n                   1.13
    #define DEVMGMT_MSG_GET_FW_VERSION_RSP          DEVMGMT_MSG_GET_FW_INFO_RSP //DEPRECATED

    #define DEVMGMT_MSG_GET_DEVICE_STATUS_REQ       0x17    //0
    #define DEVMGMT_MSG_GET_DEVICE_STATUS_RSP       0x18    //60

    #define DEVMGMT_MSG_GET_RTC_REQ                 0x0F    //0
    #define DEVMGMT_MSG_GET_RTC_RSP                 0x10    //5
    #define DEVMGMT_MSG_SET_RTC_REQ                 0x0D    //4
    #define DEVMGMT_MSG_SET_RTC_RSP                 0x0E    //1

    #define DEVMGMT_MSG_SET_RTC_ALARM_REQ           0x31    //4
    #define DEVMGMT_MSG_SET_RTC_ALARM_RSP           0x32    //1
    #define DEVMGMT_MSG_RTC_ALARM_IND               0x38    //1
    #define DEVMGMT_MSG_GET_RTC_ALARM_REQ           0x35    //0
    #define DEVMGMT_MSG_GET_RTC_ALARM_RSP           0x36    //6
    #define DEVMGMT_MSG_CLEAR_RTC_ALARM_REQ         0x33    //0
    #define DEVMGMT_MSG_CLEAR_RTC_ALARM_RSP         0x34    //1

    #define DEVMGMT_MSG_GET_OPMODE_REQ              0x0B    //0
    #define DEVMGMT_MSG_GET_OPMODE_RSP              0x0C    //2
    #define DEVMGMT_MSG_SET_OPMODE_REQ              0x09    //1
    #define DEVMGMT_MSG_SET_OPMODE_RSP              0x0A    //1

    ////LoRaWAN SAP Message Identifier:

    // Status Identifier
    #define LORAWAN_STATUS_OK                       0x00
    #define LORAWAN_STATUS_ERROR                    0x01
    #define LORAWAN_STATUS_CMD_NOT_SUPPORTED        0x02
    #define LORAWAN_STATUS_WRONG_PARAMETER          0x03
    #define LORAWAN_STATUS_WRONG_DEVICE_MODE        0x04
    #define LORAWAN_STATUS_DEVICE_NOT_ACTIVATED     0x05                            //1.22
    #define LORAWAN_STATUS_NOT_ACTIVATED            LORAWAN_STATUS_DEVICE_NOT_ACTIVATED //DEPRECATED
    #define LORAWAN_STATUS_BUSY                     0x06
    #define LORAWAN_STATUS_QUEUE_FULL               0x07
    #define LORAWAN_STATUS_LENGTH_ERROR             0x08
    #define LORAWAN_STATUS_NO_FACTORY_SETTINGS      0x09
    #define LORAWAN_STATUS_CHANNEL_BLOCKED          0x0A                            //1.22
    #define LORAWAN_STATUS_CHANNEL_BLOCKED_BY_DC    LORAWAN_STATUS_CHANNEL_BLOCKED  //DEPRECATED
    #define LORAWAN_STATUS_CHANNEL_NOT_AVAILABLE    0x0B

    // Message Identifier                         | value | PayloadOctets | WiMOD LoraWAN HCI PDF version
    #define LORAWAN_MSG_ACTIVATE_DEVICE_REQ         0x01    //36
    #define LORAWAN_MSG_ACTIVATE_DEVICE_RSP         0x02    //1
    #define LORAWAN_MSG_REACTIVATE_DEVICE_REQ       0x1D    //0
    #define LORAWAN_MSG_REACTIVATE_DEVICE_RSP       0x1E    //5
    #define LORAWAN_MSG_DEACTIVATE_DEVICE_REQ       0x21    //0
    #define LORAWAN_MSG_DEACTIVATE_DEVICE_RSP       0x22    //1

    #define LORAWAN_MSG_SET_JOIN_PARAM_REQ          0x05    //24
    #define LORAWAN_MSG_SET_JOIN_PARAM_RSP          0x06    //1
    #define LORAWAN_MSG_JOIN_NETWORK_REQ            0x09    //0
    #define LORAWAN_MSG_JOIN_NETWORK_RSP            0x0A    //1
    #define LORAWAN_MSG_JOIN_NETWORK_TX_IND         0x0B    //1 (+3)                1.13
    #define LORAWAN_MSG_JOIN_TRANSMIT_IND           LORAWAN_MSG_JOIN_NETWORK_TX_IND //DEPRECATED
    #define LORAWAN_MSG_JOIN_NETWORK_IND            0x0C    //1 (+4 or +9)

    #define LORAWAN_MSG_SEND_UDATA_REQ              0x0D    //1+n
    #define LORAWAN_MSG_SEND_UDATA_RSP              0x0E    //1 (+4)
    #define LORAWAN_MSG_SEND_UDATA_TX_IND           0x0F    //1 (+2)                1.13
    #define LORAWAN_MSG_SEND_UDATA_IND              LORAWAN_MSG_SEND_UDATA_TX_IND   //DEPRECATED
    #define LORAWAN_MSG_RECV_UDATA_IND              0x10    //1+n (+5)

    #define LORAWAN_MSG_SEND_CDATA_REQ              0x11    //1+n
    #define LORAWAN_MSG_SEND_CDATA_RSP              0x12    //1 (+4)
    #define LORAWAN_MSG_SEND_CDATA_TX_IND           0x13    //1 (+3)                1.13
    #define LORAWAN_MSG_SEND_CDATA_IND              LORAWAN_MSG_SEND_CDATA_TX_IND   //DEPRECATED
    #define LORAWAN_MSG_RECV_CDATA_IND              0x14    //1+n (+5)

    #define LORAWAN_MSG_RECV_ACK_IND                0x15    //1(+5) (OBSOLETE - search in PDF for details)
    #define LORAWAN_MSG_RECV_NO_DATA_IND            0x16    //1                     1.13
    #define LORAWAN_MSG_RECV_NODATA_IND             LORAWAN_MSG_RECV_NO_DATA_IND    //DEPRECATED

    #define LORAWAN_MSG_SET_RSTACK_CONFIG_REQ       0x19    //6
    #define LORAWAN_MSG_SET_RSTACK_CONFIG_RSP       0x1A    //1
    #define LORAWAN_MSG_GET_RSTACK_CONFIG_REQ       0x1B    //0
    #define LORAWAN_MSG_GET_RSTACK_CONFIG_RSP       0x1C    //7

    #define LORAWAN_MSG_GET_DEVICE_EUI_REQ          0x27    //0
    #define LORAWAN_MSG_GET_DEVICE_EUI_RSP          0x28    //9
    #define LORAWAN_MSG_SET_DEVICE_EUI_REQ          0x25    //8
    #define LORAWAN_MSG_SET_DEVICE_EUI_RSP          0x26    //1

    #define LORAWAN_MSG_GET_CUSTOM_CFG_REQ          0x33    //0
    #define LORAWAN_MSG_GET_CUSTOM_CFG_RSP          0x34    //2
    #define LORAWAN_MSG_SET_CUSTOM_CFG_REQ          0x31    //1
    #define LORAWAN_MSG_SET_CUSTOM_CFG_RSP          0x32    //1

    #define LORAWAN_MSG_FACTORY_RESET_REQ           0x23    //0
    #define LORAWAN_MSG_FACTORY_RESET_RSP           0x24    //1

    #define LORAWAN_MSG_GET_NWK_STATUS_REQ          0x29    //0
    #define LORAWAN_MSG_GET_NWK_STATUS_RSP          0x2A    //2

    #define LORAWAN_MSG_SEND_MAC_CMD_REQ            0x2B    //1+n
    #define LORAWAN_MSG_SEND_MAC_CMD_RSP            0x2C    //1
    #define LORAWAN_MSG_RECV_MAC_CMD_IND            0x2D    //1+n (+5)

    #define LORAWAN_MSG_GET_SUPPORTED_BANDS_REQ     0x35    //0                     1.22
    #define LORAWAN_MSG_GET_SUPPORTED_BANDS_RSP     0x36    //1+2*(n+1)             1.22
    #define LORAWAN_MSG_GET_LINKADRREQ_CONFIG_REQ   0x3D    //0                     1.22
    #define LORAWAN_MSG_GET_LINKADRREQ_CONFIG_RSP   0x3E    //2                     1.22
    #define LORAWAN_MSG_SET_LINKADRREQ_CONFIG_REQ   0x3B    //1                     1.22
    #define LORAWAN_MSG_SET_LINKADRREQ_CONFIG_RSP   0x3C    //1 (+1)                1.22

    //--------------------------------------------------------------------------
    //  Function Prototypes
    //--------------------------------------------------------------------------

    /**
     * Init
     * @brief: initializes LoRaWAN Link, including network authentication
     * @param transmitter: Function that writes to iM88xx (Serial Transmitter)
     * @return true on success
     */
    bool
    WiMOD_LoRaWAN_Init(serialTransmitHandler transmitter, LWstat *LWstatus);

    void
    WiMOD_LoRaWAN_nextRequest(flag_t *responseCatched);

    /**
     * Ping
     * @brief: ping device
     */
    int
    WiMOD_LoRaWAN_SendPing();

    /**
     * GetFirmwareVersion
     * @brief: get firmware version
     */
    int
    WiMOD_LoRaWAN_GetFirmwareVersion();

    /**
     * JoinNetworkRequest
     * @brief: send join radio message
     */
    int
    WiMOD_LoRaWAN_JoinNetworkRequest();

    /**
     * SendURadioData
     * @brief: send unconfirmed radio message
     */
    int
    WiMOD_LoRaWAN_SendURadioData(UINT8 port, UINT8 *data, UINT8 length);

    /**
     * SendCRadioData
     * @brief: send confirmed radio message
     */
    int
    WiMOD_LoRaWAN_SendCRadioData(UINT8 port, UINT8 *data, UINT8 length);

    /**
     * Process
     * @brief: handle receiver process
     */
    void
    WiMOD_LoRaWAN_Process();

    /**
     * Request the time from RTC on module
     */
    int
    WiMOD_LoRaWAN_GetTime();

    /**
     * Request the status of the device on the LoRaWAN Network
     */
    int
    WiMOD_LoRaWAN_GetNetworkStatus();

#ifdef	__cplusplus
}
#endif

#endif // WIMOD_LORAWAN_API_H

//------------------------------------------------------------------------------
// end of file
//-------