multiline_comment|/* net/atm/pppoatm.c - RFC2364 PPP over ATM/AAL5 */
multiline_comment|/* Copyright 1999-2000 by Mitchell Blank Jr */
multiline_comment|/* Based on clip.c; 1995-1999 by Werner Almesberger, EPFL LRC/ICA */
multiline_comment|/* And on ppp_async.c; Copyright 1999 Paul Mackerras */
multiline_comment|/* And help from Jens Axboe */
multiline_comment|/*&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; *&n; * This driver provides the encapsulation and framing for sending&n; * and receiving PPP frames in ATM AAL5 PDUs.&n; */
multiline_comment|/*&n; * One shortcoming of this driver is that it does not comply with&n; * section 8 of RFC2364 - we are supposed to detect a change&n; * in encapsulation and immediately abort the connection (in order&n; * to avoid a black-hole being created if our peer loses state&n; * and changes encapsulation unilaterally.  However, since the&n; * ppp_generic layer actually does the decapsulation, we need&n; * a way of notifying it when we _think_ there might be a problem)&n; * There&squot;s two cases:&n; *   1.&t;LLC-encapsulation was missing when it was enabled.  In&n; *&t;this case, we should tell the upper layer &quot;tear down&n; *&t;this session if this skb looks ok to you&quot;&n; *   2.&t;LLC-encapsulation was present when it was disabled.  Then&n; *&t;we need to tell the upper layer &quot;this packet may be&n; *&t;ok, but if its in error tear down the session&quot;&n; * These hooks are not yet available in ppp_generic&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/atm.h&gt;
macro_line|#include &lt;linux/atmdev.h&gt;
macro_line|#include &lt;linux/ppp_defs.h&gt;
macro_line|#include &lt;linux/if_ppp.h&gt;
macro_line|#include &lt;linux/ppp_channel.h&gt;
macro_line|#include &lt;linux/atmppp.h&gt;
macro_line|#include &quot;common.h&quot;
macro_line|#if 0
mdefine_line|#define DPRINTK(format, args...) &bslash;&n;&t;printk(KERN_DEBUG &quot;pppoatm: &quot; format, ##args)
macro_line|#else
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(format, args...)
macro_line|#endif
DECL|enum|pppoatm_encaps
r_enum
id|pppoatm_encaps
(brace
DECL|enumerator|e_autodetect
id|e_autodetect
op_assign
id|PPPOATM_ENCAPS_AUTODETECT
comma
DECL|enumerator|e_vc
id|e_vc
op_assign
id|PPPOATM_ENCAPS_VC
comma
DECL|enumerator|e_llc
id|e_llc
op_assign
id|PPPOATM_ENCAPS_LLC
comma
)brace
suffix:semicolon
DECL|struct|pppoatm_vcc
r_struct
id|pppoatm_vcc
(brace
DECL|member|atmvcc
r_struct
id|atm_vcc
op_star
id|atmvcc
suffix:semicolon
multiline_comment|/* VCC descriptor */
DECL|member|old_push
r_void
(paren
op_star
id|old_push
)paren
(paren
r_struct
id|atm_vcc
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
DECL|member|old_pop
r_void
(paren
op_star
id|old_pop
)paren
(paren
r_struct
id|atm_vcc
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
multiline_comment|/* keep old push/pop for detaching */
DECL|member|encaps
r_enum
id|pppoatm_encaps
id|encaps
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* SC_COMP_PROT - compress protocol */
DECL|member|chan
r_struct
id|ppp_channel
id|chan
suffix:semicolon
multiline_comment|/* interface to generic ppp layer */
DECL|member|wakeup_tasklet
r_struct
id|tasklet_struct
id|wakeup_tasklet
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Header used for LLC Encapsulated PPP (4 bytes) followed by the LCP protocol&n; * ID (0xC021) used in autodetection&n; */
DECL|variable|pppllc
r_static
r_const
r_int
r_char
id|pppllc
(braket
l_int|6
)braket
op_assign
(brace
l_int|0xFE
comma
l_int|0xFE
comma
l_int|0x03
comma
l_int|0xCF
comma
l_int|0xC0
comma
l_int|0x21
)brace
suffix:semicolon
DECL|macro|LLC_LEN
mdefine_line|#define LLC_LEN&t;&t;(4)
DECL|function|atmvcc_to_pvcc
r_static
r_inline
r_struct
id|pppoatm_vcc
op_star
id|atmvcc_to_pvcc
c_func
(paren
r_const
r_struct
id|atm_vcc
op_star
id|atmvcc
)paren
(brace
r_return
(paren
r_struct
id|pppoatm_vcc
op_star
)paren
(paren
id|atmvcc-&gt;user_back
)paren
suffix:semicolon
)brace
DECL|function|chan_to_pvcc
r_static
r_inline
r_struct
id|pppoatm_vcc
op_star
id|chan_to_pvcc
c_func
(paren
r_const
r_struct
id|ppp_channel
op_star
id|chan
)paren
(brace
r_return
(paren
r_struct
id|pppoatm_vcc
op_star
)paren
(paren
id|chan
op_member_access_from_pointer
r_private
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * We can&squot;t do this directly from our _pop handler, since the ppp code&n; * doesn&squot;t want to be called in interrupt context, so we do it from&n; * a tasklet&n; */
DECL|function|pppoatm_wakeup_sender
r_static
r_void
id|pppoatm_wakeup_sender
c_func
(paren
r_int
r_int
id|arg
)paren
(brace
id|ppp_output_wakeup
c_func
(paren
(paren
r_struct
id|ppp_channel
op_star
)paren
id|arg
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This gets called every time the ATM card has finished sending our&n; * skb.  The -&gt;old_pop will take care up normal atm flow control,&n; * but we also need to wake up the device if we blocked it&n; */
DECL|function|pppoatm_pop
r_static
r_void
id|pppoatm_pop
c_func
(paren
r_struct
id|atm_vcc
op_star
id|atmvcc
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|pppoatm_vcc
op_star
id|pvcc
op_assign
id|atmvcc_to_pvcc
c_func
(paren
id|atmvcc
)paren
suffix:semicolon
id|pvcc
op_member_access_from_pointer
id|old_pop
c_func
(paren
id|atmvcc
comma
id|skb
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We don&squot;t really always want to do this since it&squot;s&n;&t; * really inefficient - it would be much better if we could&n;&t; * test if we had actually throttled the generic layer.&n;&t; * Unfortunately then there would be a nasty SMP race where&n;&t; * we could clear that flag just as we refuse another packet.&n;&t; * For now we do the safe thing.&n;&t; */
id|tasklet_schedule
c_func
(paren
op_amp
id|pvcc-&gt;wakeup_tasklet
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Unbind from PPP - currently we only do this when closing the socket,&n; * but we could put this into an ioctl if need be&n; */
DECL|function|pppoatm_unassign_vcc
r_static
r_void
id|pppoatm_unassign_vcc
c_func
(paren
r_struct
id|atm_vcc
op_star
id|atmvcc
)paren
(brace
r_struct
id|pppoatm_vcc
op_star
id|pvcc
suffix:semicolon
id|pvcc
op_assign
id|atmvcc_to_pvcc
c_func
(paren
id|atmvcc
)paren
suffix:semicolon
id|atmvcc-&gt;push
op_assign
id|pvcc-&gt;old_push
suffix:semicolon
id|atmvcc-&gt;pop
op_assign
id|pvcc-&gt;old_pop
suffix:semicolon
id|tasklet_kill
c_func
(paren
op_amp
id|pvcc-&gt;wakeup_tasklet
)paren
suffix:semicolon
id|ppp_unregister_channel
c_func
(paren
op_amp
id|pvcc-&gt;chan
)paren
suffix:semicolon
id|atmvcc-&gt;user_back
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|pvcc
)paren
suffix:semicolon
multiline_comment|/* Gee, I hope we have the big kernel lock here... */
id|module_put
c_func
(paren
id|THIS_MODULE
)paren
suffix:semicolon
)brace
multiline_comment|/* Called when an AAL5 PDU comes in */
DECL|function|pppoatm_push
r_static
r_void
id|pppoatm_push
c_func
(paren
r_struct
id|atm_vcc
op_star
id|atmvcc
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|pppoatm_vcc
op_star
id|pvcc
op_assign
id|atmvcc_to_pvcc
c_func
(paren
id|atmvcc
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;pppoatm push&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* VCC was closed */
id|DPRINTK
c_func
(paren
l_string|&quot;removing ATMPPP VCC %p&bslash;n&quot;
comma
id|pvcc
)paren
suffix:semicolon
id|pppoatm_unassign_vcc
c_func
(paren
id|atmvcc
)paren
suffix:semicolon
id|atmvcc
op_member_access_from_pointer
id|push
c_func
(paren
id|atmvcc
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* Pass along bad news */
r_return
suffix:semicolon
)brace
id|atm_return
c_func
(paren
id|atmvcc
comma
id|skb-&gt;truesize
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|pvcc-&gt;encaps
)paren
(brace
r_case
id|e_llc
suffix:colon
r_if
c_cond
(paren
id|skb-&gt;len
OL
id|LLC_LEN
op_logical_or
id|memcmp
c_func
(paren
id|skb-&gt;data
comma
id|pppllc
comma
id|LLC_LEN
)paren
)paren
r_goto
id|error
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|LLC_LEN
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|e_autodetect
suffix:colon
r_if
c_cond
(paren
id|pvcc-&gt;chan.ppp
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* Not bound yet! */
id|kfree_skb
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
id|skb-&gt;len
op_ge
r_sizeof
(paren
id|pppllc
)paren
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|skb-&gt;data
comma
id|pppllc
comma
r_sizeof
(paren
id|pppllc
)paren
)paren
)paren
(brace
id|pvcc-&gt;encaps
op_assign
id|e_llc
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|LLC_LEN
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb-&gt;len
op_ge
(paren
r_sizeof
(paren
id|pppllc
)paren
op_minus
id|LLC_LEN
)paren
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|skb-&gt;data
comma
op_amp
id|pppllc
(braket
id|LLC_LEN
)braket
comma
r_sizeof
(paren
id|pppllc
)paren
op_minus
id|LLC_LEN
)paren
)paren
(brace
id|pvcc-&gt;encaps
op_assign
id|e_vc
suffix:semicolon
id|pvcc-&gt;chan.mtu
op_add_assign
id|LLC_LEN
suffix:semicolon
r_break
suffix:semicolon
)brace
id|DPRINTK
c_func
(paren
l_string|&quot;(unit %d): Couldn&squot;t autodetect yet &quot;
l_string|&quot;(skb: %02X %02X %02X %02X %02X %02X)&bslash;n&quot;
comma
id|pvcc-&gt;chan.unit
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
id|skb-&gt;data
(braket
l_int|2
)braket
comma
id|skb-&gt;data
(braket
l_int|3
)braket
comma
id|skb-&gt;data
(braket
l_int|4
)braket
comma
id|skb-&gt;data
(braket
l_int|5
)braket
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
r_case
id|e_vc
suffix:colon
r_break
suffix:semicolon
)brace
id|ppp_input
c_func
(paren
op_amp
id|pvcc-&gt;chan
comma
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
id|error
suffix:colon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|ppp_input_error
c_func
(paren
op_amp
id|pvcc-&gt;chan
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Called by the ppp_generic.c to send a packet - returns true if packet&n; * was accepted.  If we return false, then it&squot;s our job to call&n; * ppp_output_wakeup(chan) when we&squot;re feeling more up to it.&n; * Note that in the ENOMEM case (as opposed to the !atm_may_send case)&n; * we should really drop the packet, but the generic layer doesn&squot;t&n; * support this yet.  We just return &squot;DROP_PACKET&squot; which we actually define&n; * as success, just to be clear what we&squot;re really doing.&n; */
DECL|macro|DROP_PACKET
mdefine_line|#define DROP_PACKET 1
DECL|function|pppoatm_send
r_static
r_int
id|pppoatm_send
c_func
(paren
r_struct
id|ppp_channel
op_star
id|chan
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|pppoatm_vcc
op_star
id|pvcc
op_assign
id|chan_to_pvcc
c_func
(paren
id|chan
)paren
suffix:semicolon
id|ATM_SKB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|vcc
op_assign
id|pvcc-&gt;atmvcc
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;(unit %d): pppoatm_send (skb=0x%p, vcc=0x%p)&bslash;n&quot;
comma
id|pvcc-&gt;chan.unit
comma
id|skb
comma
id|pvcc-&gt;atmvcc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;data
(braket
l_int|0
)braket
op_eq
l_char|&squot;&bslash;0&squot;
op_logical_and
(paren
id|pvcc-&gt;flags
op_amp
id|SC_COMP_PROT
)paren
)paren
(paren
r_void
)paren
id|skb_pull
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|pvcc-&gt;encaps
)paren
(brace
multiline_comment|/* LLC encapsulation needed */
r_case
id|e_llc
suffix:colon
r_if
c_cond
(paren
id|skb_headroom
c_func
(paren
id|skb
)paren
OL
id|LLC_LEN
)paren
(brace
r_struct
id|sk_buff
op_star
id|n
suffix:semicolon
id|n
op_assign
id|skb_realloc_headroom
c_func
(paren
id|skb
comma
id|LLC_LEN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ne
l_int|NULL
op_logical_and
op_logical_neg
id|atm_may_send
c_func
(paren
id|pvcc-&gt;atmvcc
comma
id|n-&gt;truesize
)paren
)paren
(brace
id|kfree_skb
c_func
(paren
id|n
)paren
suffix:semicolon
r_goto
id|nospace
suffix:semicolon
)brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|n
)paren
op_eq
l_int|NULL
)paren
r_return
id|DROP_PACKET
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|atm_may_send
c_func
(paren
id|pvcc-&gt;atmvcc
comma
id|skb-&gt;truesize
)paren
)paren
r_goto
id|nospace
suffix:semicolon
id|memcpy
c_func
(paren
id|skb_push
c_func
(paren
id|skb
comma
id|LLC_LEN
)paren
comma
id|pppllc
comma
id|LLC_LEN
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|e_vc
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|atm_may_send
c_func
(paren
id|pvcc-&gt;atmvcc
comma
id|skb-&gt;truesize
)paren
)paren
r_goto
id|nospace
suffix:semicolon
r_break
suffix:semicolon
r_case
id|e_autodetect
suffix:colon
id|DPRINTK
c_func
(paren
l_string|&quot;(unit %d): Trying to send without setting encaps!&bslash;n&quot;
comma
id|pvcc-&gt;chan.unit
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|atomic_add
c_func
(paren
id|skb-&gt;truesize
comma
op_amp
id|ATM_SKB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|vcc-&gt;sk-&gt;sk_wmem_alloc
)paren
suffix:semicolon
id|ATM_SKB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|atm_options
op_assign
id|ATM_SKB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|vcc-&gt;atm_options
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;(unit %d): atm_skb(%p)-&gt;vcc(%p)-&gt;dev(%p)&bslash;n&quot;
comma
id|pvcc-&gt;chan.unit
comma
id|skb
comma
id|ATM_SKB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|vcc
comma
id|ATM_SKB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|vcc-&gt;dev
)paren
suffix:semicolon
r_return
id|ATM_SKB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|vcc
op_member_access_from_pointer
id|send
c_func
(paren
id|ATM_SKB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|vcc
comma
id|skb
)paren
ques
c_cond
id|DROP_PACKET
suffix:colon
l_int|1
suffix:semicolon
id|nospace
suffix:colon
multiline_comment|/*&n;&t; * We don&squot;t have space to send this SKB now, but we might have&n;&t; * already applied SC_COMP_PROT compression, so may need to undo&n;&t; */
r_if
c_cond
(paren
(paren
id|pvcc-&gt;flags
op_amp
id|SC_COMP_PROT
)paren
op_logical_and
id|skb_headroom
c_func
(paren
id|skb
)paren
OG
l_int|0
op_logical_and
id|skb-&gt;data
(braket
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;0&squot;
)paren
(paren
r_void
)paren
id|skb_push
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* This handles ioctls sent to the /dev/ppp interface */
DECL|function|pppoatm_devppp_ioctl
r_static
r_int
id|pppoatm_devppp_ioctl
c_func
(paren
r_struct
id|ppp_channel
op_star
id|chan
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|PPPIOCGFLAGS
suffix:colon
r_return
id|put_user
c_func
(paren
id|chan_to_pvcc
c_func
(paren
id|chan
)paren
op_member_access_from_pointer
id|flags
comma
(paren
r_int
id|__user
op_star
)paren
id|arg
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_case
id|PPPIOCSFLAGS
suffix:colon
r_return
id|get_user
c_func
(paren
id|chan_to_pvcc
c_func
(paren
id|chan
)paren
op_member_access_from_pointer
id|flags
comma
(paren
r_int
id|__user
op_star
)paren
id|arg
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|ENOTTY
suffix:semicolon
)brace
DECL|variable|pppoatm_ops
r_static
multiline_comment|/*const*/
r_struct
id|ppp_channel_ops
id|pppoatm_ops
op_assign
(brace
dot
id|start_xmit
op_assign
id|pppoatm_send
comma
dot
id|ioctl
op_assign
id|pppoatm_devppp_ioctl
comma
)brace
suffix:semicolon
DECL|function|pppoatm_assign_vcc
r_static
r_int
id|pppoatm_assign_vcc
c_func
(paren
r_struct
id|atm_vcc
op_star
id|atmvcc
comma
r_void
id|__user
op_star
id|arg
)paren
(brace
r_struct
id|atm_backend_ppp
id|be
suffix:semicolon
r_struct
id|pppoatm_vcc
op_star
id|pvcc
suffix:semicolon
r_int
id|err
suffix:semicolon
multiline_comment|/*&n;&t; * Each PPPoATM instance has its own tasklet - this is just a&n;&t; * prototypical one used to initialize them&n;&t; */
r_static
r_const
id|DECLARE_TASKLET
c_func
(paren
id|tasklet_proto
comma
id|pppoatm_wakeup_sender
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|be
comma
id|arg
comma
r_sizeof
id|be
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|be.encaps
op_ne
id|PPPOATM_ENCAPS_AUTODETECT
op_logical_and
id|be.encaps
op_ne
id|PPPOATM_ENCAPS_VC
op_logical_and
id|be.encaps
op_ne
id|PPPOATM_ENCAPS_LLC
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|pvcc
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|pvcc
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pvcc
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|pvcc
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|pvcc
)paren
)paren
suffix:semicolon
id|pvcc-&gt;atmvcc
op_assign
id|atmvcc
suffix:semicolon
id|pvcc-&gt;old_push
op_assign
id|atmvcc-&gt;push
suffix:semicolon
id|pvcc-&gt;old_pop
op_assign
id|atmvcc-&gt;pop
suffix:semicolon
id|pvcc-&gt;encaps
op_assign
(paren
r_enum
id|pppoatm_encaps
)paren
id|be.encaps
suffix:semicolon
id|pvcc-&gt;chan
dot
r_private
op_assign
id|pvcc
suffix:semicolon
id|pvcc-&gt;chan.ops
op_assign
op_amp
id|pppoatm_ops
suffix:semicolon
id|pvcc-&gt;chan.mtu
op_assign
id|atmvcc-&gt;qos.txtp.max_sdu
op_minus
id|PPP_HDRLEN
op_minus
(paren
id|be.encaps
op_eq
id|e_vc
ques
c_cond
l_int|0
suffix:colon
id|LLC_LEN
)paren
suffix:semicolon
id|pvcc-&gt;wakeup_tasklet
op_assign
id|tasklet_proto
suffix:semicolon
id|pvcc-&gt;wakeup_tasklet.data
op_assign
(paren
r_int
r_int
)paren
op_amp
id|pvcc-&gt;chan
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|ppp_register_channel
c_func
(paren
op_amp
id|pvcc-&gt;chan
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|pvcc
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|atmvcc-&gt;user_back
op_assign
id|pvcc
suffix:semicolon
id|atmvcc-&gt;push
op_assign
id|pppoatm_push
suffix:semicolon
id|atmvcc-&gt;pop
op_assign
id|pppoatm_pop
suffix:semicolon
(paren
r_void
)paren
id|try_module_get
c_func
(paren
id|THIS_MODULE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This handles ioctls actually performed on our vcc - we must return&n; * -ENOIOCTLCMD for any unrecognized ioctl&n; */
DECL|function|pppoatm_ioctl
r_static
r_int
id|pppoatm_ioctl
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|atm_vcc
op_star
id|atmvcc
op_assign
id|ATM_SD
c_func
(paren
id|sock
)paren
suffix:semicolon
r_void
id|__user
op_star
id|argp
op_assign
(paren
r_void
id|__user
op_star
)paren
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_ne
id|ATM_SETBACKEND
op_logical_and
id|atmvcc-&gt;push
op_ne
id|pppoatm_push
)paren
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|ATM_SETBACKEND
suffix:colon
(brace
id|atm_backend_t
id|b
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|b
comma
(paren
id|atm_backend_t
id|__user
op_star
)paren
id|argp
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|b
op_ne
id|ATM_BACKEND_PPP
)paren
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_return
id|pppoatm_assign_vcc
c_func
(paren
id|atmvcc
comma
id|argp
)paren
suffix:semicolon
)brace
r_case
id|PPPIOCGCHAN
suffix:colon
r_return
id|put_user
c_func
(paren
id|ppp_channel_index
c_func
(paren
op_amp
id|atmvcc_to_pvcc
c_func
(paren
id|atmvcc
)paren
op_member_access_from_pointer
id|chan
)paren
comma
(paren
r_int
id|__user
op_star
)paren
id|argp
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_case
id|PPPIOCGUNIT
suffix:colon
r_return
id|put_user
c_func
(paren
id|ppp_unit_number
c_func
(paren
op_amp
id|atmvcc_to_pvcc
c_func
(paren
id|atmvcc
)paren
op_member_access_from_pointer
id|chan
)paren
comma
(paren
r_int
id|__user
op_star
)paren
id|argp
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
)brace
DECL|variable|pppoatm_ioctl_ops
r_struct
id|atm_ioctl
id|pppoatm_ioctl_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|ioctl
op_assign
id|pppoatm_ioctl
comma
)brace
suffix:semicolon
DECL|function|pppoatm_init
r_static
r_int
id|__init
id|pppoatm_init
c_func
(paren
r_void
)paren
(brace
id|register_atm_ioctl
c_func
(paren
op_amp
id|pppoatm_ioctl_ops
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pppoatm_exit
r_static
r_void
id|__exit
id|pppoatm_exit
c_func
(paren
r_void
)paren
(brace
id|deregister_atm_ioctl
c_func
(paren
op_amp
id|pppoatm_ioctl_ops
)paren
suffix:semicolon
)brace
DECL|variable|pppoatm_init
id|module_init
c_func
(paren
id|pppoatm_init
)paren
suffix:semicolon
DECL|variable|pppoatm_exit
id|module_exit
c_func
(paren
id|pppoatm_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Mitchell Blank Jr &lt;mitch@sfgoth.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;RFC2364 PPP over ATM/AAL5&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
