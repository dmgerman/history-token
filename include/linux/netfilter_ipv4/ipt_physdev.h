macro_line|#ifndef _IPT_PHYSDEV_H
DECL|macro|_IPT_PHYSDEV_H
mdefine_line|#define _IPT_PHYSDEV_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/if.h&gt;
macro_line|#endif
DECL|macro|IPT_PHYSDEV_OP_MATCH_IN
mdefine_line|#define IPT_PHYSDEV_OP_MATCH_IN 0x01
DECL|macro|IPT_PHYSDEV_OP_MATCH_OUT
mdefine_line|#define IPT_PHYSDEV_OP_MATCH_OUT 0x02
DECL|struct|ipt_physdev_info
r_struct
id|ipt_physdev_info
(brace
DECL|member|invert
id|u_int8_t
id|invert
suffix:semicolon
DECL|member|physindev
r_char
id|physindev
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
DECL|member|in_mask
r_char
id|in_mask
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
DECL|member|physoutdev
r_char
id|physoutdev
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
DECL|member|out_mask
r_char
id|out_mask
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /*_IPT_PHYSDEV_H*/
eof
