multiline_comment|/*&n; * Flash memory access on Alchemy Db1550 board&n; * &n; * $Id: db1550-flash.c,v 1.3 2004/07/14 17:45:40 dwmw2 Exp $&n; *&n; * (C) 2004 Embedded Edge, LLC, based on db1550-flash.c:&n; * (C) 2003 Pete Popov &lt;pete_popov@yahoo.com&gt;&n; * &n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/au1000.h&gt;
macro_line|#ifdef &t;DEBUG_RW
DECL|macro|DBG
mdefine_line|#define&t;DBG(x...)&t;printk(x)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define&t;DBG(x...)&t;
macro_line|#endif
DECL|variable|window_addr
r_static
r_int
r_int
id|window_addr
suffix:semicolon
DECL|variable|window_size
r_static
r_int
r_int
id|window_size
suffix:semicolon
DECL|variable|db1550_map
r_static
r_struct
id|map_info
id|db1550_map
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Db1550 flash&quot;
comma
)brace
suffix:semicolon
DECL|variable|flash_bankwidth
r_static
r_int
r_char
id|flash_bankwidth
op_assign
l_int|4
suffix:semicolon
multiline_comment|/* &n; * Support only 64MB NOR Flash parts&n; */
macro_line|#if defined(CONFIG_MTD_DB1550_BOOT) &amp;&amp; defined(CONFIG_MTD_DB1550_USER)
DECL|macro|DB1550_BOTH_BANKS
mdefine_line|#define DB1550_BOTH_BANKS
macro_line|#elif defined(CONFIG_MTD_DB1550_BOOT) &amp;&amp; !defined(CONFIG_MTD_DB1550_USER)
DECL|macro|DB1550_BOOT_ONLY
mdefine_line|#define DB1550_BOOT_ONLY
macro_line|#elif !defined(CONFIG_MTD_DB1550_BOOT) &amp;&amp; defined(CONFIG_MTD_DB1550_USER)
DECL|macro|DB1550_USER_ONLY
mdefine_line|#define DB1550_USER_ONLY
macro_line|#endif
macro_line|#ifdef DB1550_BOTH_BANKS
multiline_comment|/* both banks will be used. Combine the first bank and the first &n; * part of the second bank together into a single jffs/jffs2&n; * partition.&n; */
DECL|variable|db1550_partitions
r_static
r_struct
id|mtd_partition
id|db1550_partitions
(braket
)braket
op_assign
(brace
multiline_comment|/* assume boot[2:0]:swap is &squot;0000&squot; or &squot;1000&squot;, which translates to:&n;&t; * 1C00 0000 1FFF FFFF CE0 64MB Boot NOR Flash&n;&t; * 1800 0000 1BFF FFFF CE0 64MB Param NOR Flash&n;&t; */
(brace
dot
id|name
op_assign
l_string|&quot;User FS&quot;
comma
dot
id|size
op_assign
(paren
l_int|0x1FC00000
op_minus
l_int|0x18000000
)paren
comma
dot
id|offset
op_assign
l_int|0x0000000
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;yamon&quot;
comma
dot
id|size
op_assign
l_int|0x0100000
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
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;raw kernel&quot;
comma
dot
id|size
op_assign
(paren
l_int|0x300000
op_minus
l_int|0x40000
)paren
comma
multiline_comment|/* last 256KB is yamon env */
dot
id|offset
op_assign
id|MTDPART_OFS_APPEND
comma
)brace
)brace
suffix:semicolon
macro_line|#elif defined(DB1550_BOOT_ONLY)
DECL|variable|db1550_partitions
r_static
r_struct
id|mtd_partition
id|db1550_partitions
(braket
)braket
op_assign
(brace
multiline_comment|/* assume boot[2:0]:swap is &squot;0000&squot; or &squot;1000&squot;, which translates to:&n;&t; * 1C00 0000 1FFF FFFF CE0 64MB Boot NOR Flash&n;&t; */
(brace
dot
id|name
op_assign
l_string|&quot;User FS&quot;
comma
dot
id|size
op_assign
l_int|0x03c00000
comma
dot
id|offset
op_assign
l_int|0x0000000
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;yamon&quot;
comma
dot
id|size
op_assign
l_int|0x0100000
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
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;raw kernel&quot;
comma
dot
id|size
op_assign
(paren
l_int|0x300000
op_minus
l_int|0x40000
)paren
comma
multiline_comment|/* last 256KB is yamon env */
dot
id|offset
op_assign
id|MTDPART_OFS_APPEND
comma
)brace
)brace
suffix:semicolon
macro_line|#elif defined(DB1550_USER_ONLY)
DECL|variable|db1550_partitions
r_static
r_struct
id|mtd_partition
id|db1550_partitions
(braket
)braket
op_assign
(brace
multiline_comment|/* assume boot[2:0]:swap is &squot;0000&squot; or &squot;1000&squot;, which translates to:&n;&t; * 1800 0000 1BFF FFFF CE0 64MB Param NOR Flash&n;&t; */
(brace
dot
id|name
op_assign
l_string|&quot;User FS&quot;
comma
dot
id|size
op_assign
(paren
l_int|0x4000000
op_minus
l_int|0x200000
)paren
comma
multiline_comment|/* reserve 2MB for raw kernel */
dot
id|offset
op_assign
l_int|0x0000000
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;raw kernel&quot;
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
)brace
)brace
suffix:semicolon
macro_line|#else
macro_line|#error MTD_DB1550 define combo error /* should never happen */
macro_line|#endif
DECL|macro|NB_OF
mdefine_line|#define NB_OF(x)  (sizeof(x)/sizeof(x[0]))
DECL|variable|mymtd
r_static
r_struct
id|mtd_info
op_star
id|mymtd
suffix:semicolon
multiline_comment|/*&n; * Probe the flash density and setup window address and size&n; * based on user CONFIG options. There are times when we don&squot;t&n; * want the MTD driver to be probing the boot or user flash,&n; * so having the option to enable only one bank is important.&n; */
DECL|function|setup_flash_params
r_int
id|setup_flash_params
c_func
(paren
r_void
)paren
(brace
macro_line|#if defined(DB1550_BOTH_BANKS)
id|window_addr
op_assign
l_int|0x18000000
suffix:semicolon
id|window_size
op_assign
l_int|0x8000000
suffix:semicolon
macro_line|#elif defined(DB1550_BOOT_ONLY)
id|window_addr
op_assign
l_int|0x1C000000
suffix:semicolon
id|window_size
op_assign
l_int|0x4000000
suffix:semicolon
macro_line|#else /* USER ONLY */
id|window_addr
op_assign
l_int|0x1E000000
suffix:semicolon
id|window_size
op_assign
l_int|0x4000000
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|db1550_mtd_init
r_int
id|__init
id|db1550_mtd_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|mtd_partition
op_star
id|parts
suffix:semicolon
r_int
id|nb_parts
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Default flash bankwidth */
id|db1550_map.bankwidth
op_assign
id|flash_bankwidth
suffix:semicolon
r_if
c_cond
(paren
id|setup_flash_params
c_func
(paren
)paren
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
multiline_comment|/*&n;&t; * Static partition definition selection&n;&t; */
id|parts
op_assign
id|db1550_partitions
suffix:semicolon
id|nb_parts
op_assign
id|NB_OF
c_func
(paren
id|db1550_partitions
)paren
suffix:semicolon
id|db1550_map.size
op_assign
id|window_size
suffix:semicolon
multiline_comment|/*&n;&t; * Now let&squot;s probe for the actual flash.  Do it here since&n;&t; * specific machine settings might have been set above.&n;&t; */
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Pb1550 flash: probing %d-bit flash bus&bslash;n&quot;
comma
id|db1550_map.bankwidth
op_star
l_int|8
)paren
suffix:semicolon
id|db1550_map.virt
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|window_addr
comma
id|window_size
)paren
suffix:semicolon
id|mymtd
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;cfi_probe&quot;
comma
op_amp
id|db1550_map
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mymtd
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|mymtd-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|add_mtd_partitions
c_func
(paren
id|mymtd
comma
id|parts
comma
id|nb_parts
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|db1550_mtd_cleanup
r_static
r_void
id|__exit
id|db1550_mtd_cleanup
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|mymtd
)paren
(brace
id|del_mtd_partitions
c_func
(paren
id|mymtd
)paren
suffix:semicolon
id|map_destroy
c_func
(paren
id|mymtd
)paren
suffix:semicolon
)brace
)brace
DECL|variable|db1550_mtd_init
id|module_init
c_func
(paren
id|db1550_mtd_init
)paren
suffix:semicolon
DECL|variable|db1550_mtd_cleanup
id|module_exit
c_func
(paren
id|db1550_mtd_cleanup
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Embedded Edge, LLC&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Db1550 mtd map driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
