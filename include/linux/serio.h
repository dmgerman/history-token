macro_line|#ifndef _SERIO_H
DECL|macro|_SERIO_H
mdefine_line|#define _SERIO_H
multiline_comment|/*&n; * Copyright (C) 1999-2002 Vojtech Pavlik&n;*&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation.&n; */
macro_line|#include &lt;linux/ioctl.h&gt;
DECL|macro|SPIOCSTYPE
mdefine_line|#define SPIOCSTYPE&t;_IOW(&squot;q&squot;, 0x01, unsigned long)
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/device.h&gt;
DECL|struct|serio_device_id
r_struct
id|serio_device_id
(brace
DECL|member|type
r_int
r_char
id|type
suffix:semicolon
DECL|member|extra
r_int
r_char
id|extra
suffix:semicolon
DECL|member|id
r_int
r_char
id|id
suffix:semicolon
DECL|member|proto
r_int
r_char
id|proto
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|serio
r_struct
id|serio
(brace
DECL|member|port_data
r_void
op_star
id|port_data
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|phys
r_char
id|phys
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|manual_bind
r_int
r_int
id|manual_bind
suffix:semicolon
DECL|member|id
r_struct
id|serio_device_id
id|id
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* protects critical sections from port&squot;s interrupt handler */
DECL|member|write
r_int
(paren
op_star
id|write
)paren
(paren
r_struct
id|serio
op_star
comma
r_int
r_char
)paren
suffix:semicolon
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
r_struct
id|serio
op_star
)paren
suffix:semicolon
DECL|member|close
r_void
(paren
op_star
id|close
)paren
(paren
r_struct
id|serio
op_star
)paren
suffix:semicolon
DECL|member|start
r_int
(paren
op_star
id|start
)paren
(paren
r_struct
id|serio
op_star
)paren
suffix:semicolon
DECL|member|stop
r_void
(paren
op_star
id|stop
)paren
(paren
r_struct
id|serio
op_star
)paren
suffix:semicolon
DECL|member|parent
DECL|member|child
r_struct
id|serio
op_star
id|parent
comma
op_star
id|child
suffix:semicolon
DECL|member|drv
r_struct
id|serio_driver
op_star
id|drv
suffix:semicolon
multiline_comment|/* accessed from interrupt, must be protected by serio-&gt;lock and serio-&gt;sem */
DECL|member|drv_sem
r_struct
id|semaphore
id|drv_sem
suffix:semicolon
multiline_comment|/* protects serio-&gt;drv so attributes can pin driver */
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
DECL|member|registered
r_int
r_int
id|registered
suffix:semicolon
multiline_comment|/* port has been fully registered with driver core */
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_serio_port
mdefine_line|#define to_serio_port(d)&t;container_of(d, struct serio, dev)
DECL|struct|serio_driver
r_struct
id|serio_driver
(brace
DECL|member|private
r_void
op_star
r_private
suffix:semicolon
DECL|member|description
r_char
op_star
id|description
suffix:semicolon
DECL|member|id_table
r_struct
id|serio_device_id
op_star
id|id_table
suffix:semicolon
DECL|member|manual_bind
r_int
r_int
id|manual_bind
suffix:semicolon
DECL|member|write_wakeup
r_void
(paren
op_star
id|write_wakeup
)paren
(paren
r_struct
id|serio
op_star
)paren
suffix:semicolon
DECL|member|interrupt
id|irqreturn_t
(paren
op_star
id|interrupt
)paren
(paren
r_struct
id|serio
op_star
comma
r_int
r_char
comma
r_int
r_int
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|member|connect
r_int
(paren
op_star
id|connect
)paren
(paren
r_struct
id|serio
op_star
comma
r_struct
id|serio_driver
op_star
id|drv
)paren
suffix:semicolon
DECL|member|reconnect
r_int
(paren
op_star
id|reconnect
)paren
(paren
r_struct
id|serio
op_star
)paren
suffix:semicolon
DECL|member|disconnect
r_void
(paren
op_star
id|disconnect
)paren
(paren
r_struct
id|serio
op_star
)paren
suffix:semicolon
DECL|member|cleanup
r_void
(paren
op_star
id|cleanup
)paren
(paren
r_struct
id|serio
op_star
)paren
suffix:semicolon
DECL|member|driver
r_struct
id|device_driver
id|driver
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_serio_driver
mdefine_line|#define to_serio_driver(d)&t;container_of(d, struct serio_driver, driver)
r_int
id|serio_open
c_func
(paren
r_struct
id|serio
op_star
id|serio
comma
r_struct
id|serio_driver
op_star
id|drv
)paren
suffix:semicolon
r_void
id|serio_close
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
suffix:semicolon
r_void
id|serio_rescan
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
suffix:semicolon
r_void
id|serio_reconnect
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
suffix:semicolon
id|irqreturn_t
id|serio_interrupt
c_func
(paren
r_struct
id|serio
op_star
id|serio
comma
r_int
r_char
id|data
comma
r_int
r_int
id|flags
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_void
id|__serio_register_port
c_func
(paren
r_struct
id|serio
op_star
id|serio
comma
r_struct
id|module
op_star
id|owner
)paren
suffix:semicolon
DECL|function|serio_register_port
r_static
r_inline
r_void
id|serio_register_port
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
id|__serio_register_port
c_func
(paren
id|serio
comma
id|THIS_MODULE
)paren
suffix:semicolon
)brace
r_void
id|serio_unregister_port
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
suffix:semicolon
r_void
id|__serio_unregister_port_delayed
c_func
(paren
r_struct
id|serio
op_star
id|serio
comma
r_struct
id|module
op_star
id|owner
)paren
suffix:semicolon
DECL|function|serio_unregister_port_delayed
r_static
r_inline
r_void
id|serio_unregister_port_delayed
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
id|__serio_unregister_port_delayed
c_func
(paren
id|serio
comma
id|THIS_MODULE
)paren
suffix:semicolon
)brace
r_void
id|__serio_register_driver
c_func
(paren
r_struct
id|serio_driver
op_star
id|drv
comma
r_struct
id|module
op_star
id|owner
)paren
suffix:semicolon
DECL|function|serio_register_driver
r_static
r_inline
r_void
id|serio_register_driver
c_func
(paren
r_struct
id|serio_driver
op_star
id|drv
)paren
(brace
id|__serio_register_driver
c_func
(paren
id|drv
comma
id|THIS_MODULE
)paren
suffix:semicolon
)brace
r_void
id|serio_unregister_driver
c_func
(paren
r_struct
id|serio_driver
op_star
id|drv
)paren
suffix:semicolon
DECL|function|serio_write
r_static
r_inline
r_int
id|serio_write
c_func
(paren
r_struct
id|serio
op_star
id|serio
comma
r_int
r_char
id|data
)paren
(brace
r_if
c_cond
(paren
id|serio-&gt;write
)paren
r_return
id|serio
op_member_access_from_pointer
id|write
c_func
(paren
id|serio
comma
id|data
)paren
suffix:semicolon
r_else
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|serio_drv_write_wakeup
r_static
r_inline
r_void
id|serio_drv_write_wakeup
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_if
c_cond
(paren
id|serio-&gt;drv
op_logical_and
id|serio-&gt;drv-&gt;write_wakeup
)paren
id|serio-&gt;drv
op_member_access_from_pointer
id|write_wakeup
c_func
(paren
id|serio
)paren
suffix:semicolon
)brace
DECL|function|serio_cleanup
r_static
r_inline
r_void
id|serio_cleanup
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_if
c_cond
(paren
id|serio-&gt;drv
op_logical_and
id|serio-&gt;drv-&gt;cleanup
)paren
id|serio-&gt;drv
op_member_access_from_pointer
id|cleanup
c_func
(paren
id|serio
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Use the following fucntions to manipulate serio&squot;s per-port&n; * driver-specific data.&n; */
DECL|function|serio_get_drvdata
r_static
r_inline
r_void
op_star
id|serio_get_drvdata
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_return
id|dev_get_drvdata
c_func
(paren
op_amp
id|serio-&gt;dev
)paren
suffix:semicolon
)brace
DECL|function|serio_set_drvdata
r_static
r_inline
r_void
id|serio_set_drvdata
c_func
(paren
r_struct
id|serio
op_star
id|serio
comma
r_void
op_star
id|data
)paren
(brace
id|dev_set_drvdata
c_func
(paren
op_amp
id|serio-&gt;dev
comma
id|data
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Use the following fucntions to protect critical sections in&n; * driver code from port&squot;s interrupt handler&n; */
DECL|function|serio_pause_rx
r_static
r_inline
r_void
id|serio_pause_rx
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
id|spin_lock_irq
c_func
(paren
op_amp
id|serio-&gt;lock
)paren
suffix:semicolon
)brace
DECL|function|serio_continue_rx
r_static
r_inline
r_void
id|serio_continue_rx
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|serio-&gt;lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Use the following fucntions to pin serio&squot;s driver in process context&n; */
DECL|function|serio_pin_driver
r_static
r_inline
r_int
id|serio_pin_driver
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_return
id|down_interruptible
c_func
(paren
op_amp
id|serio-&gt;drv_sem
)paren
suffix:semicolon
)brace
DECL|function|serio_unpin_driver
r_static
r_inline
r_void
id|serio_unpin_driver
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
id|up
c_func
(paren
op_amp
id|serio-&gt;drv_sem
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * bit masks for use in &quot;interrupt&quot; flags (3rd argument)&n; */
DECL|macro|SERIO_TIMEOUT
mdefine_line|#define SERIO_TIMEOUT&t;1
DECL|macro|SERIO_PARITY
mdefine_line|#define SERIO_PARITY&t;2
DECL|macro|SERIO_FRAME
mdefine_line|#define SERIO_FRAME&t;4
DECL|macro|SERIO_ANY
mdefine_line|#define SERIO_ANY&t;0xff
multiline_comment|/*&n; * Serio types&n; */
DECL|macro|SERIO_XT
mdefine_line|#define SERIO_XT&t;0x00
DECL|macro|SERIO_8042
mdefine_line|#define SERIO_8042&t;0x01
DECL|macro|SERIO_RS232
mdefine_line|#define SERIO_RS232&t;0x02
DECL|macro|SERIO_HIL_MLC
mdefine_line|#define SERIO_HIL_MLC&t;0x03
DECL|macro|SERIO_PS_PSTHRU
mdefine_line|#define SERIO_PS_PSTHRU&t;0x05
DECL|macro|SERIO_8042_XL
mdefine_line|#define SERIO_8042_XL&t;0x06
multiline_comment|/*&n; * Serio types&n; */
DECL|macro|SERIO_UNKNOWN
mdefine_line|#define SERIO_UNKNOWN&t;0x00
DECL|macro|SERIO_MSC
mdefine_line|#define SERIO_MSC&t;0x01
DECL|macro|SERIO_SUN
mdefine_line|#define SERIO_SUN&t;0x02
DECL|macro|SERIO_MS
mdefine_line|#define SERIO_MS&t;0x03
DECL|macro|SERIO_MP
mdefine_line|#define SERIO_MP&t;0x04
DECL|macro|SERIO_MZ
mdefine_line|#define SERIO_MZ&t;0x05
DECL|macro|SERIO_MZP
mdefine_line|#define SERIO_MZP&t;0x06
DECL|macro|SERIO_MZPP
mdefine_line|#define SERIO_MZPP&t;0x07
DECL|macro|SERIO_VSXXXAA
mdefine_line|#define SERIO_VSXXXAA&t;0x08
DECL|macro|SERIO_SUNKBD
mdefine_line|#define SERIO_SUNKBD&t;0x10
DECL|macro|SERIO_WARRIOR
mdefine_line|#define SERIO_WARRIOR&t;0x18
DECL|macro|SERIO_SPACEORB
mdefine_line|#define SERIO_SPACEORB&t;0x19
DECL|macro|SERIO_MAGELLAN
mdefine_line|#define SERIO_MAGELLAN&t;0x1a
DECL|macro|SERIO_SPACEBALL
mdefine_line|#define SERIO_SPACEBALL&t;0x1b
DECL|macro|SERIO_GUNZE
mdefine_line|#define SERIO_GUNZE&t;0x1c
DECL|macro|SERIO_IFORCE
mdefine_line|#define SERIO_IFORCE&t;0x1d
DECL|macro|SERIO_STINGER
mdefine_line|#define SERIO_STINGER&t;0x1e
DECL|macro|SERIO_NEWTON
mdefine_line|#define SERIO_NEWTON&t;0x1f
DECL|macro|SERIO_STOWAWAY
mdefine_line|#define SERIO_STOWAWAY&t;0x20
DECL|macro|SERIO_H3600
mdefine_line|#define SERIO_H3600&t;0x21
DECL|macro|SERIO_PS2SER
mdefine_line|#define SERIO_PS2SER&t;0x22
DECL|macro|SERIO_TWIDKBD
mdefine_line|#define SERIO_TWIDKBD&t;0x23
DECL|macro|SERIO_TWIDJOY
mdefine_line|#define SERIO_TWIDJOY&t;0x24
DECL|macro|SERIO_HIL
mdefine_line|#define SERIO_HIL&t;0x25
DECL|macro|SERIO_SNES232
mdefine_line|#define SERIO_SNES232&t;0x26
DECL|macro|SERIO_SEMTECH
mdefine_line|#define SERIO_SEMTECH&t;0x27
DECL|macro|SERIO_LKKBD
mdefine_line|#define SERIO_LKKBD&t;0x28
DECL|macro|SERIO_ELO
mdefine_line|#define SERIO_ELO&t;0x29
macro_line|#endif
eof
