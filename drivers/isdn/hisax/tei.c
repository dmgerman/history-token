multiline_comment|/* $Id: tei.c,v 2.17.6.3 2001/09/23 22:24:51 kai Exp $&n; *&n; * Author       Karsten Keil&n; *              based on the teles driver from Jan den Ouden&n; * Copyright    by Karsten Keil      &lt;keil@isdn4linux.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; * For changes and modifications please read&n; * ../../../Documentation/isdn/HiSax.cert&n; *&n; * Thanks to    Jan den Ouden&n; *              Fritz Elfert&n; *&n; */
macro_line|#include &quot;hisax.h&quot;
macro_line|#include &quot;isdnl2.h&quot;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/random.h&gt;
DECL|variable|tei_revision
r_const
r_char
op_star
id|tei_revision
op_assign
l_string|&quot;$Revision: 2.17.6.3 $&quot;
suffix:semicolon
DECL|macro|ID_REQUEST
mdefine_line|#define ID_REQUEST&t;1
DECL|macro|ID_ASSIGNED
mdefine_line|#define ID_ASSIGNED&t;2
DECL|macro|ID_DENIED
mdefine_line|#define ID_DENIED&t;3
DECL|macro|ID_CHK_REQ
mdefine_line|#define ID_CHK_REQ&t;4
DECL|macro|ID_CHK_RES
mdefine_line|#define ID_CHK_RES&t;5
DECL|macro|ID_REMOVE
mdefine_line|#define ID_REMOVE&t;6
DECL|macro|ID_VERIFY
mdefine_line|#define ID_VERIFY&t;7
DECL|macro|TEI_ENTITY_ID
mdefine_line|#define TEI_ENTITY_ID&t;0xf
DECL|variable|teifsm
r_static
r_struct
id|Fsm
id|teifsm
suffix:semicolon
r_void
id|tei_handler
c_func
(paren
r_struct
id|PStack
op_star
id|st
comma
id|u_char
id|pr
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_enum
(brace
DECL|enumerator|ST_TEI_NOP
id|ST_TEI_NOP
comma
DECL|enumerator|ST_TEI_IDREQ
id|ST_TEI_IDREQ
comma
DECL|enumerator|ST_TEI_IDVERIFY
id|ST_TEI_IDVERIFY
comma
)brace
suffix:semicolon
DECL|macro|TEI_STATE_COUNT
mdefine_line|#define TEI_STATE_COUNT (ST_TEI_IDVERIFY+1)
DECL|variable|strTeiState
r_static
r_char
op_star
id|strTeiState
(braket
)braket
op_assign
(brace
l_string|&quot;ST_TEI_NOP&quot;
comma
l_string|&quot;ST_TEI_IDREQ&quot;
comma
l_string|&quot;ST_TEI_IDVERIFY&quot;
comma
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|EV_IDREQ
id|EV_IDREQ
comma
DECL|enumerator|EV_ASSIGN
id|EV_ASSIGN
comma
DECL|enumerator|EV_DENIED
id|EV_DENIED
comma
DECL|enumerator|EV_CHKREQ
id|EV_CHKREQ
comma
DECL|enumerator|EV_REMOVE
id|EV_REMOVE
comma
DECL|enumerator|EV_VERIFY
id|EV_VERIFY
comma
DECL|enumerator|EV_T202
id|EV_T202
comma
)brace
suffix:semicolon
DECL|macro|TEI_EVENT_COUNT
mdefine_line|#define TEI_EVENT_COUNT (EV_T202+1)
DECL|variable|strTeiEvent
r_static
r_char
op_star
id|strTeiEvent
(braket
)braket
op_assign
(brace
l_string|&quot;EV_IDREQ&quot;
comma
l_string|&quot;EV_ASSIGN&quot;
comma
l_string|&quot;EV_DENIED&quot;
comma
l_string|&quot;EV_CHKREQ&quot;
comma
l_string|&quot;EV_REMOVE&quot;
comma
l_string|&quot;EV_VERIFY&quot;
comma
l_string|&quot;EV_T202&quot;
comma
)brace
suffix:semicolon
r_int
r_int
DECL|function|random_ri
id|random_ri
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|x
suffix:semicolon
id|get_random_bytes
c_func
(paren
op_amp
id|x
comma
r_sizeof
(paren
id|x
)paren
)paren
suffix:semicolon
r_return
(paren
id|x
op_amp
l_int|0xffff
)paren
suffix:semicolon
)brace
r_static
r_struct
id|PStack
op_star
DECL|function|findtei
id|findtei
c_func
(paren
r_struct
id|PStack
op_star
id|st
comma
r_int
id|tei
)paren
(brace
r_struct
id|PStack
op_star
id|ptr
op_assign
op_star
(paren
id|st-&gt;l1.stlistp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tei
op_eq
l_int|127
)paren
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
r_while
c_loop
(paren
id|ptr
)paren
r_if
c_cond
(paren
id|ptr-&gt;l2.tei
op_eq
id|tei
)paren
r_return
(paren
id|ptr
)paren
suffix:semicolon
r_else
id|ptr
op_assign
id|ptr-&gt;next
suffix:semicolon
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|put_tei_msg
id|put_tei_msg
c_func
(paren
r_struct
id|PStack
op_star
id|st
comma
id|u_char
id|m_id
comma
r_int
r_int
id|ri
comma
id|u_char
id|tei
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|u_char
op_star
id|bp
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
l_int|8
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
l_string|&quot;HiSax: No skb for TEI manager&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|bp
op_assign
id|skb_put
c_func
(paren
id|skb
comma
l_int|3
)paren
suffix:semicolon
id|bp
(braket
l_int|0
)braket
op_assign
(paren
id|TEI_SAPI
op_lshift
l_int|2
)paren
suffix:semicolon
id|bp
(braket
l_int|1
)braket
op_assign
(paren
id|GROUP_TEI
op_lshift
l_int|1
)paren
op_or
l_int|0x1
suffix:semicolon
id|bp
(braket
l_int|2
)braket
op_assign
id|UI
suffix:semicolon
id|bp
op_assign
id|skb_put
c_func
(paren
id|skb
comma
l_int|5
)paren
suffix:semicolon
id|bp
(braket
l_int|0
)braket
op_assign
id|TEI_ENTITY_ID
suffix:semicolon
id|bp
(braket
l_int|1
)braket
op_assign
id|ri
op_rshift
l_int|8
suffix:semicolon
id|bp
(braket
l_int|2
)braket
op_assign
id|ri
op_amp
l_int|0xff
suffix:semicolon
id|bp
(braket
l_int|3
)braket
op_assign
id|m_id
suffix:semicolon
id|bp
(braket
l_int|4
)braket
op_assign
(paren
id|tei
op_lshift
l_int|1
)paren
op_or
l_int|1
suffix:semicolon
id|L2L1
c_func
(paren
id|st
comma
id|PH_DATA
op_or
id|REQUEST
comma
id|skb
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|tei_id_request
id|tei_id_request
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
id|st-&gt;l2.tei
op_ne
op_minus
l_int|1
)paren
(brace
id|st-&gt;ma.tei_m
dot
id|printdebug
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
l_string|&quot;assign request for allready asigned tei %d&quot;
comma
id|st-&gt;l2.tei
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|st-&gt;ma.ri
op_assign
id|random_ri
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|st-&gt;ma.debug
)paren
id|st-&gt;ma.tei_m
dot
id|printdebug
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
l_string|&quot;assign request ri %d&quot;
comma
id|st-&gt;ma.ri
)paren
suffix:semicolon
id|put_tei_msg
c_func
(paren
id|st
comma
id|ID_REQUEST
comma
id|st-&gt;ma.ri
comma
l_int|127
)paren
suffix:semicolon
id|FsmChangeState
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
id|ST_TEI_IDREQ
)paren
suffix:semicolon
id|FsmAddTimer
c_func
(paren
op_amp
id|st-&gt;ma.t202
comma
id|st-&gt;ma.T202
comma
id|EV_T202
comma
l_int|NULL
comma
l_int|1
)paren
suffix:semicolon
id|st-&gt;ma.N202
op_assign
l_int|3
suffix:semicolon
)brace
r_static
r_void
DECL|function|tei_id_assign
id|tei_id_assign
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
id|ost
comma
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
r_struct
id|IsdnCardState
op_star
id|cs
suffix:semicolon
r_int
id|ri
comma
id|tei
suffix:semicolon
id|ri
op_assign
(paren
(paren
r_int
r_int
)paren
id|skb-&gt;data
(braket
l_int|1
)braket
op_lshift
l_int|8
)paren
op_plus
id|skb-&gt;data
(braket
l_int|2
)braket
suffix:semicolon
id|tei
op_assign
id|skb-&gt;data
(braket
l_int|4
)braket
op_rshift
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|st-&gt;ma.debug
)paren
id|st-&gt;ma.tei_m
dot
id|printdebug
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
l_string|&quot;identity assign ri %d tei %d&quot;
comma
id|ri
comma
id|tei
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ost
op_assign
id|findtei
c_func
(paren
id|st
comma
id|tei
)paren
)paren
)paren
(brace
multiline_comment|/* same tei is in use */
r_if
c_cond
(paren
id|ri
op_ne
id|ost-&gt;ma.ri
)paren
(brace
id|st-&gt;ma.tei_m
dot
id|printdebug
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
l_string|&quot;possible duplicate assignment tei %d&quot;
comma
id|tei
)paren
suffix:semicolon
id|ost-&gt;l2
dot
id|l2tei
c_func
(paren
id|ost
comma
id|MDL_ERROR
op_or
id|RESPONSE
comma
l_int|NULL
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|ri
op_eq
id|st-&gt;ma.ri
)paren
(brace
id|FsmDelTimer
c_func
(paren
op_amp
id|st-&gt;ma.t202
comma
l_int|1
)paren
suffix:semicolon
id|FsmChangeState
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
id|ST_TEI_NOP
)paren
suffix:semicolon
id|L3L2
c_func
(paren
id|st
comma
id|MDL_ASSIGN
op_or
id|REQUEST
comma
(paren
r_void
op_star
)paren
(paren
r_int
)paren
id|tei
)paren
suffix:semicolon
id|cs
op_assign
(paren
r_struct
id|IsdnCardState
op_star
)paren
id|st-&gt;l1.hardware
suffix:semicolon
id|cs
op_member_access_from_pointer
id|cardmsg
c_func
(paren
id|cs
comma
id|MDL_ASSIGN
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
DECL|function|tei_id_test_dup
id|tei_id_test_dup
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
id|ost
comma
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
id|tei
comma
id|ri
suffix:semicolon
id|ri
op_assign
(paren
(paren
r_int
r_int
)paren
id|skb-&gt;data
(braket
l_int|1
)braket
op_lshift
l_int|8
)paren
op_plus
id|skb-&gt;data
(braket
l_int|2
)braket
suffix:semicolon
id|tei
op_assign
id|skb-&gt;data
(braket
l_int|4
)braket
op_rshift
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|st-&gt;ma.debug
)paren
id|st-&gt;ma.tei_m
dot
id|printdebug
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
l_string|&quot;foreign identity assign ri %d tei %d&quot;
comma
id|ri
comma
id|tei
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ost
op_assign
id|findtei
c_func
(paren
id|st
comma
id|tei
)paren
)paren
)paren
(brace
multiline_comment|/* same tei is in use */
r_if
c_cond
(paren
id|ri
op_ne
id|ost-&gt;ma.ri
)paren
(brace
multiline_comment|/* and it wasn&squot;t our request */
id|st-&gt;ma.tei_m
dot
id|printdebug
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
l_string|&quot;possible duplicate assignment tei %d&quot;
comma
id|tei
)paren
suffix:semicolon
id|FsmEvent
c_func
(paren
op_amp
id|ost-&gt;ma.tei_m
comma
id|EV_VERIFY
comma
l_int|NULL
)paren
suffix:semicolon
)brace
)brace
)brace
r_static
r_void
DECL|function|tei_id_denied
id|tei_id_denied
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
id|ri
comma
id|tei
suffix:semicolon
id|ri
op_assign
(paren
(paren
r_int
r_int
)paren
id|skb-&gt;data
(braket
l_int|1
)braket
op_lshift
l_int|8
)paren
op_plus
id|skb-&gt;data
(braket
l_int|2
)braket
suffix:semicolon
id|tei
op_assign
id|skb-&gt;data
(braket
l_int|4
)braket
op_rshift
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|st-&gt;ma.debug
)paren
id|st-&gt;ma.tei_m
dot
id|printdebug
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
l_string|&quot;identity denied ri %d tei %d&quot;
comma
id|ri
comma
id|tei
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|tei_id_chk_req
id|tei_id_chk_req
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
id|tei
suffix:semicolon
id|tei
op_assign
id|skb-&gt;data
(braket
l_int|4
)braket
op_rshift
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|st-&gt;ma.debug
)paren
id|st-&gt;ma.tei_m
dot
id|printdebug
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
l_string|&quot;identity check req tei %d&quot;
comma
id|tei
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|st-&gt;l2.tei
op_ne
op_minus
l_int|1
)paren
op_logical_and
(paren
(paren
id|tei
op_eq
id|GROUP_TEI
)paren
op_logical_or
(paren
id|tei
op_eq
id|st-&gt;l2.tei
)paren
)paren
)paren
(brace
id|FsmDelTimer
c_func
(paren
op_amp
id|st-&gt;ma.t202
comma
l_int|4
)paren
suffix:semicolon
id|FsmChangeState
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
id|ST_TEI_NOP
)paren
suffix:semicolon
id|put_tei_msg
c_func
(paren
id|st
comma
id|ID_CHK_RES
comma
id|random_ri
c_func
(paren
)paren
comma
id|st-&gt;l2.tei
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|tei_id_remove
id|tei_id_remove
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
r_struct
id|IsdnCardState
op_star
id|cs
suffix:semicolon
r_int
id|tei
suffix:semicolon
id|tei
op_assign
id|skb-&gt;data
(braket
l_int|4
)braket
op_rshift
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|st-&gt;ma.debug
)paren
id|st-&gt;ma.tei_m
dot
id|printdebug
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
l_string|&quot;identity remove tei %d&quot;
comma
id|tei
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|st-&gt;l2.tei
op_ne
op_minus
l_int|1
)paren
op_logical_and
(paren
(paren
id|tei
op_eq
id|GROUP_TEI
)paren
op_logical_or
(paren
id|tei
op_eq
id|st-&gt;l2.tei
)paren
)paren
)paren
(brace
id|FsmDelTimer
c_func
(paren
op_amp
id|st-&gt;ma.t202
comma
l_int|5
)paren
suffix:semicolon
id|FsmChangeState
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
id|ST_TEI_NOP
)paren
suffix:semicolon
id|L3L2
c_func
(paren
id|st
comma
id|MDL_REMOVE
op_or
id|REQUEST
comma
l_int|0
)paren
suffix:semicolon
id|cs
op_assign
(paren
r_struct
id|IsdnCardState
op_star
)paren
id|st-&gt;l1.hardware
suffix:semicolon
id|cs
op_member_access_from_pointer
id|cardmsg
c_func
(paren
id|cs
comma
id|MDL_REMOVE
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
DECL|function|tei_id_verify
id|tei_id_verify
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
id|st-&gt;ma.debug
)paren
id|st-&gt;ma.tei_m
dot
id|printdebug
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
l_string|&quot;id verify request for tei %d&quot;
comma
id|st-&gt;l2.tei
)paren
suffix:semicolon
id|put_tei_msg
c_func
(paren
id|st
comma
id|ID_VERIFY
comma
l_int|0
comma
id|st-&gt;l2.tei
)paren
suffix:semicolon
id|FsmChangeState
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
id|ST_TEI_IDVERIFY
)paren
suffix:semicolon
id|FsmAddTimer
c_func
(paren
op_amp
id|st-&gt;ma.t202
comma
id|st-&gt;ma.T202
comma
id|EV_T202
comma
l_int|NULL
comma
l_int|2
)paren
suffix:semicolon
id|st-&gt;ma.N202
op_assign
l_int|2
suffix:semicolon
)brace
r_static
r_void
DECL|function|tei_id_req_tout
id|tei_id_req_tout
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
id|IsdnCardState
op_star
id|cs
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|st-&gt;ma.N202
)paren
(brace
id|st-&gt;ma.ri
op_assign
id|random_ri
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|st-&gt;ma.debug
)paren
id|st-&gt;ma.tei_m
dot
id|printdebug
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
l_string|&quot;assign req(%d) ri %d&quot;
comma
l_int|4
op_minus
id|st-&gt;ma.N202
comma
id|st-&gt;ma.ri
)paren
suffix:semicolon
id|put_tei_msg
c_func
(paren
id|st
comma
id|ID_REQUEST
comma
id|st-&gt;ma.ri
comma
l_int|127
)paren
suffix:semicolon
id|FsmAddTimer
c_func
(paren
op_amp
id|st-&gt;ma.t202
comma
id|st-&gt;ma.T202
comma
id|EV_T202
comma
l_int|NULL
comma
l_int|3
)paren
suffix:semicolon
)brace
r_else
(brace
id|st-&gt;ma.tei_m
dot
id|printdebug
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
l_string|&quot;assign req failed&quot;
)paren
suffix:semicolon
id|L3L2
c_func
(paren
id|st
comma
id|MDL_ERROR
op_or
id|RESPONSE
comma
l_int|0
)paren
suffix:semicolon
id|cs
op_assign
(paren
r_struct
id|IsdnCardState
op_star
)paren
id|st-&gt;l1.hardware
suffix:semicolon
id|cs
op_member_access_from_pointer
id|cardmsg
c_func
(paren
id|cs
comma
id|MDL_REMOVE
op_or
id|REQUEST
comma
l_int|NULL
)paren
suffix:semicolon
id|FsmChangeState
c_func
(paren
id|fi
comma
id|ST_TEI_NOP
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|tei_id_ver_tout
id|tei_id_ver_tout
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
id|IsdnCardState
op_star
id|cs
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|st-&gt;ma.N202
)paren
(brace
r_if
c_cond
(paren
id|st-&gt;ma.debug
)paren
id|st-&gt;ma.tei_m
dot
id|printdebug
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
l_string|&quot;id verify req(%d) for tei %d&quot;
comma
l_int|3
op_minus
id|st-&gt;ma.N202
comma
id|st-&gt;l2.tei
)paren
suffix:semicolon
id|put_tei_msg
c_func
(paren
id|st
comma
id|ID_VERIFY
comma
l_int|0
comma
id|st-&gt;l2.tei
)paren
suffix:semicolon
id|FsmAddTimer
c_func
(paren
op_amp
id|st-&gt;ma.t202
comma
id|st-&gt;ma.T202
comma
id|EV_T202
comma
l_int|NULL
comma
l_int|4
)paren
suffix:semicolon
)brace
r_else
(brace
id|st-&gt;ma.tei_m
dot
id|printdebug
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
l_string|&quot;verify req for tei %d failed&quot;
comma
id|st-&gt;l2.tei
)paren
suffix:semicolon
id|L3L2
c_func
(paren
id|st
comma
id|MDL_REMOVE
op_or
id|REQUEST
comma
l_int|0
)paren
suffix:semicolon
id|cs
op_assign
(paren
r_struct
id|IsdnCardState
op_star
)paren
id|st-&gt;l1.hardware
suffix:semicolon
id|cs
op_member_access_from_pointer
id|cardmsg
c_func
(paren
id|cs
comma
id|MDL_REMOVE
op_or
id|REQUEST
comma
l_int|NULL
)paren
suffix:semicolon
id|FsmChangeState
c_func
(paren
id|fi
comma
id|ST_TEI_NOP
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|tei_l1l2
id|tei_l1l2
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
r_int
id|mt
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|FLG_FIXED_TEI
comma
op_amp
id|st-&gt;l2.flag
)paren
)paren
(brace
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pr
op_eq
(paren
id|PH_DATA
op_or
id|INDICATION
)paren
)paren
(brace
r_if
c_cond
(paren
id|skb-&gt;len
OL
l_int|3
)paren
(brace
id|st-&gt;ma.tei_m
dot
id|printdebug
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
l_string|&quot;short mgr frame %ld/3&quot;
comma
id|skb-&gt;len
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|skb-&gt;data
(braket
l_int|0
)braket
op_ne
(paren
(paren
id|TEI_SAPI
op_lshift
l_int|2
)paren
op_or
l_int|2
)paren
)paren
op_logical_or
(paren
id|skb-&gt;data
(braket
l_int|1
)braket
op_ne
(paren
(paren
id|GROUP_TEI
op_lshift
l_int|1
)paren
op_or
l_int|1
)paren
)paren
)paren
(brace
id|st-&gt;ma.tei_m
dot
id|printdebug
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
l_string|&quot;wrong mgr sapi/tei %x/%x&quot;
comma
id|skb-&gt;data
(braket
l_int|0
)braket
comma
id|skb-&gt;data
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|skb-&gt;data
(braket
l_int|2
)braket
op_amp
l_int|0xef
)paren
op_ne
id|UI
)paren
(brace
id|st-&gt;ma.tei_m
dot
id|printdebug
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
l_string|&quot;mgr frame is not ui %x&quot;
comma
id|skb-&gt;data
(braket
l_int|2
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
id|skb_pull
c_func
(paren
id|skb
comma
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
OL
l_int|5
)paren
(brace
id|st-&gt;ma.tei_m
dot
id|printdebug
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
l_string|&quot;short mgr frame %ld/5&quot;
comma
id|skb-&gt;len
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|skb-&gt;data
(braket
l_int|0
)braket
op_ne
id|TEI_ENTITY_ID
)paren
(brace
multiline_comment|/* wrong management entity identifier, ignore */
id|st-&gt;ma.tei_m
dot
id|printdebug
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
l_string|&quot;tei handler wrong entity id %x&quot;
comma
id|skb-&gt;data
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
id|mt
op_assign
id|skb-&gt;data
(braket
l_int|3
)braket
suffix:semicolon
r_if
c_cond
(paren
id|mt
op_eq
id|ID_ASSIGNED
)paren
id|FsmEvent
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
id|EV_ASSIGN
comma
id|skb
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|mt
op_eq
id|ID_DENIED
)paren
id|FsmEvent
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
id|EV_DENIED
comma
id|skb
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|mt
op_eq
id|ID_CHK_REQ
)paren
id|FsmEvent
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
id|EV_CHKREQ
comma
id|skb
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|mt
op_eq
id|ID_REMOVE
)paren
id|FsmEvent
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
id|EV_REMOVE
comma
id|skb
)paren
suffix:semicolon
r_else
(brace
id|st-&gt;ma.tei_m
dot
id|printdebug
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
l_string|&quot;tei handler wrong mt %x&bslash;n&quot;
comma
id|mt
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
r_else
(brace
id|st-&gt;ma.tei_m
dot
id|printdebug
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
l_string|&quot;tei handler wrong pr %x&bslash;n&quot;
comma
id|pr
)paren
suffix:semicolon
)brace
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|tei_l2tei
id|tei_l2tei
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
id|IsdnCardState
op_star
id|cs
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|FLG_FIXED_TEI
comma
op_amp
id|st-&gt;l2.flag
)paren
)paren
(brace
r_if
c_cond
(paren
id|pr
op_eq
(paren
id|MDL_ASSIGN
op_or
id|INDICATION
)paren
)paren
(brace
r_if
c_cond
(paren
id|st-&gt;ma.debug
)paren
id|st-&gt;ma.tei_m
dot
id|printdebug
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
l_string|&quot;fixed assign tei %d&quot;
comma
id|st-&gt;l2.tei
)paren
suffix:semicolon
id|L3L2
c_func
(paren
id|st
comma
id|MDL_ASSIGN
op_or
id|REQUEST
comma
(paren
r_void
op_star
)paren
(paren
r_int
)paren
id|st-&gt;l2.tei
)paren
suffix:semicolon
id|cs
op_assign
(paren
r_struct
id|IsdnCardState
op_star
)paren
id|st-&gt;l1.hardware
suffix:semicolon
id|cs
op_member_access_from_pointer
id|cardmsg
c_func
(paren
id|cs
comma
id|MDL_ASSIGN
op_or
id|REQUEST
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|pr
)paren
(brace
r_case
(paren
id|MDL_ASSIGN
op_or
id|INDICATION
)paren
suffix:colon
id|FsmEvent
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
id|EV_IDREQ
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|MDL_ERROR
op_or
id|REQUEST
)paren
suffix:colon
id|FsmEvent
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
id|EV_VERIFY
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|tei_debug
id|tei_debug
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
l_string|&quot;tei &quot;
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
r_void
DECL|function|setstack_tei
id|setstack_tei
c_func
(paren
r_struct
id|PStack
op_star
id|st
)paren
(brace
id|st-&gt;l2.l2tei
op_assign
id|tei_l2tei
suffix:semicolon
id|st-&gt;ma.T202
op_assign
l_int|2000
suffix:semicolon
multiline_comment|/* T202  2000 milliseconds */
id|st-&gt;l1.l1tei
op_assign
id|tei_l1l2
suffix:semicolon
id|st-&gt;ma.debug
op_assign
l_int|1
suffix:semicolon
id|st-&gt;ma.tei_m.fsm
op_assign
op_amp
id|teifsm
suffix:semicolon
id|st-&gt;ma.tei_m.state
op_assign
id|ST_TEI_NOP
suffix:semicolon
id|st-&gt;ma.tei_m.debug
op_assign
l_int|1
suffix:semicolon
id|st-&gt;ma.tei_m.userdata
op_assign
id|st
suffix:semicolon
id|st-&gt;ma.tei_m.userint
op_assign
l_int|0
suffix:semicolon
id|st-&gt;ma.tei_m.printdebug
op_assign
id|tei_debug
suffix:semicolon
id|FsmInitTimer
c_func
(paren
op_amp
id|st-&gt;ma.tei_m
comma
op_amp
id|st-&gt;ma.t202
)paren
suffix:semicolon
)brace
r_void
DECL|function|init_tei
id|init_tei
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|protocol
)paren
(brace
)brace
r_void
DECL|function|release_tei
id|release_tei
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
r_struct
id|PStack
op_star
id|st
op_assign
id|cs-&gt;stlist
suffix:semicolon
r_while
c_loop
(paren
id|st
)paren
(brace
id|FsmDelTimer
c_func
(paren
op_amp
id|st-&gt;ma.t202
comma
l_int|1
)paren
suffix:semicolon
id|st
op_assign
id|st-&gt;next
suffix:semicolon
)brace
)brace
DECL|variable|__initdata
r_static
r_struct
id|FsmNode
id|TeiFnList
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|ST_TEI_NOP
comma
id|EV_IDREQ
comma
id|tei_id_request
)brace
comma
(brace
id|ST_TEI_NOP
comma
id|EV_ASSIGN
comma
id|tei_id_test_dup
)brace
comma
(brace
id|ST_TEI_NOP
comma
id|EV_VERIFY
comma
id|tei_id_verify
)brace
comma
(brace
id|ST_TEI_NOP
comma
id|EV_REMOVE
comma
id|tei_id_remove
)brace
comma
(brace
id|ST_TEI_NOP
comma
id|EV_CHKREQ
comma
id|tei_id_chk_req
)brace
comma
(brace
id|ST_TEI_IDREQ
comma
id|EV_T202
comma
id|tei_id_req_tout
)brace
comma
(brace
id|ST_TEI_IDREQ
comma
id|EV_ASSIGN
comma
id|tei_id_assign
)brace
comma
(brace
id|ST_TEI_IDREQ
comma
id|EV_DENIED
comma
id|tei_id_denied
)brace
comma
(brace
id|ST_TEI_IDVERIFY
comma
id|EV_T202
comma
id|tei_id_ver_tout
)brace
comma
(brace
id|ST_TEI_IDVERIFY
comma
id|EV_REMOVE
comma
id|tei_id_remove
)brace
comma
(brace
id|ST_TEI_IDVERIFY
comma
id|EV_CHKREQ
comma
id|tei_id_chk_req
)brace
comma
)brace
suffix:semicolon
DECL|macro|TEI_FN_COUNT
mdefine_line|#define TEI_FN_COUNT (sizeof(TeiFnList)/sizeof(struct FsmNode))
r_int
id|__init
DECL|function|TeiNew
id|TeiNew
c_func
(paren
r_void
)paren
(brace
id|teifsm.state_count
op_assign
id|TEI_STATE_COUNT
suffix:semicolon
id|teifsm.event_count
op_assign
id|TEI_EVENT_COUNT
suffix:semicolon
id|teifsm.strEvent
op_assign
id|strTeiEvent
suffix:semicolon
id|teifsm.strState
op_assign
id|strTeiState
suffix:semicolon
r_return
id|FsmNew
c_func
(paren
op_amp
id|teifsm
comma
id|TeiFnList
comma
id|TEI_FN_COUNT
)paren
suffix:semicolon
)brace
r_void
DECL|function|TeiFree
id|TeiFree
c_func
(paren
r_void
)paren
(brace
id|FsmFree
c_func
(paren
op_amp
id|teifsm
)paren
suffix:semicolon
)brace
eof
