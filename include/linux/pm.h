multiline_comment|/*&n; *  pm.h - Power management interface&n; *&n; *  Copyright (C) 2000 Andrew Henroid&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _LINUX_PM_H
DECL|macro|_LINUX_PM_H
mdefine_line|#define _LINUX_PM_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
multiline_comment|/*&n; * Power management requests... these are passed to pm_send_all() and friends.&n; *&n; * these functions are old and deprecated, see below.&n; */
DECL|typedef|pm_request_t
r_typedef
r_int
id|__bitwise
id|pm_request_t
suffix:semicolon
DECL|macro|PM_SUSPEND
mdefine_line|#define PM_SUSPEND&t;((__force pm_request_t) 1)&t;/* enter D1-D3 */
DECL|macro|PM_RESUME
mdefine_line|#define PM_RESUME&t;((__force pm_request_t) 2)&t;/* enter D0 */
multiline_comment|/*&n; * Device types... these are passed to pm_register&n; */
DECL|typedef|pm_dev_t
r_typedef
r_int
id|__bitwise
id|pm_dev_t
suffix:semicolon
DECL|macro|PM_UNKNOWN_DEV
mdefine_line|#define PM_UNKNOWN_DEV&t;((__force pm_dev_t) 0)&t;/* generic */
DECL|macro|PM_SYS_DEV
mdefine_line|#define PM_SYS_DEV&t;((__force pm_dev_t) 1)&t;/* system device (fan, KB controller, ...) */
DECL|macro|PM_PCI_DEV
mdefine_line|#define PM_PCI_DEV&t;((__force pm_dev_t) 2)&t;/* PCI device */
DECL|macro|PM_USB_DEV
mdefine_line|#define PM_USB_DEV&t;((__force pm_dev_t) 3)&t;/* USB device */
DECL|macro|PM_SCSI_DEV
mdefine_line|#define PM_SCSI_DEV&t;((__force pm_dev_t) 4)&t;/* SCSI device */
DECL|macro|PM_ISA_DEV
mdefine_line|#define PM_ISA_DEV&t;((__force pm_dev_t) 5)&t;/* ISA device */
DECL|macro|PM_MTD_DEV
mdefine_line|#define&t;PM_MTD_DEV&t;((__force pm_dev_t) 6)&t;/* Memory Technology Device */
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
r_int
id|state
suffix:semicolon
DECL|member|prev_state
r_int
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
id|__deprecated
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
id|__deprecated
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
id|__deprecated
id|pm_unregister_all
c_func
(paren
id|pm_callback
id|callback
)paren
suffix:semicolon
multiline_comment|/*&n; * Send a request to a single device&n; */
r_int
id|__deprecated
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
id|__deprecated
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
macro_line|#else /* CONFIG_PM */
DECL|macro|PM_IS_ACTIVE
mdefine_line|#define PM_IS_ACTIVE() 0
DECL|function|pm_register
r_static
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
l_int|NULL
suffix:semicolon
)brace
DECL|function|pm_unregister
r_static
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
r_static
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
r_static
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
r_static
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
macro_line|#endif /* CONFIG_PM */
multiline_comment|/* Functions above this comment are list-based old-style power&n; * managment. Please avoid using them.  */
multiline_comment|/*&n; * Callbacks for platform drivers to implement.&n; */
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
DECL|typedef|suspend_state_t
r_typedef
r_int
id|__bitwise
id|suspend_state_t
suffix:semicolon
DECL|macro|PM_SUSPEND_ON
mdefine_line|#define PM_SUSPEND_ON&t;&t;((__force suspend_state_t) 0)
DECL|macro|PM_SUSPEND_STANDBY
mdefine_line|#define PM_SUSPEND_STANDBY&t;((__force suspend_state_t) 1)
DECL|macro|PM_SUSPEND_MEM
mdefine_line|#define PM_SUSPEND_MEM&t;&t;((__force suspend_state_t) 3)
DECL|macro|PM_SUSPEND_DISK
mdefine_line|#define PM_SUSPEND_DISK&t;&t;((__force suspend_state_t) 4)
DECL|macro|PM_SUSPEND_MAX
mdefine_line|#define PM_SUSPEND_MAX&t;&t;((__force suspend_state_t) 5)
DECL|typedef|suspend_disk_method_t
r_typedef
r_int
id|__bitwise
id|suspend_disk_method_t
suffix:semicolon
DECL|macro|PM_DISK_FIRMWARE
mdefine_line|#define&t;PM_DISK_FIRMWARE&t;((__force suspend_disk_method_t) 1)
DECL|macro|PM_DISK_PLATFORM
mdefine_line|#define&t;PM_DISK_PLATFORM&t;((__force suspend_disk_method_t) 2)
DECL|macro|PM_DISK_SHUTDOWN
mdefine_line|#define&t;PM_DISK_SHUTDOWN&t;((__force suspend_disk_method_t) 3)
DECL|macro|PM_DISK_REBOOT
mdefine_line|#define&t;PM_DISK_REBOOT&t;&t;((__force suspend_disk_method_t) 4)
DECL|macro|PM_DISK_MAX
mdefine_line|#define&t;PM_DISK_MAX&t;&t;((__force suspend_disk_method_t) 5)
DECL|struct|pm_ops
r_struct
id|pm_ops
(brace
DECL|member|pm_disk_mode
id|suspend_disk_method_t
id|pm_disk_mode
suffix:semicolon
DECL|member|prepare
r_int
(paren
op_star
id|prepare
)paren
(paren
id|suspend_state_t
id|state
)paren
suffix:semicolon
DECL|member|enter
r_int
(paren
op_star
id|enter
)paren
(paren
id|suspend_state_t
id|state
)paren
suffix:semicolon
DECL|member|finish
r_int
(paren
op_star
id|finish
)paren
(paren
id|suspend_state_t
id|state
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|pm_set_ops
c_func
(paren
r_struct
id|pm_ops
op_star
)paren
suffix:semicolon
r_extern
r_int
id|pm_suspend
c_func
(paren
id|suspend_state_t
id|state
)paren
suffix:semicolon
multiline_comment|/*&n; * Device power management&n; */
r_struct
id|device
suffix:semicolon
DECL|typedef|pm_message_t
r_typedef
id|u32
id|__bitwise
id|pm_message_t
suffix:semicolon
multiline_comment|/*&n; * There are 4 important states driver can be in:&n; * ON     -- driver is working&n; * FREEZE -- stop operations and apply whatever policy is applicable to a suspended driver&n; *           of that class, freeze queues for block like IDE does, drop packets for&n; *           ethernet, etc... stop DMA engine too etc... so a consistent image can be&n; *           saved; but do not power any hardware down.&n; * SUSPEND - like FREEZE, but hardware is doing as much powersaving as possible. Roughly&n; *           pci D3.&n; *&n; * Unfortunately, current drivers only recognize numeric values 0 (ON) and 3 (SUSPEND).&n; * We&squot;ll need to fix the drivers. So yes, putting 3 to all diferent defines is intentional,&n; * and will go away as soon as drivers are fixed. Also note that typedef is neccessary,&n; * we&squot;ll probably want to switch to&n; *   typedef struct pm_message_t { int event; int flags; } pm_message_t&n; * or something similar soon.&n; */
DECL|macro|PMSG_FREEZE
mdefine_line|#define PMSG_FREEZE&t;((__force pm_message_t) 3)
DECL|macro|PMSG_SUSPEND
mdefine_line|#define PMSG_SUSPEND&t;((__force pm_message_t) 3)
DECL|macro|PMSG_ON
mdefine_line|#define PMSG_ON&t;&t;((__force pm_message_t) 0)
DECL|struct|dev_pm_info
r_struct
id|dev_pm_info
(brace
DECL|member|power_state
id|pm_message_t
id|power_state
suffix:semicolon
macro_line|#ifdef&t;CONFIG_PM
DECL|member|prev_state
id|pm_message_t
id|prev_state
suffix:semicolon
DECL|member|saved_state
r_void
op_star
id|saved_state
suffix:semicolon
DECL|member|pm_users
id|atomic_t
id|pm_users
suffix:semicolon
DECL|member|pm_parent
r_struct
id|device
op_star
id|pm_parent
suffix:semicolon
DECL|member|entry
r_struct
id|list_head
id|entry
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
r_extern
r_void
id|device_pm_set_parent
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|device
op_star
id|parent
)paren
suffix:semicolon
r_extern
r_int
id|device_suspend
c_func
(paren
id|pm_message_t
id|state
)paren
suffix:semicolon
r_extern
r_int
id|device_power_down
c_func
(paren
id|pm_message_t
id|state
)paren
suffix:semicolon
r_extern
r_void
id|device_power_up
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|device_resume
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_PM_H */
eof
