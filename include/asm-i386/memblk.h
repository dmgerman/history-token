macro_line|#ifndef _ASM_I386_MEMBLK_H_
DECL|macro|_ASM_I386_MEMBLK_H_
mdefine_line|#define _ASM_I386_MEMBLK_H_
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
macro_line|#include &lt;linux/memblk.h&gt;
macro_line|#include &lt;linux/topology.h&gt;
macro_line|#include &lt;asm/node.h&gt;
DECL|struct|i386_memblk
r_struct
id|i386_memblk
(brace
DECL|member|memblk
r_struct
id|memblk
id|memblk
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|i386_memblk
id|memblk_devices
(braket
id|MAX_NR_MEMBLKS
)braket
suffix:semicolon
DECL|function|arch_register_memblk
r_static
r_inline
r_int
(def_block
id|arch_register_memblk
c_func
(paren
r_int
id|num
)paren
(brace
r_int
id|p_node
op_assign
id|memblk_to_node
c_func
(paren
id|num
)paren
suffix:semicolon
r_return
id|register_memblk
c_func
(paren
op_amp
id|memblk_devices
(braket
id|num
)braket
dot
id|memblk
comma
id|num
comma
op_amp
id|node_devices
(braket
id|p_node
)braket
dot
id|node
)paren
suffix:semicolon
)brace
)def_block
macro_line|#endif /* _ASM_I386_MEMBLK_H_ */
eof
