multiline_comment|/*&n; * include/asm-sh/dreamcast/pci.h&n; *&n; * Copyright (C) 2001, 2002  M. R. Brown&n; * Copyright (C) 2002, 2003  Paul Mundt&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef __ASM_SH_DREAMCAST_PCI_H
DECL|macro|__ASM_SH_DREAMCAST_PCI_H
mdefine_line|#define __ASM_SH_DREAMCAST_PCI_H
macro_line|#include &lt;asm/mach/sysasic.h&gt;
DECL|macro|GAPSPCI_REGS
mdefine_line|#define&t;GAPSPCI_REGS&t;&t;0x01001400
DECL|macro|GAPSPCI_DMA_BASE
mdefine_line|#define GAPSPCI_DMA_BASE&t;0x01840000
DECL|macro|GAPSPCI_DMA_SIZE
mdefine_line|#define GAPSPCI_DMA_SIZE&t;32768
DECL|macro|GAPSPCI_BBA_CONFIG
mdefine_line|#define GAPSPCI_BBA_CONFIG&t;0x01001600
DECL|macro|GAPSPCI_BBA_CONFIG_SIZE
mdefine_line|#define GAPSPCI_BBA_CONFIG_SIZE&t;0x2000
DECL|macro|GAPSPCI_IRQ
mdefine_line|#define&t;GAPSPCI_IRQ&t;&t;HW_EVENT_EXTERNAL
macro_line|#endif /* __ASM_SH_DREAMCAST_PCI_H */
eof
