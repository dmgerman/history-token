multiline_comment|/*********************************************************************&n; *&n; * msnd_pinnacle.h&n; *&n; * Turtle Beach MultiSound Sound Card Driver for Linux&n; *&n; * Some parts of this header file were derived from the Turtle Beach&n; * MultiSound Driver Development Kit.&n; *&n; * Copyright (C) 1998 Andrew Veliath&n; * Copyright (C) 1993 Turtle Beach Systems, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * $Id: msnd_pinnacle.h,v 1.11 1999/03/21 17:36:09 andrewtv Exp $&n; *&n; ********************************************************************/
macro_line|#ifndef __MSND_PINNACLE_H
DECL|macro|__MSND_PINNACLE_H
mdefine_line|#define __MSND_PINNACLE_H
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|DSP_NUMIO
mdefine_line|#define DSP_NUMIO&t;&t;&t;&t;0x08
DECL|macro|IREG_LOGDEVICE
mdefine_line|#define IREG_LOGDEVICE&t;&t;&t;&t;0x07
DECL|macro|IREG_ACTIVATE
mdefine_line|#define IREG_ACTIVATE&t;&t;&t;&t;0x30
DECL|macro|LD_ACTIVATE
mdefine_line|#define LD_ACTIVATE&t;&t;&t;&t;0x01
DECL|macro|LD_DISACTIVATE
mdefine_line|#define LD_DISACTIVATE&t;&t;&t;&t;0x00
DECL|macro|IREG_EECONTROL
mdefine_line|#define IREG_EECONTROL&t;&t;&t;&t;0x3F
DECL|macro|IREG_MEMBASEHI
mdefine_line|#define IREG_MEMBASEHI&t;&t;&t;&t;0x40
DECL|macro|IREG_MEMBASELO
mdefine_line|#define IREG_MEMBASELO&t;&t;&t;&t;0x41
DECL|macro|IREG_MEMCONTROL
mdefine_line|#define IREG_MEMCONTROL&t;&t;&t;&t;0x42
DECL|macro|IREG_MEMRANGEHI
mdefine_line|#define IREG_MEMRANGEHI&t;&t;&t;&t;0x43
DECL|macro|IREG_MEMRANGELO
mdefine_line|#define IREG_MEMRANGELO&t;&t;&t;&t;0x44
DECL|macro|MEMTYPE_8BIT
mdefine_line|#define MEMTYPE_8BIT&t;&t;&t;&t;0x00
DECL|macro|MEMTYPE_16BIT
mdefine_line|#define MEMTYPE_16BIT&t;&t;&t;&t;0x02
DECL|macro|MEMTYPE_RANGE
mdefine_line|#define MEMTYPE_RANGE&t;&t;&t;&t;0x00
DECL|macro|MEMTYPE_HIADDR
mdefine_line|#define MEMTYPE_HIADDR&t;&t;&t;&t;0x01
DECL|macro|IREG_IO0_BASEHI
mdefine_line|#define IREG_IO0_BASEHI&t;&t;&t;&t;0x60
DECL|macro|IREG_IO0_BASELO
mdefine_line|#define IREG_IO0_BASELO&t;&t;&t;&t;0x61
DECL|macro|IREG_IO1_BASEHI
mdefine_line|#define IREG_IO1_BASEHI&t;&t;&t;&t;0x62
DECL|macro|IREG_IO1_BASELO
mdefine_line|#define IREG_IO1_BASELO&t;&t;&t;&t;0x63
DECL|macro|IREG_IRQ_NUMBER
mdefine_line|#define IREG_IRQ_NUMBER&t;&t;&t;&t;0x70
DECL|macro|IREG_IRQ_TYPE
mdefine_line|#define IREG_IRQ_TYPE&t;&t;&t;&t;0x71
DECL|macro|IRQTYPE_HIGH
mdefine_line|#define IRQTYPE_HIGH&t;&t;&t;&t;0x02
DECL|macro|IRQTYPE_LOW
mdefine_line|#define IRQTYPE_LOW&t;&t;&t;&t;0x00
DECL|macro|IRQTYPE_LEVEL
mdefine_line|#define IRQTYPE_LEVEL&t;&t;&t;&t;0x01
DECL|macro|IRQTYPE_EDGE
mdefine_line|#define IRQTYPE_EDGE&t;&t;&t;&t;0x00
DECL|macro|HP_DSPR
mdefine_line|#define&t;HP_DSPR&t;&t;&t;&t;&t;0x04
DECL|macro|HP_BLKS
mdefine_line|#define&t;HP_BLKS&t;&t;&t;&t;&t;0x04
DECL|macro|HPDSPRESET_OFF
mdefine_line|#define HPDSPRESET_OFF&t;&t;&t;&t;2
DECL|macro|HPDSPRESET_ON
mdefine_line|#define HPDSPRESET_ON&t;&t;&t;&t;0
DECL|macro|HPBLKSEL_0
mdefine_line|#define HPBLKSEL_0&t;&t;&t;&t;2
DECL|macro|HPBLKSEL_1
mdefine_line|#define HPBLKSEL_1&t;&t;&t;&t;3
DECL|macro|HIMT_DAT_OFF
mdefine_line|#define&t;HIMT_DAT_OFF&t;&t;&t;&t;0x03
DECL|macro|HIDSP_PLAY_UNDER
mdefine_line|#define&t;HIDSP_PLAY_UNDER&t;&t;&t;0x00
DECL|macro|HIDSP_INT_PLAY_UNDER
mdefine_line|#define&t;HIDSP_INT_PLAY_UNDER&t;&t;&t;0x01
DECL|macro|HIDSP_SSI_TX_UNDER
mdefine_line|#define&t;HIDSP_SSI_TX_UNDER  &t;&t;&t;0x02
DECL|macro|HIDSP_RECQ_OVERFLOW
mdefine_line|#define HIDSP_RECQ_OVERFLOW&t;&t;&t;0x08
DECL|macro|HIDSP_INT_RECORD_OVER
mdefine_line|#define HIDSP_INT_RECORD_OVER&t;&t;&t;0x09
DECL|macro|HIDSP_SSI_RX_OVERFLOW
mdefine_line|#define HIDSP_SSI_RX_OVERFLOW&t;&t;&t;0x0a
DECL|macro|HIDSP_MIDI_IN_OVER
mdefine_line|#define&t;HIDSP_MIDI_IN_OVER&t;&t;&t;0x10
DECL|macro|HIDSP_MIDI_FRAME_ERR
mdefine_line|#define&t;HIDSP_MIDI_FRAME_ERR&t;&t;&t;0x11
DECL|macro|HIDSP_MIDI_PARITY_ERR
mdefine_line|#define&t;HIDSP_MIDI_PARITY_ERR&t;&t;&t;0x12
DECL|macro|HIDSP_MIDI_OVERRUN_ERR
mdefine_line|#define&t;HIDSP_MIDI_OVERRUN_ERR&t;&t;&t;0x13
DECL|macro|HIDSP_INPUT_CLIPPING
mdefine_line|#define HIDSP_INPUT_CLIPPING&t;&t;&t;0x20
DECL|macro|HIDSP_MIX_CLIPPING
mdefine_line|#define&t;HIDSP_MIX_CLIPPING&t;&t;&t;0x30
DECL|macro|HIDSP_DAT_IN_OFF
mdefine_line|#define HIDSP_DAT_IN_OFF&t;&t;&t;0x21
DECL|macro|HDEXAR_SET_ANA_IN
mdefine_line|#define&t;HDEXAR_SET_ANA_IN&t;&t;&t;0
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
DECL|macro|HDEXAR_SET_SYNTH_IN
mdefine_line|#define&t;HDEXAR_SET_SYNTH_IN&t;&t;&t;4
DECL|macro|HDEXAR_READ_DAT_IN
mdefine_line|#define&t;HDEXAR_READ_DAT_IN&t;&t;&t;5
DECL|macro|HDEXAR_MIC_SET_POTS
mdefine_line|#define&t;HDEXAR_MIC_SET_POTS&t;&t;&t;6
DECL|macro|HDEXAR_SET_DAT_IN
mdefine_line|#define&t;HDEXAR_SET_DAT_IN&t;&t;&t;7
DECL|macro|HDEXAR_SET_SYNTH_48
mdefine_line|#define HDEXAR_SET_SYNTH_48&t;&t;&t;8
DECL|macro|HDEXAR_SET_SYNTH_44
mdefine_line|#define HDEXAR_SET_SYNTH_44&t;&t;&t;9
DECL|macro|TIME_PRO_RESET_DONE
mdefine_line|#define TIME_PRO_RESET_DONE&t;&t;&t;0x028A
DECL|macro|TIME_PRO_SYSEX
mdefine_line|#define TIME_PRO_SYSEX&t;&t;&t;&t;0x001E
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
mdefine_line|#define MIDQ_BUFF_SIZE&t;&t;&t;&t;0x800
DECL|macro|DSPQ_BUFF_SIZE
mdefine_line|#define DSPQ_BUFF_SIZE&t;&t;&t;&t;0x5A0
DECL|macro|DAPQ_DATA_BUFF
mdefine_line|#define DAPQ_DATA_BUFF&t;&t;&t;&t;0x6C00
DECL|macro|DARQ_DATA_BUFF
mdefine_line|#define DARQ_DATA_BUFF&t;&t;&t;&t;0x6C30
DECL|macro|MODQ_DATA_BUFF
mdefine_line|#define MODQ_DATA_BUFF&t;&t;&t;&t;0x6C60
DECL|macro|MIDQ_DATA_BUFF
mdefine_line|#define MIDQ_DATA_BUFF&t;&t;&t;&t;0x7060
DECL|macro|DSPQ_DATA_BUFF
mdefine_line|#define DSPQ_DATA_BUFF&t;&t;&t;&t;0x7860
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
DECL|macro|MOP_WAVEHDR
mdefine_line|#define MOP_WAVEHDR&t;&t;&t;&t;0
DECL|macro|MOP_EXTOUT
mdefine_line|#define MOP_EXTOUT&t;&t;&t;&t;1
DECL|macro|MOP_HWINIT
mdefine_line|#define MOP_HWINIT&t;&t;&t;&t;0xfe
DECL|macro|MOP_NONE
mdefine_line|#define MOP_NONE&t;&t;&t;&t;0xff
DECL|macro|MOP_MAX
mdefine_line|#define MOP_MAX&t;&t;&t;&t;&t;1
DECL|macro|MIP_EXTIN
mdefine_line|#define MIP_EXTIN&t;&t;&t;&t;0
DECL|macro|MIP_WAVEHDR
mdefine_line|#define MIP_WAVEHDR&t;&t;&t;&t;1
DECL|macro|MIP_HWINIT
mdefine_line|#define MIP_HWINIT&t;&t;&t;&t;0xfe
DECL|macro|MIP_MAX
mdefine_line|#define MIP_MAX&t;&t;&t;&t;&t;1
multiline_comment|/* Pinnacle/Fiji SMA Common Data */
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
DECL|macro|SMA_wCurrMHdrVolLeft
mdefine_line|#define SMA_wCurrMHdrVolLeft&t;&t;&t;0x000c
DECL|macro|SMA_wCurrMHdrVolRight
mdefine_line|#define SMA_wCurrMHdrVolRight&t;&t;&t;0x000e
DECL|macro|SMA_dwCurrPlayPitch
mdefine_line|#define SMA_dwCurrPlayPitch&t;&t;&t;0x0010
DECL|macro|SMA_dwCurrPlayRate
mdefine_line|#define SMA_dwCurrPlayRate&t;&t;&t;0x0014
DECL|macro|SMA_wCurrMIDIIOPatch
mdefine_line|#define SMA_wCurrMIDIIOPatch&t;&t;&t;0x0018
DECL|macro|SMA_wCurrPlayFormat
mdefine_line|#define SMA_wCurrPlayFormat&t;&t;&t;0x001a
DECL|macro|SMA_wCurrPlaySampleSize
mdefine_line|#define SMA_wCurrPlaySampleSize&t;&t;&t;0x001c
DECL|macro|SMA_wCurrPlayChannels
mdefine_line|#define SMA_wCurrPlayChannels&t;&t;&t;0x001e
DECL|macro|SMA_wCurrPlaySampleRate
mdefine_line|#define SMA_wCurrPlaySampleRate&t;&t;&t;0x0020
DECL|macro|SMA_wCurrRecordFormat
mdefine_line|#define SMA_wCurrRecordFormat&t;&t;&t;0x0022
DECL|macro|SMA_wCurrRecordSampleSize
mdefine_line|#define SMA_wCurrRecordSampleSize&t;&t;0x0024
DECL|macro|SMA_wCurrRecordChannels
mdefine_line|#define SMA_wCurrRecordChannels&t;&t;&t;0x0026
DECL|macro|SMA_wCurrRecordSampleRate
mdefine_line|#define SMA_wCurrRecordSampleRate&t;&t;0x0028
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
DECL|macro|SMA_bMicPotPosLeft
mdefine_line|#define SMA_bMicPotPosLeft&t;&t;&t;0x0034
DECL|macro|SMA_bMicPotPosRight
mdefine_line|#define SMA_bMicPotPosRight&t;&t;&t;0x0035
DECL|macro|SMA_bMicPotMaxLeft
mdefine_line|#define SMA_bMicPotMaxLeft&t;&t;&t;0x0036
DECL|macro|SMA_bMicPotMaxRight
mdefine_line|#define SMA_bMicPotMaxRight&t;&t;&t;0x0037
DECL|macro|SMA_bInPotPosLeft
mdefine_line|#define SMA_bInPotPosLeft&t;&t;&t;0x0038
DECL|macro|SMA_bInPotPosRight
mdefine_line|#define SMA_bInPotPosRight&t;&t;&t;0x0039
DECL|macro|SMA_bAuxPotPosLeft
mdefine_line|#define SMA_bAuxPotPosLeft&t;&t;&t;0x003a
DECL|macro|SMA_bAuxPotPosRight
mdefine_line|#define SMA_bAuxPotPosRight&t;&t;&t;0x003b
DECL|macro|SMA_bInPotMaxLeft
mdefine_line|#define SMA_bInPotMaxLeft&t;&t;&t;0x003c
DECL|macro|SMA_bInPotMaxRight
mdefine_line|#define SMA_bInPotMaxRight&t;&t;&t;0x003d
DECL|macro|SMA_bAuxPotMaxLeft
mdefine_line|#define SMA_bAuxPotMaxLeft&t;&t;&t;0x003e
DECL|macro|SMA_bAuxPotMaxRight
mdefine_line|#define SMA_bAuxPotMaxRight&t;&t;&t;0x003f
DECL|macro|SMA_bInPotMaxMethod
mdefine_line|#define SMA_bInPotMaxMethod&t;&t;&t;0x0040
DECL|macro|SMA_bAuxPotMaxMethod
mdefine_line|#define SMA_bAuxPotMaxMethod&t;&t;&t;0x0041
DECL|macro|SMA_wCurrMastVolLeft
mdefine_line|#define SMA_wCurrMastVolLeft&t;&t;&t;0x0042
DECL|macro|SMA_wCurrMastVolRight
mdefine_line|#define SMA_wCurrMastVolRight&t;&t;&t;0x0044
DECL|macro|SMA_wCalFreqAtoD
mdefine_line|#define SMA_wCalFreqAtoD&t;&t;&t;0x0046
DECL|macro|SMA_wCurrAuxVolLeft
mdefine_line|#define SMA_wCurrAuxVolLeft&t;&t;&t;0x0048
DECL|macro|SMA_wCurrAuxVolRight
mdefine_line|#define SMA_wCurrAuxVolRight&t;&t;&t;0x004a
DECL|macro|SMA_wCurrPlay1VolLeft
mdefine_line|#define SMA_wCurrPlay1VolLeft&t;&t;&t;0x004c
DECL|macro|SMA_wCurrPlay1VolRight
mdefine_line|#define SMA_wCurrPlay1VolRight&t;&t;&t;0x004e
DECL|macro|SMA_wCurrPlay2VolLeft
mdefine_line|#define SMA_wCurrPlay2VolLeft&t;&t;&t;0x0050
DECL|macro|SMA_wCurrPlay2VolRight
mdefine_line|#define SMA_wCurrPlay2VolRight&t;&t;&t;0x0052
DECL|macro|SMA_wCurrPlay3VolLeft
mdefine_line|#define SMA_wCurrPlay3VolLeft&t;&t;&t;0x0054
DECL|macro|SMA_wCurrPlay3VolRight
mdefine_line|#define SMA_wCurrPlay3VolRight&t;&t;&t;0x0056
DECL|macro|SMA_wCurrPlay4VolLeft
mdefine_line|#define SMA_wCurrPlay4VolLeft&t;&t;&t;0x0058
DECL|macro|SMA_wCurrPlay4VolRight
mdefine_line|#define SMA_wCurrPlay4VolRight&t;&t;&t;0x005a
DECL|macro|SMA_wCurrPlay1PeakLeft
mdefine_line|#define SMA_wCurrPlay1PeakLeft&t;&t;&t;0x005c
DECL|macro|SMA_wCurrPlay1PeakRight
mdefine_line|#define SMA_wCurrPlay1PeakRight&t;&t;&t;0x005e
DECL|macro|SMA_wCurrPlay2PeakLeft
mdefine_line|#define SMA_wCurrPlay2PeakLeft&t;&t;&t;0x0060
DECL|macro|SMA_wCurrPlay2PeakRight
mdefine_line|#define SMA_wCurrPlay2PeakRight&t;&t;&t;0x0062
DECL|macro|SMA_wCurrPlay3PeakLeft
mdefine_line|#define SMA_wCurrPlay3PeakLeft&t;&t;&t;0x0064
DECL|macro|SMA_wCurrPlay3PeakRight
mdefine_line|#define SMA_wCurrPlay3PeakRight&t;&t;&t;0x0066
DECL|macro|SMA_wCurrPlay4PeakLeft
mdefine_line|#define SMA_wCurrPlay4PeakLeft&t;&t;&t;0x0068
DECL|macro|SMA_wCurrPlay4PeakRight
mdefine_line|#define SMA_wCurrPlay4PeakRight&t;&t;&t;0x006a
DECL|macro|SMA_wCurrPlayPeakLeft
mdefine_line|#define SMA_wCurrPlayPeakLeft&t;&t;&t;0x006c
DECL|macro|SMA_wCurrPlayPeakRight
mdefine_line|#define SMA_wCurrPlayPeakRight&t;&t;&t;0x006e
DECL|macro|SMA_wCurrDATSR
mdefine_line|#define SMA_wCurrDATSR&t;&t;&t;&t;0x0070
DECL|macro|SMA_wCurrDATRXCHNL
mdefine_line|#define SMA_wCurrDATRXCHNL&t;&t;&t;0x0072
DECL|macro|SMA_wCurrDATTXCHNL
mdefine_line|#define SMA_wCurrDATTXCHNL&t;&t;&t;0x0074
DECL|macro|SMA_wCurrDATRXRate
mdefine_line|#define SMA_wCurrDATRXRate&t;&t;&t;0x0076
DECL|macro|SMA_dwDSPPlayCount
mdefine_line|#define SMA_dwDSPPlayCount&t;&t;&t;0x0078
DECL|macro|SMA__size
mdefine_line|#define SMA__size&t;&t;&t;&t;0x007c
macro_line|#ifdef HAVE_DSPCODEH
macro_line|#  include &quot;pndsperm.c&quot;
macro_line|#  include &quot;pndspini.c&quot;
DECL|macro|PERMCODE
macro_line|#  define PERMCODE&t;&t;pndsperm
DECL|macro|INITCODE
macro_line|#  define INITCODE&t;&t;pndspini
DECL|macro|PERMCODESIZE
macro_line|#  define PERMCODESIZE&t;&t;sizeof(pndsperm)
DECL|macro|INITCODESIZE
macro_line|#  define INITCODESIZE&t;&t;sizeof(pndspini)
macro_line|#else
macro_line|#  ifndef CONFIG_MSNDPIN_INIT_FILE
DECL|macro|CONFIG_MSNDPIN_INIT_FILE
macro_line|#    define CONFIG_MSNDPIN_INIT_FILE&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&quot;/etc/sound/pndspini.bin&quot;
macro_line|#  endif
macro_line|#  ifndef CONFIG_MSNDPIN_PERM_FILE
DECL|macro|CONFIG_MSNDPIN_PERM_FILE
macro_line|#    define CONFIG_MSNDPIN_PERM_FILE&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&quot;/etc/sound/pndsperm.bin&quot;
macro_line|#  endif
DECL|macro|PERMCODEFILE
macro_line|#  define PERMCODEFILE&t;&t;CONFIG_MSNDPIN_PERM_FILE
DECL|macro|INITCODEFILE
macro_line|#  define INITCODEFILE&t;&t;CONFIG_MSNDPIN_INIT_FILE
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
mdefine_line|#define LONGNAME&t;&t;&quot;MultiSound (Pinnacle/Fiji)&quot;
macro_line|#endif /* __MSND_PINNACLE_H */
eof
