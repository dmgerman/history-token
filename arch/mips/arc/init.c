multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * PROM library initialisation code.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
DECL|macro|DEBUG_PROM_INIT
macro_line|#undef DEBUG_PROM_INIT
multiline_comment|/* Master romvec interface. */
DECL|variable|romvec
r_struct
id|linux_romvec
op_star
id|romvec
suffix:semicolon
DECL|variable|prom_argc
r_int
id|prom_argc
suffix:semicolon
DECL|variable|_prom_argv
DECL|variable|_prom_envp
id|LONG
op_star
id|_prom_argv
comma
op_star
id|_prom_envp
suffix:semicolon
DECL|function|prom_init
r_void
id|__init
id|prom_init
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
comma
r_char
op_star
op_star
id|envp
comma
r_int
op_star
id|prom_vec
)paren
(brace
id|PSYSTEM_PARAMETER_BLOCK
id|pb
op_assign
id|PROMBLOCK
suffix:semicolon
id|romvec
op_assign
id|ROMVECTOR
suffix:semicolon
id|prom_argc
op_assign
id|argc
suffix:semicolon
id|_prom_argv
op_assign
(paren
id|LONG
op_star
)paren
id|argv
suffix:semicolon
id|_prom_envp
op_assign
(paren
id|LONG
op_star
)paren
id|envp
suffix:semicolon
r_if
c_cond
(paren
id|pb-&gt;magic
op_ne
l_int|0x53435241
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;Aieee, bad prom vector magic %08lx&bslash;n&quot;
comma
id|pb-&gt;magic
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
)brace
id|prom_init_cmdline
c_func
(paren
)paren
suffix:semicolon
id|prom_identify_arch
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PROMLIB: ARC firmware Version %d Revision %d&bslash;n&quot;
comma
id|pb-&gt;ver
comma
id|pb-&gt;rev
)paren
suffix:semicolon
id|prom_meminit
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_PROM_INIT
id|prom_printf
c_func
(paren
l_string|&quot;Press a key to reboot&bslash;n&quot;
)paren
suffix:semicolon
id|prom_getchar
c_func
(paren
)paren
suffix:semicolon
id|ArcEnterInteractiveMode
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
