multiline_comment|/*********************************************************************&n; *&n; * msnd.c - Driver Base&n; *&n; * Turtle Beach MultiSound Sound Card Driver for Linux&n; *&n; * Copyright (C) 1998 Andrew Veliath&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * $Id: msnd.c,v 1.17 1999/03/21 16:50:09 andrewtv Exp $&n; *&n; ********************************************************************/
macro_line|#include &lt;linux/version.h&gt;
macro_line|#if LINUX_VERSION_CODE &lt; 0x020101
DECL|macro|LINUX20
macro_line|#  define LINUX20
macro_line|#endif
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#ifdef LINUX20
macro_line|#  include &lt;linux/major.h&gt;
macro_line|#  include &lt;linux/fs.h&gt;
macro_line|#  include &lt;linux/sound.h&gt;
macro_line|#  include &lt;asm/segment.h&gt;
macro_line|#  include &quot;sound_config.h&quot;
macro_line|#else
macro_line|#  include &lt;linux/init.h&gt;
macro_line|#  include &lt;asm/io.h&gt;
macro_line|#  include &lt;asm/uaccess.h&gt;
macro_line|#  include &lt;linux/spinlock.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;msnd.h&quot;
DECL|macro|LOGNAME
mdefine_line|#define LOGNAME&t;&t;&t;&quot;msnd&quot;
DECL|macro|MSND_MAX_DEVS
mdefine_line|#define MSND_MAX_DEVS&t;&t;4
DECL|variable|devs
r_static
id|multisound_dev_t
op_star
id|devs
(braket
id|MSND_MAX_DEVS
)braket
suffix:semicolon
DECL|variable|num_devs
r_static
r_int
id|num_devs
suffix:semicolon
DECL|function|msnd_register
r_int
id|__init
id|msnd_register
c_func
(paren
id|multisound_dev_t
op_star
id|dev
)paren
(brace
r_int
id|i
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
id|MSND_MAX_DEVS
suffix:semicolon
op_increment
id|i
)paren
r_if
c_cond
(paren
id|devs
(braket
id|i
)braket
op_eq
l_int|NULL
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|MSND_MAX_DEVS
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|devs
(braket
id|i
)braket
op_assign
id|dev
suffix:semicolon
op_increment
id|num_devs
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|msnd_unregister
r_void
id|msnd_unregister
c_func
(paren
id|multisound_dev_t
op_star
id|dev
)paren
(brace
r_int
id|i
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
id|MSND_MAX_DEVS
suffix:semicolon
op_increment
id|i
)paren
r_if
c_cond
(paren
id|devs
(braket
id|i
)braket
op_eq
id|dev
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|MSND_MAX_DEVS
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|LOGNAME
l_string|&quot;: Unregistering unknown device&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|devs
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
op_decrement
id|num_devs
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|function|msnd_get_num_devs
r_int
id|msnd_get_num_devs
c_func
(paren
r_void
)paren
(brace
r_return
id|num_devs
suffix:semicolon
)brace
DECL|function|msnd_get_dev
id|multisound_dev_t
op_star
id|msnd_get_dev
c_func
(paren
r_int
id|j
)paren
(brace
r_int
id|i
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
id|MSND_MAX_DEVS
op_logical_and
id|j
suffix:semicolon
op_increment
id|i
)paren
r_if
c_cond
(paren
id|devs
(braket
id|i
)braket
op_ne
l_int|NULL
)paren
op_decrement
id|j
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|MSND_MAX_DEVS
op_logical_or
id|j
op_ne
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|devs
(braket
id|i
)braket
suffix:semicolon
)brace
DECL|function|msnd_init_queue
r_void
id|msnd_init_queue
c_func
(paren
r_int
r_int
id|base
comma
r_int
id|start
comma
r_int
id|size
)paren
(brace
id|isa_writew
c_func
(paren
id|PCTODSP_BASED
c_func
(paren
id|start
)paren
comma
id|base
op_plus
id|JQS_wStart
)paren
suffix:semicolon
id|isa_writew
c_func
(paren
id|PCTODSP_OFFSET
c_func
(paren
id|size
)paren
op_minus
l_int|1
comma
id|base
op_plus
id|JQS_wSize
)paren
suffix:semicolon
id|isa_writew
c_func
(paren
l_int|0
comma
id|base
op_plus
id|JQS_wHead
)paren
suffix:semicolon
id|isa_writew
c_func
(paren
l_int|0
comma
id|base
op_plus
id|JQS_wTail
)paren
suffix:semicolon
)brace
DECL|function|msnd_fifo_init
r_void
id|msnd_fifo_init
c_func
(paren
id|msnd_fifo
op_star
id|f
)paren
(brace
id|f-&gt;data
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|msnd_fifo_free
r_void
id|msnd_fifo_free
c_func
(paren
id|msnd_fifo
op_star
id|f
)paren
(brace
r_if
c_cond
(paren
id|f-&gt;data
)paren
(brace
id|vfree
c_func
(paren
id|f-&gt;data
)paren
suffix:semicolon
id|f-&gt;data
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|function|msnd_fifo_alloc
r_int
id|msnd_fifo_alloc
c_func
(paren
id|msnd_fifo
op_star
id|f
comma
r_int
id|n
)paren
(brace
id|msnd_fifo_free
c_func
(paren
id|f
)paren
suffix:semicolon
id|f-&gt;data
op_assign
(paren
r_char
op_star
)paren
id|vmalloc
c_func
(paren
id|n
)paren
suffix:semicolon
id|f-&gt;n
op_assign
id|n
suffix:semicolon
id|f-&gt;tail
op_assign
l_int|0
suffix:semicolon
id|f-&gt;head
op_assign
l_int|0
suffix:semicolon
id|f-&gt;len
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|f-&gt;data
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|msnd_fifo_make_empty
r_void
id|msnd_fifo_make_empty
c_func
(paren
id|msnd_fifo
op_star
id|f
)paren
(brace
id|f-&gt;len
op_assign
id|f-&gt;tail
op_assign
id|f-&gt;head
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|msnd_fifo_write
r_int
id|msnd_fifo_write
c_func
(paren
id|msnd_fifo
op_star
id|f
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|user
)paren
(brace
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|f-&gt;len
op_eq
id|f-&gt;n
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|count
OL
id|len
)paren
op_logical_and
(paren
id|f-&gt;len
op_ne
id|f-&gt;n
)paren
)paren
(brace
r_int
id|nwritten
suffix:semicolon
r_if
c_cond
(paren
id|f-&gt;head
op_le
id|f-&gt;tail
)paren
(brace
id|nwritten
op_assign
id|len
op_minus
id|count
suffix:semicolon
r_if
c_cond
(paren
id|nwritten
OG
id|f-&gt;n
op_minus
id|f-&gt;tail
)paren
id|nwritten
op_assign
id|f-&gt;n
op_minus
id|f-&gt;tail
suffix:semicolon
)brace
r_else
(brace
id|nwritten
op_assign
id|f-&gt;head
op_minus
id|f-&gt;tail
suffix:semicolon
r_if
c_cond
(paren
id|nwritten
OG
id|len
op_minus
id|count
)paren
id|nwritten
op_assign
id|len
op_minus
id|count
suffix:semicolon
)brace
r_if
c_cond
(paren
id|user
)paren
(brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|f-&gt;data
op_plus
id|f-&gt;tail
comma
id|buf
comma
id|nwritten
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
id|isa_memcpy_fromio
c_func
(paren
id|f-&gt;data
op_plus
id|f-&gt;tail
comma
(paren
r_int
r_int
)paren
id|buf
comma
id|nwritten
)paren
suffix:semicolon
id|count
op_add_assign
id|nwritten
suffix:semicolon
id|buf
op_add_assign
id|nwritten
suffix:semicolon
id|f-&gt;len
op_add_assign
id|nwritten
suffix:semicolon
id|f-&gt;tail
op_add_assign
id|nwritten
suffix:semicolon
id|f-&gt;tail
op_mod_assign
id|f-&gt;n
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|function|msnd_fifo_read
r_int
id|msnd_fifo_read
c_func
(paren
id|msnd_fifo
op_star
id|f
comma
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|user
)paren
(brace
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|f-&gt;len
op_eq
l_int|0
)paren
r_return
id|f-&gt;len
suffix:semicolon
r_while
c_loop
(paren
(paren
id|count
OL
id|len
)paren
op_logical_and
(paren
id|f-&gt;len
OG
l_int|0
)paren
)paren
(brace
r_int
id|nread
suffix:semicolon
r_if
c_cond
(paren
id|f-&gt;tail
op_le
id|f-&gt;head
)paren
(brace
id|nread
op_assign
id|len
op_minus
id|count
suffix:semicolon
r_if
c_cond
(paren
id|nread
OG
id|f-&gt;n
op_minus
id|f-&gt;head
)paren
id|nread
op_assign
id|f-&gt;n
op_minus
id|f-&gt;head
suffix:semicolon
)brace
r_else
(brace
id|nread
op_assign
id|f-&gt;tail
op_minus
id|f-&gt;head
suffix:semicolon
r_if
c_cond
(paren
id|nread
OG
id|len
op_minus
id|count
)paren
id|nread
op_assign
id|len
op_minus
id|count
suffix:semicolon
)brace
r_if
c_cond
(paren
id|user
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|f-&gt;data
op_plus
id|f-&gt;head
comma
id|nread
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
id|isa_memcpy_toio
c_func
(paren
(paren
r_int
r_int
)paren
id|buf
comma
id|f-&gt;data
op_plus
id|f-&gt;head
comma
id|nread
)paren
suffix:semicolon
id|count
op_add_assign
id|nread
suffix:semicolon
id|buf
op_add_assign
id|nread
suffix:semicolon
id|f-&gt;len
op_sub_assign
id|nread
suffix:semicolon
id|f-&gt;head
op_add_assign
id|nread
suffix:semicolon
id|f-&gt;head
op_mod_assign
id|f-&gt;n
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|function|msnd_wait_TXDE
r_int
id|msnd_wait_TXDE
c_func
(paren
id|multisound_dev_t
op_star
id|dev
)paren
(brace
r_register
r_int
r_int
id|io
op_assign
id|dev-&gt;io
suffix:semicolon
r_register
r_int
id|timeout
op_assign
l_int|1000
suffix:semicolon
r_while
c_loop
(paren
id|timeout
op_decrement
OG
l_int|0
)paren
r_if
c_cond
(paren
id|inb
c_func
(paren
id|io
op_plus
id|HP_ISR
)paren
op_amp
id|HPISR_TXDE
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
DECL|function|msnd_wait_HC0
r_int
id|msnd_wait_HC0
c_func
(paren
id|multisound_dev_t
op_star
id|dev
)paren
(brace
r_register
r_int
r_int
id|io
op_assign
id|dev-&gt;io
suffix:semicolon
r_register
r_int
id|timeout
op_assign
l_int|1000
suffix:semicolon
r_while
c_loop
(paren
id|timeout
op_decrement
OG
l_int|0
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|inb
c_func
(paren
id|io
op_plus
id|HP_CVR
)paren
op_amp
id|HPCVR_HC
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
DECL|function|msnd_send_dsp_cmd
r_int
id|msnd_send_dsp_cmd
c_func
(paren
id|multisound_dev_t
op_star
id|dev
comma
id|BYTE
id|cmd
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dev-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|msnd_wait_HC0
c_func
(paren
id|dev
)paren
op_eq
l_int|0
)paren
(brace
id|outb
c_func
(paren
id|cmd
comma
id|dev-&gt;io
op_plus
id|HP_CVR
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dev-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dev-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
id|LOGNAME
l_string|&quot;: Send DSP command timeout&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
DECL|function|msnd_send_word
r_int
id|msnd_send_word
c_func
(paren
id|multisound_dev_t
op_star
id|dev
comma
r_int
r_char
id|high
comma
r_int
r_char
id|mid
comma
r_int
r_char
id|low
)paren
(brace
r_register
r_int
r_int
id|io
op_assign
id|dev-&gt;io
suffix:semicolon
r_if
c_cond
(paren
id|msnd_wait_TXDE
c_func
(paren
id|dev
)paren
op_eq
l_int|0
)paren
(brace
id|outb
c_func
(paren
id|high
comma
id|io
op_plus
id|HP_TXH
)paren
suffix:semicolon
id|outb
c_func
(paren
id|mid
comma
id|io
op_plus
id|HP_TXM
)paren
suffix:semicolon
id|outb
c_func
(paren
id|low
comma
id|io
op_plus
id|HP_TXL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_DEBUG
id|LOGNAME
l_string|&quot;: Send host word timeout&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
DECL|function|msnd_upload_host
r_int
id|msnd_upload_host
c_func
(paren
id|multisound_dev_t
op_star
id|dev
comma
r_char
op_star
id|bin
comma
r_int
id|len
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|len
op_mod
l_int|3
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|LOGNAME
l_string|&quot;: Upload host data not multiple of 3!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|len
suffix:semicolon
id|i
op_add_assign
l_int|3
)paren
r_if
c_cond
(paren
id|msnd_send_word
c_func
(paren
id|dev
comma
id|bin
(braket
id|i
)braket
comma
id|bin
(braket
id|i
op_plus
l_int|1
)braket
comma
id|bin
(braket
id|i
op_plus
l_int|2
)braket
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|inb
c_func
(paren
id|dev-&gt;io
op_plus
id|HP_RXL
)paren
suffix:semicolon
id|inb
c_func
(paren
id|dev-&gt;io
op_plus
id|HP_CVR
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|msnd_enable_irq
r_int
id|msnd_enable_irq
c_func
(paren
id|multisound_dev_t
op_star
id|dev
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;irq_ref
op_increment
)paren
r_return
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
id|LOGNAME
l_string|&quot;: Enabling IRQ&bslash;n&quot;
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dev-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|msnd_wait_TXDE
c_func
(paren
id|dev
)paren
op_eq
l_int|0
)paren
(brace
id|outb
c_func
(paren
id|inb
c_func
(paren
id|dev-&gt;io
op_plus
id|HP_ICR
)paren
op_or
id|HPICR_TREQ
comma
id|dev-&gt;io
op_plus
id|HP_ICR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;type
op_eq
id|msndClassic
)paren
id|outb
c_func
(paren
id|dev-&gt;irqid
comma
id|dev-&gt;io
op_plus
id|HP_IRQM
)paren
suffix:semicolon
id|outb
c_func
(paren
id|inb
c_func
(paren
id|dev-&gt;io
op_plus
id|HP_ICR
)paren
op_amp
op_complement
id|HPICR_TREQ
comma
id|dev-&gt;io
op_plus
id|HP_ICR
)paren
suffix:semicolon
id|outb
c_func
(paren
id|inb
c_func
(paren
id|dev-&gt;io
op_plus
id|HP_ICR
)paren
op_or
id|HPICR_RREQ
comma
id|dev-&gt;io
op_plus
id|HP_ICR
)paren
suffix:semicolon
id|enable_irq
c_func
(paren
id|dev-&gt;irq
)paren
suffix:semicolon
id|msnd_init_queue
c_func
(paren
id|dev-&gt;DSPQ
comma
id|dev-&gt;dspq_data_buff
comma
id|dev-&gt;dspq_buff_size
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dev-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dev-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
id|LOGNAME
l_string|&quot;: Enable IRQ failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
DECL|function|msnd_disable_irq
r_int
id|msnd_disable_irq
c_func
(paren
id|multisound_dev_t
op_star
id|dev
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|dev-&gt;irq_ref
OG
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;irq_ref
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
id|LOGNAME
l_string|&quot;: IRQ ref count is %d&bslash;n&quot;
comma
id|dev-&gt;irq_ref
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
id|LOGNAME
l_string|&quot;: Disabling IRQ&bslash;n&quot;
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dev-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|msnd_wait_TXDE
c_func
(paren
id|dev
)paren
op_eq
l_int|0
)paren
(brace
id|outb
c_func
(paren
id|inb
c_func
(paren
id|dev-&gt;io
op_plus
id|HP_ICR
)paren
op_amp
op_complement
id|HPICR_RREQ
comma
id|dev-&gt;io
op_plus
id|HP_ICR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;type
op_eq
id|msndClassic
)paren
id|outb
c_func
(paren
id|HPIRQ_NONE
comma
id|dev-&gt;io
op_plus
id|HP_IRQM
)paren
suffix:semicolon
id|disable_irq
c_func
(paren
id|dev-&gt;irq
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dev-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dev-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
id|LOGNAME
l_string|&quot;: Disable IRQ failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
macro_line|#ifndef LINUX20
DECL|variable|msnd_register
id|EXPORT_SYMBOL
c_func
(paren
id|msnd_register
)paren
suffix:semicolon
DECL|variable|msnd_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|msnd_unregister
)paren
suffix:semicolon
DECL|variable|msnd_get_num_devs
id|EXPORT_SYMBOL
c_func
(paren
id|msnd_get_num_devs
)paren
suffix:semicolon
DECL|variable|msnd_get_dev
id|EXPORT_SYMBOL
c_func
(paren
id|msnd_get_dev
)paren
suffix:semicolon
DECL|variable|msnd_init_queue
id|EXPORT_SYMBOL
c_func
(paren
id|msnd_init_queue
)paren
suffix:semicolon
DECL|variable|msnd_fifo_init
id|EXPORT_SYMBOL
c_func
(paren
id|msnd_fifo_init
)paren
suffix:semicolon
DECL|variable|msnd_fifo_free
id|EXPORT_SYMBOL
c_func
(paren
id|msnd_fifo_free
)paren
suffix:semicolon
DECL|variable|msnd_fifo_alloc
id|EXPORT_SYMBOL
c_func
(paren
id|msnd_fifo_alloc
)paren
suffix:semicolon
DECL|variable|msnd_fifo_make_empty
id|EXPORT_SYMBOL
c_func
(paren
id|msnd_fifo_make_empty
)paren
suffix:semicolon
DECL|variable|msnd_fifo_write
id|EXPORT_SYMBOL
c_func
(paren
id|msnd_fifo_write
)paren
suffix:semicolon
DECL|variable|msnd_fifo_read
id|EXPORT_SYMBOL
c_func
(paren
id|msnd_fifo_read
)paren
suffix:semicolon
DECL|variable|msnd_wait_TXDE
id|EXPORT_SYMBOL
c_func
(paren
id|msnd_wait_TXDE
)paren
suffix:semicolon
DECL|variable|msnd_wait_HC0
id|EXPORT_SYMBOL
c_func
(paren
id|msnd_wait_HC0
)paren
suffix:semicolon
DECL|variable|msnd_send_dsp_cmd
id|EXPORT_SYMBOL
c_func
(paren
id|msnd_send_dsp_cmd
)paren
suffix:semicolon
DECL|variable|msnd_send_word
id|EXPORT_SYMBOL
c_func
(paren
id|msnd_send_word
)paren
suffix:semicolon
DECL|variable|msnd_upload_host
id|EXPORT_SYMBOL
c_func
(paren
id|msnd_upload_host
)paren
suffix:semicolon
DECL|variable|msnd_enable_irq
id|EXPORT_SYMBOL
c_func
(paren
id|msnd_enable_irq
)paren
suffix:semicolon
DECL|variable|msnd_disable_irq
id|EXPORT_SYMBOL
c_func
(paren
id|msnd_disable_irq
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef MODULE
id|MODULE_AUTHOR
(paren
l_string|&quot;Andrew Veliath &lt;andrewtv@usa.net&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
(paren
l_string|&quot;Turtle Beach MultiSound Driver Base&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif
eof