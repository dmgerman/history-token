multiline_comment|/*&n; * Setup pointers to hardware-dependent routines.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 1997, 1998, 2000 by Ralf Baechle&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/pc_keyb.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/bcache.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/keyboard.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;asm/sni.h&gt;
r_extern
r_void
id|sni_machine_restart
c_func
(paren
r_char
op_star
id|command
)paren
suffix:semicolon
r_extern
r_void
id|sni_machine_halt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sni_machine_power_off
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|ide_ops
id|std_ide_ops
suffix:semicolon
r_extern
r_struct
id|rtc_ops
id|std_rtc_ops
suffix:semicolon
r_extern
r_struct
id|kbd_ops
id|std_kbd_ops
suffix:semicolon
DECL|variable|board_time_init
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
DECL|function|sni_rm200_pci_time_init
r_static
r_void
id|__init
id|sni_rm200_pci_time_init
c_func
(paren
r_struct
id|irqaction
op_star
id|irq
)paren
(brace
multiline_comment|/* set the clock to 100 Hz */
id|outb_p
c_func
(paren
l_int|0x34
comma
l_int|0x43
)paren
suffix:semicolon
multiline_comment|/* binary, mode 2, LSB/MSB, ch 0 */
id|outb_p
c_func
(paren
id|LATCH
op_amp
l_int|0xff
comma
l_int|0x40
)paren
suffix:semicolon
multiline_comment|/* LSB */
id|outb
c_func
(paren
id|LATCH
op_rshift
l_int|8
comma
l_int|0x40
)paren
suffix:semicolon
multiline_comment|/* MSB */
id|setup_irq
c_func
(paren
l_int|0
comma
id|irq
)paren
suffix:semicolon
)brace
DECL|variable|aux_device_present
r_int
r_char
id|aux_device_present
suffix:semicolon
r_extern
r_int
r_char
id|sni_map_isa_cache
suffix:semicolon
multiline_comment|/*&n; * A bit more gossip about the iron we&squot;re running on ...&n; */
DECL|function|sni_pcimt_detect
r_static
r_inline
r_void
id|sni_pcimt_detect
c_func
(paren
r_void
)paren
(brace
r_char
id|boardtype
(braket
l_int|80
)braket
suffix:semicolon
r_int
r_char
id|csmsr
suffix:semicolon
r_char
op_star
id|p
op_assign
id|boardtype
suffix:semicolon
r_int
r_int
id|asic
suffix:semicolon
id|csmsr
op_assign
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|PCIMT_CSMSR
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;%s PCI&quot;
comma
(paren
id|csmsr
op_amp
l_int|0x80
)paren
ques
c_cond
l_string|&quot;RM200&quot;
suffix:colon
l_string|&quot;RM300&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|csmsr
op_amp
l_int|0x80
)paren
op_eq
l_int|0
)paren
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;, board revision %s&quot;
comma
(paren
id|csmsr
op_amp
l_int|0x20
)paren
ques
c_cond
l_string|&quot;D&quot;
suffix:colon
l_string|&quot;C&quot;
)paren
suffix:semicolon
id|asic
op_assign
id|csmsr
op_amp
l_int|0x80
suffix:semicolon
id|asic
op_assign
(paren
id|csmsr
op_amp
l_int|0x08
)paren
ques
c_cond
id|asic
suffix:colon
op_logical_neg
id|asic
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;, ASIC PCI Rev %s&quot;
comma
id|asic
ques
c_cond
l_string|&quot;1.0&quot;
suffix:colon
l_string|&quot;1.1&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s.&bslash;n&quot;
comma
id|boardtype
)paren
suffix:semicolon
)brace
DECL|function|sni_rm200_pci_setup
r_void
id|__init
id|sni_rm200_pci_setup
c_func
(paren
r_void
)paren
(brace
id|sni_pcimt_detect
c_func
(paren
)paren
suffix:semicolon
id|sni_pcimt_sc_init
c_func
(paren
)paren
suffix:semicolon
id|mips_io_port_base
op_assign
id|SNI_PORT_BASE
suffix:semicolon
multiline_comment|/*&n;&t; * Setup (E)ISA I/O memory access stuff&n;&t; */
id|isa_slot_offset
op_assign
l_int|0xb0000000
suffix:semicolon
singleline_comment|// sni_map_isa_cache = 0;
id|EISA_bus
op_assign
l_int|1
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x00
comma
l_int|0x20
comma
l_string|&quot;dma1&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x40
comma
l_int|0x20
comma
l_string|&quot;timer&quot;
)paren
suffix:semicolon
multiline_comment|/* XXX FIXME: CONFIG_RTC */
id|request_region
c_func
(paren
l_int|0x70
comma
l_int|0x10
comma
l_string|&quot;rtc&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x80
comma
l_int|0x10
comma
l_string|&quot;dma page reg&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0xc0
comma
l_int|0x20
comma
l_string|&quot;dma2&quot;
)paren
suffix:semicolon
id|board_time_init
op_assign
id|sni_rm200_pci_time_init
suffix:semicolon
id|_machine_restart
op_assign
id|sni_machine_restart
suffix:semicolon
id|_machine_halt
op_assign
id|sni_machine_halt
suffix:semicolon
id|_machine_power_off
op_assign
id|sni_machine_power_off
suffix:semicolon
id|aux_device_present
op_assign
l_int|0xaa
suffix:semicolon
multiline_comment|/*&n;&t; * Some cluefull person has placed the PCI config data directly in&n;&t; * the I/O port space ...&n;&t; */
id|request_region
c_func
(paren
l_int|0xcfc
comma
l_int|0x04
comma
l_string|&quot;PCI config data&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_IDE
id|ide_ops
op_assign
op_amp
id|std_ide_ops
suffix:semicolon
macro_line|#endif
id|conswitchp
op_assign
op_amp
id|vga_con
suffix:semicolon
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
l_int|52
comma
multiline_comment|/* orig_video_page */
l_int|3
comma
multiline_comment|/* orig_video_mode */
l_int|80
comma
multiline_comment|/* orig_video_cols */
l_int|4626
comma
l_int|3
comma
l_int|9
comma
multiline_comment|/* unused, ega_bx, unused */
l_int|50
comma
multiline_comment|/* orig_video_lines */
l_int|0x22
comma
multiline_comment|/* orig_video_isVGA */
l_int|16
multiline_comment|/* orig_video_points */
)brace
suffix:semicolon
id|rtc_ops
op_assign
op_amp
id|std_rtc_ops
suffix:semicolon
id|kbd_ops
op_assign
op_amp
id|std_kbd_ops
suffix:semicolon
macro_line|#ifdef CONFIG_PSMOUSE
id|aux_device_present
op_assign
l_int|0xaa
suffix:semicolon
macro_line|#endif
)brace
eof
