multiline_comment|/*&n; *  linux/include/asm-arm/iomd.h&n; *&n; *  Copyright (C) 1999 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  This file contains information out the IOMD ASIC used in the&n; *  Acorn RiscPC and subsequently integrated into the CLPS7500 chips.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef __ASSEMBLY__
DECL|macro|__IOMD
mdefine_line|#define __IOMD(offset)&t;(IO_IOMD_BASE + (offset &gt;&gt; 2))
macro_line|#else
DECL|macro|__IOMD
mdefine_line|#define __IOMD(offset)&t;offset
macro_line|#endif
DECL|macro|IOMD_CONTROL
mdefine_line|#define IOMD_CONTROL&t;__IOMD(0x000)
DECL|macro|IOMD_KARTTX
mdefine_line|#define IOMD_KARTTX&t;__IOMD(0x004)
DECL|macro|IOMD_KARTRX
mdefine_line|#define IOMD_KARTRX&t;__IOMD(0x004)
DECL|macro|IOMD_KCTRL
mdefine_line|#define IOMD_KCTRL&t;__IOMD(0x008)
macro_line|#ifdef CONFIG_ARCH_CLPS7500
DECL|macro|IOMD_IOLINES
mdefine_line|#define IOMD_IOLINES&t;__IOMD(0x00C)
macro_line|#endif
DECL|macro|IOMD_IRQSTATA
mdefine_line|#define IOMD_IRQSTATA&t;__IOMD(0x010)
DECL|macro|IOMD_IRQREQA
mdefine_line|#define IOMD_IRQREQA&t;__IOMD(0x014)
DECL|macro|IOMD_IRQCLRA
mdefine_line|#define IOMD_IRQCLRA&t;__IOMD(0x014)
DECL|macro|IOMD_IRQMASKA
mdefine_line|#define IOMD_IRQMASKA&t;__IOMD(0x018)
macro_line|#ifdef CONFIG_ARCH_CLPS7500
DECL|macro|IOMD_SUSMODE
mdefine_line|#define IOMD_SUSMODE&t;__IOMD(0x01C)
macro_line|#endif
DECL|macro|IOMD_IRQSTATB
mdefine_line|#define IOMD_IRQSTATB&t;__IOMD(0x020)
DECL|macro|IOMD_IRQREQB
mdefine_line|#define IOMD_IRQREQB&t;__IOMD(0x024)
DECL|macro|IOMD_IRQMASKB
mdefine_line|#define IOMD_IRQMASKB&t;__IOMD(0x028)
DECL|macro|IOMD_FIQSTAT
mdefine_line|#define IOMD_FIQSTAT&t;__IOMD(0x030)
DECL|macro|IOMD_FIQREQ
mdefine_line|#define IOMD_FIQREQ&t;__IOMD(0x034)
DECL|macro|IOMD_FIQMASK
mdefine_line|#define IOMD_FIQMASK&t;__IOMD(0x038)
macro_line|#ifdef CONFIG_ARCH_CLPS7500
DECL|macro|IOMD_CLKCTL
mdefine_line|#define IOMD_CLKCTL&t;__IOMD(0x03C)
macro_line|#endif
DECL|macro|IOMD_T0CNTL
mdefine_line|#define IOMD_T0CNTL&t;__IOMD(0x040)
DECL|macro|IOMD_T0LTCHL
mdefine_line|#define IOMD_T0LTCHL&t;__IOMD(0x040)
DECL|macro|IOMD_T0CNTH
mdefine_line|#define IOMD_T0CNTH&t;__IOMD(0x044)
DECL|macro|IOMD_T0LTCHH
mdefine_line|#define IOMD_T0LTCHH&t;__IOMD(0x044)
DECL|macro|IOMD_T0GO
mdefine_line|#define IOMD_T0GO&t;__IOMD(0x048)
DECL|macro|IOMD_T0LATCH
mdefine_line|#define IOMD_T0LATCH&t;__IOMD(0x04c)
DECL|macro|IOMD_T1CNTL
mdefine_line|#define IOMD_T1CNTL&t;__IOMD(0x050)
DECL|macro|IOMD_T1LTCHL
mdefine_line|#define IOMD_T1LTCHL&t;__IOMD(0x050)
DECL|macro|IOMD_T1CNTH
mdefine_line|#define IOMD_T1CNTH&t;__IOMD(0x054)
DECL|macro|IOMD_T1LTCHH
mdefine_line|#define IOMD_T1LTCHH&t;__IOMD(0x054)
DECL|macro|IOMD_T1GO
mdefine_line|#define IOMD_T1GO&t;__IOMD(0x058)
DECL|macro|IOMD_T1LATCH
mdefine_line|#define IOMD_T1LATCH&t;__IOMD(0x05c)
macro_line|#ifdef CONFIG_ARCH_CLPS7500
DECL|macro|IOMD_IRQSTATC
mdefine_line|#define IOMD_IRQSTATC&t;__IOMD(0x060)
DECL|macro|IOMD_IRQREQC
mdefine_line|#define IOMD_IRQREQC&t;__IOMD(0x064)
DECL|macro|IOMD_IRQMASKC
mdefine_line|#define IOMD_IRQMASKC&t;__IOMD(0x068)
DECL|macro|IOMD_VIDMUX
mdefine_line|#define IOMD_VIDMUX&t;__IOMD(0x06c)
DECL|macro|IOMD_IRQSTATD
mdefine_line|#define IOMD_IRQSTATD&t;__IOMD(0x070)
DECL|macro|IOMD_IRQREQD
mdefine_line|#define IOMD_IRQREQD&t;__IOMD(0x074)
DECL|macro|IOMD_IRQMASKD
mdefine_line|#define IOMD_IRQMASKD&t;__IOMD(0x078)
macro_line|#endif
DECL|macro|IOMD_ROMCR0
mdefine_line|#define IOMD_ROMCR0&t;__IOMD(0x080)
DECL|macro|IOMD_ROMCR1
mdefine_line|#define IOMD_ROMCR1&t;__IOMD(0x084)
macro_line|#ifdef CONFIG_ARCH_RPC
DECL|macro|IOMD_DRAMCR
mdefine_line|#define IOMD_DRAMCR&t;__IOMD(0x088)
macro_line|#endif
DECL|macro|IOMD_REFCR
mdefine_line|#define IOMD_REFCR&t;__IOMD(0x08C)
DECL|macro|IOMD_FSIZE
mdefine_line|#define IOMD_FSIZE&t;__IOMD(0x090)
DECL|macro|IOMD_ID0
mdefine_line|#define IOMD_ID0&t;__IOMD(0x094)
DECL|macro|IOMD_ID1
mdefine_line|#define IOMD_ID1&t;__IOMD(0x098)
DECL|macro|IOMD_VERSION
mdefine_line|#define IOMD_VERSION&t;__IOMD(0x09C)
macro_line|#ifdef CONFIG_ARCH_RPC
DECL|macro|IOMD_MOUSEX
mdefine_line|#define IOMD_MOUSEX&t;__IOMD(0x0A0)
DECL|macro|IOMD_MOUSEY
mdefine_line|#define IOMD_MOUSEY&t;__IOMD(0x0A4)
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_CLPS7500
DECL|macro|IOMD_MSEDAT
mdefine_line|#define IOMD_MSEDAT&t;__IOMD(0x0A8)
DECL|macro|IOMD_MSECTL
mdefine_line|#define IOMD_MSECTL&t;__IOMD(0x0Ac)
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_RPC
DECL|macro|IOMD_DMATCR
mdefine_line|#define IOMD_DMATCR&t;__IOMD(0x0C0)
macro_line|#endif
DECL|macro|IOMD_IOTCR
mdefine_line|#define IOMD_IOTCR&t;__IOMD(0x0C4)
DECL|macro|IOMD_ECTCR
mdefine_line|#define IOMD_ECTCR&t;__IOMD(0x0C8)
macro_line|#ifdef CONFIG_ARCH_RPC
DECL|macro|IOMD_DMAEXT
mdefine_line|#define IOMD_DMAEXT&t;__IOMD(0x0CC)
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_CLPS7500
DECL|macro|IOMD_ASTCR
mdefine_line|#define IOMD_ASTCR&t;__IOMD(0x0CC)
DECL|macro|IOMD_DRAMCR
mdefine_line|#define IOMD_DRAMCR&t;__IOMD(0x0D0)
DECL|macro|IOMD_SELFREF
mdefine_line|#define IOMD_SELFREF&t;__IOMD(0x0D4)
DECL|macro|IOMD_ATODICR
mdefine_line|#define IOMD_ATODICR&t;__IOMD(0x0E0)
DECL|macro|IOMD_ATODSR
mdefine_line|#define IOMD_ATODSR&t;__IOMD(0x0E4)
DECL|macro|IOMD_ATODCC
mdefine_line|#define IOMD_ATODCC&t;__IOMD(0x0E8)
DECL|macro|IOMD_ATODCNT1
mdefine_line|#define IOMD_ATODCNT1&t;__IOMD(0x0EC)
DECL|macro|IOMD_ATODCNT2
mdefine_line|#define IOMD_ATODCNT2&t;__IOMD(0x0F0)
DECL|macro|IOMD_ATODCNT3
mdefine_line|#define IOMD_ATODCNT3&t;__IOMD(0x0F4)
DECL|macro|IOMD_ATODCNT4
mdefine_line|#define IOMD_ATODCNT4&t;__IOMD(0x0F8)
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_RPC
DECL|macro|DMA_EXT_IO0
mdefine_line|#define DMA_EXT_IO0&t;1
DECL|macro|DMA_EXT_IO1
mdefine_line|#define DMA_EXT_IO1&t;2
DECL|macro|DMA_EXT_IO2
mdefine_line|#define DMA_EXT_IO2&t;4
DECL|macro|DMA_EXT_IO3
mdefine_line|#define DMA_EXT_IO3&t;8
DECL|macro|IOMD_IO0CURA
mdefine_line|#define IOMD_IO0CURA&t;__IOMD(0x100)
DECL|macro|IOMD_IO0ENDA
mdefine_line|#define IOMD_IO0ENDA&t;__IOMD(0x104)
DECL|macro|IOMD_IO0CURB
mdefine_line|#define IOMD_IO0CURB&t;__IOMD(0x108)
DECL|macro|IOMD_IO0ENDB
mdefine_line|#define IOMD_IO0ENDB&t;__IOMD(0x10C)
DECL|macro|IOMD_IO0CR
mdefine_line|#define IOMD_IO0CR&t;__IOMD(0x110)
DECL|macro|IOMD_IO0ST
mdefine_line|#define IOMD_IO0ST&t;__IOMD(0x114)
DECL|macro|IOMD_IO1CURA
mdefine_line|#define IOMD_IO1CURA&t;__IOMD(0x120)
DECL|macro|IOMD_IO1ENDA
mdefine_line|#define IOMD_IO1ENDA&t;__IOMD(0x124)
DECL|macro|IOMD_IO1CURB
mdefine_line|#define IOMD_IO1CURB&t;__IOMD(0x128)
DECL|macro|IOMD_IO1ENDB
mdefine_line|#define IOMD_IO1ENDB&t;__IOMD(0x12C)
DECL|macro|IOMD_IO1CR
mdefine_line|#define IOMD_IO1CR&t;__IOMD(0x130)
DECL|macro|IOMD_IO1ST
mdefine_line|#define IOMD_IO1ST&t;__IOMD(0x134)
DECL|macro|IOMD_IO2CURA
mdefine_line|#define IOMD_IO2CURA&t;__IOMD(0x140)
DECL|macro|IOMD_IO2ENDA
mdefine_line|#define IOMD_IO2ENDA&t;__IOMD(0x144)
DECL|macro|IOMD_IO2CURB
mdefine_line|#define IOMD_IO2CURB&t;__IOMD(0x148)
DECL|macro|IOMD_IO2ENDB
mdefine_line|#define IOMD_IO2ENDB&t;__IOMD(0x14C)
DECL|macro|IOMD_IO2CR
mdefine_line|#define IOMD_IO2CR&t;__IOMD(0x150)
DECL|macro|IOMD_IO2ST
mdefine_line|#define IOMD_IO2ST&t;__IOMD(0x154)
DECL|macro|IOMD_IO3CURA
mdefine_line|#define IOMD_IO3CURA&t;__IOMD(0x160)
DECL|macro|IOMD_IO3ENDA
mdefine_line|#define IOMD_IO3ENDA&t;__IOMD(0x164)
DECL|macro|IOMD_IO3CURB
mdefine_line|#define IOMD_IO3CURB&t;__IOMD(0x168)
DECL|macro|IOMD_IO3ENDB
mdefine_line|#define IOMD_IO3ENDB&t;__IOMD(0x16C)
DECL|macro|IOMD_IO3CR
mdefine_line|#define IOMD_IO3CR&t;__IOMD(0x170)
DECL|macro|IOMD_IO3ST
mdefine_line|#define IOMD_IO3ST&t;__IOMD(0x174)
macro_line|#endif
DECL|macro|IOMD_SD0CURA
mdefine_line|#define IOMD_SD0CURA&t;__IOMD(0x180)
DECL|macro|IOMD_SD0ENDA
mdefine_line|#define IOMD_SD0ENDA&t;__IOMD(0x184)
DECL|macro|IOMD_SD0CURB
mdefine_line|#define IOMD_SD0CURB&t;__IOMD(0x188)
DECL|macro|IOMD_SD0ENDB
mdefine_line|#define IOMD_SD0ENDB&t;__IOMD(0x18C)
DECL|macro|IOMD_SD0CR
mdefine_line|#define IOMD_SD0CR&t;__IOMD(0x190)
DECL|macro|IOMD_SD0ST
mdefine_line|#define IOMD_SD0ST&t;__IOMD(0x194)
macro_line|#ifdef CONFIG_ARCH_RPC
DECL|macro|IOMD_SD1CURA
mdefine_line|#define IOMD_SD1CURA&t;__IOMD(0x1A0)
DECL|macro|IOMD_SD1ENDA
mdefine_line|#define IOMD_SD1ENDA&t;__IOMD(0x1A4)
DECL|macro|IOMD_SD1CURB
mdefine_line|#define IOMD_SD1CURB&t;__IOMD(0x1A8)
DECL|macro|IOMD_SD1ENDB
mdefine_line|#define IOMD_SD1ENDB&t;__IOMD(0x1AC)
DECL|macro|IOMD_SD1CR
mdefine_line|#define IOMD_SD1CR&t;__IOMD(0x1B0)
DECL|macro|IOMD_SD1ST
mdefine_line|#define IOMD_SD1ST&t;__IOMD(0x1B4)
macro_line|#endif
DECL|macro|IOMD_CURSCUR
mdefine_line|#define IOMD_CURSCUR&t;__IOMD(0x1C0)
DECL|macro|IOMD_CURSINIT
mdefine_line|#define IOMD_CURSINIT&t;__IOMD(0x1C4)
DECL|macro|IOMD_VIDCUR
mdefine_line|#define IOMD_VIDCUR&t;__IOMD(0x1D0)
DECL|macro|IOMD_VIDEND
mdefine_line|#define IOMD_VIDEND&t;__IOMD(0x1D4)
DECL|macro|IOMD_VIDSTART
mdefine_line|#define IOMD_VIDSTART&t;__IOMD(0x1D8)
DECL|macro|IOMD_VIDINIT
mdefine_line|#define IOMD_VIDINIT&t;__IOMD(0x1DC)
DECL|macro|IOMD_VIDCR
mdefine_line|#define IOMD_VIDCR&t;__IOMD(0x1E0)
DECL|macro|IOMD_DMASTAT
mdefine_line|#define IOMD_DMASTAT&t;__IOMD(0x1F0)
DECL|macro|IOMD_DMAREQ
mdefine_line|#define IOMD_DMAREQ&t;__IOMD(0x1F4)
DECL|macro|IOMD_DMAMASK
mdefine_line|#define IOMD_DMAMASK&t;__IOMD(0x1F8)
DECL|macro|DMA_END_S
mdefine_line|#define DMA_END_S&t;(1 &lt;&lt; 31)
DECL|macro|DMA_END_L
mdefine_line|#define DMA_END_L&t;(1 &lt;&lt; 30)
DECL|macro|DMA_CR_C
mdefine_line|#define DMA_CR_C&t;0x80
DECL|macro|DMA_CR_D
mdefine_line|#define DMA_CR_D&t;0x40
DECL|macro|DMA_CR_E
mdefine_line|#define DMA_CR_E&t;0x20
DECL|macro|DMA_ST_OFL
mdefine_line|#define DMA_ST_OFL&t;4
DECL|macro|DMA_ST_INT
mdefine_line|#define DMA_ST_INT&t;2
DECL|macro|DMA_ST_AB
mdefine_line|#define DMA_ST_AB&t;1
macro_line|#ifndef IOC_CONTROL
multiline_comment|/*&n; * IOC compatability&n; */
DECL|macro|IOC_CONTROL
mdefine_line|#define IOC_CONTROL&t;IOMD_CONTROL
DECL|macro|IOC_IRQSTATA
mdefine_line|#define IOC_IRQSTATA&t;IOMD_IRQSTATA
DECL|macro|IOC_IRQREQA
mdefine_line|#define IOC_IRQREQA&t;IOMD_IRQREQA
DECL|macro|IOC_IRQCLRA
mdefine_line|#define IOC_IRQCLRA&t;IOMD_IRQCLRA
DECL|macro|IOC_IRQMASKA
mdefine_line|#define IOC_IRQMASKA&t;IOMD_IRQMASKA
DECL|macro|IOC_IRQSTATB
mdefine_line|#define IOC_IRQSTATB&t;IOMD_IRQSTATB
DECL|macro|IOC_IRQREQB
mdefine_line|#define IOC_IRQREQB&t;IOMD_IRQREQB
DECL|macro|IOC_IRQMASKB
mdefine_line|#define IOC_IRQMASKB&t;IOMD_IRQMASKB
DECL|macro|IOC_FIQSTAT
mdefine_line|#define IOC_FIQSTAT&t;IOMD_FIQSTAT
DECL|macro|IOC_FIQREQ
mdefine_line|#define IOC_FIQREQ&t;IOMD_FIQREQ
DECL|macro|IOC_FIQMASK
mdefine_line|#define IOC_FIQMASK&t;IOMD_FIQMASK
DECL|macro|IOC_T0CNTL
mdefine_line|#define IOC_T0CNTL&t;IOMD_T0CNTL
DECL|macro|IOC_T0LTCHL
mdefine_line|#define IOC_T0LTCHL&t;IOMD_T0LTCHL
DECL|macro|IOC_T0CNTH
mdefine_line|#define IOC_T0CNTH&t;IOMD_T0CNTH
DECL|macro|IOC_T0LTCHH
mdefine_line|#define IOC_T0LTCHH&t;IOMD_T0LTCHH
DECL|macro|IOC_T0GO
mdefine_line|#define IOC_T0GO&t;IOMD_T0GO
DECL|macro|IOC_T0LATCH
mdefine_line|#define IOC_T0LATCH&t;IOMD_T0LATCH
DECL|macro|IOC_T1CNTL
mdefine_line|#define IOC_T1CNTL&t;IOMD_T1CNTL
DECL|macro|IOC_T1LTCHL
mdefine_line|#define IOC_T1LTCHL&t;IOMD_T1LTCHL
DECL|macro|IOC_T1CNTH
mdefine_line|#define IOC_T1CNTH&t;IOMD_T1CNTH
DECL|macro|IOC_T1LTCHH
mdefine_line|#define IOC_T1LTCHH&t;IOMD_T1LTCHH
DECL|macro|IOC_T1GO
mdefine_line|#define IOC_T1GO&t;IOMD_T1GO
DECL|macro|IOC_T1LATCH
mdefine_line|#define IOC_T1LATCH&t;IOMD_T1LATCH
macro_line|#endif
multiline_comment|/*&n; * DMA (MEMC) compatability&n; */
DECL|macro|HALF_SAM
mdefine_line|#define HALF_SAM&t;vram_half_sam
DECL|macro|VDMA_ALIGNMENT
mdefine_line|#define VDMA_ALIGNMENT&t;(HALF_SAM * 2)
DECL|macro|VDMA_XFERSIZE
mdefine_line|#define VDMA_XFERSIZE&t;(HALF_SAM)
DECL|macro|VDMA_INIT
mdefine_line|#define VDMA_INIT&t;IOMD_VIDINIT
DECL|macro|VDMA_START
mdefine_line|#define VDMA_START&t;IOMD_VIDSTART
DECL|macro|VDMA_END
mdefine_line|#define VDMA_END&t;IOMD_VIDEND
macro_line|#ifndef __ASSEMBLY__
r_extern
r_int
r_int
id|vram_half_sam
suffix:semicolon
DECL|macro|video_set_dma
mdefine_line|#define video_set_dma(start,end,offset)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;outl (SCREEN_START + start, VDMA_START);&t;&t;&bslash;&n;&t;outl (SCREEN_START + end - VDMA_XFERSIZE, VDMA_END);&t;&bslash;&n;&t;if (offset &gt;= end - VDMA_XFERSIZE)&t;&t;&t;&bslash;&n;&t;&t;offset |= 0x40000000;&t;&t;&t;&t;&bslash;&n;&t;outl (SCREEN_START + offset, VDMA_INIT);&t;&t;&bslash;&n;} while (0)
macro_line|#endif
eof
