multiline_comment|/*&n; *  linux/include/asm-sh64/ide.h&n; *&n; *  Copyright (C) 1994-1996  Linus Torvalds &amp; authors&n; *&n; *  sh64 version by Richard Curnow &amp; Paul Mundt&n; */
multiline_comment|/*&n; *  This file contains the sh64 architecture specific IDE code.&n; */
macro_line|#ifndef __ASM_SH64_IDE_H
DECL|macro|__ASM_SH64_IDE_H
mdefine_line|#define __ASM_SH64_IDE_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef MAX_HWIFS
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;CONFIG_IDE_MAX_HWIFS
macro_line|#endif
multiline_comment|/* Without this, the initialisation of PCI IDE cards end up calling&n; * ide_init_hwif_ports, which won&squot;t work. */
macro_line|#ifdef CONFIG_BLK_DEV_IDEPCI
DECL|macro|IDE_ARCH_OBSOLETE_INIT
mdefine_line|#define IDE_ARCH_OBSOLETE_INIT 1
DECL|macro|ide_default_io_ctl
mdefine_line|#define ide_default_io_ctl(base)&t;(0)
macro_line|#endif
macro_line|#include &lt;asm-generic/ide_iops.h&gt;
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_SH64_IDE_H */
eof
