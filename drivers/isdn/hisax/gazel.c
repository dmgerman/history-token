multiline_comment|/* $Id: gazel.c,v 2.11.6.7 2001/09/23 22:24:47 kai Exp $&n; *&n; * low level stuff for Gazel isdn cards&n; *&n; * Author       BeWan Systems&n; *              based on source code from Karsten Keil&n; * Copyright    by BeWan Systems&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;hisax.h&quot;
macro_line|#include &quot;isac.h&quot;
macro_line|#include &quot;hscx.h&quot;
macro_line|#include &quot;isdnl1.h&quot;
macro_line|#include &quot;ipac.h&quot;
macro_line|#include &lt;linux/pci.h&gt;
r_extern
r_const
r_char
op_star
id|CardType
(braket
)braket
suffix:semicolon
DECL|variable|gazel_revision
r_const
r_char
op_star
id|gazel_revision
op_assign
l_string|&quot;$Revision: 2.11.6.7 $&quot;
suffix:semicolon
DECL|variable|gazel_lock
r_static
id|spinlock_t
id|gazel_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|macro|R647
mdefine_line|#define R647      1
DECL|macro|R685
mdefine_line|#define R685      2
DECL|macro|R753
mdefine_line|#define R753      3
DECL|macro|R742
mdefine_line|#define R742      4
DECL|macro|PLX_CNTRL
mdefine_line|#define PLX_CNTRL    0x50&t;/* registre de controle PLX */
DECL|macro|RESET_GAZEL
mdefine_line|#define RESET_GAZEL  0x4
DECL|macro|RESET_9050
mdefine_line|#define RESET_9050   0x40000000
DECL|macro|PLX_INCSR
mdefine_line|#define PLX_INCSR    0x4C&t;/* registre d&squot;IT du 9050 */
DECL|macro|INT_ISAC_EN
mdefine_line|#define INT_ISAC_EN  0x8&t;/* 1 = enable IT isac */
DECL|macro|INT_ISAC
mdefine_line|#define INT_ISAC     0x20&t;/* 1 = IT isac en cours */
DECL|macro|INT_HSCX_EN
mdefine_line|#define INT_HSCX_EN  0x1&t;/* 1 = enable IT hscx */
DECL|macro|INT_HSCX
mdefine_line|#define INT_HSCX     0x4&t;/* 1 = IT hscx en cours */
DECL|macro|INT_PCI_EN
mdefine_line|#define INT_PCI_EN   0x40&t;/* 1 = enable IT PCI */
DECL|macro|INT_IPAC_EN
mdefine_line|#define INT_IPAC_EN  0x3&t;/* enable IT ipac */
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
id|u_short
id|off
)paren
(brace
r_return
id|bytein
c_func
(paren
id|adr
op_plus
id|off
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
id|u_short
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
DECL|function|r685_isac_read
id|r685_isac_read
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
id|readreg
c_func
(paren
id|cs-&gt;hw.gazel.isac
comma
id|off
)paren
suffix:semicolon
)brace
r_static
id|u8
DECL|function|r647_isac_read
id|r647_isac_read
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
id|readreg
c_func
(paren
id|cs-&gt;hw.gazel.isac
comma
(paren
id|off
op_lshift
l_int|8
op_amp
l_int|0xf000
)paren
op_or
(paren
id|off
op_amp
l_int|0xf
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|r685_isac_write
id|r685_isac_write
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
id|value
)paren
(brace
id|writereg
c_func
(paren
id|cs-&gt;hw.gazel.isac
comma
id|off
comma
id|value
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|r647_isac_write
id|r647_isac_write
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
id|value
)paren
(brace
id|writereg
c_func
(paren
id|cs-&gt;hw.gazel.isac
comma
(paren
id|off
op_lshift
l_int|8
op_amp
l_int|0xf000
)paren
op_or
(paren
id|off
op_amp
l_int|0xf
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
id|cs-&gt;hw.gazel.isacfifo
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
id|cs-&gt;hw.gazel.isacfifo
comma
id|data
comma
id|size
)paren
suffix:semicolon
)brace
DECL|variable|r685_isac_ops
r_static
r_struct
id|dc_hw_ops
id|r685_isac_ops
op_assign
(brace
dot
id|read_reg
op_assign
id|r685_isac_read
comma
dot
id|write_reg
op_assign
id|r685_isac_write
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
DECL|variable|r647_isac_ops
r_static
r_struct
id|dc_hw_ops
id|r647_isac_ops
op_assign
(brace
dot
id|read_reg
op_assign
id|r647_isac_read
comma
dot
id|write_reg
op_assign
id|r647_isac_write
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
DECL|function|r685_hscx_read
id|r685_hscx_read
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
id|readreg
c_func
(paren
id|cs-&gt;hw.gazel.hscx
(braket
id|hscx
)braket
comma
id|off
)paren
suffix:semicolon
)brace
r_static
id|u8
DECL|function|r647_hscx_read
id|r647_hscx_read
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
id|readreg
c_func
(paren
id|cs-&gt;hw.gazel.hscx
(braket
id|hscx
)braket
comma
(paren
id|off
op_lshift
l_int|8
op_amp
l_int|0xf000
)paren
op_or
(paren
id|off
op_amp
l_int|0xf
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|r685_hscx_write
id|r685_hscx_write
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
id|value
)paren
(brace
id|writereg
c_func
(paren
id|cs-&gt;hw.gazel.hscx
(braket
id|hscx
)braket
comma
id|off
comma
id|value
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|r647_hscx_write
id|r647_hscx_write
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
id|value
)paren
(brace
id|writereg
c_func
(paren
id|cs-&gt;hw.gazel.hscx
(braket
id|hscx
)braket
comma
(paren
id|off
op_lshift
l_int|8
op_amp
l_int|0xf000
)paren
op_or
(paren
id|off
op_amp
l_int|0xf
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
id|cs-&gt;hw.gazel.hscxfifo
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
id|cs-&gt;hw.gazel.hscxfifo
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
DECL|variable|r685_hscx_ops
r_static
r_struct
id|bc_hw_ops
id|r685_hscx_ops
op_assign
(brace
dot
id|read_reg
op_assign
id|r685_hscx_read
comma
dot
id|write_reg
op_assign
id|r685_hscx_write
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
DECL|variable|r647_hscx_ops
r_static
r_struct
id|bc_hw_ops
id|r647_hscx_ops
op_assign
(brace
dot
id|read_reg
op_assign
id|r647_hscx_read
comma
dot
id|write_reg
op_assign
id|r647_hscx_write
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
r_inline
id|u8
DECL|function|ipac_read
id|ipac_read
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u_short
id|off
)paren
(brace
r_register
id|u8
id|ret
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|gazel_lock
comma
id|flags
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.gazel.ipac
comma
id|off
)paren
suffix:semicolon
id|ret
op_assign
id|bytein
c_func
(paren
id|cs-&gt;hw.gazel.ipac
op_plus
l_int|4
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gazel_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ipac_write
id|ipac_write
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u_short
id|off
comma
id|u8
id|data
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
id|gazel_lock
comma
id|flags
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.gazel.ipac
comma
id|off
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.gazel.ipac
op_plus
l_int|4
comma
id|data
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gazel_lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ipac_readfifo
id|ipac_readfifo
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
op_star
id|data
comma
r_int
id|size
)paren
(brace
id|byteout
c_func
(paren
id|cs-&gt;hw.gazel.ipac
comma
id|off
)paren
suffix:semicolon
id|insb
c_func
(paren
id|cs-&gt;hw.gazel.ipac
op_plus
l_int|4
comma
id|data
comma
id|size
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ipac_writefifo
id|ipac_writefifo
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
op_star
id|data
comma
r_int
id|size
)paren
(brace
id|byteout
c_func
(paren
id|cs-&gt;hw.gazel.ipac
comma
id|off
)paren
suffix:semicolon
id|outsb
c_func
(paren
id|cs-&gt;hw.gazel.ipac
op_plus
l_int|4
comma
id|data
comma
id|size
)paren
suffix:semicolon
)brace
multiline_comment|/* This will generate ipac_dc_ops and ipac_bc_ops using the functions&n; * above */
DECL|variable|ipac
id|BUILD_IPAC_OPS
c_func
(paren
id|ipac
)paren
suffix:semicolon
r_static
r_int
DECL|function|r647_reset
id|r647_reset
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
id|writereg
c_func
(paren
id|cs-&gt;hw.gazel.cfg_reg
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|HZDELAY
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|cs-&gt;hw.gazel.cfg_reg
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|HZDELAY
c_func
(paren
l_int|2
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|r685_reset
id|r685_reset
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
r_int
r_int
id|plxcntrl
comma
id|addr
op_assign
id|cs-&gt;hw.gazel.cfg_reg
suffix:semicolon
id|plxcntrl
op_assign
id|inl
c_func
(paren
id|addr
op_plus
id|PLX_CNTRL
)paren
suffix:semicolon
id|plxcntrl
op_or_assign
(paren
id|RESET_9050
op_plus
id|RESET_GAZEL
)paren
suffix:semicolon
id|outl
c_func
(paren
id|plxcntrl
comma
id|addr
op_plus
id|PLX_CNTRL
)paren
suffix:semicolon
id|plxcntrl
op_and_assign
op_complement
(paren
id|RESET_9050
op_plus
id|RESET_GAZEL
)paren
suffix:semicolon
id|HZDELAY
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|outl
c_func
(paren
id|plxcntrl
comma
id|addr
op_plus
id|PLX_CNTRL
)paren
suffix:semicolon
id|HZDELAY
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|outb
c_func
(paren
id|INT_ISAC_EN
op_plus
id|INT_HSCX_EN
op_plus
id|INT_PCI_EN
comma
id|addr
op_plus
id|PLX_INCSR
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|r753_reset
id|r753_reset
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
r_int
r_int
id|plxcntrl
comma
id|addr
op_assign
id|cs-&gt;hw.gazel.cfg_reg
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|FLG_BUGGY_PLX9050
comma
op_amp
id|cs-&gt;HW_Flags
)paren
)paren
multiline_comment|/* we can&squot;t read, assume the default */
id|plxcntrl
op_assign
l_int|0x18784db6
suffix:semicolon
r_else
id|plxcntrl
op_assign
id|inl
c_func
(paren
id|addr
op_plus
id|PLX_CNTRL
)paren
suffix:semicolon
id|plxcntrl
op_or_assign
(paren
id|RESET_9050
op_plus
id|RESET_GAZEL
)paren
suffix:semicolon
id|outl
c_func
(paren
id|plxcntrl
comma
id|addr
op_plus
id|PLX_CNTRL
)paren
suffix:semicolon
id|ipac_write
c_func
(paren
id|cs
comma
id|IPAC_POTA2
comma
l_int|0x20
)paren
suffix:semicolon
id|HZDELAY
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|plxcntrl
op_and_assign
op_complement
(paren
id|RESET_9050
op_plus
id|RESET_GAZEL
)paren
suffix:semicolon
id|outl
c_func
(paren
id|plxcntrl
comma
id|addr
op_plus
id|PLX_CNTRL
)paren
suffix:semicolon
id|HZDELAY
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|ipac_write
c_func
(paren
id|cs
comma
id|IPAC_POTA2
comma
l_int|0x00
)paren
suffix:semicolon
id|ipac_write
c_func
(paren
id|cs
comma
id|IPAC_ACFG
comma
l_int|0xff
)paren
suffix:semicolon
id|ipac_write
c_func
(paren
id|cs
comma
id|IPAC_AOE
comma
l_int|0x0
)paren
suffix:semicolon
id|ipac_write
c_func
(paren
id|cs
comma
id|IPAC_MASK
comma
l_int|0xff
)paren
suffix:semicolon
id|ipac_write
c_func
(paren
id|cs
comma
id|IPAC_CONF
comma
l_int|0x1
)paren
suffix:semicolon
id|outb
c_func
(paren
id|INT_IPAC_EN
op_plus
id|INT_PCI_EN
comma
id|addr
op_plus
id|PLX_INCSR
)paren
suffix:semicolon
id|ipac_write
c_func
(paren
id|cs
comma
id|IPAC_MASK
comma
l_int|0xc0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|r742_reset
id|r742_reset
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
id|ipac_write
c_func
(paren
id|cs
comma
id|IPAC_POTA2
comma
l_int|0x20
)paren
suffix:semicolon
id|HZDELAY
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|ipac_write
c_func
(paren
id|cs
comma
id|IPAC_POTA2
comma
l_int|0x00
)paren
suffix:semicolon
id|ipac_write
c_func
(paren
id|cs
comma
id|IPAC_ACFG
comma
l_int|0xff
)paren
suffix:semicolon
id|ipac_write
c_func
(paren
id|cs
comma
id|IPAC_AOE
comma
l_int|0x0
)paren
suffix:semicolon
id|ipac_write
c_func
(paren
id|cs
comma
id|IPAC_MASK
comma
l_int|0xff
)paren
suffix:semicolon
id|ipac_write
c_func
(paren
id|cs
comma
id|IPAC_CONF
comma
l_int|0x1
)paren
suffix:semicolon
id|ipac_write
c_func
(paren
id|cs
comma
id|IPAC_MASK
comma
l_int|0xc0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|gazel_init
id|gazel_init
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
id|cs-&gt;bcs
(braket
id|i
)braket
dot
id|hw.hscx.tsaxr0
op_assign
l_int|0x1f
suffix:semicolon
id|cs-&gt;bcs
(braket
id|i
)braket
dot
id|hw.hscx.tsaxr1
op_assign
l_int|0x23
suffix:semicolon
)brace
id|inithscxisac
c_func
(paren
id|cs
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|r647_reserve_regions
id|r647_reserve_regions
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
id|base
op_assign
id|cs-&gt;hw.gazel.hscx
(braket
l_int|0
)braket
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
l_int|0xc000
suffix:semicolon
id|i
op_add_assign
l_int|0x1000
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|request_io
c_func
(paren
op_amp
id|cs-&gt;rs
comma
id|i
op_plus
id|base
comma
l_int|16
comma
l_string|&quot;gazel&quot;
)paren
)paren
r_goto
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|request_io
c_func
(paren
op_amp
id|cs-&gt;rs
comma
l_int|0xc000
op_plus
id|base
comma
l_int|1
comma
l_string|&quot;gazel&quot;
)paren
)paren
r_goto
id|err
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err
suffix:colon
id|hisax_release_resources
c_func
(paren
id|cs
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_static
r_int
DECL|function|r685_reserve_regions
id|r685_reserve_regions
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
op_logical_neg
id|request_io
c_func
(paren
op_amp
id|cs-&gt;rs
comma
id|cs-&gt;hw.gazel.hscx
(braket
l_int|0
)braket
comma
l_int|0x100
comma
l_string|&quot;gazel&quot;
)paren
)paren
r_goto
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_io
c_func
(paren
op_amp
id|cs-&gt;rs
comma
id|cs-&gt;hw.gazel.cfg_reg
comma
l_int|0x80
comma
l_string|&quot;gazel&quot;
)paren
)paren
r_goto
id|err
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err
suffix:colon
id|hisax_release_resources
c_func
(paren
id|cs
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_static
r_int
DECL|function|r742_reserve_regions
id|r742_reserve_regions
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
op_logical_neg
id|request_io
c_func
(paren
op_amp
id|cs-&gt;rs
comma
id|cs-&gt;hw.gazel.ipac
comma
l_int|0x8
comma
l_string|&quot;gazel&quot;
)paren
)paren
r_goto
id|err
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err
suffix:colon
id|hisax_release_resources
c_func
(paren
id|cs
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_static
r_int
DECL|function|r753_reserve_regions
id|r753_reserve_regions
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
op_logical_neg
id|request_io
c_func
(paren
op_amp
id|cs-&gt;rs
comma
id|cs-&gt;hw.gazel.ipac
comma
l_int|0x8
comma
l_string|&quot;gazel&quot;
)paren
)paren
r_goto
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_io
c_func
(paren
op_amp
id|cs-&gt;rs
comma
id|cs-&gt;hw.gazel.cfg_reg
comma
l_int|0x80
comma
l_string|&quot;gazel&quot;
)paren
)paren
r_goto
id|err
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err
suffix:colon
id|hisax_release_resources
c_func
(paren
id|cs
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
DECL|variable|r647_ops
r_static
r_struct
id|card_ops
id|r647_ops
op_assign
(brace
dot
id|init
op_assign
id|gazel_init
comma
dot
id|reset
op_assign
id|r647_reset
comma
dot
id|release
op_assign
id|hisax_release_resources
comma
dot
id|irq_func
op_assign
id|hscxisac_irq
comma
)brace
suffix:semicolon
DECL|variable|r685_ops
r_static
r_struct
id|card_ops
id|r685_ops
op_assign
(brace
dot
id|init
op_assign
id|gazel_init
comma
dot
id|reset
op_assign
id|r685_reset
comma
dot
id|release
op_assign
id|hisax_release_resources
comma
dot
id|irq_func
op_assign
id|hscxisac_irq
comma
)brace
suffix:semicolon
DECL|variable|r742_ops
r_static
r_struct
id|card_ops
id|r742_ops
op_assign
(brace
dot
id|init
op_assign
id|ipac_init
comma
dot
id|reset
op_assign
id|r742_reset
comma
dot
id|release
op_assign
id|hisax_release_resources
comma
dot
id|irq_func
op_assign
id|ipac_irq
comma
)brace
suffix:semicolon
DECL|variable|r753_ops
r_static
r_struct
id|card_ops
id|r753_ops
op_assign
(brace
dot
id|init
op_assign
id|ipac_init
comma
dot
id|reset
op_assign
id|r753_reset
comma
dot
id|release
op_assign
id|hisax_release_resources
comma
dot
id|irq_func
op_assign
id|ipac_irq
comma
)brace
suffix:semicolon
r_static
r_int
id|__init
DECL|function|setup_gazelisa
id|setup_gazelisa
c_func
(paren
r_struct
id|IsdnCard
op_star
id|card
comma
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Gazel: ISA PnP card automatic recognition&bslash;n&quot;
)paren
suffix:semicolon
singleline_comment|// we got an irq parameter, assume it is an ISA card
singleline_comment|// R742 decodes address even in not started...
singleline_comment|// R647 returns FF if not present or not started
singleline_comment|// eventually needs improvment
id|cs-&gt;hw.gazel.ipac
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ipac_read
c_func
(paren
id|cs
comma
id|IPAC_ID
)paren
op_eq
l_int|1
)paren
id|cs-&gt;subtyp
op_assign
id|R742
suffix:semicolon
r_else
id|cs-&gt;subtyp
op_assign
id|R647
suffix:semicolon
id|cs-&gt;hw.gazel.cfg_reg
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
op_plus
l_int|0xC000
suffix:semicolon
id|cs-&gt;hw.gazel.isac
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
op_plus
l_int|0x8000
suffix:semicolon
id|cs-&gt;hw.gazel.hscx
(braket
l_int|0
)braket
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
suffix:semicolon
id|cs-&gt;hw.gazel.hscx
(braket
l_int|1
)braket
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
op_plus
l_int|0x4000
suffix:semicolon
id|cs-&gt;irq
op_assign
id|card-&gt;para
(braket
l_int|0
)braket
suffix:semicolon
id|cs-&gt;hw.gazel.isacfifo
op_assign
id|cs-&gt;hw.gazel.isac
suffix:semicolon
id|cs-&gt;hw.gazel.hscxfifo
(braket
l_int|0
)braket
op_assign
id|cs-&gt;hw.gazel.hscx
(braket
l_int|0
)braket
suffix:semicolon
id|cs-&gt;hw.gazel.hscxfifo
(braket
l_int|1
)braket
op_assign
id|cs-&gt;hw.gazel.hscx
(braket
l_int|1
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|cs-&gt;subtyp
)paren
(brace
r_case
id|R647
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Gazel: Card ISA R647/R648 found&bslash;n&quot;
)paren
suffix:semicolon
id|cs-&gt;dc.isac.adf2
op_assign
l_int|0x87
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Gazel: config irq:%d isac:0x%X  cfg:0x%X&bslash;n&quot;
comma
id|cs-&gt;irq
comma
id|cs-&gt;hw.gazel.isac
comma
id|cs-&gt;hw.gazel.cfg_reg
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Gazel: hscx A:0x%X  hscx B:0x%X&bslash;n&quot;
comma
id|cs-&gt;hw.gazel.hscx
(braket
l_int|0
)braket
comma
id|cs-&gt;hw.gazel.hscx
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_return
id|r647_reserve_regions
c_func
(paren
id|cs
)paren
suffix:semicolon
r_case
id|R742
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Gazel: Card ISA R742 found&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Gazel: config irq:%d ipac:0x%X&bslash;n&quot;
comma
id|cs-&gt;irq
comma
id|cs-&gt;hw.gazel.ipac
)paren
suffix:semicolon
r_return
id|r742_reserve_regions
c_func
(paren
id|cs
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|pci_dev
op_star
id|dev_tel
id|__initdata
op_assign
l_int|NULL
suffix:semicolon
r_static
r_int
id|__init
DECL|function|setup_gazelpci
id|setup_gazelpci
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
id|u_int
id|pci_ioaddr0
op_assign
l_int|0
comma
id|pci_ioaddr1
op_assign
l_int|0
suffix:semicolon
id|u8
id|pci_irq
op_assign
l_int|0
comma
id|found
suffix:semicolon
id|u_int
id|nbseek
comma
id|seekcard
suffix:semicolon
id|u8
id|pci_rev
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Gazel: PCI card automatic recognition&bslash;n&quot;
)paren
suffix:semicolon
id|found
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pci_present
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Gazel: No PCI bus present&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|seekcard
op_assign
id|PCI_DEVICE_ID_PLX_R685
suffix:semicolon
r_for
c_loop
(paren
id|nbseek
op_assign
l_int|0
suffix:semicolon
id|nbseek
OL
l_int|3
suffix:semicolon
id|nbseek
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|dev_tel
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_PLX
comma
id|seekcard
comma
id|dev_tel
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|pci_enable_device
c_func
(paren
id|dev_tel
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|pci_irq
op_assign
id|dev_tel-&gt;irq
suffix:semicolon
id|pci_ioaddr0
op_assign
id|pci_resource_start
c_func
(paren
id|dev_tel
comma
l_int|1
)paren
suffix:semicolon
id|pci_ioaddr1
op_assign
id|pci_resource_start
c_func
(paren
id|dev_tel
comma
l_int|2
)paren
suffix:semicolon
id|found
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|found
)paren
r_break
suffix:semicolon
r_else
(brace
r_switch
c_cond
(paren
id|seekcard
)paren
(brace
r_case
id|PCI_DEVICE_ID_PLX_R685
suffix:colon
id|seekcard
op_assign
id|PCI_DEVICE_ID_PLX_R753
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_DEVICE_ID_PLX_R753
suffix:colon
id|seekcard
op_assign
id|PCI_DEVICE_ID_PLX_DJINN_ITOO
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|found
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Gazel: No PCI card found&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pci_irq
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Gazel: No IRQ for PCI card found&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|cs-&gt;hw.gazel.pciaddr
(braket
l_int|0
)braket
op_assign
id|pci_ioaddr0
suffix:semicolon
id|cs-&gt;hw.gazel.pciaddr
(braket
l_int|1
)braket
op_assign
id|pci_ioaddr1
suffix:semicolon
id|pci_ioaddr1
op_and_assign
l_int|0xfffe
suffix:semicolon
id|cs-&gt;hw.gazel.cfg_reg
op_assign
id|pci_ioaddr0
op_amp
l_int|0xfffe
suffix:semicolon
id|cs-&gt;hw.gazel.ipac
op_assign
id|pci_ioaddr1
suffix:semicolon
id|cs-&gt;hw.gazel.isac
op_assign
id|pci_ioaddr1
op_plus
l_int|0x80
suffix:semicolon
id|cs-&gt;hw.gazel.hscx
(braket
l_int|0
)braket
op_assign
id|pci_ioaddr1
suffix:semicolon
id|cs-&gt;hw.gazel.hscx
(braket
l_int|1
)braket
op_assign
id|pci_ioaddr1
op_plus
l_int|0x40
suffix:semicolon
id|cs-&gt;hw.gazel.isacfifo
op_assign
id|cs-&gt;hw.gazel.isac
suffix:semicolon
id|cs-&gt;hw.gazel.hscxfifo
(braket
l_int|0
)braket
op_assign
id|cs-&gt;hw.gazel.hscx
(braket
l_int|0
)braket
suffix:semicolon
id|cs-&gt;hw.gazel.hscxfifo
(braket
l_int|1
)braket
op_assign
id|cs-&gt;hw.gazel.hscx
(braket
l_int|1
)braket
suffix:semicolon
id|cs-&gt;irq
op_assign
id|pci_irq
suffix:semicolon
id|cs-&gt;irq_flags
op_or_assign
id|SA_SHIRQ
suffix:semicolon
r_switch
c_cond
(paren
id|seekcard
)paren
(brace
r_case
id|PCI_DEVICE_ID_PLX_R685
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Gazel: Card PCI R685 found&bslash;n&quot;
)paren
suffix:semicolon
id|cs-&gt;subtyp
op_assign
id|R685
suffix:semicolon
id|cs-&gt;dc.isac.adf2
op_assign
l_int|0x87
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Gazel: config irq:%d isac:0x%X  cfg:0x%X&bslash;n&quot;
comma
id|cs-&gt;irq
comma
id|cs-&gt;hw.gazel.isac
comma
id|cs-&gt;hw.gazel.cfg_reg
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Gazel: hscx A:0x%X  hscx B:0x%X&bslash;n&quot;
comma
id|cs-&gt;hw.gazel.hscx
(braket
l_int|0
)braket
comma
id|cs-&gt;hw.gazel.hscx
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_return
id|r685_reserve_regions
c_func
(paren
id|cs
)paren
suffix:semicolon
r_case
id|PCI_DEVICE_ID_PLX_R753
suffix:colon
r_case
id|PCI_DEVICE_ID_PLX_DJINN_ITOO
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Gazel: Card PCI R753 found&bslash;n&quot;
)paren
suffix:semicolon
id|cs-&gt;subtyp
op_assign
id|R753
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Gazel: config irq:%d ipac:0x%X  cfg:0x%X&bslash;n&quot;
comma
id|cs-&gt;irq
comma
id|cs-&gt;hw.gazel.ipac
comma
id|cs-&gt;hw.gazel.cfg_reg
)paren
suffix:semicolon
multiline_comment|/* &n;&t;&t; * Erratum for PLX9050, revision 1:&n;&t;&t; * If bit 7 of BAR 0/1 is set, local config registers&n;&t;&t; * can not be read (write is okay)&n;&t;&t; */
r_if
c_cond
(paren
id|cs-&gt;hw.gazel.cfg_reg
op_amp
l_int|0x80
)paren
(brace
id|pci_read_config_byte
c_func
(paren
id|dev_tel
comma
id|PCI_REVISION_ID
comma
op_amp
id|pci_rev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pci_rev
op_eq
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Gazel: PLX9050 rev1 workaround activated&bslash;n&quot;
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|FLG_BUGGY_PLX9050
comma
op_amp
id|cs-&gt;HW_Flags
)paren
suffix:semicolon
)brace
)brace
r_return
id|r753_reserve_regions
c_func
(paren
id|cs
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_int
id|__init
DECL|function|setup_gazel
id|setup_gazel
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
id|u8
id|val
suffix:semicolon
id|strcpy
c_func
(paren
id|tmp
comma
id|gazel_revision
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Gazel: Driver Revision %s&bslash;n&quot;
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
id|card-&gt;para
(braket
l_int|0
)braket
)paren
(brace
r_if
c_cond
(paren
id|setup_gazelisa
c_func
(paren
id|card
comma
id|cs
)paren
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|setup_gazelpci
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
)brace
r_switch
c_cond
(paren
id|cs-&gt;subtyp
)paren
(brace
r_case
id|R647
suffix:colon
r_case
id|R685
suffix:colon
r_if
c_cond
(paren
id|cs-&gt;subtyp
op_eq
id|R647
)paren
(brace
id|cs-&gt;dc_hw_ops
op_assign
op_amp
id|r647_isac_ops
suffix:semicolon
id|cs-&gt;bc_hw_ops
op_assign
op_amp
id|r647_hscx_ops
suffix:semicolon
id|cs-&gt;card_ops
op_assign
op_amp
id|r647_ops
suffix:semicolon
)brace
r_else
(brace
id|cs-&gt;dc_hw_ops
op_assign
op_amp
id|r685_isac_ops
suffix:semicolon
id|cs-&gt;bc_hw_ops
op_assign
op_amp
id|r685_hscx_ops
suffix:semicolon
id|cs-&gt;card_ops
op_assign
op_amp
id|r685_ops
suffix:semicolon
)brace
id|cs-&gt;card_ops
op_member_access_from_pointer
id|reset
c_func
(paren
id|cs
)paren
suffix:semicolon
id|ISACVersion
c_func
(paren
id|cs
comma
l_string|&quot;Gazel:&quot;
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
l_string|&quot;Gazel:&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Gazel: wrong HSCX versions check IO address&bslash;n&quot;
)paren
suffix:semicolon
id|cs-&gt;card_ops
op_member_access_from_pointer
id|release
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
r_break
suffix:semicolon
r_case
id|R742
suffix:colon
r_case
id|R753
suffix:colon
r_if
c_cond
(paren
id|cs-&gt;subtyp
op_eq
id|R742
)paren
(brace
id|cs-&gt;card_ops
op_assign
op_amp
id|r742_ops
suffix:semicolon
)brace
r_else
(brace
id|cs-&gt;card_ops
op_assign
op_amp
id|r753_ops
suffix:semicolon
)brace
id|cs-&gt;dc_hw_ops
op_assign
op_amp
id|ipac_dc_ops
suffix:semicolon
id|cs-&gt;bc_hw_ops
op_assign
op_amp
id|ipac_bc_ops
suffix:semicolon
id|cs-&gt;card_ops
op_member_access_from_pointer
id|reset
c_func
(paren
id|cs
)paren
suffix:semicolon
id|val
op_assign
id|ipac_read
c_func
(paren
id|cs
comma
id|IPAC_ID
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Gazel: IPAC version %x&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
eof
