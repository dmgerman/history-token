multiline_comment|/*&n; * Network interface table.&n; *&n; * Network interfaces (devices) do not have a security field, so we&n; * maintain a table associating each interface with a SID.&n; *&n; * Author: James Morris &lt;jmorris@redhat.com&gt;&n; *&n; * Copyright (C) 2003 Red Hat, Inc., James Morris &lt;jmorris@redhat.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2,&n; * as published by the Free Software Foundation.&n; */
macro_line|#ifndef _SELINUX_NETIF_H_
DECL|macro|_SELINUX_NETIF_H_
mdefine_line|#define _SELINUX_NETIF_H_
r_int
id|sel_netif_sids
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|u32
op_star
id|if_sid
comma
id|u32
op_star
id|msg_sid
)paren
suffix:semicolon
macro_line|#endif&t;/* _SELINUX_NETIF_H_ */
eof
