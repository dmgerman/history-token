multiline_comment|/* elf-fdpic.c: ELF FDPIC memory layout management&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/elf-fdpic.h&gt;
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * lay out the userspace VM according to our grand design&n; */
macro_line|#ifdef CONFIG_MMU
DECL|function|elf_fdpic_arch_lay_out_mm
r_void
id|elf_fdpic_arch_lay_out_mm
c_func
(paren
r_struct
id|elf_fdpic_params
op_star
id|exec_params
comma
r_struct
id|elf_fdpic_params
op_star
id|interp_params
comma
r_int
r_int
op_star
id|start_stack
comma
r_int
r_int
op_star
id|start_brk
)paren
(brace
op_star
id|start_stack
op_assign
l_int|0x02200000UL
suffix:semicolon
multiline_comment|/* if the only executable is a shared object, assume that it is an interpreter rather than&n;&t; * a true executable, and map it such that &quot;ld.so --list&quot; comes out right&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|interp_params-&gt;flags
op_amp
id|ELF_FDPIC_FLAG_PRESENT
)paren
op_logical_and
id|exec_params-&gt;hdr.e_type
op_ne
id|ET_EXEC
)paren
(brace
id|exec_params-&gt;load_addr
op_assign
id|PAGE_SIZE
suffix:semicolon
op_star
id|start_brk
op_assign
l_int|0x80000000UL
suffix:semicolon
)brace
r_else
(brace
id|exec_params-&gt;load_addr
op_assign
l_int|0x02200000UL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|exec_params-&gt;flags
op_amp
id|ELF_FDPIC_FLAG_ARRANGEMENT
)paren
op_eq
id|ELF_FDPIC_FLAG_INDEPENDENT
)paren
(brace
id|exec_params-&gt;flags
op_and_assign
op_complement
id|ELF_FDPIC_FLAG_ARRANGEMENT
suffix:semicolon
id|exec_params-&gt;flags
op_or_assign
id|ELF_FDPIC_FLAG_CONSTDISP
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* end elf_fdpic_arch_lay_out_mm() */
macro_line|#endif
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * place non-fixed mmaps firstly in the bottom part of memory, working up, and then in the top part&n; * of memory, working down&n; */
DECL|function|arch_get_unmapped_area
r_int
r_int
id|arch_get_unmapped_area
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|len
comma
r_int
r_int
id|pgoff
comma
r_int
r_int
id|flags
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_int
r_int
id|limit
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|TASK_SIZE
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* only honour a hint if we&squot;re not going to clobber something doing so */
r_if
c_cond
(paren
id|addr
)paren
(brace
id|addr
op_assign
id|PAGE_ALIGN
c_func
(paren
id|addr
)paren
suffix:semicolon
id|vma
op_assign
id|find_vma
c_func
(paren
id|current-&gt;mm
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|TASK_SIZE
op_minus
id|len
op_ge
id|addr
op_logical_and
(paren
op_logical_neg
id|vma
op_logical_or
id|addr
op_plus
id|len
op_le
id|vma-&gt;vm_start
)paren
)paren
r_goto
id|success
suffix:semicolon
)brace
multiline_comment|/* search between the bottom of user VM and the stack grow area */
id|addr
op_assign
id|PAGE_SIZE
suffix:semicolon
id|limit
op_assign
(paren
id|current-&gt;mm-&gt;start_stack
op_minus
l_int|0x00200000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_plus
id|len
op_le
id|limit
)paren
(brace
id|limit
op_sub_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_le
id|limit
)paren
(brace
id|vma
op_assign
id|find_vma
c_func
(paren
id|current-&gt;mm
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|vma
suffix:semicolon
id|vma
op_assign
id|vma-&gt;vm_next
)paren
(brace
r_if
c_cond
(paren
id|addr
OG
id|limit
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_plus
id|len
op_le
id|vma-&gt;vm_start
)paren
r_goto
id|success
suffix:semicolon
id|addr
op_assign
id|vma-&gt;vm_end
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* search from just above the WorkRAM area to the top of memory */
id|addr
op_assign
id|PAGE_ALIGN
c_func
(paren
l_int|0x80000000
)paren
suffix:semicolon
id|limit
op_assign
id|TASK_SIZE
op_minus
id|len
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_le
id|limit
)paren
(brace
id|vma
op_assign
id|find_vma
c_func
(paren
id|current-&gt;mm
comma
id|addr
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|vma
suffix:semicolon
id|vma
op_assign
id|vma-&gt;vm_next
)paren
(brace
r_if
c_cond
(paren
id|addr
OG
id|limit
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_plus
id|len
op_le
id|vma-&gt;vm_start
)paren
r_goto
id|success
suffix:semicolon
id|addr
op_assign
id|vma-&gt;vm_end
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|vma
op_logical_and
id|addr
op_le
id|limit
)paren
r_goto
id|success
suffix:semicolon
)brace
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;[area] l=%lx (ENOMEM) f=&squot;%s&squot;&bslash;n&quot;
comma
id|len
comma
id|filp
ques
c_cond
id|filp-&gt;f_dentry-&gt;d_name.name
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|success
suffix:colon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;[area] l=%lx ad=%lx f=&squot;%s&squot;&bslash;n&quot;
comma
id|len
comma
id|addr
comma
id|filp
ques
c_cond
id|filp-&gt;f_dentry-&gt;d_name.name
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
id|addr
suffix:semicolon
)brace
multiline_comment|/* end arch_get_unmapped_area() */
eof
