macro_line|#ifndef _ASM_PPC64_MODULE_H
DECL|macro|_ASM_PPC64_MODULE_H
mdefine_line|#define _ASM_PPC64_MODULE_H
multiline_comment|/*&n; * This file contains the PPC architecture specific module code.&n; *&n; * Copyright (C) 2001 PPC 64 Team, IBM Corp&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
DECL|macro|module_map
mdefine_line|#define module_map(x)&t;&t;vmalloc(x)
DECL|macro|module_unmap
mdefine_line|#define module_unmap(x)&t;&t;vfree(x)
DECL|macro|arch_init_modules
mdefine_line|#define arch_init_modules(x)&t;do { } while (0)
DECL|macro|module_arch_init
mdefine_line|#define module_arch_init(x)  (0)
macro_line|#endif /* _ASM_PPC64_MODULE_H */
eof
