multiline_comment|/*********************************************************************&n; *                &n; * Filename:      ali-ircc.h&n; * Version:       0.5&n; * Description:   Driver for the ALI M1535D and M1543C FIR Controller&n; * Status:        Experimental.&n; * Author:        Benjamin Kong &lt;benjamin_kong@ali.com.tw&gt;&n; * Created at:    2000/10/16 03:46PM&n; * Modified at:   2001/1/3 02:56PM&n; * Modified by:   Benjamin Kong &lt;benjamin_kong@ali.com.tw&gt;&n; * &n; *     Copyright (c) 2000 Benjamin Kong &lt;benjamin_kong@ali.com.tw&gt;&n; *     All Rights Reserved&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; ********************************************************************/
macro_line|#ifndef ALI_IRCC_H
DECL|macro|ALI_IRCC_H
mdefine_line|#define ALI_IRCC_H
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/* SIR Register */
multiline_comment|/* Usr definition of linux/serial_reg.h */
multiline_comment|/* FIR Register */
DECL|macro|BANK0
mdefine_line|#define BANK0&t;&t;0x20
DECL|macro|BANK1
mdefine_line|#define BANK1&t;&t;0x21
DECL|macro|BANK2
mdefine_line|#define BANK2&t;&t;0x22
DECL|macro|BANK3
mdefine_line|#define BANK3&t;&t;0x23
DECL|macro|FIR_MCR
mdefine_line|#define FIR_MCR&t;&t;0x07&t;/* Master Control Register */
multiline_comment|/* Bank 0 */
DECL|macro|FIR_DR
mdefine_line|#define FIR_DR&t;&t;0x00&t;/* Alias 0, FIR Data Register (R/W) */ 
DECL|macro|FIR_IER
mdefine_line|#define FIR_IER&t;&t;0x01&t;/* Alias 1, FIR Interrupt Enable Register (R/W) */
DECL|macro|FIR_IIR
mdefine_line|#define FIR_IIR&t;&t;0x02&t;/* Alias 2, FIR Interrupt Identification Register (Read only) */
DECL|macro|FIR_LCR_A
mdefine_line|#define FIR_LCR_A&t;0x03&t;/* Alias 3, FIR Line Control Register A (R/W) */
DECL|macro|FIR_LCR_B
mdefine_line|#define FIR_LCR_B&t;0x04&t;/* Alias 4, FIR Line Control Register B (R/W) */
DECL|macro|FIR_LSR
mdefine_line|#define FIR_LSR&t;&t;0x05&t;/* Alias 5, FIR Line Status Register (R/W) */
DECL|macro|FIR_BSR
mdefine_line|#define FIR_BSR&t;&t;0x06&t;/* Alias 6, FIR Bus Status Register (Read only) */
multiline_comment|/* Alias 1 */
DECL|macro|IER_FIFO
mdefine_line|#define&t;IER_FIFO&t;0x10&t;/* FIR FIFO Interrupt Enable */&t;
DECL|macro|IER_TIMER
mdefine_line|#define&t;IER_TIMER&t;0x20 &t;/* Timer Interrupt Enable */ 
DECL|macro|IER_EOM
mdefine_line|#define&t;IER_EOM&t;&t;0x40&t;/* End of Message Interrupt Enable */
DECL|macro|IER_ACT
mdefine_line|#define IER_ACT&t;&t;0x80&t;/* Active Frame Interrupt Enable */
multiline_comment|/* Alias 2 */
DECL|macro|IIR_FIFO
mdefine_line|#define IIR_FIFO&t;0x10&t;/* FIR FIFO Interrupt */
DECL|macro|IIR_TIMER
mdefine_line|#define IIR_TIMER&t;0x20&t;/* Timer Interrupt */
DECL|macro|IIR_EOM
mdefine_line|#define IIR_EOM&t;&t;0x40&t;/* End of Message Interrupt */
DECL|macro|IIR_ACT
mdefine_line|#define IIR_ACT&t;&t;0x80&t;/* Active Frame Interrupt */&t;
multiline_comment|/* Alias 3 */
DECL|macro|LCR_A_FIFO_RESET
mdefine_line|#define LCR_A_FIFO_RESET 0x80&t;/* FIFO Reset */
multiline_comment|/* Alias 4 */
DECL|macro|LCR_B_BW
mdefine_line|#define&t;LCR_B_BW&t;0x10&t;/* Brick Wall */
DECL|macro|LCR_B_SIP
mdefine_line|#define LCR_B_SIP&t;0x20&t;/* SIP Enable */
DECL|macro|LCR_B_TX_MODE
mdefine_line|#define&t;LCR_B_TX_MODE &t;0x40&t;/* Transmit Mode */
DECL|macro|LCR_B_RX_MODE
mdefine_line|#define LCR_B_RX_MODE&t;0x80&t;/* Receive Mode */
multiline_comment|/* Alias 5 */
DECL|macro|LSR_FIR_LSA
mdefine_line|#define LSR_FIR_LSA&t;0x00&t;/* FIR Line Status Address */
DECL|macro|LSR_FRAME_ABORT
mdefine_line|#define LSR_FRAME_ABORT&t;0x08&t;/* Frame Abort */
DECL|macro|LSR_CRC_ERROR
mdefine_line|#define LSR_CRC_ERROR&t;0x10&t;/* CRC Error */
DECL|macro|LSR_SIZE_ERROR
mdefine_line|#define LSR_SIZE_ERROR&t;0x20&t;/* Size Error */
DECL|macro|LSR_FRAME_ERROR
mdefine_line|#define LSR_FRAME_ERROR&t;0x40&t;/* Frame Error */
DECL|macro|LSR_FIFO_UR
mdefine_line|#define LSR_FIFO_UR&t;0x80&t;/* FIFO Underrun */
DECL|macro|LSR_FIFO_OR
mdefine_line|#define LSR_FIFO_OR&t;0x80&t;/* FIFO Overrun */
multiline_comment|/* Alias 6 */
DECL|macro|BSR_FIFO_NOT_EMPTY
mdefine_line|#define BSR_FIFO_NOT_EMPTY&t;0x80&t;/* FIFO Not Empty */
multiline_comment|/* Bank 1 */
DECL|macro|FIR_CR
mdefine_line|#define&t;FIR_CR&t;&t;0x00 &t;/* Alias 0, FIR Configuration Register (R/W) */
DECL|macro|FIR_FIFO_TR
mdefine_line|#define FIR_FIFO_TR&t;0x01   &t;/* Alias 1, FIR FIFO Threshold Register (R/W) */
DECL|macro|FIR_DMA_TR
mdefine_line|#define FIR_DMA_TR&t;0x02&t;/* Alias 2, FIR DMA Threshold Register (R/W) */
DECL|macro|FIR_TIMER_IIR
mdefine_line|#define FIR_TIMER_IIR&t;0x03&t;/* Alias 3, FIR Timer interrupt interval register (W/O) */
DECL|macro|FIR_FIFO_FR
mdefine_line|#define FIR_FIFO_FR&t;0x03&t;/* Alias 3, FIR FIFO Flag register (R/O) */
DECL|macro|FIR_FIFO_RAR
mdefine_line|#define FIR_FIFO_RAR&t;0x04 &t;/* Alias 4, FIR FIFO Read Address register (R/O) */
DECL|macro|FIR_FIFO_WAR
mdefine_line|#define FIR_FIFO_WAR&t;0x05&t;/* Alias 5, FIR FIFO Write Address register (R/O) */
DECL|macro|FIR_TR
mdefine_line|#define FIR_TR&t;&t;0x06&t;/* Alias 6, Test REgister (W/O) */
multiline_comment|/* Alias 0 */
DECL|macro|CR_DMA_EN
mdefine_line|#define CR_DMA_EN&t;0x01&t;/* DMA Enable */
DECL|macro|CR_DMA_BURST
mdefine_line|#define CR_DMA_BURST&t;0x02&t;/* DMA Burst Mode */
DECL|macro|CR_TIMER_EN
mdefine_line|#define CR_TIMER_EN &t;0x08&t;/* Timer Enable */
multiline_comment|/* Alias 3 */
DECL|macro|TIMER_IIR_500
mdefine_line|#define TIMER_IIR_500&t;0x00&t;/* 500 us */
DECL|macro|TIMER_IIR_1ms
mdefine_line|#define TIMER_IIR_1ms&t;0x01&t;/* 1   ms */
DECL|macro|TIMER_IIR_2ms
mdefine_line|#define TIMER_IIR_2ms&t;0x02&t;/* 2   ms */
DECL|macro|TIMER_IIR_4ms
mdefine_line|#define TIMER_IIR_4ms&t;0x03&t;/* 4   ms */
multiline_comment|/* Bank 2 */
DECL|macro|FIR_IRDA_CR
mdefine_line|#define FIR_IRDA_CR&t;0x00&t;/* Alias 0, IrDA Control Register (R/W) */
DECL|macro|FIR_BOF_CR
mdefine_line|#define FIR_BOF_CR&t;0x01&t;/* Alias 1, BOF Count Register (R/W) */
DECL|macro|FIR_BW_CR
mdefine_line|#define FIR_BW_CR&t;0x02&t;/* Alias 2, Brick Wall Count Register (R/W) */
DECL|macro|FIR_TX_DSR_HI
mdefine_line|#define FIR_TX_DSR_HI&t;0x03&t;/* Alias 3, TX Data Size Register (high) (R/W) */
DECL|macro|FIR_TX_DSR_LO
mdefine_line|#define FIR_TX_DSR_LO&t;0x04&t;/* Alias 4, TX Data Size Register (low) (R/W) */
DECL|macro|FIR_RX_DSR_HI
mdefine_line|#define FIR_RX_DSR_HI&t;0x05&t;/* Alias 5, RX Data Size Register (high) (R/W) */
DECL|macro|FIR_RX_DSR_LO
mdefine_line|#define FIR_RX_DSR_LO&t;0x06&t;/* Alias 6, RX Data Size Register (low) (R/W) */
multiline_comment|/* Alias 0 */
DECL|macro|IRDA_CR_HDLC1152
mdefine_line|#define IRDA_CR_HDLC1152 0x80&t;/* 1.152Mbps HDLC Select */
DECL|macro|IRDA_CR_CRC
mdefine_line|#define IRDA_CR_CRC&t;0X40&t;/* CRC Select. */
DECL|macro|IRDA_CR_HDLC
mdefine_line|#define IRDA_CR_HDLC&t;0x20&t;/* HDLC select. */
DECL|macro|IRDA_CR_HP_MODE
mdefine_line|#define IRDA_CR_HP_MODE 0x10&t;/* HP mode (read only) */
DECL|macro|IRDA_CR_SD_ST
mdefine_line|#define IRDA_CR_SD_ST&t;0x08&t;/* SD/MODE State.  */
DECL|macro|IRDA_CR_FIR_SIN
mdefine_line|#define IRDA_CR_FIR_SIN 0x04&t;/* FIR SIN Select. */
DECL|macro|IRDA_CR_ITTX_0
mdefine_line|#define IRDA_CR_ITTX_0&t;0x02&t;/* SOUT State. IRTX force to 0 */
DECL|macro|IRDA_CR_ITTX_1
mdefine_line|#define IRDA_CR_ITTX_1&t;0x03&t;/* SOUT State. IRTX force to 1 */
multiline_comment|/* Bank 3 */
DECL|macro|FIR_ID_VR
mdefine_line|#define FIR_ID_VR&t;0x00&t;/* Alias 0, FIR ID Version Register (R/O) */
DECL|macro|FIR_MODULE_CR
mdefine_line|#define FIR_MODULE_CR&t;0x01&t;/* Alias 1, FIR Module Control Register (R/W) */
DECL|macro|FIR_IO_BASE_HI
mdefine_line|#define FIR_IO_BASE_HI&t;0x02&t;/* Alias 2, FIR Higher I/O Base Address Register (R/O) */
DECL|macro|FIR_IO_BASE_LO
mdefine_line|#define FIR_IO_BASE_LO&t;0x03&t;/* Alias 3, FIR Lower I/O Base Address Register (R/O) */
DECL|macro|FIR_IRQ_CR
mdefine_line|#define FIR_IRQ_CR&t;0x04&t;/* Alias 4, FIR IRQ Channel Register (R/O) */
DECL|macro|FIR_DMA_CR
mdefine_line|#define FIR_DMA_CR&t;0x05&t;/* Alias 5, FIR DMA Channel Register (R/O) */
DECL|struct|ali_chip
r_struct
id|ali_chip
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|cfg
r_int
id|cfg
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|entr1
r_int
r_char
id|entr1
suffix:semicolon
DECL|member|entr2
r_int
r_char
id|entr2
suffix:semicolon
DECL|member|cid_index
r_int
r_char
id|cid_index
suffix:semicolon
DECL|member|cid_value
r_int
r_char
id|cid_value
suffix:semicolon
DECL|member|probe
r_int
(paren
op_star
id|probe
)paren
(paren
r_struct
id|ali_chip
op_star
id|chip
comma
id|chipio_t
op_star
id|info
)paren
suffix:semicolon
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_struct
id|ali_chip
op_star
id|chip
comma
id|chipio_t
op_star
id|info
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|ali_chip_t
r_typedef
r_struct
id|ali_chip
id|ali_chip_t
suffix:semicolon
multiline_comment|/* DMA modes needed */
DECL|macro|DMA_TX_MODE
mdefine_line|#define DMA_TX_MODE     0x08    /* Mem to I/O, ++, demand. */
DECL|macro|DMA_RX_MODE
mdefine_line|#define DMA_RX_MODE     0x04    /* I/O to mem, ++, demand. */
DECL|macro|MAX_TX_WINDOW
mdefine_line|#define MAX_TX_WINDOW &t;7
DECL|macro|MAX_RX_WINDOW
mdefine_line|#define MAX_RX_WINDOW &t;7
DECL|macro|TX_FIFO_Threshold
mdefine_line|#define TX_FIFO_Threshold&t;8
DECL|macro|RX_FIFO_Threshold
mdefine_line|#define RX_FIFO_Threshold&t;1
DECL|macro|TX_DMA_Threshold
mdefine_line|#define TX_DMA_Threshold&t;1
DECL|macro|RX_DMA_Threshold
mdefine_line|#define RX_DMA_Threshold&t;1
multiline_comment|/* For storing entries in the status FIFO */
DECL|struct|st_fifo_entry
r_struct
id|st_fifo_entry
(brace
DECL|member|status
r_int
id|status
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|st_fifo
r_struct
id|st_fifo
(brace
DECL|member|entries
r_struct
id|st_fifo_entry
id|entries
(braket
id|MAX_RX_WINDOW
)braket
suffix:semicolon
DECL|member|pending_bytes
r_int
id|pending_bytes
suffix:semicolon
DECL|member|head
r_int
id|head
suffix:semicolon
DECL|member|tail
r_int
id|tail
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|frame_cb
r_struct
id|frame_cb
(brace
DECL|member|start
r_void
op_star
id|start
suffix:semicolon
multiline_comment|/* Start of frame in DMA mem */
DECL|member|len
r_int
id|len
suffix:semicolon
multiline_comment|/* Lenght of frame in DMA mem */
)brace
suffix:semicolon
DECL|struct|tx_fifo
r_struct
id|tx_fifo
(brace
DECL|member|queue
r_struct
id|frame_cb
id|queue
(braket
id|MAX_TX_WINDOW
)braket
suffix:semicolon
multiline_comment|/* Info about frames in queue */
DECL|member|ptr
r_int
id|ptr
suffix:semicolon
multiline_comment|/* Currently being sent */
DECL|member|len
r_int
id|len
suffix:semicolon
multiline_comment|/* Lenght of queue */
DECL|member|free
r_int
id|free
suffix:semicolon
multiline_comment|/* Next free slot */
DECL|member|tail
r_void
op_star
id|tail
suffix:semicolon
multiline_comment|/* Next free start in DMA mem */
)brace
suffix:semicolon
multiline_comment|/* Private data for each instance */
DECL|struct|ali_ircc_cb
r_struct
id|ali_ircc_cb
(brace
DECL|member|st_fifo
r_struct
id|st_fifo
id|st_fifo
suffix:semicolon
multiline_comment|/* Info about received frames */
DECL|member|tx_fifo
r_struct
id|tx_fifo
id|tx_fifo
suffix:semicolon
multiline_comment|/* Info about frames to be transmitted */
DECL|member|netdev
r_struct
id|net_device
op_star
id|netdev
suffix:semicolon
multiline_comment|/* Yes! we are some kind of netdevice */
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|irlap
r_struct
id|irlap_cb
op_star
id|irlap
suffix:semicolon
multiline_comment|/* The link layer we are binded to */
DECL|member|qos
r_struct
id|qos_info
id|qos
suffix:semicolon
multiline_comment|/* QoS capabilities for this device */
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
DECL|member|ier
id|__u8
id|ier
suffix:semicolon
multiline_comment|/* Interrupt enable register */
DECL|member|InterruptID
id|__u8
id|InterruptID
suffix:semicolon
multiline_comment|/* Interrupt ID */
DECL|member|BusStatus
id|__u8
id|BusStatus
suffix:semicolon
multiline_comment|/* Bus Status */
DECL|member|LineStatus
id|__u8
id|LineStatus
suffix:semicolon
multiline_comment|/* Line Status */
DECL|member|rcvFramesOverflow
r_int
r_char
id|rcvFramesOverflow
suffix:semicolon
DECL|member|stamp
r_struct
id|timeval
id|stamp
suffix:semicolon
DECL|member|now
r_struct
id|timeval
id|now
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* For serializing operations */
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
multiline_comment|/* Interface flags */
DECL|member|new_speed
id|__u32
id|new_speed
suffix:semicolon
DECL|member|index
r_int
id|index
suffix:semicolon
multiline_comment|/* Instance index */
DECL|member|fifo_opti_buf
r_int
r_char
id|fifo_opti_buf
suffix:semicolon
DECL|member|dev
r_struct
id|pm_dev
op_star
id|dev
suffix:semicolon
)brace
suffix:semicolon
DECL|function|switch_bank
r_static
r_inline
r_void
id|switch_bank
c_func
(paren
r_int
id|iobase
comma
r_int
id|bank
)paren
(brace
id|outb
c_func
(paren
id|bank
comma
id|iobase
op_plus
id|FIR_MCR
)paren
suffix:semicolon
)brace
macro_line|#endif /* ALI_IRCC_H */
eof
