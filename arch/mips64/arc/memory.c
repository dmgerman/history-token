multiline_comment|/*&n; * memory.c: PROM library functions for acquiring/using memory descriptors&n; *           given to us from the ARCS firmware.&n; *&n; * Copyright (C) 1996 by David S. Miller&n; * Copyright (C) 1999, 2000, 2001 by Ralf Baechle&n; * Copyright (C) 1999, 2000 by Silicon Graphics, Inc.&n; *&n; * PROM library functions for acquiring/using memory descriptors given to us&n; * from the ARCS firmware.  This is only used when CONFIG_ARC_MEMORY is set&n; * because on some machines like SGI IP27 the ARC memory configuration data&n; * completly bogus and alternate easier to use mechanisms are available.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
DECL|macro|DEBUG
macro_line|#undef DEBUG
r_struct
id|linux_mdesc
op_star
id|__init
DECL|function|ArcGetMemoryDescriptor
id|ArcGetMemoryDescriptor
c_func
(paren
r_struct
id|linux_mdesc
op_star
id|Current
)paren
(brace
r_return
(paren
r_struct
id|linux_mdesc
op_star
)paren
id|ARC_CALL1
c_func
(paren
id|get_mdesc
comma
id|Current
)paren
suffix:semicolon
)brace
macro_line|#ifdef DEBUG /* convenient for debugging */
DECL|variable|arcs_mtypes
r_static
r_char
op_star
id|arcs_mtypes
(braket
l_int|8
)braket
op_assign
(brace
l_string|&quot;Exception Block&quot;
comma
l_string|&quot;ARCS Romvec Page&quot;
comma
l_string|&quot;Free/Contig RAM&quot;
comma
l_string|&quot;Generic Free RAM&quot;
comma
l_string|&quot;Bad Memory&quot;
comma
l_string|&quot;Standalone Program Pages&quot;
comma
l_string|&quot;ARCS Temp Storage Area&quot;
comma
l_string|&quot;ARCS Permanent Storage Area&quot;
)brace
suffix:semicolon
DECL|variable|arc_mtypes
r_static
r_char
op_star
id|arc_mtypes
(braket
l_int|8
)braket
op_assign
(brace
l_string|&quot;Exception Block&quot;
comma
l_string|&quot;SystemParameterBlock&quot;
comma
l_string|&quot;FreeMemory&quot;
comma
l_string|&quot;Bad Memory&quot;
comma
l_string|&quot;LoadedProgram&quot;
comma
l_string|&quot;FirmwareTemporary&quot;
comma
l_string|&quot;FirmwarePermanent&quot;
comma
l_string|&quot;FreeContiguous&quot;
)brace
suffix:semicolon
DECL|macro|mtypes
mdefine_line|#define mtypes(a) (prom_flags &amp; PROM_FLAG_ARCS) ? arcs_mtypes[a.arcs] : arc_mtypes[a.arc]
macro_line|#endif
DECL|function|memtype_classify_arcs
r_static
r_inline
r_int
id|memtype_classify_arcs
(paren
r_union
id|linux_memtypes
id|type
)paren
(brace
r_switch
c_cond
(paren
id|type.arcs
)paren
(brace
r_case
id|arcs_fcontig
suffix:colon
r_case
id|arcs_free
suffix:colon
r_return
id|BOOT_MEM_RAM
suffix:semicolon
r_case
id|arcs_atmp
suffix:colon
r_return
id|BOOT_MEM_ROM_DATA
suffix:semicolon
r_case
id|arcs_eblock
suffix:colon
r_case
id|arcs_rvpage
suffix:colon
r_case
id|arcs_bmem
suffix:colon
r_case
id|arcs_prog
suffix:colon
r_case
id|arcs_aperm
suffix:colon
r_return
id|BOOT_MEM_RESERVED
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* Nuke warning.  */
)brace
DECL|function|memtype_classify_arc
r_static
r_inline
r_int
id|memtype_classify_arc
(paren
r_union
id|linux_memtypes
id|type
)paren
(brace
r_switch
c_cond
(paren
id|type.arc
)paren
(brace
r_case
id|arc_free
suffix:colon
r_case
id|arc_fcontig
suffix:colon
r_return
id|BOOT_MEM_RAM
suffix:semicolon
r_case
id|arc_atmp
suffix:colon
r_return
id|BOOT_MEM_ROM_DATA
suffix:semicolon
r_case
id|arc_eblock
suffix:colon
r_case
id|arc_rvpage
suffix:colon
r_case
id|arc_bmem
suffix:colon
r_case
id|arc_prog
suffix:colon
r_case
id|arc_aperm
suffix:colon
r_return
id|BOOT_MEM_RESERVED
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* Nuke warning.  */
)brace
DECL|function|prom_memtype_classify
r_static
r_int
id|__init
id|prom_memtype_classify
(paren
r_union
id|linux_memtypes
id|type
)paren
(brace
r_if
c_cond
(paren
id|prom_flags
op_amp
id|PROM_FLAG_ARCS
)paren
multiline_comment|/* SGI is ``different&squot;&squot; ...  */
r_return
id|memtype_classify_arcs
c_func
(paren
id|type
)paren
suffix:semicolon
r_return
id|memtype_classify_arc
c_func
(paren
id|type
)paren
suffix:semicolon
)brace
DECL|function|prom_meminit
r_void
id|__init
id|prom_meminit
c_func
(paren
r_void
)paren
(brace
r_struct
id|linux_mdesc
op_star
id|p
suffix:semicolon
macro_line|#ifdef DEBUG
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;ARCS MEMORY DESCRIPTOR dump:&bslash;n&quot;
)paren
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
id|prom_printf
(paren
l_string|&quot;i=%d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|p
op_assign
id|ArcGetMemoryDescriptor
c_func
(paren
id|PROM_NULL_MDESC
)paren
suffix:semicolon
id|prom_printf
(paren
l_string|&quot;i=%d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
r_while
c_loop
(paren
id|p
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;[%d,%p]: base&lt;%08lx&gt; pages&lt;%08lx&gt; type&lt;%s&gt;&bslash;n&quot;
comma
id|i
comma
id|p
comma
id|p-&gt;base
comma
id|p-&gt;pages
comma
id|mtypes
c_func
(paren
id|p-&gt;type
)paren
)paren
suffix:semicolon
id|p
op_assign
id|ArcGetMemoryDescriptor
c_func
(paren
id|p
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
macro_line|#endif
id|p
op_assign
id|PROM_NULL_MDESC
suffix:semicolon
r_while
c_loop
(paren
(paren
id|p
op_assign
id|ArcGetMemoryDescriptor
c_func
(paren
id|p
)paren
)paren
)paren
(brace
r_int
r_int
id|base
comma
id|size
suffix:semicolon
r_int
id|type
suffix:semicolon
id|base
op_assign
id|p-&gt;base
op_lshift
id|PAGE_SHIFT
suffix:semicolon
id|size
op_assign
id|p-&gt;pages
op_lshift
id|PAGE_SHIFT
suffix:semicolon
id|type
op_assign
id|prom_memtype_classify
c_func
(paren
id|p-&gt;type
)paren
suffix:semicolon
id|add_memory_region
c_func
(paren
id|base
comma
id|size
comma
id|type
)paren
suffix:semicolon
)brace
)brace
r_void
id|__init
DECL|function|prom_free_prom_memory
id|prom_free_prom_memory
(paren
r_void
)paren
(brace
r_struct
id|prom_pmemblock
op_star
id|p
suffix:semicolon
r_int
r_int
id|freed
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|boot_mem_map.nr_map
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|boot_mem_map.map
(braket
id|i
)braket
dot
id|type
op_ne
id|BOOT_MEM_ROM_DATA
)paren
r_continue
suffix:semicolon
id|addr
op_assign
id|boot_mem_map.map
(braket
id|i
)braket
dot
id|addr
suffix:semicolon
r_while
c_loop
(paren
id|addr
OL
id|boot_mem_map.map
(braket
id|i
)braket
dot
id|addr
op_plus
id|boot_mem_map.map
(braket
id|i
)braket
dot
id|size
)paren
(brace
id|ClearPageReserved
c_func
(paren
id|virt_to_page
c_func
(paren
id|__va
c_func
(paren
id|addr
)paren
)paren
)paren
suffix:semicolon
id|set_page_count
c_func
(paren
id|virt_to_page
c_func
(paren
id|__va
c_func
(paren
id|addr
)paren
)paren
comma
l_int|1
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|__va
c_func
(paren
id|addr
)paren
)paren
suffix:semicolon
id|addr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|freed
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;Freeing prom memory: %ldkb freed&bslash;n&quot;
comma
id|freed
op_rshift
l_int|10
)paren
suffix:semicolon
)brace
eof
