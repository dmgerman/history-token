macro_line|#ifndef __M68K_ENTRY_H
DECL|macro|__M68K_ENTRY_H
mdefine_line|#define __M68K_ENTRY_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/*&n; * Stack layout in &squot;ret_from_exception&squot;:&n; *&n; *&t;This allows access to the syscall arguments in registers d1-d5&n; *&n; *&t; 0(sp) - d1&n; *&t; 4(sp) - d2&n; *&t; 8(sp) - d3&n; *&t; C(sp) - d4&n; *&t;10(sp) - d5&n; *&t;14(sp) - a0&n; *&t;18(sp) - a1&n; *&t;1C(sp) - a2&n; *&t;20(sp) - d0&n; *&t;24(sp) - orig_d0&n; *&t;28(sp) - stack adjustment&n; *&t;2C(sp) - sr&n; *&t;2E(sp) - pc&n; *&t;32(sp) - format &amp; vector&n; */
multiline_comment|/*&n; * 97/05/14 Andreas: Register %a2 is now set to the current task throughout&n; *&t;&t;     the whole kernel.&n; */
multiline_comment|/* the following macro is used when enabling interrupts */
macro_line|#if defined(MACH_ATARI_ONLY) &amp;&amp; !defined(CONFIG_HADES)
multiline_comment|/* block out HSYNC on the atari */
DECL|macro|ALLOWINT
mdefine_line|#define ALLOWINT 0xfbff
DECL|macro|MAX_NOINT_IPL
mdefine_line|#define&t;MAX_NOINT_IPL&t;3
macro_line|#else
multiline_comment|/* portable version */
DECL|macro|ALLOWINT
mdefine_line|#define ALLOWINT 0xf8ff
DECL|macro|MAX_NOINT_IPL
mdefine_line|#define&t;MAX_NOINT_IPL&t;0
macro_line|#endif /* machine compilation types */ 
macro_line|#ifdef __ASSEMBLY__
DECL|macro|curptr
mdefine_line|#define curptr a2
id|LFLUSH_I_AND_D
op_assign
l_int|0x00000808
id|LSIGTRAP
op_assign
l_int|5
multiline_comment|/* process bits for task_struct.ptrace */
id|PT_TRACESYS_OFF
op_assign
l_int|3
id|PT_TRACESYS_BIT
op_assign
l_int|1
id|PT_PTRACED_OFF
op_assign
l_int|3
id|PT_PTRACED_BIT
op_assign
l_int|0
id|PT_DTRACE_OFF
op_assign
l_int|3
id|PT_DTRACE_BIT
op_assign
l_int|2
DECL|macro|SAVE_ALL_INT
mdefine_line|#define SAVE_ALL_INT save_all_int
DECL|macro|SAVE_ALL_SYS
mdefine_line|#define SAVE_ALL_SYS save_all_sys
DECL|macro|RESTORE_ALL
mdefine_line|#define RESTORE_ALL restore_all
multiline_comment|/*&n; * This defines the normal kernel pt-regs layout.&n; *&n; * regs a3-a6 and d6-d7 are preserved by C code&n; * the kernel doesn&squot;t mess with usp unless it needs to&n; */
multiline_comment|/*&n; * a -1 in the orig_d0 field signifies&n; * that the stack frame is NOT for syscall&n; */
dot
id|macro
id|save_all_int
id|clrl
op_mod
id|sp
"@"
op_minus
op_or
id|stk_adj
id|pea
op_minus
l_int|1
suffix:colon
id|w
op_or
id|orig
id|d0
id|movel
op_mod
id|d0
comma
op_mod
id|sp
"@"
op_minus
op_or
id|d0
id|moveml
op_mod
id|d1
op_minus
op_mod
id|d5
op_div
op_mod
id|a0
op_minus
op_mod
id|a1
op_div
op_mod
id|curptr
comma
op_mod
id|sp
"@"
op_minus
dot
id|endm
dot
id|macro
id|save_all_sys
id|clrl
op_mod
id|sp
"@"
op_minus
op_or
id|stk_adj
id|movel
op_mod
id|d0
comma
op_mod
id|sp
"@"
op_minus
op_or
id|orig
id|d0
id|movel
op_mod
id|d0
comma
op_mod
id|sp
"@"
op_minus
op_or
id|d0
id|moveml
op_mod
id|d1
op_minus
op_mod
id|d5
op_div
op_mod
id|a0
op_minus
op_mod
id|a1
op_div
op_mod
id|curptr
comma
op_mod
id|sp
"@"
op_minus
dot
id|endm
dot
id|macro
id|restore_all
id|moveml
op_mod
id|sp
"@"
op_plus
comma
op_mod
id|a0
op_minus
op_mod
id|a1
op_div
op_mod
id|curptr
op_div
op_mod
id|d1
op_minus
op_mod
id|d5
id|movel
op_mod
id|sp
"@"
op_plus
comma
op_mod
id|d0
DECL|variable|addql
id|addql
macro_line|#4,%sp&t;&t;| orig d0
DECL|variable|sp
id|addl
op_mod
id|sp
"@"
op_plus
comma
op_mod
id|sp
op_or
id|stk
id|adj
id|rte
dot
id|endm
DECL|macro|SWITCH_STACK_SIZE
mdefine_line|#define SWITCH_STACK_SIZE (6*4+4)&t;/* includes return address */
DECL|macro|SAVE_SWITCH_STACK
mdefine_line|#define SAVE_SWITCH_STACK save_switch_stack
DECL|macro|RESTORE_SWITCH_STACK
mdefine_line|#define RESTORE_SWITCH_STACK restore_switch_stack
DECL|macro|GET_CURRENT
mdefine_line|#define GET_CURRENT(tmp) get_current tmp
dot
id|macro
id|save_switch_stack
id|moveml
op_mod
id|a3
op_minus
op_mod
id|a6
op_div
op_mod
id|d6
op_minus
op_mod
id|d7
comma
op_mod
id|sp
"@"
op_minus
dot
id|endm
dot
id|macro
id|restore_switch_stack
id|moveml
op_mod
id|sp
"@"
op_plus
comma
op_mod
id|a3
op_minus
op_mod
id|a6
op_div
op_mod
id|d6
op_minus
op_mod
id|d7
dot
id|endm
dot
id|macro
id|get_current
id|reg
op_assign
op_mod
id|d0
id|movel
op_mod
id|sp
comma
"&bslash;"
id|reg
id|andw
macro_line|#-KTHREAD_SIZE,&bslash;reg
DECL|variable|reg
id|movel
"&bslash;"
id|reg
comma
op_mod
id|curptr
dot
id|endm
macro_line|#else /* C source */
mdefine_line|#define STR(X) STR1(X)
mdefine_line|#define STR1(X) #X
mdefine_line|#define PT_OFF_ORIG_D0&t; 0x24
mdefine_line|#define PT_OFF_FORMATVEC 0x32
mdefine_line|#define PT_OFF_SR&t; 0x2C
mdefine_line|#define SAVE_ALL_INT&t;&t;&t;&t;&bslash;&n;&t;&quot;clrl&t;%%sp@-;&quot;    /* stk_adj */&t;&bslash;&n;&t;&quot;pea&t;-1:w;&quot;&t;    /* orig d0 = -1 */&t;&bslash;&n;&t;&quot;movel&t;%%d0,%%sp@-;&quot; /* d0 */&t;&t;&bslash;&n;&t;&quot;moveml&t;%%d1-%%d5/%%a0-%%a2,%%sp@-&quot;
mdefine_line|#define GET_CURRENT(tmp) &bslash;&n;&t;&quot;movel&t;%%sp,&quot;#tmp&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;andw&t;#-&quot;STR(KTHREAD_SIZE)&quot;,&quot;#tmp&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movel&t;&quot;#tmp&quot;,%%a2&quot;
macro_line|#endif
macro_line|#endif /* __M68K_ENTRY_H */
eof
