multiline_comment|/*&n; * Include file for the interface to a PnP BIOS&n; *&n; * Original BIOS code (C) 1998 Christian Schmidt (chr.schmidt@tu-bs.de)&n; * PnP handler parts (c) 1998 Tom Lees &lt;tom@lpsg.demon.co.uk&gt;&n; * Minor reorganizations by David Hinds &lt;dhinds@zen.stanford.edu&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _LINUX_PNPBIOS_H
DECL|macro|_LINUX_PNPBIOS_H
mdefine_line|#define _LINUX_PNPBIOS_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
multiline_comment|/*&n; * Status codes (warnings and errors)&n; */
DECL|macro|PNP_SUCCESS
mdefine_line|#define PNP_SUCCESS                     0x00
DECL|macro|PNP_NOT_SET_STATICALLY
mdefine_line|#define PNP_NOT_SET_STATICALLY          0x7f
DECL|macro|PNP_UNKNOWN_FUNCTION
mdefine_line|#define PNP_UNKNOWN_FUNCTION            0x81
DECL|macro|PNP_FUNCTION_NOT_SUPPORTED
mdefine_line|#define PNP_FUNCTION_NOT_SUPPORTED      0x82
DECL|macro|PNP_INVALID_HANDLE
mdefine_line|#define PNP_INVALID_HANDLE              0x83
DECL|macro|PNP_BAD_PARAMETER
mdefine_line|#define PNP_BAD_PARAMETER               0x84
DECL|macro|PNP_SET_FAILED
mdefine_line|#define PNP_SET_FAILED                  0x85
DECL|macro|PNP_EVENTS_NOT_PENDING
mdefine_line|#define PNP_EVENTS_NOT_PENDING          0x86
DECL|macro|PNP_SYSTEM_NOT_DOCKED
mdefine_line|#define PNP_SYSTEM_NOT_DOCKED           0x87
DECL|macro|PNP_NO_ISA_PNP_CARDS
mdefine_line|#define PNP_NO_ISA_PNP_CARDS            0x88
DECL|macro|PNP_UNABLE_TO_DETERMINE_DOCK_CAPABILITIES
mdefine_line|#define PNP_UNABLE_TO_DETERMINE_DOCK_CAPABILITIES 0x89
DECL|macro|PNP_CONFIG_CHANGE_FAILED_NO_BATTERY
mdefine_line|#define PNP_CONFIG_CHANGE_FAILED_NO_BATTERY 0x8a
DECL|macro|PNP_CONFIG_CHANGE_FAILED_RESOURCE_CONFLICT
mdefine_line|#define PNP_CONFIG_CHANGE_FAILED_RESOURCE_CONFLICT 0x8b
DECL|macro|PNP_BUFFER_TOO_SMALL
mdefine_line|#define PNP_BUFFER_TOO_SMALL            0x8c
DECL|macro|PNP_USE_ESCD_SUPPORT
mdefine_line|#define PNP_USE_ESCD_SUPPORT            0x8d
DECL|macro|PNP_MESSAGE_NOT_SUPPORTED
mdefine_line|#define PNP_MESSAGE_NOT_SUPPORTED       0x8e
DECL|macro|PNP_HARDWARE_ERROR
mdefine_line|#define PNP_HARDWARE_ERROR              0x8f
DECL|macro|ESCD_SUCCESS
mdefine_line|#define ESCD_SUCCESS                    0x00
DECL|macro|ESCD_IO_ERROR_READING
mdefine_line|#define ESCD_IO_ERROR_READING           0x55
DECL|macro|ESCD_INVALID
mdefine_line|#define ESCD_INVALID                    0x56
DECL|macro|ESCD_BUFFER_TOO_SMALL
mdefine_line|#define ESCD_BUFFER_TOO_SMALL           0x59
DECL|macro|ESCD_NVRAM_TOO_SMALL
mdefine_line|#define ESCD_NVRAM_TOO_SMALL            0x5a
DECL|macro|ESCD_FUNCTION_NOT_SUPPORTED
mdefine_line|#define ESCD_FUNCTION_NOT_SUPPORTED     0x81
multiline_comment|/*&n; * Events that can be received by &quot;get event&quot;&n; */
DECL|macro|PNPEV_ABOUT_TO_CHANGE_CONFIG
mdefine_line|#define PNPEV_ABOUT_TO_CHANGE_CONFIG&t;0x0001
DECL|macro|PNPEV_DOCK_CHANGED
mdefine_line|#define PNPEV_DOCK_CHANGED&t;&t;0x0002
DECL|macro|PNPEV_SYSTEM_DEVICE_CHANGED
mdefine_line|#define PNPEV_SYSTEM_DEVICE_CHANGED&t;0x0003
DECL|macro|PNPEV_CONFIG_CHANGED_FAILED
mdefine_line|#define PNPEV_CONFIG_CHANGED_FAILED&t;0x0004
DECL|macro|PNPEV_UNKNOWN_SYSTEM_EVENT
mdefine_line|#define PNPEV_UNKNOWN_SYSTEM_EVENT&t;0xffff
multiline_comment|/* 0x8000 through 0xfffe are OEM defined */
multiline_comment|/*&n; * Messages that should be sent through &quot;send message&quot;&n; */
DECL|macro|PNPMSG_OK
mdefine_line|#define PNPMSG_OK&t;&t;&t;0x00
DECL|macro|PNPMSG_ABORT
mdefine_line|#define PNPMSG_ABORT&t;&t;&t;0x01
DECL|macro|PNPMSG_UNDOCK_DEFAULT_ACTION
mdefine_line|#define PNPMSG_UNDOCK_DEFAULT_ACTION&t;0x40
DECL|macro|PNPMSG_POWER_OFF
mdefine_line|#define PNPMSG_POWER_OFF&t;&t;0x41
DECL|macro|PNPMSG_PNP_OS_ACTIVE
mdefine_line|#define PNPMSG_PNP_OS_ACTIVE&t;&t;0x42
DECL|macro|PNPMSG_PNP_OS_INACTIVE
mdefine_line|#define PNPMSG_PNP_OS_INACTIVE&t;&t;0x43
multiline_comment|/* 0x8000 through 0xffff are OEM defined */
macro_line|#pragma pack(1)
DECL|struct|pnp_dev_node_info
r_struct
id|pnp_dev_node_info
(brace
DECL|member|no_nodes
id|__u16
id|no_nodes
suffix:semicolon
DECL|member|max_node_size
id|__u16
id|max_node_size
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pnp_docking_station_info
r_struct
id|pnp_docking_station_info
(brace
DECL|member|location_id
id|__u32
id|location_id
suffix:semicolon
DECL|member|serial
id|__u32
id|serial
suffix:semicolon
DECL|member|capabilities
id|__u16
id|capabilities
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pnp_isa_config_struc
r_struct
id|pnp_isa_config_struc
(brace
DECL|member|revision
id|__u8
id|revision
suffix:semicolon
DECL|member|no_csns
id|__u8
id|no_csns
suffix:semicolon
DECL|member|isa_rd_data_port
id|__u16
id|isa_rd_data_port
suffix:semicolon
DECL|member|reserved
id|__u16
id|reserved
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|escd_info_struc
r_struct
id|escd_info_struc
(brace
DECL|member|min_escd_write_size
id|__u16
id|min_escd_write_size
suffix:semicolon
DECL|member|escd_size
id|__u16
id|escd_size
suffix:semicolon
DECL|member|nv_storage_base
id|__u32
id|nv_storage_base
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pnp_bios_node
r_struct
id|pnp_bios_node
(brace
DECL|member|size
id|__u16
id|size
suffix:semicolon
DECL|member|handle
id|__u8
id|handle
suffix:semicolon
DECL|member|eisa_id
id|__u32
id|eisa_id
suffix:semicolon
DECL|member|type_code
id|__u8
id|type_code
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|flags
id|__u16
id|flags
suffix:semicolon
DECL|member|data
id|__u8
id|data
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#pragma pack()
DECL|struct|pnpbios_device_id
r_struct
id|pnpbios_device_id
(brace
DECL|member|id
r_char
id|id
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|driver_data
r_int
r_int
id|driver_data
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pnpbios_driver
r_struct
id|pnpbios_driver
(brace
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|id_table
r_const
r_struct
id|pnpbios_device_id
op_star
id|id_table
suffix:semicolon
multiline_comment|/* NULL if wants all devices */
DECL|member|probe
r_int
(paren
op_star
id|probe
)paren
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_const
r_struct
id|pnpbios_device_id
op_star
id|id
)paren
suffix:semicolon
multiline_comment|/* New device inserted */
DECL|member|remove
r_void
(paren
op_star
id|remove
)paren
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* Device removed, either due to hotplug remove or module remove */
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_PNPBIOS
multiline_comment|/* exported */
r_extern
r_int
id|pnpbios_register_driver
c_func
(paren
r_struct
id|pnpbios_driver
op_star
id|drv
)paren
suffix:semicolon
r_extern
r_void
id|pnpbios_unregister_driver
c_func
(paren
r_struct
id|pnpbios_driver
op_star
id|drv
)paren
suffix:semicolon
multiline_comment|/* non-exported */
DECL|macro|pnpbios_for_each_dev
mdefine_line|#define pnpbios_for_each_dev(dev) &bslash;&n;&t;for(dev = pnpbios_dev_g(pnpbios_devices.next); dev != pnpbios_dev_g(&amp;pnpbios_devices); dev = pnpbios_dev_g(dev-&gt;global_list.next))
DECL|macro|pnpbios_dev_g
mdefine_line|#define pnpbios_dev_g(n) list_entry(n, struct pci_dev, global_list)
DECL|function|pnpbios_dev_driver
r_static
id|__inline
r_struct
id|pnpbios_driver
op_star
id|pnpbios_dev_driver
c_func
(paren
r_const
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_return
(paren
r_struct
id|pnpbios_driver
op_star
)paren
id|dev-&gt;driver
suffix:semicolon
)brace
r_extern
r_int
id|pnpbios_dont_use_current_config
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
r_void
id|pnpbios_init
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pnpbios_proc_init
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|pnp_bios_dev_node_info
(paren
r_struct
id|pnp_dev_node_info
op_star
id|data
)paren
suffix:semicolon
r_extern
r_int
id|pnp_bios_get_dev_node
(paren
id|u8
op_star
id|nodenum
comma
r_char
id|config
comma
r_struct
id|pnp_bios_node
op_star
id|data
)paren
suffix:semicolon
r_extern
r_int
id|pnp_bios_set_dev_node
(paren
id|u8
id|nodenum
comma
r_char
id|config
comma
r_struct
id|pnp_bios_node
op_star
id|data
)paren
suffix:semicolon
macro_line|#if needed
r_extern
r_int
id|pnp_bios_get_event
(paren
id|u16
op_star
id|message
)paren
suffix:semicolon
r_extern
r_int
id|pnp_bios_send_message
(paren
id|u16
id|message
)paren
suffix:semicolon
r_extern
r_int
id|pnp_bios_set_stat_res
(paren
r_char
op_star
id|info
)paren
suffix:semicolon
r_extern
r_int
id|pnp_bios_get_stat_res
(paren
r_char
op_star
id|info
)paren
suffix:semicolon
r_extern
r_int
id|pnp_bios_apm_id_table
(paren
r_char
op_star
id|table
comma
id|u16
op_star
id|size
)paren
suffix:semicolon
r_extern
r_int
id|pnp_bios_isapnp_config
(paren
r_struct
id|pnp_isa_config_struc
op_star
id|data
)paren
suffix:semicolon
r_extern
r_int
id|pnp_bios_escd_info
(paren
r_struct
id|escd_info_struc
op_star
id|data
)paren
suffix:semicolon
r_extern
r_int
id|pnp_bios_read_escd
(paren
r_char
op_star
id|data
comma
id|u32
id|nvram_base
)paren
suffix:semicolon
r_extern
r_int
id|pnp_bios_write_escd
(paren
r_char
op_star
id|data
comma
id|u32
id|nvram_base
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * a helper function which helps ensure correct pnpbios_driver&n; * setup and cleanup for commonly-encountered hotplug/modular cases&n; *&n; * This MUST stay in a header, as it checks for -DMODULE&n; */
DECL|function|pnpbios_module_init
r_static
r_inline
r_int
id|pnpbios_module_init
c_func
(paren
r_struct
id|pnpbios_driver
op_star
id|drv
)paren
(brace
r_int
id|rc
op_assign
id|pnpbios_register_driver
(paren
id|drv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OG
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* iff CONFIG_HOTPLUG and built into kernel, we should&n;&t; * leave the driver around for future hotplug events.&n;&t; * For the module case, a hotplug daemon of some sort&n;&t; * should load a module in response to an insert event. */
macro_line|#if defined(CONFIG_HOTPLUG) &amp;&amp; !defined(MODULE)
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
)paren
id|rc
op_assign
op_minus
id|ENODEV
suffix:semicolon
macro_line|#endif
multiline_comment|/* if we get here, we need to clean up pci driver instance&n;&t; * and return some sort of error */
id|pnpbios_unregister_driver
(paren
id|drv
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
macro_line|#else /* CONFIG_PNPBIOS */
DECL|function|pnpbios_register_driver
r_static
id|__inline__
r_int
id|pnpbios_register_driver
c_func
(paren
r_struct
id|pnpbios_driver
op_star
id|drv
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pnpbios_unregister_driver
r_static
id|__inline__
r_void
id|pnpbios_unregister_driver
c_func
(paren
r_struct
id|pnpbios_driver
op_star
id|drv
)paren
(brace
r_return
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PNPBIOS */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_PNPBIOS_H */
eof
