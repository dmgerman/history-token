multiline_comment|/******************************************************************************&n; *&n; * Name: acgcc.h - GCC specific defines, etc.&n; *       $Revision: 22 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ACGCC_H__
DECL|macro|__ACGCC_H__
mdefine_line|#define __ACGCC_H__
macro_line|#ifdef __ia64__
DECL|macro|_IA64
mdefine_line|#define _IA64
DECL|macro|COMPILER_DEPENDENT_INT64
mdefine_line|#define COMPILER_DEPENDENT_INT64   long
DECL|macro|COMPILER_DEPENDENT_UINT64
mdefine_line|#define COMPILER_DEPENDENT_UINT64  unsigned long
multiline_comment|/*&n; * Calling conventions:&n; *&n; * ACPI_SYSTEM_XFACE        - Interfaces to host OS (handlers, threads)&n; * ACPI_EXTERNAL_XFACE      - External ACPI interfaces&n; * ACPI_INTERNAL_XFACE      - Internal ACPI interfaces&n; * ACPI_INTERNAL_VAR_XFACE  - Internal variable-parameter list interfaces&n; */
DECL|macro|ACPI_SYSTEM_XFACE
mdefine_line|#define ACPI_SYSTEM_XFACE
DECL|macro|ACPI_EXTERNAL_XFACE
mdefine_line|#define ACPI_EXTERNAL_XFACE
DECL|macro|ACPI_INTERNAL_XFACE
mdefine_line|#define ACPI_INTERNAL_XFACE
DECL|macro|ACPI_INTERNAL_VAR_XFACE
mdefine_line|#define ACPI_INTERNAL_VAR_XFACE
multiline_comment|/* Single threaded */
DECL|macro|ACPI_APPLICATION
mdefine_line|#define ACPI_APPLICATION
multiline_comment|/* Asm macros */
DECL|macro|ACPI_ASM_MACROS
mdefine_line|#define ACPI_ASM_MACROS
DECL|macro|BREAKPOINT3
mdefine_line|#define BREAKPOINT3
DECL|macro|ACPI_DISABLE_IRQS
mdefine_line|#define ACPI_DISABLE_IRQS() __cli()
DECL|macro|ACPI_ENABLE_IRQS
mdefine_line|#define ACPI_ENABLE_IRQS()  __sti()
multiline_comment|/*! [Begin] no source code translation */
macro_line|#include &lt;asm/pal.h&gt;
DECL|macro|halt
mdefine_line|#define halt()              ia64_pal_halt_light()           /* PAL_HALT[_LIGHT] */
DECL|macro|safe_halt
mdefine_line|#define safe_halt()         ia64_pal_halt(1)                /* PAL_HALT */
DECL|macro|ACPI_ACQUIRE_GLOBAL_LOCK
mdefine_line|#define ACPI_ACQUIRE_GLOBAL_LOCK(GLptr, Acq) &bslash;&n;&t;do { &bslash;&n;&t;__asm__ volatile (&quot;1:  ld4      r29=%1&bslash;n&quot;  &bslash;&n;&t;&t;&quot;;;&bslash;n&quot;                  &bslash;&n;&t;&t;&quot;mov    ar.ccv=r29&bslash;n&quot;   &bslash;&n;&t;&t;&quot;mov    r2=r29&bslash;n&quot;       &bslash;&n;&t;&t;&quot;shr.u  r30=r29,1&bslash;n&quot;    &bslash;&n;&t;&t;&quot;and    r29=-4,r29&bslash;n&quot;   &bslash;&n;&t;&t;&quot;;;&bslash;n&quot;                  &bslash;&n;&t;&t;&quot;add    r29=2,r29&bslash;n&quot;    &bslash;&n;&t;&t;&quot;and    r30=1,r30&bslash;n&quot;    &bslash;&n;&t;&t;&quot;;;&bslash;n&quot;                  &bslash;&n;&t;&t;&quot;add    r29=r29,r30&bslash;n&quot;  &bslash;&n;&t;&t;&quot;;;&bslash;n&quot;                  &bslash;&n;&t;&t;&quot;cmpxchg4.acq   r30=%1,r29,ar.ccv&bslash;n&quot; &bslash;&n;&t;&t;&quot;;;&bslash;n&quot;                  &bslash;&n;&t;&t;&quot;cmp.eq p6,p7=r2,r30&bslash;n&quot; &bslash;&n;&t;&t;&quot;(p7) br.dpnt.few 1b&bslash;n&quot; &bslash;&n;&t;&t;&quot;cmp.gt p8,p9=3,r29&bslash;n&quot;  &bslash;&n;&t;&t;&quot;;;&bslash;n&quot;                  &bslash;&n;&t;&t;&quot;(p8) mov %0=-1&bslash;n&quot;      &bslash;&n;&t;&t;&quot;(p9) mov %0=r0&bslash;n&quot;      &bslash;&n;&t;&t;:&quot;=r&quot;(Acq):&quot;m&quot;(GLptr):&quot;r2&quot;,&quot;r29&quot;,&quot;r30&quot;,&quot;memory&quot;); &bslash;&n;&t;} while (0)
DECL|macro|ACPI_RELEASE_GLOBAL_LOCK
mdefine_line|#define ACPI_RELEASE_GLOBAL_LOCK(GLptr, Acq) &bslash;&n;&t;do { &bslash;&n;&t;__asm__ volatile (&quot;1:  ld4      r29=%1&bslash;n&quot; &bslash;&n;&t;&t;&quot;;;&bslash;n&quot;                  &bslash;&n;&t;&t;&quot;mov    ar.ccv=r29&bslash;n&quot;   &bslash;&n;&t;&t;&quot;mov    r2=r29&bslash;n&quot;       &bslash;&n;&t;&t;&quot;and    r29=-4,r29&bslash;n&quot;   &bslash;&n;&t;&t;&quot;;;&bslash;n&quot;                  &bslash;&n;&t;&t;&quot;cmpxchg4.acq   r30=%1,r29,ar.ccv&bslash;n&quot; &bslash;&n;&t;&t;&quot;;;&bslash;n&quot;                  &bslash;&n;&t;&t;&quot;cmp.eq p6,p7=r2,r30&bslash;n&quot; &bslash;&n;&t;&t;&quot;(p7) br.dpnt.few 1b&bslash;n&quot; &bslash;&n;&t;&t;&quot;and    %0=1,r2&bslash;n&quot;      &bslash;&n;&t;&t;&quot;;;&bslash;n&quot;                  &bslash;&n;&t;&t;:&quot;=r&quot;(Acq):&quot;m&quot;(GLptr):&quot;r2&quot;,&quot;r29&quot;,&quot;r30&quot;,&quot;memory&quot;); &bslash;&n;&t;} while (0)
multiline_comment|/*! [End] no source code translation !*/
macro_line|#else /* DO IA32 */
DECL|macro|COMPILER_DEPENDENT_INT64
mdefine_line|#define COMPILER_DEPENDENT_INT64   long long
DECL|macro|COMPILER_DEPENDENT_UINT64
mdefine_line|#define COMPILER_DEPENDENT_UINT64  unsigned long long
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
mdefine_line|#define ACPI_DISABLE_IRQS() __cli()
DECL|macro|ACPI_ENABLE_IRQS
mdefine_line|#define ACPI_ENABLE_IRQS()  __sti()
multiline_comment|/*! [Begin] no source code translation&n; *&n; * A brief explanation as GNU inline assembly is a bit hairy&n; *  %0 is the output parameter in EAX (&quot;=a&quot;)&n; *  %1 and %2 are the input parameters in ECX (&quot;c&quot;)&n; *  and an immediate value (&quot;i&quot;) respectively&n; *  All actual register references are preceded with &quot;%%&quot; as in &quot;%%edx&quot;&n; *  Immediate values in the assembly are preceded by &quot;$&quot; as in &quot;$0x1&quot;&n; *  The final asm parameter are the operation altered non-output registers.&n; */
DECL|macro|ACPI_ACQUIRE_GLOBAL_LOCK
mdefine_line|#define ACPI_ACQUIRE_GLOBAL_LOCK(GLptr, Acq) &bslash;&n;&t;do { &bslash;&n;&t;&t;int dummy; &bslash;&n;&t;&t;asm(&quot;1:     movl (%1),%%eax;&quot; &bslash;&n;&t;&t;&t;&quot;movl   %%eax,%%edx;&quot; &bslash;&n;&t;&t;&t;&quot;andl   %2,%%edx;&quot; &bslash;&n;&t;&t;&t;&quot;btsl   $0x1,%%edx;&quot; &bslash;&n;&t;&t;&t;&quot;adcl   $0x0,%%edx;&quot; &bslash;&n;&t;&t;&t;&quot;lock;  cmpxchgl %%edx,(%1);&quot; &bslash;&n;&t;&t;&t;&quot;jnz    1b;&quot; &bslash;&n;&t;&t;&t;&quot;cmpb   $0x3,%%dl;&quot; &bslash;&n;&t;&t;&t;&quot;sbbl   %%eax,%%eax&quot; &bslash;&n;&t;&t;&t;:&quot;=a&quot;(Acq),&quot;=c&quot;(dummy):&quot;c&quot;(GLptr),&quot;i&quot;(~1L):&quot;dx&quot;); &bslash;&n;&t;} while(0)
DECL|macro|ACPI_RELEASE_GLOBAL_LOCK
mdefine_line|#define ACPI_RELEASE_GLOBAL_LOCK(GLptr, Acq) &bslash;&n;&t;do { &bslash;&n;&t;&t;int dummy; &bslash;&n;&t;&t;asm(&quot;1:     movl (%1),%%eax;&quot; &bslash;&n;&t;&t;&t;&quot;movl   %%eax,%%edx;&quot; &bslash;&n;&t;&t;&t;&quot;andl   %2,%%edx;&quot; &bslash;&n;&t;&t;&t;&quot;lock;  cmpxchgl %%edx,(%1);&quot; &bslash;&n;&t;&t;&t;&quot;jnz    1b;&quot; &bslash;&n;&t;&t;&t;&quot;andl   $0x1,%%eax&quot; &bslash;&n;&t;&t;&t;:&quot;=a&quot;(Acq),&quot;=c&quot;(dummy):&quot;c&quot;(GLptr),&quot;i&quot;(~3L):&quot;dx&quot;); &bslash;&n;&t;} while(0)
multiline_comment|/*&n; * Math helper asm macros&n; */
DECL|macro|ACPI_DIV_64_BY_32
mdefine_line|#define ACPI_DIV_64_BY_32(n_hi, n_lo, d32, q32, r32) &bslash;&n;&t;&t;asm(&quot;divl %2;&quot;        &bslash;&n;&t;&t;:&quot;=a&quot;(q32), &quot;=d&quot;(r32) &bslash;&n;&t;&t;:&quot;r&quot;(d32),            &bslash;&n;&t;&t;&quot;0&quot;(n_lo), &quot;1&quot;(n_hi))
DECL|macro|ACPI_SHIFT_RIGHT_64
mdefine_line|#define ACPI_SHIFT_RIGHT_64(n_hi, n_lo) &bslash;&n;&t;asm(&quot;shrl   $1,%2;&quot;             &bslash;&n;&t;&t;&quot;rcrl   $1,%3;&quot;             &bslash;&n;&t;&t;:&quot;=r&quot;(n_hi), &quot;=r&quot;(n_lo)     &bslash;&n;&t;&t;:&quot;0&quot;(n_hi), &quot;1&quot;(n_lo))
multiline_comment|/*! [End] no source code translation !*/
macro_line|#endif /* IA 32 */
multiline_comment|/* This macro is used to tag functions as &quot;printf-like&quot; because&n; * some compilers (like GCC) can catch printf format string problems.&n; */
DECL|macro|ACPI_PRINTF_LIKE_FUNC
mdefine_line|#define ACPI_PRINTF_LIKE_FUNC __attribute__ ((__format__ (__printf__, 4, 5)))
macro_line|#endif /* __ACGCC_H__ */
eof
