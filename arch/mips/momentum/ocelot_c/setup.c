multiline_comment|/*&n; * BRIEF MODULE DESCRIPTION&n; * Momentum Computer Ocelot-C and -CS board dependent boot routines&n; *&n; * Copyright (C) 1996, 1997, 2001  Ralf Baechle&n; * Copyright (C) 2000 RidgeRun, Inc.&n; * Copyright (C) 2001 Red Hat, Inc.&n; * Copyright (C) 2002 Momentum Computer&n; *&n; * Author: Matthew Dharm, Momentum Computer&n; *   mdharm@momenco.com&n; *&n; * Author: RidgeRun, Inc.&n; *   glonnon@ridgerun.com, skranz@ridgerun.com, stevej@ridgerun.com&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: jsun@mvista.com or jsun@junsun.net&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#include &lt;linux/bcd.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
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
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/pci.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;asm/mc146818rtc.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;asm/mv64340.h&gt;
macro_line|#include &quot;ocelot_c_fpga.h&quot;
DECL|variable|mv64340_base
r_int
r_int
id|mv64340_base
suffix:semicolon
DECL|variable|cpu_clock
r_int
r_int
id|cpu_clock
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
r_void
id|momenco_time_init
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
DECL|macro|ENTRYLO
mdefine_line|#define ENTRYLO(x) ((pte_val(mk_pte_phys((x), PAGE_KERNEL_UNCACHED)) &gt;&gt; 6)|1)
multiline_comment|/* setup code for a handoff from a version 2 PMON 2000 PROM */
DECL|function|PMON_v2_setup
r_void
id|PMON_v2_setup
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Some wired TLB entries for the MV64340 and perhiperals. The&n;&t;   MV64340 is going to be hit on every IRQ anyway - there&squot;s&n;&t;   absolutely no point in letting it be a random TLB entry, as&n;&t;   it&squot;ll just cause needless churning of the TLB. And we use&n;&t;   the other half for the serial port, which is just a PITA&n;&t;   otherwise :)&n;&n;&t;&t;Device&t;&t;&t;Physical&t;Virtual&n;&t;&t;MV64340 Internal Regs&t;0xf4000000&t;0xf4000000&n;&t;&t;Ocelot-C[S] PLD (CS0)&t;0xfc000000&t;0xfc000000&n;&t;&t;NVRAM (CS1)&t;&t;0xfc800000&t;0xfc800000&n;&t;&t;UARTs (CS2)&t;&t;0xfd000000&t;0xfd000000&n;&t;&t;Internal SRAM&t;&t;0xfe000000&t;0xfe000000&n;&t;&t;M-Systems DOC (CS3)&t;0xff000000&t;0xff000000&n;&t;*/
multiline_comment|/* marvell and extra space */
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
multiline_comment|/* fpga, rtc, and uart */
id|add_wired_entry
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
l_int|0xfd000000
)paren
comma
l_int|0xfc000000
comma
id|PM_16M
)paren
suffix:semicolon
multiline_comment|/* m-sys and internal SRAM */
id|add_wired_entry
c_func
(paren
id|ENTRYLO
c_func
(paren
l_int|0xfe000000
)paren
comma
id|ENTRYLO
c_func
(paren
l_int|0xff000000
)paren
comma
l_int|0xfe000000
comma
id|PM_16M
)paren
suffix:semicolon
id|mv64340_base
op_assign
l_int|0xf4000000
suffix:semicolon
)brace
DECL|function|m48t37y_get_time
r_int
r_int
id|m48t37y_get_time
c_func
(paren
r_void
)paren
(brace
r_int
r_char
op_star
id|rtc_base
op_assign
(paren
r_int
r_char
op_star
)paren
l_int|0xfc800000
suffix:semicolon
r_int
r_int
id|year
comma
id|month
comma
id|day
comma
id|hour
comma
id|min
comma
id|sec
suffix:semicolon
multiline_comment|/* stop the update */
id|rtc_base
(braket
l_int|0x7ff8
)braket
op_assign
l_int|0x40
suffix:semicolon
id|year
op_assign
id|BCD2BIN
c_func
(paren
id|rtc_base
(braket
l_int|0x7fff
)braket
)paren
suffix:semicolon
id|year
op_add_assign
id|BCD2BIN
c_func
(paren
id|rtc_base
(braket
l_int|0x7ff1
)braket
)paren
op_star
l_int|100
suffix:semicolon
id|month
op_assign
id|BCD2BIN
c_func
(paren
id|rtc_base
(braket
l_int|0x7ffe
)braket
)paren
suffix:semicolon
id|day
op_assign
id|BCD2BIN
c_func
(paren
id|rtc_base
(braket
l_int|0x7ffd
)braket
)paren
suffix:semicolon
id|hour
op_assign
id|BCD2BIN
c_func
(paren
id|rtc_base
(braket
l_int|0x7ffb
)braket
)paren
suffix:semicolon
id|min
op_assign
id|BCD2BIN
c_func
(paren
id|rtc_base
(braket
l_int|0x7ffa
)braket
)paren
suffix:semicolon
id|sec
op_assign
id|BCD2BIN
c_func
(paren
id|rtc_base
(braket
l_int|0x7ff9
)braket
)paren
suffix:semicolon
multiline_comment|/* start the update */
id|rtc_base
(braket
l_int|0x7ff8
)braket
op_assign
l_int|0x00
suffix:semicolon
r_return
id|mktime
c_func
(paren
id|year
comma
id|month
comma
id|day
comma
id|hour
comma
id|min
comma
id|sec
)paren
suffix:semicolon
)brace
DECL|function|m48t37y_set_time
r_int
id|m48t37y_set_time
c_func
(paren
r_int
r_int
id|sec
)paren
(brace
r_int
r_char
op_star
id|rtc_base
op_assign
(paren
r_int
r_char
op_star
)paren
l_int|0xfc800000
suffix:semicolon
r_struct
id|rtc_time
id|tm
suffix:semicolon
multiline_comment|/* convert to a more useful format -- note months count from 0 */
id|to_tm
c_func
(paren
id|sec
comma
op_amp
id|tm
)paren
suffix:semicolon
id|tm.tm_mon
op_add_assign
l_int|1
suffix:semicolon
multiline_comment|/* enable writing */
id|rtc_base
(braket
l_int|0x7ff8
)braket
op_assign
l_int|0x80
suffix:semicolon
multiline_comment|/* year */
id|rtc_base
(braket
l_int|0x7fff
)braket
op_assign
id|BIN2BCD
c_func
(paren
id|tm.tm_year
op_mod
l_int|100
)paren
suffix:semicolon
id|rtc_base
(braket
l_int|0x7ff1
)braket
op_assign
id|BIN2BCD
c_func
(paren
id|tm.tm_year
op_div
l_int|100
)paren
suffix:semicolon
multiline_comment|/* month */
id|rtc_base
(braket
l_int|0x7ffe
)braket
op_assign
id|BIN2BCD
c_func
(paren
id|tm.tm_mon
)paren
suffix:semicolon
multiline_comment|/* day */
id|rtc_base
(braket
l_int|0x7ffd
)braket
op_assign
id|BIN2BCD
c_func
(paren
id|tm.tm_mday
)paren
suffix:semicolon
multiline_comment|/* hour/min/sec */
id|rtc_base
(braket
l_int|0x7ffb
)braket
op_assign
id|BIN2BCD
c_func
(paren
id|tm.tm_hour
)paren
suffix:semicolon
id|rtc_base
(braket
l_int|0x7ffa
)braket
op_assign
id|BIN2BCD
c_func
(paren
id|tm.tm_min
)paren
suffix:semicolon
id|rtc_base
(braket
l_int|0x7ff9
)braket
op_assign
id|BIN2BCD
c_func
(paren
id|tm.tm_sec
)paren
suffix:semicolon
multiline_comment|/* day of week -- not really used, but let&squot;s keep it up-to-date */
id|rtc_base
(braket
l_int|0x7ffc
)braket
op_assign
id|CONV_BIN2BCD
c_func
(paren
id|tm.tm_wday
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* disable writing */
id|rtc_base
(braket
l_int|0x7ff8
)braket
op_assign
l_int|0x00
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|momenco_timer_setup
r_void
id|momenco_timer_setup
c_func
(paren
r_struct
id|irqaction
op_star
id|irq
)paren
(brace
id|setup_irq
c_func
(paren
l_int|7
comma
id|irq
)paren
suffix:semicolon
)brace
DECL|function|momenco_time_init
r_void
id|momenco_time_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_CPU_SR71000
id|mips_counter_frequency
op_assign
id|cpu_clock
suffix:semicolon
macro_line|#elif defined(CONFIG_CPU_RM7000)
id|mips_counter_frequency
op_assign
id|cpu_clock
op_div
l_int|2
suffix:semicolon
macro_line|#else
macro_line|#error Unknown CPU for this board
macro_line|#endif
id|board_timer_setup
op_assign
id|momenco_timer_setup
suffix:semicolon
id|rtc_get_time
op_assign
id|m48t37y_get_time
suffix:semicolon
id|rtc_set_time
op_assign
id|m48t37y_set_time
suffix:semicolon
)brace
DECL|function|momenco_ocelot_c_setup
r_void
id|__init
id|momenco_ocelot_c_setup
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|tmpword
suffix:semicolon
id|board_time_init
op_assign
id|momenco_time_init
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
multiline_comment|/* shut down ethernet ports, just to be sure our memory doesn&squot;t get&n;&t; * corrupted by random ethernet traffic.&n;&t; */
id|MV_WRITE
c_func
(paren
id|MV64340_ETH_TRANSMIT_QUEUE_COMMAND_REG
c_func
(paren
l_int|0
)paren
comma
l_int|0xff
op_lshift
l_int|8
)paren
suffix:semicolon
id|MV_WRITE
c_func
(paren
id|MV64340_ETH_TRANSMIT_QUEUE_COMMAND_REG
c_func
(paren
l_int|1
)paren
comma
l_int|0xff
op_lshift
l_int|8
)paren
suffix:semicolon
id|MV_WRITE
c_func
(paren
id|MV64340_ETH_RECEIVE_QUEUE_COMMAND_REG
c_func
(paren
l_int|0
)paren
comma
l_int|0xff
op_lshift
l_int|8
)paren
suffix:semicolon
id|MV_WRITE
c_func
(paren
id|MV64340_ETH_RECEIVE_QUEUE_COMMAND_REG
c_func
(paren
l_int|1
)paren
comma
l_int|0xff
op_lshift
l_int|8
)paren
suffix:semicolon
r_do
(brace
)brace
r_while
c_loop
(paren
id|MV_READ_DATA
c_func
(paren
id|MV64340_ETH_RECEIVE_QUEUE_COMMAND_REG
c_func
(paren
l_int|0
)paren
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
r_do
(brace
)brace
r_while
c_loop
(paren
id|MV_READ_DATA
c_func
(paren
id|MV64340_ETH_RECEIVE_QUEUE_COMMAND_REG
c_func
(paren
l_int|1
)paren
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
r_do
(brace
)brace
r_while
c_loop
(paren
id|MV_READ_DATA
c_func
(paren
id|MV64340_ETH_TRANSMIT_QUEUE_COMMAND_REG
c_func
(paren
l_int|0
)paren
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
r_do
(brace
)brace
r_while
c_loop
(paren
id|MV_READ_DATA
c_func
(paren
id|MV64340_ETH_TRANSMIT_QUEUE_COMMAND_REG
c_func
(paren
l_int|1
)paren
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|MV_WRITE
c_func
(paren
id|MV64340_ETH_PORT_SERIAL_CONTROL_REG
c_func
(paren
l_int|0
)paren
comma
id|MV_READ_DATA
c_func
(paren
id|MV64340_ETH_PORT_SERIAL_CONTROL_REG
c_func
(paren
l_int|0
)paren
)paren
op_amp
op_complement
l_int|1
)paren
suffix:semicolon
id|MV_WRITE
c_func
(paren
id|MV64340_ETH_PORT_SERIAL_CONTROL_REG
c_func
(paren
l_int|1
)paren
comma
id|MV_READ_DATA
c_func
(paren
id|MV64340_ETH_PORT_SERIAL_CONTROL_REG
c_func
(paren
l_int|1
)paren
)paren
op_amp
op_complement
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Turn off the Bit-Error LED */
id|OCELOT_FPGA_WRITE
c_func
(paren
l_int|0x80
comma
id|CLR
)paren
suffix:semicolon
id|tmpword
op_assign
id|OCELOT_FPGA_READ
c_func
(paren
id|BOARDREV
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_SR71000
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
l_string|&quot;Momenco Ocelot-CS: Board Assembly Rev. %c&bslash;n&quot;
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
l_string|&quot;Momenco Ocelot-CS: Board Assembly Revision #0x%x&bslash;n&quot;
comma
id|tmpword
)paren
suffix:semicolon
macro_line|#else
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
l_string|&quot;Momenco Ocelot-C: Board Assembly Rev. %c&bslash;n&quot;
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
l_string|&quot;Momenco Ocelot-C: Board Assembly Revision #0x%x&bslash;n&quot;
comma
id|tmpword
)paren
suffix:semicolon
macro_line|#endif
id|tmpword
op_assign
id|OCELOT_FPGA_READ
c_func
(paren
id|FPGA_REV
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;FPGA Rev: %d.%d&bslash;n&quot;
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
id|OCELOT_FPGA_READ
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
r_switch
c_cond
(paren
id|tmpword
)paren
(brace
r_case
l_int|0x1
suffix:colon
id|printk
c_func
(paren
l_string|&quot;  - Power-up reset&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x2
suffix:colon
id|printk
c_func
(paren
l_string|&quot;  - Push-button reset&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x4
suffix:colon
id|printk
c_func
(paren
l_string|&quot;  - cPCI bus reset&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x8
suffix:colon
id|printk
c_func
(paren
l_string|&quot;  - Watchdog reset&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x10
suffix:colon
id|printk
c_func
(paren
l_string|&quot;  - Software reset&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;  - Unknown reset cause&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|reset_reason
op_assign
id|tmpword
suffix:semicolon
id|OCELOT_FPGA_WRITE
c_func
(paren
l_int|0xff
comma
id|RESET_STATUS
)paren
suffix:semicolon
id|tmpword
op_assign
id|OCELOT_FPGA_READ
c_func
(paren
id|CPCI_ID
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cPCI ID register: 0x%02x&bslash;n&quot;
comma
id|tmpword
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  - Slot number: %d&bslash;n&quot;
comma
id|tmpword
op_amp
l_int|0x1f
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  - PCI bus present: %s&bslash;n&quot;
comma
id|tmpword
op_amp
l_int|0x40
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  - System Slot: %s&bslash;n&quot;
comma
id|tmpword
op_amp
l_int|0x20
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
)paren
suffix:semicolon
id|tmpword
op_assign
id|OCELOT_FPGA_READ
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
multiline_comment|/* 512MiB */
id|add_memory_region
c_func
(paren
l_int|0x0
comma
l_int|0x200
op_lshift
l_int|20
comma
id|BOOT_MEM_RAM
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* 256MiB */
id|add_memory_region
c_func
(paren
l_int|0x0
comma
l_int|0x100
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
multiline_comment|/* 128MiB */
id|add_memory_region
c_func
(paren
l_int|0x0
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
l_int|0
suffix:colon
multiline_comment|/* 1GiB -- needs CONFIG_HIGHMEM */
id|add_memory_region
c_func
(paren
l_int|0x0
comma
l_int|0x400
op_lshift
l_int|20
comma
id|BOOT_MEM_RAM
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
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
r_void
op_star
id|io_remap_range
op_assign
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
(brace
id|panic
c_func
(paren
l_string|&quot;Could not ioremap I/O port range&quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;io_remap_range set at 0x%08x&bslash;n&quot;
comma
(paren
r_uint32
)paren
id|io_remap_range
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
