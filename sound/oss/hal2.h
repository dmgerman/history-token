macro_line|#ifndef __HAL2_H
DECL|macro|__HAL2_H
mdefine_line|#define __HAL2_H
multiline_comment|/*&n; *  Driver for HAL2 sound processors&n; *  Copyright (c) 1999 Ulf Carlsson &lt;ulfc@bun.falkenberg.se&gt;&n; *  Copyright (c) 2001 Ladislav Michl &lt;ladis@psi.cz&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License version 2 as &n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/sgi/sgihpc.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|H2_HAL2_BASE
mdefine_line|#define H2_HAL2_BASE&t;&t;0x58000
DECL|macro|H2_CTL_PIO
mdefine_line|#define H2_CTL_PIO&t;&t;(H2_HAL2_BASE + 0 * 0x400)
DECL|macro|H2_AES_PIO
mdefine_line|#define H2_AES_PIO&t;&t;(H2_HAL2_BASE + 1 * 0x400)
DECL|macro|H2_VOL_PIO
mdefine_line|#define H2_VOL_PIO&t;&t;(H2_HAL2_BASE + 2 * 0x400)
DECL|macro|H2_SYN_PIO
mdefine_line|#define H2_SYN_PIO&t;&t;(H2_HAL2_BASE + 3 * 0x400)
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
DECL|typedef|hal2_reg_t
r_typedef
r_volatile
id|u32
id|hal2_reg_t
suffix:semicolon
DECL|typedef|hal2_ctl_regs_t
r_typedef
r_struct
id|stru_hal2_ctl_regs
id|hal2_ctl_regs_t
suffix:semicolon
DECL|struct|stru_hal2_ctl_regs
r_struct
id|stru_hal2_ctl_regs
(brace
DECL|member|_unused0
id|hal2_reg_t
id|_unused0
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|isr
id|hal2_reg_t
id|isr
suffix:semicolon
multiline_comment|/* 0x10 Status Register */
DECL|member|_unused1
id|hal2_reg_t
id|_unused1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|rev
id|hal2_reg_t
id|rev
suffix:semicolon
multiline_comment|/* 0x20 Revision Register */
DECL|member|_unused2
id|hal2_reg_t
id|_unused2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|iar
id|hal2_reg_t
id|iar
suffix:semicolon
multiline_comment|/* 0x30 Indirect Address Register */
DECL|member|_unused3
id|hal2_reg_t
id|_unused3
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|idr0
id|hal2_reg_t
id|idr0
suffix:semicolon
multiline_comment|/* 0x40 Indirect Data Register 0 */
DECL|member|_unused4
id|hal2_reg_t
id|_unused4
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|idr1
id|hal2_reg_t
id|idr1
suffix:semicolon
multiline_comment|/* 0x50 Indirect Data Register 1 */
DECL|member|_unused5
id|hal2_reg_t
id|_unused5
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|idr2
id|hal2_reg_t
id|idr2
suffix:semicolon
multiline_comment|/* 0x60 Indirect Data Register 2 */
DECL|member|_unused6
id|hal2_reg_t
id|_unused6
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|idr3
id|hal2_reg_t
id|idr3
suffix:semicolon
multiline_comment|/* 0x70 Indirect Data Register 3 */
)brace
suffix:semicolon
DECL|typedef|hal2_aes_regs_t
r_typedef
r_struct
id|stru_hal2_aes_regs
id|hal2_aes_regs_t
suffix:semicolon
DECL|struct|stru_hal2_aes_regs
r_struct
id|stru_hal2_aes_regs
(brace
DECL|member|rx_stat
id|hal2_reg_t
id|rx_stat
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Status registers */
DECL|member|rx_cr
id|hal2_reg_t
id|rx_cr
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Control registers */
DECL|member|rx_ud
id|hal2_reg_t
id|rx_ud
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* User data window */
DECL|member|rx_st
id|hal2_reg_t
id|rx_st
(braket
l_int|24
)braket
suffix:semicolon
multiline_comment|/* Channel status data */
DECL|member|tx_stat
id|hal2_reg_t
id|tx_stat
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Status register */
DECL|member|tx_cr
id|hal2_reg_t
id|tx_cr
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Control registers */
DECL|member|tx_ud
id|hal2_reg_t
id|tx_ud
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* User data window */
DECL|member|tx_st
id|hal2_reg_t
id|tx_st
(braket
l_int|24
)braket
suffix:semicolon
multiline_comment|/* Channel status data */
)brace
suffix:semicolon
DECL|typedef|hal2_vol_regs_t
r_typedef
r_struct
id|stru_hal2_vol_regs
id|hal2_vol_regs_t
suffix:semicolon
DECL|struct|stru_hal2_vol_regs
r_struct
id|stru_hal2_vol_regs
(brace
DECL|member|right
id|hal2_reg_t
id|right
suffix:semicolon
multiline_comment|/* 0x00 Right volume */
DECL|member|left
id|hal2_reg_t
id|left
suffix:semicolon
multiline_comment|/* 0x04 Left volume */
)brace
suffix:semicolon
DECL|typedef|hal2_syn_regs_t
r_typedef
r_struct
id|stru_hal2_syn_regs
id|hal2_syn_regs_t
suffix:semicolon
DECL|struct|stru_hal2_syn_regs
r_struct
id|stru_hal2_syn_regs
(brace
DECL|member|_unused0
id|hal2_reg_t
id|_unused0
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|page
id|hal2_reg_t
id|page
suffix:semicolon
multiline_comment|/* DOC Page register */
DECL|member|regsel
id|hal2_reg_t
id|regsel
suffix:semicolon
multiline_comment|/* DOC Register selection */
DECL|member|dlow
id|hal2_reg_t
id|dlow
suffix:semicolon
multiline_comment|/* DOC Data low */
DECL|member|dhigh
id|hal2_reg_t
id|dhigh
suffix:semicolon
multiline_comment|/* DOC Data high */
DECL|member|irq
id|hal2_reg_t
id|irq
suffix:semicolon
multiline_comment|/* IRQ Status */
DECL|member|dram
id|hal2_reg_t
id|dram
suffix:semicolon
multiline_comment|/* DRAM Access */
)brace
suffix:semicolon
multiline_comment|/* HAL2 specific structures */
DECL|typedef|hal2_pbus_t
r_typedef
r_struct
id|stru_hal2_pbus
id|hal2_pbus_t
suffix:semicolon
DECL|struct|stru_hal2_pbus
r_struct
id|stru_hal2_pbus
(brace
DECL|member|pbus
r_struct
id|hpc3_pbus_dmacregs
op_star
id|pbus
suffix:semicolon
DECL|member|pbusnr
r_int
id|pbusnr
suffix:semicolon
DECL|member|ctrl
r_int
r_int
id|ctrl
suffix:semicolon
multiline_comment|/* Current state of pbus-&gt;pbdma_ctrl */
)brace
suffix:semicolon
DECL|typedef|hal2_binfo_t
r_typedef
r_struct
id|stru_hal2_binfo
id|hal2_binfo_t
suffix:semicolon
DECL|typedef|hal2_buf_t
r_typedef
r_struct
id|stru_hal2_buffer
id|hal2_buf_t
suffix:semicolon
DECL|struct|stru_hal2_binfo
r_struct
id|stru_hal2_binfo
(brace
DECL|member|desc
r_volatile
r_struct
id|hpc_dma_desc
id|desc
suffix:semicolon
DECL|member|next
id|hal2_buf_t
op_star
id|next
suffix:semicolon
multiline_comment|/* pointer to next buffer */
DECL|member|cnt
r_int
id|cnt
suffix:semicolon
multiline_comment|/* bytes in buffer */
)brace
suffix:semicolon
DECL|macro|H2_BUFFER_SIZE
mdefine_line|#define H2_BUFFER_SIZE&t;(PAGE_SIZE - &bslash;&n;&t;&t;((sizeof(hal2_binfo_t) - 1) / 8 + 1) * 8)
DECL|struct|stru_hal2_buffer
r_struct
id|stru_hal2_buffer
(brace
DECL|member|info
id|hal2_binfo_t
id|info
suffix:semicolon
DECL|member|data
r_char
id|data
(braket
id|H2_BUFFER_SIZE
)braket
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|hal2_codec_t
r_typedef
r_struct
id|stru_hal2_codec
id|hal2_codec_t
suffix:semicolon
DECL|struct|stru_hal2_codec
r_struct
id|stru_hal2_codec
(brace
DECL|member|head
id|hal2_buf_t
op_star
id|head
suffix:semicolon
DECL|member|tail
id|hal2_buf_t
op_star
id|tail
suffix:semicolon
DECL|member|pbus
id|hal2_pbus_t
id|pbus
suffix:semicolon
DECL|member|format
r_int
r_int
id|format
suffix:semicolon
multiline_comment|/* Audio data format */
DECL|member|voices
r_int
id|voices
suffix:semicolon
multiline_comment|/* mono/stereo */
DECL|member|sample_rate
r_int
r_int
id|sample_rate
suffix:semicolon
DECL|member|master
r_int
r_int
id|master
suffix:semicolon
multiline_comment|/* Master frequency */
DECL|member|mod
r_int
r_int
id|mod
suffix:semicolon
multiline_comment|/* MOD value */
DECL|member|inc
r_int
r_int
id|inc
suffix:semicolon
multiline_comment|/* INC value */
DECL|member|dma_wait
id|wait_queue_head_t
id|dma_wait
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
DECL|member|usecount
r_int
id|usecount
suffix:semicolon
multiline_comment|/* recording and playback are &n;&t;&t;&t;&t;&t; * independent */
)brace
suffix:semicolon
DECL|macro|H2_MIX_OUTPUT_ATT
mdefine_line|#define H2_MIX_OUTPUT_ATT&t;0
DECL|macro|H2_MIX_INPUT_GAIN
mdefine_line|#define H2_MIX_INPUT_GAIN&t;1
DECL|macro|H2_MIXERS
mdefine_line|#define H2_MIXERS&t;&t;2
DECL|typedef|hal2_mixer_t
r_typedef
r_struct
id|stru_hal2_mixer
id|hal2_mixer_t
suffix:semicolon
DECL|struct|stru_hal2_mixer
r_struct
id|stru_hal2_mixer
(brace
DECL|member|modcnt
r_int
id|modcnt
suffix:semicolon
DECL|member|volume
r_int
r_int
id|volume
(braket
id|H2_MIXERS
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|hal2_card_t
r_typedef
r_struct
id|stru_hal2_card
id|hal2_card_t
suffix:semicolon
DECL|struct|stru_hal2_card
r_struct
id|stru_hal2_card
(brace
DECL|member|dev_dsp
r_int
id|dev_dsp
suffix:semicolon
multiline_comment|/* audio device */
DECL|member|dev_mixer
r_int
id|dev_mixer
suffix:semicolon
multiline_comment|/* mixer device */
DECL|member|dev_midi
r_int
id|dev_midi
suffix:semicolon
multiline_comment|/* midi device */
DECL|member|ctl_regs
id|hal2_ctl_regs_t
op_star
id|ctl_regs
suffix:semicolon
multiline_comment|/* HAL2 ctl registers */
DECL|member|aes_regs
id|hal2_aes_regs_t
op_star
id|aes_regs
suffix:semicolon
multiline_comment|/* HAL2 vol registers */
DECL|member|vol_regs
id|hal2_vol_regs_t
op_star
id|vol_regs
suffix:semicolon
multiline_comment|/* HAL2 aes registers */
DECL|member|syn_regs
id|hal2_syn_regs_t
op_star
id|syn_regs
suffix:semicolon
multiline_comment|/* HAL2 syn registers */
DECL|member|dac
id|hal2_codec_t
id|dac
suffix:semicolon
DECL|member|adc
id|hal2_codec_t
id|adc
suffix:semicolon
DECL|member|mixer
id|hal2_mixer_t
id|mixer
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* __HAL2_H */
eof
