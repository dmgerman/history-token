multiline_comment|/*&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;PB1000 board setup&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or source@mvista.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
r_extern
r_int
id|prom_argc
suffix:semicolon
r_extern
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
id|MACH_GROUP_ALCHEMY
suffix:semicolon
id|mips_machtype
op_assign
id|MACH_PB1000
suffix:semicolon
id|prom_init_cmdline
c_func
(paren
)paren
suffix:semicolon
id|add_memory_region
c_func
(paren
l_int|1
comma
l_int|64
op_lshift
l_int|20
comma
id|BOOT_MEM_RAM
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
