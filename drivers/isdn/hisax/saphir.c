multiline_comment|/* $Id: saphir.c,v 1.8.6.2 2001/09/23 22:24:51 kai Exp $&n; *&n; * low level stuff for HST Saphir 1&n; *&n; * Author       Karsten Keil&n; * Copyright    by Karsten Keil      &lt;keil@isdn4linux.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; * Thanks to    HST High Soft Tech GmbH&n; *&n; */
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
DECL|variable|saphir_rev
r_static
r_char
op_star
id|saphir_rev
op_assign
l_string|&quot;$Revision: 1.8.6.2 $&quot;
suffix:semicolon
DECL|variable|saphir_lock
r_static
id|spinlock_t
id|saphir_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|macro|byteout
mdefine_line|#define byteout(addr,val) outb(val,addr)
DECL|macro|bytein
mdefine_line|#define bytein(addr) inb(addr)
DECL|macro|ISAC_DATA
mdefine_line|#define ISAC_DATA&t;0
DECL|macro|HSCX_DATA
mdefine_line|#define HSCX_DATA&t;1
DECL|macro|ADDRESS_REG
mdefine_line|#define ADDRESS_REG&t;2
DECL|macro|IRQ_REG
mdefine_line|#define IRQ_REG&t;&t;3
DECL|macro|SPARE_REG
mdefine_line|#define SPARE_REG&t;4
DECL|macro|RESET_REG
mdefine_line|#define RESET_REG&t;5
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
id|saphir_lock
comma
id|flags
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.saphir.ale
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
id|saphir_lock
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
id|saphir_lock
comma
id|flags
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.saphir.ale
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
id|saphir_lock
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
id|byteout
c_func
(paren
id|cs-&gt;hw.saphir.ale
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
id|byteout
c_func
(paren
id|cs-&gt;hw.saphir.ale
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
id|cs
comma
id|cs-&gt;hw.saphir.isac
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
id|cs
comma
id|cs-&gt;hw.saphir.isac
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
id|readfifo
c_func
(paren
id|cs
comma
id|cs-&gt;hw.saphir.isac
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
id|cs-&gt;hw.saphir.isac
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
id|readreg
c_func
(paren
id|cs
comma
id|cs-&gt;hw.saphir.hscx
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
id|cs
comma
id|cs-&gt;hw.saphir.hscx
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
id|readfifo
c_func
(paren
id|cs
comma
id|cs-&gt;hw.saphir.hscx
comma
id|hscx
ques
c_cond
l_int|0x40
suffix:colon
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
id|cs-&gt;hw.saphir.hscx
comma
id|hscx
ques
c_cond
l_int|0x40
suffix:colon
l_int|0
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
DECL|function|saphir_interrupt
id|saphir_interrupt
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
multiline_comment|/* Watchdog */
r_if
c_cond
(paren
id|cs-&gt;hw.saphir.timer.function
)paren
id|mod_timer
c_func
(paren
op_amp
id|cs-&gt;hw.saphir.timer
comma
id|jiffies
op_plus
l_int|1
op_star
id|HZ
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;saphir: Spurious timer!&bslash;n&quot;
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
DECL|function|SaphirWatchDog
id|SaphirWatchDog
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
multiline_comment|/* 5 sec WatchDog, so read at least every 4 sec */
id|isac_read
c_func
(paren
id|cs
comma
id|ISAC_RBCH
)paren
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|cs-&gt;hw.saphir.timer
comma
id|jiffies
op_plus
l_int|1
op_star
id|HZ
)paren
suffix:semicolon
)brace
r_void
DECL|function|release_io_saphir
id|release_io_saphir
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
id|cs-&gt;hw.saphir.cfg_reg
op_plus
id|IRQ_REG
comma
l_int|0xff
)paren
suffix:semicolon
id|del_timer_sync
c_func
(paren
op_amp
id|cs-&gt;hw.saphir.timer
)paren
suffix:semicolon
id|cs-&gt;hw.saphir.timer.function
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;hw.saphir.cfg_reg
)paren
id|release_region
c_func
(paren
id|cs-&gt;hw.saphir.cfg_reg
comma
l_int|6
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|saphir_reset
id|saphir_reset
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
id|u8
id|irq_val
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
id|irq_val
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|irq_val
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|11
suffix:colon
id|irq_val
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|12
suffix:colon
id|irq_val
op_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|15
suffix:colon
id|irq_val
op_assign
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: saphir wrong IRQ %d&bslash;n&quot;
comma
id|cs-&gt;irq
)paren
suffix:semicolon
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|byteout
c_func
(paren
id|cs-&gt;hw.saphir.cfg_reg
op_plus
id|IRQ_REG
comma
id|irq_val
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.saphir.cfg_reg
op_plus
id|RESET_REG
comma
l_int|1
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
l_int|30
op_star
id|HZ
)paren
op_div
l_int|1000
)paren
suffix:semicolon
multiline_comment|/* Timeout 30ms */
id|byteout
c_func
(paren
id|cs-&gt;hw.saphir.cfg_reg
op_plus
id|RESET_REG
comma
l_int|0
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
l_int|30
op_star
id|HZ
)paren
op_div
l_int|1000
)paren
suffix:semicolon
multiline_comment|/* Timeout 30ms */
id|byteout
c_func
(paren
id|cs-&gt;hw.saphir.cfg_reg
op_plus
id|IRQ_REG
comma
id|irq_val
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.saphir.cfg_reg
op_plus
id|SPARE_REG
comma
l_int|0x02
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|saphir_card_msg
id|saphir_card_msg
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
id|saphir_reset
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
id|release_io_saphir
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
r_int
id|__init
DECL|function|setup_saphir
id|setup_saphir
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
id|saphir_rev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: HST Saphir driver Rev. %s&bslash;n&quot;
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
id|ISDN_CTYPE_HSTSAPHIR
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* IO-Ports */
id|cs-&gt;hw.saphir.cfg_reg
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
suffix:semicolon
id|cs-&gt;hw.saphir.isac
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
op_plus
id|ISAC_DATA
suffix:semicolon
id|cs-&gt;hw.saphir.hscx
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
op_plus
id|HSCX_DATA
suffix:semicolon
id|cs-&gt;hw.saphir.ale
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
op_plus
id|ADDRESS_REG
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
id|cs-&gt;hw.saphir.cfg_reg
)paren
comma
l_int|6
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
id|cs-&gt;hw.saphir.cfg_reg
comma
id|cs-&gt;hw.saphir.cfg_reg
op_plus
l_int|5
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_else
id|request_region
c_func
(paren
id|cs-&gt;hw.saphir.cfg_reg
comma
l_int|6
comma
l_string|&quot;saphir&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: %s config irq:%d io:0x%X&bslash;n&quot;
comma
id|CardType
(braket
id|cs-&gt;typ
)braket
comma
id|cs-&gt;irq
comma
id|cs-&gt;hw.saphir.cfg_reg
)paren
suffix:semicolon
id|cs-&gt;hw.saphir.timer.function
op_assign
(paren
r_void
op_star
)paren
id|SaphirWatchDog
suffix:semicolon
id|cs-&gt;hw.saphir.timer.data
op_assign
(paren
r_int
)paren
id|cs
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|cs-&gt;hw.saphir.timer
)paren
suffix:semicolon
id|cs-&gt;hw.saphir.timer.expires
op_assign
id|jiffies
op_plus
l_int|4
op_star
id|HZ
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|cs-&gt;hw.saphir.timer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|saphir_reset
c_func
(paren
id|cs
)paren
)paren
(brace
id|release_io_saphir
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
id|saphir_card_msg
suffix:semicolon
id|cs-&gt;irq_func
op_assign
op_amp
id|saphir_interrupt
suffix:semicolon
id|ISACVersion
c_func
(paren
id|cs
comma
l_string|&quot;saphir:&quot;
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
l_string|&quot;saphir:&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;saphir: wrong HSCX versions check IO address&bslash;n&quot;
)paren
suffix:semicolon
id|release_io_saphir
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
