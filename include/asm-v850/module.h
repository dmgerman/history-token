multiline_comment|/*&n; * include/asm-v850/module.h -- Architecture-specific module hooks&n; *&n; *  Copyright (C) 2001,02  NEC Corporation&n; *  Copyright (C) 2001,02  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_MODULE_H__
DECL|macro|__V850_MODULE_H__
mdefine_line|#define __V850_MODULE_H__
DECL|macro|arch_init_modules
mdefine_line|#define arch_init_modules(x)&t;((void)0)
DECL|macro|module_arch_init
mdefine_line|#define module_arch_init(x)&t;(0)
DECL|macro|module_map
mdefine_line|#define module_map(sz)&t;&t;vmalloc (sz)
DECL|macro|module_unmap
mdefine_line|#define module_unmap(sz)&t;vfree (sz)
macro_line|#endif /* __V850_MODULE_H__ */
eof
