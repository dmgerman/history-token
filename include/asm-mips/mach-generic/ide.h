multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994-1996  Linus Torvalds &amp; authors&n; *&n; * Copied from i386; many of the especially older MIPS or ISA-based platforms&n; * are basically identical.  Using this file probably implies i8259 PIC&n; * support in a system but the very least interrupt numbers 0 - 15 need to&n; * be put aside for legacy devices.&n; */
macro_line|#ifndef __ASM_MACH_GENERIC_IDE_H
DECL|macro|__ASM_MACH_GENERIC_IDE_H
mdefine_line|#define __ASM_MACH_GENERIC_IDE_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#ifndef MAX_HWIFS
macro_line|# ifdef CONFIG_BLK_DEV_IDEPCI
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;10
macro_line|# else
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;6
macro_line|# endif
macro_line|#endif
DECL|macro|IDE_ARCH_OBSOLETE_DEFAULTS
mdefine_line|#define IDE_ARCH_OBSOLETE_DEFAULTS
DECL|function|ide_probe_legacy
r_static
id|__inline__
r_int
id|ide_probe_legacy
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_PCI
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev
op_assign
id|pci_get_class
c_func
(paren
id|PCI_CLASS_BRIDGE_EISA
op_lshift
l_int|8
comma
l_int|NULL
)paren
)paren
op_ne
l_int|NULL
op_logical_or
(paren
id|dev
op_assign
id|pci_get_class
c_func
(paren
id|PCI_CLASS_BRIDGE_ISA
op_lshift
l_int|8
comma
l_int|NULL
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|pci_dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
macro_line|#elif defined(CONFIG_EISA) || defined(CONFIG_ISA)
r_return
l_int|1
suffix:semicolon
macro_line|#else
r_return
l_int|0
suffix:semicolon
macro_line|#endif
)brace
DECL|function|ide_default_irq
r_static
id|__inline__
r_int
id|ide_default_irq
c_func
(paren
r_int
r_int
id|base
)paren
(brace
r_if
c_cond
(paren
id|ide_probe_legacy
c_func
(paren
)paren
)paren
r_switch
c_cond
(paren
id|base
)paren
(brace
r_case
l_int|0x1f0
suffix:colon
r_return
l_int|14
suffix:semicolon
r_case
l_int|0x170
suffix:colon
r_return
l_int|15
suffix:semicolon
r_case
l_int|0x1e8
suffix:colon
r_return
l_int|11
suffix:semicolon
r_case
l_int|0x168
suffix:colon
r_return
l_int|10
suffix:semicolon
r_case
l_int|0x1e0
suffix:colon
r_return
l_int|8
suffix:semicolon
r_case
l_int|0x160
suffix:colon
r_return
l_int|12
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ide_default_io_base
r_static
id|__inline__
r_int
r_int
id|ide_default_io_base
c_func
(paren
r_int
id|index
)paren
(brace
r_if
c_cond
(paren
id|ide_probe_legacy
c_func
(paren
)paren
)paren
r_switch
c_cond
(paren
id|index
)paren
(brace
r_case
l_int|0
suffix:colon
r_return
l_int|0x1f0
suffix:semicolon
r_case
l_int|1
suffix:colon
r_return
l_int|0x170
suffix:semicolon
r_case
l_int|2
suffix:colon
r_return
l_int|0x1e8
suffix:semicolon
r_case
l_int|3
suffix:colon
r_return
l_int|0x168
suffix:semicolon
r_case
l_int|4
suffix:colon
r_return
l_int|0x1e0
suffix:semicolon
r_case
l_int|5
suffix:colon
r_return
l_int|0x160
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|IDE_ARCH_OBSOLETE_INIT
mdefine_line|#define IDE_ARCH_OBSOLETE_INIT
DECL|macro|ide_default_io_ctl
mdefine_line|#define ide_default_io_ctl(base)&t;((base) + 0x206) /* obsolete */
macro_line|#ifdef CONFIG_BLK_DEV_IDEPCI
DECL|macro|ide_init_default_irq
mdefine_line|#define ide_init_default_irq(base)&t;(0)
macro_line|#else
DECL|macro|ide_init_default_irq
mdefine_line|#define ide_init_default_irq(base)&t;ide_default_irq(base)
macro_line|#endif
multiline_comment|/* MIPS port and memory-mapped I/O string operations.  */
DECL|macro|__ide_insw
mdefine_line|#define __ide_insw&t;insw
DECL|macro|__ide_insl
mdefine_line|#define __ide_insl&t;insl
DECL|macro|__ide_outsw
mdefine_line|#define __ide_outsw&t;outsw
DECL|macro|__ide_outsl
mdefine_line|#define __ide_outsl&t;outsl
DECL|macro|__ide_mm_insw
mdefine_line|#define __ide_mm_insw&t;readsw
DECL|macro|__ide_mm_insl
mdefine_line|#define __ide_mm_insl&t;readsl
DECL|macro|__ide_mm_outsw
mdefine_line|#define __ide_mm_outsw&t;writesw
DECL|macro|__ide_mm_outsl
mdefine_line|#define __ide_mm_outsl&t;writesl
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_MACH_GENERIC_IDE_H */
eof
