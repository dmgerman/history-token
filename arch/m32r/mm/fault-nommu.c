multiline_comment|/*&n; *  linux/arch/m32r/mm/fault.c&n; *&n; *  Copyright (c) 2001, 2002  Hitoshi Yamamoto, and H. Kondo&n; *&n; *  Some code taken from i386 version.&n; *    Copyright (C) 1995  Linus Torvalds&n; */
multiline_comment|/* $Id: fault-nommu.c,v 1.1 2004/03/30 06:40:59 sakugawa Exp $ */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/m32r.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
r_extern
r_void
id|die
c_func
(paren
r_const
r_char
op_star
comma
r_struct
id|pt_regs
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
DECL|variable|tlb_entry_i_dat
id|asmlinkage
r_int
r_int
id|tlb_entry_i_dat
suffix:semicolon
DECL|variable|tlb_entry_d_dat
id|asmlinkage
r_int
r_int
id|tlb_entry_d_dat
suffix:semicolon
DECL|macro|tlb_entry_i
mdefine_line|#define tlb_entry_i tlb_entry_i_dat
DECL|macro|tlb_entry_d
mdefine_line|#define tlb_entry_d tlb_entry_d_dat
macro_line|#else
DECL|variable|tlb_entry_i_dat
r_int
r_int
id|tlb_entry_i_dat
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|tlb_entry_d_dat
r_int
r_int
id|tlb_entry_d_dat
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|macro|tlb_entry_i
mdefine_line|#define tlb_entry_i tlb_entry_i_dat[smp_processor_id()]
DECL|macro|tlb_entry_d
mdefine_line|#define tlb_entry_d tlb_entry_d_dat[smp_processor_id()]
macro_line|#endif
multiline_comment|/*&n; * Unlock any spinlocks which will prevent us from getting the&n; * message out&n; */
DECL|function|bust_spinlocks
r_void
id|bust_spinlocks
c_func
(paren
r_int
id|yes
)paren
(brace
r_int
id|loglevel_save
op_assign
id|console_loglevel
suffix:semicolon
r_if
c_cond
(paren
id|yes
)paren
(brace
id|oops_in_progress
op_assign
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_VT
id|unblank_screen
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|oops_in_progress
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * OK, the message is on the console.  Now we call printk()&n;&t; * without oops_in_progress set so that printk will give klogd&n;&t; * a poke.  Hold onto your hats...&n;&t; */
id|console_loglevel
op_assign
l_int|15
suffix:semicolon
multiline_comment|/* NMI oopser may have shut the console up */
id|printk
c_func
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
id|console_loglevel
op_assign
id|loglevel_save
suffix:semicolon
)brace
DECL|function|do_BUG
r_void
id|do_BUG
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
)paren
(brace
id|bust_spinlocks
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;kernel BUG at %s:%d!&bslash;n&quot;
comma
id|file
comma
id|line
)paren
suffix:semicolon
)brace
multiline_comment|/*======================================================================*&n; * do_page_fault()&n; *======================================================================*&n; * This routine handles page faults.  It determines the address,&n; * and the problem, and then passes it off to one of the appropriate&n; * routines.&n; *&n; * ARGUMENT:&n; *  regs       : M32R SP reg.&n; *  error_code : See below&n; *  address    : M32R MMU MDEVA reg. (Operand ACE)&n; *             : M32R BPC reg. (Instruction ACE)&n; *&n; * error_code :&n; *  bit 0 == 0 means no page found, 1 means protection fault&n; *  bit 1 == 0 means read, 1 means write&n; *  bit 2 == 0 means kernel, 1 means user-mode&n; *======================================================================*/
DECL|function|do_page_fault
id|asmlinkage
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
id|error_code
comma
r_int
r_int
id|address
)paren
(brace
multiline_comment|/*&n; * Oops. The kernel tried to access some bad page. We&squot;ll have to&n; * terminate things with extreme prejudice.&n; */
id|bust_spinlocks
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|address
OL
id|PAGE_SIZE
)paren
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;Unable to handle kernel NULL pointer dereference&quot;
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;Unable to handle kernel paging request&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; at virtual address %08lx&bslash;n&quot;
comma
id|address
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; printing bpc:&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;bpc = %08lx&bslash;n&quot;
comma
id|regs-&gt;bpc
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;Oops&quot;
comma
id|regs
comma
id|error_code
)paren
suffix:semicolon
id|bust_spinlocks
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|SIGKILL
)paren
suffix:semicolon
)brace
multiline_comment|/*======================================================================*&n; * update_mmu_cache()&n; *======================================================================*/
DECL|function|update_mmu_cache
r_void
id|update_mmu_cache
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|addr
comma
id|pte_t
id|pte
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*======================================================================*&n; * flush_tlb_page() : flushes one page&n; *======================================================================*/
DECL|function|local_flush_tlb_page
r_void
id|local_flush_tlb_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|page
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*======================================================================*&n; * flush_tlb_range() : flushes a range of pages&n; *======================================================================*/
DECL|function|local_flush_tlb_range
r_void
id|local_flush_tlb_range
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
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*======================================================================*&n; * flush_tlb_mm() : flushes the specified mm context TLB&squot;s&n; *======================================================================*/
DECL|function|local_flush_tlb_mm
r_void
id|local_flush_tlb_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*======================================================================*&n; * flush_tlb_all() : flushes all processes TLBs&n; *======================================================================*/
DECL|function|local_flush_tlb_all
r_void
id|local_flush_tlb_all
c_func
(paren
r_void
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
eof
