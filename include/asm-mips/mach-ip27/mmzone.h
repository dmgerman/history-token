macro_line|#ifndef _ASM_MACH_MMZONE_H
DECL|macro|_ASM_MACH_MMZONE_H
mdefine_line|#define _ASM_MACH_MMZONE_H
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/arch.h&gt;
macro_line|#include &lt;asm/sn/hub.h&gt;
DECL|macro|pa_to_nid
mdefine_line|#define pa_to_nid(addr)&t;&t;NASID_TO_COMPACT_NODEID(NASID_GET(addr))
DECL|macro|LEVELS_PER_SLICE
mdefine_line|#define LEVELS_PER_SLICE        128
DECL|struct|slice_data
r_struct
id|slice_data
(brace
DECL|member|irq_alloc_mask
r_int
r_int
id|irq_alloc_mask
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|irq_enable_mask
r_int
r_int
id|irq_enable_mask
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|level_to_irq
r_int
id|level_to_irq
(braket
id|LEVELS_PER_SLICE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hub_data
r_struct
id|hub_data
(brace
DECL|member|kern_vars
id|kern_vars_t
id|kern_vars
suffix:semicolon
id|DECLARE_BITMAP
c_func
(paren
id|h_bigwin_used
comma
id|HUB_NUM_BIG_WINDOW
)paren
suffix:semicolon
DECL|member|h_cpus
id|cpumask_t
id|h_cpus
suffix:semicolon
DECL|member|slice_map
r_int
r_int
id|slice_map
suffix:semicolon
DECL|member|slice
r_struct
id|slice_data
id|slice
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|node_data
r_struct
id|node_data
(brace
DECL|member|pglist
r_struct
id|pglist_data
id|pglist
suffix:semicolon
DECL|member|hub
r_struct
id|hub_data
id|hub
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|node_data
op_star
id|__node_data
(braket
)braket
suffix:semicolon
DECL|macro|NODE_DATA
mdefine_line|#define NODE_DATA(n)&t;&t;(&amp;__node_data[(n)]-&gt;pglist)
DECL|macro|hub_data
mdefine_line|#define hub_data(n)&t;&t;(&amp;__node_data[(n)]-&gt;hub)
macro_line|#endif /* _ASM_MACH_MMZONE_H */
eof
