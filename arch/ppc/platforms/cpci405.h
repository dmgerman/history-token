multiline_comment|/*&n; * CPCI-405 board specific definitions&n; *&n; * Copyright (c) 2001 Stefan Roese (stefan.roese@esd-electronics.com)&n; */
macro_line|#ifndef __ASM_CPCI405_H__
DECL|macro|__ASM_CPCI405_H__
mdefine_line|#define __ASM_CPCI405_H__
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* We have a 405GP core */
macro_line|#include &lt;platforms/ibm405gp.h&gt;
macro_line|#include &lt;asm/ppcboot.h&gt;
multiline_comment|/* Some 4xx parts use a different timebase frequency from the internal clock.&n;*/
DECL|macro|bi_tbfreq
mdefine_line|#define bi_tbfreq bi_intfreq
multiline_comment|/* Early initialization address mapping for block_io.&n; * Standard 405GP map.&n; */
DECL|macro|PPC4xx_PCI_IO_PADDR
mdefine_line|#define PPC4xx_PCI_IO_PADDR&t;((uint)PPC405_PCI_PHY_IO_BASE)
DECL|macro|PPC4xx_PCI_IO_VADDR
mdefine_line|#define PPC4xx_PCI_IO_VADDR&t;PPC4xx_PCI_IO_PADDR
DECL|macro|PPC4xx_PCI_IO_SIZE
mdefine_line|#define PPC4xx_PCI_IO_SIZE&t;((uint)64*1024)
DECL|macro|PPC4xx_PCI_CFG_PADDR
mdefine_line|#define PPC4xx_PCI_CFG_PADDR&t;((uint)PPC405_PCI_CONFIG_ADDR)
DECL|macro|PPC4xx_PCI_CFG_VADDR
mdefine_line|#define PPC4xx_PCI_CFG_VADDR&t;PPC4xx_PCI_CFG_PADDR
DECL|macro|PPC4xx_PCI_CFG_SIZE
mdefine_line|#define PPC4xx_PCI_CFG_SIZE&t;((uint)4*1024)
DECL|macro|PPC4xx_PCI_LCFG_PADDR
mdefine_line|#define PPC4xx_PCI_LCFG_PADDR&t;((uint)0xef400000)
DECL|macro|PPC4xx_PCI_LCFG_VADDR
mdefine_line|#define PPC4xx_PCI_LCFG_VADDR&t;PPC4xx_PCI_LCFG_PADDR
DECL|macro|PPC4xx_PCI_LCFG_SIZE
mdefine_line|#define PPC4xx_PCI_LCFG_SIZE&t;((uint)4*1024)
DECL|macro|PPC4xx_ONB_IO_PADDR
mdefine_line|#define PPC4xx_ONB_IO_PADDR&t;((uint)0xef600000)
DECL|macro|PPC4xx_ONB_IO_VADDR
mdefine_line|#define PPC4xx_ONB_IO_VADDR&t;PPC4xx_ONB_IO_PADDR
DECL|macro|PPC4xx_ONB_IO_SIZE
mdefine_line|#define PPC4xx_ONB_IO_SIZE&t;((uint)4*1024)
macro_line|#ifdef CONFIG_PPC405GP_INTERNAL_CLOCK
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD&t;&t;201600
macro_line|#else
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD&t;&t;691200
macro_line|#endif
DECL|macro|PPC4xx_MACHINE_NAME
mdefine_line|#define PPC4xx_MACHINE_NAME &quot;esd CPCI-405&quot;
macro_line|#endif&t;/* __ASM_CPCI405_H__ */
eof
