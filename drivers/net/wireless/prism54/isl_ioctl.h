multiline_comment|/*&n; *  &n; *  Copyright (C) 2002 Intersil Americas Inc.&n; *            (C) 2003 Aurelien Alleaume &lt;slts@free.fr&gt;&n; *            (C) 2003 Luis R. Rodriguez &lt;mcgrof@ruslug.rutgers.edu&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; */
macro_line|#ifndef _ISL_IOCTL_H
DECL|macro|_ISL_IOCTL_H
mdefine_line|#define _ISL_IOCTL_H
macro_line|#include &quot;islpci_mgt.h&quot;
macro_line|#include &quot;islpci_dev.h&quot;
macro_line|#include &lt;net/iw_handler.h&gt;&t;/* New driver API */
DECL|macro|SUPPORTED_WIRELESS_EXT
mdefine_line|#define SUPPORTED_WIRELESS_EXT                  16
r_void
id|prism54_mib_init
c_func
(paren
id|islpci_private
op_star
)paren
suffix:semicolon
r_void
id|prism54_mib_init_work
c_func
(paren
id|islpci_private
op_star
)paren
suffix:semicolon
r_struct
id|iw_statistics
op_star
id|prism54_get_wireless_stats
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_void
id|prism54_update_stats
c_func
(paren
id|islpci_private
op_star
)paren
suffix:semicolon
r_void
id|prism54_acl_init
c_func
(paren
r_struct
id|islpci_acl
op_star
)paren
suffix:semicolon
r_void
id|prism54_acl_clean
c_func
(paren
r_struct
id|islpci_acl
op_star
)paren
suffix:semicolon
r_void
id|prism54_process_trap
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_void
id|prism54_wpa_ie_init
c_func
(paren
id|islpci_private
op_star
id|priv
)paren
suffix:semicolon
r_void
id|prism54_wpa_ie_clean
c_func
(paren
id|islpci_private
op_star
id|priv
)paren
suffix:semicolon
r_void
id|prism54_wpa_ie_add
c_func
(paren
id|islpci_private
op_star
id|priv
comma
id|u8
op_star
id|bssid
comma
id|u8
op_star
id|wpa_ie
comma
r_int
id|wpa_ie_len
)paren
suffix:semicolon
r_int
id|prism54_wpa_ie_get
c_func
(paren
id|islpci_private
op_star
id|priv
comma
id|u8
op_star
id|bssid
comma
id|u8
op_star
id|wpa_ie
)paren
suffix:semicolon
r_int
id|prism54_set_mac_address
c_func
(paren
r_struct
id|net_device
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_int
id|prism54_ioctl
c_func
(paren
r_struct
id|net_device
op_star
comma
r_struct
id|ifreq
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_const
r_struct
id|iw_handler_def
id|prism54_handler_def
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _ISL_IOCTL_H */
eof
