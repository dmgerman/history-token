macro_line|#ifndef __ASM_SH_BUGS_H
DECL|macro|__ASM_SH_BUGS_H
mdefine_line|#define __ASM_SH_BUGS_H
multiline_comment|/*&n; * This is included by init/main.c to check for architecture-dependent bugs.&n; *&n; * Needs:&n; *&t;void check_bugs(void);&n; */
multiline_comment|/*&n; * I don&squot;t know of any Super-H bugs yet.&n; */
macro_line|#include &lt;asm/processor.h&gt;
DECL|function|check_bugs
r_static
r_void
id|__init
id|check_bugs
c_func
(paren
r_void
)paren
(brace
r_extern
r_int
r_int
id|loops_per_jiffy
suffix:semicolon
r_char
op_star
id|p
op_assign
op_amp
id|system_utsname.machine
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* &quot;sh&quot; */
id|cpu_data-&gt;loops_per_jiffy
op_assign
id|loops_per_jiffy
suffix:semicolon
r_switch
c_cond
(paren
id|cpu_data-&gt;type
)paren
(brace
r_case
id|CPU_SH7708
suffix:colon
op_star
id|p
op_increment
op_assign
l_char|&squot;3&squot;
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU: SH7707/SH7708/SH7709&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPU_SH7729
suffix:colon
op_star
id|p
op_increment
op_assign
l_char|&squot;3&squot;
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU: SH7709A/SH7729&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPU_SH7750
suffix:colon
op_star
id|p
op_increment
op_assign
l_char|&squot;4&squot;
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU: SH7750&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;CPU: ??????&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#ifndef __LITTLE_ENDIAN__
multiline_comment|/* &squot;eb&squot; means &squot;Endian Big&squot; */
op_star
id|p
op_increment
op_assign
l_char|&squot;e&squot;
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_char|&squot;b&squot;
suffix:semicolon
macro_line|#endif
op_star
id|p
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
macro_line|#endif /* __ASM_SH_BUGS_H */
eof
