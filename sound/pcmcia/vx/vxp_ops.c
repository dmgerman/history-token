multiline_comment|/*&n; * Driver for Digigram VXpocket soundcards&n; *&n; * lowlevel routines for VXpocket soundcards&n; *&n; * Copyright (c) 2002 by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/firmware.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;vxpocket.h&quot;
DECL|variable|vxp_reg_offset
r_static
r_int
id|vxp_reg_offset
(braket
id|VX_REG_MAX
)braket
op_assign
(brace
(braket
id|VX_ICR
)braket
op_assign
l_int|0x00
comma
singleline_comment|// ICR
(braket
id|VX_CVR
)braket
op_assign
l_int|0x01
comma
singleline_comment|// CVR
(braket
id|VX_ISR
)braket
op_assign
l_int|0x02
comma
singleline_comment|// ISR
(braket
id|VX_IVR
)braket
op_assign
l_int|0x03
comma
singleline_comment|// IVR
(braket
id|VX_RXH
)braket
op_assign
l_int|0x05
comma
singleline_comment|// RXH
(braket
id|VX_RXM
)braket
op_assign
l_int|0x06
comma
singleline_comment|// RXM
(braket
id|VX_RXL
)braket
op_assign
l_int|0x07
comma
singleline_comment|// RXL
(braket
id|VX_DMA
)braket
op_assign
l_int|0x04
comma
singleline_comment|// DMA
(braket
id|VX_CDSP
)braket
op_assign
l_int|0x08
comma
singleline_comment|// CDSP
(braket
id|VX_LOFREQ
)braket
op_assign
l_int|0x09
comma
singleline_comment|// LFREQ
(braket
id|VX_HIFREQ
)braket
op_assign
l_int|0x0a
comma
singleline_comment|// HFREQ
(braket
id|VX_DATA
)braket
op_assign
l_int|0x0b
comma
singleline_comment|// DATA
(braket
id|VX_MICRO
)braket
op_assign
l_int|0x0c
comma
singleline_comment|// MICRO
(braket
id|VX_DIALOG
)braket
op_assign
l_int|0x0d
comma
singleline_comment|// DIALOG
(braket
id|VX_CSUER
)braket
op_assign
l_int|0x0e
comma
singleline_comment|// CSUER
(braket
id|VX_RUER
)braket
op_assign
l_int|0x0f
comma
singleline_comment|// RUER
)brace
suffix:semicolon
DECL|function|vxp_reg_addr
r_inline
r_static
r_int
r_int
id|vxp_reg_addr
c_func
(paren
id|vx_core_t
op_star
id|_chip
comma
r_int
id|reg
)paren
(brace
r_struct
id|snd_vxpocket
op_star
id|chip
op_assign
(paren
r_struct
id|snd_vxpocket
op_star
)paren
id|_chip
suffix:semicolon
r_return
id|chip-&gt;port
op_plus
id|vxp_reg_offset
(braket
id|reg
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; * snd_vx_inb - read a byte from the register&n; * @offset: register offset&n; */
DECL|function|vxp_inb
r_static
r_int
r_char
id|vxp_inb
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|offset
)paren
(brace
r_return
id|inb
c_func
(paren
id|vxp_reg_addr
c_func
(paren
id|chip
comma
id|offset
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * snd_vx_outb - write a byte on the register&n; * @offset: the register offset&n; * @val: the value to write&n; */
DECL|function|vxp_outb
r_static
r_void
id|vxp_outb
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|offset
comma
r_int
r_char
id|val
)paren
(brace
id|outb
c_func
(paren
id|val
comma
id|vxp_reg_addr
c_func
(paren
id|chip
comma
id|offset
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * redefine macros to call directly&n; */
DECL|macro|vx_inb
macro_line|#undef vx_inb
DECL|macro|vx_inb
mdefine_line|#define vx_inb(chip,reg)&t;vxp_inb((vx_core_t*)(chip), VX_##reg)
DECL|macro|vx_outb
macro_line|#undef vx_outb
DECL|macro|vx_outb
mdefine_line|#define vx_outb(chip,reg,val)&t;vxp_outb((vx_core_t*)(chip), VX_##reg,val)
multiline_comment|/*&n; * vx_check_magic - check the magic word on xilinx&n; *&n; * returns zero if a magic word is detected, or a negative error code.&n; */
DECL|function|vx_check_magic
r_static
r_int
id|vx_check_magic
c_func
(paren
id|vx_core_t
op_star
id|chip
)paren
(brace
r_int
r_int
id|end_time
op_assign
id|jiffies
op_plus
id|HZ
op_div
l_int|5
suffix:semicolon
r_int
id|c
suffix:semicolon
r_do
(brace
id|c
op_assign
id|vx_inb
c_func
(paren
id|chip
comma
id|CDSP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
id|CDSP_MAGIC
)paren
r_return
l_int|0
suffix:semicolon
id|snd_vx_delay
c_func
(paren
id|chip
comma
l_int|10
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|time_after_eq
c_func
(paren
id|end_time
comma
id|jiffies
)paren
)paren
suffix:semicolon
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cannot find xilinx magic word (%x)&bslash;n&quot;
comma
id|c
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/*&n; * vx_reset_dsp - reset the DSP&n; */
DECL|macro|XX_DSP_RESET_WAIT_TIME
mdefine_line|#define XX_DSP_RESET_WAIT_TIME&t;&t;2&t;/* ms */
DECL|function|vxp_reset_dsp
r_static
r_void
id|vxp_reset_dsp
c_func
(paren
id|vx_core_t
op_star
id|_chip
)paren
(brace
r_struct
id|snd_vxpocket
op_star
id|chip
op_assign
(paren
r_struct
id|snd_vxpocket
op_star
)paren
id|_chip
suffix:semicolon
multiline_comment|/* set the reset dsp bit to 1 */
id|vx_outb
c_func
(paren
id|chip
comma
id|CDSP
comma
id|chip-&gt;regCDSP
op_or
id|VXP_CDSP_DSP_RESET_MASK
)paren
suffix:semicolon
id|vx_inb
c_func
(paren
id|chip
comma
id|CDSP
)paren
suffix:semicolon
id|mdelay
c_func
(paren
id|XX_DSP_RESET_WAIT_TIME
)paren
suffix:semicolon
multiline_comment|/* reset the bit */
id|chip-&gt;regCDSP
op_and_assign
op_complement
id|VXP_CDSP_DSP_RESET_MASK
suffix:semicolon
id|vx_outb
c_func
(paren
id|chip
comma
id|CDSP
comma
id|chip-&gt;regCDSP
)paren
suffix:semicolon
id|vx_inb
c_func
(paren
id|chip
comma
id|CDSP
)paren
suffix:semicolon
id|mdelay
c_func
(paren
id|XX_DSP_RESET_WAIT_TIME
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * reset codec bit&n; */
DECL|function|vxp_reset_codec
r_static
r_void
id|vxp_reset_codec
c_func
(paren
id|vx_core_t
op_star
id|_chip
)paren
(brace
r_struct
id|snd_vxpocket
op_star
id|chip
op_assign
(paren
r_struct
id|snd_vxpocket
op_star
)paren
id|_chip
suffix:semicolon
multiline_comment|/* Set the reset CODEC bit to 1. */
id|vx_outb
c_func
(paren
id|chip
comma
id|CDSP
comma
id|chip-&gt;regCDSP
op_or
id|VXP_CDSP_CODEC_RESET_MASK
)paren
suffix:semicolon
id|vx_inb
c_func
(paren
id|chip
comma
id|CDSP
)paren
suffix:semicolon
id|snd_vx_delay
c_func
(paren
id|_chip
comma
l_int|10
)paren
suffix:semicolon
multiline_comment|/* Set the reset CODEC bit to 0. */
id|chip-&gt;regCDSP
op_and_assign
op_complement
id|VXP_CDSP_CODEC_RESET_MASK
suffix:semicolon
id|vx_outb
c_func
(paren
id|chip
comma
id|CDSP
comma
id|chip-&gt;regCDSP
)paren
suffix:semicolon
id|vx_inb
c_func
(paren
id|chip
comma
id|CDSP
)paren
suffix:semicolon
id|snd_vx_delay
c_func
(paren
id|_chip
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * vx_load_xilinx_binary - load the xilinx binary image&n; * the binary image is the binary array converted from the bitstream file.&n; */
DECL|function|vxp_load_xilinx_binary
r_static
r_int
id|vxp_load_xilinx_binary
c_func
(paren
id|vx_core_t
op_star
id|_chip
comma
r_const
r_struct
id|firmware
op_star
id|fw
)paren
(brace
r_struct
id|snd_vxpocket
op_star
id|chip
op_assign
(paren
r_struct
id|snd_vxpocket
op_star
)paren
id|_chip
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_int
id|c
suffix:semicolon
r_int
id|regCSUER
comma
id|regRUER
suffix:semicolon
r_int
r_char
op_star
id|image
suffix:semicolon
r_int
r_char
id|data
suffix:semicolon
multiline_comment|/* Switch to programmation mode */
id|chip-&gt;regDIALOG
op_or_assign
id|VXP_DLG_XILINX_REPROG_MASK
suffix:semicolon
id|vx_outb
c_func
(paren
id|chip
comma
id|DIALOG
comma
id|chip-&gt;regDIALOG
)paren
suffix:semicolon
multiline_comment|/* Save register CSUER and RUER */
id|regCSUER
op_assign
id|vx_inb
c_func
(paren
id|chip
comma
id|CSUER
)paren
suffix:semicolon
id|regRUER
op_assign
id|vx_inb
c_func
(paren
id|chip
comma
id|RUER
)paren
suffix:semicolon
multiline_comment|/* reset HF0 and HF1 */
id|vx_outb
c_func
(paren
id|chip
comma
id|ICR
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Wait for answer HF2 equal to 1 */
id|snd_printdd
c_func
(paren
id|KERN_DEBUG
l_string|&quot;check ISR_HF2&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vx_check_isr
c_func
(paren
id|_chip
comma
id|ISR_HF2
comma
id|ISR_HF2
comma
l_int|20
)paren
OL
l_int|0
)paren
r_goto
id|_error
suffix:semicolon
multiline_comment|/* set HF1 for loading xilinx binary */
id|vx_outb
c_func
(paren
id|chip
comma
id|ICR
comma
id|ICR_HF1
)paren
suffix:semicolon
id|image
op_assign
id|fw-&gt;data
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|fw-&gt;size
suffix:semicolon
id|i
op_increment
comma
id|image
op_increment
)paren
(brace
id|data
op_assign
op_star
id|image
suffix:semicolon
r_if
c_cond
(paren
id|vx_wait_isr_bit
c_func
(paren
id|_chip
comma
id|ISR_TX_EMPTY
)paren
OL
l_int|0
)paren
r_goto
id|_error
suffix:semicolon
id|vx_outb
c_func
(paren
id|chip
comma
id|TXL
comma
id|data
)paren
suffix:semicolon
multiline_comment|/* wait for reading */
r_if
c_cond
(paren
id|vx_wait_for_rx_full
c_func
(paren
id|_chip
)paren
OL
l_int|0
)paren
r_goto
id|_error
suffix:semicolon
id|c
op_assign
id|vx_inb
c_func
(paren
id|chip
comma
id|RXL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ne
(paren
r_int
)paren
id|data
)paren
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;vxpocket: load xilinx mismatch at %d: 0x%x != 0x%x&bslash;n&quot;
comma
id|i
comma
id|c
comma
(paren
r_int
)paren
id|data
)paren
suffix:semicolon
)brace
multiline_comment|/* reset HF1 */
id|vx_outb
c_func
(paren
id|chip
comma
id|ICR
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* wait for HF3 */
r_if
c_cond
(paren
id|vx_check_isr
c_func
(paren
id|_chip
comma
id|ISR_HF3
comma
id|ISR_HF3
comma
l_int|20
)paren
OL
l_int|0
)paren
r_goto
id|_error
suffix:semicolon
multiline_comment|/* read the number of bytes received */
r_if
c_cond
(paren
id|vx_wait_for_rx_full
c_func
(paren
id|_chip
)paren
OL
l_int|0
)paren
r_goto
id|_error
suffix:semicolon
id|c
op_assign
(paren
r_int
)paren
id|vx_inb
c_func
(paren
id|chip
comma
id|RXH
)paren
op_lshift
l_int|16
suffix:semicolon
id|c
op_or_assign
(paren
r_int
)paren
id|vx_inb
c_func
(paren
id|chip
comma
id|RXM
)paren
op_lshift
l_int|8
suffix:semicolon
id|c
op_or_assign
id|vx_inb
c_func
(paren
id|chip
comma
id|RXL
)paren
suffix:semicolon
id|snd_printdd
c_func
(paren
id|KERN_DEBUG
l_string|&quot;xilinx: dsp size received 0x%x, orig 0x%x&bslash;n&quot;
comma
id|c
comma
id|fw-&gt;size
)paren
suffix:semicolon
id|vx_outb
c_func
(paren
id|chip
comma
id|ICR
comma
id|ICR_HF0
)paren
suffix:semicolon
multiline_comment|/* TEMPO 250ms : wait until Xilinx is downloaded */
id|snd_vx_delay
c_func
(paren
id|_chip
comma
l_int|300
)paren
suffix:semicolon
multiline_comment|/* test magical word */
r_if
c_cond
(paren
id|vx_check_magic
c_func
(paren
id|_chip
)paren
OL
l_int|0
)paren
r_goto
id|_error
suffix:semicolon
multiline_comment|/* Restore register 0x0E and 0x0F (thus replacing COR and FCSR) */
id|vx_outb
c_func
(paren
id|chip
comma
id|CSUER
comma
id|regCSUER
)paren
suffix:semicolon
id|vx_outb
c_func
(paren
id|chip
comma
id|RUER
comma
id|regRUER
)paren
suffix:semicolon
multiline_comment|/* Reset the Xilinx&squot;s signal enabling IO access */
id|chip-&gt;regDIALOG
op_or_assign
id|VXP_DLG_XILINX_REPROG_MASK
suffix:semicolon
id|vx_outb
c_func
(paren
id|chip
comma
id|DIALOG
comma
id|chip-&gt;regDIALOG
)paren
suffix:semicolon
id|vx_inb
c_func
(paren
id|chip
comma
id|DIALOG
)paren
suffix:semicolon
id|snd_vx_delay
c_func
(paren
id|_chip
comma
l_int|10
)paren
suffix:semicolon
id|chip-&gt;regDIALOG
op_and_assign
op_complement
id|VXP_DLG_XILINX_REPROG_MASK
suffix:semicolon
id|vx_outb
c_func
(paren
id|chip
comma
id|DIALOG
comma
id|chip-&gt;regDIALOG
)paren
suffix:semicolon
id|vx_inb
c_func
(paren
id|chip
comma
id|DIALOG
)paren
suffix:semicolon
multiline_comment|/* Reset of the Codec */
id|vxp_reset_codec
c_func
(paren
id|_chip
)paren
suffix:semicolon
id|vx_reset_dsp
c_func
(paren
id|_chip
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|_error
suffix:colon
id|vx_outb
c_func
(paren
id|chip
comma
id|CSUER
comma
id|regCSUER
)paren
suffix:semicolon
id|vx_outb
c_func
(paren
id|chip
comma
id|RUER
comma
id|regRUER
)paren
suffix:semicolon
id|chip-&gt;regDIALOG
op_and_assign
op_complement
id|VXP_DLG_XILINX_REPROG_MASK
suffix:semicolon
id|vx_outb
c_func
(paren
id|chip
comma
id|DIALOG
comma
id|chip-&gt;regDIALOG
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/*&n; * vxp_load_dsp - load_dsp callback&n; */
DECL|function|vxp_load_dsp
r_static
r_int
id|vxp_load_dsp
c_func
(paren
id|vx_core_t
op_star
id|vx
comma
r_int
id|index
comma
r_const
r_struct
id|firmware
op_star
id|fw
)paren
(brace
r_int
id|err
suffix:semicolon
r_switch
c_cond
(paren
id|index
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* xilinx boot */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|vx_check_magic
c_func
(paren
id|vx
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_vx_load_boot_image
c_func
(paren
id|vx
comma
id|fw
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* xilinx image */
r_return
id|vxp_load_xilinx_binary
c_func
(paren
id|vx
comma
id|fw
)paren
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* DSP boot */
r_return
id|snd_vx_dsp_boot
c_func
(paren
id|vx
comma
id|fw
)paren
suffix:semicolon
r_case
l_int|3
suffix:colon
multiline_comment|/* DSP image */
r_return
id|snd_vx_dsp_load
c_func
(paren
id|vx
comma
id|fw
)paren
suffix:semicolon
r_default
suffix:colon
id|snd_BUG
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * vx_test_and_ack - test and acknowledge interrupt&n; *&n; * called from irq hander, too&n; *&n; * spinlock held!&n; */
DECL|function|vxp_test_and_ack
r_static
r_int
id|vxp_test_and_ack
c_func
(paren
id|vx_core_t
op_star
id|_chip
)paren
(brace
r_struct
id|snd_vxpocket
op_star
id|chip
op_assign
(paren
r_struct
id|snd_vxpocket
op_star
)paren
id|_chip
suffix:semicolon
multiline_comment|/* not booted yet? */
r_if
c_cond
(paren
op_logical_neg
(paren
id|_chip-&gt;chip_status
op_amp
id|VX_STAT_XILINX_LOADED
)paren
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|vx_inb
c_func
(paren
id|chip
comma
id|DIALOG
)paren
op_amp
id|VXP_DLG_MEMIRQ_MASK
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* ok, interrupts generated, now ack it */
multiline_comment|/* set ACQUIT bit up and down */
id|vx_outb
c_func
(paren
id|chip
comma
id|DIALOG
comma
id|chip-&gt;regDIALOG
op_or
id|VXP_DLG_ACK_MEMIRQ_MASK
)paren
suffix:semicolon
multiline_comment|/* useless read just to spend some time and maintain&n;&t; * the ACQUIT signal up for a while ( a bus cycle )&n;&t; */
id|vx_inb
c_func
(paren
id|chip
comma
id|DIALOG
)paren
suffix:semicolon
id|vx_outb
c_func
(paren
id|chip
comma
id|DIALOG
comma
id|chip-&gt;regDIALOG
op_amp
op_complement
id|VXP_DLG_ACK_MEMIRQ_MASK
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * vx_validate_irq - enable/disable IRQ&n; */
DECL|function|vxp_validate_irq
r_static
r_void
id|vxp_validate_irq
c_func
(paren
id|vx_core_t
op_star
id|_chip
comma
r_int
id|enable
)paren
(brace
r_struct
id|snd_vxpocket
op_star
id|chip
op_assign
(paren
r_struct
id|snd_vxpocket
op_star
)paren
id|_chip
suffix:semicolon
multiline_comment|/* Set the interrupt enable bit to 1 in CDSP register */
r_if
c_cond
(paren
id|enable
)paren
id|chip-&gt;regCDSP
op_or_assign
id|VXP_CDSP_VALID_IRQ_MASK
suffix:semicolon
r_else
id|chip-&gt;regCDSP
op_and_assign
op_complement
id|VXP_CDSP_VALID_IRQ_MASK
suffix:semicolon
id|vx_outb
c_func
(paren
id|chip
comma
id|CDSP
comma
id|chip-&gt;regCDSP
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * vx_setup_pseudo_dma - set up the pseudo dma read/write mode.&n; * @do_write: 0 = read, 1 = set up for DMA write&n; */
DECL|function|vx_setup_pseudo_dma
r_static
r_void
id|vx_setup_pseudo_dma
c_func
(paren
id|vx_core_t
op_star
id|_chip
comma
r_int
id|do_write
)paren
(brace
r_struct
id|snd_vxpocket
op_star
id|chip
op_assign
(paren
r_struct
id|snd_vxpocket
op_star
)paren
id|_chip
suffix:semicolon
multiline_comment|/* Interrupt mode and HREQ pin enabled for host transmit / receive data transfers */
id|vx_outb
c_func
(paren
id|chip
comma
id|ICR
comma
id|do_write
ques
c_cond
id|ICR_TREQ
suffix:colon
id|ICR_RREQ
)paren
suffix:semicolon
multiline_comment|/* Reset the pseudo-dma register */
id|vx_inb
c_func
(paren
id|chip
comma
id|ISR
)paren
suffix:semicolon
id|vx_outb
c_func
(paren
id|chip
comma
id|ISR
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Select DMA in read/write transfer mode and in 16-bit accesses */
id|chip-&gt;regDIALOG
op_or_assign
id|VXP_DLG_DMA16_SEL_MASK
suffix:semicolon
id|chip-&gt;regDIALOG
op_or_assign
id|do_write
ques
c_cond
id|VXP_DLG_DMAWRITE_SEL_MASK
suffix:colon
id|VXP_DLG_DMAREAD_SEL_MASK
suffix:semicolon
id|vx_outb
c_func
(paren
id|chip
comma
id|DIALOG
comma
id|chip-&gt;regDIALOG
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * vx_release_pseudo_dma - disable the pseudo-DMA mode&n; */
DECL|function|vx_release_pseudo_dma
r_static
r_void
id|vx_release_pseudo_dma
c_func
(paren
id|vx_core_t
op_star
id|_chip
)paren
(brace
r_struct
id|snd_vxpocket
op_star
id|chip
op_assign
(paren
r_struct
id|snd_vxpocket
op_star
)paren
id|_chip
suffix:semicolon
multiline_comment|/* Disable DMA and 16-bit accesses */
id|chip-&gt;regDIALOG
op_and_assign
op_complement
(paren
id|VXP_DLG_DMAWRITE_SEL_MASK
op_or
id|VXP_DLG_DMAREAD_SEL_MASK
op_or
id|VXP_DLG_DMA16_SEL_MASK
)paren
suffix:semicolon
id|vx_outb
c_func
(paren
id|chip
comma
id|DIALOG
comma
id|chip-&gt;regDIALOG
)paren
suffix:semicolon
multiline_comment|/* HREQ pin disabled. */
id|vx_outb
c_func
(paren
id|chip
comma
id|ICR
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * vx_pseudo_dma_write - write bulk data on pseudo-DMA mode&n; * @count: data length to transfer in bytes&n; *&n; * data size must be aligned to 6 bytes to ensure the 24bit alignment on DSP.&n; * NB: call with a certain lock!&n; */
DECL|function|vxp_dma_write
r_static
r_void
id|vxp_dma_write
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
id|snd_pcm_runtime_t
op_star
id|runtime
comma
id|vx_pipe_t
op_star
id|pipe
comma
r_int
id|count
)paren
(brace
r_int
id|port
op_assign
id|vxp_reg_addr
c_func
(paren
id|chip
comma
id|VX_DMA
)paren
suffix:semicolon
r_int
id|offset
op_assign
id|pipe-&gt;hw_ptr
suffix:semicolon
r_int
r_int
op_star
id|addr
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|runtime-&gt;dma_area
op_plus
id|offset
)paren
suffix:semicolon
id|vx_setup_pseudo_dma
c_func
(paren
id|chip
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_plus
id|count
OG
id|pipe-&gt;buffer_bytes
)paren
(brace
r_int
id|length
op_assign
id|pipe-&gt;buffer_bytes
op_minus
id|offset
suffix:semicolon
id|count
op_sub_assign
id|length
suffix:semicolon
id|length
op_rshift_assign
l_int|1
suffix:semicolon
multiline_comment|/* in 16bit words */
multiline_comment|/* Transfer using pseudo-dma. */
r_while
c_loop
(paren
id|length
op_decrement
OG
l_int|0
)paren
(brace
id|outw
c_func
(paren
id|cpu_to_le16
c_func
(paren
op_star
id|addr
)paren
comma
id|port
)paren
suffix:semicolon
id|addr
op_increment
suffix:semicolon
)brace
id|addr
op_assign
(paren
r_int
r_int
op_star
)paren
id|runtime-&gt;dma_area
suffix:semicolon
id|pipe-&gt;hw_ptr
op_assign
l_int|0
suffix:semicolon
)brace
id|pipe-&gt;hw_ptr
op_add_assign
id|count
suffix:semicolon
id|count
op_rshift_assign
l_int|1
suffix:semicolon
multiline_comment|/* in 16bit words */
multiline_comment|/* Transfer using pseudo-dma. */
r_while
c_loop
(paren
id|count
op_decrement
OG
l_int|0
)paren
(brace
id|outw
c_func
(paren
id|cpu_to_le16
c_func
(paren
op_star
id|addr
)paren
comma
id|port
)paren
suffix:semicolon
id|addr
op_increment
suffix:semicolon
)brace
id|vx_release_pseudo_dma
c_func
(paren
id|chip
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * vx_pseudo_dma_read - read bulk data on pseudo DMA mode&n; * @offset: buffer offset in bytes&n; * @count: data length to transfer in bytes&n; *&n; * the read length must be aligned to 6 bytes, as well as write.&n; * NB: call with a certain lock!&n; */
DECL|function|vxp_dma_read
r_static
r_void
id|vxp_dma_read
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
id|snd_pcm_runtime_t
op_star
id|runtime
comma
id|vx_pipe_t
op_star
id|pipe
comma
r_int
id|count
)paren
(brace
r_struct
id|snd_vxpocket
op_star
id|pchip
op_assign
(paren
r_struct
id|snd_vxpocket
op_star
)paren
id|chip
suffix:semicolon
r_int
id|port
op_assign
id|vxp_reg_addr
c_func
(paren
id|chip
comma
id|VX_DMA
)paren
suffix:semicolon
r_int
id|offset
op_assign
id|pipe-&gt;hw_ptr
suffix:semicolon
r_int
r_int
op_star
id|addr
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|runtime-&gt;dma_area
op_plus
id|offset
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|count
op_mod
l_int|2
op_eq
l_int|0
comma
r_return
)paren
suffix:semicolon
id|vx_setup_pseudo_dma
c_func
(paren
id|chip
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_plus
id|count
OG
id|pipe-&gt;buffer_bytes
)paren
(brace
r_int
id|length
op_assign
id|pipe-&gt;buffer_bytes
op_minus
id|offset
suffix:semicolon
id|count
op_sub_assign
id|length
suffix:semicolon
id|length
op_rshift_assign
l_int|1
suffix:semicolon
multiline_comment|/* in 16bit words */
multiline_comment|/* Transfer using pseudo-dma. */
r_while
c_loop
(paren
id|length
op_decrement
OG
l_int|0
)paren
op_star
id|addr
op_increment
op_assign
id|le16_to_cpu
c_func
(paren
id|inw
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
id|addr
op_assign
(paren
r_int
r_int
op_star
)paren
id|runtime-&gt;dma_area
suffix:semicolon
id|pipe-&gt;hw_ptr
op_assign
l_int|0
suffix:semicolon
)brace
id|pipe-&gt;hw_ptr
op_add_assign
id|count
suffix:semicolon
id|count
op_rshift_assign
l_int|1
suffix:semicolon
multiline_comment|/* in 16bit words */
multiline_comment|/* Transfer using pseudo-dma. */
r_while
c_loop
(paren
id|count
op_decrement
OG
l_int|1
)paren
op_star
id|addr
op_increment
op_assign
id|le16_to_cpu
c_func
(paren
id|inw
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
multiline_comment|/* Disable DMA */
id|pchip-&gt;regDIALOG
op_and_assign
op_complement
id|VXP_DLG_DMAREAD_SEL_MASK
suffix:semicolon
id|vx_outb
c_func
(paren
id|chip
comma
id|DIALOG
comma
id|pchip-&gt;regDIALOG
)paren
suffix:semicolon
multiline_comment|/* Read the last word (16 bits) */
op_star
id|addr
op_assign
id|le16_to_cpu
c_func
(paren
id|inw
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
multiline_comment|/* Disable 16-bit accesses */
id|pchip-&gt;regDIALOG
op_and_assign
op_complement
id|VXP_DLG_DMA16_SEL_MASK
suffix:semicolon
id|vx_outb
c_func
(paren
id|chip
comma
id|DIALOG
comma
id|pchip-&gt;regDIALOG
)paren
suffix:semicolon
multiline_comment|/* HREQ pin disabled. */
id|vx_outb
c_func
(paren
id|chip
comma
id|ICR
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * write a codec data (24bit)&n; */
DECL|function|vxp_write_codec_reg
r_static
r_void
id|vxp_write_codec_reg
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|codec
comma
r_int
r_int
id|data
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* Activate access to the corresponding codec register */
r_if
c_cond
(paren
op_logical_neg
id|codec
)paren
id|vx_inb
c_func
(paren
id|chip
comma
id|LOFREQ
)paren
suffix:semicolon
r_else
id|vx_inb
c_func
(paren
id|chip
comma
id|CODEC2
)paren
suffix:semicolon
multiline_comment|/* We have to send 24 bits (3 x 8 bits). Start with most signif. Bit */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|24
suffix:semicolon
id|i
op_increment
comma
id|data
op_lshift_assign
l_int|1
)paren
id|vx_outb
c_func
(paren
id|chip
comma
id|DATA
comma
(paren
(paren
id|data
op_amp
l_int|0x800000
)paren
ques
c_cond
id|VX_DATA_CODEC_MASK
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
multiline_comment|/* Terminate access to codec registers */
id|vx_inb
c_func
(paren
id|chip
comma
id|HIFREQ
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * vx_set_mic_boost - set mic boost level (on vxp440 only)&n; * @boost: 0 = 20dB, 1 = +38dB&n; */
DECL|function|vx_set_mic_boost
r_void
id|vx_set_mic_boost
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|boost
)paren
(brace
r_struct
id|snd_vxpocket
op_star
id|pchip
op_assign
(paren
r_struct
id|snd_vxpocket
op_star
)paren
id|chip
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|chip-&gt;chip_status
op_amp
id|VX_STAT_IS_STALE
)paren
r_return
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|chip-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pchip-&gt;regCDSP
op_amp
id|P24_CDSP_MICS_SEL_MASK
)paren
(brace
r_if
c_cond
(paren
id|boost
)paren
(brace
multiline_comment|/* boost: 38 dB */
id|pchip-&gt;regCDSP
op_and_assign
op_complement
id|P24_CDSP_MIC20_SEL_MASK
suffix:semicolon
id|pchip-&gt;regCDSP
op_or_assign
id|P24_CDSP_MIC38_SEL_MASK
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* minimum value: 20 dB */
id|pchip-&gt;regCDSP
op_or_assign
id|P24_CDSP_MIC20_SEL_MASK
suffix:semicolon
id|pchip-&gt;regCDSP
op_and_assign
op_complement
id|P24_CDSP_MIC38_SEL_MASK
suffix:semicolon
)brace
id|vx_outb
c_func
(paren
id|chip
comma
id|CDSP
comma
id|pchip-&gt;regCDSP
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|chip-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * remap the linear value (0-8) to the actual value (0-15)&n; */
DECL|function|vx_compute_mic_level
r_static
r_int
id|vx_compute_mic_level
c_func
(paren
r_int
id|level
)paren
(brace
r_switch
c_cond
(paren
id|level
)paren
(brace
r_case
l_int|5
suffix:colon
id|level
op_assign
l_int|6
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
id|level
op_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
id|level
op_assign
l_int|11
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|level
op_assign
l_int|15
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
id|level
suffix:semicolon
)brace
multiline_comment|/*&n; * vx_set_mic_level - set mic level (on vxpocket only)&n; * @level: the mic level = 0 - 8 (max)&n; */
DECL|function|vx_set_mic_level
r_void
id|vx_set_mic_level
c_func
(paren
id|vx_core_t
op_star
id|chip
comma
r_int
id|level
)paren
(brace
r_struct
id|snd_vxpocket
op_star
id|pchip
op_assign
(paren
r_struct
id|snd_vxpocket
op_star
)paren
id|chip
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|chip-&gt;chip_status
op_amp
id|VX_STAT_IS_STALE
)paren
r_return
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|chip-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pchip-&gt;regCDSP
op_amp
id|VXP_CDSP_MIC_SEL_MASK
)paren
(brace
id|level
op_assign
id|vx_compute_mic_level
c_func
(paren
id|level
)paren
suffix:semicolon
id|vx_outb
c_func
(paren
id|chip
comma
id|MICRO
comma
id|level
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|chip-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * change the input audio source&n; */
DECL|function|vxp_change_audio_source
r_static
r_void
id|vxp_change_audio_source
c_func
(paren
id|vx_core_t
op_star
id|_chip
comma
r_int
id|src
)paren
(brace
r_struct
id|snd_vxpocket
op_star
id|chip
op_assign
(paren
r_struct
id|snd_vxpocket
op_star
)paren
id|_chip
suffix:semicolon
r_switch
c_cond
(paren
id|src
)paren
(brace
r_case
id|VX_AUDIO_SRC_DIGITAL
suffix:colon
id|chip-&gt;regCDSP
op_or_assign
id|VXP_CDSP_DATAIN_SEL_MASK
suffix:semicolon
id|vx_outb
c_func
(paren
id|chip
comma
id|CDSP
comma
id|chip-&gt;regCDSP
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VX_AUDIO_SRC_LINE
suffix:colon
id|chip-&gt;regCDSP
op_and_assign
op_complement
id|VXP_CDSP_DATAIN_SEL_MASK
suffix:semicolon
r_if
c_cond
(paren
id|_chip-&gt;type
op_eq
id|VX_TYPE_VXP440
)paren
id|chip-&gt;regCDSP
op_and_assign
op_complement
id|P24_CDSP_MICS_SEL_MASK
suffix:semicolon
r_else
id|chip-&gt;regCDSP
op_and_assign
op_complement
id|VXP_CDSP_MIC_SEL_MASK
suffix:semicolon
id|vx_outb
c_func
(paren
id|chip
comma
id|CDSP
comma
id|chip-&gt;regCDSP
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VX_AUDIO_SRC_MIC
suffix:colon
id|chip-&gt;regCDSP
op_and_assign
op_complement
id|VXP_CDSP_DATAIN_SEL_MASK
suffix:semicolon
multiline_comment|/* reset mic levels */
r_if
c_cond
(paren
id|_chip-&gt;type
op_eq
id|VX_TYPE_VXP440
)paren
(brace
id|chip-&gt;regCDSP
op_and_assign
op_complement
id|P24_CDSP_MICS_SEL_MASK
suffix:semicolon
r_if
c_cond
(paren
id|chip-&gt;mic_level
)paren
id|chip-&gt;regCDSP
op_or_assign
id|P24_CDSP_MIC38_SEL_MASK
suffix:semicolon
r_else
id|chip-&gt;regCDSP
op_or_assign
id|P24_CDSP_MIC20_SEL_MASK
suffix:semicolon
id|vx_outb
c_func
(paren
id|chip
comma
id|CDSP
comma
id|chip-&gt;regCDSP
)paren
suffix:semicolon
)brace
r_else
(brace
id|chip-&gt;regCDSP
op_or_assign
id|VXP_CDSP_MIC_SEL_MASK
suffix:semicolon
id|vx_outb
c_func
(paren
id|chip
comma
id|CDSP
comma
id|chip-&gt;regCDSP
)paren
suffix:semicolon
id|vx_outb
c_func
(paren
id|chip
comma
id|MICRO
comma
id|vx_compute_mic_level
c_func
(paren
id|chip-&gt;mic_level
)paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * change the clock source&n; * source = INTERNAL_QUARTZ or UER_SYNC&n; */
DECL|function|vxp_set_clock_source
r_static
r_void
id|vxp_set_clock_source
c_func
(paren
id|vx_core_t
op_star
id|_chip
comma
r_int
id|source
)paren
(brace
r_struct
id|snd_vxpocket
op_star
id|chip
op_assign
(paren
r_struct
id|snd_vxpocket
op_star
)paren
id|_chip
suffix:semicolon
r_if
c_cond
(paren
id|source
op_eq
id|INTERNAL_QUARTZ
)paren
id|chip-&gt;regCDSP
op_and_assign
op_complement
id|VXP_CDSP_CLOCKIN_SEL_MASK
suffix:semicolon
r_else
id|chip-&gt;regCDSP
op_or_assign
id|VXP_CDSP_CLOCKIN_SEL_MASK
suffix:semicolon
id|vx_outb
c_func
(paren
id|chip
comma
id|CDSP
comma
id|chip-&gt;regCDSP
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * reset the board&n; */
DECL|function|vxp_reset_board
r_static
r_void
id|vxp_reset_board
c_func
(paren
id|vx_core_t
op_star
id|_chip
comma
r_int
id|cold_reset
)paren
(brace
r_struct
id|snd_vxpocket
op_star
id|chip
op_assign
(paren
r_struct
id|snd_vxpocket
op_star
)paren
id|_chip
suffix:semicolon
id|chip-&gt;regCDSP
op_assign
l_int|0
suffix:semicolon
id|chip-&gt;regDIALOG
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * callbacks&n; */
multiline_comment|/* exported */
DECL|variable|snd_vxpocket_ops
r_struct
id|snd_vx_ops
id|snd_vxpocket_ops
op_assign
(brace
dot
id|in8
op_assign
id|vxp_inb
comma
dot
id|out8
op_assign
id|vxp_outb
comma
dot
id|test_and_ack
op_assign
id|vxp_test_and_ack
comma
dot
id|validate_irq
op_assign
id|vxp_validate_irq
comma
dot
id|write_codec
op_assign
id|vxp_write_codec_reg
comma
dot
id|reset_codec
op_assign
id|vxp_reset_codec
comma
dot
id|change_audio_source
op_assign
id|vxp_change_audio_source
comma
dot
id|set_clock_source
op_assign
id|vxp_set_clock_source
comma
dot
id|load_dsp
op_assign
id|vxp_load_dsp
comma
dot
id|add_controls
op_assign
id|vxp_add_mic_controls
comma
dot
id|reset_dsp
op_assign
id|vxp_reset_dsp
comma
dot
id|reset_board
op_assign
id|vxp_reset_board
comma
dot
id|dma_write
op_assign
id|vxp_dma_write
comma
dot
id|dma_read
op_assign
id|vxp_dma_read
comma
)brace
suffix:semicolon
eof
