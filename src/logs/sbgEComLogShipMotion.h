/*!
 * \file            sbgEComLogShipMotion.h
 * \ingroup         binaryLogs
 * \author          SBG Systems
 * \date            30 March 2013
 *
 * \brief           Parse logs that returns ship motion values such as heave.
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

#ifndef SBG_ECOM_LOG_SHIP_MOTION_H
#define SBG_ECOM_LOG_SHIP_MOTION_H

// sbgCommonLib headers
#include <sbgCommon.h>
#include <streamBuffer/sbgStreamBuffer.h>

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------//
//- Heave status definitions                                           -//
//----------------------------------------------------------------------//

#define SBG_ECOM_HEAVE_VALID                (0x0001u << 0)          /*!< Set to 1 after heave convergence time. */
#define SBG_ECOM_HEAVE_VEL_AIDED            (0x0001u << 1)          /*!< Set to 1 if heave output is compensated for transient accelerations. */
#define SBG_ECOM_HEAVE_SURGE_SWAY_INCLUDED  (0x0001u << 2)          /*!< Set to 1 if surge and sway channels are provided in this output. */
#define SBG_ECOM_HEAVE_PERIOD_INCLUDED      (0x0001u << 3)          /*!< Set to 1 if the heave period is provided in this output. */
#define SBG_ECOM_HEAVE_PERIOD_VALID         (0x0001u << 4)          /*!< Set to 1 if the returned heave period is assumed to be valid. */
#define SBG_ECOM_HEAVE_SWELL_MODE           (0x0001u << 5)          /*!< Set to 1 if the real time heave filter is using the swell mode computations. */

//----------------------------------------------------------------------//
//- Log structure definitions                                          -//
//----------------------------------------------------------------------//

/*!
 * Structure that stores data for the SBG_ECOM_LOG_SHIP_MOTION or SBG_ECOM_LOG_SHIP_MOTION_HP message.
 * 
 * The data are expressed in the standard NED Inertial Navigation System coordinate frame. 
 * Surge is positive forward, sway is positive right and heave is positive down. 
 * 
 * Note that status flag should be read before using the different parameters because it will provide validity information 
 * about all included outputs. Some frames may not provide the heave period or surge/sway axes for example
 */
typedef struct _SbgEComLogShipMotion
{
    uint32_t    timeStamp;                  /*!< Time in us since the sensor power up. */
    uint16_t    status;                     /*!< Ship Motion data status bitmask */
    float       mainHeavePeriod;            /*!< Main heave period in seconds. */
    float       shipMotion[3];              /*!< Surge, sway and heave in meters. */
    float       shipAccel[3];               /*!< Surge, sway and heave ship Acceleration in m.s^-2. */
    float       shipVel[3];                 /*!< Surge, sway and heave velocities */
} SbgEComLogShipMotion;

//----------------------------------------------------------------------//
//- Public methods                                                     -//
//----------------------------------------------------------------------//

/*!
 * Parse data for the SBG_ECOM_LOG_SHIP_MOTION or SBG_ECOM_LOG_SHIP_MOTION_HP message and fill the corresponding structure.
 * 
 * \param[out]  pLogData                    Log structure instance to fill.
 * \param[in]   pStreamBuffer               Input stream buffer to read the log from.
 * \return                                  SBG_NO_ERROR if a valid log has been read from the stream buffer.
 */
SbgErrorCode sbgEComLogShipMotionReadFromStream(SbgEComLogShipMotion *pLogData, SbgStreamBuffer *pStreamBuffer);

/*!
 * Write data for the SBG_ECOM_LOG_SHIP_MOTION or SBG_ECOM_LOG_SHIP_MOTION_HP message to the output stream buffer from the provided structure.
 *
 * \param[in]   pLogData                    Log structure instance to write.
 * \param[out]  pStreamBuffer               Output stream buffer to write the log to.
 * \return                                  SBG_NO_ERROR if the log has been written to the stream buffer.
 */
SbgErrorCode sbgEComLogShipMotionWriteToStream(const SbgEComLogShipMotion *pLogData, SbgStreamBuffer *pStreamBuffer);

//----------------------------------------------------------------------//
//- DEPRECATED - Used for backward compatibility                       -//
//----------------------------------------------------------------------//

SBG_DEPRECATED_TYPEDEF(typedef struct _SbgEComLogShipMotion SbgLogShipMotionData);

SBG_DEPRECATED(SbgErrorCode sbgEComBinaryLogParseShipMotionData(SbgStreamBuffer *pStreamBuffer, SbgEComLogShipMotion *pLogData));
SBG_DEPRECATED(SbgErrorCode sbgEComBinaryLogWriteShipMotionData(SbgStreamBuffer *pStreamBuffer, const SbgEComLogShipMotion *pLogData));

#ifdef __cplusplus
}
#endif

#endif // SBG_ECOM_LOG_SHIP_MOTION_H
