multiline_comment|/*&n; *&t;linux/arch/i386/kernel/ioport.c&n; *&n; * This contains the io-permission bitmap code - written by obz, with changes&n; * by Linus.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
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
id|base
comma
r_int
id|extent
comma
r_int
id|new_value
)paren
(brace
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
op_rshift
l_int|6
)paren
suffix:semicolon
r_int
r_int
id|low_index
op_assign
id|base
op_amp
l_int|0x3f
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
l_int|0
op_lshift
id|low_index
)paren
suffix:semicolon
r_if
c_cond
(paren
id|length
OL
l_int|64
)paren
id|mask
op_and_assign
op_complement
(paren
op_complement
l_int|0
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
l_int|32
suffix:semicolon
)brace
id|mask
op_assign
(paren
id|new_value
ques
c_cond
op_complement
l_int|0
suffix:colon
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
id|length
op_ge
l_int|64
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
l_int|64
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
l_int|0
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
op_assign
id|init_tss
op_plus
id|smp_processor_id
c_func
(paren
)paren
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
id|IO_BITMAP_SIZE
op_star
l_int|32
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
r_if
c_cond
(paren
op_logical_neg
id|t-&gt;io_bitmap_ptr
)paren
(brace
id|t-&gt;io_bitmap_ptr
op_assign
id|kmalloc
c_func
(paren
(paren
id|IO_BITMAP_SIZE
op_plus
l_int|1
)paren
op_star
l_int|4
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|t-&gt;io_bitmap_ptr
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|t-&gt;io_bitmap_ptr
comma
l_int|0xff
comma
(paren
id|IO_BITMAP_SIZE
op_plus
l_int|1
)paren
op_star
l_int|4
)paren
suffix:semicolon
id|tss-&gt;io_map_base
op_assign
id|IO_BITMAP_OFFSET
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * do it in the per-thread copy and in the TSS ...&n;&t; */
id|set_bitmap
c_func
(paren
(paren
r_int
r_int
op_star
)paren
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
id|set_bitmap
c_func
(paren
(paren
r_int
r_int
op_star
)paren
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
id|level
comma
r_struct
id|pt_regs
id|regs
)paren
(brace
r_int
r_int
id|old
op_assign
(paren
id|regs.eflags
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
id|regs.eflags
op_assign
(paren
id|regs.eflags
op_amp
l_int|0xffffffffffffcfff
)paren
op_or
(paren
id|level
op_lshift
l_int|12
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
