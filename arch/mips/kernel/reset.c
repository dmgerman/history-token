multiline_comment|/*&n; *  linux/arch/mips/sni/process.c&n; *&n; *  Reset the machine.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
multiline_comment|/*&n; * Urgs ...  Too many MIPS machines to handle this in a generic way.&n; * So handle all using function pointers to machine specific&n; * functions.&n; */
DECL|function|machine_restart
r_void
id|machine_restart
c_func
(paren
r_char
op_star
id|command
)paren
(brace
id|_machine_restart
c_func
(paren
id|command
)paren
suffix:semicolon
)brace
DECL|function|machine_halt
r_void
id|machine_halt
c_func
(paren
r_void
)paren
(brace
id|_machine_halt
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|machine_power_off
r_void
id|machine_power_off
c_func
(paren
r_void
)paren
(brace
id|_machine_power_off
c_func
(paren
)paren
suffix:semicolon
)brace
eof
