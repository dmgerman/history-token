macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|typedef|instr
r_typedef
r_int
r_int
id|instr
suffix:semicolon
DECL|macro|MAJOR_OP
mdefine_line|#define MAJOR_OP&t;0xfc000000
DECL|macro|LDA_OP
mdefine_line|#define LDA_OP&t;&t;0x20000000
DECL|macro|STQ_OP
mdefine_line|#define STQ_OP&t;&t;0xb4000000
DECL|macro|BR_OP
mdefine_line|#define BR_OP&t;&t;0xc0000000
DECL|macro|STK_ALLOC_1
mdefine_line|#define STK_ALLOC_1&t;0x23de8000 /* lda $30,-X($30) */
DECL|macro|STK_ALLOC_1M
mdefine_line|#define STK_ALLOC_1M&t;0xffff8000
DECL|macro|STK_ALLOC_2
mdefine_line|#define STK_ALLOC_2&t;0x43c0153e /* subq $30,X,$30 */
DECL|macro|STK_ALLOC_2M
mdefine_line|#define STK_ALLOC_2M&t;0xffe01fff
DECL|macro|MEM_REG
mdefine_line|#define MEM_REG&t;&t;0x03e00000
DECL|macro|MEM_BASE
mdefine_line|#define MEM_BASE&t;0x001f0000
DECL|macro|MEM_OFF
mdefine_line|#define MEM_OFF&t;&t;0x0000ffff
DECL|macro|MEM_OFF_SIGN
mdefine_line|#define MEM_OFF_SIGN&t;0x00008000
DECL|macro|BASE_SP
mdefine_line|#define&t;BASE_SP&t;&t;0x001e0000
DECL|macro|STK_ALLOC_MATCH
mdefine_line|#define STK_ALLOC_MATCH(INSTR)&t;&t;&t;&bslash;&n;  (((INSTR) &amp; STK_ALLOC_1M) == STK_ALLOC_1&t;&bslash;&n;   || ((INSTR) &amp; STK_ALLOC_2M) == STK_ALLOC_2)
DECL|macro|STK_PUSH_MATCH
mdefine_line|#define STK_PUSH_MATCH(INSTR) &bslash;&n;  (((INSTR) &amp; (MAJOR_OP | MEM_BASE | MEM_OFF_SIGN)) == (STQ_OP | BASE_SP))
DECL|macro|MEM_OP_OFFSET
mdefine_line|#define MEM_OP_OFFSET(INSTR) &bslash;&n;  (((long)((INSTR) &amp; MEM_OFF) &lt;&lt; 48) &gt;&gt; 48)
DECL|macro|MEM_OP_REG
mdefine_line|#define MEM_OP_REG(INSTR) &bslash;&n;  (((INSTR) &amp; MEM_REG) &gt;&gt; 22)
multiline_comment|/* Branches, jumps, PAL calls, and illegal opcodes end a basic block. */
DECL|macro|BB_END
mdefine_line|#define BB_END(INSTR)&t;&t;&t;&t;&t;&t;&bslash;&n;  (((instr)(INSTR) &gt;= BR_OP) | ((instr)(INSTR) &lt; LDA_OP) |&t;&bslash;&n;   ((((instr)(INSTR) ^ 0x60000000) &lt; 0x20000000) &amp;&t;&t;&bslash;&n;    (((instr)(INSTR) &amp; 0x0c000000) != 0)))
DECL|macro|IS_KERNEL_TEXT
mdefine_line|#define IS_KERNEL_TEXT(PC) ((unsigned long)(PC) &gt; START_ADDR)
DECL|variable|reg_name
r_static
r_char
id|reg_name
(braket
)braket
(braket
l_int|4
)braket
op_assign
(brace
l_string|&quot;v0 &quot;
comma
l_string|&quot;t0 &quot;
comma
l_string|&quot;t1 &quot;
comma
l_string|&quot;t2 &quot;
comma
l_string|&quot;t3 &quot;
comma
l_string|&quot;t4 &quot;
comma
l_string|&quot;t5 &quot;
comma
l_string|&quot;t6 &quot;
comma
l_string|&quot;t7 &quot;
comma
l_string|&quot;s0 &quot;
comma
l_string|&quot;s1 &quot;
comma
l_string|&quot;s2 &quot;
comma
l_string|&quot;s3 &quot;
comma
l_string|&quot;s4 &quot;
comma
l_string|&quot;s5 &quot;
comma
l_string|&quot;s6 &quot;
comma
l_string|&quot;a0 &quot;
comma
l_string|&quot;a1 &quot;
comma
l_string|&quot;a2 &quot;
comma
l_string|&quot;a3 &quot;
comma
l_string|&quot;a4 &quot;
comma
l_string|&quot;a5 &quot;
comma
l_string|&quot;t8 &quot;
comma
l_string|&quot;t9 &quot;
comma
l_string|&quot;t10&quot;
comma
l_string|&quot;t11&quot;
comma
l_string|&quot;ra &quot;
comma
l_string|&quot;pv &quot;
comma
l_string|&quot;at &quot;
comma
l_string|&quot;gp &quot;
comma
l_string|&quot;sp &quot;
comma
l_string|&quot;0&quot;
)brace
suffix:semicolon
r_static
id|instr
op_star
DECL|function|display_stored_regs
id|display_stored_regs
c_func
(paren
id|instr
op_star
id|pro_pc
comma
r_int
r_char
op_star
id|sp
)paren
(brace
id|instr
op_star
id|ret_pc
op_assign
l_int|0
suffix:semicolon
r_int
id|reg
suffix:semicolon
r_int
r_int
id|value
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Prologue [&lt;%p&gt;], Frame %p:&bslash;n&quot;
comma
id|pro_pc
comma
id|sp
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|BB_END
c_func
(paren
op_star
id|pro_pc
)paren
)paren
r_if
c_cond
(paren
id|STK_PUSH_MATCH
c_func
(paren
op_star
id|pro_pc
)paren
)paren
(brace
id|reg
op_assign
(paren
op_star
id|pro_pc
op_amp
id|MEM_REG
)paren
op_rshift
l_int|21
suffix:semicolon
id|value
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|sp
op_plus
(paren
op_star
id|pro_pc
op_amp
id|MEM_OFF
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_eq
l_int|26
)paren
id|ret_pc
op_assign
(paren
id|instr
op_star
)paren
id|value
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;t&bslash;t%s / 0x%016lx&bslash;n&quot;
comma
id|reg_name
(braket
id|reg
)braket
comma
id|value
)paren
suffix:semicolon
)brace
r_return
id|ret_pc
suffix:semicolon
)brace
r_static
id|instr
op_star
DECL|function|seek_prologue
id|seek_prologue
c_func
(paren
id|instr
op_star
id|pc
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
id|STK_ALLOC_MATCH
c_func
(paren
op_star
id|pc
)paren
)paren
op_decrement
id|pc
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|BB_END
c_func
(paren
op_star
(paren
id|pc
op_minus
l_int|1
)paren
)paren
)paren
op_decrement
id|pc
suffix:semicolon
r_return
id|pc
suffix:semicolon
)brace
r_static
r_int
DECL|function|stack_increment
id|stack_increment
c_func
(paren
id|instr
op_star
id|prologue_pc
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
id|STK_ALLOC_MATCH
c_func
(paren
op_star
id|prologue_pc
)paren
)paren
op_increment
id|prologue_pc
suffix:semicolon
multiline_comment|/* Count the bytes allocated. */
r_if
c_cond
(paren
(paren
op_star
id|prologue_pc
op_amp
id|STK_ALLOC_1M
)paren
op_eq
id|STK_ALLOC_1M
)paren
r_return
op_minus
(paren
(paren
(paren
r_int
)paren
(paren
op_star
id|prologue_pc
)paren
op_lshift
l_int|48
)paren
op_rshift
l_int|48
)paren
suffix:semicolon
r_else
r_return
(paren
op_star
id|prologue_pc
op_rshift
l_int|13
)paren
op_amp
l_int|0xff
suffix:semicolon
)brace
r_void
DECL|function|stacktrace
id|stacktrace
c_func
(paren
r_void
)paren
(brace
id|instr
op_star
id|ret_pc
suffix:semicolon
id|instr
op_star
id|prologue
op_assign
(paren
id|instr
op_star
)paren
id|stacktrace
suffix:semicolon
r_register
r_int
r_char
op_star
id|sp
id|__asm__
(paren
l_string|&quot;$30&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;tstack trace:&bslash;n&quot;
)paren
suffix:semicolon
r_do
(brace
id|ret_pc
op_assign
id|display_stored_regs
c_func
(paren
id|prologue
comma
id|sp
)paren
suffix:semicolon
id|sp
op_add_assign
id|stack_increment
c_func
(paren
id|prologue
)paren
suffix:semicolon
id|prologue
op_assign
id|seek_prologue
c_func
(paren
id|ret_pc
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|IS_KERNEL_TEXT
c_func
(paren
id|ret_pc
)paren
)paren
suffix:semicolon
)brace
eof
