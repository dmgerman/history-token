multiline_comment|/* $Id: teleint.c,v 1.14.6.2 2001/09/23 22:24:52 kai Exp $&n; *&n; * low level stuff for TeleInt isdn cards&n; *&n; * Author       Karsten Keil&n; * Copyright    by Karsten Keil      &lt;keil@isdn4linux.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;hisax.h&quot;
macro_line|#include &quot;isac.h&quot;
macro_line|#include &quot;hfc_2bs0.h&quot;
macro_line|#include &quot;isdnl1.h&quot;
r_extern
r_const
r_char
op_star
id|CardType
(braket
)braket
suffix:semicolon
DECL|variable|TeleInt_revision
r_const
r_char
op_star
id|TeleInt_revision
op_assign
l_string|&quot;$Revision: 1.14.6.2 $&quot;
suffix:semicolon
DECL|variable|teleint_lock
r_static
id|spinlock_t
id|teleint_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
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
id|ale
comma
r_int
r_int
id|adr
comma
id|u_char
id|off
)paren
(brace
r_register
id|u_char
id|ret
suffix:semicolon
r_int
id|max_delay
op_assign
l_int|2000
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|teleint_lock
comma
id|flags
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|ale
comma
id|off
)paren
suffix:semicolon
id|ret
op_assign
id|HFC_BUSY
op_amp
id|bytein
c_func
(paren
id|ale
)paren
suffix:semicolon
r_while
c_loop
(paren
id|ret
op_logical_and
op_decrement
id|max_delay
)paren
id|ret
op_assign
id|HFC_BUSY
op_amp
id|bytein
c_func
(paren
id|ale
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|max_delay
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;TeleInt Busy not inactive&bslash;n&quot;
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|teleint_lock
comma
id|flags
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
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
id|teleint_lock
comma
id|flags
)paren
suffix:semicolon
r_return
(paren
id|ret
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
r_int
r_int
id|ale
comma
r_int
r_int
id|adr
comma
id|u_char
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
r_register
id|u_char
id|ret
suffix:semicolon
r_register
r_int
id|max_delay
op_assign
l_int|20000
suffix:semicolon
r_register
r_int
id|i
suffix:semicolon
id|byteout
c_func
(paren
id|ale
comma
id|off
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
id|ret
op_assign
id|HFC_BUSY
op_amp
id|bytein
c_func
(paren
id|ale
)paren
suffix:semicolon
r_while
c_loop
(paren
id|ret
op_logical_and
op_decrement
id|max_delay
)paren
id|ret
op_assign
id|HFC_BUSY
op_amp
id|bytein
c_func
(paren
id|ale
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|max_delay
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;TeleInt Busy not inactive&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|data
(braket
id|i
)braket
op_assign
id|bytein
c_func
(paren
id|adr
)paren
suffix:semicolon
)brace
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
id|ale
comma
r_int
r_int
id|adr
comma
id|u_char
id|off
comma
id|u_char
id|data
)paren
(brace
r_register
id|u_char
id|ret
suffix:semicolon
r_int
id|max_delay
op_assign
l_int|2000
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|teleint_lock
comma
id|flags
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|ale
comma
id|off
)paren
suffix:semicolon
id|ret
op_assign
id|HFC_BUSY
op_amp
id|bytein
c_func
(paren
id|ale
)paren
suffix:semicolon
r_while
c_loop
(paren
id|ret
op_logical_and
op_decrement
id|max_delay
)paren
id|ret
op_assign
id|HFC_BUSY
op_amp
id|bytein
c_func
(paren
id|ale
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|max_delay
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;TeleInt Busy not inactive&bslash;n&quot;
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|teleint_lock
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
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
id|teleint_lock
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
r_int
r_int
id|ale
comma
r_int
r_int
id|adr
comma
id|u_char
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
r_register
id|u_char
id|ret
suffix:semicolon
r_register
r_int
id|max_delay
op_assign
l_int|20000
suffix:semicolon
r_register
r_int
id|i
suffix:semicolon
multiline_comment|/* fifo write without cli because it&squot;s allready done  */
id|byteout
c_func
(paren
id|ale
comma
id|off
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
id|ret
op_assign
id|HFC_BUSY
op_amp
id|bytein
c_func
(paren
id|ale
)paren
suffix:semicolon
r_while
c_loop
(paren
id|ret
op_logical_and
op_decrement
id|max_delay
)paren
id|ret
op_assign
id|HFC_BUSY
op_amp
id|bytein
c_func
(paren
id|ale
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|max_delay
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;TeleInt Busy not inactive&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|byteout
c_func
(paren
id|adr
comma
id|data
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
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
id|cs-&gt;hw.hfc.cip
op_assign
id|offset
suffix:semicolon
r_return
(paren
id|readreg
c_func
(paren
id|cs-&gt;hw.hfc.addr
op_or
l_int|1
comma
id|cs-&gt;hw.hfc.addr
comma
id|offset
)paren
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
id|cs-&gt;hw.hfc.cip
op_assign
id|offset
suffix:semicolon
id|writereg
c_func
(paren
id|cs-&gt;hw.hfc.addr
op_or
l_int|1
comma
id|cs-&gt;hw.hfc.addr
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
id|cs-&gt;hw.hfc.cip
op_assign
l_int|0
suffix:semicolon
id|readfifo
c_func
(paren
id|cs-&gt;hw.hfc.addr
op_or
l_int|1
comma
id|cs-&gt;hw.hfc.addr
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
id|cs-&gt;hw.hfc.cip
op_assign
l_int|0
suffix:semicolon
id|writefifo
c_func
(paren
id|cs-&gt;hw.hfc.addr
op_or
l_int|1
comma
id|cs-&gt;hw.hfc.addr
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
id|u_char
DECL|function|ReadHFC
id|ReadHFC
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|data
comma
id|u_char
id|reg
)paren
(brace
r_register
id|u_char
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|data
)paren
(brace
id|cs-&gt;hw.hfc.cip
op_assign
id|reg
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.hfc.addr
op_or
l_int|1
comma
id|reg
)paren
suffix:semicolon
id|ret
op_assign
id|bytein
c_func
(paren
id|cs-&gt;hw.hfc.addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_HSCX_FIFO
op_logical_and
(paren
id|data
op_ne
l_int|2
)paren
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;hfc RD %02x %02x&quot;
comma
id|reg
comma
id|ret
)paren
suffix:semicolon
)brace
r_else
id|ret
op_assign
id|bytein
c_func
(paren
id|cs-&gt;hw.hfc.addr
op_or
l_int|1
)paren
suffix:semicolon
r_return
(paren
id|ret
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|WriteHFC
id|WriteHFC
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|data
comma
id|u_char
id|reg
comma
id|u_char
id|value
)paren
(brace
id|byteout
c_func
(paren
id|cs-&gt;hw.hfc.addr
op_or
l_int|1
comma
id|reg
)paren
suffix:semicolon
id|cs-&gt;hw.hfc.cip
op_assign
id|reg
suffix:semicolon
r_if
c_cond
(paren
id|data
)paren
id|byteout
c_func
(paren
id|cs-&gt;hw.hfc.addr
comma
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_HSCX_FIFO
op_logical_and
(paren
id|data
op_ne
l_int|2
)paren
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;hfc W%c %02x %02x&quot;
comma
id|data
ques
c_cond
l_char|&squot;D&squot;
suffix:colon
l_char|&squot;C&squot;
comma
id|reg
comma
id|value
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|TeleInt_interrupt
id|TeleInt_interrupt
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
id|cs-&gt;hw.hfc.addr
op_or
l_int|1
comma
id|cs-&gt;hw.hfc.addr
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
id|cs-&gt;hw.hfc.addr
op_or
l_int|1
comma
id|cs-&gt;hw.hfc.addr
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
id|cs-&gt;hw.hfc.addr
op_or
l_int|1
comma
id|cs-&gt;hw.hfc.addr
comma
id|ISAC_MASK
comma
l_int|0xFF
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|cs-&gt;hw.hfc.addr
op_or
l_int|1
comma
id|cs-&gt;hw.hfc.addr
comma
id|ISAC_MASK
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
DECL|function|TeleInt_Timer
id|TeleInt_Timer
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
r_int
id|stat
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;bcs
(braket
l_int|0
)braket
dot
id|mode
)paren
(brace
id|stat
op_or_assign
l_int|1
suffix:semicolon
id|main_irq_hfc
c_func
(paren
op_amp
id|cs-&gt;bcs
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cs-&gt;bcs
(braket
l_int|1
)braket
dot
id|mode
)paren
(brace
id|stat
op_or_assign
l_int|2
suffix:semicolon
id|main_irq_hfc
c_func
(paren
op_amp
id|cs-&gt;bcs
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
id|cs-&gt;hw.hfc.timer.expires
op_assign
id|jiffies
op_plus
l_int|1
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|cs-&gt;hw.hfc.timer
)paren
suffix:semicolon
)brace
r_void
DECL|function|release_io_TeleInt
id|release_io_TeleInt
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|cs-&gt;hw.hfc.timer
)paren
suffix:semicolon
id|releasehfc
c_func
(paren
id|cs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;hw.hfc.addr
)paren
id|release_region
c_func
(paren
id|cs-&gt;hw.hfc.addr
comma
l_int|2
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|reset_TeleInt
id|reset_TeleInt
c_func
(paren
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
l_string|&quot;TeleInt: resetting card&bslash;n&quot;
)paren
suffix:semicolon
id|cs-&gt;hw.hfc.cirm
op_or_assign
id|HFC_RESET
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.hfc.addr
op_or
l_int|1
comma
id|cs-&gt;hw.hfc.cirm
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
l_int|30
op_star
id|HZ
)paren
op_div
l_int|1000
)paren
suffix:semicolon
id|cs-&gt;hw.hfc.cirm
op_and_assign
op_complement
id|HFC_RESET
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.hfc.addr
op_or
l_int|1
comma
id|cs-&gt;hw.hfc.cirm
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
)brace
r_static
r_int
DECL|function|TeleInt_card_msg
id|TeleInt_card_msg
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
id|reset_TeleInt
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
id|release_io_TeleInt
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
id|inithfc
c_func
(paren
id|cs
)paren
suffix:semicolon
id|initisac
c_func
(paren
id|cs
)paren
suffix:semicolon
id|cs-&gt;hw.hfc.timer.expires
op_assign
id|jiffies
op_plus
l_int|1
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|cs-&gt;hw.hfc.timer
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
DECL|function|setup_TeleInt
id|setup_TeleInt
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
id|TeleInt_revision
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: TeleInt driver Rev. %s&bslash;n&quot;
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
id|ISDN_CTYPE_TELEINT
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
id|cs-&gt;hw.hfc.addr
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
op_amp
l_int|0x3fe
suffix:semicolon
id|cs-&gt;irq
op_assign
id|card-&gt;para
(braket
l_int|0
)braket
suffix:semicolon
id|cs-&gt;hw.hfc.cirm
op_assign
id|HFC_CIRM
suffix:semicolon
id|cs-&gt;hw.hfc.isac_spcr
op_assign
l_int|0x00
suffix:semicolon
id|cs-&gt;hw.hfc.cip
op_assign
l_int|0
suffix:semicolon
id|cs-&gt;hw.hfc.ctmt
op_assign
id|HFC_CTMT
op_or
id|HFC_CLTIMER
suffix:semicolon
id|cs-&gt;bcs
(braket
l_int|0
)braket
dot
id|hw.hfc.send
op_assign
l_int|NULL
suffix:semicolon
id|cs-&gt;bcs
(braket
l_int|1
)braket
dot
id|hw.hfc.send
op_assign
l_int|NULL
suffix:semicolon
id|cs-&gt;hw.hfc.fifosize
op_assign
l_int|7
op_star
l_int|1024
op_plus
l_int|512
suffix:semicolon
id|cs-&gt;hw.hfc.timer.function
op_assign
(paren
r_void
op_star
)paren
id|TeleInt_Timer
suffix:semicolon
id|cs-&gt;hw.hfc.timer.data
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
id|cs-&gt;hw.hfc.timer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|check_region
c_func
(paren
(paren
id|cs-&gt;hw.hfc.addr
)paren
comma
l_int|2
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
id|cs-&gt;hw.hfc.addr
comma
id|cs-&gt;hw.hfc.addr
op_plus
l_int|2
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
id|cs-&gt;hw.hfc.addr
comma
l_int|2
comma
l_string|&quot;TeleInt isdn&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* HW IO = IO */
id|byteout
c_func
(paren
id|cs-&gt;hw.hfc.addr
comma
id|cs-&gt;hw.hfc.addr
op_amp
l_int|0xff
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.hfc.addr
op_or
l_int|1
comma
(paren
(paren
id|cs-&gt;hw.hfc.addr
op_amp
l_int|0x300
)paren
op_rshift
l_int|8
)paren
op_or
l_int|0x54
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cs-&gt;irq
)paren
(brace
r_case
l_int|3
suffix:colon
id|cs-&gt;hw.hfc.cirm
op_or_assign
id|HFC_INTA
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|cs-&gt;hw.hfc.cirm
op_or_assign
id|HFC_INTB
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|cs-&gt;hw.hfc.cirm
op_or_assign
id|HFC_INTC
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
id|cs-&gt;hw.hfc.cirm
op_or_assign
id|HFC_INTD
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|10
suffix:colon
id|cs-&gt;hw.hfc.cirm
op_or_assign
id|HFC_INTE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|11
suffix:colon
id|cs-&gt;hw.hfc.cirm
op_or_assign
id|HFC_INTF
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;TeleInt: wrong IRQ&bslash;n&quot;
)paren
suffix:semicolon
id|release_io_TeleInt
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
id|byteout
c_func
(paren
id|cs-&gt;hw.hfc.addr
op_or
l_int|1
comma
id|cs-&gt;hw.hfc.cirm
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.hfc.addr
op_or
l_int|1
comma
id|cs-&gt;hw.hfc.ctmt
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;TeleInt: defined at 0x%x IRQ %d&bslash;n&quot;
comma
id|cs-&gt;hw.hfc.addr
comma
id|cs-&gt;irq
)paren
suffix:semicolon
id|reset_TeleInt
c_func
(paren
id|cs
)paren
suffix:semicolon
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
id|ReadHFC
suffix:semicolon
id|cs-&gt;BC_Write_Reg
op_assign
op_amp
id|WriteHFC
suffix:semicolon
id|cs-&gt;cardmsg
op_assign
op_amp
id|TeleInt_card_msg
suffix:semicolon
id|cs-&gt;irq_func
op_assign
op_amp
id|TeleInt_interrupt
suffix:semicolon
id|ISACVersion
c_func
(paren
id|cs
comma
l_string|&quot;TeleInt:&quot;
)paren
suffix:semicolon
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
eof
