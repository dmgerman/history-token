macro_line|#ifndef __ASM_SN_HUB_H
DECL|macro|__ASM_SN_HUB_H
mdefine_line|#define __ASM_SN_HUB_H
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#include &lt;asm/sn/klkernvars.h&gt;
DECL|struct|hub_data
r_struct
id|hub_data
(brace
DECL|member|kern_vars
id|kern_vars_t
id|kern_vars
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
macro_line|#endif /* __ASM_SN_HUB_H */
eof
