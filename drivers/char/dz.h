multiline_comment|/*&n; * dz.h: Serial port driver for DECStations equiped &n; *       with the DZ chipset.&n; *&n; * Copyright (C) 1998 Olivier A. D. Lebaillif &n; *             &n; * Email: olivier.lebaillif@ifrsys.com&n; *&n; */
macro_line|#ifndef DZ_SERIAL_H
DECL|macro|DZ_SERIAL_H
mdefine_line|#define DZ_SERIAL_H
multiline_comment|/*&n; * Definitions for the Control and Status Received.&n; */
DECL|macro|DZ_TRDY
mdefine_line|#define DZ_TRDY        0x8000                 /* Transmitter empty */
DECL|macro|DZ_TIE
mdefine_line|#define DZ_TIE         0x4000                 /* Transmitter Interrupt Enable */
DECL|macro|DZ_RDONE
mdefine_line|#define DZ_RDONE       0x0080                 /* Receiver data ready */
DECL|macro|DZ_RIE
mdefine_line|#define DZ_RIE         0x0040                 /* Receive Interrupt Enable */
DECL|macro|DZ_MSE
mdefine_line|#define DZ_MSE         0x0020                 /* Master Scan Enable */
DECL|macro|DZ_CLR
mdefine_line|#define DZ_CLR         0x0010                 /* Master reset */
DECL|macro|DZ_MAINT
mdefine_line|#define DZ_MAINT       0x0008                 /* Loop Back Mode */
multiline_comment|/*&n; * Definitions for the Received buffer. &n; */
DECL|macro|DZ_RBUF_MASK
mdefine_line|#define DZ_RBUF_MASK   0x00FF                 /* Data Mask in the Receive Buffer */
DECL|macro|DZ_LINE_MASK
mdefine_line|#define DZ_LINE_MASK   0x0300                 /* Line Mask in the Receive Buffer */
DECL|macro|DZ_DVAL
mdefine_line|#define DZ_DVAL        0x8000                 /* Valid Data indicator */
DECL|macro|DZ_OERR
mdefine_line|#define DZ_OERR        0x4000                 /* Overrun error indicator */
DECL|macro|DZ_FERR
mdefine_line|#define DZ_FERR        0x2000                 /* Frame error indicator */
DECL|macro|DZ_PERR
mdefine_line|#define DZ_PERR        0x1000                 /* Parity error indicator */
DECL|macro|LINE
mdefine_line|#define LINE(x) (x &amp; DZ_LINE_MASK) &gt;&gt; 8       /* Get the line number from the input buffer */
DECL|macro|UCHAR
mdefine_line|#define UCHAR(x) (unsigned char)(x &amp; DZ_RBUF_MASK)
multiline_comment|/*&n; * Definitions for the Transmit Register.&n; */
DECL|macro|DZ_LINE_KEYBOARD
mdefine_line|#define DZ_LINE_KEYBOARD 0x0001
DECL|macro|DZ_LINE_MOUSE
mdefine_line|#define DZ_LINE_MOUSE    0x0002
DECL|macro|DZ_LINE_MODEM
mdefine_line|#define DZ_LINE_MODEM    0x0004
DECL|macro|DZ_LINE_PRINTER
mdefine_line|#define DZ_LINE_PRINTER  0x0008
DECL|macro|DZ_MODEM_DTR
mdefine_line|#define DZ_MODEM_DTR     0x0400               /* DTR for the modem line (2) */
multiline_comment|/*&n; * Definitions for the Modem Status Register.&n; */
DECL|macro|DZ_MODEM_DSR
mdefine_line|#define DZ_MODEM_DSR     0x0200               /* DSR for the modem line (2) */
multiline_comment|/*&n; * Definitions for the Transmit Data Register.&n; */
DECL|macro|DZ_BRK0
mdefine_line|#define DZ_BRK0          0x0100               /* Break assertion for line 0 */
DECL|macro|DZ_BRK1
mdefine_line|#define DZ_BRK1          0x0200               /* Break assertion for line 1 */
DECL|macro|DZ_BRK2
mdefine_line|#define DZ_BRK2          0x0400               /* Break assertion for line 2 */
DECL|macro|DZ_BRK3
mdefine_line|#define DZ_BRK3          0x0800               /* Break assertion for line 3 */
multiline_comment|/*&n; * Definitions for the Line Parameter Register.&n; */
DECL|macro|DZ_KEYBOARD
mdefine_line|#define DZ_KEYBOARD      0x0000               /* line 0 = keyboard */
DECL|macro|DZ_MOUSE
mdefine_line|#define DZ_MOUSE         0x0001               /* line 1 = mouse */
DECL|macro|DZ_MODEM
mdefine_line|#define DZ_MODEM         0x0002               /* line 2 = modem */
DECL|macro|DZ_PRINTER
mdefine_line|#define DZ_PRINTER       0x0003               /* line 3 = printer */
DECL|macro|DZ_CSIZE
mdefine_line|#define DZ_CSIZE         0x0018               /* Number of bits per byte (mask) */
DECL|macro|DZ_CS5
mdefine_line|#define DZ_CS5           0x0000               /* 5 bits per byte */
DECL|macro|DZ_CS6
mdefine_line|#define DZ_CS6           0x0008               /* 6 bits per byte */
DECL|macro|DZ_CS7
mdefine_line|#define DZ_CS7           0x0010               /* 7 bits per byte */
DECL|macro|DZ_CS8
mdefine_line|#define DZ_CS8           0x0018               /* 8 bits per byte */
DECL|macro|DZ_CSTOPB
mdefine_line|#define DZ_CSTOPB        0x0020               /* 2 stop bits instead of one */ 
DECL|macro|DZ_PARENB
mdefine_line|#define DZ_PARENB        0x0040               /* Parity enable */
DECL|macro|DZ_PARODD
mdefine_line|#define DZ_PARODD        0x0080               /* Odd parity instead of even */
DECL|macro|DZ_CBAUD
mdefine_line|#define DZ_CBAUD         0x0E00               /* Baud Rate (mask) */
DECL|macro|DZ_B50
mdefine_line|#define DZ_B50           0x0000
DECL|macro|DZ_B75
mdefine_line|#define DZ_B75           0x0100
DECL|macro|DZ_B110
mdefine_line|#define DZ_B110          0x0200
DECL|macro|DZ_B134
mdefine_line|#define DZ_B134          0x0300
DECL|macro|DZ_B150
mdefine_line|#define DZ_B150          0x0400
DECL|macro|DZ_B300
mdefine_line|#define DZ_B300          0x0500
DECL|macro|DZ_B600
mdefine_line|#define DZ_B600          0x0600
DECL|macro|DZ_B1200
mdefine_line|#define DZ_B1200         0x0700 
DECL|macro|DZ_B1800
mdefine_line|#define DZ_B1800         0x0800
DECL|macro|DZ_B2000
mdefine_line|#define DZ_B2000         0x0900
DECL|macro|DZ_B2400
mdefine_line|#define DZ_B2400         0x0A00
DECL|macro|DZ_B3600
mdefine_line|#define DZ_B3600         0x0B00
DECL|macro|DZ_B4800
mdefine_line|#define DZ_B4800         0x0C00
DECL|macro|DZ_B7200
mdefine_line|#define DZ_B7200         0x0D00
DECL|macro|DZ_B9600
mdefine_line|#define DZ_B9600         0x0E00
DECL|macro|DZ_CREAD
mdefine_line|#define DZ_CREAD         0x1000               /* Enable receiver */
DECL|macro|DZ_RXENAB
mdefine_line|#define DZ_RXENAB        0x1000               /* enable receive char */
multiline_comment|/*&n; * Addresses for the DZ registers&n; */
DECL|macro|DZ_CSR
mdefine_line|#define DZ_CSR       0x00            /* Control and Status Register */
DECL|macro|DZ_RBUF
mdefine_line|#define DZ_RBUF      0x08            /* Receive Buffer */
DECL|macro|DZ_LPR
mdefine_line|#define DZ_LPR       0x08            /* Line Parameters Register */
DECL|macro|DZ_TCR
mdefine_line|#define DZ_TCR       0x10            /* Transmitter Control Register */
DECL|macro|DZ_MSR
mdefine_line|#define DZ_MSR       0x18            /* Modem Status Register */
DECL|macro|DZ_TDR
mdefine_line|#define DZ_TDR       0x18            /* Transmit Data Register */
DECL|macro|DZ_NB_PORT
mdefine_line|#define DZ_NB_PORT 4
DECL|macro|DZ_XMIT_SIZE
mdefine_line|#define DZ_XMIT_SIZE   4096                 /* buffer size */
DECL|macro|WAKEUP_CHARS
mdefine_line|#define WAKEUP_CHARS   DZ_XMIT_SIZE/4
DECL|macro|DZ_EVENT_WRITE_WAKEUP
mdefine_line|#define DZ_EVENT_WRITE_WAKEUP   0
macro_line|#ifndef MIN
DECL|macro|MIN
mdefine_line|#define MIN(a,b)        ((a) &lt; (b) ? (a) : (b))
DECL|macro|DZ_INITIALIZED
mdefine_line|#define DZ_INITIALIZED       0x80000000 /* Serial port was initialized */
DECL|macro|DZ_CALLOUT_ACTIVE
mdefine_line|#define DZ_CALLOUT_ACTIVE    0x40000000 /* Call out device is active */
DECL|macro|DZ_NORMAL_ACTIVE
mdefine_line|#define DZ_NORMAL_ACTIVE     0x20000000 /* Normal device is active */
DECL|macro|DZ_BOOT_AUTOCONF
mdefine_line|#define DZ_BOOT_AUTOCONF     0x10000000 /* Autoconfigure port on bootup */
DECL|macro|DZ_CLOSING
mdefine_line|#define DZ_CLOSING           0x08000000 /* Serial port is closing */
DECL|macro|DZ_CTS_FLOW
mdefine_line|#define DZ_CTS_FLOW          0x04000000 /* Do CTS flow control */
DECL|macro|DZ_CHECK_CD
mdefine_line|#define DZ_CHECK_CD          0x02000000 /* i.e., CLOCAL */
DECL|macro|DZ_CLOSING_WAIT_INF
mdefine_line|#define DZ_CLOSING_WAIT_INF  0
DECL|macro|DZ_CLOSING_WAIT_NONE
mdefine_line|#define DZ_CLOSING_WAIT_NONE 65535
DECL|macro|DZ_SPLIT_TERMIOS
mdefine_line|#define DZ_SPLIT_TERMIOS   0x0008 /* Separate termios for dialin/callout */
DECL|macro|DZ_SESSION_LOCKOUT
mdefine_line|#define DZ_SESSION_LOCKOUT 0x0100 /* Lock out cua opens based on session */
DECL|macro|DZ_PGRP_LOCKOUT
mdefine_line|#define DZ_PGRP_LOCKOUT    0x0200 /* Lock out cua opens based on pgrp */
DECL|struct|dz_serial
r_struct
id|dz_serial
(brace
DECL|member|port
r_int
id|port
suffix:semicolon
multiline_comment|/* base address for the port */
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|baud_base
r_int
id|baud_base
suffix:semicolon
DECL|member|blocked_open
r_int
id|blocked_open
suffix:semicolon
DECL|member|close_delay
r_int
r_int
id|close_delay
suffix:semicolon
DECL|member|closing_wait
r_int
r_int
id|closing_wait
suffix:semicolon
DECL|member|line
r_int
r_int
id|line
suffix:semicolon
multiline_comment|/* port/line number */
DECL|member|cflags
r_int
r_int
id|cflags
suffix:semicolon
multiline_comment|/* line configuration flag */
DECL|member|x_char
r_int
r_int
id|x_char
suffix:semicolon
multiline_comment|/* xon/xoff character */
DECL|member|read_status_mask
r_int
r_int
id|read_status_mask
suffix:semicolon
multiline_comment|/* mask for read condition */
DECL|member|ignore_status_mask
r_int
r_int
id|ignore_status_mask
suffix:semicolon
multiline_comment|/* mask for ignore condition */
DECL|member|event
r_int
r_int
id|event
suffix:semicolon
multiline_comment|/* mask used in BH */
DECL|member|xmit_buf
r_int
r_char
op_star
id|xmit_buf
suffix:semicolon
multiline_comment|/* Transmit buffer */
DECL|member|xmit_head
r_int
id|xmit_head
suffix:semicolon
multiline_comment|/* Position of the head */
DECL|member|xmit_tail
r_int
id|xmit_tail
suffix:semicolon
multiline_comment|/* Position of the tail */
DECL|member|xmit_cnt
r_int
id|xmit_cnt
suffix:semicolon
multiline_comment|/* Count of the chars in the buffer */
DECL|member|count
r_int
id|count
suffix:semicolon
multiline_comment|/* indicates how many times it has been opened */
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|icount
r_struct
id|async_icount
id|icount
suffix:semicolon
multiline_comment|/* keep track of things ... */
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
multiline_comment|/* tty associated */
DECL|member|tqueue
r_struct
id|tq_struct
id|tqueue
suffix:semicolon
multiline_comment|/* Queue for BH */
DECL|member|tqueue_hangup
r_struct
id|tq_struct
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
DECL|member|is_console
r_int
r_char
id|is_console
suffix:semicolon
multiline_comment|/* flag indicating a serial console */
DECL|member|is_initialized
r_int
r_char
id|is_initialized
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|multi
r_static
r_struct
id|dz_serial
id|multi
(braket
id|DZ_NB_PORT
)braket
suffix:semicolon
multiline_comment|/* Four serial lines in the DZ chip */
DECL|variable|dz_console
r_static
r_struct
id|dz_serial
op_star
id|dz_console
suffix:semicolon
DECL|variable|serial_driver
DECL|variable|callout_driver
r_static
r_struct
id|tty_driver
id|serial_driver
comma
id|callout_driver
suffix:semicolon
DECL|variable|serial_table
r_static
r_struct
id|tty_struct
op_star
id|serial_table
(braket
id|DZ_NB_PORT
)braket
suffix:semicolon
DECL|variable|serial_termios
r_static
r_struct
id|termios
op_star
id|serial_termios
(braket
id|DZ_NB_PORT
)braket
suffix:semicolon
DECL|variable|serial_termios_locked
r_static
r_struct
id|termios
op_star
id|serial_termios_locked
(braket
id|DZ_NB_PORT
)braket
suffix:semicolon
DECL|variable|serial_refcount
r_static
r_int
id|serial_refcount
suffix:semicolon
multiline_comment|/*&n; * tmp_buf is used as a temporary buffer by serial_write.  We need to&n; * lock it in case the copy_from_user blocks while swapping in a page,&n; * and some other program tries to do a serial write at the same time.&n; * Since the lock will only come under contention when the system is&n; * swapping and available memory is low, it makes sense to share one&n; * buffer across all the serial ports, since it significantly saves&n; * memory if large numbers of serial ports are open.&n; */
DECL|variable|tmp_buf
r_static
r_int
r_char
op_star
id|tmp_buf
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|tmp_buf_sem
)paren
suffix:semicolon
DECL|variable|dz_name
r_static
r_char
op_star
id|dz_name
op_assign
l_string|&quot;DECstation DZ serial driver version &quot;
suffix:semicolon
DECL|variable|dz_version
r_static
r_char
op_star
id|dz_version
op_assign
l_string|&quot;1.02&quot;
suffix:semicolon
r_static
r_inline
r_int
r_int
id|dz_in
(paren
r_struct
id|dz_serial
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_inline
r_void
id|dz_out
(paren
r_struct
id|dz_serial
op_star
comma
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_static
r_inline
r_void
id|dz_sched_event
(paren
r_struct
id|dz_serial
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_inline
r_void
id|receive_chars
(paren
r_struct
id|dz_serial
op_star
)paren
suffix:semicolon
r_static
r_inline
r_void
id|transmit_chars
(paren
r_struct
id|dz_serial
op_star
)paren
suffix:semicolon
r_static
r_inline
r_void
id|check_modem_status
(paren
r_struct
id|dz_serial
op_star
)paren
suffix:semicolon
r_static
r_void
id|dz_stop
(paren
r_struct
id|tty_struct
op_star
)paren
suffix:semicolon
r_static
r_void
id|dz_start
(paren
r_struct
id|tty_struct
op_star
)paren
suffix:semicolon
r_static
r_void
id|dz_interrupt
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_static
r_void
id|do_serial_bh
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|do_softint
(paren
r_void
op_star
)paren
suffix:semicolon
r_static
r_void
id|do_serial_hangup
(paren
r_void
op_star
)paren
suffix:semicolon
r_static
r_void
id|change_speed
(paren
r_struct
id|dz_serial
op_star
)paren
suffix:semicolon
r_static
r_void
id|dz_flush_chars
(paren
r_struct
id|tty_struct
op_star
)paren
suffix:semicolon
r_static
r_void
id|dz_console_print
(paren
r_struct
id|console
op_star
comma
r_const
r_char
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
id|dz_flush_buffer
(paren
r_struct
id|tty_struct
op_star
)paren
suffix:semicolon
r_static
r_void
id|dz_throttle
(paren
r_struct
id|tty_struct
op_star
)paren
suffix:semicolon
r_static
r_void
id|dz_unthrottle
(paren
r_struct
id|tty_struct
op_star
)paren
suffix:semicolon
r_static
r_void
id|dz_send_xchar
(paren
r_struct
id|tty_struct
op_star
comma
r_char
)paren
suffix:semicolon
r_static
r_void
id|shutdown
(paren
r_struct
id|dz_serial
op_star
)paren
suffix:semicolon
r_static
r_void
id|send_break
(paren
r_struct
id|dz_serial
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_void
id|dz_set_termios
(paren
r_struct
id|tty_struct
op_star
comma
r_struct
id|termios
op_star
)paren
suffix:semicolon
r_static
r_void
id|dz_close
(paren
r_struct
id|tty_struct
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_static
r_void
id|dz_hangup
(paren
r_struct
id|tty_struct
op_star
)paren
suffix:semicolon
r_static
r_void
id|show_serial_version
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|dz_write
(paren
r_struct
id|tty_struct
op_star
comma
r_int
comma
r_const
r_int
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|dz_write_room
(paren
r_struct
id|tty_struct
op_star
)paren
suffix:semicolon
r_static
r_int
id|dz_chars_in_buffer
(paren
r_struct
id|tty_struct
op_star
)paren
suffix:semicolon
r_static
r_int
id|startup
(paren
r_struct
id|dz_serial
op_star
)paren
suffix:semicolon
r_static
r_int
id|get_serial_info
(paren
r_struct
id|dz_serial
op_star
comma
r_struct
id|serial_struct
op_star
)paren
suffix:semicolon
r_static
r_int
id|set_serial_info
(paren
r_struct
id|dz_serial
op_star
comma
r_struct
id|serial_struct
op_star
)paren
suffix:semicolon
r_static
r_int
id|get_lsr_info
(paren
r_struct
id|dz_serial
op_star
comma
r_int
r_int
op_star
)paren
suffix:semicolon
r_static
r_int
id|dz_ioctl
(paren
r_struct
id|tty_struct
op_star
comma
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_static
r_int
id|block_til_ready
(paren
r_struct
id|tty_struct
op_star
comma
r_struct
id|file
op_star
comma
r_struct
id|dz_serial
op_star
)paren
suffix:semicolon
r_static
r_int
id|dz_open
(paren
r_struct
id|tty_struct
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
macro_line|#ifdef MODULE
r_int
id|init_module
(paren
r_void
)paren
r_void
id|cleanup_module
(paren
r_void
)paren
macro_line|#endif
macro_line|#endif
macro_line|#endif /* DZ_SERIAL_H */
eof
