multiline_comment|/*&n; * BRIEF MODULE DESCRIPTION&n; * Galileo Evaluation Boards - board dependent boot routines&n; *&n; * Copyright (C) 2000 RidgeRun, Inc.&n; * Author: RidgeRun, Inc.&n; *   glonnon@ridgerun.com, skranz@ridgerun.com, stevej@ridgerun.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/pci.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;asm/mc146818rtc.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
r_extern
r_struct
id|rtc_ops
id|no_rtc_ops
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
r_extern
r_int
r_int
id|mips_machgroup
suffix:semicolon
DECL|variable|arcs_cmdline
r_char
id|arcs_cmdline
(braket
id|CL_SIZE
)braket
op_assign
(brace
l_string|&quot;console=ttyS0,115200 &quot;
l_string|&quot;root=/dev/nfs rw nfsroot=192.168.1.1:/mnt/disk2/fs.gal &quot;
l_string|&quot;ip=192.168.1.211:192.168.1.1:::gt::&quot;
)brace
suffix:semicolon
singleline_comment|//struct eeprom_parameters eeprom_param;
multiline_comment|/*&n; * This function is added because arch/mips/mm/init.c needs it&n; * basically it does nothing&n; */
DECL|function|prom_free_prom_memory
r_void
id|prom_free_prom_memory
c_func
(paren
r_void
)paren
(brace
)brace
r_extern
r_void
(paren
op_star
id|board_time_init
)paren
(paren
r_struct
id|irqaction
op_star
id|irq
)paren
suffix:semicolon
DECL|function|galileo_rtc_read_data
r_static
r_int
r_char
id|galileo_rtc_read_data
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|galileo_rtc_write_data
r_static
r_void
id|galileo_rtc_write_data
c_func
(paren
r_int
r_char
id|data
comma
r_int
r_int
id|addr
)paren
(brace
)brace
DECL|function|galileo_rtc_bcd_mode
r_static
r_int
id|galileo_rtc_bcd_mode
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|galileo_rtc_ops
r_struct
id|rtc_ops
id|galileo_rtc_ops
op_assign
(brace
op_amp
id|galileo_rtc_read_data
comma
op_amp
id|galileo_rtc_write_data
comma
op_amp
id|galileo_rtc_bcd_mode
)brace
suffix:semicolon
multiline_comment|/********************************************************************&n; *ev64120_setup -&n; *&n; *Initializes basic routines and structures pointers, memory size (as&n; *given by the bios and saves the command line.&n; *&n; *&n; *Inputs :&n; *&n; *Outpus :&n; *&n; *********************************************************************/
r_extern
r_void
id|galileo_time_init
c_func
(paren
)paren
suffix:semicolon
DECL|function|ev64120_setup
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
id|rtc_ops
op_assign
op_amp
id|galileo_rtc_ops
suffix:semicolon
id|board_time_init
op_assign
id|galileo_time_init
suffix:semicolon
id|set_io_port_base
c_func
(paren
id|KSEG1
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_L2_L3_CACHE
macro_line|#error &quot;external cache not implemented yet&quot;
id|config_register
op_assign
id|read_c0_config
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&bslash;n&bslash;nchecking second level cache cp0_config = %08lx&bslash;n&quot;
comma
id|config_register
)paren
suffix:semicolon
r_if
c_cond
(paren
id|config_register
op_amp
id|CONF_SC
)paren
(brace
singleline_comment|// second/third level cache available
id|config_register
op_assign
id|config_register
op_amp
(paren
l_int|1
op_lshift
l_int|12
)paren
suffix:semicolon
id|write_c0_config
c_func
(paren
id|config_register
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;&bslash;n&bslash;n&bslash;nchecking second level cache c0_config = %08lx&bslash;n&quot;
comma
id|config_register
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
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
multiline_comment|/*&n; * SetUpBootInfo -&n; *&n; * This function is called at very first stages of kernel startup.&n; * It specifies for the kernel the evaluation board that the linux&n; * is running on. Then it saves the eprom parameters that holds the&n; * command line, memory size etc...&n; *&n; * Inputs :&n; * argc - nothing&n; * argv - holds a pointer to the eprom parameters&n; * envp - nothing&n; */
DECL|function|SetUpBootInfo
r_void
id|SetUpBootInfo
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
)brace
DECL|function|prom_init
r_void
id|__init
id|prom_init
c_func
(paren
r_int
id|a
comma
r_char
op_star
op_star
id|b
comma
r_char
op_star
op_star
id|c
comma
r_int
op_star
id|d
)paren
(brace
id|mips_machgroup
op_assign
id|MACH_GROUP_GALILEO
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
