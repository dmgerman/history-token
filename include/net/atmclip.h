multiline_comment|/* net/atm/atmarp.h - RFC1577 ATM ARP */
multiline_comment|/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */
macro_line|#ifndef _ATMCLIP_H
DECL|macro|_ATMCLIP_H
mdefine_line|#define _ATMCLIP_H
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/atm.h&gt;
macro_line|#include &lt;linux/atmdev.h&gt;
macro_line|#include &lt;linux/atmarp.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;net/neighbour.h&gt;
DECL|macro|CLIP_VCC
mdefine_line|#define CLIP_VCC(vcc) ((struct clip_vcc *) ((vcc)-&gt;user_back))
DECL|macro|NEIGH2ENTRY
mdefine_line|#define NEIGH2ENTRY(neigh) ((struct atmarp_entry *) (neigh)-&gt;primary_key)
DECL|struct|clip_vcc
r_struct
id|clip_vcc
(brace
DECL|member|vcc
r_struct
id|atm_vcc
op_star
id|vcc
suffix:semicolon
multiline_comment|/* VCC descriptor */
DECL|member|entry
r_struct
id|atmarp_entry
op_star
id|entry
suffix:semicolon
multiline_comment|/* ATMARP table entry, NULL if IP addr.&n;&t;&t;&t;&t;&t;   isn&squot;t known yet */
DECL|member|xoff
r_int
id|xoff
suffix:semicolon
multiline_comment|/* 1 if send buffer is full */
DECL|member|encap
r_int
r_char
id|encap
suffix:semicolon
multiline_comment|/* 0: NULL, 1: LLC/SNAP */
DECL|member|last_use
r_int
r_int
id|last_use
suffix:semicolon
multiline_comment|/* last send or receive operation */
DECL|member|idle_timeout
r_int
r_int
id|idle_timeout
suffix:semicolon
multiline_comment|/* keep open idle for so many jiffies*/
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
id|vcc
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
multiline_comment|/* keep old push fn for chaining */
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
id|vcc
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
multiline_comment|/* keep old pop fn for chaining */
DECL|member|next
r_struct
id|clip_vcc
op_star
id|next
suffix:semicolon
multiline_comment|/* next VCC */
)brace
suffix:semicolon
DECL|struct|atmarp_entry
r_struct
id|atmarp_entry
(brace
DECL|member|ip
id|u32
id|ip
suffix:semicolon
multiline_comment|/* IP address */
DECL|member|vccs
r_struct
id|clip_vcc
op_star
id|vccs
suffix:semicolon
multiline_comment|/* active VCCs; NULL if resolution is&n;&t;&t;&t;&t;&t;   pending */
DECL|member|expires
r_int
r_int
id|expires
suffix:semicolon
multiline_comment|/* entry expiration time */
DECL|member|neigh
r_struct
id|neighbour
op_star
id|neigh
suffix:semicolon
multiline_comment|/* neighbour back-pointer */
)brace
suffix:semicolon
DECL|macro|PRIV
mdefine_line|#define PRIV(dev) ((struct clip_priv *) ((struct net_device *) (dev)+1))
DECL|struct|clip_priv
r_struct
id|clip_priv
(brace
DECL|member|number
r_int
id|number
suffix:semicolon
multiline_comment|/* for convenience ... */
DECL|member|xoff_lock
id|spinlock_t
id|xoff_lock
suffix:semicolon
multiline_comment|/* ensures that pop is atomic (SMP) */
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|next
r_struct
id|net_device
op_star
id|next
suffix:semicolon
multiline_comment|/* next CLIP interface */
)brace
suffix:semicolon
r_extern
r_struct
id|atm_vcc
op_star
id|atmarpd
suffix:semicolon
multiline_comment|/* ugly */
r_extern
r_struct
id|neigh_table
id|clip_tbl
suffix:semicolon
r_int
id|clip_create
c_func
(paren
r_int
id|number
)paren
suffix:semicolon
r_int
id|clip_mkip
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_int
id|timeout
)paren
suffix:semicolon
r_int
id|clip_setentry
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
id|u32
id|ip
)paren
suffix:semicolon
r_int
id|clip_encap
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_int
id|mode
)paren
suffix:semicolon
r_void
id|atm_clip_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
