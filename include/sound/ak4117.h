macro_line|#ifndef __SOUND_AK4117_H
DECL|macro|__SOUND_AK4117_H
mdefine_line|#define __SOUND_AK4117_H
multiline_comment|/*&n; *  Routines for Asahi Kasei AK4117&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;,&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|macro|AK4117_REG_PWRDN
mdefine_line|#define AK4117_REG_PWRDN&t;0x00&t;/* power down */
DECL|macro|AK4117_REG_CLOCK
mdefine_line|#define AK4117_REG_CLOCK&t;0x01&t;/* clock control */
DECL|macro|AK4117_REG_IO
mdefine_line|#define AK4117_REG_IO&t;&t;0x02&t;/* input/output control */
DECL|macro|AK4117_REG_INT0_MASK
mdefine_line|#define AK4117_REG_INT0_MASK&t;0x03&t;/* interrupt0 mask */
DECL|macro|AK4117_REG_INT1_MASK
mdefine_line|#define AK4117_REG_INT1_MASK&t;0x04&t;/* interrupt1 mask */
DECL|macro|AK4117_REG_RCS0
mdefine_line|#define AK4117_REG_RCS0&t;&t;0x05&t;/* receiver status 0 */
DECL|macro|AK4117_REG_RCS1
mdefine_line|#define AK4117_REG_RCS1&t;&t;0x06&t;/* receiver status 1 */
DECL|macro|AK4117_REG_RCS2
mdefine_line|#define AK4117_REG_RCS2&t;&t;0x07&t;/* receiver status 2 */
DECL|macro|AK4117_REG_RXCSB0
mdefine_line|#define AK4117_REG_RXCSB0&t;0x08&t;/* RX channel status byte 0 */
DECL|macro|AK4117_REG_RXCSB1
mdefine_line|#define AK4117_REG_RXCSB1&t;0x09&t;/* RX channel status byte 1 */
DECL|macro|AK4117_REG_RXCSB2
mdefine_line|#define AK4117_REG_RXCSB2&t;0x0a&t;/* RX channel status byte 2 */
DECL|macro|AK4117_REG_RXCSB3
mdefine_line|#define AK4117_REG_RXCSB3&t;0x0b&t;/* RX channel status byte 3 */
DECL|macro|AK4117_REG_RXCSB4
mdefine_line|#define AK4117_REG_RXCSB4&t;0x0c&t;/* RX channel status byte 4 */
DECL|macro|AK4117_REG_Pc0
mdefine_line|#define AK4117_REG_Pc0&t;&t;0x0d&t;/* burst preamble Pc byte 0 */
DECL|macro|AK4117_REG_Pc1
mdefine_line|#define AK4117_REG_Pc1&t;&t;0x0e&t;/* burst preamble Pc byte 1 */
DECL|macro|AK4117_REG_Pd0
mdefine_line|#define AK4117_REG_Pd0&t;&t;0x0f&t;/* burst preamble Pd byte 0 */
DECL|macro|AK4117_REG_Pd1
mdefine_line|#define AK4117_REG_Pd1&t;&t;0x10&t;/* burst preamble Pd byte 1 */
DECL|macro|AK4117_REG_QSUB_ADDR
mdefine_line|#define AK4117_REG_QSUB_ADDR&t;0x11&t;/* Q-subcode address + control */
DECL|macro|AK4117_REG_QSUB_TRACK
mdefine_line|#define AK4117_REG_QSUB_TRACK&t;0x12&t;/* Q-subcode track */
DECL|macro|AK4117_REG_QSUB_INDEX
mdefine_line|#define AK4117_REG_QSUB_INDEX&t;0x13&t;/* Q-subcode index */
DECL|macro|AK4117_REG_QSUB_MINUTE
mdefine_line|#define AK4117_REG_QSUB_MINUTE&t;0x14&t;/* Q-subcode minute */
DECL|macro|AK4117_REG_QSUB_SECOND
mdefine_line|#define AK4117_REG_QSUB_SECOND&t;0x15&t;/* Q-subcode second */
DECL|macro|AK4117_REG_QSUB_FRAME
mdefine_line|#define AK4117_REG_QSUB_FRAME&t;0x16&t;/* Q-subcode frame */
DECL|macro|AK4117_REG_QSUB_ZERO
mdefine_line|#define AK4117_REG_QSUB_ZERO&t;0x17&t;/* Q-subcode zero */
DECL|macro|AK4117_REG_QSUB_ABSMIN
mdefine_line|#define AK4117_REG_QSUB_ABSMIN&t;0x18&t;/* Q-subcode absolute minute */
DECL|macro|AK4117_REG_QSUB_ABSSEC
mdefine_line|#define AK4117_REG_QSUB_ABSSEC&t;0x19&t;/* Q-subcode absolute second */
DECL|macro|AK4117_REG_QSUB_ABSFRM
mdefine_line|#define AK4117_REG_QSUB_ABSFRM&t;0x1a&t;/* Q-subcode absolute frame */
multiline_comment|/* sizes */
DECL|macro|AK4117_REG_RXCSB_SIZE
mdefine_line|#define AK4117_REG_RXCSB_SIZE&t;((AK4117_REG_RXCSB4-AK4117_REG_RXCSB0)+1)
DECL|macro|AK4117_REG_QSUB_SIZE
mdefine_line|#define AK4117_REG_QSUB_SIZE&t;((AK4117_REG_QSUB_ABSFRM-AK4117_REG_QSUB_ADDR)+1)
multiline_comment|/* AK4117_REG_PWRDN bits */
DECL|macro|AK4117_EXCT
mdefine_line|#define AK4117_EXCT&t;&t;(1&lt;&lt;4)&t;/* 0 = X&squot;tal mode, 1 = external clock mode */
DECL|macro|AK4117_XTL1
mdefine_line|#define AK4117_XTL1&t;&t;(1&lt;&lt;3)&t;/* XTL1=0,XTL0=0 -&gt; 11.2896Mhz; XTL1=0,XTL0=1 -&gt; 12.288Mhz */
DECL|macro|AK4117_XTL0
mdefine_line|#define AK4117_XTL0&t;&t;(1&lt;&lt;2)&t;/* XTL1=1,XTL0=0 -&gt; 24.576Mhz; XTL1=1,XTL0=1 -&gt; use channel status */
DECL|macro|AK4117_XTL_11_2896M
mdefine_line|#define AK4117_XTL_11_2896M&t;(0)
DECL|macro|AK4117_XTL_12_288M
mdefine_line|#define AK4117_XTL_12_288M&t;AK4117_XTL0
DECL|macro|AK4117_XTL_24_576M
mdefine_line|#define AK4117_XTL_24_576M&t;AK4117_XTL1
DECL|macro|AK4117_XTL_EXT
mdefine_line|#define AK4117_XTL_EXT&t;&t;(AK4117_XTL1|AK4117_XTL0)
DECL|macro|AK4117_PWN
mdefine_line|#define AK4117_PWN&t;&t;(1&lt;&lt;1)&t;/* 0 = power down, 1 = normal operation */
DECL|macro|AK4117_RST
mdefine_line|#define AK4117_RST&t;&t;(1&lt;&lt;0)&t;/* 0 = reset &amp; initialize (except this register), 1 = normal operation */
multiline_comment|/* AK4117_REQ_CLOCK bits */
DECL|macro|AK4117_LP
mdefine_line|#define AK4117_LP&t;&t;(1&lt;&lt;7)&t;/* 0 = normal mode, 1 = low power mode (Fs up to 48kHz only) */
DECL|macro|AK4117_PKCS1
mdefine_line|#define AK4117_PKCS1&t;&t;(1&lt;&lt;6)&t;/* master clock frequency at PLL mode (when LP == 0) */
DECL|macro|AK4117_PKCS0
mdefine_line|#define AK4117_PKCS0&t;&t;(1&lt;&lt;5)
DECL|macro|AK4117_PKCS_512fs
mdefine_line|#define AK4117_PKCS_512fs&t;(0)
DECL|macro|AK4117_PKCS_256fs
mdefine_line|#define AK4117_PKCS_256fs&t;AK4117_PKCS0
DECL|macro|AK4117_PKCS_128fs
mdefine_line|#define AK4117_PKCS_128fs&t;AK4117_PKCS1
DECL|macro|AK4117_DIV
mdefine_line|#define AK4117_DIV&t;&t;(1&lt;&lt;4)&t;/* 0 = MCKO == Fs, 1 = MCKO == Fs / 2; X&squot;tal mode only */
DECL|macro|AK4117_XCKS1
mdefine_line|#define AK4117_XCKS1&t;&t;(1&lt;&lt;3)&t;/* master clock frequency at X&squot;tal mode */
DECL|macro|AK4117_XCKS0
mdefine_line|#define AK4117_XCKS0&t;&t;(1&lt;&lt;2)
DECL|macro|AK4117_XCKS_128fs
mdefine_line|#define AK4117_XCKS_128fs&t;(0)
DECL|macro|AK4117_XCKS_256fs
mdefine_line|#define AK4117_XCKS_256fs&t;AK4117_XCKS0
DECL|macro|AK4117_XCKS_512fs
mdefine_line|#define AK4117_XCKS_512fs&t;AK4117_XCKS1
DECL|macro|AK4117_XCKS_1024fs
mdefine_line|#define AK4117_XCKS_1024fs&t;(AK4117_XCKS1|AK4117_XCKS0)
DECL|macro|AK4117_CM1
mdefine_line|#define AK4117_CM1&t;&t;(1&lt;&lt;1)&t;/* MCKO operation mode select */
DECL|macro|AK4117_CM0
mdefine_line|#define AK4117_CM0&t;&t;(1&lt;&lt;0)
DECL|macro|AK4117_CM_PLL
mdefine_line|#define AK4117_CM_PLL&t;&t;(0)&t;&t;/* use RX input as master clock */
DECL|macro|AK4117_CM_XTAL
mdefine_line|#define AK4117_CM_XTAL&t;&t;(AK4117_CM0)&t;/* use X&squot;tal as master clock */
DECL|macro|AK4117_CM_PLL_XTAL
mdefine_line|#define AK4117_CM_PLL_XTAL&t;(AK4117_CM1)&t;/* use Rx input but X&squot;tal when PLL loses lock */
DECL|macro|AK4117_CM_MONITOR
mdefine_line|#define AK4117_CM_MONITOR&t;(AK4117_CM0|AK4117_CM1) /* use X&squot;tal as master clock, but use PLL for monitoring */
multiline_comment|/* AK4117_REG_IO */
DECL|macro|AK4117_IPS
mdefine_line|#define AK4117_IPS&t;&t;(1&lt;&lt;7)&t;/* Input Recovery Data Select, 0 = RX0, 1 = RX1 */
DECL|macro|AK4117_UOUTE
mdefine_line|#define AK4117_UOUTE&t;&t;(1&lt;&lt;6)&t;/* U-bit output enable to UOUT, 0 = disable, 1 = enable */
DECL|macro|AK4117_CS12
mdefine_line|#define AK4117_CS12&t;&t;(1&lt;&lt;5)&t;/* channel status select, 0 = channel1, 1 = channel2 */
DECL|macro|AK4117_EFH2
mdefine_line|#define AK4117_EFH2&t;&t;(1&lt;&lt;4)&t;/* INT0 pin hold count select */
DECL|macro|AK4117_EFH1
mdefine_line|#define AK4117_EFH1&t;&t;(1&lt;&lt;3)
DECL|macro|AK4117_EFH_512LRCLK
mdefine_line|#define AK4117_EFH_512LRCLK&t;(0)
DECL|macro|AK4117_EFH_1024LRCLK
mdefine_line|#define AK4117_EFH_1024LRCLK&t;(AK4117_EFH1)
DECL|macro|AK4117_EFH_2048LRCLK
mdefine_line|#define AK4117_EFH_2048LRCLK&t;(AK4117_EFH2)
DECL|macro|AK4117_EFH_4096LRCLK
mdefine_line|#define AK4117_EFH_4096LRCLK&t;(AK4117_EFH1|AK4117_EFH2)
DECL|macro|AK4117_DIF2
mdefine_line|#define AK4117_DIF2&t;&t;(1&lt;&lt;2)&t;/* audio data format control */
DECL|macro|AK4117_DIF1
mdefine_line|#define AK4117_DIF1&t;&t;(1&lt;&lt;1)
DECL|macro|AK4117_DIF0
mdefine_line|#define AK4117_DIF0&t;&t;(1&lt;&lt;0)
DECL|macro|AK4117_DIF_16R
mdefine_line|#define AK4117_DIF_16R&t;&t;(0)&t;&t;&t;&t;/* STDO: 16-bit, right justified */
DECL|macro|AK4117_DIF_18R
mdefine_line|#define AK4117_DIF_18R&t;&t;(AK4117_DIF0)&t;&t;&t;/* STDO: 18-bit, right justified */
DECL|macro|AK4117_DIF_20R
mdefine_line|#define AK4117_DIF_20R&t;&t;(AK4117_DIF1)&t;&t;&t;/* STDO: 20-bit, right justified */
DECL|macro|AK4117_DIF_24R
mdefine_line|#define AK4117_DIF_24R&t;&t;(AK4117_DIF1|AK4117_DIF0)&t;/* STDO: 24-bit, right justified */
DECL|macro|AK4117_DIF_24L
mdefine_line|#define AK4117_DIF_24L&t;&t;(AK4117_DIF2)&t;&t;&t;/* STDO: 24-bit, left justified */
DECL|macro|AK4117_DIF_24I2S
mdefine_line|#define AK4117_DIF_24I2S&t;(AK4117_DIF2|AK4117_DIF0)&t;/* STDO: I2S */
multiline_comment|/* AK4117_REG_INT0_MASK &amp; AK4117_REG_INT1_MASK */
DECL|macro|AK4117_MULK
mdefine_line|#define AK4117_MULK&t;&t;(1&lt;&lt;7)&t;/* mask enable for UNLOCK bit */
DECL|macro|AK4117_MPAR
mdefine_line|#define AK4117_MPAR&t;&t;(1&lt;&lt;6)&t;/* mask enable for PAR bit */
DECL|macro|AK4117_MAUTO
mdefine_line|#define AK4117_MAUTO&t;&t;(1&lt;&lt;5)&t;/* mask enable for AUTO bit */
DECL|macro|AK4117_MV
mdefine_line|#define AK4117_MV&t;&t;(1&lt;&lt;4)&t;/* mask enable for V bit */
DECL|macro|AK4117_MAUD
mdefine_line|#define AK4117_MAUD&t;&t;(1&lt;&lt;3)&t;/* mask enable for AUDION bit */
DECL|macro|AK4117_MSTC
mdefine_line|#define AK4117_MSTC&t;&t;(1&lt;&lt;2)&t;/* mask enable for STC bit */
DECL|macro|AK4117_MCIT
mdefine_line|#define AK4117_MCIT&t;&t;(1&lt;&lt;1)&t;/* mask enable for CINT bit */
DECL|macro|AK4117_MQIT
mdefine_line|#define AK4117_MQIT&t;&t;(1&lt;&lt;0)&t;/* mask enable for QINT bit */
multiline_comment|/* AK4117_REG_RCS0 */
DECL|macro|AK4117_UNLCK
mdefine_line|#define AK4117_UNLCK&t;&t;(1&lt;&lt;7)&t;/* PLL lock status, 0 = lock, 1 = unlock */
DECL|macro|AK4117_PAR
mdefine_line|#define AK4117_PAR&t;&t;(1&lt;&lt;6)&t;/* parity error or biphase error status, 0 = no error, 1 = error */
DECL|macro|AK4117_AUTO
mdefine_line|#define AK4117_AUTO&t;&t;(1&lt;&lt;5)&t;/* Non-PCM or DTS stream auto detection, 0 = no detect, 1 = detect */
DECL|macro|AK4117_V
mdefine_line|#define AK4117_V&t;&t;(1&lt;&lt;4)&t;/* Validity bit, 0 = valid, 1 = invalid */
DECL|macro|AK4117_AUDION
mdefine_line|#define AK4117_AUDION&t;&t;(1&lt;&lt;3)&t;/* audio bit output, 0 = audio, 1 = non-audio */
DECL|macro|AK4117_STC
mdefine_line|#define AK4117_STC&t;&t;(1&lt;&lt;2)&t;/* sampling frequency or Pre-emphasis change, 0 = no detect, 1 = detect */
DECL|macro|AK4117_CINT
mdefine_line|#define AK4117_CINT&t;&t;(1&lt;&lt;1)&t;/* channel status buffer interrupt, 0 = no change, 1 = change */
DECL|macro|AK4117_QINT
mdefine_line|#define AK4117_QINT&t;&t;(1&lt;&lt;0)&t;/* Q-subcode buffer interrupt, 0 = no change, 1 = changed */
multiline_comment|/* AK4117_REG_RCS1 */
DECL|macro|AK4117_DTSCD
mdefine_line|#define AK4117_DTSCD&t;&t;(1&lt;&lt;6)&t;/* DTS-CD bit audio stream detect, 0 = no detect, 1 = detect */
DECL|macro|AK4117_NPCM
mdefine_line|#define AK4117_NPCM&t;&t;(1&lt;&lt;5)&t;/* Non-PCM bit stream detection, 0 = no detect, 1 = detect */
DECL|macro|AK4117_PEM
mdefine_line|#define AK4117_PEM&t;&t;(1&lt;&lt;4)&t;/* Pre-emphasis detect, 0 = OFF, 1 = ON */
DECL|macro|AK4117_FS3
mdefine_line|#define AK4117_FS3&t;&t;(1&lt;&lt;3)&t;/* sampling frequency detection */
DECL|macro|AK4117_FS2
mdefine_line|#define AK4117_FS2&t;&t;(1&lt;&lt;2)
DECL|macro|AK4117_FS1
mdefine_line|#define AK4117_FS1&t;&t;(1&lt;&lt;1)
DECL|macro|AK4117_FS0
mdefine_line|#define AK4117_FS0&t;&t;(1&lt;&lt;0)
DECL|macro|AK4117_FS_44100HZ
mdefine_line|#define AK4117_FS_44100HZ&t;(0)
DECL|macro|AK4117_FS_48000HZ
mdefine_line|#define AK4117_FS_48000HZ&t;(AK4117_FS1)
DECL|macro|AK4117_FS_32000HZ
mdefine_line|#define AK4117_FS_32000HZ&t;(AK4117_FS1|AK4117_FS0)
DECL|macro|AK4117_FS_88200HZ
mdefine_line|#define AK4117_FS_88200HZ&t;(AK4117_FS3)
DECL|macro|AK4117_FS_96000HZ
mdefine_line|#define AK4117_FS_96000HZ&t;(AK4117_FS3|AK4117_FS1)
DECL|macro|AK4117_FS_176400HZ
mdefine_line|#define AK4117_FS_176400HZ&t;(AK4117_FS3|AK4117_FS2)
DECL|macro|AK4117_FS_192000HZ
mdefine_line|#define AK4117_FS_192000HZ&t;(AK4117_FS3|AK4117_FS2|AK4117_FS1)
multiline_comment|/* AK4117_REG_RCS2 */
DECL|macro|AK4117_CCRC
mdefine_line|#define AK4117_CCRC&t;&t;(1&lt;&lt;1)&t;/* CRC for channel status, 0 = no error, 1 = error */
DECL|macro|AK4117_QCRC
mdefine_line|#define AK4117_QCRC&t;&t;(1&lt;&lt;0)&t;/* CRC for Q-subcode, 0 = no error, 1 = error */
multiline_comment|/* flags for snd_ak4117_check_rate_and_errors() */
DECL|macro|AK4117_CHECK_NO_STAT
mdefine_line|#define AK4117_CHECK_NO_STAT&t;(1&lt;&lt;0)&t;/* no statistics */
DECL|macro|AK4117_CHECK_NO_RATE
mdefine_line|#define AK4117_CHECK_NO_RATE&t;(1&lt;&lt;1)&t;/* no rate check */
DECL|macro|AK4117_CONTROLS
mdefine_line|#define AK4117_CONTROLS&t;&t;13
DECL|typedef|ak4117_write_t
r_typedef
r_void
(paren
id|ak4117_write_t
)paren
(paren
r_void
op_star
id|private_data
comma
r_int
r_char
id|addr
comma
r_int
r_char
id|data
)paren
suffix:semicolon
DECL|typedef|ak4117_read_t
r_typedef
r_int
r_char
(paren
id|ak4117_read_t
)paren
(paren
r_void
op_star
id|private_data
comma
r_int
r_char
id|addr
)paren
suffix:semicolon
DECL|typedef|ak4117_t
r_typedef
r_struct
id|ak4117
id|ak4117_t
suffix:semicolon
DECL|struct|ak4117
r_struct
id|ak4117
(brace
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
DECL|member|write
id|ak4117_write_t
op_star
id|write
suffix:semicolon
DECL|member|read
id|ak4117_read_t
op_star
id|read
suffix:semicolon
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
DECL|member|init
r_int
r_int
id|init
suffix:colon
l_int|1
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|regmap
r_int
r_char
id|regmap
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|kctls
id|snd_kcontrol_t
op_star
id|kctls
(braket
id|AK4117_CONTROLS
)braket
suffix:semicolon
DECL|member|substream
id|snd_pcm_substream_t
op_star
id|substream
suffix:semicolon
DECL|member|parity_errors
r_int
r_int
id|parity_errors
suffix:semicolon
DECL|member|v_bit_errors
r_int
r_int
id|v_bit_errors
suffix:semicolon
DECL|member|qcrc_errors
r_int
r_int
id|qcrc_errors
suffix:semicolon
DECL|member|ccrc_errors
r_int
r_int
id|ccrc_errors
suffix:semicolon
DECL|member|rcs0
r_int
r_char
id|rcs0
suffix:semicolon
DECL|member|rcs1
r_int
r_char
id|rcs1
suffix:semicolon
DECL|member|rcs2
r_int
r_char
id|rcs2
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
multiline_comment|/* statistic timer */
DECL|member|change_callback_private
r_void
op_star
id|change_callback_private
suffix:semicolon
DECL|member|change_callback
r_void
(paren
op_star
id|change_callback
)paren
(paren
id|ak4117_t
op_star
id|ak4117
comma
r_int
r_char
id|c0
comma
r_int
r_char
id|c1
)paren
suffix:semicolon
)brace
suffix:semicolon
r_int
id|snd_ak4117_create
c_func
(paren
id|snd_card_t
op_star
id|card
comma
id|ak4117_read_t
op_star
id|read
comma
id|ak4117_write_t
op_star
id|write
comma
r_int
r_char
id|pgm
(braket
l_int|5
)braket
comma
r_void
op_star
id|private_data
comma
id|ak4117_t
op_star
op_star
id|r_ak4117
)paren
suffix:semicolon
r_void
id|snd_ak4117_reg_write
c_func
(paren
id|ak4117_t
op_star
id|ak4117
comma
r_int
r_char
id|reg
comma
r_int
r_char
id|mask
comma
r_int
r_char
id|val
)paren
suffix:semicolon
r_void
id|snd_ak4117_reinit
c_func
(paren
id|ak4117_t
op_star
id|ak4117
)paren
suffix:semicolon
r_int
id|snd_ak4117_build
c_func
(paren
id|ak4117_t
op_star
id|ak4117
comma
id|snd_pcm_substream_t
op_star
id|capture_substream
)paren
suffix:semicolon
r_int
id|snd_ak4117_external_rate
c_func
(paren
id|ak4117_t
op_star
id|ak4117
)paren
suffix:semicolon
r_int
id|snd_ak4117_check_rate_and_errors
c_func
(paren
id|ak4117_t
op_star
id|ak4117
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
macro_line|#endif /* __SOUND_AK4117_H */
eof
