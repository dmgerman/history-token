multiline_comment|/* $Id: sportster.c,v 1.14.6.2 2001/09/23 22:24:51 kai Exp $&n; *&n; * low level stuff for USR Sportster internal TA&n; *&n; * Author       Karsten Keil&n; * Copyright    by Karsten Keil      &lt;keil@isdn4linux.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; * Thanks to Christian &quot;naddy&quot; Weisgerber (3Com, US Robotics) for documentation&n; *&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;hisax.h&quot;
macro_line|#include &quot;isac.h&quot;
macro_line|#include &quot;hscx.h&quot;
macro_line|#include &quot;isdnl1.h&quot;
r_extern
r_const
r_char
op_star
id|CardType
(braket
)braket
suffix:semicolon
DECL|variable|sportster_revision
r_const
r_char
op_star
id|sportster_revision
op_assign
l_string|&quot;$Revision: 1.14.6.2 $&quot;
suffix:semicolon
DECL|macro|byteout
mdefine_line|#define byteout(addr,val) outb(val,addr)
DECL|macro|bytein
mdefine_line|#define bytein(addr) inb(addr)
DECL|macro|SPORTSTER_ISAC
mdefine_line|#define&t; SPORTSTER_ISAC&t;&t;0xC000
DECL|macro|SPORTSTER_HSCXA
mdefine_line|#define&t; SPORTSTER_HSCXA&t;0x0000
DECL|macro|SPORTSTER_HSCXB
mdefine_line|#define&t; SPORTSTER_HSCXB&t;0x4000
DECL|macro|SPORTSTER_RES_IRQ
mdefine_line|#define&t; SPORTSTER_RES_IRQ&t;0x8000
DECL|macro|SPORTSTER_RESET
mdefine_line|#define&t; SPORTSTER_RESET&t;0x80
DECL|macro|SPORTSTER_INTE
mdefine_line|#define&t; SPORTSTER_INTE&t;&t;0x40
r_static
r_inline
r_int
DECL|function|calc_off
id|calc_off
c_func
(paren
r_int
r_int
id|base
comma
r_int
r_int
id|off
)paren
(brace
r_return
id|base
op_plus
(paren
(paren
id|off
op_amp
l_int|0xfc
)paren
op_lshift
l_int|8
)paren
op_plus
(paren
(paren
id|off
op_amp
l_int|3
)paren
op_lshift
l_int|1
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|read_fifo
id|read_fifo
c_func
(paren
r_int
r_int
id|adr
comma
id|u8
op_star
id|data
comma
r_int
id|size
)paren
(brace
id|insb
c_func
(paren
id|adr
comma
id|data
comma
id|size
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|write_fifo
id|write_fifo
c_func
(paren
r_int
r_int
id|adr
comma
id|u8
op_star
id|data
comma
r_int
id|size
)paren
(brace
id|outsb
c_func
(paren
id|adr
comma
id|data
comma
id|size
)paren
suffix:semicolon
)brace
r_static
id|u8
DECL|function|isac_read
id|isac_read
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u8
id|offset
)paren
(brace
r_return
id|bytein
c_func
(paren
id|calc_off
c_func
(paren
id|cs-&gt;hw.spt.isac
comma
id|offset
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|isac_write
id|isac_write
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u8
id|offset
comma
id|u8
id|value
)paren
(brace
id|byteout
c_func
(paren
id|calc_off
c_func
(paren
id|cs-&gt;hw.spt.isac
comma
id|offset
)paren
comma
id|value
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|isac_read_fifo
id|isac_read_fifo
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u8
op_star
id|data
comma
r_int
id|size
)paren
(brace
id|read_fifo
c_func
(paren
id|cs-&gt;hw.spt.isac
comma
id|data
comma
id|size
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|isac_write_fifo
id|isac_write_fifo
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u8
op_star
id|data
comma
r_int
id|size
)paren
(brace
id|write_fifo
c_func
(paren
id|cs-&gt;hw.spt.isac
comma
id|data
comma
id|size
)paren
suffix:semicolon
)brace
DECL|variable|isac_ops
r_static
r_struct
id|dc_hw_ops
id|isac_ops
op_assign
(brace
dot
id|read_reg
op_assign
id|isac_read
comma
dot
id|write_reg
op_assign
id|isac_write
comma
dot
id|read_fifo
op_assign
id|isac_read_fifo
comma
dot
id|write_fifo
op_assign
id|isac_write_fifo
comma
)brace
suffix:semicolon
r_static
id|u8
DECL|function|hscx_read
id|hscx_read
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|hscx
comma
id|u8
id|offset
)paren
(brace
r_return
id|bytein
c_func
(paren
id|calc_off
c_func
(paren
id|cs-&gt;hw.spt.hscx
(braket
id|hscx
)braket
comma
id|offset
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|hscx_write
id|hscx_write
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|hscx
comma
id|u8
id|offset
comma
id|u8
id|value
)paren
(brace
id|byteout
c_func
(paren
id|calc_off
c_func
(paren
id|cs-&gt;hw.spt.hscx
(braket
id|hscx
)braket
comma
id|offset
)paren
comma
id|value
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|hscx_read_fifo
id|hscx_read_fifo
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|hscx
comma
id|u8
op_star
id|data
comma
r_int
id|size
)paren
(brace
id|read_fifo
c_func
(paren
id|cs-&gt;hw.spt.hscx
(braket
id|hscx
)braket
comma
id|data
comma
id|size
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|hscx_write_fifo
id|hscx_write_fifo
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|hscx
comma
id|u8
op_star
id|data
comma
r_int
id|size
)paren
(brace
id|write_fifo
c_func
(paren
id|cs-&gt;hw.spt.hscx
(braket
id|hscx
)braket
comma
id|data
comma
id|size
)paren
suffix:semicolon
)brace
DECL|variable|hscx_ops
r_static
r_struct
id|bc_hw_ops
id|hscx_ops
op_assign
(brace
dot
id|read_reg
op_assign
id|hscx_read
comma
dot
id|write_reg
op_assign
id|hscx_write
comma
dot
id|read_fifo
op_assign
id|hscx_read_fifo
comma
dot
id|write_fifo
op_assign
id|hscx_write_fifo
comma
)brace
suffix:semicolon
r_static
r_void
DECL|function|sportster_interrupt
id|sportster_interrupt
c_func
(paren
r_int
id|intno
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|IsdnCardState
op_star
id|cs
op_assign
id|dev_id
suffix:semicolon
id|hscxisac_irq
c_func
(paren
id|intno
comma
id|dev_id
comma
id|regs
)paren
suffix:semicolon
id|bytein
c_func
(paren
id|cs-&gt;hw.spt.cfg_reg
op_plus
id|SPORTSTER_RES_IRQ
op_plus
l_int|1
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|sportster_release
id|sportster_release
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
r_int
id|i
comma
id|adr
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.spt.cfg_reg
op_plus
id|SPORTSTER_RES_IRQ
comma
l_int|0
)paren
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
l_int|64
suffix:semicolon
id|i
op_increment
)paren
(brace
id|adr
op_assign
id|cs-&gt;hw.spt.cfg_reg
op_plus
id|i
op_star
l_int|1024
suffix:semicolon
id|release_region
c_func
(paren
id|adr
comma
l_int|8
)paren
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|sportster_reset
id|sportster_reset
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
id|cs-&gt;hw.spt.res_irq
op_or_assign
id|SPORTSTER_RESET
suffix:semicolon
multiline_comment|/* Reset On */
id|byteout
c_func
(paren
id|cs-&gt;hw.spt.cfg_reg
op_plus
id|SPORTSTER_RES_IRQ
comma
id|cs-&gt;hw.spt.res_irq
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
(paren
l_int|10
op_star
id|HZ
)paren
op_div
l_int|1000
)paren
suffix:semicolon
id|cs-&gt;hw.spt.res_irq
op_and_assign
op_complement
id|SPORTSTER_RESET
suffix:semicolon
multiline_comment|/* Reset Off */
id|byteout
c_func
(paren
id|cs-&gt;hw.spt.cfg_reg
op_plus
id|SPORTSTER_RES_IRQ
comma
id|cs-&gt;hw.spt.res_irq
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
(paren
l_int|10
op_star
id|HZ
)paren
op_div
l_int|1000
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|Sportster_card_msg
id|Sportster_card_msg
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|mt
comma
r_void
op_star
id|arg
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|sportster_init
id|sportster_init
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
id|inithscxisac
c_func
(paren
id|cs
)paren
suffix:semicolon
id|cs-&gt;hw.spt.res_irq
op_or_assign
id|SPORTSTER_INTE
suffix:semicolon
multiline_comment|/* IRQ On */
id|byteout
c_func
(paren
id|cs-&gt;hw.spt.cfg_reg
op_plus
id|SPORTSTER_RES_IRQ
comma
id|cs-&gt;hw.spt.res_irq
)paren
suffix:semicolon
)brace
DECL|variable|sportster_ops
r_static
r_struct
id|card_ops
id|sportster_ops
op_assign
(brace
dot
id|init
op_assign
id|sportster_init
comma
dot
id|reset
op_assign
id|sportster_reset
comma
dot
id|release
op_assign
id|sportster_release
comma
dot
id|irq_func
op_assign
id|sportster_interrupt
comma
)brace
suffix:semicolon
r_static
r_int
id|__init
DECL|function|get_io_range
id|get_io_range
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
r_int
id|i
comma
id|j
comma
id|adr
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
l_int|64
suffix:semicolon
id|i
op_increment
)paren
(brace
id|adr
op_assign
id|cs-&gt;hw.spt.cfg_reg
op_plus
id|i
op_star
l_int|1024
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|adr
comma
l_int|8
comma
l_string|&quot;sportster&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s config port %x-%x already in use&bslash;n&quot;
comma
id|CardType
(braket
id|cs-&gt;typ
)braket
comma
id|adr
comma
id|adr
op_plus
l_int|8
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|i
op_eq
l_int|64
)paren
r_return
l_int|1
suffix:semicolon
r_else
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|i
suffix:semicolon
id|j
op_increment
)paren
(brace
id|adr
op_assign
id|cs-&gt;hw.spt.cfg_reg
op_plus
id|j
op_star
l_int|1024
suffix:semicolon
id|release_region
c_func
(paren
id|adr
comma
l_int|8
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_int
id|__init
DECL|function|setup_sportster
id|setup_sportster
c_func
(paren
r_struct
id|IsdnCard
op_star
id|card
)paren
(brace
r_struct
id|IsdnCardState
op_star
id|cs
op_assign
id|card-&gt;cs
suffix:semicolon
r_char
id|tmp
(braket
l_int|64
)braket
suffix:semicolon
id|strcpy
c_func
(paren
id|tmp
comma
id|sportster_revision
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: USR Sportster driver Rev. %s&bslash;n&quot;
comma
id|HiSax_getrev
c_func
(paren
id|tmp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;typ
op_ne
id|ISDN_CTYPE_SPORTSTER
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
id|cs-&gt;hw.spt.cfg_reg
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
suffix:semicolon
id|cs-&gt;irq
op_assign
id|card-&gt;para
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|get_io_range
c_func
(paren
id|cs
)paren
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
id|cs-&gt;hw.spt.isac
op_assign
id|cs-&gt;hw.spt.cfg_reg
op_plus
id|SPORTSTER_ISAC
suffix:semicolon
id|cs-&gt;hw.spt.hscx
(braket
l_int|0
)braket
op_assign
id|cs-&gt;hw.spt.cfg_reg
op_plus
id|SPORTSTER_HSCXA
suffix:semicolon
id|cs-&gt;hw.spt.hscx
(braket
l_int|1
)braket
op_assign
id|cs-&gt;hw.spt.cfg_reg
op_plus
id|SPORTSTER_HSCXB
suffix:semicolon
r_switch
c_cond
(paren
id|cs-&gt;irq
)paren
(brace
r_case
l_int|5
suffix:colon
id|cs-&gt;hw.spt.res_irq
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
id|cs-&gt;hw.spt.res_irq
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|10
suffix:colon
id|cs-&gt;hw.spt.res_irq
op_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|11
suffix:colon
id|cs-&gt;hw.spt.res_irq
op_assign
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|12
suffix:colon
id|cs-&gt;hw.spt.res_irq
op_assign
l_int|5
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|14
suffix:colon
id|cs-&gt;hw.spt.res_irq
op_assign
l_int|6
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|15
suffix:colon
id|cs-&gt;hw.spt.res_irq
op_assign
l_int|7
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|sportster_release
c_func
(paren
id|cs
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Sportster: wrong IRQ&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|sportster_reset
c_func
(paren
id|cs
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: %s config irq:%d cfg:0x%X&bslash;n&quot;
comma
id|CardType
(braket
id|cs-&gt;typ
)braket
comma
id|cs-&gt;irq
comma
id|cs-&gt;hw.spt.cfg_reg
)paren
suffix:semicolon
id|cs-&gt;dc_hw_ops
op_assign
op_amp
id|isac_ops
suffix:semicolon
id|cs-&gt;bc_hw_ops
op_assign
op_amp
id|hscx_ops
suffix:semicolon
id|cs-&gt;cardmsg
op_assign
op_amp
id|Sportster_card_msg
suffix:semicolon
id|cs-&gt;card_ops
op_assign
op_amp
id|sportster_ops
suffix:semicolon
id|ISACVersion
c_func
(paren
id|cs
comma
l_string|&quot;Sportster:&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|HscxVersion
c_func
(paren
id|cs
comma
l_string|&quot;Sportster:&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Sportster: wrong HSCX versions check IO address&bslash;n&quot;
)paren
suffix:semicolon
id|sportster_release
c_func
(paren
id|cs
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
eof
