/*!
 * \file            sbgEComVersion.h
 * \ingroup         main
 * \author          SBG Systems
 * \date            05 February 2013
 *
 * \brief           Header file that contains all versions related information such as change log.
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

#ifndef SBG_E_COM_VERSION_H
#define SBG_E_COM_VERSION_H

// sbgCommonLib headers
#include <sbgCommon.h>

#ifdef __cplusplus
extern "C" {
#endif


//----------------------------------------------------------------------//
//- Version definitions                                                -//
//----------------------------------------------------------------------//

#define SBG_E_COM_VERSION_MAJOR         5
#define SBG_E_COM_VERSION_MINOR         2
#define SBG_E_COM_VERSION_REV           590
#define SBG_E_COM_VERSION_BUILD         SBG_VERSION_QUALIFIER_STABLE

#define SBG_E_COM_VERSION               SBG_VERSION_SOFTWARE(SBG_E_COM_VERSION_MAJOR,SBG_E_COM_VERSION_MINOR,SBG_E_COM_VERSION_REV,SBG_E_COM_VERSION_BUILD)

/*
 * Backward compatibility macro definitions.
 */
 #ifndef SBG_STR
    #define SBG_STR(X)      #X
#endif
#ifndef SBG_ASSTR
    #define SBG_ASSTR(X)    SBG_STR(X)
#endif
#define SBG_E_COM_VERSION_STR           SBG_ASSTR(SBG_E_COM_VERSION_MAJOR) "." SBG_ASSTR(SBG_E_COM_VERSION_MINOR) "." SBG_ASSTR(SBG_E_COM_VERSION_REV) "-stable\0"

#ifdef __cplusplus
}
#endif

#endif // SBG_E_COM_VERSION_H
