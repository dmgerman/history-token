multiline_comment|/*&n; * drivers/i2c/i2c-ibm_iic.h&n; *&n; * Support for the IIC peripheral on IBM PPC 4xx&n; * &n; * Copyright (c) 2003 Zultys Technologies.&n; * Eugene Surovegin &lt;eugene.surovegin@zultys.com&gt; or &lt;ebs@ebshome.net&gt;&n; *&n; * Based on original work by &n; * &t;Ian DaSilva  &lt;idasilva@mvista.com&gt;&n; *      Armin Kuster &lt;akuster@mvista.com&gt;&n; * &t;Matt Porter  &lt;mporter@mvista.com&gt;&n; *&n; *      Copyright 2000-2003 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
macro_line|#ifndef __I2C_IBM_IIC_H_
DECL|macro|__I2C_IBM_IIC_H_
mdefine_line|#define __I2C_IBM_IIC_H_
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/i2c.h&gt; 
DECL|struct|iic_regs
r_struct
id|iic_regs
(brace
DECL|member|mdbuf
id|u16
id|mdbuf
suffix:semicolon
DECL|member|sbbuf
id|u16
id|sbbuf
suffix:semicolon
DECL|member|lmadr
id|u8
id|lmadr
suffix:semicolon
DECL|member|hmadr
id|u8
id|hmadr
suffix:semicolon
DECL|member|cntl
id|u8
id|cntl
suffix:semicolon
DECL|member|mdcntl
id|u8
id|mdcntl
suffix:semicolon
DECL|member|sts
id|u8
id|sts
suffix:semicolon
DECL|member|extsts
id|u8
id|extsts
suffix:semicolon
DECL|member|lsadr
id|u8
id|lsadr
suffix:semicolon
DECL|member|hsadr
id|u8
id|hsadr
suffix:semicolon
DECL|member|clkdiv
id|u8
id|clkdiv
suffix:semicolon
DECL|member|intmsk
id|u8
id|intmsk
suffix:semicolon
DECL|member|xfrcnt
id|u8
id|xfrcnt
suffix:semicolon
DECL|member|xtcntlss
id|u8
id|xtcntlss
suffix:semicolon
DECL|member|directcntl
id|u8
id|directcntl
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ibm_iic_private
r_struct
id|ibm_iic_private
(brace
DECL|member|adap
r_struct
id|i2c_adapter
id|adap
suffix:semicolon
DECL|member|vaddr
r_volatile
r_struct
id|iic_regs
id|__iomem
op_star
id|vaddr
suffix:semicolon
DECL|member|wq
id|wait_queue_head_t
id|wq
suffix:semicolon
DECL|member|idx
r_int
id|idx
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|fast_mode
r_int
id|fast_mode
suffix:semicolon
DECL|member|clckdiv
id|u8
id|clckdiv
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* IICx_CNTL register */
DECL|macro|CNTL_HMT
mdefine_line|#define CNTL_HMT&t;0x80
DECL|macro|CNTL_AMD
mdefine_line|#define CNTL_AMD&t;0x40
DECL|macro|CNTL_TCT_MASK
mdefine_line|#define CNTL_TCT_MASK&t;0x30
DECL|macro|CNTL_TCT_SHIFT
mdefine_line|#define CNTL_TCT_SHIFT&t;4
DECL|macro|CNTL_RPST
mdefine_line|#define CNTL_RPST&t;0x08
DECL|macro|CNTL_CHT
mdefine_line|#define CNTL_CHT&t;0x04 
DECL|macro|CNTL_RW
mdefine_line|#define CNTL_RW&t;&t;0x02
DECL|macro|CNTL_PT
mdefine_line|#define CNTL_PT&t;&t;0x01
multiline_comment|/* IICx_MDCNTL register */
DECL|macro|MDCNTL_FSDB
mdefine_line|#define MDCNTL_FSDB&t;0x80
DECL|macro|MDCNTL_FMDB
mdefine_line|#define MDCNTL_FMDB&t;0x40
DECL|macro|MDCNTL_EGC
mdefine_line|#define MDCNTL_EGC&t;0x20
DECL|macro|MDCNTL_FSM
mdefine_line|#define MDCNTL_FSM&t;0x10
DECL|macro|MDCNTL_ESM
mdefine_line|#define MDCNTL_ESM&t;0x08
DECL|macro|MDCNTL_EINT
mdefine_line|#define MDCNTL_EINT&t;0x04
DECL|macro|MDCNTL_EUBS
mdefine_line|#define MDCNTL_EUBS&t;0x02
DECL|macro|MDCNTL_HSCL
mdefine_line|#define MDCNTL_HSCL&t;0x01
multiline_comment|/* IICx_STS register */
DECL|macro|STS_SSS
mdefine_line|#define STS_SSS&t;&t;0x80
DECL|macro|STS_SLPR
mdefine_line|#define STS_SLPR&t;0x40
DECL|macro|STS_MDBS
mdefine_line|#define STS_MDBS&t;0x20
DECL|macro|STS_MDBF
mdefine_line|#define STS_MDBF&t;0x10
DECL|macro|STS_SCMP
mdefine_line|#define STS_SCMP&t;0x08
DECL|macro|STS_ERR
mdefine_line|#define STS_ERR&t;&t;0x04
DECL|macro|STS_IRQA
mdefine_line|#define STS_IRQA&t;0x02
DECL|macro|STS_PT
mdefine_line|#define STS_PT&t;&t;0x01
multiline_comment|/* IICx_EXTSTS register */
DECL|macro|EXTSTS_IRQP
mdefine_line|#define EXTSTS_IRQP&t;0x80
DECL|macro|EXTSTS_BCS_MASK
mdefine_line|#define EXTSTS_BCS_MASK&t;0x70
DECL|macro|EXTSTS_BCS_FREE
mdefine_line|#define   EXTSTS_BCS_FREE  0x40
DECL|macro|EXTSTS_IRQD
mdefine_line|#define EXTSTS_IRQD&t;0x08
DECL|macro|EXTSTS_LA
mdefine_line|#define EXTSTS_LA&t;0x04
DECL|macro|EXTSTS_ICT
mdefine_line|#define EXTSTS_ICT&t;0x02
DECL|macro|EXTSTS_XFRA
mdefine_line|#define EXTSTS_XFRA&t;0x01
multiline_comment|/* IICx_INTRMSK register */
DECL|macro|INTRMSK_EIRC
mdefine_line|#define INTRMSK_EIRC&t;0x80
DECL|macro|INTRMSK_EIRS
mdefine_line|#define INTRMSK_EIRS&t;0x40
DECL|macro|INTRMSK_EIWC
mdefine_line|#define INTRMSK_EIWC&t;0x20
DECL|macro|INTRMSK_EIWS
mdefine_line|#define INTRMSK_EIWS&t;0x10
DECL|macro|INTRMSK_EIHE
mdefine_line|#define INTRMSK_EIHE&t;0x08
DECL|macro|INTRMSK_EIIC
mdefine_line|#define INTRMSK_EIIC&t;0x04
DECL|macro|INTRMSK_EITA
mdefine_line|#define INTRMSK_EITA&t;0x02
DECL|macro|INTRMSK_EIMTC
mdefine_line|#define INTRMSK_EIMTC&t;0x01
multiline_comment|/* IICx_XFRCNT register */
DECL|macro|XFRCNT_MTC_MASK
mdefine_line|#define XFRCNT_MTC_MASK&t;0x07
multiline_comment|/* IICx_XTCNTLSS register */
DECL|macro|XTCNTLSS_SRC
mdefine_line|#define XTCNTLSS_SRC&t;0x80
DECL|macro|XTCNTLSS_SRS
mdefine_line|#define XTCNTLSS_SRS&t;0x40
DECL|macro|XTCNTLSS_SWC
mdefine_line|#define XTCNTLSS_SWC&t;0x20
DECL|macro|XTCNTLSS_SWS
mdefine_line|#define XTCNTLSS_SWS&t;0x10
DECL|macro|XTCNTLSS_SRST
mdefine_line|#define XTCNTLSS_SRST&t;0x01
multiline_comment|/* IICx_DIRECTCNTL register */
DECL|macro|DIRCNTL_SDAC
mdefine_line|#define DIRCNTL_SDAC&t;0x08
DECL|macro|DIRCNTL_SCC
mdefine_line|#define DIRCNTL_SCC&t;0x04
DECL|macro|DIRCNTL_MSDA
mdefine_line|#define DIRCNTL_MSDA&t;0x02
DECL|macro|DIRCNTL_MSC
mdefine_line|#define DIRCNTL_MSC&t;0x01
multiline_comment|/* Check if we really control the I2C bus and bus is free */
DECL|macro|DIRCTNL_FREE
mdefine_line|#define DIRCTNL_FREE(v)&t;(((v) &amp; 0x0f) == 0x0f)
macro_line|#endif /* __I2C_IBM_IIC_H_ */
eof
