multiline_comment|/*&n; * include/asm-s390/qeth.h&n; *&n; * ioctl definitions for qeth driver&n; *&n; * Copyright (C) 2004 IBM Corporation&n; *&n; * Author(s):&t;Thomas Spatzier &lt;tspat@de.ibm.com&gt;&n; *&n; */
macro_line|#ifndef __ASM_S390_IOCTL_H__
DECL|macro|__ASM_S390_IOCTL_H__
mdefine_line|#define __ASM_S390_IOCTL_H__
macro_line|#include &lt;linux/ioctl.h&gt;
DECL|macro|QETH_IOCTL_LETTER
mdefine_line|#define QETH_IOCTL_LETTER &squot;Q&squot;
DECL|macro|SIOC_QETH_ARP_SET_NO_ENTRIES
mdefine_line|#define SIOC_QETH_ARP_SET_NO_ENTRIES&t;_IOWR(QETH_IOCTL_LETTER, 1, int)
DECL|macro|SIOC_QETH_ARP_QUERY_INFO
mdefine_line|#define SIOC_QETH_ARP_QUERY_INFO&t;_IOWR(QETH_IOCTL_LETTER, 2, int)
DECL|macro|SIOC_QETH_ARP_ADD_ENTRY
mdefine_line|#define SIOC_QETH_ARP_ADD_ENTRY&t;&t;_IOWR(QETH_IOCTL_LETTER, 3, int)
DECL|macro|SIOC_QETH_ARP_REMOVE_ENTRY
mdefine_line|#define SIOC_QETH_ARP_REMOVE_ENTRY&t;_IOWR(QETH_IOCTL_LETTER, 4, int)
DECL|macro|SIOC_QETH_ARP_FLUSH_CACHE
mdefine_line|#define SIOC_QETH_ARP_FLUSH_CACHE&t;_IOWR(QETH_IOCTL_LETTER, 5, int)
DECL|macro|SIOC_QETH_ADP_SET_SNMP_CONTROL
mdefine_line|#define SIOC_QETH_ADP_SET_SNMP_CONTROL&t;_IOWR(QETH_IOCTL_LETTER, 6, int)
DECL|macro|SIOC_QETH_GET_CARD_TYPE
mdefine_line|#define SIOC_QETH_GET_CARD_TYPE&t;&t;_IOWR(QETH_IOCTL_LETTER, 7, int)
DECL|struct|qeth_arp_cache_entry
r_struct
id|qeth_arp_cache_entry
(brace
DECL|member|macaddr
id|__u8
id|macaddr
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|reserved1
id|__u8
id|reserved1
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|ipaddr
id|__u8
id|ipaddr
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* for both  IPv4 and IPv6 */
DECL|member|reserved2
id|__u8
id|reserved2
(braket
l_int|32
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|qeth_arp_qi_entry7
r_struct
id|qeth_arp_qi_entry7
(brace
DECL|member|media_specific
id|__u8
id|media_specific
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|macaddr_type
id|__u8
id|macaddr_type
suffix:semicolon
DECL|member|ipaddr_type
id|__u8
id|ipaddr_type
suffix:semicolon
DECL|member|macaddr
id|__u8
id|macaddr
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|ipaddr
id|__u8
id|ipaddr
(braket
l_int|4
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|qeth_arp_qi_entry5
r_struct
id|qeth_arp_qi_entry5
(brace
DECL|member|media_specific
id|__u8
id|media_specific
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|macaddr_type
id|__u8
id|macaddr_type
suffix:semicolon
DECL|member|ipaddr_type
id|__u8
id|ipaddr_type
suffix:semicolon
DECL|member|ipaddr
id|__u8
id|ipaddr
(braket
l_int|4
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* data sent to user space as result of query arp ioctl */
DECL|macro|QETH_QARP_USER_DATA_SIZE
mdefine_line|#define QETH_QARP_USER_DATA_SIZE 20000
DECL|macro|QETH_QARP_MASK_OFFSET
mdefine_line|#define QETH_QARP_MASK_OFFSET    4
DECL|macro|QETH_QARP_ENTRIES_OFFSET
mdefine_line|#define QETH_QARP_ENTRIES_OFFSET 6
DECL|struct|qeth_arp_query_user_data
r_struct
id|qeth_arp_query_user_data
(brace
r_union
(brace
DECL|member|data_len
id|__u32
id|data_len
suffix:semicolon
multiline_comment|/* set by user space program */
DECL|member|no_entries
id|__u32
id|no_entries
suffix:semicolon
multiline_comment|/* set by kernel */
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|mask_bits
id|__u16
id|mask_bits
suffix:semicolon
DECL|member|entries
r_char
op_star
id|entries
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
macro_line|#endif /* __ASM_S390_IOCTL_H__ */
eof
