multiline_comment|/*&n; *  asm-ia64/acpi.h&n; *&n; *  Copyright (C) 1999 VA Linux Systems&n; *  Copyright (C) 1999 Walt Drummond &lt;drummond@valinux.com&gt;&n; *  Copyright (C) 2000,2001 J.I. Lee &lt;jung-ik.lee@intel.com&gt;&n; *  Copyright (C) 2001,2002 Paul Diefenbaugh &lt;paul.s.diefenbaugh@intel.com&gt;&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; */
macro_line|#ifndef _ASM_ACPI_H
DECL|macro|_ASM_ACPI_H
mdefine_line|#define _ASM_ACPI_H
macro_line|#ifdef __KERNEL__
DECL|macro|COMPILER_DEPENDENT_INT64
mdefine_line|#define COMPILER_DEPENDENT_INT64&t;long
DECL|macro|COMPILER_DEPENDENT_UINT64
mdefine_line|#define COMPILER_DEPENDENT_UINT64&t;unsigned long
multiline_comment|/*&n; * Calling conventions:&n; *&n; * ACPI_SYSTEM_XFACE        - Interfaces to host OS (handlers, threads)&n; * ACPI_EXTERNAL_XFACE      - External ACPI interfaces&n; * ACPI_INTERNAL_XFACE      - Internal ACPI interfaces&n; * ACPI_INTERNAL_VAR_XFACE  - Internal variable-parameter list interfaces&n; */
DECL|macro|ACPI_SYSTEM_XFACE
mdefine_line|#define ACPI_SYSTEM_XFACE
DECL|macro|ACPI_EXTERNAL_XFACE
mdefine_line|#define ACPI_EXTERNAL_XFACE
DECL|macro|ACPI_INTERNAL_XFACE
mdefine_line|#define ACPI_INTERNAL_XFACE
DECL|macro|ACPI_INTERNAL_VAR_XFACE
mdefine_line|#define ACPI_INTERNAL_VAR_XFACE
multiline_comment|/* Asm macros */
DECL|macro|ACPI_ASM_MACROS
mdefine_line|#define ACPI_ASM_MACROS
DECL|macro|BREAKPOINT3
mdefine_line|#define BREAKPOINT3
DECL|macro|ACPI_DISABLE_IRQS
mdefine_line|#define ACPI_DISABLE_IRQS() local_irq_disable()
DECL|macro|ACPI_ENABLE_IRQS
mdefine_line|#define ACPI_ENABLE_IRQS()  local_irq_enable()
DECL|macro|ACPI_FLUSH_CPU_CACHE
mdefine_line|#define ACPI_FLUSH_CPU_CACHE()
DECL|macro|ACPI_ACQUIRE_GLOBAL_LOCK
mdefine_line|#define ACPI_ACQUIRE_GLOBAL_LOCK(GLptr, Acq) &bslash;&n;&t;do { &bslash;&n;&t;__asm__ volatile (&quot;1:  ld4      r29=%1&bslash;n&quot;  &bslash;&n;&t;&t;&quot;;;&bslash;n&quot;                  &bslash;&n;&t;&t;&quot;mov    ar.ccv=r29&bslash;n&quot;   &bslash;&n;&t;&t;&quot;mov    r2=r29&bslash;n&quot;       &bslash;&n;&t;&t;&quot;shr.u  r30=r29,1&bslash;n&quot;    &bslash;&n;&t;&t;&quot;and    r29=-4,r29&bslash;n&quot;   &bslash;&n;&t;&t;&quot;;;&bslash;n&quot;                  &bslash;&n;&t;&t;&quot;add    r29=2,r29&bslash;n&quot;    &bslash;&n;&t;&t;&quot;and    r30=1,r30&bslash;n&quot;    &bslash;&n;&t;&t;&quot;;;&bslash;n&quot;                  &bslash;&n;&t;&t;&quot;add    r29=r29,r30&bslash;n&quot;  &bslash;&n;&t;&t;&quot;;;&bslash;n&quot;                  &bslash;&n;&t;&t;&quot;cmpxchg4.acq   r30=%1,r29,ar.ccv&bslash;n&quot; &bslash;&n;&t;&t;&quot;;;&bslash;n&quot;                  &bslash;&n;&t;&t;&quot;cmp.eq p6,p7=r2,r30&bslash;n&quot; &bslash;&n;&t;&t;&quot;(p7) br.dpnt.few 1b&bslash;n&quot; &bslash;&n;&t;&t;&quot;cmp.gt p8,p9=3,r29&bslash;n&quot;  &bslash;&n;&t;&t;&quot;;;&bslash;n&quot;                  &bslash;&n;&t;&t;&quot;(p8) mov %0=-1&bslash;n&quot;      &bslash;&n;&t;&t;&quot;(p9) mov %0=r0&bslash;n&quot;      &bslash;&n;&t;&t;:&quot;=r&quot;(Acq):&quot;m&quot;(GLptr):&quot;r2&quot;,&quot;r29&quot;,&quot;r30&quot;,&quot;memory&quot;); &bslash;&n;&t;} while (0)
DECL|macro|ACPI_RELEASE_GLOBAL_LOCK
mdefine_line|#define ACPI_RELEASE_GLOBAL_LOCK(GLptr, Acq) &bslash;&n;&t;do { &bslash;&n;&t;__asm__ volatile (&quot;1:  ld4      r29=%1&bslash;n&quot; &bslash;&n;&t;&t;&quot;;;&bslash;n&quot;                  &bslash;&n;&t;&t;&quot;mov    ar.ccv=r29&bslash;n&quot;   &bslash;&n;&t;&t;&quot;mov    r2=r29&bslash;n&quot;       &bslash;&n;&t;&t;&quot;and    r29=-4,r29&bslash;n&quot;   &bslash;&n;&t;&t;&quot;;;&bslash;n&quot;                  &bslash;&n;&t;&t;&quot;cmpxchg4.acq   r30=%1,r29,ar.ccv&bslash;n&quot; &bslash;&n;&t;&t;&quot;;;&bslash;n&quot;                  &bslash;&n;&t;&t;&quot;cmp.eq p6,p7=r2,r30&bslash;n&quot; &bslash;&n;&t;&t;&quot;(p7) br.dpnt.few 1b&bslash;n&quot; &bslash;&n;&t;&t;&quot;and    %0=1,r2&bslash;n&quot;      &bslash;&n;&t;&t;&quot;;;&bslash;n&quot;                  &bslash;&n;&t;&t;:&quot;=r&quot;(Acq):&quot;m&quot;(GLptr):&quot;r2&quot;,&quot;r29&quot;,&quot;r30&quot;,&quot;memory&quot;); &bslash;&n;&t;} while (0)
r_const
r_char
op_star
id|acpi_get_sysname
(paren
r_void
)paren
suffix:semicolon
r_int
id|acpi_boot_init
(paren
r_char
op_star
id|cdline
)paren
suffix:semicolon
r_int
id|acpi_request_vector
(paren
id|u32
id|int_type
)paren
suffix:semicolon
r_int
id|acpi_get_prt
(paren
r_struct
id|pci_vector_struct
op_star
op_star
id|vectors
comma
r_int
op_star
id|count
)paren
suffix:semicolon
r_int
id|acpi_get_interrupt_model
(paren
r_int
op_star
id|type
)paren
suffix:semicolon
r_int
id|acpi_irq_to_vector
(paren
id|u32
id|irq
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DISCONTIGMEM
DECL|macro|NODE_ARRAY_INDEX
mdefine_line|#define NODE_ARRAY_INDEX(x)&t;((x) / 8)&t;/* 8 bits/char */
DECL|macro|NODE_ARRAY_OFFSET
mdefine_line|#define NODE_ARRAY_OFFSET(x)&t;((x) % 8)&t;/* 8 bits/char */
DECL|macro|MAX_PXM_DOMAINS
mdefine_line|#define MAX_PXM_DOMAINS&t;&t;(256)
macro_line|#endif /* CONFIG_DISCONTIGMEM */
macro_line|#endif /*__KERNEL__*/
macro_line|#endif /*_ASM_ACPI_H*/
eof
