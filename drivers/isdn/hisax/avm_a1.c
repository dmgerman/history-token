multiline_comment|/* $Id: avm_a1.c,v 2.13.6.2 2001/09/23 22:24:46 kai Exp $&n; *&n; * low level stuff for AVM A1 (Fritz) isdn cards&n; *&n; * Author       Karsten Keil&n; * Copyright    by Karsten Keil      &lt;keil@isdn4linux.de&gt;&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
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
DECL|variable|avm_revision
r_static
r_const
r_char
op_star
id|avm_revision
op_assign
l_string|&quot;$Revision: 2.13.6.2 $&quot;
suffix:semicolon
DECL|macro|AVM_A1_STAT_ISAC
mdefine_line|#define&t; AVM_A1_STAT_ISAC&t;0x01
DECL|macro|AVM_A1_STAT_HSCX
mdefine_line|#define&t; AVM_A1_STAT_HSCX&t;0x02
DECL|macro|AVM_A1_STAT_TIMER
mdefine_line|#define&t; AVM_A1_STAT_TIMER&t;0x04
DECL|macro|byteout
mdefine_line|#define byteout(addr,val) outb(val,addr)
DECL|macro|bytein
mdefine_line|#define bytein(addr) inb(addr)
r_static
r_inline
id|u8
DECL|function|readreg
id|readreg
c_func
(paren
r_int
r_int
id|adr
comma
id|u8
id|off
)paren
(brace
r_return
(paren
id|bytein
c_func
(paren
id|adr
op_plus
id|off
)paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|writereg
id|writereg
c_func
(paren
r_int
r_int
id|adr
comma
id|u8
id|off
comma
id|u8
id|data
)paren
(brace
id|byteout
c_func
(paren
id|adr
op_plus
id|off
comma
id|data
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
id|readreg
c_func
(paren
id|cs-&gt;hw.avm.isac
comma
id|offset
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
id|writereg
c_func
(paren
id|cs-&gt;hw.avm.isac
comma
id|offset
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
id|cs-&gt;hw.avm.isacfifo
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
id|cs-&gt;hw.avm.isacfifo
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
(paren
id|readreg
c_func
(paren
id|cs-&gt;hw.avm.hscx
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
id|writereg
c_func
(paren
id|cs-&gt;hw.avm.hscx
(braket
id|hscx
)braket
comma
id|offset
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
id|cs-&gt;hw.avm.hscxfifo
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
id|cs-&gt;hw.avm.hscxfifo
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
DECL|function|avm_a1_interrupt
id|avm_a1_interrupt
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
comma
id|sval
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|cs-&gt;lock
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
(paren
id|sval
op_assign
id|bytein
c_func
(paren
id|cs-&gt;hw.avm.cfg_reg
)paren
)paren
op_amp
l_int|0xf
)paren
op_ne
l_int|0x7
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|sval
op_amp
id|AVM_A1_STAT_TIMER
)paren
)paren
(brace
id|byteout
c_func
(paren
id|cs-&gt;hw.avm.cfg_reg
comma
l_int|0x1E
)paren
suffix:semicolon
id|sval
op_assign
id|bytein
c_func
(paren
id|cs-&gt;hw.avm.cfg_reg
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_INTSTAT
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;avm IntStatus %x&quot;
comma
id|sval
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sval
op_amp
id|AVM_A1_STAT_HSCX
)paren
)paren
(brace
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
)paren
id|hscx_int_main
c_func
(paren
id|cs
comma
id|val
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|sval
op_amp
id|AVM_A1_STAT_ISAC
)paren
)paren
(brace
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
)paren
id|isac_interrupt
c_func
(paren
id|cs
comma
id|val
)paren
suffix:semicolon
)brace
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
r_inline
r_static
r_void
DECL|function|release_ioregs
id|release_ioregs
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|mask
)paren
(brace
id|release_region
c_func
(paren
id|cs-&gt;hw.avm.cfg_reg
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mask
op_amp
l_int|1
)paren
id|release_region
c_func
(paren
id|cs-&gt;hw.avm.isac
op_plus
l_int|32
comma
l_int|32
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mask
op_amp
l_int|2
)paren
id|release_region
c_func
(paren
id|cs-&gt;hw.avm.isacfifo
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mask
op_amp
l_int|4
)paren
id|release_region
c_func
(paren
id|cs-&gt;hw.avm.hscx
(braket
l_int|0
)braket
op_plus
l_int|32
comma
l_int|32
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mask
op_amp
l_int|8
)paren
id|release_region
c_func
(paren
id|cs-&gt;hw.avm.hscxfifo
(braket
l_int|0
)braket
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mask
op_amp
l_int|0x10
)paren
id|release_region
c_func
(paren
id|cs-&gt;hw.avm.hscx
(braket
l_int|1
)braket
op_plus
l_int|32
comma
l_int|32
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mask
op_amp
l_int|0x20
)paren
id|release_region
c_func
(paren
id|cs-&gt;hw.avm.hscxfifo
(braket
l_int|1
)braket
comma
l_int|1
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|AVM_card_msg
id|AVM_card_msg
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
r_switch
c_cond
(paren
id|mt
)paren
(brace
r_case
id|CARD_RESET
suffix:colon
r_return
l_int|0
suffix:semicolon
r_case
id|CARD_RELEASE
suffix:colon
id|release_ioregs
c_func
(paren
id|cs
comma
l_int|0x3f
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|CARD_TEST
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|avm_a1_init
id|avm_a1_init
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
id|byteout
c_func
(paren
id|cs-&gt;hw.avm.cfg_reg
comma
l_int|0x16
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.avm.cfg_reg
comma
l_int|0x1E
)paren
suffix:semicolon
id|inithscxisac
c_func
(paren
id|cs
)paren
suffix:semicolon
)brace
DECL|variable|avm_a1_ops
r_static
r_struct
id|card_ops
id|avm_a1_ops
op_assign
(brace
dot
id|init
op_assign
id|avm_a1_init
comma
dot
id|irq_func
op_assign
id|avm_a1_interrupt
comma
)brace
suffix:semicolon
r_int
id|__init
DECL|function|setup_avm_a1
id|setup_avm_a1
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
id|avm_revision
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: AVM driver Rev. %s&bslash;n&quot;
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
id|ISDN_CTYPE_A1
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
id|cs-&gt;hw.avm.cfg_reg
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
op_plus
l_int|0x1800
suffix:semicolon
id|cs-&gt;hw.avm.isac
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
op_plus
l_int|0x1400
op_minus
l_int|0x20
suffix:semicolon
id|cs-&gt;hw.avm.hscx
(braket
l_int|0
)braket
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
op_plus
l_int|0x400
op_minus
l_int|0x20
suffix:semicolon
id|cs-&gt;hw.avm.hscx
(braket
l_int|1
)braket
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
op_plus
l_int|0xc00
op_minus
l_int|0x20
suffix:semicolon
id|cs-&gt;hw.avm.isacfifo
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
op_plus
l_int|0x1000
suffix:semicolon
id|cs-&gt;hw.avm.hscxfifo
(braket
l_int|0
)braket
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
suffix:semicolon
id|cs-&gt;hw.avm.hscxfifo
(braket
l_int|1
)braket
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
op_plus
l_int|0x800
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
id|request_region
c_func
(paren
id|cs-&gt;hw.avm.cfg_reg
comma
l_int|8
comma
l_string|&quot;avm cfg&quot;
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
id|cs-&gt;hw.avm.cfg_reg
comma
id|cs-&gt;hw.avm.cfg_reg
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
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|cs-&gt;hw.avm.isac
op_plus
l_int|32
comma
l_int|32
comma
l_string|&quot;HiSax isac&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s isac ports %x-%x already in use&bslash;n&quot;
comma
id|CardType
(braket
id|cs-&gt;typ
)braket
comma
id|cs-&gt;hw.avm.isac
op_plus
l_int|32
comma
id|cs-&gt;hw.avm.isac
op_plus
l_int|64
)paren
suffix:semicolon
id|release_ioregs
c_func
(paren
id|cs
comma
l_int|0
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
op_logical_neg
id|request_region
c_func
(paren
id|cs-&gt;hw.avm.isacfifo
comma
l_int|1
comma
l_string|&quot;HiSax isac fifo&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s isac fifo port %x already in use&bslash;n&quot;
comma
id|CardType
(braket
id|cs-&gt;typ
)braket
comma
id|cs-&gt;hw.avm.isacfifo
)paren
suffix:semicolon
id|release_ioregs
c_func
(paren
id|cs
comma
l_int|1
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
op_logical_neg
id|request_region
c_func
(paren
id|cs-&gt;hw.avm.hscx
(braket
l_int|0
)braket
op_plus
l_int|32
comma
l_int|32
comma
l_string|&quot;HiSax hscx A&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s hscx A ports %x-%x already in use&bslash;n&quot;
comma
id|CardType
(braket
id|cs-&gt;typ
)braket
comma
id|cs-&gt;hw.avm.hscx
(braket
l_int|0
)braket
op_plus
l_int|32
comma
id|cs-&gt;hw.avm.hscx
(braket
l_int|0
)braket
op_plus
l_int|64
)paren
suffix:semicolon
id|release_ioregs
c_func
(paren
id|cs
comma
l_int|3
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
op_logical_neg
id|request_region
c_func
(paren
id|cs-&gt;hw.avm.hscxfifo
(braket
l_int|0
)braket
comma
l_int|1
comma
l_string|&quot;HiSax hscx A fifo&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s hscx A fifo port %x already in use&bslash;n&quot;
comma
id|CardType
(braket
id|cs-&gt;typ
)braket
comma
id|cs-&gt;hw.avm.hscxfifo
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|release_ioregs
c_func
(paren
id|cs
comma
l_int|7
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
op_logical_neg
id|request_region
c_func
(paren
id|cs-&gt;hw.avm.hscx
(braket
l_int|1
)braket
op_plus
l_int|32
comma
l_int|32
comma
l_string|&quot;HiSax hscx B&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s hscx B ports %x-%x already in use&bslash;n&quot;
comma
id|CardType
(braket
id|cs-&gt;typ
)braket
comma
id|cs-&gt;hw.avm.hscx
(braket
l_int|1
)braket
op_plus
l_int|32
comma
id|cs-&gt;hw.avm.hscx
(braket
l_int|1
)braket
op_plus
l_int|64
)paren
suffix:semicolon
id|release_ioregs
c_func
(paren
id|cs
comma
l_int|0xf
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
op_logical_neg
id|request_region
c_func
(paren
id|cs-&gt;hw.avm.hscxfifo
(braket
l_int|1
)braket
comma
l_int|1
comma
l_string|&quot;HiSax hscx B fifo&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s hscx B fifo port %x already in use&bslash;n&quot;
comma
id|CardType
(braket
id|cs-&gt;typ
)braket
comma
id|cs-&gt;hw.avm.hscxfifo
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|release_ioregs
c_func
(paren
id|cs
comma
l_int|0x1f
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|byteout
c_func
(paren
id|cs-&gt;hw.avm.cfg_reg
comma
l_int|0x0
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
id|byteout
c_func
(paren
id|cs-&gt;hw.avm.cfg_reg
comma
l_int|0x1
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
id|byteout
c_func
(paren
id|cs-&gt;hw.avm.cfg_reg
comma
l_int|0x0
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
id|val
op_assign
id|cs-&gt;irq
suffix:semicolon
r_if
c_cond
(paren
id|val
op_eq
l_int|9
)paren
id|val
op_assign
l_int|2
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.avm.cfg_reg
op_plus
l_int|1
comma
id|val
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
id|byteout
c_func
(paren
id|cs-&gt;hw.avm.cfg_reg
comma
l_int|0x0
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
id|val
op_assign
id|bytein
c_func
(paren
id|cs-&gt;hw.avm.cfg_reg
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;AVM A1: Byte at %x is %x&bslash;n&quot;
comma
id|cs-&gt;hw.avm.cfg_reg
comma
id|val
)paren
suffix:semicolon
id|val
op_assign
id|bytein
c_func
(paren
id|cs-&gt;hw.avm.cfg_reg
op_plus
l_int|3
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;AVM A1: Byte at %x is %x&bslash;n&quot;
comma
id|cs-&gt;hw.avm.cfg_reg
op_plus
l_int|3
comma
id|val
)paren
suffix:semicolon
id|val
op_assign
id|bytein
c_func
(paren
id|cs-&gt;hw.avm.cfg_reg
op_plus
l_int|2
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;AVM A1: Byte at %x is %x&bslash;n&quot;
comma
id|cs-&gt;hw.avm.cfg_reg
op_plus
l_int|2
comma
id|val
)paren
suffix:semicolon
id|val
op_assign
id|bytein
c_func
(paren
id|cs-&gt;hw.avm.cfg_reg
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;AVM A1: Byte at %x is %x&bslash;n&quot;
comma
id|cs-&gt;hw.avm.cfg_reg
comma
id|val
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
id|cs-&gt;hw.avm.cfg_reg
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: isac:0x%X/0x%X&bslash;n&quot;
comma
id|cs-&gt;hw.avm.isac
op_plus
l_int|32
comma
id|cs-&gt;hw.avm.isacfifo
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: hscx A:0x%X/0x%X  hscx B:0x%X/0x%X&bslash;n&quot;
comma
id|cs-&gt;hw.avm.hscx
(braket
l_int|0
)braket
op_plus
l_int|32
comma
id|cs-&gt;hw.avm.hscxfifo
(braket
l_int|0
)braket
comma
id|cs-&gt;hw.avm.hscx
(braket
l_int|1
)braket
op_plus
l_int|32
comma
id|cs-&gt;hw.avm.hscxfifo
(braket
l_int|1
)braket
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
id|AVM_card_msg
suffix:semicolon
id|cs-&gt;card_ops
op_assign
op_amp
id|avm_a1_ops
suffix:semicolon
id|ISACVersion
c_func
(paren
id|cs
comma
l_string|&quot;AVM A1:&quot;
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
l_string|&quot;AVM A1:&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;AVM A1: wrong HSCX versions check IO address&bslash;n&quot;
)paren
suffix:semicolon
id|release_ioregs
c_func
(paren
id|cs
comma
l_int|0x3f
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
