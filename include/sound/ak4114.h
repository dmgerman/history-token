macro_line|#ifndef __SOUND_AK4114_H
DECL|macro|__SOUND_AK4114_H
mdefine_line|#define __SOUND_AK4114_H
multiline_comment|/*&n; *  Routines for Asahi Kasei AK4114&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;,&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
multiline_comment|/* AK4114 registers */
DECL|macro|AK4114_REG_PWRDN
mdefine_line|#define AK4114_REG_PWRDN&t;0x00&t;/* power down */
DECL|macro|AK4114_REG_FORMAT
mdefine_line|#define AK4114_REG_FORMAT&t;0x01&t;/* format control */
DECL|macro|AK4114_REG_IO0
mdefine_line|#define AK4114_REG_IO0&t;&t;0x02&t;/* input/output control */
DECL|macro|AK4114_REG_IO1
mdefine_line|#define AK4114_REG_IO1&t;&t;0x03&t;/* input/output control */
DECL|macro|AK4114_REG_INT0_MASK
mdefine_line|#define AK4114_REG_INT0_MASK&t;0x04&t;/* interrupt0 mask */
DECL|macro|AK4114_REG_INT1_MASK
mdefine_line|#define AK4114_REG_INT1_MASK&t;0x05&t;/* interrupt1 mask */
DECL|macro|AK4114_REG_RCS0
mdefine_line|#define AK4114_REG_RCS0&t;&t;0x06&t;/* receiver status 0 */
DECL|macro|AK4114_REG_RCS1
mdefine_line|#define AK4114_REG_RCS1&t;&t;0x07&t;/* receiver status 1 */
DECL|macro|AK4114_REG_RXCSB0
mdefine_line|#define AK4114_REG_RXCSB0&t;0x08&t;/* RX channel status byte 0 */
DECL|macro|AK4114_REG_RXCSB1
mdefine_line|#define AK4114_REG_RXCSB1&t;0x09&t;/* RX channel status byte 1 */
DECL|macro|AK4114_REG_RXCSB2
mdefine_line|#define AK4114_REG_RXCSB2&t;0x0a&t;/* RX channel status byte 2 */
DECL|macro|AK4114_REG_RXCSB3
mdefine_line|#define AK4114_REG_RXCSB3&t;0x0b&t;/* RX channel status byte 3 */
DECL|macro|AK4114_REG_RXCSB4
mdefine_line|#define AK4114_REG_RXCSB4&t;0x0c&t;/* RX channel status byte 4 */
DECL|macro|AK4114_REG_TXCSB0
mdefine_line|#define AK4114_REG_TXCSB0&t;0x0d&t;/* TX channel status byte 0 */
DECL|macro|AK4114_REG_TXCSB1
mdefine_line|#define AK4114_REG_TXCSB1&t;0x0e&t;/* TX channel status byte 1 */
DECL|macro|AK4114_REG_TXCSB2
mdefine_line|#define AK4114_REG_TXCSB2&t;0x0f&t;/* TX channel status byte 2 */
DECL|macro|AK4114_REG_TXCSB3
mdefine_line|#define AK4114_REG_TXCSB3&t;0x10&t;/* TX channel status byte 3 */
DECL|macro|AK4114_REG_TXCSB4
mdefine_line|#define AK4114_REG_TXCSB4&t;0x11&t;/* TX channel status byte 4 */
DECL|macro|AK4114_REG_Pc0
mdefine_line|#define AK4114_REG_Pc0&t;&t;0x12&t;/* burst preamble Pc byte 0 */
DECL|macro|AK4114_REG_Pc1
mdefine_line|#define AK4114_REG_Pc1&t;&t;0x13&t;/* burst preamble Pc byte 1 */
DECL|macro|AK4114_REG_Pd0
mdefine_line|#define AK4114_REG_Pd0&t;&t;0x14&t;/* burst preamble Pd byte 0 */
DECL|macro|AK4114_REG_Pd1
mdefine_line|#define AK4114_REG_Pd1&t;&t;0x15&t;/* burst preamble Pd byte 1 */
DECL|macro|AK4114_REG_QSUB_ADDR
mdefine_line|#define AK4114_REG_QSUB_ADDR&t;0x16&t;/* Q-subcode address + control */
DECL|macro|AK4114_REG_QSUB_TRACK
mdefine_line|#define AK4114_REG_QSUB_TRACK&t;0x17&t;/* Q-subcode track */
DECL|macro|AK4114_REG_QSUB_INDEX
mdefine_line|#define AK4114_REG_QSUB_INDEX&t;0x18&t;/* Q-subcode index */
DECL|macro|AK4114_REG_QSUB_MINUTE
mdefine_line|#define AK4114_REG_QSUB_MINUTE&t;0x19&t;/* Q-subcode minute */
DECL|macro|AK4114_REG_QSUB_SECOND
mdefine_line|#define AK4114_REG_QSUB_SECOND&t;0x1a&t;/* Q-subcode second */
DECL|macro|AK4114_REG_QSUB_FRAME
mdefine_line|#define AK4114_REG_QSUB_FRAME&t;0x1b&t;/* Q-subcode frame */
DECL|macro|AK4114_REG_QSUB_ZERO
mdefine_line|#define AK4114_REG_QSUB_ZERO&t;0x1c&t;/* Q-subcode zero */
DECL|macro|AK4114_REG_QSUB_ABSMIN
mdefine_line|#define AK4114_REG_QSUB_ABSMIN&t;0x1d&t;/* Q-subcode absolute minute */
DECL|macro|AK4114_REG_QSUB_ABSSEC
mdefine_line|#define AK4114_REG_QSUB_ABSSEC&t;0x1e&t;/* Q-subcode absolute second */
DECL|macro|AK4114_REG_QSUB_ABSFRM
mdefine_line|#define AK4114_REG_QSUB_ABSFRM&t;0x1f&t;/* Q-subcode absolute frame */
multiline_comment|/* sizes */
DECL|macro|AK4114_REG_RXCSB_SIZE
mdefine_line|#define AK4114_REG_RXCSB_SIZE&t;((AK4114_REG_RXCSB4-AK4114_REG_RXCSB0)+1)
DECL|macro|AK4114_REG_TXCSB_SIZE
mdefine_line|#define AK4114_REG_TXCSB_SIZE&t;((AK4114_REG_TXCSB4-AK4114_REG_TXCSB0)+1)
DECL|macro|AK4114_REG_QSUB_SIZE
mdefine_line|#define AK4114_REG_QSUB_SIZE&t;((AK4114_REG_QSUB_ABSFRM-AK4114_REG_QSUB_ADDR)+1)
multiline_comment|/* AK4117_REG_PWRDN bits */
DECL|macro|AK4114_CS12
mdefine_line|#define AK4114_CS12&t;&t;(1&lt;&lt;7)&t;/* Channel Status Select */
DECL|macro|AK4114_BCU
mdefine_line|#define AK4114_BCU&t;&t;(1&lt;&lt;6)&t;/* Block Start &amp; C/U Output Mode */
DECL|macro|AK4114_CM1
mdefine_line|#define AK4114_CM1&t;&t;(1&lt;&lt;5)&t;/* Master Clock Operation Select */
DECL|macro|AK4114_CM0
mdefine_line|#define AK4114_CM0&t;&t;(1&lt;&lt;4)&t;/* Master Clock Operation Select */
DECL|macro|AK4114_OCKS1
mdefine_line|#define AK4114_OCKS1&t;&t;(1&lt;&lt;3)&t;/* Master Clock Frequency Select */
DECL|macro|AK4114_OCKS0
mdefine_line|#define AK4114_OCKS0&t;&t;(1&lt;&lt;2)&t;/* Master Clock Frequency Select */
DECL|macro|AK4114_PWN
mdefine_line|#define AK4114_PWN&t;&t;(1&lt;&lt;1)&t;/* 0 = power down, 1 = normal operation */
DECL|macro|AK4114_RST
mdefine_line|#define AK4114_RST&t;&t;(1&lt;&lt;0)&t;/* 0 = reset &amp; initialize (except this register), 1 = normal operation */
multiline_comment|/* AK4114_REQ_FORMAT bits */
DECL|macro|AK4114_MONO
mdefine_line|#define AK4114_MONO&t;&t;(1&lt;&lt;7)&t;/* Double Sampling Frequency Mode: 0 = stereo, 1 = mono */
DECL|macro|AK4114_DIF2
mdefine_line|#define AK4114_DIF2&t;&t;(1&lt;&lt;5)&t;/* Audio Data Control */
DECL|macro|AK4114_DIF1
mdefine_line|#define AK4114_DIF1&t;&t;(1&lt;&lt;5)&t;/* Audio Data Control */
DECL|macro|AK4114_DIF0
mdefine_line|#define AK4114_DIF0&t;&t;(1&lt;&lt;4)&t;/* Audio Data Control */
DECL|macro|AK4114_DIF_16R
mdefine_line|#define AK4114_DIF_16R&t;&t;(0)&t;&t;&t;&t;/* STDO: 16-bit, right justified */
DECL|macro|AK4114_DIF_18R
mdefine_line|#define AK4114_DIF_18R&t;&t;(AK4114_DIF0)&t;&t;&t;/* STDO: 18-bit, right justified */
DECL|macro|AK4114_DIF_20R
mdefine_line|#define AK4114_DIF_20R&t;&t;(AK4114_DIF1)&t;&t;&t;/* STDO: 20-bit, right justified */
DECL|macro|AK4114_DIF_24R
mdefine_line|#define AK4114_DIF_24R&t;&t;(AK4114_DIF1|AK4114_DIF0)&t;/* STDO: 24-bit, right justified */
DECL|macro|AK4114_DIF_24L
mdefine_line|#define AK4114_DIF_24L&t;&t;(AK4114_DIF2)&t;&t;&t;/* STDO: 24-bit, left justified */
DECL|macro|AK4114_DIF_24I2S
mdefine_line|#define AK4114_DIF_24I2S&t;(AK4114_DIF2|AK4114_DIF0)&t;/* STDO: I2S */
DECL|macro|AK4114_DIF_I24L
mdefine_line|#define AK4114_DIF_I24L&t;&t;(AK4114_DIF2|AK4114_DIF1)&t;/* STDO: 24-bit, left justified; LRCLK, BICK = Input */
DECL|macro|AK4114_DIF_I24I2S
mdefine_line|#define AK4114_DIF_I24I2S&t;(AK4114_DIF2|AK4114_DIF1|AK4114_DIF0) /* STDO: I2S;  LRCLK, BICK = Input */
DECL|macro|AK4114_DEAU
mdefine_line|#define AK4114_DEAU&t;&t;(1&lt;&lt;3)&t;/* Deemphasis Autodetect Enable (1 = enable) */
DECL|macro|AK4114_DEM1
mdefine_line|#define AK4114_DEM1&t;&t;(1&lt;&lt;2)&t;/* 32kHz-48kHz Deemphasis Control */
DECL|macro|AK4114_DEM0
mdefine_line|#define AK4114_DEM0&t;&t;(1&lt;&lt;1)&t;/* 32kHz-48kHz Deemphasis Control */
DECL|macro|AK4114_DEM_44KHZ
mdefine_line|#define AK4114_DEM_44KHZ&t;(0)
DECL|macro|AK4114_DEM_48KHZ
mdefine_line|#define AK4114_DEM_48KHZ&t;(AK4114_DEM1)
DECL|macro|AK4114_DEM_32KHZ
mdefine_line|#define AK4114_DEM_32KHZ&t;(AK4114_DEM0|AK4114_DEM1)
DECL|macro|AK4114_DEM_96KHZ
mdefine_line|#define AK4114_DEM_96KHZ&t;(AK4114_DEM1)&t;/* DFS must be set */
DECL|macro|AK4114_DFS
mdefine_line|#define AK4114_DFS&t;&t;(1&lt;&lt;0)&t;/* 96kHz Deemphasis Control */
multiline_comment|/* AK4114_REG_IO0 */
DECL|macro|AK4114_TX1E
mdefine_line|#define AK4114_TX1E&t;&t;(1&lt;&lt;7)&t;/* TX1 Output Enable (1 = enable) */
DECL|macro|AK4114_OPS12
mdefine_line|#define AK4114_OPS12&t;&t;(1&lt;&lt;2)&t;/* Output Though Data Selector for TX1 pin */
DECL|macro|AK4114_OPS11
mdefine_line|#define AK4114_OPS11&t;&t;(1&lt;&lt;1)&t;/* Output Though Data Selector for TX1 pin */
DECL|macro|AK4114_OPS10
mdefine_line|#define AK4114_OPS10&t;&t;(1&lt;&lt;0)&t;/* Output Though Data Selector for TX1 pin */
DECL|macro|AK4114_TX0E
mdefine_line|#define AK4114_TX0E&t;&t;(1&lt;&lt;3)&t;/* TX0 Output Enable (1 = enable) */
DECL|macro|AK4114_OPS02
mdefine_line|#define AK4114_OPS02&t;&t;(1&lt;&lt;2)&t;/* Output Though Data Selector for TX0 pin */
DECL|macro|AK4114_OPS01
mdefine_line|#define AK4114_OPS01&t;&t;(1&lt;&lt;1)&t;/* Output Though Data Selector for TX0 pin */
DECL|macro|AK4114_OPS00
mdefine_line|#define AK4114_OPS00&t;&t;(1&lt;&lt;0)&t;/* Output Though Data Selector for TX0 pin */
multiline_comment|/* AK4114_REG_IO1 */
DECL|macro|AK4114_EFH1
mdefine_line|#define AK4114_EFH1&t;&t;(1&lt;&lt;7)&t;/* Interrupt 0 pin Hold */
DECL|macro|AK4114_EFH0
mdefine_line|#define AK4114_EFH0&t;&t;(1&lt;&lt;6)&t;/* Interrupt 0 pin Hold */
DECL|macro|AK4114_EFH_512
mdefine_line|#define AK4114_EFH_512&t;&t;(0)
DECL|macro|AK4114_EFH_1024
mdefine_line|#define AK4114_EFH_1024&t;&t;(AK4114_EFH0)
DECL|macro|AK4114_EFH_2048
mdefine_line|#define AK4114_EFH_2048&t;&t;(AK4114_EFH1)
DECL|macro|AK4114_EFH_4096
mdefine_line|#define AK4114_EFH_4096&t;&t;(AK4114_EFH1|AK4114_EFH0)
DECL|macro|AK4114_UDIT
mdefine_line|#define AK4114_UDIT&t;&t;(1&lt;&lt;5)&t;/* U-bit Control for DIT (0 = fixed &squot;0&squot;, 1 = recovered) */
DECL|macro|AK4114_TLR
mdefine_line|#define AK4114_TLR&t;&t;(1&lt;&lt;4)&t;/* Double Sampling Frequency Select for DIT (0 = L channel, 1 = R channel) */
DECL|macro|AK4114_DIT
mdefine_line|#define AK4114_DIT&t;&t;(1&lt;&lt;3)&t;/* TX1 out: 0 = Through Data (RX data), 1 = Transmit Data (DAUX data) */
DECL|macro|AK4114_IPS2
mdefine_line|#define AK4114_IPS2&t;&t;(1&lt;&lt;2)&t;/* Input Recovery Data Select */
DECL|macro|AK4114_IPS1
mdefine_line|#define AK4114_IPS1&t;&t;(1&lt;&lt;1)&t;/* Input Recovery Data Select */
DECL|macro|AK4114_IPS0
mdefine_line|#define AK4114_IPS0&t;&t;(1&lt;&lt;0)&t;/* Input Recovery Data Select */
DECL|macro|AK4114_IPS
mdefine_line|#define AK4114_IPS(x)&t;&t;((x)&amp;7)
multiline_comment|/* AK4114_REG_INT0_MASK &amp;&amp; AK4114_REG_INT1_MASK*/
DECL|macro|AK4117_MQI
mdefine_line|#define AK4117_MQI              (1&lt;&lt;7)  /* mask enable for QINT bit */
DECL|macro|AK4117_MAT
mdefine_line|#define AK4117_MAT              (1&lt;&lt;6)  /* mask enable for AUTO bit */
DECL|macro|AK4117_MCI
mdefine_line|#define AK4117_MCI              (1&lt;&lt;5)  /* mask enable for CINT bit */
DECL|macro|AK4117_MUL
mdefine_line|#define AK4117_MUL              (1&lt;&lt;4)  /* mask enable for UNLOCK bit */
DECL|macro|AK4117_MDTS
mdefine_line|#define AK4117_MDTS             (1&lt;&lt;3)  /* mask enable for DTSCD bit */
DECL|macro|AK4117_MPE
mdefine_line|#define AK4117_MPE              (1&lt;&lt;2)  /* mask enable for PEM bit */
DECL|macro|AK4117_MAN
mdefine_line|#define AK4117_MAN              (1&lt;&lt;1)  /* mask enable for AUDN bit */
DECL|macro|AK4117_MPR
mdefine_line|#define AK4117_MPR              (1&lt;&lt;0)  /* mask enable for PAR bit */
multiline_comment|/* AK4114_REG_RCS0 */
DECL|macro|AK4114_QINT
mdefine_line|#define AK4114_QINT&t;&t;(1&lt;&lt;7)&t;/* Q-subcode buffer interrupt, 0 = no change, 1 = changed */
DECL|macro|AK4114_AUTO
mdefine_line|#define AK4114_AUTO&t;&t;(1&lt;&lt;6)&t;/* Non-PCM or DTS stream auto detection, 0 = no detect, 1 = detect */
DECL|macro|AK4114_CINT
mdefine_line|#define AK4114_CINT&t;&t;(1&lt;&lt;5)&t;/* channel status buffer interrupt, 0 = no change, 1 = change */
DECL|macro|AK4114_UNLCK
mdefine_line|#define AK4114_UNLCK&t;&t;(1&lt;&lt;4)&t;/* PLL lock status, 0 = lock, 1 = unlock */
DECL|macro|AK4114_DTSCD
mdefine_line|#define AK4114_DTSCD&t;&t;(1&lt;&lt;3)&t;/* DTS-CD Detect, 0 = No detect, 1 = Detect */
DECL|macro|AK4114_PEM
mdefine_line|#define AK4114_PEM&t;&t;(1&lt;&lt;2)&t;/* Pre-emphasis Detect, 0 = OFF, 1 = ON */
DECL|macro|AK4114_AUDION
mdefine_line|#define AK4114_AUDION&t;&t;(1&lt;&lt;1)&t;/* audio bit output, 0 = audio, 1 = non-audio */
DECL|macro|AK4114_PAR
mdefine_line|#define AK4114_PAR&t;&t;(1&lt;&lt;0)&t;/* parity error or biphase error status, 0 = no error, 1 = error */
multiline_comment|/* AK4114_REG_RCS1 */
DECL|macro|AK4114_FS3
mdefine_line|#define AK4114_FS3&t;&t;(1&lt;&lt;7)&t;/* sampling frequency detection */
DECL|macro|AK4114_FS2
mdefine_line|#define AK4114_FS2&t;&t;(1&lt;&lt;6)
DECL|macro|AK4114_FS1
mdefine_line|#define AK4114_FS1&t;&t;(1&lt;&lt;5)
DECL|macro|AK4114_FS0
mdefine_line|#define AK4114_FS0&t;&t;(1&lt;&lt;4)
DECL|macro|AK4114_FS_44100HZ
mdefine_line|#define AK4114_FS_44100HZ&t;(0)
DECL|macro|AK4114_FS_48000HZ
mdefine_line|#define AK4114_FS_48000HZ&t;(AK4114_FS1)
DECL|macro|AK4114_FS_32000HZ
mdefine_line|#define AK4114_FS_32000HZ&t;(AK4114_FS1|AK4114_FS0)
DECL|macro|AK4114_FS_88200HZ
mdefine_line|#define AK4114_FS_88200HZ&t;(AK4114_FS3)
DECL|macro|AK4114_FS_96000HZ
mdefine_line|#define AK4114_FS_96000HZ&t;(AK4114_FS3|AK4114_FS1)
DECL|macro|AK4114_FS_176400HZ
mdefine_line|#define AK4114_FS_176400HZ&t;(AK4114_FS3|AK4114_FS2)
DECL|macro|AK4114_FS_192000HZ
mdefine_line|#define AK4114_FS_192000HZ&t;(AK4114_FS3|AK4114_FS2|AK4114_FS1)
DECL|macro|AK4114_V
mdefine_line|#define AK4114_V&t;&t;(1&lt;&lt;3)&t;/* Validity of Channel Status, 0 = Valid, 1 = Invalid */
DECL|macro|AK4114_QCRC
mdefine_line|#define AK4114_QCRC&t;&t;(1&lt;&lt;1)&t;/* CRC for Q-subcode, 0 = no error, 1 = error */
DECL|macro|AK4114_CCRC
mdefine_line|#define AK4114_CCRC&t;&t;(1&lt;&lt;0)&t;/* CRC for channel status, 0 = no error, 1 = error */
multiline_comment|/* flags for snd_ak4114_check_rate_and_errors() */
DECL|macro|AK4114_CHECK_NO_STAT
mdefine_line|#define AK4114_CHECK_NO_STAT&t;(1&lt;&lt;0)&t;/* no statistics */
DECL|macro|AK4114_CHECK_NO_RATE
mdefine_line|#define AK4114_CHECK_NO_RATE&t;(1&lt;&lt;1)&t;/* no rate check */
DECL|macro|AK4114_CONTROLS
mdefine_line|#define AK4114_CONTROLS&t;&t;14
DECL|typedef|ak4114_write_t
r_typedef
r_void
(paren
id|ak4114_write_t
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
DECL|typedef|ak4114_read_t
r_typedef
r_int
r_char
(paren
id|ak4114_read_t
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
DECL|typedef|ak4114_t
r_typedef
r_struct
id|ak4114
id|ak4114_t
suffix:semicolon
DECL|struct|ak4114
r_struct
id|ak4114
(brace
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
DECL|member|write
id|ak4114_write_t
op_star
id|write
suffix:semicolon
DECL|member|read
id|ak4114_read_t
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
l_int|7
)braket
suffix:semicolon
DECL|member|txcsb
r_int
r_char
id|txcsb
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|kctls
id|snd_kcontrol_t
op_star
id|kctls
(braket
id|AK4114_CONTROLS
)braket
suffix:semicolon
DECL|member|playback_substream
id|snd_pcm_substream_t
op_star
id|playback_substream
suffix:semicolon
DECL|member|capture_substream
id|snd_pcm_substream_t
op_star
id|capture_substream
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
DECL|member|workqueue
r_struct
id|workqueue_struct
op_star
id|workqueue
suffix:semicolon
DECL|member|work
r_struct
id|work_struct
id|work
suffix:semicolon
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
id|ak4114_t
op_star
id|ak4114
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
id|snd_ak4114_create
c_func
(paren
id|snd_card_t
op_star
id|card
comma
id|ak4114_read_t
op_star
id|read
comma
id|ak4114_write_t
op_star
id|write
comma
r_int
r_char
id|pgm
(braket
l_int|7
)braket
comma
r_int
r_char
id|txcsb
(braket
l_int|5
)braket
comma
r_void
op_star
id|private_data
comma
id|ak4114_t
op_star
op_star
id|r_ak4114
)paren
suffix:semicolon
r_void
id|snd_ak4114_reg_write
c_func
(paren
id|ak4114_t
op_star
id|ak4114
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
id|snd_ak4114_reinit
c_func
(paren
id|ak4114_t
op_star
id|ak4114
)paren
suffix:semicolon
r_int
id|snd_ak4114_build
c_func
(paren
id|ak4114_t
op_star
id|ak4114
comma
id|snd_pcm_substream_t
op_star
id|playback_substream
comma
id|snd_pcm_substream_t
op_star
id|capture_substream
)paren
suffix:semicolon
r_int
id|snd_ak4114_external_rate
c_func
(paren
id|ak4114_t
op_star
id|ak4114
)paren
suffix:semicolon
r_int
id|snd_ak4114_check_rate_and_errors
c_func
(paren
id|ak4114_t
op_star
id|ak4114
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
macro_line|#endif /* __SOUND_AK4114_H */
eof
