multiline_comment|/*&n; *  ebt_ip&n; *&n; *&t;Authors:&n; *&t;Bart De Schuymer &lt;bart.de.schuymer@pandora.be&gt;&n; *&n; *  April, 2002&n; *&n; *  Changes:&n; *    added ip-sport and ip-dport&n; *    Innominate Security Technologies AG &lt;mhopf@innominate.com&gt;&n; *    September, 2002&n; */
macro_line|#ifndef __LINUX_BRIDGE_EBT_IP_H
DECL|macro|__LINUX_BRIDGE_EBT_IP_H
mdefine_line|#define __LINUX_BRIDGE_EBT_IP_H
DECL|macro|EBT_IP_SOURCE
mdefine_line|#define EBT_IP_SOURCE 0x01
DECL|macro|EBT_IP_DEST
mdefine_line|#define EBT_IP_DEST 0x02
DECL|macro|EBT_IP_TOS
mdefine_line|#define EBT_IP_TOS 0x04
DECL|macro|EBT_IP_PROTO
mdefine_line|#define EBT_IP_PROTO 0x08
DECL|macro|EBT_IP_SPORT
mdefine_line|#define EBT_IP_SPORT 0x10
DECL|macro|EBT_IP_DPORT
mdefine_line|#define EBT_IP_DPORT 0x20
DECL|macro|EBT_IP_MASK
mdefine_line|#define EBT_IP_MASK (EBT_IP_SOURCE | EBT_IP_DEST | EBT_IP_TOS | EBT_IP_PROTO |&bslash;&n; EBT_IP_SPORT | EBT_IP_DPORT )
DECL|macro|EBT_IP_MATCH
mdefine_line|#define EBT_IP_MATCH &quot;ip&quot;
multiline_comment|/* the same values are used for the invflags */
DECL|struct|ebt_ip_info
r_struct
id|ebt_ip_info
(brace
DECL|member|saddr
r_uint32
id|saddr
suffix:semicolon
DECL|member|daddr
r_uint32
id|daddr
suffix:semicolon
DECL|member|smsk
r_uint32
id|smsk
suffix:semicolon
DECL|member|dmsk
r_uint32
id|dmsk
suffix:semicolon
DECL|member|tos
r_uint8
id|tos
suffix:semicolon
DECL|member|protocol
r_uint8
id|protocol
suffix:semicolon
DECL|member|bitmask
r_uint8
id|bitmask
suffix:semicolon
DECL|member|invflags
r_uint8
id|invflags
suffix:semicolon
DECL|member|sport
r_uint16
id|sport
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|dport
r_uint16
id|dport
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
