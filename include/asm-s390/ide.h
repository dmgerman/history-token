multiline_comment|/*&n; *  linux/include/asm-s390/ide.h&n; *&n; *  Copyright (C) 1994-1996  Linus Torvalds &amp; authors&n; */
multiline_comment|/* s390 does not have IDE */
macro_line|#ifndef __ASMS390_IDE_H
DECL|macro|__ASMS390_IDE_H
mdefine_line|#define __ASMS390_IDE_H
macro_line|#ifdef __KERNEL__
macro_line|#ifndef MAX_HWIFS
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;0
macro_line|#endif
multiline_comment|/*&n; * We always use the new IDE port registering,&n; * so these are fixed here.&n; */
DECL|macro|ide_default_io_base
mdefine_line|#define ide_default_io_base(i)&t;&t;((ide_ioreg_t)0)
DECL|macro|ide_default_irq
mdefine_line|#define ide_default_irq(b)&t;&t;(0)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASMS390_IDE_H */
eof
