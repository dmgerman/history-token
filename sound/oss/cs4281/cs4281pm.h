macro_line|#ifndef NOT_CS4281_PM
multiline_comment|/*******************************************************************************&n;*&n;*      &quot;cs4281pm.h&quot; --  Cirrus Logic-Crystal CS4281 linux audio driver.&n;*&n;*      Copyright (C) 2000,2001  Cirrus Logic Corp.  &n;*            -- tom woller (twoller@crystal.cirrus.com) or&n;*               (audio@crystal.cirrus.com).&n;*&n;*      This program is free software; you can redistribute it and/or modify&n;*      it under the terms of the GNU General Public License as published by&n;*      the Free Software Foundation; either version 2 of the License, or&n;*      (at your option) any later version.&n;*&n;*      This program is distributed in the hope that it will be useful,&n;*      but WITHOUT ANY WARRANTY; without even the implied warranty of&n;*      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;*      GNU General Public License for more details.&n;*&n;*      You should have received a copy of the GNU General Public License&n;*      along with this program; if not, write to the Free Software&n;*      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*&n;* 12/22/00 trw - new file. &n;*&n;*******************************************************************************/
multiline_comment|/* general pm definitions */
DECL|macro|CS4281_AC97_HIGHESTREGTORESTORE
mdefine_line|#define CS4281_AC97_HIGHESTREGTORESTORE 0x26
DECL|macro|CS4281_AC97_NUMBER_RESTORE_REGS
mdefine_line|#define CS4281_AC97_NUMBER_RESTORE_REGS (CS4281_AC97_HIGHESTREGTORESTORE/2-1)
multiline_comment|/* pipeline definitions */
DECL|macro|CS4281_NUMBER_OF_PIPELINES
mdefine_line|#define CS4281_NUMBER_OF_PIPELINES &t;4
DECL|macro|CS4281_PIPELINE_VALID
mdefine_line|#define CS4281_PIPELINE_VALID &t;&t;0x0001
DECL|macro|CS4281_PLAYBACK_PIPELINE_NUMBER
mdefine_line|#define CS4281_PLAYBACK_PIPELINE_NUMBER&t;0x0000
DECL|macro|CS4281_CAPTURE_PIPELINE_NUMBER
mdefine_line|#define CS4281_CAPTURE_PIPELINE_NUMBER &t;0x0001
multiline_comment|/* PM state defintions */
DECL|macro|CS4281_PM_NOT_REGISTERED
mdefine_line|#define CS4281_PM_NOT_REGISTERED&t;0x1000
DECL|macro|CS4281_PM_IDLE
mdefine_line|#define CS4281_PM_IDLE&t;&t;&t;0x0001
DECL|macro|CS4281_PM_SUSPENDING
mdefine_line|#define CS4281_PM_SUSPENDING&t;&t;0x0002
DECL|macro|CS4281_PM_SUSPENDED
mdefine_line|#define CS4281_PM_SUSPENDED&t;&t;0x0004
DECL|macro|CS4281_PM_RESUMING
mdefine_line|#define CS4281_PM_RESUMING&t;&t;0x0008
DECL|macro|CS4281_PM_RESUMED
mdefine_line|#define CS4281_PM_RESUMED&t;&t;0x0010
DECL|struct|cs4281_pm
r_struct
id|cs4281_pm
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
id|CS4281_AC97_NUMBER_RESTORE_REGS
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
)brace
suffix:semicolon
DECL|struct|cs4281_pipeline
r_struct
id|cs4281_pipeline
(brace
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|number
r_int
id|number
suffix:semicolon
DECL|member|u32DBAnValue
DECL|member|u32DBCnValue
DECL|member|u32DMRnValue
DECL|member|u32DCRnValue
id|u32
id|u32DBAnValue
comma
id|u32DBCnValue
comma
id|u32DMRnValue
comma
id|u32DCRnValue
suffix:semicolon
DECL|member|u32DBAnAddress
DECL|member|u32DCAnAddress
DECL|member|u32DBCnAddress
DECL|member|u32DCCnAddress
id|u32
id|u32DBAnAddress
comma
id|u32DCAnAddress
comma
id|u32DBCnAddress
comma
id|u32DCCnAddress
suffix:semicolon
DECL|member|u32DMRnAddress
DECL|member|u32DCRnAddress
DECL|member|u32HDSRnAddress
id|u32
id|u32DMRnAddress
comma
id|u32DCRnAddress
comma
id|u32HDSRnAddress
suffix:semicolon
DECL|member|u32DBAn_Save
DECL|member|u32DBCn_Save
DECL|member|u32DMRn_Save
DECL|member|u32DCRn_Save
id|u32
id|u32DBAn_Save
comma
id|u32DBCn_Save
comma
id|u32DMRn_Save
comma
id|u32DCRn_Save
suffix:semicolon
DECL|member|u32DCCn_Save
DECL|member|u32DCAn_Save
id|u32
id|u32DCCn_Save
comma
id|u32DCAn_Save
suffix:semicolon
multiline_comment|/* &n;* technically, these are fifo variables, but just map the &n;* first fifo with the first pipeline and then use the fifo&n;* variables inside of the pipeline struct.&n;*/
DECL|member|u32FCRn_Save
DECL|member|u32FSICn_Save
id|u32
id|u32FCRn_Save
comma
id|u32FSICn_Save
suffix:semicolon
DECL|member|u32FCRnValue
DECL|member|u32FCRnAddress
DECL|member|u32FSICnValue
DECL|member|u32FSICnAddress
id|u32
id|u32FCRnValue
comma
id|u32FCRnAddress
comma
id|u32FSICnValue
comma
id|u32FSICnAddress
suffix:semicolon
DECL|member|u32FPDRnValue
DECL|member|u32FPDRnAddress
id|u32
id|u32FPDRnValue
comma
id|u32FPDRnAddress
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
