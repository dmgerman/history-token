multiline_comment|/*&n; *      linux/drivers/char/specialix_io8.h  -- &n; *                                   Specialix IO8+ multiport serial driver.&n; *&n; *      Copyright (C) 1997 Roger Wolff (R.E.Wolff@BitWizard.nl)&n; *      Copyright (C) 1994-1996  Dmitry Gorodchanin (pgmdsg@ibi.com)&n; *&n; *&n; *      Specialix pays for the development and support of this driver.&n; *      Please DO contact io8-linux@specialix.co.uk if you require&n; *      support.&n; *&n; *      This driver was developped in the BitWizard linux device&n; *      driver service. If you require a linux device driver for your&n; *      product, please contact devices@BitWizard.nl for a quote.&n; *&n; *      This code is firmly based on the riscom/8 serial driver,&n; *      written by Dmitry Gorodchanin. The specialix IO8+ card&n; *      programming information was obtained from the CL-CD1865 Data&n; *      Book, and Specialix document number 6200059: IO8+ Hardware&n; *      Functional Specification.&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License as&n; *      published by the Free Software Foundation; either version 2 of&n; *      the License, or (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be&n; *      useful, but WITHOUT ANY WARRANTY; without even the implied&n; *      warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR&n; *      PURPOSE.  See the GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public&n; *      License along with this program; if not, write to the Free&n; *      Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139,&n; *      USA.&n; * */
macro_line|#ifndef __LINUX_SPECIALIX_H
DECL|macro|__LINUX_SPECIALIX_H
mdefine_line|#define __LINUX_SPECIALIX_H
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#ifdef __KERNEL__
multiline_comment|/* You can have max 4 ISA cards in one PC, and I recommend not much &n;more than a few  PCI versions of the card. */
DECL|macro|SX_NBOARD
mdefine_line|#define SX_NBOARD&t;&t;8
multiline_comment|/* NOTE: Specialix decoder recognizes 4 addresses, but only two are used.... */
DECL|macro|SX_IO_SPACE
mdefine_line|#define SX_IO_SPACE             4
multiline_comment|/* The PCI version decodes 8 addresses, but still only 2 are used. */
DECL|macro|SX_PCI_IO_SPACE
mdefine_line|#define SX_PCI_IO_SPACE         8
multiline_comment|/* eight ports per board. */
DECL|macro|SX_NPORT
mdefine_line|#define SX_NPORT        &t;8
DECL|macro|SX_BOARD
mdefine_line|#define SX_BOARD(line)&t;&t;((line) / SX_NPORT)
DECL|macro|SX_PORT
mdefine_line|#define SX_PORT(line)&t;&t;((line) &amp; (SX_NPORT - 1))
DECL|macro|SX_DATA_REG
mdefine_line|#define SX_DATA_REG 0     /* Base+0 : Data register */
DECL|macro|SX_ADDR_REG
mdefine_line|#define SX_ADDR_REG 1     /* base+1 : Address register. */
DECL|macro|MHz
mdefine_line|#define MHz *1000000&t;/* I&squot;m ashamed of myself. */
multiline_comment|/* On-board oscillator frequency */
DECL|macro|SX_OSCFREQ
mdefine_line|#define SX_OSCFREQ      (25 MHz/2)
multiline_comment|/* There is a 25MHz crystal on the board, but the chip is in /2 mode */
multiline_comment|/* Ticks per sec. Used for setting receiver timeout and break length */
DECL|macro|SPECIALIX_TPS
mdefine_line|#define SPECIALIX_TPS&t;&t;4000
multiline_comment|/* Yeah, after heavy testing I decided it must be 6.&n; * Sure, You can change it if needed.&n; */
DECL|macro|SPECIALIX_RXFIFO
mdefine_line|#define SPECIALIX_RXFIFO&t;6&t;/* Max. receiver FIFO size (1-8) */
DECL|macro|SPECIALIX_MAGIC
mdefine_line|#define SPECIALIX_MAGIC&t;&t;0x0907
DECL|macro|SX_CCR_TIMEOUT
mdefine_line|#define SX_CCR_TIMEOUT 10000   /* CCR timeout. You may need to wait upto&n;                                  10 milliseconds before the internal&n;                                  processor is available again after&n;                                  you give it a command */
DECL|macro|SX_IOBASE1
mdefine_line|#define SX_IOBASE1&t;0x100
DECL|macro|SX_IOBASE2
mdefine_line|#define SX_IOBASE2&t;0x180
DECL|macro|SX_IOBASE3
mdefine_line|#define SX_IOBASE3&t;0x250
DECL|macro|SX_IOBASE4
mdefine_line|#define SX_IOBASE4&t;0x260
DECL|struct|specialix_board
r_struct
id|specialix_board
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
DECL|member|reg
r_int
id|reg
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SX_BOARD_PRESENT
mdefine_line|#define SX_BOARD_PRESENT&t;0x00000001
DECL|macro|SX_BOARD_ACTIVE
mdefine_line|#define SX_BOARD_ACTIVE&t;&t;0x00000002
DECL|macro|SX_BOARD_IS_PCI
mdefine_line|#define SX_BOARD_IS_PCI&t;&t;0x00000004
DECL|struct|specialix_port
r_struct
id|specialix_port
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
macro_line|#ifdef SX_REPORT_OVERRUN
DECL|member|overrun
r_int
r_int
id|overrun
suffix:semicolon
macro_line|#endif&t;
macro_line|#ifdef SX_REPORT_FIFO
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
macro_line|#endif /* __LINUX_SPECIALIX_H */
eof
