multiline_comment|/* $Id: sab82532.h,v 1.7 2001/05/23 23:09:10 ecd Exp $&n; * sab82532.h: Register Definitions for the Siemens SAB82532 DUSCC&n; *&n; * Copyright (C) 1997  Eddie C. Dost  (ecd@skynet.be)&n; */
macro_line|#ifndef _SPARC64_SAB82532_H
DECL|macro|_SPARC64_SAB82532_H
mdefine_line|#define _SPARC64_SAB82532_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/circ_buf.h&gt;
DECL|struct|sab82532_async_rd_regs
r_struct
id|sab82532_async_rd_regs
(brace
DECL|member|rfifo
id|u8
id|rfifo
(braket
l_int|0x20
)braket
suffix:semicolon
multiline_comment|/* Receive FIFO&t;&t;&t;&t;*/
DECL|member|star
id|u8
id|star
suffix:semicolon
multiline_comment|/* Status Register&t;&t;&t;*/
DECL|member|__pad1
id|u8
id|__pad1
suffix:semicolon
DECL|member|mode
id|u8
id|mode
suffix:semicolon
multiline_comment|/* Mode Register&t;&t;&t;*/
DECL|member|timr
id|u8
id|timr
suffix:semicolon
multiline_comment|/* Timer Register&t;&t;&t;*/
DECL|member|xon
id|u8
id|xon
suffix:semicolon
multiline_comment|/* XON Character&t;&t;&t;*/
DECL|member|xoff
id|u8
id|xoff
suffix:semicolon
multiline_comment|/* XOFF Character&t;&t;&t;*/
DECL|member|tcr
id|u8
id|tcr
suffix:semicolon
multiline_comment|/* Termination Character Register&t;*/
DECL|member|dafo
id|u8
id|dafo
suffix:semicolon
multiline_comment|/* Data Format&t;&t;&t;&t;*/
DECL|member|rfc
id|u8
id|rfc
suffix:semicolon
multiline_comment|/* RFIFO Control Register&t;&t;*/
DECL|member|__pad2
id|u8
id|__pad2
suffix:semicolon
DECL|member|rbcl
id|u8
id|rbcl
suffix:semicolon
multiline_comment|/* Receive Byte Count Low&t;&t;*/
DECL|member|rbch
id|u8
id|rbch
suffix:semicolon
multiline_comment|/* Receive Byte Count High&t;&t;*/
DECL|member|ccr0
id|u8
id|ccr0
suffix:semicolon
multiline_comment|/* Channel Configuration Register 0&t;*/
DECL|member|ccr1
id|u8
id|ccr1
suffix:semicolon
multiline_comment|/* Channel Configuration Register 1&t;*/
DECL|member|ccr2
id|u8
id|ccr2
suffix:semicolon
multiline_comment|/* Channel Configuration Register 2&t;*/
DECL|member|ccr3
id|u8
id|ccr3
suffix:semicolon
multiline_comment|/* Channel Configuration Register 3&t;*/
DECL|member|__pad3
id|u8
id|__pad3
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|vstr
id|u8
id|vstr
suffix:semicolon
multiline_comment|/* Version Status Register&t;&t;*/
DECL|member|__pad4
id|u8
id|__pad4
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|gis
id|u8
id|gis
suffix:semicolon
multiline_comment|/* Global Interrupt Status&t;&t;*/
DECL|member|ipc
id|u8
id|ipc
suffix:semicolon
multiline_comment|/* Interrupt Port Configuration&t;&t;*/
DECL|member|isr0
id|u8
id|isr0
suffix:semicolon
multiline_comment|/* Interrupt Status 0&t;&t;&t;*/
DECL|member|isr1
id|u8
id|isr1
suffix:semicolon
multiline_comment|/* Interrupt Status 1&t;&t;&t;*/
DECL|member|pvr
id|u8
id|pvr
suffix:semicolon
multiline_comment|/* Port Value Register&t;&t;&t;*/
DECL|member|pis
id|u8
id|pis
suffix:semicolon
multiline_comment|/* Port Interrupt Status&t;&t;*/
DECL|member|pcr
id|u8
id|pcr
suffix:semicolon
multiline_comment|/* Port Configuration Register&t;&t;*/
DECL|member|ccr4
id|u8
id|ccr4
suffix:semicolon
multiline_comment|/* Channel Configuration Register 4&t;*/
)brace
suffix:semicolon
DECL|struct|sab82532_async_wr_regs
r_struct
id|sab82532_async_wr_regs
(brace
DECL|member|xfifo
id|u8
id|xfifo
(braket
l_int|0x20
)braket
suffix:semicolon
multiline_comment|/* Transmit FIFO&t;&t;&t;*/
DECL|member|cmdr
id|u8
id|cmdr
suffix:semicolon
multiline_comment|/* Command Register&t;&t;&t;*/
DECL|member|__pad1
id|u8
id|__pad1
suffix:semicolon
DECL|member|mode
id|u8
id|mode
suffix:semicolon
DECL|member|timr
id|u8
id|timr
suffix:semicolon
DECL|member|xon
id|u8
id|xon
suffix:semicolon
DECL|member|xoff
id|u8
id|xoff
suffix:semicolon
DECL|member|tcr
id|u8
id|tcr
suffix:semicolon
DECL|member|dafo
id|u8
id|dafo
suffix:semicolon
DECL|member|rfc
id|u8
id|rfc
suffix:semicolon
DECL|member|__pad2
id|u8
id|__pad2
suffix:semicolon
DECL|member|xbcl
id|u8
id|xbcl
suffix:semicolon
multiline_comment|/* Transmit Byte Count Low&t;&t;*/
DECL|member|xbch
id|u8
id|xbch
suffix:semicolon
multiline_comment|/* Transmit Byte Count High&t;&t;*/
DECL|member|ccr0
id|u8
id|ccr0
suffix:semicolon
DECL|member|ccr1
id|u8
id|ccr1
suffix:semicolon
DECL|member|ccr2
id|u8
id|ccr2
suffix:semicolon
DECL|member|ccr3
id|u8
id|ccr3
suffix:semicolon
DECL|member|tsax
id|u8
id|tsax
suffix:semicolon
multiline_comment|/* Time-Slot Assignment Reg. Transmit&t;*/
DECL|member|tsar
id|u8
id|tsar
suffix:semicolon
multiline_comment|/* Time-Slot Assignment Reg. Receive&t;*/
DECL|member|xccr
id|u8
id|xccr
suffix:semicolon
multiline_comment|/* Transmit Channel Capacity Register&t;*/
DECL|member|rccr
id|u8
id|rccr
suffix:semicolon
multiline_comment|/* Receive Channel Capacity Register&t;*/
DECL|member|bgr
id|u8
id|bgr
suffix:semicolon
multiline_comment|/* Baud Rate Generator Register&t;&t;*/
DECL|member|tic
id|u8
id|tic
suffix:semicolon
multiline_comment|/* Transmit Immediate Character&t;&t;*/
DECL|member|mxn
id|u8
id|mxn
suffix:semicolon
multiline_comment|/* Mask XON Character&t;&t;&t;*/
DECL|member|mxf
id|u8
id|mxf
suffix:semicolon
multiline_comment|/* Mask XOFF Character&t;&t;&t;*/
DECL|member|iva
id|u8
id|iva
suffix:semicolon
multiline_comment|/* Interrupt Vector Address&t;&t;*/
DECL|member|ipc
id|u8
id|ipc
suffix:semicolon
DECL|member|imr0
id|u8
id|imr0
suffix:semicolon
multiline_comment|/* Interrupt Mask Register 0&t;&t;*/
DECL|member|imr1
id|u8
id|imr1
suffix:semicolon
multiline_comment|/* Interrupt Mask Register 1&t;&t;*/
DECL|member|pvr
id|u8
id|pvr
suffix:semicolon
DECL|member|pim
id|u8
id|pim
suffix:semicolon
multiline_comment|/* Port Interrupt Mask&t;&t;&t;*/
DECL|member|pcr
id|u8
id|pcr
suffix:semicolon
DECL|member|ccr4
id|u8
id|ccr4
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sab82532_async_rw_regs
r_struct
id|sab82532_async_rw_regs
(brace
multiline_comment|/* Read/Write registers&t;&t;&t;*/
DECL|member|__pad1
id|u8
id|__pad1
(braket
l_int|0x20
)braket
suffix:semicolon
DECL|member|__pad2
id|u8
id|__pad2
suffix:semicolon
DECL|member|__pad3
id|u8
id|__pad3
suffix:semicolon
DECL|member|mode
id|u8
id|mode
suffix:semicolon
DECL|member|timr
id|u8
id|timr
suffix:semicolon
DECL|member|xon
id|u8
id|xon
suffix:semicolon
DECL|member|xoff
id|u8
id|xoff
suffix:semicolon
DECL|member|tcr
id|u8
id|tcr
suffix:semicolon
DECL|member|dafo
id|u8
id|dafo
suffix:semicolon
DECL|member|rfc
id|u8
id|rfc
suffix:semicolon
DECL|member|__pad4
id|u8
id|__pad4
suffix:semicolon
DECL|member|__pad5
id|u8
id|__pad5
suffix:semicolon
DECL|member|__pad6
id|u8
id|__pad6
suffix:semicolon
DECL|member|ccr0
id|u8
id|ccr0
suffix:semicolon
DECL|member|ccr1
id|u8
id|ccr1
suffix:semicolon
DECL|member|ccr2
id|u8
id|ccr2
suffix:semicolon
DECL|member|ccr3
id|u8
id|ccr3
suffix:semicolon
DECL|member|__pad7
id|u8
id|__pad7
suffix:semicolon
DECL|member|__pad8
id|u8
id|__pad8
suffix:semicolon
DECL|member|__pad9
id|u8
id|__pad9
suffix:semicolon
DECL|member|__pad10
id|u8
id|__pad10
suffix:semicolon
DECL|member|__pad11
id|u8
id|__pad11
suffix:semicolon
DECL|member|__pad12
id|u8
id|__pad12
suffix:semicolon
DECL|member|__pad13
id|u8
id|__pad13
suffix:semicolon
DECL|member|__pad14
id|u8
id|__pad14
suffix:semicolon
DECL|member|__pad15
id|u8
id|__pad15
suffix:semicolon
DECL|member|ipc
id|u8
id|ipc
suffix:semicolon
DECL|member|__pad16
id|u8
id|__pad16
suffix:semicolon
DECL|member|__pad17
id|u8
id|__pad17
suffix:semicolon
DECL|member|pvr
id|u8
id|pvr
suffix:semicolon
DECL|member|__pad18
id|u8
id|__pad18
suffix:semicolon
DECL|member|pcr
id|u8
id|pcr
suffix:semicolon
DECL|member|ccr4
id|u8
id|ccr4
suffix:semicolon
)brace
suffix:semicolon
DECL|union|sab82532_async_regs
r_union
id|sab82532_async_regs
(brace
DECL|member|r
id|__volatile__
r_struct
id|sab82532_async_rd_regs
id|r
suffix:semicolon
DECL|member|w
id|__volatile__
r_struct
id|sab82532_async_wr_regs
id|w
suffix:semicolon
DECL|member|rw
id|__volatile__
r_struct
id|sab82532_async_rw_regs
id|rw
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NR_PORTS
mdefine_line|#define NR_PORTS&t;&t;&t; 2
DECL|union|sab82532_irq_status
r_union
id|sab82532_irq_status
(brace
DECL|member|stat
r_int
r_int
id|stat
suffix:semicolon
r_struct
(brace
DECL|member|isr0
r_int
r_char
id|isr0
suffix:semicolon
DECL|member|isr1
r_int
r_char
id|isr1
suffix:semicolon
DECL|member|sreg
)brace
id|sreg
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sab82532
r_struct
id|sab82532
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|baud_base
r_int
id|baud_base
suffix:semicolon
DECL|member|regs
r_union
id|sab82532_async_regs
op_star
id|regs
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
multiline_comment|/* SAB82532 version */
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
DECL|member|recv_fifo_size
r_int
id|recv_fifo_size
suffix:semicolon
DECL|member|custom_divisor
r_int
id|custom_divisor
suffix:semicolon
DECL|member|baud
r_int
id|baud
suffix:semicolon
DECL|member|cec_timeout
r_int
r_int
id|cec_timeout
suffix:semicolon
DECL|member|tec_timeout
r_int
r_int
id|tec_timeout
suffix:semicolon
DECL|member|x_char
r_int
id|x_char
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
DECL|member|irqflags
r_int
r_int
id|irqflags
suffix:semicolon
DECL|member|is_console
r_int
id|is_console
suffix:semicolon
DECL|member|interrupt_mask0
r_int
r_char
id|interrupt_mask0
suffix:semicolon
DECL|member|interrupt_mask1
r_int
r_char
id|interrupt_mask1
suffix:semicolon
DECL|member|pvr_dtr_bit
r_int
r_char
id|pvr_dtr_bit
suffix:semicolon
DECL|member|pvr_dsr_bit
r_int
r_char
id|pvr_dsr_bit
suffix:semicolon
DECL|member|dcd
r_int
r_char
id|dcd
suffix:semicolon
DECL|member|cts
r_int
r_char
id|cts
suffix:semicolon
DECL|member|dsr
r_int
r_char
id|dsr
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
DECL|member|blocked_open
r_int
id|blocked_open
suffix:semicolon
DECL|member|session
r_int
id|session
suffix:semicolon
DECL|member|pgrp
r_int
id|pgrp
suffix:semicolon
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
DECL|member|tqueue_hangup
r_struct
id|tq_struct
id|tqueue_hangup
suffix:semicolon
DECL|member|icount
r_struct
id|async_icount
id|icount
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
DECL|member|delta_msr_wait
id|wait_queue_head_t
id|delta_msr_wait
suffix:semicolon
DECL|member|next
r_struct
id|sab82532
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|sab82532
op_star
id|prev
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* irqflags bits */
DECL|macro|SAB82532_ALLS
mdefine_line|#define SAB82532_ALLS&t;&t;&t;0x00000001
DECL|macro|SAB82532_XPR
mdefine_line|#define SAB82532_XPR&t;&t;&t;0x00000002
multiline_comment|/* RFIFO Status Byte */
DECL|macro|SAB82532_RSTAT_PE
mdefine_line|#define SAB82532_RSTAT_PE&t;&t;0x80
DECL|macro|SAB82532_RSTAT_FE
mdefine_line|#define SAB82532_RSTAT_FE&t;&t;0x40
DECL|macro|SAB82532_RSTAT_PARITY
mdefine_line|#define SAB82532_RSTAT_PARITY&t;&t;0x01
multiline_comment|/* Status Register (STAR) */
DECL|macro|SAB82532_STAR_XDOV
mdefine_line|#define SAB82532_STAR_XDOV&t;&t;0x80
DECL|macro|SAB82532_STAR_XFW
mdefine_line|#define SAB82532_STAR_XFW&t;&t;0x40
DECL|macro|SAB82532_STAR_RFNE
mdefine_line|#define SAB82532_STAR_RFNE&t;&t;0x20
DECL|macro|SAB82532_STAR_FCS
mdefine_line|#define SAB82532_STAR_FCS&t;&t;0x10
DECL|macro|SAB82532_STAR_TEC
mdefine_line|#define SAB82532_STAR_TEC&t;&t;0x08
DECL|macro|SAB82532_STAR_CEC
mdefine_line|#define SAB82532_STAR_CEC&t;&t;0x04
DECL|macro|SAB82532_STAR_CTS
mdefine_line|#define SAB82532_STAR_CTS&t;&t;0x02
multiline_comment|/* Command Register (CMDR) */
DECL|macro|SAB82532_CMDR_RMC
mdefine_line|#define SAB82532_CMDR_RMC&t;&t;0x80
DECL|macro|SAB82532_CMDR_RRES
mdefine_line|#define SAB82532_CMDR_RRES&t;&t;0x40
DECL|macro|SAB82532_CMDR_RFRD
mdefine_line|#define SAB82532_CMDR_RFRD&t;&t;0x20
DECL|macro|SAB82532_CMDR_STI
mdefine_line|#define SAB82532_CMDR_STI&t;&t;0x10
DECL|macro|SAB82532_CMDR_XF
mdefine_line|#define SAB82532_CMDR_XF&t;&t;0x08
DECL|macro|SAB82532_CMDR_XRES
mdefine_line|#define SAB82532_CMDR_XRES&t;&t;0x01
multiline_comment|/* Mode Register (MODE) */
DECL|macro|SAB82532_MODE_FRTS
mdefine_line|#define SAB82532_MODE_FRTS&t;&t;0x40
DECL|macro|SAB82532_MODE_FCTS
mdefine_line|#define SAB82532_MODE_FCTS&t;&t;0x20
DECL|macro|SAB82532_MODE_FLON
mdefine_line|#define SAB82532_MODE_FLON&t;&t;0x10
DECL|macro|SAB82532_MODE_RAC
mdefine_line|#define SAB82532_MODE_RAC&t;&t;0x08
DECL|macro|SAB82532_MODE_RTS
mdefine_line|#define SAB82532_MODE_RTS&t;&t;0x04
DECL|macro|SAB82532_MODE_TRS
mdefine_line|#define SAB82532_MODE_TRS&t;&t;0x02
DECL|macro|SAB82532_MODE_TLP
mdefine_line|#define SAB82532_MODE_TLP&t;&t;0x01
multiline_comment|/* Timer Register (TIMR) */
DECL|macro|SAB82532_TIMR_CNT_MASK
mdefine_line|#define SAB82532_TIMR_CNT_MASK&t;&t;0xe0
DECL|macro|SAB82532_TIMR_VALUE_MASK
mdefine_line|#define SAB82532_TIMR_VALUE_MASK&t;0x1f
multiline_comment|/* Data Format (DAFO) */
DECL|macro|SAB82532_DAFO_XBRK
mdefine_line|#define SAB82532_DAFO_XBRK&t;&t;0x40
DECL|macro|SAB82532_DAFO_STOP
mdefine_line|#define SAB82532_DAFO_STOP&t;&t;0x20
DECL|macro|SAB82532_DAFO_PAR_SPACE
mdefine_line|#define SAB82532_DAFO_PAR_SPACE&t;&t;0x00
DECL|macro|SAB82532_DAFO_PAR_ODD
mdefine_line|#define SAB82532_DAFO_PAR_ODD&t;&t;0x08
DECL|macro|SAB82532_DAFO_PAR_EVEN
mdefine_line|#define SAB82532_DAFO_PAR_EVEN&t;&t;0x10
DECL|macro|SAB82532_DAFO_PAR_MARK
mdefine_line|#define SAB82532_DAFO_PAR_MARK&t;&t;0x18
DECL|macro|SAB82532_DAFO_PARE
mdefine_line|#define SAB82532_DAFO_PARE&t;&t;0x04
DECL|macro|SAB82532_DAFO_CHL8
mdefine_line|#define SAB82532_DAFO_CHL8&t;&t;0x00
DECL|macro|SAB82532_DAFO_CHL7
mdefine_line|#define SAB82532_DAFO_CHL7&t;&t;0x01
DECL|macro|SAB82532_DAFO_CHL6
mdefine_line|#define SAB82532_DAFO_CHL6&t;&t;0x02
DECL|macro|SAB82532_DAFO_CHL5
mdefine_line|#define SAB82532_DAFO_CHL5&t;&t;0x03
multiline_comment|/* RFIFO Control Register (RFC) */
DECL|macro|SAB82532_RFC_DPS
mdefine_line|#define SAB82532_RFC_DPS&t;&t;0x40
DECL|macro|SAB82532_RFC_DXS
mdefine_line|#define SAB82532_RFC_DXS&t;&t;0x20
DECL|macro|SAB82532_RFC_RFDF
mdefine_line|#define SAB82532_RFC_RFDF&t;&t;0x10
DECL|macro|SAB82532_RFC_RFTH_1
mdefine_line|#define SAB82532_RFC_RFTH_1&t;&t;0x00
DECL|macro|SAB82532_RFC_RFTH_4
mdefine_line|#define SAB82532_RFC_RFTH_4&t;&t;0x04
DECL|macro|SAB82532_RFC_RFTH_16
mdefine_line|#define SAB82532_RFC_RFTH_16&t;&t;0x08
DECL|macro|SAB82532_RFC_RFTH_32
mdefine_line|#define SAB82532_RFC_RFTH_32&t;&t;0x0c
DECL|macro|SAB82532_RFC_TCDE
mdefine_line|#define SAB82532_RFC_TCDE&t;&t;0x01
multiline_comment|/* Received Byte Count High (RBCH) */
DECL|macro|SAB82532_RBCH_DMA
mdefine_line|#define SAB82532_RBCH_DMA&t;&t;0x80
DECL|macro|SAB82532_RBCH_CAS
mdefine_line|#define SAB82532_RBCH_CAS&t;&t;0x20
multiline_comment|/* Transmit Byte Count High (XBCH) */
DECL|macro|SAB82532_XBCH_DMA
mdefine_line|#define SAB82532_XBCH_DMA&t;&t;0x80
DECL|macro|SAB82532_XBCH_CAS
mdefine_line|#define SAB82532_XBCH_CAS&t;&t;0x20
DECL|macro|SAB82532_XBCH_XC
mdefine_line|#define SAB82532_XBCH_XC&t;&t;0x10
multiline_comment|/* Channel Configuration Register 0 (CCR0) */
DECL|macro|SAB82532_CCR0_PU
mdefine_line|#define SAB82532_CCR0_PU&t;&t;0x80
DECL|macro|SAB82532_CCR0_MCE
mdefine_line|#define SAB82532_CCR0_MCE&t;&t;0x40
DECL|macro|SAB82532_CCR0_SC_NRZ
mdefine_line|#define SAB82532_CCR0_SC_NRZ&t;&t;0x00
DECL|macro|SAB82532_CCR0_SC_NRZI
mdefine_line|#define SAB82532_CCR0_SC_NRZI&t;&t;0x08
DECL|macro|SAB82532_CCR0_SC_FM0
mdefine_line|#define SAB82532_CCR0_SC_FM0&t;&t;0x10
DECL|macro|SAB82532_CCR0_SC_FM1
mdefine_line|#define SAB82532_CCR0_SC_FM1&t;&t;0x14
DECL|macro|SAB82532_CCR0_SC_MANCH
mdefine_line|#define SAB82532_CCR0_SC_MANCH&t;&t;0x18
DECL|macro|SAB82532_CCR0_SM_HDLC
mdefine_line|#define SAB82532_CCR0_SM_HDLC&t;&t;0x00
DECL|macro|SAB82532_CCR0_SM_SDLC_LOOP
mdefine_line|#define SAB82532_CCR0_SM_SDLC_LOOP&t;0x01
DECL|macro|SAB82532_CCR0_SM_BISYNC
mdefine_line|#define SAB82532_CCR0_SM_BISYNC&t;&t;0x02
DECL|macro|SAB82532_CCR0_SM_ASYNC
mdefine_line|#define SAB82532_CCR0_SM_ASYNC&t;&t;0x03
multiline_comment|/* Channel Configuration Register 1 (CCR1) */
DECL|macro|SAB82532_CCR1_ODS
mdefine_line|#define SAB82532_CCR1_ODS&t;&t;0x10
DECL|macro|SAB82532_CCR1_BCR
mdefine_line|#define SAB82532_CCR1_BCR&t;&t;0x08
DECL|macro|SAB82532_CCR1_CM_MASK
mdefine_line|#define SAB82532_CCR1_CM_MASK&t;&t;0x07
multiline_comment|/* Channel Configuration Register 2 (CCR2) */
DECL|macro|SAB82532_CCR2_SOC1
mdefine_line|#define SAB82532_CCR2_SOC1&t;&t;0x80
DECL|macro|SAB82532_CCR2_SOC0
mdefine_line|#define SAB82532_CCR2_SOC0&t;&t;0x40
DECL|macro|SAB82532_CCR2_BR9
mdefine_line|#define SAB82532_CCR2_BR9&t;&t;0x80
DECL|macro|SAB82532_CCR2_BR8
mdefine_line|#define SAB82532_CCR2_BR8&t;&t;0x40
DECL|macro|SAB82532_CCR2_BDF
mdefine_line|#define SAB82532_CCR2_BDF&t;&t;0x20
DECL|macro|SAB82532_CCR2_SSEL
mdefine_line|#define SAB82532_CCR2_SSEL&t;&t;0x10
DECL|macro|SAB82532_CCR2_XCS0
mdefine_line|#define SAB82532_CCR2_XCS0&t;&t;0x20
DECL|macro|SAB82532_CCR2_RCS0
mdefine_line|#define SAB82532_CCR2_RCS0&t;&t;0x10
DECL|macro|SAB82532_CCR2_TOE
mdefine_line|#define SAB82532_CCR2_TOE&t;&t;0x08
DECL|macro|SAB82532_CCR2_RWX
mdefine_line|#define SAB82532_CCR2_RWX&t;&t;0x04
DECL|macro|SAB82532_CCR2_DIV
mdefine_line|#define SAB82532_CCR2_DIV&t;&t;0x01
multiline_comment|/* Channel Configuration Register 3 (CCR3) */
DECL|macro|SAB82532_CCR3_PSD
mdefine_line|#define SAB82532_CCR3_PSD&t;&t;0x01
multiline_comment|/* Time Slot Assignment Register Transmit (TSAX) */
DECL|macro|SAB82532_TSAX_TSNX_MASK
mdefine_line|#define SAB82532_TSAX_TSNX_MASK&t;&t;0xfc
DECL|macro|SAB82532_TSAX_XCS2
mdefine_line|#define SAB82532_TSAX_XCS2&t;&t;0x02&t;/* see also CCR2 */
DECL|macro|SAB82532_TSAX_XCS1
mdefine_line|#define SAB82532_TSAX_XCS1&t;&t;0x01
multiline_comment|/* Time Slot Assignment Register Receive (TSAR) */
DECL|macro|SAB82532_TSAR_TSNR_MASK
mdefine_line|#define SAB82532_TSAR_TSNR_MASK&t;&t;0xfc
DECL|macro|SAB82532_TSAR_RCS2
mdefine_line|#define SAB82532_TSAR_RCS2&t;&t;0x02&t;/* see also CCR2 */
DECL|macro|SAB82532_TSAR_RCS1
mdefine_line|#define SAB82532_TSAR_RCS1&t;&t;0x01
multiline_comment|/* Version Status Register (VSTR) */
DECL|macro|SAB82532_VSTR_CD
mdefine_line|#define SAB82532_VSTR_CD&t;&t;0x80
DECL|macro|SAB82532_VSTR_DPLA
mdefine_line|#define SAB82532_VSTR_DPLA&t;&t;0x40
DECL|macro|SAB82532_VSTR_VN_MASK
mdefine_line|#define SAB82532_VSTR_VN_MASK&t;&t;0x0f
DECL|macro|SAB82532_VSTR_VN_1
mdefine_line|#define SAB82532_VSTR_VN_1&t;&t;0x00
DECL|macro|SAB82532_VSTR_VN_2
mdefine_line|#define SAB82532_VSTR_VN_2&t;&t;0x01
DECL|macro|SAB82532_VSTR_VN_3_2
mdefine_line|#define SAB82532_VSTR_VN_3_2&t;&t;0x02
multiline_comment|/* Global Interrupt Status Register (GIS) */
DECL|macro|SAB82532_GIS_PI
mdefine_line|#define SAB82532_GIS_PI&t;&t;&t;0x80
DECL|macro|SAB82532_GIS_ISA1
mdefine_line|#define SAB82532_GIS_ISA1&t;&t;0x08
DECL|macro|SAB82532_GIS_ISA0
mdefine_line|#define SAB82532_GIS_ISA0&t;&t;0x04
DECL|macro|SAB82532_GIS_ISB1
mdefine_line|#define SAB82532_GIS_ISB1&t;&t;0x02
DECL|macro|SAB82532_GIS_ISB0
mdefine_line|#define SAB82532_GIS_ISB0&t;&t;0x01
multiline_comment|/* Interrupt Vector Address (IVA) */
DECL|macro|SAB82532_IVA_MASK
mdefine_line|#define SAB82532_IVA_MASK&t;&t;0xf1
multiline_comment|/* Interrupt Port Configuration (IPC) */
DECL|macro|SAB82532_IPC_VIS
mdefine_line|#define SAB82532_IPC_VIS&t;&t;0x80
DECL|macro|SAB82532_IPC_SLA1
mdefine_line|#define SAB82532_IPC_SLA1&t;&t;0x10
DECL|macro|SAB82532_IPC_SLA0
mdefine_line|#define SAB82532_IPC_SLA0&t;&t;0x08
DECL|macro|SAB82532_IPC_CASM
mdefine_line|#define SAB82532_IPC_CASM&t;&t;0x04
DECL|macro|SAB82532_IPC_IC_OPEN_DRAIN
mdefine_line|#define SAB82532_IPC_IC_OPEN_DRAIN&t;0x00
DECL|macro|SAB82532_IPC_IC_ACT_LOW
mdefine_line|#define SAB82532_IPC_IC_ACT_LOW&t;&t;0x01
DECL|macro|SAB82532_IPC_IC_ACT_HIGH
mdefine_line|#define SAB82532_IPC_IC_ACT_HIGH&t;0x03
multiline_comment|/* Interrupt Status Register 0 (ISR0) */
DECL|macro|SAB82532_ISR0_TCD
mdefine_line|#define SAB82532_ISR0_TCD&t;&t;0x80
DECL|macro|SAB82532_ISR0_TIME
mdefine_line|#define SAB82532_ISR0_TIME&t;&t;0x40
DECL|macro|SAB82532_ISR0_PERR
mdefine_line|#define SAB82532_ISR0_PERR&t;&t;0x20
DECL|macro|SAB82532_ISR0_FERR
mdefine_line|#define SAB82532_ISR0_FERR&t;&t;0x10
DECL|macro|SAB82532_ISR0_PLLA
mdefine_line|#define SAB82532_ISR0_PLLA&t;&t;0x08
DECL|macro|SAB82532_ISR0_CDSC
mdefine_line|#define SAB82532_ISR0_CDSC&t;&t;0x04
DECL|macro|SAB82532_ISR0_RFO
mdefine_line|#define SAB82532_ISR0_RFO&t;&t;0x02
DECL|macro|SAB82532_ISR0_RPF
mdefine_line|#define SAB82532_ISR0_RPF&t;&t;0x01
multiline_comment|/* Interrupt Status Register 1 (ISR1) */
DECL|macro|SAB82532_ISR1_BRK
mdefine_line|#define SAB82532_ISR1_BRK&t;&t;0x80
DECL|macro|SAB82532_ISR1_BRKT
mdefine_line|#define SAB82532_ISR1_BRKT&t;&t;0x40
DECL|macro|SAB82532_ISR1_ALLS
mdefine_line|#define SAB82532_ISR1_ALLS&t;&t;0x20
DECL|macro|SAB82532_ISR1_XOFF
mdefine_line|#define SAB82532_ISR1_XOFF&t;&t;0x10
DECL|macro|SAB82532_ISR1_TIN
mdefine_line|#define SAB82532_ISR1_TIN&t;&t;0x08
DECL|macro|SAB82532_ISR1_CSC
mdefine_line|#define SAB82532_ISR1_CSC&t;&t;0x04
DECL|macro|SAB82532_ISR1_XON
mdefine_line|#define SAB82532_ISR1_XON&t;&t;0x02
DECL|macro|SAB82532_ISR1_XPR
mdefine_line|#define SAB82532_ISR1_XPR&t;&t;0x01
multiline_comment|/* Interrupt Mask Register 0 (IMR0) */
DECL|macro|SAB82532_IMR0_TCD
mdefine_line|#define SAB82532_IMR0_TCD&t;&t;0x80
DECL|macro|SAB82532_IMR0_TIME
mdefine_line|#define SAB82532_IMR0_TIME&t;&t;0x40
DECL|macro|SAB82532_IMR0_PERR
mdefine_line|#define SAB82532_IMR0_PERR&t;&t;0x20
DECL|macro|SAB82532_IMR0_FERR
mdefine_line|#define SAB82532_IMR0_FERR&t;&t;0x10
DECL|macro|SAB82532_IMR0_PLLA
mdefine_line|#define SAB82532_IMR0_PLLA&t;&t;0x08
DECL|macro|SAB82532_IMR0_CDSC
mdefine_line|#define SAB82532_IMR0_CDSC&t;&t;0x04
DECL|macro|SAB82532_IMR0_RFO
mdefine_line|#define SAB82532_IMR0_RFO&t;&t;0x02
DECL|macro|SAB82532_IMR0_RPF
mdefine_line|#define SAB82532_IMR0_RPF&t;&t;0x01
multiline_comment|/* Interrupt Mask Register 1 (IMR1) */
DECL|macro|SAB82532_IMR1_BRK
mdefine_line|#define SAB82532_IMR1_BRK&t;&t;0x80
DECL|macro|SAB82532_IMR1_BRKT
mdefine_line|#define SAB82532_IMR1_BRKT&t;&t;0x40
DECL|macro|SAB82532_IMR1_ALLS
mdefine_line|#define SAB82532_IMR1_ALLS&t;&t;0x20
DECL|macro|SAB82532_IMR1_XOFF
mdefine_line|#define SAB82532_IMR1_XOFF&t;&t;0x10
DECL|macro|SAB82532_IMR1_TIN
mdefine_line|#define SAB82532_IMR1_TIN&t;&t;0x08
DECL|macro|SAB82532_IMR1_CSC
mdefine_line|#define SAB82532_IMR1_CSC&t;&t;0x04
DECL|macro|SAB82532_IMR1_XON
mdefine_line|#define SAB82532_IMR1_XON&t;&t;0x02
DECL|macro|SAB82532_IMR1_XPR
mdefine_line|#define SAB82532_IMR1_XPR&t;&t;0x01
multiline_comment|/* Port Interrupt Status Register (PIS) */
DECL|macro|SAB82532_PIS_SYNC_B
mdefine_line|#define SAB82532_PIS_SYNC_B&t;&t;0x08
DECL|macro|SAB82532_PIS_DTR_B
mdefine_line|#define SAB82532_PIS_DTR_B&t;&t;0x04
DECL|macro|SAB82532_PIS_DTR_A
mdefine_line|#define SAB82532_PIS_DTR_A&t;&t;0x02
DECL|macro|SAB82532_PIS_SYNC_A
mdefine_line|#define SAB82532_PIS_SYNC_A&t;&t;0x01
multiline_comment|/* Channel Configuration Register 4 (CCR4) */
DECL|macro|SAB82532_CCR4_MCK4
mdefine_line|#define SAB82532_CCR4_MCK4&t;&t;0x80
DECL|macro|SAB82532_CCR4_EBRG
mdefine_line|#define SAB82532_CCR4_EBRG&t;&t;0x40
DECL|macro|SAB82532_CCR4_TST1
mdefine_line|#define SAB82532_CCR4_TST1&t;&t;0x20
DECL|macro|SAB82532_CCR4_ICD
mdefine_line|#define SAB82532_CCR4_ICD&t;&t;0x10
macro_line|#endif /* !(_SPARC64_SAB82532_H) */
eof
