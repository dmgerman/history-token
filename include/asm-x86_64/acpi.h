multiline_comment|/*&n; *  asm-x86_64/acpi.h&n; *&n; *  Copyright (C) 2001 Paul Diefenbaugh &lt;paul.s.diefenbaugh@intel.com&gt;&n; *  Copyright (C) 2001 Patrick Mochel &lt;mochel@osdl.org&gt;&n;  *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; */
macro_line|#ifndef _ASM_ACPI_H
DECL|macro|_ASM_ACPI_H
mdefine_line|#define _ASM_ACPI_H
macro_line|#ifdef __KERNEL__
DECL|macro|COMPILER_DEPENDENT_INT64
mdefine_line|#define COMPILER_DEPENDENT_INT64   long long
DECL|macro|COMPILER_DEPENDENT_UINT64
mdefine_line|#define COMPILER_DEPENDENT_UINT64  unsigned long long
multiline_comment|/*&n; * Calling conventions:&n; *&n; * ACPI_SYSTEM_XFACE        - Interfaces to host OS (handlers, threads)&n; * ACPI_EXTERNAL_XFACE      - External ACPI interfaces &n; * ACPI_INTERNAL_XFACE      - Internal ACPI interfaces&n; * ACPI_INTERNAL_VAR_XFACE  - Internal variable-parameter list interfaces&n; */
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
mdefine_line|#define ACPI_FLUSH_CPU_CACHE()&t;wbinvd()
r_static
r_inline
r_int
DECL|function|__acpi_acquire_global_lock
id|__acpi_acquire_global_lock
(paren
r_int
r_int
op_star
id|lock
)paren
(brace
r_int
r_int
id|old
comma
r_new
comma
id|val
suffix:semicolon
r_do
(brace
id|old
op_assign
op_star
id|lock
suffix:semicolon
r_new
op_assign
(paren
(paren
(paren
id|old
op_amp
op_complement
l_int|0x3
)paren
op_plus
l_int|2
)paren
op_plus
(paren
(paren
id|old
op_rshift
l_int|1
)paren
op_amp
l_int|0x1
)paren
)paren
suffix:semicolon
id|val
op_assign
id|cmpxchg
c_func
(paren
id|lock
comma
id|old
comma
r_new
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|unlikely
(paren
id|val
op_ne
id|old
)paren
)paren
suffix:semicolon
r_return
(paren
r_new
OL
l_int|3
)paren
ques
c_cond
op_minus
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|__acpi_release_global_lock
id|__acpi_release_global_lock
(paren
r_int
r_int
op_star
id|lock
)paren
(brace
r_int
r_int
id|old
comma
r_new
comma
id|val
suffix:semicolon
r_do
(brace
id|old
op_assign
op_star
id|lock
suffix:semicolon
r_new
op_assign
id|old
op_amp
op_complement
l_int|0x3
suffix:semicolon
id|val
op_assign
id|cmpxchg
c_func
(paren
id|lock
comma
id|old
comma
r_new
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|unlikely
(paren
id|val
op_ne
id|old
)paren
)paren
suffix:semicolon
r_return
id|old
op_amp
l_int|0x1
suffix:semicolon
)brace
DECL|macro|ACPI_ACQUIRE_GLOBAL_LOCK
mdefine_line|#define ACPI_ACQUIRE_GLOBAL_LOCK(GLptr, Acq) &bslash;&n;&t;((Acq) = __acpi_acquire_global_lock((unsigned int *) GLptr))
DECL|macro|ACPI_RELEASE_GLOBAL_LOCK
mdefine_line|#define ACPI_RELEASE_GLOBAL_LOCK(GLptr, Acq) &bslash;&n;&t;((Acq) = __acpi_release_global_lock((unsigned int *) GLptr))
multiline_comment|/*&n; * Math helper asm macros&n; */
DECL|macro|ACPI_DIV_64_BY_32
mdefine_line|#define ACPI_DIV_64_BY_32(n_hi, n_lo, d32, q32, r32) &bslash;&n;        asm(&quot;divl %2;&quot;        &bslash;&n;        :&quot;=a&quot;(q32), &quot;=d&quot;(r32) &bslash;&n;        :&quot;r&quot;(d32),            &bslash;&n;        &quot;0&quot;(n_lo), &quot;1&quot;(n_hi))
DECL|macro|ACPI_SHIFT_RIGHT_64
mdefine_line|#define ACPI_SHIFT_RIGHT_64(n_hi, n_lo) &bslash;&n;    asm(&quot;shrl   $1,%2;&quot;             &bslash;&n;        &quot;rcrl   $1,%3;&quot;             &bslash;&n;        :&quot;=r&quot;(n_hi), &quot;=r&quot;(n_lo)     &bslash;&n;        :&quot;0&quot;(n_hi), &quot;1&quot;(n_lo))
macro_line|#ifdef CONFIG_ACPI_BOOT
r_extern
r_int
id|acpi_lapic
suffix:semicolon
r_extern
r_int
id|acpi_ioapic
suffix:semicolon
r_extern
r_int
id|acpi_noirq
suffix:semicolon
r_extern
r_int
id|acpi_strict
suffix:semicolon
r_extern
r_int
id|acpi_disabled
suffix:semicolon
r_extern
r_int
id|acpi_ht
suffix:semicolon
DECL|function|disable_acpi
r_static
r_inline
r_void
id|disable_acpi
c_func
(paren
r_void
)paren
(brace
id|acpi_disabled
op_assign
l_int|1
suffix:semicolon
id|acpi_ht
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Fixmap pages to reserve for ACPI boot-time tables (see fixmap.h) */
DECL|macro|FIX_ACPI_PAGES
mdefine_line|#define FIX_ACPI_PAGES 4
macro_line|#else&t;/* !CONFIG_ACPI_BOOT */
DECL|macro|acpi_lapic
mdefine_line|#define acpi_lapic 0
DECL|macro|acpi_ioapic
mdefine_line|#define acpi_ioapic 0
macro_line|#endif /* !CONFIG_ACPI_BOOT */
macro_line|#ifdef CONFIG_ACPI_PCI
DECL|function|acpi_noirq_set
r_static
r_inline
r_void
id|acpi_noirq_set
c_func
(paren
r_void
)paren
(brace
id|acpi_noirq
op_assign
l_int|1
suffix:semicolon
)brace
r_extern
r_int
id|acpi_irq_balance_set
c_func
(paren
r_char
op_star
id|str
)paren
suffix:semicolon
macro_line|#else
DECL|function|acpi_noirq_set
r_static
r_inline
r_void
id|acpi_noirq_set
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|acpi_irq_balance_set
r_static
r_inline
r_int
id|acpi_irq_balance_set
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_ACPI_SLEEP
multiline_comment|/* routines for saving/restoring kernel state */
r_extern
r_int
id|acpi_save_state_mem
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|acpi_save_state_disk
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|acpi_restore_state_mem
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|acpi_wakeup_address
suffix:semicolon
multiline_comment|/* early initialization routine */
r_extern
r_void
id|acpi_reserve_bootmem
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /*CONFIG_ACPI_SLEEP*/
DECL|macro|boot_cpu_physical_apicid
mdefine_line|#define boot_cpu_physical_apicid boot_cpu_id
r_extern
r_int
id|acpi_disabled
suffix:semicolon
DECL|macro|dmi_broken
mdefine_line|#define dmi_broken (0)
DECL|macro|BROKEN_ACPI_Sx
mdefine_line|#define BROKEN_ACPI_Sx&t;&t;0x0001
DECL|macro|BROKEN_INIT_AFTER_S1
mdefine_line|#define BROKEN_INIT_AFTER_S1&t;0x0002
macro_line|#endif /*__KERNEL__*/
macro_line|#endif /*_ASM_ACPI_H*/
eof
