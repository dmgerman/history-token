multiline_comment|/* $Id: jade.c,v 1.6.6.3 2001/09/23 22:24:49 kai Exp $&n; *&n; * JADE stuff (derived from original hscx.c)&n; *&n; * Author       Roland Klabunde&n; * Copyright    by Roland Klabunde   &lt;R.Klabunde@Berkom.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;hisax.h&quot;
macro_line|#include &quot;hscx.h&quot;
macro_line|#include &quot;jade.h&quot;
macro_line|#include &quot;isdnl1.h&quot;
macro_line|#include &lt;linux/interrupt.h&gt;
DECL|variable|jade_lock
r_static
id|spinlock_t
id|jade_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
r_int
id|__init
DECL|function|JadeVersion
id|JadeVersion
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
id|ver
comma
id|i
suffix:semicolon
r_int
id|to
op_assign
l_int|50
suffix:semicolon
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
op_minus
l_int|1
comma
l_int|0x50
comma
l_int|0x19
)paren
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|to
)paren
(brace
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|ver
op_assign
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
op_minus
l_int|1
comma
l_int|0x60
)paren
suffix:semicolon
id|to
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|ver
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|to
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s JADE version not obtainable&bslash;n&quot;
comma
id|s
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Wait for the JADE */
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
multiline_comment|/* Read version */
id|ver
op_assign
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
op_minus
l_int|1
comma
l_int|0x60
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s JADE version: %d&bslash;n&quot;
comma
id|s
comma
id|ver
)paren
suffix:semicolon
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* Write to indirect accessible jade register set */
r_static
r_void
DECL|function|jade_write_indirect
id|jade_write_indirect
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u_char
id|reg
comma
id|u_char
id|value
)paren
(brace
r_int
id|to
op_assign
l_int|50
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|u_char
id|ret
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|jade_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Write the data */
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
op_minus
l_int|1
comma
id|COMM_JADE
op_plus
l_int|1
comma
id|value
)paren
suffix:semicolon
multiline_comment|/* Say JADE we wanna write indirect reg &squot;reg&squot; */
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
op_minus
l_int|1
comma
id|COMM_JADE
comma
id|reg
)paren
suffix:semicolon
id|to
op_assign
l_int|50
suffix:semicolon
multiline_comment|/* Wait for RDY goes high */
r_while
c_loop
(paren
id|to
)paren
(brace
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|ret
op_assign
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
op_minus
l_int|1
comma
id|COMM_JADE
)paren
suffix:semicolon
id|to
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_amp
l_int|1
)paren
multiline_comment|/* Got acknowledge */
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|to
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|jade_lock
comma
id|flags
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Can not see ready bit from JADE DSP (reg=0x%X, value=0x%X)&bslash;n&quot;
comma
id|reg
comma
id|value
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|jade_lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_void
DECL|function|modejade
id|modejade
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
id|jade
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
(brace
r_char
id|tmp
(braket
l_int|40
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|tmp
comma
l_string|&quot;jade %c mode %d ichan %d&quot;
comma
l_char|&squot;A&squot;
op_plus
id|jade
comma
id|mode
comma
id|bc
)paren
suffix:semicolon
id|debugl1
c_func
(paren
id|cs
comma
id|tmp
)paren
suffix:semicolon
)brace
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
id|jade
comma
id|jade_HDLC_MODE
comma
(paren
id|mode
op_eq
id|L1_MODE_TRANS
ques
c_cond
id|jadeMODE_TMO
suffix:colon
l_int|0x00
)paren
)paren
suffix:semicolon
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|jade
comma
id|jade_HDLC_CCR0
comma
(paren
id|jadeCCR0_PU
op_or
id|jadeCCR0_ITF
)paren
)paren
suffix:semicolon
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|jade
comma
id|jade_HDLC_CCR1
comma
l_int|0x00
)paren
suffix:semicolon
id|jade_write_indirect
c_func
(paren
id|cs
comma
id|jade_HDLC1SERRXPATH
comma
l_int|0x08
)paren
suffix:semicolon
id|jade_write_indirect
c_func
(paren
id|cs
comma
id|jade_HDLC2SERRXPATH
comma
l_int|0x08
)paren
suffix:semicolon
id|jade_write_indirect
c_func
(paren
id|cs
comma
id|jade_HDLC1SERTXPATH
comma
l_int|0x00
)paren
suffix:semicolon
id|jade_write_indirect
c_func
(paren
id|cs
comma
id|jade_HDLC2SERTXPATH
comma
l_int|0x00
)paren
suffix:semicolon
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|jade
comma
id|jade_HDLC_XCCR
comma
l_int|0x07
)paren
suffix:semicolon
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|jade
comma
id|jade_HDLC_RCCR
comma
l_int|0x07
)paren
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
id|jade
comma
id|jade_HDLC_TSAX
comma
l_int|0x00
)paren
suffix:semicolon
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|jade
comma
id|jade_HDLC_TSAR
comma
l_int|0x00
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
id|jade
comma
id|jade_HDLC_TSAX
comma
l_int|0x04
)paren
suffix:semicolon
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|jade
comma
id|jade_HDLC_TSAR
comma
l_int|0x04
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
id|jade
comma
id|jade_HDLC_MODE
comma
id|jadeMODE_TMO
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
id|jade
comma
id|jade_HDLC_MODE
comma
(paren
id|jadeMODE_TMO
op_or
id|jadeMODE_RAC
op_or
id|jadeMODE_XAC
)paren
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
id|jade
comma
id|jade_HDLC_MODE
comma
(paren
id|jadeMODE_RAC
op_or
id|jadeMODE_XAC
)paren
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
(brace
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|jade
comma
id|jade_HDLC_RCMD
comma
(paren
id|jadeRCMD_RRES
op_or
id|jadeRCMD_RMC
)paren
)paren
suffix:semicolon
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|jade
comma
id|jade_HDLC_XCMD
comma
id|jadeXCMD_XRES
)paren
suffix:semicolon
multiline_comment|/* Unmask ints */
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|jade
comma
id|jade_HDLC_IMR
comma
l_int|0xF8
)paren
suffix:semicolon
)brace
r_else
multiline_comment|/* Mask ints */
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|jade
comma
id|jade_HDLC_IMR
comma
l_int|0x00
)paren
suffix:semicolon
)brace
r_void
DECL|function|jade_sched_event
id|jade_sched_event
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
r_static
r_void
DECL|function|jade_l2l1
id|jade_l2l1
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
id|xmit_data_req_b
c_func
(paren
id|st-&gt;l1.bcs
comma
id|skb
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
l_string|&quot;jade_l2l1: this shouldn&squot;t happen&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
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
id|st-&gt;l1.bcs-&gt;count
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
id|modejade
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
id|modejade
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
DECL|function|close_jadestate
id|close_jadestate
c_func
(paren
r_struct
id|BCState
op_star
id|bcs
)paren
(brace
id|modejade
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
r_static
r_int
DECL|function|open_jadestate
id|open_jadestate
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
DECL|function|setstack_jade
id|setstack_jade
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
id|open_jadestate
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
id|jade_l2l1
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
DECL|function|initjade
id|initjade
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
suffix:semicolon
id|cs-&gt;bcs
(braket
l_int|0
)braket
dot
id|BC_SetStack
op_assign
id|setstack_jade
suffix:semicolon
id|cs-&gt;bcs
(braket
l_int|1
)braket
dot
id|BC_SetStack
op_assign
id|setstack_jade
suffix:semicolon
id|cs-&gt;bcs
(braket
l_int|0
)braket
dot
id|BC_Close
op_assign
id|close_jadestate
suffix:semicolon
id|cs-&gt;bcs
(braket
l_int|1
)braket
dot
id|BC_Close
op_assign
id|close_jadestate
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
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
l_int|0
comma
id|jade_HDLC_IMR
comma
l_int|0x00
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
id|jade_HDLC_IMR
comma
l_int|0x00
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
id|jade_HDLC_ISR
)paren
suffix:semicolon
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;jade B ISTA %x&quot;
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
id|jade_HDLC_ISR
)paren
suffix:semicolon
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;jade A ISTA %x&quot;
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
id|jade_HDLC_STAR
)paren
suffix:semicolon
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;jade B STAR %x&quot;
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
id|jade_HDLC_STAR
)paren
suffix:semicolon
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;jade A STAR %x&quot;
comma
id|val
)paren
suffix:semicolon
multiline_comment|/* Unmask ints */
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
l_int|0
comma
id|jade_HDLC_IMR
comma
l_int|0xF8
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
id|jade_HDLC_IMR
comma
l_int|0xF8
)paren
suffix:semicolon
multiline_comment|/* Stop DSP audio tx/rx */
id|jade_write_indirect
c_func
(paren
id|cs
comma
l_int|0x11
comma
l_int|0x0f
)paren
suffix:semicolon
id|jade_write_indirect
c_func
(paren
id|cs
comma
l_int|0x17
comma
l_int|0x2f
)paren
suffix:semicolon
multiline_comment|/* Transparent Mode, RxTx inactive, No Test, No RFS/TFS */
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
l_int|0
comma
id|jade_HDLC_MODE
comma
id|jadeMODE_TMO
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
id|jade_HDLC_MODE
comma
id|jadeMODE_TMO
)paren
suffix:semicolon
multiline_comment|/* Power down, 1-Idle, RxTx least significant bit first */
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
l_int|0
comma
id|jade_HDLC_CCR0
comma
l_int|0x00
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
id|jade_HDLC_CCR0
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Mask all interrupts */
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
l_int|0
comma
id|jade_HDLC_IMR
comma
l_int|0x00
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
id|jade_HDLC_IMR
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Setup host access to hdlc controller */
id|jade_write_indirect
c_func
(paren
id|cs
comma
id|jade_HDLCCNTRACCESS
comma
(paren
id|jadeINDIRECT_HAH1
op_or
id|jadeINDIRECT_HAH2
)paren
)paren
suffix:semicolon
multiline_comment|/* Unmask HDLC int (don&#xfffd;t forget DSP int later on)*/
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
op_minus
l_int|1
comma
id|jade_INT
comma
(paren
id|jadeINT_HDLC1
op_or
id|jadeINT_HDLC2
)paren
)paren
suffix:semicolon
multiline_comment|/* once again TRANSPARENT */
id|modejade
c_func
(paren
id|cs-&gt;bcs
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|modejade
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
)brace
eof
