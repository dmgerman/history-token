multiline_comment|/* 68328serial.h: Definitions for the mc68328 serial driver.&n; *&n; * Copyright (C) 1995       David S. Miller    &lt;davem@caip.rutgers.edu&gt;&n; * Copyright (C) 1998       Kenneth Albanowski &lt;kjahds@kjahds.com&gt;&n; * Copyright (C) 1998, 1999 D. Jeff Dionne     &lt;jeff@uclinux.org&gt;&n; * Copyright (C) 1999       Vladimir Gurevich  &lt;vgurevic@cisco.com&gt;&n; *&n; * VZ Support/Fixes             Evan Stawnyczy &lt;e@lineo.ca&gt;&n; */
macro_line|#ifndef _MC683XX_SERIAL_H
DECL|macro|_MC683XX_SERIAL_H
mdefine_line|#define _MC683XX_SERIAL_H
macro_line|#include &lt;linux/config.h&gt;
DECL|struct|serial_struct
r_struct
id|serial_struct
(brace
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|line
r_int
id|line
suffix:semicolon
DECL|member|port
r_int
id|port
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|xmit_fifo_size
r_int
id|xmit_fifo_size
suffix:semicolon
DECL|member|custom_divisor
r_int
id|custom_divisor
suffix:semicolon
DECL|member|baud_base
r_int
id|baud_base
suffix:semicolon
DECL|member|close_delay
r_int
r_int
id|close_delay
suffix:semicolon
DECL|member|reserved_char
r_char
id|reserved_char
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|hub6
r_int
id|hub6
suffix:semicolon
multiline_comment|/* FIXME: We don&squot;t have AT&amp;T Hub6 boards! */
DECL|member|closing_wait
r_int
r_int
id|closing_wait
suffix:semicolon
multiline_comment|/* time to wait before closing */
DECL|member|closing_wait2
r_int
r_int
id|closing_wait2
suffix:semicolon
multiline_comment|/* no longer used... */
DECL|member|reserved
r_int
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * For the close wait times, 0 means wait forever for serial port to&n; * flush its output.  65535 means don&squot;t wait at all.&n; */
DECL|macro|S_CLOSING_WAIT_INF
mdefine_line|#define S_CLOSING_WAIT_INF&t;0
DECL|macro|S_CLOSING_WAIT_NONE
mdefine_line|#define S_CLOSING_WAIT_NONE&t;65535
multiline_comment|/*&n; * Definitions for S_struct (and serial_struct) flags field&n; */
DECL|macro|S_HUP_NOTIFY
mdefine_line|#define S_HUP_NOTIFY 0x0001 /* Notify getty on hangups and closes &n;&t;&t;&t;&t;   on the callout port */
DECL|macro|S_FOURPORT
mdefine_line|#define S_FOURPORT  0x0002&t;/* Set OU1, OUT2 per AST Fourport settings */
DECL|macro|S_SAK
mdefine_line|#define S_SAK&t;0x0004&t;/* Secure Attention Key (Orange book) */
DECL|macro|S_SPLIT_TERMIOS
mdefine_line|#define S_SPLIT_TERMIOS 0x0008 /* Separate termios for dialin/callout */
DECL|macro|S_SPD_MASK
mdefine_line|#define S_SPD_MASK&t;0x0030
DECL|macro|S_SPD_HI
mdefine_line|#define S_SPD_HI&t;0x0010&t;/* Use 56000 instead of 38400 bps */
DECL|macro|S_SPD_VHI
mdefine_line|#define S_SPD_VHI&t;0x0020  /* Use 115200 instead of 38400 bps */
DECL|macro|S_SPD_CUST
mdefine_line|#define S_SPD_CUST&t;0x0030  /* Use user-specified divisor */
DECL|macro|S_SKIP_TEST
mdefine_line|#define S_SKIP_TEST&t;0x0040 /* Skip UART test during autoconfiguration */
DECL|macro|S_AUTO_IRQ
mdefine_line|#define S_AUTO_IRQ  0x0080 /* Do automatic IRQ during autoconfiguration */
DECL|macro|S_SESSION_LOCKOUT
mdefine_line|#define S_SESSION_LOCKOUT 0x0100 /* Lock out cua opens based on session */
DECL|macro|S_PGRP_LOCKOUT
mdefine_line|#define S_PGRP_LOCKOUT    0x0200 /* Lock out cua opens based on pgrp */
DECL|macro|S_CALLOUT_NOHUP
mdefine_line|#define S_CALLOUT_NOHUP   0x0400 /* Don&squot;t do hangups for cua device */
DECL|macro|S_FLAGS
mdefine_line|#define S_FLAGS&t;0x0FFF&t;/* Possible legal S flags */
DECL|macro|S_USR_MASK
mdefine_line|#define S_USR_MASK 0x0430&t;/* Legal flags that non-privileged&n;&t;&t;&t;&t; * users can set or reset */
multiline_comment|/* Internal flags used only by kernel/chr_drv/serial.c */
DECL|macro|S_INITIALIZED
mdefine_line|#define S_INITIALIZED&t;0x80000000 /* Serial port was initialized */
DECL|macro|S_CALLOUT_ACTIVE
mdefine_line|#define S_CALLOUT_ACTIVE&t;0x40000000 /* Call out device is active */
DECL|macro|S_NORMAL_ACTIVE
mdefine_line|#define S_NORMAL_ACTIVE&t;0x20000000 /* Normal device is active */
DECL|macro|S_BOOT_AUTOCONF
mdefine_line|#define S_BOOT_AUTOCONF&t;0x10000000 /* Autoconfigure port on bootup */
DECL|macro|S_CLOSING
mdefine_line|#define S_CLOSING&t;&t;0x08000000 /* Serial port is closing */
DECL|macro|S_CTS_FLOW
mdefine_line|#define S_CTS_FLOW&t;&t;0x04000000 /* Do CTS flow control */
DECL|macro|S_CHECK_CD
mdefine_line|#define S_CHECK_CD&t;&t;0x02000000 /* i.e., CLOCAL */
multiline_comment|/* Software state per channel */
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * I believe this is the optimal setting that reduces the number of interrupts.&n; * At high speeds the output might become a little &quot;bursted&quot; (use USTCNT_TXHE&n; * if that bothers you), but in most cases it will not, since we try to &n; * transmit characters every time rs_interrupt is called. Thus, quite often&n; * you&squot;ll see that a receive interrupt occures before the transmit one.&n; *                                  -- Vladimir Gurevich&n; */
DECL|macro|USTCNT_TX_INTR_MASK
mdefine_line|#define USTCNT_TX_INTR_MASK (USTCNT_TXEE)
multiline_comment|/*&n; * 68328 and 68EZ328 UARTS are a little bit different. EZ328 has special&n; * &quot;Old data interrupt&quot; which occures whenever the data stay in the FIFO&n; * longer than 30 bits time. This allows us to use FIFO without compromising&n; * latency. &squot;328 does not have this feature and without the real  328-based&n; * board I would assume that RXRE is the safest setting.&n; *&n; * For EZ328 I use RXHE (Half empty) interrupt to reduce the number of&n; * interrupts. RXFE (receive queue full) causes the system to lose data&n; * at least at 115200 baud&n; *&n; * If your board is busy doing other stuff, you might consider to use&n; * RXRE (data ready intrrupt) instead.&n; *&n; * The other option is to make these INTR masks run-time configurable, so&n; * that people can dynamically adapt them according to the current usage.&n; *                                  -- Vladimir Gurevich&n; */
multiline_comment|/* (es) */
macro_line|#if defined(CONFIG_M68EZ328) || defined(CONFIG_M68VZ328)
DECL|macro|USTCNT_RX_INTR_MASK
mdefine_line|#define USTCNT_RX_INTR_MASK (USTCNT_RXHE | USTCNT_ODEN)
macro_line|#elif defined(CONFIG_M68328)
DECL|macro|USTCNT_RX_INTR_MASK
mdefine_line|#define USTCNT_RX_INTR_MASK (USTCNT_RXRE)
macro_line|#else
macro_line|#error Please, define the Rx interrupt events for your CPU
macro_line|#endif
multiline_comment|/* (/es) */
multiline_comment|/*&n; * This is our internal structure for each serial port&squot;s state.&n; * &n; * Many fields are paralleled by the structure used by the serial_struct&n; * structure.&n; *&n; * For definitions of the flags field, see tty.h&n; */
DECL|struct|m68k_serial
r_struct
id|m68k_serial
(brace
DECL|member|soft_carrier
r_char
id|soft_carrier
suffix:semicolon
multiline_comment|/* Use soft carrier on this channel */
DECL|member|break_abort
r_char
id|break_abort
suffix:semicolon
multiline_comment|/* Is serial console in, so process brk/abrt */
DECL|member|is_cons
r_char
id|is_cons
suffix:semicolon
multiline_comment|/* Is this our console. */
multiline_comment|/* We need to know the current clock divisor&n;&t; * to read the bps rate the chip has currently&n;&t; * loaded.&n;&t; */
DECL|member|clk_divisor
r_int
r_char
id|clk_divisor
suffix:semicolon
multiline_comment|/* May be 1, 16, 32, or 64 */
DECL|member|baud
r_int
id|baud
suffix:semicolon
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|baud_base
r_int
id|baud_base
suffix:semicolon
DECL|member|port
r_int
id|port
suffix:semicolon
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
DECL|member|read_status_mask
r_int
id|read_status_mask
suffix:semicolon
DECL|member|ignore_status_mask
r_int
id|ignore_status_mask
suffix:semicolon
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
DECL|member|xmit_fifo_size
r_int
id|xmit_fifo_size
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
DECL|member|last_active
r_int
r_int
id|last_active
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
DECL|macro|SERIAL_MAGIC
mdefine_line|#define SERIAL_MAGIC 0x5301
multiline_comment|/*&n; * The size of the serial xmit buffer is 1 page, or 4096 bytes&n; */
DECL|macro|SERIAL_XMIT_SIZE
mdefine_line|#define SERIAL_XMIT_SIZE 4096
multiline_comment|/*&n; * Events are used to schedule things to happen at timer-interrupt&n; * time, instead of at rs interrupt time.&n; */
DECL|macro|RS_EVENT_WRITE_WAKEUP
mdefine_line|#define RS_EVENT_WRITE_WAKEUP&t;0
multiline_comment|/* &n; * Define the number of ports supported and their irqs.&n; */
macro_line|#ifndef CONFIG_68328_SERIAL_UART2
DECL|macro|NR_PORTS
mdefine_line|#define NR_PORTS 1
DECL|macro|UART_IRQ_DEFNS
mdefine_line|#define UART_IRQ_DEFNS {UART_IRQ_NUM}
macro_line|#else
DECL|macro|NR_PORTS
mdefine_line|#define NR_PORTS 2
DECL|macro|UART_IRQ_DEFNS
mdefine_line|#define UART_IRQ_DEFNS {UART1_IRQ_NUM, UART2_IRQ_NUM}
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* !(_MC683XX_SERIAL_H) */
eof
