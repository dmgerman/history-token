multiline_comment|/*&n; * sound/awe_hw.h&n; *&n; * Access routines and definitions for the low level driver for the &n; * Creative AWE32/SB32/AWE64 wave table synth.&n; *   version 0.4.4; Jan. 4, 2000&n; *&n; * Copyright (C) 1996-2000 Takashi Iwai&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef AWE_HW_H_DEF
DECL|macro|AWE_HW_H_DEF
mdefine_line|#define AWE_HW_H_DEF
multiline_comment|/*&n; * Emu-8000 control registers&n; * name(channel)&t;reg, port&n; */
DECL|macro|awe_cmd_idx
mdefine_line|#define awe_cmd_idx(reg,ch)&t;(((reg)&lt;&lt; 5) | (ch))
DECL|macro|Data0
mdefine_line|#define Data0    0&t;&t;/* 0x620: doubleword r/w */
DECL|macro|Data1
mdefine_line|#define Data1    1&t;&t;/* 0xA20: doubleword r/w */
DECL|macro|Data2
mdefine_line|#define Data2    2&t;&t;/* 0xA22: word r/w */
DECL|macro|Data3
mdefine_line|#define Data3    3&t;&t;/* 0xE20: word r/w */
DECL|macro|Pointer
mdefine_line|#define Pointer  4&t;&t;/* 0xE22 register pointer r/w */
DECL|macro|AWE_CPF
mdefine_line|#define AWE_CPF(ch)&t;awe_cmd_idx(0,ch), Data0&t;/* DW: current pitch and fractional address */
DECL|macro|AWE_PTRX
mdefine_line|#define AWE_PTRX(ch)&t;awe_cmd_idx(1,ch), Data0&t;/* DW: pitch target and reverb send */
DECL|macro|AWE_CVCF
mdefine_line|#define AWE_CVCF(ch)&t;awe_cmd_idx(2,ch), Data0&t;/* DW: current volume and filter cutoff */
DECL|macro|AWE_VTFT
mdefine_line|#define AWE_VTFT(ch)&t;awe_cmd_idx(3,ch), Data0&t;/* DW: volume and filter cutoff targets */
DECL|macro|AWE_0080
mdefine_line|#define AWE_0080(ch)&t;awe_cmd_idx(4,ch), Data0&t;/* DW: ?? */
DECL|macro|AWE_00A0
mdefine_line|#define AWE_00A0(ch)&t;awe_cmd_idx(5,ch), Data0&t;/* DW: ?? */
DECL|macro|AWE_PSST
mdefine_line|#define AWE_PSST(ch)&t;awe_cmd_idx(6,ch), Data0&t;/* DW: pan send and loop start address */
DECL|macro|AWE_CSL
mdefine_line|#define AWE_CSL(ch)&t;awe_cmd_idx(7,ch), Data0&t;/* DW: chorus send and loop end address */
DECL|macro|AWE_CCCA
mdefine_line|#define AWE_CCCA(ch)&t;awe_cmd_idx(0,ch), Data1&t;/* DW: Q, control bits, and current address */
DECL|macro|AWE_HWCF4
mdefine_line|#define AWE_HWCF4&t;awe_cmd_idx(1,9),  Data1&t;/* DW: config dw 4 */
DECL|macro|AWE_HWCF5
mdefine_line|#define AWE_HWCF5&t;awe_cmd_idx(1,10), Data1&t;/* DW: config dw 5 */
DECL|macro|AWE_HWCF6
mdefine_line|#define AWE_HWCF6&t;awe_cmd_idx(1,13), Data1&t;/* DW: config dw 6 */
DECL|macro|AWE_HWCF7
mdefine_line|#define AWE_HWCF7&t;awe_cmd_idx(1,14), Data1&t;/* DW: config dw 7? (not documented) */
DECL|macro|AWE_SMALR
mdefine_line|#define AWE_SMALR&t;awe_cmd_idx(1,20), Data1&t;/* DW: sound memory address for left read */
DECL|macro|AWE_SMARR
mdefine_line|#define AWE_SMARR&t;awe_cmd_idx(1,21), Data1&t;/* DW:    for right read */
DECL|macro|AWE_SMALW
mdefine_line|#define AWE_SMALW&t;awe_cmd_idx(1,22), Data1&t;/* DW: sound memory address for left write */
DECL|macro|AWE_SMARW
mdefine_line|#define AWE_SMARW&t;awe_cmd_idx(1,23), Data1&t;/* DW:    for right write */
DECL|macro|AWE_SMLD
mdefine_line|#define AWE_SMLD&t;awe_cmd_idx(1,26), Data1&t;/* W: sound memory left data */
DECL|macro|AWE_SMRD
mdefine_line|#define AWE_SMRD&t;awe_cmd_idx(1,26), Data2&t;/* W:    right data */
DECL|macro|AWE_WC
mdefine_line|#define AWE_WC&t;&t;awe_cmd_idx(1,27), Data2&t;/* W: sample counter */
DECL|macro|AWE_WC_Cmd
mdefine_line|#define AWE_WC_Cmd&t;awe_cmd_idx(1,27)
DECL|macro|AWE_WC_Port
mdefine_line|#define AWE_WC_Port&t;Data2
DECL|macro|AWE_HWCF1
mdefine_line|#define AWE_HWCF1&t;awe_cmd_idx(1,29), Data1&t;/* W: config w 1 */
DECL|macro|AWE_HWCF2
mdefine_line|#define AWE_HWCF2&t;awe_cmd_idx(1,30), Data1&t;/* W: config w 2 */
DECL|macro|AWE_HWCF3
mdefine_line|#define AWE_HWCF3&t;awe_cmd_idx(1,31), Data1&t;/* W: config w 3 */
DECL|macro|AWE_INIT1
mdefine_line|#define AWE_INIT1(ch)&t;awe_cmd_idx(2,ch), Data1&t;/* W: init array 1 */
DECL|macro|AWE_INIT2
mdefine_line|#define AWE_INIT2(ch)&t;awe_cmd_idx(2,ch), Data2&t;/* W: init array 2 */
DECL|macro|AWE_INIT3
mdefine_line|#define AWE_INIT3(ch)&t;awe_cmd_idx(3,ch), Data1&t;/* W: init array 3 */
DECL|macro|AWE_INIT4
mdefine_line|#define AWE_INIT4(ch)&t;awe_cmd_idx(3,ch), Data2&t;/* W: init array 4 */
DECL|macro|AWE_ENVVOL
mdefine_line|#define AWE_ENVVOL(ch)&t;awe_cmd_idx(4,ch), Data1&t;/* W: volume envelope delay */
DECL|macro|AWE_DCYSUSV
mdefine_line|#define AWE_DCYSUSV(ch)&t;awe_cmd_idx(5,ch), Data1&t;/* W: volume envelope sustain and decay */
DECL|macro|AWE_ENVVAL
mdefine_line|#define AWE_ENVVAL(ch)&t;awe_cmd_idx(6,ch), Data1&t;/* W: modulation envelope delay */
DECL|macro|AWE_DCYSUS
mdefine_line|#define AWE_DCYSUS(ch)&t;awe_cmd_idx(7,ch), Data1&t;/* W: modulation envelope sustain and decay */
DECL|macro|AWE_ATKHLDV
mdefine_line|#define AWE_ATKHLDV(ch)&t;awe_cmd_idx(4,ch), Data2&t;/* W: volume envelope attack and hold */
DECL|macro|AWE_LFO1VAL
mdefine_line|#define AWE_LFO1VAL(ch)&t;awe_cmd_idx(5,ch), Data2&t;/* W: LFO#1 Delay */
DECL|macro|AWE_ATKHLD
mdefine_line|#define AWE_ATKHLD(ch)&t;awe_cmd_idx(6,ch), Data2&t;/* W: modulation envelope attack and hold */
DECL|macro|AWE_LFO2VAL
mdefine_line|#define AWE_LFO2VAL(ch)&t;awe_cmd_idx(7,ch), Data2&t;/* W: LFO#2 Delay */
DECL|macro|AWE_IP
mdefine_line|#define AWE_IP(ch)&t;awe_cmd_idx(0,ch), Data3&t;/* W: initial pitch */
DECL|macro|AWE_IFATN
mdefine_line|#define AWE_IFATN(ch)&t;awe_cmd_idx(1,ch), Data3&t;/* W: initial filter cutoff and attenuation */
DECL|macro|AWE_PEFE
mdefine_line|#define AWE_PEFE(ch)&t;awe_cmd_idx(2,ch), Data3&t;/* W: pitch and filter envelope heights */
DECL|macro|AWE_FMMOD
mdefine_line|#define AWE_FMMOD(ch)&t;awe_cmd_idx(3,ch), Data3&t;/* W: vibrato and filter modulation freq */
DECL|macro|AWE_TREMFRQ
mdefine_line|#define AWE_TREMFRQ(ch)&t;awe_cmd_idx(4,ch), Data3&t;/* W: LFO#1 tremolo amount and freq */
DECL|macro|AWE_FM2FRQ2
mdefine_line|#define AWE_FM2FRQ2(ch)&t;awe_cmd_idx(5,ch), Data3&t;/* W: LFO#2 vibrato amount and freq */
multiline_comment|/* used during detection (returns ROM version?; not documented in ADIP) */
DECL|macro|AWE_U1
mdefine_line|#define AWE_U1&t;&t;0xE0, Data3&t;  /* (R)(W) used in initialization */
DECL|macro|AWE_U2
mdefine_line|#define AWE_U2(ch)&t;0xC0+(ch), Data3  /* (W)(W) used in init envelope  */
DECL|macro|AWE_MAX_VOICES
mdefine_line|#define AWE_MAX_VOICES&t;&t;32
DECL|macro|AWE_NORMAL_VOICES
mdefine_line|#define AWE_NORMAL_VOICES&t;30&t;/*30&amp;31 are reserved for DRAM refresh*/
DECL|macro|AWE_MAX_CHANNELS
mdefine_line|#define AWE_MAX_CHANNELS&t;32&t;/* max midi channels (must &gt;= voices) */
DECL|macro|AWE_MAX_LAYERS
mdefine_line|#define AWE_MAX_LAYERS&t;AWE_MAX_VOICES&t;/* maximum number of multiple layers */
DECL|macro|AWE_DRAM_OFFSET
mdefine_line|#define AWE_DRAM_OFFSET&t;&t;0x200000
DECL|macro|AWE_MAX_DRAM_SIZE
mdefine_line|#define AWE_MAX_DRAM_SIZE&t;(28 * 1024)&t;/* 28 MB is max onboard memory */
macro_line|#endif
eof
