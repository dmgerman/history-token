multiline_comment|/*&n; * ItLpRegSave.h&n; * Copyright (C) 2001  Mike Corrigan IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
singleline_comment|//=====================================================================================
singleline_comment|//
singleline_comment|//&t;This control block contains the data that is shared between PLIC
singleline_comment|//&t;and the OS
singleline_comment|//    
singleline_comment|//
macro_line|#ifndef _ITLPREGSAVE_H
DECL|macro|_ITLPREGSAVE_H
mdefine_line|#define _ITLPREGSAVE_H
DECL|struct|ItLpRegSave
r_struct
id|ItLpRegSave
(brace
DECL|member|xDesc
id|u32
id|xDesc
suffix:semicolon
singleline_comment|// Eye catcher  &quot;LpRS&quot; ebcdic&t;000-003
DECL|member|xSize
id|u16
id|xSize
suffix:semicolon
singleline_comment|// Size of this class&t;&t;004-005
DECL|member|xInUse
id|u8
id|xInUse
suffix:semicolon
singleline_comment|// Area is live                 006-007
DECL|member|xRsvd1
id|u8
id|xRsvd1
(braket
l_int|9
)braket
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;007-00F
DECL|member|xFixedRegSave
id|u8
id|xFixedRegSave
(braket
l_int|352
)braket
suffix:semicolon
singleline_comment|// Fixed Register Save Area 010-16F 
DECL|member|xCTRL
id|u32
id|xCTRL
suffix:semicolon
singleline_comment|// Control Register&t;&t;170-173
DECL|member|xDEC
id|u32
id|xDEC
suffix:semicolon
singleline_comment|// Decrementer&t;&t;&t;174-177    
DECL|member|xFPSCR
id|u32
id|xFPSCR
suffix:semicolon
singleline_comment|// FP Status and Control Reg&t;178-17B
DECL|member|xPVR
id|u32
id|xPVR
suffix:semicolon
singleline_comment|// Processor Version Number&t;17C-17F
DECL|member|xMMCR0
id|u64
id|xMMCR0
suffix:semicolon
singleline_comment|// Monitor Mode Control Reg 0&t;180-187
DECL|member|xPMC1
id|u32
id|xPMC1
suffix:semicolon
singleline_comment|// Perf Monitor Counter 1&t;188-18B
DECL|member|xPMC2
id|u32
id|xPMC2
suffix:semicolon
singleline_comment|// Perf Monitor Counter 2&t;18C-18F
DECL|member|xPMC3
id|u32
id|xPMC3
suffix:semicolon
singleline_comment|// Perf Monitor Counter 3&t;190-193
DECL|member|xPMC4
id|u32
id|xPMC4
suffix:semicolon
singleline_comment|// Perf Monitor Counter 4&t;194-197
DECL|member|xPIR
id|u32
id|xPIR
suffix:semicolon
singleline_comment|// Processor ID Reg&t;&t;198-19B
DECL|member|xMMCR1
id|u32
id|xMMCR1
suffix:semicolon
singleline_comment|// Monitor Mode Control Reg 1&t;19C-19F
DECL|member|xMMCRA
id|u32
id|xMMCRA
suffix:semicolon
singleline_comment|// Monitor Mode Control Reg A&t;1A0-1A3
DECL|member|xPMC5
id|u32
id|xPMC5
suffix:semicolon
singleline_comment|// Perf Monitor Counter 5&t;1A4-1A7
DECL|member|xPMC6
id|u32
id|xPMC6
suffix:semicolon
singleline_comment|// Perf Monitor Counter 6&t;1A8-1AB
DECL|member|xPMC7
id|u32
id|xPMC7
suffix:semicolon
singleline_comment|// Perf Monitor Counter 7&t;1AC-1AF
DECL|member|xPMC8
id|u32
id|xPMC8
suffix:semicolon
singleline_comment|// Perf Monitor Counter 8&t;1B0-1B3
DECL|member|xTSC
id|u32
id|xTSC
suffix:semicolon
singleline_comment|// Thread Switch Control&t;1B4-1B7
DECL|member|xTST
id|u32
id|xTST
suffix:semicolon
singleline_comment|// Thread Switch Timeout&t;1B8-1BB
DECL|member|xRsvd
id|u32
id|xRsvd
suffix:semicolon
singleline_comment|// Reserved                     1BC-1BF
DECL|member|xACCR
id|u64
id|xACCR
suffix:semicolon
singleline_comment|// Address Compare Control Reg&t;1C0-1C7
DECL|member|xIMR
id|u64
id|xIMR
suffix:semicolon
singleline_comment|// Instruction Match Register&t;1C8-1CF    
DECL|member|xSDR1
id|u64
id|xSDR1
suffix:semicolon
singleline_comment|// Storage Description Reg 1&t;1D0-1D7    
DECL|member|xSPRG0
id|u64
id|xSPRG0
suffix:semicolon
singleline_comment|// Special Purpose Reg General0&t;1D8-1DF
DECL|member|xSPRG1
id|u64
id|xSPRG1
suffix:semicolon
singleline_comment|// Special Purpose Reg General1&t;1E0-1E7
DECL|member|xSPRG2
id|u64
id|xSPRG2
suffix:semicolon
singleline_comment|// Special Purpose Reg General2&t;1E8-1EF
DECL|member|xSPRG3
id|u64
id|xSPRG3
suffix:semicolon
singleline_comment|// Special Purpose Reg General3&t;1F0-1F7
DECL|member|xTB
id|u64
id|xTB
suffix:semicolon
singleline_comment|// Time Base Register&t;&t;1F8-1FF
DECL|member|xFPR
id|u64
id|xFPR
(braket
l_int|32
)braket
suffix:semicolon
singleline_comment|// Floating Point Registers&t;200-2FF
DECL|member|xMSR
id|u64
id|xMSR
suffix:semicolon
singleline_comment|// Machine State Register  &t;300-307
DECL|member|xNIA
id|u64
id|xNIA
suffix:semicolon
singleline_comment|// Next Instruction Address&t;308-30F
DECL|member|xDABR
id|u64
id|xDABR
suffix:semicolon
singleline_comment|// Data Address Breakpoint Reg&t;310-317
DECL|member|xIABR
id|u64
id|xIABR
suffix:semicolon
singleline_comment|// Inst Address Breakpoint Reg&t;318-31F
DECL|member|xHID0
id|u64
id|xHID0
suffix:semicolon
singleline_comment|// HW Implementation Dependent0&t;320-327
DECL|member|xHID4
id|u64
id|xHID4
suffix:semicolon
singleline_comment|// HW Implementation Dependent4&t;328-32F
DECL|member|xSCOMd
id|u64
id|xSCOMd
suffix:semicolon
singleline_comment|// SCON Data Reg (SPRG4)       &t;330-337
DECL|member|xSCOMc
id|u64
id|xSCOMc
suffix:semicolon
singleline_comment|// SCON Command Reg (SPRG5)    &t;338-33F
DECL|member|xSDAR
id|u64
id|xSDAR
suffix:semicolon
singleline_comment|// Sample Data Address Register&t;340-347
DECL|member|xSIAR
id|u64
id|xSIAR
suffix:semicolon
singleline_comment|// Sample Inst Address Register&t;348-34F
DECL|member|xRsvd3
id|u8
id|xRsvd3
(braket
l_int|176
)braket
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;350-3FF
)brace
suffix:semicolon
macro_line|#endif 
singleline_comment|// _ITLPREGSAVE_H
eof
