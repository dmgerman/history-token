multiline_comment|/*&n; * RPA Hot Plug Virtual I/O device functions &n; * Copyright (C) 2004 Linda Xie &lt;lxie@us.ibm.com&gt;&n; *&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or (at&n; * your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;lxie@us.ibm.com&gt;&n; *&n; */
macro_line|#include &lt;asm/vio.h&gt;
macro_line|#include &quot;rpaphp.h&quot;
multiline_comment|/*&n; * get_vio_adapter_status - get  the status of a slot&n; * &n; * status:&n; * &n; * 1-- adapter is configured&n; * 2-- adapter is not configured&n; * 3-- not valid&n; */
DECL|function|rpaphp_get_vio_adapter_status
r_inline
r_int
id|rpaphp_get_vio_adapter_status
c_func
(paren
r_struct
id|slot
op_star
id|slot
comma
r_int
id|is_init
comma
id|u8
op_star
id|value
)paren
(brace
op_star
id|value
op_assign
id|slot-&gt;state
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rpaphp_unconfig_vio_adapter
r_int
id|rpaphp_unconfig_vio_adapter
c_func
(paren
r_struct
id|slot
op_star
id|slot
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;Entry %s: slot[%s]&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|slot-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|slot-&gt;dev.vio_dev
)paren
(brace
id|info
c_func
(paren
l_string|&quot;%s: no VIOA in slot[%s]&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|slot-&gt;name
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
multiline_comment|/* remove the device from the vio core */
id|vio_unregister_device
c_func
(paren
id|slot-&gt;dev.vio_dev
)paren
suffix:semicolon
id|slot-&gt;state
op_assign
id|NOT_CONFIGURED
suffix:semicolon
id|info
c_func
(paren
l_string|&quot;%s: adapter in slot[%s] unconfigured.&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|slot-&gt;name
)paren
suffix:semicolon
m_exit
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;Exit %s, rc=0x%x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|retval
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|setup_vio_hotplug_slot_info
r_static
r_int
id|setup_vio_hotplug_slot_info
c_func
(paren
r_struct
id|slot
op_star
id|slot
)paren
(brace
id|slot-&gt;hotplug_slot-&gt;info-&gt;power_status
op_assign
l_int|1
suffix:semicolon
id|rpaphp_get_vio_adapter_status
c_func
(paren
id|slot
comma
l_int|1
comma
op_amp
id|slot-&gt;hotplug_slot-&gt;info-&gt;adapter_status
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|register_vio_slot
r_int
id|register_vio_slot
c_func
(paren
r_struct
id|device_node
op_star
id|dn
)paren
(brace
id|u32
op_star
id|index
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
r_int
id|rc
op_assign
l_int|1
suffix:semicolon
r_struct
id|slot
op_star
id|slot
op_assign
l_int|NULL
suffix:semicolon
id|index
op_assign
(paren
id|u32
op_star
)paren
id|get_property
c_func
(paren
id|dn
comma
l_string|&quot;ibm,my-drc-index&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|index
)paren
r_goto
id|exit_rc
suffix:semicolon
id|name
op_assign
id|get_property
c_func
(paren
id|dn
comma
l_string|&quot;ibm,loc-code&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
r_goto
id|exit_rc
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|slot
op_assign
id|alloc_slot_struct
c_func
(paren
id|dn
comma
op_star
id|index
comma
id|name
comma
l_int|0
)paren
)paren
)paren
(brace
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|exit_rc
suffix:semicolon
)brace
id|slot-&gt;dev_type
op_assign
id|VIO_DEV
suffix:semicolon
id|slot-&gt;dev.vio_dev
op_assign
id|vio_find_node
c_func
(paren
id|dn
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|slot-&gt;dev.vio_dev
)paren
id|slot-&gt;dev.vio_dev
op_assign
id|vio_register_device
c_func
(paren
id|dn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slot-&gt;dev.vio_dev
)paren
id|slot-&gt;state
op_assign
id|CONFIGURED
suffix:semicolon
r_else
id|slot-&gt;state
op_assign
id|NOT_CONFIGURED
suffix:semicolon
r_if
c_cond
(paren
id|setup_vio_hotplug_slot_info
c_func
(paren
id|slot
)paren
)paren
r_goto
id|exit_rc
suffix:semicolon
id|strcpy
c_func
(paren
id|slot-&gt;name
comma
id|slot-&gt;dev.vio_dev-&gt;dev.bus_id
)paren
suffix:semicolon
id|info
c_func
(paren
l_string|&quot;%s: registered VIO device[name=%s vio_dev=%p]&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|slot-&gt;name
comma
id|slot-&gt;dev.vio_dev
)paren
suffix:semicolon
id|rc
op_assign
id|register_slot
c_func
(paren
id|slot
)paren
suffix:semicolon
id|exit_rc
suffix:colon
r_if
c_cond
(paren
id|rc
op_logical_and
id|slot
)paren
id|dealloc_slot_struct
c_func
(paren
id|slot
)paren
suffix:semicolon
r_return
(paren
id|rc
)paren
suffix:semicolon
)brace
DECL|function|rpaphp_enable_vio_slot
r_int
id|rpaphp_enable_vio_slot
c_func
(paren
r_struct
id|slot
op_star
id|slot
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|slot-&gt;dev.vio_dev
op_assign
id|vio_register_device
c_func
(paren
id|slot-&gt;dn
)paren
)paren
)paren
(brace
id|info
c_func
(paren
l_string|&quot;%s: VIO adapter %s in slot[%s] has been configured&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|slot-&gt;dn-&gt;name
comma
id|slot-&gt;name
)paren
suffix:semicolon
id|slot-&gt;state
op_assign
id|CONFIGURED
suffix:semicolon
)brace
r_else
(brace
id|info
c_func
(paren
l_string|&quot;%s: no vio_dev struct for adapter in slot[%s]&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|slot-&gt;name
)paren
suffix:semicolon
id|slot-&gt;state
op_assign
id|NOT_CONFIGURED
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
eof
