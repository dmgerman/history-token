macro_line|#ifndef __LINUX_BRIDGE_EBT_NAT_H
DECL|macro|__LINUX_BRIDGE_EBT_NAT_H
mdefine_line|#define __LINUX_BRIDGE_EBT_NAT_H
DECL|struct|ebt_nat_info
r_struct
id|ebt_nat_info
(brace
DECL|member|mac
r_int
r_char
id|mac
(braket
id|ETH_ALEN
)braket
suffix:semicolon
multiline_comment|/* EBT_ACCEPT, EBT_DROP, EBT_CONTINUE or EBT_RETURN */
DECL|member|target
r_int
id|target
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|EBT_SNAT_TARGET
mdefine_line|#define EBT_SNAT_TARGET &quot;snat&quot;
DECL|macro|EBT_DNAT_TARGET
mdefine_line|#define EBT_DNAT_TARGET &quot;dnat&quot;
macro_line|#endif
eof
