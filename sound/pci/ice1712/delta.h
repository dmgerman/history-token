macro_line|#ifndef __SOUND_DELTA_H
DECL|macro|__SOUND_DELTA_H
mdefine_line|#define __SOUND_DELTA_H
multiline_comment|/*&n; *   ALSA driver for ICEnsemble ICE1712 (Envy24)&n; *&n; *   Lowlevel functions for M-Audio Delta 1010, 44, 66, Dio2496, Audiophile&n; *&n; *&t;Copyright (c) 2000 Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|macro|DELTA_DEVICE_DESC
mdefine_line|#define DELTA_DEVICE_DESC &bslash;&n;&t;&t;&quot;{MidiMan M Audio,Delta 1010},&quot;&bslash;&n;&t;&t;&quot;{MidiMan M Audio,Delta DiO 2496},&quot;&bslash;&n;&t;&t;&quot;{MidiMan M Audio,Delta 66},&quot;&bslash;&n;&t;&t;&quot;{MidiMan M Audio,Delta 44},&quot;&bslash;&n;&t;&t;&quot;{MidiMan M Audio,Audiophile 24/96},&quot;
DECL|macro|ICE1712_SUBDEVICE_DELTA1010
mdefine_line|#define ICE1712_SUBDEVICE_DELTA1010&t;0x121430d6
DECL|macro|ICE1712_SUBDEVICE_DELTADIO2496
mdefine_line|#define ICE1712_SUBDEVICE_DELTADIO2496&t;0x121431d6
DECL|macro|ICE1712_SUBDEVICE_DELTA66
mdefine_line|#define ICE1712_SUBDEVICE_DELTA66&t;0x121432d6
DECL|macro|ICE1712_SUBDEVICE_DELTA44
mdefine_line|#define ICE1712_SUBDEVICE_DELTA44&t;0x121433d6
DECL|macro|ICE1712_SUBDEVICE_AUDIOPHILE
mdefine_line|#define ICE1712_SUBDEVICE_AUDIOPHILE&t;0x121434d6
DECL|macro|ICE1712_SUBDEVICE_DELTA1010LT
mdefine_line|#define ICE1712_SUBDEVICE_DELTA1010LT&t;0x12143bd6
multiline_comment|/* entry point */
r_extern
r_struct
id|snd_ice1712_card_info
id|snd_ice1712_delta_cards
(braket
)braket
suffix:semicolon
multiline_comment|/*&n; *  MidiMan M-Audio Delta GPIO definitions&n; */
multiline_comment|/* MidiMan M-Audio Delta1010 */
DECL|macro|ICE1712_DELTA_DFS
mdefine_line|#define ICE1712_DELTA_DFS 0x01&t;&t;/* fast/slow sample rate mode */
multiline_comment|/* (&gt;48kHz must be 1) */
DECL|macro|ICE1712_DELTA_SPDIF_IN_STAT
mdefine_line|#define ICE1712_DELTA_SPDIF_IN_STAT 0x02
multiline_comment|/* S/PDIF input status */
multiline_comment|/* 0 = valid signal is present */
multiline_comment|/* all except Delta44 */
multiline_comment|/* look to CS8414 datasheet */
DECL|macro|ICE1712_DELTA_SPDIF_OUT_STAT_CLOCK
mdefine_line|#define ICE1712_DELTA_SPDIF_OUT_STAT_CLOCK 0x04
multiline_comment|/* S/PDIF output status clock */
multiline_comment|/* (writting on rising edge - 0-&gt;1) */
multiline_comment|/* all except Delta44 */
multiline_comment|/* look to CS8404A datasheet */
DECL|macro|ICE1712_DELTA_SPDIF_OUT_STAT_DATA
mdefine_line|#define ICE1712_DELTA_SPDIF_OUT_STAT_DATA 0x08
multiline_comment|/* S/PDIF output status data */
multiline_comment|/* all except Delta44 */
multiline_comment|/* look to CS8404A datasheet */
multiline_comment|/* MidiMan M-Audio DeltaDiO */
multiline_comment|/* 0x01 = DFS */
multiline_comment|/* 0x02 = SPDIF_IN_STAT */
multiline_comment|/* 0x04 = SPDIF_OUT_STAT_CLOCK */
multiline_comment|/* 0x08 = SPDIF_OUT_STAT_DATA */
DECL|macro|ICE1712_DELTA_SPDIF_INPUT_SELECT
mdefine_line|#define ICE1712_DELTA_SPDIF_INPUT_SELECT 0x10
multiline_comment|/* coaxial (0), optical (1) */
multiline_comment|/* S/PDIF input select*/
multiline_comment|/* MidiMan M-Audio Delta1010 */
multiline_comment|/* 0x01 = DFS */
multiline_comment|/* 0x02 = SPDIF_IN_STAT */
multiline_comment|/* 0x04 = SPDIF_OUT_STAT_CLOCK */
multiline_comment|/* 0x08 = SPDIF_OUT_STAT_DATA */
DECL|macro|ICE1712_DELTA_WORD_CLOCK_SELECT
mdefine_line|#define ICE1712_DELTA_WORD_CLOCK_SELECT 0x10
multiline_comment|/* 1 - clock are taken from S/PDIF input */
multiline_comment|/* 0 - clock are taken from Word Clock input */
multiline_comment|/* affected SPMCLKIN pin of Envy24 */
DECL|macro|ICE1712_DELTA_WORD_CLOCK_STATUS
mdefine_line|#define ICE1712_DELTA_WORD_CLOCK_STATUS&t;0x20
multiline_comment|/* 0 = valid word clock signal is present */
multiline_comment|/* MidiMan M-Audio Delta66 */
multiline_comment|/* 0x01 = DFS */
multiline_comment|/* 0x02 = SPDIF_IN_STAT */
multiline_comment|/* 0x04 = SPDIF_OUT_STAT_CLOCK */
multiline_comment|/* 0x08 = SPDIF_OUT_STAT_DATA */
DECL|macro|ICE1712_DELTA_CODEC_SERIAL_DATA
mdefine_line|#define ICE1712_DELTA_CODEC_SERIAL_DATA 0x10
multiline_comment|/* AKM4524 serial data */
DECL|macro|ICE1712_DELTA_CODEC_SERIAL_CLOCK
mdefine_line|#define ICE1712_DELTA_CODEC_SERIAL_CLOCK 0x20
multiline_comment|/* AKM4524 serial clock */
multiline_comment|/* (writting on rising edge - 0-&gt;1 */
DECL|macro|ICE1712_DELTA_CODEC_CHIP_A
mdefine_line|#define ICE1712_DELTA_CODEC_CHIP_A&t;0x40
DECL|macro|ICE1712_DELTA_CODEC_CHIP_B
mdefine_line|#define ICE1712_DELTA_CODEC_CHIP_B&t;0x80
multiline_comment|/* 1 - select chip A or B */
multiline_comment|/* MidiMan M-Audio Delta44 */
multiline_comment|/* 0x01 = DFS */
multiline_comment|/* 0x10 = CODEC_SERIAL_DATA */
multiline_comment|/* 0x20 = CODEC_SERIAL_CLOCK */
multiline_comment|/* 0x40 = CODEC_CHIP_A */
multiline_comment|/* 0x80 = CODEC_CHIP_B */
multiline_comment|/* MidiMan M-Audio Audiophile definitions */
multiline_comment|/* 0x01 = DFS */
DECL|macro|ICE1712_DELTA_AP_CCLK
mdefine_line|#define ICE1712_DELTA_AP_CCLK&t;0x02&t;/* SPI clock */
multiline_comment|/* (clocking on rising edge - 0-&gt;1) */
DECL|macro|ICE1712_DELTA_AP_DIN
mdefine_line|#define ICE1712_DELTA_AP_DIN&t;0x04&t;/* data input */
DECL|macro|ICE1712_DELTA_AP_DOUT
mdefine_line|#define ICE1712_DELTA_AP_DOUT&t;0x08&t;/* data output */
DECL|macro|ICE1712_DELTA_AP_CS_DIGITAL
mdefine_line|#define ICE1712_DELTA_AP_CS_DIGITAL 0x10 /* CS8427 chip select */
multiline_comment|/* low signal = select */
DECL|macro|ICE1712_DELTA_AP_CS_CODEC
mdefine_line|#define ICE1712_DELTA_AP_CS_CODEC 0x20&t;/* AK4528 chip select */
multiline_comment|/* low signal = select */
macro_line|#endif /* __SOUND_DELTA_H */
eof
