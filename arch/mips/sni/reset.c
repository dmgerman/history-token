multiline_comment|/*&n; *  linux/arch/mips/sni/process.c&n; *&n; *  Reset a SNI machine.&n; */
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/sni.h&gt;
multiline_comment|/*&n; * This routine reboots the machine by asking the keyboard&n; * controller to pulse the reset-line low. We try that for a while,&n; * and if it doesn&squot;t work, we do some other stupid things.&n; */
r_static
r_inline
r_void
DECL|function|kb_wait
id|kb_wait
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|0x10000
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
(paren
id|inb_p
c_func
(paren
l_int|0x64
)paren
op_amp
l_int|0x02
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
multiline_comment|/* XXX This ends up at the ARC firmware prompt ...  */
DECL|function|sni_machine_restart
r_void
id|sni_machine_restart
c_func
(paren
r_char
op_star
id|command
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
multiline_comment|/* This does a normal via the keyboard controller like a PC.&n;&t;   We can do that easier ...  */
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|100
suffix:semicolon
id|i
op_increment
)paren
(brace
id|kb_wait
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|100000
suffix:semicolon
id|j
op_increment
)paren
(brace
multiline_comment|/* nothing */
suffix:semicolon
)brace
id|outb_p
c_func
(paren
l_int|0xfe
comma
l_int|0x64
)paren
suffix:semicolon
multiline_comment|/* pulse reset low */
)brace
)brace
)brace
DECL|function|sni_machine_halt
r_void
id|sni_machine_halt
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|sni_machine_power_off
r_void
id|sni_machine_power_off
c_func
(paren
r_void
)paren
(brace
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|PCIMT_CSWCSM
op_assign
l_int|0xfd
suffix:semicolon
)brace
eof
