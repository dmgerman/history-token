multiline_comment|/* $Id: misc.c,v 1.18 2000/08/26 02:38:03 anton Exp $&n; * misc.c:  Miscellaneous prom functions that don&squot;t belong&n; *          anywhere else.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/openprom.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/auxio.h&gt;
macro_line|#include &lt;asm/system.h&gt;
r_extern
r_void
id|restore_current
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|prom_lock
id|spinlock_t
id|prom_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* Reset and reboot the machine with the command &squot;bcommand&squot;. */
r_void
DECL|function|prom_reboot
id|prom_reboot
c_func
(paren
r_char
op_star
id|bcommand
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
(paren
op_star
(paren
id|romvec-&gt;pv_reboot
)paren
)paren
(paren
id|bcommand
)paren
suffix:semicolon
multiline_comment|/* Never get here. */
id|restore_current
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Forth evaluate the expression contained in &squot;fstring&squot;. */
r_void
DECL|function|prom_feval
id|prom_feval
c_func
(paren
r_char
op_star
id|fstring
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fstring
op_logical_or
id|fstring
(braket
l_int|0
)braket
op_eq
l_int|0
)paren
(brace
r_return
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prom_vers
op_eq
id|PROM_V0
)paren
(brace
(paren
op_star
(paren
id|romvec-&gt;pv_fortheval.v0_eval
)paren
)paren
(paren
id|strlen
c_func
(paren
id|fstring
)paren
comma
id|fstring
)paren
suffix:semicolon
)brace
r_else
(paren
op_star
(paren
id|romvec-&gt;pv_fortheval.v2_eval
)paren
)paren
(paren
id|fstring
)paren
suffix:semicolon
id|restore_current
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* We want to do this more nicely some day. */
r_extern
r_void
(paren
op_star
id|prom_palette
)paren
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/* Drop into the prom, with the chance to continue with the &squot;go&squot;&n; * prom command.&n; */
r_void
DECL|function|prom_cmdline
id|prom_cmdline
c_func
(paren
r_void
)paren
(brace
r_extern
r_void
id|install_obp_ticker
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|install_linux_ticker
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|serial_console
op_logical_and
id|prom_palette
)paren
(brace
id|prom_palette
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
id|install_obp_ticker
c_func
(paren
)paren
suffix:semicolon
(paren
op_star
(paren
id|romvec-&gt;pv_abort
)paren
)paren
(paren
)paren
suffix:semicolon
id|restore_current
c_func
(paren
)paren
suffix:semicolon
id|install_linux_ticker
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SUN_AUXIO
id|set_auxio
c_func
(paren
id|AUXIO_LED
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|serial_console
op_logical_and
id|prom_palette
)paren
(brace
id|prom_palette
(paren
l_int|0
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Drop into the prom, but completely terminate the program.&n; * No chance of continuing.&n; */
r_void
DECL|function|prom_halt
id|prom_halt
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|again
suffix:colon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
(paren
op_star
(paren
id|romvec-&gt;pv_halt
)paren
)paren
(paren
)paren
suffix:semicolon
multiline_comment|/* Never get here. */
id|restore_current
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
r_goto
id|again
suffix:semicolon
multiline_comment|/* PROM is out to get me -DaveM */
)brace
DECL|typedef|sfunc_t
r_typedef
r_void
(paren
op_star
id|sfunc_t
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Set prom sync handler to call function &squot;funcp&squot;. */
r_void
DECL|function|prom_setsync
id|prom_setsync
c_func
(paren
id|sfunc_t
id|funcp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|funcp
)paren
(brace
r_return
suffix:semicolon
)brace
op_star
id|romvec-&gt;pv_synchook
op_assign
id|funcp
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
id|len
suffix:semicolon
id|len
op_assign
id|prom_getproplen
c_func
(paren
id|prom_root_node
comma
l_string|&quot;idprom&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
OG
id|num_bytes
)paren
op_logical_or
(paren
id|len
op_eq
op_minus
l_int|1
)paren
)paren
(brace
r_return
l_int|0xff
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|prom_getproperty
c_func
(paren
id|prom_root_node
comma
l_string|&quot;idprom&quot;
comma
id|idbuf
comma
id|num_bytes
)paren
)paren
(brace
r_return
id|idbuf
(braket
l_int|0
)braket
suffix:semicolon
)brace
r_return
l_int|0xff
suffix:semicolon
)brace
multiline_comment|/* Get the major prom version number. */
r_int
DECL|function|prom_version
id|prom_version
c_func
(paren
r_void
)paren
(brace
r_return
id|romvec-&gt;pv_romvers
suffix:semicolon
)brace
multiline_comment|/* Get the prom plugin-revision. */
r_int
DECL|function|prom_getrev
id|prom_getrev
c_func
(paren
r_void
)paren
(brace
r_return
id|prom_rev
suffix:semicolon
)brace
multiline_comment|/* Get the prom firmware print revision. */
r_int
DECL|function|prom_getprev
id|prom_getprev
c_func
(paren
r_void
)paren
(brace
r_return
id|prom_prev
suffix:semicolon
)brace
eof
