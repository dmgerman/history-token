multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/* i2c-iop3xx.h algorithm driver definitions private to i2c-iop3xx.c         */
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/*   Copyright (C) 2003 Peter Milne, D-TACQ Solutions Ltd&n; *                      &lt;Peter dot Milne at D hyphen TACQ dot com&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation, version 2.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                */
multiline_comment|/* ------------------------------------------------------------------------- */
macro_line|#ifndef I2C_IOP3XX_H
DECL|macro|I2C_IOP3XX_H
mdefine_line|#define I2C_IOP3XX_H 1
multiline_comment|/*&n; * iop321 hardware bit definitions&n; */
DECL|macro|IOP321_ICR_FAST_MODE
mdefine_line|#define IOP321_ICR_FAST_MODE  0x8000 /* 1=400kBps, 0=100kBps */
DECL|macro|IOP321_ICR_UNIT_RESET
mdefine_line|#define IOP321_ICR_UNIT_RESET 0x4000 /* 1=RESET */
DECL|macro|IOP321_ICR_SADIE
mdefine_line|#define IOP321_ICR_SADIE      0x2000 /* 1=Slave Detect Interrupt Enable */
DECL|macro|IOP321_ICR_ALDIE
mdefine_line|#define IOP321_ICR_ALDIE      0x1000 /* 1=Arb Loss Detect Interrupt Enable */
DECL|macro|IOP321_ICR_SSDIE
mdefine_line|#define IOP321_ICR_SSDIE      0x0800 /* 1=Slave STOP Detect Interrupt Enable */
DECL|macro|IOP321_ICR_BERRIE
mdefine_line|#define IOP321_ICR_BERRIE     0x0400 /* 1=Bus Error Interrupt Enable */
DECL|macro|IOP321_ICR_RXFULLIE
mdefine_line|#define IOP321_ICR_RXFULLIE   0x0200 /* 1=Receive Full Interrupt Enable */
DECL|macro|IOP321_ICR_TXEMPTYIE
mdefine_line|#define IOP321_ICR_TXEMPTYIE  0x0100 /* 1=Transmit Empty Interrupt Enable */
DECL|macro|IOP321_ICR_GCD
mdefine_line|#define IOP321_ICR_GCD        0x0080 /* 1=General Call Disable */
multiline_comment|/*&n; * IOP321_ICR_GCD: 1 disables response as slave. &quot;This bit must be set&n; * when sending a master mode general call message from the I2C unit&quot;&n; */
DECL|macro|IOP321_ICR_UE
mdefine_line|#define IOP321_ICR_UE         0x0040 /* 1=Unit Enable */
multiline_comment|/*&n; * &quot;NOTE: To avoid I2C bus integrity problems, &n; * the user needs to ensure that the GPIO Output Data Register - &n; * GPOD bits associated with an I2C port are cleared prior to setting &n; * the enable bit for that I2C serial port. &n; * The user prepares to enable I2C port 0 and &n; * I2C port 1 by clearing GPOD bits 7:6 and GPOD bits 5:4, respectively.&n; */
DECL|macro|IOP321_ICR_SCLEN
mdefine_line|#define IOP321_ICR_SCLEN     0x0020 /* 1=SCL enable for master mode */
DECL|macro|IOP321_ICR_MABORT
mdefine_line|#define IOP321_ICR_MABORT    0x0010 /* 1=Send a STOP with no data &n;                                     * NB TBYTE must be clear       */
DECL|macro|IOP321_ICR_TBYTE
mdefine_line|#define IOP321_ICR_TBYTE     0x0008 /* 1=Send/Receive a byte. i2c clears */
DECL|macro|IOP321_ICR_NACK
mdefine_line|#define IOP321_ICR_NACK      0x0004 /* 1=reply with NACK */
DECL|macro|IOP321_ICR_MSTOP
mdefine_line|#define IOP321_ICR_MSTOP     0x0002 /* 1=send a STOP after next data byte */
DECL|macro|IOP321_ICR_MSTART
mdefine_line|#define IOP321_ICR_MSTART    0x0001 /* 1=initiate a START */
DECL|macro|IOP321_ISR_BERRD
mdefine_line|#define IOP321_ISR_BERRD     0x0400 /* 1=BUS ERROR Detected */
DECL|macro|IOP321_ISR_SAD
mdefine_line|#define IOP321_ISR_SAD       0x0200 /* 1=Slave ADdress Detected */
DECL|macro|IOP321_ISR_GCAD
mdefine_line|#define IOP321_ISR_GCAD      0x0100 /* 1=General Call Address Detected */
DECL|macro|IOP321_ISR_RXFULL
mdefine_line|#define IOP321_ISR_RXFULL    0x0080 /* 1=Receive Full */
DECL|macro|IOP321_ISR_TXEMPTY
mdefine_line|#define IOP321_ISR_TXEMPTY   0x0040 /* 1=Transmit Empty */
DECL|macro|IOP321_ISR_ALD
mdefine_line|#define IOP321_ISR_ALD       0x0020 /* 1=Arbitration Loss Detected */
DECL|macro|IOP321_ISR_SSD
mdefine_line|#define IOP321_ISR_SSD       0x0010 /* 1=Slave STOP Detected */
DECL|macro|IOP321_ISR_BBUSY
mdefine_line|#define IOP321_ISR_BBUSY     0x0008 /* 1=Bus BUSY */
DECL|macro|IOP321_ISR_UNITBUSY
mdefine_line|#define IOP321_ISR_UNITBUSY  0x0004 /* 1=Unit Busy */
DECL|macro|IOP321_ISR_NACK
mdefine_line|#define IOP321_ISR_NACK      0x0002 /* 1=Unit Rx or Tx a NACK */
DECL|macro|IOP321_ISR_RXREAD
mdefine_line|#define IOP321_ISR_RXREAD    0x0001 /* 1=READ 0=WRITE (R/W bit of slave addr */
DECL|macro|IOP321_ISR_CLEARBITS
mdefine_line|#define IOP321_ISR_CLEARBITS 0x07f0
DECL|macro|IOP321_ISAR_SAMASK
mdefine_line|#define IOP321_ISAR_SAMASK   0x007f 
DECL|macro|IOP321_IDBR_MASK
mdefine_line|#define IOP321_IDBR_MASK     0x00ff
DECL|macro|IOP321_IBMR_SCL
mdefine_line|#define IOP321_IBMR_SCL      0x0002
DECL|macro|IOP321_IBMR_SDA
mdefine_line|#define IOP321_IBMR_SDA      0x0001
DECL|macro|IOP321_GPOD_I2C0
mdefine_line|#define IOP321_GPOD_I2C0     0x00c0  /* clear these bits to enable ch0 */
DECL|macro|IOP321_GPOD_I2C1
mdefine_line|#define IOP321_GPOD_I2C1     0x0030  /* clear these bits to enable ch1 */
DECL|macro|MYSAR
mdefine_line|#define MYSAR                0x02     /* SWAG a suitable slave address */
DECL|macro|I2C_ERR
mdefine_line|#define I2C_ERR              321
DECL|macro|I2C_ERR_BERR
mdefine_line|#define I2C_ERR_BERR         (I2C_ERR+0)
DECL|macro|I2C_ERR_ALD
mdefine_line|#define I2C_ERR_ALD          (I2C_ERR+1)
DECL|typedef|r32
r_typedef
r_volatile
id|u32
op_star
id|r32
suffix:semicolon
DECL|struct|iop3xx_biu
r_struct
id|iop3xx_biu
(brace
multiline_comment|/* Bus Interface Unit - the hardware */
multiline_comment|/* physical hardware defs - regs*/
DECL|member|CR
id|r32
id|CR
suffix:semicolon
DECL|member|SR
id|r32
id|SR
suffix:semicolon
DECL|member|SAR
id|r32
id|SAR
suffix:semicolon
DECL|member|DBR
id|r32
id|DBR
suffix:semicolon
DECL|member|BMR
id|r32
id|BMR
suffix:semicolon
multiline_comment|/* irq bit vector */
DECL|member|irq
id|u32
id|irq
suffix:semicolon
multiline_comment|/* stored flags */
DECL|member|SR_enabled
DECL|member|SR_received
id|u32
id|SR_enabled
comma
id|SR_received
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|i2c_algo_iop3xx_data
r_struct
id|i2c_algo_iop3xx_data
(brace
DECL|member|channel
r_int
id|channel
suffix:semicolon
DECL|member|waitq
id|wait_queue_head_t
id|waitq
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
DECL|member|biu
r_struct
id|iop3xx_biu
op_star
id|biu
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|REGION_START
mdefine_line|#define REGION_START( adap )  ((u32)((adap)-&gt;biu-&gt;CR))
DECL|macro|REGION_END
mdefine_line|#define REGION_END( adap )    ((u32)((adap)-&gt;biu-&gt;BMR+1))
DECL|macro|REGION_LENGTH
mdefine_line|#define REGION_LENGTH( adap ) (REGION_END(adap)-REGION_START(adap))
DECL|macro|IRQ_STATUS_MASK
mdefine_line|#define IRQ_STATUS_MASK( adap ) (1&lt;&lt;adap-&gt;biu-&gt;irq)
macro_line|#endif /* I2C_IOP3XX_H */
eof
