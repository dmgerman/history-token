multiline_comment|/*********************************************************************&n; * $Id: smsc-ircc2.h,v 1.12.2.1 2002/10/27 10:52:37 dip Exp $               &n; *&n; * Description:   Definitions for the SMC IrCC chipset&n; * Status:        Experimental.&n; * Author:        Daniele Peri (peri@csai.unipa.it)&n; *&n; *     Copyright (c) 2002      Daniele Peri&n; *     All Rights Reserved.&n; *&n; * Based on smc-ircc.h:&n; * &n; *     Copyright (c) 1999-2000, Dag Brattli &lt;dagb@cs.uit.no&gt;&n; *     Copyright (c) 1998-1999, Thomas Davis (tadavis@jps.net&gt;&n; *     All Rights Reserved&n; *&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; * &n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; *     GNU General Public License for more details.&n; * &n; *     You should have received a copy of the GNU General Public License &n; *     along with this program; if not, write to the Free Software &n; *     Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n; *     MA 02111-1307 USA&n; *&n; ********************************************************************/
macro_line|#ifndef SMSC_IRCC2_H
DECL|macro|SMSC_IRCC2_H
mdefine_line|#define SMSC_IRCC2_H
multiline_comment|/* DMA modes needed */
DECL|macro|DMA_TX_MODE
mdefine_line|#define DMA_TX_MODE                0x08    /* Mem to I/O, ++, demand. */
DECL|macro|DMA_RX_MODE
mdefine_line|#define DMA_RX_MODE                0x04    /* I/O to mem, ++, demand. */
multiline_comment|/* Master Control Register */
DECL|macro|IRCC_MASTER
mdefine_line|#define IRCC_MASTER                0x07
DECL|macro|IRCC_MASTER_POWERDOWN
mdefine_line|#define   IRCC_MASTER_POWERDOWN&t;   0x80
DECL|macro|IRCC_MASTER_RESET
mdefine_line|#define   IRCC_MASTER_RESET        0x40
DECL|macro|IRCC_MASTER_INT_EN
mdefine_line|#define   IRCC_MASTER_INT_EN       0x20
DECL|macro|IRCC_MASTER_ERROR_RESET
mdefine_line|#define   IRCC_MASTER_ERROR_RESET  0x10
multiline_comment|/* Register block 0 */
multiline_comment|/* Interrupt Identification */
DECL|macro|IRCC_IIR
mdefine_line|#define IRCC_IIR&t;&t;&t;&t;&t;0x01
DECL|macro|IRCC_IIR_ACTIVE_FRAME
mdefine_line|#define   IRCC_IIR_ACTIVE_FRAME&t;&t;0x80
DECL|macro|IRCC_IIR_EOM
mdefine_line|#define   IRCC_IIR_EOM&t;&t;&t;&t;0x40
DECL|macro|IRCC_IIR_RAW_MODE
mdefine_line|#define   IRCC_IIR_RAW_MODE&t;&t;&t;0x20
DECL|macro|IRCC_IIR_FIFO
mdefine_line|#define   IRCC_IIR_FIFO&t;&t;&t;&t;0x10
multiline_comment|/* Interrupt Enable */
DECL|macro|IRCC_IER
mdefine_line|#define IRCC_IER&t;&t;&t;&t;&t;0x02
DECL|macro|IRCC_IER_ACTIVE_FRAME
mdefine_line|#define   IRCC_IER_ACTIVE_FRAME&t;&t;0x80
DECL|macro|IRCC_IER_EOM
mdefine_line|#define   IRCC_IER_EOM&t;&t;&t;&t;0x40
DECL|macro|IRCC_IER_RAW_MODE
mdefine_line|#define   IRCC_IER_RAW_MODE&t;&t;&t;0x20
DECL|macro|IRCC_IER_FIFO
mdefine_line|#define   IRCC_IER_FIFO&t;&t;&t;&t;0x10
multiline_comment|/* Line Status Register */
DECL|macro|IRCC_LSR
mdefine_line|#define IRCC_LSR&t;&t;&t;&t;&t;0x03
DECL|macro|IRCC_LSR_UNDERRUN
mdefine_line|#define   IRCC_LSR_UNDERRUN&t;&t;&t;0x80
DECL|macro|IRCC_LSR_OVERRUN
mdefine_line|#define   IRCC_LSR_OVERRUN&t;&t;&t;0x40
DECL|macro|IRCC_LSR_FRAME_ERROR
mdefine_line|#define   IRCC_LSR_FRAME_ERROR&t;&t;0x20
DECL|macro|IRCC_LSR_SIZE_ERROR
mdefine_line|#define   IRCC_LSR_SIZE_ERROR&t;&t;0x10
DECL|macro|IRCC_LSR_CRC_ERROR
mdefine_line|#define   IRCC_LSR_CRC_ERROR&t;&t;0x80
DECL|macro|IRCC_LSR_FRAME_ABORT
mdefine_line|#define   IRCC_LSR_FRAME_ABORT&t;&t;0x40
multiline_comment|/* Line Status Address Register */
DECL|macro|IRCC_LSAR
mdefine_line|#define IRCC_LSAR&t;&t;&t;&t;&t;0x03
DECL|macro|IRCC_LSAR_ADDRESS_MASK
mdefine_line|#define IRCC_LSAR_ADDRESS_MASK&t;&t;0x07
multiline_comment|/* Line Control Register A */
DECL|macro|IRCC_LCR_A
mdefine_line|#define IRCC_LCR_A                 0x04
DECL|macro|IRCC_LCR_A_FIFO_RESET
mdefine_line|#define   IRCC_LCR_A_FIFO_RESET    0x80
DECL|macro|IRCC_LCR_A_FAST
mdefine_line|#define   IRCC_LCR_A_FAST          0x40
DECL|macro|IRCC_LCR_A_GP_DATA
mdefine_line|#define   IRCC_LCR_A_GP_DATA       0x20
DECL|macro|IRCC_LCR_A_RAW_TX
mdefine_line|#define   IRCC_LCR_A_RAW_TX        0x10
DECL|macro|IRCC_LCR_A_RAW_RX
mdefine_line|#define   IRCC_LCR_A_RAW_RX        0x08
DECL|macro|IRCC_LCR_A_ABORT
mdefine_line|#define   IRCC_LCR_A_ABORT         0x04
DECL|macro|IRCC_LCR_A_DATA_DONE
mdefine_line|#define   IRCC_LCR_A_DATA_DONE     0x02
multiline_comment|/* Line Control Register B */
DECL|macro|IRCC_LCR_B
mdefine_line|#define IRCC_LCR_B                 0x05
DECL|macro|IRCC_LCR_B_SCE_DISABLED
mdefine_line|#define   IRCC_LCR_B_SCE_DISABLED  0x00
DECL|macro|IRCC_LCR_B_SCE_TRANSMIT
mdefine_line|#define   IRCC_LCR_B_SCE_TRANSMIT  0x40
DECL|macro|IRCC_LCR_B_SCE_RECEIVE
mdefine_line|#define   IRCC_LCR_B_SCE_RECEIVE   0x80
DECL|macro|IRCC_LCR_B_SCE_UNDEFINED
mdefine_line|#define   IRCC_LCR_B_SCE_UNDEFINED 0xc0
DECL|macro|IRCC_LCR_B_SIP_ENABLE
mdefine_line|#define   IRCC_LCR_B_SIP_ENABLE&t;   0x20
DECL|macro|IRCC_LCR_B_BRICK_WALL
mdefine_line|#define   IRCC_LCR_B_BRICK_WALL    0x10
multiline_comment|/* Bus Status Register */
DECL|macro|IRCC_BSR
mdefine_line|#define IRCC_BSR                   0x06
DECL|macro|IRCC_BSR_NOT_EMPTY
mdefine_line|#define   IRCC_BSR_NOT_EMPTY&t;   0x80
DECL|macro|IRCC_BSR_FIFO_FULL
mdefine_line|#define   IRCC_BSR_FIFO_FULL&t;   0x40
DECL|macro|IRCC_BSR_TIMEOUT
mdefine_line|#define   IRCC_BSR_TIMEOUT&t;   0x20
multiline_comment|/* Register block 1 */
DECL|macro|IRCC_FIFO_THRESHOLD
mdefine_line|#define IRCC_FIFO_THRESHOLD&t;&t;&t;0x02
DECL|macro|IRCC_SCE_CFGA
mdefine_line|#define IRCC_SCE_CFGA&t;&t;&t;&t;0x00
DECL|macro|IRCC_CFGA_AUX_IR
mdefine_line|#define   IRCC_CFGA_AUX_IR&t;&t;&t;0x80
DECL|macro|IRCC_CFGA_HALF_DUPLEX
mdefine_line|#define   IRCC_CFGA_HALF_DUPLEX&t;&t;0x04
DECL|macro|IRCC_CFGA_TX_POLARITY
mdefine_line|#define   IRCC_CFGA_TX_POLARITY&t;&t;0x02
DECL|macro|IRCC_CFGA_RX_POLARITY
mdefine_line|#define   IRCC_CFGA_RX_POLARITY&t;&t;0x01
DECL|macro|IRCC_CFGA_COM
mdefine_line|#define   IRCC_CFGA_COM&t;&t;&t;&t;0x00
DECL|macro|IRCC_SCE_CFGA_BLOCK_CTRL_BITS_MASK
mdefine_line|#define&t;&t;IRCC_SCE_CFGA_BLOCK_CTRL_BITS_MASK&t;0x87
DECL|macro|IRCC_CFGA_IRDA_SIR_A
mdefine_line|#define   &t;IRCC_CFGA_IRDA_SIR_A&t;0x08
DECL|macro|IRCC_CFGA_ASK_SIR
mdefine_line|#define   &t;IRCC_CFGA_ASK_SIR&t;&t;0x10
DECL|macro|IRCC_CFGA_IRDA_SIR_B
mdefine_line|#define   &t;IRCC_CFGA_IRDA_SIR_B&t;0x18
DECL|macro|IRCC_CFGA_IRDA_HDLC
mdefine_line|#define   &t;IRCC_CFGA_IRDA_HDLC&t;&t;0x20
DECL|macro|IRCC_CFGA_IRDA_4PPM
mdefine_line|#define&t;&t;IRCC_CFGA_IRDA_4PPM&t;&t;0x28
DECL|macro|IRCC_CFGA_CONSUMER
mdefine_line|#define&t;&t;IRCC_CFGA_CONSUMER&t;&t;0x30
DECL|macro|IRCC_CFGA_RAW_IR
mdefine_line|#define&t;&t;IRCC_CFGA_RAW_IR&t;&t;0x38
DECL|macro|IRCC_CFGA_OTHER
mdefine_line|#define     IRCC_CFGA_OTHER&t;&t;&t;0x40
DECL|macro|IRCC_IR_HDLC
mdefine_line|#define IRCC_IR_HDLC               0x04
DECL|macro|IRCC_IR_4PPM
mdefine_line|#define IRCC_IR_4PPM               0x01
DECL|macro|IRCC_IR_CONSUMER
mdefine_line|#define IRCC_IR_CONSUMER           0x02
DECL|macro|IRCC_SCE_CFGB
mdefine_line|#define IRCC_SCE_CFGB&t;           0x01
DECL|macro|IRCC_CFGB_LOOPBACK
mdefine_line|#define IRCC_CFGB_LOOPBACK         0x20
DECL|macro|IRCC_CFGB_LPBCK_TX_CRC
mdefine_line|#define IRCC_CFGB_LPBCK_TX_CRC&t;   0x10
DECL|macro|IRCC_CFGB_NOWAIT
mdefine_line|#define IRCC_CFGB_NOWAIT&t;   0x08
DECL|macro|IRCC_CFGB_STRING_MOVE
mdefine_line|#define IRCC_CFGB_STRING_MOVE&t;   0x04
DECL|macro|IRCC_CFGB_DMA_BURST
mdefine_line|#define IRCC_CFGB_DMA_BURST &t;   0x02
DECL|macro|IRCC_CFGB_DMA_ENABLE
mdefine_line|#define IRCC_CFGB_DMA_ENABLE&t;   0x01
DECL|macro|IRCC_CFGB_MUX_COM
mdefine_line|#define IRCC_CFGB_MUX_COM          0x00
DECL|macro|IRCC_CFGB_MUX_IR
mdefine_line|#define IRCC_CFGB_MUX_IR           0x40
DECL|macro|IRCC_CFGB_MUX_AUX
mdefine_line|#define IRCC_CFGB_MUX_AUX          0x80
DECL|macro|IRCC_CFGB_MUX_INACTIVE
mdefine_line|#define IRCC_CFGB_MUX_INACTIVE&t;   0xc0
multiline_comment|/* Register block 3 - Identification Registers! */
DECL|macro|IRCC_ID_HIGH
mdefine_line|#define IRCC_ID_HIGH&t;           0x00   /* 0x10 */
DECL|macro|IRCC_ID_LOW
mdefine_line|#define IRCC_ID_LOW&t;           0x01   /* 0xB8 */
DECL|macro|IRCC_CHIP_ID
mdefine_line|#define IRCC_CHIP_ID &t;           0x02   /* 0xF1 */
DECL|macro|IRCC_VERSION
mdefine_line|#define IRCC_VERSION&t;           0x03   /* 0x01 */
DECL|macro|IRCC_INTERFACE
mdefine_line|#define IRCC_INTERFACE&t;           0x04   /* low 4 = DMA, high 4 = IRQ */
DECL|macro|IRCC_INTERFACE_DMA_MASK
mdefine_line|#define &t;IRCC_INTERFACE_DMA_MASK&t;0x0F   /* low 4 = DMA, high 4 = IRQ */
DECL|macro|IRCC_INTERFACE_IRQ_MASK
mdefine_line|#define &t;IRCC_INTERFACE_IRQ_MASK&t;0xF0   /* low 4 = DMA, high 4 = IRQ */
multiline_comment|/* Register block 4 - IrDA */
DECL|macro|IRCC_CONTROL
mdefine_line|#define IRCC_CONTROL               0x00
DECL|macro|IRCC_BOF_COUNT_LO
mdefine_line|#define IRCC_BOF_COUNT_LO          0x01 /* Low byte */
DECL|macro|IRCC_BOF_COUNT_HI
mdefine_line|#define IRCC_BOF_COUNT_HI          0x00 /* High nibble (bit 0-3) */
DECL|macro|IRCC_BRICKWALL_CNT_LO
mdefine_line|#define IRCC_BRICKWALL_CNT_LO      0x02 /* Low byte */
DECL|macro|IRCC_BRICKWALL_CNT_HI
mdefine_line|#define IRCC_BRICKWALL_CNT_HI      0x03 /* High nibble (bit 4-7) */
DECL|macro|IRCC_TX_SIZE_LO
mdefine_line|#define IRCC_TX_SIZE_LO            0x04 /* Low byte */
DECL|macro|IRCC_TX_SIZE_HI
mdefine_line|#define IRCC_TX_SIZE_HI            0x03 /* High nibble (bit 0-3) */
DECL|macro|IRCC_RX_SIZE_HI
mdefine_line|#define IRCC_RX_SIZE_HI            0x05 /* High nibble (bit 0-3) */
DECL|macro|IRCC_RX_SIZE_LO
mdefine_line|#define IRCC_RX_SIZE_LO            0x06 /* Low byte */
DECL|macro|IRCC_1152
mdefine_line|#define IRCC_1152                  0x80
DECL|macro|IRCC_CRC
mdefine_line|#define IRCC_CRC                   0x40
multiline_comment|/* Register block 5 - IrDA */
DECL|macro|IRCC_ATC
mdefine_line|#define IRCC_ATC&t;&t;&t;&t;&t;0x00
DECL|macro|IRCC_ATC_nPROGREADY
mdefine_line|#define &t;IRCC_ATC_nPROGREADY&t;&t;0x80
DECL|macro|IRCC_ATC_SPEED
mdefine_line|#define &t;IRCC_ATC_SPEED&t;&t;&t;0x40
DECL|macro|IRCC_ATC_ENABLE
mdefine_line|#define &t;IRCC_ATC_ENABLE&t;&t;&t;0x20
DECL|macro|IRCC_ATC_MASK
mdefine_line|#define &t;IRCC_ATC_MASK&t;&t;&t;0xE0
DECL|macro|IRCC_IRHALFDUPLEX_TIMEOUT
mdefine_line|#define IRCC_IRHALFDUPLEX_TIMEOUT&t;0x01
DECL|macro|IRCC_SCE_TX_DELAY_TIMER
mdefine_line|#define IRCC_SCE_TX_DELAY_TIMER&t;&t;0x02
multiline_comment|/*&n; * Other definitions&n; */
DECL|macro|SMSC_IRCC2_MAX_SIR_SPEED
mdefine_line|#define SMSC_IRCC2_MAX_SIR_SPEED&t;&t;115200
DECL|macro|SMSC_IRCC2_FIR_CHIP_IO_EXTENT
mdefine_line|#define SMSC_IRCC2_FIR_CHIP_IO_EXTENT &t;8
DECL|macro|SMSC_IRCC2_SIR_CHIP_IO_EXTENT
mdefine_line|#define SMSC_IRCC2_SIR_CHIP_IO_EXTENT &t;8
DECL|macro|SMSC_IRCC2_FIFO_SIZE
mdefine_line|#define SMSC_IRCC2_FIFO_SIZE&t;&t;&t;16
DECL|macro|SMSC_IRCC2_FIFO_THRESHOLD
mdefine_line|#define SMSC_IRCC2_FIFO_THRESHOLD&t;&t;64
multiline_comment|/* Max DMA buffer size needed = (data_size + 6) * (window_size) + 6; */
DECL|macro|SMSC_IRCC2_RX_BUFF_TRUESIZE
mdefine_line|#define SMSC_IRCC2_RX_BUFF_TRUESIZE&t;&t;14384
DECL|macro|SMSC_IRCC2_TX_BUFF_TRUESIZE
mdefine_line|#define SMSC_IRCC2_TX_BUFF_TRUESIZE&t;&t;14384
DECL|macro|SMSC_IRCC2_MIN_TURN_TIME
mdefine_line|#define SMSC_IRCC2_MIN_TURN_TIME&t;&t;0x07
DECL|macro|SMSC_IRCC2_WINDOW_SIZE
mdefine_line|#define SMSC_IRCC2_WINDOW_SIZE&t;&t;&t;0x07
multiline_comment|/* Maximum wait for hw transmitter to finish */
DECL|macro|SMSC_IRCC2_HW_TRANSMITTER_TIMEOUT_US
mdefine_line|#define SMSC_IRCC2_HW_TRANSMITTER_TIMEOUT_US&t;1000&t;/* 1 ms */
multiline_comment|/* Maximum wait for ATC transceiver programming to finish */
DECL|macro|SMSC_IRCC2_ATC_PROGRAMMING_TIMEOUT_JIFFIES
mdefine_line|#define SMSC_IRCC2_ATC_PROGRAMMING_TIMEOUT_JIFFIES 1
macro_line|#endif /* SMSC_IRCC2_H */
eof
