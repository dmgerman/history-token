multiline_comment|/*&n; * $Id: ocelot.c,v 1.16 2005/01/05 18:05:13 dwmw2 Exp $&n; *&n; * Flash on Momenco Ocelot&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
DECL|macro|OCELOT_PLD
mdefine_line|#define OCELOT_PLD 0x2c000000
DECL|macro|FLASH_WINDOW_ADDR
mdefine_line|#define FLASH_WINDOW_ADDR 0x2fc00000
DECL|macro|FLASH_WINDOW_SIZE
mdefine_line|#define FLASH_WINDOW_SIZE 0x00080000
DECL|macro|FLASH_BUSWIDTH
mdefine_line|#define FLASH_BUSWIDTH 1
DECL|macro|NVRAM_WINDOW_ADDR
mdefine_line|#define NVRAM_WINDOW_ADDR 0x2c800000
DECL|macro|NVRAM_WINDOW_SIZE
mdefine_line|#define NVRAM_WINDOW_SIZE 0x00007FF0
DECL|macro|NVRAM_BUSWIDTH
mdefine_line|#define NVRAM_BUSWIDTH 1
DECL|variable|cacheflush
r_static
r_int
r_int
id|cacheflush
op_assign
l_int|0
suffix:semicolon
DECL|variable|flash_mtd
r_static
r_struct
id|mtd_info
op_star
id|flash_mtd
suffix:semicolon
DECL|variable|nvram_mtd
r_static
r_struct
id|mtd_info
op_star
id|nvram_mtd
suffix:semicolon
DECL|function|ocelot_ram_write
r_static
r_void
id|ocelot_ram_write
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|to
comma
r_int
id|len
comma
r_int
op_star
id|retlen
comma
r_const
id|u_char
op_star
id|buf
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
id|done
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* If we use memcpy, it does word-wide writes. Even though we told the &n;&t;   GT64120A that it&squot;s an 8-bit wide region, word-wide writes don&squot;t work.&n;&t;   We end up just writing the first byte of the four to all four bytes.&n;&t;   So we have this loop instead */
op_star
id|retlen
op_assign
id|len
suffix:semicolon
r_while
c_loop
(paren
id|len
)paren
(brace
id|__raw_writeb
c_func
(paren
op_star
(paren
r_int
r_char
op_star
)paren
id|from
comma
id|map-&gt;virt
op_plus
id|to
)paren
suffix:semicolon
id|from
op_increment
suffix:semicolon
id|to
op_increment
suffix:semicolon
id|len
op_decrement
suffix:semicolon
)brace
)brace
DECL|variable|parsed_parts
r_static
r_struct
id|mtd_partition
op_star
id|parsed_parts
suffix:semicolon
DECL|variable|ocelot_flash_map
r_struct
id|map_info
id|ocelot_flash_map
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Ocelot boot flash&quot;
comma
dot
id|size
op_assign
id|FLASH_WINDOW_SIZE
comma
dot
id|bankwidth
op_assign
id|FLASH_BUSWIDTH
comma
dot
id|phys
op_assign
id|FLASH_WINDOW_ADDR
comma
)brace
suffix:semicolon
DECL|variable|ocelot_nvram_map
r_struct
id|map_info
id|ocelot_nvram_map
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Ocelot NVRAM&quot;
comma
dot
id|size
op_assign
id|NVRAM_WINDOW_SIZE
comma
dot
id|bankwidth
op_assign
id|NVRAM_BUSWIDTH
comma
dot
id|phys
op_assign
id|NVRAM_WINDOW_ADDR
comma
)brace
suffix:semicolon
DECL|variable|probes
r_static
r_const
r_char
op_star
id|probes
(braket
)braket
op_assign
(brace
l_string|&quot;RedBoot&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|init_ocelot_maps
r_static
r_int
id|__init
id|init_ocelot_maps
c_func
(paren
r_void
)paren
(brace
r_void
op_star
id|pld
suffix:semicolon
r_int
id|nr_parts
suffix:semicolon
r_int
r_char
id|brd_status
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Momenco Ocelot MTD mappings: Flash 0x%x at 0x%x, NVRAM 0x%x at 0x%x&bslash;n&quot;
comma
id|FLASH_WINDOW_SIZE
comma
id|FLASH_WINDOW_ADDR
comma
id|NVRAM_WINDOW_SIZE
comma
id|NVRAM_WINDOW_ADDR
)paren
suffix:semicolon
multiline_comment|/* First check whether the flash jumper is present */
id|pld
op_assign
id|ioremap
c_func
(paren
id|OCELOT_PLD
comma
l_int|0x10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pld
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Failed to ioremap Ocelot PLD&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|brd_status
op_assign
id|readb
c_func
(paren
id|pld
op_plus
l_int|4
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|pld
)paren
suffix:semicolon
multiline_comment|/* Now ioremap the NVRAM space */
id|ocelot_nvram_map.virt
op_assign
id|ioremap_nocache
c_func
(paren
id|NVRAM_WINDOW_ADDR
comma
id|NVRAM_WINDOW_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ocelot_nvram_map.virt
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Failed to ioremap Ocelot NVRAM space&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|simple_map_init
c_func
(paren
op_amp
id|ocelot_nvram_map
)paren
suffix:semicolon
multiline_comment|/* And do the RAM probe on it to get an MTD device */
id|nvram_mtd
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;map_ram&quot;
comma
op_amp
id|ocelot_nvram_map
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nvram_mtd
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;NVRAM probe failed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|fail_1
suffix:semicolon
)brace
id|nvram_mtd-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|nvram_mtd-&gt;erasesize
op_assign
l_int|16
suffix:semicolon
multiline_comment|/* Override the write() method */
id|nvram_mtd-&gt;write
op_assign
id|ocelot_ram_write
suffix:semicolon
multiline_comment|/* Now map the flash space */
id|ocelot_flash_map.virt
op_assign
id|ioremap_nocache
c_func
(paren
id|FLASH_WINDOW_ADDR
comma
id|FLASH_WINDOW_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ocelot_flash_map.virt
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Failed to ioremap Ocelot flash space&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|fail_2
suffix:semicolon
)brace
multiline_comment|/* Now the cached version */
id|ocelot_flash_map.cached
op_assign
(paren
r_int
r_int
)paren
id|__ioremap
c_func
(paren
id|FLASH_WINDOW_ADDR
comma
id|FLASH_WINDOW_SIZE
comma
l_int|0
)paren
suffix:semicolon
id|simple_map_init
c_func
(paren
op_amp
id|ocelot_flash_map
)paren
suffix:semicolon
multiline_comment|/* Only probe for flash if the write jumper is present */
r_if
c_cond
(paren
id|brd_status
op_amp
l_int|0x40
)paren
(brace
id|flash_mtd
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;jedec&quot;
comma
op_amp
id|ocelot_flash_map
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Ocelot flash write jumper not present. Treating as ROM&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* If that failed or the jumper&squot;s absent, pretend it&squot;s ROM */
r_if
c_cond
(paren
op_logical_neg
id|flash_mtd
)paren
(brace
id|flash_mtd
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;map_rom&quot;
comma
op_amp
id|ocelot_flash_map
)paren
suffix:semicolon
multiline_comment|/* If we&squot;re treating it as ROM, set the erase size */
r_if
c_cond
(paren
id|flash_mtd
)paren
id|flash_mtd-&gt;erasesize
op_assign
l_int|0x10000
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|flash_mtd
)paren
r_goto
id|fail3
suffix:semicolon
id|add_mtd_device
c_func
(paren
id|nvram_mtd
)paren
suffix:semicolon
id|flash_mtd-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|nr_parts
op_assign
id|parse_mtd_partitions
c_func
(paren
id|flash_mtd
comma
id|probes
comma
op_amp
id|parsed_parts
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr_parts
OG
l_int|0
)paren
id|add_mtd_partitions
c_func
(paren
id|flash_mtd
comma
id|parsed_parts
comma
id|nr_parts
)paren
suffix:semicolon
r_else
id|add_mtd_device
c_func
(paren
id|flash_mtd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|fail3
suffix:colon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|ocelot_flash_map.virt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ocelot_flash_map.cached
)paren
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|ocelot_flash_map.cached
)paren
suffix:semicolon
id|fail_2
suffix:colon
id|map_destroy
c_func
(paren
id|nvram_mtd
)paren
suffix:semicolon
id|fail_1
suffix:colon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|ocelot_nvram_map.virt
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
DECL|function|cleanup_ocelot_maps
r_static
r_void
id|__exit
id|cleanup_ocelot_maps
c_func
(paren
r_void
)paren
(brace
id|del_mtd_device
c_func
(paren
id|nvram_mtd
)paren
suffix:semicolon
id|map_destroy
c_func
(paren
id|nvram_mtd
)paren
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|ocelot_nvram_map.virt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parsed_parts
)paren
id|del_mtd_partitions
c_func
(paren
id|flash_mtd
)paren
suffix:semicolon
r_else
id|del_mtd_device
c_func
(paren
id|flash_mtd
)paren
suffix:semicolon
id|map_destroy
c_func
(paren
id|flash_mtd
)paren
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|ocelot_flash_map.virt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ocelot_flash_map.cached
)paren
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|ocelot_flash_map.cached
)paren
suffix:semicolon
)brace
DECL|variable|init_ocelot_maps
id|module_init
c_func
(paren
id|init_ocelot_maps
)paren
suffix:semicolon
DECL|variable|cleanup_ocelot_maps
id|module_exit
c_func
(paren
id|cleanup_ocelot_maps
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
l_string|&quot;Red Hat, Inc. - David Woodhouse &lt;dwmw2@cambridge.redhat.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;MTD map driver for Momenco Ocelot board&quot;
)paren
suffix:semicolon
eof
