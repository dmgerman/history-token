multiline_comment|/* $Id: hscx.c,v 1.21.6.3 2001/09/23 22:24:48 kai Exp $&n; *&n; * HSCX specific routines&n; *&n; * Author       Karsten Keil&n; * Copyright    by Karsten Keil      &lt;keil@isdn4linux.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;hisax.h&quot;
macro_line|#include &quot;hscx.h&quot;
macro_line|#include &quot;isac.h&quot;
macro_line|#include &quot;isdnl1.h&quot;
macro_line|#include &lt;linux/interrupt.h&gt;
DECL|variable|__initdata
r_static
r_char
op_star
id|HSCXVer
(braket
)braket
id|__initdata
op_assign
(brace
l_string|&quot;A1&quot;
comma
l_string|&quot;?1&quot;
comma
l_string|&quot;A2&quot;
comma
l_string|&quot;?3&quot;
comma
l_string|&quot;A3&quot;
comma
l_string|&quot;V2.1&quot;
comma
l_string|&quot;?6&quot;
comma
l_string|&quot;?7&quot;
comma
l_string|&quot;?8&quot;
comma
l_string|&quot;?9&quot;
comma
l_string|&quot;?10&quot;
comma
l_string|&quot;?11&quot;
comma
l_string|&quot;?12&quot;
comma
l_string|&quot;?13&quot;
comma
l_string|&quot;?14&quot;
comma
l_string|&quot;???&quot;
)brace
suffix:semicolon
r_int
id|__init
DECL|function|HscxVersion
id|HscxVersion
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_char
op_star
id|s
)paren
(brace
r_int
id|verA
comma
id|verB
suffix:semicolon
id|verA
op_assign
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
l_int|0
comma
id|HSCX_VSTR
)paren
op_amp
l_int|0xf
suffix:semicolon
id|verB
op_assign
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
l_int|1
comma
id|HSCX_VSTR
)paren
op_amp
l_int|0xf
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s HSCX version A: %s  B: %s&bslash;n&quot;
comma
id|s
comma
id|HSCXVer
(braket
id|verA
)braket
comma
id|HSCXVer
(braket
id|verB
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|verA
op_eq
l_int|0
)paren
op_or
(paren
id|verA
op_eq
l_int|0xf
)paren
op_or
(paren
id|verB
op_eq
l_int|0
)paren
op_or
(paren
id|verB
op_eq
l_int|0xf
)paren
)paren
r_return
(paren
l_int|1
)paren
suffix:semicolon
r_else
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_void
DECL|function|modehscx
id|modehscx
c_func
(paren
r_struct
id|BCState
op_star
id|bcs
comma
r_int
id|mode
comma
r_int
id|bc
)paren
(brace
r_struct
id|IsdnCardState
op_star
id|cs
op_assign
id|bcs-&gt;cs
suffix:semicolon
r_int
id|hscx
op_assign
id|bcs-&gt;hw.hscx.hscx
suffix:semicolon
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
l_string|&quot;hscx %c mode %d ichan %d&quot;
comma
l_char|&squot;A&squot;
op_plus
id|hscx
comma
id|mode
comma
id|bc
)paren
suffix:semicolon
id|bcs-&gt;mode
op_assign
id|mode
suffix:semicolon
id|bcs-&gt;channel
op_assign
id|bc
suffix:semicolon
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|hscx
comma
id|HSCX_XAD1
comma
l_int|0xFF
)paren
suffix:semicolon
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|hscx
comma
id|HSCX_XAD2
comma
l_int|0xFF
)paren
suffix:semicolon
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|hscx
comma
id|HSCX_RAH2
comma
l_int|0xFF
)paren
suffix:semicolon
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|hscx
comma
id|HSCX_XBCH
comma
l_int|0x0
)paren
suffix:semicolon
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|hscx
comma
id|HSCX_RLCR
comma
l_int|0x0
)paren
suffix:semicolon
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|hscx
comma
id|HSCX_CCR1
comma
id|test_bit
c_func
(paren
id|HW_IPAC
comma
op_amp
id|cs-&gt;HW_Flags
)paren
ques
c_cond
l_int|0x82
suffix:colon
l_int|0x85
)paren
suffix:semicolon
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|hscx
comma
id|HSCX_CCR2
comma
l_int|0x30
)paren
suffix:semicolon
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|hscx
comma
id|HSCX_XCCR
comma
l_int|7
)paren
suffix:semicolon
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|hscx
comma
id|HSCX_RCCR
comma
l_int|7
)paren
suffix:semicolon
multiline_comment|/* Switch IOM 1 SSI */
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|HW_IOM1
comma
op_amp
id|cs-&gt;HW_Flags
)paren
op_logical_and
(paren
id|hscx
op_eq
l_int|0
)paren
)paren
id|bc
op_assign
l_int|1
op_minus
id|bc
suffix:semicolon
r_if
c_cond
(paren
id|bc
op_eq
l_int|0
)paren
(brace
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|hscx
comma
id|HSCX_TSAX
comma
id|test_bit
c_func
(paren
id|HW_IOM1
comma
op_amp
id|cs-&gt;HW_Flags
)paren
ques
c_cond
l_int|0x7
suffix:colon
id|bcs-&gt;hw.hscx.tsaxr0
)paren
suffix:semicolon
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|hscx
comma
id|HSCX_TSAR
comma
id|test_bit
c_func
(paren
id|HW_IOM1
comma
op_amp
id|cs-&gt;HW_Flags
)paren
ques
c_cond
l_int|0x7
suffix:colon
id|bcs-&gt;hw.hscx.tsaxr0
)paren
suffix:semicolon
)brace
r_else
(brace
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|hscx
comma
id|HSCX_TSAX
comma
id|bcs-&gt;hw.hscx.tsaxr1
)paren
suffix:semicolon
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|hscx
comma
id|HSCX_TSAR
comma
id|bcs-&gt;hw.hscx.tsaxr1
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
(paren
id|L1_MODE_NULL
)paren
suffix:colon
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|hscx
comma
id|HSCX_TSAX
comma
l_int|0x1f
)paren
suffix:semicolon
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|hscx
comma
id|HSCX_TSAR
comma
l_int|0x1f
)paren
suffix:semicolon
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|hscx
comma
id|HSCX_MODE
comma
l_int|0x84
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|L1_MODE_TRANS
)paren
suffix:colon
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|hscx
comma
id|HSCX_MODE
comma
l_int|0xe4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|L1_MODE_HDLC
)paren
suffix:colon
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|hscx
comma
id|HSCX_CCR1
comma
id|test_bit
c_func
(paren
id|HW_IPAC
comma
op_amp
id|cs-&gt;HW_Flags
)paren
ques
c_cond
l_int|0x8a
suffix:colon
l_int|0x8d
)paren
suffix:semicolon
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|hscx
comma
id|HSCX_MODE
comma
l_int|0x8c
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mode
)paren
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|hscx
comma
id|HSCX_CMDR
comma
l_int|0x41
)paren
suffix:semicolon
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|hscx
comma
id|HSCX_ISTA
comma
l_int|0x00
)paren
suffix:semicolon
)brace
r_void
DECL|function|hscx_sched_event
id|hscx_sched_event
c_func
(paren
r_struct
id|BCState
op_star
id|bcs
comma
r_int
id|event
)paren
(brace
id|bcs-&gt;event
op_or_assign
l_int|1
op_lshift
id|event
suffix:semicolon
id|schedule_work
c_func
(paren
op_amp
id|bcs-&gt;work
)paren
suffix:semicolon
)brace
r_void
DECL|function|hscx_l2l1
id|hscx_l2l1
c_func
(paren
r_struct
id|PStack
op_star
id|st
comma
r_int
id|pr
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
op_assign
id|arg
suffix:semicolon
r_struct
id|IsdnCardState
op_star
id|cs
op_assign
id|st-&gt;l1.bcs-&gt;cs
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_switch
c_cond
(paren
id|pr
)paren
(brace
r_case
(paren
id|PH_DATA
op_or
id|REQUEST
)paren
suffix:colon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|cs-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|st-&gt;l1.bcs-&gt;tx_skb
)paren
(brace
id|skb_queue_tail
c_func
(paren
op_amp
id|st-&gt;l1.bcs-&gt;squeue
comma
id|skb
)paren
suffix:semicolon
)brace
r_else
(brace
id|st-&gt;l1.bcs-&gt;tx_skb
op_assign
id|skb
suffix:semicolon
id|test_and_set_bit
c_func
(paren
id|BC_FLG_BUSY
comma
op_amp
id|st-&gt;l1.bcs-&gt;Flag
)paren
suffix:semicolon
id|st-&gt;l1.bcs-&gt;hw.hscx.count
op_assign
l_int|0
suffix:semicolon
id|st-&gt;l1.bcs-&gt;cs
op_member_access_from_pointer
id|BC_Send_Data
c_func
(paren
id|st-&gt;l1.bcs
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|cs-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|PH_PULL
op_or
id|INDICATION
)paren
suffix:colon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|cs-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|st-&gt;l1.bcs-&gt;tx_skb
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;hscx_l2l1: this shouldn&squot;t happen&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|test_and_set_bit
c_func
(paren
id|BC_FLG_BUSY
comma
op_amp
id|st-&gt;l1.bcs-&gt;Flag
)paren
suffix:semicolon
id|st-&gt;l1.bcs-&gt;tx_skb
op_assign
id|skb
suffix:semicolon
id|st-&gt;l1.bcs-&gt;hw.hscx.count
op_assign
l_int|0
suffix:semicolon
id|st-&gt;l1.bcs-&gt;cs
op_member_access_from_pointer
id|BC_Send_Data
c_func
(paren
id|st-&gt;l1.bcs
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|cs-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|PH_PULL
op_or
id|REQUEST
)paren
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|st-&gt;l1.bcs-&gt;tx_skb
)paren
(brace
id|test_and_clear_bit
c_func
(paren
id|FLG_L1_PULL_REQ
comma
op_amp
id|st-&gt;l1.Flags
)paren
suffix:semicolon
id|L1L2
c_func
(paren
id|st
comma
id|PH_PULL
op_or
id|CONFIRM
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_else
id|test_and_set_bit
c_func
(paren
id|FLG_L1_PULL_REQ
comma
op_amp
id|st-&gt;l1.Flags
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|PH_ACTIVATE
op_or
id|REQUEST
)paren
suffix:colon
id|test_and_set_bit
c_func
(paren
id|BC_FLG_ACTIV
comma
op_amp
id|st-&gt;l1.bcs-&gt;Flag
)paren
suffix:semicolon
id|modehscx
c_func
(paren
id|st-&gt;l1.bcs
comma
id|st-&gt;l1.mode
comma
id|st-&gt;l1.bc
)paren
suffix:semicolon
id|l1_msg_b
c_func
(paren
id|st
comma
id|pr
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|PH_DEACTIVATE
op_or
id|REQUEST
)paren
suffix:colon
id|l1_msg_b
c_func
(paren
id|st
comma
id|pr
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|PH_DEACTIVATE
op_or
id|CONFIRM
)paren
suffix:colon
id|test_and_clear_bit
c_func
(paren
id|BC_FLG_ACTIV
comma
op_amp
id|st-&gt;l1.bcs-&gt;Flag
)paren
suffix:semicolon
id|test_and_clear_bit
c_func
(paren
id|BC_FLG_BUSY
comma
op_amp
id|st-&gt;l1.bcs-&gt;Flag
)paren
suffix:semicolon
id|modehscx
c_func
(paren
id|st-&gt;l1.bcs
comma
l_int|0
comma
id|st-&gt;l1.bc
)paren
suffix:semicolon
id|L1L2
c_func
(paren
id|st
comma
id|PH_DEACTIVATE
op_or
id|CONFIRM
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_void
DECL|function|close_hscxstate
id|close_hscxstate
c_func
(paren
r_struct
id|BCState
op_star
id|bcs
)paren
(brace
id|modehscx
c_func
(paren
id|bcs
comma
l_int|0
comma
id|bcs-&gt;channel
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_and_clear_bit
c_func
(paren
id|BC_FLG_INIT
comma
op_amp
id|bcs-&gt;Flag
)paren
)paren
(brace
r_if
c_cond
(paren
id|bcs-&gt;hw.hscx.rcvbuf
)paren
(brace
id|kfree
c_func
(paren
id|bcs-&gt;hw.hscx.rcvbuf
)paren
suffix:semicolon
id|bcs-&gt;hw.hscx.rcvbuf
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bcs-&gt;blog
)paren
(brace
id|kfree
c_func
(paren
id|bcs-&gt;blog
)paren
suffix:semicolon
id|bcs-&gt;blog
op_assign
l_int|NULL
suffix:semicolon
)brace
id|skb_queue_purge
c_func
(paren
op_amp
id|bcs-&gt;rqueue
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|bcs-&gt;squeue
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|bcs-&gt;cmpl_queue
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bcs-&gt;tx_skb
)paren
(brace
id|dev_kfree_skb_any
c_func
(paren
id|bcs-&gt;tx_skb
)paren
suffix:semicolon
id|bcs-&gt;tx_skb
op_assign
l_int|NULL
suffix:semicolon
id|test_and_clear_bit
c_func
(paren
id|BC_FLG_BUSY
comma
op_amp
id|bcs-&gt;Flag
)paren
suffix:semicolon
)brace
)brace
)brace
r_int
DECL|function|open_hscxstate
id|open_hscxstate
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_struct
id|BCState
op_star
id|bcs
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|test_and_set_bit
c_func
(paren
id|BC_FLG_INIT
comma
op_amp
id|bcs-&gt;Flag
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|bcs-&gt;hw.hscx.rcvbuf
op_assign
id|kmalloc
c_func
(paren
id|HSCX_BUFMAX
comma
id|GFP_ATOMIC
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: No memory for hscx.rcvbuf&bslash;n&quot;
)paren
suffix:semicolon
id|test_and_clear_bit
c_func
(paren
id|BC_FLG_INIT
comma
op_amp
id|bcs-&gt;Flag
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
(paren
id|bcs-&gt;blog
op_assign
id|kmalloc
c_func
(paren
id|MAX_BLOG_SPACE
comma
id|GFP_ATOMIC
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: No memory for bcs-&gt;blog&bslash;n&quot;
)paren
suffix:semicolon
id|test_and_clear_bit
c_func
(paren
id|BC_FLG_INIT
comma
op_amp
id|bcs-&gt;Flag
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|bcs-&gt;hw.hscx.rcvbuf
)paren
suffix:semicolon
id|bcs-&gt;hw.hscx.rcvbuf
op_assign
l_int|NULL
suffix:semicolon
r_return
(paren
l_int|2
)paren
suffix:semicolon
)brace
id|skb_queue_head_init
c_func
(paren
op_amp
id|bcs-&gt;rqueue
)paren
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|bcs-&gt;squeue
)paren
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|bcs-&gt;cmpl_queue
)paren
suffix:semicolon
)brace
id|bcs-&gt;tx_skb
op_assign
l_int|NULL
suffix:semicolon
id|test_and_clear_bit
c_func
(paren
id|BC_FLG_BUSY
comma
op_amp
id|bcs-&gt;Flag
)paren
suffix:semicolon
id|bcs-&gt;event
op_assign
l_int|0
suffix:semicolon
id|bcs-&gt;hw.hscx.rcvidx
op_assign
l_int|0
suffix:semicolon
id|bcs-&gt;tx_cnt
op_assign
l_int|0
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_int
DECL|function|setstack_hscx
id|setstack_hscx
c_func
(paren
r_struct
id|PStack
op_star
id|st
comma
r_struct
id|BCState
op_star
id|bcs
)paren
(brace
id|bcs-&gt;channel
op_assign
id|st-&gt;l1.bc
suffix:semicolon
r_if
c_cond
(paren
id|open_hscxstate
c_func
(paren
id|st-&gt;l1.hardware
comma
id|bcs
)paren
)paren
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
id|st-&gt;l1.bcs
op_assign
id|bcs
suffix:semicolon
id|st-&gt;l1.l2l1
op_assign
id|hscx_l2l1
suffix:semicolon
id|setstack_manager
c_func
(paren
id|st
)paren
suffix:semicolon
id|bcs-&gt;st
op_assign
id|st
suffix:semicolon
id|setstack_l1_B
c_func
(paren
id|st
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|inithscx
id|inithscx
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
r_int
id|val
comma
id|eval
suffix:semicolon
id|cs-&gt;bcs
(braket
l_int|0
)braket
dot
id|BC_SetStack
op_assign
id|setstack_hscx
suffix:semicolon
id|cs-&gt;bcs
(braket
l_int|1
)braket
dot
id|BC_SetStack
op_assign
id|setstack_hscx
suffix:semicolon
id|cs-&gt;bcs
(braket
l_int|0
)braket
dot
id|BC_Close
op_assign
id|close_hscxstate
suffix:semicolon
id|cs-&gt;bcs
(braket
l_int|1
)braket
dot
id|BC_Close
op_assign
id|close_hscxstate
suffix:semicolon
id|cs-&gt;bcs
(braket
l_int|0
)braket
dot
id|hw.hscx.hscx
op_assign
l_int|0
suffix:semicolon
id|cs-&gt;bcs
(braket
l_int|1
)braket
dot
id|hw.hscx.hscx
op_assign
l_int|1
suffix:semicolon
id|cs-&gt;bcs
(braket
l_int|0
)braket
dot
id|hw.hscx.tsaxr0
op_assign
l_int|0x2f
suffix:semicolon
id|cs-&gt;bcs
(braket
l_int|0
)braket
dot
id|hw.hscx.tsaxr1
op_assign
l_int|3
suffix:semicolon
id|cs-&gt;bcs
(braket
l_int|1
)braket
dot
id|hw.hscx.tsaxr0
op_assign
l_int|0x2f
suffix:semicolon
id|cs-&gt;bcs
(braket
l_int|1
)braket
dot
id|hw.hscx.tsaxr1
op_assign
l_int|3
suffix:semicolon
id|val
op_assign
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
l_int|1
comma
id|HSCX_ISTA
)paren
suffix:semicolon
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;HSCX B ISTA %x&quot;
comma
id|val
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
l_int|0x01
)paren
(brace
id|eval
op_assign
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
l_int|1
comma
id|HSCX_EXIR
)paren
suffix:semicolon
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;HSCX B EXIR %x&quot;
comma
id|eval
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|val
op_amp
l_int|0x02
)paren
(brace
id|eval
op_assign
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
l_int|0
comma
id|HSCX_EXIR
)paren
suffix:semicolon
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;HSCX A EXIR %x&quot;
comma
id|eval
)paren
suffix:semicolon
)brace
id|val
op_assign
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
l_int|0
comma
id|HSCX_ISTA
)paren
suffix:semicolon
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;HSCX A ISTA %x&quot;
comma
id|val
)paren
suffix:semicolon
id|val
op_assign
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
l_int|1
comma
id|HSCX_STAR
)paren
suffix:semicolon
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;HSCX B STAR %x&quot;
comma
id|val
)paren
suffix:semicolon
id|val
op_assign
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
l_int|0
comma
id|HSCX_STAR
)paren
suffix:semicolon
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;HSCX A STAR %x&quot;
comma
id|val
)paren
suffix:semicolon
multiline_comment|/* disable all IRQ */
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
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
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
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
id|modehscx
c_func
(paren
id|cs-&gt;bcs
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|modehscx
c_func
(paren
id|cs-&gt;bcs
op_plus
l_int|1
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Reenable all IRQ */
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
l_int|0
comma
id|HSCX_MASK
comma
l_int|0
)paren
suffix:semicolon
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
l_int|1
comma
id|HSCX_MASK
comma
l_int|0
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|inithscxisac
id|inithscxisac
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
id|initisac
c_func
(paren
id|cs
)paren
suffix:semicolon
id|inithscx
c_func
(paren
id|cs
)paren
suffix:semicolon
)brace
eof
