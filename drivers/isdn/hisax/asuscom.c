multiline_comment|/* $Id: asuscom.c,v 1.11.6.3 2001/09/23 22:24:46 kai Exp $&n; *&n; * low level stuff for ASUSCOM NETWORK INC. ISDNLink cards&n; *&n; * Author       Karsten Keil&n; * Copyright    by Karsten Keil      &lt;keil@isdn4linux.de&gt;&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; * Thanks to  ASUSCOM NETWORK INC. Taiwan and  Dynalink NL for information&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/isapnp.h&gt;
macro_line|#include &quot;hisax.h&quot;
macro_line|#include &quot;isac.h&quot;
macro_line|#include &quot;ipac.h&quot;
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
DECL|variable|Asuscom_revision
r_const
r_char
op_star
id|Asuscom_revision
op_assign
l_string|&quot;$Revision: 1.11.6.3 $&quot;
suffix:semicolon
DECL|variable|asuscom_lock
r_static
id|spinlock_t
id|asuscom_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|macro|byteout
mdefine_line|#define byteout(addr,val) outb(val,addr)
DECL|macro|bytein
mdefine_line|#define bytein(addr) inb(addr)
DECL|macro|ASUS_ISAC
mdefine_line|#define ASUS_ISAC&t;0
DECL|macro|ASUS_HSCX
mdefine_line|#define ASUS_HSCX&t;1
DECL|macro|ASUS_ADR
mdefine_line|#define ASUS_ADR&t;2
DECL|macro|ASUS_CTRL_U7
mdefine_line|#define ASUS_CTRL_U7&t;3
DECL|macro|ASUS_CTRL_POTS
mdefine_line|#define ASUS_CTRL_POTS&t;5
DECL|macro|ASUS_IPAC_ALE
mdefine_line|#define ASUS_IPAC_ALE&t;0
DECL|macro|ASUS_IPAC_DATA
mdefine_line|#define ASUS_IPAC_DATA&t;1
DECL|macro|ASUS_ISACHSCX
mdefine_line|#define ASUS_ISACHSCX&t;1
DECL|macro|ASUS_IPAC
mdefine_line|#define ASUS_IPAC&t;2
multiline_comment|/* CARD_ADR (Write) */
DECL|macro|ASUS_RESET
mdefine_line|#define ASUS_RESET      0x80&t;/* Bit 7 Reset-Leitung */
r_static
r_inline
id|u8
DECL|function|readreg
id|readreg
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
r_int
id|adr
comma
id|u8
id|off
)paren
(brace
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
id|asuscom_lock
comma
id|flags
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.asus.adr
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
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|asuscom_lock
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
DECL|function|readfifo
id|readfifo
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
r_int
id|adr
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
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|asuscom_lock
comma
id|flags
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.asus.adr
comma
id|off
)paren
suffix:semicolon
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
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|asuscom_lock
comma
id|flags
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
r_struct
id|IsdnCardState
op_star
id|cs
comma
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
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|asuscom_lock
comma
id|flags
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.asus.adr
comma
id|off
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|adr
comma
id|data
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|asuscom_lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|writefifo
id|writefifo
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
r_int
id|adr
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
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|asuscom_lock
comma
id|flags
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.asus.adr
comma
id|off
)paren
suffix:semicolon
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
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|asuscom_lock
comma
id|flags
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
r_return
id|readreg
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.isac
comma
id|offset
)paren
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
id|writereg
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.isac
comma
id|offset
comma
id|value
)paren
suffix:semicolon
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
id|readfifo
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.isac
comma
l_int|0
comma
id|data
comma
id|size
)paren
suffix:semicolon
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
id|writefifo
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.isac
comma
l_int|0
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
id|ReadISAC
comma
dot
id|write_reg
op_assign
id|WriteISAC
comma
dot
id|read_fifo
op_assign
id|ReadISACfifo
comma
dot
id|write_fifo
op_assign
id|WriteISACfifo
comma
)brace
suffix:semicolon
r_static
id|u_char
DECL|function|ReadISAC_IPAC
id|ReadISAC_IPAC
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
r_return
id|readreg
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.isac
comma
id|offset
op_or
l_int|0x80
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|WriteISAC_IPAC
id|WriteISAC_IPAC
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
id|writereg
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.isac
comma
id|offset
op_or
l_int|0x80
comma
id|value
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|ReadISACfifo_IPAC
id|ReadISACfifo_IPAC
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
id|readfifo
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.isac
comma
l_int|0x80
comma
id|data
comma
id|size
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|WriteISACfifo_IPAC
id|WriteISACfifo_IPAC
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
id|writefifo
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.isac
comma
l_int|0x80
comma
id|data
comma
id|size
)paren
suffix:semicolon
)brace
DECL|variable|ipac_dc_ops
r_static
r_struct
id|dc_hw_ops
id|ipac_dc_ops
op_assign
(brace
dot
id|read_reg
op_assign
id|ReadISAC_IPAC
comma
dot
id|write_reg
op_assign
id|WriteISAC_IPAC
comma
dot
id|read_fifo
op_assign
id|ReadISACfifo_IPAC
comma
dot
id|write_fifo
op_assign
id|WriteISACfifo_IPAC
comma
)brace
suffix:semicolon
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
r_return
id|readreg
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.hscx
comma
id|offset
op_plus
(paren
id|hscx
ques
c_cond
l_int|0x40
suffix:colon
l_int|0
)paren
)paren
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
id|writereg
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.hscx
comma
id|offset
op_plus
(paren
id|hscx
ques
c_cond
l_int|0x40
suffix:colon
l_int|0
)paren
comma
id|value
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
id|ReadHSCX
comma
dot
id|write_reg
op_assign
id|WriteHSCX
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * fast interrupt HSCX stuff goes here&n; */
DECL|macro|READHSCX
mdefine_line|#define READHSCX(cs, nr, reg) readreg(cs, &bslash;&n;&t;&t;cs-&gt;hw.asus.hscx, reg + (nr ? 0x40 : 0))
DECL|macro|WRITEHSCX
mdefine_line|#define WRITEHSCX(cs, nr, reg, data) writereg(cs, &bslash;&n;&t;&t;cs-&gt;hw.asus.hscx, reg + (nr ? 0x40 : 0), data)
DECL|macro|READHSCXFIFO
mdefine_line|#define READHSCXFIFO(cs, nr, ptr, cnt) readfifo(cs, &bslash;&n;&t;&t;cs-&gt;hw.asus.hscx, (nr ? 0x40 : 0), ptr, cnt)
DECL|macro|WRITEHSCXFIFO
mdefine_line|#define WRITEHSCXFIFO(cs, nr, ptr, cnt) writefifo(cs, &bslash;&n;&t;&t;cs-&gt;hw.asus.hscx, (nr ? 0x40 : 0), ptr, cnt)
macro_line|#include &quot;hscx_irq.c&quot;
r_static
r_void
DECL|function|asuscom_interrupt
id|asuscom_interrupt
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
id|val
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
id|readreg
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.hscx
comma
id|HSCX_ISTA
op_plus
l_int|0x40
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
id|readreg
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.isac
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
id|val
op_assign
id|readreg
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.hscx
comma
id|HSCX_ISTA
op_plus
l_int|0x40
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
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
id|readreg
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.isac
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
id|writereg
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.hscx
comma
id|HSCX_MASK
comma
l_int|0xFF
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.hscx
comma
id|HSCX_MASK
op_plus
l_int|0x40
comma
l_int|0xFF
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.isac
comma
id|ISAC_MASK
comma
l_int|0xFF
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.isac
comma
id|ISAC_MASK
comma
l_int|0x0
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.hscx
comma
id|HSCX_MASK
comma
l_int|0x0
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.hscx
comma
id|HSCX_MASK
op_plus
l_int|0x40
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
DECL|function|asuscom_interrupt_ipac
id|asuscom_interrupt_ipac
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
comma
id|icnt
op_assign
l_int|5
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
l_string|&quot;ISDNLink: Spurious interrupt!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ista
op_assign
id|readreg
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.isac
comma
id|IPAC_ISTA
)paren
suffix:semicolon
id|Start_IPAC
suffix:colon
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_IPAC
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;IPAC ISTA %02X&quot;
comma
id|ista
)paren
suffix:semicolon
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
id|readreg
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.hscx
comma
id|HSCX_ISTA
op_plus
l_int|0x40
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
id|ista
op_amp
l_int|0x20
)paren
(brace
id|val
op_assign
l_int|0xfe
op_amp
id|readreg
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.isac
comma
id|ISAC_ISTA
op_or
l_int|0x80
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
id|readreg
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.isac
comma
id|IPAC_ISTA
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ista
op_amp
l_int|0x3f
)paren
op_logical_and
id|icnt
)paren
(brace
id|icnt
op_decrement
suffix:semicolon
r_goto
id|Start_IPAC
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|icnt
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ASUS IRQ LOOP&bslash;n&quot;
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.isac
comma
id|IPAC_MASK
comma
l_int|0xFF
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.isac
comma
id|IPAC_MASK
comma
l_int|0xC0
)paren
suffix:semicolon
)brace
r_void
DECL|function|release_io_asuscom
id|release_io_asuscom
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
r_int
id|bytecnt
op_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;hw.asus.cfg_reg
)paren
id|release_region
c_func
(paren
id|cs-&gt;hw.asus.cfg_reg
comma
id|bytecnt
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|reset_asuscom
id|reset_asuscom
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
id|cs-&gt;subtyp
op_eq
id|ASUS_IPAC
)paren
id|writereg
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.isac
comma
id|IPAC_POTA2
comma
l_int|0x20
)paren
suffix:semicolon
r_else
id|byteout
c_func
(paren
id|cs-&gt;hw.asus.adr
comma
id|ASUS_RESET
)paren
suffix:semicolon
multiline_comment|/* Reset On */
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
r_if
c_cond
(paren
id|cs-&gt;subtyp
op_eq
id|ASUS_IPAC
)paren
id|writereg
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.isac
comma
id|IPAC_POTA2
comma
l_int|0x0
)paren
suffix:semicolon
r_else
id|byteout
c_func
(paren
id|cs-&gt;hw.asus.adr
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Reset Off */
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
r_if
c_cond
(paren
id|cs-&gt;subtyp
op_eq
id|ASUS_IPAC
)paren
(brace
id|writereg
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.isac
comma
id|IPAC_CONF
comma
l_int|0x0
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.isac
comma
id|IPAC_ACFG
comma
l_int|0xff
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.isac
comma
id|IPAC_AOE
comma
l_int|0x0
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.isac
comma
id|IPAC_MASK
comma
l_int|0xc0
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.isac
comma
id|IPAC_PCFG
comma
l_int|0x12
)paren
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|Asus_card_msg
id|Asus_card_msg
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
id|reset_asuscom
c_func
(paren
id|cs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|CARD_RELEASE
suffix:colon
id|release_io_asuscom
c_func
(paren
id|cs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|CARD_INIT
suffix:colon
id|cs-&gt;debug
op_or_assign
id|L1_DEB_IPAC
suffix:semicolon
id|inithscxisac
c_func
(paren
id|cs
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
macro_line|#ifdef __ISAPNP__
DECL|variable|__initdata
r_static
r_struct
id|isapnp_device_id
id|asus_ids
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;A&squot;
comma
l_char|&squot;S&squot;
comma
l_char|&squot;U&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x1688
)paren
comma
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;A&squot;
comma
l_char|&squot;S&squot;
comma
l_char|&squot;U&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x1688
)paren
comma
(paren
r_int
r_int
)paren
l_string|&quot;Asus1688 PnP&quot;
)brace
comma
(brace
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;A&squot;
comma
l_char|&squot;S&squot;
comma
l_char|&squot;U&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x1690
)paren
comma
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;A&squot;
comma
l_char|&squot;S&squot;
comma
l_char|&squot;U&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x1690
)paren
comma
(paren
r_int
r_int
)paren
l_string|&quot;Asus1690 PnP&quot;
)brace
comma
(brace
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;S&squot;
comma
l_char|&squot;I&squot;
comma
l_char|&squot;E&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x0020
)paren
comma
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;S&squot;
comma
l_char|&squot;I&squot;
comma
l_char|&squot;E&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x0020
)paren
comma
(paren
r_int
r_int
)paren
l_string|&quot;Isurf2 PnP&quot;
)brace
comma
(brace
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;E&squot;
comma
l_char|&squot;L&squot;
comma
l_char|&squot;F&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x0000
)paren
comma
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;E&squot;
comma
l_char|&squot;L&squot;
comma
l_char|&squot;F&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x0000
)paren
comma
(paren
r_int
r_int
)paren
l_string|&quot;Iscas TE320&quot;
)brace
comma
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
DECL|variable|adev
r_static
r_struct
id|isapnp_device_id
op_star
id|adev
op_assign
op_amp
id|asus_ids
(braket
l_int|0
)braket
suffix:semicolon
DECL|variable|__devinitdata
r_static
r_struct
id|pci_bus
op_star
id|pnp_c
id|__devinitdata
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
r_int
id|__init
DECL|function|setup_asuscom
id|setup_asuscom
c_func
(paren
r_struct
id|IsdnCard
op_star
id|card
)paren
(brace
r_int
id|bytecnt
suffix:semicolon
r_struct
id|IsdnCardState
op_star
id|cs
op_assign
id|card-&gt;cs
suffix:semicolon
id|u_char
id|val
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
id|Asuscom_revision
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: Asuscom ISDNLink driver Rev. %s&bslash;n&quot;
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
id|ISDN_CTYPE_ASUSCOM
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#ifdef __ISAPNP__
r_if
c_cond
(paren
op_logical_neg
id|card-&gt;para
(braket
l_int|1
)braket
op_logical_and
id|isapnp_present
c_func
(paren
)paren
)paren
(brace
r_struct
id|pci_bus
op_star
id|pb
suffix:semicolon
r_struct
id|pci_dev
op_star
id|pd
suffix:semicolon
r_while
c_loop
(paren
id|adev-&gt;card_vendor
)paren
(brace
r_if
c_cond
(paren
(paren
id|pb
op_assign
id|isapnp_find_card
c_func
(paren
id|adev-&gt;card_vendor
comma
id|adev-&gt;card_device
comma
id|pnp_c
)paren
)paren
)paren
(brace
id|pnp_c
op_assign
id|pb
suffix:semicolon
id|pd
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pd
op_assign
id|isapnp_find_dev
c_func
(paren
id|pnp_c
comma
id|adev-&gt;vendor
comma
id|adev-&gt;function
comma
id|pd
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: %s detected&bslash;n&quot;
comma
(paren
r_char
op_star
)paren
id|adev-&gt;driver_data
)paren
suffix:semicolon
id|pd
op_member_access_from_pointer
id|prepare
c_func
(paren
id|pd
)paren
suffix:semicolon
id|pd
op_member_access_from_pointer
id|deactivate
c_func
(paren
id|pd
)paren
suffix:semicolon
id|pd
op_member_access_from_pointer
id|activate
c_func
(paren
id|pd
)paren
suffix:semicolon
id|card-&gt;para
(braket
l_int|1
)braket
op_assign
id|pd-&gt;resource
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
id|card-&gt;para
(braket
l_int|0
)braket
op_assign
id|pd-&gt;irq_resource
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card-&gt;para
(braket
l_int|0
)braket
op_logical_or
op_logical_neg
id|card-&gt;para
(braket
l_int|1
)braket
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;AsusPnP:some resources are missing %ld/%lx&bslash;n&quot;
comma
id|card-&gt;para
(braket
l_int|0
)braket
comma
id|card-&gt;para
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|pd
op_member_access_from_pointer
id|deactivate
c_func
(paren
id|pd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;AsusPnP: PnP error card found, no device&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
id|adev
op_increment
suffix:semicolon
id|pnp_c
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|adev-&gt;card_vendor
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;AsusPnP: no ISAPnP card found&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#endif
id|bytecnt
op_assign
l_int|8
suffix:semicolon
id|cs-&gt;hw.asus.cfg_reg
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
id|check_region
c_func
(paren
(paren
id|cs-&gt;hw.asus.cfg_reg
)paren
comma
id|bytecnt
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
id|cs-&gt;hw.asus.cfg_reg
comma
id|cs-&gt;hw.asus.cfg_reg
op_plus
id|bytecnt
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
id|request_region
c_func
(paren
id|cs-&gt;hw.asus.cfg_reg
comma
id|bytecnt
comma
l_string|&quot;asuscom isdn&quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ISDNLink: defined at 0x%x IRQ %d&bslash;n&quot;
comma
id|cs-&gt;hw.asus.cfg_reg
comma
id|cs-&gt;irq
)paren
suffix:semicolon
id|cs-&gt;bc_hw_ops
op_assign
op_amp
id|hscx_ops
suffix:semicolon
id|cs-&gt;BC_Send_Data
op_assign
op_amp
id|hscx_fill_fifo
suffix:semicolon
id|cs-&gt;cardmsg
op_assign
op_amp
id|Asus_card_msg
suffix:semicolon
id|cs-&gt;hw.asus.adr
op_assign
id|cs-&gt;hw.asus.cfg_reg
op_plus
id|ASUS_IPAC_ALE
suffix:semicolon
id|val
op_assign
id|readreg
c_func
(paren
id|cs
comma
id|cs-&gt;hw.asus.cfg_reg
op_plus
id|ASUS_IPAC_DATA
comma
id|IPAC_ID
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|val
op_eq
l_int|1
)paren
op_logical_or
(paren
id|val
op_eq
l_int|2
)paren
)paren
(brace
id|cs-&gt;subtyp
op_assign
id|ASUS_IPAC
suffix:semicolon
id|cs-&gt;hw.asus.isac
op_assign
id|cs-&gt;hw.asus.cfg_reg
op_plus
id|ASUS_IPAC_DATA
suffix:semicolon
id|cs-&gt;hw.asus.hscx
op_assign
id|cs-&gt;hw.asus.cfg_reg
op_plus
id|ASUS_IPAC_DATA
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
id|cs-&gt;dc_hw_ops
op_assign
op_amp
id|ipac_dc_ops
suffix:semicolon
id|cs-&gt;irq_func
op_assign
op_amp
id|asuscom_interrupt_ipac
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Asus: IPAC version %x&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
)brace
r_else
(brace
id|cs-&gt;subtyp
op_assign
id|ASUS_ISACHSCX
suffix:semicolon
id|cs-&gt;hw.asus.adr
op_assign
id|cs-&gt;hw.asus.cfg_reg
op_plus
id|ASUS_ADR
suffix:semicolon
id|cs-&gt;hw.asus.isac
op_assign
id|cs-&gt;hw.asus.cfg_reg
op_plus
id|ASUS_ISAC
suffix:semicolon
id|cs-&gt;hw.asus.hscx
op_assign
id|cs-&gt;hw.asus.cfg_reg
op_plus
id|ASUS_HSCX
suffix:semicolon
id|cs-&gt;hw.asus.u7
op_assign
id|cs-&gt;hw.asus.cfg_reg
op_plus
id|ASUS_CTRL_U7
suffix:semicolon
id|cs-&gt;hw.asus.pots
op_assign
id|cs-&gt;hw.asus.cfg_reg
op_plus
id|ASUS_CTRL_POTS
suffix:semicolon
id|cs-&gt;dc_hw_ops
op_assign
op_amp
id|isac_ops
suffix:semicolon
id|cs-&gt;irq_func
op_assign
op_amp
id|asuscom_interrupt
suffix:semicolon
id|ISACVersion
c_func
(paren
id|cs
comma
l_string|&quot;ISDNLink:&quot;
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
l_string|&quot;ISDNLink:&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ISDNLink: wrong HSCX versions check IO address&bslash;n&quot;
)paren
suffix:semicolon
id|release_io_asuscom
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
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ISDNLink: resetting card&bslash;n&quot;
)paren
suffix:semicolon
id|reset_asuscom
c_func
(paren
id|cs
)paren
suffix:semicolon
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
eof
