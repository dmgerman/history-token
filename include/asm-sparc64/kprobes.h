macro_line|#ifndef _SPARC64_KPROBES_H
DECL|macro|_SPARC64_KPROBES_H
mdefine_line|#define _SPARC64_KPROBES_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
DECL|typedef|kprobe_opcode_t
r_typedef
id|u32
id|kprobe_opcode_t
suffix:semicolon
DECL|macro|BREAKPOINT_INSTRUCTION
mdefine_line|#define BREAKPOINT_INSTRUCTION   0x91d02070 /* ta 0x70 */
DECL|macro|BREAKPOINT_INSTRUCTION_2
mdefine_line|#define BREAKPOINT_INSTRUCTION_2 0x91d02071 /* ta 0x71 */
DECL|macro|MAX_INSN_SIZE
mdefine_line|#define MAX_INSN_SIZE 2
DECL|macro|JPROBE_ENTRY
mdefine_line|#define JPROBE_ENTRY(pentry)&t;(kprobe_opcode_t *)pentry
multiline_comment|/* Architecture specific copy of original instruction*/
DECL|struct|arch_specific_insn
r_struct
id|arch_specific_insn
(brace
multiline_comment|/* copy of the original instruction */
DECL|member|insn
id|kprobe_opcode_t
id|insn
(braket
id|MAX_INSN_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_KPROBES
r_extern
r_int
id|kprobe_exceptions_notify
c_func
(paren
r_struct
id|notifier_block
op_star
id|self
comma
r_int
r_int
id|val
comma
r_void
op_star
id|data
)paren
suffix:semicolon
macro_line|#else&t;&t;&t;&t;/* !CONFIG_KPROBES */
DECL|function|kprobe_exceptions_notify
r_static
r_inline
r_int
id|kprobe_exceptions_notify
c_func
(paren
r_struct
id|notifier_block
op_star
id|self
comma
r_int
r_int
id|val
comma
r_void
op_star
id|data
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif /* _SPARC64_KPROBES_H */
eof
