multiline_comment|/* module.h: FRV module stuff&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_MODULE_H
DECL|macro|_ASM_MODULE_H
mdefine_line|#define _ASM_MODULE_H
DECL|macro|module_map
mdefine_line|#define module_map(x)&t;&t;vmalloc(x)
DECL|macro|module_unmap
mdefine_line|#define module_unmap(x)&t;&t;vfree(x)
DECL|macro|module_arch_init
mdefine_line|#define module_arch_init(x)&t;(0)
DECL|macro|arch_init_modules
mdefine_line|#define arch_init_modules(x)&t;do { } while (0)
macro_line|#endif /* _ASM_MODULE_H */
eof
