/*!
 * \file            sbgEComCmdOutput.h
 * \ingroup         commands
 * \author          SBG Systems
 * \date            11 June 2014
 *
 * \brief           Commands used to setup logs to output over the device interfaces.
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

#ifndef SBG_ECOM_CMD_OUTPUT_H
#define SBG_ECOM_CMD_OUTPUT_H

// sbgCommonLib headers
#include <sbgCommon.h>

// Project headers
#include <sbgECom.h>

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------//
//- Public definitions                                                 -//
//----------------------------------------------------------------------//

/*!
 * List of output ports available.
 */
typedef enum _SbgEComOutputPort
{
    SBG_ECOM_OUTPUT_PORT_A = 0,             /*!< Main output port. */
    SBG_ECOM_OUTPUT_PORT_C = 2,             /*!< Secondary output port only available on Ellipse-E devices */
    SBG_ECOM_OUTPUT_PORT_E = 4              /*!< Secondary output port only available on B1 devices */
} SbgEComOutputPort;

/*!
 * List of output modes available.
 */
typedef enum _SbgEComOutputMode
{
    SBG_ECOM_OUTPUT_MODE_DISABLED       = 0,        /*!< This output is disabled. */
    SBG_ECOM_OUTPUT_MODE_MAIN_LOOP      = 1,        /*!< Output is generated at  200 Hz. */
    SBG_ECOM_OUTPUT_MODE_DIV_2          = 2,        /*!< Output is generated at  100 Hz. */
    SBG_ECOM_OUTPUT_MODE_DIV_4          = 4,        /*!< Output is generated at   50 Hz. */
    SBG_ECOM_OUTPUT_MODE_DIV_5          = 5,        /*!< Output is generated at   40 Hz. */
    SBG_ECOM_OUTPUT_MODE_DIV_8          = 8,        /*!< Output is generated at   25 Hz. */
    SBG_ECOM_OUTPUT_MODE_DIV_10         = 10,       /*!< Output is generated at   20 Hz. */
    SBG_ECOM_OUTPUT_MODE_DIV_20         = 20,       /*!< Output is generated at   10 Hz. */
    SBG_ECOM_OUTPUT_MODE_DIV_40         = 40,       /*!< Output is generated at    5 Hz. */
    SBG_ECOM_OUTPUT_MODE_DIV_100        = 100,      /*!< Output is generated at    2 Hz. (only ELLIPSE fmw v3). */
    SBG_ECOM_OUTPUT_MODE_DIV_200        = 200,      /*!< Output is generated at    1 Hz. */

    SBG_ECOM_OUTPUT_MODE_1_MS           = 1001,     /*!< Output is generated at 1000 Hz (only ELLIPSE fmw v3). */
    SBG_ECOM_OUTPUT_MODE_2_MS           = 1002,     /*!< Output is generated at  500 Hz (only ELLIPSE fmw v3). */
    SBG_ECOM_OUTPUT_MODE_4_MS           = 1004,     /*!< Output is generated at  250 Hz (only ELLIPSE fmw v3). */

    SBG_ECOM_OUTPUT_MODE_PPS            = 10000,    /*!< Output the message on a Pulse Per Second event. */
    SBG_ECOM_OUTPUT_MODE_NEW_DATA       = 10001,    /*!< Output sent when a new data is available. */

    SBG_ECOM_OUTPUT_MODE_EVENT_IN_A     = 10003,    /*!< Output the message when a Sync A is received. */
    SBG_ECOM_OUTPUT_MODE_EVENT_IN_B     = 10004,    /*!< Output the message when a Sync B is received. */
    SBG_ECOM_OUTPUT_MODE_EVENT_IN_C     = 10005,    /*!< Output the message when a Sync C is received. */
    SBG_ECOM_OUTPUT_MODE_EVENT_IN_D     = 10006,    /*!< Output the message when a Sync D is received. */
    SBG_ECOM_OUTPUT_MODE_EVENT_IN_E     = 10007,    /*!< Output the message when a Sync E is received. */

    SBG_ECOM_OUTPUT_MODE_HIGH_FREQ_LOOP = 20001     /*!< Output the message in the 1KHz IMU loop (deprecated for ELLIPSE fmw v3, only used for IMU FAST). */
} SbgEComOutputMode;

/*!
 * Defines which monitoring point to use for an output port.
 * This feature enabled deporting measurements at a specific monitoring point.
 */
typedef enum _SbgEComOutputMonitoringPoint
{
    SBG_ECOM_OUTPUT_MONITORING_POINT_IMU    = 0,        /*!< Output measurements at the IMU location. */
    SBG_ECOM_OUTPUT_MONITORING_POINT_COG    = 1,        /*!< Output measurements at the center of rotation. */
    SBG_ECOM_OUTPUT_MONITORING_POINT_1      = 2,        /*!< Output measurements at the user deported location 1 (only for Ekinox and Apogee). */
    SBG_ECOM_OUTPUT_MONITORING_POINT_2      = 3,        /*!< Output measurements at the user deported location 2 (only for Ekinox and Apogee). */
    SBG_ECOM_OUTPUT_MONITORING_POINT_3      = 4,        /*!< Output measurements at the user deported location 3 (only for Ekinox and Apogee). */
    SBG_ECOM_OUTPUT_MONITORING_NUM                      /*!< Number of output monitoring points. */
} SbgEComOutputMonitoringPoint;

//----------------------------------------------------------------------//
//- Public methods                                                     -//
//----------------------------------------------------------------------//

