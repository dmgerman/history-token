multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * IDE routines for typical pc-like legacy IDE configurations.&n; *&n; * Copyright (C) 1998, 1999, 2001, 2003 by Ralf Baechle&n; */
macro_line|#ifndef __ASM_MACH_GENERIC_IDE_H
DECL|macro|__ASM_MACH_GENERIC_IDE_H
mdefine_line|#define __ASM_MACH_GENERIC_IDE_H
macro_line|#include &lt;linux/config.h&gt;
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
DECL|function|ide_default_irq
r_static
r_inline
r_int
id|ide_default_irq
c_func
(paren
r_int
r_int
id|base
)paren
(brace
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
)brace
DECL|function|ide_default_io_base
r_static
r_inline
r_int
r_int
id|ide_default_io_base
c_func
(paren
r_int
id|index
)paren
(brace
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
macro_line|#endif /* __ASM_MACH_GENERIC_IDE_H */
eof
