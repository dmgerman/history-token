multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Global definitions for the Token-Ring IEEE 802.5 interface.&n; *&n; * Version:&t;@(#)if_tr.h&t;0.0&t;07/11/94&n; *&n; * Author:&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&t;&t;Donald Becker, &lt;becker@super.org&gt;&n; *    Peter De Schrijver, &lt;stud11@cc4.kuleuven.ac.be&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_IF_TR_H
DECL|macro|_LINUX_IF_TR_H
mdefine_line|#define _LINUX_IF_TR_H
multiline_comment|/* IEEE 802.5 Token-Ring magic constants.  The frame sizes omit the preamble&n;   and FCS/CRC (frame check sequence). */
DECL|macro|TR_ALEN
mdefine_line|#define TR_ALEN&t;6&t;&t;/* Octets in one ethernet addr&t; */
DECL|macro|TR_HLEN
mdefine_line|#define TR_HLEN   (sizeof(struct trh_hdr)+sizeof(struct trllc))
DECL|macro|AC
mdefine_line|#define AC&t;&t;&t;0x10
DECL|macro|LLC_FRAME
mdefine_line|#define LLC_FRAME 0x40
macro_line|#if 0
mdefine_line|#define ETH_HLEN&t;14&t;&t;/* Total octets in header.&t; */
mdefine_line|#define ETH_ZLEN&t;60&t;&t;/* Min. octets in frame sans FCS */
mdefine_line|#define ETH_DATA_LEN&t;1500&t;&t;/* Max. octets in payload&t; */
mdefine_line|#define ETH_FRAME_LEN&t;1514&t;&t;/* Max. octets in frame sans FCS */
macro_line|#endif
multiline_comment|/* LLC and SNAP constants */
DECL|macro|EXTENDED_SAP
mdefine_line|#define EXTENDED_SAP 0xAA
DECL|macro|UI_CMD
mdefine_line|#define UI_CMD       0x03
multiline_comment|/* This is an Token-Ring frame header. */
DECL|struct|trh_hdr
r_struct
id|trh_hdr
(brace
DECL|member|ac
id|__u8
id|ac
suffix:semicolon
multiline_comment|/* access control field */
DECL|member|fc
id|__u8
id|fc
suffix:semicolon
multiline_comment|/* frame control field */
DECL|member|daddr
id|__u8
id|daddr
(braket
id|TR_ALEN
)braket
suffix:semicolon
multiline_comment|/* destination address */
DECL|member|saddr
id|__u8
id|saddr
(braket
id|TR_ALEN
)braket
suffix:semicolon
multiline_comment|/* source address */
DECL|member|rcf
id|__u16
id|rcf
suffix:semicolon
multiline_comment|/* route control field */
DECL|member|rseg
id|__u16
id|rseg
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* routing registers */
)brace
suffix:semicolon
multiline_comment|/* This is an Token-Ring LLC structure */
DECL|struct|trllc
r_struct
id|trllc
(brace
DECL|member|dsap
id|__u8
id|dsap
suffix:semicolon
multiline_comment|/* destination SAP */
DECL|member|ssap
id|__u8
id|ssap
suffix:semicolon
multiline_comment|/* source SAP */
DECL|member|llc
id|__u8
id|llc
suffix:semicolon
multiline_comment|/* LLC control field */
DECL|member|protid
id|__u8
id|protid
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* protocol id */
DECL|member|ethertype
id|__u16
id|ethertype
suffix:semicolon
multiline_comment|/* ether type field */
)brace
suffix:semicolon
multiline_comment|/* Token-Ring statistics collection data. */
DECL|struct|tr_statistics
r_struct
id|tr_statistics
(brace
DECL|member|rx_packets
r_int
r_int
id|rx_packets
suffix:semicolon
multiline_comment|/* total packets received&t;*/
DECL|member|tx_packets
r_int
r_int
id|tx_packets
suffix:semicolon
multiline_comment|/* total packets transmitted&t;*/
DECL|member|rx_bytes
r_int
r_int
id|rx_bytes
suffix:semicolon
multiline_comment|/* total bytes received   &t;*/
DECL|member|tx_bytes
r_int
r_int
id|tx_bytes
suffix:semicolon
multiline_comment|/* total bytes transmitted&t;*/
DECL|member|rx_errors
r_int
r_int
id|rx_errors
suffix:semicolon
multiline_comment|/* bad packets received&t;&t;*/
DECL|member|tx_errors
r_int
r_int
id|tx_errors
suffix:semicolon
multiline_comment|/* packet transmit problems&t;*/
DECL|member|rx_dropped
r_int
r_int
id|rx_dropped
suffix:semicolon
multiline_comment|/* no space in linux buffers&t;*/
DECL|member|tx_dropped
r_int
r_int
id|tx_dropped
suffix:semicolon
multiline_comment|/* no space available in linux&t;*/
DECL|member|multicast
r_int
r_int
id|multicast
suffix:semicolon
multiline_comment|/* multicast packets received&t;*/
DECL|member|transmit_collision
r_int
r_int
id|transmit_collision
suffix:semicolon
multiline_comment|/* detailed Token-Ring errors. See IBM Token-Ring Network&n;&t;   Architecture for more info */
DECL|member|line_errors
r_int
r_int
id|line_errors
suffix:semicolon
DECL|member|internal_errors
r_int
r_int
id|internal_errors
suffix:semicolon
DECL|member|burst_errors
r_int
r_int
id|burst_errors
suffix:semicolon
DECL|member|A_C_errors
r_int
r_int
id|A_C_errors
suffix:semicolon
DECL|member|abort_delimiters
r_int
r_int
id|abort_delimiters
suffix:semicolon
DECL|member|lost_frames
r_int
r_int
id|lost_frames
suffix:semicolon
DECL|member|recv_congest_count
r_int
r_int
id|recv_congest_count
suffix:semicolon
DECL|member|frame_copied_errors
r_int
r_int
id|frame_copied_errors
suffix:semicolon
DECL|member|frequency_errors
r_int
r_int
id|frequency_errors
suffix:semicolon
DECL|member|token_errors
r_int
r_int
id|token_errors
suffix:semicolon
DECL|member|dummy1
r_int
r_int
id|dummy1
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* source routing stuff */
DECL|macro|TR_RII
mdefine_line|#define TR_RII 0x80
DECL|macro|TR_RCF_DIR_BIT
mdefine_line|#define TR_RCF_DIR_BIT 0x80
DECL|macro|TR_RCF_LEN_MASK
mdefine_line|#define TR_RCF_LEN_MASK 0x1f00
DECL|macro|TR_RCF_BROADCAST
mdefine_line|#define TR_RCF_BROADCAST 0x8000         /* all-routes broadcast */
DECL|macro|TR_RCF_LIMITED_BROADCAST
mdefine_line|#define TR_RCF_LIMITED_BROADCAST 0xC000 /* single-route broadcast */
DECL|macro|TR_RCF_FRAME2K
mdefine_line|#define TR_RCF_FRAME2K 0x20
DECL|macro|TR_RCF_BROADCAST_MASK
mdefine_line|#define TR_RCF_BROADCAST_MASK 0xC000
DECL|macro|TR_MAXRIFLEN
mdefine_line|#define TR_MAXRIFLEN 18
macro_line|#endif&t;/* _LINUX_IF_TR_H */
eof
