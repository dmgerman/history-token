macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|function|main
r_int
id|main
c_func
(paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;#ifndef __ASM_OFFSETS_H__&bslash;n#define __ASM_OFFSETS_H__&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;#define TASK_STATE %ld&bslash;n&quot;
comma
(paren
r_int
)paren
m_offsetof
(paren
r_struct
id|task_struct
comma
id|state
)paren
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;#define TASK_FLAGS %ld&bslash;n&quot;
comma
(paren
r_int
)paren
m_offsetof
(paren
r_struct
id|task_struct
comma
id|flags
)paren
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;#define TASK_SIGPENDING %ld&bslash;n&quot;
comma
macro_line|#error&t;       (long)offsetof(struct task_struct, sigpending));
id|printf
c_func
(paren
l_string|&quot;#define TASK_ADDR_LIMIT %ld&bslash;n&quot;
comma
(paren
r_int
)paren
m_offsetof
(paren
r_struct
id|task_struct
comma
id|addr_limit
)paren
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;#define TASK_EXEC_DOMAIN %ld&bslash;n&quot;
comma
(paren
r_int
)paren
m_offsetof
(paren
r_struct
id|task_struct
comma
id|exec_domain
)paren
)paren
suffix:semicolon
id|printf
(paren
l_string|&quot;#define TASK_NEED_RESCHED %ld&bslash;n&quot;
comma
macro_line|#error&t;       (long)offsetof(struct task_struct, work.need_resched));
id|printf
c_func
(paren
l_string|&quot;#define TASK_SIZE %ld&bslash;n&quot;
comma
r_sizeof
(paren
r_struct
id|task_struct
)paren
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;#define STACK_SIZE %ld&bslash;n&quot;
comma
r_sizeof
(paren
r_union
id|task_union
)paren
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;#define HAE_CACHE %ld&bslash;n&quot;
comma
(paren
r_int
)paren
m_offsetof
(paren
r_struct
id|alpha_machine_vector
comma
id|hae_cache
)paren
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;#define HAE_REG %ld&bslash;n&quot;
comma
(paren
r_int
)paren
m_offsetof
(paren
r_struct
id|alpha_machine_vector
comma
id|hae_register
)paren
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;#endif /* __ASM_OFFSETS_H__ */&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
