multiline_comment|/* $Id: fault.c,v 1.5 2000/01/26 16:20:29 jsm Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; *&n; * Copyright (C) 1995, 1996, 1997, 1998 by Ralf Baechle&n; * Copyright 1999 SuSE GmbH (Philipp Rumpf, prumpf@tux.org)&n; * Copyright 1999 Hewlett Packard Co.&n; *&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
DECL|macro|PRINT_USER_FAULTS
mdefine_line|#define PRINT_USER_FAULTS /* (turn this on if you want user faults to be */
multiline_comment|/*  dumped to the console via printk)          */
multiline_comment|/* Defines for parisc_acctyp()&t;*/
DECL|macro|READ
mdefine_line|#define READ&t;&t;0
DECL|macro|WRITE
mdefine_line|#define WRITE&t;&t;1
multiline_comment|/* Various important other fields */
DECL|macro|bit22set
mdefine_line|#define bit22set(x)&t;&t;(x &amp; 0x00000200)
DECL|macro|bits23_25set
mdefine_line|#define bits23_25set(x)&t;&t;(x &amp; 0x000001c0)
DECL|macro|isGraphicsFlushRead
mdefine_line|#define isGraphicsFlushRead(x)&t;((x &amp; 0xfc003fdf) == 0x04001a80)
multiline_comment|/* extended opcode is 0x6a */
DECL|macro|BITSSET
mdefine_line|#define BITSSET&t;&t;0x1c0&t;/* for identifying LDCW */
multiline_comment|/*&n; * parisc_acctyp(unsigned int inst) --&n; *    Given a PA-RISC memory access instruction, determine if the&n; *    the instruction would perform a memory read or memory write&n; *    operation.&n; *&n; *    This function assumes that the given instruction is a memory access&n; *    instruction (i.e. you should really only call it if you know that&n; *    the instruction has generated some sort of a memory access fault).&n; *&n; * Returns:&n; *   VM_READ  if read operation&n; *   VM_WRITE if write operation&n; *   VM_EXEC  if execute operation&n; */
r_static
r_int
r_int
DECL|function|parisc_acctyp
id|parisc_acctyp
c_func
(paren
r_int
r_int
id|code
comma
r_int
r_int
id|inst
)paren
(brace
r_if
c_cond
(paren
id|code
op_eq
l_int|6
op_logical_or
id|code
op_eq
l_int|16
)paren
r_return
id|VM_EXEC
suffix:semicolon
r_switch
c_cond
(paren
id|inst
op_amp
l_int|0xf0000000
)paren
(brace
r_case
l_int|0x40000000
suffix:colon
multiline_comment|/* load */
r_case
l_int|0x50000000
suffix:colon
multiline_comment|/* new load */
r_return
id|VM_READ
suffix:semicolon
r_case
l_int|0x60000000
suffix:colon
multiline_comment|/* store */
r_case
l_int|0x70000000
suffix:colon
multiline_comment|/* new store */
r_return
id|VM_WRITE
suffix:semicolon
r_case
l_int|0x20000000
suffix:colon
multiline_comment|/* coproc */
r_case
l_int|0x30000000
suffix:colon
multiline_comment|/* coproc2 */
r_if
c_cond
(paren
id|bit22set
c_func
(paren
id|inst
)paren
)paren
r_return
id|VM_WRITE
suffix:semicolon
r_case
l_int|0x0
suffix:colon
multiline_comment|/* indexed/memory management */
r_if
c_cond
(paren
id|bit22set
c_func
(paren
id|inst
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Check for the &squot;Graphics Flush Read&squot; instruction.&n;&t;&t;&t; * It resembles an FDC instruction, except for bits&n;&t;&t;&t; * 20 and 21. Any combination other than zero will&n;&t;&t;&t; * utilize the block mover functionality on some&n;&t;&t;&t; * older PA-RISC platforms.  The case where a block&n;&t;&t;&t; * move is performed from VM to graphics IO space&n;&t;&t;&t; * should be treated as a READ.&n;&t;&t;&t; *&n;&t;&t;&t; * The significance of bits 20,21 in the FDC&n;&t;&t;&t; * instruction is:&n;&t;&t;&t; *&n;&t;&t;&t; *   00  Flush data cache (normal instruction behavior)&n;&t;&t;&t; *   01  Graphics flush write  (IO space -&gt; VM)&n;&t;&t;&t; *   10  Graphics flush read   (VM -&gt; IO space)&n;&t;&t;&t; *   11  Graphics flush read/write (VM &lt;-&gt; IO space)&n;&t;&t;&t; */
r_if
c_cond
(paren
id|isGraphicsFlushRead
c_func
(paren
id|inst
)paren
)paren
r_return
id|VM_READ
suffix:semicolon
r_return
id|VM_WRITE
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * Check for LDCWX and LDCWS (semaphore instructions).&n;&t;&t;&t; * If bits 23 through 25 are all 1&squot;s it is one of&n;&t;&t;&t; * the above two instructions and is a write.&n;&t;&t;&t; *&n;&t;&t;&t; * Note: With the limited bits we are looking at,&n;&t;&t;&t; * this will also catch PROBEW and PROBEWI. However,&n;&t;&t;&t; * these should never get in here because they don&squot;t&n;&t;&t;&t; * generate exceptions of the type:&n;&t;&t;&t; *   Data TLB miss fault/data page fault&n;&t;&t;&t; *   Data memory protection trap&n;&t;&t;&t; */
r_if
c_cond
(paren
id|bits23_25set
c_func
(paren
id|inst
)paren
op_eq
id|BITSSET
)paren
r_return
id|VM_WRITE
suffix:semicolon
)brace
r_return
id|VM_READ
suffix:semicolon
multiline_comment|/* Default */
)brace
r_return
id|VM_READ
suffix:semicolon
multiline_comment|/* Default */
)brace
DECL|macro|bit22set
macro_line|#undef bit22set
DECL|macro|bits23_25set
macro_line|#undef bits23_25set
DECL|macro|isGraphicsFlushRead
macro_line|#undef isGraphicsFlushRead
DECL|macro|BITSSET
macro_line|#undef BITSSET
macro_line|#if 0
multiline_comment|/* This is the treewalk to find a vma which is the highest that has&n; * a start &lt; addr.  We&squot;re using find_vma_prev instead right now, but&n; * we might want to use this at some point in the future.  Probably&n; * not, but I want it committed to CVS so I don&squot;t lose it :-)&n; */
r_while
c_loop
(paren
id|tree
op_ne
id|vm_avl_empty
)paren
(brace
r_if
c_cond
(paren
id|tree-&gt;vm_start
OG
id|addr
)paren
(brace
id|tree
op_assign
id|tree-&gt;vm_avl_left
suffix:semicolon
)brace
r_else
(brace
id|prev
op_assign
id|tree
suffix:semicolon
r_if
c_cond
(paren
id|prev-&gt;vm_next
op_eq
l_int|NULL
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|prev-&gt;vm_next-&gt;vm_start
OG
id|addr
)paren
r_break
suffix:semicolon
id|tree
op_assign
id|tree-&gt;vm_avl_right
suffix:semicolon
)brace
)brace
macro_line|#endif
DECL|function|do_page_fault
r_void
id|do_page_fault
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|code
comma
r_int
r_int
id|address
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|vma
comma
op_star
id|prev_vma
suffix:semicolon
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|tsk-&gt;mm
suffix:semicolon
r_const
r_struct
id|exception_table_entry
op_star
id|fix
suffix:semicolon
r_int
r_int
id|acc_type
suffix:semicolon
r_if
c_cond
(paren
id|in_interrupt
c_func
(paren
)paren
op_logical_or
op_logical_neg
id|mm
)paren
r_goto
id|no_context
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
id|vma
op_assign
id|find_vma_prev
c_func
(paren
id|mm
comma
id|address
comma
op_amp
id|prev_vma
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma
op_logical_or
id|address
OL
id|vma-&gt;vm_start
)paren
r_goto
id|check_expansion
suffix:semicolon
multiline_comment|/*&n; * Ok, we have a good vm_area for this memory access. We still need to&n; * check the access permissions.&n; */
id|good_area
suffix:colon
id|acc_type
op_assign
id|parisc_acctyp
c_func
(paren
id|code
comma
id|regs-&gt;iir
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|vma-&gt;vm_flags
op_amp
id|acc_type
)paren
op_ne
id|acc_type
)paren
r_goto
id|bad_area
suffix:semicolon
multiline_comment|/*&n;&t; * If for any reason at all we couldn&squot;t handle the fault, make&n;&t; * sure we exit gracefully rather than endlessly redo the&n;&t; * fault.&n;&t; */
r_switch
c_cond
(paren
id|handle_mm_fault
c_func
(paren
id|mm
comma
id|vma
comma
id|address
comma
(paren
id|acc_type
op_amp
id|VM_WRITE
)paren
op_ne
l_int|0
)paren
)paren
(brace
r_case
l_int|1
suffix:colon
op_increment
id|current-&gt;min_flt
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
op_increment
id|current-&gt;maj_flt
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0
suffix:colon
multiline_comment|/*&n;&t;&t; * We ran out of memory, or some other thing happened&n;&t;&t; * to us that made us unable to handle the page fault&n;&t;&t; * gracefully.&n;&t;&t; */
r_goto
id|bad_area
suffix:semicolon
r_default
suffix:colon
r_goto
id|out_of_memory
suffix:semicolon
)brace
id|up_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
r_return
suffix:semicolon
id|check_expansion
suffix:colon
id|vma
op_assign
id|prev_vma
suffix:semicolon
r_if
c_cond
(paren
id|vma
op_logical_and
(paren
id|expand_stack
c_func
(paren
id|vma
comma
id|address
)paren
op_eq
l_int|0
)paren
)paren
r_goto
id|good_area
suffix:semicolon
multiline_comment|/*&n; * Something tried to access memory that isn&squot;t in our memory map..&n; */
id|bad_area
suffix:colon
id|up_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|user_mode
c_func
(paren
id|regs
)paren
)paren
(brace
r_struct
id|siginfo
id|si
suffix:semicolon
macro_line|#ifdef PRINT_USER_FAULTS
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;do_page_fault() pid=%d command=&squot;%s&squot; type=%lu address=0x%08lx&bslash;n&quot;
comma
id|tsk-&gt;pid
comma
id|tsk-&gt;comm
comma
id|code
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vma
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;vm_start = 0x%08lx, vm_end = 0x%08lx&bslash;n&quot;
comma
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_end
)paren
suffix:semicolon
)brace
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* FIXME: actually we need to get the signo and code correct */
id|si.si_signo
op_assign
id|SIGSEGV
suffix:semicolon
id|si.si_errno
op_assign
l_int|0
suffix:semicolon
id|si.si_code
op_assign
id|SEGV_MAPERR
suffix:semicolon
id|si.si_addr
op_assign
(paren
r_void
op_star
)paren
id|address
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGSEGV
comma
op_amp
id|si
comma
id|current
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|no_context
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|user_mode
c_func
(paren
id|regs
)paren
)paren
(brace
id|fix
op_assign
id|search_exception_tables
c_func
(paren
id|regs-&gt;iaoq
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fix
)paren
(brace
r_if
c_cond
(paren
id|fix-&gt;skip
op_amp
l_int|1
)paren
id|regs-&gt;gr
(braket
l_int|8
)braket
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|fix-&gt;skip
op_amp
l_int|2
)paren
id|regs-&gt;gr
(braket
l_int|9
)braket
op_assign
l_int|0
suffix:semicolon
id|regs-&gt;iaoq
(braket
l_int|0
)braket
op_add_assign
(paren
(paren
id|fix-&gt;skip
)paren
op_amp
op_complement
l_int|3
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * NOTE: In some cases the faulting instruction&n;&t;&t;&t; * may be in the delay slot of a branch. We&n;&t;&t;&t; * don&squot;t want to take the branch, so we don&squot;t&n;&t;&t;&t; * increment iaoq[1], instead we set it to be&n;&t;&t;&t; * iaoq[0]+4, and clear the B bit in the PSW&n;&t;&t;&t; */
id|regs-&gt;iaoq
(braket
l_int|1
)braket
op_assign
id|regs-&gt;iaoq
(braket
l_int|0
)braket
op_plus
l_int|4
suffix:semicolon
id|regs-&gt;gr
(braket
l_int|0
)braket
op_and_assign
op_complement
id|PSW_B
suffix:semicolon
multiline_comment|/* IPSW in gr[0] */
r_return
suffix:semicolon
)brace
)brace
id|parisc_terminate
c_func
(paren
l_string|&quot;Bad Address (null pointer deref?)&quot;
comma
id|regs
comma
id|code
comma
id|address
)paren
suffix:semicolon
id|out_of_memory
suffix:colon
id|up_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;VM: killing process %s&bslash;n&quot;
comma
id|current-&gt;comm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|user_mode
c_func
(paren
id|regs
)paren
)paren
id|do_exit
c_func
(paren
id|SIGKILL
)paren
suffix:semicolon
r_goto
id|no_context
suffix:semicolon
)brace
eof
