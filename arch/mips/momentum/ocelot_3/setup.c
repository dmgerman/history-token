multiline_comment|/*&n; * setup.c&n; *&n; * BRIEF MODULE DESCRIPTION&n; * Momentum Computer Ocelot-3 board dependent boot routines&n; *&n; * Copyright (C) 1996, 1997, 01, 05  Ralf Baechle&n; * Copyright (C) 2000 RidgeRun, Inc.&n; * Copyright (C) 2001 Red Hat, Inc.&n; * Copyright (C) 2002 Momentum Computer&n; *&n; * Author: Matthew Dharm, Momentum Computer&n; *   mdharm@momenco.com&n; *&n; * Louis Hamilton, Red Hat, Inc.&n; *   hamilton@redhat.com  [MIPS64 modifications]&n; *&n; * Author: RidgeRun, Inc.&n; *   glonnon@ridgerun.com, skranz@ridgerun.com, stevej@ridgerun.com&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: jsun@mvista.com or jsun@junsun.net&n; *&n; * Copyright 2004 PMC-Sierra&n; * Author: Manish Lachwani (lachwani@pmc-sierra.com)&n; *&n; * Copyright (C) 2004 MontaVista Software Inc.&n; * Author: Manish Lachwani, mlachwani@mvista.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/mv643xx.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/pci.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;asm/mc146818rtc.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &quot;ocelot_3_fpga.h&quot;
multiline_comment|/* Marvell Discovery Register Base */
DECL|variable|marvell_base
r_int
r_int
id|marvell_base
op_assign
(paren
r_int
)paren
l_int|0xf4000000
suffix:semicolon
multiline_comment|/* CPU clock */
DECL|variable|cpu_clock
r_int
r_int
id|cpu_clock
suffix:semicolon
multiline_comment|/* RTC/NVRAM */
DECL|variable|rtc_base
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
(paren
r_int
)paren
l_int|0xfc800000
suffix:semicolon
multiline_comment|/* FPGA Base */
DECL|variable|ocelot_fpga_base
r_int
r_int
id|ocelot_fpga_base
op_assign
(paren
r_int
)paren
l_int|0xfc000000
suffix:semicolon
multiline_comment|/* Serial base */
DECL|variable|uart_base
r_int
r_int
id|uart_base
op_assign
(paren
r_int
)paren
l_int|0xfd000000
suffix:semicolon
multiline_comment|/*&n; * Marvell Discovery SRAM. This is one place where Ethernet&n; * Tx and Rx descriptors can be placed to improve performance&n; */
r_extern
r_int
r_int
id|mv64340_sram_base
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
r_void
id|add_wired_entry
c_func
(paren
r_int
r_int
id|entrylo0
comma
r_int
r_int
id|entrylo1
comma
r_int
r_int
id|entryhi
comma
r_int
r_int
id|pagemask
)paren
suffix:semicolon
DECL|function|ENTRYLO
r_static
r_inline
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
DECL|function|bus_error_init
r_void
id|__init
id|bus_error_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* nothing */
)brace
multiline_comment|/*&n; * setup code for a handoff from a version 2 PMON 2000 PROM&n; */
DECL|function|setup_wired_tlb_entries
r_void
id|setup_wired_tlb_entries
c_func
(paren
r_void
)paren
(brace
id|write_c0_wired
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|local_flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
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
(paren
r_int
)paren
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
(paren
r_int
)paren
l_int|0xfc000000
comma
id|PM_16M
)paren
suffix:semicolon
)brace
DECL|macro|CONV_BCD_TO_BIN
mdefine_line|#define CONV_BCD_TO_BIN(val)&t;(((val) &amp; 0xf) + (((val) &gt;&gt; 4) * 10))
DECL|macro|CONV_BIN_TO_BCD
mdefine_line|#define CONV_BIN_TO_BCD(val)&t;(((val) % 10) + (((val) / 10) &lt;&lt; 4))
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
id|CONV_BCD_TO_BIN
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
id|CONV_BCD_TO_BIN
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
id|CONV_BCD_TO_BIN
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
id|CONV_BCD_TO_BIN
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
id|CONV_BCD_TO_BIN
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
id|CONV_BCD_TO_BIN
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
id|CONV_BCD_TO_BIN
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
id|CONV_BIN_TO_BCD
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
id|CONV_BIN_TO_BCD
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
id|CONV_BIN_TO_BCD
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
id|CONV_BIN_TO_BCD
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
id|CONV_BIN_TO_BCD
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
id|CONV_BIN_TO_BCD
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
id|CONV_BIN_TO_BCD
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
id|CONV_BIN_TO_BCD
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
multiline_comment|/* Timer interrupt, unmask status IM7 */
)brace
DECL|function|momenco_time_init
r_void
id|momenco_time_init
c_func
(paren
r_void
)paren
(brace
id|setup_wired_tlb_entries
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Ocelot-3 board has been built with both&n;&t; * the Rm7900 and the Rm7065C&n;&t; */
id|mips_hpt_frequency
op_assign
id|cpu_clock
op_div
l_int|2
suffix:semicolon
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
multiline_comment|/*&n; * PCI Support for Ocelot-3&n; */
multiline_comment|/* Bus #0 IO and MEM space */
DECL|macro|OCELOT_3_PCI_IO_0_START
mdefine_line|#define&t;OCELOT_3_PCI_IO_0_START&t;&t;0xe0000000
DECL|macro|OCELOT_3_PCI_IO_0_SIZE
mdefine_line|#define&t;OCELOT_3_PCI_IO_0_SIZE&t;&t;0x08000000
DECL|macro|OCELOT_3_PCI_MEM_0_START
mdefine_line|#define&t;OCELOT_3_PCI_MEM_0_START&t;0xc0000000
DECL|macro|OCELOT_3_PCI_MEM_0_SIZE
mdefine_line|#define&t;OCELOT_3_PCI_MEM_0_SIZE&t;&t;0x10000000
multiline_comment|/* Bus #1 IO and MEM space */
DECL|macro|OCELOT_3_PCI_IO_1_START
mdefine_line|#define&t;OCELOT_3_PCI_IO_1_START&t;&t;0xe8000000
DECL|macro|OCELOT_3_PCI_IO_1_SIZE
mdefine_line|#define&t;OCELOT_3_PCI_IO_1_SIZE&t;&t;0x08000000
DECL|macro|OCELOT_3_PCI_MEM_1_START
mdefine_line|#define&t;OCELOT_3_PCI_MEM_1_START&t;0xd0000000
DECL|macro|OCELOT_3_PCI_MEM_1_SIZE
mdefine_line|#define&t;OCELOT_3_PCI_MEM_1_SIZE&t;&t;0x10000000
DECL|variable|mv_pci_io_mem0_resource
r_static
r_struct
id|resource
id|mv_pci_io_mem0_resource
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;MV64340 PCI0 IO MEM&quot;
comma
dot
id|start
op_assign
id|OCELOT_3_PCI_IO_0_START
comma
dot
id|end
op_assign
id|OCELOT_3_PCI_IO_0_START
op_plus
id|OCELOT_3_PCI_IO_0_SIZE
op_minus
l_int|1
comma
dot
id|flags
op_assign
id|IORESOURCE_IO
comma
)brace
suffix:semicolon
DECL|variable|mv_pci_io_mem1_resource
r_static
r_struct
id|resource
id|mv_pci_io_mem1_resource
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;MV64340 PCI1 IO MEM&quot;
comma
dot
id|start
op_assign
id|OCELOT_3_PCI_IO_1_START
comma
dot
id|end
op_assign
id|OCELOT_3_PCI_IO_1_START
op_plus
id|OCELOT_3_PCI_IO_1_SIZE
op_minus
l_int|1
comma
dot
id|flags
op_assign
id|IORESOURCE_IO
comma
)brace
suffix:semicolon
DECL|variable|mv_pci_mem0_resource
r_static
r_struct
id|resource
id|mv_pci_mem0_resource
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;MV64340 PCI0 MEM&quot;
comma
dot
id|start
op_assign
id|OCELOT_3_PCI_MEM_0_START
comma
dot
id|end
op_assign
id|OCELOT_3_PCI_MEM_0_START
op_plus
id|OCELOT_3_PCI_MEM_0_SIZE
op_minus
l_int|1
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
suffix:semicolon
DECL|variable|mv_pci_mem1_resource
r_static
r_struct
id|resource
id|mv_pci_mem1_resource
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;MV64340 PCI1 MEM&quot;
comma
dot
id|start
op_assign
id|OCELOT_3_PCI_MEM_1_START
comma
dot
id|end
op_assign
id|OCELOT_3_PCI_MEM_1_START
op_plus
id|OCELOT_3_PCI_MEM_1_SIZE
op_minus
l_int|1
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
suffix:semicolon
DECL|variable|mv_bus0_controller
r_static
r_struct
id|mv_pci_controller
id|mv_bus0_controller
op_assign
(brace
dot
id|pcic
op_assign
(brace
dot
id|pci_ops
op_assign
op_amp
id|mv_pci_ops
comma
dot
id|mem_resource
op_assign
op_amp
id|mv_pci_mem0_resource
comma
dot
id|io_resource
op_assign
op_amp
id|mv_pci_io_mem0_resource
comma
)brace
comma
dot
id|config_addr
op_assign
id|MV64340_PCI_0_CONFIG_ADDR
comma
dot
id|config_vreg
op_assign
id|MV64340_PCI_0_CONFIG_DATA_VIRTUAL_REG
comma
)brace
suffix:semicolon
DECL|variable|mv_bus1_controller
r_static
r_struct
id|mv_pci_controller
id|mv_bus1_controller
op_assign
(brace
dot
id|pcic
op_assign
(brace
dot
id|pci_ops
op_assign
op_amp
id|mv_pci_ops
comma
dot
id|mem_resource
op_assign
op_amp
id|mv_pci_mem1_resource
comma
dot
id|io_resource
op_assign
op_amp
id|mv_pci_io_mem1_resource
comma
)brace
comma
dot
id|config_addr
op_assign
id|MV64340_PCI_1_CONFIG_ADDR
comma
dot
id|config_vreg
op_assign
id|MV64340_PCI_1_CONFIG_DATA_VIRTUAL_REG
comma
)brace
suffix:semicolon
DECL|function|ja_pci_init
r_static
id|__init
r_int
id|__init
id|ja_pci_init
c_func
(paren
r_void
)paren
(brace
r_uint32
id|enable
suffix:semicolon
r_extern
r_int
id|pci_probe_only
suffix:semicolon
multiline_comment|/* PMON will assign PCI resources */
id|pci_probe_only
op_assign
l_int|1
suffix:semicolon
id|enable
op_assign
op_complement
id|MV_READ
c_func
(paren
id|MV64340_BASE_ADDR_ENABLE
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We require at least one enabled I/O or PCI memory window or we&n;&t; * will ignore this PCI bus.  We ignore PCI windows 1, 2 and 3.&n;&t; */
r_if
c_cond
(paren
id|enable
op_amp
(paren
l_int|0x01
op_lshift
l_int|9
)paren
op_logical_or
id|enable
op_amp
(paren
l_int|0x01
op_lshift
l_int|10
)paren
)paren
id|register_pci_controller
c_func
(paren
op_amp
id|mv_bus0_controller.pcic
)paren
suffix:semicolon
r_if
c_cond
(paren
id|enable
op_amp
(paren
l_int|0x01
op_lshift
l_int|14
)paren
op_logical_or
id|enable
op_amp
(paren
l_int|0x01
op_lshift
l_int|15
)paren
)paren
id|register_pci_controller
c_func
(paren
op_amp
id|mv_bus1_controller.pcic
)paren
suffix:semicolon
id|ioport_resource.end
op_assign
id|OCELOT_3_PCI_IO_0_START
op_plus
id|OCELOT_3_PCI_IO_0_SIZE
op_plus
id|OCELOT_3_PCI_IO_1_SIZE
op_minus
l_int|1
suffix:semicolon
id|iomem_resource.end
op_assign
id|OCELOT_3_PCI_MEM_0_START
op_plus
id|OCELOT_3_PCI_MEM_0_SIZE
op_plus
id|OCELOT_3_PCI_MEM_1_SIZE
op_minus
l_int|1
suffix:semicolon
id|set_io_port_base
c_func
(paren
id|OCELOT_3_PCI_IO_0_START
)paren
suffix:semicolon
multiline_comment|/* mips_io_port_base */
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ja_pci_init
id|arch_initcall
c_func
(paren
id|ja_pci_init
)paren
suffix:semicolon
DECL|function|momenco_ocelot_3_setup
r_static
r_int
id|__init
id|momenco_ocelot_3_setup
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
multiline_comment|/* Wired TLB entries */
id|setup_wired_tlb_entries
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
id|MV_READ
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
id|MV_READ
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
id|MV_READ
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
id|MV_READ
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
id|MV_READ
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
id|MV_READ
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
l_string|&quot;Momenco Ocelot-3: Board Assembly Rev. %c&bslash;n&quot;
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
l_string|&quot;Momenco Ocelot-3: Board Assembly Revision #0x%x&bslash;n&quot;
comma
id|tmpword
)paren
suffix:semicolon
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
l_string|&quot;  - L3 cache size: %d MB&bslash;n&quot;
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
multiline_comment|/* Support for 128 MB memory */
id|add_memory_region
c_func
(paren
l_int|0x0
comma
l_int|0x08000000
comma
id|BOOT_MEM_RAM
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|momenco_ocelot_3_setup
id|early_initcall
c_func
(paren
id|momenco_ocelot_3_setup
)paren
suffix:semicolon
eof
