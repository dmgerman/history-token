multiline_comment|/*&n; * INET         An implementation of the TCP/IP protocol suite for the LINUX&n; *              operating system.  INET is implemented using the  BSD Socket&n; *              interface as the means of communication with the user level.&n; *&n; *              Global definitions for the ARCnet interface.&n; *&n; * Authors:     David Woodhouse and Avery Pennarun&n; *&n; *              This program is free software; you can redistribute it and/or&n; *              modify it under the terms of the GNU General Public License&n; *              as published by the Free Software Foundation; either version&n; *              2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_IF_ARCNET_H
DECL|macro|_LINUX_IF_ARCNET_H
mdefine_line|#define _LINUX_IF_ARCNET_H
macro_line|#include &lt;linux/if_ether.h&gt;
multiline_comment|/*&n; *    These are the defined ARCnet Protocol ID&squot;s.&n; */
multiline_comment|/* RFC1201 Protocol ID&squot;s */
DECL|macro|ARC_P_IP
mdefine_line|#define ARC_P_IP&t;&t;212&t;/* 0xD4 */
DECL|macro|ARC_P_ARP
mdefine_line|#define ARC_P_ARP&t;&t;213&t;/* 0xD5 */
DECL|macro|ARC_P_RARP
mdefine_line|#define ARC_P_RARP&t;&t;214&t;/* 0xD6 */
DECL|macro|ARC_P_IPX
mdefine_line|#define ARC_P_IPX&t;&t;250&t;/* 0xFA */
DECL|macro|ARC_P_NOVELL_EC
mdefine_line|#define ARC_P_NOVELL_EC&t;&t;236&t;/* 0xEC */
multiline_comment|/* Old RFC1051 Protocol ID&squot;s */
DECL|macro|ARC_P_IP_RFC1051
mdefine_line|#define ARC_P_IP_RFC1051&t;240&t;/* 0xF0 */
DECL|macro|ARC_P_ARP_RFC1051
mdefine_line|#define ARC_P_ARP_RFC1051&t;241&t;/* 0xF1 */
multiline_comment|/* MS LanMan/WfWg &quot;NDIS&quot; encapsulation */
DECL|macro|ARC_P_ETHER
mdefine_line|#define ARC_P_ETHER&t;&t;232&t;/* 0xE8 */
multiline_comment|/* Unsupported/indirectly supported protocols */
DECL|macro|ARC_P_DATAPOINT_BOOT
mdefine_line|#define ARC_P_DATAPOINT_BOOT&t;0&t;/* very old Datapoint equipment */
DECL|macro|ARC_P_DATAPOINT_MOUNT
mdefine_line|#define ARC_P_DATAPOINT_MOUNT&t;1
DECL|macro|ARC_P_POWERLAN_BEACON
mdefine_line|#define ARC_P_POWERLAN_BEACON&t;8&t;/* Probably ATA-Netbios related */
DECL|macro|ARC_P_POWERLAN_BEACON2
mdefine_line|#define ARC_P_POWERLAN_BEACON2&t;243&t;/* 0xF3 */
DECL|macro|ARC_P_LANSOFT
mdefine_line|#define ARC_P_LANSOFT&t;&t;251&t;/* 0xFB - what is this? */
DECL|macro|ARC_P_ATALK
mdefine_line|#define ARC_P_ATALK&t;&t;0xDD
multiline_comment|/*&n; * The RFC1201-specific components of an arcnet packet header.&n; */
DECL|struct|arc_rfc1201
r_struct
id|arc_rfc1201
(brace
DECL|member|proto
r_uint8
id|proto
suffix:semicolon
multiline_comment|/* protocol ID field - varies&t;&t;*/
DECL|member|split_flag
r_uint8
id|split_flag
suffix:semicolon
multiline_comment|/* for use with split packets&t;&t;*/
DECL|member|sequence
r_uint16
id|sequence
suffix:semicolon
multiline_comment|/* sequence number&t;&t;&t;*/
DECL|member|payload
r_uint8
id|payload
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* space remaining in packet (504 bytes)*/
)brace
suffix:semicolon
DECL|macro|RFC1201_HDR_SIZE
mdefine_line|#define RFC1201_HDR_SIZE 4
multiline_comment|/*&n; * The RFC1051-specific components.&n; */
DECL|struct|arc_rfc1051
r_struct
id|arc_rfc1051
(brace
DECL|member|proto
r_uint8
id|proto
suffix:semicolon
multiline_comment|/* ARC_P_RFC1051_ARP/RFC1051_IP&t;*/
DECL|member|payload
r_uint8
id|payload
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* 507 bytes&t;&t;&t;*/
)brace
suffix:semicolon
DECL|macro|RFC1051_HDR_SIZE
mdefine_line|#define RFC1051_HDR_SIZE 1
multiline_comment|/*&n; * The ethernet-encap-specific components.  We have a real ethernet header&n; * and some data.&n; */
DECL|struct|arc_eth_encap
r_struct
id|arc_eth_encap
(brace
DECL|member|proto
r_uint8
id|proto
suffix:semicolon
multiline_comment|/* Always ARC_P_ETHER&t;&t;&t;*/
DECL|member|eth
r_struct
id|ethhdr
id|eth
suffix:semicolon
multiline_comment|/* standard ethernet header (yuck!)&t;*/
DECL|member|payload
r_uint8
id|payload
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* 493 bytes&t;&t;&t;&t;*/
)brace
suffix:semicolon
DECL|macro|ETH_ENCAP_HDR_SIZE
mdefine_line|#define ETH_ENCAP_HDR_SIZE 14
multiline_comment|/*&n; * The data needed by the actual arcnet hardware.&n; *&n; * Now, in the real arcnet hardware, the third and fourth bytes are the&n; * &squot;offset&squot; specification instead of the length, and the soft data is at&n; * the _end_ of the 512-byte buffer.  We hide this complexity inside the&n; * driver.&n; */
DECL|struct|arc_hardware
r_struct
id|arc_hardware
(brace
DECL|member|source
r_uint8
id|source
comma
multiline_comment|/* source ARCnet - filled in automagically */
DECL|member|dest
id|dest
comma
multiline_comment|/* destination ARCnet - 0 for broadcast    */
DECL|member|offset
id|offset
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* offset bytes (some weird semantics)     */
)brace
suffix:semicolon
DECL|macro|ARC_HDR_SIZE
mdefine_line|#define ARC_HDR_SIZE 4
multiline_comment|/*&n; * This is an ARCnet frame header, as seen by the kernel (and userspace,&n; * when you do a raw packet capture).&n; */
DECL|struct|archdr
r_struct
id|archdr
(brace
multiline_comment|/* hardware requirements */
DECL|member|hard
r_struct
id|arc_hardware
id|hard
suffix:semicolon
multiline_comment|/* arcnet encapsulation-specific bits */
r_union
(brace
DECL|member|rfc1201
r_struct
id|arc_rfc1201
id|rfc1201
suffix:semicolon
DECL|member|rfc1051
r_struct
id|arc_rfc1051
id|rfc1051
suffix:semicolon
DECL|member|eth_encap
r_struct
id|arc_eth_encap
id|eth_encap
suffix:semicolon
DECL|member|raw
r_uint8
id|raw
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* 508 bytes&t;&t;&t;&t;*/
DECL|member|soft
)brace
id|soft
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _LINUX_IF_ARCNET_H */
eof
