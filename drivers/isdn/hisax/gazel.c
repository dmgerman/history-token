multiline_comment|/* $Id: gazel.c,v 2.11.6.7 2001/09/23 22:24:47 kai Exp $&n; *&n; * low level stuff for Gazel isdn cards&n; *&n; * Author       BeWan Systems&n; *              based on source code from Karsten Keil&n; * Copyright    by BeWan Systems&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
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
id|u_char
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
id|u_char
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
id|u_char
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
id|u_char
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
r_inline
id|u_char
DECL|function|readreg_ipac
id|readreg_ipac
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
r_register
id|u_char
id|ret
suffix:semicolon
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|adr
comma
id|off
)paren
suffix:semicolon
id|ret
op_assign
id|bytein
c_func
(paren
id|adr
op_plus
l_int|4
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
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
DECL|function|writereg_ipac
id|writereg_ipac
c_func
(paren
r_int
r_int
id|adr
comma
id|u_short
id|off
comma
id|u_char
id|data
)paren
(brace
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|adr
comma
id|off
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|adr
op_plus
l_int|4
comma
id|data
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|read_fifo_ipac
id|read_fifo_ipac
c_func
(paren
r_int
r_int
id|adr
comma
id|u_short
id|off
comma
id|u_char
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
id|adr
comma
id|off
)paren
suffix:semicolon
id|insb
c_func
(paren
id|adr
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
r_void
DECL|function|write_fifo_ipac
id|write_fifo_ipac
c_func
(paren
r_int
r_int
id|adr
comma
id|u_short
id|off
comma
id|u_char
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
id|adr
comma
id|off
)paren
suffix:semicolon
id|outsb
c_func
(paren
id|adr
op_plus
l_int|4
comma
id|data
comma
id|size
)paren
suffix:semicolon
)brace
multiline_comment|/* Interface functions */
r_static
id|u_char
DECL|function|ReadISAC
id|ReadISAC
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u_char
id|offset
)paren
(brace
id|u_short
id|off2
op_assign
id|offset
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
id|off2
op_assign
(paren
(paren
id|off2
op_lshift
l_int|8
op_amp
l_int|0xf000
)paren
op_or
(paren
id|off2
op_amp
l_int|0xf
)paren
)paren
suffix:semicolon
r_case
id|R685
suffix:colon
r_return
(paren
id|readreg
c_func
(paren
id|cs-&gt;hw.gazel.isac
comma
id|off2
)paren
)paren
suffix:semicolon
r_case
id|R753
suffix:colon
r_case
id|R742
suffix:colon
r_return
(paren
id|readreg_ipac
c_func
(paren
id|cs-&gt;hw.gazel.ipac
comma
l_int|0x80
op_plus
id|off2
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|WriteISAC
id|WriteISAC
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u_char
id|offset
comma
id|u_char
id|value
)paren
(brace
id|u_short
id|off2
op_assign
id|offset
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
id|off2
op_assign
(paren
(paren
id|off2
op_lshift
l_int|8
op_amp
l_int|0xf000
)paren
op_or
(paren
id|off2
op_amp
l_int|0xf
)paren
)paren
suffix:semicolon
r_case
id|R685
suffix:colon
id|writereg
c_func
(paren
id|cs-&gt;hw.gazel.isac
comma
id|off2
comma
id|value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R753
suffix:colon
r_case
id|R742
suffix:colon
id|writereg_ipac
c_func
(paren
id|cs-&gt;hw.gazel.ipac
comma
l_int|0x80
op_plus
id|off2
comma
id|value
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|ReadISACfifo
id|ReadISACfifo
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u_char
op_star
id|data
comma
r_int
id|size
)paren
(brace
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
r_break
suffix:semicolon
r_case
id|R753
suffix:colon
r_case
id|R742
suffix:colon
id|read_fifo_ipac
c_func
(paren
id|cs-&gt;hw.gazel.ipac
comma
l_int|0x80
comma
id|data
comma
id|size
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|WriteISACfifo
id|WriteISACfifo
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u_char
op_star
id|data
comma
r_int
id|size
)paren
(brace
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
r_break
suffix:semicolon
r_case
id|R753
suffix:colon
r_case
id|R742
suffix:colon
id|write_fifo_ipac
c_func
(paren
id|cs-&gt;hw.gazel.ipac
comma
l_int|0x80
comma
id|data
comma
id|size
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|ReadHSCXfifo
id|ReadHSCXfifo
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
id|u_char
op_star
id|data
comma
r_int
id|size
)paren
(brace
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
r_break
suffix:semicolon
r_case
id|R753
suffix:colon
r_case
id|R742
suffix:colon
id|read_fifo_ipac
c_func
(paren
id|cs-&gt;hw.gazel.ipac
comma
id|hscx
op_star
l_int|0x40
comma
id|data
comma
id|size
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|WriteHSCXfifo
id|WriteHSCXfifo
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
id|u_char
op_star
id|data
comma
r_int
id|size
)paren
(brace
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
r_break
suffix:semicolon
r_case
id|R753
suffix:colon
r_case
id|R742
suffix:colon
id|write_fifo_ipac
c_func
(paren
id|cs-&gt;hw.gazel.ipac
comma
id|hscx
op_star
l_int|0x40
comma
id|data
comma
id|size
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_static
id|u_char
DECL|function|ReadHSCX
id|ReadHSCX
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
id|u_char
id|offset
)paren
(brace
id|u_short
id|off2
op_assign
id|offset
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
id|off2
op_assign
(paren
(paren
id|off2
op_lshift
l_int|8
op_amp
l_int|0xf000
)paren
op_or
(paren
id|off2
op_amp
l_int|0xf
)paren
)paren
suffix:semicolon
r_case
id|R685
suffix:colon
r_return
(paren
id|readreg
c_func
(paren
id|cs-&gt;hw.gazel.hscx
(braket
id|hscx
)braket
comma
id|off2
)paren
)paren
suffix:semicolon
r_case
id|R753
suffix:colon
r_case
id|R742
suffix:colon
r_return
(paren
id|readreg_ipac
c_func
(paren
id|cs-&gt;hw.gazel.ipac
comma
id|hscx
op_star
l_int|0x40
op_plus
id|off2
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|WriteHSCX
id|WriteHSCX
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
id|u_char
id|offset
comma
id|u_char
id|value
)paren
(brace
id|u_short
id|off2
op_assign
id|offset
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
id|off2
op_assign
(paren
(paren
id|off2
op_lshift
l_int|8
op_amp
l_int|0xf000
)paren
op_or
(paren
id|off2
op_amp
l_int|0xf
)paren
)paren
suffix:semicolon
r_case
id|R685
suffix:colon
id|writereg
c_func
(paren
id|cs-&gt;hw.gazel.hscx
(braket
id|hscx
)braket
comma
id|off2
comma
id|value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R753
suffix:colon
r_case
id|R742
suffix:colon
id|writereg_ipac
c_func
(paren
id|cs-&gt;hw.gazel.ipac
comma
id|hscx
op_star
l_int|0x40
op_plus
id|off2
comma
id|value
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * fast interrupt HSCX stuff goes here&n; */
DECL|macro|READHSCX
mdefine_line|#define READHSCX(cs, nr, reg) ReadHSCX(cs, nr, reg)
DECL|macro|WRITEHSCX
mdefine_line|#define WRITEHSCX(cs, nr, reg, data) WriteHSCX(cs, nr, reg, data)
DECL|macro|READHSCXFIFO
mdefine_line|#define READHSCXFIFO(cs, nr, ptr, cnt) ReadHSCXfifo(cs, nr, ptr, cnt)
DECL|macro|WRITEHSCXFIFO
mdefine_line|#define WRITEHSCXFIFO(cs, nr, ptr, cnt) WriteHSCXfifo(cs, nr, ptr, cnt)
macro_line|#include &quot;hscx_irq.c&quot;
r_static
r_void
DECL|function|gazel_interrupt
id|gazel_interrupt
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
DECL|macro|MAXCOUNT
mdefine_line|#define MAXCOUNT 5
r_struct
id|IsdnCardState
op_star
id|cs
op_assign
id|dev_id
suffix:semicolon
id|u_char
id|valisac
comma
id|valhscx
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cs
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Gazel: Spurious interrupt!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_do
(brace
id|valhscx
op_assign
id|ReadHSCX
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
id|valhscx
)paren
id|hscx_int_main
c_func
(paren
id|cs
comma
id|valhscx
)paren
suffix:semicolon
id|valisac
op_assign
id|ReadISAC
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
id|valisac
)paren
id|isac_interrupt
c_func
(paren
id|cs
comma
id|valisac
)paren
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|valhscx
op_logical_or
id|valisac
)paren
op_logical_and
(paren
id|count
OL
id|MAXCOUNT
)paren
)paren
suffix:semicolon
id|WriteHSCX
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
id|WriteHSCX
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
id|WriteISAC
c_func
(paren
id|cs
comma
id|ISAC_MASK
comma
l_int|0xFF
)paren
suffix:semicolon
id|WriteISAC
c_func
(paren
id|cs
comma
id|ISAC_MASK
comma
l_int|0x0
)paren
suffix:semicolon
id|WriteHSCX
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
id|WriteHSCX
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
)brace
r_static
r_void
DECL|function|gazel_interrupt_ipac
id|gazel_interrupt_ipac
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
id|u_char
id|ista
comma
id|val
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cs
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Gazel: Spurious interrupt!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ista
op_assign
id|ReadISAC
c_func
(paren
id|cs
comma
id|IPAC_ISTA
op_minus
l_int|0x80
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|ista
op_amp
l_int|0x0f
)paren
(brace
id|val
op_assign
id|ReadHSCX
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
id|ista
op_amp
l_int|0x01
)paren
id|val
op_or_assign
l_int|0x01
suffix:semicolon
r_if
c_cond
(paren
id|ista
op_amp
l_int|0x04
)paren
id|val
op_or_assign
l_int|0x02
suffix:semicolon
r_if
c_cond
(paren
id|ista
op_amp
l_int|0x08
)paren
id|val
op_or_assign
l_int|0x04
suffix:semicolon
r_if
c_cond
(paren
id|val
)paren
(brace
id|hscx_int_main
c_func
(paren
id|cs
comma
id|val
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|ista
op_amp
l_int|0x20
)paren
(brace
id|val
op_assign
l_int|0xfe
op_amp
id|ReadISAC
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
(brace
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
r_if
c_cond
(paren
id|ista
op_amp
l_int|0x10
)paren
(brace
id|val
op_assign
l_int|0x01
suffix:semicolon
id|isac_interrupt
c_func
(paren
id|cs
comma
id|val
)paren
suffix:semicolon
)brace
id|ista
op_assign
id|ReadISAC
c_func
(paren
id|cs
comma
id|IPAC_ISTA
op_minus
l_int|0x80
)paren
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|ista
op_amp
l_int|0x3f
)paren
op_logical_and
(paren
id|count
OL
id|MAXCOUNT
)paren
)paren
suffix:semicolon
id|WriteISAC
c_func
(paren
id|cs
comma
id|IPAC_MASK
op_minus
l_int|0x80
comma
l_int|0xFF
)paren
suffix:semicolon
id|WriteISAC
c_func
(paren
id|cs
comma
id|IPAC_MASK
op_minus
l_int|0x80
comma
l_int|0xC0
)paren
suffix:semicolon
)brace
r_void
DECL|function|release_io_gazel
id|release_io_gazel
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
id|i
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0x0000
suffix:semicolon
id|i
OL
l_int|0xC000
suffix:semicolon
id|i
op_add_assign
l_int|0x1000
)paren
id|release_region
c_func
(paren
id|i
op_plus
id|cs-&gt;hw.gazel.hscx
(braket
l_int|0
)braket
comma
l_int|16
)paren
suffix:semicolon
id|release_region
c_func
(paren
l_int|0xC000
op_plus
id|cs-&gt;hw.gazel.hscx
(braket
l_int|0
)braket
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R685
suffix:colon
id|release_region
c_func
(paren
id|cs-&gt;hw.gazel.hscx
(braket
l_int|0
)braket
comma
l_int|0x100
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|cs-&gt;hw.gazel.cfg_reg
comma
l_int|0x80
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R753
suffix:colon
id|release_region
c_func
(paren
id|cs-&gt;hw.gazel.ipac
comma
l_int|0x8
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|cs-&gt;hw.gazel.cfg_reg
comma
l_int|0x80
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R742
suffix:colon
id|release_region
c_func
(paren
id|cs-&gt;hw.gazel.ipac
comma
l_int|8
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|reset_gazel
id|reset_gazel
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
r_int
id|flags
suffix:semicolon
r_int
r_int
id|plxcntrl
comma
id|addr
op_assign
id|cs-&gt;hw.gazel.cfg_reg
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
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|addr
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
id|addr
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
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R685
suffix:colon
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
r_break
suffix:semicolon
r_case
id|R753
suffix:colon
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
id|WriteISAC
c_func
(paren
id|cs
comma
id|IPAC_POTA2
op_minus
l_int|0x80
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
id|WriteISAC
c_func
(paren
id|cs
comma
id|IPAC_POTA2
op_minus
l_int|0x80
comma
l_int|0x00
)paren
suffix:semicolon
id|WriteISAC
c_func
(paren
id|cs
comma
id|IPAC_ACFG
op_minus
l_int|0x80
comma
l_int|0xff
)paren
suffix:semicolon
id|WriteISAC
c_func
(paren
id|cs
comma
id|IPAC_AOE
op_minus
l_int|0x80
comma
l_int|0x0
)paren
suffix:semicolon
id|WriteISAC
c_func
(paren
id|cs
comma
id|IPAC_MASK
op_minus
l_int|0x80
comma
l_int|0xff
)paren
suffix:semicolon
id|WriteISAC
c_func
(paren
id|cs
comma
id|IPAC_CONF
op_minus
l_int|0x80
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
id|WriteISAC
c_func
(paren
id|cs
comma
id|IPAC_MASK
op_minus
l_int|0x80
comma
l_int|0xc0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R742
suffix:colon
id|WriteISAC
c_func
(paren
id|cs
comma
id|IPAC_POTA2
op_minus
l_int|0x80
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
id|WriteISAC
c_func
(paren
id|cs
comma
id|IPAC_POTA2
op_minus
l_int|0x80
comma
l_int|0x00
)paren
suffix:semicolon
id|WriteISAC
c_func
(paren
id|cs
comma
id|IPAC_ACFG
op_minus
l_int|0x80
comma
l_int|0xff
)paren
suffix:semicolon
id|WriteISAC
c_func
(paren
id|cs
comma
id|IPAC_AOE
op_minus
l_int|0x80
comma
l_int|0x0
)paren
suffix:semicolon
id|WriteISAC
c_func
(paren
id|cs
comma
id|IPAC_MASK
op_minus
l_int|0x80
comma
l_int|0xff
)paren
suffix:semicolon
id|WriteISAC
c_func
(paren
id|cs
comma
id|IPAC_CONF
op_minus
l_int|0x80
comma
l_int|0x1
)paren
suffix:semicolon
id|WriteISAC
c_func
(paren
id|cs
comma
id|IPAC_MASK
op_minus
l_int|0x80
comma
l_int|0xc0
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|Gazel_card_msg
id|Gazel_card_msg
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
id|reset_gazel
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
r_case
id|CARD_RELEASE
suffix:colon
id|release_io_gazel
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
r_case
id|CARD_INIT
suffix:colon
id|inithscxisac
c_func
(paren
id|cs
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cs-&gt;subtyp
op_eq
id|R647
)paren
op_logical_or
(paren
id|cs-&gt;subtyp
op_eq
id|R685
)paren
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
(paren
l_int|2
op_plus
id|MAX_WAITING_CALLS
)paren
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
)brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
r_case
id|CARD_TEST
suffix:colon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|reserve_regions
id|reserve_regions
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
r_int
r_int
id|i
comma
id|base
op_assign
l_int|0
comma
id|adr
op_assign
l_int|0
comma
id|len
op_assign
l_int|0
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
l_int|0x0000
suffix:semicolon
id|i
OL
l_int|0xC000
suffix:semicolon
id|i
op_add_assign
l_int|0x1000
)paren
(brace
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|adr
op_assign
(paren
id|i
op_plus
id|base
)paren
comma
id|len
op_assign
l_int|16
)paren
)paren
r_goto
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|adr
op_assign
(paren
l_int|0xC000
op_plus
id|base
)paren
comma
id|len
op_assign
l_int|1
)paren
)paren
r_goto
id|error
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0x0000
suffix:semicolon
id|i
OL
l_int|0xC000
suffix:semicolon
id|i
op_add_assign
l_int|0x1000
)paren
id|request_region
c_func
(paren
id|i
op_plus
id|base
comma
l_int|16
comma
l_string|&quot;gazel&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0xC000
op_plus
id|base
comma
l_int|1
comma
l_string|&quot;gazel&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R685
suffix:colon
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|adr
op_assign
id|cs-&gt;hw.gazel.hscx
(braket
l_int|0
)braket
comma
id|len
op_assign
l_int|0x100
)paren
)paren
r_goto
id|error
suffix:semicolon
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|adr
op_assign
id|cs-&gt;hw.gazel.cfg_reg
comma
id|len
op_assign
l_int|0x80
)paren
)paren
r_goto
id|error
suffix:semicolon
id|request_region
c_func
(paren
id|cs-&gt;hw.gazel.hscx
(braket
l_int|0
)braket
comma
l_int|0x100
comma
l_string|&quot;gazel&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
id|cs-&gt;hw.gazel.cfg_reg
comma
l_int|0x80
comma
l_string|&quot;gazel&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R753
suffix:colon
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|adr
op_assign
id|cs-&gt;hw.gazel.ipac
comma
id|len
op_assign
l_int|0x8
)paren
)paren
r_goto
id|error
suffix:semicolon
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|adr
op_assign
id|cs-&gt;hw.gazel.cfg_reg
comma
id|len
op_assign
l_int|0x80
)paren
)paren
r_goto
id|error
suffix:semicolon
id|request_region
c_func
(paren
id|cs-&gt;hw.gazel.ipac
comma
l_int|0x8
comma
l_string|&quot;gazel&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
id|cs-&gt;hw.gazel.cfg_reg
comma
l_int|0x80
comma
l_string|&quot;gazel&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R742
suffix:colon
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|adr
op_assign
id|cs-&gt;hw.gazel.ipac
comma
id|len
op_assign
l_int|0x8
)paren
)paren
r_goto
id|error
suffix:semicolon
id|request_region
c_func
(paren
id|cs-&gt;hw.gazel.ipac
comma
l_int|0x8
comma
l_string|&quot;gazel&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|error
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Gazel: %s io ports 0x%x-0x%x already in use&bslash;n&quot;
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
id|len
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|readreg_ipac
c_func
(paren
id|card-&gt;para
(braket
l_int|1
)braket
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
id|cs-&gt;hw.gazel.ipac
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
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
r_break
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
id|test_and_set_bit
c_func
(paren
id|HW_IPAC
comma
op_amp
id|cs-&gt;HW_Flags
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
r_break
suffix:semicolon
)brace
r_return
(paren
l_int|0
)paren
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
id|u_char
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
(paren
l_int|1
)paren
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
l_int|1
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
r_break
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
id|test_and_set_bit
c_func
(paren
id|HW_IPAC
comma
op_amp
id|cs-&gt;HW_Flags
)paren
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
r_break
suffix:semicolon
)brace
r_return
(paren
l_int|0
)paren
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
id|u_char
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
id|cs-&gt;typ
op_ne
id|ISDN_CTYPE_GAZEL
)paren
r_return
(paren
l_int|0
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
macro_line|#if CONFIG_PCI
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
macro_line|#else
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Gazel: Card PCI requested and NO_PCI_BIOS, unable to config&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* CONFIG_PCI */
)brace
r_if
c_cond
(paren
id|reserve_regions
c_func
(paren
id|card
comma
id|cs
)paren
)paren
(brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|reset_gazel
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
l_string|&quot;Gazel: wrong IRQ&bslash;n&quot;
)paren
suffix:semicolon
id|release_io_gazel
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
id|cs-&gt;readisac
op_assign
op_amp
id|ReadISAC
suffix:semicolon
id|cs-&gt;writeisac
op_assign
op_amp
id|WriteISAC
suffix:semicolon
id|cs-&gt;readisacfifo
op_assign
op_amp
id|ReadISACfifo
suffix:semicolon
id|cs-&gt;writeisacfifo
op_assign
op_amp
id|WriteISACfifo
suffix:semicolon
id|cs-&gt;BC_Read_Reg
op_assign
op_amp
id|ReadHSCX
suffix:semicolon
id|cs-&gt;BC_Write_Reg
op_assign
op_amp
id|WriteHSCX
suffix:semicolon
id|cs-&gt;BC_Send_Data
op_assign
op_amp
id|hscx_fill_fifo
suffix:semicolon
id|cs-&gt;cardmsg
op_assign
op_amp
id|Gazel_card_msg
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
r_case
id|R685
suffix:colon
id|cs-&gt;irq_func
op_assign
op_amp
id|gazel_interrupt
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
id|release_io_gazel
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
id|cs-&gt;irq_func
op_assign
op_amp
id|gazel_interrupt_ipac
suffix:semicolon
id|val
op_assign
id|ReadISAC
c_func
(paren
id|cs
comma
id|IPAC_ID
op_minus
l_int|0x80
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
(paren
l_int|1
)paren
suffix:semicolon
)brace
eof
