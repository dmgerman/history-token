multiline_comment|/*&n; *  linux/arch/arm/kernel/ptrace.c&n; *&n; *  By Ross Biro 1/23/92&n; * edited by Linus Torvalds&n; * ARM modifications Copyright (C) 2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &quot;ptrace.h&quot;
DECL|macro|REG_PC
mdefine_line|#define REG_PC&t;15
DECL|macro|REG_PSR
mdefine_line|#define REG_PSR&t;16
multiline_comment|/*&n; * does not yet catch signals sent when the child dies.&n; * in exit.c or in signal.c.&n; */
macro_line|#if 0
multiline_comment|/*&n; * Breakpoint SWI instruction: SWI &amp;9F0001&n; */
mdefine_line|#define BREAKINST_ARM&t;0xef9f0001
mdefine_line|#define BREAKINST_THUMB&t;0xdf00&t;&t;/* fill this in later */
macro_line|#else
multiline_comment|/*&n; * New breakpoints - use an undefined instruction.  The ARM architecture&n; * reference manual guarantees that the following instruction space&n; * will produce an undefined instruction exception on all CPUs:&n; *&n; *  ARM:   xxxx 0111 1111 xxxx xxxx xxxx 1111 xxxx&n; *  Thumb: 1101 1110 xxxx xxxx&n; */
DECL|macro|BREAKINST_ARM
mdefine_line|#define BREAKINST_ARM&t;0xe7f001f0
DECL|macro|BREAKINST_THUMB
mdefine_line|#define BREAKINST_THUMB&t;0xde01
macro_line|#endif
multiline_comment|/*&n; * Get the address of the live pt_regs for the specified task.&n; * These are saved onto the top kernel stack when the process&n; * is not running.&n; *&n; * Note: if a user thread is execve&squot;d from kernel space, the&n; * kernel stack will not be empty on entry to the kernel, so&n; * ptracing these tasks will fail.&n; */
r_static
r_inline
r_struct
id|pt_regs
op_star
DECL|function|get_user_regs
id|get_user_regs
c_func
(paren
r_struct
id|task_struct
op_star
id|task
)paren
(brace
r_return
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|task-&gt;thread_info
op_plus
id|THREAD_SIZE
op_minus
l_int|8
op_minus
r_sizeof
(paren
r_struct
id|pt_regs
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * this routine will get a word off of the processes privileged stack.&n; * the offset is how far from the base addr as stored in the THREAD.&n; * this routine assumes that all the privileged stacks are in our&n; * data space.&n; */
DECL|function|get_user_reg
r_static
r_inline
r_int
id|get_user_reg
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
id|offset
)paren
(brace
r_return
id|get_user_regs
c_func
(paren
id|task
)paren
op_member_access_from_pointer
id|uregs
(braket
id|offset
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; * this routine will put a word on the processes privileged stack.&n; * the offset is how far from the base addr as stored in the THREAD.&n; * this routine assumes that all the privileged stacks are in our&n; * data space.&n; */
r_static
r_inline
r_int
DECL|function|put_user_reg
id|put_user_reg
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
id|offset
comma
r_int
id|data
)paren
(brace
r_struct
id|pt_regs
id|newregs
comma
op_star
id|regs
op_assign
id|get_user_regs
c_func
(paren
id|task
)paren
suffix:semicolon
r_int
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|newregs
op_assign
op_star
id|regs
suffix:semicolon
id|newregs.uregs
(braket
id|offset
)braket
op_assign
id|data
suffix:semicolon
r_if
c_cond
(paren
id|valid_user_regs
c_func
(paren
op_amp
id|newregs
)paren
)paren
(brace
id|regs-&gt;uregs
(braket
id|offset
)braket
op_assign
id|data
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|read_u32
id|read_u32
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
comma
id|u32
op_star
id|res
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|access_process_vm
c_func
(paren
id|task
comma
id|addr
comma
id|res
comma
r_sizeof
(paren
op_star
id|res
)paren
comma
l_int|0
)paren
suffix:semicolon
r_return
id|ret
op_eq
r_sizeof
(paren
op_star
id|res
)paren
ques
c_cond
l_int|0
suffix:colon
op_minus
id|EIO
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|read_instr
id|read_instr
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
comma
id|u32
op_star
id|res
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_amp
l_int|1
)paren
(brace
id|u16
id|val
suffix:semicolon
id|ret
op_assign
id|access_process_vm
c_func
(paren
id|task
comma
id|addr
op_amp
op_complement
l_int|1
comma
op_amp
id|val
comma
r_sizeof
(paren
id|val
)paren
comma
l_int|0
)paren
suffix:semicolon
id|ret
op_assign
id|ret
op_eq
r_sizeof
(paren
id|val
)paren
ques
c_cond
l_int|0
suffix:colon
op_minus
id|EIO
suffix:semicolon
op_star
id|res
op_assign
id|val
suffix:semicolon
)brace
r_else
(brace
id|u32
id|val
suffix:semicolon
id|ret
op_assign
id|access_process_vm
c_func
(paren
id|task
comma
id|addr
op_amp
op_complement
l_int|3
comma
op_amp
id|val
comma
r_sizeof
(paren
id|val
)paren
comma
l_int|0
)paren
suffix:semicolon
id|ret
op_assign
id|ret
op_eq
r_sizeof
(paren
id|val
)paren
ques
c_cond
l_int|0
suffix:colon
op_minus
id|EIO
suffix:semicolon
op_star
id|res
op_assign
id|val
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Get value of register `rn&squot; (in the instruction)&n; */
r_static
r_int
r_int
DECL|function|ptrace_getrn
id|ptrace_getrn
c_func
(paren
r_struct
id|task_struct
op_star
id|child
comma
r_int
r_int
id|insn
)paren
(brace
r_int
r_int
id|reg
op_assign
(paren
id|insn
op_rshift
l_int|16
)paren
op_amp
l_int|15
suffix:semicolon
r_int
r_int
id|val
suffix:semicolon
id|val
op_assign
id|get_user_reg
c_func
(paren
id|child
comma
id|reg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_eq
l_int|15
)paren
id|val
op_assign
id|pc_pointer
c_func
(paren
id|val
op_plus
l_int|8
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
multiline_comment|/*&n; * Get value of operand 2 (in an ALU instruction)&n; */
r_static
r_int
r_int
DECL|function|ptrace_getaluop2
id|ptrace_getaluop2
c_func
(paren
r_struct
id|task_struct
op_star
id|child
comma
r_int
r_int
id|insn
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
r_int
id|shift
suffix:semicolon
r_int
id|type
suffix:semicolon
r_if
c_cond
(paren
id|insn
op_amp
l_int|1
op_lshift
l_int|25
)paren
(brace
id|val
op_assign
id|insn
op_amp
l_int|255
suffix:semicolon
id|shift
op_assign
(paren
id|insn
op_rshift
l_int|8
)paren
op_amp
l_int|15
suffix:semicolon
id|type
op_assign
l_int|3
suffix:semicolon
)brace
r_else
(brace
id|val
op_assign
id|get_user_reg
(paren
id|child
comma
id|insn
op_amp
l_int|15
)paren
suffix:semicolon
r_if
c_cond
(paren
id|insn
op_amp
(paren
l_int|1
op_lshift
l_int|4
)paren
)paren
id|shift
op_assign
(paren
r_int
)paren
id|get_user_reg
(paren
id|child
comma
(paren
id|insn
op_rshift
l_int|8
)paren
op_amp
l_int|15
)paren
suffix:semicolon
r_else
id|shift
op_assign
(paren
id|insn
op_rshift
l_int|7
)paren
op_amp
l_int|31
suffix:semicolon
id|type
op_assign
(paren
id|insn
op_rshift
l_int|5
)paren
op_amp
l_int|3
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
l_int|0
suffix:colon
id|val
op_lshift_assign
id|shift
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|val
op_rshift_assign
id|shift
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|val
op_assign
(paren
(paren
(paren
r_int
r_int
)paren
id|val
)paren
op_rshift
id|shift
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|val
op_assign
(paren
id|val
op_rshift
id|shift
)paren
op_or
(paren
id|val
op_lshift
(paren
l_int|32
op_minus
id|shift
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|val
suffix:semicolon
)brace
multiline_comment|/*&n; * Get value of operand 2 (in a LDR instruction)&n; */
r_static
r_int
r_int
DECL|function|ptrace_getldrop2
id|ptrace_getldrop2
c_func
(paren
r_struct
id|task_struct
op_star
id|child
comma
r_int
r_int
id|insn
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
r_int
id|shift
suffix:semicolon
r_int
id|type
suffix:semicolon
id|val
op_assign
id|get_user_reg
c_func
(paren
id|child
comma
id|insn
op_amp
l_int|15
)paren
suffix:semicolon
id|shift
op_assign
(paren
id|insn
op_rshift
l_int|7
)paren
op_amp
l_int|31
suffix:semicolon
id|type
op_assign
(paren
id|insn
op_rshift
l_int|5
)paren
op_amp
l_int|3
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
l_int|0
suffix:colon
id|val
op_lshift_assign
id|shift
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|val
op_rshift_assign
id|shift
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|val
op_assign
(paren
(paren
(paren
r_int
r_int
)paren
id|val
)paren
op_rshift
id|shift
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|val
op_assign
(paren
id|val
op_rshift
id|shift
)paren
op_or
(paren
id|val
op_lshift
(paren
l_int|32
op_minus
id|shift
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|val
suffix:semicolon
)brace
DECL|macro|OP_MASK
mdefine_line|#define OP_MASK&t;0x01e00000
DECL|macro|OP_AND
mdefine_line|#define OP_AND&t;0x00000000
DECL|macro|OP_EOR
mdefine_line|#define OP_EOR&t;0x00200000
DECL|macro|OP_SUB
mdefine_line|#define OP_SUB&t;0x00400000
DECL|macro|OP_RSB
mdefine_line|#define OP_RSB&t;0x00600000
DECL|macro|OP_ADD
mdefine_line|#define OP_ADD&t;0x00800000
DECL|macro|OP_ADC
mdefine_line|#define OP_ADC&t;0x00a00000
DECL|macro|OP_SBC
mdefine_line|#define OP_SBC&t;0x00c00000
DECL|macro|OP_RSC
mdefine_line|#define OP_RSC&t;0x00e00000
DECL|macro|OP_ORR
mdefine_line|#define OP_ORR&t;0x01800000
DECL|macro|OP_MOV
mdefine_line|#define OP_MOV&t;0x01a00000
DECL|macro|OP_BIC
mdefine_line|#define OP_BIC&t;0x01c00000
DECL|macro|OP_MVN
mdefine_line|#define OP_MVN&t;0x01e00000
r_static
r_int
r_int
DECL|function|get_branch_address
id|get_branch_address
c_func
(paren
r_struct
id|task_struct
op_star
id|child
comma
r_int
r_int
id|pc
comma
r_int
r_int
id|insn
)paren
(brace
id|u32
id|alt
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|insn
op_amp
l_int|0x0e000000
)paren
(brace
r_case
l_int|0x00000000
suffix:colon
r_case
l_int|0x02000000
suffix:colon
(brace
multiline_comment|/*&n;&t;&t; * data processing&n;&t;&t; */
r_int
id|aluop1
comma
id|aluop2
comma
id|ccbit
suffix:semicolon
r_if
c_cond
(paren
(paren
id|insn
op_amp
l_int|0xf000
)paren
op_ne
l_int|0xf000
)paren
r_break
suffix:semicolon
id|aluop1
op_assign
id|ptrace_getrn
c_func
(paren
id|child
comma
id|insn
)paren
suffix:semicolon
id|aluop2
op_assign
id|ptrace_getaluop2
c_func
(paren
id|child
comma
id|insn
)paren
suffix:semicolon
id|ccbit
op_assign
id|get_user_reg
c_func
(paren
id|child
comma
id|REG_PSR
)paren
op_amp
id|PSR_C_BIT
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|insn
op_amp
id|OP_MASK
)paren
(brace
r_case
id|OP_AND
suffix:colon
id|alt
op_assign
id|aluop1
op_amp
id|aluop2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_EOR
suffix:colon
id|alt
op_assign
id|aluop1
op_xor
id|aluop2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_SUB
suffix:colon
id|alt
op_assign
id|aluop1
op_minus
id|aluop2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_RSB
suffix:colon
id|alt
op_assign
id|aluop2
op_minus
id|aluop1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_ADD
suffix:colon
id|alt
op_assign
id|aluop1
op_plus
id|aluop2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_ADC
suffix:colon
id|alt
op_assign
id|aluop1
op_plus
id|aluop2
op_plus
id|ccbit
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_SBC
suffix:colon
id|alt
op_assign
id|aluop1
op_minus
id|aluop2
op_plus
id|ccbit
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_RSC
suffix:colon
id|alt
op_assign
id|aluop2
op_minus
id|aluop1
op_plus
id|ccbit
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_ORR
suffix:colon
id|alt
op_assign
id|aluop1
op_or
id|aluop2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_MOV
suffix:colon
id|alt
op_assign
id|aluop2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_BIC
suffix:colon
id|alt
op_assign
id|aluop1
op_amp
op_complement
id|aluop2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_MVN
suffix:colon
id|alt
op_assign
op_complement
id|aluop2
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_case
l_int|0x04000000
suffix:colon
r_case
l_int|0x06000000
suffix:colon
multiline_comment|/*&n;&t;&t; * ldr&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|insn
op_amp
l_int|0x0010f000
)paren
op_eq
l_int|0x0010f000
)paren
(brace
r_int
r_int
id|base
suffix:semicolon
id|base
op_assign
id|ptrace_getrn
c_func
(paren
id|child
comma
id|insn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|insn
op_amp
l_int|1
op_lshift
l_int|24
)paren
(brace
r_int
id|aluop2
suffix:semicolon
r_if
c_cond
(paren
id|insn
op_amp
l_int|0x02000000
)paren
id|aluop2
op_assign
id|ptrace_getldrop2
c_func
(paren
id|child
comma
id|insn
)paren
suffix:semicolon
r_else
id|aluop2
op_assign
id|insn
op_amp
l_int|0xfff
suffix:semicolon
r_if
c_cond
(paren
id|insn
op_amp
l_int|1
op_lshift
l_int|23
)paren
id|base
op_add_assign
id|aluop2
suffix:semicolon
r_else
id|base
op_sub_assign
id|aluop2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|read_u32
c_func
(paren
id|child
comma
id|base
comma
op_amp
id|alt
)paren
op_eq
l_int|0
)paren
id|alt
op_assign
id|pc_pointer
c_func
(paren
id|alt
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|0x08000000
suffix:colon
multiline_comment|/*&n;&t;&t; * ldm&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|insn
op_amp
l_int|0x00108000
)paren
op_eq
l_int|0x00108000
)paren
(brace
r_int
r_int
id|base
suffix:semicolon
r_int
r_int
id|nr_regs
suffix:semicolon
r_if
c_cond
(paren
id|insn
op_amp
(paren
l_int|1
op_lshift
l_int|23
)paren
)paren
(brace
id|nr_regs
op_assign
id|hweight16
c_func
(paren
id|insn
op_amp
l_int|65535
)paren
op_lshift
l_int|2
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|insn
op_amp
(paren
l_int|1
op_lshift
l_int|24
)paren
)paren
)paren
id|nr_regs
op_sub_assign
l_int|4
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|insn
op_amp
(paren
l_int|1
op_lshift
l_int|24
)paren
)paren
id|nr_regs
op_assign
op_minus
l_int|4
suffix:semicolon
r_else
id|nr_regs
op_assign
l_int|0
suffix:semicolon
)brace
id|base
op_assign
id|ptrace_getrn
c_func
(paren
id|child
comma
id|insn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_u32
c_func
(paren
id|child
comma
id|base
op_plus
id|nr_regs
comma
op_amp
id|alt
)paren
op_eq
l_int|0
)paren
id|alt
op_assign
id|pc_pointer
c_func
(paren
id|alt
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|0x0a000000
suffix:colon
(brace
multiline_comment|/*&n;&t;&t; * bl or b&n;&t;&t; */
r_int
r_int
id|displ
suffix:semicolon
multiline_comment|/* It&squot;s a branch/branch link: instead of trying to&n;&t;&t; * figure out whether the branch will be taken or not,&n;&t;&t; * we&squot;ll put a breakpoint at both locations.  This is&n;&t;&t; * simpler, more reliable, and probably not a whole lot&n;&t;&t; * slower than the alternative approach of emulating the&n;&t;&t; * branch.&n;&t;&t; */
id|displ
op_assign
(paren
id|insn
op_amp
l_int|0x00ffffff
)paren
op_lshift
l_int|8
suffix:semicolon
id|displ
op_assign
(paren
id|displ
op_rshift
l_int|6
)paren
op_plus
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|displ
op_ne
l_int|0
op_logical_and
id|displ
op_ne
l_int|4
)paren
id|alt
op_assign
id|pc
op_plus
id|displ
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_return
id|alt
suffix:semicolon
)brace
r_static
r_int
DECL|function|swap_insn
id|swap_insn
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
comma
r_void
op_star
id|old_insn
comma
r_void
op_star
id|new_insn
comma
r_int
id|size
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|access_process_vm
c_func
(paren
id|task
comma
id|addr
comma
id|old_insn
comma
id|size
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|size
)paren
id|ret
op_assign
id|access_process_vm
c_func
(paren
id|task
comma
id|addr
comma
id|new_insn
comma
id|size
comma
l_int|1
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_void
DECL|function|add_breakpoint
id|add_breakpoint
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_struct
id|debug_info
op_star
id|dbg
comma
r_int
r_int
id|addr
)paren
(brace
r_int
id|nr
op_assign
id|dbg-&gt;nsaved
suffix:semicolon
r_if
c_cond
(paren
id|nr
OL
l_int|2
)paren
(brace
id|u32
id|new_insn
op_assign
id|BREAKINST_ARM
suffix:semicolon
r_int
id|res
suffix:semicolon
id|res
op_assign
id|swap_insn
c_func
(paren
id|task
comma
id|addr
comma
op_amp
id|dbg-&gt;bp
(braket
id|nr
)braket
dot
id|insn
comma
op_amp
id|new_insn
comma
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
op_eq
l_int|4
)paren
(brace
id|dbg-&gt;bp
(braket
id|nr
)braket
dot
id|address
op_assign
id|addr
suffix:semicolon
id|dbg-&gt;nsaved
op_add_assign
l_int|1
suffix:semicolon
)brace
)brace
r_else
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ptrace: too many breakpoints&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Clear one breakpoint in the user program.  We copy what the hardware&n; * does and use bit 0 of the address to indicate whether this is a Thumb&n; * breakpoint or an ARM breakpoint.&n; */
DECL|function|clear_breakpoint
r_static
r_void
id|clear_breakpoint
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_struct
id|debug_entry
op_star
id|bp
)paren
(brace
r_int
r_int
id|addr
op_assign
id|bp-&gt;address
suffix:semicolon
r_union
id|debug_insn
id|old_insn
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_amp
l_int|1
)paren
(brace
id|ret
op_assign
id|swap_insn
c_func
(paren
id|task
comma
id|addr
op_amp
op_complement
l_int|1
comma
op_amp
id|old_insn.thumb
comma
op_amp
id|bp-&gt;insn.thumb
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|2
op_logical_or
id|old_insn.thumb
op_ne
id|BREAKINST_THUMB
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s:%d: corrupted Thumb breakpoint at &quot;
l_string|&quot;0x%08lx (0x%04x)&bslash;n&quot;
comma
id|task-&gt;comm
comma
id|task-&gt;pid
comma
id|addr
comma
id|old_insn.thumb
)paren
suffix:semicolon
)brace
r_else
(brace
id|ret
op_assign
id|swap_insn
c_func
(paren
id|task
comma
id|addr
op_amp
op_complement
l_int|3
comma
op_amp
id|old_insn.arm
comma
op_amp
id|bp-&gt;insn.arm
comma
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|4
op_logical_or
id|old_insn.arm
op_ne
id|BREAKINST_ARM
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s:%d: corrupted ARM breakpoint at &quot;
l_string|&quot;0x%08lx (0x%08x)&bslash;n&quot;
comma
id|task-&gt;comm
comma
id|task-&gt;pid
comma
id|addr
comma
id|old_insn.arm
)paren
suffix:semicolon
)brace
)brace
DECL|function|ptrace_set_bpt
r_void
id|ptrace_set_bpt
c_func
(paren
r_struct
id|task_struct
op_star
id|child
)paren
(brace
r_struct
id|pt_regs
op_star
id|regs
suffix:semicolon
r_int
r_int
id|pc
suffix:semicolon
id|u32
id|insn
suffix:semicolon
r_int
id|res
suffix:semicolon
id|regs
op_assign
id|get_user_regs
c_func
(paren
id|child
)paren
suffix:semicolon
id|pc
op_assign
id|instruction_pointer
c_func
(paren
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|thumb_mode
c_func
(paren
id|regs
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ptrace: can&squot;t handle thumb mode&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|res
op_assign
id|read_instr
c_func
(paren
id|child
comma
id|pc
comma
op_amp
id|insn
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
(brace
r_struct
id|debug_info
op_star
id|dbg
op_assign
op_amp
id|child-&gt;thread.debug
suffix:semicolon
r_int
r_int
id|alt
suffix:semicolon
id|dbg-&gt;nsaved
op_assign
l_int|0
suffix:semicolon
id|alt
op_assign
id|get_branch_address
c_func
(paren
id|child
comma
id|pc
comma
id|insn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|alt
)paren
id|add_breakpoint
c_func
(paren
id|child
comma
id|dbg
comma
id|alt
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Note that we ignore the result of setting the above&n;&t;&t; * breakpoint since it may fail.  When it does, this is&n;&t;&t; * not so much an error, but a forewarning that we may&n;&t;&t; * be receiving a prefetch abort shortly.&n;&t;&t; *&n;&t;&t; * If we don&squot;t set this breakpoint here, then we can&n;&t;&t; * lose control of the thread during single stepping.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|alt
op_logical_or
id|predicate
c_func
(paren
id|insn
)paren
op_ne
id|PREDICATE_ALWAYS
)paren
id|add_breakpoint
c_func
(paren
id|child
comma
id|dbg
comma
id|pc
op_plus
l_int|4
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Ensure no single-step breakpoint is pending.  Returns non-zero&n; * value if child was being single-stepped.&n; */
DECL|function|ptrace_cancel_bpt
r_void
id|ptrace_cancel_bpt
c_func
(paren
r_struct
id|task_struct
op_star
id|child
)paren
(brace
r_int
id|i
comma
id|nsaved
op_assign
id|child-&gt;thread.debug.nsaved
suffix:semicolon
id|child-&gt;thread.debug.nsaved
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|nsaved
OG
l_int|2
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ptrace_cancel_bpt: bogus nsaved: %d!&bslash;n&quot;
comma
id|nsaved
)paren
suffix:semicolon
id|nsaved
op_assign
l_int|2
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nsaved
suffix:semicolon
id|i
op_increment
)paren
id|clear_breakpoint
c_func
(paren
id|child
comma
op_amp
id|child-&gt;thread.debug.bp
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Called by kernel/ptrace.c when detaching..&n; *&n; * Make sure the single step bit is not set.&n; */
DECL|function|ptrace_disable
r_void
id|ptrace_disable
c_func
(paren
r_struct
id|task_struct
op_star
id|child
)paren
(brace
id|child-&gt;ptrace
op_and_assign
op_complement
id|PT_SINGLESTEP
suffix:semicolon
id|ptrace_cancel_bpt
c_func
(paren
id|child
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Handle hitting a breakpoint.&n; */
DECL|function|ptrace_break
r_void
id|ptrace_break
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|siginfo_t
id|info
suffix:semicolon
id|ptrace_cancel_bpt
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|info.si_signo
op_assign
id|SIGTRAP
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
id|info.si_code
op_assign
id|TRAP_BRKPT
suffix:semicolon
id|info.si_addr
op_assign
(paren
r_void
op_star
)paren
id|instruction_pointer
c_func
(paren
id|regs
)paren
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGTRAP
comma
op_amp
id|info
comma
id|tsk
)paren
suffix:semicolon
)brace
DECL|function|break_trap
r_static
r_int
id|break_trap
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|instr
)paren
(brace
id|ptrace_break
c_func
(paren
id|current
comma
id|regs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|arm_break_hook
r_static
r_struct
id|undef_hook
id|arm_break_hook
op_assign
(brace
dot
id|instr_mask
op_assign
l_int|0x0fffffff
comma
dot
id|instr_val
op_assign
l_int|0x07f001f0
comma
dot
id|cpsr_mask
op_assign
id|PSR_T_BIT
comma
dot
id|cpsr_val
op_assign
l_int|0
comma
dot
id|fn
op_assign
id|break_trap
comma
)brace
suffix:semicolon
DECL|variable|thumb_break_hook
r_static
r_struct
id|undef_hook
id|thumb_break_hook
op_assign
(brace
dot
id|instr_mask
op_assign
l_int|0xffff
comma
dot
id|instr_val
op_assign
l_int|0xde01
comma
dot
id|cpsr_mask
op_assign
id|PSR_T_BIT
comma
dot
id|cpsr_val
op_assign
id|PSR_T_BIT
comma
dot
id|fn
op_assign
id|break_trap
comma
)brace
suffix:semicolon
DECL|function|ptrace_break_init
r_static
r_int
id|__init
id|ptrace_break_init
c_func
(paren
r_void
)paren
(brace
id|register_undef_hook
c_func
(paren
op_amp
id|arm_break_hook
)paren
suffix:semicolon
id|register_undef_hook
c_func
(paren
op_amp
id|thumb_break_hook
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ptrace_break_init
id|core_initcall
c_func
(paren
id|ptrace_break_init
)paren
suffix:semicolon
multiline_comment|/*&n; * Read the word at offset &quot;off&quot; into the &quot;struct user&quot;.  We&n; * actually access the pt_regs stored on the kernel stack.&n; */
DECL|function|ptrace_read_user
r_static
r_int
id|ptrace_read_user
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|off
comma
r_int
r_int
op_star
id|ret
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|off
op_amp
l_int|3
op_logical_or
id|off
op_ge
r_sizeof
(paren
r_struct
id|user
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|tmp
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|off
OL
r_sizeof
(paren
r_struct
id|pt_regs
)paren
)paren
id|tmp
op_assign
id|get_user_reg
c_func
(paren
id|tsk
comma
id|off
op_rshift
l_int|2
)paren
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|tmp
comma
id|ret
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Write the word at offset &quot;off&quot; into &quot;struct user&quot;.  We&n; * actually access the pt_regs stored on the kernel stack.&n; */
DECL|function|ptrace_write_user
r_static
r_int
id|ptrace_write_user
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|off
comma
r_int
r_int
id|val
)paren
(brace
r_if
c_cond
(paren
id|off
op_amp
l_int|3
op_logical_or
id|off
op_ge
r_sizeof
(paren
r_struct
id|user
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|off
op_ge
r_sizeof
(paren
r_struct
id|pt_regs
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|put_user_reg
c_func
(paren
id|tsk
comma
id|off
op_rshift
l_int|2
comma
id|val
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Get all user integer registers.&n; */
DECL|function|ptrace_getregs
r_static
r_int
id|ptrace_getregs
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_void
op_star
id|uregs
)paren
(brace
r_struct
id|pt_regs
op_star
id|regs
op_assign
id|get_user_regs
c_func
(paren
id|tsk
)paren
suffix:semicolon
r_return
id|copy_to_user
c_func
(paren
id|uregs
comma
id|regs
comma
r_sizeof
(paren
r_struct
id|pt_regs
)paren
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Set all user integer registers.&n; */
DECL|function|ptrace_setregs
r_static
r_int
id|ptrace_setregs
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_void
op_star
id|uregs
)paren
(brace
r_struct
id|pt_regs
id|newregs
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|newregs
comma
id|uregs
comma
r_sizeof
(paren
r_struct
id|pt_regs
)paren
)paren
op_eq
l_int|0
)paren
(brace
r_struct
id|pt_regs
op_star
id|regs
op_assign
id|get_user_regs
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|valid_user_regs
c_func
(paren
op_amp
id|newregs
)paren
)paren
(brace
op_star
id|regs
op_assign
id|newregs
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Get the child FPU state.&n; */
DECL|function|ptrace_getfpregs
r_static
r_int
id|ptrace_getfpregs
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_void
op_star
id|ufp
)paren
(brace
r_return
id|copy_to_user
c_func
(paren
id|ufp
comma
op_amp
id|tsk-&gt;thread_info-&gt;fpstate
comma
r_sizeof
(paren
r_struct
id|user_fp
)paren
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Set the child FPU state.&n; */
DECL|function|ptrace_setfpregs
r_static
r_int
id|ptrace_setfpregs
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_void
op_star
id|ufp
)paren
(brace
r_struct
id|thread_info
op_star
id|thread
op_assign
id|tsk-&gt;thread_info
suffix:semicolon
id|thread-&gt;used_cp
(braket
l_int|1
)braket
op_assign
id|thread-&gt;used_cp
(braket
l_int|2
)braket
op_assign
l_int|1
suffix:semicolon
r_return
id|copy_from_user
c_func
(paren
op_amp
id|thread-&gt;fpstate
comma
id|ufp
comma
r_sizeof
(paren
r_struct
id|user_fp
)paren
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|do_ptrace
r_static
r_int
id|do_ptrace
c_func
(paren
r_int
id|request
comma
r_struct
id|task_struct
op_star
id|child
comma
r_int
id|addr
comma
r_int
id|data
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_switch
c_cond
(paren
id|request
)paren
(brace
multiline_comment|/*&n;&t;&t; * read word at location &quot;addr&quot; in the child process.&n;&t;&t; */
r_case
id|PTRACE_PEEKTEXT
suffix:colon
r_case
id|PTRACE_PEEKDATA
suffix:colon
id|ret
op_assign
id|access_process_vm
c_func
(paren
id|child
comma
id|addr
comma
op_amp
id|tmp
comma
r_sizeof
(paren
r_int
r_int
)paren
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
r_sizeof
(paren
r_int
r_int
)paren
)paren
id|ret
op_assign
id|put_user
c_func
(paren
id|tmp
comma
(paren
r_int
r_int
op_star
)paren
id|data
)paren
suffix:semicolon
r_else
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PTRACE_PEEKUSR
suffix:colon
id|ret
op_assign
id|ptrace_read_user
c_func
(paren
id|child
comma
id|addr
comma
(paren
r_int
r_int
op_star
)paren
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * write the word at location addr.&n;&t;&t; */
r_case
id|PTRACE_POKETEXT
suffix:colon
r_case
id|PTRACE_POKEDATA
suffix:colon
id|ret
op_assign
id|access_process_vm
c_func
(paren
id|child
comma
id|addr
comma
op_amp
id|data
comma
r_sizeof
(paren
r_int
r_int
)paren
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
r_sizeof
(paren
r_int
r_int
)paren
)paren
id|ret
op_assign
l_int|0
suffix:semicolon
r_else
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PTRACE_POKEUSR
suffix:colon
id|ret
op_assign
id|ptrace_write_user
c_func
(paren
id|child
comma
id|addr
comma
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * continue/restart and stop at next (return from) syscall&n;&t;&t; */
r_case
id|PTRACE_SYSCALL
suffix:colon
r_case
id|PTRACE_CONT
suffix:colon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|data
OG
id|_NSIG
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|request
op_eq
id|PTRACE_SYSCALL
)paren
id|set_tsk_thread_flag
c_func
(paren
id|child
comma
id|TIF_SYSCALL_TRACE
)paren
suffix:semicolon
r_else
id|clear_tsk_thread_flag
c_func
(paren
id|child
comma
id|TIF_SYSCALL_TRACE
)paren
suffix:semicolon
id|child-&gt;exit_code
op_assign
id|data
suffix:semicolon
multiline_comment|/* make sure single-step breakpoint is gone. */
id|child-&gt;ptrace
op_and_assign
op_complement
id|PT_SINGLESTEP
suffix:semicolon
id|ptrace_cancel_bpt
c_func
(paren
id|child
)paren
suffix:semicolon
id|wake_up_process
c_func
(paren
id|child
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * make the child exit.  Best I can do is send it a sigkill.&n;&t;&t; * perhaps it should be put in the status that it wants to&n;&t;&t; * exit.&n;&t;&t; */
r_case
id|PTRACE_KILL
suffix:colon
multiline_comment|/* make sure single-step breakpoint is gone. */
id|child-&gt;ptrace
op_and_assign
op_complement
id|PT_SINGLESTEP
suffix:semicolon
id|ptrace_cancel_bpt
c_func
(paren
id|child
)paren
suffix:semicolon
r_if
c_cond
(paren
id|child-&gt;state
op_ne
id|TASK_ZOMBIE
)paren
(brace
id|child-&gt;exit_code
op_assign
id|SIGKILL
suffix:semicolon
id|wake_up_process
c_func
(paren
id|child
)paren
suffix:semicolon
)brace
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * execute single instruction.&n;&t;&t; */
r_case
id|PTRACE_SINGLESTEP
suffix:colon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|data
OG
id|_NSIG
)paren
r_break
suffix:semicolon
id|child-&gt;ptrace
op_or_assign
id|PT_SINGLESTEP
suffix:semicolon
id|clear_tsk_thread_flag
c_func
(paren
id|child
comma
id|TIF_SYSCALL_TRACE
)paren
suffix:semicolon
id|child-&gt;exit_code
op_assign
id|data
suffix:semicolon
multiline_comment|/* give it a chance to run. */
id|wake_up_process
c_func
(paren
id|child
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PTRACE_DETACH
suffix:colon
id|ret
op_assign
id|ptrace_detach
c_func
(paren
id|child
comma
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PTRACE_GETREGS
suffix:colon
id|ret
op_assign
id|ptrace_getregs
c_func
(paren
id|child
comma
(paren
r_void
op_star
)paren
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PTRACE_SETREGS
suffix:colon
id|ret
op_assign
id|ptrace_setregs
c_func
(paren
id|child
comma
(paren
r_void
op_star
)paren
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PTRACE_GETFPREGS
suffix:colon
id|ret
op_assign
id|ptrace_getfpregs
c_func
(paren
id|child
comma
(paren
r_void
op_star
)paren
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PTRACE_SETFPREGS
suffix:colon
id|ret
op_assign
id|ptrace_setfpregs
c_func
(paren
id|child
comma
(paren
r_void
op_star
)paren
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ret
op_assign
id|ptrace_request
c_func
(paren
id|child
comma
id|request
comma
id|addr
comma
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|sys_ptrace
id|asmlinkage
r_int
id|sys_ptrace
c_func
(paren
r_int
id|request
comma
r_int
id|pid
comma
r_int
id|addr
comma
r_int
id|data
)paren
(brace
r_struct
id|task_struct
op_star
id|child
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|request
op_eq
id|PTRACE_TRACEME
)paren
(brace
multiline_comment|/* are we already being traced? */
r_if
c_cond
(paren
id|current-&gt;ptrace
op_amp
id|PT_PTRACED
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
id|security_ptrace
c_func
(paren
id|current-&gt;parent
comma
id|current
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* set the ptrace bit in the process flags. */
id|current-&gt;ptrace
op_or_assign
id|PT_PTRACED
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|ret
op_assign
op_minus
id|ESRCH
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|child
op_assign
id|find_task_by_pid
c_func
(paren
id|pid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|child
)paren
id|get_task_struct
c_func
(paren
id|child
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|child
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|pid
op_eq
l_int|1
)paren
multiline_comment|/* you may not mess with init */
r_goto
id|out_tsk
suffix:semicolon
r_if
c_cond
(paren
id|request
op_eq
id|PTRACE_ATTACH
)paren
(brace
id|ret
op_assign
id|ptrace_attach
c_func
(paren
id|child
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
id|ret
op_assign
id|ptrace_check_attach
c_func
(paren
id|child
comma
id|request
op_eq
id|PTRACE_KILL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|ret
op_assign
id|do_ptrace
c_func
(paren
id|request
comma
id|child
comma
id|addr
comma
id|data
)paren
suffix:semicolon
id|out_tsk
suffix:colon
id|put_task_struct
c_func
(paren
id|child
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|syscall_trace
id|asmlinkage
r_void
id|syscall_trace
c_func
(paren
r_int
id|why
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|ip
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_thread_flag
c_func
(paren
id|TIF_SYSCALL_TRACE
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|current-&gt;ptrace
op_amp
id|PT_PTRACED
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * Save IP.  IP is used to denote syscall entry/exit:&n;&t; *  IP = 0 -&gt; entry, = 1 -&gt; exit&n;&t; */
id|ip
op_assign
id|regs-&gt;ARM_ip
suffix:semicolon
id|regs-&gt;ARM_ip
op_assign
id|why
suffix:semicolon
multiline_comment|/* the 0x80 provides a way for the tracing parent to distinguish&n;&t;   between a syscall stop and SIGTRAP delivery */
id|current-&gt;exit_code
op_assign
id|SIGTRAP
op_or
(paren
(paren
id|current-&gt;ptrace
op_amp
id|PT_TRACESYSGOOD
)paren
ques
c_cond
l_int|0x80
suffix:colon
l_int|0
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_STOPPED
suffix:semicolon
id|notify_parent
c_func
(paren
id|current
comma
id|SIGCHLD
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * this isn&squot;t the same as continuing with a signal, but it will do&n;&t; * for normal use.  strace only continues with a signal if the&n;&t; * stopping signal is not SIGTRAP.  -brl&n;&t; */
r_if
c_cond
(paren
id|current-&gt;exit_code
)paren
(brace
id|send_sig
c_func
(paren
id|current-&gt;exit_code
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
id|current-&gt;exit_code
op_assign
l_int|0
suffix:semicolon
)brace
id|regs-&gt;ARM_ip
op_assign
id|ip
suffix:semicolon
)brace
eof
