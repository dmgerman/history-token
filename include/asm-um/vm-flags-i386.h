multiline_comment|/*&n; * Copyright (C) 2004 Jeff Dike (jdike@addtoit.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __VM_FLAGS_I386_H
DECL|macro|__VM_FLAGS_I386_H
mdefine_line|#define __VM_FLAGS_I386_H
DECL|macro|VM_DATA_DEFAULT_FLAGS
mdefine_line|#define VM_DATA_DEFAULT_FLAGS &bslash;&n;&t;(VM_READ | VM_WRITE | &bslash;&n;&t;((current-&gt;personality &amp; READ_IMPLIES_EXEC) ? VM_EXEC : 0 ) | &bslash;&n;&t;&t; VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC)
macro_line|#endif
eof
