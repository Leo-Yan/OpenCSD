/*
 * \file       trc_cmp_cfg_stm.h
 * \brief      Reference CoreSight Trace Decoder : STM compnent configuration.
 * 
 * \copyright  Copyright (c) 2015, ARM Limited. All Rights Reserved.
 */

/* 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, 
 * this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 * this list of conditions and the following disclaimer in the documentation 
 * and/or other materials provided with the distribution. 
 * 
 * 3. Neither the name of the copyright holder nor the names of its contributors 
 * may be used to endorse or promote products derived from this software without 
 * specific prior written permission. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 'AS IS' AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND 
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */ 

#ifndef ARM_TRC_CMP_CFG_STM_H_INCLUDED
#define ARM_TRC_CMP_CFG_STM_H_INCLUDED

#include "trc_pkt_types_stm.h"

/** @addtogroup rctdl_protocol_cfg
@{*/

/** @name STM configuration
@{*/


class STMConfig : public rctdl_stm_cfg
{
public:
    STMConfig();
    ~STMConfig() {};

    STMConfig & operator=(const rctdl_stm_cfg *p_cfg);  //!< set from full config.
    void setTraceID(const uint8_t traceID);     //!< use default 256 masters + 65536 channels & set trace ID.
    
    const uint8_t getTraceID() const;
    const uint8_t getMaxMasterIdx() const;
    const uint16_t getMaxChannelIdx() const;
};

STMConfig::STMConfig()
{
    reg_tcsr = 0;
    reg_devid = 0xFF;   // default to 256 masters.
    reg_feat3r = 0x10000; // default to 65536 channels.
}
  
STMConfig & STMConfig::operator=(const rctdl_stm_cfg *p_cfg)
{
    *dynamic_cast<rctdl_stm_cfg *>(this) = *p_cfg;
    return *this;
}

void STMConfig::setTraceID(const uint8_t traceID)
{
    uint32_t IDmask = 0x007F0000;
    reg_tcsr &= ~IDmask;
    reg_tcsr |= (((uint32_t)traceID) << 16) & IDmask;
}

const uint8_t STMConfig::getTraceID() const
{
    return (uint8_t)((reg_tcsr >> 16) & 0x7F);
}

const uint8_t STMConfig::getMaxMasterIdx() const
{
    return (uint8_t)(reg_devid & 0xFF);
}

const uint16_t STMConfig::getMaxChannelIdx() const
{
    return (uint16_t)(reg_feat3r - 1);
}

/** @}*/

/** @}*/

#endif // ARM_TRC_CMP_CFG_STM_H_INCLUDED

/* End of File trc_cmp_cfg_stm.h */
