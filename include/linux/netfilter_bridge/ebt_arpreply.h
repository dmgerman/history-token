macro_line|#ifndef __LINUX_BRIDGE_EBT_ARPREPLY_H
DECL|macro|__LINUX_BRIDGE_EBT_ARPREPLY_H
mdefine_line|#define __LINUX_BRIDGE_EBT_ARPREPLY_H
DECL|struct|ebt_arpreply_info
r_struct
id|ebt_arpreply_info
(brace
DECL|member|mac
r_int
r_char
id|mac
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|target
r_int
id|target
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|EBT_ARPREPLY_TARGET
mdefine_line|#define EBT_ARPREPLY_TARGET &quot;arpreply&quot;
macro_line|#endif
eof
