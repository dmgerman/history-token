multiline_comment|/*&n; * serial.h: Arch-dep definitions for the Etrax100 serial driver.&n; *&n; * Copyright (C) 1998, 1999, 2000 Axis Communications AB&n; */
macro_line|#ifndef _ETRAX_SERIAL_H
DECL|macro|_ETRAX_SERIAL_H
mdefine_line|#define _ETRAX_SERIAL_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/circ_buf.h&gt;
macro_line|#include &lt;asm/termios.h&gt;
multiline_comment|/* Software state per channel */
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * This is our internal structure for each serial port&squot;s state.&n; * &n; * Many fields are paralleled by the structure used by the serial_struct&n; * structure.&n; *&n; * For definitions of the flags field, see tty.h&n; */
DECL|struct|e100_serial
r_struct
id|e100_serial
(brace
DECL|member|baud
r_int
id|baud
suffix:semicolon
DECL|member|port
r_volatile
id|u8
op_star
id|port
suffix:semicolon
multiline_comment|/* R_SERIALx_CTRL */
DECL|member|irq
id|u32
id|irq
suffix:semicolon
multiline_comment|/* bitnr in R_IRQ_MASK2 for dmaX_descr */
DECL|member|oclrintradr
r_volatile
id|u8
op_star
id|oclrintradr
suffix:semicolon
multiline_comment|/* adr to R_DMA_CHx_CLR_INTR, output */
DECL|member|ofirstadr
r_volatile
id|u32
op_star
id|ofirstadr
suffix:semicolon
multiline_comment|/* adr to R_DMA_CHx_FIRST, output */
DECL|member|ocmdadr
r_volatile
id|u8
op_star
id|ocmdadr
suffix:semicolon
multiline_comment|/* adr to R_DMA_CHx_CMD, output */
DECL|member|ostatusadr
r_const
r_volatile
id|u8
op_star
id|ostatusadr
suffix:semicolon
multiline_comment|/* adr to R_DMA_CHx_STATUS, output */
DECL|member|ohwswadr
r_volatile
id|u32
op_star
id|ohwswadr
suffix:semicolon
multiline_comment|/* adr to R_DMA_CHx_HWSW, output */
DECL|member|iclrintradr
r_volatile
id|u8
op_star
id|iclrintradr
suffix:semicolon
multiline_comment|/* adr to R_DMA_CHx_CLR_INTR, input */
DECL|member|ifirstadr
r_volatile
id|u32
op_star
id|ifirstadr
suffix:semicolon
multiline_comment|/* adr to R_DMA_CHx_FIRST, input */
DECL|member|icmdadr
r_volatile
id|u8
op_star
id|icmdadr
suffix:semicolon
multiline_comment|/* adr to R_DMA_CHx_CMD, input */
DECL|member|istatusadr
r_const
r_volatile
id|u8
op_star
id|istatusadr
suffix:semicolon
multiline_comment|/* adr to R_DMA_CHx_STATUS, input */
DECL|member|ihwswadr
r_volatile
id|u32
op_star
id|ihwswadr
suffix:semicolon
multiline_comment|/* adr to R_DMA_CHx_HWSW, input */
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* defined in tty.h */
DECL|member|rx_ctrl
id|u8
id|rx_ctrl
suffix:semicolon
multiline_comment|/* shadow for R_SERIALx_REC_CTRL */
DECL|member|tx_ctrl
id|u8
id|tx_ctrl
suffix:semicolon
multiline_comment|/* shadow for R_SERIALx_TR_CTRL */
DECL|member|iseteop
id|u8
id|iseteop
suffix:semicolon
multiline_comment|/* bit number for R_SET_EOP for the input dma */
DECL|member|enabled
r_int
id|enabled
suffix:semicolon
multiline_comment|/* Set to 1 if the port is enabled in HW config */
multiline_comment|/* end of fields defined in rs_table[] in .c-file */
DECL|member|uses_dma
r_int
id|uses_dma
suffix:semicolon
multiline_comment|/* Set to 1 if DMA should be used */
DECL|member|fifo_didmagic
r_int
r_char
id|fifo_didmagic
suffix:semicolon
multiline_comment|/* a fifo eop has been forced */
DECL|member|tr_descr
DECL|member|rec_descr
r_struct
id|etrax_dma_descr
id|tr_descr
comma
id|rec_descr
suffix:semicolon
DECL|member|fifo_magic
r_int
id|fifo_magic
suffix:semicolon
multiline_comment|/* fifo amount - bytes left in dma buffer */
DECL|member|tr_running
r_volatile
r_int
id|tr_running
suffix:semicolon
multiline_comment|/* 1 if output is running */
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
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* PORT_ETRAX */
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
DECL|member|xmit
r_struct
id|circ_buf
id|xmit
suffix:semicolon
DECL|member|tqueue
r_struct
id|tq_struct
id|tqueue
suffix:semicolon
DECL|member|icount
r_struct
id|async_icount
id|icount
suffix:semicolon
multiline_comment|/* error-statistics etc.*/
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
macro_line|#ifdef DECLARE_WAITQUEUE
DECL|member|open_wait
id|wait_queue_head_t
id|open_wait
suffix:semicolon
DECL|member|close_wait
id|wait_queue_head_t
id|close_wait
suffix:semicolon
macro_line|#else   
DECL|member|open_wait
r_struct
id|wait_queue
op_star
id|open_wait
suffix:semicolon
DECL|member|close_wait
r_struct
id|wait_queue
op_star
id|close_wait
suffix:semicolon
macro_line|#endif  
macro_line|#ifdef CONFIG_RS485
DECL|member|rs485
r_struct
id|rs485_control
id|rs485
suffix:semicolon
multiline_comment|/* RS-485 support */
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* this PORT is not in the standard serial.h. it&squot;s not actually used for&n; * anything since we only have one type of async serial-port anyway in this&n; * system.&n; */
DECL|macro|PORT_ETRAX
mdefine_line|#define PORT_ETRAX 1
multiline_comment|/*&n; * Events are used to schedule things to happen at timer-interrupt&n; * time, instead of at rs interrupt time.&n; */
DECL|macro|RS_EVENT_WRITE_WAKEUP
mdefine_line|#define RS_EVENT_WRITE_WAKEUP&t;0
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* !(_ETRAX_SERIAL_H) */
eof
