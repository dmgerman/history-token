multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000-2001 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_IFCONFIG_NET_H
DECL|macro|_ASM_IA64_SN_IFCONFIG_NET_H
mdefine_line|#define _ASM_IA64_SN_IFCONFIG_NET_H
DECL|macro|NETCONFIG_FILE
mdefine_line|#define NETCONFIG_FILE &quot;/tmp/ifconfig_net&quot;
DECL|macro|POUND_CHAR
mdefine_line|#define POUND_CHAR                   &squot;#&squot;
DECL|macro|MAX_LINE_LEN
mdefine_line|#define MAX_LINE_LEN 128
DECL|macro|MAXPATHLEN
mdefine_line|#define MAXPATHLEN 128
DECL|struct|ifname_num
r_struct
id|ifname_num
(brace
DECL|member|next_eth
r_int
id|next_eth
suffix:semicolon
DECL|member|next_fddi
r_int
id|next_fddi
suffix:semicolon
DECL|member|next_hip
r_int
id|next_hip
suffix:semicolon
DECL|member|next_tr
r_int
id|next_tr
suffix:semicolon
DECL|member|next_fc
r_int
id|next_fc
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ifname_MAC
r_struct
id|ifname_MAC
(brace
DECL|member|name
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|dev_addr
r_int
r_char
id|dev_addr
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|addr_len
r_int
r_char
id|addr_len
suffix:semicolon
multiline_comment|/* hardware address length      */
)brace
suffix:semicolon
macro_line|#endif /* _ASM_IA64_SN_IFCONFIG_NET_H */
eof
