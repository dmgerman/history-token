macro_line|#ifndef __HAL2_H
DECL|macro|__HAL2_H
mdefine_line|#define __HAL2_H
multiline_comment|/*&n; *  Driver for HAL2 sound processors&n; *  Copyright (c) 1999 Ulf Carlsson &lt;ulfc@bun.falkenberg.se&gt;&n; *  Copyright (c) 2001, 2002, 2003 Ladislav Michl &lt;ladis@linux-mips.org&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License version 2 as &n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/sgi/hpc3.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* Indirect status register */
DECL|macro|H2_ISR_TSTATUS
mdefine_line|#define H2_ISR_TSTATUS&t;&t;0x01&t;/* RO: transaction status 1=busy */
DECL|macro|H2_ISR_USTATUS
mdefine_line|#define H2_ISR_USTATUS&t;&t;0x02&t;/* RO: utime status bit 1=armed */
DECL|macro|H2_ISR_QUAD_MODE
mdefine_line|#define H2_ISR_QUAD_MODE&t;0x04&t;/* codec mode 0=indigo 1=quad */
DECL|macro|H2_ISR_GLOBAL_RESET_N
mdefine_line|#define H2_ISR_GLOBAL_RESET_N&t;0x08&t;/* chip global reset 0=reset */
DECL|macro|H2_ISR_CODEC_RESET_N
mdefine_line|#define H2_ISR_CODEC_RESET_N&t;0x10&t;/* codec/synth reset 0=reset  */
multiline_comment|/* Revision register */
DECL|macro|H2_REV_AUDIO_PRESENT
mdefine_line|#define H2_REV_AUDIO_PRESENT&t;0x8000&t;/* RO: audio present 0=present */
DECL|macro|H2_REV_BOARD_M
mdefine_line|#define H2_REV_BOARD_M&t;&t;0x7000&t;/* RO: bits 14:12, board revision */
DECL|macro|H2_REV_MAJOR_CHIP_M
mdefine_line|#define H2_REV_MAJOR_CHIP_M&t;0x00F0&t;/* RO: bits 7:4, major chip revision */
DECL|macro|H2_REV_MINOR_CHIP_M
mdefine_line|#define H2_REV_MINOR_CHIP_M&t;0x000F&t;/* RO: bits 3:0, minor chip revision */
multiline_comment|/* Indirect address register */
multiline_comment|/*&n; * Address of indirect internal register to be accessed. A write to this&n; * register initiates read or write access to the indirect registers in the&n; * HAL2. Note that there af four indirect data registers for write access to&n; * registers larger than 16 byte.&n; */
DECL|macro|H2_IAR_TYPE_M
mdefine_line|#define H2_IAR_TYPE_M&t;&t;0xF000&t;/* bits 15:12, type of functional */
multiline_comment|/* block the register resides in */
multiline_comment|/* 1=DMA Port */
multiline_comment|/* 9=Global DMA Control */
multiline_comment|/* 2=Bresenham */
multiline_comment|/* 3=Unix Timer */
DECL|macro|H2_IAR_NUM_M
mdefine_line|#define H2_IAR_NUM_M&t;&t;0x0F00&t;/* bits 11:8 instance of the */
multiline_comment|/* blockin which the indirect */
multiline_comment|/* register resides */
multiline_comment|/* If IAR_TYPE_M=DMA Port: */
multiline_comment|/* 1=Synth In */
multiline_comment|/* 2=AES In */
multiline_comment|/* 3=AES Out */
multiline_comment|/* 4=DAC Out */
multiline_comment|/* 5=ADC Out */
multiline_comment|/* 6=Synth Control */
multiline_comment|/* If IAR_TYPE_M=Global DMA Control: */
multiline_comment|/* 1=Control */
multiline_comment|/* If IAR_TYPE_M=Bresenham: */
multiline_comment|/* 1=Bresenham Clock Gen 1 */
multiline_comment|/* 2=Bresenham Clock Gen 2 */
multiline_comment|/* 3=Bresenham Clock Gen 3 */
multiline_comment|/* If IAR_TYPE_M=Unix Timer: */
multiline_comment|/* 1=Unix Timer */
DECL|macro|H2_IAR_ACCESS_SELECT
mdefine_line|#define H2_IAR_ACCESS_SELECT&t;0x0080&t;/* 1=read 0=write */
DECL|macro|H2_IAR_PARAM
mdefine_line|#define H2_IAR_PARAM&t;&t;0x000C&t;/* Parameter Select */
DECL|macro|H2_IAR_RB_INDEX_M
mdefine_line|#define H2_IAR_RB_INDEX_M&t;0x0003&t;/* Read Back Index */
multiline_comment|/* 00:word0 */
multiline_comment|/* 01:word1 */
multiline_comment|/* 10:word2 */
multiline_comment|/* 11:word3 */
multiline_comment|/*&n; * HAL2 internal addressing&n; *&n; * The HAL2 has &quot;indirect registers&quot; (idr) which are accessed by writing to the&n; * Indirect Data registers. Write the address to the Indirect Address register&n; * to transfer the data.&n; *&n; * We define the H2IR_* to the read address and H2IW_* to the write address and&n; * H2I_* to be fields in whatever register is referred to.&n; *&n; * When we write to indirect registers which are larger than one word (16 bit)&n; * we have to fill more than one indirect register before writing. When we read&n; * back however we have to read several times, each time with different Read&n; * Back Indexes (there are defs for doing this easily).&n; */
multiline_comment|/*&n; * Relay Control&n; */
DECL|macro|H2I_RELAY_C
mdefine_line|#define H2I_RELAY_C&t;&t;0x9100
DECL|macro|H2I_RELAY_C_STATE
mdefine_line|#define H2I_RELAY_C_STATE&t;0x01&t;&t;/* state of RELAY pin signal */
multiline_comment|/* DMA port enable */
DECL|macro|H2I_DMA_PORT_EN
mdefine_line|#define H2I_DMA_PORT_EN&t;&t;0x9104
DECL|macro|H2I_DMA_PORT_EN_SY_IN
mdefine_line|#define H2I_DMA_PORT_EN_SY_IN&t;0x01&t;&t;/* Synth_in DMA port */
DECL|macro|H2I_DMA_PORT_EN_AESRX
mdefine_line|#define H2I_DMA_PORT_EN_AESRX&t;0x02&t;&t;/* AES receiver DMA port */
DECL|macro|H2I_DMA_PORT_EN_AESTX
mdefine_line|#define H2I_DMA_PORT_EN_AESTX&t;0x04&t;&t;/* AES transmitter DMA port */
DECL|macro|H2I_DMA_PORT_EN_CODECTX
mdefine_line|#define H2I_DMA_PORT_EN_CODECTX&t;0x08&t;&t;/* CODEC transmit DMA port */
DECL|macro|H2I_DMA_PORT_EN_CODECR
mdefine_line|#define H2I_DMA_PORT_EN_CODECR&t;0x10&t;&t;/* CODEC receive DMA port */
DECL|macro|H2I_DMA_END
mdefine_line|#define H2I_DMA_END&t;&t;0x9108 &t;&t;/* global dma endian select */
DECL|macro|H2I_DMA_END_SY_IN
mdefine_line|#define H2I_DMA_END_SY_IN&t;0x01&t;&t;/* Synth_in DMA port */
DECL|macro|H2I_DMA_END_AESRX
mdefine_line|#define H2I_DMA_END_AESRX&t;0x02&t;&t;/* AES receiver DMA port */
DECL|macro|H2I_DMA_END_AESTX
mdefine_line|#define H2I_DMA_END_AESTX&t;0x04&t;&t;/* AES transmitter DMA port */
DECL|macro|H2I_DMA_END_CODECTX
mdefine_line|#define H2I_DMA_END_CODECTX&t;0x08&t;&t;/* CODEC transmit DMA port */
DECL|macro|H2I_DMA_END_CODECR
mdefine_line|#define H2I_DMA_END_CODECR&t;0x10&t;&t;/* CODEC receive DMA port */
multiline_comment|/* 0=b_end 1=l_end */
DECL|macro|H2I_DMA_DRV
mdefine_line|#define H2I_DMA_DRV&t;&t;0x910C  &t;/* global PBUS DMA enable */
DECL|macro|H2I_SYNTH_C
mdefine_line|#define H2I_SYNTH_C&t;&t;0x1104&t;&t;/* Synth DMA control */
DECL|macro|H2I_AESRX_C
mdefine_line|#define H2I_AESRX_C&t;&t;0x1204&t; &t;/* AES RX dma control */
DECL|macro|H2I_C_TS_EN
mdefine_line|#define H2I_C_TS_EN&t;&t;0x20&t;&t;/* Timestamp enable */
DECL|macro|H2I_C_TS_FRMT
mdefine_line|#define H2I_C_TS_FRMT&t;&t;0x40&t;&t;/* Timestamp format */
DECL|macro|H2I_C_NAUDIO
mdefine_line|#define H2I_C_NAUDIO&t;&t;0x80&t;&t;/* Sign extend */
multiline_comment|/* AESRX CTL, 16 bit */
DECL|macro|H2I_AESTX_C
mdefine_line|#define H2I_AESTX_C&t;&t;0x1304&t;&t;/* AES TX DMA control */
DECL|macro|H2I_AESTX_C_CLKID_SHIFT
mdefine_line|#define H2I_AESTX_C_CLKID_SHIFT&t;3&t;&t;/* Bresenham Clock Gen 1-3 */
DECL|macro|H2I_AESTX_C_CLKID_M
mdefine_line|#define H2I_AESTX_C_CLKID_M&t;0x18
DECL|macro|H2I_AESTX_C_DATAT_SHIFT
mdefine_line|#define H2I_AESTX_C_DATAT_SHIFT&t;8&t;&t;/* 1=mono 2=stereo (3=quad) */
DECL|macro|H2I_AESTX_C_DATAT_M
mdefine_line|#define H2I_AESTX_C_DATAT_M&t;0x300
multiline_comment|/* CODEC registers */
DECL|macro|H2I_DAC_C1
mdefine_line|#define H2I_DAC_C1&t;&t;0x1404 &t;&t;/* DAC DMA control, 16 bit */
DECL|macro|H2I_DAC_C2
mdefine_line|#define H2I_DAC_C2&t;&t;0x1408&t;&t;/* DAC DMA control, 32 bit */
DECL|macro|H2I_ADC_C1
mdefine_line|#define H2I_ADC_C1&t;&t;0x1504 &t;&t;/* ADC DMA control, 16 bit */
DECL|macro|H2I_ADC_C2
mdefine_line|#define H2I_ADC_C2&t;&t;0x1508&t;&t;/* ADC DMA control, 32 bit */
multiline_comment|/* Bits in CTL1 register */
DECL|macro|H2I_C1_DMA_SHIFT
mdefine_line|#define H2I_C1_DMA_SHIFT&t;0&t;&t;/* DMA channel */
DECL|macro|H2I_C1_DMA_M
mdefine_line|#define H2I_C1_DMA_M&t;&t;0x7
DECL|macro|H2I_C1_CLKID_SHIFT
mdefine_line|#define H2I_C1_CLKID_SHIFT&t;3&t;&t;/* Bresenham Clock Gen 1-3 */
DECL|macro|H2I_C1_CLKID_M
mdefine_line|#define H2I_C1_CLKID_M&t;&t;0x18
DECL|macro|H2I_C1_DATAT_SHIFT
mdefine_line|#define H2I_C1_DATAT_SHIFT&t;8&t;&t;/* 1=mono 2=stereo (3=quad) */
DECL|macro|H2I_C1_DATAT_M
mdefine_line|#define H2I_C1_DATAT_M&t;&t;0x300
multiline_comment|/* Bits in CTL2 register */
DECL|macro|H2I_C2_R_GAIN_SHIFT
mdefine_line|#define H2I_C2_R_GAIN_SHIFT&t;0&t;&t;/* right a/d input gain */&t;
DECL|macro|H2I_C2_R_GAIN_M
mdefine_line|#define H2I_C2_R_GAIN_M&t;&t;0xf&t;
DECL|macro|H2I_C2_L_GAIN_SHIFT
mdefine_line|#define H2I_C2_L_GAIN_SHIFT&t;4&t;&t;/* left a/d input gain */
DECL|macro|H2I_C2_L_GAIN_M
mdefine_line|#define H2I_C2_L_GAIN_M&t;&t;0xf0
DECL|macro|H2I_C2_R_SEL
mdefine_line|#define H2I_C2_R_SEL&t;&t;0x100&t;&t;/* right input select */
DECL|macro|H2I_C2_L_SEL
mdefine_line|#define H2I_C2_L_SEL&t;&t;0x200&t;&t;/* left input select */
DECL|macro|H2I_C2_MUTE
mdefine_line|#define H2I_C2_MUTE&t;&t;0x400&t;&t;/* mute */
DECL|macro|H2I_C2_DO1
mdefine_line|#define H2I_C2_DO1&t;&t;0x00010000&t;/* digital output port bit 0 */
DECL|macro|H2I_C2_DO2
mdefine_line|#define H2I_C2_DO2&t;&t;0x00020000&t;/* digital output port bit 1 */
DECL|macro|H2I_C2_R_ATT_SHIFT
mdefine_line|#define H2I_C2_R_ATT_SHIFT&t;18&t;&t;/* right d/a output - */
DECL|macro|H2I_C2_R_ATT_M
mdefine_line|#define H2I_C2_R_ATT_M&t;&t;0x007c0000&t;/* attenuation */
DECL|macro|H2I_C2_L_ATT_SHIFT
mdefine_line|#define H2I_C2_L_ATT_SHIFT&t;23&t;&t;/* left d/a output - */
DECL|macro|H2I_C2_L_ATT_M
mdefine_line|#define H2I_C2_L_ATT_M&t;&t;0x0f800000&t;/* attenuation */
DECL|macro|H2I_SYNTH_MAP_C
mdefine_line|#define H2I_SYNTH_MAP_C&t;&t;0x1104&t;&t;/* synth dma handshake ctrl */
multiline_comment|/* Clock generator CTL 1, 16 bit */
DECL|macro|H2I_BRES1_C1
mdefine_line|#define H2I_BRES1_C1&t;&t;0x2104
DECL|macro|H2I_BRES2_C1
mdefine_line|#define H2I_BRES2_C1&t;&t;0x2204
DECL|macro|H2I_BRES3_C1
mdefine_line|#define H2I_BRES3_C1&t;&t;0x2304
DECL|macro|H2I_BRES_C1_SHIFT
mdefine_line|#define H2I_BRES_C1_SHIFT&t;0&t;&t;/* 0=48.0 1=44.1 2=aes_rx */
DECL|macro|H2I_BRES_C1_M
mdefine_line|#define H2I_BRES_C1_M&t;&t;0x03
multiline_comment|/* Clock generator CTL 2, 32 bit */
DECL|macro|H2I_BRES1_C2
mdefine_line|#define H2I_BRES1_C2&t;&t;0x2108
DECL|macro|H2I_BRES2_C2
mdefine_line|#define H2I_BRES2_C2&t;&t;0x2208
DECL|macro|H2I_BRES3_C2
mdefine_line|#define H2I_BRES3_C2&t;&t;0x2308
DECL|macro|H2I_BRES_C2_INC_SHIFT
mdefine_line|#define H2I_BRES_C2_INC_SHIFT&t;0&t;&t;/* increment value */
DECL|macro|H2I_BRES_C2_INC_M
mdefine_line|#define H2I_BRES_C2_INC_M&t;0xffff
DECL|macro|H2I_BRES_C2_MOD_SHIFT
mdefine_line|#define H2I_BRES_C2_MOD_SHIFT&t;16&t;&t;/* modcontrol value */
DECL|macro|H2I_BRES_C2_MOD_M
mdefine_line|#define H2I_BRES_C2_MOD_M&t;0xffff0000&t;/* modctrl=0xffff&amp;(modinc-1) */
multiline_comment|/* Unix timer, 64 bit */
DECL|macro|H2I_UTIME
mdefine_line|#define H2I_UTIME&t;&t;0x3104
DECL|macro|H2I_UTIME_0_LD
mdefine_line|#define H2I_UTIME_0_LD&t;&t;0xffff&t;&t;/* microseconds, LSB&squot;s */
DECL|macro|H2I_UTIME_1_LD0
mdefine_line|#define H2I_UTIME_1_LD0&t;&t;0x0f&t;&t;/* microseconds, MSB&squot;s */
DECL|macro|H2I_UTIME_1_LD1
mdefine_line|#define H2I_UTIME_1_LD1&t;&t;0xf0&t;&t;/* tenths of microseconds */
DECL|macro|H2I_UTIME_2_LD
mdefine_line|#define H2I_UTIME_2_LD&t;&t;0xffff&t;&t;/* seconds, LSB&squot;s */
DECL|macro|H2I_UTIME_3_LD
mdefine_line|#define H2I_UTIME_3_LD&t;&t;0xffff&t;&t;/* seconds, MSB&squot;s */
DECL|struct|hal2_ctl_regs
r_struct
id|hal2_ctl_regs
(brace
DECL|member|_unused0
id|u32
id|_unused0
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|isr
r_volatile
id|u32
id|isr
suffix:semicolon
multiline_comment|/* 0x10 Status Register */
DECL|member|_unused1
id|u32
id|_unused1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|rev
r_volatile
id|u32
id|rev
suffix:semicolon
multiline_comment|/* 0x20 Revision Register */
DECL|member|_unused2
id|u32
id|_unused2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|iar
r_volatile
id|u32
id|iar
suffix:semicolon
multiline_comment|/* 0x30 Indirect Address Register */
DECL|member|_unused3
id|u32
id|_unused3
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|idr0
r_volatile
id|u32
id|idr0
suffix:semicolon
multiline_comment|/* 0x40 Indirect Data Register 0 */
DECL|member|_unused4
id|u32
id|_unused4
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|idr1
r_volatile
id|u32
id|idr1
suffix:semicolon
multiline_comment|/* 0x50 Indirect Data Register 1 */
DECL|member|_unused5
id|u32
id|_unused5
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|idr2
r_volatile
id|u32
id|idr2
suffix:semicolon
multiline_comment|/* 0x60 Indirect Data Register 2 */
DECL|member|_unused6
id|u32
id|_unused6
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|idr3
r_volatile
id|u32
id|idr3
suffix:semicolon
multiline_comment|/* 0x70 Indirect Data Register 3 */
)brace
suffix:semicolon
DECL|struct|hal2_aes_regs
r_struct
id|hal2_aes_regs
(brace
DECL|member|rx_stat
r_volatile
id|u32
id|rx_stat
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Status registers */
DECL|member|rx_cr
r_volatile
id|u32
id|rx_cr
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Control registers */
DECL|member|rx_ud
r_volatile
id|u32
id|rx_ud
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* User data window */
DECL|member|rx_st
r_volatile
id|u32
id|rx_st
(braket
l_int|24
)braket
suffix:semicolon
multiline_comment|/* Channel status data */
DECL|member|tx_stat
r_volatile
id|u32
id|tx_stat
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Status register */
DECL|member|tx_cr
r_volatile
id|u32
id|tx_cr
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Control registers */
DECL|member|tx_ud
r_volatile
id|u32
id|tx_ud
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* User data window */
DECL|member|tx_st
r_volatile
id|u32
id|tx_st
(braket
l_int|24
)braket
suffix:semicolon
multiline_comment|/* Channel status data */
)brace
suffix:semicolon
DECL|struct|hal2_vol_regs
r_struct
id|hal2_vol_regs
(brace
DECL|member|right
r_volatile
id|u32
id|right
suffix:semicolon
multiline_comment|/* Right volume */
DECL|member|left
r_volatile
id|u32
id|left
suffix:semicolon
multiline_comment|/* Left volume */
)brace
suffix:semicolon
DECL|struct|hal2_syn_regs
r_struct
id|hal2_syn_regs
(brace
DECL|member|_unused0
id|u32
id|_unused0
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|page
r_volatile
id|u32
id|page
suffix:semicolon
multiline_comment|/* DOC Page register */
DECL|member|regsel
r_volatile
id|u32
id|regsel
suffix:semicolon
multiline_comment|/* DOC Register selection */
DECL|member|dlow
r_volatile
id|u32
id|dlow
suffix:semicolon
multiline_comment|/* DOC Data low */
DECL|member|dhigh
r_volatile
id|u32
id|dhigh
suffix:semicolon
multiline_comment|/* DOC Data high */
DECL|member|irq
r_volatile
id|u32
id|irq
suffix:semicolon
multiline_comment|/* IRQ Status */
DECL|member|dram
r_volatile
id|u32
id|dram
suffix:semicolon
multiline_comment|/* DRAM Access */
)brace
suffix:semicolon
macro_line|#endif&t;/* __HAL2_H */
eof
