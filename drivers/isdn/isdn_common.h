multiline_comment|/* $Id: isdn_common.h,v 1.21.6.1 2001/09/23 22:24:31 kai Exp $&n; *&n; * header for Linux ISDN subsystem&n; * common used functions and debugging-switches (linklevel).&n; *&n; * Copyright 1994-1999  by Fritz Elfert (fritz@isdn4linux.de)&n; * Copyright 1995,96    by Thinking Objects Software GmbH Wuerzburg&n; * Copyright 1995,96    by Michael Hipp (Michael.Hipp@student.uni-tuebingen.de)&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
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
macro_line|#undef  ISDN_DEBUG_NET_DIAL
DECL|macro|ISDN_DEBUG_NET_ICALL
macro_line|#undef  ISDN_DEBUG_NET_ICALL
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
id|isdn_all_eaz
c_func
(paren
r_int
id|di
comma
r_int
id|ch
)paren
suffix:semicolon
r_extern
r_int
id|isdn_command
c_func
(paren
id|isdn_ctrl
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_dc2minor
c_func
(paren
r_int
id|di
comma
r_int
id|ch
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
r_void
id|isdn_unexclusive_channel
c_func
(paren
r_int
id|di
comma
r_int
id|ch
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
id|isdn_readbchan
c_func
(paren
r_int
comma
r_int
comma
id|u_char
op_star
comma
id|u_char
op_star
comma
r_int
comma
id|wait_queue_head_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_get_free_channel
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
r_int
id|isdn_writebuf_skb_stub
c_func
(paren
r_int
comma
r_int
comma
r_int
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_extern
r_int
id|register_isdn
c_func
(paren
id|isdn_if
op_star
id|i
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
r_extern
r_int
id|isdn_add_channels
c_func
(paren
id|driver
op_star
comma
r_int
comma
r_int
comma
r_int
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
macro_line|#endif
eof
