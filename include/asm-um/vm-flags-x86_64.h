multiline_comment|/*&n; * Copyright (C) 2004 Jeff Dike (jdike@addtoit.com)&n; * Copyright 2003 PathScale, Inc.&n; * Licensed under the GPL&n; */
macro_line|#ifndef __VM_FLAGS_X86_64_H
DECL|macro|__VM_FLAGS_X86_64_H
mdefine_line|#define __VM_FLAGS_X86_64_H
DECL|macro|__VM_DATA_DEFAULT_FLAGS
mdefine_line|#define __VM_DATA_DEFAULT_FLAGS&t;(VM_READ | VM_WRITE | VM_EXEC | &bslash;&n;&t;&t;&t;&t; VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC)
DECL|macro|__VM_STACK_FLAGS
mdefine_line|#define __VM_STACK_FLAGS &t;(VM_GROWSDOWN | VM_READ | VM_WRITE | &bslash;&n;&t;&t;&t;&t; VM_EXEC | VM_MAYREAD | VM_MAYWRITE | &bslash;&n;&t;&t;&t;&t; VM_MAYEXEC)
r_extern
r_int
r_int
id|vm_stack_flags
comma
id|vm_stack_flags32
suffix:semicolon
r_extern
r_int
r_int
id|vm_data_default_flags
comma
id|vm_data_default_flags32
suffix:semicolon
r_extern
r_int
r_int
id|vm_force_exec32
suffix:semicolon
macro_line|#ifdef TIF_IA32
DECL|macro|VM_DATA_DEFAULT_FLAGS
mdefine_line|#define VM_DATA_DEFAULT_FLAGS &bslash;&n;&t;(test_thread_flag(TIF_IA32) ? vm_data_default_flags32 : &bslash;&n;&t;  vm_data_default_flags)
DECL|macro|VM_STACK_DEFAULT_FLAGS
mdefine_line|#define VM_STACK_DEFAULT_FLAGS &bslash;&n;&t;(test_thread_flag(TIF_IA32) ? vm_stack_flags32 : vm_stack_flags)
macro_line|#endif
DECL|macro|VM_DATA_DEFAULT_FLAGS
mdefine_line|#define VM_DATA_DEFAULT_FLAGS vm_data_default_flags
DECL|macro|VM_STACK_DEFAULT_FLAGS
mdefine_line|#define VM_STACK_DEFAULT_FLAGS vm_stack_flags
macro_line|#endif
eof
