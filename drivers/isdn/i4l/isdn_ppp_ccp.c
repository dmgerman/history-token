multiline_comment|/* Linux ISDN subsystem, PPP CCP support&n; *&n; * Copyright 1994-1998  by Fritz Elfert (fritz@isdn4linux.de)&n; *           1995,96    by Thinking Objects Software GmbH Wuerzburg&n; *           1995,96    by Michael Hipp (Michael.Hipp@student.uni-tuebingen.de)&n; *           1999-2002  by Kai Germaschewski &lt;kai@germaschewski.name&gt;&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; */
macro_line|#include &quot;isdn_ppp_ccp.h&quot;
macro_line|#include &quot;isdn_common.h&quot;
macro_line|#include &quot;isdn_net_lib.h&quot;
macro_line|#include &quot;isdn_ppp.h&quot;
macro_line|#include &lt;linux/ppp-comp.h&gt;
multiline_comment|/* ====================================================================== */
DECL|enum|ippp_ccp_reset_states
r_enum
id|ippp_ccp_reset_states
(brace
DECL|enumerator|CCPResetIdle
id|CCPResetIdle
comma
DECL|enumerator|CCPResetSentReq
id|CCPResetSentReq
comma
DECL|enumerator|CCPResetRcvdReq
id|CCPResetRcvdReq
comma
DECL|enumerator|CCPResetSentAck
id|CCPResetSentAck
comma
DECL|enumerator|CCPResetRcvdAck
id|CCPResetRcvdAck
)brace
suffix:semicolon
DECL|struct|ippp_ccp_reset_state
r_struct
id|ippp_ccp_reset_state
(brace
DECL|member|state
r_enum
id|ippp_ccp_reset_states
id|state
suffix:semicolon
multiline_comment|/* State of this transaction */
DECL|member|ccp
r_struct
id|ippp_ccp
op_star
id|ccp
suffix:semicolon
multiline_comment|/* Backlink */
DECL|member|id
r_int
r_char
id|id
suffix:semicolon
multiline_comment|/* id index */
DECL|member|ta
r_int
r_char
id|ta
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* The timer is active (flag) */
DECL|member|expra
r_int
r_char
id|expra
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* We expect a ResetAck at all */
DECL|member|dlen
r_int
id|dlen
suffix:semicolon
multiline_comment|/* Databytes stored in data */
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
multiline_comment|/* For timeouts/retries */
multiline_comment|/* This is a hack but seems sufficient for the moment. We do not want&n;&t;   to have this be yet another allocation for some bytes, it is more&n;&t;   memory management overhead than the whole mess is worth. */
DECL|member|data
r_int
r_char
id|data
(braket
id|IPPP_RESET_MAXDATABYTES
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The data structure keeping track of the currently outstanding CCP Reset&n;   transactions. */
DECL|struct|ippp_ccp_reset
r_struct
id|ippp_ccp_reset
(brace
DECL|member|rs
r_struct
id|ippp_ccp_reset_state
op_star
id|rs
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* One per possible id */
DECL|member|lastid
r_int
r_char
id|lastid
suffix:semicolon
multiline_comment|/* Last id allocated */
)brace
suffix:semicolon
multiline_comment|/* In-kernel handling of CCP Reset-Request and Reset-Ack is necessary,&n;   but absolutely nontrivial. The most abstruse problem we are facing is&n;   that the generation, reception and all the handling of timeouts and&n;   resends including proper request id management should be entirely left&n;   to the (de)compressor, but indeed is not covered by the current API to&n;   the (de)compressor. The API is a prototype version from PPP where only&n;   some (de)compressors have yet been implemented and all of them are&n;   rather simple in their reset handling. Especially, their is only one&n;   outstanding ResetAck at a time with all of them and ResetReq/-Acks do&n;   not have parameters. For this very special case it was sufficient to&n;   just return an error code from the decompressor and have a single&n;   reset() entry to communicate all the necessary information between&n;   the framework and the (de)compressor. Bad enough, LZS is different&n;   (and any other compressor may be different, too). It has multiple&n;   histories (eventually) and needs to Reset each of them independently&n;   and thus uses multiple outstanding Acks and history numbers as an&n;   additional parameter to Reqs/Acks.&n;   All that makes it harder to port the reset state engine into the&n;   kernel because it is not just the same simple one as in (i)pppd but&n;   it must be able to pass additional parameters and have multiple out-&n;   standing Acks. We are trying to achieve the impossible by handling&n;   reset transactions independent by their id. The id MUST change when&n;   the data portion changes, thus any (de)compressor who uses more than&n;   one resettable state must provide and recognize individual ids for&n;   each individual reset transaction. The framework itself does _only_&n;   differentiate them by id, because it has no other semantics like the&n;   (de)compressor might.&n;   This looks like a major redesign of the interface would be nice,&n;   but I don&squot;t have an idea how to do it better. */
multiline_comment|/* ====================================================================== */
multiline_comment|/* Free a given state and clear everything up for later reallocation */
r_static
r_void
DECL|function|ippp_ccp_reset_free_state
id|ippp_ccp_reset_free_state
c_func
(paren
r_struct
id|ippp_ccp
op_star
id|ccp
comma
r_int
r_char
id|id
)paren
(brace
r_struct
id|ippp_ccp_reset_state
op_star
id|rs
op_assign
id|ccp-&gt;reset-&gt;rs
(braket
id|id
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rs
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|rs-&gt;ta
)paren
singleline_comment|// FIXME?
id|del_timer_sync
c_func
(paren
op_amp
id|rs-&gt;timer
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|rs
)paren
suffix:semicolon
id|ccp-&gt;reset-&gt;rs
(braket
id|id
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
r_static
r_void
DECL|function|do_xmit_reset
id|do_xmit_reset
c_func
(paren
r_struct
id|ippp_ccp
op_star
id|ccp
comma
r_int
r_char
id|code
comma
r_int
r_char
id|id
comma
r_int
r_char
op_star
id|data
comma
r_int
id|len
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
r_char
op_star
id|p
suffix:semicolon
id|u16
id|proto
op_assign
id|ccp-&gt;proto
op_eq
id|PPP_COMP
ques
c_cond
id|PPP_CCP
suffix:colon
id|PPP_CCPFRAG
suffix:semicolon
id|skb
op_assign
id|ccp
op_member_access_from_pointer
id|alloc_skb
c_func
(paren
id|ccp-&gt;priv
comma
l_int|4
op_plus
id|len
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
id|p
op_assign
id|skb_put
c_func
(paren
id|skb
comma
l_int|4
)paren
suffix:semicolon
id|p
op_add_assign
id|put_u8
(paren
id|p
comma
id|code
)paren
suffix:semicolon
id|p
op_add_assign
id|put_u8
(paren
id|p
comma
id|id
)paren
suffix:semicolon
id|p
op_add_assign
id|put_u16
c_func
(paren
id|p
comma
id|len
op_plus
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
)paren
id|memcpy
c_func
(paren
id|skb_put
c_func
(paren
id|skb
comma
id|len
)paren
comma
id|data
comma
id|len
)paren
suffix:semicolon
id|isdn_ppp_frame_log
c_func
(paren
l_string|&quot;ccp-xmit&quot;
comma
id|skb-&gt;data
comma
id|skb-&gt;len
comma
l_int|32
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|ccp
op_member_access_from_pointer
id|xmit
c_func
(paren
id|ccp-&gt;priv
comma
id|skb
comma
id|proto
)paren
suffix:semicolon
)brace
multiline_comment|/* The timer callback function which is called when a ResetReq has timed out,&n;   aka has never been answered by a ResetAck */
r_static
r_void
DECL|function|isdn_ppp_ccp_timer_callback
id|isdn_ppp_ccp_timer_callback
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_struct
id|ippp_ccp_reset_state
op_star
id|rs
op_assign
(paren
r_struct
id|ippp_ccp_reset_state
op_star
)paren
id|data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rs-&gt;ta
)paren
(brace
id|isdn_BUG
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rs-&gt;state
op_ne
id|CCPResetSentReq
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ippp_ccp: timer cb in wrong state %d&bslash;n&quot;
comma
id|rs-&gt;state
)paren
suffix:semicolon
id|rs-&gt;ta
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* We are correct here */
r_if
c_cond
(paren
op_logical_neg
id|rs-&gt;expra
)paren
(brace
multiline_comment|/* Hmm, there is no Ack really expected. We can clean&n;&t;&t;   up the state now, it will be reallocated if the&n;&t;&t;   decompressor insists on another reset */
id|rs-&gt;ta
op_assign
l_int|0
suffix:semicolon
id|ippp_ccp_reset_free_state
c_func
(paren
id|rs-&gt;ccp
comma
id|rs-&gt;id
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ippp_ccp: CCP Reset timed out for id %d&bslash;n&quot;
comma
id|rs-&gt;id
)paren
suffix:semicolon
multiline_comment|/* Push it again */
id|do_xmit_reset
c_func
(paren
id|rs-&gt;ccp
comma
id|CCP_RESETREQ
comma
id|rs-&gt;id
comma
id|rs-&gt;data
comma
id|rs-&gt;dlen
)paren
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|rs-&gt;timer
comma
id|jiffies
op_plus
l_int|5
op_star
id|HZ
)paren
suffix:semicolon
)brace
multiline_comment|/* Allocate a new reset transaction state */
r_static
r_struct
id|ippp_ccp_reset_state
op_star
DECL|function|ippp_ccp_reset_alloc_state
id|ippp_ccp_reset_alloc_state
c_func
(paren
r_struct
id|ippp_ccp
op_star
id|ccp
comma
r_int
r_char
id|id
)paren
(brace
r_struct
id|ippp_ccp_reset_state
op_star
id|rs
suffix:semicolon
id|rs
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ippp_ccp_reset_state
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rs
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|rs
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ippp_ccp_reset_state
)paren
)paren
suffix:semicolon
id|rs-&gt;state
op_assign
id|CCPResetIdle
suffix:semicolon
id|rs-&gt;ccp
op_assign
id|ccp
suffix:semicolon
id|rs-&gt;id
op_assign
id|id
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|rs-&gt;timer
)paren
suffix:semicolon
id|rs-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|rs
suffix:semicolon
id|rs-&gt;timer.function
op_assign
id|isdn_ppp_ccp_timer_callback
suffix:semicolon
id|ccp-&gt;reset-&gt;rs
(braket
id|id
)braket
op_assign
id|rs
suffix:semicolon
r_return
id|rs
suffix:semicolon
)brace
multiline_comment|/* A decompressor wants a reset with a set of parameters - do what is&n;   necessary to fulfill it */
r_static
r_void
DECL|function|ippp_ccp_reset_xmit
id|ippp_ccp_reset_xmit
c_func
(paren
r_struct
id|ippp_ccp
op_star
id|ccp
comma
r_struct
id|isdn_ppp_resetparams
op_star
id|rp
)paren
(brace
r_struct
id|ippp_ccp_reset_state
op_star
id|rs
suffix:semicolon
r_int
id|id
suffix:semicolon
r_if
c_cond
(paren
id|rp-&gt;valid
)paren
(brace
multiline_comment|/* The decompressor defines parameters by itself */
r_if
c_cond
(paren
op_logical_neg
id|rp-&gt;rsend
)paren
r_return
suffix:semicolon
multiline_comment|/* And it wants us to send a request */
r_if
c_cond
(paren
op_logical_neg
id|rp-&gt;idval
)paren
(brace
id|isdn_BUG
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|id
op_assign
id|rp-&gt;id
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* The reset params are invalid. The decompressor does not&n;&t;&t;   care about them, so we just send the minimal requests&n;&t;&t;   and increase ids only when an Ack is received for a&n;&t;&t;   given id */
id|id
op_assign
id|ccp-&gt;reset-&gt;lastid
op_increment
suffix:semicolon
multiline_comment|/* We always expect an Ack if the decompressor doesnt&n;&t;&t;   know&t;better */
id|rp-&gt;expra
op_assign
l_int|1
suffix:semicolon
id|rp-&gt;dtval
op_assign
l_int|0
suffix:semicolon
)brace
id|rs
op_assign
id|ccp-&gt;reset-&gt;rs
(braket
id|id
)braket
suffix:semicolon
r_if
c_cond
(paren
id|rs
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ippp_ccp: reset xmit in wrong state %d &quot;
l_string|&quot;for id %d (%d)&bslash;n&quot;
comma
id|rs-&gt;state
comma
id|id
comma
id|rs-&gt;ta
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Ok, this is a new transaction */
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ippp_ccp: new xmit for id %d&bslash;n&quot;
comma
id|id
)paren
suffix:semicolon
id|rs
op_assign
id|ippp_ccp_reset_alloc_state
c_func
(paren
id|ccp
comma
id|id
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rs
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ippp_ccp: out of mem allocing ccp trans&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|rs-&gt;expra
op_assign
id|rp-&gt;expra
suffix:semicolon
id|rs-&gt;id
op_assign
id|id
suffix:semicolon
r_if
c_cond
(paren
id|rp-&gt;dtval
)paren
(brace
id|rs-&gt;dlen
op_assign
id|rp-&gt;dlen
suffix:semicolon
id|memcpy
c_func
(paren
id|rs-&gt;data
comma
id|rp-&gt;data
comma
id|rp-&gt;dlen
)paren
suffix:semicolon
)brace
r_else
(brace
id|rs-&gt;dlen
op_assign
l_int|0
suffix:semicolon
)brace
id|rs-&gt;state
op_assign
id|CCPResetSentReq
suffix:semicolon
id|do_xmit_reset
c_func
(paren
id|rs-&gt;ccp
comma
id|CCP_RESETREQ
comma
id|rs-&gt;id
comma
id|rs-&gt;data
comma
id|rs-&gt;dlen
)paren
suffix:semicolon
multiline_comment|/* Start the timer */
id|rs-&gt;timer.expires
op_assign
id|jiffies
op_plus
l_int|5
op_star
id|HZ
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|rs-&gt;timer
)paren
suffix:semicolon
id|rs-&gt;ta
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* ====================================================================== */
r_struct
id|ippp_ccp
op_star
DECL|function|ippp_ccp_alloc
id|ippp_ccp_alloc
c_func
(paren
r_void
)paren
(brace
r_struct
id|ippp_ccp
op_star
id|ccp
suffix:semicolon
id|ccp
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|ccp
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
singleline_comment|// FIXME
r_if
c_cond
(paren
op_logical_neg
id|ccp
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|ccp
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|ccp
)paren
)paren
suffix:semicolon
id|ccp-&gt;mru
op_assign
l_int|1524
suffix:semicolon
multiline_comment|/* MRU, default 1524 */
id|ccp-&gt;reset
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|ccp-&gt;reset
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
singleline_comment|// FIXME alloc together?
r_if
c_cond
(paren
op_logical_neg
id|ccp-&gt;reset
)paren
(brace
id|kfree
c_func
(paren
id|ccp
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|ccp-&gt;reset
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|ccp-&gt;reset
)paren
)paren
suffix:semicolon
r_return
id|ccp
suffix:semicolon
)brace
r_void
DECL|function|ippp_ccp_free
id|ippp_ccp_free
c_func
(paren
r_struct
id|ippp_ccp
op_star
id|ccp
)paren
(brace
r_int
id|id
suffix:semicolon
r_if
c_cond
(paren
id|ccp-&gt;comp_stat
)paren
id|ccp-&gt;compressor
op_member_access_from_pointer
id|free
c_func
(paren
id|ccp-&gt;comp_stat
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ccp-&gt;decomp_stat
)paren
id|ccp-&gt;decompressor
op_member_access_from_pointer
id|free
c_func
(paren
id|ccp-&gt;decomp_stat
)paren
suffix:semicolon
r_for
c_loop
(paren
id|id
op_assign
l_int|0
suffix:semicolon
id|id
OL
l_int|256
suffix:semicolon
id|id
op_increment
)paren
(brace
r_if
c_cond
(paren
id|ccp-&gt;reset-&gt;rs
(braket
id|id
)braket
)paren
id|ippp_ccp_reset_free_state
c_func
(paren
id|ccp
comma
id|id
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|ccp-&gt;reset
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ccp
)paren
suffix:semicolon
)brace
r_int
DECL|function|ippp_ccp_set_mru
id|ippp_ccp_set_mru
c_func
(paren
r_struct
id|ippp_ccp
op_star
id|ccp
comma
r_int
r_int
id|mru
)paren
(brace
id|ccp-&gt;mru
op_assign
id|mru
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
r_int
DECL|function|ippp_ccp_get_flags
id|ippp_ccp_get_flags
c_func
(paren
r_struct
id|ippp_ccp
op_star
id|ccp
)paren
(brace
r_return
id|ccp-&gt;compflags
op_amp
(paren
id|SC_DC_ERROR
op_or
id|SC_DC_FERROR
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * compress a frame &n; * returns original skb if we did not compress the frame&n; * and a new skb otherwise&n; */
r_struct
id|sk_buff
op_star
DECL|function|ippp_ccp_compress
id|ippp_ccp_compress
c_func
(paren
r_struct
id|ippp_ccp
op_star
id|ccp
comma
r_struct
id|sk_buff
op_star
id|skb_in
comma
id|u16
op_star
id|proto
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
id|ccp-&gt;compflags
op_amp
(paren
id|SC_COMP_ON
op_or
id|SC_DECOMP_ON
)paren
)paren
)paren
(brace
multiline_comment|/* We send compressed only if both down- und upstream&n;&t;&t;   compression is negotiated, that means, CCP is up */
r_return
id|skb_in
suffix:semicolon
)brace
multiline_comment|/* we do not compress control protocols */
r_if
c_cond
(paren
op_star
id|proto
OG
l_int|0x3fff
)paren
(brace
r_return
id|skb_in
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ccp-&gt;compressor
op_logical_or
op_logical_neg
id|ccp-&gt;comp_stat
)paren
(brace
id|isdn_BUG
c_func
(paren
)paren
suffix:semicolon
r_return
id|skb_in
suffix:semicolon
)brace
multiline_comment|/* Allow for at least 150 % expansion (for now) */
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|skb_in-&gt;len
op_star
l_int|2
op_plus
id|skb_headroom
c_func
(paren
id|skb_in
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
r_return
id|skb_in
suffix:semicolon
id|skb_reserve
c_func
(paren
id|skb
comma
id|skb_headroom
c_func
(paren
id|skb_in
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ccp-&gt;compressor
op_member_access_from_pointer
id|compress
c_func
(paren
id|ccp-&gt;comp_stat
comma
id|skb_in
comma
id|skb
comma
op_star
id|proto
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
id|skb_in
suffix:semicolon
)brace
id|isdn_ppp_frame_log
c_func
(paren
l_string|&quot;comp  in:&quot;
comma
id|skb_in-&gt;data
comma
id|skb_in-&gt;len
comma
l_int|20
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|isdn_ppp_frame_log
c_func
(paren
l_string|&quot;comp out:&quot;
comma
id|skb-&gt;data
comma
id|skb-&gt;len
comma
l_int|20
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|skb_in
)paren
suffix:semicolon
op_star
id|proto
op_assign
id|ccp-&gt;proto
suffix:semicolon
r_return
id|skb
suffix:semicolon
)brace
multiline_comment|/* &n; * decompress packet&n; *&n; * proto is updated to protocol field of uncompressed packet.&n; * retval: decompressed packet,&n; *         same packet if uncompressed,&n; *&t;   NULL if decompression error&n; */
r_struct
id|sk_buff
op_star
DECL|function|ippp_ccp_decompress
id|ippp_ccp_decompress
c_func
(paren
r_struct
id|ippp_ccp
op_star
id|ccp
comma
r_struct
id|sk_buff
op_star
id|skb_in
comma
id|u16
op_star
id|proto
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_struct
id|isdn_ppp_resetparams
id|rsparm
suffix:semicolon
r_int
r_char
id|rsdata
(braket
id|IPPP_RESET_MAXDATABYTES
)braket
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ccp-&gt;compflags
op_amp
id|SC_DECOMP_ON
)paren
)paren
(brace
r_return
id|skb_in
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ccp-&gt;decompressor
op_logical_or
op_logical_neg
id|ccp-&gt;decomp_stat
)paren
(brace
id|isdn_BUG
c_func
(paren
)paren
suffix:semicolon
r_return
id|skb_in
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|proto
op_ne
id|ccp-&gt;proto
)paren
(brace
multiline_comment|/* uncompressed packets are fed through the decompressor to&n;&t;&t; * update the decompressor state */
id|ccp-&gt;decompressor
op_member_access_from_pointer
id|incomp
c_func
(paren
id|ccp-&gt;decomp_stat
comma
id|skb_in
comma
op_star
id|proto
)paren
suffix:semicolon
r_return
id|skb_in
suffix:semicolon
)brace
id|skb
op_assign
id|dev_alloc_skb
c_func
(paren
id|ccp-&gt;mru
op_plus
id|PPP_HDRLEN
)paren
suffix:semicolon
singleline_comment|// FIXME oom?
singleline_comment|// Set up reset params for the decompressor
id|memset
c_func
(paren
op_amp
id|rsparm
comma
l_int|0
comma
r_sizeof
(paren
id|rsparm
)paren
)paren
suffix:semicolon
id|rsparm.data
op_assign
id|rsdata
suffix:semicolon
id|rsparm.maxdlen
op_assign
id|IPPP_RESET_MAXDATABYTES
suffix:semicolon
id|len
op_assign
id|ccp-&gt;decompressor
op_member_access_from_pointer
id|decompress
c_func
(paren
id|ccp-&gt;decomp_stat
comma
id|skb_in
comma
id|skb
comma
op_amp
id|rsparm
)paren
suffix:semicolon
id|isdn_ppp_frame_log
c_func
(paren
l_string|&quot;deco  in:&quot;
comma
id|skb_in-&gt;data
comma
id|skb_in-&gt;len
comma
l_int|20
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|isdn_ppp_frame_log
c_func
(paren
l_string|&quot;deco out:&quot;
comma
id|skb-&gt;data
comma
id|skb-&gt;len
comma
l_int|20
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb_in
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
l_int|0
)paren
(brace
r_switch
c_cond
(paren
id|len
)paren
(brace
r_case
id|DECOMP_ERROR
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ippp: decomp wants reset with%s params&bslash;n&quot;
comma
id|rsparm.valid
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;out&quot;
)paren
suffix:semicolon
id|ippp_ccp_reset_xmit
c_func
(paren
id|ccp
comma
op_amp
id|rsparm
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DECOMP_FATALERROR
suffix:colon
id|ccp-&gt;compflags
op_or_assign
id|SC_DC_FERROR
suffix:semicolon
multiline_comment|/* Kick ipppd to recognize the error */
id|ccp
op_member_access_from_pointer
id|kick_up
c_func
(paren
id|ccp-&gt;priv
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|isdn_ppp_strip_proto
c_func
(paren
id|skb
comma
id|proto
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
l_int|NULL
suffix:semicolon
)brace
r_return
id|skb
suffix:semicolon
)brace
multiline_comment|/* An Ack was received for this id. This means we stop the timer and clean&n;   up the state prior to calling the decompressors reset routine. */
r_static
r_void
DECL|function|isdn_ppp_ccp_reset_ack_rcvd
id|isdn_ppp_ccp_reset_ack_rcvd
c_func
(paren
r_struct
id|ippp_ccp
op_star
id|ccp
comma
r_int
r_char
id|id
)paren
(brace
r_struct
id|ippp_ccp_reset_state
op_star
id|rs
op_assign
id|ccp-&gt;reset-&gt;rs
(braket
id|id
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rs
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ippp_ccp: ResetAck received for unknown id&quot;
l_string|&quot; %d&bslash;n&quot;
comma
id|id
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rs-&gt;ta
op_logical_and
id|rs-&gt;state
op_eq
id|CCPResetSentReq
)paren
(brace
multiline_comment|/* Great, we are correct */
r_if
c_cond
(paren
op_logical_neg
id|rs-&gt;expra
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ippp_ccp: ResetAck received&quot;
l_string|&quot; for id %d but not expected&bslash;n&quot;
comma
id|id
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ippp_ccp: ResetAck received out of&quot;
l_string|&quot;sync for id %d&bslash;n&quot;
comma
id|id
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rs-&gt;ta
)paren
(brace
id|rs-&gt;ta
op_assign
l_int|0
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|rs-&gt;timer
)paren
suffix:semicolon
)brace
id|ippp_ccp_reset_free_state
c_func
(paren
id|ccp
comma
id|id
)paren
suffix:semicolon
)brace
r_void
DECL|function|ippp_ccp_receive_ccp
id|ippp_ccp_receive_ccp
c_func
(paren
r_struct
id|ippp_ccp
op_star
id|ccp
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|len
suffix:semicolon
r_struct
id|isdn_ppp_resetparams
id|rsparm
suffix:semicolon
r_int
r_char
id|rsdata
(braket
id|IPPP_RESET_MAXDATABYTES
)braket
suffix:semicolon
id|isdn_ppp_frame_log
c_func
(paren
l_string|&quot;ccp-recv&quot;
comma
id|skb-&gt;data
comma
id|skb-&gt;len
comma
l_int|32
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|skb-&gt;data
(braket
l_int|0
)braket
)paren
(brace
r_case
id|CCP_CONFREQ
suffix:colon
r_if
c_cond
(paren
id|ccp-&gt;debug
op_amp
l_int|0x10
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Disable compression here!&bslash;n&quot;
)paren
suffix:semicolon
id|ccp-&gt;compflags
op_and_assign
op_complement
id|SC_COMP_ON
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CCP_TERMREQ
suffix:colon
r_case
id|CCP_TERMACK
suffix:colon
r_if
c_cond
(paren
id|ccp-&gt;debug
op_amp
l_int|0x10
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Disable (de)compression here!&bslash;n&quot;
)paren
suffix:semicolon
id|ccp-&gt;compflags
op_and_assign
op_complement
(paren
id|SC_DECOMP_ON
op_or
id|SC_COMP_ON
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CCP_CONFACK
suffix:colon
multiline_comment|/* if we RECEIVE an ackowledge we enable the decompressor */
r_if
c_cond
(paren
id|ccp-&gt;debug
op_amp
l_int|0x10
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Enable decompression here!&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ccp-&gt;decomp_stat
)paren
r_break
suffix:semicolon
id|ccp-&gt;compflags
op_or_assign
id|SC_DECOMP_ON
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CCP_RESETACK
suffix:colon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Received ResetAck from peer&bslash;n&quot;
)paren
suffix:semicolon
id|len
op_assign
(paren
id|skb-&gt;data
(braket
l_int|2
)braket
op_lshift
l_int|8
)paren
op_or
id|skb-&gt;data
(braket
l_int|3
)braket
suffix:semicolon
id|len
op_sub_assign
l_int|4
suffix:semicolon
multiline_comment|/* If a reset Ack was outstanding for this id, then&n;&t;&t;   clean up the state engine */
id|isdn_ppp_ccp_reset_ack_rcvd
c_func
(paren
id|ccp
comma
id|skb-&gt;data
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ccp-&gt;decomp_stat
)paren
id|ccp-&gt;decompressor
op_member_access_from_pointer
id|reset
c_func
(paren
id|ccp-&gt;decomp_stat
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
comma
id|len
ques
c_cond
op_amp
id|skb-&gt;data
(braket
l_int|4
)braket
suffix:colon
l_int|NULL
comma
id|len
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* TODO: This is not easy to decide here */
id|ccp-&gt;compflags
op_and_assign
op_complement
id|SC_DECOMP_DISCARD
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CCP_RESETREQ
suffix:colon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Received ResetReq from peer&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Receiving a ResetReq means we must reset our compressor */
multiline_comment|/* Set up reset params for the reset entry */
id|memset
c_func
(paren
op_amp
id|rsparm
comma
l_int|0
comma
r_sizeof
(paren
id|rsparm
)paren
)paren
suffix:semicolon
id|rsparm.data
op_assign
id|rsdata
suffix:semicolon
id|rsparm.maxdlen
op_assign
id|IPPP_RESET_MAXDATABYTES
suffix:semicolon
multiline_comment|/* Isolate data length */
id|len
op_assign
(paren
id|skb-&gt;data
(braket
l_int|2
)braket
op_lshift
l_int|8
)paren
op_or
id|skb-&gt;data
(braket
l_int|3
)braket
suffix:semicolon
id|len
op_sub_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|ccp-&gt;comp_stat
)paren
id|ccp-&gt;compressor
op_member_access_from_pointer
id|reset
c_func
(paren
id|ccp-&gt;comp_stat
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
comma
id|len
ques
c_cond
op_amp
id|skb-&gt;data
(braket
l_int|4
)braket
suffix:colon
l_int|NULL
comma
id|len
comma
op_amp
id|rsparm
)paren
suffix:semicolon
multiline_comment|/* Ack the Req as specified by rsparm */
r_if
c_cond
(paren
id|rsparm.valid
)paren
(brace
multiline_comment|/* Compressor reset handler decided how to answer */
r_if
c_cond
(paren
op_logical_neg
id|rsparm.rsend
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ResetAck suppressed&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* We should send a Frame */
id|do_xmit_reset
c_func
(paren
id|ccp
comma
id|CCP_RESETACK
comma
id|rsparm.idval
ques
c_cond
id|rsparm.id
suffix:colon
id|skb-&gt;data
(braket
l_int|1
)braket
comma
id|rsparm.data
comma
id|rsparm.dtval
ques
c_cond
id|rsparm.dlen
suffix:colon
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* We answer with a straight reflected Ack */
id|do_xmit_reset
c_func
(paren
id|ccp
comma
id|CCP_RESETACK
comma
id|skb-&gt;data
(braket
l_int|1
)braket
comma
id|skb-&gt;data
op_plus
l_int|4
comma
id|len
)paren
suffix:semicolon
)brace
)brace
r_void
DECL|function|ippp_ccp_send_ccp
id|ippp_ccp_send_ccp
c_func
(paren
r_struct
id|ippp_ccp
op_star
id|ccp
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|isdn_ppp_frame_log
c_func
(paren
l_string|&quot;ccp-xmit&quot;
comma
id|skb-&gt;data
comma
id|skb-&gt;len
comma
l_int|32
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|skb-&gt;data
(braket
l_int|2
)braket
)paren
(brace
r_case
id|CCP_CONFREQ
suffix:colon
r_if
c_cond
(paren
id|ccp-&gt;debug
op_amp
l_int|0x10
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Disable decompression here!&bslash;n&quot;
)paren
suffix:semicolon
id|ccp-&gt;compflags
op_and_assign
op_complement
id|SC_DECOMP_ON
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CCP_TERMREQ
suffix:colon
r_case
id|CCP_TERMACK
suffix:colon
r_if
c_cond
(paren
id|ccp-&gt;debug
op_amp
l_int|0x10
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Disable (de)compression here!&bslash;n&quot;
)paren
suffix:semicolon
id|ccp-&gt;compflags
op_and_assign
op_complement
(paren
id|SC_DECOMP_ON
op_or
id|SC_COMP_ON
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CCP_CONFACK
suffix:colon
multiline_comment|/* if we SEND an ackowledge we can/must enable the compressor */
r_if
c_cond
(paren
id|ccp-&gt;debug
op_amp
l_int|0x10
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Enable compression here!&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ccp-&gt;compressor
)paren
r_break
suffix:semicolon
id|ccp-&gt;compflags
op_or_assign
id|SC_COMP_ON
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CCP_RESETACK
suffix:colon
multiline_comment|/* If we send a ACK we should reset our compressor */
r_if
c_cond
(paren
id|ccp-&gt;debug
op_amp
l_int|0x10
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Reset decompression state here!&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ResetAck from daemon passed by&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ccp-&gt;comp_stat
)paren
r_break
suffix:semicolon
id|ccp-&gt;compressor
op_member_access_from_pointer
id|reset
c_func
(paren
id|ccp-&gt;comp_stat
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
id|ccp-&gt;compflags
op_and_assign
op_complement
id|SC_COMP_DISCARD
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CCP_RESETREQ
suffix:colon
multiline_comment|/* Just let it pass by */
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ResetReq from daemon passed by&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|variable|ipc_head
r_static
r_struct
id|isdn_ppp_compressor
op_star
id|ipc_head
op_assign
l_int|NULL
suffix:semicolon
r_int
DECL|function|ippp_ccp_set_compressor
id|ippp_ccp_set_compressor
c_func
(paren
r_struct
id|ippp_ccp
op_star
id|ccp
comma
r_int
id|unit
comma
r_struct
id|isdn_ppp_comp_data
op_star
id|data
)paren
(brace
r_struct
id|isdn_ppp_compressor
op_star
id|ipc
op_assign
id|ipc_head
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_void
op_star
id|stat
suffix:semicolon
r_int
id|num
op_assign
id|data-&gt;num
suffix:semicolon
r_if
c_cond
(paren
id|ccp-&gt;debug
op_amp
l_int|0x10
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;[%d] Set %scompressor type %d&bslash;n&quot;
comma
id|unit
comma
id|data-&gt;flags
op_amp
id|IPPP_COMP_FLAG_XMIT
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;de&quot;
comma
id|num
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ipc
op_assign
id|ipc_head
suffix:semicolon
id|ipc
suffix:semicolon
id|ipc
op_assign
id|ipc-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|ipc-&gt;num
op_ne
id|num
)paren
r_continue
suffix:semicolon
id|stat
op_assign
id|ipc
op_member_access_from_pointer
id|alloc
c_func
(paren
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|stat
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Can&squot;t alloc (de)compression!&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ret
op_assign
id|ipc
op_member_access_from_pointer
id|init
c_func
(paren
id|stat
comma
id|data
comma
id|unit
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Can&squot;t init (de)compression!&bslash;n&quot;
)paren
suffix:semicolon
id|ipc
op_member_access_from_pointer
id|free
c_func
(paren
id|stat
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|data-&gt;flags
op_amp
id|IPPP_COMP_FLAG_XMIT
)paren
(brace
r_if
c_cond
(paren
id|ccp-&gt;comp_stat
)paren
id|ccp-&gt;compressor
op_member_access_from_pointer
id|free
c_func
(paren
id|ccp-&gt;comp_stat
)paren
suffix:semicolon
id|ccp-&gt;comp_stat
op_assign
id|stat
suffix:semicolon
id|ccp-&gt;compressor
op_assign
id|ipc
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|ccp-&gt;decomp_stat
)paren
id|ccp-&gt;decompressor
op_member_access_from_pointer
id|free
c_func
(paren
id|ccp-&gt;decomp_stat
)paren
suffix:semicolon
id|ccp-&gt;decomp_stat
op_assign
id|stat
suffix:semicolon
id|ccp-&gt;decompressor
op_assign
id|ipc
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_void
DECL|function|ippp_ccp_get_compressors
id|ippp_ccp_get_compressors
c_func
(paren
r_int
r_int
id|protos
(braket
l_int|8
)braket
)paren
(brace
r_struct
id|isdn_ppp_compressor
op_star
id|ipc
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
id|memset
c_func
(paren
id|protos
comma
l_int|0
comma
r_sizeof
(paren
r_int
r_int
)paren
op_star
l_int|8
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ipc
op_assign
id|ipc_head
suffix:semicolon
id|ipc
suffix:semicolon
id|ipc
op_assign
id|ipc-&gt;next
)paren
(brace
id|j
op_assign
id|ipc-&gt;num
op_div
(paren
r_sizeof
(paren
r_int
)paren
op_star
l_int|8
)paren
suffix:semicolon
id|i
op_assign
id|ipc-&gt;num
op_mod
(paren
r_sizeof
(paren
r_int
)paren
op_star
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|j
OL
l_int|8
)paren
id|protos
(braket
id|j
)braket
op_or_assign
l_int|1
op_lshift
id|i
suffix:semicolon
)brace
)brace
r_int
DECL|function|isdn_ppp_register_compressor
id|isdn_ppp_register_compressor
c_func
(paren
r_struct
id|isdn_ppp_compressor
op_star
id|ipc
)paren
(brace
id|ipc-&gt;next
op_assign
id|ipc_head
suffix:semicolon
id|ipc-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|ipc_head
)paren
(brace
id|ipc_head-&gt;prev
op_assign
id|ipc
suffix:semicolon
)brace
id|ipc_head
op_assign
id|ipc
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|isdn_ppp_unregister_compressor
id|isdn_ppp_unregister_compressor
c_func
(paren
r_struct
id|isdn_ppp_compressor
op_star
id|ipc
)paren
(brace
r_if
c_cond
(paren
id|ipc-&gt;prev
)paren
id|ipc-&gt;prev-&gt;next
op_assign
id|ipc-&gt;next
suffix:semicolon
r_else
id|ipc_head
op_assign
id|ipc-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|ipc-&gt;next
)paren
id|ipc-&gt;next-&gt;prev
op_assign
id|ipc-&gt;prev
suffix:semicolon
id|ipc-&gt;prev
op_assign
id|ipc-&gt;next
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
