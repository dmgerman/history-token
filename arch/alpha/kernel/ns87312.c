multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/ns87312.c&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;proto.h&quot;
multiline_comment|/*&n; * The SRM console *disables* the IDE interface, this code ensures it&squot;s&n; * enabled.&n; *&n; * This code bangs on a control register of the 87312 Super I/O chip&n; * that implements parallel port/serial ports/IDE/FDI.  Depending on&n; * the motherboard, the Super I/O chip can be configured through a&n; * pair of registers that are located either at I/O ports 0x26e/0x26f&n; * or 0x398/0x399.  Unfortunately, autodetecting which base address is&n; * in use works only once (right after a reset).  The Super I/O chip&n; * has the additional quirk that configuration register data must be&n; * written twice (I believe this is a safety feature to prevent&n; * accidental modification---fun, isn&squot;t it?).&n; */
r_void
id|__init
DECL|function|ns87312_enable_ide
id|ns87312_enable_ide
c_func
(paren
r_int
id|ide_base
)paren
(brace
r_int
id|data
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|__save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|ide_base
)paren
suffix:semicolon
multiline_comment|/* set the index register for reg #0 */
id|data
op_assign
id|inb
c_func
(paren
id|ide_base
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* read the current contents */
id|outb
c_func
(paren
l_int|0
comma
id|ide_base
)paren
suffix:semicolon
multiline_comment|/* set the index register for reg #0 */
id|outb
c_func
(paren
id|data
op_or
l_int|0x40
comma
id|ide_base
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* turn on IDE */
id|outb
c_func
(paren
id|data
op_or
l_int|0x40
comma
id|ide_base
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* turn on IDE, really! */
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
eof
