multiline_comment|/*&t;$Id: aurora.h,v 1.5 1999/12/02 09:55:16 davem Exp $&n; *&t;linux/drivers/sbus/char/aurora.h -- Aurora multiport driver&n; *&n; *&t;Copyright (c) 1999 by Oliver Aldulea (oli@bv.ro)&n; *&n; *&t;This code is based on the RISCom/8 multiport serial driver written&n; *&t;by Dmitry Gorodchanin (pgmdsg@ibi.com), based on the Linux serial&n; *&t;driver, written by Linus Torvalds, Theodore T&squot;so and others.&n; *&t;The Aurora multiport programming info was obtained mainly from the&n; *&t;Cirrus Logic CD180 documentation (available on the web), and by&n; *&t;doing heavy tests on the board. Many thanks to Eddie C. Dost for the&n; *&t;help on the sbus interface.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;This program is distributed in the hope that it will be useful,&n; *&t;but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *&t;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *&t;GNU General Public License for more details.&n; *&n; *&t;You should have received a copy of the GNU General Public License&n; *&t;along with this program; if not, write to the Free Software&n; *&t;Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *&t;Revision 1.0&n; *&n; *&t;This is the first public release.&n; *&n; *&t;This version needs a lot of feedback. This is the version that works&n; *&t;with _my_ board. My board is model 1600se, revision &squot;@(#)1600se.fth&n; *&t;1.2 3/28/95 1&squot;. The driver might work with your board, but I do not&n; *&t;guarantee it. If you have _any_ type of board, I need to know if the&n; *&t;driver works or not, I need to know exactly your board parameters&n; *&t;(get them with &squot;cd /proc/openprom/iommu/sbus/sio16/; ls *; cat *&squot;)&n; *&t;Also, I need your board revision code, which is written on the board.&n; *&t;Send me the output of my driver too (it outputs through klogd).&n; *&n; *&t;If the driver does not work, you can try enabling the debug options&n; *&t;to see what&squot;s wrong or what should be done.&n; *&n; *&t;I&squot;m sorry about the alignment of the code. It was written in a&n; *&t;128x48 environment.&n; *&n; *&t;I must say that I do not like Aurora Technologies&squot; policy. I asked&n; *&t;them to help me do this driver faster, but they ended by something&n; *&t;like &quot;don&squot;t call us, we&squot;ll call you&quot;, and I never heard anything&n; *&t;from them. They told me &quot;knowing the way the board works, I don&squot;t&n; *&t;doubt you and others on the net will make the driver.&quot;&n; *&t;The truth about this board is that it has nothing intelligent on it.&n; *&t;If you want to say to somebody what kind of board you have, say that&n; *&t;it uses Cirrus Logic processors (CD180). The power of the board is&n; *&t;in those two chips. The rest of the board is the interface to the&n; *&t;sbus and to the peripherals. Still, they did something smart: they&n; *&t;reversed DTR and RTS to make on-board automatic hardware flow&n; *&t;control usable.&n; *&t;Thanks to Aurora Technologies for wasting my time, nerves and money.&n; */
macro_line|#ifndef __LINUX_AURORA_H
DECL|macro|__LINUX_AURORA_H
mdefine_line|#define __LINUX_AURORA_H
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/serialP.h&gt;
macro_line|#ifdef __KERNEL__
multiline_comment|/* This is the number of boards to support. I&squot;ve only tested this driver with&n; * one board, so it might not work.&n; */
DECL|macro|AURORA_NBOARD
mdefine_line|#define AURORA_NBOARD 1
multiline_comment|/* Useful ? Yes. But you can safely comment the warnings if they annoy you&n; * (let me say that again: the warnings in the code, not this define). &n; */
DECL|macro|AURORA_PARANOIA_CHECK
mdefine_line|#define AURORA_PARANOIA_CHECK
multiline_comment|/* Well, after many lost nights, I found that the IRQ for this board is&n; * selected from four built-in values by writing some bits in the&n; * configuration register. This causes a little problem to occur: which&n; * IRQ to select ? Which one is the best for the user ? Well, I finally&n; * decided for the following algorithm: if the &quot;bintr&quot; value is not acceptable&n; * (not within type_1_irq[], then test the &quot;intr&quot; value, if that fails too,&n; * try each value from type_1_irq until succeded. Hope it&squot;s ok.&n; * You can safely reorder the irq&squot;s.&n; */
DECL|macro|TYPE_1_IRQS
mdefine_line|#define TYPE_1_IRQS 4
DECL|variable|type_1_irq
r_int
r_char
id|type_1_irq
(braket
id|TYPE_1_IRQS
)braket
op_assign
(brace
l_int|3
comma
l_int|5
comma
l_int|9
comma
l_int|13
)brace
suffix:semicolon
multiline_comment|/* I know something about another method of interrupt setting, but not enough.&n; * Also, this is for another type of board, so I first have to learn how to&n; * detect it.&n;#define TYPE_2_IRQS 3&n;unsigned char type_2_irq[TYPE_2_IRQS] = {&n;&t;0, 0, 0 ** could anyone find these for me ? (see AURORA_ALLIRQ below) **&n;&t;};&n;unsigned char type_2_mask[TYPE_2_IRQS] = {&n;&t;32, 64, 128&n;&t;};&n;*/
multiline_comment|/* The following section should only be modified by those who know what&n; * they&squot;re doing (or don&squot;t, but want to help with some feedback). Modifying&n; * anything raises a _big_ probability for your system to hang, but the&n; * sacrifice worths. (I sacrificed my ext2fs many, many times...)&n; */
multiline_comment|/* This one tries to dump to console the name of almost every function called,&n; * and many other debugging info.&n; */
DECL|macro|AURORA_DEBUG
macro_line|#undef AURORA_DEBUG
multiline_comment|/* These are the most dangerous and useful defines. They do printk() during&n; * the interrupt processing routine(s), so if you manage to get &quot;flooded&quot; by&n; * irq&squot;s, start thinking about the &quot;Power off/on&quot; button...&n; */
DECL|macro|AURORA_INTNORM
macro_line|#undef AURORA_INTNORM&t;/* This one enables the &quot;normal&quot; messages, but some&n;&t;&t;&t; * of them cause flood, so I preffered putting&n;&t;&t;&t; * them under a define */
DECL|macro|AURORA_INT_DEBUG
macro_line|#undef AURORA_INT_DEBUG /* This one is really bad. */
multiline_comment|/* Here&squot;s something helpful: after n irq&squot;s, the board will be disabled. This&n; * prevents irq flooding during debug (no need to think about power&n; * off/on anymore...)&n; */
DECL|macro|AURORA_FLOODPRO
mdefine_line|#define AURORA_FLOODPRO&t;10
multiline_comment|/* This one helps finding which irq the board calls, in case of a strange/&n; * unsupported board. AURORA_INT_DEBUG should be enabled, because I don&squot;t&n; * think /proc/interrupts or any command will be available in case of an irq&n; * flood... &quot;allirq&quot; is the list of all free irq&squot;s.&n; */
multiline_comment|/*&n;#define AURORA_ALLIRQ 6&n;int allirq[AURORA_ALLIRQ]={&n;&t;2,3,5,7,9,13&n;&t;};&n;*/
multiline_comment|/* These must not be modified. These values are assumed during the code for&n; * performance optimisations.&n; */
DECL|macro|AURORA_NCD180
mdefine_line|#define AURORA_NCD180 2 /* two chips per board */
DECL|macro|AURORA_NPORT
mdefine_line|#define AURORA_NPORT 8  /* 8 ports per chip */
multiline_comment|/* several utilities */
DECL|macro|AURORA_BOARD
mdefine_line|#define AURORA_BOARD(line)&t;(((line) &gt;&gt; 4) &amp; 0x01)
DECL|macro|AURORA_CD180
mdefine_line|#define AURORA_CD180(line)&t;(((line) &gt;&gt; 3) &amp; 0x01)
DECL|macro|AURORA_PORT
mdefine_line|#define AURORA_PORT(line)&t;((line) &amp; 15)
DECL|macro|AURORA_TNPORTS
mdefine_line|#define AURORA_TNPORTS (AURORA_NBOARD*AURORA_NCD180*AURORA_NPORT)
multiline_comment|/* Ticks per sec. Used for setting receiver timeout and break length */
DECL|macro|AURORA_TPS
mdefine_line|#define AURORA_TPS&t;&t;4000
DECL|macro|AURORA_MAGIC
mdefine_line|#define AURORA_MAGIC&t;0x0A18
multiline_comment|/* Yeah, after heavy testing I decided it must be 6.&n; * Sure, You can change it if needed.&n; */
DECL|macro|AURORA_RXFIFO
mdefine_line|#define AURORA_RXFIFO&t;&t;6&t;/* Max. receiver FIFO size (1-8) */
DECL|macro|AURORA_RXTH
mdefine_line|#define AURORA_RXTH&t;&t;7
DECL|struct|aurora_reg1
r_struct
id|aurora_reg1
(brace
DECL|member|r
id|__volatile__
r_int
r_char
id|r
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|aurora_reg128
r_struct
id|aurora_reg128
(brace
DECL|member|r
id|__volatile__
r_int
r_char
id|r
(braket
l_int|128
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|aurora_reg4
r_struct
id|aurora_reg4
(brace
DECL|member|r
id|__volatile__
r_int
r_char
id|r
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|Aurora_board
r_struct
id|Aurora_board
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|r0
r_struct
id|aurora_reg1
op_star
id|r0
suffix:semicolon
multiline_comment|/* This is the board configuration&n;&t;&t;&t;&t;&t; * register (write-only). */
DECL|member|r
r_struct
id|aurora_reg128
op_star
id|r
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* These are the registers for the&n;&t;&t;&t;&t;&t; * two chips. */
DECL|member|r3
r_struct
id|aurora_reg4
op_star
id|r3
suffix:semicolon
multiline_comment|/* These are used for hardware-based&n;&t;&t;&t;&t;&t; * acknowledge. Software-based ack is&n;&t;&t;&t;&t;&t; * not supported by CD180. */
DECL|member|oscfreq
r_int
r_int
id|oscfreq
suffix:semicolon
multiline_comment|/* The on-board oscillator&n;&t;&t;&t;&t;&t;  * frequency, in Hz. */
DECL|member|irq
r_int
r_char
id|irq
suffix:semicolon
macro_line|#ifdef MODULE
DECL|member|count
r_int
r_char
id|count
suffix:semicolon
multiline_comment|/* counts the use of the board */
macro_line|#endif
multiline_comment|/* Values for the dtr_rts swapped mode. */
DECL|member|DTR
r_int
r_char
id|DTR
suffix:semicolon
DECL|member|RTS
r_int
r_char
id|RTS
suffix:semicolon
DECL|member|MSVDTR
r_int
r_char
id|MSVDTR
suffix:semicolon
DECL|member|MSVRTS
r_int
r_char
id|MSVRTS
suffix:semicolon
multiline_comment|/* Values for hardware acknowledge. */
DECL|member|ACK_MINT
DECL|member|ACK_TINT
DECL|member|ACK_RINT
r_int
r_char
id|ACK_MINT
comma
id|ACK_TINT
comma
id|ACK_RINT
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Board configuration register */
DECL|macro|AURORA_CFG_ENABLE_IO
mdefine_line|#define AURORA_CFG_ENABLE_IO&t;8
DECL|macro|AURORA_CFG_ENABLE_IRQ
mdefine_line|#define AURORA_CFG_ENABLE_IRQ&t;4
multiline_comment|/* Board flags */
DECL|macro|AURORA_BOARD_PRESENT
mdefine_line|#define AURORA_BOARD_PRESENT&t;&t;0x00000001
DECL|macro|AURORA_BOARD_ACTIVE
mdefine_line|#define AURORA_BOARD_ACTIVE&t;&t;0x00000002
DECL|macro|AURORA_BOARD_TYPE_2
mdefine_line|#define AURORA_BOARD_TYPE_2&t;&t;0x00000004&t;/* don&squot;t know how to&n;&t;&t;&t;&t;&t;&t;&t; * detect this yet */
DECL|macro|AURORA_BOARD_DTR_FLOW_OK
mdefine_line|#define AURORA_BOARD_DTR_FLOW_OK&t;0x00000008
multiline_comment|/* The story goes like this: Cirrus programmed the CD-180 chip to do automatic&n; * hardware flow control, and do it using CTS and DTR. CTS is ok, but, if you&n; * have a modem and the chip drops DTR, then the modem will drop the carrier&n; * (ain&squot;t that cute...). Luckily, the guys at Aurora decided to swap DTR and&n; * RTS, which makes the flow control usable. I hope that all the boards made&n; * by Aurora have these two signals swapped. If your&squot;s doesn&squot;t but you have a&n; * breakout box, you can try to reverse them yourself, then set the following&n; * flag.&n; */
DECL|macro|AURORA_FORCE_DTR_FLOW
macro_line|#undef AURORA_FORCE_DTR_FLOW
multiline_comment|/* In fact, a few more words have to be said about hardware flow control.&n; * This driver handles &quot;output&quot; flow control through the on-board facility&n; * CTS Auto Enable. For the &quot;input&quot; flow control there are two cases when&n; * the flow should be controlled. The first case is when the kernel is so&n; * busy that it cannot process IRQ&squot;s in time; this flow control can only be&n; * activated by the on-board chip, and if the board has RTS and DTR swapped,&n; * this facility is usable. The second case is when the application is so&n; * busy that it cannot receive bytes from the kernel, and this flow must be&n; * activated by software. This second case is not yet implemented in this&n; * driver. Unfortunately, I estimate that the second case is the one that&n; * occurs the most.&n; */
DECL|struct|Aurora_port
r_struct
id|Aurora_port
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
DECL|member|SRER
r_int
r_char
id|SRER
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
macro_line|#ifdef AURORA_REPORT_OVERRUN
DECL|member|overrun
r_int
r_int
id|overrun
suffix:semicolon
macro_line|#endif&t;
macro_line|#ifdef AURORA_REPORT_FIFO
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
macro_line|#endif
macro_line|#endif /*__LINUX_AURORA_H*/
eof
