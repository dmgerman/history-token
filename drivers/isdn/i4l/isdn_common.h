multiline_comment|/* Linux ISDN subsystem, common used functions and debugging-switches&n; *&n; * Copyright 1994-1999  by Fritz Elfert (fritz@isdn4linux.de)&n; * Copyright 1995,96    by Thinking Objects Software GmbH Wuerzburg&n; * Copyright 1995,96    by Michael Hipp (Michael.Hipp@student.uni-tuebingen.de)&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#include &lt;linux/isdn.h&gt;
DECL|macro|ISDN_DEBUG_MODEM_OPEN
macro_line|#undef  ISDN_DEBUG_MODEM_OPEN
DECL|macro|ISDN_DEBUG_MODEM_IOCTL
macro_line|#undef  ISDN_DEBUG_MODEM_IOCTL
DECL|macro|ISDN_DEBUG_MODEM_WAITSENT
macro_line|#undef  ISDN_DEBUG_MODEM_WAITSENT
DECL|macro|ISDN_DEBUG_MODEM_HUP
macro_line|#undef  ISDN_DEBUG_MODEM_HUP
DECL|macro|ISDN_DEBUG_MODEM_ICALL
macro_line|#undef  ISDN_DEBUG_MODEM_ICALL
DECL|macro|ISDN_DEBUG_MODEM_DUMP
macro_line|#undef  ISDN_DEBUG_MODEM_DUMP
DECL|macro|ISDN_DEBUG_MODEM_VOICE
macro_line|#undef  ISDN_DEBUG_MODEM_VOICE
DECL|macro|ISDN_DEBUG_AT
macro_line|#undef  ISDN_DEBUG_AT
DECL|macro|ISDN_DEBUG_NET_DUMP
macro_line|#undef  ISDN_DEBUG_NET_DUMP
DECL|macro|ISDN_DEBUG_NET_DIAL
mdefine_line|#define  ISDN_DEBUG_NET_DIAL
DECL|macro|ISDN_DEBUG_NET_ICALL
mdefine_line|#define  ISDN_DEBUG_NET_ICALL
DECL|macro|ISDN_DEBUG_STATCALLB
mdefine_line|#define  ISDN_DEBUG_STATCALLB
DECL|macro|ISDN_DEBUG_COMMAND
mdefine_line|#define  ISDN_DEBUG_COMMAND
macro_line|#ifdef ISDN_DEBUG_NET_DIAL
DECL|macro|dbg_net_dial
mdefine_line|#define dbg_net_dial(arg...) printk(KERN_DEBUG arg)
macro_line|#else
DECL|macro|dbg_net_dial
mdefine_line|#define dbg_net_dial(arg...) do {} while (0)
macro_line|#endif
macro_line|#ifdef ISDN_DEBUG_NET_ICALL
DECL|macro|dbg_net_icall
mdefine_line|#define dbg_net_icall(arg...) printk(KERN_DEBUG arg)
macro_line|#else
DECL|macro|dbg_net_icall
mdefine_line|#define dbg_net_icall(arg...) do {} while (0)
macro_line|#endif
macro_line|#ifdef ISDN_DEBUG_STATCALLB
DECL|macro|dbg_statcallb
mdefine_line|#define dbg_statcallb(arg...) printk(KERN_DEBUG arg)
macro_line|#else
DECL|macro|dbg_statcallb
mdefine_line|#define dbg_statcallb(arg...) do {} while (0)
macro_line|#endif
DECL|macro|isdn_BUG
mdefine_line|#define isdn_BUG() &bslash;&n;do { printk(KERN_WARNING &quot;ISDN BUG at %s:%d&bslash;n&quot;, __FILE__, __LINE__); &bslash;&n;} while(0)
DECL|macro|HERE
mdefine_line|#define HERE printk(&quot;%s:%d (%s)&bslash;n&quot;, __FILE__, __LINE__, __FUNCTION__)
r_extern
r_struct
id|list_head
id|isdn_net_devs
suffix:semicolon
multiline_comment|/* Prototypes */
r_extern
r_void
id|isdn_MOD_INC_USE_COUNT
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|isdn_MOD_DEC_USE_COUNT
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|isdn_lock_drivers
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|isdn_unlock_drivers
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|isdn_free_channel
c_func
(paren
r_int
id|di
comma
r_int
id|ch
comma
r_int
id|usage
)paren
suffix:semicolon
r_extern
r_void
id|isdn_info_update
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_char
op_star
id|isdn_map_eaz2msn
c_func
(paren
r_char
op_star
id|msn
comma
r_int
id|di
)paren
suffix:semicolon
r_extern
r_void
id|isdn_timer_ctrl
c_func
(paren
r_int
id|tf
comma
r_int
id|onoff
)paren
suffix:semicolon
r_extern
r_int
id|isdn_getnum
c_func
(paren
r_char
op_star
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_msncmp
c_func
(paren
r_const
r_char
op_star
comma
r_const
r_char
op_star
)paren
suffix:semicolon
macro_line|#if defined(ISDN_DEBUG_NET_DUMP) || defined(ISDN_DEBUG_MODEM_DUMP)
r_extern
r_void
id|isdn_dumppkt
c_func
(paren
r_char
op_star
comma
id|u_char
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
macro_line|#else
DECL|function|isdn_dumppkt
r_static
r_inline
r_void
id|isdn_dumppkt
c_func
(paren
r_char
op_star
id|s
comma
id|u_char
op_star
id|d
comma
r_int
id|l
comma
r_int
id|m
)paren
(brace
)brace
macro_line|#endif
DECL|struct|dial_info
r_struct
id|dial_info
(brace
DECL|member|l2_proto
r_int
id|l2_proto
suffix:semicolon
DECL|member|l3_proto
r_int
id|l3_proto
suffix:semicolon
DECL|member|fax
r_struct
id|T30_s
op_star
id|fax
suffix:semicolon
DECL|member|si1
r_int
r_char
id|si1
suffix:semicolon
DECL|member|si2
r_int
r_char
id|si2
suffix:semicolon
DECL|member|msn
r_int
r_char
op_star
id|msn
suffix:semicolon
DECL|member|phone
r_int
r_char
op_star
id|phone
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|isdn_get_free_slot
c_func
(paren
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|isdn_slot_free
c_func
(paren
r_int
id|slot
)paren
suffix:semicolon
r_extern
r_int
id|isdn_slot_command
c_func
(paren
r_int
id|slot
comma
r_int
id|cmd
comma
id|isdn_ctrl
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_slot_dial
c_func
(paren
r_int
id|slot
comma
r_struct
id|dial_info
op_star
id|dial
)paren
suffix:semicolon
r_extern
r_char
op_star
id|isdn_slot_map_eaz2msn
c_func
(paren
r_int
id|slot
comma
r_char
op_star
id|msn
)paren
suffix:semicolon
r_extern
r_int
id|isdn_slot_write
c_func
(paren
r_int
id|slot
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_slot_hdrlen
c_func
(paren
r_int
id|slot
)paren
suffix:semicolon
r_extern
r_int
id|isdn_slot_maxbufsize
c_func
(paren
r_int
id|slot
)paren
suffix:semicolon
r_extern
r_int
id|isdn_slot_usage
c_func
(paren
r_int
id|slot
)paren
suffix:semicolon
r_extern
r_char
op_star
id|isdn_slot_num
c_func
(paren
r_int
id|slot
)paren
suffix:semicolon
r_extern
r_int
id|isdn_slot_m_idx
c_func
(paren
r_int
id|slot
)paren
suffix:semicolon
r_extern
r_void
id|isdn_slot_set_m_idx
c_func
(paren
r_int
id|slot
comma
r_int
id|midx
)paren
suffix:semicolon
r_extern
r_void
id|isdn_slot_set_priv
c_func
(paren
r_int
id|sl
comma
r_int
id|usage
comma
r_void
op_star
id|priv
comma
r_int
(paren
op_star
id|stat_cb
)paren
(paren
r_int
id|sl
comma
id|isdn_ctrl
op_star
id|ctrl
)paren
comma
r_int
(paren
op_star
id|recv_cb
)paren
(paren
r_int
id|sl
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
)paren
suffix:semicolon
r_extern
r_void
op_star
id|isdn_slot_priv
c_func
(paren
r_int
id|sl
)paren
suffix:semicolon
r_extern
r_int
id|isdn_hard_header_len
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|isdn_drv_lookup
c_func
(paren
r_char
op_star
id|drvid
)paren
suffix:semicolon
r_char
op_star
id|isdn_drv_drvid
c_func
(paren
r_int
id|di
)paren
suffix:semicolon
eof
