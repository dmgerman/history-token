multiline_comment|/* Linux ISDN subsystem, CISCO HDLC network interfaces&n; *&n; * Copyright 1999-2002  by Kai Germaschewski &lt;kai@germaschewski.name&gt;&n; *           2001       by Bjoern A. Zeeb &lt;i4l@zabbadoz.net&gt;&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; */
macro_line|#ifndef ISDN_CISCOHDLCK_H
DECL|macro|ISDN_CISCOHDLCK_H
mdefine_line|#define ISDN_CISCOHDLCK_H
r_extern
r_struct
id|isdn_netif_ops
id|isdn_ciscohdlck_ops
suffix:semicolon
DECL|struct|inl_cisco
r_struct
id|inl_cisco
(brace
DECL|member|myseq
id|u32
id|myseq
suffix:semicolon
multiline_comment|/* local keepalive seq. for Cisco */
DECL|member|mineseen
id|u32
id|mineseen
suffix:semicolon
multiline_comment|/* returned keepalive seq. from remote */
DECL|member|yourseq
id|u32
id|yourseq
suffix:semicolon
multiline_comment|/* remote keepalive seq. for Cisco  */
DECL|member|keepalive_period
r_int
id|keepalive_period
suffix:semicolon
multiline_comment|/* keepalive period */
DECL|member|last_slarp_in
r_int
id|last_slarp_in
suffix:semicolon
multiline_comment|/* jiffie of last recvd keepalive pkt */
DECL|member|line_state
r_char
id|line_state
suffix:semicolon
multiline_comment|/* state of line */
DECL|member|debserint
r_char
id|debserint
suffix:semicolon
multiline_comment|/* debugging flags */
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
