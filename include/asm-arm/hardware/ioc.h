multiline_comment|/*&n; *  linux/include/asm-arm/hardware/ioc.h&n; *&n; *  Copyright (C) Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Use these macros to read/write the IOC.  All it does is perform the actual&n; *  read/write.&n; */
macro_line|#ifndef IOC_CONTROL
macro_line|#ifndef __ASSEMBLY__
DECL|macro|__IOC
mdefine_line|#define __IOC(offset)&t;(IOC_BASE + (offset &gt;&gt; 2))
macro_line|#else
DECL|macro|__IOC
mdefine_line|#define __IOC(offset)&t;offset
macro_line|#endif
DECL|macro|IOC_CONTROL
mdefine_line|#define IOC_CONTROL&t;__IOC(0x00)
DECL|macro|IOC_KARTTX
mdefine_line|#define IOC_KARTTX&t;__IOC(0x04)
DECL|macro|IOC_KARTRX
mdefine_line|#define IOC_KARTRX&t;__IOC(0x04)
DECL|macro|IOC_IRQSTATA
mdefine_line|#define IOC_IRQSTATA&t;__IOC(0x10)
DECL|macro|IOC_IRQREQA
mdefine_line|#define IOC_IRQREQA&t;__IOC(0x14)
DECL|macro|IOC_IRQCLRA
mdefine_line|#define IOC_IRQCLRA&t;__IOC(0x14)
DECL|macro|IOC_IRQMASKA
mdefine_line|#define IOC_IRQMASKA&t;__IOC(0x18)
DECL|macro|IOC_IRQSTATB
mdefine_line|#define IOC_IRQSTATB&t;__IOC(0x20)
DECL|macro|IOC_IRQREQB
mdefine_line|#define IOC_IRQREQB&t;__IOC(0x24)
DECL|macro|IOC_IRQMASKB
mdefine_line|#define IOC_IRQMASKB&t;__IOC(0x28)
DECL|macro|IOC_FIQSTAT
mdefine_line|#define IOC_FIQSTAT&t;__IOC(0x30)
DECL|macro|IOC_FIQREQ
mdefine_line|#define IOC_FIQREQ&t;__IOC(0x34)
DECL|macro|IOC_FIQMASK
mdefine_line|#define IOC_FIQMASK&t;__IOC(0x38)
DECL|macro|IOC_T0CNTL
mdefine_line|#define IOC_T0CNTL&t;__IOC(0x40)
DECL|macro|IOC_T0LTCHL
mdefine_line|#define IOC_T0LTCHL&t;__IOC(0x40)
DECL|macro|IOC_T0CNTH
mdefine_line|#define IOC_T0CNTH&t;__IOC(0x44)
DECL|macro|IOC_T0LTCHH
mdefine_line|#define IOC_T0LTCHH&t;__IOC(0x44)
DECL|macro|IOC_T0GO
mdefine_line|#define IOC_T0GO&t;__IOC(0x48)
DECL|macro|IOC_T0LATCH
mdefine_line|#define IOC_T0LATCH&t;__IOC(0x4c)
DECL|macro|IOC_T1CNTL
mdefine_line|#define IOC_T1CNTL&t;__IOC(0x50)
DECL|macro|IOC_T1LTCHL
mdefine_line|#define IOC_T1LTCHL&t;__IOC(0x50)
DECL|macro|IOC_T1CNTH
mdefine_line|#define IOC_T1CNTH&t;__IOC(0x54)
DECL|macro|IOC_T1LTCHH
mdefine_line|#define IOC_T1LTCHH&t;__IOC(0x54)
DECL|macro|IOC_T1GO
mdefine_line|#define IOC_T1GO&t;__IOC(0x58)
DECL|macro|IOC_T1LATCH
mdefine_line|#define IOC_T1LATCH&t;__IOC(0x5c)
DECL|macro|IOC_T2CNTL
mdefine_line|#define IOC_T2CNTL&t;__IOC(0x60)
DECL|macro|IOC_T2LTCHL
mdefine_line|#define IOC_T2LTCHL&t;__IOC(0x60)
DECL|macro|IOC_T2CNTH
mdefine_line|#define IOC_T2CNTH&t;__IOC(0x64)
DECL|macro|IOC_T2LTCHH
mdefine_line|#define IOC_T2LTCHH&t;__IOC(0x64)
DECL|macro|IOC_T2GO
mdefine_line|#define IOC_T2GO&t;__IOC(0x68)
DECL|macro|IOC_T2LATCH
mdefine_line|#define IOC_T2LATCH&t;__IOC(0x6c)
DECL|macro|IOC_T3CNTL
mdefine_line|#define IOC_T3CNTL&t;__IOC(0x70)
DECL|macro|IOC_T3LTCHL
mdefine_line|#define IOC_T3LTCHL&t;__IOC(0x70)
DECL|macro|IOC_T3CNTH
mdefine_line|#define IOC_T3CNTH&t;__IOC(0x74)
DECL|macro|IOC_T3LTCHH
mdefine_line|#define IOC_T3LTCHH&t;__IOC(0x74)
DECL|macro|IOC_T3GO
mdefine_line|#define IOC_T3GO&t;__IOC(0x78)
DECL|macro|IOC_T3LATCH
mdefine_line|#define IOC_T3LATCH&t;__IOC(0x7c)
macro_line|#endif
eof
