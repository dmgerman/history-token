multiline_comment|/*&n; *  linux/include/asm-arm/hardware/ioc.h&n; *&n; *  Copyright (C) Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Use these macros to read/write the IOC.  All it does is perform the actual&n; *  read/write.&n; */
macro_line|#ifndef __ASMARM_HARDWARE_IOC_H
DECL|macro|__ASMARM_HARDWARE_IOC_H
mdefine_line|#define __ASMARM_HARDWARE_IOC_H
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * We use __raw_base variants here so that we give the compiler the&n; * chance to keep IOC_BASE in a register.&n; */
DECL|macro|ioc_readb
mdefine_line|#define ioc_readb(off)&t;&t;__raw_base_readb(IOC_BASE, (off))
DECL|macro|ioc_writeb
mdefine_line|#define ioc_writeb(val,off)&t;__raw_base_writeb(val, IOC_BASE, (off))
macro_line|#endif
DECL|macro|IOC_CONTROL
mdefine_line|#define IOC_CONTROL&t;(0x00)
DECL|macro|IOC_KARTTX
mdefine_line|#define IOC_KARTTX&t;(0x04)
DECL|macro|IOC_KARTRX
mdefine_line|#define IOC_KARTRX&t;(0x04)
DECL|macro|IOC_IRQSTATA
mdefine_line|#define IOC_IRQSTATA&t;(0x10)
DECL|macro|IOC_IRQREQA
mdefine_line|#define IOC_IRQREQA&t;(0x14)
DECL|macro|IOC_IRQCLRA
mdefine_line|#define IOC_IRQCLRA&t;(0x14)
DECL|macro|IOC_IRQMASKA
mdefine_line|#define IOC_IRQMASKA&t;(0x18)
DECL|macro|IOC_IRQSTATB
mdefine_line|#define IOC_IRQSTATB&t;(0x20)
DECL|macro|IOC_IRQREQB
mdefine_line|#define IOC_IRQREQB&t;(0x24)
DECL|macro|IOC_IRQMASKB
mdefine_line|#define IOC_IRQMASKB&t;(0x28)
DECL|macro|IOC_FIQSTAT
mdefine_line|#define IOC_FIQSTAT&t;(0x30)
DECL|macro|IOC_FIQREQ
mdefine_line|#define IOC_FIQREQ&t;(0x34)
DECL|macro|IOC_FIQMASK
mdefine_line|#define IOC_FIQMASK&t;(0x38)
DECL|macro|IOC_T0CNTL
mdefine_line|#define IOC_T0CNTL&t;(0x40)
DECL|macro|IOC_T0LTCHL
mdefine_line|#define IOC_T0LTCHL&t;(0x40)
DECL|macro|IOC_T0CNTH
mdefine_line|#define IOC_T0CNTH&t;(0x44)
DECL|macro|IOC_T0LTCHH
mdefine_line|#define IOC_T0LTCHH&t;(0x44)
DECL|macro|IOC_T0GO
mdefine_line|#define IOC_T0GO&t;(0x48)
DECL|macro|IOC_T0LATCH
mdefine_line|#define IOC_T0LATCH&t;(0x4c)
DECL|macro|IOC_T1CNTL
mdefine_line|#define IOC_T1CNTL&t;(0x50)
DECL|macro|IOC_T1LTCHL
mdefine_line|#define IOC_T1LTCHL&t;(0x50)
DECL|macro|IOC_T1CNTH
mdefine_line|#define IOC_T1CNTH&t;(0x54)
DECL|macro|IOC_T1LTCHH
mdefine_line|#define IOC_T1LTCHH&t;(0x54)
DECL|macro|IOC_T1GO
mdefine_line|#define IOC_T1GO&t;(0x58)
DECL|macro|IOC_T1LATCH
mdefine_line|#define IOC_T1LATCH&t;(0x5c)
DECL|macro|IOC_T2CNTL
mdefine_line|#define IOC_T2CNTL&t;(0x60)
DECL|macro|IOC_T2LTCHL
mdefine_line|#define IOC_T2LTCHL&t;(0x60)
DECL|macro|IOC_T2CNTH
mdefine_line|#define IOC_T2CNTH&t;(0x64)
DECL|macro|IOC_T2LTCHH
mdefine_line|#define IOC_T2LTCHH&t;(0x64)
DECL|macro|IOC_T2GO
mdefine_line|#define IOC_T2GO&t;(0x68)
DECL|macro|IOC_T2LATCH
mdefine_line|#define IOC_T2LATCH&t;(0x6c)
DECL|macro|IOC_T3CNTL
mdefine_line|#define IOC_T3CNTL&t;(0x70)
DECL|macro|IOC_T3LTCHL
mdefine_line|#define IOC_T3LTCHL&t;(0x70)
DECL|macro|IOC_T3CNTH
mdefine_line|#define IOC_T3CNTH&t;(0x74)
DECL|macro|IOC_T3LTCHH
mdefine_line|#define IOC_T3LTCHH&t;(0x74)
DECL|macro|IOC_T3GO
mdefine_line|#define IOC_T3GO&t;(0x78)
DECL|macro|IOC_T3LATCH
mdefine_line|#define IOC_T3LATCH&t;(0x7c)
macro_line|#endif
eof
