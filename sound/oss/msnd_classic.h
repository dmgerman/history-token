multiline_comment|/*********************************************************************&n; *&n; * msnd_classic.h&n; *&n; * Turtle Beach MultiSound Sound Card Driver for Linux&n; *&n; * Some parts of this header file were derived from the Turtle Beach&n; * MultiSound Driver Development Kit.&n; *&n; * Copyright (C) 1998 Andrew Veliath&n; * Copyright (C) 1993 Turtle Beach Systems, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; * &n; * $Id: msnd_classic.h,v 1.10 1999/03/21 17:36:09 andrewtv Exp $&n; *&n; ********************************************************************/
macro_line|#ifndef __MSND_CLASSIC_H
DECL|macro|__MSND_CLASSIC_H
mdefine_line|#define __MSND_CLASSIC_H
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|DSP_NUMIO
mdefine_line|#define DSP_NUMIO&t;&t;&t;&t;0x10
DECL|macro|HP_MEMM
mdefine_line|#define&t;HP_MEMM&t;&t;&t;&t;&t;0x08
DECL|macro|HP_BITM
mdefine_line|#define&t;HP_BITM&t;&t;&t;&t;&t;0x0E
DECL|macro|HP_WAIT
mdefine_line|#define&t;HP_WAIT&t;&t;&t;&t;&t;0x0D
DECL|macro|HP_DSPR
mdefine_line|#define&t;HP_DSPR&t;&t;&t;&t;&t;0x0A
DECL|macro|HP_PROR
mdefine_line|#define&t;HP_PROR&t;&t;&t;&t;&t;0x0B
DECL|macro|HP_BLKS
mdefine_line|#define&t;HP_BLKS&t;&t;&t;&t;&t;0x0C
DECL|macro|HPPRORESET_OFF
mdefine_line|#define&t;HPPRORESET_OFF&t;&t;&t;&t;0
DECL|macro|HPPRORESET_ON
mdefine_line|#define HPPRORESET_ON&t;&t;&t;&t;1
DECL|macro|HPDSPRESET_OFF
mdefine_line|#define HPDSPRESET_OFF&t;&t;&t;&t;0
DECL|macro|HPDSPRESET_ON
mdefine_line|#define HPDSPRESET_ON&t;&t;&t;&t;1
DECL|macro|HPBLKSEL_0
mdefine_line|#define HPBLKSEL_0&t;&t;&t;&t;0
DECL|macro|HPBLKSEL_1
mdefine_line|#define HPBLKSEL_1&t;&t;&t;&t;1
DECL|macro|HPWAITSTATE_0
mdefine_line|#define HPWAITSTATE_0&t;&t;&t;&t;0
DECL|macro|HPWAITSTATE_1
mdefine_line|#define HPWAITSTATE_1&t;&t;&t;&t;1
DECL|macro|HPBITMODE_16
mdefine_line|#define HPBITMODE_16&t;&t;&t;&t;0
DECL|macro|HPBITMODE_8
mdefine_line|#define HPBITMODE_8&t;&t;&t;&t;1
DECL|macro|HIDSP_INT_PLAY_UNDER
mdefine_line|#define&t;HIDSP_INT_PLAY_UNDER&t;&t;&t;0x00
DECL|macro|HIDSP_INT_RECORD_OVER
mdefine_line|#define&t;HIDSP_INT_RECORD_OVER&t;&t;&t;0x01
DECL|macro|HIDSP_INPUT_CLIPPING
mdefine_line|#define&t;HIDSP_INPUT_CLIPPING&t;&t;&t;0x02
DECL|macro|HIDSP_MIDI_IN_OVER
mdefine_line|#define&t;HIDSP_MIDI_IN_OVER&t;&t;&t;0x10
DECL|macro|HIDSP_MIDI_OVERRUN_ERR
mdefine_line|#define&t;HIDSP_MIDI_OVERRUN_ERR  0x13
DECL|macro|HDEXAR_CLEAR_PEAKS
mdefine_line|#define&t;HDEXAR_CLEAR_PEAKS&t;&t;&t;1
DECL|macro|HDEXAR_IN_SET_POTS
mdefine_line|#define&t;HDEXAR_IN_SET_POTS&t;&t;&t;2
DECL|macro|HDEXAR_AUX_SET_POTS
mdefine_line|#define&t;HDEXAR_AUX_SET_POTS&t;&t;&t;3
DECL|macro|HDEXAR_CAL_A_TO_D
mdefine_line|#define&t;HDEXAR_CAL_A_TO_D&t;&t;&t;4
DECL|macro|HDEXAR_RD_EXT_DSP_BITS
mdefine_line|#define&t;HDEXAR_RD_EXT_DSP_BITS&t;&t;&t;5
DECL|macro|TIME_PRO_RESET_DONE
mdefine_line|#define TIME_PRO_RESET_DONE&t;&t;&t;0x028A
DECL|macro|TIME_PRO_SYSEX
mdefine_line|#define TIME_PRO_SYSEX&t;&t;&t;&t;0x0040
DECL|macro|TIME_PRO_RESET
mdefine_line|#define TIME_PRO_RESET&t;&t;&t;&t;0x0032
DECL|macro|AGND
mdefine_line|#define AGND&t;&t;&t;&t;&t;0x01
DECL|macro|SIGNAL
mdefine_line|#define SIGNAL&t;&t;&t;&t;&t;0x02
DECL|macro|EXT_DSP_BIT_DCAL
mdefine_line|#define EXT_DSP_BIT_DCAL&t;&t;&t;0x0001
DECL|macro|EXT_DSP_BIT_MIDI_CON
mdefine_line|#define EXT_DSP_BIT_MIDI_CON&t;&t;&t;0x0002
DECL|macro|BUFFSIZE
mdefine_line|#define BUFFSIZE&t;&t;&t;&t;0x8000
DECL|macro|HOSTQ_SIZE
mdefine_line|#define HOSTQ_SIZE&t;&t;&t;&t;0x40
DECL|macro|SRAM_CNTL_START
mdefine_line|#define SRAM_CNTL_START&t;&t;&t;&t;0x7F00
DECL|macro|SMA_STRUCT_START
mdefine_line|#define SMA_STRUCT_START&t;&t;&t;0x7F40
DECL|macro|DAP_BUFF_SIZE
mdefine_line|#define DAP_BUFF_SIZE&t;&t;&t;&t;0x2400
DECL|macro|DAR_BUFF_SIZE
mdefine_line|#define DAR_BUFF_SIZE&t;&t;&t;&t;0x2000
DECL|macro|DAPQ_STRUCT_SIZE
mdefine_line|#define DAPQ_STRUCT_SIZE&t;&t;&t;0x10
DECL|macro|DARQ_STRUCT_SIZE
mdefine_line|#define DARQ_STRUCT_SIZE&t;&t;&t;0x10
DECL|macro|DAPQ_BUFF_SIZE
mdefine_line|#define DAPQ_BUFF_SIZE&t;&t;&t;&t;(3 * 0x10)
DECL|macro|DARQ_BUFF_SIZE
mdefine_line|#define DARQ_BUFF_SIZE&t;&t;&t;&t;(3 * 0x10)
DECL|macro|MODQ_BUFF_SIZE
mdefine_line|#define MODQ_BUFF_SIZE&t;&t;&t;&t;0x400
DECL|macro|MIDQ_BUFF_SIZE
mdefine_line|#define MIDQ_BUFF_SIZE&t;&t;&t;&t;0x200
DECL|macro|DSPQ_BUFF_SIZE
mdefine_line|#define DSPQ_BUFF_SIZE&t;&t;&t;&t;0x40
DECL|macro|DAPQ_DATA_BUFF
mdefine_line|#define DAPQ_DATA_BUFF&t;&t;&t;&t;0x6C00
DECL|macro|DARQ_DATA_BUFF
mdefine_line|#define DARQ_DATA_BUFF&t;&t;&t;&t;0x6C30
DECL|macro|MODQ_DATA_BUFF
mdefine_line|#define MODQ_DATA_BUFF&t;&t;&t;&t;0x6C60
DECL|macro|MIDQ_DATA_BUFF
mdefine_line|#define MIDQ_DATA_BUFF&t;&t;&t;&t;0x7060
DECL|macro|DSPQ_DATA_BUFF
mdefine_line|#define DSPQ_DATA_BUFF&t;&t;&t;&t;0x7260
DECL|macro|DAPQ_OFFSET
mdefine_line|#define DAPQ_OFFSET&t;&t;&t;&t;SRAM_CNTL_START
DECL|macro|DARQ_OFFSET
mdefine_line|#define DARQ_OFFSET&t;&t;&t;&t;(SRAM_CNTL_START + 0x08)
DECL|macro|MODQ_OFFSET
mdefine_line|#define MODQ_OFFSET&t;&t;&t;&t;(SRAM_CNTL_START + 0x10)
DECL|macro|MIDQ_OFFSET
mdefine_line|#define MIDQ_OFFSET&t;&t;&t;&t;(SRAM_CNTL_START + 0x18)
DECL|macro|DSPQ_OFFSET
mdefine_line|#define DSPQ_OFFSET&t;&t;&t;&t;(SRAM_CNTL_START + 0x20)
DECL|macro|MOP_SYNTH
mdefine_line|#define MOP_SYNTH&t;&t;&t;&t;0x10
DECL|macro|MOP_EXTOUT
mdefine_line|#define MOP_EXTOUT&t;&t;&t;&t;0x32
DECL|macro|MOP_EXTTHRU
mdefine_line|#define MOP_EXTTHRU&t;&t;&t;&t;0x02
DECL|macro|MOP_OUTMASK
mdefine_line|#define MOP_OUTMASK&t;&t;&t;&t;0x01
DECL|macro|MIP_EXTIN
mdefine_line|#define MIP_EXTIN&t;&t;&t;&t;0x01
DECL|macro|MIP_SYNTH
mdefine_line|#define MIP_SYNTH&t;&t;&t;&t;0x00
DECL|macro|MIP_INMASK
mdefine_line|#define MIP_INMASK&t;&t;&t;&t;0x32
multiline_comment|/* Classic SMA Common Data */
DECL|macro|SMA_wCurrPlayBytes
mdefine_line|#define SMA_wCurrPlayBytes&t;&t;&t;0x0000
DECL|macro|SMA_wCurrRecordBytes
mdefine_line|#define SMA_wCurrRecordBytes&t;&t;&t;0x0002
DECL|macro|SMA_wCurrPlayVolLeft
mdefine_line|#define SMA_wCurrPlayVolLeft&t;&t;&t;0x0004
DECL|macro|SMA_wCurrPlayVolRight
mdefine_line|#define SMA_wCurrPlayVolRight&t;&t;&t;0x0006
DECL|macro|SMA_wCurrInVolLeft
mdefine_line|#define SMA_wCurrInVolLeft&t;&t;&t;0x0008
DECL|macro|SMA_wCurrInVolRight
mdefine_line|#define SMA_wCurrInVolRight&t;&t;&t;0x000a
DECL|macro|SMA_wUser_3
mdefine_line|#define SMA_wUser_3&t;&t;&t;&t;0x000c
DECL|macro|SMA_wUser_4
mdefine_line|#define SMA_wUser_4&t;&t;&t;&t;0x000e
DECL|macro|SMA_dwUser_5
mdefine_line|#define SMA_dwUser_5&t;&t;&t;&t;0x0010
DECL|macro|SMA_dwUser_6
mdefine_line|#define SMA_dwUser_6&t;&t;&t;&t;0x0014
DECL|macro|SMA_wUser_7
mdefine_line|#define SMA_wUser_7&t;&t;&t;&t;0x0018
DECL|macro|SMA_wReserved_A
mdefine_line|#define SMA_wReserved_A&t;&t;&t;&t;0x001a
DECL|macro|SMA_wReserved_B
mdefine_line|#define SMA_wReserved_B&t;&t;&t;&t;0x001c
DECL|macro|SMA_wReserved_C
mdefine_line|#define SMA_wReserved_C&t;&t;&t;&t;0x001e
DECL|macro|SMA_wReserved_D
mdefine_line|#define SMA_wReserved_D&t;&t;&t;&t;0x0020
DECL|macro|SMA_wReserved_E
mdefine_line|#define SMA_wReserved_E&t;&t;&t;&t;0x0022
DECL|macro|SMA_wReserved_F
mdefine_line|#define SMA_wReserved_F&t;&t;&t;&t;0x0024
DECL|macro|SMA_wReserved_G
mdefine_line|#define SMA_wReserved_G&t;&t;&t;&t;0x0026
DECL|macro|SMA_wReserved_H
mdefine_line|#define SMA_wReserved_H&t;&t;&t;&t;0x0028
DECL|macro|SMA_wCurrDSPStatusFlags
mdefine_line|#define SMA_wCurrDSPStatusFlags&t;&t;&t;0x002a
DECL|macro|SMA_wCurrHostStatusFlags
mdefine_line|#define SMA_wCurrHostStatusFlags&t;&t;0x002c
DECL|macro|SMA_wCurrInputTagBits
mdefine_line|#define SMA_wCurrInputTagBits&t;&t;&t;0x002e
DECL|macro|SMA_wCurrLeftPeak
mdefine_line|#define SMA_wCurrLeftPeak&t;&t;&t;0x0030
DECL|macro|SMA_wCurrRightPeak
mdefine_line|#define SMA_wCurrRightPeak&t;&t;&t;0x0032
DECL|macro|SMA_wExtDSPbits
mdefine_line|#define SMA_wExtDSPbits&t;&t;&t;&t;0x0034
DECL|macro|SMA_bExtHostbits
mdefine_line|#define SMA_bExtHostbits&t;&t;&t;0x0036
DECL|macro|SMA_bBoardLevel
mdefine_line|#define SMA_bBoardLevel&t;&t;&t;&t;0x0037
DECL|macro|SMA_bInPotPosRight
mdefine_line|#define SMA_bInPotPosRight&t;&t;&t;0x0038
DECL|macro|SMA_bInPotPosLeft
mdefine_line|#define SMA_bInPotPosLeft&t;&t;&t;0x0039
DECL|macro|SMA_bAuxPotPosRight
mdefine_line|#define SMA_bAuxPotPosRight&t;&t;&t;0x003a
DECL|macro|SMA_bAuxPotPosLeft
mdefine_line|#define SMA_bAuxPotPosLeft&t;&t;&t;0x003b
DECL|macro|SMA_wCurrMastVolLeft
mdefine_line|#define SMA_wCurrMastVolLeft&t;&t;&t;0x003c
DECL|macro|SMA_wCurrMastVolRight
mdefine_line|#define SMA_wCurrMastVolRight&t;&t;&t;0x003e
DECL|macro|SMA_bUser_12
mdefine_line|#define SMA_bUser_12&t;&t;&t;&t;0x0040
DECL|macro|SMA_bUser_13
mdefine_line|#define SMA_bUser_13&t;&t;&t;&t;0x0041
DECL|macro|SMA_wUser_14
mdefine_line|#define SMA_wUser_14&t;&t;&t;&t;0x0042
DECL|macro|SMA_wUser_15
mdefine_line|#define SMA_wUser_15&t;&t;&t;&t;0x0044
DECL|macro|SMA_wCalFreqAtoD
mdefine_line|#define SMA_wCalFreqAtoD&t;&t;&t;0x0046
DECL|macro|SMA_wUser_16
mdefine_line|#define SMA_wUser_16&t;&t;&t;&t;0x0048
DECL|macro|SMA_wUser_17
mdefine_line|#define SMA_wUser_17&t;&t;&t;&t;0x004a
DECL|macro|SMA__size
mdefine_line|#define SMA__size&t;&t;&t;&t;0x004c
macro_line|#ifdef HAVE_DSPCODEH
macro_line|#  include &quot;msndperm.c&quot;
macro_line|#  include &quot;msndinit.c&quot;
DECL|macro|PERMCODE
macro_line|#  define PERMCODE&t;&t;msndperm
DECL|macro|INITCODE
macro_line|#  define INITCODE&t;&t;msndinit
DECL|macro|PERMCODESIZE
macro_line|#  define PERMCODESIZE&t;&t;sizeof(msndperm)
DECL|macro|INITCODESIZE
macro_line|#  define INITCODESIZE&t;&t;sizeof(msndinit)
macro_line|#else
macro_line|#  ifndef CONFIG_MSNDCLAS_INIT_FILE
DECL|macro|CONFIG_MSNDCLAS_INIT_FILE
macro_line|#    define CONFIG_MSNDCLAS_INIT_FILE&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&quot;/etc/sound/msndinit.bin&quot;
macro_line|#  endif
macro_line|#  ifndef CONFIG_MSNDCLAS_PERM_FILE
DECL|macro|CONFIG_MSNDCLAS_PERM_FILE
macro_line|#    define CONFIG_MSNDCLAS_PERM_FILE&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&quot;/etc/sound/msndperm.bin&quot;
macro_line|#  endif
DECL|macro|PERMCODEFILE
macro_line|#  define PERMCODEFILE&t;&t;CONFIG_MSNDCLAS_PERM_FILE
DECL|macro|INITCODEFILE
macro_line|#  define INITCODEFILE&t;&t;CONFIG_MSNDCLAS_INIT_FILE
DECL|macro|PERMCODE
macro_line|#  define PERMCODE&t;&t;dspini
DECL|macro|INITCODE
macro_line|#  define INITCODE&t;&t;permini
DECL|macro|PERMCODESIZE
macro_line|#  define PERMCODESIZE&t;&t;sizeof_dspini
DECL|macro|INITCODESIZE
macro_line|#  define INITCODESIZE&t;&t;sizeof_permini
macro_line|#endif
DECL|macro|LONGNAME
mdefine_line|#define LONGNAME&t;&t;&quot;MultiSound (Classic/Monterey/Tahiti)&quot;
macro_line|#endif /* __MSND_CLASSIC_H */
eof
