multiline_comment|/***********************************************************************&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *              ahennessy@mvista.com&n; *&n; * arch/mips/jmr3927/common/init.c&n; *&n; * Copyright (C) 2000-2001 Toshiba Corporation&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; ***********************************************************************&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/jmr3927/jmr3927.h&gt;
DECL|variable|prom_argc
r_int
id|prom_argc
suffix:semicolon
DECL|variable|prom_argv
DECL|variable|prom_envp
r_char
op_star
op_star
id|prom_argv
comma
op_star
op_star
id|prom_envp
suffix:semicolon
r_extern
r_void
id|__init
id|prom_init_cmdline
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_char
op_star
id|prom_getenv
c_func
(paren
r_char
op_star
id|envname
)paren
suffix:semicolon
DECL|variable|mips_nofpu
r_int
r_int
id|mips_nofpu
op_assign
l_int|0
suffix:semicolon
DECL|function|get_system_type
r_const
r_char
op_star
id|get_system_type
c_func
(paren
r_void
)paren
(brace
r_return
l_string|&quot;Toshiba&quot;
macro_line|#ifdef CONFIG_TOSHIBA_JMR3927
l_string|&quot; JMR_TX3927&quot;
macro_line|#endif
suffix:semicolon
)brace
r_extern
r_void
id|puts
c_func
(paren
r_int
r_char
op_star
id|cp
)paren
suffix:semicolon
DECL|function|prom_init
r_int
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
macro_line|#ifdef CONFIG_TOSHIBA_JMR3927
multiline_comment|/* CCFG */
r_if
c_cond
(paren
(paren
id|tx3927_ccfgptr-&gt;ccfg
op_amp
id|TX3927_CCFG_TLBOFF
)paren
op_eq
l_int|0
)paren
id|puts
c_func
(paren
l_string|&quot;Warning: TX3927 TLB off&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|prom_argc
op_assign
id|argc
suffix:semicolon
id|prom_argv
op_assign
id|argv
suffix:semicolon
id|prom_envp
op_assign
id|envp
suffix:semicolon
id|mips_machgroup
op_assign
id|MACH_GROUP_TOSHIBA
suffix:semicolon
macro_line|#ifdef CONFIG_TOSHIBA_JMR3927
id|mips_machtype
op_assign
id|MACH_TOSHIBA_JMR3927
suffix:semicolon
macro_line|#endif
id|prom_init_cmdline
c_func
(paren
)paren
suffix:semicolon
id|add_memory_region
c_func
(paren
l_int|0
comma
id|JMR3927_SDRAM_SIZE
comma
id|BOOT_MEM_RAM
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
