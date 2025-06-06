﻿// sbgCommonLib headers
#include <sbgCommon.h>
#include <streamBuffer/sbgStreamBuffer.h>

// Project headers
#include <sbgECom.h>

// Local headers
#include "sbgEComCmdCommon.h"
#include "sbgEComCmdInterface.h"

//----------------------------------------------------------------------//
//- Public methods                                                     -//
//----------------------------------------------------------------------//

SbgErrorCode sbgEComCmdInterfaceGetUartConf(SbgEComHandle *pHandle, SbgEComPortId interfaceId, SbgEComInterfaceConf *pConf)
{
    SbgErrorCode            errorCode = SBG_NO_ERROR;
    SbgEComProtocolPayload  receivedPayload;
    uint32_t                trial;  
    
    assert(pHandle);
    assert(pConf);

    sbgEComProtocolPayloadConstruct(&receivedPayload);

    //
    // Send the command three times
    //
    for (trial = 0; trial < pHandle->numTrials; trial++)
    {
        uint8_t interfaceIdParam = interfaceId;

        //
        // Send the command and the interfaceId as a 1-byte payload
        //
        errorCode = sbgEComProtocolSend(&pHandle->protocolHandle, SBG_ECOM_CLASS_LOG_CMD_0, SBG_ECOM_CMD_UART_CONF, &interfaceIdParam, sizeof(interfaceIdParam));

        //
        // Make sure that the command has been sent
        //
        if (errorCode == SBG_NO_ERROR)
        {
            //
            // Try to read the device answer for 500 ms
            //
            errorCode = sbgEComReceiveCmd2(pHandle, SBG_ECOM_CLASS_LOG_CMD_0, SBG_ECOM_CMD_UART_CONF, &receivedPayload, pHandle->cmdDefaultTimeOut);

            //
            // Test if we have received correctly the answer
            //
            if (errorCode == SBG_NO_ERROR)
            {
                SbgStreamBuffer     inputStream;

                //
                // Initialize stream buffer to read parameters
                //
                sbgStreamBufferInitForRead(&inputStream, sbgEComProtocolPayloadGetBuffer(&receivedPayload), sbgEComProtocolPayloadGetSize(&receivedPayload));

                //
                // Read parameters
                // First is returned interfaceId, then baud rate and the mode at last.
                //
                interfaceId = (SbgEComPortId)sbgStreamBufferReadUint8LE(&inputStream);
                pConf->baudRate = sbgStreamBufferReadUint32LE(&inputStream);
                pConf->mode = (SbgEComPortMode)sbgStreamBufferReadUint8LE(&inputStream);

                //
                // The command has been executed successfully so return
                //
                break;
            }
        }
        else
        {
            //
            // We have a write error so exit the try loop
            //
            break;
        }
    }

    sbgEComProtocolPayloadDestroy(&receivedPayload);
    
    return errorCode;
}

SbgErrorCode sbgEComCmdInterfaceSetUartConf(SbgEComHandle *pHandle, SbgEComPortId interfaceId, const SbgEComInterfaceConf *pConf)
{
    SbgErrorCode        errorCode = SBG_NO_ERROR;
    uint32_t            trial;
    uint8_t             outputBuffer[64];
    SbgStreamBuffer     outputStream;

    assert(pHandle);
    assert(pConf);

    //
    // Send the command three times
    //
    for (trial = 0; trial < pHandle->numTrials; trial++)
    {
        //
        // Init stream buffer for output
        //
        sbgStreamBufferInitForWrite(&outputStream, outputBuffer, sizeof(outputBuffer));

        //
        // Build payload
        //
        sbgStreamBufferWriteUint8LE(&outputStream, (uint8_t)interfaceId);
        sbgStreamBufferWriteUint32LE(&outputStream, pConf->baudRate);
        sbgStreamBufferWriteUint8LE(&outputStream, (uint8_t)pConf->mode);

        //
        // Send the payload over ECom
        //
        errorCode = sbgEComProtocolSend(&pHandle->protocolHandle, SBG_ECOM_CLASS_LOG_CMD_0, SBG_ECOM_CMD_UART_CONF, sbgStreamBufferGetLinkedBuffer(&outputStream), sbgStreamBufferGetLength(&outputStream));

        //
        // Make sure that the command has been sent
        //
        if (errorCode == SBG_NO_ERROR)
        {
            //
            // Try to read the device answer for 500 ms
            //
            errorCode = sbgEComWaitForAck(pHandle, SBG_ECOM_CLASS_LOG_CMD_0, SBG_ECOM_CMD_UART_CONF, pHandle->cmdDefaultTimeOut);

            //
            // Test if we have received a valid ACK
            //
            if (errorCode == SBG_NO_ERROR)
            {
                //
                // The command has been executed successfully so return
                //
                break;
            }
        }
        else
        {
            //
            // We have a write error so exit the try loop
            //
            break;
        }
    }
    
    return errorCode;
}

