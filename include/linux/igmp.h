multiline_comment|/*&n; *&t;Linux NET3:&t;Internet Group Management Protocol  [IGMP]&n; *&n; *&t;Authors:&n; *&t;&t;Alan Cox &lt;Alan.Cox@linux.org&gt;&n; *&n; *&t;Extended to talk the BSD extended IGMP protocol of mrouted 3.6&n; *&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_IGMP_H
DECL|macro|_LINUX_IGMP_H
mdefine_line|#define _LINUX_IGMP_H
multiline_comment|/*&n; *&t;IGMP protocol structures&n; */
multiline_comment|/*&n; *&t;Header in on cable format&n; */
DECL|struct|igmphdr
r_struct
id|igmphdr
(brace
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|code
id|__u8
id|code
suffix:semicolon
multiline_comment|/* For newer IGMP */
DECL|member|csum
id|__u16
id|csum
suffix:semicolon
DECL|member|group
id|__u32
id|group
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* V3 group record types [grec_type] */
DECL|macro|IGMPV3_MODE_IS_INCLUDE
mdefine_line|#define IGMPV3_MODE_IS_INCLUDE&t;&t;1
DECL|macro|IGMPV3_MODE_IS_EXCLUDE
mdefine_line|#define IGMPV3_MODE_IS_EXCLUDE&t;&t;2
DECL|macro|IGMPV3_CHANGE_TO_INCLUDE
mdefine_line|#define IGMPV3_CHANGE_TO_INCLUDE&t;3
DECL|macro|IGMPV3_CHANGE_TO_EXCLUDE
mdefine_line|#define IGMPV3_CHANGE_TO_EXCLUDE&t;4
DECL|macro|IGMPV3_ALLOW_NEW_SOURCES
mdefine_line|#define IGMPV3_ALLOW_NEW_SOURCES&t;5
DECL|macro|IGMPV3_BLOCK_OLD_SOURCES
mdefine_line|#define IGMPV3_BLOCK_OLD_SOURCES&t;6
DECL|struct|igmpv3_grec
r_struct
id|igmpv3_grec
(brace
DECL|member|grec_type
id|__u8
id|grec_type
suffix:semicolon
DECL|member|grec_auxwords
id|__u8
id|grec_auxwords
suffix:semicolon
DECL|member|grec_nsrcs
id|__u16
id|grec_nsrcs
suffix:semicolon
DECL|member|grec_mca
id|__u32
id|grec_mca
suffix:semicolon
DECL|member|grec_src
id|__u32
id|grec_src
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|igmpv3_report
r_struct
id|igmpv3_report
(brace
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|resv1
id|__u8
id|resv1
suffix:semicolon
DECL|member|csum
id|__u16
id|csum
suffix:semicolon
DECL|member|resv2
id|__u16
id|resv2
suffix:semicolon
DECL|member|ngrec
id|__u16
id|ngrec
suffix:semicolon
DECL|member|grec
r_struct
id|igmpv3_grec
id|grec
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|igmpv3_query
r_struct
id|igmpv3_query
(brace
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|code
id|__u8
id|code
suffix:semicolon
DECL|member|csum
id|__u16
id|csum
suffix:semicolon
DECL|member|group
id|__u32
id|group
suffix:semicolon
macro_line|#if defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|qrv
id|__u8
id|qrv
suffix:colon
l_int|3
comma
DECL|member|suppress
id|suppress
suffix:colon
l_int|1
comma
DECL|member|resv
id|resv
suffix:colon
l_int|4
suffix:semicolon
macro_line|#elif defined(__BIG_ENDIAN_BITFIELD)
DECL|member|resv
id|__u8
id|resv
suffix:colon
l_int|4
comma
DECL|member|suppress
id|suppress
suffix:colon
l_int|1
comma
DECL|member|qrv
id|qrv
suffix:colon
l_int|3
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|qqic
id|__u8
id|qqic
suffix:semicolon
DECL|member|nsrcs
id|__u16
id|nsrcs
suffix:semicolon
DECL|member|srcs
id|__u32
id|srcs
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IGMP_HOST_MEMBERSHIP_QUERY
mdefine_line|#define IGMP_HOST_MEMBERSHIP_QUERY&t;0x11&t;/* From RFC1112 */
DECL|macro|IGMP_HOST_MEMBERSHIP_REPORT
mdefine_line|#define IGMP_HOST_MEMBERSHIP_REPORT&t;0x12&t;/* Ditto */
DECL|macro|IGMP_DVMRP
mdefine_line|#define IGMP_DVMRP&t;&t;&t;0x13&t;/* DVMRP routing */
DECL|macro|IGMP_PIM
mdefine_line|#define IGMP_PIM&t;&t;&t;0x14&t;/* PIM routing */
DECL|macro|IGMP_TRACE
mdefine_line|#define IGMP_TRACE&t;&t;&t;0x15
DECL|macro|IGMPV2_HOST_MEMBERSHIP_REPORT
mdefine_line|#define IGMPV2_HOST_MEMBERSHIP_REPORT&t;0x16&t;/* V2 version of 0x11 */
DECL|macro|IGMP_HOST_LEAVE_MESSAGE
mdefine_line|#define IGMP_HOST_LEAVE_MESSAGE &t;0x17
DECL|macro|IGMPV3_HOST_MEMBERSHIP_REPORT
mdefine_line|#define IGMPV3_HOST_MEMBERSHIP_REPORT&t;0x22&t;/* V3 version of 0x11 */
DECL|macro|IGMP_MTRACE_RESP
mdefine_line|#define IGMP_MTRACE_RESP&t;&t;0x1e
DECL|macro|IGMP_MTRACE
mdefine_line|#define IGMP_MTRACE&t;&t;&t;0x1f
multiline_comment|/*&n; *&t;Use the BSD names for these for compatibility&n; */
DECL|macro|IGMP_DELAYING_MEMBER
mdefine_line|#define IGMP_DELAYING_MEMBER&t;&t;0x01
DECL|macro|IGMP_IDLE_MEMBER
mdefine_line|#define IGMP_IDLE_MEMBER&t;&t;0x02
DECL|macro|IGMP_LAZY_MEMBER
mdefine_line|#define IGMP_LAZY_MEMBER&t;&t;0x03
DECL|macro|IGMP_SLEEPING_MEMBER
mdefine_line|#define IGMP_SLEEPING_MEMBER&t;&t;0x04
DECL|macro|IGMP_AWAKENING_MEMBER
mdefine_line|#define IGMP_AWAKENING_MEMBER&t;&t;0x05
DECL|macro|IGMP_MINLEN
mdefine_line|#define IGMP_MINLEN&t;&t;&t;8
DECL|macro|IGMP_MAX_HOST_REPORT_DELAY
mdefine_line|#define IGMP_MAX_HOST_REPORT_DELAY&t;10&t;/* max delay for response to */
multiline_comment|/* query (in seconds)&t;*/
DECL|macro|IGMP_TIMER_SCALE
mdefine_line|#define IGMP_TIMER_SCALE&t;&t;10&t;/* denotes that the igmphdr-&gt;timer field */
multiline_comment|/* specifies time in 10th of seconds&t; */
DECL|macro|IGMP_AGE_THRESHOLD
mdefine_line|#define IGMP_AGE_THRESHOLD&t;&t;400&t;/* If this host don&squot;t hear any IGMP V1&t;*/
multiline_comment|/* message in this period of time,&t;*/
multiline_comment|/* revert to IGMP v2 router.&t;&t;*/
DECL|macro|IGMP_ALL_HOSTS
mdefine_line|#define IGMP_ALL_HOSTS&t;&t;htonl(0xE0000001L)
DECL|macro|IGMP_ALL_ROUTER
mdefine_line|#define IGMP_ALL_ROUTER &t;htonl(0xE0000002L)
DECL|macro|IGMPV3_ALL_MCR
mdefine_line|#define IGMPV3_ALL_MCR&t; &t;htonl(0xE0000016L)
DECL|macro|IGMP_LOCAL_GROUP
mdefine_line|#define IGMP_LOCAL_GROUP&t;htonl(0xE0000000L)
DECL|macro|IGMP_LOCAL_GROUP_MASK
mdefine_line|#define IGMP_LOCAL_GROUP_MASK&t;htonl(0xFFFFFF00L)
multiline_comment|/*&n; * struct for keeping the multicast list in&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/in.h&gt;
DECL|struct|ip_sf_socklist
r_struct
id|ip_sf_socklist
(brace
DECL|member|sl_max
r_int
r_int
id|sl_max
suffix:semicolon
DECL|member|sl_count
r_int
r_int
id|sl_count
suffix:semicolon
DECL|member|sl_addr
id|__u32
id|sl_addr
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IP_SFLSIZE
mdefine_line|#define IP_SFLSIZE(count)&t;(sizeof(struct ip_sf_socklist) + &bslash;&n;&t;(count) * sizeof(__u32))
DECL|macro|IP_SFBLOCK
mdefine_line|#define IP_SFBLOCK&t;10&t;/* allocate this many at once */
multiline_comment|/* ip_mc_socklist is real list now. Speed is not argument;&n;   this list never used in fast path code&n; */
DECL|struct|ip_mc_socklist
r_struct
id|ip_mc_socklist
(brace
DECL|member|next
r_struct
id|ip_mc_socklist
op_star
id|next
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|multi
r_struct
id|ip_mreqn
id|multi
suffix:semicolon
DECL|member|sfmode
r_int
r_int
id|sfmode
suffix:semicolon
multiline_comment|/* MCAST_{INCLUDE,EXCLUDE} */
DECL|member|sflist
r_struct
id|ip_sf_socklist
op_star
id|sflist
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ip_sf_list
r_struct
id|ip_sf_list
(brace
DECL|member|sf_next
r_struct
id|ip_sf_list
op_star
id|sf_next
suffix:semicolon
DECL|member|sf_inaddr
id|__u32
id|sf_inaddr
suffix:semicolon
DECL|member|sf_count
r_int
r_int
id|sf_count
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* include/exclude counts */
DECL|member|sf_gsresp
r_int
r_char
id|sf_gsresp
suffix:semicolon
multiline_comment|/* include in g &amp; s response? */
DECL|member|sf_oldin
r_int
r_char
id|sf_oldin
suffix:semicolon
multiline_comment|/* change state */
DECL|member|sf_crcount
r_int
r_char
id|sf_crcount
suffix:semicolon
multiline_comment|/* retrans. left to send */
)brace
suffix:semicolon
DECL|struct|ip_mc_list
r_struct
id|ip_mc_list
(brace
DECL|member|interface
r_struct
id|in_device
op_star
id|interface
suffix:semicolon
DECL|member|multiaddr
r_int
r_int
id|multiaddr
suffix:semicolon
DECL|member|sources
r_struct
id|ip_sf_list
op_star
id|sources
suffix:semicolon
DECL|member|tomb
r_struct
id|ip_sf_list
op_star
id|tomb
suffix:semicolon
DECL|member|sfmode
r_int
r_int
id|sfmode
suffix:semicolon
DECL|member|sfcount
r_int
r_int
id|sfcount
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|next
r_struct
id|ip_mc_list
op_star
id|next
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|users
r_int
id|users
suffix:semicolon
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|tm_running
r_char
id|tm_running
suffix:semicolon
DECL|member|reporter
r_char
id|reporter
suffix:semicolon
DECL|member|unsolicit_count
r_char
id|unsolicit_count
suffix:semicolon
DECL|member|loaded
r_char
id|loaded
suffix:semicolon
DECL|member|gsquery
r_int
r_char
id|gsquery
suffix:semicolon
multiline_comment|/* check source marks? */
DECL|member|crcount
r_int
r_char
id|crcount
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* V3 exponential field decoding */
DECL|macro|IGMPV3_MASK
mdefine_line|#define IGMPV3_MASK(value, nb) ((nb)&gt;=32 ? (value) : ((1&lt;&lt;(nb))-1) &amp; (value))
DECL|macro|IGMPV3_EXP
mdefine_line|#define IGMPV3_EXP(thresh, nbmant, nbexp, value) &bslash;&n;&t;((value) &lt; (thresh) ? (value) : &bslash;&n;        ((IGMPV3_MASK(value, nbmant) | (1&lt;&lt;(nbmant+nbexp))) &lt;&lt; &bslash;&n;         (IGMPV3_MASK((value) &gt;&gt; (nbmant), nbexp) + (nbexp))))
DECL|macro|IGMPV3_QQIC
mdefine_line|#define IGMPV3_QQIC(value) IGMPV3_EXP(0x80, 4, 3, value)
DECL|macro|IGMPV3_MRC
mdefine_line|#define IGMPV3_MRC(value) IGMPV3_EXP(0x80, 4, 3, value)
r_extern
r_int
id|ip_check_mc
c_func
(paren
r_struct
id|in_device
op_star
id|dev
comma
id|u32
id|mc_addr
comma
id|u32
id|src_addr
comma
id|u16
id|proto
)paren
suffix:semicolon
r_extern
r_int
id|igmp_rcv
c_func
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ip_mc_join_group
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|ip_mreqn
op_star
id|imr
)paren
suffix:semicolon
r_extern
r_int
id|ip_mc_leave_group
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|ip_mreqn
op_star
id|imr
)paren
suffix:semicolon
r_extern
r_void
id|ip_mc_drop_socket
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
r_extern
r_int
id|ip_mc_source
c_func
(paren
r_int
id|add
comma
r_int
id|omode
comma
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|ip_mreq_source
op_star
id|mreqs
comma
r_int
id|ifindex
)paren
suffix:semicolon
r_extern
r_int
id|ip_mc_msfilter
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|ip_msfilter
op_star
id|msf
comma
r_int
id|ifindex
)paren
suffix:semicolon
r_extern
r_int
id|ip_mc_msfget
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|ip_msfilter
op_star
id|msf
comma
r_struct
id|ip_msfilter
op_star
id|optval
comma
r_int
op_star
id|optlen
)paren
suffix:semicolon
r_extern
r_int
id|ip_mc_gsfget
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|group_filter
op_star
id|gsf
comma
r_struct
id|group_filter
op_star
id|optval
comma
r_int
op_star
id|optlen
)paren
suffix:semicolon
r_extern
r_int
id|ip_mc_sf_allow
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
id|u32
id|local
comma
id|u32
id|rmt
comma
r_int
id|dif
)paren
suffix:semicolon
r_extern
r_void
id|ip_mr_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ip_mc_init_dev
c_func
(paren
r_struct
id|in_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ip_mc_destroy_dev
c_func
(paren
r_struct
id|in_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ip_mc_up
c_func
(paren
r_struct
id|in_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ip_mc_down
c_func
(paren
r_struct
id|in_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ip_mc_dec_group
c_func
(paren
r_struct
id|in_device
op_star
id|in_dev
comma
id|u32
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|ip_mc_inc_group
c_func
(paren
r_struct
id|in_device
op_star
id|in_dev
comma
id|u32
id|addr
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
