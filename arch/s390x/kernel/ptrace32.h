macro_line|#ifndef _PTRACE32_H
DECL|macro|_PTRACE32_H
mdefine_line|#define _PTRACE32_H
macro_line|#include &quot;linux32.h&quot;  /* needed for _psw_t32 */
r_typedef
r_struct
(brace
DECL|member|cr
id|__u32
id|cr
(braket
l_int|3
)braket
suffix:semicolon
DECL|typedef|per_cr_words32
)brace
id|per_cr_words32
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|perc_atmid
id|__u16
id|perc_atmid
suffix:semicolon
multiline_comment|/* 0x096 */
DECL|member|address
id|__u32
id|address
suffix:semicolon
multiline_comment|/* 0x098 */
DECL|member|access_id
id|__u8
id|access_id
suffix:semicolon
multiline_comment|/* 0x0a1 */
DECL|typedef|per_lowcore_words32
)brace
id|per_lowcore_words32
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_typedef
r_struct
(brace
r_union
(brace
DECL|member|words
id|per_cr_words32
id|words
suffix:semicolon
DECL|member|control_regs
)brace
id|control_regs
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Use these flags instead of setting em_instruction_fetch&n;&t; * directly they are used so that single stepping can be&n;&t; * switched on &amp; off while not affecting other tracing&n;&t; */
DECL|member|single_step
r_int
id|single_step
suffix:colon
l_int|1
suffix:semicolon
DECL|member|instruction_fetch
r_int
id|instruction_fetch
suffix:colon
l_int|1
suffix:semicolon
r_int
suffix:colon
l_int|30
suffix:semicolon
multiline_comment|/*&n;&t; * These addresses are copied into cr10 &amp; cr11 if single&n;&t; * stepping is switched off&n;&t; */
DECL|member|starting_addr
id|__u32
id|starting_addr
suffix:semicolon
DECL|member|ending_addr
id|__u32
id|ending_addr
suffix:semicolon
r_union
(brace
DECL|member|words
id|per_lowcore_words32
id|words
suffix:semicolon
DECL|member|lowcore
)brace
id|lowcore
suffix:semicolon
DECL|typedef|per_struct32
)brace
id|per_struct32
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|user_regs_struct32
r_struct
id|user_regs_struct32
(brace
DECL|member|psw
id|_psw_t32
id|psw
suffix:semicolon
DECL|member|gprs
id|u32
id|gprs
(braket
id|NUM_GPRS
)braket
suffix:semicolon
DECL|member|acrs
id|u32
id|acrs
(braket
id|NUM_ACRS
)braket
suffix:semicolon
DECL|member|orig_gpr2
id|u32
id|orig_gpr2
suffix:semicolon
DECL|member|fp_regs
id|s390_fp_regs
id|fp_regs
suffix:semicolon
multiline_comment|/*&n;&t; * These per registers are in here so that gdb can modify them&n;&t; * itself as there is no &quot;official&quot; ptrace interface for hardware&n;&t; * watchpoints. This is the way intel does it.&n;&t; */
DECL|member|per_info
id|per_struct32
id|per_info
suffix:semicolon
DECL|member|ieee_instruction_pointer
id|u32
id|ieee_instruction_pointer
suffix:semicolon
multiline_comment|/* Used to give failing instruction back to user for ieee exceptions */
)brace
suffix:semicolon
DECL|struct|user32
r_struct
id|user32
(brace
multiline_comment|/* We start with the registers, to mimic the way that &quot;memory&quot;&n;&t;   is returned from the ptrace(3,...) function.  */
DECL|member|regs
r_struct
id|user_regs_struct32
id|regs
suffix:semicolon
multiline_comment|/* Where the registers are actually stored */
multiline_comment|/* The rest of this junk is to help gdb figure out what goes where */
DECL|member|u_tsize
id|u32
id|u_tsize
suffix:semicolon
multiline_comment|/* Text segment size (pages). */
DECL|member|u_dsize
id|u32
id|u_dsize
suffix:semicolon
multiline_comment|/* Data segment size (pages). */
DECL|member|u_ssize
id|u32
id|u_ssize
suffix:semicolon
multiline_comment|/* Stack segment size (pages). */
DECL|member|start_code
id|u32
id|start_code
suffix:semicolon
multiline_comment|/* Starting virtual address of text. */
DECL|member|start_stack
id|u32
id|start_stack
suffix:semicolon
multiline_comment|/* Starting virtual address of stack area.&n;&t;&t;&t;&t;   This is actually the bottom of the stack,&n;&t;&t;&t;&t;   the top of the stack is always found in the&n;&t;&t;&t;&t;   esp register.  */
DECL|member|signal
id|s32
id|signal
suffix:semicolon
multiline_comment|/* Signal that caused the core dump. */
DECL|member|u_ar0
id|u32
id|u_ar0
suffix:semicolon
multiline_comment|/* Used by gdb to help find the values for */
multiline_comment|/* the registers. */
DECL|member|magic
id|u32
id|magic
suffix:semicolon
multiline_comment|/* To uniquely identify a core file */
DECL|member|u_comm
r_char
id|u_comm
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* User command that was responsible */
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|len
id|__u32
id|len
suffix:semicolon
DECL|member|kernel_addr
id|__u32
id|kernel_addr
suffix:semicolon
DECL|member|process_addr
id|__u32
id|process_addr
suffix:semicolon
DECL|typedef|ptrace_area_emu31
)brace
id|ptrace_area_emu31
suffix:semicolon
macro_line|#endif /* _PTRACE32_H */
eof
