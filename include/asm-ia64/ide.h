multiline_comment|/*&n; *  linux/include/asm-ia64/ide.h&n; *&n; *  Copyright (C) 1994-1996  Linus Torvalds &amp; authors&n; */
multiline_comment|/*&n; *  This file contains the ia64 architecture specific IDE code.&n; */
macro_line|#ifndef __ASM_IA64_IDE_H
DECL|macro|__ASM_IA64_IDE_H
mdefine_line|#define __ASM_IA64_IDE_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#ifndef MAX_HWIFS
macro_line|# ifdef CONFIG_PCI
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;10
macro_line|# else
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;6
macro_line|# endif
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
id|isa_irq_to_vector
c_func
(paren
l_int|14
)paren
suffix:semicolon
r_case
l_int|0x170
suffix:colon
r_return
id|isa_irq_to_vector
c_func
(paren
l_int|15
)paren
suffix:semicolon
r_case
l_int|0x1e8
suffix:colon
r_return
id|isa_irq_to_vector
c_func
(paren
l_int|11
)paren
suffix:semicolon
r_case
l_int|0x168
suffix:colon
r_return
id|isa_irq_to_vector
c_func
(paren
l_int|10
)paren
suffix:semicolon
r_case
l_int|0x1e0
suffix:colon
r_return
id|isa_irq_to_vector
c_func
(paren
l_int|8
)paren
suffix:semicolon
r_case
l_int|0x160
suffix:colon
r_return
id|isa_irq_to_vector
c_func
(paren
l_int|12
)paren
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
macro_line|#ifdef CONFIG_PCI
DECL|macro|ide_init_default_irq
mdefine_line|#define ide_init_default_irq(base)&t;(0)
macro_line|#else
DECL|macro|ide_init_default_irq
mdefine_line|#define ide_init_default_irq(base)&t;ide_default_irq(base)
macro_line|#endif
macro_line|#include &lt;asm-generic/ide_iops.h&gt;
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_IA64_IDE_H */
eof
