multiline_comment|/*&n; *  linux/include/asm-sh/ide.h&n; *&n; *  Copyright (C) 1994-1996  Linus Torvalds &amp; authors&n; */
multiline_comment|/*&n; *  This file contains the i386 architecture specific IDE code.&n; *  In future, SuperH code.&n; */
macro_line|#ifndef __ASM_SH_IDE_H
DECL|macro|__ASM_SH_IDE_H
mdefine_line|#define __ASM_SH_IDE_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef MAX_HWIFS
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;CONFIG_IDE_MAX_HWIFS
macro_line|#endif
DECL|macro|ide_default_io_ctl
mdefine_line|#define ide_default_io_ctl(base)&t;(0)
macro_line|#include &lt;asm-generic/ide_iops.h&gt;
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_SH_IDE_H */
eof
