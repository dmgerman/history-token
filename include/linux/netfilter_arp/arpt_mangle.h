macro_line|#ifndef _ARPT_MANGLE_H
DECL|macro|_ARPT_MANGLE_H
mdefine_line|#define _ARPT_MANGLE_H
macro_line|#include &lt;linux/netfilter_arp/arp_tables.h&gt;
DECL|macro|ARPT_MANGLE_ADDR_LEN_MAX
mdefine_line|#define ARPT_MANGLE_ADDR_LEN_MAX sizeof(struct in_addr)
DECL|struct|arpt_mangle
r_struct
id|arpt_mangle
(brace
DECL|member|src_devaddr
r_char
id|src_devaddr
(braket
id|ARPT_DEV_ADDR_LEN_MAX
)braket
suffix:semicolon
DECL|member|tgt_devaddr
r_char
id|tgt_devaddr
(braket
id|ARPT_DEV_ADDR_LEN_MAX
)braket
suffix:semicolon
r_union
(brace
DECL|member|src_ip
r_struct
id|in_addr
id|src_ip
suffix:semicolon
DECL|member|u_s
)brace
id|u_s
suffix:semicolon
r_union
(brace
DECL|member|tgt_ip
r_struct
id|in_addr
id|tgt_ip
suffix:semicolon
DECL|member|u_t
)brace
id|u_t
suffix:semicolon
DECL|member|flags
id|u_int8_t
id|flags
suffix:semicolon
DECL|member|target
r_int
id|target
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ARPT_MANGLE_SDEV
mdefine_line|#define ARPT_MANGLE_SDEV 0x01
DECL|macro|ARPT_MANGLE_TDEV
mdefine_line|#define ARPT_MANGLE_TDEV 0x02
DECL|macro|ARPT_MANGLE_SIP
mdefine_line|#define ARPT_MANGLE_SIP 0x04
DECL|macro|ARPT_MANGLE_TIP
mdefine_line|#define ARPT_MANGLE_TIP 0x08
DECL|macro|ARPT_MANGLE_MASK
mdefine_line|#define ARPT_MANGLE_MASK 0x0f
macro_line|#endif /* _ARPT_MANGLE_H */
eof
