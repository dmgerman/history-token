multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Global definitions for Fibre Channel.&n; *&n; * Version:&t;@(#)if_fc.h&t;0.0&t;11/20/98&n; *&n; * Author:&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&t;&t;Donald Becker, &lt;becker@super.org&gt;&n; *    Peter De Schrijver, &lt;stud11@cc4.kuleuven.ac.be&gt;&n; *&t;  Vineet Abraham, &lt;vma@iol.unh.edu&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_IF_FC_H
DECL|macro|_LINUX_IF_FC_H
mdefine_line|#define _LINUX_IF_FC_H
DECL|macro|FC_ALEN
mdefine_line|#define FC_ALEN&t;6&t;&t;/* Octets in one ethernet addr&t; */
DECL|macro|FC_HLEN
mdefine_line|#define FC_HLEN   (sizeof(struct fch_hdr)+sizeof(struct fcllc))
DECL|macro|FC_ID_LEN
mdefine_line|#define FC_ID_LEN 3&t;&t;/* Octets in a Fibre Channel Address */
multiline_comment|/* LLC and SNAP constants */
DECL|macro|EXTENDED_SAP
mdefine_line|#define EXTENDED_SAP 0xAA
DECL|macro|UI_CMD
mdefine_line|#define UI_CMD       0x03
multiline_comment|/* This is NOT the Fibre Channel frame header. The FC frame header is&n; *  constructed in the driver as the Tachyon needs certain fields in&n; *  certains positions. So, it can&squot;t be generalized here.*/
DECL|struct|fch_hdr
r_struct
id|fch_hdr
(brace
DECL|member|daddr
id|__u8
id|daddr
(braket
id|FC_ALEN
)braket
suffix:semicolon
multiline_comment|/* destination address */
DECL|member|saddr
id|__u8
id|saddr
(braket
id|FC_ALEN
)braket
suffix:semicolon
multiline_comment|/* source address */
)brace
suffix:semicolon
multiline_comment|/* This is a Fibre Channel LLC structure */
DECL|struct|fcllc
r_struct
id|fcllc
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
macro_line|#endif&t;/* _LINUX_IF_FC_H */
eof
