multiline_comment|/*&n; * BRIEF MODULE DESCRIPTION&n; *&t;IT8172/QED5231 board setup.&n; *&n; * Copyright 2000 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or source@mvista.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/it8172/it8172.h&gt;
macro_line|#include &lt;asm/it8172/it8172_dbg.h&gt;
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
r_char
id|_end
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
r_int
r_int
id|__init
id|prom_get_memsize
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__init
id|it8172_init_ram_resource
c_func
(paren
r_int
r_int
id|memsize
)paren
suffix:semicolon
DECL|macro|PFN_UP
mdefine_line|#define PFN_UP(x)&t;(((x) + PAGE_SIZE-1) &gt;&gt; PAGE_SHIFT)
DECL|macro|PFN_ALIGN
mdefine_line|#define PFN_ALIGN(x)&t;(((unsigned long)(x) + (PAGE_SIZE - 1)) &amp; PAGE_MASK)
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
l_string|&quot;ITE QED-4N-S01B&quot;
suffix:semicolon
)brace
DECL|function|prom_init
r_void
id|__init
id|prom_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|mem_size
suffix:semicolon
r_int
r_int
id|pcicr
suffix:semicolon
id|prom_argc
op_assign
id|fw_arg0
suffix:semicolon
id|prom_argv
op_assign
(paren
r_char
op_star
op_star
)paren
id|fw_arg1
suffix:semicolon
id|prom_envp
op_assign
(paren
r_int
op_star
)paren
id|fw_arg3
suffix:semicolon
id|mips_machgroup
op_assign
id|MACH_GROUP_ITE
suffix:semicolon
id|mips_machtype
op_assign
id|MACH_QED_4N_S01B
suffix:semicolon
multiline_comment|/* ITE board name/number */
id|prom_init_cmdline
c_func
(paren
)paren
suffix:semicolon
id|mem_size
op_assign
id|prom_get_memsize
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Memory size: %dMB&bslash;n&quot;
comma
(paren
r_int
)paren
id|mem_size
)paren
suffix:semicolon
id|mem_size
op_lshift_assign
l_int|20
suffix:semicolon
multiline_comment|/* MB */
multiline_comment|/*&n;&t; * make the entire physical memory visible to pci bus masters&n;&t; */
id|IT_READ
c_func
(paren
id|IT_MC_PCICR
comma
id|pcicr
)paren
suffix:semicolon
id|pcicr
op_and_assign
op_complement
l_int|0x1f
suffix:semicolon
id|pcicr
op_or_assign
(paren
id|mem_size
op_minus
l_int|1
)paren
op_rshift
l_int|22
suffix:semicolon
id|IT_WRITE
c_func
(paren
id|IT_MC_PCICR
comma
id|pcicr
)paren
suffix:semicolon
id|it8172_init_ram_resource
c_func
(paren
id|mem_size
)paren
suffix:semicolon
id|add_memory_region
c_func
(paren
l_int|0
comma
id|mem_size
comma
id|BOOT_MEM_RAM
)paren
suffix:semicolon
)brace
eof
