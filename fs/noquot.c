multiline_comment|/* noquot.c: Quota stubs necessary for when quotas are not&n; *           compiled into the kernel.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
DECL|variable|nr_dquots
DECL|variable|nr_free_dquots
r_int
id|nr_dquots
comma
id|nr_free_dquots
suffix:semicolon
DECL|variable|max_dquots
r_int
id|max_dquots
suffix:semicolon
DECL|function|sys_quotactl
id|asmlinkage
r_int
id|sys_quotactl
c_func
(paren
r_int
id|cmd
comma
r_const
r_char
op_star
id|special
comma
r_int
id|id
comma
id|caddr_t
id|addr
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
eof