SbgErrorCode sbgEComCmdInterfaceGetCanConf(SbgEComHandle *pHandle, SbgEComCanBitRate *pBitrate, SbgEComCanMode *pMode)
{
    SbgErrorCode            errorCode = SBG_NO_ERROR;
    SbgEComProtocolPayload  receivedPayload;
    uint32_t                trial;
    
    assert(pHandle);
    assert(pBitrate);
    assert(pMode);

    sbgEComProtocolPayloadConstruct(&receivedPayload);

    //
    // Send the command three times
    //
    for (trial = 0; trial < pHandle->numTrials; trial++)
    {
        //
        // Send the command with no payload
        //
        errorCode = sbgEComProtocolSend(&pHandle->protocolHandle, SBG_ECOM_CLASS_LOG_CMD_0, SBG_ECOM_CMD_CAN_BUS_CONF, NULL, 0);

        //
        // Make sure that the command has been sent
        //
        if (errorCode == SBG_NO_ERROR)
        {
            //
            // Try to read the device answer for 500 ms
            //
            errorCode = sbgEComReceiveCmd2(pHandle, SBG_ECOM_CLASS_LOG_CMD_0, SBG_ECOM_CMD_CAN_BUS_CONF, &receivedPayload, pHandle->cmdDefaultTimeOut);

            //
            // Test if we have received a SBG_ECOM_CMD_CAN_BUS_CONF command
            //
            if (errorCode == SBG_NO_ERROR)
            {
                SbgStreamBuffer     inputStream;

                //
                // Initialize stream buffer to read parameters
                //
                sbgStreamBufferInitForRead(&inputStream, sbgEComProtocolPayloadGetBuffer(&receivedPayload), sbgEComProtocolPayloadGetSize(&receivedPayload));

                //
                // Read bit rate returned by the device
                //
                *pBitrate = (SbgEComCanBitRate)sbgStreamBufferReadUint16LE(&inputStream);

                //
                // Check if we can parse the CAN mode that has been introduced in sbgECom version 2.0
                // 
                if (sbgStreamBufferGetSpace(&inputStream) > 0)
                {
                    //
                    // Read mode returned by the device
                    //
                    *pMode = (SbgEComCanMode)sbgStreamBufferReadUint8(&inputStream);
                }
                else
                {
                    //
                    // Default the mode to the behavior prior to CAN mode setting introduction
                    //
                    *pMode = SBG_ECOM_CAN_MODE_NORMAL;
                }

                //
                // The command has been executed successfully so return
                //
                break;
            }
        }
        else
        {
            //
            // We have a write error so exit the try loop
            //
            break;
        }
    }

    sbgEComProtocolPayloadDestroy(&receivedPayload);
    
    return errorCode;
}

SbgErrorCode sbgEComCmdInterfaceSetCanConf(SbgEComHandle *pHandle, SbgEComCanBitRate bitrate, SbgEComCanMode mode)
{
    SbgErrorCode        errorCode = SBG_NO_ERROR;
    uint32_t            trial;
    uint8_t             outputBuffer[3];
    SbgStreamBuffer     outputStream;

    assert(pHandle);

    //
    // Build the command payload
    //
    sbgStreamBufferInitForWrite(&outputStream, outputBuffer, sizeof(outputBuffer));
    
    sbgStreamBufferWriteUint16LE(&outputStream, (uint16_t)bitrate);
    sbgStreamBufferWriteUint8(&outputStream, (uint8_t)mode);

    //
    // Send the command three times
    //
    for (trial = 0; trial < pHandle->numTrials; trial++)
    {
        //
        // Send the payload over ECom
        //
        errorCode = sbgEComProtocolSend(&pHandle->protocolHandle, SBG_ECOM_CLASS_LOG_CMD_0, SBG_ECOM_CMD_CAN_BUS_CONF, sbgStreamBufferGetLinkedBuffer(&outputStream), sbgStreamBufferGetLength(&outputStream));

        //
        // Make sure that the command has been sent
        //
        if (errorCode == SBG_NO_ERROR)
        {
            //
            // Try to read the device answer for 500 ms
            //
            errorCode = sbgEComWaitForAck(pHandle, SBG_ECOM_CLASS_LOG_CMD_0, SBG_ECOM_CMD_CAN_BUS_CONF, pHandle->cmdDefaultTimeOut);

            //
            // Test if we have received a valid ACK
            //
            if (errorCode == SBG_NO_ERROR)
            {
                //
                // The command has been executed successfully so return
                //
                break;
            }
        }
        else
        {
            //
            // We have a write error so exit the try loop
            //
            break;
        }
    }

    return errorCode;
}
