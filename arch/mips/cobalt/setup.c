multiline_comment|/*&n; * Setup pointers to hardware dependent routines.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 1997 by Ralf Baechle&n; * Copyright (C) 2001, 2002, 2003 by Liam Davies (ldavies@agile.tv)&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;asm/gt64120.h&gt;
macro_line|#include &lt;asm/cobalt/cobalt.h&gt;
r_extern
r_void
id|cobalt_machine_restart
c_func
(paren
r_char
op_star
id|command
)paren
suffix:semicolon
r_extern
r_void
id|cobalt_machine_halt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cobalt_machine_power_off
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|rtc_ops
id|std_rtc_ops
suffix:semicolon
r_extern
r_struct
id|ide_ops
id|std_ide_ops
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
macro_line|#ifdef CONFIG_IP_PNP
l_string|&quot;ip=on &quot;
macro_line|#endif
macro_line|#ifdef CONFIG_ROOT_NFS
l_string|&quot;root=/dev/nfs &quot;
macro_line|#else
l_string|&quot;root=/dev/hda1 &quot;
macro_line|#endif
)brace
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
l_string|&quot;MIPS Cobalt&quot;
suffix:semicolon
)brace
DECL|function|cobalt_time_init
r_static
r_void
id|__init
id|cobalt_time_init
c_func
(paren
r_void
)paren
(brace
id|rtc_ops
op_assign
op_amp
id|std_rtc_ops
suffix:semicolon
)brace
DECL|function|cobalt_timer_setup
r_static
r_void
id|__init
id|cobalt_timer_setup
c_func
(paren
r_struct
id|irqaction
op_star
id|irq
)paren
(brace
multiline_comment|/* Load timer value for 150 Hz */
id|GALILEO_OUTL
c_func
(paren
l_int|500000
comma
id|GT_TC0_OFS
)paren
suffix:semicolon
multiline_comment|/* Register our timer interrupt */
id|setup_irq
c_func
(paren
id|COBALT_TIMER_IRQ
comma
id|irq
)paren
suffix:semicolon
multiline_comment|/* Enable timer ints */
id|GALILEO_OUTL
c_func
(paren
(paren
id|GALILEO_ENTC0
op_or
id|GALILEO_SELTC0
)paren
comma
id|GT_TC_CONTROL_OFS
)paren
suffix:semicolon
multiline_comment|/* Unmask timer int */
id|GALILEO_OUTL
c_func
(paren
l_int|0x100
comma
id|GT_INTRMASK_OFS
)paren
suffix:semicolon
)brace
DECL|function|cobalt_setup
r_void
id|__init
id|cobalt_setup
c_func
(paren
r_void
)paren
(brace
id|_machine_restart
op_assign
id|cobalt_machine_restart
suffix:semicolon
id|_machine_halt
op_assign
id|cobalt_machine_halt
suffix:semicolon
id|_machine_power_off
op_assign
id|cobalt_machine_power_off
suffix:semicolon
id|board_time_init
op_assign
id|cobalt_time_init
suffix:semicolon
id|board_timer_setup
op_assign
id|cobalt_timer_setup
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_IDE
id|ide_ops
op_assign
op_amp
id|std_ide_ops
suffix:semicolon
macro_line|#endif
id|set_io_port_base
c_func
(paren
id|KSEG1ADDR
c_func
(paren
l_int|0x10000000
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This is a prom style console. We just poke at the&n;&t; *  UART to make it talk.&n;&t; * Only use this console if you really screw up and can&squot;t&n;&t; *  get to the stage of setting up a real serial console.&n;&t; */
multiline_comment|/*ns16550_setup_console();*/
)brace
multiline_comment|/* Prom init. We read our one and only communication with the&n;    firmware. Grab the amount of installed memory */
DECL|function|prom_init
r_void
id|__init
id|prom_init
c_func
(paren
r_int
id|argc
)paren
(brace
id|mips_machgroup
op_assign
id|MACH_GROUP_COBALT
suffix:semicolon
id|add_memory_region
c_func
(paren
l_int|0x0
comma
id|argc
op_amp
l_int|0x7fffffff
comma
id|BOOT_MEM_RAM
)paren
suffix:semicolon
)brace
DECL|function|prom_free_prom_memory
r_void
id|__init
id|prom_free_prom_memory
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Nothing to do! */
)brace
eof
