multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * This file contains the MIPS architecture specific IDE code.&n; *&n; * Copyright (C) 1994-1996  Linus Torvalds &amp; authors&n; */
macro_line|#ifndef __ASM_IDE_H
DECL|macro|__ASM_IDE_H
mdefine_line|#define __ASM_IDE_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;ide.h&gt;
DECL|macro|__ide_mm_insw
mdefine_line|#define __ide_mm_insw   ide_insw
DECL|macro|__ide_mm_insl
mdefine_line|#define __ide_mm_insl   ide_insl
DECL|macro|__ide_mm_outsw
mdefine_line|#define __ide_mm_outsw  ide_outsw
DECL|macro|__ide_mm_outsl
mdefine_line|#define __ide_mm_outsl  ide_outsl
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_IDE_H */
eof
