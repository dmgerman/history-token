macro_line|#ifndef __LINUX_VMALLOC_H
DECL|macro|__LINUX_VMALLOC_H
mdefine_line|#define __LINUX_VMALLOC_H
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
multiline_comment|/* bits in vm_struct-&gt;flags */
DECL|macro|VM_IOREMAP
mdefine_line|#define VM_IOREMAP&t;0x00000001&t;/* ioremap() and friends */
DECL|macro|VM_ALLOC
mdefine_line|#define VM_ALLOC&t;0x00000002&t;/* vmalloc() */
DECL|struct|vm_struct
r_struct
id|vm_struct
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|addr
r_void
op_star
id|addr
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|phys_addr
r_int
r_int
id|phys_addr
suffix:semicolon
DECL|member|next
r_struct
id|vm_struct
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|vm_struct
op_star
id|get_vm_area
(paren
r_int
r_int
id|size
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
r_extern
r_void
id|vfree
c_func
(paren
r_void
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_void
op_star
id|__vmalloc
(paren
r_int
r_int
id|size
comma
r_int
id|gfp_mask
comma
id|pgprot_t
id|prot
)paren
suffix:semicolon
r_extern
r_int
id|vread
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
id|addr
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|vmfree_area_pages
c_func
(paren
r_int
r_int
id|address
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
id|vmalloc_area_pages
c_func
(paren
r_int
r_int
id|address
comma
r_int
r_int
id|size
comma
r_int
id|gfp_mask
comma
id|pgprot_t
id|prot
)paren
suffix:semicolon
r_extern
r_struct
id|vm_struct
op_star
id|remove_kernel_area
c_func
(paren
r_void
op_star
id|addr
)paren
suffix:semicolon
multiline_comment|/*&n; * Various ways to allocate pages.&n; */
r_extern
r_void
op_star
id|vmalloc
c_func
(paren
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
op_star
id|vmalloc_32
c_func
(paren
r_int
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/*&n; * vmlist_lock is a read-write spinlock that protects vmlist&n; * Used in mm/vmalloc.c (get_vm_area() and vfree()) and fs/proc/kcore.c.&n; */
r_extern
id|rwlock_t
id|vmlist_lock
suffix:semicolon
r_extern
r_struct
id|vm_struct
op_star
id|vmlist
suffix:semicolon
macro_line|#endif
eof
