multiline_comment|/*&n; *&t;linux/arch/i386/kernel/ioport.c&n; *&n; * This contains the io-permission bitmap code - written by obz, with changes&n; * by Linus.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/thread_info.h&gt;
multiline_comment|/* Set EXTENT bits starting at BASE in BITMAP to value TURN_ON. */
DECL|function|set_bitmap
r_static
r_void
id|set_bitmap
c_func
(paren
r_int
r_int
op_star
id|bitmap
comma
r_int
r_int
id|base
comma
r_int
r_int
id|extent
comma
r_int
id|new_value
)paren
(brace
r_int
r_int
id|mask
suffix:semicolon
r_int
r_int
op_star
id|bitmap_base
op_assign
id|bitmap
op_plus
(paren
id|base
op_div
id|BITS_PER_LONG
)paren
suffix:semicolon
r_int
r_int
id|low_index
op_assign
id|base
op_amp
(paren
id|BITS_PER_LONG
op_minus
l_int|1
)paren
suffix:semicolon
r_int
id|length
op_assign
id|low_index
op_plus
id|extent
suffix:semicolon
r_if
c_cond
(paren
id|low_index
op_ne
l_int|0
)paren
(brace
id|mask
op_assign
(paren
op_complement
l_int|0UL
op_lshift
id|low_index
)paren
suffix:semicolon
r_if
c_cond
(paren
id|length
OL
id|BITS_PER_LONG
)paren
id|mask
op_and_assign
op_complement
(paren
op_complement
l_int|0UL
op_lshift
id|length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_value
)paren
op_star
id|bitmap_base
op_increment
op_or_assign
id|mask
suffix:semicolon
r_else
op_star
id|bitmap_base
op_increment
op_and_assign
op_complement
id|mask
suffix:semicolon
id|length
op_sub_assign
id|BITS_PER_LONG
suffix:semicolon
)brace
id|mask
op_assign
(paren
id|new_value
ques
c_cond
op_complement
l_int|0UL
suffix:colon
l_int|0UL
)paren
suffix:semicolon
r_while
c_loop
(paren
id|length
op_ge
id|BITS_PER_LONG
)paren
(brace
op_star
id|bitmap_base
op_increment
op_assign
id|mask
suffix:semicolon
id|length
op_sub_assign
id|BITS_PER_LONG
suffix:semicolon
)brace
r_if
c_cond
(paren
id|length
OG
l_int|0
)paren
(brace
id|mask
op_assign
op_complement
(paren
op_complement
l_int|0UL
op_lshift
id|length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_value
)paren
op_star
id|bitmap_base
op_increment
op_or_assign
id|mask
suffix:semicolon
r_else
op_star
id|bitmap_base
op_increment
op_and_assign
op_complement
id|mask
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * this changes the io permissions bitmap in the current task.&n; */
DECL|function|sys_ioperm
id|asmlinkage
r_int
id|sys_ioperm
c_func
(paren
r_int
r_int
id|from
comma
r_int
r_int
id|num
comma
r_int
id|turn_on
)paren
(brace
r_struct
id|thread_struct
op_star
id|t
op_assign
op_amp
id|current-&gt;thread
suffix:semicolon
r_struct
id|tss_struct
op_star
id|tss
suffix:semicolon
r_int
r_int
op_star
id|bitmap
suffix:semicolon
r_if
c_cond
(paren
(paren
id|from
op_plus
id|num
op_le
id|from
)paren
op_logical_or
(paren
id|from
op_plus
id|num
OG
id|IO_BITMAP_BITS
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|turn_on
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_RAWIO
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
multiline_comment|/*&n;&t; * If it&squot;s the first ioperm() call in this thread&squot;s lifetime, set the&n;&t; * IO bitmap up. ioperm() is much less timing critical than clone(),&n;&t; * this is why we delay this operation until now:&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|t-&gt;io_bitmap_ptr
)paren
(brace
id|bitmap
op_assign
id|kmalloc
c_func
(paren
id|IO_BITMAP_BYTES
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bitmap
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|bitmap
comma
l_int|0xff
comma
id|IO_BITMAP_BYTES
)paren
suffix:semicolon
id|t-&gt;io_bitmap_ptr
op_assign
id|bitmap
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * do it in the per-thread copy and in the TSS ...&n;&t; */
id|set_bitmap
c_func
(paren
id|t-&gt;io_bitmap_ptr
comma
id|from
comma
id|num
comma
op_logical_neg
id|turn_on
)paren
suffix:semicolon
id|tss
op_assign
id|init_tss
op_plus
id|get_cpu
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tss-&gt;io_bitmap_base
op_eq
id|IO_BITMAP_OFFSET
)paren
(brace
multiline_comment|/* already active? */
id|set_bitmap
c_func
(paren
id|tss-&gt;io_bitmap
comma
id|from
comma
id|num
comma
op_logical_neg
id|turn_on
)paren
suffix:semicolon
)brace
r_else
(brace
id|memcpy
c_func
(paren
id|tss-&gt;io_bitmap
comma
id|t-&gt;io_bitmap_ptr
comma
id|IO_BITMAP_BYTES
)paren
suffix:semicolon
id|tss-&gt;io_bitmap_base
op_assign
id|IO_BITMAP_OFFSET
suffix:semicolon
multiline_comment|/* Activate it in the TSS */
)brace
id|put_cpu
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * sys_iopl has to be used when you want to access the IO ports&n; * beyond the 0x3ff range: to get the full 65536 ports bitmapped&n; * you&squot;d need 8kB of bitmaps/process, which is a bit excessive.&n; *&n; * Here we just change the eflags value on the stack: we allow&n; * only the super-user to do it. This depends on the stack-layout&n; * on system-call entry - see also fork() and the signal handling&n; * code.&n; */
DECL|function|sys_iopl
id|asmlinkage
r_int
id|sys_iopl
c_func
(paren
r_int
r_int
id|unused
)paren
(brace
r_volatile
r_struct
id|pt_regs
op_star
id|regs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
op_amp
id|unused
suffix:semicolon
r_int
r_int
id|level
op_assign
id|regs-&gt;ebx
suffix:semicolon
r_int
r_int
id|old
op_assign
(paren
id|regs-&gt;eflags
op_rshift
l_int|12
)paren
op_amp
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|level
OG
l_int|3
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Trying to gain more privileges? */
r_if
c_cond
(paren
id|level
OG
id|old
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_RAWIO
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
id|regs-&gt;eflags
op_assign
(paren
id|regs-&gt;eflags
op_amp
op_complement
l_int|0x3000UL
)paren
op_or
(paren
id|level
op_lshift
l_int|12
)paren
suffix:semicolon
multiline_comment|/* Make sure we return the long way (not sysenter) */
id|set_thread_flag
c_func
(paren
id|TIF_IRET
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
