multiline_comment|/* $Id: teles0.c,v 2.13.6.2 2001/09/23 22:24:52 kai Exp $&n; *&n; * low level stuff for Teles Memory IO isdn cards&n; *&n; * Author       Karsten Keil&n; *              based on the teles driver from Jan den Ouden&n; * Copyright    by Karsten Keil      &lt;keil@isdn4linux.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; * Thanks to    Jan den Ouden&n; *              Fritz Elfert&n; *              Beat Doebeli&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;hisax.h&quot;
macro_line|#include &quot;isdnl1.h&quot;
macro_line|#include &quot;isac.h&quot;
macro_line|#include &quot;hscx.h&quot;
r_extern
r_const
r_char
op_star
id|CardType
(braket
)braket
suffix:semicolon
DECL|variable|teles0_revision
r_const
r_char
op_star
id|teles0_revision
op_assign
l_string|&quot;$Revision: 2.13.6.2 $&quot;
suffix:semicolon
DECL|macro|TELES_IOMEM_SIZE
mdefine_line|#define TELES_IOMEM_SIZE&t;0x400
DECL|macro|byteout
mdefine_line|#define byteout(addr,val) outb(val,addr)
DECL|macro|bytein
mdefine_line|#define bytein(addr) inb(addr)
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
id|off
)paren
(brace
r_return
id|readb
c_func
(paren
id|cs-&gt;hw.teles0.membase
op_plus
(paren
(paren
id|off
op_amp
l_int|1
)paren
ques
c_cond
l_int|0x2ff
suffix:colon
l_int|0x100
)paren
op_plus
id|off
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
id|off
comma
id|u8
id|data
)paren
(brace
id|writeb
c_func
(paren
id|data
comma
id|cs-&gt;hw.teles0.membase
op_plus
(paren
(paren
id|off
op_amp
l_int|1
)paren
ques
c_cond
l_int|0x2ff
suffix:colon
l_int|0x100
)paren
op_plus
id|off
)paren
suffix:semicolon
id|mb
c_func
(paren
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
r_int
id|i
suffix:semicolon
r_int
r_int
id|ad
op_assign
id|cs-&gt;hw.teles0.membase
op_plus
l_int|0x100
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
id|size
suffix:semicolon
id|i
op_increment
)paren
id|data
(braket
id|i
)braket
op_assign
id|readb
c_func
(paren
id|ad
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
r_int
id|i
suffix:semicolon
r_int
r_int
id|ad
op_assign
id|cs-&gt;hw.teles0.membase
op_plus
l_int|0x100
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
id|size
suffix:semicolon
id|i
op_increment
)paren
(brace
id|writeb
c_func
(paren
id|data
(braket
id|i
)braket
comma
id|ad
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
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
id|off
)paren
(brace
r_return
id|readb
c_func
(paren
id|cs-&gt;hw.teles0.membase
op_plus
(paren
id|hscx
ques
c_cond
l_int|0x1c0
suffix:colon
l_int|0x180
)paren
op_plus
(paren
(paren
id|off
op_amp
l_int|1
)paren
ques
c_cond
l_int|0x1ff
suffix:colon
l_int|0
)paren
op_plus
id|off
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
id|off
comma
id|u8
id|data
)paren
(brace
id|writeb
c_func
(paren
id|data
comma
id|cs-&gt;hw.teles0.membase
op_plus
(paren
id|hscx
ques
c_cond
l_int|0x1c0
suffix:colon
l_int|0x180
)paren
op_plus
(paren
(paren
id|off
op_amp
l_int|1
)paren
ques
c_cond
l_int|0x1ff
suffix:colon
l_int|0
)paren
op_plus
id|off
)paren
suffix:semicolon
id|mb
c_func
(paren
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
r_int
id|i
suffix:semicolon
r_int
r_int
id|ad
op_assign
id|cs-&gt;hw.teles0.membase
op_plus
(paren
id|hscx
ques
c_cond
l_int|0x1c0
suffix:colon
l_int|0x180
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
id|size
suffix:semicolon
id|i
op_increment
)paren
id|data
(braket
id|i
)braket
op_assign
id|readb
c_func
(paren
id|ad
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
r_int
id|i
suffix:semicolon
r_int
r_int
id|ad
op_assign
id|cs-&gt;hw.teles0.membase
op_plus
(paren
id|hscx
ques
c_cond
l_int|0x1c0
suffix:colon
l_int|0x180
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
id|size
suffix:semicolon
id|i
op_increment
)paren
(brace
id|writeb
c_func
(paren
id|data
(braket
id|i
)braket
comma
id|ad
)paren
suffix:semicolon
)brace
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
DECL|function|teles0_interrupt
id|teles0_interrupt
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
id|u8
id|val
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|cs-&gt;lock
)paren
suffix:semicolon
id|val
op_assign
id|hscx_read
c_func
(paren
id|cs
comma
l_int|1
comma
id|HSCX_ISTA
)paren
suffix:semicolon
id|Start_HSCX
suffix:colon
r_if
c_cond
(paren
id|val
)paren
id|hscx_int_main
c_func
(paren
id|cs
comma
id|val
)paren
suffix:semicolon
id|val
op_assign
id|isac_read
c_func
(paren
id|cs
comma
id|ISAC_ISTA
)paren
suffix:semicolon
id|Start_ISAC
suffix:colon
r_if
c_cond
(paren
id|val
)paren
id|isac_interrupt
c_func
(paren
id|cs
comma
id|val
)paren
suffix:semicolon
id|count
op_increment
suffix:semicolon
id|val
op_assign
id|hscx_read
c_func
(paren
id|cs
comma
l_int|1
comma
id|HSCX_ISTA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_logical_and
id|count
OL
l_int|5
)paren
(brace
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_HSCX
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;HSCX IntStat after IntRoutine&quot;
)paren
suffix:semicolon
r_goto
id|Start_HSCX
suffix:semicolon
)brace
id|val
op_assign
id|isac_read
c_func
(paren
id|cs
comma
id|ISAC_ISTA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_logical_and
id|count
OL
l_int|5
)paren
(brace
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_ISAC
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;ISAC IntStat after IntRoutine&quot;
)paren
suffix:semicolon
r_goto
id|Start_ISAC
suffix:semicolon
)brace
id|hscx_write
c_func
(paren
id|cs
comma
l_int|0
comma
id|HSCX_MASK
comma
l_int|0xFF
)paren
suffix:semicolon
id|hscx_write
c_func
(paren
id|cs
comma
l_int|1
comma
id|HSCX_MASK
comma
l_int|0xFF
)paren
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_MASK
comma
l_int|0xFF
)paren
suffix:semicolon
id|isac_write
c_func
(paren
id|cs
comma
id|ISAC_MASK
comma
l_int|0x0
)paren
suffix:semicolon
id|hscx_write
c_func
(paren
id|cs
comma
l_int|0
comma
id|HSCX_MASK
comma
l_int|0x0
)paren
suffix:semicolon
id|hscx_write
c_func
(paren
id|cs
comma
l_int|1
comma
id|HSCX_MASK
comma
l_int|0x0
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|cs-&gt;lock
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|teles0_release
id|teles0_release
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
r_if
c_cond
(paren
id|cs-&gt;hw.teles0.cfg_reg
)paren
id|release_region
c_func
(paren
id|cs-&gt;hw.teles0.cfg_reg
comma
l_int|8
)paren
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_int
r_char
op_star
)paren
id|cs-&gt;hw.teles0.membase
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
id|cs-&gt;hw.teles0.phymem
comma
id|TELES_IOMEM_SIZE
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|teles0_reset
id|teles0_reset
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
id|u8
id|cfval
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;hw.teles0.cfg_reg
)paren
(brace
r_switch
c_cond
(paren
id|cs-&gt;irq
)paren
(brace
r_case
l_int|2
suffix:colon
r_case
l_int|9
suffix:colon
id|cfval
op_assign
l_int|0x00
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|cfval
op_assign
l_int|0x02
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|cfval
op_assign
l_int|0x04
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|cfval
op_assign
l_int|0x06
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|10
suffix:colon
id|cfval
op_assign
l_int|0x08
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|11
suffix:colon
id|cfval
op_assign
l_int|0x0A
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|12
suffix:colon
id|cfval
op_assign
l_int|0x0C
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|15
suffix:colon
id|cfval
op_assign
l_int|0x0E
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|1
suffix:semicolon
)brace
id|cfval
op_or_assign
(paren
(paren
id|cs-&gt;hw.teles0.phymem
op_rshift
l_int|9
)paren
op_amp
l_int|0xF0
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.teles0.cfg_reg
op_plus
l_int|4
comma
id|cfval
)paren
suffix:semicolon
id|HZDELAY
c_func
(paren
id|HZ
op_div
l_int|10
op_plus
l_int|1
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.teles0.cfg_reg
op_plus
l_int|4
comma
id|cfval
op_or
l_int|1
)paren
suffix:semicolon
id|HZDELAY
c_func
(paren
id|HZ
op_div
l_int|10
op_plus
l_int|1
)paren
suffix:semicolon
)brace
id|writeb
c_func
(paren
l_int|0
comma
id|cs-&gt;hw.teles0.membase
op_plus
l_int|0x80
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|HZDELAY
c_func
(paren
id|HZ
op_div
l_int|5
op_plus
l_int|1
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|1
comma
id|cs-&gt;hw.teles0.membase
op_plus
l_int|0x80
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|HZDELAY
c_func
(paren
id|HZ
op_div
l_int|5
op_plus
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|Teles_card_msg
id|Teles_card_msg
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
DECL|variable|teles0_ops
r_static
r_struct
id|card_ops
id|teles0_ops
op_assign
(brace
dot
id|init
op_assign
id|inithscxisac
comma
dot
id|reset
op_assign
id|teles0_reset
comma
dot
id|release
op_assign
id|teles0_release
comma
dot
id|irq_func
op_assign
id|teles0_interrupt
comma
)brace
suffix:semicolon
r_int
id|__init
DECL|function|setup_teles0
id|setup_teles0
c_func
(paren
r_struct
id|IsdnCard
op_star
id|card
)paren
(brace
id|u8
id|val
suffix:semicolon
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
id|teles0_revision
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: Teles 8.0/16.0 driver Rev. %s&bslash;n&quot;
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
(paren
id|cs-&gt;typ
op_ne
id|ISDN_CTYPE_16_0
)paren
op_logical_and
(paren
id|cs-&gt;typ
op_ne
id|ISDN_CTYPE_8_0
)paren
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;typ
op_eq
id|ISDN_CTYPE_16_0
)paren
id|cs-&gt;hw.teles0.cfg_reg
op_assign
id|card-&gt;para
(braket
l_int|2
)braket
suffix:semicolon
r_else
multiline_comment|/* 8.0 */
id|cs-&gt;hw.teles0.cfg_reg
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;para
(braket
l_int|1
)braket
OL
l_int|0x10000
)paren
(brace
id|card-&gt;para
(braket
l_int|1
)braket
op_lshift_assign
l_int|4
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Teles0: membase configured DOSish, assuming 0x%lx&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|card-&gt;para
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
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
id|cs-&gt;hw.teles0.cfg_reg
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|cs-&gt;hw.teles0.cfg_reg
comma
l_int|8
comma
l_string|&quot;teles cfg&quot;
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
id|card-&gt;typ
)braket
comma
id|cs-&gt;hw.teles0.cfg_reg
comma
id|cs-&gt;hw.teles0.cfg_reg
op_plus
l_int|8
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|cs-&gt;hw.teles0.cfg_reg
)paren
(brace
r_if
c_cond
(paren
(paren
id|val
op_assign
id|bytein
c_func
(paren
id|cs-&gt;hw.teles0.cfg_reg
op_plus
l_int|0
)paren
)paren
op_ne
l_int|0x51
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Teles0: 16.0 Byte at %x is %x&bslash;n&quot;
comma
id|cs-&gt;hw.teles0.cfg_reg
op_plus
l_int|0
comma
id|val
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|cs-&gt;hw.teles0.cfg_reg
comma
l_int|8
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|val
op_assign
id|bytein
c_func
(paren
id|cs-&gt;hw.teles0.cfg_reg
op_plus
l_int|1
)paren
)paren
op_ne
l_int|0x93
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Teles0: 16.0 Byte at %x is %x&bslash;n&quot;
comma
id|cs-&gt;hw.teles0.cfg_reg
op_plus
l_int|1
comma
id|val
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|cs-&gt;hw.teles0.cfg_reg
comma
l_int|8
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|val
op_assign
id|bytein
c_func
(paren
id|cs-&gt;hw.teles0.cfg_reg
op_plus
l_int|2
)paren
suffix:semicolon
multiline_comment|/* 0x1e=without AB&n;&t;&t;&t;&t;&t;&t;&t;&t;   * 0x1f=with AB&n;&t;&t;&t;&t;&t;&t;&t;&t;   * 0x1c 16.3 ???&n;&t;&t;&t;&t;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|val
op_ne
l_int|0x1e
op_logical_and
id|val
op_ne
l_int|0x1f
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Teles0: 16.0 Byte at %x is %x&bslash;n&quot;
comma
id|cs-&gt;hw.teles0.cfg_reg
op_plus
l_int|2
comma
id|val
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|cs-&gt;hw.teles0.cfg_reg
comma
l_int|8
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* 16.0 and 8.0 designed for IOM1 */
id|test_and_set_bit
c_func
(paren
id|HW_IOM1
comma
op_amp
id|cs-&gt;HW_Flags
)paren
suffix:semicolon
id|cs-&gt;hw.teles0.phymem
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|check_mem_region
c_func
(paren
id|cs-&gt;hw.teles0.phymem
comma
id|TELES_IOMEM_SIZE
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s memory region %lx-%lx already in use&bslash;n&quot;
comma
id|CardType
(braket
id|card-&gt;typ
)braket
comma
id|cs-&gt;hw.teles0.phymem
comma
id|cs-&gt;hw.teles0.phymem
op_plus
id|TELES_IOMEM_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;hw.teles0.cfg_reg
)paren
id|release_region
c_func
(paren
id|cs-&gt;hw.teles0.cfg_reg
comma
l_int|8
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|request_mem_region
c_func
(paren
id|cs-&gt;hw.teles0.phymem
comma
id|TELES_IOMEM_SIZE
comma
l_string|&quot;teles iomem&quot;
)paren
suffix:semicolon
)brace
id|cs-&gt;hw.teles0.membase
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|cs-&gt;hw.teles0.phymem
comma
id|TELES_IOMEM_SIZE
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: %s config irq:%d mem:0x%lX cfg:0x%X&bslash;n&quot;
comma
id|CardType
(braket
id|cs-&gt;typ
)braket
comma
id|cs-&gt;irq
comma
id|cs-&gt;hw.teles0.membase
comma
id|cs-&gt;hw.teles0.cfg_reg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|teles0_reset
c_func
(paren
id|cs
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Teles0: wrong IRQ&bslash;n&quot;
)paren
suffix:semicolon
id|teles0_release
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
id|Teles_card_msg
suffix:semicolon
id|cs-&gt;card_ops
op_assign
op_amp
id|teles0_ops
suffix:semicolon
id|ISACVersion
c_func
(paren
id|cs
comma
l_string|&quot;Teles0:&quot;
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
l_string|&quot;Teles0:&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Teles0: wrong HSCX versions check IO/MEM addresses&bslash;n&quot;
)paren
suffix:semicolon
id|teles0_release
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
