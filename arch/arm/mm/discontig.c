multiline_comment|/*&n; * linux/arch/arm/mm/discontig.c&n; *&n; * Discontiguous memory support.&n; *&n; * Initial code: Copyright (C) 1999-2000 Nicolas Pitre&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#if NR_NODES != 4
macro_line|#error Fix Me Please
macro_line|#endif
multiline_comment|/*&n; * Our node_data structure for discontigous memory.&n; */
DECL|variable|node_bootmem_data
r_static
id|bootmem_data_t
id|node_bootmem_data
(braket
id|NR_NODES
)braket
suffix:semicolon
DECL|variable|discontig_node_data
id|pg_data_t
id|discontig_node_data
(braket
id|NR_NODES
)braket
op_assign
(brace
(brace
id|bdata
suffix:colon
op_amp
id|node_bootmem_data
(braket
l_int|0
)braket
)brace
comma
(brace
id|bdata
suffix:colon
op_amp
id|node_bootmem_data
(braket
l_int|1
)braket
)brace
comma
(brace
id|bdata
suffix:colon
op_amp
id|node_bootmem_data
(braket
l_int|2
)braket
)brace
comma
(brace
id|bdata
suffix:colon
op_amp
id|node_bootmem_data
(braket
l_int|3
)braket
)brace
)brace
suffix:semicolon
DECL|variable|discontig_node_data
id|EXPORT_SYMBOL
c_func
(paren
id|discontig_node_data
)paren
suffix:semicolon
eof
