multiline_comment|/*    $Id: setup.c,v 1.8 2000/02/02 04:42:38 prumpf Exp $&n; *&n; *    Initial setup-routines for HP 9000 based hardware.&n; *&n; *    Copyright (C) 1991, 1992, 1995  Linus Torvalds&n; *    Modifications for PA-RISC (C) 1999 Helge Deller &lt;deller@gmx.de&gt;&n; *    Modifications copyright 1999 SuSE GmbH (Philipp Rumpf)&n; *    Modifications copyright 2000 Martin K. Petersen &lt;mkp@mkp.net&gt;&n; *    Modifications copyright 2000 Philipp Rumpf &lt;prumpf@tux.org&gt;&n; *    Modifications copyright 2001 Ryan Bradetich &lt;rbradetich@uswest.net&gt;&n; *&n; *    Initial PA-RISC Version: 04-23-1999 by Helge Deller&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2, or (at your option)&n; *    any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *    GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
DECL|macro|PCI_DEBUG
mdefine_line|#define PCI_DEBUG
macro_line|#include &lt;linux/pci.h&gt;
DECL|macro|PCI_DEBUG
macro_line|#undef PCI_DEBUG
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/pdc.h&gt;
macro_line|#include &lt;asm/led.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;&t;/* for pa7300lc_init() proto */
macro_line|#include &lt;asm/pdc_chassis.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|COMMAND_LINE_SIZE
mdefine_line|#define COMMAND_LINE_SIZE 1024
DECL|variable|saved_command_line
r_char
id|saved_command_line
(braket
id|COMMAND_LINE_SIZE
)braket
suffix:semicolon
DECL|variable|command_line
r_char
id|command_line
(braket
id|COMMAND_LINE_SIZE
)braket
suffix:semicolon
multiline_comment|/* Intended for ccio/sba/cpu statistics under /proc/bus/{runway|gsc} */
DECL|variable|proc_runway_root
r_struct
id|proc_dir_entry
op_star
id|proc_runway_root
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|proc_gsc_root
r_struct
id|proc_dir_entry
op_star
id|proc_gsc_root
op_assign
l_int|NULL
suffix:semicolon
DECL|function|setup_cmdline
r_void
id|__init
id|setup_cmdline
c_func
(paren
r_char
op_star
op_star
id|cmdline_p
)paren
(brace
r_extern
r_int
r_int
id|boot_args
(braket
)braket
suffix:semicolon
multiline_comment|/* Collect stuff passed in from the boot loader */
multiline_comment|/* boot_args[0] is free-mem start, boot_args[1] is ptr to command line */
r_if
c_cond
(paren
id|boot_args
(braket
l_int|0
)braket
OL
l_int|64
)paren
(brace
multiline_comment|/* called from hpux boot loader */
id|saved_command_line
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
r_else
(brace
id|strcpy
c_func
(paren
id|saved_command_line
comma
(paren
r_char
op_star
)paren
id|__va
c_func
(paren
id|boot_args
(braket
l_int|1
)braket
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
id|boot_args
(braket
l_int|2
)braket
op_ne
l_int|0
)paren
multiline_comment|/* did palo pass us a ramdisk? */
(brace
id|initrd_start
op_assign
(paren
r_int
r_int
)paren
id|__va
c_func
(paren
id|boot_args
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|initrd_end
op_assign
(paren
r_int
r_int
)paren
id|__va
c_func
(paren
id|boot_args
(braket
l_int|3
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
id|strcpy
c_func
(paren
id|command_line
comma
id|saved_command_line
)paren
suffix:semicolon
op_star
id|cmdline_p
op_assign
id|command_line
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PA11
DECL|function|dma_ops_init
r_void
id|__init
id|dma_ops_init
c_func
(paren
r_void
)paren
(brace
r_switch
c_cond
(paren
id|boot_cpu_data.cpu_type
)paren
(brace
r_case
id|pcx
suffix:colon
multiline_comment|/*&n;&t;&t; * We&squot;ve got way too many dependencies on 1.1 semantics&n;&t;&t; * to support 1.0 boxes at this point.&n;&t;&t; */
id|panic
c_func
(paren
l_string|&quot;PA-RISC Linux currently only supports machines that conform to&bslash;n&quot;
l_string|&quot;the PA-RISC 1.1 or 2.0 architecture specification.&bslash;n&quot;
)paren
suffix:semicolon
r_case
id|pcxs
suffix:colon
r_case
id|pcxt
suffix:colon
id|hppa_dma_ops
op_assign
op_amp
id|pcx_dma_ops
suffix:semicolon
r_break
suffix:semicolon
r_case
id|pcxl2
suffix:colon
id|pa7300lc_init
c_func
(paren
)paren
suffix:semicolon
r_case
id|pcxl
suffix:colon
multiline_comment|/* falls through */
id|hppa_dma_ops
op_assign
op_amp
id|pcxl_dma_ops
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
macro_line|#endif
r_extern
r_int
id|init_per_cpu
c_func
(paren
r_int
id|cpuid
)paren
suffix:semicolon
r_extern
r_void
id|collect_boot_cpu_data
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|setup_arch
r_void
id|__init
id|setup_arch
c_func
(paren
r_char
op_star
op_star
id|cmdline_p
)paren
(brace
id|init_per_cpu
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Set Modes &amp; Enable FP */
macro_line|#ifdef __LP64__
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;The 64-bit Kernel has started...&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;The 32-bit Kernel has started...&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|pdc_console_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PDC_NARROW
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Kernel is using PDC in 32-bit mode.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|setup_pdc
c_func
(paren
)paren
suffix:semicolon
id|setup_cmdline
c_func
(paren
id|cmdline_p
)paren
suffix:semicolon
id|collect_boot_cpu_data
c_func
(paren
)paren
suffix:semicolon
id|do_memory_inventory
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* probe for physical memory */
id|parisc_cache_init
c_func
(paren
)paren
suffix:semicolon
id|paging_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CHASSIS_LCD_LED
multiline_comment|/* initialize the LCD/LED after boot_cpu_data is available ! */
id|led_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* LCD/LED initialization */
macro_line|#endif
macro_line|#ifdef CONFIG_PA11
id|dma_ops_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_VT) &amp;&amp; defined(CONFIG_DUMMY_CONSOLE)
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
multiline_comment|/* we use take_over_console() later ! */
macro_line|#endif
)brace
multiline_comment|/*&n; * Display cpu info for all cpu&squot;s.&n; * for parisc this is in processor.c&n; */
r_extern
r_int
id|show_cpuinfo
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
suffix:semicolon
r_static
r_void
op_star
DECL|function|c_start
id|c_start
(paren
r_struct
id|seq_file
op_star
id|m
comma
id|loff_t
op_star
id|pos
)paren
(brace
multiline_comment|/* Looks like the caller will call repeatedly until we return&n;&t; * 0, signaling EOF perhaps.  This could be used to sequence&n;&t; * through CPUs for example.  Since we print all cpu info in our&n;&t; * show_cpuinfo() disregarding &squot;pos&squot; (which I assume is &squot;v&squot; above)&n;&t; * we only allow for one &quot;position&quot;.  */
r_return
(paren
(paren
r_int
)paren
op_star
id|pos
OL
l_int|1
)paren
ques
c_cond
(paren
r_void
op_star
)paren
l_int|1
suffix:colon
l_int|NULL
suffix:semicolon
)brace
r_static
r_void
op_star
DECL|function|c_next
id|c_next
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
comma
id|loff_t
op_star
id|pos
)paren
(brace
op_increment
op_star
id|pos
suffix:semicolon
r_return
id|c_start
c_func
(paren
id|m
comma
id|pos
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|c_stop
id|c_stop
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
(brace
)brace
DECL|variable|cpuinfo_op
r_struct
id|seq_operations
id|cpuinfo_op
op_assign
(brace
dot
id|start
op_assign
id|c_start
comma
dot
id|next
op_assign
id|c_next
comma
dot
id|stop
op_assign
id|c_stop
comma
dot
id|show
op_assign
id|show_cpuinfo
)brace
suffix:semicolon
DECL|function|parisc_proc_mkdir
r_static
r_void
id|__init
id|parisc_proc_mkdir
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t;** Can&squot;t call proc_mkdir() until after proc_root_init() has been&n;&t;** called by start_kernel(). In other words, this code can&squot;t&n;&t;** live in arch/.../setup.c because start_parisc() calls&n;&t;** start_kernel().&n;&t;*/
r_switch
c_cond
(paren
id|boot_cpu_data.cpu_type
)paren
(brace
r_case
id|pcxl
suffix:colon
r_case
id|pcxl2
suffix:colon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|proc_gsc_root
)paren
(brace
id|proc_gsc_root
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;bus/gsc&quot;
comma
l_int|0
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|pcxt_
suffix:colon
r_case
id|pcxu
suffix:colon
r_case
id|pcxu_
suffix:colon
r_case
id|pcxw
suffix:colon
r_case
id|pcxw_
suffix:colon
r_case
id|pcxw2
suffix:colon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|proc_runway_root
)paren
(brace
id|proc_runway_root
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;bus/runway&quot;
comma
l_int|0
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* FIXME: this was added to prevent the compiler &n;&t;&t; * complaining about missing pcx, pcxs and pcxt&n;&t;&t; * I&squot;m assuming they have neither gsc nor runway */
r_break
suffix:semicolon
)brace
)brace
DECL|variable|central_bus
r_static
r_struct
id|resource
id|central_bus
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Central Bus&quot;
comma
dot
id|start
op_assign
id|F_EXTEND
c_func
(paren
l_int|0xfff80000
)paren
comma
dot
id|end
op_assign
id|F_EXTEND
c_func
(paren
l_int|0xfffaffff
)paren
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
suffix:semicolon
DECL|variable|local_broadcast
r_static
r_struct
id|resource
id|local_broadcast
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Local Broadcast&quot;
comma
dot
id|start
op_assign
id|F_EXTEND
c_func
(paren
l_int|0xfffb0000
)paren
comma
dot
id|end
op_assign
id|F_EXTEND
c_func
(paren
l_int|0xfffdffff
)paren
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
suffix:semicolon
DECL|variable|global_broadcast
r_static
r_struct
id|resource
id|global_broadcast
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Global Broadcast&quot;
comma
dot
id|start
op_assign
id|F_EXTEND
c_func
(paren
l_int|0xfffe0000
)paren
comma
dot
id|end
op_assign
id|F_EXTEND
c_func
(paren
l_int|0xffffffff
)paren
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
suffix:semicolon
DECL|function|parisc_init_resources
r_static
r_int
id|__init
id|parisc_init_resources
c_func
(paren
r_void
)paren
(brace
r_int
id|result
suffix:semicolon
id|result
op_assign
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|central_bus
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: failed to claim %s address space!&bslash;n&quot;
comma
id|__FILE__
comma
id|central_bus.name
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
id|result
op_assign
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|local_broadcast
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: failed to claim %saddress space!&bslash;n&quot;
comma
id|__FILE__
comma
id|local_broadcast.name
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
id|result
op_assign
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|global_broadcast
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: failed to claim %s address space!&bslash;n&quot;
comma
id|__FILE__
comma
id|global_broadcast.name
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_extern
r_void
id|gsc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|processor_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ccio_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|hppb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|dino_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|iosapic_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|lba_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sba_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|eisa_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|parisc_init
r_static
r_int
id|__init
id|parisc_init
c_func
(paren
r_void
)paren
(brace
id|parisc_proc_mkdir
c_func
(paren
)paren
suffix:semicolon
id|parisc_init_resources
c_func
(paren
)paren
suffix:semicolon
id|do_device_inventory
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* probe for hardware */
id|parisc_pdc_chassis_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* set up a new led state on systems shipped LED State panel */
id|pdc_chassis_send_status
c_func
(paren
id|PDC_CHASSIS_DIRECT_BSTART
)paren
suffix:semicolon
id|processor_init
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;CPU(s): %d x %s at %d.%06d MHz&bslash;n&quot;
comma
id|boot_cpu_data.cpu_count
comma
id|boot_cpu_data.cpu_name
comma
id|boot_cpu_data.cpu_hz
op_div
l_int|1000000
comma
id|boot_cpu_data.cpu_hz
op_mod
l_int|1000000
)paren
suffix:semicolon
multiline_comment|/* These are in a non-obvious order, will fix when we have an iotree */
macro_line|#if defined(CONFIG_IOSAPIC)
id|iosapic_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_IOMMU_SBA)
id|sba_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_PCI_LBA)
id|lba_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* CCIO before any potential subdevices */
macro_line|#if defined(CONFIG_IOMMU_CCIO)
id|ccio_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Need to register Asp &amp; Wax before the EISA adapters for the IRQ&n;&t; * regions.  EISA must come before PCI to be sure it gets IRQ region&n;&t; * 0.&n;&t; */
macro_line|#if defined(CONFIG_GSC_LASI) || defined(CONFIG_GSC_WAX)
id|gsc_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_EISA
id|eisa_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_HPPB)
id|hppb_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_GSC_DINO)
id|dino_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_CHASSIS_LCD_LED
id|register_led_regions
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* register LED port info in procfs */
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|parisc_init
id|arch_initcall
c_func
(paren
id|parisc_init
)paren
suffix:semicolon
eof
