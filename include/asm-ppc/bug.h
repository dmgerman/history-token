macro_line|#ifndef _PPC_BUG_H
DECL|macro|_PPC_BUG_H
mdefine_line|#define _PPC_BUG_H
DECL|struct|bug_entry
r_struct
id|bug_entry
(brace
DECL|member|bug_addr
r_int
r_int
id|bug_addr
suffix:semicolon
DECL|member|line
r_int
id|line
suffix:semicolon
DECL|member|file
r_const
r_char
op_star
id|file
suffix:semicolon
DECL|member|function
r_const
r_char
op_star
id|function
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * If this bit is set in the line number it means that the trap&n; * is for WARN_ON rather than BUG or BUG_ON.&n; */
DECL|macro|BUG_WARNING_TRAP
mdefine_line|#define BUG_WARNING_TRAP&t;0x1000000
DECL|macro|BUG
mdefine_line|#define BUG() do {&t;&t;&t;&t;&t;&t;&t; &bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t; &bslash;&n;&t;&t;&quot;1:&t;twi 31,0,0&bslash;n&quot;&t;&t;&t;&t;&t; &bslash;&n;&t;&t;&quot;.section __bug_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot;&t;&t;&t; &bslash;&n;&t;&t;&quot;&t;.long 1b,%0,%1,%2&bslash;n&quot;&t;&t;&t;&t; &bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&t; &bslash;&n;&t;&t;: : &quot;i&quot; (__LINE__), &quot;i&quot; (__FILE__), &quot;i&quot; (__FUNCTION__)); &bslash;&n;} while (0)
DECL|macro|BUG_ON
mdefine_line|#define BUG_ON(x) do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&t;twnei %0,0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __bug_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 1b,%1,%2,%3&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: : &quot;r&quot; (x), &quot;i&quot; (__LINE__), &quot;i&quot; (__FILE__),&t;&bslash;&n;&t;&t;    &quot;i&quot; (__FUNCTION__));&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page) do { BUG(); } while (0)
DECL|macro|WARN_ON
mdefine_line|#define WARN_ON(x) do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&t;twnei %0,0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __bug_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long 1b,%1,%2,%3&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: : &quot;r&quot; (x), &quot;i&quot; (__LINE__ + BUG_WARNING_TRAP),&t;&bslash;&n;&t;&t;    &quot;i&quot; (__FILE__), &quot;i&quot; (__FUNCTION__));&t;&bslash;&n;} while (0)
macro_line|#endif
eof
