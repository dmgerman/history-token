multiline_comment|/*&n; *  linux/arch/mips/jazz/process.c&n; *&n; *  Reset a Jazz machine.&n; *&n; *  $Id:$&n; */
macro_line|#include &lt;linux/jiffies.h&gt;
macro_line|#include &lt;asm/jazz.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/keyboard.h&gt;
DECL|function|kb_wait
r_static
r_inline
r_void
id|kb_wait
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|start
op_assign
id|jiffies
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|kbd_read_status
c_func
(paren
)paren
op_amp
l_int|0x02
)paren
)paren
r_return
suffix:semicolon
)brace
r_while
c_loop
(paren
id|jiffies
op_minus
id|start
OL
l_int|50
)paren
suffix:semicolon
)brace
DECL|function|jazz_machine_restart
r_void
id|jazz_machine_restart
c_func
(paren
r_char
op_star
id|command
)paren
(brace
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|kb_wait
(paren
)paren
suffix:semicolon
id|kbd_write_command
(paren
l_int|0xd1
)paren
suffix:semicolon
id|kb_wait
(paren
)paren
suffix:semicolon
id|kbd_write_output
(paren
l_int|0x00
)paren
suffix:semicolon
)brace
)brace
DECL|function|jazz_machine_halt
r_void
id|jazz_machine_halt
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|jazz_machine_power_off
r_void
id|jazz_machine_power_off
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Jazz machines don&squot;t have a software power switch */
)brace
eof
