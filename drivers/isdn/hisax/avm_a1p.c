multiline_comment|/* $Id: avm_a1p.c,v 2.7.6.2 2001/09/23 22:24:46 kai Exp $&n; *&n; * low level stuff for the following AVM cards:&n; * A1 PCMCIA&n; * FRITZ!Card PCMCIA&n; * FRITZ!Card PCMCIA 2.0&n; *&n; * Author       Carsten Paeth&n; * Copyright    by Carsten Paeth     &lt;calle@calle.de&gt;&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;hisax.h&quot;
macro_line|#include &quot;isac.h&quot;
macro_line|#include &quot;hscx.h&quot;
macro_line|#include &quot;isdnl1.h&quot;
multiline_comment|/* register offsets */
DECL|macro|ADDRREG_OFFSET
mdefine_line|#define ADDRREG_OFFSET&t;&t;0x02
DECL|macro|DATAREG_OFFSET
mdefine_line|#define DATAREG_OFFSET&t;&t;0x03
DECL|macro|ASL0_OFFSET
mdefine_line|#define ASL0_OFFSET&t;&t;0x04
DECL|macro|ASL1_OFFSET
mdefine_line|#define ASL1_OFFSET&t;&t;0x05
DECL|macro|MODREG_OFFSET
mdefine_line|#define MODREG_OFFSET&t;&t;0x06
DECL|macro|VERREG_OFFSET
mdefine_line|#define VERREG_OFFSET&t;&t;0x07
multiline_comment|/* address offsets */
DECL|macro|ISAC_FIFO_OFFSET
mdefine_line|#define ISAC_FIFO_OFFSET&t;0x00
DECL|macro|ISAC_REG_OFFSET
mdefine_line|#define ISAC_REG_OFFSET&t;&t;0x20
DECL|macro|HSCX_CH_DIFF
mdefine_line|#define HSCX_CH_DIFF&t;&t;0x40
DECL|macro|HSCX_FIFO_OFFSET
mdefine_line|#define HSCX_FIFO_OFFSET&t;0x80
DECL|macro|HSCX_REG_OFFSET
mdefine_line|#define HSCX_REG_OFFSET&t;&t;0xa0
multiline_comment|/* read bits ASL0 */
DECL|macro|ASL0_R_TIMER
mdefine_line|#define&t; ASL0_R_TIMER&t;&t;0x10 /* active low */
DECL|macro|ASL0_R_ISAC
mdefine_line|#define&t; ASL0_R_ISAC&t;&t;0x20 /* active low */
DECL|macro|ASL0_R_HSCX
mdefine_line|#define&t; ASL0_R_HSCX&t;&t;0x40 /* active low */
DECL|macro|ASL0_R_TESTBIT
mdefine_line|#define&t; ASL0_R_TESTBIT&t;&t;0x80
DECL|macro|ASL0_R_IRQPENDING
mdefine_line|#define  ASL0_R_IRQPENDING&t;(ASL0_R_ISAC|ASL0_R_HSCX|ASL0_R_TIMER)
multiline_comment|/* write bits ASL0 */
DECL|macro|ASL0_W_RESET
mdefine_line|#define&t; ASL0_W_RESET&t;&t;0x01
DECL|macro|ASL0_W_TDISABLE
mdefine_line|#define&t; ASL0_W_TDISABLE&t;0x02
DECL|macro|ASL0_W_TRESET
mdefine_line|#define&t; ASL0_W_TRESET&t;&t;0x04
DECL|macro|ASL0_W_IRQENABLE
mdefine_line|#define&t; ASL0_W_IRQENABLE&t;0x08
DECL|macro|ASL0_W_TESTBIT
mdefine_line|#define&t; ASL0_W_TESTBIT&t;&t;0x80
multiline_comment|/* write bits ASL1 */
DECL|macro|ASL1_W_LED0
mdefine_line|#define&t; ASL1_W_LED0&t;&t;0x10
DECL|macro|ASL1_W_LED1
mdefine_line|#define&t; ASL1_W_LED1&t;&t;0x20
DECL|macro|ASL1_W_ENABLE_S0
mdefine_line|#define&t; ASL1_W_ENABLE_S0&t;0xC0
DECL|macro|byteout
mdefine_line|#define byteout(addr,val) outb(val,addr)
DECL|macro|bytein
mdefine_line|#define bytein(addr) inb(addr)
DECL|variable|avm_revision
r_static
r_const
r_char
op_star
id|avm_revision
op_assign
l_string|&quot;$Revision: 2.7.6.2 $&quot;
suffix:semicolon
DECL|variable|avm_a1p_lock
r_static
id|spinlock_t
id|avm_a1p_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
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
id|offset
comma
id|u8
id|adr
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|u8
id|ret
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|avm_a1p_lock
comma
id|flags
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.avm.cfg_reg
op_plus
id|ADDRREG_OFFSET
comma
id|offset
op_plus
id|adr
op_minus
l_int|0x20
)paren
suffix:semicolon
id|ret
op_assign
id|bytein
c_func
(paren
id|cs-&gt;hw.avm.cfg_reg
op_plus
id|DATAREG_OFFSET
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|avm_a1p_lock
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
id|offset
comma
id|u8
id|adr
comma
id|u8
id|value
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
id|avm_a1p_lock
comma
id|flags
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.avm.cfg_reg
op_plus
id|ADDRREG_OFFSET
comma
id|offset
op_plus
id|adr
op_minus
l_int|0x20
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.avm.cfg_reg
op_plus
id|DATAREG_OFFSET
comma
id|value
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|avm_a1p_lock
comma
id|flags
)paren
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
id|offset
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
id|cs-&gt;hw.avm.cfg_reg
op_plus
id|ADDRREG_OFFSET
comma
id|offset
)paren
suffix:semicolon
id|insb
c_func
(paren
id|cs-&gt;hw.avm.cfg_reg
op_plus
id|DATAREG_OFFSET
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
id|offset
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
id|cs-&gt;hw.avm.cfg_reg
op_plus
id|ADDRREG_OFFSET
comma
id|offset
)paren
suffix:semicolon
id|outsb
c_func
(paren
id|cs-&gt;hw.avm.cfg_reg
op_plus
id|DATAREG_OFFSET
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
id|adr
)paren
(brace
r_return
id|readreg
c_func
(paren
id|cs
comma
id|ISAC_REG_OFFSET
comma
id|adr
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
id|adr
comma
id|u8
id|value
)paren
(brace
id|writereg
c_func
(paren
id|cs
comma
id|ISAC_REG_OFFSET
comma
id|adr
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
id|readfifo
c_func
(paren
id|cs
comma
id|ISAC_FIFO_OFFSET
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
id|writefifo
c_func
(paren
id|cs
comma
id|ISAC_FIFO_OFFSET
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
id|adr
)paren
(brace
r_return
id|readreg
c_func
(paren
id|cs
comma
id|HSCX_REG_OFFSET
op_plus
id|hscx
op_star
id|HSCX_CH_DIFF
comma
id|adr
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
id|adr
comma
id|u8
id|value
)paren
(brace
id|writereg
c_func
(paren
id|cs
comma
id|HSCX_REG_OFFSET
op_plus
id|hscx
op_star
id|HSCX_CH_DIFF
comma
id|adr
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
r_return
id|readfifo
c_func
(paren
id|cs
comma
id|HSCX_FIFO_OFFSET
op_plus
id|hscx
op_star
id|HSCX_CH_DIFF
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
id|writefifo
c_func
(paren
id|cs
comma
id|HSCX_FIFO_OFFSET
op_plus
id|hscx
op_star
id|HSCX_CH_DIFF
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
DECL|function|avm_a1p_interrupt
id|avm_a1p_interrupt
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
id|sval
op_assign
(paren
op_complement
id|bytein
c_func
(paren
id|cs-&gt;hw.avm.cfg_reg
op_plus
id|ASL0_OFFSET
)paren
op_amp
id|ASL0_R_IRQPENDING
)paren
)paren
)paren
(brace
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
id|sval
op_amp
id|ASL0_R_HSCX
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
id|sval
op_amp
id|ASL0_R_ISAC
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
r_static
r_void
DECL|function|avm_a1p_init
id|avm_a1p_init
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
op_plus
id|ASL0_OFFSET
comma
id|ASL0_W_TDISABLE
op_or
id|ASL0_W_TRESET
op_or
id|ASL0_W_IRQENABLE
)paren
suffix:semicolon
id|inithscxisac
c_func
(paren
id|cs
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|avm_a1p_reset
id|avm_a1p_reset
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
op_plus
id|ASL0_OFFSET
comma
l_int|0x00
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
op_plus
id|ASL0_OFFSET
comma
id|ASL0_W_RESET
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
op_plus
id|ASL0_OFFSET
comma
l_int|0x00
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|avm_a1p_ops
r_static
r_struct
id|card_ops
id|avm_a1p_ops
op_assign
(brace
dot
id|init
op_assign
id|avm_a1p_init
comma
dot
id|reset
op_assign
id|avm_a1p_reset
comma
dot
id|irq_func
op_assign
id|avm_a1p_interrupt
comma
)brace
suffix:semicolon
r_int
id|__devinit
DECL|function|setup_avm_a1_pcmcia
id|setup_avm_a1_pcmcia
c_func
(paren
r_struct
id|IsdnCard
op_star
id|card
)paren
(brace
id|u8
id|model
comma
id|vers
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
l_string|&quot;HiSax: AVM A1 PCMCIA driver Rev. %s&bslash;n&quot;
comma
id|HiSax_getrev
c_func
(paren
id|tmp
)paren
)paren
suffix:semicolon
id|cs-&gt;hw.avm.cfg_reg
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
id|outb
c_func
(paren
id|cs-&gt;hw.avm.cfg_reg
op_plus
id|ASL1_OFFSET
comma
id|ASL1_W_ENABLE_S0
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.avm.cfg_reg
op_plus
id|ASL0_OFFSET
comma
l_int|0x00
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
op_plus
id|ASL0_OFFSET
comma
id|ASL0_W_RESET
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
op_plus
id|ASL0_OFFSET
comma
l_int|0x00
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.avm.cfg_reg
op_plus
id|ASL0_OFFSET
comma
id|ASL0_W_TDISABLE
op_or
id|ASL0_W_TRESET
)paren
suffix:semicolon
id|model
op_assign
id|bytein
c_func
(paren
id|cs-&gt;hw.avm.cfg_reg
op_plus
id|MODREG_OFFSET
)paren
suffix:semicolon
id|vers
op_assign
id|bytein
c_func
(paren
id|cs-&gt;hw.avm.cfg_reg
op_plus
id|VERREG_OFFSET
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;AVM A1 PCMCIA: io 0x%x irq %d model %d version %d&bslash;n&quot;
comma
id|cs-&gt;hw.avm.cfg_reg
comma
id|cs-&gt;irq
comma
id|model
comma
id|vers
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
id|cs-&gt;card_ops
op_assign
op_amp
id|avm_a1p_ops
suffix:semicolon
id|ISACVersion
c_func
(paren
id|cs
comma
l_string|&quot;AVM A1 PCMCIA:&quot;
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
l_string|&quot;AVM A1 PCMCIA:&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;AVM A1 PCMCIA: wrong HSCX versions check IO address&bslash;n&quot;
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
