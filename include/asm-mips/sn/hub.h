macro_line|#ifndef __ASM_SN_HUB_H
DECL|macro|__ASM_SN_HUB_H
mdefine_line|#define __ASM_SN_HUB_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/cpumask.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#include &lt;asm/sn/klkernvars.h&gt;
macro_line|#include &lt;asm/xtalk/xtalk.h&gt;
DECL|macro|LEVELS_PER_SLICE
mdefine_line|#define LEVELS_PER_SLICE&t;128
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
r_extern
r_struct
id|hub_data
op_star
id|hub_data
(braket
)braket
suffix:semicolon
DECL|macro|HUB_DATA
mdefine_line|#define HUB_DATA(n)&t;&t;(hub_data[(n)])
multiline_comment|/* ip27-hubio.c */
r_extern
r_int
r_int
id|hub_pio_map
c_func
(paren
id|cnodeid_t
id|cnode
comma
id|xwidgetnum_t
id|widget
comma
r_int
r_int
id|xtalk_addr
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|hub_pio_init
c_func
(paren
id|cnodeid_t
id|cnode
)paren
suffix:semicolon
macro_line|#endif /* __ASM_SN_HUB_H */
eof
