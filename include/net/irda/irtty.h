multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irtty.h&n; * Version:       1.0&n; * Description:   &n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Tue Dec  9 21:13:12 1997&n; * Modified at:   Tue Jan 25 09:10:18 2000&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; *  &n; *     Copyright (c) 1997, 1999-2000 Dag Brattli, All Rights Reserved.&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
macro_line|#ifndef IRTTY_H
DECL|macro|IRTTY_H
mdefine_line|#define IRTTY_H
macro_line|#include &lt;linux/if.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/termios.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irqueue.h&gt;
macro_line|#include &lt;net/irda/irda_device.h&gt;
multiline_comment|/* Used by ioctl */
DECL|struct|irtty_info
r_struct
id|irtty_info
(brace
DECL|member|name
r_char
id|name
(braket
l_int|6
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IRTTY_IOC_MAGIC
mdefine_line|#define IRTTY_IOC_MAGIC &squot;e&squot;
DECL|macro|IRTTY_IOCTDONGLE
mdefine_line|#define IRTTY_IOCTDONGLE  _IO(IRTTY_IOC_MAGIC, 1)
DECL|macro|IRTTY_IOCGET
mdefine_line|#define IRTTY_IOCGET     _IOR(IRTTY_IOC_MAGIC, 2, struct irtty_info)
DECL|macro|IRTTY_IOC_MAXNR
mdefine_line|#define IRTTY_IOC_MAXNR   2
DECL|struct|irtty_cb
r_struct
id|irtty_cb
(brace
DECL|member|q
id|irda_queue_t
id|q
suffix:semicolon
multiline_comment|/* Must be first */
DECL|member|magic
id|magic_t
id|magic
suffix:semicolon
DECL|member|netdev
r_struct
id|net_device
op_star
id|netdev
suffix:semicolon
multiline_comment|/* Yes! we are some kind of netdevice */
DECL|member|task
r_struct
id|irda_task
op_star
id|task
suffix:semicolon
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
DECL|member|irlap
r_struct
id|irlap_cb
op_star
id|irlap
suffix:semicolon
multiline_comment|/* The link layer we are binded to */
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
DECL|member|new_speed
id|__u32
id|new_speed
suffix:semicolon
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
multiline_comment|/* Interface flags */
DECL|member|mode
id|INFRARED_MODE
id|mode
suffix:semicolon
)brace
suffix:semicolon
r_int
id|irtty_register_dongle
c_func
(paren
r_struct
id|dongle_reg
op_star
id|dongle
)paren
suffix:semicolon
r_void
id|irtty_unregister_dongle
c_func
(paren
r_struct
id|dongle_reg
op_star
id|dongle
)paren
suffix:semicolon
macro_line|#endif
eof
