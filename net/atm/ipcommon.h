multiline_comment|/* net/atm/ipcommon.h - Common items for all ways of doing IP over ATM */
multiline_comment|/* Written 1996-2000 by Werner Almesberger, EPFL LRC/ICA */
macro_line|#ifndef NET_ATM_IPCOMMON_H
DECL|macro|NET_ATM_IPCOMMON_H
mdefine_line|#define NET_ATM_IPCOMMON_H
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/atmdev.h&gt;
r_extern
r_struct
id|net_device
op_star
id|clip_devs
suffix:semicolon
multiline_comment|/*&n; * Appends all skbs from &quot;from&quot; to &quot;to&quot;. The operation is atomic with respect&n; * to all other skb operations on &quot;from&quot; or &quot;to&quot;.&n; */
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
suffix:semicolon
macro_line|#endif
eof
