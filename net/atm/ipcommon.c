multiline_comment|/* net/atm/ipcommon.c - Common items for all ways of doing IP over ATM */
multiline_comment|/* Written 1996-2000 by Werner Almesberger, EPFL LRC/ICA */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/atmdev.h&gt;
macro_line|#include &lt;linux/atmclip.h&gt;
macro_line|#include &quot;common.h&quot;
macro_line|#include &quot;ipcommon.h&quot;
macro_line|#if 0
mdefine_line|#define DPRINTK(format,args...) printk(KERN_DEBUG format,##args)
macro_line|#else
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(format,args...)
macro_line|#endif
DECL|variable|llc_oui
r_const
r_int
r_char
id|llc_oui
(braket
)braket
op_assign
(brace
l_int|0xaa
comma
multiline_comment|/* DSAP: non-ISO */
l_int|0xaa
comma
multiline_comment|/* SSAP: non-ISO */
l_int|0x03
comma
multiline_comment|/* Ctrl: Unnumbered Information Command PDU */
l_int|0x00
comma
multiline_comment|/* OUI: EtherType */
l_int|0x00
comma
l_int|0x00
)brace
suffix:semicolon
multiline_comment|/*&n; * skb_migrate appends the list at &quot;from&quot; to &quot;to&quot;, emptying &quot;from&quot; in the&n; * process. skb_migrate is atomic with respect to all other skb operations on&n; * &quot;from&quot; and &quot;to&quot;. Note that it locks both lists at the same time, so beware&n; * of potential deadlocks.&n; *&n; * This function should live in skbuff.c or skbuff.h.&n; */
DECL|function|skb_migrate
r_void
id|skb_migrate
c_func
(paren
r_struct
id|sk_buff_head
op_star
id|from
comma
r_struct
id|sk_buff_head
op_star
id|to
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb_from
op_assign
(paren
r_struct
id|sk_buff
op_star
)paren
id|from
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb_to
op_assign
(paren
r_struct
id|sk_buff
op_star
)paren
id|to
suffix:semicolon
r_struct
id|sk_buff
op_star
id|prev
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|from-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|to-&gt;lock
)paren
suffix:semicolon
id|prev
op_assign
id|from-&gt;prev
suffix:semicolon
id|from-&gt;next-&gt;prev
op_assign
id|to-&gt;prev
suffix:semicolon
id|prev-&gt;next
op_assign
id|skb_to
suffix:semicolon
id|to-&gt;prev-&gt;next
op_assign
id|from-&gt;next
suffix:semicolon
id|to-&gt;prev
op_assign
id|from-&gt;prev
suffix:semicolon
r_for
c_loop
(paren
id|skb
op_assign
id|from-&gt;next
suffix:semicolon
id|skb
op_ne
id|skb_to
suffix:semicolon
id|skb
op_assign
id|skb-&gt;next
)paren
id|skb-&gt;list
op_assign
id|to
suffix:semicolon
id|to-&gt;qlen
op_add_assign
id|from-&gt;qlen
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|to-&gt;lock
)paren
suffix:semicolon
id|from-&gt;prev
op_assign
id|skb_from
suffix:semicolon
id|from-&gt;next
op_assign
id|skb_from
suffix:semicolon
id|from-&gt;qlen
op_assign
l_int|0
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|from-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|variable|skb_migrate
id|EXPORT_SYMBOL
c_func
(paren
id|skb_migrate
)paren
suffix:semicolon
eof
