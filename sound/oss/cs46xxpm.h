multiline_comment|/*******************************************************************************&n;*&n;*      &quot;cs46xxpm.h&quot; --  Cirrus Logic-Crystal CS46XX linux audio driver.&n;*&n;*      Copyright (C) 2000,2001  Cirrus Logic Corp.  &n;*            -- tom woller (twoller@crystal.cirrus.com) or&n;*               (pcaudio@crystal.cirrus.com).&n;*&n;*      This program is free software; you can redistribute it and/or modify&n;*      it under the terms of the GNU General Public License as published by&n;*      the Free Software Foundation; either version 2 of the License, or&n;*      (at your option) any later version.&n;*&n;*      This program is distributed in the hope that it will be useful,&n;*      but WITHOUT ANY WARRANTY; without even the implied warranty of&n;*      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;*      GNU General Public License for more details.&n;*&n;*      You should have received a copy of the GNU General Public License&n;*      along with this program; if not, write to the Free Software&n;*      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*&n;* 12/22/00 trw - new file. &n;*&n;*******************************************************************************/
macro_line|#ifndef __CS46XXPM_H
DECL|macro|__CS46XXPM_H
mdefine_line|#define __CS46XXPM_H
DECL|macro|CS46XX_AC97_HIGHESTREGTORESTORE
mdefine_line|#define CS46XX_AC97_HIGHESTREGTORESTORE 0x26
DECL|macro|CS46XX_AC97_NUMBER_RESTORE_REGS
mdefine_line|#define CS46XX_AC97_NUMBER_RESTORE_REGS (CS46XX_AC97_HIGHESTREGTORESTORE/2-1)
multiline_comment|/* PM state defintions */
DECL|macro|CS46XX_PM_NOT_REGISTERED
mdefine_line|#define CS46XX_PM_NOT_REGISTERED&t;0x1000
DECL|macro|CS46XX_PM_IDLE
mdefine_line|#define CS46XX_PM_IDLE&t;&t;&t;0x0001
DECL|macro|CS46XX_PM_SUSPENDING
mdefine_line|#define CS46XX_PM_SUSPENDING&t;&t;0x0002
DECL|macro|CS46XX_PM_SUSPENDED
mdefine_line|#define CS46XX_PM_SUSPENDED&t;&t;0x0004
DECL|macro|CS46XX_PM_RESUMING
mdefine_line|#define CS46XX_PM_RESUMING&t;&t;0x0008
DECL|macro|CS46XX_PM_RESUMED
mdefine_line|#define CS46XX_PM_RESUMED&t;&t;0x0010
DECL|macro|CS_POWER_DAC
mdefine_line|#define CS_POWER_DAC&t;&t;&t;0x0001
DECL|macro|CS_POWER_ADC
mdefine_line|#define CS_POWER_ADC&t;&t;&t;0x0002
DECL|macro|CS_POWER_MIXVON
mdefine_line|#define CS_POWER_MIXVON&t;&t;&t;0x0004
DECL|macro|CS_POWER_MIXVOFF
mdefine_line|#define CS_POWER_MIXVOFF&t;&t;0x0008
DECL|macro|CS_AC97_POWER_CONTROL_ON
mdefine_line|#define CS_AC97_POWER_CONTROL_ON&t;0xf000  /* always on bits (inverted) */
DECL|macro|CS_AC97_POWER_CONTROL_ADC
mdefine_line|#define CS_AC97_POWER_CONTROL_ADC&t;0x0100
DECL|macro|CS_AC97_POWER_CONTROL_DAC
mdefine_line|#define CS_AC97_POWER_CONTROL_DAC&t;0x0200
DECL|macro|CS_AC97_POWER_CONTROL_MIXVON
mdefine_line|#define CS_AC97_POWER_CONTROL_MIXVON&t;0x0400
DECL|macro|CS_AC97_POWER_CONTROL_MIXVOFF
mdefine_line|#define CS_AC97_POWER_CONTROL_MIXVOFF&t;0x0800
DECL|macro|CS_AC97_POWER_CONTROL_ADC_ON
mdefine_line|#define CS_AC97_POWER_CONTROL_ADC_ON&t;0x0001
DECL|macro|CS_AC97_POWER_CONTROL_DAC_ON
mdefine_line|#define CS_AC97_POWER_CONTROL_DAC_ON&t;0x0002
DECL|macro|CS_AC97_POWER_CONTROL_MIXVON_ON
mdefine_line|#define CS_AC97_POWER_CONTROL_MIXVON_ON&t;0x0004
DECL|macro|CS_AC97_POWER_CONTROL_MIXVOFF_ON
mdefine_line|#define CS_AC97_POWER_CONTROL_MIXVOFF_ON 0x0008
DECL|struct|cs46xx_pm
r_struct
id|cs46xx_pm
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|u32CLKCR1_SAVE
DECL|member|u32SSPMValue
DECL|member|u32PPLVCvalue
DECL|member|u32PPRVCvalue
id|u32
id|u32CLKCR1_SAVE
comma
id|u32SSPMValue
comma
id|u32PPLVCvalue
comma
id|u32PPRVCvalue
suffix:semicolon
DECL|member|u32FMLVCvalue
DECL|member|u32FMRVCvalue
DECL|member|u32GPIORvalue
DECL|member|u32JSCTLvalue
DECL|member|u32SSCR
id|u32
id|u32FMLVCvalue
comma
id|u32FMRVCvalue
comma
id|u32GPIORvalue
comma
id|u32JSCTLvalue
comma
id|u32SSCR
suffix:semicolon
DECL|member|u32SRCSA
DECL|member|u32DacASR
DECL|member|u32AdcASR
DECL|member|u32DacSR
DECL|member|u32AdcSR
DECL|member|u32MIDCR_Save
id|u32
id|u32SRCSA
comma
id|u32DacASR
comma
id|u32AdcASR
comma
id|u32DacSR
comma
id|u32AdcSR
comma
id|u32MIDCR_Save
suffix:semicolon
DECL|member|u32SSPM_BITS
id|u32
id|u32SSPM_BITS
suffix:semicolon
DECL|member|ac97
id|u32
id|ac97
(braket
id|CS46XX_AC97_NUMBER_RESTORE_REGS
)braket
suffix:semicolon
DECL|member|u32AC97_master_volume
DECL|member|u32AC97_headphone_volume
DECL|member|u32AC97_master_volume_mono
id|u32
id|u32AC97_master_volume
comma
id|u32AC97_headphone_volume
comma
id|u32AC97_master_volume_mono
suffix:semicolon
DECL|member|u32AC97_pcm_out_volume
DECL|member|u32AC97_powerdown
DECL|member|u32AC97_general_purpose
id|u32
id|u32AC97_pcm_out_volume
comma
id|u32AC97_powerdown
comma
id|u32AC97_general_purpose
suffix:semicolon
DECL|member|u32hwptr_playback
DECL|member|u32hwptr_capture
id|u32
id|u32hwptr_playback
comma
id|u32hwptr_capture
suffix:semicolon
DECL|member|dmabuf_swptr_play
r_int
id|dmabuf_swptr_play
suffix:semicolon
DECL|member|dmabuf_count_play
r_int
id|dmabuf_count_play
suffix:semicolon
DECL|member|dmabuf_swptr_capture
r_int
id|dmabuf_swptr_capture
suffix:semicolon
DECL|member|dmabuf_count_capture
r_int
id|dmabuf_count_capture
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
