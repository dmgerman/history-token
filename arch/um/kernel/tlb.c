multiline_comment|/* &n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/mm.h&quot;
macro_line|#include &quot;asm/page.h&quot;
macro_line|#include &quot;asm/pgalloc.h&quot;
macro_line|#include &quot;asm/tlbflush.h&quot;
macro_line|#include &quot;choose-mode.h&quot;
macro_line|#include &quot;mode_kern.h&quot;
DECL|function|flush_tlb_page
r_void
id|flush_tlb_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
)paren
(brace
id|address
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|flush_tlb_range
c_func
(paren
id|vma
comma
id|address
comma
id|address
op_plus
id|PAGE_SIZE
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_all
r_void
id|flush_tlb_all
c_func
(paren
r_void
)paren
(brace
id|flush_tlb_mm
c_func
(paren
id|current-&gt;mm
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_kernel_range
r_void
id|flush_tlb_kernel_range
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
(brace
id|CHOOSE_MODE_PROC
c_func
(paren
id|flush_tlb_kernel_range_tt
comma
id|flush_tlb_kernel_range_skas
comma
id|start
comma
id|end
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_kernel_vm
r_void
id|flush_tlb_kernel_vm
c_func
(paren
r_void
)paren
(brace
id|CHOOSE_MODE
c_func
(paren
id|flush_tlb_kernel_vm_tt
c_func
(paren
)paren
comma
id|flush_tlb_kernel_vm_skas
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|__flush_tlb_one
r_void
id|__flush_tlb_one
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|CHOOSE_MODE_PROC
c_func
(paren
id|__flush_tlb_one_tt
comma
id|__flush_tlb_one_skas
comma
id|addr
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_range
r_void
id|flush_tlb_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
id|CHOOSE_MODE_PROC
c_func
(paren
id|flush_tlb_range_tt
comma
id|flush_tlb_range_skas
comma
id|vma
comma
id|start
comma
id|end
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_mm
r_void
id|flush_tlb_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|CHOOSE_MODE_PROC
c_func
(paren
id|flush_tlb_mm_tt
comma
id|flush_tlb_mm_skas
comma
id|mm
)paren
suffix:semicolon
)brace
DECL|function|force_flush_all
r_void
id|force_flush_all
c_func
(paren
r_void
)paren
(brace
id|CHOOSE_MODE
c_func
(paren
id|force_flush_all_tt
c_func
(paren
)paren
comma
id|force_flush_all_skas
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|pgd_offset_proc
id|pgd_t
op_star
id|pgd_offset_proc
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|address
)paren
(brace
r_return
id|pgd_offset
c_func
(paren
id|mm
comma
id|address
)paren
suffix:semicolon
)brace
DECL|function|pmd_offset_proc
id|pmd_t
op_star
id|pmd_offset_proc
c_func
(paren
id|pgd_t
op_star
id|pgd
comma
r_int
r_int
id|address
)paren
(brace
r_return
id|pmd_offset
c_func
(paren
id|pgd
comma
id|address
)paren
suffix:semicolon
)brace
DECL|function|pte_offset_proc
id|pte_t
op_star
id|pte_offset_proc
c_func
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|address
)paren
(brace
r_return
id|pte_offset_kernel
c_func
(paren
id|pmd
comma
id|address
)paren
suffix:semicolon
)brace
DECL|function|addr_pte
id|pte_t
op_star
id|addr_pte
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
r_int
id|addr
)paren
(brace
r_return
id|pte_offset_kernel
c_func
(paren
id|pmd_offset
c_func
(paren
id|pgd_offset
c_func
(paren
id|task-&gt;mm
comma
id|addr
)paren
comma
id|addr
)paren
comma
id|addr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
