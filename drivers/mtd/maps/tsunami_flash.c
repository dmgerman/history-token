multiline_comment|/*&n; * tsunami_flash.c&n; *&n; * flash chip on alpha ds10...&n; * $Id: tsunami_flash.c,v 1.9 2004/07/14 09:52:55 dwmw2 Exp $&n; */
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/core_tsunami.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
DECL|macro|FLASH_ENABLE_PORT
mdefine_line|#define FLASH_ENABLE_PORT 0x00C00001
DECL|macro|FLASH_ENABLE_BYTE
mdefine_line|#define FLASH_ENABLE_BYTE 0x01
DECL|macro|FLASH_DISABLE_BYTE
mdefine_line|#define FLASH_DISABLE_BYTE 0x00
DECL|macro|MAX_TIG_FLASH_SIZE
mdefine_line|#define MAX_TIG_FLASH_SIZE (12*1024*1024)
DECL|function|tsunami_flash_read8
r_static
r_inline
id|map_word
id|tsunami_flash_read8
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_int
r_int
id|offset
)paren
(brace
id|map_word
id|val
suffix:semicolon
id|val.x
(braket
l_int|0
)braket
op_assign
id|tsunami_tig_readb
c_func
(paren
id|offset
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|tsunami_flash_write8
r_static
r_void
id|tsunami_flash_write8
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
id|map_word
id|value
comma
r_int
r_int
id|offset
)paren
(brace
id|tsunami_tig_writeb
c_func
(paren
id|value.x
(braket
l_int|0
)braket
comma
id|offset
)paren
suffix:semicolon
)brace
DECL|function|tsunami_flash_copy_from
r_static
r_void
id|tsunami_flash_copy_from
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_void
op_star
id|addr
comma
r_int
r_int
id|offset
comma
id|ssize_t
id|len
)paren
(brace
r_int
r_char
op_star
id|dest
suffix:semicolon
id|dest
op_assign
id|addr
suffix:semicolon
r_while
c_loop
(paren
id|len
op_logical_and
(paren
id|offset
OL
id|MAX_TIG_FLASH_SIZE
)paren
)paren
(brace
op_star
id|dest
op_assign
id|tsunami_tig_readb
c_func
(paren
id|offset
)paren
suffix:semicolon
id|offset
op_increment
suffix:semicolon
id|dest
op_increment
suffix:semicolon
id|len
op_decrement
suffix:semicolon
)brace
)brace
DECL|function|tsunami_flash_copy_to
r_static
r_void
id|tsunami_flash_copy_to
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_int
r_int
id|offset
comma
r_const
r_void
op_star
id|addr
comma
id|ssize_t
id|len
)paren
(brace
r_const
r_int
r_char
op_star
id|src
suffix:semicolon
id|src
op_assign
id|addr
suffix:semicolon
r_while
c_loop
(paren
id|len
op_logical_and
(paren
id|offset
OL
id|MAX_TIG_FLASH_SIZE
)paren
)paren
(brace
id|tsunami_tig_writeb
c_func
(paren
op_star
id|src
comma
id|offset
)paren
suffix:semicolon
id|offset
op_increment
suffix:semicolon
id|src
op_increment
suffix:semicolon
id|len
op_decrement
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Deliberately don&squot;t provide operations wider than 8 bits.  I don&squot;t&n; * have then and it scares me to think how you could mess up if&n; * you tried to use them.   Buswidth is correctly so I&squot;m safe.&n; */
DECL|variable|tsunami_flash_map
r_static
r_struct
id|map_info
id|tsunami_flash_map
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;flash chip on the Tsunami TIG bus&quot;
comma
dot
id|size
op_assign
id|MAX_TIG_FLASH_SIZE
comma
dot
id|phys
op_assign
id|NO_XIP
suffix:semicolon
dot
id|bankwidth
op_assign
l_int|1
comma
dot
id|read
op_assign
id|tsunami_flash_read8
comma
dot
id|copy_from
op_assign
id|tsunami_flash_copy_from
comma
dot
id|write
op_assign
id|tsunami_flash_write8
comma
dot
id|copy_to
op_assign
id|tsunami_flash_copy_to
comma
)brace
suffix:semicolon
DECL|variable|tsunami_flash_mtd
r_static
r_struct
id|mtd_info
op_star
id|tsunami_flash_mtd
suffix:semicolon
DECL|function|cleanup_tsunami_flash
r_static
r_void
id|__exit
id|cleanup_tsunami_flash
c_func
(paren
r_void
)paren
(brace
r_struct
id|mtd_info
op_star
id|mtd
suffix:semicolon
id|mtd
op_assign
id|tsunami_flash_mtd
suffix:semicolon
r_if
c_cond
(paren
id|mtd
)paren
(brace
id|del_mtd_device
c_func
(paren
id|mtd
)paren
suffix:semicolon
id|map_destroy
c_func
(paren
id|mtd
)paren
suffix:semicolon
)brace
id|tsunami_flash_mtd
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|init_tsunami_flash
r_static
r_int
id|__init
id|init_tsunami_flash
c_func
(paren
r_void
)paren
(brace
r_static
r_const
r_char
op_star
id|rom_probe_types
(braket
)braket
op_assign
(brace
l_string|&quot;cfi_probe&quot;
comma
l_string|&quot;jedec_probe&quot;
comma
l_string|&quot;map_rom&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_char
op_star
op_star
id|type
suffix:semicolon
id|tsunami_tig_writeb
c_func
(paren
id|FLASH_ENABLE_BYTE
comma
id|FLASH_ENABLE_PORT
)paren
suffix:semicolon
id|tsunami_flash_mtd
op_assign
l_int|0
suffix:semicolon
id|type
op_assign
id|rom_probe_types
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
op_logical_neg
id|tsunami_flash_mtd
op_logical_and
op_star
id|type
suffix:semicolon
id|type
op_increment
)paren
(brace
id|tsunami_flash_mtd
op_assign
id|do_map_probe
c_func
(paren
op_star
id|type
comma
op_amp
id|tsunami_flash_map
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tsunami_flash_mtd
)paren
(brace
id|tsunami_flash_mtd-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|add_mtd_device
c_func
(paren
id|tsunami_flash_mtd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
DECL|variable|init_tsunami_flash
id|module_init
c_func
(paren
id|init_tsunami_flash
)paren
suffix:semicolon
DECL|variable|cleanup_tsunami_flash
id|module_exit
c_func
(paren
id|cleanup_tsunami_flash
)paren
suffix:semicolon
eof
