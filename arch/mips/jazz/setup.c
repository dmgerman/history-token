multiline_comment|/*&n; * Setup pointers to hardware-dependent routines.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 1997, 1998, 2001 by Ralf Baechle&n; * Copyright (C) 2001 MIPS Technologies, Inc.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/eisa.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/jazz.h&gt;
macro_line|#include &lt;asm/jazzdma.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
r_extern
id|asmlinkage
r_void
id|jazz_handle_int
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|jazz_machine_restart
c_func
(paren
r_char
op_star
id|command
)paren
suffix:semicolon
r_extern
r_void
id|jazz_machine_halt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|jazz_machine_power_off
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|jazz_time_init
r_static
r_void
id|__init
id|jazz_time_init
c_func
(paren
r_struct
id|irqaction
op_star
id|irq
)paren
(brace
multiline_comment|/* set the clock to 100 Hz */
id|r4030_write_reg32
c_func
(paren
id|JAZZ_TIMER_INTERVAL
comma
l_int|9
)paren
suffix:semicolon
id|setup_irq
c_func
(paren
id|JAZZ_TIMER_IRQ
comma
id|irq
)paren
suffix:semicolon
)brace
DECL|variable|jazz_io_resources
r_static
r_struct
id|resource
id|jazz_io_resources
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;dma1&quot;
comma
l_int|0x00
comma
l_int|0x1f
comma
id|IORESOURCE_BUSY
)brace
comma
(brace
l_string|&quot;timer&quot;
comma
l_int|0x40
comma
l_int|0x5f
comma
id|IORESOURCE_BUSY
)brace
comma
(brace
l_string|&quot;dma page reg&quot;
comma
l_int|0x80
comma
l_int|0x8f
comma
id|IORESOURCE_BUSY
)brace
comma
(brace
l_string|&quot;dma2&quot;
comma
l_int|0xc0
comma
l_int|0xdf
comma
id|IORESOURCE_BUSY
)brace
comma
)brace
suffix:semicolon
DECL|function|jazz_setup
r_static
r_void
id|__init
id|jazz_setup
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* Map 0xe0000000 -&gt; 0x0:800005C0, 0xe0010000 -&gt; 0x1:30000580 */
id|add_wired_entry
(paren
l_int|0x02000017
comma
l_int|0x03c00017
comma
l_int|0xe0000000
comma
id|PM_64K
)paren
suffix:semicolon
multiline_comment|/* Map 0xe2000000 -&gt; 0x0:900005C0, 0xe3010000 -&gt; 0x0:910005C0 */
id|add_wired_entry
(paren
l_int|0x02400017
comma
l_int|0x02440017
comma
l_int|0xe2000000
comma
id|PM_16M
)paren
suffix:semicolon
multiline_comment|/* Map 0xe4000000 -&gt; 0x0:600005C0, 0xe4100000 -&gt; 400005C0 */
id|add_wired_entry
(paren
l_int|0x01800017
comma
l_int|0x01000017
comma
l_int|0xe4000000
comma
id|PM_4M
)paren
suffix:semicolon
id|set_io_port_base
c_func
(paren
id|JAZZ_PORT_BASE
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_EISA
r_if
c_cond
(paren
id|mips_machtype
op_eq
id|MACH_MIPS_MAGNUM_4000
)paren
id|EISA_bus
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
id|isa_slot_offset
op_assign
l_int|0xe3000000
suffix:semicolon
multiline_comment|/* request I/O space for devices used on all i[345]86 PCs */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ARRAY_SIZE
c_func
(paren
id|jazz_io_resources
)paren
suffix:semicolon
id|i
op_increment
)paren
id|request_resource
c_func
(paren
op_amp
id|ioport_resource
comma
id|jazz_io_resources
op_plus
id|i
)paren
suffix:semicolon
id|board_timer_setup
op_assign
id|jazz_time_init
suffix:semicolon
multiline_comment|/* The RTC is outside the port address space */
id|_machine_restart
op_assign
id|jazz_machine_restart
suffix:semicolon
id|_machine_halt
op_assign
id|jazz_machine_halt
suffix:semicolon
id|_machine_power_off
op_assign
id|jazz_machine_power_off
suffix:semicolon
macro_line|#warning &quot;Somebody should check if screen_info is ok for Jazz.&quot;
id|screen_info
op_assign
(paren
r_struct
id|screen_info
)paren
(brace
l_int|0
comma
l_int|0
comma
multiline_comment|/* orig-x, orig-y */
l_int|0
comma
multiline_comment|/* unused */
l_int|0
comma
multiline_comment|/* orig_video_page */
l_int|0
comma
multiline_comment|/* orig_video_mode */
l_int|160
comma
multiline_comment|/* orig_video_cols */
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* unused, ega_bx, unused */
l_int|64
comma
multiline_comment|/* orig_video_lines */
l_int|0
comma
multiline_comment|/* orig_video_isVGA */
l_int|16
multiline_comment|/* orig_video_points */
)brace
suffix:semicolon
id|vdma_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|jazz_setup
id|early_initcall
c_func
(paren
id|jazz_setup
)paren
suffix:semicolon
eof
