multiline_comment|/*&n; * BRIEF MODULE DESCRIPTION&n; * Momentum Computer Ocelot-G (CP7000G) - board dependent boot routines&n; *&n; * Copyright (C) 1996, 1997, 2001  Ralf Baechle&n; * Copyright (C) 2000 RidgeRun, Inc.&n; * Copyright (C) 2001 Red Hat, Inc.&n; * Copyright (C) 2002 Momentum Computer&n; *&n; * Author: Matthew Dharm, Momentum Computer&n; *   mdharm@momenco.com&n; *&n; * Author: RidgeRun, Inc.&n; *   glonnon@ridgerun.com, skranz@ridgerun.com, stevej@ridgerun.com&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: jsun@mvista.com or jsun@junsun.net&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
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
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/gt64240.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/pci.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &quot;ocelot_pld.h&quot;
macro_line|#ifdef CONFIG_GALILLEO_GT64240_ETH
r_extern
r_int
r_char
id|prom_mac_addr_base
(braket
l_int|6
)braket
suffix:semicolon
macro_line|#endif
DECL|variable|marvell_base
r_int
r_int
id|marvell_base
suffix:semicolon
multiline_comment|/* These functions are used for rebooting or halting the machine*/
r_extern
r_void
id|momenco_ocelot_restart
c_func
(paren
r_char
op_star
id|command
)paren
suffix:semicolon
r_extern
r_void
id|momenco_ocelot_halt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|momenco_ocelot_power_off
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|gt64240_time_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|momenco_ocelot_irq_setup
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|reset_reason
r_static
r_char
id|reset_reason
suffix:semicolon
DECL|function|ENTRYLO
r_static
r_int
r_int
id|ENTRYLO
c_func
(paren
r_int
r_int
id|paddr
)paren
(brace
r_return
(paren
(paren
id|paddr
op_amp
id|PAGE_MASK
)paren
op_or
(paren
id|_PAGE_PRESENT
op_or
id|__READABLE
op_or
id|__WRITEABLE
op_or
id|_PAGE_GLOBAL
op_or
id|_CACHE_UNCACHED
)paren
)paren
op_rshift
l_int|6
suffix:semicolon
)brace
multiline_comment|/* setup code for a handoff from a version 2 PMON 2000 PROM */
DECL|function|PMON_v2_setup
r_void
id|PMON_v2_setup
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* A wired TLB entry for the GT64240 and the serial port. The&n;&t;   GT64240 is going to be hit on every IRQ anyway - there&squot;s&n;&t;   absolutely no point in letting it be a random TLB entry, as&n;&t;   it&squot;ll just cause needless churning of the TLB. And we use&n;&t;   the other half for the serial port, which is just a PITA&n;&t;   otherwise :)&n;&n;&t;&t;Device&t;&t;&t;Physical&t;Virtual&n;&t;&t;GT64240 Internal Regs&t;0xf4000000&t;0xe0000000&n;&t;&t;UARTs (CS2)&t;&t;0xfd000000&t;0xe0001000&n;&t;*/
id|add_wired_entry
c_func
(paren
id|ENTRYLO
c_func
(paren
l_int|0xf4000000
)paren
comma
id|ENTRYLO
c_func
(paren
l_int|0xf4010000
)paren
comma
l_int|0xf4000000
comma
id|PM_64K
)paren
suffix:semicolon
id|add_wired_entry
c_func
(paren
id|ENTRYLO
c_func
(paren
l_int|0xfd000000
)paren
comma
id|ENTRYLO
c_func
(paren
l_int|0xfd001000
)paren
comma
l_int|0xfd000000
comma
id|PM_4K
)paren
suffix:semicolon
multiline_comment|/* Also a temporary entry to let us talk to the Ocelot PLD and NVRAM&n;&t;   in the CS[012] region. We can&squot;t use ioremap() yet. The NVRAM&n;&t;   is a ST M48T37Y, which includes NVRAM, RTC, and Watchdog functions.&n;&n;&t;&t;Ocelot PLD (CS0)&t;0xfc000000&t;0xe0020000&n;&t;&t;NVRAM (CS1)&t;&t;0xfc800000&t;0xe0030000&n;&t;*/
id|add_temporary_entry
c_func
(paren
id|ENTRYLO
c_func
(paren
l_int|0xfc000000
)paren
comma
id|ENTRYLO
c_func
(paren
l_int|0xfc010000
)paren
comma
l_int|0xfc000000
comma
id|PM_64K
)paren
suffix:semicolon
id|add_temporary_entry
c_func
(paren
id|ENTRYLO
c_func
(paren
l_int|0xfc800000
)paren
comma
id|ENTRYLO
c_func
(paren
l_int|0xfc810000
)paren
comma
l_int|0xfc800000
comma
id|PM_64K
)paren
suffix:semicolon
id|marvell_base
op_assign
l_int|0xf4000000
suffix:semicolon
)brace
r_extern
r_int
id|rm7k_tcache_enabled
suffix:semicolon
multiline_comment|/*&n; * This runs in KSEG1. See the verbiage in rm7k.c::probe_scache()&n; */
DECL|macro|Page_Invalidate_T
mdefine_line|#define Page_Invalidate_T 0x16
DECL|function|setup_l3cache
r_static
r_void
id|__init
id|setup_l3cache
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_int
r_register
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Enabling L3 cache...&quot;
)paren
suffix:semicolon
multiline_comment|/* Enable the L3 cache in the GT64120A&squot;s CPU Configuration register */
id|MV_WRITE
c_func
(paren
l_int|0
comma
id|MV_READ
c_func
(paren
l_int|0
)paren
op_or
(paren
l_int|1
op_lshift
l_int|14
)paren
)paren
suffix:semicolon
multiline_comment|/* Enable the L3 cache in the CPU */
id|set_c0_config
c_func
(paren
l_int|1
op_lshift
l_int|12
multiline_comment|/* CONF_TE */
)paren
suffix:semicolon
multiline_comment|/* Clear the cache */
id|write_c0_taglo
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|write_c0_taghi
c_func
(paren
l_int|0
)paren
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
id|size
suffix:semicolon
id|i
op_add_assign
l_int|4096
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;.set noreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set mips3&bslash;n&bslash;t&quot;
l_string|&quot;cache %1, (%0)&bslash;n&bslash;t&quot;
l_string|&quot;.set mips0&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|KSEG0ADDR
c_func
(paren
id|i
)paren
)paren
comma
l_string|&quot;i&quot;
(paren
id|Page_Invalidate_T
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Let the RM7000 MM code know that the tertiary cache is enabled */
id|rm7k_tcache_enabled
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Done&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|momenco_ocelot_g_setup
r_static
r_int
id|__init
id|momenco_ocelot_g_setup
c_func
(paren
r_void
)paren
(brace
r_void
(paren
op_star
id|l3func
)paren
(paren
r_int
r_int
)paren
op_assign
(paren
r_void
op_star
)paren
id|KSEG1ADDR
c_func
(paren
id|setup_l3cache
)paren
suffix:semicolon
r_int
r_int
id|tmpword
suffix:semicolon
id|board_time_init
op_assign
id|gt64240_time_init
suffix:semicolon
id|_machine_restart
op_assign
id|momenco_ocelot_restart
suffix:semicolon
id|_machine_halt
op_assign
id|momenco_ocelot_halt
suffix:semicolon
id|_machine_power_off
op_assign
id|momenco_ocelot_power_off
suffix:semicolon
multiline_comment|/*&n;&t; * initrd_start = (ulong)ocelot_initrd_start;&n;&t; * initrd_end = (ulong)ocelot_initrd_start + (ulong)ocelot_initrd_size;&n;&t; * initrd_below_start_ok = 1;&n;&t; */
multiline_comment|/* do handoff reconfiguration */
id|PMON_v2_setup
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_GALILLEO_GT64240_ETH
multiline_comment|/* get the mac addr */
id|memcpy
c_func
(paren
id|prom_mac_addr_base
comma
(paren
r_void
op_star
)paren
l_int|0xfc807cf2
comma
l_int|6
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Turn off the Bit-Error LED */
id|OCELOT_PLD_WRITE
c_func
(paren
l_int|0x80
comma
id|INTCLR
)paren
suffix:semicolon
id|tmpword
op_assign
id|OCELOT_PLD_READ
c_func
(paren
id|BOARDREV
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmpword
OL
l_int|26
)paren
id|printk
c_func
(paren
l_string|&quot;Momenco Ocelot-G: Board Assembly Rev. %c&bslash;n&quot;
comma
l_char|&squot;A&squot;
op_plus
id|tmpword
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;Momenco Ocelot-G: Board Assembly Revision #0x%x&bslash;n&quot;
comma
id|tmpword
)paren
suffix:semicolon
id|tmpword
op_assign
id|OCELOT_PLD_READ
c_func
(paren
id|PLD1_ID
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PLD 1 ID: %d.%d&bslash;n&quot;
comma
id|tmpword
op_rshift
l_int|4
comma
id|tmpword
op_amp
l_int|15
)paren
suffix:semicolon
id|tmpword
op_assign
id|OCELOT_PLD_READ
c_func
(paren
id|PLD2_ID
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PLD 2 ID: %d.%d&bslash;n&quot;
comma
id|tmpword
op_rshift
l_int|4
comma
id|tmpword
op_amp
l_int|15
)paren
suffix:semicolon
id|tmpword
op_assign
id|OCELOT_PLD_READ
c_func
(paren
id|RESET_STATUS
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Reset reason: 0x%x&bslash;n&quot;
comma
id|tmpword
)paren
suffix:semicolon
id|reset_reason
op_assign
id|tmpword
suffix:semicolon
id|OCELOT_PLD_WRITE
c_func
(paren
l_int|0xff
comma
id|RESET_STATUS
)paren
suffix:semicolon
id|tmpword
op_assign
id|OCELOT_PLD_READ
c_func
(paren
id|BOARD_STATUS
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Board Status register: 0x%02x&bslash;n&quot;
comma
id|tmpword
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  - User jumper: %s&bslash;n&quot;
comma
(paren
id|tmpword
op_amp
l_int|0x80
)paren
ques
c_cond
l_string|&quot;installed&quot;
suffix:colon
l_string|&quot;absent&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  - Boot flash write jumper: %s&bslash;n&quot;
comma
(paren
id|tmpword
op_amp
l_int|0x40
)paren
ques
c_cond
l_string|&quot;installed&quot;
suffix:colon
l_string|&quot;absent&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  - Tulip PHY %s connected&bslash;n&quot;
comma
(paren
id|tmpword
op_amp
l_int|0x10
)paren
ques
c_cond
l_string|&quot;is&quot;
suffix:colon
l_string|&quot;not&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  - L3 Cache size: %d MiB&bslash;n&quot;
comma
(paren
l_int|1
op_lshift
(paren
(paren
id|tmpword
op_amp
l_int|12
)paren
op_rshift
l_int|2
)paren
)paren
op_amp
op_complement
l_int|1
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  - SDRAM size: %d MiB&bslash;n&quot;
comma
l_int|1
op_lshift
(paren
l_int|6
op_plus
(paren
id|tmpword
op_amp
l_int|3
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmpword
op_amp
l_int|12
)paren
id|l3func
c_func
(paren
(paren
l_int|1
op_lshift
(paren
(paren
(paren
id|tmpword
op_amp
l_int|12
)paren
op_rshift
l_int|2
)paren
op_plus
l_int|20
)paren
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|tmpword
op_amp
l_int|3
)paren
(brace
r_case
l_int|3
suffix:colon
multiline_comment|/* 512MiB -- two banks of 256MiB */
id|add_memory_region
c_func
(paren
l_int|0x0
op_lshift
l_int|20
comma
l_int|0x100
op_lshift
l_int|20
comma
id|BOOT_MEM_RAM
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;add_memory_region(0x100&lt;&lt;20, 0x100&lt;&lt;20, BOOT_MEM_RAM);&n;*/
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* 256MiB -- two banks of 128MiB */
id|add_memory_region
c_func
(paren
l_int|0x0
op_lshift
l_int|20
comma
l_int|0x80
op_lshift
l_int|20
comma
id|BOOT_MEM_RAM
)paren
suffix:semicolon
id|add_memory_region
c_func
(paren
l_int|0x80
op_lshift
l_int|20
comma
l_int|0x80
op_lshift
l_int|20
comma
id|BOOT_MEM_RAM
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* 128MiB -- 64MiB per bank */
id|add_memory_region
c_func
(paren
l_int|0x0
op_lshift
l_int|20
comma
l_int|0x40
op_lshift
l_int|20
comma
id|BOOT_MEM_RAM
)paren
suffix:semicolon
id|add_memory_region
c_func
(paren
l_int|0x40
op_lshift
l_int|20
comma
l_int|0x40
op_lshift
l_int|20
comma
id|BOOT_MEM_RAM
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0
suffix:colon
multiline_comment|/* 64MiB */
id|add_memory_region
c_func
(paren
l_int|0x0
op_lshift
l_int|20
comma
l_int|0x40
op_lshift
l_int|20
comma
id|BOOT_MEM_RAM
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* FIXME: Fix up the DiskOnChip mapping */
id|MV_WRITE
c_func
(paren
l_int|0x468
comma
l_int|0xfef73
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|momenco_ocelot_g_setup
id|early_initcall
c_func
(paren
id|momenco_ocelot_g_setup
)paren
suffix:semicolon
multiline_comment|/* This needs to be one of the first initcalls, because no I/O port access&n;   can work before this */
DECL|function|io_base_ioremap
r_static
r_int
id|io_base_ioremap
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* we&squot;re mapping PCI accesses from 0xc0000000 to 0xf0000000 */
r_int
r_int
id|io_remap_range
suffix:semicolon
id|io_remap_range
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
l_int|0xc0000000
comma
l_int|0x30000000
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|io_remap_range
)paren
id|panic
c_func
(paren
l_string|&quot;Could not ioremap I/O port range&quot;
)paren
suffix:semicolon
id|set_io_port_base
c_func
(paren
id|io_remap_range
op_minus
l_int|0xc0000000
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|io_base_ioremap
id|module_init
c_func
(paren
id|io_base_ioremap
)paren
suffix:semicolon
eof
