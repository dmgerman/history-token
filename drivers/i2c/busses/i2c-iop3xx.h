multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/* i2c-iop3xx.h algorithm driver definitions private to i2c-iop3xx.c         */
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/*   Copyright (C) 2003 Peter Milne, D-TACQ Solutions Ltd&n; *                      &lt;Peter dot Milne at D hyphen TACQ dot com&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation, version 2.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                */
multiline_comment|/* ------------------------------------------------------------------------- */
macro_line|#ifndef I2C_IOP3XX_H
DECL|macro|I2C_IOP3XX_H
mdefine_line|#define I2C_IOP3XX_H 1
multiline_comment|/*&n; * iop321 hardware bit definitions&n; */
DECL|macro|IOP3XX_ICR_FAST_MODE
mdefine_line|#define IOP3XX_ICR_FAST_MODE&t;0x8000&t;/* 1=400kBps, 0=100kBps */
DECL|macro|IOP3XX_ICR_UNIT_RESET
mdefine_line|#define IOP3XX_ICR_UNIT_RESET&t;0x4000&t;/* 1=RESET */
DECL|macro|IOP3XX_ICR_SAD_IE
mdefine_line|#define IOP3XX_ICR_SAD_IE&t;0x2000&t;/* 1=Slave Detect Interrupt Enable */
DECL|macro|IOP3XX_ICR_ALD_IE
mdefine_line|#define IOP3XX_ICR_ALD_IE&t;0x1000&t;/* 1=Arb Loss Detect Interrupt Enable */
DECL|macro|IOP3XX_ICR_SSD_IE
mdefine_line|#define IOP3XX_ICR_SSD_IE&t;0x0800&t;/* 1=Slave STOP Detect Interrupt Enable */
DECL|macro|IOP3XX_ICR_BERR_IE
mdefine_line|#define IOP3XX_ICR_BERR_IE&t;0x0400&t;/* 1=Bus Error Interrupt Enable */
DECL|macro|IOP3XX_ICR_RXFULL_IE
mdefine_line|#define IOP3XX_ICR_RXFULL_IE&t;0x0200&t;/* 1=Receive Full Interrupt Enable */
DECL|macro|IOP3XX_ICR_TXEMPTY_IE
mdefine_line|#define IOP3XX_ICR_TXEMPTY_IE&t;0x0100&t;/* 1=Transmit Empty Interrupt Enable */
DECL|macro|IOP3XX_ICR_GCD
mdefine_line|#define IOP3XX_ICR_GCD&t;&t;0x0080&t;/* 1=General Call Disable */
multiline_comment|/*&n; * IOP3XX_ICR_GCD: 1 disables response as slave. &quot;This bit must be set&n; * when sending a master mode general call message from the I2C unit&quot;&n; */
DECL|macro|IOP3XX_ICR_UE
mdefine_line|#define IOP3XX_ICR_UE&t;&t;0x0040&t;/* 1=Unit Enable */
multiline_comment|/*&n; * &quot;NOTE: To avoid I2C bus integrity problems, &n; * the user needs to ensure that the GPIO Output Data Register - &n; * GPOD bits associated with an I2C port are cleared prior to setting &n; * the enable bit for that I2C serial port. &n; * The user prepares to enable I2C port 0 and &n; * I2C port 1 by clearing GPOD bits 7:6 and GPOD bits 5:4, respectively.&n; */
DECL|macro|IOP3XX_ICR_SCLEN
mdefine_line|#define IOP3XX_ICR_SCLEN&t;0x0020&t;/* 1=SCL enable for master mode */
DECL|macro|IOP3XX_ICR_MABORT
mdefine_line|#define IOP3XX_ICR_MABORT&t;0x0010&t;/* 1=Send a STOP with no data &n;&t;&t;&t;&t;&t; * NB TBYTE must be clear */
DECL|macro|IOP3XX_ICR_TBYTE
mdefine_line|#define IOP3XX_ICR_TBYTE&t;0x0008&t;/* 1=Send/Receive a byte. i2c clears */
DECL|macro|IOP3XX_ICR_NACK
mdefine_line|#define IOP3XX_ICR_NACK&t;&t;0x0004&t;/* 1=reply with NACK */
DECL|macro|IOP3XX_ICR_MSTOP
mdefine_line|#define IOP3XX_ICR_MSTOP&t;0x0002&t;/* 1=send a STOP after next data byte */
DECL|macro|IOP3XX_ICR_MSTART
mdefine_line|#define IOP3XX_ICR_MSTART&t;0x0001&t;/* 1=initiate a START */
DECL|macro|IOP3XX_ISR_BERRD
mdefine_line|#define IOP3XX_ISR_BERRD&t;0x0400&t;/* 1=BUS ERROR Detected */
DECL|macro|IOP3XX_ISR_SAD
mdefine_line|#define IOP3XX_ISR_SAD&t;&t;0x0200&t;/* 1=Slave ADdress Detected */
DECL|macro|IOP3XX_ISR_GCAD
mdefine_line|#define IOP3XX_ISR_GCAD&t;&t;0x0100&t;/* 1=General Call Address Detected */
DECL|macro|IOP3XX_ISR_RXFULL
mdefine_line|#define IOP3XX_ISR_RXFULL&t;0x0080&t;/* 1=Receive Full */
DECL|macro|IOP3XX_ISR_TXEMPTY
mdefine_line|#define IOP3XX_ISR_TXEMPTY&t;0x0040&t;/* 1=Transmit Empty */
DECL|macro|IOP3XX_ISR_ALD
mdefine_line|#define IOP3XX_ISR_ALD&t;&t;0x0020&t;/* 1=Arbitration Loss Detected */
DECL|macro|IOP3XX_ISR_SSD
mdefine_line|#define IOP3XX_ISR_SSD&t;&t;0x0010&t;/* 1=Slave STOP Detected */
DECL|macro|IOP3XX_ISR_BBUSY
mdefine_line|#define IOP3XX_ISR_BBUSY&t;0x0008&t;/* 1=Bus BUSY */
DECL|macro|IOP3XX_ISR_UNITBUSY
mdefine_line|#define IOP3XX_ISR_UNITBUSY&t;0x0004&t;/* 1=Unit Busy */
DECL|macro|IOP3XX_ISR_NACK
mdefine_line|#define IOP3XX_ISR_NACK&t;&t;0x0002&t;/* 1=Unit Rx or Tx a NACK */
DECL|macro|IOP3XX_ISR_RXREAD
mdefine_line|#define IOP3XX_ISR_RXREAD&t;0x0001&t;/* 1=READ 0=WRITE (R/W bit of slave addr */
DECL|macro|IOP3XX_ISR_CLEARBITS
mdefine_line|#define IOP3XX_ISR_CLEARBITS&t;0x07f0
DECL|macro|IOP3XX_ISAR_SAMASK
mdefine_line|#define IOP3XX_ISAR_SAMASK&t;0x007f
DECL|macro|IOP3XX_IDBR_MASK
mdefine_line|#define IOP3XX_IDBR_MASK&t;0x00ff
DECL|macro|IOP3XX_IBMR_SCL
mdefine_line|#define IOP3XX_IBMR_SCL&t;&t;0x0002
DECL|macro|IOP3XX_IBMR_SDA
mdefine_line|#define IOP3XX_IBMR_SDA&t;&t;0x0001
DECL|macro|IOP3XX_GPOD_I2C0
mdefine_line|#define IOP3XX_GPOD_I2C0&t;0x00c0&t;/* clear these bits to enable ch0 */
DECL|macro|IOP3XX_GPOD_I2C1
mdefine_line|#define IOP3XX_GPOD_I2C1&t;0x0030&t;/* clear these bits to enable ch1 */
DECL|macro|MYSAR
mdefine_line|#define MYSAR&t;&t;&t;0x02&t;/* SWAG a suitable slave address */
DECL|macro|I2C_ERR
mdefine_line|#define I2C_ERR&t;&t;&t;321
DECL|macro|I2C_ERR_BERR
mdefine_line|#define I2C_ERR_BERR&t;&t;(I2C_ERR+0)
DECL|macro|I2C_ERR_ALD
mdefine_line|#define I2C_ERR_ALD&t;&t;(I2C_ERR+1)
DECL|macro|CR_OFFSET
mdefine_line|#define&t;CR_OFFSET&t;&t;0
DECL|macro|SR_OFFSET
mdefine_line|#define&t;SR_OFFSET&t;&t;0x4
DECL|macro|SAR_OFFSET
mdefine_line|#define&t;SAR_OFFSET&t;&t;0x8
DECL|macro|DBR_OFFSET
mdefine_line|#define&t;DBR_OFFSET&t;&t;0xc
DECL|macro|CCR_OFFSET
mdefine_line|#define&t;CCR_OFFSET&t;&t;0x10
DECL|macro|BMR_OFFSET
mdefine_line|#define&t;BMR_OFFSET&t;&t;0x14
DECL|macro|IOP3XX_I2C_IO_SIZE
mdefine_line|#define&t;IOP3XX_I2C_IO_SIZE&t;0x18
DECL|struct|i2c_algo_iop3xx_data
r_struct
id|i2c_algo_iop3xx_data
(brace
DECL|member|ioaddr
id|u32
id|ioaddr
suffix:semicolon
DECL|member|waitq
id|wait_queue_head_t
id|waitq
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|SR_enabled
DECL|member|SR_received
id|u32
id|SR_enabled
comma
id|SR_received
suffix:semicolon
DECL|member|id
r_int
id|id
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* I2C_IOP3XX_H */
eof
