multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __TLB_H__
DECL|macro|__TLB_H__
mdefine_line|#define __TLB_H__
macro_line|#include &quot;um_mmu.h&quot;
DECL|struct|host_vm_op
r_struct
id|host_vm_op
(brace
DECL|enumerator|MMAP
DECL|enumerator|MUNMAP
DECL|enumerator|MPROTECT
DECL|member|type
r_enum
(brace
id|MMAP
comma
id|MUNMAP
comma
id|MPROTECT
)brace
id|type
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|r
r_int
r_int
id|r
suffix:colon
l_int|1
suffix:semicolon
DECL|member|w
r_int
r_int
id|w
suffix:colon
l_int|1
suffix:semicolon
DECL|member|x
r_int
r_int
id|x
suffix:colon
l_int|1
suffix:semicolon
DECL|member|fd
r_int
id|fd
suffix:semicolon
DECL|member|offset
id|__u64
id|offset
suffix:semicolon
DECL|member|mmap
)brace
id|mmap
suffix:semicolon
r_struct
(brace
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|munmap
)brace
id|munmap
suffix:semicolon
r_struct
(brace
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|r
r_int
r_int
id|r
suffix:colon
l_int|1
suffix:semicolon
DECL|member|w
r_int
r_int
id|w
suffix:colon
l_int|1
suffix:semicolon
DECL|member|x
r_int
r_int
id|x
suffix:colon
l_int|1
suffix:semicolon
DECL|member|mprotect
)brace
id|mprotect
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|mprotect_kernel_vm
c_func
(paren
r_int
id|w
)paren
suffix:semicolon
r_extern
r_void
id|force_flush_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fix_range_common
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|start_addr
comma
r_int
r_int
id|end_addr
comma
r_int
id|force
comma
r_int
id|data
comma
r_void
(paren
op_star
id|do_ops
)paren
(paren
r_int
comma
r_struct
id|host_vm_op
op_star
comma
r_int
)paren
)paren
suffix:semicolon
r_extern
r_int
id|flush_tlb_kernel_range_common
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
suffix:semicolon
r_extern
r_int
id|add_mmap
c_func
(paren
r_int
r_int
id|virt
comma
r_int
r_int
id|phys
comma
r_int
r_int
id|len
comma
r_int
id|r
comma
r_int
id|w
comma
r_int
id|x
comma
r_struct
id|host_vm_op
op_star
id|ops
comma
r_int
id|index
comma
r_int
id|last_filled
comma
r_int
id|data
comma
r_void
(paren
op_star
id|do_ops
)paren
(paren
r_int
comma
r_struct
id|host_vm_op
op_star
comma
r_int
)paren
)paren
suffix:semicolon
r_extern
r_int
id|add_munmap
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|len
comma
r_struct
id|host_vm_op
op_star
id|ops
comma
r_int
id|index
comma
r_int
id|last_filled
comma
r_int
id|data
comma
r_void
(paren
op_star
id|do_ops
)paren
(paren
r_int
comma
r_struct
id|host_vm_op
op_star
comma
r_int
)paren
)paren
suffix:semicolon
r_extern
r_int
id|add_mprotect
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|len
comma
r_int
id|r
comma
r_int
id|w
comma
r_int
id|x
comma
r_struct
id|host_vm_op
op_star
id|ops
comma
r_int
id|index
comma
r_int
id|last_filled
comma
r_int
id|data
comma
r_void
(paren
op_star
id|do_ops
)paren
(paren
r_int
comma
r_struct
id|host_vm_op
op_star
comma
r_int
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
