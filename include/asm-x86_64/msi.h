multiline_comment|/*&n; * Copyright (C) 2003-2004 Intel&n; * Copyright (C) Tom Long Nguyen (tom.l.nguyen@intel.com)&n; */
macro_line|#ifndef ASM_MSI_H
DECL|macro|ASM_MSI_H
mdefine_line|#define ASM_MSI_H
macro_line|#include &lt;asm/desc.h&gt;
DECL|macro|LAST_DEVICE_VECTOR
mdefine_line|#define LAST_DEVICE_VECTOR&t;&t;232
DECL|macro|MSI_DEST_MODE
mdefine_line|#define MSI_DEST_MODE&t;&t;&t;MSI_LOGICAL_MODE
DECL|macro|MSI_TARGET_CPU_SHIFT
mdefine_line|#define MSI_TARGET_CPU_SHIFT&t;&t;12
macro_line|#ifdef CONFIG_SMP
DECL|macro|MSI_TARGET_CPU
mdefine_line|#define MSI_TARGET_CPU&t;&t;logical_smp_processor_id()
macro_line|#else
DECL|macro|MSI_TARGET_CPU
mdefine_line|#define MSI_TARGET_CPU&t;&t;TARGET_CPUS
macro_line|#endif
macro_line|#endif /* ASM_MSI_H */
eof
