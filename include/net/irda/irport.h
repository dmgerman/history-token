multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irport.h&n; * Version:       0.1&n; * Description:   Serial driver for IrDA&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Sun Aug  3 13:49:59 1997&n; * Modified at:   Fri Jan 14 10:21:10 2000&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1997, 1998-2000 Dag Brattli &lt;dagb@cs.uit.no&gt;&n; *     All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *&n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *&n; ********************************************************************/
macro_line|#ifndef IRPORT_H
DECL|macro|IRPORT_H
mdefine_line|#define IRPORT_H
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;net/irda/irda_device.h&gt;
DECL|macro|SPEED_DEFAULT
mdefine_line|#define SPEED_DEFAULT 9600
DECL|macro|SPEED_MAX
mdefine_line|#define SPEED_MAX     115200
multiline_comment|/*&n; * These are the supported serial types.&n; */
DECL|macro|PORT_UNKNOWN
mdefine_line|#define PORT_UNKNOWN    0
DECL|macro|PORT_8250
mdefine_line|#define PORT_8250       1
DECL|macro|PORT_16450
mdefine_line|#define PORT_16450      2
DECL|macro|PORT_16550
mdefine_line|#define PORT_16550      3
DECL|macro|PORT_16550A
mdefine_line|#define PORT_16550A     4
DECL|macro|PORT_CIRRUS
mdefine_line|#define PORT_CIRRUS     5
DECL|macro|PORT_16650
mdefine_line|#define PORT_16650      6
DECL|macro|PORT_MAX
mdefine_line|#define PORT_MAX        6  
DECL|macro|FRAME_MAX_SIZE
mdefine_line|#define FRAME_MAX_SIZE 2048
DECL|struct|irport_cb
r_struct
id|irport_cb
(brace
DECL|member|netdev
r_struct
id|net_device
op_star
id|netdev
suffix:semicolon
multiline_comment|/* Yes! we are some kind of netdevice */
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|irlap
r_struct
id|irlap_cb
op_star
id|irlap
suffix:semicolon
multiline_comment|/* The link layer we are attached to */
DECL|member|io
id|chipio_t
id|io
suffix:semicolon
multiline_comment|/* IrDA controller information */
DECL|member|tx_buff
id|iobuff_t
id|tx_buff
suffix:semicolon
multiline_comment|/* Transmit buffer */
DECL|member|rx_buff
id|iobuff_t
id|rx_buff
suffix:semicolon
multiline_comment|/* Receive buffer */
DECL|member|qos
r_struct
id|qos_info
id|qos
suffix:semicolon
multiline_comment|/* QoS capabilities for this device */
DECL|member|dongle
id|dongle_t
op_star
id|dongle
suffix:semicolon
multiline_comment|/* Dongle driver */
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
multiline_comment|/* Interface flags */
DECL|member|new_speed
id|__u32
id|new_speed
suffix:semicolon
DECL|member|mode
r_int
id|mode
suffix:semicolon
DECL|member|index
r_int
id|index
suffix:semicolon
multiline_comment|/* Instance index */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* For serializing operations */
multiline_comment|/* For piggyback drivers */
DECL|member|priv
r_void
op_star
id|priv
suffix:semicolon
DECL|member|change_speed
r_void
(paren
op_star
id|change_speed
)paren
(paren
r_void
op_star
id|priv
comma
id|__u32
id|speed
)paren
suffix:semicolon
DECL|member|interrupt
r_void
(paren
op_star
id|interrupt
)paren
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|irport_cb
op_star
id|irport_open
c_func
(paren
r_int
id|i
comma
r_int
r_int
id|iobase
comma
r_int
r_int
id|irq
)paren
suffix:semicolon
r_int
id|irport_close
c_func
(paren
r_struct
id|irport_cb
op_star
id|self
)paren
suffix:semicolon
r_void
id|irport_start
c_func
(paren
r_struct
id|irport_cb
op_star
id|self
)paren
suffix:semicolon
r_void
id|irport_stop
c_func
(paren
r_struct
id|irport_cb
op_star
id|self
)paren
suffix:semicolon
r_void
id|irport_change_speed
c_func
(paren
r_void
op_star
id|priv
comma
id|__u32
id|speed
)paren
suffix:semicolon
r_void
id|irport_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_int
id|irport_hard_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_int
id|irport_net_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_int
id|irport_net_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif /* IRPORT_H */
eof
