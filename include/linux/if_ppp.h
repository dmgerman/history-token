multiline_comment|/*&t;$Id: if_ppp.h,v 1.21 2000/03/27 06:03:36 paulus Exp $&t;*/
multiline_comment|/*&n; * if_ppp.h - Point-to-Point Protocol definitions.&n; *&n; * Copyright (c) 1989 Carnegie Mellon University.&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms are permitted&n; * provided that the above copyright notice and this paragraph are&n; * duplicated in all such forms and that any documentation,&n; * advertising materials, and other materials related to such&n; * distribution and use acknowledge that the software was developed&n; * by Carnegie Mellon University.  The name of the&n; * University may not be used to endorse or promote products derived&n; * from this software without specific prior written permission.&n; * THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND WITHOUT ANY EXPRESS OR&n; * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED&n; * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; */
multiline_comment|/*&n; *  ==FILEVERSION 20000724==&n; *&n; *  NOTE TO MAINTAINERS:&n; *     If you modify this file at all, please set the above date.&n; *     if_ppp.h is shipped with a PPP distribution as well as with the kernel;&n; *     if everyone increases the FILEVERSION number above, then scripts&n; *     can do the right thing when deciding whether to install a new if_ppp.h&n; *     file.  Don&squot;t change the format of that line otherwise, so the&n; *     installation script can recognize it.&n; */
macro_line|#ifndef _IF_PPP_H_
DECL|macro|_IF_PPP_H_
mdefine_line|#define _IF_PPP_H_
multiline_comment|/*&n; * Packet sizes&n; */
DECL|macro|PPP_MTU
mdefine_line|#define&t;PPP_MTU&t;&t;1500&t;/* Default MTU (size of Info field) */
DECL|macro|PPP_MAXMRU
mdefine_line|#define PPP_MAXMRU&t;65000&t;/* Largest MRU we allow */
DECL|macro|PROTO_IPX
mdefine_line|#define PROTO_IPX&t;0x002b&t;/* protocol numbers */
DECL|macro|PROTO_DNA_RT
mdefine_line|#define PROTO_DNA_RT    0x0027  /* DNA Routing */
multiline_comment|/*&n; * Bit definitions for flags.&n; */
DECL|macro|SC_COMP_PROT
mdefine_line|#define SC_COMP_PROT&t;0x00000001&t;/* protocol compression (output) */
DECL|macro|SC_COMP_AC
mdefine_line|#define SC_COMP_AC&t;0x00000002&t;/* header compression (output) */
DECL|macro|SC_COMP_TCP
mdefine_line|#define&t;SC_COMP_TCP&t;0x00000004&t;/* TCP (VJ) compression (output) */
DECL|macro|SC_NO_TCP_CCID
mdefine_line|#define SC_NO_TCP_CCID&t;0x00000008&t;/* disable VJ connection-id comp. */
DECL|macro|SC_REJ_COMP_AC
mdefine_line|#define SC_REJ_COMP_AC&t;0x00000010&t;/* reject adrs/ctrl comp. on input */
DECL|macro|SC_REJ_COMP_TCP
mdefine_line|#define SC_REJ_COMP_TCP&t;0x00000020&t;/* reject TCP (VJ) comp. on input */
DECL|macro|SC_CCP_OPEN
mdefine_line|#define SC_CCP_OPEN&t;0x00000040&t;/* Look at CCP packets */
DECL|macro|SC_CCP_UP
mdefine_line|#define SC_CCP_UP&t;0x00000080&t;/* May send/recv compressed packets */
DECL|macro|SC_ENABLE_IP
mdefine_line|#define SC_ENABLE_IP&t;0x00000100&t;/* IP packets may be exchanged */
DECL|macro|SC_LOOP_TRAFFIC
mdefine_line|#define SC_LOOP_TRAFFIC&t;0x00000200&t;/* send traffic to pppd */
DECL|macro|SC_MULTILINK
mdefine_line|#define SC_MULTILINK&t;0x00000400&t;/* do multilink encapsulation */
DECL|macro|SC_MP_SHORTSEQ
mdefine_line|#define SC_MP_SHORTSEQ&t;0x00000800&t;/* use short MP sequence numbers */
DECL|macro|SC_COMP_RUN
mdefine_line|#define SC_COMP_RUN&t;0x00001000&t;/* compressor has been inited */
DECL|macro|SC_DECOMP_RUN
mdefine_line|#define SC_DECOMP_RUN&t;0x00002000&t;/* decompressor has been inited */
DECL|macro|SC_MP_XSHORTSEQ
mdefine_line|#define SC_MP_XSHORTSEQ&t;0x00004000&t;/* transmit short MP seq numbers */
DECL|macro|SC_DEBUG
mdefine_line|#define SC_DEBUG&t;0x00010000&t;/* enable debug messages */
DECL|macro|SC_LOG_INPKT
mdefine_line|#define SC_LOG_INPKT&t;0x00020000&t;/* log contents of good pkts recvd */
DECL|macro|SC_LOG_OUTPKT
mdefine_line|#define SC_LOG_OUTPKT&t;0x00040000&t;/* log contents of pkts sent */
DECL|macro|SC_LOG_RAWIN
mdefine_line|#define SC_LOG_RAWIN&t;0x00080000&t;/* log all chars received */
DECL|macro|SC_LOG_FLUSH
mdefine_line|#define SC_LOG_FLUSH&t;0x00100000&t;/* log all chars flushed */
DECL|macro|SC_SYNC
mdefine_line|#define&t;SC_SYNC&t;&t;0x00200000&t;/* synchronous serial mode */
DECL|macro|SC_MASK
mdefine_line|#define&t;SC_MASK&t;&t;0x0f200fff&t;/* bits that user can change */
multiline_comment|/* state bits */
DECL|macro|SC_XMIT_BUSY
mdefine_line|#define SC_XMIT_BUSY&t;0x10000000&t;/* (used by isdn_ppp?) */
DECL|macro|SC_RCV_ODDP
mdefine_line|#define SC_RCV_ODDP&t;0x08000000&t;/* have rcvd char with odd parity */
DECL|macro|SC_RCV_EVNP
mdefine_line|#define SC_RCV_EVNP&t;0x04000000&t;/* have rcvd char with even parity */
DECL|macro|SC_RCV_B7_1
mdefine_line|#define SC_RCV_B7_1&t;0x02000000&t;/* have rcvd char with bit 7 = 1 */
DECL|macro|SC_RCV_B7_0
mdefine_line|#define SC_RCV_B7_0&t;0x01000000&t;/* have rcvd char with bit 7 = 0 */
DECL|macro|SC_DC_FERROR
mdefine_line|#define SC_DC_FERROR&t;0x00800000&t;/* fatal decomp error detected */
DECL|macro|SC_DC_ERROR
mdefine_line|#define SC_DC_ERROR&t;0x00400000&t;/* non-fatal decomp error detected */
multiline_comment|/*&n; * Ioctl definitions.&n; */
DECL|struct|npioctl
r_struct
id|npioctl
(brace
DECL|member|protocol
r_int
id|protocol
suffix:semicolon
multiline_comment|/* PPP protocol, e.g. PPP_IP */
DECL|member|mode
r_enum
id|NPmode
id|mode
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Structure describing a CCP configuration option, for PPPIOCSCOMPRESS */
DECL|struct|ppp_option_data
r_struct
id|ppp_option_data
(brace
DECL|member|ptr
id|__u8
op_star
id|ptr
suffix:semicolon
DECL|member|length
id|__u32
id|length
suffix:semicolon
DECL|member|transmit
r_int
id|transmit
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ifpppstatsreq
r_struct
id|ifpppstatsreq
(brace
DECL|member|b
r_struct
id|ifreq
id|b
suffix:semicolon
DECL|member|stats
r_struct
id|ppp_stats
id|stats
suffix:semicolon
multiline_comment|/* statistic information */
)brace
suffix:semicolon
DECL|struct|ifpppcstatsreq
r_struct
id|ifpppcstatsreq
(brace
DECL|member|b
r_struct
id|ifreq
id|b
suffix:semicolon
DECL|member|stats
r_struct
id|ppp_comp_stats
id|stats
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ifr__name
mdefine_line|#define ifr__name       b.ifr_ifrn.ifrn_name
DECL|macro|stats_ptr
mdefine_line|#define stats_ptr       b.ifr_ifru.ifru_data
multiline_comment|/*&n; * Ioctl definitions.&n; */
DECL|macro|PPPIOCGFLAGS
mdefine_line|#define&t;PPPIOCGFLAGS&t;_IOR(&squot;t&squot;, 90, int)&t;/* get configuration flags */
DECL|macro|PPPIOCSFLAGS
mdefine_line|#define&t;PPPIOCSFLAGS&t;_IOW(&squot;t&squot;, 89, int)&t;/* set configuration flags */
DECL|macro|PPPIOCGASYNCMAP
mdefine_line|#define&t;PPPIOCGASYNCMAP&t;_IOR(&squot;t&squot;, 88, int)&t;/* get async map */
DECL|macro|PPPIOCSASYNCMAP
mdefine_line|#define&t;PPPIOCSASYNCMAP&t;_IOW(&squot;t&squot;, 87, int)&t;/* set async map */
DECL|macro|PPPIOCGUNIT
mdefine_line|#define&t;PPPIOCGUNIT&t;_IOR(&squot;t&squot;, 86, int)&t;/* get ppp unit number */
DECL|macro|PPPIOCGRASYNCMAP
mdefine_line|#define&t;PPPIOCGRASYNCMAP _IOR(&squot;t&squot;, 85, int)&t;/* get receive async map */
DECL|macro|PPPIOCSRASYNCMAP
mdefine_line|#define&t;PPPIOCSRASYNCMAP _IOW(&squot;t&squot;, 84, int)&t;/* set receive async map */
DECL|macro|PPPIOCGMRU
mdefine_line|#define&t;PPPIOCGMRU&t;_IOR(&squot;t&squot;, 83, int)&t;/* get max receive unit */
DECL|macro|PPPIOCSMRU
mdefine_line|#define&t;PPPIOCSMRU&t;_IOW(&squot;t&squot;, 82, int)&t;/* set max receive unit */
DECL|macro|PPPIOCSMAXCID
mdefine_line|#define&t;PPPIOCSMAXCID&t;_IOW(&squot;t&squot;, 81, int)&t;/* set VJ max slot ID */
DECL|macro|PPPIOCGXASYNCMAP
mdefine_line|#define PPPIOCGXASYNCMAP _IOR(&squot;t&squot;, 80, ext_accm) /* get extended ACCM */
DECL|macro|PPPIOCSXASYNCMAP
mdefine_line|#define PPPIOCSXASYNCMAP _IOW(&squot;t&squot;, 79, ext_accm) /* set extended ACCM */
DECL|macro|PPPIOCXFERUNIT
mdefine_line|#define PPPIOCXFERUNIT&t;_IO(&squot;t&squot;, 78)&t;&t;/* transfer PPP unit */
DECL|macro|PPPIOCSCOMPRESS
mdefine_line|#define PPPIOCSCOMPRESS&t;_IOW(&squot;t&squot;, 77, struct ppp_option_data)
DECL|macro|PPPIOCGNPMODE
mdefine_line|#define PPPIOCGNPMODE&t;_IOWR(&squot;t&squot;, 76, struct npioctl) /* get NP mode */
DECL|macro|PPPIOCSNPMODE
mdefine_line|#define PPPIOCSNPMODE&t;_IOW(&squot;t&squot;, 75, struct npioctl)  /* set NP mode */
DECL|macro|PPPIOCSPASS
mdefine_line|#define PPPIOCSPASS&t;_IOW(&squot;t&squot;, 71, struct sock_fprog) /* set pass filter */
DECL|macro|PPPIOCSACTIVE
mdefine_line|#define PPPIOCSACTIVE&t;_IOW(&squot;t&squot;, 70, struct sock_fprog) /* set active filt */
DECL|macro|PPPIOCGDEBUG
mdefine_line|#define PPPIOCGDEBUG&t;_IOR(&squot;t&squot;, 65, int)&t;/* Read debug level */
DECL|macro|PPPIOCSDEBUG
mdefine_line|#define PPPIOCSDEBUG&t;_IOW(&squot;t&squot;, 64, int)&t;/* Set debug level */
DECL|macro|PPPIOCGIDLE
mdefine_line|#define PPPIOCGIDLE&t;_IOR(&squot;t&squot;, 63, struct ppp_idle) /* get idle time */
DECL|macro|PPPIOCNEWUNIT
mdefine_line|#define PPPIOCNEWUNIT&t;_IOWR(&squot;t&squot;, 62, int)&t;/* create new ppp unit */
DECL|macro|PPPIOCATTACH
mdefine_line|#define PPPIOCATTACH&t;_IOW(&squot;t&squot;, 61, int)&t;/* attach to ppp unit */
DECL|macro|PPPIOCDETACH
mdefine_line|#define PPPIOCDETACH&t;_IOW(&squot;t&squot;, 60, int)&t;/* detach from ppp unit/chan */
DECL|macro|PPPIOCSMRRU
mdefine_line|#define PPPIOCSMRRU&t;_IOW(&squot;t&squot;, 59, int)&t;/* set multilink MRU */
DECL|macro|PPPIOCCONNECT
mdefine_line|#define PPPIOCCONNECT&t;_IOW(&squot;t&squot;, 58, int)&t;/* connect channel to unit */
DECL|macro|PPPIOCDISCONN
mdefine_line|#define PPPIOCDISCONN&t;_IO(&squot;t&squot;, 57)&t;&t;/* disconnect channel */
DECL|macro|PPPIOCATTCHAN
mdefine_line|#define PPPIOCATTCHAN&t;_IOW(&squot;t&squot;, 56, int)&t;/* attach to ppp channel */
DECL|macro|PPPIOCGCHAN
mdefine_line|#define PPPIOCGCHAN&t;_IOR(&squot;t&squot;, 55, int)&t;/* get ppp channel number */
DECL|macro|SIOCGPPPSTATS
mdefine_line|#define SIOCGPPPSTATS   (SIOCDEVPRIVATE + 0)
DECL|macro|SIOCGPPPVER
mdefine_line|#define SIOCGPPPVER     (SIOCDEVPRIVATE + 1)&t;/* NEVER change this!! */
DECL|macro|SIOCGPPPCSTATS
mdefine_line|#define SIOCGPPPCSTATS  (SIOCDEVPRIVATE + 2)
macro_line|#if !defined(ifr_mtu)
DECL|macro|ifr_mtu
mdefine_line|#define ifr_mtu&t;ifr_ifru.ifru_metric
macro_line|#endif
macro_line|#endif /* _IF_PPP_H_ */
eof
