macro_line|#ifndef _LINUX_NETBEUI_H
DECL|macro|_LINUX_NETBEUI_H
mdefine_line|#define _LINUX_NETBEUI_H
macro_line|#include &lt;linux/if.h&gt;
DECL|macro|NB_NAME_LEN
mdefine_line|#define NB_NAME_LEN&t;20&t;/* Set this properly from the full docs when&n;&t;&t;&t;&t;   I get them */
DECL|struct|sockaddr_netbeui
r_struct
id|sockaddr_netbeui
(brace
DECL|member|snb_family
id|sa_family
id|snb_family
suffix:semicolon
DECL|member|snb_name
r_char
id|snb_name
(braket
id|NB_NAME_LEN
)braket
suffix:semicolon
DECL|member|snb_devhint
r_char
id|snb_devhint
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
