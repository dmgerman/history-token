multiline_comment|/*********************************************************************&n; *                &n; * Filename:      w83977af_ir.h&n; * Version:       &n; * Description:   &n; * Status:        Experimental.&n; * Author:        Paul VanderSpek&n; * Created at:    Thu Nov 19 13:55:34 1998&n; * Modified at:   Tue Jan 11 13:08:19 2000&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1998-2000 Dag Brattli, All Rights Reserved.&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
macro_line|#ifndef W83977AF_IR_H
DECL|macro|W83977AF_IR_H
mdefine_line|#define W83977AF_IR_H
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/* Flags for configuration register CRF0 */
DECL|macro|ENBNKSEL
mdefine_line|#define ENBNKSEL&t;0x01
DECL|macro|APEDCRC
mdefine_line|#define APEDCRC&t;&t;0x02
DECL|macro|TXW4C
mdefine_line|#define TXW4C           0x04
DECL|macro|RXW4C
mdefine_line|#define RXW4C           0x08
multiline_comment|/* Bank 0 */
DECL|macro|RBR
mdefine_line|#define RBR             0x00 /* Receiver buffer register */
DECL|macro|TBR
mdefine_line|#define TBR             0x00 /* Transmitter buffer register */
DECL|macro|ICR
mdefine_line|#define ICR&t;&t;0x01 /* Interrupt configuration register */
DECL|macro|ICR_ERBRI
mdefine_line|#define ICR_ERBRI       0x01 /* Receiver buffer register interrupt */
DECL|macro|ICR_ETBREI
mdefine_line|#define ICR_ETBREI      0x02 /* Transeiver empty interrupt */
DECL|macro|ICR_EUSRI
mdefine_line|#define ICR_EUSRI&t;0x04
singleline_comment|//* IR status interrupt */
DECL|macro|ICR_EHSRI
mdefine_line|#define ICR_EHSRI       0x04
DECL|macro|ICR_ETXURI
mdefine_line|#define ICR_ETXURI      0x04 /* Tx underrun */
DECL|macro|ICR_EDMAI
mdefine_line|#define ICR_EDMAI&t;0x10 /* DMA interrupt */
DECL|macro|ICR_ETXTHI
mdefine_line|#define ICR_ETXTHI      0x20 /* Transmitter threshold interrupt */
DECL|macro|ICR_EFSFI
mdefine_line|#define ICR_EFSFI       0x40 /* Frame status FIFO interrupt */
DECL|macro|ICR_ETMRI
mdefine_line|#define ICR_ETMRI       0x80 /* Timer interrupt */
DECL|macro|UFR
mdefine_line|#define UFR&t;&t;0x02 /* FIFO control register */
DECL|macro|UFR_EN_FIFO
mdefine_line|#define UFR_EN_FIFO     0x01 /* Enable FIFO&squot;s */
DECL|macro|UFR_RXF_RST
mdefine_line|#define UFR_RXF_RST     0x02 /* Reset Rx FIFO */
DECL|macro|UFR_TXF_RST
mdefine_line|#define UFR_TXF_RST     0x04 /* Reset Tx FIFO */
DECL|macro|UFR_RXTL
mdefine_line|#define UFR_RXTL&t;0x80 /* Rx FIFO threshold (set to 16) */
DECL|macro|UFR_TXTL
mdefine_line|#define UFR_TXTL&t;0x20 /* Tx FIFO threshold (set to 17) */
DECL|macro|ISR
mdefine_line|#define ISR&t;&t;0x02 /* Interrupt status register */
DECL|macro|ISR_RXTH_I
mdefine_line|#define ISR_RXTH_I&t;0x01 /* Receive threshold interrupt */
DECL|macro|ISR_TXEMP_I
mdefine_line|#define ISR_TXEMP_I     0x02 /* Transmitter empty interrupt */
DECL|macro|ISR_FEND_I
mdefine_line|#define ISR_FEND_I&t;0x04
DECL|macro|ISR_DMA_I
mdefine_line|#define ISR_DMA_I&t;0x10
DECL|macro|ISR_TXTH_I
mdefine_line|#define ISR_TXTH_I&t;0x20 /* Transmitter threshold interrupt */
DECL|macro|ISR_FSF_I
mdefine_line|#define ISR_FSF_I       0x40
DECL|macro|ISR_TMR_I
mdefine_line|#define ISR_TMR_I       0x80 /* Timer interrupt */
DECL|macro|UCR
mdefine_line|#define UCR             0x03 /* Uart control register */
DECL|macro|UCR_DLS8
mdefine_line|#define UCR_DLS8        0x03 /* 8N1 */
DECL|macro|SSR
mdefine_line|#define SSR &t;        0x03 /* Sets select register */
DECL|macro|SET0
mdefine_line|#define SET0 &t;        UCR_DLS8        /* Make sure we keep 8N1 */
DECL|macro|SET1
mdefine_line|#define SET1&t;        (0x80|UCR_DLS8) /* Make sure we keep 8N1 */
DECL|macro|SET2
mdefine_line|#define SET2&t;        0xE0
DECL|macro|SET3
mdefine_line|#define SET3&t;        0xE4
DECL|macro|SET4
mdefine_line|#define SET4&t;        0xE8
DECL|macro|SET5
mdefine_line|#define SET5&t;        0xEC
DECL|macro|SET6
mdefine_line|#define SET6&t;        0xF0
DECL|macro|SET7
mdefine_line|#define SET7&t;        0xF4
DECL|macro|HCR
mdefine_line|#define HCR&t;&t;0x04
DECL|macro|HCR_MODE_MASK
mdefine_line|#define HCR_MODE_MASK&t;~(0xD0)
DECL|macro|HCR_SIR
mdefine_line|#define HCR_SIR         0x60
DECL|macro|HCR_MIR_576
mdefine_line|#define HCR_MIR_576  &t;0x20&t;
DECL|macro|HCR_MIR_1152
mdefine_line|#define HCR_MIR_1152&t;0x80
DECL|macro|HCR_FIR
mdefine_line|#define HCR_FIR&t;&t;0xA0
DECL|macro|HCR_EN_DMA
mdefine_line|#define HCR_EN_DMA&t;0x04
DECL|macro|HCR_EN_IRQ
mdefine_line|#define HCR_EN_IRQ&t;0x08
DECL|macro|HCR_TX_WT
mdefine_line|#define HCR_TX_WT&t;0x08
DECL|macro|USR
mdefine_line|#define USR             0x05 /* IR status register */
DECL|macro|USR_RDR
mdefine_line|#define USR_RDR         0x01 /* Receive data ready */
DECL|macro|USR_TSRE
mdefine_line|#define USR_TSRE        0x40 /* Transmitter empty? */
DECL|macro|AUDR
mdefine_line|#define AUDR            0x07
DECL|macro|AUDR_SFEND
mdefine_line|#define AUDR_SFEND      0x08 /* Set a frame end */
DECL|macro|AUDR_RXBSY
mdefine_line|#define AUDR_RXBSY      0x20 /* Rx busy */
DECL|macro|AUDR_UNDR
mdefine_line|#define AUDR_UNDR       0x40 /* Transeiver underrun */
multiline_comment|/* Set 2 */
DECL|macro|ABLL
mdefine_line|#define ABLL            0x00 /* Advanced baud rate divisor latch (low byte) */
DECL|macro|ABHL
mdefine_line|#define ABHL            0x01 /* Advanced baud rate divisor latch (high byte) */
DECL|macro|ADCR1
mdefine_line|#define ADCR1&t;&t;0x02
DECL|macro|ADCR1_ADV_SL
mdefine_line|#define ADCR1_ADV_SL&t;0x01&t;
DECL|macro|ADCR1_D_CHSW
mdefine_line|#define ADCR1_D_CHSW&t;0x08&t;/* the specs are wrong. its bit 3, not 4 */
DECL|macro|ADCR1_DMA_F
mdefine_line|#define ADCR1_DMA_F&t;0x02
DECL|macro|ADCR2
mdefine_line|#define ADCR2&t;&t;0x04
DECL|macro|ADCR2_TXFS32
mdefine_line|#define ADCR2_TXFS32&t;0x01
DECL|macro|ADCR2_RXFS32
mdefine_line|#define ADCR2_RXFS32&t;0x04
DECL|macro|RXFDTH
mdefine_line|#define RXFDTH          0x07
multiline_comment|/* Set 3 */
DECL|macro|AUID
mdefine_line|#define AUID&t;&t;0x00
multiline_comment|/* Set 4 */
DECL|macro|TMRL
mdefine_line|#define TMRL            0x00 /* Timer value register (low byte) */
DECL|macro|TMRH
mdefine_line|#define TMRH            0x01 /* Timer value register (high byte) */
DECL|macro|IR_MSL
mdefine_line|#define IR_MSL          0x02 /* Infrared mode select */
DECL|macro|IR_MSL_EN_TMR
mdefine_line|#define IR_MSL_EN_TMR   0x01 /* Enable timer */
DECL|macro|TFRLL
mdefine_line|#define TFRLL&t;&t;0x04 /* Transmitter frame length (low byte) */
DECL|macro|TFRLH
mdefine_line|#define TFRLH&t;&t;0x05 /* Transmitter frame length (high byte) */
DECL|macro|RFRLL
mdefine_line|#define RFRLL&t;&t;0x06 /* Receiver frame length (low byte) */
DECL|macro|RFRLH
mdefine_line|#define RFRLH&t;&t;0x07 /* Receiver frame length (high byte) */
multiline_comment|/* Set 5 */
DECL|macro|FS_FO
mdefine_line|#define FS_FO           0x05 /* Frame status FIFO */
DECL|macro|FS_FO_FSFDR
mdefine_line|#define FS_FO_FSFDR     0x80 /* Frame status FIFO data ready */
DECL|macro|FS_FO_LST_FR
mdefine_line|#define FS_FO_LST_FR    0x40 /* Frame lost */
DECL|macro|FS_FO_MX_LEX
mdefine_line|#define FS_FO_MX_LEX    0x10 /* Max frame len exceeded */
DECL|macro|FS_FO_PHY_ERR
mdefine_line|#define FS_FO_PHY_ERR   0x08 /* Physical layer error */
DECL|macro|FS_FO_CRC_ERR
mdefine_line|#define FS_FO_CRC_ERR   0x04 
DECL|macro|FS_FO_RX_OV
mdefine_line|#define FS_FO_RX_OV     0x02 /* Receive overrun */
DECL|macro|FS_FO_FSF_OV
mdefine_line|#define FS_FO_FSF_OV    0x01 /* Frame status FIFO overrun */
DECL|macro|FS_FO_ERR_MSK
mdefine_line|#define FS_FO_ERR_MSK   0x5f /* Error mask */
DECL|macro|RFLFL
mdefine_line|#define RFLFL           0x06
DECL|macro|RFLFH
mdefine_line|#define RFLFH           0x07
multiline_comment|/* Set 6 */
DECL|macro|IR_CFG2
mdefine_line|#define IR_CFG2&t;&t;0x00
DECL|macro|IR_CFG2_DIS_CRC
mdefine_line|#define IR_CFG2_DIS_CRC&t;0x02
multiline_comment|/* Set 7 */
DECL|macro|IRM_CR
mdefine_line|#define IRM_CR&t;&t;0x07 /* Infrared module control register */
DECL|macro|IRM_CR_IRX_MSL
mdefine_line|#define IRM_CR_IRX_MSL&t;0x40
DECL|macro|IRM_CR_AF_MNT
mdefine_line|#define IRM_CR_AF_MNT   0x80 /* Automatic format */
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
l_int|10
)braket
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
multiline_comment|/* Private data for each instance */
DECL|struct|w83977af_ir
r_struct
id|w83977af_ir
(brace
DECL|member|st_fifo
r_struct
id|st_fifo
id|st_fifo
suffix:semicolon
DECL|member|tx_buff_offsets
r_int
id|tx_buff_offsets
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* Offsets between frames in tx_buff */
DECL|member|tx_len
r_int
id|tx_len
suffix:semicolon
multiline_comment|/* Number of frames in tx_buff */
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
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
multiline_comment|/* Interface flags */
DECL|member|new_speed
id|__u32
id|new_speed
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
id|set
)paren
(brace
id|outb
c_func
(paren
id|set
comma
id|iobase
op_plus
id|SSR
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
