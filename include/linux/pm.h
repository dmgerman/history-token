multiline_comment|/*&n; *  pm.h - Power management interface&n; *&n; *  Copyright (C) 2000 Andrew Henroid&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _LINUX_PM_H
DECL|macro|_LINUX_PM_H
mdefine_line|#define _LINUX_PM_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/list.h&gt;
multiline_comment|/*&n; * Power management requests&n; */
r_enum
(brace
DECL|enumerator|PM_SUSPEND
id|PM_SUSPEND
comma
multiline_comment|/* enter D1-D3 */
DECL|enumerator|PM_RESUME
id|PM_RESUME
comma
multiline_comment|/* enter D0 */
DECL|enumerator|PM_SAVE_STATE
id|PM_SAVE_STATE
comma
multiline_comment|/* save device&squot;s state */
multiline_comment|/* enable wake-on */
DECL|enumerator|PM_SET_WAKEUP
id|PM_SET_WAKEUP
comma
multiline_comment|/* bus resource management */
DECL|enumerator|PM_GET_RESOURCES
id|PM_GET_RESOURCES
comma
DECL|enumerator|PM_SET_RESOURCES
id|PM_SET_RESOURCES
comma
multiline_comment|/* base station management */
DECL|enumerator|PM_EJECT
id|PM_EJECT
comma
DECL|enumerator|PM_LOCK
id|PM_LOCK
comma
)brace
suffix:semicolon
DECL|typedef|pm_request_t
r_typedef
r_int
id|pm_request_t
suffix:semicolon
multiline_comment|/*&n; * Device types&n; */
r_enum
(brace
DECL|enumerator|PM_UNKNOWN_DEV
id|PM_UNKNOWN_DEV
op_assign
l_int|0
comma
multiline_comment|/* generic */
DECL|enumerator|PM_SYS_DEV
id|PM_SYS_DEV
comma
multiline_comment|/* system device (fan, KB controller, ...) */
DECL|enumerator|PM_PCI_DEV
id|PM_PCI_DEV
comma
multiline_comment|/* PCI device */
DECL|enumerator|PM_USB_DEV
id|PM_USB_DEV
comma
multiline_comment|/* USB device */
DECL|enumerator|PM_SCSI_DEV
id|PM_SCSI_DEV
comma
multiline_comment|/* SCSI device */
DECL|enumerator|PM_ISA_DEV
id|PM_ISA_DEV
comma
multiline_comment|/* ISA device */
DECL|enumerator|PM_MTD_DEV
id|PM_MTD_DEV
comma
multiline_comment|/* Memory Technology Device */
)brace
suffix:semicolon
DECL|typedef|pm_dev_t
r_typedef
r_int
id|pm_dev_t
suffix:semicolon
multiline_comment|/*&n; * System device hardware ID (PnP) values&n; */
r_enum
(brace
DECL|enumerator|PM_SYS_UNKNOWN
id|PM_SYS_UNKNOWN
op_assign
l_int|0x00000000
comma
multiline_comment|/* generic */
DECL|enumerator|PM_SYS_KBC
id|PM_SYS_KBC
op_assign
l_int|0x41d00303
comma
multiline_comment|/* keyboard controller */
DECL|enumerator|PM_SYS_COM
id|PM_SYS_COM
op_assign
l_int|0x41d00500
comma
multiline_comment|/* serial port */
DECL|enumerator|PM_SYS_IRDA
id|PM_SYS_IRDA
op_assign
l_int|0x41d00510
comma
multiline_comment|/* IRDA controller */
DECL|enumerator|PM_SYS_FDC
id|PM_SYS_FDC
op_assign
l_int|0x41d00700
comma
multiline_comment|/* floppy controller */
DECL|enumerator|PM_SYS_VGA
id|PM_SYS_VGA
op_assign
l_int|0x41d00900
comma
multiline_comment|/* VGA controller */
DECL|enumerator|PM_SYS_PCMCIA
id|PM_SYS_PCMCIA
op_assign
l_int|0x41d00e00
comma
multiline_comment|/* PCMCIA controller */
)brace
suffix:semicolon
multiline_comment|/*&n; * Device identifier&n; */
DECL|macro|PM_PCI_ID
mdefine_line|#define PM_PCI_ID(dev) ((dev)-&gt;bus-&gt;number &lt;&lt; 16 | (dev)-&gt;devfn)
multiline_comment|/*&n; * Request handler callback&n; */
r_struct
id|pm_dev
suffix:semicolon
DECL|typedef|pm_callback
r_typedef
r_int
(paren
op_star
id|pm_callback
)paren
(paren
r_struct
id|pm_dev
op_star
id|dev
comma
id|pm_request_t
id|rqst
comma
r_void
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/*&n; * Dynamic device information&n; */
DECL|struct|pm_dev
r_struct
id|pm_dev
(brace
DECL|member|type
id|pm_dev_t
id|type
suffix:semicolon
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
DECL|member|callback
id|pm_callback
id|callback
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|prev_state
r_int
id|prev_state
suffix:semicolon
DECL|member|entry
r_struct
id|list_head
id|entry
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_PM
r_extern
r_int
id|pm_active
suffix:semicolon
DECL|macro|PM_IS_ACTIVE
mdefine_line|#define PM_IS_ACTIVE() (pm_active != 0)
multiline_comment|/*&n; * Register a device with power management&n; */
r_struct
id|pm_dev
op_star
id|pm_register
c_func
(paren
id|pm_dev_t
id|type
comma
r_int
r_int
id|id
comma
id|pm_callback
id|callback
)paren
suffix:semicolon
multiline_comment|/*&n; * Unregister a device with power management&n; */
r_void
id|pm_unregister
c_func
(paren
r_struct
id|pm_dev
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/*&n; * Unregister all devices with matching callback&n; */
r_void
id|pm_unregister_all
c_func
(paren
id|pm_callback
id|callback
)paren
suffix:semicolon
multiline_comment|/*&n; * Send a request to a single device&n; */
r_int
id|pm_send
c_func
(paren
r_struct
id|pm_dev
op_star
id|dev
comma
id|pm_request_t
id|rqst
comma
r_void
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/*&n; * Send a request to all devices&n; */
r_int
id|pm_send_all
c_func
(paren
id|pm_request_t
id|rqst
comma
r_void
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/*&n; * Find a device&n; */
r_struct
id|pm_dev
op_star
id|pm_find
c_func
(paren
id|pm_dev_t
id|type
comma
r_struct
id|pm_dev
op_star
id|from
)paren
suffix:semicolon
DECL|function|pm_access
r_extern
r_inline
r_void
id|pm_access
c_func
(paren
r_struct
id|pm_dev
op_star
id|dev
)paren
(brace
)brace
DECL|function|pm_dev_idle
r_extern
r_inline
r_void
id|pm_dev_idle
c_func
(paren
r_struct
id|pm_dev
op_star
id|dev
)paren
(brace
)brace
macro_line|#else /* CONFIG_PM */
DECL|macro|PM_IS_ACTIVE
mdefine_line|#define PM_IS_ACTIVE() 0
DECL|function|pm_register
r_extern
r_inline
r_struct
id|pm_dev
op_star
id|pm_register
c_func
(paren
id|pm_dev_t
id|type
comma
r_int
r_int
id|id
comma
id|pm_callback
id|callback
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pm_unregister
r_extern
r_inline
r_void
id|pm_unregister
c_func
(paren
r_struct
id|pm_dev
op_star
id|dev
)paren
(brace
)brace
DECL|function|pm_unregister_all
r_extern
r_inline
r_void
id|pm_unregister_all
c_func
(paren
id|pm_callback
id|callback
)paren
(brace
)brace
DECL|function|pm_send
r_extern
r_inline
r_int
id|pm_send
c_func
(paren
r_struct
id|pm_dev
op_star
id|dev
comma
id|pm_request_t
id|rqst
comma
r_void
op_star
id|data
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pm_send_all
r_extern
r_inline
r_int
id|pm_send_all
c_func
(paren
id|pm_request_t
id|rqst
comma
r_void
op_star
id|data
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pm_find
r_extern
r_inline
r_struct
id|pm_dev
op_star
id|pm_find
c_func
(paren
id|pm_dev_t
id|type
comma
r_struct
id|pm_dev
op_star
id|from
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pm_access
r_extern
r_inline
r_void
id|pm_access
c_func
(paren
r_struct
id|pm_dev
op_star
id|dev
)paren
(brace
)brace
DECL|function|pm_dev_idle
r_extern
r_inline
r_void
id|pm_dev_idle
c_func
(paren
r_struct
id|pm_dev
op_star
id|dev
)paren
(brace
)brace
macro_line|#endif /* CONFIG_PM */
r_extern
r_void
(paren
op_star
id|pm_idle
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|pm_power_off
)paren
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_PM_H */
eof
