multiline_comment|/* Prom access routines for the sun3x */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/sun3xprom.h&gt;
macro_line|#include &lt;asm/idprom.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/sun3ints.h&gt;
macro_line|#include &lt;asm/openprom.h&gt;
macro_line|#include &lt;asm/machines.h&gt;
DECL|variable|sun3x_putchar
r_void
(paren
op_star
id|sun3x_putchar
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|variable|sun3x_getchar
r_int
(paren
op_star
id|sun3x_getchar
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|sun3x_mayget
r_int
(paren
op_star
id|sun3x_mayget
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|sun3x_mayput
r_int
(paren
op_star
id|sun3x_mayput
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|variable|sun3x_prom_reboot
r_void
(paren
op_star
id|sun3x_prom_reboot
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|sun3x_prom_abort
id|e_vector
id|sun3x_prom_abort
suffix:semicolon
DECL|variable|romvec
r_struct
id|linux_romvec
op_star
id|romvec
suffix:semicolon
multiline_comment|/* prom vector table */
DECL|variable|sun3x_prom_vbr
id|e_vector
op_star
id|sun3x_prom_vbr
suffix:semicolon
r_extern
id|e_vector
id|vectors
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* arch/m68k/kernel/traps.c */
multiline_comment|/* Handle returning to the prom */
DECL|function|sun3x_halt
r_void
id|sun3x_halt
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Disable interrupts while we mess with things */
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* Restore prom vbr */
id|__asm__
r_volatile
(paren
l_string|&quot;movec %0,%%vbr&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
(paren
r_void
op_star
)paren
id|sun3x_prom_vbr
)paren
)paren
suffix:semicolon
multiline_comment|/* Restore prom NMI clock */
singleline_comment|//    sun3x_disable_intreg(5);
id|sun3_enable_irq
c_func
(paren
l_int|7
)paren
suffix:semicolon
multiline_comment|/* Let &squot;er rip */
id|__asm__
r_volatile
(paren
l_string|&quot;trap #14&quot;
suffix:colon
suffix:colon
)paren
suffix:semicolon
multiline_comment|/* Restore everything */
id|sun3_disable_irq
c_func
(paren
l_int|7
)paren
suffix:semicolon
id|sun3_enable_irq
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|__asm__
r_volatile
(paren
l_string|&quot;movec %0,%%vbr&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
(paren
r_void
op_star
)paren
id|vectors
)paren
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|sun3x_reboot
r_void
id|sun3x_reboot
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* This never returns, don&squot;t bother saving things */
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Restore prom vbr */
id|__asm__
r_volatile
(paren
l_string|&quot;movec %0,%%vbr&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
(paren
r_void
op_star
)paren
id|sun3x_prom_vbr
)paren
)paren
suffix:semicolon
multiline_comment|/* Restore prom NMI clock */
id|sun3_disable_irq
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|sun3_enable_irq
c_func
(paren
l_int|7
)paren
suffix:semicolon
multiline_comment|/* Let &squot;er rip */
(paren
op_star
id|romvec-&gt;pv_reboot
)paren
(paren
l_string|&quot;vmlinux&quot;
)paren
suffix:semicolon
)brace
r_extern
r_char
id|m68k_debug_device
(braket
)braket
suffix:semicolon
DECL|function|sun3x_prom_write
r_static
r_void
id|sun3x_prom_write
c_func
(paren
r_struct
id|console
op_star
id|co
comma
r_const
r_char
op_star
id|s
comma
r_int
r_int
id|count
)paren
(brace
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
r_if
c_cond
(paren
op_star
id|s
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|sun3x_putchar
c_func
(paren
l_char|&squot;&bslash;r&squot;
)paren
suffix:semicolon
id|sun3x_putchar
c_func
(paren
op_star
id|s
op_increment
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* debug console - write-only */
DECL|variable|sun3x_debug
r_static
r_struct
id|console
id|sun3x_debug
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;debug&quot;
comma
dot
id|write
op_assign
id|sun3x_prom_write
comma
dot
id|flags
op_assign
id|CON_PRINTBUFFER
comma
dot
id|index
op_assign
op_minus
l_int|1
comma
)brace
suffix:semicolon
DECL|function|sun3x_prom_init
r_void
id|sun3x_prom_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Read the vector table */
id|sun3x_putchar
op_assign
op_star
(paren
r_void
(paren
op_star
op_star
)paren
(paren
r_int
)paren
)paren
(paren
id|SUN3X_P_PUTCHAR
)paren
suffix:semicolon
id|sun3x_getchar
op_assign
op_star
(paren
r_int
(paren
op_star
op_star
)paren
(paren
r_void
)paren
)paren
(paren
id|SUN3X_P_GETCHAR
)paren
suffix:semicolon
id|sun3x_mayget
op_assign
op_star
(paren
r_int
(paren
op_star
op_star
)paren
(paren
r_void
)paren
)paren
(paren
id|SUN3X_P_MAYGET
)paren
suffix:semicolon
id|sun3x_mayput
op_assign
op_star
(paren
r_int
(paren
op_star
op_star
)paren
(paren
r_int
)paren
)paren
(paren
id|SUN3X_P_MAYPUT
)paren
suffix:semicolon
id|sun3x_prom_reboot
op_assign
op_star
(paren
r_void
(paren
op_star
op_star
)paren
(paren
r_void
)paren
)paren
(paren
id|SUN3X_P_REBOOT
)paren
suffix:semicolon
id|sun3x_prom_abort
op_assign
op_star
(paren
id|e_vector
op_star
)paren
(paren
id|SUN3X_P_ABORT
)paren
suffix:semicolon
id|romvec
op_assign
(paren
r_struct
id|linux_romvec
op_star
)paren
id|SUN3X_PROM_BASE
suffix:semicolon
id|idprom_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|idprom-&gt;id_machtype
op_amp
id|SM_ARCH_MASK
)paren
op_eq
id|SM_SUN3X
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Warning: machine reports strange type %02x&bslash;n&quot;
comma
id|idprom-&gt;id_machtype
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Pretending it&squot;s a 3/80, but very afraid...&bslash;n&quot;
)paren
suffix:semicolon
id|idprom-&gt;id_machtype
op_assign
id|SM_SUN3X
op_or
id|SM_3_80
suffix:semicolon
)brace
multiline_comment|/* point trap #14 at abort.&n;     * XXX this is futile since we restore the vbr first - oops&n;     */
id|vectors
(braket
id|VEC_TRAP14
)braket
op_assign
id|sun3x_prom_abort
suffix:semicolon
multiline_comment|/* If debug=prom was specified, start the debug console */
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|m68k_debug_device
comma
l_string|&quot;prom&quot;
)paren
)paren
id|register_console
c_func
(paren
op_amp
id|sun3x_debug
)paren
suffix:semicolon
)brace
multiline_comment|/* some prom functions to export */
DECL|function|prom_getintdefault
r_int
id|prom_getintdefault
c_func
(paren
r_int
id|node
comma
r_char
op_star
id|property
comma
r_int
id|deflt
)paren
(brace
r_return
id|deflt
suffix:semicolon
)brace
DECL|function|prom_getbool
r_int
id|prom_getbool
(paren
r_int
id|node
comma
r_char
op_star
id|prop
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|prom_printf
r_void
id|prom_printf
c_func
(paren
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
)brace
DECL|function|prom_halt
r_void
id|prom_halt
(paren
r_void
)paren
(brace
id|sun3x_halt
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Get the idprom and stuff it into buffer &squot;idbuf&squot;.  Returns the&n; * format type.  &squot;num_bytes&squot; is the number of bytes that your idbuf&n; * has space for.  Returns 0xff on error.&n; */
r_int
r_char
DECL|function|prom_get_idprom
id|prom_get_idprom
c_func
(paren
r_char
op_star
id|idbuf
comma
r_int
id|num_bytes
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* make a copy of the idprom structure */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num_bytes
suffix:semicolon
id|i
op_increment
)paren
(brace
id|idbuf
(braket
id|i
)braket
op_assign
(paren
(paren
r_char
op_star
)paren
id|SUN3X_IDPROM
)paren
(braket
id|i
)braket
suffix:semicolon
)brace
r_return
id|idbuf
(braket
l_int|0
)braket
suffix:semicolon
)brace
eof
