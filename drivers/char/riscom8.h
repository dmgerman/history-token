multiline_comment|/*&n; *      linux/drivers/char/riscom8.h  -- RISCom/8 multiport serial driver.&n; *&n; *      Copyright (C) 1994-1996  Dmitry Gorodchanin (pgmdsg@ibi.com)&n; *&n; *      This code is loosely based on the Linux serial driver, written by&n; *      Linus Torvalds, Theodore T&squot;so and others. The RISCom/8 card &n; *      programming info was obtained from various drivers for other OSes &n; *&t;(FreeBSD, ISC, etc), but no source code from those drivers were &n; *&t;directly included in this driver.&n; *&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __LINUX_RISCOM8_H
DECL|macro|__LINUX_RISCOM8_H
mdefine_line|#define __LINUX_RISCOM8_H
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#ifdef __KERNEL__
DECL|macro|RC_NBOARD
mdefine_line|#define RC_NBOARD&t;&t;4
multiline_comment|/* NOTE: RISCom decoder recognizes 16 addresses... */
DECL|macro|RC_NPORT
mdefine_line|#define RC_NPORT        &t;8  
DECL|macro|RC_BOARD
mdefine_line|#define RC_BOARD(line)&t;&t;(((line) &gt;&gt; 3) &amp; 0x07)
DECL|macro|RC_PORT
mdefine_line|#define RC_PORT(line)&t;&t;((line) &amp; (RC_NPORT - 1))
multiline_comment|/* Ticks per sec. Used for setting receiver timeout and break length */
DECL|macro|RISCOM_TPS
mdefine_line|#define RISCOM_TPS&t;&t;4000
multiline_comment|/* Yeah, after heavy testing I decided it must be 6.&n; * Sure, You can change it if needed.&n; */
DECL|macro|RISCOM_RXFIFO
mdefine_line|#define RISCOM_RXFIFO&t;&t;6&t;/* Max. receiver FIFO size (1-8) */
DECL|macro|RISCOM8_MAGIC
mdefine_line|#define RISCOM8_MAGIC&t;&t;0x0907
DECL|macro|RC_IOBASE1
mdefine_line|#define RC_IOBASE1&t;0x220
DECL|macro|RC_IOBASE2
mdefine_line|#define RC_IOBASE2&t;0x240
DECL|macro|RC_IOBASE3
mdefine_line|#define RC_IOBASE3&t;0x250
DECL|macro|RC_IOBASE4
mdefine_line|#define RC_IOBASE4&t;0x260
DECL|struct|riscom_board
r_struct
id|riscom_board
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
DECL|member|irq
r_int
r_char
id|irq
suffix:semicolon
DECL|member|count
r_int
r_char
id|count
suffix:semicolon
DECL|member|DTR
r_int
r_char
id|DTR
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RC_BOARD_PRESENT
mdefine_line|#define RC_BOARD_PRESENT&t;0x00000001
DECL|macro|RC_BOARD_ACTIVE
mdefine_line|#define RC_BOARD_ACTIVE&t;&t;0x00000002
DECL|struct|riscom_port
r_struct
id|riscom_port
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|baud_base
r_int
id|baud_base
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|blocked_open
r_int
id|blocked_open
suffix:semicolon
DECL|member|event
r_int
id|event
suffix:semicolon
multiline_comment|/* long req&squot;d for set_bit --RR */
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
DECL|member|close_delay
r_int
id|close_delay
suffix:semicolon
DECL|member|session
r_int
id|session
suffix:semicolon
DECL|member|pgrp
r_int
id|pgrp
suffix:semicolon
DECL|member|xmit_buf
r_int
r_char
op_star
id|xmit_buf
suffix:semicolon
DECL|member|custom_divisor
r_int
id|custom_divisor
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
DECL|member|tqueue
r_struct
id|tq_struct
id|tqueue
suffix:semicolon
DECL|member|tqueue_hangup
r_struct
id|tq_struct
id|tqueue_hangup
suffix:semicolon
DECL|member|wakeup_chars
r_int
id|wakeup_chars
suffix:semicolon
DECL|member|break_length
r_int
id|break_length
suffix:semicolon
DECL|member|closing_wait
r_int
r_int
id|closing_wait
suffix:semicolon
DECL|member|mark_mask
r_int
r_char
id|mark_mask
suffix:semicolon
DECL|member|IER
r_int
r_char
id|IER
suffix:semicolon
DECL|member|MSVR
r_int
r_char
id|MSVR
suffix:semicolon
DECL|member|COR2
r_int
r_char
id|COR2
suffix:semicolon
macro_line|#ifdef RC_REPORT_OVERRUN
DECL|member|overrun
r_int
r_int
id|overrun
suffix:semicolon
macro_line|#endif&t;
macro_line|#ifdef RC_REPORT_FIFO
DECL|member|hits
r_int
r_int
id|hits
(braket
l_int|10
)braket
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __LINUX_RISCOM8_H */
eof