/*!
 * Retrieve the configuration of one message for an output interfaces.
 *
 * \param[in]   pHandle                     A valid sbgECom handle.
 * \param[in]   outputPort                  The output port of the device for the log concerned.
 * \param[in]   classId                     The class of the concerned log.
 * \param[in]   msgId                       The id of the concerned log.
 * \param[out]  pMode                       Pointer to a SbgEComOutputMode to contain the current output mode of the message.
 * \return                                  SBG_NO_ERROR if the command has been executed successfully.
 */
SbgErrorCode sbgEComCmdOutputGetConf(SbgEComHandle *pHandle, SbgEComOutputPort outputPort, SbgEComClass classId, SbgEComMsgId msgId, SbgEComOutputMode *pMode);

/*!
 * Set the configuration of one message for an output interfaces.
 *
 * \param[in]   pHandle                     A valid sbgECom handle.
 * \param[in]   outputPort                  The output port of the device for the log concerned.
 * \param[in]   classId                     The class of the concerned log.
 * \param[in]   msgId                       The id of the concerned log.
 * \param[in]   mode                        New output mode to set.
 * \return                                  SBG_NO_ERROR if the command has been executed successfully.
 */
SbgErrorCode sbgEComCmdOutputSetConf(SbgEComHandle *pHandle, SbgEComOutputPort outputPort, SbgEComClass classId, SbgEComMsgId msgId, SbgEComOutputMode mode);

/*!
 * Retrieve if a whole message class is enabled or not for an output interface.
 *
 * \param[in]   pHandle                     A valid sbgECom handle.
 * \param[in]   outputPort                  The output port.
 * \param[in]   classId                     The class to enable or disable.
 * \param[out]  pEnable                     TRUE to enable message output of this class, FALSE to disable it.
 * \return                                  SBG_NO_ERROR if the command has been executed successfully.
 */
SbgErrorCode sbgEComCmdOutputClassGetEnable(SbgEComHandle *pHandle, SbgEComOutputPort outputPort, SbgEComClass classId, bool *pEnable);

/*!
 * Set if a whole message class is enabled or not for an output interface.
 *
 * Note: You can use the special classId SBG_ECOM_CLASS_LOG_ALL to disable or enable all classes at once.
 *       This is only available for ELLIPSE firmware v3 and above.
 * 
 * \param[in]   pHandle                     A valid sbgECom handle.
 * \param[in]   outputPort                  The output port.
 * \param[in]   classId                     The class to enable or disable.
 * \param[in]   enable                      TRUE to enable message output of this class, FALSE to disable it.
 * \return                                  SBG_NO_ERROR if the command has been executed successfully.
 */
SbgErrorCode sbgEComCmdOutputClassSetEnable(SbgEComHandle *pHandle, SbgEComOutputPort outputPort, SbgEComClass classId, bool enable);

/*!
 * Retrieve the configuration of one message for the CAN interface.
 *
 * \param[in]   pHandle                     A valid sbgECom handle.
 * \param[in]   internalId                  The internal message id.
 * \param[out]  pMode                       Pointer to a SbgEComOutputMode to contain the current output mode of the message.
 * \param[out]  pUserId                     The user defined message id.
 * \param[out]  pExtended                   TRUE if the user id uses the extended format.
 * \return                                  SBG_NO_ERROR if the command has been executed successfully.
 */
SbgErrorCode sbgEComCmdCanOutputGetConf(SbgEComHandle *pHandle, SbgECanMessageId internalId, SbgEComOutputMode *pMode, uint32_t *pUserId, bool *pExtended);

/*!
 * Set the configuration of one message for the CAN interface.
 *
 * \param[in]   pHandle                     A valid sbgECom handle.
 * \param[in]   internalId                  The internal message id.
 * \param[in]   mode                        Pointer to a SbgEComOutputMode containing the new output mode of the message.
 * \param[in]   userId                      The user defined message id.
 * \param[in]   extended                    TRUE if the user id uses the extended format.
 * \return                                  SBG_NO_ERROR if the command has been executed successfully.
 */
SbgErrorCode sbgEComCmdCanOutputSetConf(SbgEComHandle *pHandle, SbgECanMessageId internalId, SbgEComOutputMode mode, uint32_t userId, bool extended);

/*!
 * Retrieve the NMEA talker id for an output interface.
 *
 * \param[in]   pHandle                     A valid sbgECom handle.
 * \param[in]   outputPort                  The output port of the device for the log concerned.
 * \param[out]  pNmeaTalkerId               A 2-char array to contain the NMEA talker id.
 * \return                                  SBG_NO_ERROR if the command has been executed successfully.
 */
SbgErrorCode sbgEComCmdOutputGetNmeaTalkerId(SbgEComHandle *pHandle, SbgEComOutputPort outputPort, char *pNmeaTalkerId);

/*!
 * Set the NMEA talker id for an output interface.
 *
 * \param[in]   pHandle                     A valid sbgECom handle.
 * \param[in]   outputPort                  The output port of the device for the log concerned.
 * \param[out]  pNmeaTalkerId               A 2-char array containing the new NMEA talker id.
 * \return                                  SBG_NO_ERROR if the command has been executed successfully.
 */
SbgErrorCode sbgEComCmdOutputSetNmeaTalkerId(SbgEComHandle *pHandle, SbgEComOutputPort outputPort, const char *pNmeaTalkerId);

#ifdef __cplusplus
}
#endif

#endif // SBG_ECOM_CMD_OUTPUT_H
