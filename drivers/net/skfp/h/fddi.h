multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998,1999 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
macro_line|#ifndef&t;_FDDI_
DECL|macro|_FDDI_
mdefine_line|#define _FDDI_
DECL|struct|fddi_addr
r_struct
id|fddi_addr
(brace
DECL|member|a
id|u_char
id|a
(braket
l_int|6
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|GROUP_ADDR
mdefine_line|#define GROUP_ADDR&t;0x80&t;&t;/* MSB in a[0] */
DECL|struct|fddi_mac
r_struct
id|fddi_mac
(brace
DECL|member|mac_dest
r_struct
id|fddi_addr
id|mac_dest
suffix:semicolon
DECL|member|mac_source
r_struct
id|fddi_addr
id|mac_source
suffix:semicolon
DECL|member|mac_info
id|u_char
id|mac_info
(braket
l_int|4478
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|FDDI_MAC_SIZE
mdefine_line|#define FDDI_MAC_SIZE&t;(12)
DECL|macro|FDDI_RAW_MTU
mdefine_line|#define FDDI_RAW_MTU&t;(4500-5)&t;/* exl. Pr,SD, ED/FS */
DECL|macro|FDDI_RAW
mdefine_line|#define FDDI_RAW&t;(4500)
multiline_comment|/*&n; * FC values&n; */
DECL|macro|FC_VOID
mdefine_line|#define FC_VOID&t;&t;0x40&t;&t;/* void frame */
DECL|macro|FC_TOKEN
mdefine_line|#define FC_TOKEN&t;0x80&t;&t;/* token */
DECL|macro|FC_RES_TOKEN
mdefine_line|#define FC_RES_TOKEN&t;0xc0&t;&t;/* restricted token */
DECL|macro|FC_SMT_INFO
mdefine_line|#define FC_SMT_INFO&t;0x41&t;&t;/* SMT Info frame */
multiline_comment|/*&n; * FC_SMT_LAN_LOC &amp;&amp; FC_SMT_LOC are SK specific !&n; */
DECL|macro|FC_SMT_LAN_LOC
mdefine_line|#define FC_SMT_LAN_LOC&t;0x42&t;&t;/* local SMT Info frame */
DECL|macro|FC_SMT_LOC
mdefine_line|#define FC_SMT_LOC&t;0x43&t;&t;/* local SMT Info frame */
DECL|macro|FC_SMT_NSA
mdefine_line|#define FC_SMT_NSA&t;0x4f&t;&t;/* SMT NSA frame */
DECL|macro|FC_MAC
mdefine_line|#define FC_MAC&t;&t;0xc0&t;&t;/* MAC frame */
DECL|macro|FC_BEACON
mdefine_line|#define FC_BEACON&t;0xc2&t;&t;/* MAC beacon frame */
DECL|macro|FC_CLAIM
mdefine_line|#define FC_CLAIM&t;0xc3&t;&t;/* MAC claim frame */
DECL|macro|FC_SYNC_LLC
mdefine_line|#define FC_SYNC_LLC&t;0xd0&t;&t;/* sync. LLC frame */
DECL|macro|FC_ASYNC_LLC
mdefine_line|#define FC_ASYNC_LLC&t;0x50&t;&t;/* async. LLC frame */
DECL|macro|FC_SYNC_BIT
mdefine_line|#define FC_SYNC_BIT&t;0x80&t;&t;/* sync. bit in FC */
DECL|macro|FC_LLC_PRIOR
mdefine_line|#define FC_LLC_PRIOR&t;0x07&t;&t;/* priority bits */
DECL|macro|BEACON_INFO
mdefine_line|#define BEACON_INFO&t;0&t;&t;/* beacon type */
DECL|macro|DBEACON_INFO
mdefine_line|#define DBEACON_INFO&t;1&t;&t;/* beacon type DIRECTED */
multiline_comment|/*&n; * indicator bits&n; */
DECL|macro|C_INDICATOR
mdefine_line|#define C_INDICATOR&t;(1&lt;&lt;0)
DECL|macro|A_INDICATOR
mdefine_line|#define A_INDICATOR&t;(1&lt;&lt;1)
DECL|macro|E_INDICATOR
mdefine_line|#define E_INDICATOR&t;(1&lt;&lt;2)
DECL|macro|I_INDICATOR
mdefine_line|#define I_INDICATOR&t;(1&lt;&lt;6)&t;&t;/* SK specific */ 
DECL|macro|L_INDICATOR
mdefine_line|#define L_INDICATOR&t;(1&lt;&lt;7)&t;&t;/* SK specific */
macro_line|#endif&t;/* _FDDI_ */
eof
