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
DECL|macro|SERIAL_RECV_DESCRIPTORS
mdefine_line|#define SERIAL_RECV_DESCRIPTORS 8
DECL|struct|etrax_recv_buffer
r_struct
id|etrax_recv_buffer
(brace
DECL|member|next
r_struct
id|etrax_recv_buffer
op_star
id|next
suffix:semicolon
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
DECL|member|error
r_int
r_char
id|error
suffix:semicolon
DECL|member|pad
r_int
r_char
id|pad
suffix:semicolon
DECL|member|buffer
r_int
r_char
id|buffer
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
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
multiline_comment|/* Output registers */
DECL|member|oclrintradr
r_volatile
id|u8
op_star
id|oclrintradr
suffix:semicolon
multiline_comment|/* adr to R_DMA_CHx_CLR_INTR */
DECL|member|ofirstadr
r_volatile
id|u32
op_star
id|ofirstadr
suffix:semicolon
multiline_comment|/* adr to R_DMA_CHx_FIRST */
DECL|member|ocmdadr
r_volatile
id|u8
op_star
id|ocmdadr
suffix:semicolon
multiline_comment|/* adr to R_DMA_CHx_CMD */
DECL|member|ostatusadr
r_const
r_volatile
id|u8
op_star
id|ostatusadr
suffix:semicolon
multiline_comment|/* adr to R_DMA_CHx_STATUS */
multiline_comment|/* Input registers */
DECL|member|iclrintradr
r_volatile
id|u8
op_star
id|iclrintradr
suffix:semicolon
multiline_comment|/* adr to R_DMA_CHx_CLR_INTR */
DECL|member|ifirstadr
r_volatile
id|u32
op_star
id|ifirstadr
suffix:semicolon
multiline_comment|/* adr to R_DMA_CHx_FIRST */
DECL|member|icmdadr
r_volatile
id|u8
op_star
id|icmdadr
suffix:semicolon
multiline_comment|/* adr to R_DMA_CHx_CMD */
DECL|member|idescradr
r_volatile
id|u32
op_star
id|idescradr
suffix:semicolon
multiline_comment|/* adr to R_DMA_CHx_DESCR */
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
DECL|member|dma_out_enabled
id|u8
id|dma_out_enabled
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Set to 1 if DMA should be used */
DECL|member|dma_in_enabled
id|u8
id|dma_in_enabled
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Set to 1 if DMA should be used */
multiline_comment|/* end of fields defined in rs_table[] in .c-file */
DECL|member|uses_dma_in
id|u8
id|uses_dma_in
suffix:semicolon
multiline_comment|/* Set to 1 if DMA is used */
DECL|member|uses_dma_out
id|u8
id|uses_dma_out
suffix:semicolon
multiline_comment|/* Set to 1 if DMA is used */
DECL|member|forced_eop
id|u8
id|forced_eop
suffix:semicolon
multiline_comment|/* a fifo eop has been forced */
DECL|member|baud_base
r_int
id|baud_base
suffix:semicolon
multiline_comment|/* For special baudrates */
DECL|member|custom_divisor
r_int
id|custom_divisor
suffix:semicolon
multiline_comment|/* For special baudrates */
DECL|member|tr_descr
r_struct
id|etrax_dma_descr
id|tr_descr
suffix:semicolon
DECL|member|rec_descr
r_struct
id|etrax_dma_descr
id|rec_descr
(braket
id|SERIAL_RECV_DESCRIPTORS
)braket
suffix:semicolon
DECL|member|cur_rec_descr
r_int
id|cur_rec_descr
suffix:semicolon
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
DECL|member|xmit
r_struct
id|circ_buf
id|xmit
suffix:semicolon
DECL|member|first_recv_buffer
r_struct
id|etrax_recv_buffer
op_star
id|first_recv_buffer
suffix:semicolon
DECL|member|last_recv_buffer
r_struct
id|etrax_recv_buffer
op_star
id|last_recv_buffer
suffix:semicolon
DECL|member|recv_cnt
r_int
r_int
id|recv_cnt
suffix:semicolon
DECL|member|max_recv_cnt
r_int
r_int
id|max_recv_cnt
suffix:semicolon
DECL|member|work
r_struct
id|work_struct
id|work
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
DECL|member|char_time_usec
r_int
r_int
id|char_time_usec
suffix:semicolon
multiline_comment|/* The time for 1 char, in usecs */
DECL|member|flush_time_usec
r_int
r_int
id|flush_time_usec
suffix:semicolon
multiline_comment|/* How often we should flush */
DECL|member|last_tx_active_usec
r_int
r_int
id|last_tx_active_usec
suffix:semicolon
multiline_comment|/* Last tx usec in the jiffies */
DECL|member|last_tx_active
r_int
r_int
id|last_tx_active
suffix:semicolon
multiline_comment|/* Last tx time in jiffies */
DECL|member|last_rx_active_usec
r_int
r_int
id|last_rx_active_usec
suffix:semicolon
multiline_comment|/* Last rx usec in the jiffies */
DECL|member|last_rx_active
r_int
r_int
id|last_rx_active
suffix:semicolon
multiline_comment|/* Last rx time in jiffies */
DECL|member|break_detected_cnt
r_int
id|break_detected_cnt
suffix:semicolon
DECL|member|errorcode
r_int
id|errorcode
suffix:semicolon
macro_line|#ifdef CONFIG_ETRAX_RS485
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
macro_line|#endif /* !_ETRAX_SERIAL_H */
eof
