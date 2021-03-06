macro_line|#include &quot;linux/sched.h&quot;
macro_line|#include &quot;asm/ptrace.h&quot;
DECL|function|putreg
r_int
id|putreg
c_func
(paren
r_struct
id|task_struct
op_star
id|child
comma
r_int
r_int
id|regno
comma
r_int
r_int
id|value
)paren
(brace
id|child-&gt;thread.process_regs.regs
(braket
id|regno
op_rshift
l_int|2
)braket
op_assign
id|value
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|getreg
r_int
r_int
id|getreg
c_func
(paren
r_struct
id|task_struct
op_star
id|child
comma
r_int
r_int
id|regno
)paren
(brace
r_int
r_int
id|retval
op_assign
op_complement
l_int|0UL
suffix:semicolon
id|retval
op_and_assign
id|child-&gt;thread.process_regs.regs
(braket
id|regno
op_rshift
l_int|2
)braket
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
