multiline_comment|/*&n; * pnpbios -- PnP BIOS driver&n; *&n; * This driver provides access to Plug-&squot;n&squot;-Play services provided by&n; * the PnP BIOS firmware, described in the following documents:&n; *   Plug and Play BIOS Specification, Version 1.0A, 5 May 1994&n; *   Plug and Play BIOS Clarification Paper, 6 October 1994&n; *     Compaq Computer Corporation, Phoenix Technologies Ltd., Intel Corp.&n; * &n; * Originally (C) 1998 Christian Schmidt &lt;schmidt@digadd.de&gt;&n; * Modifications (C) 1998 Tom Lees &lt;tom@lpsg.demon.co.uk&gt;&n; * Minor reorganizations by David Hinds &lt;dahinds@users.sourceforge.net&gt;&n; * Further modifications (C) 2001, 2002 by:&n; *   Alan Cox &lt;alan@redhat.com&gt;&n; *   Thomas Hood &lt;jdthood@mail.com&gt;&n; *   Brian Gerst &lt;bgerst@didntduck.org&gt;&n; *&n; * Ported to the PnP Layer and several additional improvements (C) 2002&n; * by Adam Belay &lt;ambx1@neo.rr.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
multiline_comment|/* Change Log&n; *&n; * Adam Belay - &lt;ambx1@neo.rr.com&gt; - March 16, 2003&n; * rev 1.01&t;Only call pnp_bios_dev_node_info once&n; *&t;&t;Added pnpbios_print_status&n; *&t;&t;Added several new error messages and info messages&n; *&t;&t;Added pnpbios_interface_attach_device&n; *&t;&t;integrated core and proc init system&n; *&t;&t;Introduced PNPMODE flags&n; *&t;&t;Removed some useless includes&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pnpbios.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/pnp.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/desc.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &quot;pnpbios.h&quot;
multiline_comment|/*&n; *&n; * PnP BIOS INTERFACE&n; *&n; */
DECL|variable|pnp_bios_install
r_static
r_union
id|pnp_bios_install_struct
op_star
id|pnp_bios_install
op_assign
l_int|NULL
suffix:semicolon
DECL|function|pnp_bios_present
r_int
id|pnp_bios_present
c_func
(paren
r_void
)paren
(brace
r_return
(paren
id|pnp_bios_install
op_ne
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|node_info
r_struct
id|pnp_dev_node_info
id|node_info
suffix:semicolon
DECL|function|pnpbios_kmalloc
r_void
op_star
id|pnpbios_kmalloc
c_func
(paren
r_int
id|size
comma
r_int
id|f
)paren
(brace
r_void
op_star
id|p
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|f
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PnPBIOS: kmalloc() failed&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|memset
c_func
(paren
id|p
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
multiline_comment|/*&n; *&n; * DOCKING FUNCTIONS&n; *&n; */
macro_line|#ifdef CONFIG_HOTPLUG
DECL|variable|unloading
r_static
r_int
id|unloading
op_assign
l_int|0
suffix:semicolon
DECL|variable|unload_sem
r_static
r_struct
id|completion
id|unload_sem
suffix:semicolon
multiline_comment|/*&n; * (Much of this belongs in a shared routine somewhere)&n; */
DECL|function|pnp_dock_event
r_static
r_int
id|pnp_dock_event
c_func
(paren
r_int
id|dock
comma
r_struct
id|pnp_docking_station_info
op_star
id|info
)paren
(brace
r_char
op_star
id|argv
(braket
l_int|3
)braket
comma
op_star
op_star
id|envp
comma
op_star
id|buf
comma
op_star
id|scratch
suffix:semicolon
r_int
id|i
op_assign
l_int|0
comma
id|value
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hotplug_path
(braket
l_int|0
)braket
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;fs-&gt;root
)paren
(brace
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|envp
op_assign
(paren
r_char
op_star
op_star
)paren
id|pnpbios_kmalloc
(paren
l_int|20
op_star
r_sizeof
(paren
r_char
op_star
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|buf
op_assign
id|pnpbios_kmalloc
(paren
l_int|256
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|kfree
(paren
id|envp
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/* only one standardized param to hotplug command: type */
id|argv
(braket
l_int|0
)braket
op_assign
id|hotplug_path
suffix:semicolon
id|argv
(braket
l_int|1
)braket
op_assign
l_string|&quot;dock&quot;
suffix:semicolon
id|argv
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* minimal command environment */
id|envp
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;HOME=/&quot;
suffix:semicolon
id|envp
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;PATH=/sbin:/bin:/usr/sbin:/usr/bin&quot;
suffix:semicolon
macro_line|#ifdef&t;DEBUG
multiline_comment|/* hint that policy agent should enter no-stdout debug mode */
id|envp
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;DEBUG=kernel&quot;
suffix:semicolon
macro_line|#endif
multiline_comment|/* extensible set of named bus-specific parameters,&n;&t; * supporting multiple driver selection algorithms.&n;&t; */
id|scratch
op_assign
id|buf
suffix:semicolon
multiline_comment|/* action:  add, remove */
id|envp
(braket
id|i
op_increment
)braket
op_assign
id|scratch
suffix:semicolon
id|scratch
op_add_assign
id|sprintf
(paren
id|scratch
comma
l_string|&quot;ACTION=%s&quot;
comma
id|dock
ques
c_cond
l_string|&quot;add&quot;
suffix:colon
l_string|&quot;remove&quot;
)paren
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* Report the ident for the dock */
id|envp
(braket
id|i
op_increment
)braket
op_assign
id|scratch
suffix:semicolon
id|scratch
op_add_assign
id|sprintf
(paren
id|scratch
comma
l_string|&quot;DOCK=%x/%x/%x&quot;
comma
id|info-&gt;location_id
comma
id|info-&gt;serial
comma
id|info-&gt;capabilities
)paren
suffix:semicolon
id|envp
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|value
op_assign
id|call_usermodehelper
(paren
id|argv
(braket
l_int|0
)braket
comma
id|argv
comma
id|envp
comma
l_int|0
)paren
suffix:semicolon
id|kfree
(paren
id|buf
)paren
suffix:semicolon
id|kfree
(paren
id|envp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Poll the PnP docking at regular intervals&n; */
DECL|function|pnp_dock_thread
r_static
r_int
id|pnp_dock_thread
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
r_static
r_struct
id|pnp_docking_station_info
id|now
suffix:semicolon
r_int
id|docked
op_assign
op_minus
l_int|1
comma
id|d
op_assign
l_int|0
suffix:semicolon
id|daemonize
c_func
(paren
l_string|&quot;kpnpbiosd&quot;
)paren
suffix:semicolon
id|allow_signal
c_func
(paren
id|SIGKILL
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|unloading
op_logical_and
op_logical_neg
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
r_int
id|status
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Poll every 2 seconds&n;&t;&t; */
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|HZ
op_star
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
r_break
suffix:semicolon
)brace
id|status
op_assign
id|pnp_bios_dock_station_info
c_func
(paren
op_amp
id|now
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|status
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * No dock to manage&n;&t;&t;&t; */
r_case
id|PNP_FUNCTION_NOT_SUPPORTED
suffix:colon
id|complete_and_exit
c_func
(paren
op_amp
id|unload_sem
comma
l_int|0
)paren
suffix:semicolon
r_case
id|PNP_SYSTEM_NOT_DOCKED
suffix:colon
id|d
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PNP_SUCCESS
suffix:colon
id|d
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|pnpbios_print_status
c_func
(paren
l_string|&quot;pnp_dock_thread&quot;
comma
id|status
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|d
op_ne
id|docked
)paren
(brace
r_if
c_cond
(paren
id|pnp_dock_event
c_func
(paren
id|d
comma
op_amp
id|now
)paren
op_eq
l_int|0
)paren
(brace
id|docked
op_assign
id|d
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PnPBIOS: Docking station %stached&bslash;n&quot;
comma
id|docked
ques
c_cond
l_string|&quot;at&quot;
suffix:colon
l_string|&quot;de&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
)brace
id|complete_and_exit
c_func
(paren
op_amp
id|unload_sem
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#endif   /* CONFIG_HOTPLUG */
DECL|function|pnpbios_get_resources
r_static
r_int
id|pnpbios_get_resources
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_struct
id|pnp_resource_table
op_star
id|res
)paren
(brace
id|u8
id|nodenum
op_assign
id|dev-&gt;number
suffix:semicolon
r_struct
id|pnp_bios_node
op_star
id|node
suffix:semicolon
multiline_comment|/* just in case */
r_if
c_cond
(paren
op_logical_neg
id|pnpbios_is_dynamic
c_func
(paren
id|dev
)paren
)paren
(brace
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
id|node
op_assign
id|pnpbios_kmalloc
c_func
(paren
id|node_info.max_node_size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|pnp_bios_get_dev_node
c_func
(paren
op_amp
id|nodenum
comma
(paren
r_char
)paren
id|PNPMODE_DYNAMIC
comma
id|node
)paren
)paren
(brace
id|kfree
c_func
(paren
id|node
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|pnpbios_read_resources_from_node
c_func
(paren
id|res
comma
id|node
)paren
suffix:semicolon
id|dev-&gt;active
op_assign
id|pnp_is_active
c_func
(paren
id|dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|node
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pnpbios_set_resources
r_static
r_int
id|pnpbios_set_resources
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_struct
id|pnp_resource_table
op_star
id|res
)paren
(brace
id|u8
id|nodenum
op_assign
id|dev-&gt;number
suffix:semicolon
r_struct
id|pnp_bios_node
op_star
id|node
suffix:semicolon
r_int
id|ret
suffix:semicolon
multiline_comment|/* just in case */
r_if
c_cond
(paren
op_logical_neg
id|pnpbios_is_dynamic
c_func
(paren
id|dev
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|node
op_assign
id|pnpbios_kmalloc
c_func
(paren
id|node_info.max_node_size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|pnp_bios_get_dev_node
c_func
(paren
op_amp
id|nodenum
comma
(paren
r_char
)paren
id|PNPMODE_STATIC
comma
id|node
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|pnpbios_write_resources_to_node
c_func
(paren
id|res
comma
id|node
)paren
OL
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|node
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|ret
op_assign
id|pnp_bios_set_dev_node
c_func
(paren
id|node-&gt;handle
comma
(paren
r_char
)paren
id|PNPMODE_DYNAMIC
comma
id|node
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OG
l_int|0
)paren
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|pnpbios_zero_data_stream
r_static
r_void
id|pnpbios_zero_data_stream
c_func
(paren
r_struct
id|pnp_bios_node
op_star
id|node
)paren
(brace
r_int
r_char
op_star
id|p
op_assign
(paren
r_char
op_star
)paren
id|node-&gt;data
suffix:semicolon
r_int
r_char
op_star
id|end
op_assign
(paren
r_char
op_star
)paren
(paren
id|node-&gt;data
op_plus
id|node-&gt;size
)paren
suffix:semicolon
r_int
r_int
id|len
suffix:semicolon
r_int
id|i
suffix:semicolon
r_while
c_loop
(paren
(paren
r_char
op_star
)paren
id|p
OL
(paren
r_char
op_star
)paren
id|end
)paren
(brace
r_if
c_cond
(paren
id|p
(braket
l_int|0
)braket
op_amp
l_int|0x80
)paren
(brace
multiline_comment|/* large tag */
id|len
op_assign
(paren
id|p
(braket
l_int|2
)braket
op_lshift
l_int|8
)paren
op_or
id|p
(braket
l_int|1
)braket
suffix:semicolon
id|p
op_add_assign
l_int|3
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
(paren
id|p
(braket
l_int|0
)braket
op_rshift
l_int|3
)paren
op_amp
l_int|0x0f
)paren
op_eq
l_int|0x0f
)paren
r_return
suffix:semicolon
id|len
op_assign
id|p
(braket
l_int|0
)braket
op_amp
l_int|0x07
suffix:semicolon
id|p
op_add_assign
l_int|1
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|len
suffix:semicolon
id|i
op_increment
)paren
id|p
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|p
op_add_assign
id|len
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PnPBIOS: Resource structure did not contain an end tag.&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|pnpbios_disable_resources
r_static
r_int
id|pnpbios_disable_resources
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
r_struct
id|pnp_bios_node
op_star
id|node
suffix:semicolon
id|u8
id|nodenum
op_assign
id|dev-&gt;number
suffix:semicolon
r_int
id|ret
suffix:semicolon
multiline_comment|/* just in case */
r_if
c_cond
(paren
id|dev-&gt;flags
op_amp
id|PNPBIOS_NO_DISABLE
op_logical_or
op_logical_neg
id|pnpbios_is_dynamic
c_func
(paren
id|dev
)paren
)paren
(brace
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
id|node
op_assign
id|pnpbios_kmalloc
c_func
(paren
id|node_info.max_node_size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|pnp_bios_get_dev_node
c_func
(paren
op_amp
id|nodenum
comma
(paren
r_char
)paren
id|PNPMODE_DYNAMIC
comma
id|node
)paren
)paren
(brace
id|kfree
c_func
(paren
id|node
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|pnpbios_zero_data_stream
c_func
(paren
id|node
)paren
suffix:semicolon
id|ret
op_assign
id|pnp_bios_set_dev_node
c_func
(paren
id|dev-&gt;number
comma
(paren
r_char
)paren
id|PNPMODE_DYNAMIC
comma
id|node
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OG
l_int|0
)paren
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* PnP Layer support */
DECL|variable|pnpbios_protocol
r_struct
id|pnp_protocol
id|pnpbios_protocol
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Plug and Play BIOS&quot;
comma
dot
id|get
op_assign
id|pnpbios_get_resources
comma
dot
id|set
op_assign
id|pnpbios_set_resources
comma
dot
id|disable
op_assign
id|pnpbios_disable_resources
comma
)brace
suffix:semicolon
DECL|function|insert_device
r_static
r_int
id|insert_device
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_struct
id|pnp_bios_node
op_star
id|node
)paren
(brace
r_struct
id|list_head
op_star
id|pos
suffix:semicolon
r_struct
id|pnp_dev
op_star
id|pnp_dev
suffix:semicolon
r_struct
id|pnp_id
op_star
id|dev_id
suffix:semicolon
r_char
id|id
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* check if the device is already added */
id|dev-&gt;number
op_assign
id|node-&gt;handle
suffix:semicolon
id|list_for_each
(paren
id|pos
comma
op_amp
id|pnpbios_protocol.devices
)paren
(brace
id|pnp_dev
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|pnp_dev
comma
id|protocol_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;number
op_eq
id|pnp_dev-&gt;number
)paren
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* set the initial values for the PnP device */
id|dev_id
op_assign
id|pnpbios_kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|pnp_id
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev_id
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|pnpid32_to_pnpid
c_func
(paren
id|node-&gt;eisa_id
comma
id|id
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dev_id-&gt;id
comma
id|id
comma
l_int|7
)paren
suffix:semicolon
id|pnp_add_id
c_func
(paren
id|dev_id
comma
id|dev
)paren
suffix:semicolon
id|pnpbios_parse_data_stream
c_func
(paren
id|dev
comma
id|node
)paren
suffix:semicolon
id|dev-&gt;active
op_assign
id|pnp_is_active
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;flags
op_assign
id|node-&gt;flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dev-&gt;flags
op_amp
id|PNPBIOS_NO_CONFIG
)paren
)paren
id|dev-&gt;capabilities
op_or_assign
id|PNP_CONFIGURABLE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dev-&gt;flags
op_amp
id|PNPBIOS_NO_DISABLE
)paren
)paren
id|dev-&gt;capabilities
op_or_assign
id|PNP_DISABLE
suffix:semicolon
id|dev-&gt;capabilities
op_or_assign
id|PNP_READ
suffix:semicolon
r_if
c_cond
(paren
id|pnpbios_is_dynamic
c_func
(paren
id|dev
)paren
)paren
id|dev-&gt;capabilities
op_or_assign
id|PNP_WRITE
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;flags
op_amp
id|PNPBIOS_REMOVABLE
)paren
id|dev-&gt;capabilities
op_or_assign
id|PNP_REMOVABLE
suffix:semicolon
id|dev-&gt;protocol
op_assign
op_amp
id|pnpbios_protocol
suffix:semicolon
multiline_comment|/* clear out the damaged flags */
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;active
)paren
id|pnp_init_resource_table
c_func
(paren
op_amp
id|dev-&gt;res
)paren
suffix:semicolon
id|pnp_add_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|pnpbios_interface_attach_device
c_func
(paren
id|node
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|build_devlist
r_static
r_void
id|__init
id|build_devlist
c_func
(paren
r_void
)paren
(brace
id|u8
id|nodenum
suffix:semicolon
r_int
r_int
id|nodes_got
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|devs
op_assign
l_int|0
suffix:semicolon
r_struct
id|pnp_bios_node
op_star
id|node
suffix:semicolon
r_struct
id|pnp_dev
op_star
id|dev
suffix:semicolon
id|node
op_assign
id|pnpbios_kmalloc
c_func
(paren
id|node_info.max_node_size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|nodenum
op_assign
l_int|0
suffix:semicolon
id|nodenum
OL
l_int|0xff
suffix:semicolon
)paren
(brace
id|u8
id|thisnodenum
op_assign
id|nodenum
suffix:semicolon
multiline_comment|/* eventually we will want to use PNPMODE_STATIC here but for now&n;&t;&t; * dynamic will help us catch buggy bioses to add to the blacklist.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|pnpbios_dont_use_current_config
)paren
(brace
r_if
c_cond
(paren
id|pnp_bios_get_dev_node
c_func
(paren
op_amp
id|nodenum
comma
(paren
r_char
)paren
id|PNPMODE_DYNAMIC
comma
id|node
)paren
)paren
r_break
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|pnp_bios_get_dev_node
c_func
(paren
op_amp
id|nodenum
comma
(paren
r_char
)paren
id|PNPMODE_STATIC
comma
id|node
)paren
)paren
r_break
suffix:semicolon
)brace
id|nodes_got
op_increment
suffix:semicolon
id|dev
op_assign
id|pnpbios_kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|pnp_dev
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|insert_device
c_func
(paren
id|dev
comma
id|node
)paren
OL
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_else
id|devs
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|nodenum
op_le
id|thisnodenum
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PnPBIOS: build_devlist: Node number 0x%x is out of sequence following node 0x%x. Aborting.&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|nodenum
comma
(paren
r_int
r_int
)paren
id|thisnodenum
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|kfree
c_func
(paren
id|node
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PnPBIOS: %i node%s reported by PnP BIOS; %i recorded by driver&bslash;n&quot;
comma
id|nodes_got
comma
id|nodes_got
op_ne
l_int|1
ques
c_cond
l_string|&quot;s&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|devs
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&n; * INIT AND EXIT&n; *&n; */
DECL|variable|pnpbios_disabled
r_static
r_int
id|pnpbios_disabled
suffix:semicolon
multiline_comment|/* = 0 */
DECL|variable|pnpbios_dont_use_current_config
r_int
id|pnpbios_dont_use_current_config
suffix:semicolon
multiline_comment|/* = 0 */
macro_line|#ifndef MODULE
DECL|function|pnpbios_setup
r_static
r_int
id|__init
id|pnpbios_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
id|invert
suffix:semicolon
r_while
c_loop
(paren
(paren
id|str
op_ne
l_int|NULL
)paren
op_logical_and
(paren
op_star
id|str
op_ne
l_char|&squot;&bslash;0&squot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;off&quot;
comma
l_int|3
)paren
op_eq
l_int|0
)paren
id|pnpbios_disabled
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;on&quot;
comma
l_int|2
)paren
op_eq
l_int|0
)paren
id|pnpbios_disabled
op_assign
l_int|0
suffix:semicolon
id|invert
op_assign
(paren
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;no-&quot;
comma
l_int|3
)paren
op_eq
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|invert
)paren
id|str
op_add_assign
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;curr&quot;
comma
l_int|4
)paren
op_eq
l_int|0
)paren
id|pnpbios_dont_use_current_config
op_assign
id|invert
suffix:semicolon
id|str
op_assign
id|strchr
c_func
(paren
id|str
comma
l_char|&squot;,&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|str
op_ne
l_int|NULL
)paren
id|str
op_add_assign
id|strspn
c_func
(paren
id|str
comma
l_string|&quot;, &bslash;t&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;pnpbios=&quot;
comma
id|pnpbios_setup
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* PnP BIOS signature: &quot;$PnP&quot; */
DECL|macro|PNP_SIGNATURE
mdefine_line|#define PNP_SIGNATURE   ((&squot;$&squot; &lt;&lt; 0) + (&squot;P&squot; &lt;&lt; 8) + (&squot;n&squot; &lt;&lt; 16) + (&squot;P&squot; &lt;&lt; 24))
DECL|function|pnpbios_probe_system
r_int
id|__init
id|pnpbios_probe_system
c_func
(paren
r_void
)paren
(brace
r_union
id|pnp_bios_install_struct
op_star
id|check
suffix:semicolon
id|u8
id|sum
suffix:semicolon
r_int
id|length
comma
id|i
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PnPBIOS: Scanning system for PnP BIOS support...&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; &t; * Search the defined area (0xf0000-0xffff0) for a valid PnP BIOS&n;&t; * structure and, if one is found, sets up the selectors and&n;&t; * entry points&n;&t; */
r_for
c_loop
(paren
id|check
op_assign
(paren
r_union
id|pnp_bios_install_struct
op_star
)paren
id|__va
c_func
(paren
l_int|0xf0000
)paren
suffix:semicolon
id|check
OL
(paren
r_union
id|pnp_bios_install_struct
op_star
)paren
id|__va
c_func
(paren
l_int|0xffff0
)paren
suffix:semicolon
(paren
(paren
r_void
op_star
)paren
(paren
id|check
)paren
)paren
op_add_assign
l_int|16
)paren
(brace
r_if
c_cond
(paren
id|check-&gt;fields.signature
op_ne
id|PNP_SIGNATURE
)paren
r_continue
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PnPBIOS: Found PnP BIOS installation structure at 0x%p&bslash;n&quot;
comma
id|check
)paren
suffix:semicolon
id|length
op_assign
id|check-&gt;fields.length
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|length
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PnPBIOS: installation structure is invalid, skipping&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_for
c_loop
(paren
id|sum
op_assign
l_int|0
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|length
suffix:semicolon
id|i
op_increment
)paren
id|sum
op_add_assign
id|check-&gt;chars
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|sum
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PnPBIOS: installation structure is corrupted, skipping&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|check-&gt;fields.version
OL
l_int|0x10
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;PnPBIOS: PnP BIOS version %d.%d is not supported&bslash;n&quot;
comma
id|check-&gt;fields.version
op_rshift
l_int|4
comma
id|check-&gt;fields.version
op_amp
l_int|15
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PnPBIOS: PnP BIOS version %d.%d, entry 0x%x:0x%x, dseg 0x%x&bslash;n&quot;
comma
id|check-&gt;fields.version
op_rshift
l_int|4
comma
id|check-&gt;fields.version
op_amp
l_int|15
comma
id|check-&gt;fields.pm16cseg
comma
id|check-&gt;fields.pm16offset
comma
id|check-&gt;fields.pm16dseg
)paren
suffix:semicolon
id|pnp_bios_install
op_assign
id|check
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PnPBIOS: PnP BIOS support was not detected.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pnpbios_init
r_int
id|__init
id|pnpbios_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|pnpbios_disabled
op_logical_or
(paren
id|dmi_broken
op_amp
id|BROKEN_PNP_BIOS
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PnPBIOS: Disabled&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* scan the system for pnpbios support */
r_if
c_cond
(paren
op_logical_neg
id|pnpbios_probe_system
c_func
(paren
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* make preparations for bios calls */
id|pnpbios_calls_init
c_func
(paren
id|pnp_bios_install
)paren
suffix:semicolon
multiline_comment|/* read the node info */
id|ret
op_assign
id|pnp_bios_dev_node_info
c_func
(paren
op_amp
id|node_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PnPBIOS: Unable to get node info.  Aborting.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* register with the pnp layer */
id|ret
op_assign
id|pnp_register_protocol
c_func
(paren
op_amp
id|pnpbios_protocol
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PnPBIOS: Unable to register driver.  Aborting.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* start the proc interface */
id|ret
op_assign
id|pnpbios_proc_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PnPBIOS: Failed to create proc interface.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* scan for pnpbios devices */
id|build_devlist
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pnpbios_init
id|subsys_initcall
c_func
(paren
id|pnpbios_init
)paren
suffix:semicolon
DECL|function|pnpbios_thread_init
r_static
r_int
id|__init
id|pnpbios_thread_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_HOTPLUG
id|init_completion
c_func
(paren
op_amp
id|unload_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kernel_thread
c_func
(paren
id|pnp_dock_thread
comma
l_int|NULL
comma
id|CLONE_KERNEL
)paren
OG
l_int|0
)paren
id|unloading
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifndef MODULE
multiline_comment|/* init/main.c calls pnpbios_init early */
multiline_comment|/* Start the kernel thread later: */
DECL|variable|pnpbios_thread_init
id|module_init
c_func
(paren
id|pnpbios_thread_init
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/*&n; * N.B.: Building pnpbios as a module hasn&squot;t been fully implemented&n; */
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|function|pnpbios_init_all
r_static
r_int
id|__init
id|pnpbios_init_all
c_func
(paren
r_void
)paren
(brace
r_int
id|r
suffix:semicolon
id|r
op_assign
id|pnpbios_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
r_return
id|r
suffix:semicolon
id|r
op_assign
id|pnpbios_thread_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
r_return
id|r
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pnpbios_exit
r_static
r_void
id|__exit
id|pnpbios_exit
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_HOTPLUG
id|unloading
op_assign
l_int|1
suffix:semicolon
id|wait_for_completion
c_func
(paren
op_amp
id|unload_sem
)paren
suffix:semicolon
macro_line|#endif
id|pnpbios_proc_exit
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* We ought to free resources here */
r_return
suffix:semicolon
)brace
DECL|variable|pnpbios_init_all
id|module_init
c_func
(paren
id|pnpbios_init_all
)paren
suffix:semicolon
DECL|variable|pnpbios_exit
id|module_exit
c_func
(paren
id|pnpbios_exit
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|pnpbios_protocol
id|EXPORT_SYMBOL
c_func
(paren
id|pnpbios_protocol
)paren
suffix:semicolon
eof
