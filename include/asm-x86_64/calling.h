multiline_comment|/* &n; * Some macros to handle stack frames in assembly.&n; */
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|R15
mdefine_line|#define R15 0
DECL|macro|R14
mdefine_line|#define R14 8
DECL|macro|R13
mdefine_line|#define R13 16
DECL|macro|R12
mdefine_line|#define R12 24
DECL|macro|RBP
mdefine_line|#define RBP 36
DECL|macro|RBX
mdefine_line|#define RBX 40
multiline_comment|/* arguments: interrupts/non tracing syscalls only save upto here*/
DECL|macro|R11
mdefine_line|#define R11 48
DECL|macro|R10
mdefine_line|#define R10 56&t;
DECL|macro|R9
mdefine_line|#define R9 64
DECL|macro|R8
mdefine_line|#define R8 72
DECL|macro|RAX
mdefine_line|#define RAX 80
DECL|macro|RCX
mdefine_line|#define RCX 88
DECL|macro|RDX
mdefine_line|#define RDX 96
DECL|macro|RSI
mdefine_line|#define RSI 104
DECL|macro|RDI
mdefine_line|#define RDI 112
DECL|macro|ORIG_RAX
mdefine_line|#define ORIG_RAX 120       /* + error_code */ 
multiline_comment|/* end of arguments */
multiline_comment|/* cpu exception frame or undefined in case of fast syscall. */
DECL|macro|RIP
mdefine_line|#define RIP 128
DECL|macro|CS
mdefine_line|#define CS 136
DECL|macro|EFLAGS
mdefine_line|#define EFLAGS 144
DECL|macro|RSP
mdefine_line|#define RSP 152
DECL|macro|SS
mdefine_line|#define SS 160
DECL|macro|ARGOFFSET
mdefine_line|#define ARGOFFSET R11
DECL|variable|norcx
dot
id|macro
id|SAVE_ARGS
id|addskip
op_assign
l_int|0
comma
id|norcx
op_assign
l_int|0
id|subq
"$"
l_int|9
op_star
l_int|8
op_plus
"&bslash;"
id|addskip
comma
op_mod
id|rsp
DECL|variable|rdi
id|movq
op_mod
id|rdi
comma
l_int|8
op_star
l_int|8
(paren
op_mod
id|rsp
)paren
DECL|variable|rsi
id|movq
op_mod
id|rsi
comma
l_int|7
op_star
l_int|8
(paren
op_mod
id|rsp
)paren
DECL|variable|rdx
id|movq
op_mod
id|rdx
comma
l_int|6
op_star
l_int|8
(paren
op_mod
id|rsp
)paren
dot
r_if
c_cond
"&bslash;"
id|norcx
dot
r_else
id|movq
op_mod
id|rcx
comma
l_int|5
op_star
l_int|8
(paren
op_mod
id|rsp
)paren
dot
id|endif
id|movq
op_mod
id|rax
comma
l_int|4
op_star
l_int|8
(paren
op_mod
id|rsp
)paren
DECL|variable|r8
id|movq
op_mod
id|r8
comma
l_int|3
op_star
l_int|8
(paren
op_mod
id|rsp
)paren
DECL|variable|r9
id|movq
op_mod
id|r9
comma
l_int|2
op_star
l_int|8
(paren
op_mod
id|rsp
)paren
DECL|variable|r10
id|movq
op_mod
id|r10
comma
l_int|1
op_star
l_int|8
(paren
op_mod
id|rsp
)paren
DECL|variable|r11
id|movq
op_mod
id|r11
comma
(paren
op_mod
id|rsp
)paren
dot
id|endm
DECL|macro|ARG_SKIP
mdefine_line|#define ARG_SKIP 9*8
DECL|variable|addskip
DECL|variable|skiprcx
dot
id|macro
id|RESTORE_ARGS
id|skiprax
op_assign
l_int|0
comma
id|addskip
op_assign
l_int|0
comma
id|skiprcx
op_assign
l_int|0
id|movq
(paren
op_mod
id|rsp
)paren
comma
op_mod
id|r11
id|movq
l_int|1
op_star
l_int|8
(paren
op_mod
id|rsp
)paren
comma
op_mod
id|r10
id|movq
l_int|2
op_star
l_int|8
(paren
op_mod
id|rsp
)paren
comma
op_mod
id|r9
id|movq
l_int|3
op_star
l_int|8
(paren
op_mod
id|rsp
)paren
comma
op_mod
id|r8
dot
r_if
c_cond
"&bslash;"
id|skiprax
dot
r_else
id|movq
l_int|4
op_star
l_int|8
(paren
op_mod
id|rsp
)paren
comma
op_mod
id|rax
dot
id|endif
dot
r_if
c_cond
"&bslash;"
id|skiprcx
dot
r_else
id|movq
l_int|5
op_star
l_int|8
(paren
op_mod
id|rsp
)paren
comma
op_mod
id|rcx
dot
id|endif
id|movq
l_int|6
op_star
l_int|8
(paren
op_mod
id|rsp
)paren
comma
op_mod
id|rdx
id|movq
l_int|7
op_star
l_int|8
(paren
op_mod
id|rsp
)paren
comma
op_mod
id|rsi
id|movq
l_int|8
op_star
l_int|8
(paren
op_mod
id|rsp
)paren
comma
op_mod
id|rdi
dot
r_if
c_cond
id|ARG_SKIP
op_plus
"&bslash;"
id|addskip
OG
l_int|0
id|addq
"$"
id|ARG_SKIP
op_plus
"&bslash;"
id|addskip
comma
op_mod
id|rsp
dot
id|endif
dot
id|endm
dot
id|macro
id|LOAD_ARGS
id|offset
id|movq
"&bslash;"
id|offset
c_func
(paren
op_mod
id|rsp
)paren
comma
op_mod
id|r11
id|movq
"&bslash;"
id|offset
op_plus
l_int|8
(paren
op_mod
id|rsp
)paren
comma
op_mod
id|r10
id|movq
"&bslash;"
id|offset
op_plus
l_int|16
(paren
op_mod
id|rsp
)paren
comma
op_mod
id|r9
id|movq
"&bslash;"
id|offset
op_plus
l_int|24
(paren
op_mod
id|rsp
)paren
comma
op_mod
id|r8
id|movq
"&bslash;"
id|offset
op_plus
l_int|40
(paren
op_mod
id|rsp
)paren
comma
op_mod
id|rcx
id|movq
"&bslash;"
id|offset
op_plus
l_int|48
(paren
op_mod
id|rsp
)paren
comma
op_mod
id|rdx
id|movq
"&bslash;"
id|offset
op_plus
l_int|56
(paren
op_mod
id|rsp
)paren
comma
op_mod
id|rsi
id|movq
"&bslash;"
id|offset
op_plus
l_int|64
(paren
op_mod
id|rsp
)paren
comma
op_mod
id|rdi
id|movq
"&bslash;"
id|offset
op_plus
l_int|72
(paren
op_mod
id|rsp
)paren
comma
op_mod
id|rax
dot
id|endm
dot
id|macro
id|SAVE_REST
id|subq
"$"
l_int|6
op_star
l_int|8
comma
op_mod
id|rsp
DECL|variable|rbx
id|movq
op_mod
id|rbx
comma
l_int|5
op_star
l_int|8
(paren
op_mod
id|rsp
)paren
DECL|variable|rbp
id|movq
op_mod
id|rbp
comma
l_int|4
op_star
l_int|8
(paren
op_mod
id|rsp
)paren
DECL|variable|r12
id|movq
op_mod
id|r12
comma
l_int|3
op_star
l_int|8
(paren
op_mod
id|rsp
)paren
DECL|variable|r13
id|movq
op_mod
id|r13
comma
l_int|2
op_star
l_int|8
(paren
op_mod
id|rsp
)paren
DECL|variable|r14
id|movq
op_mod
id|r14
comma
l_int|1
op_star
l_int|8
(paren
op_mod
id|rsp
)paren
DECL|variable|r15
id|movq
op_mod
id|r15
comma
(paren
op_mod
id|rsp
)paren
dot
id|endm
DECL|macro|REST_SKIP
mdefine_line|#define REST_SKIP 6*8
dot
id|macro
id|RESTORE_REST
id|movq
(paren
op_mod
id|rsp
)paren
comma
op_mod
id|r15
id|movq
l_int|1
op_star
l_int|8
(paren
op_mod
id|rsp
)paren
comma
op_mod
id|r14
id|movq
l_int|2
op_star
l_int|8
(paren
op_mod
id|rsp
)paren
comma
op_mod
id|r13
id|movq
l_int|3
op_star
l_int|8
(paren
op_mod
id|rsp
)paren
comma
op_mod
id|r12
id|movq
l_int|4
op_star
l_int|8
(paren
op_mod
id|rsp
)paren
comma
op_mod
id|rbp
id|movq
l_int|5
op_star
l_int|8
(paren
op_mod
id|rsp
)paren
comma
op_mod
id|rbx
DECL|variable|$REST_SKIP
id|addq
"$"
id|REST_SKIP
comma
op_mod
id|rsp
dot
id|endm
dot
id|macro
id|SAVE_ALL
id|SAVE_ARGS
id|SAVE_REST
dot
id|endm
dot
id|macro
id|RESTORE_ALL
id|addskip
op_assign
l_int|0
id|RESTORE_REST
id|RESTORE_ARGS
l_int|0
comma
"&bslash;"
id|addskip
dot
id|endm
multiline_comment|/* push in order ss, rsp, eflags, cs, rip */
dot
id|macro
id|FAKE_STACK_FRAME
id|child_rip
id|xorl
op_mod
id|eax
comma
op_mod
id|eax
id|subq
"$"
l_int|6
op_star
l_int|8
comma
op_mod
id|rsp
DECL|variable|rax
id|movq
op_mod
id|rax
comma
l_int|5
op_star
l_int|8
(paren
op_mod
id|rsp
)paren
multiline_comment|/* ss */
DECL|variable|rax
id|movq
op_mod
id|rax
comma
l_int|4
op_star
l_int|8
(paren
op_mod
id|rsp
)paren
multiline_comment|/* rsp */
id|movq
"$"
(paren
l_int|1
op_lshift
l_int|9
)paren
comma
l_int|3
op_star
l_int|8
(paren
op_mod
id|rsp
)paren
multiline_comment|/* eflags */
DECL|variable|$__KERNEL_CS
id|movq
"$"
id|__KERNEL_CS
comma
l_int|2
op_star
l_int|8
(paren
op_mod
id|rsp
)paren
multiline_comment|/* cs */
DECL|variable|child_rip
id|movq
"&bslash;"
id|child_rip
comma
l_int|1
op_star
l_int|8
(paren
op_mod
id|rsp
)paren
multiline_comment|/* rip */
DECL|variable|rax
id|movq
op_mod
id|rax
comma
(paren
op_mod
id|rsp
)paren
multiline_comment|/* orig_rax */
dot
id|endm
dot
id|macro
id|UNFAKE_STACK_FRAME
id|addq
"$"
l_int|8
op_star
l_int|6
comma
op_mod
id|rsp
dot
id|endm
dot
id|macro
id|icebp
dot
id|byte
l_int|0xf1
dot
id|endm
macro_line|#ifdef CONFIG_FRAME_POINTER
DECL|macro|ENTER
mdefine_line|#define ENTER enter
DECL|macro|LEAVE
mdefine_line|#define LEAVE leave
macro_line|#else
mdefine_line|#define ENTER
mdefine_line|#define LEAVE
macro_line|#endif
eof
