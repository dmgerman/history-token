multiline_comment|/*&n; * mcfserial.c -- serial driver for ColdFire internal UARTS.&n; *&n; * Copyright (c) 1999 Greg Ungerer &lt;gerg@snapgear.com&gt;&n; * Copyright (c) 2000-2001 Lineo, Inc. &lt;www.lineo.com&gt;&n; * Copyright (c) 2002 SnapGear Inc., &lt;www.snapgear.com&gt;&n; *&n; * Based on code from 68332serial.c which was:&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1998 TSHG&n; * Copyright (c) 1999 Rt-Control Inc. &lt;jeff@uclinux.org&gt;&n; */
macro_line|#ifndef _MCF_SERIAL_H
DECL|macro|_MCF_SERIAL_H
mdefine_line|#define _MCF_SERIAL_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; *&t;Define a local serial stats structure.&n; */
DECL|struct|mcf_stats
r_struct
id|mcf_stats
(brace
DECL|member|rx
r_int
r_int
id|rx
suffix:semicolon
DECL|member|tx
r_int
r_int
id|tx
suffix:semicolon
DECL|member|rxbreak
r_int
r_int
id|rxbreak
suffix:semicolon
DECL|member|rxframing
r_int
r_int
id|rxframing
suffix:semicolon
DECL|member|rxparity
r_int
r_int
id|rxparity
suffix:semicolon
DECL|member|rxoverrun
r_int
r_int
id|rxoverrun
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This is our internal structure for each serial port&squot;s state.&n; * Each serial port has one of these structures associated with it.&n; */
DECL|struct|mcf_serial
r_struct
id|mcf_serial
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
multiline_comment|/* UART memory address */
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* defined in tty.h */
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* UART type */
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
DECL|member|imr
r_int
r_char
id|imr
suffix:semicolon
multiline_comment|/* Software imr register */
DECL|member|baud
r_int
r_int
id|baud
suffix:semicolon
DECL|member|sigs
r_int
id|sigs
suffix:semicolon
DECL|member|custom_divisor
r_int
id|custom_divisor
suffix:semicolon
DECL|member|x_char
r_int
id|x_char
suffix:semicolon
multiline_comment|/* xon/xoff character */
DECL|member|baud_base
r_int
id|baud_base
suffix:semicolon
DECL|member|close_delay
r_int
id|close_delay
suffix:semicolon
DECL|member|closing_wait
r_int
r_int
id|closing_wait
suffix:semicolon
DECL|member|closing_wait2
r_int
r_int
id|closing_wait2
suffix:semicolon
DECL|member|event
r_int
r_int
id|event
suffix:semicolon
DECL|member|line
r_int
id|line
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
multiline_comment|/* # of fd on device */
DECL|member|blocked_open
r_int
id|blocked_open
suffix:semicolon
multiline_comment|/* # of blocked opens */
DECL|member|session
r_int
id|session
suffix:semicolon
multiline_comment|/* Session of opening process */
DECL|member|pgrp
r_int
id|pgrp
suffix:semicolon
multiline_comment|/* pgrp of opening process */
DECL|member|xmit_buf
r_int
r_char
op_star
id|xmit_buf
suffix:semicolon
DECL|member|xmit_head
r_int
id|xmit_head
suffix:semicolon
DECL|member|xmit_tail
r_int
id|xmit_tail
suffix:semicolon
DECL|member|xmit_cnt
r_int
id|xmit_cnt
suffix:semicolon
DECL|member|stats
r_struct
id|mcf_stats
id|stats
suffix:semicolon
DECL|member|tqueue
r_struct
id|work_struct
id|tqueue
suffix:semicolon
DECL|member|tqueue_hangup
r_struct
id|work_struct
id|tqueue_hangup
suffix:semicolon
DECL|member|normal_termios
r_struct
id|termios
id|normal_termios
suffix:semicolon
DECL|member|callout_termios
r_struct
id|termios
id|callout_termios
suffix:semicolon
DECL|member|open_wait
id|wait_queue_head_t
id|open_wait
suffix:semicolon
DECL|member|close_wait
id|wait_queue_head_t
id|close_wait
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _MCF_SERIAL_H */
eof
