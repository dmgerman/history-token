multiline_comment|/* net/atm/raw.c - Raw AAL0 and AAL5 transports */
multiline_comment|/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/atmdev.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &quot;common.h&quot;
macro_line|#include &quot;protocols.h&quot;
macro_line|#if 0
mdefine_line|#define DPRINTK(format,args...) printk(KERN_DEBUG format,##args)
macro_line|#else
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(format,args...)
macro_line|#endif
multiline_comment|/*&n; * SKB == NULL indicates that the link is being closed&n; */
DECL|function|atm_push_raw
r_static
r_void
id|atm_push_raw
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_if
c_cond
(paren
id|skb
)paren
(brace
r_struct
id|sock
op_star
id|sk
op_assign
id|sk_atm
c_func
(paren
id|vcc
)paren
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|sk-&gt;sk_receive_queue
comma
id|skb
)paren
suffix:semicolon
id|sk
op_member_access_from_pointer
id|sk_data_ready
c_func
(paren
id|sk
comma
id|skb-&gt;len
)paren
suffix:semicolon
)brace
)brace
DECL|function|atm_pop_raw
r_static
r_void
id|atm_pop_raw
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|sock
op_star
id|sk
op_assign
id|sk_atm
c_func
(paren
id|vcc
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;APopR (%d) %d -= %d&bslash;n&quot;
comma
id|vcc-&gt;vci
comma
id|sk-&gt;sk_wmem_alloc
comma
id|skb-&gt;truesize
)paren
suffix:semicolon
id|atomic_sub
c_func
(paren
id|skb-&gt;truesize
comma
op_amp
id|sk-&gt;sk_wmem_alloc
)paren
suffix:semicolon
id|dev_kfree_skb_any
c_func
(paren
id|skb
)paren
suffix:semicolon
id|sk
op_member_access_from_pointer
id|sk_write_space
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
DECL|function|atm_send_aal0
r_static
r_int
id|atm_send_aal0
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
multiline_comment|/*&n;&t; * Note that if vpi/vci are _ANY or _UNSPEC the below will&n;&t; * still work&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
op_logical_and
(paren
(paren
(paren
id|u32
op_star
)paren
id|skb-&gt;data
)paren
(braket
l_int|0
)braket
op_amp
(paren
id|ATM_HDR_VPI_MASK
op_or
id|ATM_HDR_VCI_MASK
)paren
)paren
op_ne
(paren
(paren
id|vcc-&gt;vpi
op_lshift
id|ATM_HDR_VPI_SHIFT
)paren
op_or
(paren
id|vcc-&gt;vci
op_lshift
id|ATM_HDR_VCI_SHIFT
)paren
)paren
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
id|EADDRNOTAVAIL
suffix:semicolon
)brace
r_return
id|vcc-&gt;dev-&gt;ops
op_member_access_from_pointer
id|send
c_func
(paren
id|vcc
comma
id|skb
)paren
suffix:semicolon
)brace
DECL|function|atm_init_aal0
r_int
id|atm_init_aal0
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
)paren
(brace
id|vcc-&gt;push
op_assign
id|atm_push_raw
suffix:semicolon
id|vcc-&gt;pop
op_assign
id|atm_pop_raw
suffix:semicolon
id|vcc-&gt;push_oam
op_assign
l_int|NULL
suffix:semicolon
id|vcc-&gt;send
op_assign
id|atm_send_aal0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|atm_init_aal34
r_int
id|atm_init_aal34
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
)paren
(brace
id|vcc-&gt;push
op_assign
id|atm_push_raw
suffix:semicolon
id|vcc-&gt;pop
op_assign
id|atm_pop_raw
suffix:semicolon
id|vcc-&gt;push_oam
op_assign
l_int|NULL
suffix:semicolon
id|vcc-&gt;send
op_assign
id|vcc-&gt;dev-&gt;ops-&gt;send
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|atm_init_aal5
r_int
id|atm_init_aal5
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
)paren
(brace
id|vcc-&gt;push
op_assign
id|atm_push_raw
suffix:semicolon
id|vcc-&gt;pop
op_assign
id|atm_pop_raw
suffix:semicolon
id|vcc-&gt;push_oam
op_assign
l_int|NULL
suffix:semicolon
id|vcc-&gt;send
op_assign
id|vcc-&gt;dev-&gt;ops-&gt;send
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|atm_init_aal5
id|EXPORT_SYMBOL
c_func
(paren
id|atm_init_aal5
)paren
suffix:semicolon
eof
