multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *                   Uros Bizjak &lt;uros@kss-loka.si&gt;&n; *&n; *  Lowlevel routines for control of Sound Blaster cards&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/sb.h&gt;
macro_line|#include &lt;sound/initval.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jaroslav Kysela &lt;perex@suse.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;ALSA lowlevel driver for Sound Blaster cards&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|macro|BUSY_LOOPS
mdefine_line|#define BUSY_LOOPS 100000
DECL|macro|IO_DEBUG
macro_line|#undef IO_DEBUG
DECL|function|snd_sbdsp_command
r_int
id|snd_sbdsp_command
c_func
(paren
id|sb_t
op_star
id|chip
comma
r_int
r_char
id|val
)paren
(brace
r_int
id|i
suffix:semicolon
macro_line|#ifdef IO_DEBUG
id|snd_printk
c_func
(paren
l_string|&quot;command 0x%x&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|i
op_assign
id|BUSY_LOOPS
suffix:semicolon
id|i
suffix:semicolon
id|i
op_decrement
)paren
r_if
c_cond
(paren
(paren
id|inb
c_func
(paren
id|SBP
c_func
(paren
id|chip
comma
id|STATUS
)paren
)paren
op_amp
l_int|0x80
)paren
op_eq
l_int|0
)paren
(brace
id|outb
c_func
(paren
id|val
comma
id|SBP
c_func
(paren
id|chip
comma
id|COMMAND
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|snd_printd
c_func
(paren
l_string|&quot;%s [0x%lx]: timeout (0x%x)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|chip-&gt;port
comma
id|val
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_sbdsp_get_byte
r_int
id|snd_sbdsp_get_byte
c_func
(paren
id|sb_t
op_star
id|chip
)paren
(brace
r_int
id|val
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|BUSY_LOOPS
suffix:semicolon
id|i
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|inb
c_func
(paren
id|SBP
c_func
(paren
id|chip
comma
id|DATA_AVAIL
)paren
)paren
op_amp
l_int|0x80
)paren
(brace
id|val
op_assign
id|inb
c_func
(paren
id|SBP
c_func
(paren
id|chip
comma
id|READ
)paren
)paren
suffix:semicolon
macro_line|#ifdef IO_DEBUG
id|snd_printk
c_func
(paren
l_string|&quot;get_byte 0x%x&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
macro_line|#endif
r_return
id|val
suffix:semicolon
)brace
)brace
id|snd_printd
c_func
(paren
l_string|&quot;%s [0x%lx]: timeout&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|chip-&gt;port
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|snd_sbdsp_reset
r_int
id|snd_sbdsp_reset
c_func
(paren
id|sb_t
op_star
id|chip
)paren
(brace
r_int
id|i
suffix:semicolon
id|outb
c_func
(paren
l_int|1
comma
id|SBP
c_func
(paren
id|chip
comma
id|RESET
)paren
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|SBP
c_func
(paren
id|chip
comma
id|RESET
)paren
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|30
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|BUSY_LOOPS
suffix:semicolon
id|i
suffix:semicolon
id|i
op_decrement
)paren
r_if
c_cond
(paren
id|inb
c_func
(paren
id|SBP
c_func
(paren
id|chip
comma
id|DATA_AVAIL
)paren
)paren
op_amp
l_int|0x80
)paren
(brace
r_if
c_cond
(paren
id|inb
c_func
(paren
id|SBP
c_func
(paren
id|chip
comma
id|READ
)paren
)paren
op_eq
l_int|0xaa
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_break
suffix:semicolon
)brace
id|snd_printdd
c_func
(paren
l_string|&quot;%s [0x%lx] failed...&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|chip-&gt;port
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|snd_sbdsp_version
r_static
r_int
id|snd_sbdsp_version
c_func
(paren
id|sb_t
op_star
id|chip
)paren
(brace
r_int
r_int
id|result
op_assign
op_minus
id|ENODEV
suffix:semicolon
id|snd_sbdsp_command
c_func
(paren
id|chip
comma
id|SB_DSP_GET_VERSION
)paren
suffix:semicolon
id|result
op_assign
(paren
r_int
)paren
id|snd_sbdsp_get_byte
c_func
(paren
id|chip
)paren
op_lshift
l_int|8
suffix:semicolon
id|result
op_or_assign
(paren
r_int
)paren
id|snd_sbdsp_get_byte
c_func
(paren
id|chip
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|snd_sbdsp_probe
r_static
r_int
id|snd_sbdsp_probe
c_func
(paren
id|sb_t
op_star
id|chip
)paren
(brace
r_int
id|version
suffix:semicolon
r_int
id|major
comma
id|minor
suffix:semicolon
r_char
op_star
id|str
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/*&n;&t; *  initialization sequence&n;&t; */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|chip-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|snd_sbdsp_reset
c_func
(paren
id|chip
)paren
OL
l_int|0
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|chip-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|version
op_assign
id|snd_sbdsp_version
c_func
(paren
id|chip
)paren
suffix:semicolon
r_if
c_cond
(paren
id|version
OL
l_int|0
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|chip-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|chip-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
id|major
op_assign
id|version
op_rshift
l_int|8
suffix:semicolon
id|minor
op_assign
id|version
op_amp
l_int|0xff
suffix:semicolon
id|snd_printdd
c_func
(paren
l_string|&quot;SB [0x%lx]: DSP chip found, version = %i.%i&bslash;n&quot;
comma
id|chip-&gt;port
comma
id|major
comma
id|minor
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|chip-&gt;hardware
)paren
(brace
r_case
id|SB_HW_AUTO
suffix:colon
r_switch
c_cond
(paren
id|major
)paren
(brace
r_case
l_int|1
suffix:colon
id|chip-&gt;hardware
op_assign
id|SB_HW_10
suffix:semicolon
id|str
op_assign
l_string|&quot;1.0&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_if
c_cond
(paren
id|minor
)paren
(brace
id|chip-&gt;hardware
op_assign
id|SB_HW_201
suffix:semicolon
id|str
op_assign
l_string|&quot;2.01+&quot;
suffix:semicolon
)brace
r_else
(brace
id|chip-&gt;hardware
op_assign
id|SB_HW_20
suffix:semicolon
id|str
op_assign
l_string|&quot;2.0&quot;
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|chip-&gt;hardware
op_assign
id|SB_HW_PRO
suffix:semicolon
id|str
op_assign
l_string|&quot;Pro&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|chip-&gt;hardware
op_assign
id|SB_HW_16
suffix:semicolon
id|str
op_assign
l_string|&quot;16&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|snd_printk
c_func
(paren
l_string|&quot;SB [0x%lx]: unknown DSP chip version %i.%i&bslash;n&quot;
comma
id|chip-&gt;port
comma
id|major
comma
id|minor
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SB_HW_ALS100
suffix:colon
id|str
op_assign
l_string|&quot;16 (ALS-100)&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SB_HW_ALS4000
suffix:colon
id|str
op_assign
l_string|&quot;16 (ALS-4000)&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SB_HW_DT019X
suffix:colon
id|str
op_assign
l_string|&quot;(DT019X/ALS007)&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|chip-&gt;name
comma
l_string|&quot;Sound Blaster %s&quot;
comma
id|str
)paren
suffix:semicolon
id|chip-&gt;version
op_assign
(paren
id|major
op_lshift
l_int|8
)paren
op_or
id|minor
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_sbdsp_free
r_static
r_int
id|snd_sbdsp_free
c_func
(paren
id|sb_t
op_star
id|chip
)paren
(brace
r_if
c_cond
(paren
id|chip-&gt;res_port
)paren
(brace
id|release_resource
c_func
(paren
id|chip-&gt;res_port
)paren
suffix:semicolon
id|kfree_nocheck
c_func
(paren
id|chip-&gt;res_port
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|chip-&gt;irq
op_ge
l_int|0
)paren
id|free_irq
c_func
(paren
id|chip-&gt;irq
comma
(paren
r_void
op_star
)paren
id|chip
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ISA
r_if
c_cond
(paren
id|chip-&gt;dma8
op_ge
l_int|0
)paren
(brace
id|disable_dma
c_func
(paren
id|chip-&gt;dma8
)paren
suffix:semicolon
id|free_dma
c_func
(paren
id|chip-&gt;dma8
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|chip-&gt;dma16
op_ge
l_int|0
op_logical_and
id|chip-&gt;dma16
op_ne
id|chip-&gt;dma8
)paren
(brace
id|disable_dma
c_func
(paren
id|chip-&gt;dma16
)paren
suffix:semicolon
id|free_dma
c_func
(paren
id|chip-&gt;dma16
)paren
suffix:semicolon
)brace
macro_line|#endif
id|kfree
c_func
(paren
id|chip
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_sbdsp_dev_free
r_static
r_int
id|snd_sbdsp_dev_free
c_func
(paren
id|snd_device_t
op_star
id|device
)paren
(brace
id|sb_t
op_star
id|chip
op_assign
id|device-&gt;device_data
suffix:semicolon
r_return
id|snd_sbdsp_free
c_func
(paren
id|chip
)paren
suffix:semicolon
)brace
DECL|function|snd_sbdsp_create
r_int
id|snd_sbdsp_create
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_int
r_int
id|port
comma
r_int
id|irq
comma
id|irqreturn_t
(paren
op_star
id|irq_handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
id|dma8
comma
r_int
id|dma16
comma
r_int
r_int
id|hardware
comma
id|sb_t
op_star
op_star
id|r_chip
)paren
(brace
id|sb_t
op_star
id|chip
suffix:semicolon
r_int
id|err
suffix:semicolon
r_static
id|snd_device_ops_t
id|ops
op_assign
(brace
dot
id|dev_free
op_assign
id|snd_sbdsp_dev_free
comma
)brace
suffix:semicolon
id|snd_assert
c_func
(paren
id|r_chip
op_ne
l_int|NULL
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
op_star
id|r_chip
op_assign
l_int|NULL
suffix:semicolon
id|chip
op_assign
id|kcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|chip
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chip
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|chip-&gt;reg_lock
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|chip-&gt;open_lock
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|chip-&gt;midi_input_lock
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|chip-&gt;mixer_lock
)paren
suffix:semicolon
id|chip-&gt;irq
op_assign
op_minus
l_int|1
suffix:semicolon
id|chip-&gt;dma8
op_assign
op_minus
l_int|1
suffix:semicolon
id|chip-&gt;dma16
op_assign
op_minus
l_int|1
suffix:semicolon
id|chip-&gt;port
op_assign
id|port
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|irq
comma
id|irq_handler
comma
id|hardware
op_eq
id|SB_HW_ALS4000
ques
c_cond
id|SA_INTERRUPT
op_or
id|SA_SHIRQ
suffix:colon
id|SA_INTERRUPT
comma
l_string|&quot;SoundBlaster&quot;
comma
(paren
r_void
op_star
)paren
id|chip
)paren
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sb: can&squot;t grab irq %d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|snd_sbdsp_free
c_func
(paren
id|chip
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|chip-&gt;irq
op_assign
id|irq
suffix:semicolon
r_if
c_cond
(paren
id|hardware
op_eq
id|SB_HW_ALS4000
)paren
r_goto
id|__skip_allocation
suffix:semicolon
r_if
c_cond
(paren
(paren
id|chip-&gt;res_port
op_assign
id|request_region
c_func
(paren
id|port
comma
l_int|16
comma
l_string|&quot;SoundBlaster&quot;
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sb: can&squot;t grab port 0x%lx&bslash;n&quot;
comma
id|port
)paren
suffix:semicolon
id|snd_sbdsp_free
c_func
(paren
id|chip
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ISA
r_if
c_cond
(paren
id|dma8
op_ge
l_int|0
op_logical_and
id|request_dma
c_func
(paren
id|dma8
comma
l_string|&quot;SoundBlaster - 8bit&quot;
)paren
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sb: can&squot;t grab DMA8 %d&bslash;n&quot;
comma
id|dma8
)paren
suffix:semicolon
id|snd_sbdsp_free
c_func
(paren
id|chip
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|chip-&gt;dma8
op_assign
id|dma8
suffix:semicolon
r_if
c_cond
(paren
id|dma16
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|hardware
op_ne
id|SB_HW_ALS100
op_logical_and
(paren
id|dma16
template_param
l_int|7
)paren
)paren
(brace
multiline_comment|/* no duplex */
id|dma16
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|request_dma
c_func
(paren
id|dma16
comma
l_string|&quot;SoundBlaster - 16bit&quot;
)paren
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sb: can&squot;t grab DMA16 %d&bslash;n&quot;
comma
id|dma16
)paren
suffix:semicolon
id|snd_sbdsp_free
c_func
(paren
id|chip
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
)brace
id|chip-&gt;dma16
op_assign
id|dma16
suffix:semicolon
macro_line|#endif
id|__skip_allocation
suffix:colon
id|chip-&gt;card
op_assign
id|card
suffix:semicolon
id|chip-&gt;hardware
op_assign
id|hardware
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_sbdsp_probe
c_func
(paren
id|chip
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_sbdsp_free
c_func
(paren
id|chip
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_device_new
c_func
(paren
id|card
comma
id|SNDRV_DEV_LOWLEVEL
comma
id|chip
comma
op_amp
id|ops
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_sbdsp_free
c_func
(paren
id|chip
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
op_star
id|r_chip
op_assign
id|chip
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|snd_sbdsp_command
id|EXPORT_SYMBOL
c_func
(paren
id|snd_sbdsp_command
)paren
suffix:semicolon
DECL|variable|snd_sbdsp_get_byte
id|EXPORT_SYMBOL
c_func
(paren
id|snd_sbdsp_get_byte
)paren
suffix:semicolon
DECL|variable|snd_sbdsp_reset
id|EXPORT_SYMBOL
c_func
(paren
id|snd_sbdsp_reset
)paren
suffix:semicolon
DECL|variable|snd_sbdsp_create
id|EXPORT_SYMBOL
c_func
(paren
id|snd_sbdsp_create
)paren
suffix:semicolon
multiline_comment|/* sb_mixer.c */
DECL|variable|snd_sbmixer_write
id|EXPORT_SYMBOL
c_func
(paren
id|snd_sbmixer_write
)paren
suffix:semicolon
DECL|variable|snd_sbmixer_read
id|EXPORT_SYMBOL
c_func
(paren
id|snd_sbmixer_read
)paren
suffix:semicolon
DECL|variable|snd_sbmixer_new
id|EXPORT_SYMBOL
c_func
(paren
id|snd_sbmixer_new
)paren
suffix:semicolon
DECL|variable|snd_sbmixer_add_ctl
id|EXPORT_SYMBOL
c_func
(paren
id|snd_sbmixer_add_ctl
)paren
suffix:semicolon
multiline_comment|/*&n; *  INIT part&n; */
DECL|function|alsa_sb_common_init
r_static
r_int
id|__init
id|alsa_sb_common_init
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alsa_sb_common_exit
r_static
r_void
id|__exit
id|alsa_sb_common_exit
c_func
(paren
r_void
)paren
(brace
)brace
id|module_init
c_func
(paren
id|alsa_sb_common_init
)paren
id|module_exit
c_func
(paren
id|alsa_sb_common_exit
)paren
eof
