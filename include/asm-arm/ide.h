multiline_comment|/*&n; *  linux/include/asm-arm/ide.h&n; *&n; *  Copyright (C) 1994-1996  Linus Torvalds &amp; authors&n; */
multiline_comment|/*&n; *  This file contains the i386 architecture specific IDE code.&n; */
macro_line|#ifndef __ASMARM_IDE_H
DECL|macro|__ASMARM_IDE_H
mdefine_line|#define __ASMARM_IDE_H
macro_line|#ifdef __KERNEL__
macro_line|#ifndef MAX_HWIFS
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;4
macro_line|#endif
DECL|macro|ide__sti
mdefine_line|#define ide__sti()&t;__sti()
macro_line|#include &lt;asm/arch/ide.h&gt;
DECL|macro|ide_ack_intr
mdefine_line|#define ide_ack_intr(hwif)&t;&t;(1)
DECL|macro|ide_release_lock
mdefine_line|#define ide_release_lock(lock)&t;&t;do {} while (0)
DECL|macro|ide_get_lock
mdefine_line|#define ide_get_lock(lock, hdlr, data)&t;do {} while (0)
multiline_comment|/*&n; * We always use the new IDE port registering,&n; * so these are fixed here.&n; */
DECL|macro|ide_default_io_base
mdefine_line|#define ide_default_io_base(i)&t;&t;((ide_ioreg_t)0)
DECL|macro|ide_default_irq
mdefine_line|#define ide_default_irq(b)&t;&t;(0)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASMARM_IDE_H */
eof
