macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pdc.h&gt;&t;/* for iodc_call() proto and friends */
macro_line|#include &lt;asm/real.h&gt;
DECL|variable|iodc_retbuf
r_static
r_int
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
id|iodc_retbuf
(braket
l_int|32
)braket
suffix:semicolon
DECL|variable|iodc_dbuf
r_static
r_char
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|64
)paren
)paren
)paren
id|iodc_dbuf
(braket
l_int|4096
)braket
suffix:semicolon
multiline_comment|/*&n; * pdc_putc:&n; * Console character print using IODC.&n; *&n; * Note that only these special chars are architected for console IODC io:&n; * BEL, BS, CR, and LF. Others are passed through.&n; * Since the HP console requires CR+LF to perform a &squot;newline&squot;, we translate&n; * &quot;&bslash;n&quot; to &quot;&bslash;r&bslash;n&quot;.&n; */
DECL|variable|posx
r_static
r_int
id|posx
suffix:semicolon
multiline_comment|/* for simple TAB-Simulation... */
multiline_comment|/* XXX Should we spinlock posx usage */
DECL|function|pdc_putc
r_void
id|pdc_putc
c_func
(paren
r_int
r_char
id|c
)paren
(brace
r_int
r_int
id|n
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_switch
c_cond
(paren
id|c
)paren
(brace
r_case
l_char|&squot;&bslash;n&squot;
suffix:colon
id|iodc_dbuf
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;r&squot;
suffix:semicolon
id|iodc_dbuf
(braket
l_int|1
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|n
op_assign
l_int|2
suffix:semicolon
id|posx
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;&bslash;t&squot;
suffix:colon
id|pdc_putc
c_func
(paren
l_char|&squot; &squot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|posx
op_amp
l_int|7
)paren
multiline_comment|/* expand TAB */
id|pdc_putc
c_func
(paren
l_char|&squot; &squot;
)paren
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/* return since IODC can&squot;t handle this */
r_case
l_char|&squot;&bslash;b&squot;
suffix:colon
id|posx
op_sub_assign
l_int|2
suffix:semicolon
multiline_comment|/* BS */
r_default
suffix:colon
id|iodc_dbuf
(braket
l_int|0
)braket
op_assign
id|c
suffix:semicolon
id|n
op_assign
l_int|1
suffix:semicolon
id|posx
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
(brace
id|real32_call
c_func
(paren
id|PAGE0-&gt;mem_cons.iodc_io
comma
(paren
r_int
r_int
)paren
id|PAGE0-&gt;mem_cons.hpa
comma
id|ENTRY_IO_COUT
comma
id|PAGE0-&gt;mem_cons.spa
comma
id|__pa
c_func
(paren
id|PAGE0-&gt;mem_cons.dp.layers
)paren
comma
id|__pa
c_func
(paren
id|iodc_retbuf
)paren
comma
l_int|0
comma
id|__pa
c_func
(paren
id|iodc_dbuf
)paren
comma
id|n
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
DECL|function|pdc_console_write
r_static
r_void
id|pdc_console_write
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
id|pdc_putc
c_func
(paren
op_star
id|s
op_increment
)paren
suffix:semicolon
)brace
)brace
DECL|function|pdc_console_wait_key
r_int
id|pdc_console_wait_key
c_func
(paren
r_struct
id|console
op_star
id|co
)paren
(brace
r_int
id|ch
op_assign
l_char|&squot;X&squot;
suffix:semicolon
r_int
id|status
suffix:semicolon
multiline_comment|/* Bail if no console input device. */
r_if
c_cond
(paren
op_logical_neg
id|PAGE0-&gt;mem_kbd.iodc_io
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* wait for a keyboard (rs232)-input */
r_do
(brace
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|status
op_assign
id|real32_call
c_func
(paren
id|PAGE0-&gt;mem_kbd.iodc_io
comma
(paren
r_int
r_int
)paren
id|PAGE0-&gt;mem_kbd.hpa
comma
id|ENTRY_IO_CIN
comma
id|PAGE0-&gt;mem_kbd.spa
comma
id|__pa
c_func
(paren
id|PAGE0-&gt;mem_kbd.dp.layers
)paren
comma
id|__pa
c_func
(paren
id|iodc_retbuf
)paren
comma
l_int|0
comma
id|__pa
c_func
(paren
id|iodc_dbuf
)paren
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|ch
op_assign
op_star
id|iodc_dbuf
suffix:semicolon
multiline_comment|/* save the character directly to ch */
)brace
r_while
c_loop
(paren
op_star
id|iodc_retbuf
op_eq
l_int|0
)paren
suffix:semicolon
multiline_comment|/* wait for a key */
r_return
id|ch
suffix:semicolon
)brace
DECL|function|pdc_getc
r_int
id|pdc_getc
c_func
(paren
r_void
)paren
(brace
r_return
id|pdc_console_wait_key
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|pdc_console_setup
r_static
r_int
id|pdc_console_setup
c_func
(paren
r_struct
id|console
op_star
id|co
comma
r_char
op_star
id|options
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pdc_cons
r_static
r_struct
id|console
id|pdc_cons
op_assign
(brace
id|name
suffix:colon
l_string|&quot;ttyB&quot;
comma
id|write
suffix:colon
id|pdc_console_write
comma
id|setup
suffix:colon
id|pdc_console_setup
comma
id|flags
suffix:colon
id|CON_PRINTBUFFER
op_or
id|CON_ENABLED
comma
singleline_comment|// |CON_CONSDEV,
id|index
suffix:colon
op_minus
l_int|1
comma
)brace
suffix:semicolon
DECL|variable|pdc_console_initialized
r_static
r_int
id|pdc_console_initialized
suffix:semicolon
DECL|function|pdc_console_init
r_void
id|pdc_console_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|pdc_console_initialized
)paren
r_return
suffix:semicolon
op_increment
id|pdc_console_initialized
suffix:semicolon
multiline_comment|/* If the console is duplex then copy the COUT parameters to CIN. */
r_if
c_cond
(paren
id|PAGE0-&gt;mem_cons.cl_class
op_eq
id|CL_DUPLEX
)paren
id|memcpy
c_func
(paren
op_amp
id|PAGE0-&gt;mem_kbd
comma
op_amp
id|PAGE0-&gt;mem_cons
comma
r_sizeof
(paren
id|PAGE0-&gt;mem_cons
)paren
)paren
suffix:semicolon
id|pdc_console_write
c_func
(paren
l_int|0
comma
l_string|&quot;PDC Console Initialized&bslash;n&quot;
comma
l_int|24
)paren
suffix:semicolon
multiline_comment|/* register the pdc console */
id|register_console
c_func
(paren
op_amp
id|pdc_cons
)paren
suffix:semicolon
)brace
multiline_comment|/* Unregister the pdc console with the printk console layer */
DECL|function|pdc_console_die
r_void
id|pdc_console_die
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Switching from PDC console&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pdc_console_initialized
)paren
r_return
suffix:semicolon
op_decrement
id|pdc_console_initialized
suffix:semicolon
macro_line|#ifdef CONFIG_VT_CONSOLE
id|schedule_console_callback
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|unregister_console
c_func
(paren
op_amp
id|pdc_cons
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Used for emergencies. Currently only used if an HPMC occurs. If an&n; * HPMC occurs, it is possible that the current console may not be&n; * properly initialed after the PDC IO reset. This routine unregisters all&n; * of the current consoles, reinitializes the pdc console and&n; * registers it.&n; */
DECL|function|pdc_console_restart
r_void
id|pdc_console_restart
c_func
(paren
r_void
)paren
(brace
r_struct
id|console
op_star
id|console
suffix:semicolon
r_extern
r_int
id|log_size
suffix:semicolon
r_if
c_cond
(paren
id|pdc_console_initialized
)paren
r_return
suffix:semicolon
r_while
c_loop
(paren
(paren
id|console
op_assign
id|console_drivers
)paren
op_ne
(paren
r_struct
id|console
op_star
)paren
l_int|0
)paren
id|unregister_console
c_func
(paren
id|console_drivers
)paren
suffix:semicolon
id|log_size
op_assign
l_int|0
suffix:semicolon
id|pdc_console_init
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Switched to PDC console&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
