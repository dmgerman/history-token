multiline_comment|/*&n; * Copyright (C) 2000 RidgeRun, Inc.&n; * Author: RidgeRun, Inc.&n; *   glonnon@ridgerun.com, skranz@ridgerun.com, stevej@ridgerun.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/pci.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
DECL|variable|gt64120_base
r_int
r_int
id|gt64120_base
op_assign
id|KSEG1ADDR
c_func
(paren
l_int|0x14000000
)paren
suffix:semicolon
multiline_comment|/* These functions are used for rebooting or halting the machine*/
r_extern
r_void
id|galileo_machine_restart
c_func
(paren
r_char
op_star
id|command
)paren
suffix:semicolon
r_extern
r_void
id|galileo_machine_halt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|galileo_machine_power_off
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; *This structure holds pointers to the pci configuration space accesses&n; *and interrupts allocating routine for device over the PCI&n; */
r_extern
r_struct
id|pci_ops
id|galileo_pci_ops
suffix:semicolon
DECL|function|prom_free_prom_memory
r_int
r_int
id|__init
id|prom_free_prom_memory
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Initializes basic routines and structures pointers, memory size (as&n; * given by the bios and saves the command line.&n; */
r_extern
r_void
id|gt64120_time_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|ev64120_setup
r_static
r_void
id|__init
id|ev64120_setup
c_func
(paren
r_void
)paren
(brace
id|_machine_restart
op_assign
id|galileo_machine_restart
suffix:semicolon
id|_machine_halt
op_assign
id|galileo_machine_halt
suffix:semicolon
id|_machine_power_off
op_assign
id|galileo_machine_power_off
suffix:semicolon
id|board_time_init
op_assign
id|gt64120_time_init
suffix:semicolon
id|set_io_port_base
c_func
(paren
id|KSEG1
)paren
suffix:semicolon
)brace
DECL|variable|ev64120_setup
id|early_initcall
c_func
(paren
id|ev64120_setup
)paren
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
l_string|&quot;Galileo EV64120A&quot;
suffix:semicolon
)brace
multiline_comment|/*&n; * Kernel arguments passed by the firmware&n; *&n; * $a0 - nothing&n; * $a1 - holds a pointer to the eprom parameters&n; * $a2 - nothing&n; */
DECL|function|prom_init
r_void
id|__init
id|prom_init
c_func
(paren
r_void
)paren
(brace
id|mips_machgroup
op_assign
id|MACH_GROUP_GALILEO
suffix:semicolon
id|mips_machtype
op_assign
id|MACH_EV64120A
suffix:semicolon
id|add_memory_region
c_func
(paren
l_int|0
comma
l_int|32
op_lshift
l_int|20
comma
id|BOOT_MEM_RAM
)paren
suffix:semicolon
)brace
eof
