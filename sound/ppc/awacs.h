multiline_comment|/*&n; * Driver for PowerMac AWACS onboard soundchips&n; * Copyright (c) 2001 by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *   based on dmasound.c.&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#ifndef __AWACS_H
DECL|macro|__AWACS_H
mdefine_line|#define __AWACS_H
multiline_comment|/*******************************/
multiline_comment|/* AWACs Audio Register Layout */
multiline_comment|/*******************************/
DECL|struct|awacs_regs
r_struct
id|awacs_regs
(brace
DECL|member|control
r_int
id|control
suffix:semicolon
multiline_comment|/* Audio control register */
DECL|member|pad0
r_int
id|pad0
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|codec_ctrl
r_int
id|codec_ctrl
suffix:semicolon
multiline_comment|/* Codec control register */
DECL|member|pad1
r_int
id|pad1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|codec_stat
r_int
id|codec_stat
suffix:semicolon
multiline_comment|/* Codec status register */
DECL|member|pad2
r_int
id|pad2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|clip_count
r_int
id|clip_count
suffix:semicolon
multiline_comment|/* Clipping count register */
DECL|member|pad3
r_int
id|pad3
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|byteswap
r_int
id|byteswap
suffix:semicolon
multiline_comment|/* Data is little-endian if 1 */
)brace
suffix:semicolon
multiline_comment|/*******************/
multiline_comment|/* Audio Bit Masks */
multiline_comment|/*******************/
multiline_comment|/* Audio Control Reg Bit Masks */
multiline_comment|/* ----- ------- --- --- ----- */
DECL|macro|MASK_ISFSEL
mdefine_line|#define MASK_ISFSEL&t;(0xf)&t;&t;/* Input SubFrame Select */
DECL|macro|MASK_OSFSEL
mdefine_line|#define MASK_OSFSEL&t;(0xf &lt;&lt; 4)&t;/* Output SubFrame Select */
DECL|macro|MASK_RATE
mdefine_line|#define MASK_RATE&t;(0x7 &lt;&lt; 8)&t;/* Sound Rate */
DECL|macro|MASK_CNTLERR
mdefine_line|#define MASK_CNTLERR&t;(0x1 &lt;&lt; 11)&t;/* Error */
DECL|macro|MASK_PORTCHG
mdefine_line|#define MASK_PORTCHG&t;(0x1 &lt;&lt; 12)&t;/* Port Change */
DECL|macro|MASK_IEE
mdefine_line|#define MASK_IEE&t;(0x1 &lt;&lt; 13)&t;/* Enable Interrupt on Error */
DECL|macro|MASK_IEPC
mdefine_line|#define MASK_IEPC&t;(0x1 &lt;&lt; 14)&t;/* Enable Interrupt on Port Change */
DECL|macro|MASK_SSFSEL
mdefine_line|#define MASK_SSFSEL&t;(0x3 &lt;&lt; 15)&t;/* Status SubFrame Select */
multiline_comment|/* Audio Codec Control Reg Bit Masks */
multiline_comment|/* ----- ----- ------- --- --- ----- */
DECL|macro|MASK_NEWECMD
mdefine_line|#define MASK_NEWECMD&t;(0x1 &lt;&lt; 24)&t;/* Lock: don&squot;t write to reg when 1 */
DECL|macro|MASK_EMODESEL
mdefine_line|#define MASK_EMODESEL&t;(0x3 &lt;&lt; 22)&t;/* Send info out on which frame? */
DECL|macro|MASK_EXMODEADDR
mdefine_line|#define MASK_EXMODEADDR&t;(0x3ff &lt;&lt; 12)&t;/* Extended Mode Address -- 10 bits */
DECL|macro|MASK_EXMODEDATA
mdefine_line|#define MASK_EXMODEDATA&t;(0xfff)&t;&t;/* Extended Mode Data -- 12 bits */
multiline_comment|/* Audio Codec Control Address Values / Masks */
multiline_comment|/* ----- ----- ------- ------- ------ - ----- */
DECL|macro|MASK_ADDR0
mdefine_line|#define MASK_ADDR0&t;(0x0 &lt;&lt; 12)&t;/* Expanded Data Mode Address 0 */
DECL|macro|MASK_ADDR_MUX
mdefine_line|#define MASK_ADDR_MUX&t;MASK_ADDR0&t;/* Mux Control */
DECL|macro|MASK_ADDR_GAIN
mdefine_line|#define MASK_ADDR_GAIN&t;MASK_ADDR0
DECL|macro|MASK_ADDR1
mdefine_line|#define MASK_ADDR1&t;(0x1 &lt;&lt; 12)&t;/* Expanded Data Mode Address 1 */
DECL|macro|MASK_ADDR_MUTE
mdefine_line|#define MASK_ADDR_MUTE&t;MASK_ADDR1
DECL|macro|MASK_ADDR_RATE
mdefine_line|#define MASK_ADDR_RATE&t;MASK_ADDR1
DECL|macro|MASK_ADDR2
mdefine_line|#define MASK_ADDR2&t;(0x2 &lt;&lt; 12)&t;/* Expanded Data Mode Address 2 */
DECL|macro|MASK_ADDR_VOLA
mdefine_line|#define MASK_ADDR_VOLA&t;MASK_ADDR2&t;/* Volume Control A -- Headphones */
DECL|macro|MASK_ADDR_VOLHD
mdefine_line|#define MASK_ADDR_VOLHD MASK_ADDR2
DECL|macro|MASK_ADDR4
mdefine_line|#define MASK_ADDR4&t;(0x4 &lt;&lt; 12)&t;/* Expanded Data Mode Address 4 */
DECL|macro|MASK_ADDR_VOLC
mdefine_line|#define MASK_ADDR_VOLC&t;MASK_ADDR4&t;/* Volume Control C -- Speaker */
DECL|macro|MASK_ADDR_VOLSPK
mdefine_line|#define MASK_ADDR_VOLSPK MASK_ADDR4
multiline_comment|/* additional registers of screamer */
DECL|macro|MASK_ADDR5
mdefine_line|#define MASK_ADDR5&t;(0x5 &lt;&lt; 12)&t;/* Expanded Data Mode Address 5 */
DECL|macro|MASK_ADDR6
mdefine_line|#define MASK_ADDR6&t;(0x6 &lt;&lt; 12)&t;/* Expanded Data Mode Address 6 */
DECL|macro|MASK_ADDR7
mdefine_line|#define MASK_ADDR7&t;(0x7 &lt;&lt; 12)&t;/* Expanded Data Mode Address 7 */
multiline_comment|/* Address 0 Bit Masks &amp; Macros */
multiline_comment|/* ------- - --- ----- - ------ */
DECL|macro|MASK_GAINRIGHT
mdefine_line|#define MASK_GAINRIGHT&t;(0xf)&t;&t;/* Gain Right Mask */
DECL|macro|MASK_GAINLEFT
mdefine_line|#define MASK_GAINLEFT&t;(0xf &lt;&lt; 4)&t;/* Gain Left Mask */
DECL|macro|MASK_GAINLINE
mdefine_line|#define MASK_GAINLINE&t;(0x1 &lt;&lt; 8)&t;/* Disable Mic preamp */
DECL|macro|MASK_GAINMIC
mdefine_line|#define MASK_GAINMIC&t;(0x0 &lt;&lt; 8)&t;/* Enable Mic preamp */
DECL|macro|MASK_MUX_CD
mdefine_line|#define MASK_MUX_CD&t;(0x1 &lt;&lt; 9)&t;/* Select CD in MUX */
DECL|macro|MASK_MUX_MIC
mdefine_line|#define MASK_MUX_MIC&t;(0x1 &lt;&lt; 10)&t;/* Select Mic in MUX */
DECL|macro|MASK_MUX_AUDIN
mdefine_line|#define MASK_MUX_AUDIN&t;(0x1 &lt;&lt; 11)&t;/* Select Audio In in MUX */
DECL|macro|MASK_MUX_LINE
mdefine_line|#define MASK_MUX_LINE&t;MASK_MUX_AUDIN
DECL|macro|SHIFT_GAINLINE
mdefine_line|#define SHIFT_GAINLINE&t;8
DECL|macro|SHIFT_MUX_CD
mdefine_line|#define SHIFT_MUX_CD&t;9
DECL|macro|SHIFT_MUX_MIC
mdefine_line|#define SHIFT_MUX_MIC&t;10
DECL|macro|SHIFT_MUX_LINE
mdefine_line|#define SHIFT_MUX_LINE&t;11
DECL|macro|GAINRIGHT
mdefine_line|#define GAINRIGHT(x)&t;((x) &amp; MASK_GAINRIGHT)
DECL|macro|GAINLEFT
mdefine_line|#define GAINLEFT(x)&t;(((x) &lt;&lt; 4) &amp; MASK_GAINLEFT)
multiline_comment|/* Address 1 Bit Masks */
multiline_comment|/* ------- - --- ----- */
DECL|macro|MASK_ADDR1RES1
mdefine_line|#define MASK_ADDR1RES1&t;(0x3)&t;&t;/* Reserved */
DECL|macro|MASK_RECALIBRATE
mdefine_line|#define MASK_RECALIBRATE (0x1 &lt;&lt; 2)&t;/* Recalibrate */
DECL|macro|MASK_SAMPLERATE
mdefine_line|#define MASK_SAMPLERATE&t;(0x7 &lt;&lt; 3)&t;/* Sample Rate: */
DECL|macro|MASK_LOOPTHRU
mdefine_line|#define MASK_LOOPTHRU&t;(0x1 &lt;&lt; 6)&t;/* Loopthrough Enable */
DECL|macro|SHIFT_LOOPTHRU
mdefine_line|#define SHIFT_LOOPTHRU&t;6
DECL|macro|MASK_CMUTE
mdefine_line|#define MASK_CMUTE&t;(0x1 &lt;&lt; 7)&t;/* Output C (Speaker) Mute when 1 */
DECL|macro|MASK_SPKMUTE
mdefine_line|#define MASK_SPKMUTE&t;MASK_CMUTE
DECL|macro|SHIFT_SPKMUTE
mdefine_line|#define SHIFT_SPKMUTE&t;7
DECL|macro|MASK_ADDR1RES2
mdefine_line|#define MASK_ADDR1RES2&t;(0x1 &lt;&lt; 8)&t;/* Reserved */
DECL|macro|MASK_AMUTE
mdefine_line|#define MASK_AMUTE&t;(0x1 &lt;&lt; 9)&t;/* Output A (Headphone) Mute when 1 */
DECL|macro|MASK_HDMUTE
mdefine_line|#define MASK_HDMUTE&t;MASK_AMUTE
DECL|macro|SHIFT_HDMUTE
mdefine_line|#define SHIFT_HDMUTE&t;9
DECL|macro|MASK_PAROUT
mdefine_line|#define MASK_PAROUT&t;(0x3 &lt;&lt; 10)&t;/* Parallel Out (???) */
DECL|macro|SAMPLERATE_48000
mdefine_line|#define SAMPLERATE_48000&t;(0x0 &lt;&lt; 3)&t;/* 48 or 44.1 kHz */
DECL|macro|SAMPLERATE_32000
mdefine_line|#define SAMPLERATE_32000&t;(0x1 &lt;&lt; 3)&t;/* 32 or 29.4 kHz */
DECL|macro|SAMPLERATE_24000
mdefine_line|#define SAMPLERATE_24000&t;(0x2 &lt;&lt; 3)&t;/* 24 or 22.05 kHz */
DECL|macro|SAMPLERATE_19200
mdefine_line|#define SAMPLERATE_19200&t;(0x3 &lt;&lt; 3)&t;/* 19.2 or 17.64 kHz */
DECL|macro|SAMPLERATE_16000
mdefine_line|#define SAMPLERATE_16000&t;(0x4 &lt;&lt; 3)&t;/* 16 or 14.7 kHz */
DECL|macro|SAMPLERATE_12000
mdefine_line|#define SAMPLERATE_12000&t;(0x5 &lt;&lt; 3)&t;/* 12 or 11.025 kHz */
DECL|macro|SAMPLERATE_9600
mdefine_line|#define SAMPLERATE_9600&t;&t;(0x6 &lt;&lt; 3)&t;/* 9.6 or 8.82 kHz */
DECL|macro|SAMPLERATE_8000
mdefine_line|#define SAMPLERATE_8000&t;&t;(0x7 &lt;&lt; 3)&t;/* 8 or 7.35 kHz */
multiline_comment|/* Address 2 &amp; 4 Bit Masks &amp; Macros */
multiline_comment|/* ------- - - - --- ----- - ------ */
DECL|macro|MASK_OUTVOLRIGHT
mdefine_line|#define MASK_OUTVOLRIGHT (0xf)&t;&t;/* Output Right Volume */
DECL|macro|MASK_ADDR2RES1
mdefine_line|#define MASK_ADDR2RES1&t;(0x2 &lt;&lt; 4)&t;/* Reserved */
DECL|macro|MASK_ADDR4RES1
mdefine_line|#define MASK_ADDR4RES1&t;MASK_ADDR2RES1
DECL|macro|MASK_OUTVOLLEFT
mdefine_line|#define MASK_OUTVOLLEFT&t;(0xf &lt;&lt; 6)&t;/* Output Left Volume */
DECL|macro|MASK_ADDR2RES2
mdefine_line|#define MASK_ADDR2RES2&t;(0x2 &lt;&lt; 10)&t;/* Reserved */
DECL|macro|MASK_ADDR4RES2
mdefine_line|#define MASK_ADDR4RES2&t;MASK_ADDR2RES2
DECL|macro|VOLRIGHT
mdefine_line|#define VOLRIGHT(x)&t;(((~(x)) &amp; MASK_OUTVOLRIGHT))
DECL|macro|VOLLEFT
mdefine_line|#define VOLLEFT(x)&t;(((~(x)) &lt;&lt; 6) &amp; MASK_OUTVOLLEFT)
multiline_comment|/* address 6 */
DECL|macro|MASK_MIC_BOOST
mdefine_line|#define MASK_MIC_BOOST  (0x4)           /* screamer mic boost */
DECL|macro|SHIFT_MIC_BOOST
mdefine_line|#define SHIFT_MIC_BOOST&t;2
multiline_comment|/* Audio Codec Status Reg Bit Masks */
multiline_comment|/* ----- ----- ------ --- --- ----- */
DECL|macro|MASK_EXTEND
mdefine_line|#define MASK_EXTEND&t;(0x1 &lt;&lt; 23)&t;/* Extend */
DECL|macro|MASK_VALID
mdefine_line|#define MASK_VALID&t;(0x1 &lt;&lt; 22)&t;/* Valid Data? */
DECL|macro|MASK_OFLEFT
mdefine_line|#define MASK_OFLEFT&t;(0x1 &lt;&lt; 21)&t;/* Overflow Left */
DECL|macro|MASK_OFRIGHT
mdefine_line|#define MASK_OFRIGHT&t;(0x1 &lt;&lt; 20)&t;/* Overflow Right */
DECL|macro|MASK_ERRCODE
mdefine_line|#define MASK_ERRCODE&t;(0xf &lt;&lt; 16)&t;/* Error Code */
DECL|macro|MASK_REVISION
mdefine_line|#define MASK_REVISION&t;(0xf &lt;&lt; 12)&t;/* Revision Number */
DECL|macro|MASK_MFGID
mdefine_line|#define MASK_MFGID&t;(0xf &lt;&lt; 8)&t;/* Mfg. ID */
DECL|macro|MASK_CODSTATRES
mdefine_line|#define MASK_CODSTATRES&t;(0xf &lt;&lt; 4)&t;/* bits 4 - 7 reserved */
DECL|macro|MASK_INPPORT
mdefine_line|#define MASK_INPPORT&t;(0xf)&t;&t;/* Input Port */
DECL|macro|MASK_HDPCONN
mdefine_line|#define MASK_HDPCONN&t;8&t;&t;/* headphone plugged in */
multiline_comment|/* Clipping Count Reg Bit Masks */
multiline_comment|/* -------- ----- --- --- ----- */
DECL|macro|MASK_CLIPLEFT
mdefine_line|#define MASK_CLIPLEFT&t;(0xff &lt;&lt; 7)&t;/* Clipping Count, Left Channel */
DECL|macro|MASK_CLIPRIGHT
mdefine_line|#define MASK_CLIPRIGHT&t;(0xff)&t;&t;/* Clipping Count, Right Channel */
multiline_comment|/* DBDMA ChannelStatus Bit Masks */
multiline_comment|/* ----- ------------- --- ----- */
DECL|macro|MASK_CSERR
mdefine_line|#define MASK_CSERR&t;(0x1 &lt;&lt; 7)&t;/* Error */
DECL|macro|MASK_EOI
mdefine_line|#define MASK_EOI&t;(0x1 &lt;&lt; 6)&t;/* End of Input -- only for Input Channel */
DECL|macro|MASK_CSUNUSED
mdefine_line|#define MASK_CSUNUSED&t;(0x1f &lt;&lt; 1)&t;/* bits 1-5 not used */
DECL|macro|MASK_WAIT
mdefine_line|#define MASK_WAIT&t;(0x1)&t;&t;/* Wait */
multiline_comment|/* Various Rates */
multiline_comment|/* ------- ----- */
DECL|macro|RATE_48000
mdefine_line|#define RATE_48000&t;(0x0 &lt;&lt; 8)&t;/* 48 kHz */
DECL|macro|RATE_44100
mdefine_line|#define RATE_44100&t;(0x0 &lt;&lt; 8)&t;/* 44.1 kHz */
DECL|macro|RATE_32000
mdefine_line|#define RATE_32000&t;(0x1 &lt;&lt; 8)&t;/* 32 kHz */
DECL|macro|RATE_29400
mdefine_line|#define RATE_29400&t;(0x1 &lt;&lt; 8)&t;/* 29.4 kHz */
DECL|macro|RATE_24000
mdefine_line|#define RATE_24000&t;(0x2 &lt;&lt; 8)&t;/* 24 kHz */
DECL|macro|RATE_22050
mdefine_line|#define RATE_22050&t;(0x2 &lt;&lt; 8)&t;/* 22.05 kHz */
DECL|macro|RATE_19200
mdefine_line|#define RATE_19200&t;(0x3 &lt;&lt; 8)&t;/* 19.2 kHz */
DECL|macro|RATE_17640
mdefine_line|#define RATE_17640&t;(0x3 &lt;&lt; 8)&t;/* 17.64 kHz */
DECL|macro|RATE_16000
mdefine_line|#define RATE_16000&t;(0x4 &lt;&lt; 8)&t;/* 16 kHz */
DECL|macro|RATE_14700
mdefine_line|#define RATE_14700&t;(0x4 &lt;&lt; 8)&t;/* 14.7 kHz */
DECL|macro|RATE_12000
mdefine_line|#define RATE_12000&t;(0x5 &lt;&lt; 8)&t;/* 12 kHz */
DECL|macro|RATE_11025
mdefine_line|#define RATE_11025&t;(0x5 &lt;&lt; 8)&t;/* 11.025 kHz */
DECL|macro|RATE_9600
mdefine_line|#define RATE_9600&t;(0x6 &lt;&lt; 8)&t;/* 9.6 kHz */
DECL|macro|RATE_8820
mdefine_line|#define RATE_8820&t;(0x6 &lt;&lt; 8)&t;/* 8.82 kHz */
DECL|macro|RATE_8000
mdefine_line|#define RATE_8000&t;(0x7 &lt;&lt; 8)&t;/* 8 kHz */
DECL|macro|RATE_7350
mdefine_line|#define RATE_7350&t;(0x7 &lt;&lt; 8)&t;/* 7.35 kHz */
DECL|macro|RATE_LOW
mdefine_line|#define RATE_LOW&t;1&t;/* HIGH = 48kHz, etc;  LOW = 44.1kHz, etc. */
macro_line|#endif /* __AWACS_H */
eof
