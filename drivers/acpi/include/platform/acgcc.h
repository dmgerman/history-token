multiline_comment|/******************************************************************************&n; *&n; * Name: acgcc.h - GCC specific defines, etc.&n; *       $Revision: 9 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ACGCC_H__
DECL|macro|__ACGCC_H__
mdefine_line|#define __ACGCC_H__
macro_line|#ifdef __ia64__
DECL|macro|_IA64
mdefine_line|#define _IA64
DECL|macro|COMPILER_DEPENDENT_UINT64
mdefine_line|#define COMPILER_DEPENDENT_UINT64   unsigned long
multiline_comment|/* Single threaded */
DECL|macro|ACPI_APPLICATION
mdefine_line|#define ACPI_APPLICATION
DECL|macro|ACPI_ASM_MACROS
mdefine_line|#define ACPI_ASM_MACROS
DECL|macro|causeinterrupt
mdefine_line|#define causeinterrupt(level)
DECL|macro|BREAKPOINT3
mdefine_line|#define BREAKPOINT3
DECL|macro|disable
mdefine_line|#define disable() __cli()
DECL|macro|enable
mdefine_line|#define enable()  __sti()
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
DECL|macro|COMPILER_DEPENDENT_UINT64
mdefine_line|#define COMPILER_DEPENDENT_UINT64   unsigned long long
DECL|macro|ACPI_ASM_MACROS
mdefine_line|#define ACPI_ASM_MACROS
DECL|macro|causeinterrupt
mdefine_line|#define causeinterrupt(level)
DECL|macro|BREAKPOINT3
mdefine_line|#define BREAKPOINT3
DECL|macro|disable
mdefine_line|#define disable() __cli()
DECL|macro|enable
mdefine_line|#define enable()  __sti()
DECL|macro|halt
mdefine_line|#define halt()    __asm__ __volatile__ (&quot;sti; hlt&quot;:::&quot;memory&quot;)
DECL|macro|wbinvd
mdefine_line|#define wbinvd()  __asm__ __volatile__ (&quot;wbinvd&quot;:::&quot;memory&quot;)
multiline_comment|/*! [Begin] no source code translation&n; *&n; * A brief explanation as GNU inline assembly is a bit hairy&n; *  %0 is the output parameter in EAX (&quot;=a&quot;)&n; *  %1 and %2 are the input parameters in ECX (&quot;c&quot;)&n; *  and an immediate value (&quot;i&quot;) respectively&n; *  All actual register references are preceded with &quot;%%&quot; as in &quot;%%edx&quot;&n; *  Immediate values in the assembly are preceded by &quot;$&quot; as in &quot;$0x1&quot;&n; *  The final asm parameter are the operation altered non-output registers.&n; */
DECL|macro|ACPI_ACQUIRE_GLOBAL_LOCK
mdefine_line|#define ACPI_ACQUIRE_GLOBAL_LOCK(GLptr, Acq) &bslash;&n;&t;do { &bslash;&n;&t;&t;int dummy; &bslash;&n;&t;&t;asm(&quot;1:     movl (%1),%%eax;&quot; &bslash;&n;&t;&t;&t;&quot;movl   %%eax,%%edx;&quot; &bslash;&n;&t;&t;&t;&quot;andl   %2,%%edx;&quot; &bslash;&n;&t;&t;&t;&quot;btsl   $0x1,%%edx;&quot; &bslash;&n;&t;&t;&t;&quot;adcl   $0x0,%%edx;&quot; &bslash;&n;&t;&t;&t;&quot;lock;  cmpxchgl %%edx,(%1);&quot; &bslash;&n;&t;&t;&t;&quot;jnz    1b;&quot; &bslash;&n;&t;&t;&t;&quot;cmpb   $0x3,%%dl;&quot; &bslash;&n;&t;&t;&t;&quot;sbbl   %%eax,%%eax&quot; &bslash;&n;&t;&t;&t;:&quot;=a&quot;(Acq),&quot;=c&quot;(dummy):&quot;c&quot;(GLptr),&quot;i&quot;(~1L):&quot;dx&quot;); &bslash;&n;&t;} while(0)
DECL|macro|ACPI_RELEASE_GLOBAL_LOCK
mdefine_line|#define ACPI_RELEASE_GLOBAL_LOCK(GLptr, Acq) &bslash;&n;&t;do { &bslash;&n;&t;&t;int dummy; &bslash;&n;&t;&t;asm(&quot;1:     movl (%1),%%eax;&quot; &bslash;&n;&t;&t;&t;&quot;movl   %%eax,%%edx;&quot; &bslash;&n;&t;&t;&t;&quot;andl   %2,%%edx;&quot; &bslash;&n;&t;&t;&t;&quot;lock;  cmpxchgl %%edx,(%1);&quot; &bslash;&n;&t;&t;&t;&quot;jnz    1b;&quot; &bslash;&n;&t;&t;&t;&quot;andl   $0x1,%%eax&quot; &bslash;&n;&t;&t;&t;:&quot;=a&quot;(Acq),&quot;=c&quot;(dummy):&quot;c&quot;(GLptr),&quot;i&quot;(~3L):&quot;dx&quot;); &bslash;&n;&t;} while(0)
multiline_comment|/*! [End] no source code translation !*/
macro_line|#endif /* IA 32 */
macro_line|#endif /* __ACGCC_H__ */
eof
