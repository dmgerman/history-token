multiline_comment|/*&n; *  acpi_numa.c - ACPI NUMA support&n; *&n; *  Copyright (C) 2002 Takayoshi Kochi &lt;t-kochi@bq.jp.nec.com&gt;&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;acpi/acpi_bus.h&gt;
macro_line|#include &lt;acpi/acmacros.h&gt;
DECL|macro|ACPI_NUMA
mdefine_line|#define ACPI_NUMA&t;0x80000000
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT&t;ACPI_NUMA
id|ACPI_MODULE_NAME
(paren
l_string|&quot;numa&quot;
)paren
r_extern
r_int
id|__init
id|acpi_table_parse_madt_family
(paren
r_enum
id|acpi_table_id
id|id
comma
r_int
r_int
id|madt_size
comma
r_int
id|entry_id
comma
id|acpi_madt_entry_handler
id|handler
comma
r_int
r_int
id|max_entries
)paren
suffix:semicolon
r_void
id|__init
DECL|function|acpi_table_print_srat_entry
id|acpi_table_print_srat_entry
(paren
id|acpi_table_entry_header
op_star
id|header
)paren
(brace
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;acpi_table_print_srat_entry&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|header
)paren
r_return
suffix:semicolon
r_switch
c_cond
(paren
id|header-&gt;type
)paren
(brace
r_case
id|ACPI_SRAT_PROCESSOR_AFFINITY
suffix:colon
macro_line|#ifdef ACPI_DEBUG_OUTPUT
(brace
r_struct
id|acpi_table_processor_affinity
op_star
id|p
op_assign
(paren
r_struct
id|acpi_table_processor_affinity
op_star
)paren
id|header
suffix:semicolon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;SRAT Processor (id[0x%02x] eid[0x%02x]) in proximity domain %d %s&bslash;n&quot;
comma
id|p-&gt;apic_id
comma
id|p-&gt;lsapic_eid
comma
id|p-&gt;proximity_domain
comma
id|p-&gt;flags.enabled
ques
c_cond
l_string|&quot;enabled&quot;
suffix:colon
l_string|&quot;disabled&quot;
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* ACPI_DEBUG_OUTPUT */
r_break
suffix:semicolon
r_case
id|ACPI_SRAT_MEMORY_AFFINITY
suffix:colon
macro_line|#ifdef ACPI_DEBUG_OUTPUT
(brace
r_struct
id|acpi_table_memory_affinity
op_star
id|p
op_assign
(paren
r_struct
id|acpi_table_memory_affinity
op_star
)paren
id|header
suffix:semicolon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;SRAT Memory (0x%08x%08x length 0x%08x%08x type 0x%x) in proximity domain %d %s%s&bslash;n&quot;
comma
id|p-&gt;base_addr_hi
comma
id|p-&gt;base_addr_lo
comma
id|p-&gt;length_hi
comma
id|p-&gt;length_lo
comma
id|p-&gt;memory_type
comma
id|p-&gt;proximity_domain
comma
id|p-&gt;flags.enabled
ques
c_cond
l_string|&quot;enabled&quot;
suffix:colon
l_string|&quot;disabled&quot;
comma
id|p-&gt;flags.hot_pluggable
ques
c_cond
l_string|&quot; hot-pluggable&quot;
suffix:colon
l_string|&quot;&quot;
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* ACPI_DEBUG_OUTPUT */
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;Found unsupported SRAT entry (type = 0x%x)&bslash;n&quot;
comma
id|header-&gt;type
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_static
r_int
id|__init
DECL|function|acpi_parse_slit
id|acpi_parse_slit
(paren
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|size
)paren
(brace
r_struct
id|acpi_table_slit
op_star
id|slit
suffix:semicolon
id|u32
id|localities
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|phys_addr
op_logical_or
op_logical_neg
id|size
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|slit
op_assign
(paren
r_struct
id|acpi_table_slit
op_star
)paren
id|__va
c_func
(paren
id|phys_addr
)paren
suffix:semicolon
multiline_comment|/* downcast just for %llu vs %lu for i386/ia64  */
id|localities
op_assign
(paren
id|u32
)paren
id|slit-&gt;localities
suffix:semicolon
id|acpi_numa_slit_init
c_func
(paren
id|slit
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|acpi_parse_processor_affinity
id|acpi_parse_processor_affinity
(paren
id|acpi_table_entry_header
op_star
id|header
comma
r_const
r_int
r_int
id|end
)paren
(brace
r_struct
id|acpi_table_processor_affinity
op_star
id|processor_affinity
suffix:semicolon
id|processor_affinity
op_assign
(paren
r_struct
id|acpi_table_processor_affinity
op_star
)paren
id|header
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|processor_affinity
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|acpi_table_print_srat_entry
c_func
(paren
id|header
)paren
suffix:semicolon
multiline_comment|/* let architecture-dependent part to do it */
id|acpi_numa_processor_affinity_init
c_func
(paren
id|processor_affinity
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|acpi_parse_memory_affinity
id|acpi_parse_memory_affinity
(paren
id|acpi_table_entry_header
op_star
id|header
comma
r_const
r_int
r_int
id|end
)paren
(brace
r_struct
id|acpi_table_memory_affinity
op_star
id|memory_affinity
suffix:semicolon
id|memory_affinity
op_assign
(paren
r_struct
id|acpi_table_memory_affinity
op_star
)paren
id|header
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memory_affinity
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|acpi_table_print_srat_entry
c_func
(paren
id|header
)paren
suffix:semicolon
multiline_comment|/* let architecture-dependent part to do it */
id|acpi_numa_memory_affinity_init
c_func
(paren
id|memory_affinity
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|acpi_parse_srat
id|acpi_parse_srat
(paren
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|size
)paren
(brace
r_struct
id|acpi_table_srat
op_star
id|srat
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|phys_addr
op_logical_or
op_logical_neg
id|size
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|srat
op_assign
(paren
r_struct
id|acpi_table_srat
op_star
)paren
id|__va
c_func
(paren
id|phys_addr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
id|__init
DECL|function|acpi_table_parse_srat
id|acpi_table_parse_srat
(paren
r_enum
id|acpi_srat_entry_id
id|id
comma
id|acpi_madt_entry_handler
id|handler
comma
r_int
r_int
id|max_entries
)paren
(brace
r_return
id|acpi_table_parse_madt_family
c_func
(paren
id|ACPI_SRAT
comma
r_sizeof
(paren
r_struct
id|acpi_table_srat
)paren
comma
id|id
comma
id|handler
comma
id|max_entries
)paren
suffix:semicolon
)brace
r_int
id|__init
DECL|function|acpi_numa_init
id|acpi_numa_init
c_func
(paren
r_void
)paren
(brace
r_int
id|result
suffix:semicolon
multiline_comment|/* SRAT: Static Resource Affinity Table */
id|result
op_assign
id|acpi_table_parse
c_func
(paren
id|ACPI_SRAT
comma
id|acpi_parse_srat
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OG
l_int|0
)paren
(brace
id|result
op_assign
id|acpi_table_parse_srat
c_func
(paren
id|ACPI_SRAT_PROCESSOR_AFFINITY
comma
id|acpi_parse_processor_affinity
comma
id|NR_CPUS
)paren
suffix:semicolon
id|result
op_assign
id|acpi_table_parse_srat
c_func
(paren
id|ACPI_SRAT_MEMORY_AFFINITY
comma
id|acpi_parse_memory_affinity
comma
id|NR_NODE_MEMBLKS
)paren
suffix:semicolon
singleline_comment|// IA64 specific
)brace
r_else
(brace
multiline_comment|/* FIXME */
id|printk
c_func
(paren
l_string|&quot;Warning: acpi_table_parse(ACPI_SRAT) returned %d!&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
)brace
multiline_comment|/* SLIT: System Locality Information Table */
id|result
op_assign
id|acpi_table_parse
c_func
(paren
id|ACPI_SLIT
comma
id|acpi_parse_slit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|1
)paren
(brace
multiline_comment|/* FIXME */
id|printk
c_func
(paren
l_string|&quot;Warning: acpi_table_parse(ACPI_SLIT) returned %d!&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
)brace
id|acpi_numa_arch_fixup
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|acpi_get_pxm
id|acpi_get_pxm
c_func
(paren
id|acpi_handle
id|h
)paren
(brace
r_int
r_int
id|pxm
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|acpi_handle
id|handle
suffix:semicolon
id|acpi_handle
id|phandle
op_assign
id|h
suffix:semicolon
r_do
(brace
id|handle
op_assign
id|phandle
suffix:semicolon
id|status
op_assign
id|acpi_evaluate_integer
c_func
(paren
id|handle
comma
l_string|&quot;_PXM&quot;
comma
l_int|NULL
comma
op_amp
id|pxm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_SUCCESS
c_func
(paren
id|status
)paren
)paren
r_return
(paren
r_int
)paren
id|pxm
suffix:semicolon
id|status
op_assign
id|acpi_get_parent
c_func
(paren
id|handle
comma
op_amp
id|phandle
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|ACPI_SUCCESS
c_func
(paren
id|status
)paren
)paren
(brace
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|variable|acpi_get_pxm
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_get_pxm
)paren
suffix:semicolon
eof
