multiline_comment|/*&n; * Definitions for the MIPS sysmips(2) call&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995 by Ralf Baechle&n; */
macro_line|#ifndef __ASM_MIPS_SYSMIPS_H
DECL|macro|__ASM_MIPS_SYSMIPS_H
mdefine_line|#define __ASM_MIPS_SYSMIPS_H
multiline_comment|/*&n; * Commands for the sysmips(2) call&n; *&n; * sysmips(2) is deprecated - though some existing software uses it.&n; * We only support the following commands.&n; */
DECL|macro|SETNAME
mdefine_line|#define SETNAME                    1&t;/* set hostname                  */
DECL|macro|FLUSH_CACHE
mdefine_line|#define FLUSH_CACHE&t;&t;   3&t;/* writeback and invalidate caches */
DECL|macro|MIPS_FIXADE
mdefine_line|#define MIPS_FIXADE                7&t;/* control address error fixing  */
DECL|macro|MIPS_RDNVRAM
mdefine_line|#define MIPS_RDNVRAM              10&t;/* read NVRAM */
DECL|macro|MIPS_ATOMIC_SET
mdefine_line|#define MIPS_ATOMIC_SET&t;&t;2001&t;/* atomically set variable       */
macro_line|#endif /* __ASM_MIPS_SYSMIPS_H */
eof
