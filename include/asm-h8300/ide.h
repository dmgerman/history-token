multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *  linux/include/asm-h8300/ide.h&n; *&n; *  Copyright (C) 1994-1996  Linus Torvalds &amp; authors&n; *  Copyright (C) 2001       Lineo Inc., davidm@snapgear.com&n; *  Copyright (C) 2002       Greg Ungerer (gerg@snapgear.com)&n; *  Copyright (C) 2002       Yoshinori Sato (ysato@users.sourceforge.jp)&n; */
multiline_comment|/****************************************************************************/
macro_line|#ifndef _H8300_IDE_H
DECL|macro|_H8300_IDE_H
mdefine_line|#define _H8300_IDE_H
multiline_comment|/****************************************************************************/
macro_line|#ifdef __KERNEL__
multiline_comment|/****************************************************************************/
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;1
macro_line|#include &lt;asm-generic/ide_iops.h&gt;
multiline_comment|/****************************************************************************/
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _H8300_IDE_H */
multiline_comment|/****************************************************************************/
eof
