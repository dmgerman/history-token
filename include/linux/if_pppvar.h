multiline_comment|/*&t;From: if_pppvar.h,v 1.2 1995/06/12 11:36:51 paulus Exp */
multiline_comment|/*&n; * if_pppvar.h - private structures and declarations for PPP.&n; *&n; * Copyright (c) 1994 The Australian National University.&n; * All rights reserved.&n; *&n; * Permission to use, copy, modify, and distribute this software and its&n; * documentation is hereby granted, provided that the above copyright&n; * notice appears in all copies.  This software is provided without any&n; * warranty, express or implied. The Australian National University&n; * makes no representations about the suitability of this software for&n; * any purpose.&n; *&n; * IN NO EVENT SHALL THE AUSTRALIAN NATIONAL UNIVERSITY BE LIABLE TO ANY&n; * PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES&n; * ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF&n; * THE AUSTRALIAN NATIONAL UNIVERSITY HAVE BEEN ADVISED OF THE POSSIBILITY&n; * OF SUCH DAMAGE.&n; *&n; * THE AUSTRALIAN NATIONAL UNIVERSITY SPECIFICALLY DISCLAIMS ANY WARRANTIES,&n; * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY&n; * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS&n; * ON AN &quot;AS IS&quot; BASIS, AND THE AUSTRALIAN NATIONAL UNIVERSITY HAS NO&n; * OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS,&n; * OR MODIFICATIONS.&n; *&n; * Copyright (c) 1989 Carnegie Mellon University.&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms are permitted&n; * provided that the above copyright notice and this paragraph are&n; * duplicated in all such forms and that any documentation,&n; * advertising materials, and other materials related to such&n; * distribution and use acknowledge that the software was developed&n; * by Carnegie Mellon University.  The name of the&n; * University may not be used to endorse or promote products derived&n; * from this software without specific prior written permission.&n; * THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND WITHOUT ANY EXPRESS OR&n; * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED&n; * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.&n; */
multiline_comment|/*&n; *  ==FILEVERSION 990806==&n; *&n; *  NOTE TO MAINTAINERS:&n; *   If you modify this file at all, please set the above date.&n; *   if_pppvar.h is shipped with a PPP distribution as well as with the kernel;&n; *   if everyone increases the FILEVERSION number above, then scripts&n; *   can do the right thing when deciding whether to install a new if_pppvar.h&n; *   file.  Don&squot;t change the format of that line otherwise, so the&n; *   installation script can recognize it.&n; */
multiline_comment|/*&n; * Supported network protocols.  These values are used for&n; * indexing sc_npmode.&n; */
DECL|macro|NP_IP
mdefine_line|#define NP_IP&t;0&t;&t;/* Internet Protocol */
DECL|macro|NP_IPX
mdefine_line|#define NP_IPX&t;1&t;&t;/* IPX protocol */
DECL|macro|NP_AT
mdefine_line|#define NP_AT&t;2&t;&t;/* Appletalk protocol */
DECL|macro|NP_IPV6
mdefine_line|#define NP_IPV6&t;3&t;&t;/* Internet Protocol */
DECL|macro|NUM_NP
mdefine_line|#define NUM_NP&t;4&t;&t;/* Number of NPs. */
DECL|macro|OBUFSIZE
mdefine_line|#define OBUFSIZE&t;256&t;/* # chars of output buffering */
multiline_comment|/*&n; * Structure describing each ppp unit.&n; */
DECL|struct|ppp
r_struct
id|ppp
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* magic value for structure&t;*/
DECL|member|next
r_struct
id|ppp
op_star
id|next
suffix:semicolon
multiline_comment|/* unit with next index&t;&t;*/
DECL|member|inuse
r_int
r_int
id|inuse
suffix:semicolon
multiline_comment|/* are we allocated?&t;&t;*/
DECL|member|line
r_int
id|line
suffix:semicolon
multiline_comment|/* network interface unit #&t;*/
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
multiline_comment|/* miscellaneous control flags&t;*/
DECL|member|mtu
r_int
id|mtu
suffix:semicolon
multiline_comment|/* maximum xmit frame size&t;*/
DECL|member|mru
r_int
id|mru
suffix:semicolon
multiline_comment|/* maximum receive frame size&t;*/
DECL|member|slcomp
r_struct
id|slcompress
op_star
id|slcomp
suffix:semicolon
multiline_comment|/* for TCP header compression&t;*/
DECL|member|xmt_q
r_struct
id|sk_buff_head
id|xmt_q
suffix:semicolon
multiline_comment|/* frames to send from pppd&t;*/
DECL|member|rcv_q
r_struct
id|sk_buff_head
id|rcv_q
suffix:semicolon
multiline_comment|/* frames for pppd to read&t;*/
DECL|member|xmit_busy
r_int
r_int
id|xmit_busy
suffix:semicolon
multiline_comment|/* bit 0 set when xmitter busy  */
multiline_comment|/* Information specific to using ppp on async serial lines. */
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
multiline_comment|/* ptr to TTY structure&t;*/
DECL|member|backup_tty
r_struct
id|tty_struct
op_star
id|backup_tty
suffix:semicolon
multiline_comment|/* TTY to use if tty gets closed */
DECL|member|escape
id|__u8
id|escape
suffix:semicolon
multiline_comment|/* 0x20 if prev char was PPP_ESC */
DECL|member|toss
id|__u8
id|toss
suffix:semicolon
multiline_comment|/* toss this frame&t;&t;*/
DECL|member|tty_pushing
r_volatile
id|__u8
id|tty_pushing
suffix:semicolon
multiline_comment|/* internal state flag&t;&t;*/
DECL|member|woke_up
r_volatile
id|__u8
id|woke_up
suffix:semicolon
multiline_comment|/* internal state flag&t;&t;*/
DECL|member|xmit_async_map
id|__u32
id|xmit_async_map
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 1 bit means that given control &n;&t;&t;&t;&t;&t;   character is quoted on output*/
DECL|member|recv_async_map
id|__u32
id|recv_async_map
suffix:semicolon
multiline_comment|/* 1 bit means that given control &n;&t;&t;&t;&t;&t;   character is ignored on input*/
DECL|member|bytes_sent
id|__u32
id|bytes_sent
suffix:semicolon
multiline_comment|/* Bytes sent on frame&t;*/
DECL|member|bytes_rcvd
id|__u32
id|bytes_rcvd
suffix:semicolon
multiline_comment|/* Bytes recvd on frame&t;*/
multiline_comment|/* Async transmission information */
DECL|member|tpkt
r_struct
id|sk_buff
op_star
id|tpkt
suffix:semicolon
multiline_comment|/* frame currently being sent&t;*/
DECL|member|tpkt_pos
r_int
id|tpkt_pos
suffix:semicolon
multiline_comment|/* how much of it we&squot;ve done&t;*/
DECL|member|tfcs
id|__u16
id|tfcs
suffix:semicolon
multiline_comment|/* FCS so far for it&t;&t;*/
DECL|member|optr
r_int
r_char
op_star
id|optr
suffix:semicolon
multiline_comment|/* where we&squot;re up to in sending */
DECL|member|olim
r_int
r_char
op_star
id|olim
suffix:semicolon
multiline_comment|/* points past last valid char&t;*/
multiline_comment|/* Async reception information */
DECL|member|rpkt
r_struct
id|sk_buff
op_star
id|rpkt
suffix:semicolon
multiline_comment|/* frame currently being rcvd&t;*/
DECL|member|rfcs
id|__u16
id|rfcs
suffix:semicolon
multiline_comment|/* FCS so far of rpkt&t;&t;*/
multiline_comment|/* Queues for select() functionality */
DECL|member|read_wait
id|wait_queue_head_t
id|read_wait
suffix:semicolon
multiline_comment|/* queue for reading processes&t;*/
multiline_comment|/* info for detecting idle channels */
DECL|member|last_xmit
r_int
r_int
id|last_xmit
suffix:semicolon
multiline_comment|/* time of last transmission&t;*/
DECL|member|last_recv
r_int
r_int
id|last_recv
suffix:semicolon
multiline_comment|/* time last packet received    */
multiline_comment|/* Statistic information */
DECL|member|stats
r_struct
id|pppstat
id|stats
suffix:semicolon
multiline_comment|/* statistic information&t;*/
multiline_comment|/* PPP compression protocol information */
DECL|member|sc_xcomp
r_struct
id|compressor
op_star
id|sc_xcomp
suffix:semicolon
multiline_comment|/* transmit compressor */
DECL|member|sc_xc_state
r_void
op_star
id|sc_xc_state
suffix:semicolon
multiline_comment|/* transmit compressor state */
DECL|member|sc_rcomp
r_struct
id|compressor
op_star
id|sc_rcomp
suffix:semicolon
multiline_comment|/* receive decompressor */
DECL|member|sc_rc_state
r_void
op_star
id|sc_rc_state
suffix:semicolon
multiline_comment|/* receive decompressor state */
DECL|member|sc_npmode
r_enum
id|NPmode
id|sc_npmode
(braket
id|NUM_NP
)braket
suffix:semicolon
multiline_comment|/* what to do with each NP */
DECL|member|sc_xfer
r_int
id|sc_xfer
suffix:semicolon
multiline_comment|/* PID of reserved PPP table */
DECL|member|name
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* space for unit name */
DECL|member|dev
r_struct
id|net_device
id|dev
suffix:semicolon
multiline_comment|/* net device structure */
DECL|member|estats
r_struct
id|net_device_stats
id|estats
suffix:semicolon
multiline_comment|/* more detailed stats */
multiline_comment|/* tty output buffer */
DECL|member|obuf
r_int
r_char
id|obuf
(braket
id|OBUFSIZE
)braket
suffix:semicolon
multiline_comment|/* buffer for characters to send */
)brace
suffix:semicolon
DECL|macro|PPP_MAGIC
mdefine_line|#define PPP_MAGIC&t;0x5002
DECL|macro|PPP_VERSION
mdefine_line|#define PPP_VERSION&t;&quot;2.3.7&quot;
eof
