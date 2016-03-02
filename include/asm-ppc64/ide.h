multiline_comment|/*&n; *  linux/include/asm-ppc/ide.h&n; *&n; *  Copyright (C) 1994-1996 Linus Torvalds &amp; authors&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
multiline_comment|/*&n; *  This file contains the ppc64 architecture specific IDE code.&n; */
macro_line|#ifndef __ASMPPC64_IDE_H
DECL|macro|__ASMPPC64_IDE_H
mdefine_line|#define __ASMPPC64_IDE_H
macro_line|#ifdef __KERNEL__
macro_line|#ifndef MAX_HWIFS
DECL|macro|MAX_HWIFS
macro_line|# define MAX_HWIFS&t;4
macro_line|#endif
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
r_return
l_int|0
suffix:semicolon
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|IDE_ARCH_OBSOLETE_INIT
mdefine_line|#define IDE_ARCH_OBSOLETE_INIT
DECL|macro|ide_default_io_ctl
mdefine_line|#define ide_default_io_ctl(base)&t;((base) + 0x206) /* obsolete */
DECL|macro|ide_init_default_irq
mdefine_line|#define ide_init_default_irq(base)&t;(0)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASMPPC64_IDE_H */
eof
