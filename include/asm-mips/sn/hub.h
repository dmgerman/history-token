macro_line|#ifndef __ASM_SN_HUB_H
DECL|macro|__ASM_SN_HUB_H
mdefine_line|#define __ASM_SN_HUB_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/cpumask.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#include &lt;asm/sn/klkernvars.h&gt;
macro_line|#include &lt;asm/xtalk/xtalk.h&gt;
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
