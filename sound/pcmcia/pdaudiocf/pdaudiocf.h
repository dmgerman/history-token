multiline_comment|/*&n; * Driver for Sound Cors PDAudioCF soundcard&n; *&n; * Copyright (c) 2003 by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#ifndef __PDAUDIOCF_H
DECL|macro|__PDAUDIOCF_H
mdefine_line|#define __PDAUDIOCF_H
macro_line|#include &lt;sound/pcm.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;pcmcia/cs_types.h&gt;
macro_line|#include &lt;pcmcia/cs.h&gt;
macro_line|#include &lt;pcmcia/cistpl.h&gt;
macro_line|#include &lt;pcmcia/ds.h&gt;
macro_line|#include &lt;sound/ak4117.h&gt;
multiline_comment|/* PDAUDIOCF registers */
DECL|macro|PDAUDIOCF_REG_MD
mdefine_line|#define PDAUDIOCF_REG_MD&t;0x00&t;/* music data, R/O */
DECL|macro|PDAUDIOCF_REG_WDP
mdefine_line|#define PDAUDIOCF_REG_WDP&t;0x02&t;/* write data pointer / 2, R/O */
DECL|macro|PDAUDIOCF_REG_RDP
mdefine_line|#define PDAUDIOCF_REG_RDP&t;0x04&t;/* read data pointer / 2, R/O */
DECL|macro|PDAUDIOCF_REG_TCR
mdefine_line|#define PDAUDIOCF_REG_TCR&t;0x06&t;/* test control register W/O */
DECL|macro|PDAUDIOCF_REG_SCR
mdefine_line|#define PDAUDIOCF_REG_SCR&t;0x08&t;/* status and control, R/W (see bit description) */
DECL|macro|PDAUDIOCF_REG_ISR
mdefine_line|#define PDAUDIOCF_REG_ISR&t;0x0a&t;/* interrupt status, R/O */
DECL|macro|PDAUDIOCF_REG_IER
mdefine_line|#define PDAUDIOCF_REG_IER&t;0x0c&t;/* interrupt enable, R/W */
DECL|macro|PDAUDIOCF_REG_AK_IFR
mdefine_line|#define PDAUDIOCF_REG_AK_IFR&t;0x0e&t;/* AK interface register, R/W */
multiline_comment|/* PDAUDIOCF_REG_TCR */
DECL|macro|PDAUDIOCF_ELIMAKMBIT
mdefine_line|#define PDAUDIOCF_ELIMAKMBIT&t;(1&lt;&lt;0)&t;/* simulate AKM music data */
DECL|macro|PDAUDIOCF_TESTDATASEL
mdefine_line|#define PDAUDIOCF_TESTDATASEL&t;(1&lt;&lt;1)&t;/* test data selection, 0 = 0x55, 1 = pseudo-random */
multiline_comment|/* PDAUDIOCF_REG_SCR */
DECL|macro|PDAUDIOCF_AK_SBP
mdefine_line|#define PDAUDIOCF_AK_SBP&t;(1&lt;&lt;0)&t;/* serial port busy flag */
DECL|macro|PDAUDIOCF_RST
mdefine_line|#define PDAUDIOCF_RST&t;&t;(1&lt;&lt;2)&t;/* FPGA, AKM + SRAM buffer reset */
DECL|macro|PDAUDIOCF_PDN
mdefine_line|#define PDAUDIOCF_PDN&t;&t;(1&lt;&lt;3)&t;/* power down bit */
DECL|macro|PDAUDIOCF_CLKDIV0
mdefine_line|#define PDAUDIOCF_CLKDIV0&t;(1&lt;&lt;4)&t;/* choose 24.576Mhz clock divided by 1,2,3 or 4 */
DECL|macro|PDAUDIOCF_CLKDIV1
mdefine_line|#define PDAUDIOCF_CLKDIV1&t;(1&lt;&lt;5)
DECL|macro|PDAUDIOCF_RECORD
mdefine_line|#define PDAUDIOCF_RECORD&t;(1&lt;&lt;6)&t;/* start capturing to SRAM */
DECL|macro|PDAUDIOCF_AK_SDD
mdefine_line|#define PDAUDIOCF_AK_SDD&t;(1&lt;&lt;7)&t;/* music data detected */
DECL|macro|PDAUDIOCF_RED_LED_OFF
mdefine_line|#define PDAUDIOCF_RED_LED_OFF&t;(1&lt;&lt;8)&t;/* red LED off override */
DECL|macro|PDAUDIOCF_BLUE_LED_OFF
mdefine_line|#define PDAUDIOCF_BLUE_LED_OFF&t;(1&lt;&lt;9)&t;/* blue LED off override */
DECL|macro|PDAUDIOCF_DATAFMT0
mdefine_line|#define PDAUDIOCF_DATAFMT0&t;(1&lt;&lt;10)&t;/* data format bits: 00 = 16-bit, 01 = 18-bit */
DECL|macro|PDAUDIOCF_DATAFMT1
mdefine_line|#define PDAUDIOCF_DATAFMT1&t;(1&lt;&lt;11)&t;/* 10 = 20-bit, 11 = 24-bit, all right justified */
DECL|macro|PDAUDIOCF_FPGAREV
mdefine_line|#define PDAUDIOCF_FPGAREV(x)&t;((x&gt;&gt;12)&amp;0x0f) /* FPGA revision */
multiline_comment|/* PDAUDIOCF_REG_ISR */
DECL|macro|PDAUDIOCF_IRQLVL
mdefine_line|#define PDAUDIOCF_IRQLVL&t;(1&lt;&lt;0)&t;/* Buffer level IRQ */
DECL|macro|PDAUDIOCF_IRQOVR
mdefine_line|#define PDAUDIOCF_IRQOVR&t;(1&lt;&lt;1)&t;/* Overrun IRQ */
DECL|macro|PDAUDIOCF_IRQAKM
mdefine_line|#define PDAUDIOCF_IRQAKM&t;(1&lt;&lt;2)&t;/* AKM IRQ */
multiline_comment|/* PDAUDIOCF_REG_IER */
DECL|macro|PDAUDIOCF_IRQLVLEN0
mdefine_line|#define PDAUDIOCF_IRQLVLEN0&t;(1&lt;&lt;0)&t;/* fill threshold levels; 00 = none, 01 = 1/8th of buffer */
DECL|macro|PDAUDIOCF_IRQLVLEN1
mdefine_line|#define PDAUDIOCF_IRQLVLEN1&t;(1&lt;&lt;1)&t;/* 10 = 1/4th of buffer, 11 = 1/2th of buffer */
DECL|macro|PDAUDIOCF_IRQOVREN
mdefine_line|#define PDAUDIOCF_IRQOVREN&t;(1&lt;&lt;2)&t;/* enable overrun IRQ */
DECL|macro|PDAUDIOCF_IRQAKMEN
mdefine_line|#define PDAUDIOCF_IRQAKMEN&t;(1&lt;&lt;3)&t;/* enable AKM IRQ */
DECL|macro|PDAUDIOCF_BLUEDUTY0
mdefine_line|#define PDAUDIOCF_BLUEDUTY0&t;(1&lt;&lt;8)&t;/* blue LED duty cycle; 00 = 100%, 01 = 50% */
DECL|macro|PDAUDIOCF_BLUEDUTY1
mdefine_line|#define PDAUDIOCF_BLUEDUTY1&t;(1&lt;&lt;9)&t;/* 02 = 25%, 11 = 12% */
DECL|macro|PDAUDIOCF_REDDUTY0
mdefine_line|#define PDAUDIOCF_REDDUTY0&t;(1&lt;&lt;10)&t;/* red LED duty cycle; 00 = 100%, 01 = 50% */
DECL|macro|PDAUDIOCF_REDDUTY1
mdefine_line|#define PDAUDIOCF_REDDUTY1&t;(1&lt;&lt;11)&t;/* 02 = 25%, 11 = 12% */
DECL|macro|PDAUDIOCF_BLUESDD
mdefine_line|#define PDAUDIOCF_BLUESDD&t;(1&lt;&lt;12)&t;/* blue LED against SDD bit */
DECL|macro|PDAUDIOCF_BLUEMODULATE
mdefine_line|#define PDAUDIOCF_BLUEMODULATE&t;(1&lt;&lt;13)&t;/* save power when 100% duty cycle selected */
DECL|macro|PDAUDIOCF_REDMODULATE
mdefine_line|#define PDAUDIOCF_REDMODULATE&t;(1&lt;&lt;14)&t;/* save power when 100% duty cycle selected */
DECL|macro|PDAUDIOCF_HALFRATE
mdefine_line|#define PDAUDIOCF_HALFRATE&t;(1&lt;&lt;15)&t;/* slow both LED blinks by half (also spdif detect rate) */
multiline_comment|/* chip status */
DECL|macro|PDAUDIOCF_STAT_IS_STALE
mdefine_line|#define PDAUDIOCF_STAT_IS_STALE&t;(1&lt;&lt;0)
DECL|macro|PDAUDIOCF_STAT_IS_CONFIGURED
mdefine_line|#define PDAUDIOCF_STAT_IS_CONFIGURED (1&lt;&lt;1)
DECL|macro|PDAUDIOCF_STAT_IS_SUSPENDED
mdefine_line|#define PDAUDIOCF_STAT_IS_SUSPENDED (1&lt;&lt;2)
r_typedef
r_struct
(brace
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
DECL|member|index
r_int
id|index
suffix:semicolon
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|reg_lock
id|spinlock_t
id|reg_lock
suffix:semicolon
DECL|member|regmap
r_int
r_int
id|regmap
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|suspend_reg_scr
r_int
r_int
id|suspend_reg_scr
suffix:semicolon
DECL|member|tq
r_struct
id|tasklet_struct
id|tq
suffix:semicolon
DECL|member|ak4117_lock
id|spinlock_t
id|ak4117_lock
suffix:semicolon
DECL|member|ak4117
id|ak4117_t
op_star
id|ak4117
suffix:semicolon
DECL|member|chip_status
r_int
r_int
id|chip_status
suffix:semicolon
DECL|member|pcm
id|snd_pcm_t
op_star
id|pcm
suffix:semicolon
DECL|member|pcm_substream
id|snd_pcm_substream_t
op_star
id|pcm_substream
suffix:semicolon
DECL|member|pcm_running
r_int
r_int
id|pcm_running
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pcm_channels
r_int
r_int
id|pcm_channels
suffix:semicolon
DECL|member|pcm_swab
r_int
r_int
id|pcm_swab
suffix:semicolon
DECL|member|pcm_little
r_int
r_int
id|pcm_little
suffix:semicolon
DECL|member|pcm_frame
r_int
r_int
id|pcm_frame
suffix:semicolon
DECL|member|pcm_sample
r_int
r_int
id|pcm_sample
suffix:semicolon
DECL|member|pcm_xor
r_int
r_int
id|pcm_xor
suffix:semicolon
DECL|member|pcm_size
r_int
r_int
id|pcm_size
suffix:semicolon
DECL|member|pcm_period
r_int
r_int
id|pcm_period
suffix:semicolon
DECL|member|pcm_tdone
r_int
r_int
id|pcm_tdone
suffix:semicolon
DECL|member|pcm_hwptr
r_int
r_int
id|pcm_hwptr
suffix:semicolon
DECL|member|pcm_area
r_void
op_star
id|pcm_area
suffix:semicolon
multiline_comment|/* pcmcia stuff */
DECL|member|link
id|dev_link_t
id|link
suffix:semicolon
DECL|member|node
id|dev_node_t
id|node
suffix:semicolon
DECL|typedef|pdacf_t
)brace
id|pdacf_t
suffix:semicolon
DECL|function|pdacf_reg_write
r_static
r_inline
r_void
id|pdacf_reg_write
c_func
(paren
id|pdacf_t
op_star
id|chip
comma
r_int
r_char
id|reg
comma
r_int
r_int
id|val
)paren
(brace
id|outw
c_func
(paren
id|chip-&gt;regmap
(braket
id|reg
op_rshift
l_int|1
)braket
op_assign
id|val
comma
id|chip-&gt;port
op_plus
id|reg
)paren
suffix:semicolon
)brace
DECL|function|pdacf_reg_read
r_static
r_inline
r_int
r_int
id|pdacf_reg_read
c_func
(paren
id|pdacf_t
op_star
id|chip
comma
r_int
r_char
id|reg
)paren
(brace
r_return
id|inw
c_func
(paren
id|chip-&gt;port
op_plus
id|reg
)paren
suffix:semicolon
)brace
id|pdacf_t
op_star
id|snd_pdacf_create
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
suffix:semicolon
r_int
id|snd_pdacf_ak4117_create
c_func
(paren
id|pdacf_t
op_star
id|pdacf
)paren
suffix:semicolon
r_void
id|snd_pdacf_powerdown
c_func
(paren
id|pdacf_t
op_star
id|chip
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PM
r_int
id|snd_pdacf_suspend
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_int
r_int
id|state
)paren
suffix:semicolon
r_int
id|snd_pdacf_resume
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_int
r_int
id|state
)paren
suffix:semicolon
macro_line|#endif
r_int
id|snd_pdacf_pcm_new
c_func
(paren
id|pdacf_t
op_star
id|chip
)paren
suffix:semicolon
id|irqreturn_t
id|pdacf_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_void
id|pdacf_tasklet
c_func
(paren
r_int
r_int
id|private_data
)paren
suffix:semicolon
r_void
id|pdacf_reinit
c_func
(paren
id|pdacf_t
op_star
id|chip
comma
r_int
id|resume
)paren
suffix:semicolon
macro_line|#endif /* __PDAUDIOCF_H */
eof
