macro_line|#ifndef __UM_IO_H
DECL|macro|__UM_IO_H
mdefine_line|#define __UM_IO_H
macro_line|#include &quot;asm/page.h&quot;
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xdeadbeef /* Sure hope nothing uses this */
DECL|function|inb
r_static
r_inline
r_int
id|inb
c_func
(paren
r_int
r_int
id|i
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|outb
r_static
r_inline
r_void
id|outb
c_func
(paren
r_char
id|c
comma
r_int
r_int
id|i
)paren
(brace
)brace
multiline_comment|/*&n; * Change virtual addresses to physical addresses and vv.&n; * These are pretty trivial&n; */
DECL|function|virt_to_phys
r_static
r_inline
r_int
r_int
id|virt_to_phys
c_func
(paren
r_volatile
r_void
op_star
id|address
)paren
(brace
r_return
id|__pa
c_func
(paren
(paren
r_void
op_star
)paren
id|address
)paren
suffix:semicolon
)brace
DECL|function|phys_to_virt
r_static
r_inline
r_void
op_star
id|phys_to_virt
c_func
(paren
r_int
r_int
id|address
)paren
(brace
r_return
id|__va
c_func
(paren
id|address
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Convert a physical pointer to a virtual kernel pointer for /dev/mem&n; * access&n; */
DECL|macro|xlate_dev_mem_ptr
mdefine_line|#define xlate_dev_mem_ptr(p)&t;__va(p)
multiline_comment|/*&n; * Convert a virtual cached pointer to an uncached pointer&n; */
DECL|macro|xlate_dev_kmem_ptr
mdefine_line|#define xlate_dev_kmem_ptr(p)&t;p
macro_line|#endif
eof
