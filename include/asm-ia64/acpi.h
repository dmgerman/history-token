multiline_comment|/*&n; *  asm-ia64/acpi.h&n; *&n; *  Copyright (C) 1999 VA Linux Systems&n; *  Copyright (C) 1999 Walt Drummond &lt;drummond@valinux.com&gt;&n; *  Copyright (C) 2000,2001 J.I. Lee &lt;jung-ik.lee@intel.com&gt;&n; *  Copyright (C) 2001,2002 Paul Diefenbaugh &lt;paul.s.diefenbaugh@intel.com&gt;&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; */
macro_line|#ifndef _ASM_ACPI_H
DECL|macro|_ASM_ACPI_H
mdefine_line|#define _ASM_ACPI_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/numa.h&gt;
macro_line|#include &lt;asm/system.h&gt;
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
r_static
r_inline
r_int
DECL|function|ia64_acpi_acquire_global_lock
id|ia64_acpi_acquire_global_lock
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
id|ia64_cmpxchg4_acq
c_func
(paren
id|lock
comma
r_new
comma
id|old
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
DECL|function|ia64_acpi_release_global_lock
id|ia64_acpi_release_global_lock
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
id|ia64_cmpxchg4_acq
c_func
(paren
id|lock
comma
r_new
comma
id|old
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
mdefine_line|#define ACPI_ACQUIRE_GLOBAL_LOCK(GLptr, Acq)&t;&t;&t;&t;&bslash;&n;&t;((Acq) = ia64_acpi_acquire_global_lock((unsigned int *) GLptr))
DECL|macro|ACPI_RELEASE_GLOBAL_LOCK
mdefine_line|#define ACPI_RELEASE_GLOBAL_LOCK(GLptr, Acq)&t;&t;&t;&t;&bslash;&n;&t;((Acq) = ia64_acpi_release_global_lock((unsigned int *) GLptr))
DECL|macro|acpi_disabled
mdefine_line|#define acpi_disabled 0&t;/* ACPI always enabled on IA64 */
DECL|macro|acpi_noirq
mdefine_line|#define acpi_noirq 0&t;/* ACPI always enabled on IA64 */
DECL|macro|acpi_pci_disabled
mdefine_line|#define acpi_pci_disabled 0 /* ACPI PCI always enabled on IA64 */
DECL|macro|acpi_strict
mdefine_line|#define acpi_strict 1&t;/* no ACPI spec workarounds on IA64 */
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
)brace
r_const
r_char
op_star
id|acpi_get_sysname
(paren
r_void
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
id|acpi_gsi_to_irq
(paren
id|u32
id|gsi
comma
r_int
r_int
op_star
id|irq
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ACPI_NUMA
multiline_comment|/* Proximity bitmap length; _PXM is at most 255 (8 bit)*/
DECL|macro|MAX_PXM_DOMAINS
mdefine_line|#define MAX_PXM_DOMAINS (256)
r_extern
r_int
id|__devinitdata
id|pxm_to_nid_map
(braket
id|MAX_PXM_DOMAINS
)braket
suffix:semicolon
r_extern
r_int
id|__initdata
id|nid_to_pxm_map
(braket
id|MAX_NUMNODES
)braket
suffix:semicolon
macro_line|#endif
r_extern
id|u16
id|ia64_acpiid_to_sapicid
(braket
)braket
suffix:semicolon
macro_line|#endif /*__KERNEL__*/
macro_line|#endif /*_ASM_ACPI_H*/
eof
