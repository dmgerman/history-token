multiline_comment|/*&t;$Id: ppp_defs.h,v 1.2 1994/09/21 01:31:06 paulus Exp $&t;*/
multiline_comment|/*&n; * ppp_defs.h - PPP definitions.&n; *&n; * Copyright (c) 1994 The Australian National University.&n; * All rights reserved.&n; *&n; * Permission to use, copy, modify, and distribute this software and its&n; * documentation is hereby granted, provided that the above copyright&n; * notice appears in all copies.  This software is provided without any&n; * warranty, express or implied. The Australian National University&n; * makes no representations about the suitability of this software for&n; * any purpose.&n; *&n; * IN NO EVENT SHALL THE AUSTRALIAN NATIONAL UNIVERSITY BE LIABLE TO ANY&n; * PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES&n; * ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF&n; * THE AUSTRALIAN NATIONAL UNIVERSITY HAVE BEEN ADVISED OF THE POSSIBILITY&n; * OF SUCH DAMAGE.&n; *&n; * THE AUSTRALIAN NATIONAL UNIVERSITY SPECIFICALLY DISCLAIMS ANY WARRANTIES,&n; * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY&n; * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS&n; * ON AN &quot;AS IS&quot; BASIS, AND THE AUSTRALIAN NATIONAL UNIVERSITY HAS NO&n; * OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS,&n; * OR MODIFICATIONS.&n; */
multiline_comment|/*&n; *  ==FILEVERSION 20000114==&n; *&n; *  NOTE TO MAINTAINERS:&n; *     If you modify this file at all, please set the above date.&n; *     ppp_defs.h is shipped with a PPP distribution as well as with the kernel;&n; *     if everyone increases the FILEVERSION number above, then scripts&n; *     can do the right thing when deciding whether to install a new ppp_defs.h&n; *     file.  Don&squot;t change the format of that line otherwise, so the&n; *     installation script can recognize it.&n; */
macro_line|#ifndef _PPP_DEFS_H_
DECL|macro|_PPP_DEFS_H_
mdefine_line|#define _PPP_DEFS_H_
multiline_comment|/*&n; * The basic PPP frame.&n; */
DECL|macro|PPP_HDRLEN
mdefine_line|#define PPP_HDRLEN&t;4&t;/* octets for standard ppp header */
DECL|macro|PPP_FCSLEN
mdefine_line|#define PPP_FCSLEN&t;2&t;/* octets for FCS */
DECL|macro|PPP_MRU
mdefine_line|#define PPP_MRU&t;&t;1500&t;/* default MRU = max length of info field */
DECL|macro|PPP_ADDRESS
mdefine_line|#define PPP_ADDRESS(p)&t;(((__u8 *)(p))[0])
DECL|macro|PPP_CONTROL
mdefine_line|#define PPP_CONTROL(p)&t;(((__u8 *)(p))[1])
DECL|macro|PPP_PROTOCOL
mdefine_line|#define PPP_PROTOCOL(p)&t;((((__u8 *)(p))[2] &lt;&lt; 8) + ((__u8 *)(p))[3])
multiline_comment|/*&n; * Significant octet values.&n; */
DECL|macro|PPP_ALLSTATIONS
mdefine_line|#define&t;PPP_ALLSTATIONS&t;0xff&t;/* All-Stations broadcast address */
DECL|macro|PPP_UI
mdefine_line|#define&t;PPP_UI&t;&t;0x03&t;/* Unnumbered Information */
DECL|macro|PPP_FLAG
mdefine_line|#define&t;PPP_FLAG&t;0x7e&t;/* Flag Sequence */
DECL|macro|PPP_ESCAPE
mdefine_line|#define&t;PPP_ESCAPE&t;0x7d&t;/* Asynchronous Control Escape */
DECL|macro|PPP_TRANS
mdefine_line|#define&t;PPP_TRANS&t;0x20&t;/* Asynchronous transparency modifier */
multiline_comment|/*&n; * Protocol field values.&n; */
DECL|macro|PPP_IP
mdefine_line|#define PPP_IP&t;&t;0x21&t;/* Internet Protocol */
DECL|macro|PPP_AT
mdefine_line|#define PPP_AT&t;&t;0x29&t;/* AppleTalk Protocol */
DECL|macro|PPP_IPX
mdefine_line|#define PPP_IPX&t;&t;0x2b&t;/* IPX protocol */
DECL|macro|PPP_VJC_COMP
mdefine_line|#define&t;PPP_VJC_COMP&t;0x2d&t;/* VJ compressed TCP */
DECL|macro|PPP_VJC_UNCOMP
mdefine_line|#define&t;PPP_VJC_UNCOMP&t;0x2f&t;/* VJ uncompressed TCP */
DECL|macro|PPP_MP
mdefine_line|#define PPP_MP&t;&t;0x3d&t;/* Multilink protocol */
DECL|macro|PPP_IPV6
mdefine_line|#define PPP_IPV6&t;0x57&t;/* Internet Protocol Version 6 */
DECL|macro|PPP_COMPFRAG
mdefine_line|#define PPP_COMPFRAG&t;0xfb&t;/* fragment compressed below bundle */
DECL|macro|PPP_COMP
mdefine_line|#define PPP_COMP&t;0xfd&t;/* compressed packet */
DECL|macro|PPP_IPCP
mdefine_line|#define PPP_IPCP&t;0x8021&t;/* IP Control Protocol */
DECL|macro|PPP_ATCP
mdefine_line|#define PPP_ATCP&t;0x8029&t;/* AppleTalk Control Protocol */
DECL|macro|PPP_IPXCP
mdefine_line|#define PPP_IPXCP&t;0x802b&t;/* IPX Control Protocol */
DECL|macro|PPP_IPV6CP
mdefine_line|#define PPP_IPV6CP&t;0x8057&t;/* IPv6 Control Protocol */
DECL|macro|PPP_CCPFRAG
mdefine_line|#define PPP_CCPFRAG&t;0x80fb&t;/* CCP at link level (below MP bundle) */
DECL|macro|PPP_CCP
mdefine_line|#define PPP_CCP&t;&t;0x80fd&t;/* Compression Control Protocol */
DECL|macro|PPP_LCP
mdefine_line|#define PPP_LCP&t;&t;0xc021&t;/* Link Control Protocol */
DECL|macro|PPP_PAP
mdefine_line|#define PPP_PAP&t;&t;0xc023&t;/* Password Authentication Protocol */
DECL|macro|PPP_LQR
mdefine_line|#define PPP_LQR&t;&t;0xc025&t;/* Link Quality Report protocol */
DECL|macro|PPP_CHAP
mdefine_line|#define PPP_CHAP&t;0xc223&t;/* Cryptographic Handshake Auth. Protocol */
DECL|macro|PPP_CBCP
mdefine_line|#define PPP_CBCP&t;0xc029&t;/* Callback Control Protocol */
multiline_comment|/*&n; * Values for FCS calculations.&n; */
DECL|macro|PPP_INITFCS
mdefine_line|#define PPP_INITFCS&t;0xffff&t;/* Initial FCS value */
DECL|macro|PPP_GOODFCS
mdefine_line|#define PPP_GOODFCS&t;0xf0b8&t;/* Good final FCS value */
DECL|macro|PPP_FCS
mdefine_line|#define PPP_FCS(fcs, c)&t;(((fcs) &gt;&gt; 8) ^ fcstab[((fcs) ^ (c)) &amp; 0xff])
multiline_comment|/*&n; * Extended asyncmap - allows any character to be escaped.&n; */
DECL|typedef|ext_accm
r_typedef
id|__u32
id|ext_accm
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/*&n; * What to do with network protocol (NP) packets.&n; */
DECL|enum|NPmode
r_enum
id|NPmode
(brace
DECL|enumerator|NPMODE_PASS
id|NPMODE_PASS
comma
multiline_comment|/* pass the packet through */
DECL|enumerator|NPMODE_DROP
id|NPMODE_DROP
comma
multiline_comment|/* silently drop the packet */
DECL|enumerator|NPMODE_ERROR
id|NPMODE_ERROR
comma
multiline_comment|/* return an error */
DECL|enumerator|NPMODE_QUEUE
id|NPMODE_QUEUE
multiline_comment|/* save it up for later. */
)brace
suffix:semicolon
multiline_comment|/*&n; * Statistics for LQRP and pppstats&n; */
DECL|struct|pppstat
r_struct
id|pppstat
(brace
DECL|member|ppp_discards
id|__u32
id|ppp_discards
suffix:semicolon
multiline_comment|/* # frames discarded */
DECL|member|ppp_ibytes
id|__u32
id|ppp_ibytes
suffix:semicolon
multiline_comment|/* bytes received */
DECL|member|ppp_ioctects
id|__u32
id|ppp_ioctects
suffix:semicolon
multiline_comment|/* bytes received not in error */
DECL|member|ppp_ipackets
id|__u32
id|ppp_ipackets
suffix:semicolon
multiline_comment|/* packets received */
DECL|member|ppp_ierrors
id|__u32
id|ppp_ierrors
suffix:semicolon
multiline_comment|/* receive errors */
DECL|member|ppp_ilqrs
id|__u32
id|ppp_ilqrs
suffix:semicolon
multiline_comment|/* # LQR frames received */
DECL|member|ppp_obytes
id|__u32
id|ppp_obytes
suffix:semicolon
multiline_comment|/* raw bytes sent */
DECL|member|ppp_ooctects
id|__u32
id|ppp_ooctects
suffix:semicolon
multiline_comment|/* frame bytes sent */
DECL|member|ppp_opackets
id|__u32
id|ppp_opackets
suffix:semicolon
multiline_comment|/* packets sent */
DECL|member|ppp_oerrors
id|__u32
id|ppp_oerrors
suffix:semicolon
multiline_comment|/* transmit errors */
DECL|member|ppp_olqrs
id|__u32
id|ppp_olqrs
suffix:semicolon
multiline_comment|/* # LQR frames sent */
)brace
suffix:semicolon
DECL|struct|vjstat
r_struct
id|vjstat
(brace
DECL|member|vjs_packets
id|__u32
id|vjs_packets
suffix:semicolon
multiline_comment|/* outbound packets */
DECL|member|vjs_compressed
id|__u32
id|vjs_compressed
suffix:semicolon
multiline_comment|/* outbound compressed packets */
DECL|member|vjs_searches
id|__u32
id|vjs_searches
suffix:semicolon
multiline_comment|/* searches for connection state */
DECL|member|vjs_misses
id|__u32
id|vjs_misses
suffix:semicolon
multiline_comment|/* times couldn&squot;t find conn. state */
DECL|member|vjs_uncompressedin
id|__u32
id|vjs_uncompressedin
suffix:semicolon
multiline_comment|/* inbound uncompressed packets */
DECL|member|vjs_compressedin
id|__u32
id|vjs_compressedin
suffix:semicolon
multiline_comment|/* inbound compressed packets */
DECL|member|vjs_errorin
id|__u32
id|vjs_errorin
suffix:semicolon
multiline_comment|/* inbound unknown type packets */
DECL|member|vjs_tossed
id|__u32
id|vjs_tossed
suffix:semicolon
multiline_comment|/* inbound packets tossed because of error */
)brace
suffix:semicolon
DECL|struct|compstat
r_struct
id|compstat
(brace
DECL|member|unc_bytes
id|__u32
id|unc_bytes
suffix:semicolon
multiline_comment|/* total uncompressed bytes */
DECL|member|unc_packets
id|__u32
id|unc_packets
suffix:semicolon
multiline_comment|/* total uncompressed packets */
DECL|member|comp_bytes
id|__u32
id|comp_bytes
suffix:semicolon
multiline_comment|/* compressed bytes */
DECL|member|comp_packets
id|__u32
id|comp_packets
suffix:semicolon
multiline_comment|/* compressed packets */
DECL|member|inc_bytes
id|__u32
id|inc_bytes
suffix:semicolon
multiline_comment|/* incompressible bytes */
DECL|member|inc_packets
id|__u32
id|inc_packets
suffix:semicolon
multiline_comment|/* incompressible packets */
multiline_comment|/* the compression ratio is defined as in_count / bytes_out */
DECL|member|in_count
id|__u32
id|in_count
suffix:semicolon
multiline_comment|/* Bytes received */
DECL|member|bytes_out
id|__u32
id|bytes_out
suffix:semicolon
multiline_comment|/* Bytes transmitted */
DECL|member|ratio
r_float
id|ratio
suffix:semicolon
multiline_comment|/* not computed in kernel. */
)brace
suffix:semicolon
DECL|struct|ppp_stats
r_struct
id|ppp_stats
(brace
DECL|member|p
r_struct
id|pppstat
id|p
suffix:semicolon
multiline_comment|/* basic PPP statistics */
DECL|member|vj
r_struct
id|vjstat
id|vj
suffix:semicolon
multiline_comment|/* VJ header compression statistics */
)brace
suffix:semicolon
DECL|struct|ppp_comp_stats
r_struct
id|ppp_comp_stats
(brace
DECL|member|c
r_struct
id|compstat
id|c
suffix:semicolon
multiline_comment|/* packet compression statistics */
DECL|member|d
r_struct
id|compstat
id|d
suffix:semicolon
multiline_comment|/* packet decompression statistics */
)brace
suffix:semicolon
multiline_comment|/*&n; * The following structure records the time in seconds since&n; * the last NP packet was sent or received.&n; */
DECL|struct|ppp_idle
r_struct
id|ppp_idle
(brace
DECL|member|xmit_idle
id|time_t
id|xmit_idle
suffix:semicolon
multiline_comment|/* time since last NP packet sent */
DECL|member|recv_idle
id|time_t
id|recv_idle
suffix:semicolon
multiline_comment|/* time since last NP packet received */
)brace
suffix:semicolon
macro_line|#ifndef __P
macro_line|#ifdef __STDC__
DECL|macro|__P
mdefine_line|#define __P(x)&t;x
macro_line|#else
DECL|macro|__P
mdefine_line|#define __P(x)&t;()
macro_line|#endif
macro_line|#endif
macro_line|#endif /* _PPP_DEFS_H_ */
eof
