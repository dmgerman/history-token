multiline_comment|/* $Id: isdnl3.c,v 2.17.6.5 2001/09/23 22:24:49 kai Exp $&n; *&n; * Author       Karsten Keil&n; *              based on the teles driver from Jan den Ouden&n; * Copyright    by Karsten Keil      &lt;keil@isdn4linux.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; * For changes and modifications please read&n; * ../../../Documentation/isdn/HiSax.cert&n; *&n; * Thanks to    Jan den Ouden&n; *              Fritz Elfert&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;hisax.h&quot;
macro_line|#include &quot;isdnl3.h&quot;
macro_line|#include &lt;linux/config.h&gt;
DECL|variable|l3_revision
r_const
r_char
op_star
id|l3_revision
op_assign
l_string|&quot;$Revision: 2.17.6.5 $&quot;
suffix:semicolon
DECL|variable|l3fsm
r_static
r_struct
id|Fsm
id|l3fsm
suffix:semicolon
r_enum
(brace
DECL|enumerator|ST_L3_LC_REL
id|ST_L3_LC_REL
comma
DECL|enumerator|ST_L3_LC_ESTAB_WAIT
id|ST_L3_LC_ESTAB_WAIT
comma
DECL|enumerator|ST_L3_LC_REL_DELAY
id|ST_L3_LC_REL_DELAY
comma
DECL|enumerator|ST_L3_LC_REL_WAIT
id|ST_L3_LC_REL_WAIT
comma
DECL|enumerator|ST_L3_LC_ESTAB
id|ST_L3_LC_ESTAB
comma
)brace
suffix:semicolon
DECL|macro|L3_STATE_COUNT
mdefine_line|#define L3_STATE_COUNT (ST_L3_LC_ESTAB+1)
DECL|variable|strL3State
r_static
r_char
op_star
id|strL3State
(braket
)braket
op_assign
(brace
l_string|&quot;ST_L3_LC_REL&quot;
comma
l_string|&quot;ST_L3_LC_ESTAB_WAIT&quot;
comma
l_string|&quot;ST_L3_LC_REL_DELAY&quot;
comma
l_string|&quot;ST_L3_LC_REL_WAIT&quot;
comma
l_string|&quot;ST_L3_LC_ESTAB&quot;
comma
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|EV_ESTABLISH_REQ
id|EV_ESTABLISH_REQ
comma
DECL|enumerator|EV_ESTABLISH_IND
id|EV_ESTABLISH_IND
comma
DECL|enumerator|EV_ESTABLISH_CNF
id|EV_ESTABLISH_CNF
comma
DECL|enumerator|EV_RELEASE_REQ
id|EV_RELEASE_REQ
comma
DECL|enumerator|EV_RELEASE_CNF
id|EV_RELEASE_CNF
comma
DECL|enumerator|EV_RELEASE_IND
id|EV_RELEASE_IND
comma
DECL|enumerator|EV_TIMEOUT
id|EV_TIMEOUT
comma
)brace
suffix:semicolon
DECL|macro|L3_EVENT_COUNT
mdefine_line|#define L3_EVENT_COUNT (EV_TIMEOUT+1)
DECL|variable|strL3Event
r_static
r_char
op_star
id|strL3Event
(braket
)braket
op_assign
(brace
l_string|&quot;EV_ESTABLISH_REQ&quot;
comma
l_string|&quot;EV_ESTABLISH_IND&quot;
comma
l_string|&quot;EV_ESTABLISH_CNF&quot;
comma
l_string|&quot;EV_RELEASE_REQ&quot;
comma
l_string|&quot;EV_RELEASE_CNF&quot;
comma
l_string|&quot;EV_RELEASE_IND&quot;
comma
l_string|&quot;EV_TIMEOUT&quot;
comma
)brace
suffix:semicolon
r_static
r_void
DECL|function|l3m_debug
id|l3m_debug
c_func
(paren
r_struct
id|FsmInst
op_star
id|fi
comma
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_struct
id|PStack
op_star
id|st
op_assign
id|fi-&gt;userdata
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|VHiSax_putstatus
c_func
(paren
id|st-&gt;l1.hardware
comma
id|st-&gt;l3.debug_id
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
)brace
id|u8
op_star
DECL|function|findie
id|findie
c_func
(paren
id|u8
op_star
id|p
comma
r_int
id|size
comma
id|u8
id|ie
comma
r_int
id|wanted_set
)paren
(brace
r_int
id|l
comma
id|codeset
comma
id|maincodeset
suffix:semicolon
id|u8
op_star
id|pend
op_assign
id|p
op_plus
id|size
suffix:semicolon
multiline_comment|/* skip protocol discriminator, callref and message type */
id|p
op_increment
suffix:semicolon
id|l
op_assign
(paren
op_star
id|p
op_increment
)paren
op_amp
l_int|0xf
suffix:semicolon
id|p
op_add_assign
id|l
suffix:semicolon
id|p
op_increment
suffix:semicolon
id|codeset
op_assign
l_int|0
suffix:semicolon
id|maincodeset
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* while there are bytes left... */
r_while
c_loop
(paren
id|p
OL
id|pend
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|p
op_amp
l_int|0xf0
)paren
op_eq
l_int|0x90
)paren
(brace
id|codeset
op_assign
op_star
id|p
op_amp
l_int|0x07
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|p
op_amp
l_int|0x08
)paren
)paren
id|maincodeset
op_assign
id|codeset
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|p
op_amp
l_int|0x80
)paren
id|p
op_increment
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
id|codeset
op_eq
id|wanted_set
)paren
(brace
r_if
c_cond
(paren
op_star
id|p
op_eq
id|ie
)paren
(brace
multiline_comment|/* improved length check (Werner Cornelius) */
r_if
c_cond
(paren
(paren
id|pend
op_minus
id|p
)paren
OL
l_int|2
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_star
(paren
id|p
op_plus
l_int|1
)paren
OG
(paren
id|pend
op_minus
(paren
id|p
op_plus
l_int|2
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
(paren
id|p
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|p
OG
id|ie
)paren
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|p
op_increment
suffix:semicolon
id|l
op_assign
op_star
id|p
op_increment
suffix:semicolon
id|p
op_add_assign
id|l
suffix:semicolon
id|codeset
op_assign
id|maincodeset
suffix:semicolon
)brace
)brace
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
r_int
DECL|function|getcallref
id|getcallref
c_func
(paren
id|u8
op_star
id|p
)paren
(brace
r_int
id|l
comma
id|cr
op_assign
l_int|0
suffix:semicolon
id|p
op_increment
suffix:semicolon
multiline_comment|/* prot discr */
r_if
c_cond
(paren
op_star
id|p
op_amp
l_int|0xfe
)paren
multiline_comment|/* wrong callref BRI only 1 octet*/
r_return
op_minus
l_int|2
suffix:semicolon
id|l
op_assign
l_int|0xf
op_amp
op_star
id|p
op_increment
suffix:semicolon
multiline_comment|/* callref length */
r_if
c_cond
(paren
op_logical_neg
id|l
)paren
multiline_comment|/* dummy CallRef */
r_return
op_minus
l_int|1
suffix:semicolon
id|cr
op_assign
op_star
id|p
op_increment
suffix:semicolon
r_return
(paren
id|cr
)paren
suffix:semicolon
)brace
DECL|variable|OrigCallRef
r_static
r_int
id|OrigCallRef
op_assign
l_int|0
suffix:semicolon
r_int
DECL|function|newcallref
id|newcallref
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|OrigCallRef
op_eq
l_int|127
)paren
id|OrigCallRef
op_assign
l_int|1
suffix:semicolon
r_else
id|OrigCallRef
op_increment
suffix:semicolon
r_return
(paren
id|OrigCallRef
)paren
suffix:semicolon
)brace
r_void
DECL|function|newl3state
id|newl3state
c_func
(paren
r_struct
id|l3_process
op_star
id|pc
comma
r_int
id|state
)paren
(brace
r_if
c_cond
(paren
id|pc-&gt;debug
op_amp
id|L3_DEB_STATE
)paren
id|l3_debug
c_func
(paren
id|pc-&gt;st
comma
l_string|&quot;newstate cr %d %d --&gt; %d&quot;
comma
id|pc-&gt;callref
op_amp
l_int|0x7F
comma
id|pc-&gt;state
comma
id|state
)paren
suffix:semicolon
id|pc-&gt;state
op_assign
id|state
suffix:semicolon
)brace
r_static
r_void
DECL|function|L3ExpireTimer
id|L3ExpireTimer
c_func
(paren
r_struct
id|L3Timer
op_star
id|t
)paren
(brace
id|t-&gt;pc-&gt;st-&gt;l3
dot
id|l4l3
c_func
(paren
id|t-&gt;pc-&gt;st
comma
id|t-&gt;event
comma
id|t-&gt;pc
)paren
suffix:semicolon
)brace
r_void
DECL|function|L3InitTimer
id|L3InitTimer
c_func
(paren
r_struct
id|l3_process
op_star
id|pc
comma
r_struct
id|L3Timer
op_star
id|t
)paren
(brace
id|t-&gt;pc
op_assign
id|pc
suffix:semicolon
id|t-&gt;tl.function
op_assign
(paren
r_void
op_star
)paren
id|L3ExpireTimer
suffix:semicolon
id|t-&gt;tl.data
op_assign
(paren
r_int
)paren
id|t
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|t-&gt;tl
)paren
suffix:semicolon
)brace
r_void
DECL|function|L3DelTimer
id|L3DelTimer
c_func
(paren
r_struct
id|L3Timer
op_star
id|t
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|t-&gt;tl
)paren
suffix:semicolon
)brace
r_int
DECL|function|L3AddTimer
id|L3AddTimer
c_func
(paren
r_struct
id|L3Timer
op_star
id|t
comma
r_int
id|millisec
comma
r_int
id|event
)paren
(brace
r_if
c_cond
(paren
id|timer_pending
c_func
(paren
op_amp
id|t-&gt;tl
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;L3AddTimer: timer already active!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|init_timer
c_func
(paren
op_amp
id|t-&gt;tl
)paren
suffix:semicolon
id|t-&gt;event
op_assign
id|event
suffix:semicolon
id|t-&gt;tl.expires
op_assign
id|jiffies
op_plus
(paren
id|millisec
op_star
id|HZ
)paren
op_div
l_int|1000
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|t-&gt;tl
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|StopAllL3Timer
id|StopAllL3Timer
c_func
(paren
r_struct
id|l3_process
op_star
id|pc
)paren
(brace
id|L3DelTimer
c_func
(paren
op_amp
id|pc-&gt;timer
)paren
suffix:semicolon
)brace
r_struct
id|sk_buff
op_star
DECL|function|l3_alloc_skb
id|l3_alloc_skb
c_func
(paren
r_int
id|len
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|len
op_plus
id|MAX_HEADER_LEN
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
l_string|&quot;HiSax: No skb for D-channel&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|skb_reserve
c_func
(paren
id|skb
comma
id|MAX_HEADER_LEN
)paren
suffix:semicolon
r_return
(paren
id|skb
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|no_l3_proto
id|no_l3_proto
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
id|HiSax_putstatus
c_func
(paren
id|st-&gt;l1.hardware
comma
l_string|&quot;L3&quot;
comma
l_string|&quot;no D protocol&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
(brace
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|no_l3_proto_spec
id|no_l3_proto_spec
c_func
(paren
r_struct
id|PStack
op_star
id|st
comma
id|isdn_ctrl
op_star
id|ic
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: no specific protocol handler for proto %lu&bslash;n&quot;
comma
id|ic-&gt;arg
op_amp
l_int|0xFF
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#ifdef&t;CONFIG_HISAX_EURO
r_extern
r_void
id|setstack_dss1
c_func
(paren
r_struct
id|PStack
op_star
id|st
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef  CONFIG_HISAX_NI1
r_extern
r_void
id|setstack_ni1
c_func
(paren
r_struct
id|PStack
op_star
id|st
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef&t;CONFIG_HISAX_1TR6
r_extern
r_void
id|setstack_1tr6
c_func
(paren
r_struct
id|PStack
op_star
id|st
)paren
suffix:semicolon
macro_line|#endif
r_struct
id|l3_process
DECL|function|getl3proc
op_star
id|getl3proc
c_func
(paren
r_struct
id|PStack
op_star
id|st
comma
r_int
id|cr
)paren
(brace
r_struct
id|l3_process
op_star
id|p
op_assign
id|st-&gt;l3.proc
suffix:semicolon
r_while
c_loop
(paren
id|p
)paren
r_if
c_cond
(paren
id|p-&gt;callref
op_eq
id|cr
)paren
r_return
(paren
id|p
)paren
suffix:semicolon
r_else
id|p
op_assign
id|p-&gt;next
suffix:semicolon
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
r_struct
id|l3_process
DECL|function|new_l3_process
op_star
id|new_l3_process
c_func
(paren
r_struct
id|PStack
op_star
id|st
comma
r_int
id|cr
)paren
(brace
r_struct
id|l3_process
op_star
id|p
comma
op_star
id|np
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|l3_process
)paren
comma
id|GFP_ATOMIC
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;HiSax can&squot;t get memory for cr %d&bslash;n&quot;
comma
id|cr
)paren
suffix:semicolon
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|st-&gt;l3.proc
)paren
id|st-&gt;l3.proc
op_assign
id|p
suffix:semicolon
r_else
(brace
id|np
op_assign
id|st-&gt;l3.proc
suffix:semicolon
r_while
c_loop
(paren
id|np-&gt;next
)paren
id|np
op_assign
id|np-&gt;next
suffix:semicolon
id|np-&gt;next
op_assign
id|p
suffix:semicolon
)brace
id|p-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;debug
op_assign
id|st-&gt;l3.debug
suffix:semicolon
id|p-&gt;callref
op_assign
id|cr
suffix:semicolon
id|p-&gt;state
op_assign
l_int|0
suffix:semicolon
id|p-&gt;chan
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;st
op_assign
id|st
suffix:semicolon
id|p-&gt;N303
op_assign
id|st-&gt;l3.N303
suffix:semicolon
id|L3InitTimer
c_func
(paren
id|p
comma
op_amp
id|p-&gt;timer
)paren
suffix:semicolon
r_return
(paren
id|p
)paren
suffix:semicolon
)brace
suffix:semicolon
r_void
DECL|function|release_l3_process
id|release_l3_process
c_func
(paren
r_struct
id|l3_process
op_star
id|p
)paren
(brace
r_struct
id|l3_process
op_star
id|np
comma
op_star
id|pp
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
suffix:semicolon
id|np
op_assign
id|p-&gt;st-&gt;l3.proc
suffix:semicolon
r_while
c_loop
(paren
id|np
)paren
(brace
r_if
c_cond
(paren
id|np
op_eq
id|p
)paren
(brace
id|StopAllL3Timer
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pp
)paren
id|pp-&gt;next
op_assign
id|np-&gt;next
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|p-&gt;st-&gt;l3.proc
op_assign
id|np-&gt;next
)paren
op_logical_and
op_logical_neg
id|test_bit
c_func
(paren
id|FLG_PTP
comma
op_amp
id|p-&gt;st-&gt;l2.flag
)paren
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;debug
)paren
id|l3_debug
c_func
(paren
id|p-&gt;st
comma
l_string|&quot;release_l3_process: last process&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb_queue_len
c_func
(paren
op_amp
id|p-&gt;st-&gt;l3.squeue
)paren
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;debug
)paren
id|l3_debug
c_func
(paren
id|p-&gt;st
comma
l_string|&quot;release_l3_process: release link&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;st-&gt;protocol
op_ne
id|ISDN_PTYPE_NI1
)paren
id|FsmEvent
c_func
(paren
op_amp
id|p-&gt;st-&gt;l3.l3m
comma
id|EV_RELEASE_REQ
comma
l_int|NULL
)paren
suffix:semicolon
r_else
id|FsmEvent
c_func
(paren
op_amp
id|p-&gt;st-&gt;l3.l3m
comma
id|EV_RELEASE_IND
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|p-&gt;debug
)paren
id|l3_debug
c_func
(paren
id|p-&gt;st
comma
l_string|&quot;release_l3_process: not release link&quot;
)paren
suffix:semicolon
)brace
)brace
id|kfree
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|pp
op_assign
id|np
suffix:semicolon
id|np
op_assign
id|np-&gt;next
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;HiSax internal L3 error CR(%d) not in list&bslash;n&quot;
comma
id|p-&gt;callref
)paren
suffix:semicolon
id|l3_debug
c_func
(paren
id|p-&gt;st
comma
l_string|&quot;HiSax internal L3 error CR(%d) not in list&quot;
comma
id|p-&gt;callref
)paren
suffix:semicolon
)brace
suffix:semicolon
r_static
r_void
DECL|function|l3ml3p
id|l3ml3p
c_func
(paren
r_struct
id|PStack
op_star
id|st
comma
r_int
id|pr
)paren
(brace
r_struct
id|l3_process
op_star
id|p
op_assign
id|st-&gt;l3.proc
suffix:semicolon
r_struct
id|l3_process
op_star
id|np
suffix:semicolon
r_while
c_loop
(paren
id|p
)paren
(brace
multiline_comment|/* p might be kfreed under us, so we need to save where we want to go on */
id|np
op_assign
id|p-&gt;next
suffix:semicolon
id|st-&gt;l3
dot
id|l3ml3
c_func
(paren
id|st
comma
id|pr
comma
id|p
)paren
suffix:semicolon
id|p
op_assign
id|np
suffix:semicolon
)brace
)brace
r_void
DECL|function|setstack_l3dc
id|setstack_l3dc
c_func
(paren
r_struct
id|PStack
op_star
id|st
comma
r_struct
id|Channel
op_star
id|chanp
)paren
(brace
r_char
id|tmp
(braket
l_int|64
)braket
suffix:semicolon
id|st-&gt;l3.proc
op_assign
l_int|NULL
suffix:semicolon
id|st-&gt;l3.global
op_assign
l_int|NULL
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|st-&gt;l3.squeue
)paren
suffix:semicolon
id|st-&gt;l3.l3m.fsm
op_assign
op_amp
id|l3fsm
suffix:semicolon
id|st-&gt;l3.l3m.state
op_assign
id|ST_L3_LC_REL
suffix:semicolon
id|st-&gt;l3.l3m.debug
op_assign
l_int|1
suffix:semicolon
id|st-&gt;l3.l3m.userdata
op_assign
id|st
suffix:semicolon
id|st-&gt;l3.l3m.userint
op_assign
l_int|0
suffix:semicolon
id|st-&gt;l3.l3m.printdebug
op_assign
id|l3m_debug
suffix:semicolon
id|FsmInitTimer
c_func
(paren
op_amp
id|st-&gt;l3.l3m
comma
op_amp
id|st-&gt;l3.l3m_timer
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|st-&gt;l3.debug_id
comma
l_string|&quot;L3DC &quot;
)paren
suffix:semicolon
id|st-&gt;l3.l4l3_proto
op_assign
id|no_l3_proto_spec
suffix:semicolon
macro_line|#ifdef&t;CONFIG_HISAX_EURO
r_if
c_cond
(paren
id|st-&gt;protocol
op_eq
id|ISDN_PTYPE_EURO
)paren
(brace
id|setstack_dss1
c_func
(paren
id|st
)paren
suffix:semicolon
)brace
r_else
macro_line|#endif
macro_line|#ifdef  CONFIG_HISAX_NI1
r_if
c_cond
(paren
id|st-&gt;protocol
op_eq
id|ISDN_PTYPE_NI1
)paren
(brace
id|setstack_ni1
c_func
(paren
id|st
)paren
suffix:semicolon
)brace
r_else
macro_line|#endif
macro_line|#ifdef&t;CONFIG_HISAX_1TR6
r_if
c_cond
(paren
id|st-&gt;protocol
op_eq
id|ISDN_PTYPE_1TR6
)paren
(brace
id|setstack_1tr6
c_func
(paren
id|st
)paren
suffix:semicolon
)brace
r_else
macro_line|#endif
r_if
c_cond
(paren
id|st-&gt;protocol
op_eq
id|ISDN_PTYPE_LEASED
)paren
(brace
id|st-&gt;l3.l4l3
op_assign
id|no_l3_proto
suffix:semicolon
id|st-&gt;l3.l2l3
op_assign
id|no_l3_proto
suffix:semicolon
id|st-&gt;l3.l3ml3
op_assign
id|no_l3_proto
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: Leased line mode&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|st-&gt;l3.l4l3
op_assign
id|no_l3_proto
suffix:semicolon
id|st-&gt;l3.l2l3
op_assign
id|no_l3_proto
suffix:semicolon
id|st-&gt;l3.l3ml3
op_assign
id|no_l3_proto
suffix:semicolon
id|sprintf
c_func
(paren
id|tmp
comma
l_string|&quot;protocol %s not supported&quot;
comma
(paren
id|st-&gt;protocol
op_eq
id|ISDN_PTYPE_1TR6
)paren
ques
c_cond
l_string|&quot;1tr6&quot;
suffix:colon
(paren
id|st-&gt;protocol
op_eq
id|ISDN_PTYPE_EURO
)paren
ques
c_cond
l_string|&quot;euro&quot;
suffix:colon
(paren
id|st-&gt;protocol
op_eq
id|ISDN_PTYPE_NI1
)paren
ques
c_cond
l_string|&quot;ni1&quot;
suffix:colon
l_string|&quot;unknown&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s&bslash;n&quot;
comma
id|tmp
)paren
suffix:semicolon
id|st-&gt;protocol
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
)brace
r_void
DECL|function|isdnl3_trans
id|isdnl3_trans
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
id|L3L2
c_func
(paren
id|st
comma
id|pr
comma
id|arg
)paren
suffix:semicolon
)brace
r_void
DECL|function|releasestack_isdnl3
id|releasestack_isdnl3
c_func
(paren
r_struct
id|PStack
op_star
id|st
)paren
(brace
r_while
c_loop
(paren
id|st-&gt;l3.proc
)paren
id|release_l3_process
c_func
(paren
id|st-&gt;l3.proc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|st-&gt;l3.global
)paren
(brace
id|StopAllL3Timer
c_func
(paren
id|st-&gt;l3.global
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|st-&gt;l3.global
)paren
suffix:semicolon
id|st-&gt;l3.global
op_assign
l_int|NULL
suffix:semicolon
)brace
id|FsmDelTimer
c_func
(paren
op_amp
id|st-&gt;l3.l3m_timer
comma
l_int|54
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|st-&gt;l3.squeue
)paren
suffix:semicolon
)brace
r_void
DECL|function|setstack_l3bc
id|setstack_l3bc
c_func
(paren
r_struct
id|PStack
op_star
id|st
comma
r_struct
id|Channel
op_star
id|chanp
)paren
(brace
id|st-&gt;l3.proc
op_assign
l_int|NULL
suffix:semicolon
id|st-&gt;l3.global
op_assign
l_int|NULL
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|st-&gt;l3.squeue
)paren
suffix:semicolon
id|st-&gt;l3.l3m.fsm
op_assign
op_amp
id|l3fsm
suffix:semicolon
id|st-&gt;l3.l3m.state
op_assign
id|ST_L3_LC_REL
suffix:semicolon
id|st-&gt;l3.l3m.debug
op_assign
l_int|1
suffix:semicolon
id|st-&gt;l3.l3m.userdata
op_assign
id|st
suffix:semicolon
id|st-&gt;l3.l3m.userint
op_assign
l_int|0
suffix:semicolon
id|st-&gt;l3.l3m.printdebug
op_assign
id|l3m_debug
suffix:semicolon
id|strcpy
c_func
(paren
id|st-&gt;l3.debug_id
comma
l_string|&quot;L3BC &quot;
)paren
suffix:semicolon
id|st-&gt;l3.l4l3
op_assign
id|isdnl3_trans
suffix:semicolon
)brace
DECL|macro|DREL_TIMER_VALUE
mdefine_line|#define DREL_TIMER_VALUE 40000
r_static
r_void
DECL|function|lc_activate
id|lc_activate
c_func
(paren
r_struct
id|FsmInst
op_star
id|fi
comma
r_int
id|event
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|PStack
op_star
id|st
op_assign
id|fi-&gt;userdata
suffix:semicolon
id|FsmChangeState
c_func
(paren
id|fi
comma
id|ST_L3_LC_ESTAB_WAIT
)paren
suffix:semicolon
id|L3L2
c_func
(paren
id|st
comma
id|DL_ESTABLISH
op_or
id|REQUEST
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|lc_connect
id|lc_connect
c_func
(paren
r_struct
id|FsmInst
op_star
id|fi
comma
r_int
id|event
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|PStack
op_star
id|st
op_assign
id|fi-&gt;userdata
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
op_assign
id|arg
suffix:semicolon
r_int
id|dequeued
op_assign
l_int|0
suffix:semicolon
id|FsmChangeState
c_func
(paren
id|fi
comma
id|ST_L3_LC_ESTAB
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|st-&gt;l3.squeue
)paren
)paren
)paren
(brace
id|L3L2
c_func
(paren
id|st
comma
id|DL_DATA
op_or
id|REQUEST
comma
id|skb
)paren
suffix:semicolon
id|dequeued
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
op_logical_neg
id|st-&gt;l3.proc
)paren
op_logical_and
id|dequeued
)paren
(brace
r_if
c_cond
(paren
id|st-&gt;l3.debug
)paren
id|l3_debug
c_func
(paren
id|st
comma
l_string|&quot;lc_connect: release link&quot;
)paren
suffix:semicolon
id|FsmEvent
c_func
(paren
op_amp
id|st-&gt;l3.l3m
comma
id|EV_RELEASE_REQ
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_else
id|l3ml3p
c_func
(paren
id|st
comma
id|DL_ESTABLISH
op_or
id|INDICATION
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|lc_connected
id|lc_connected
c_func
(paren
r_struct
id|FsmInst
op_star
id|fi
comma
r_int
id|event
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|PStack
op_star
id|st
op_assign
id|fi-&gt;userdata
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
op_assign
id|arg
suffix:semicolon
r_int
id|dequeued
op_assign
l_int|0
suffix:semicolon
id|FsmDelTimer
c_func
(paren
op_amp
id|st-&gt;l3.l3m_timer
comma
l_int|51
)paren
suffix:semicolon
id|FsmChangeState
c_func
(paren
id|fi
comma
id|ST_L3_LC_ESTAB
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|st-&gt;l3.squeue
)paren
)paren
)paren
(brace
id|L3L2
c_func
(paren
id|st
comma
id|DL_DATA
op_or
id|REQUEST
comma
id|skb
)paren
suffix:semicolon
id|dequeued
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
op_logical_neg
id|st-&gt;l3.proc
)paren
op_logical_and
id|dequeued
)paren
(brace
r_if
c_cond
(paren
id|st-&gt;l3.debug
)paren
id|l3_debug
c_func
(paren
id|st
comma
l_string|&quot;lc_connected: release link&quot;
)paren
suffix:semicolon
id|FsmEvent
c_func
(paren
op_amp
id|st-&gt;l3.l3m
comma
id|EV_RELEASE_REQ
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_else
id|l3ml3p
c_func
(paren
id|st
comma
id|DL_ESTABLISH
op_or
id|CONFIRM
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|lc_start_delay
id|lc_start_delay
c_func
(paren
r_struct
id|FsmInst
op_star
id|fi
comma
r_int
id|event
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|PStack
op_star
id|st
op_assign
id|fi-&gt;userdata
suffix:semicolon
id|FsmChangeState
c_func
(paren
id|fi
comma
id|ST_L3_LC_REL_DELAY
)paren
suffix:semicolon
id|FsmAddTimer
c_func
(paren
op_amp
id|st-&gt;l3.l3m_timer
comma
id|DREL_TIMER_VALUE
comma
id|EV_TIMEOUT
comma
l_int|NULL
comma
l_int|50
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|lc_start_delay_check
id|lc_start_delay_check
c_func
(paren
r_struct
id|FsmInst
op_star
id|fi
comma
r_int
id|event
comma
r_void
op_star
id|arg
)paren
multiline_comment|/* 20/09/00 - GE timer not user for NI-1 as layer 2 should stay up */
(brace
r_struct
id|PStack
op_star
id|st
op_assign
id|fi-&gt;userdata
suffix:semicolon
id|FsmChangeState
c_func
(paren
id|fi
comma
id|ST_L3_LC_REL_DELAY
)paren
suffix:semicolon
multiline_comment|/* 19/09/00 - GE timer not user for NI-1 */
r_if
c_cond
(paren
id|st-&gt;protocol
op_ne
id|ISDN_PTYPE_NI1
)paren
id|FsmAddTimer
c_func
(paren
op_amp
id|st-&gt;l3.l3m_timer
comma
id|DREL_TIMER_VALUE
comma
id|EV_TIMEOUT
comma
l_int|NULL
comma
l_int|50
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|lc_release_req
id|lc_release_req
c_func
(paren
r_struct
id|FsmInst
op_star
id|fi
comma
r_int
id|event
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|PStack
op_star
id|st
op_assign
id|fi-&gt;userdata
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|FLG_L2BLOCK
comma
op_amp
id|st-&gt;l2.flag
)paren
)paren
(brace
r_if
c_cond
(paren
id|st-&gt;l3.debug
)paren
id|l3_debug
c_func
(paren
id|st
comma
l_string|&quot;lc_release_req: l2 blocked&quot;
)paren
suffix:semicolon
multiline_comment|/* restart release timer */
id|FsmAddTimer
c_func
(paren
op_amp
id|st-&gt;l3.l3m_timer
comma
id|DREL_TIMER_VALUE
comma
id|EV_TIMEOUT
comma
l_int|NULL
comma
l_int|51
)paren
suffix:semicolon
)brace
r_else
(brace
id|FsmChangeState
c_func
(paren
id|fi
comma
id|ST_L3_LC_REL_WAIT
)paren
suffix:semicolon
id|L3L2
c_func
(paren
id|st
comma
id|DL_RELEASE
op_or
id|REQUEST
comma
l_int|NULL
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|lc_release_ind
id|lc_release_ind
c_func
(paren
r_struct
id|FsmInst
op_star
id|fi
comma
r_int
id|event
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|PStack
op_star
id|st
op_assign
id|fi-&gt;userdata
suffix:semicolon
id|FsmDelTimer
c_func
(paren
op_amp
id|st-&gt;l3.l3m_timer
comma
l_int|52
)paren
suffix:semicolon
id|FsmChangeState
c_func
(paren
id|fi
comma
id|ST_L3_LC_REL
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|st-&gt;l3.squeue
)paren
suffix:semicolon
id|l3ml3p
c_func
(paren
id|st
comma
id|DL_RELEASE
op_or
id|INDICATION
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|lc_release_cnf
id|lc_release_cnf
c_func
(paren
r_struct
id|FsmInst
op_star
id|fi
comma
r_int
id|event
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|PStack
op_star
id|st
op_assign
id|fi-&gt;userdata
suffix:semicolon
id|FsmChangeState
c_func
(paren
id|fi
comma
id|ST_L3_LC_REL
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|st-&gt;l3.squeue
)paren
suffix:semicolon
id|l3ml3p
c_func
(paren
id|st
comma
id|DL_RELEASE
op_or
id|CONFIRM
)paren
suffix:semicolon
)brace
multiline_comment|/* *INDENT-OFF* */
DECL|variable|__initdata
r_static
r_struct
id|FsmNode
id|L3FnList
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|ST_L3_LC_REL
comma
id|EV_ESTABLISH_REQ
comma
id|lc_activate
)brace
comma
(brace
id|ST_L3_LC_REL
comma
id|EV_ESTABLISH_IND
comma
id|lc_connect
)brace
comma
(brace
id|ST_L3_LC_REL
comma
id|EV_ESTABLISH_CNF
comma
id|lc_connect
)brace
comma
(brace
id|ST_L3_LC_ESTAB_WAIT
comma
id|EV_ESTABLISH_CNF
comma
id|lc_connected
)brace
comma
(brace
id|ST_L3_LC_ESTAB_WAIT
comma
id|EV_RELEASE_REQ
comma
id|lc_start_delay
)brace
comma
(brace
id|ST_L3_LC_ESTAB_WAIT
comma
id|EV_RELEASE_IND
comma
id|lc_release_ind
)brace
comma
(brace
id|ST_L3_LC_ESTAB
comma
id|EV_RELEASE_IND
comma
id|lc_release_ind
)brace
comma
(brace
id|ST_L3_LC_ESTAB
comma
id|EV_RELEASE_REQ
comma
id|lc_start_delay_check
)brace
comma
(brace
id|ST_L3_LC_REL_DELAY
comma
id|EV_RELEASE_IND
comma
id|lc_release_ind
)brace
comma
(brace
id|ST_L3_LC_REL_DELAY
comma
id|EV_ESTABLISH_REQ
comma
id|lc_connected
)brace
comma
(brace
id|ST_L3_LC_REL_DELAY
comma
id|EV_TIMEOUT
comma
id|lc_release_req
)brace
comma
(brace
id|ST_L3_LC_REL_WAIT
comma
id|EV_RELEASE_CNF
comma
id|lc_release_cnf
)brace
comma
(brace
id|ST_L3_LC_REL_WAIT
comma
id|EV_ESTABLISH_REQ
comma
id|lc_activate
)brace
comma
)brace
suffix:semicolon
multiline_comment|/* *INDENT-ON* */
DECL|macro|L3_FN_COUNT
mdefine_line|#define L3_FN_COUNT (sizeof(L3FnList)/sizeof(struct FsmNode))
r_void
DECL|function|l3_msg
id|l3_msg
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
r_switch
c_cond
(paren
id|pr
)paren
(brace
r_case
(paren
id|DL_DATA
op_or
id|REQUEST
)paren
suffix:colon
r_if
c_cond
(paren
id|st-&gt;l3.l3m.state
op_eq
id|ST_L3_LC_ESTAB
)paren
(brace
id|L3L2
c_func
(paren
id|st
comma
id|pr
comma
id|arg
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|sk_buff
op_star
id|skb
op_assign
id|arg
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|st-&gt;l3.squeue
comma
id|skb
)paren
suffix:semicolon
id|FsmEvent
c_func
(paren
op_amp
id|st-&gt;l3.l3m
comma
id|EV_ESTABLISH_REQ
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
(paren
id|DL_ESTABLISH
op_or
id|REQUEST
)paren
suffix:colon
id|FsmEvent
c_func
(paren
op_amp
id|st-&gt;l3.l3m
comma
id|EV_ESTABLISH_REQ
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|DL_ESTABLISH
op_or
id|CONFIRM
)paren
suffix:colon
id|FsmEvent
c_func
(paren
op_amp
id|st-&gt;l3.l3m
comma
id|EV_ESTABLISH_CNF
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|DL_ESTABLISH
op_or
id|INDICATION
)paren
suffix:colon
id|FsmEvent
c_func
(paren
op_amp
id|st-&gt;l3.l3m
comma
id|EV_ESTABLISH_IND
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|DL_RELEASE
op_or
id|INDICATION
)paren
suffix:colon
id|FsmEvent
c_func
(paren
op_amp
id|st-&gt;l3.l3m
comma
id|EV_RELEASE_IND
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|DL_RELEASE
op_or
id|CONFIRM
)paren
suffix:colon
id|FsmEvent
c_func
(paren
op_amp
id|st-&gt;l3.l3m
comma
id|EV_RELEASE_CNF
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|DL_RELEASE
op_or
id|REQUEST
)paren
suffix:colon
id|FsmEvent
c_func
(paren
op_amp
id|st-&gt;l3.l3m
comma
id|EV_RELEASE_REQ
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_int
id|__init
DECL|function|Isdnl3New
id|Isdnl3New
c_func
(paren
r_void
)paren
(brace
id|l3fsm.state_count
op_assign
id|L3_STATE_COUNT
suffix:semicolon
id|l3fsm.event_count
op_assign
id|L3_EVENT_COUNT
suffix:semicolon
id|l3fsm.strEvent
op_assign
id|strL3Event
suffix:semicolon
id|l3fsm.strState
op_assign
id|strL3State
suffix:semicolon
r_return
id|FsmNew
c_func
(paren
op_amp
id|l3fsm
comma
id|L3FnList
comma
id|L3_FN_COUNT
)paren
suffix:semicolon
)brace
r_void
DECL|function|Isdnl3Free
id|Isdnl3Free
c_func
(paren
r_void
)paren
(brace
id|FsmFree
c_func
(paren
op_amp
id|l3fsm
)paren
suffix:semicolon
)brace
eof
