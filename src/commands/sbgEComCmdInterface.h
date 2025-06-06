/*!
 * \file            sbgEComCmdInterface.h
 * \ingroup         commands
 * \author          SBG Systems
 * \date            11 June 2014
 *
 * \brief           Commands used to configure device serial, CAN and Ethernet interfaces.
 *
 * \copyright       Copyright (C) 2007-2024, SBG Systems SAS. All rights reserved.
 * \beginlicense    The MIT license
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * \endlicense
 */

#ifndef SBG_ECOM_CMD_INTERFACE_H
#define SBG_ECOM_CMD_INTERFACE_H

// sbgCommonLib headers
#include <sbgCommon.h>

// Project headers
#include <sbgECom.h>

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------//
//- Serial interface definitions                                       -//
//----------------------------------------------------------------------//

/*!
 * List of serial interfaces available.
 */
typedef enum _SbgEComPortId
{
    SBG_ECOM_IF_COM_A = 0,          /*!< Main communication interface. Full duplex. */
    SBG_ECOM_IF_COM_B = 1,          /*!< Auxiliary input interface for RTCM. */
    SBG_ECOM_IF_COM_C = 2,          /*!< Auxiliary communication interface. Full duplex. */
    SBG_ECOM_IF_COM_D = 3,          /*!< Auxiliary input interface. */
    SBG_ECOM_IF_COM_E = 4,          /*!< Auxiliary output interface. */

    SBG_ECOM_IF_ETH_0 = 10,         /*!< Ethernet interface 0. */
    SBG_ECOM_IF_ETH_1 = 11,         /*!< Ethernet interface 1. */
    SBG_ECOM_IF_ETH_2 = 12,         /*!< Ethernet interface 2. */
    SBG_ECOM_IF_ETH_3 = 13,         /*!< Ethernet interface 3. */
    SBG_ECOM_IF_ETH_4 = 14,         /*!< Ethernet interface 4. */

    SBG_ECOM_IF_DATA_LOGGER = 20,   /*!< Data logger interface. */
} SbgEComPortId;

/*!
 * List of serial modes available.
 */
typedef enum _SbgEComPortMode
{
    SBG_ECOM_UART_MODE_OFF = 0,     /*!< This interface is turned OFF. */
    SBG_ECOM_UART_MODE_232 = 1,     /*!< This interface is using RS-232 communications. */
    SBG_ECOM_UART_MODE_422 = 2,     /*!< This interface is using RS-422 communications. */
} SbgEComPortMode;

//----------------------------------------------------------------------//
//- Serial interface configuration                                     -//
//----------------------------------------------------------------------//

/*!
 * Helper structure to configure a serial interface
 */
typedef struct _SbgEComInterfaceConf
{
    uint32_t            baudRate;   /*!< The baud rate of the interface. */
    SbgEComPortMode     mode;       /*!< The mode of the interface. */
} SbgEComInterfaceConf;

//----------------------------------------------------------------------//
//- CAN interface definitions                                          -//
//----------------------------------------------------------------------//

/*!
 * Enum containing the list of all available bit rates (in KB/s).
 */
typedef enum _SbgEComCanBitRate
{
    SBG_ECOM_CAN_BITRATE_DISABLED   = 0,            /*!< The CAN interface is disabled. */
    SBG_ECOM_CAN_BITRATE_10         = 10,           /*!< 10Kb/s. */
    SBG_ECOM_CAN_BITRATE_20         = 20,           /*!< 20Kb/s. */
    SBG_ECOM_CAN_BITRATE_25         = 25,           /*!< 25Kb/s. */
    SBG_ECOM_CAN_BITRATE_50         = 50,           /*!< 50Kb/s. */
    SBG_ECOM_CAN_BITRATE_100        = 100,          /*!< 100Kb/s. */
    SBG_ECOM_CAN_BITRATE_125        = 125,          /*!< 125Kb/s. */
    SBG_ECOM_CAN_BITRATE_250        = 250,          /*!< 250Kb/s. */
    SBG_ECOM_CAN_BITRATE_500        = 500,          /*!< 500Kb/s. */
    SBG_ECOM_CAN_BITRATE_750        = 750,          /*!< 750Kb/s. */
    SBG_ECOM_CAN_BITRATE_1000       = 1000,         /*!< 1Mb/s. */
} SbgEComCanBitRate;

/*!
 * Enum containing the list of different CAN modes
 */
typedef enum _SbgEComCanMode
{
    SBG_ECOM_CAN_MODE_UNDEFINED     = 0,    /*!< CAN Mode undefined. */
    SBG_ECOM_CAN_MODE_SPY           = 1,    /*!< Only listening on the CAN bus and doesn't sent anything (even RX ACK bit). */
    SBG_ECOM_CAN_MODE_NORMAL        = 2,    /*!< The device is allowed to both send and receive over the CAN bus. */
    SBG_ECOM_CAN_NR_MODE
} SbgEComCanMode;

//----------------------------------------------------------------------//
//- Public methods                                                     -//
//----------------------------------------------------------------------//

/*!
 * Retrieve the configuration of one of the interfaces.
 *
 * \param[in]   pHandle                     A valid sbgECom handle.
 * \param[in]   interfaceId                 The interface from which the configuration is to be retrieved.
 * \param[out]  pConf                       Pointer to a SbgEComInterfaceConf struct to hold configuration of the interface.
 * \return                                  SBG_NO_ERROR if the command has been executed successfully.
 */
SbgErrorCode sbgEComCmdInterfaceGetUartConf(SbgEComHandle *pHandle, SbgEComPortId interfaceId, SbgEComInterfaceConf *pConf);

/*!
 * Set the configuration of one of the interfaces.
 *
 * \param[in]   pHandle                     A valid sbgECom handle.
 * \param[in]   interfaceId                 The interface from which the configuration is to be retrieved.
 * \param[in]   pConf                       Pointer to a SbgEComInterfaceConf struct that holds the new configuration for the interface.
 * \return                                  SBG_NO_ERROR if the command has been executed successfully.
 */
SbgErrorCode sbgEComCmdInterfaceSetUartConf(SbgEComHandle *pHandle, SbgEComPortId interfaceId, const SbgEComInterfaceConf *pConf);

/*!
 * Retrieve the configuration of the CAN interface.
 *
 * \param[in]   pHandle                     A valid sbgECom handle.
 * \param[out]  pBitrate                    The bitrate of the CAN interface.
 * \param[out]  pMode                       Mode of the CAN interface.
 * \return                                  SBG_NO_ERROR if the command has been executed successfully.
 */
SbgErrorCode sbgEComCmdInterfaceGetCanConf(SbgEComHandle *pHandle, SbgEComCanBitRate *pBitrate, SbgEComCanMode *pMode);

/*!
 * Set the configuration of the CAN interface.
 *
 * \param[in]   pHandle                     A valid sbgECom handle.
 * \param[in]   bitRate                     The bitrate of the CAN interface.
 * \param[in]   mode                        Mode of the CAN interface.
 * \return                                  SBG_NO_ERROR if the command has been executed successfully.
 */
SbgErrorCode sbgEComCmdInterfaceSetCanConf(SbgEComHandle *pHandle, SbgEComCanBitRate bitRate, SbgEComCanMode mode);

#ifdef __cplusplus
}
#endif

#endif // SBG_ECOM_CMD_INTERFACE_H
