multiline_comment|/*&n; * Copyright (C) 2003-2004 Intel&n; * Copyright (C) Tom Long Nguyen (tom.l.nguyen@intel.com)&n; */
macro_line|#ifndef ASM_MSI_H
DECL|macro|ASM_MSI_H
mdefine_line|#define ASM_MSI_H
macro_line|#include &lt;asm/desc.h&gt;
macro_line|#include &lt;asm/mach_apic.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
DECL|macro|LAST_DEVICE_VECTOR
mdefine_line|#define LAST_DEVICE_VECTOR&t;&t;232
DECL|macro|MSI_DEST_MODE
mdefine_line|#define MSI_DEST_MODE&t;&t;&t;MSI_LOGICAL_MODE
DECL|macro|MSI_TARGET_CPU_SHIFT
mdefine_line|#define MSI_TARGET_CPU_SHIFT&t;&t;12
DECL|macro|MSI_TARGET_CPU
mdefine_line|#define MSI_TARGET_CPU&t;&t;&t;logical_smp_processor_id()
macro_line|#endif /* ASM_MSI_H */
eof
