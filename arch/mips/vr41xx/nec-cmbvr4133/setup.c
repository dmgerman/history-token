multiline_comment|/*&n; * arch/mips/vr41xx/nec-cmbvr4133/setup.c&n; *&n; * Setup for the NEC CMB-VR4133.&n; *&n; * Author: Yoichi Yuasa &lt;yyuasa@mvista.com, or source@mvista.com&gt; and&n; *         Alex Sapkov &lt;asapkov@ru.mvista.com&gt;&n; *&n; * 2001-2004 (c) MontaVista, Software, Inc. This file is licensed under&n; * the terms of the GNU General Public License version 2. This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; *&n; * Support for CMBVR4133 board in 2.6&n; * Author: Manish Lachwani (mlachwani@mvista.com)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/vr41xx/cmbvr4133.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#ifdef CONFIG_MTD
macro_line|#include &lt;linux/mtd/physmap.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
DECL|variable|cmbvr4133_mtd_parts
r_static
r_struct
id|mtd_partition
id|cmbvr4133_mtd_parts
(braket
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;User FS&quot;
comma
dot
id|size
op_assign
l_int|0x1be0000
comma
dot
id|offset
op_assign
l_int|0
comma
dot
id|mask_flags
op_assign
l_int|0
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;PMON&quot;
comma
dot
id|size
op_assign
l_int|0x140000
comma
dot
id|offset
op_assign
id|MTDPART_OFS_APPEND
comma
dot
id|mask_flags
op_assign
id|MTD_WRITEABLE
comma
multiline_comment|/* force read-only */
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;User FS2&quot;
comma
dot
id|size
op_assign
id|MTDPART_SIZ_FULL
comma
dot
id|offset
op_assign
id|MTDPART_OFS_APPEND
comma
dot
id|mask_flags
op_assign
l_int|0
comma
)brace
)brace
suffix:semicolon
DECL|macro|number_partitions
mdefine_line|#define number_partitions (sizeof(cmbvr4133_mtd_parts)/sizeof(struct mtd_partition))
macro_line|#endif
r_extern
r_void
(paren
op_star
id|late_time_init
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|function|vr4133_serial_init
r_static
r_void
id|__init
id|vr4133_serial_init
c_func
(paren
r_void
)paren
(brace
id|vr41xx_select_siu_interface
c_func
(paren
id|SIU_RS232C
comma
id|IRDA_NONE
)paren
suffix:semicolon
id|vr41xx_siu_init
c_func
(paren
)paren
suffix:semicolon
id|vr41xx_dsiu_init
c_func
(paren
)paren
suffix:semicolon
)brace
r_extern
r_void
id|i8259_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|nec_cmbvr4133_setup
r_static
r_int
id|__init
id|nec_cmbvr4133_setup
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_ROCKHOPPER
r_extern
r_void
id|disable_pcnet
c_func
(paren
r_void
)paren
suffix:semicolon
id|disable_pcnet
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|set_io_port_base
c_func
(paren
id|KSEG1ADDR
c_func
(paren
l_int|0x16000000
)paren
)paren
suffix:semicolon
id|mips_machgroup
op_assign
id|MACH_GROUP_NEC_VR41XX
suffix:semicolon
id|mips_machtype
op_assign
id|MACH_NEC_CMBVR4133
suffix:semicolon
id|late_time_init
op_assign
id|vr4133_serial_init
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
macro_line|#ifdef CONFIG_ROCKHOPPER
id|ali_m5229_preinit
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
macro_line|#ifdef CONFIG_ROCKHOPPER
id|rockhopper_init_irq
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MTD
multiline_comment|/* we use generic physmap mapping driver and we use partitions */
id|physmap_configure
c_func
(paren
l_int|0x1C000000
comma
l_int|0x02000000
comma
l_int|4
comma
l_int|NULL
)paren
suffix:semicolon
id|physmap_set_partitions
c_func
(paren
id|cmbvr4133_mtd_parts
comma
id|number_partitions
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* 128 MB memory support */
id|add_memory_region
c_func
(paren
l_int|0
comma
l_int|0x08000000
comma
id|BOOT_MEM_RAM
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ROCKHOPPER
id|i8259_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|nec_cmbvr4133_setup
id|early_initcall
c_func
(paren
id|nec_cmbvr4133_setup
)paren
suffix:semicolon
eof
