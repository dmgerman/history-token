multiline_comment|/*&n; * Netlink event notifications for SELinux.&n; *&n; * Author: James Morris &lt;jmorris@redhat.com&gt;&n; *&n; * Copyright (C) 2004 Red Hat, Inc., James Morris &lt;jmorris@redhat.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2,&n; * as published by the Free Software Foundation.&n; */
macro_line|#ifndef _LINUX_SELINUX_NETLINK_H
DECL|macro|_LINUX_SELINUX_NETLINK_H
mdefine_line|#define _LINUX_SELINUX_NETLINK_H
multiline_comment|/* Message types. */
DECL|macro|SELNL_MSG_BASE
mdefine_line|#define SELNL_MSG_BASE 0x10
r_enum
(brace
DECL|enumerator|SELNL_MSG_SETENFORCE
id|SELNL_MSG_SETENFORCE
op_assign
id|SELNL_MSG_BASE
comma
DECL|enumerator|SELNL_MSG_POLICYLOAD
id|SELNL_MSG_POLICYLOAD
comma
DECL|enumerator|SELNL_MSG_MAX
id|SELNL_MSG_MAX
)brace
suffix:semicolon
multiline_comment|/* Multicast groups */
DECL|macro|SELNL_GRP_NONE
mdefine_line|#define SELNL_GRP_NONE&t;&t;0x00000000
DECL|macro|SELNL_GRP_AVC
mdefine_line|#define SELNL_GRP_AVC&t;&t;0x00000001&t;/* AVC notifications */
DECL|macro|SELNL_GRP_ALL
mdefine_line|#define SELNL_GRP_ALL&t;&t;0xffffffff
multiline_comment|/* Message structures */
DECL|struct|selnl_msg_setenforce
r_struct
id|selnl_msg_setenforce
(brace
DECL|member|val
r_int32
id|val
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|selnl_msg_policyload
r_struct
id|selnl_msg_policyload
(brace
DECL|member|seqno
id|u_int32_t
id|seqno
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _LINUX_SELINUX_NETLINK_H */
eof
