multiline_comment|/*&n; * ichxrom.c&n; *&n; * Normal mappings of chips in physical memory&n; * $Id: ichxrom.c,v 1.7 2004/07/14 18:14:09 eric Exp $&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/pci_ids.h&gt;
macro_line|#include &lt;linux/mtd/cfi.h&gt;
DECL|macro|xstr
mdefine_line|#define xstr(s) str(s)
DECL|macro|str
mdefine_line|#define str(s) #s
DECL|macro|MOD_NAME
mdefine_line|#define MOD_NAME xstr(KBUILD_BASENAME)
DECL|macro|MTD_DEV_NAME_LENGTH
mdefine_line|#define MTD_DEV_NAME_LENGTH 16
DECL|macro|RESERVE_MEM_REGION
mdefine_line|#define RESERVE_MEM_REGION 0
DECL|macro|MANUFACTURER_INTEL
mdefine_line|#define MANUFACTURER_INTEL&t;0x0089
DECL|macro|I82802AB
mdefine_line|#define I82802AB&t;0x00ad
DECL|macro|I82802AC
mdefine_line|#define I82802AC&t;0x00ac
DECL|macro|ICHX_FWH_REGION_START
mdefine_line|#define ICHX_FWH_REGION_START&t;0xFF000000UL
DECL|macro|ICHX_FWH_REGION_SIZE
mdefine_line|#define ICHX_FWH_REGION_SIZE&t;0x01000000UL
DECL|macro|BIOS_CNTL
mdefine_line|#define BIOS_CNTL&t;0x4e
DECL|macro|FWH_DEC_EN1
mdefine_line|#define FWH_DEC_EN1&t;0xE3
DECL|macro|FWH_DEC_EN2
mdefine_line|#define FWH_DEC_EN2&t;0xF0
DECL|macro|FWH_SEL1
mdefine_line|#define FWH_SEL1&t;0xE8
DECL|macro|FWH_SEL2
mdefine_line|#define FWH_SEL2&t;0xEE
DECL|struct|ichxrom_map_info
r_struct
id|ichxrom_map_info
(brace
DECL|member|map
r_struct
id|map_info
id|map
suffix:semicolon
DECL|member|mtd
r_struct
id|mtd_info
op_star
id|mtd
suffix:semicolon
DECL|member|window_addr
r_int
r_int
id|window_addr
suffix:semicolon
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
DECL|member|window_rsrc
r_struct
id|resource
id|window_rsrc
suffix:semicolon
DECL|member|rom_rsrc
r_struct
id|resource
id|rom_rsrc
suffix:semicolon
DECL|member|mtd_name
r_char
id|mtd_name
(braket
id|MTD_DEV_NAME_LENGTH
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|addr
r_static
r_inline
r_int
r_int
id|addr
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_int
r_int
id|ofs
)paren
(brace
r_int
r_int
id|offset
suffix:semicolon
id|offset
op_assign
(paren
(paren
l_int|8
op_star
l_int|1024
op_star
l_int|1024
)paren
op_minus
id|map-&gt;size
)paren
op_plus
id|ofs
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
(paren
l_int|4
op_star
l_int|1024
op_star
l_int|1024
)paren
)paren
(brace
id|offset
op_add_assign
l_int|0x400000
suffix:semicolon
)brace
r_return
id|map-&gt;map_priv_1
op_plus
l_int|0x400000
op_plus
id|offset
suffix:semicolon
)brace
DECL|function|dbg_addr
r_static
r_inline
r_int
r_int
id|dbg_addr
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_int
r_int
id|addr
)paren
(brace
r_return
id|addr
op_minus
id|map-&gt;map_priv_1
op_plus
id|ICHX_FWH_REGION_START
suffix:semicolon
)brace
DECL|function|ichxrom_read
r_static
id|map_word
id|ichxrom_read
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_int
r_int
id|ofs
)paren
(brace
id|map_word
id|val
suffix:semicolon
r_int
id|i
suffix:semicolon
r_switch
c_cond
(paren
id|map-&gt;bankwidth
)paren
(brace
r_case
l_int|1
suffix:colon
id|val.x
(braket
l_int|0
)braket
op_assign
id|__raw_readb
c_func
(paren
id|addr
c_func
(paren
id|map
comma
id|ofs
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|val.x
(braket
l_int|0
)braket
op_assign
id|__raw_readw
c_func
(paren
id|addr
c_func
(paren
id|map
comma
id|ofs
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|val.x
(braket
l_int|0
)braket
op_assign
id|__raw_readl
c_func
(paren
id|addr
c_func
(paren
id|map
comma
id|ofs
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#if BITS_PER_LONG &gt;= 64
r_case
l_int|8
suffix:colon
id|val.x
(braket
l_int|0
)braket
op_assign
id|__raw_readq
c_func
(paren
id|addr
c_func
(paren
id|map
comma
id|ofs
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
id|val.x
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|map_words
c_func
(paren
id|map
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|val.x
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|val
suffix:semicolon
)brace
DECL|function|ichxrom_copy_from
r_static
r_void
id|ichxrom_copy_from
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_void
op_star
id|to
comma
r_int
r_int
id|from
comma
id|ssize_t
id|len
)paren
(brace
id|memcpy_fromio
c_func
(paren
id|to
comma
id|addr
c_func
(paren
id|map
comma
id|from
)paren
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|ichxrom_write
r_static
r_void
id|ichxrom_write
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
id|map_word
id|d
comma
r_int
r_int
id|ofs
)paren
(brace
r_switch
c_cond
(paren
id|map-&gt;bankwidth
)paren
(brace
r_case
l_int|1
suffix:colon
id|__raw_writeb
c_func
(paren
id|d.x
(braket
l_int|0
)braket
comma
id|addr
c_func
(paren
id|map
comma
id|ofs
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|__raw_writew
c_func
(paren
id|d.x
(braket
l_int|0
)braket
comma
id|addr
c_func
(paren
id|map
comma
id|ofs
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|__raw_writel
c_func
(paren
id|d.x
(braket
l_int|0
)braket
comma
id|addr
c_func
(paren
id|map
comma
id|ofs
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#if BITS_PER_LONG &gt;= 64
r_case
l_int|8
suffix:colon
id|__raw_writeq
c_func
(paren
id|d.x
(braket
l_int|0
)braket
comma
id|addr
c_func
(paren
id|map
comma
id|ofs
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
)brace
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|ichxrom_copy_to
r_static
r_void
id|ichxrom_copy_to
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_int
r_int
id|to
comma
r_const
r_void
op_star
id|from
comma
id|ssize_t
id|len
)paren
(brace
id|memcpy_toio
c_func
(paren
id|addr
c_func
(paren
id|map
comma
id|to
)paren
comma
id|from
comma
id|len
)paren
suffix:semicolon
)brace
DECL|variable|ichxrom_map
r_static
r_struct
id|ichxrom_map_info
id|ichxrom_map
op_assign
(brace
dot
id|map
op_assign
(brace
dot
id|name
op_assign
id|MOD_NAME
comma
dot
id|phys
op_assign
id|NO_XIP
comma
dot
id|size
op_assign
l_int|0
comma
dot
id|bankwidth
op_assign
l_int|1
comma
dot
id|read
op_assign
id|ichxrom_read
comma
dot
id|copy_from
op_assign
id|ichxrom_copy_from
comma
dot
id|write
op_assign
id|ichxrom_write
comma
dot
id|copy_to
op_assign
id|ichxrom_copy_to
comma
multiline_comment|/* Firmware hubs only use vpp when being programmed&n;&t;&t; * in a factory setting.  So in-place programming&n;&t;&t; * needs to use a different method.&n;&t;&t; */
)brace
comma
multiline_comment|/* remaining fields of structure are initialized to 0 */
)brace
suffix:semicolon
DECL|enum|fwh_lock_state
r_enum
id|fwh_lock_state
(brace
DECL|enumerator|FWH_DENY_WRITE
id|FWH_DENY_WRITE
op_assign
l_int|1
comma
DECL|enumerator|FWH_IMMUTABLE
id|FWH_IMMUTABLE
op_assign
l_int|2
comma
DECL|enumerator|FWH_DENY_READ
id|FWH_DENY_READ
op_assign
l_int|4
comma
)brace
suffix:semicolon
DECL|function|ichxrom_cleanup
r_static
r_void
id|ichxrom_cleanup
c_func
(paren
r_struct
id|ichxrom_map_info
op_star
id|info
)paren
(brace
id|u16
id|word
suffix:semicolon
multiline_comment|/* Disable writes through the rom window */
id|pci_read_config_word
c_func
(paren
id|info-&gt;pdev
comma
id|BIOS_CNTL
comma
op_amp
id|word
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|info-&gt;pdev
comma
id|BIOS_CNTL
comma
id|word
op_amp
op_complement
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;mtd
)paren
(brace
id|del_mtd_device
c_func
(paren
id|info-&gt;mtd
)paren
suffix:semicolon
id|map_destroy
c_func
(paren
id|info-&gt;mtd
)paren
suffix:semicolon
id|info-&gt;mtd
op_assign
l_int|NULL
suffix:semicolon
id|info-&gt;map.virt
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;rom_rsrc.parent
)paren
id|release_resource
c_func
(paren
op_amp
id|info-&gt;rom_rsrc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;window_rsrc.parent
)paren
id|release_resource
c_func
(paren
op_amp
id|info-&gt;window_rsrc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;window_addr
)paren
(brace
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|info-&gt;window_addr
)paren
)paren
suffix:semicolon
id|info-&gt;window_addr
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|ichxrom_set_lock_state
r_static
r_int
id|ichxrom_set_lock_state
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|ofs
comma
r_int
id|len
comma
r_enum
id|fwh_lock_state
id|state
)paren
(brace
r_struct
id|map_info
op_star
id|map
op_assign
id|mtd-&gt;priv
suffix:semicolon
r_int
r_int
id|start
op_assign
id|ofs
suffix:semicolon
r_int
r_int
id|end
op_assign
id|start
op_plus
id|len
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* FIXME do I need to guard against concurrency here? */
multiline_comment|/* round down to 64K boundaries */
id|start
op_assign
id|start
op_amp
op_complement
l_int|0xFFFF
suffix:semicolon
id|end
op_assign
id|end
op_amp
op_complement
l_int|0xFFFF
suffix:semicolon
r_while
c_loop
(paren
id|start
op_le
id|end
)paren
(brace
r_int
r_int
id|ctrl_addr
suffix:semicolon
id|ctrl_addr
op_assign
id|addr
c_func
(paren
id|map
comma
id|start
)paren
op_minus
l_int|0x400000
op_plus
l_int|2
suffix:semicolon
id|writeb
c_func
(paren
id|state
comma
id|ctrl_addr
)paren
suffix:semicolon
id|start
op_assign
id|start
op_plus
l_int|0x10000
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ichxrom_lock
r_static
r_int
id|ichxrom_lock
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|ofs
comma
r_int
id|len
)paren
(brace
r_return
id|ichxrom_set_lock_state
c_func
(paren
id|mtd
comma
id|ofs
comma
id|len
comma
id|FWH_DENY_WRITE
)paren
suffix:semicolon
)brace
DECL|function|ichxrom_unlock
r_static
r_int
id|ichxrom_unlock
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|ofs
comma
r_int
id|len
)paren
(brace
r_return
id|ichxrom_set_lock_state
c_func
(paren
id|mtd
comma
id|ofs
comma
id|len
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|ichxrom_init_one
r_static
r_int
id|__devinit
id|ichxrom_init_one
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_const
r_struct
id|pci_device_id
op_star
id|ent
)paren
(brace
id|u16
id|word
suffix:semicolon
r_struct
id|ichxrom_map_info
op_star
id|info
op_assign
op_amp
id|ichxrom_map
suffix:semicolon
r_int
r_int
id|map_size
suffix:semicolon
r_static
r_char
op_star
id|probes
(braket
)braket
op_assign
(brace
l_string|&quot;cfi_probe&quot;
comma
l_string|&quot;jedec_probe&quot;
)brace
suffix:semicolon
r_struct
id|cfi_private
op_star
id|cfi
suffix:semicolon
multiline_comment|/* For now I just handle the ichx and I assume there&n;&t; * are not a lot of resources up at the top of the address&n;&t; * space.  It is possible to handle other devices in the&n;&t; * top 16MB but it is very painful.  Also since&n;&t; * you can only really attach a FWH to an ICHX there&n;&t; * a number of simplifications you can make.&n;&t; *&n;&t; * Also you can page firmware hubs if an 8MB window isn&squot;t enough &n;&t; * but don&squot;t currently handle that case either.&n;&t; */
id|info-&gt;pdev
op_assign
id|pdev
suffix:semicolon
multiline_comment|/*&n;&t; * Try to reserve the window mem region.  If this fails then&n;&t; * it is likely due to the window being &quot;reseved&quot; by the BIOS.&n;&t; */
id|info-&gt;window_rsrc.name
op_assign
id|MOD_NAME
suffix:semicolon
id|info-&gt;window_rsrc.start
op_assign
id|ICHX_FWH_REGION_START
suffix:semicolon
id|info-&gt;window_rsrc.end
op_assign
id|ICHX_FWH_REGION_START
op_plus
id|ICHX_FWH_REGION_SIZE
op_minus
l_int|1
suffix:semicolon
id|info-&gt;window_rsrc.flags
op_assign
id|IORESOURCE_MEM
op_or
id|IORESOURCE_BUSY
suffix:semicolon
r_if
c_cond
(paren
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|info-&gt;window_rsrc
)paren
)paren
(brace
id|info-&gt;window_rsrc.parent
op_assign
l_int|NULL
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
id|MOD_NAME
l_string|&quot; %s(): Unable to register resource&quot;
l_string|&quot; 0x%.08lx-0x%.08lx - kernel bug?&bslash;n&quot;
comma
id|__func__
comma
id|info-&gt;window_rsrc.start
comma
id|info-&gt;window_rsrc.end
)paren
suffix:semicolon
)brace
multiline_comment|/* Enable writes through the rom window */
id|pci_read_config_word
c_func
(paren
id|pdev
comma
id|BIOS_CNTL
comma
op_amp
id|word
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|word
op_amp
l_int|1
)paren
op_logical_and
(paren
id|word
op_amp
(paren
l_int|1
op_lshift
l_int|1
)paren
)paren
)paren
(brace
multiline_comment|/* The BIOS will generate an error if I enable&n;&t;&t; * this device, so don&squot;t even try.&n;&t;&t; */
id|printk
c_func
(paren
id|KERN_ERR
id|MOD_NAME
l_string|&quot;: firmware access control, I can&squot;t enable writes&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|failed
suffix:semicolon
)brace
id|pci_write_config_word
c_func
(paren
id|pdev
comma
id|BIOS_CNTL
comma
id|word
op_or
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Map the firmware hub into my address space. */
multiline_comment|/* Does this use too much virtual address space? */
id|info-&gt;window_addr
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|ICHX_FWH_REGION_START
comma
id|ICHX_FWH_REGION_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info-&gt;window_addr
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Failed to ioremap&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|failed
suffix:semicolon
)brace
multiline_comment|/* For now assume the firmware has setup all relevant firmware&n;&t; * windows.  We don&squot;t have enough information to handle this case&n;&t; * intelligently.&n;&t; */
multiline_comment|/* FIXME select the firmware hub and enable a window to it. */
id|info-&gt;mtd
op_assign
l_int|NULL
suffix:semicolon
id|info-&gt;map.map_priv_1
op_assign
id|info-&gt;window_addr
suffix:semicolon
multiline_comment|/* Loop through the possible bankwidths */
r_for
c_loop
(paren
id|ichxrom_map.map.bankwidth
op_assign
l_int|4
suffix:semicolon
id|ichxrom_map.map.bankwidth
suffix:semicolon
id|ichxrom_map.map.bankwidth
op_rshift_assign
l_int|1
)paren
(brace
id|map_size
op_assign
id|ICHX_FWH_REGION_SIZE
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|info-&gt;mtd
op_logical_and
(paren
id|map_size
OG
l_int|0
)paren
)paren
(brace
r_int
id|i
suffix:semicolon
id|info-&gt;map.size
op_assign
id|map_size
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
r_sizeof
(paren
id|probes
)paren
op_div
r_sizeof
(paren
r_char
op_star
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|info-&gt;mtd
op_assign
id|do_map_probe
c_func
(paren
id|probes
(braket
id|i
)braket
comma
op_amp
id|ichxrom_map.map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;mtd
)paren
r_break
suffix:semicolon
)brace
id|map_size
op_sub_assign
l_int|512
op_star
l_int|1024
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;mtd
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|info-&gt;mtd
)paren
(brace
r_goto
id|failed
suffix:semicolon
)brace
id|cfi
op_assign
id|ichxrom_map.map.fldrv_priv
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cfi-&gt;mfr
op_eq
id|MANUFACTURER_INTEL
)paren
op_logical_and
(paren
(paren
id|cfi-&gt;id
op_eq
id|I82802AB
)paren
op_logical_or
(paren
id|cfi-&gt;id
op_eq
id|I82802AC
)paren
)paren
)paren
(brace
multiline_comment|/* If it is a firmware hub put in the special lock&n;&t;&t; * and unlock routines.&n;&t;&t; */
id|info-&gt;mtd-&gt;lock
op_assign
id|ichxrom_lock
suffix:semicolon
id|info-&gt;mtd-&gt;unlock
op_assign
id|ichxrom_unlock
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;mtd-&gt;size
OG
id|info-&gt;map.size
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|MOD_NAME
l_string|&quot; rom(%u) larger than window(%lu). fixing...&bslash;n&quot;
comma
id|info-&gt;mtd-&gt;size
comma
id|info-&gt;map.size
)paren
suffix:semicolon
id|info-&gt;mtd-&gt;size
op_assign
id|info-&gt;map.size
suffix:semicolon
)brace
id|info-&gt;mtd-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|add_mtd_device
c_func
(paren
id|info-&gt;mtd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;window_rsrc.parent
)paren
(brace
multiline_comment|/*&n;&t;&t; * Registering the MTD device in iomem may not be possible&n;&t;&t; * if there is a BIOS &quot;reserved&quot; and BUSY range.  If this&n;&t;&t; * fails then continue anyway.&n;&t;&t; */
id|snprintf
c_func
(paren
id|info-&gt;mtd_name
comma
id|MTD_DEV_NAME_LENGTH
comma
l_string|&quot;mtd%d&quot;
comma
id|info-&gt;mtd-&gt;index
)paren
suffix:semicolon
id|info-&gt;rom_rsrc.name
op_assign
id|info-&gt;mtd_name
suffix:semicolon
id|info-&gt;rom_rsrc.start
op_assign
id|ICHX_FWH_REGION_START
op_plus
id|ICHX_FWH_REGION_SIZE
op_minus
id|map_size
suffix:semicolon
id|info-&gt;rom_rsrc.end
op_assign
id|ICHX_FWH_REGION_START
op_plus
id|ICHX_FWH_REGION_SIZE
suffix:semicolon
id|info-&gt;rom_rsrc.flags
op_assign
id|IORESOURCE_MEM
op_or
id|IORESOURCE_BUSY
suffix:semicolon
r_if
c_cond
(paren
id|request_resource
c_func
(paren
op_amp
id|info-&gt;window_rsrc
comma
op_amp
id|info-&gt;rom_rsrc
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|MOD_NAME
l_string|&quot;: cannot reserve MTD resource&bslash;n&quot;
)paren
suffix:semicolon
id|info-&gt;rom_rsrc.parent
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
id|failed
suffix:colon
id|ichxrom_cleanup
c_func
(paren
id|info
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|ichxrom_remove_one
r_static
r_void
id|__devexit
id|ichxrom_remove_one
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
r_struct
id|ichxrom_map_info
op_star
id|info
op_assign
op_amp
id|ichxrom_map
suffix:semicolon
id|u16
id|word
suffix:semicolon
id|del_mtd_device
c_func
(paren
id|info-&gt;mtd
)paren
suffix:semicolon
id|map_destroy
c_func
(paren
id|info-&gt;mtd
)paren
suffix:semicolon
id|info-&gt;mtd
op_assign
l_int|NULL
suffix:semicolon
id|info-&gt;map.map_priv_1
op_assign
l_int|0
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|info-&gt;window_addr
)paren
)paren
suffix:semicolon
id|info-&gt;window_addr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Disable writes through the rom window */
id|pci_read_config_word
c_func
(paren
id|pdev
comma
id|BIOS_CNTL
comma
op_amp
id|word
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|pdev
comma
id|BIOS_CNTL
comma
id|word
op_amp
op_complement
l_int|1
)paren
suffix:semicolon
macro_line|#if RESERVE_MEM_REGION&t;
id|release_mem_region
c_func
(paren
id|ICHX_FWH_REGION_START
comma
id|ICHX_FWH_REGION_SIZE
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|variable|__devinitdata
r_static
r_struct
id|pci_device_id
id|ichxrom_pci_tbl
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82801BA_0
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
)brace
comma
(brace
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82801CA_0
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
)brace
comma
(brace
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82801DB_0
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
)brace
comma
(brace
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82801EB_0
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
)brace
comma
(brace
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_ESB_1
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
)brace
comma
(brace
l_int|0
comma
)brace
comma
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|ichxrom_pci_tbl
)paren
suffix:semicolon
macro_line|#if 0
r_static
r_struct
id|pci_driver
id|ichxrom_driver
op_assign
(brace
dot
id|name
op_assign
id|MOD_NAME
comma
dot
id|id_table
op_assign
id|ichxrom_pci_tbl
comma
dot
id|probe
op_assign
id|ichxrom_init_one
comma
dot
id|remove
op_assign
id|ichxrom_remove_one
comma
)brace
suffix:semicolon
macro_line|#endif
DECL|variable|mydev
r_static
r_struct
id|pci_dev
op_star
id|mydev
suffix:semicolon
DECL|function|init_ichxrom
r_int
id|__init
id|init_ichxrom
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
r_struct
id|pci_device_id
op_star
id|id
suffix:semicolon
id|pdev
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|id
op_assign
id|ichxrom_pci_tbl
suffix:semicolon
id|id-&gt;vendor
suffix:semicolon
id|id
op_increment
)paren
(brace
id|pdev
op_assign
id|pci_find_device
c_func
(paren
id|id-&gt;vendor
comma
id|id-&gt;device
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pdev
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|pdev
)paren
(brace
id|mydev
op_assign
id|pdev
suffix:semicolon
r_return
id|ichxrom_init_one
c_func
(paren
id|pdev
comma
op_amp
id|ichxrom_pci_tbl
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
r_return
op_minus
id|ENXIO
suffix:semicolon
macro_line|#if 0
r_return
id|pci_module_init
c_func
(paren
op_amp
id|ichxrom_driver
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|cleanup_ichxrom
r_static
r_void
id|__exit
id|cleanup_ichxrom
c_func
(paren
r_void
)paren
(brace
id|ichxrom_remove_one
c_func
(paren
id|mydev
)paren
suffix:semicolon
)brace
DECL|variable|init_ichxrom
id|module_init
c_func
(paren
id|init_ichxrom
)paren
suffix:semicolon
DECL|variable|cleanup_ichxrom
id|module_exit
c_func
(paren
id|cleanup_ichxrom
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Eric Biederman &lt;ebiederman@lnxi.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;MTD map driver for BIOS chips on the ICHX southbridge&quot;
)paren
suffix:semicolon
eof
