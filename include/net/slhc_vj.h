macro_line|#ifndef _SLHC_H
DECL|macro|_SLHC_H
mdefine_line|#define _SLHC_H
multiline_comment|/*&n; * Definitions for tcp compression routines.&n; *&n; * $Header: slcompress.h,v 1.10 89/12/31 08:53:02 van Exp $&n; *&n; * Copyright (c) 1989 Regents of the University of California.&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms are permitted&n; * provided that the above copyright notice and this paragraph are&n; * duplicated in all such forms and that any documentation,&n; * advertising materials, and other materials related to such&n; * distribution and use acknowledge that the software was developed&n; * by the University of California, Berkeley.  The name of the&n; * University may not be used to endorse or promote products derived&n; * from this software without specific prior written permission.&n; * THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND WITHOUT ANY EXPRESS OR&n; * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED&n; * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; *&t;Van Jacobson (van@helios.ee.lbl.gov), Dec 31, 1989:&n; *&t;- Initial distribution.&n; *&n; *&n; * modified for KA9Q Internet Software Package by&n; * Katie Stevens (dkstevens@ucdavis.edu)&n; * University of California, Davis&n; * Computing Services&n; *&t;- 01-31-90&t;initial adaptation&n; *&n; *&t;- Feb 1991&t;Bill_Simpson@um.cc.umich.edu&n; *&t;&t;&t;variable number of conversation slots&n; *&t;&t;&t;allow zero or one slots&n; *&t;&t;&t;separate routines&n; *&t;&t;&t;status display&n; */
multiline_comment|/*&n; * Compressed packet format:&n; *&n; * The first octet contains the packet type (top 3 bits), TCP&n; * &squot;push&squot; bit, and flags that indicate which of the 4 TCP sequence&n; * numbers have changed (bottom 5 bits).  The next octet is a&n; * conversation number that associates a saved IP/TCP header with&n; * the compressed packet.  The next two octets are the TCP checksum&n; * from the original datagram.  The next 0 to 15 octets are&n; * sequence number changes, one change per bit set in the header&n; * (there may be no changes and there are two special cases where&n; * the receiver implicitly knows what changed -- see below).&n; *&n; * There are 5 numbers which can change (they are always inserted&n; * in the following order): TCP urgent pointer, window,&n; * acknowledgment, sequence number and IP ID.  (The urgent pointer&n; * is different from the others in that its value is sent, not the&n; * change in value.)  Since typical use of SLIP links is biased&n; * toward small packets (see comments on MTU/MSS below), changes&n; * use a variable length coding with one octet for numbers in the&n; * range 1 - 255 and 3 octets (0, MSB, LSB) for numbers in the&n; * range 256 - 65535 or 0.  (If the change in sequence number or&n; * ack is more than 65535, an uncompressed packet is sent.)&n; */
multiline_comment|/*&n; * Packet types (must not conflict with IP protocol version)&n; *&n; * The top nibble of the first octet is the packet type.  There are&n; * three possible types: IP (not proto TCP or tcp with one of the&n; * control flags set); uncompressed TCP (a normal IP/TCP packet but&n; * with the 8-bit protocol field replaced by an 8-bit connection id --&n; * this type of packet syncs the sender &amp; receiver); and compressed&n; * TCP (described above).&n; *&n; * LSB of 4-bit field is TCP &quot;PUSH&quot; bit (a worthless anachronism) and&n; * is logically part of the 4-bit &quot;changes&quot; field that follows.  Top&n; * three bits are actual packet type.  For backward compatibility&n; * and in the interest of conserving bits, numbers are chosen so the&n; * IP protocol version number (4) which normally appears in this nibble&n; * means &quot;IP packet&quot;.&n; */
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/tcp.h&gt;
multiline_comment|/* SLIP compression masks for len/vers byte */
DECL|macro|SL_TYPE_IP
mdefine_line|#define SL_TYPE_IP 0x40
DECL|macro|SL_TYPE_UNCOMPRESSED_TCP
mdefine_line|#define SL_TYPE_UNCOMPRESSED_TCP 0x70
DECL|macro|SL_TYPE_COMPRESSED_TCP
mdefine_line|#define SL_TYPE_COMPRESSED_TCP 0x80
DECL|macro|SL_TYPE_ERROR
mdefine_line|#define SL_TYPE_ERROR 0x00
multiline_comment|/* Bits in first octet of compressed packet */
DECL|macro|NEW_C
mdefine_line|#define NEW_C&t;0x40&t;/* flag bits for what changed in a packet */
DECL|macro|NEW_I
mdefine_line|#define NEW_I&t;0x20
DECL|macro|NEW_S
mdefine_line|#define NEW_S&t;0x08
DECL|macro|NEW_A
mdefine_line|#define NEW_A&t;0x04
DECL|macro|NEW_W
mdefine_line|#define NEW_W&t;0x02
DECL|macro|NEW_U
mdefine_line|#define NEW_U&t;0x01
multiline_comment|/* reserved, special-case values of above */
DECL|macro|SPECIAL_I
mdefine_line|#define SPECIAL_I (NEW_S|NEW_W|NEW_U)&t;&t;/* echoed interactive traffic */
DECL|macro|SPECIAL_D
mdefine_line|#define SPECIAL_D (NEW_S|NEW_A|NEW_W|NEW_U)&t;/* unidirectional data */
DECL|macro|SPECIALS_MASK
mdefine_line|#define SPECIALS_MASK (NEW_S|NEW_A|NEW_W|NEW_U)
DECL|macro|TCP_PUSH_BIT
mdefine_line|#define TCP_PUSH_BIT 0x10
multiline_comment|/*&n; * data type and sizes conversion assumptions:&n; *&n; *&t;VJ code&t;&t;KA9Q style&t;generic&n; *&t;u_char&t;&t;byte_t&t;&t;unsigned char&t; 8 bits&n; *&t;u_short&t;&t;int16&t;&t;unsigned short&t;16 bits&n; *&t;u_int&t;&t;int16&t;&t;unsigned short&t;16 bits&n; *&t;u_long&t;&t;unsigned long&t;unsigned long&t;32 bits&n; *&t;int&t;&t;int32&t;&t;long&t;&t;32 bits&n; */
DECL|typedef|byte_t
r_typedef
id|__u8
id|byte_t
suffix:semicolon
DECL|typedef|int32
r_typedef
id|__u32
id|int32
suffix:semicolon
multiline_comment|/*&n; * &quot;state&quot; data for each active tcp conversation on the wire.  This is&n; * basically a copy of the entire IP/TCP header from the last packet&n; * we saw from the conversation together with a small identifier&n; * the transmit &amp; receive ends of the line use to locate saved header.&n; */
DECL|struct|cstate
r_struct
id|cstate
(brace
DECL|member|cs_this
id|byte_t
id|cs_this
suffix:semicolon
multiline_comment|/* connection id number (xmit) */
DECL|member|next
r_struct
id|cstate
op_star
id|next
suffix:semicolon
multiline_comment|/* next in ring (xmit) */
DECL|member|cs_ip
r_struct
id|iphdr
id|cs_ip
suffix:semicolon
multiline_comment|/* ip/tcp hdr from most recent packet */
DECL|member|cs_tcp
r_struct
id|tcphdr
id|cs_tcp
suffix:semicolon
DECL|member|cs_ipopt
r_int
r_char
id|cs_ipopt
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|cs_tcpopt
r_int
r_char
id|cs_tcpopt
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|cs_hsize
r_int
id|cs_hsize
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NULLSLSTATE
mdefine_line|#define NULLSLSTATE&t;(struct cstate *)0
multiline_comment|/*&n; * all the state data for one serial line (we need one of these per line).&n; */
DECL|struct|slcompress
r_struct
id|slcompress
(brace
DECL|member|tstate
r_struct
id|cstate
op_star
id|tstate
suffix:semicolon
multiline_comment|/* transmit connection states (array)*/
DECL|member|rstate
r_struct
id|cstate
op_star
id|rstate
suffix:semicolon
multiline_comment|/* receive connection states (array)*/
DECL|member|tslot_limit
id|byte_t
id|tslot_limit
suffix:semicolon
multiline_comment|/* highest transmit slot id (0-l)*/
DECL|member|rslot_limit
id|byte_t
id|rslot_limit
suffix:semicolon
multiline_comment|/* highest receive slot id (0-l)*/
DECL|member|xmit_oldest
id|byte_t
id|xmit_oldest
suffix:semicolon
multiline_comment|/* oldest xmit in ring */
DECL|member|xmit_current
id|byte_t
id|xmit_current
suffix:semicolon
multiline_comment|/* most recent xmit id */
DECL|member|recv_current
id|byte_t
id|recv_current
suffix:semicolon
multiline_comment|/* most recent rcvd id */
DECL|member|flags
id|byte_t
id|flags
suffix:semicolon
DECL|macro|SLF_TOSS
mdefine_line|#define SLF_TOSS&t;0x01&t;/* tossing rcvd frames until id received */
DECL|member|sls_o_nontcp
id|int32
id|sls_o_nontcp
suffix:semicolon
multiline_comment|/* outbound non-TCP packets */
DECL|member|sls_o_tcp
id|int32
id|sls_o_tcp
suffix:semicolon
multiline_comment|/* outbound TCP packets */
DECL|member|sls_o_uncompressed
id|int32
id|sls_o_uncompressed
suffix:semicolon
multiline_comment|/* outbound uncompressed packets */
DECL|member|sls_o_compressed
id|int32
id|sls_o_compressed
suffix:semicolon
multiline_comment|/* outbound compressed packets */
DECL|member|sls_o_searches
id|int32
id|sls_o_searches
suffix:semicolon
multiline_comment|/* searches for connection state */
DECL|member|sls_o_misses
id|int32
id|sls_o_misses
suffix:semicolon
multiline_comment|/* times couldn&squot;t find conn. state */
DECL|member|sls_i_uncompressed
id|int32
id|sls_i_uncompressed
suffix:semicolon
multiline_comment|/* inbound uncompressed packets */
DECL|member|sls_i_compressed
id|int32
id|sls_i_compressed
suffix:semicolon
multiline_comment|/* inbound compressed packets */
DECL|member|sls_i_error
id|int32
id|sls_i_error
suffix:semicolon
multiline_comment|/* inbound error packets */
DECL|member|sls_i_tossed
id|int32
id|sls_i_tossed
suffix:semicolon
multiline_comment|/* inbound packets tossed because of error */
DECL|member|sls_i_runt
id|int32
id|sls_i_runt
suffix:semicolon
DECL|member|sls_i_badcheck
id|int32
id|sls_i_badcheck
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NULLSLCOMPR
mdefine_line|#define NULLSLCOMPR&t;(struct slcompress *)0
DECL|macro|__ARGS
mdefine_line|#define __ARGS(x) x
multiline_comment|/* In slhc.c: */
r_struct
id|slcompress
op_star
id|slhc_init
id|__ARGS
c_func
(paren
(paren
r_int
id|rslots
comma
r_int
id|tslots
)paren
)paren
suffix:semicolon
r_void
id|slhc_free
id|__ARGS
c_func
(paren
(paren
r_struct
id|slcompress
op_star
id|comp
)paren
)paren
suffix:semicolon
r_int
id|slhc_compress
id|__ARGS
c_func
(paren
(paren
r_struct
id|slcompress
op_star
id|comp
comma
r_int
r_char
op_star
id|icp
comma
r_int
id|isize
comma
r_int
r_char
op_star
id|ocp
comma
r_int
r_char
op_star
op_star
id|cpp
comma
r_int
id|compress_cid
)paren
)paren
suffix:semicolon
r_int
id|slhc_uncompress
id|__ARGS
c_func
(paren
(paren
r_struct
id|slcompress
op_star
id|comp
comma
r_int
r_char
op_star
id|icp
comma
r_int
id|isize
)paren
)paren
suffix:semicolon
r_int
id|slhc_remember
id|__ARGS
c_func
(paren
(paren
r_struct
id|slcompress
op_star
id|comp
comma
r_int
r_char
op_star
id|icp
comma
r_int
id|isize
)paren
)paren
suffix:semicolon
r_int
id|slhc_toss
id|__ARGS
c_func
(paren
(paren
r_struct
id|slcompress
op_star
id|comp
)paren
)paren
suffix:semicolon
r_void
id|slhc_i_status
id|__ARGS
c_func
(paren
(paren
r_struct
id|slcompress
op_star
id|comp
)paren
)paren
suffix:semicolon
r_void
id|slhc_o_status
id|__ARGS
c_func
(paren
(paren
r_struct
id|slcompress
op_star
id|comp
)paren
)paren
suffix:semicolon
macro_line|#endif&t;/* _SLHC_H */
eof
