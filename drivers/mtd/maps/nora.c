multiline_comment|/*&n; * $Id: nora.c,v 1.21 2001/10/02 15:05:14 dwmw2 Exp $&n; *&n; * This is so simple I love it.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
DECL|macro|WINDOW_ADDR
mdefine_line|#define WINDOW_ADDR 0xd0000000
DECL|macro|WINDOW_SIZE
mdefine_line|#define WINDOW_SIZE 0x04000000
DECL|variable|mymtd
r_static
r_struct
id|mtd_info
op_star
id|mymtd
suffix:semicolon
DECL|function|nora_read8
id|__u8
id|nora_read8
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
r_return
op_star
(paren
id|__u8
op_star
)paren
(paren
id|WINDOW_ADDR
op_plus
id|ofs
)paren
suffix:semicolon
)brace
DECL|function|nora_read16
id|__u16
id|nora_read16
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
r_return
op_star
(paren
id|__u16
op_star
)paren
(paren
id|WINDOW_ADDR
op_plus
id|ofs
)paren
suffix:semicolon
)brace
DECL|function|nora_read32
id|__u32
id|nora_read32
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
r_return
op_star
(paren
id|__u32
op_star
)paren
(paren
id|WINDOW_ADDR
op_plus
id|ofs
)paren
suffix:semicolon
)brace
DECL|function|nora_copy_from
r_void
id|nora_copy_from
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
id|memcpy
c_func
(paren
id|to
comma
(paren
r_void
op_star
)paren
(paren
id|WINDOW_ADDR
op_plus
id|from
)paren
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|nora_write8
r_void
id|nora_write8
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
id|__u8
id|d
comma
r_int
r_int
id|adr
)paren
(brace
op_star
(paren
id|__u8
op_star
)paren
(paren
id|WINDOW_ADDR
op_plus
id|adr
)paren
op_assign
id|d
suffix:semicolon
)brace
DECL|function|nora_write16
r_void
id|nora_write16
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
id|__u16
id|d
comma
r_int
r_int
id|adr
)paren
(brace
op_star
(paren
id|__u16
op_star
)paren
(paren
id|WINDOW_ADDR
op_plus
id|adr
)paren
op_assign
id|d
suffix:semicolon
)brace
DECL|function|nora_write32
r_void
id|nora_write32
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
id|__u32
id|d
comma
r_int
r_int
id|adr
)paren
(brace
op_star
(paren
id|__u32
op_star
)paren
(paren
id|WINDOW_ADDR
op_plus
id|adr
)paren
op_assign
id|d
suffix:semicolon
)brace
DECL|function|nora_copy_to
r_void
id|nora_copy_to
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
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|WINDOW_ADDR
op_plus
id|to
)paren
comma
id|from
comma
id|len
)paren
suffix:semicolon
)brace
DECL|variable|nora_map
r_struct
id|map_info
id|nora_map
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;NORA&quot;
comma
dot
id|size
op_assign
id|WINDOW_SIZE
comma
dot
id|buswidth
op_assign
l_int|2
comma
dot
id|read8
op_assign
id|nora_read8
comma
dot
id|read16
op_assign
id|nora_read16
comma
dot
id|read32
op_assign
id|nora_read32
comma
dot
id|copy_from
op_assign
id|nora_copy_from
comma
dot
id|write8
op_assign
id|nora_write8
comma
dot
id|write16
op_assign
id|nora_write16
comma
dot
id|write32
op_assign
id|nora_write32
comma
dot
id|copy_to
op_assign
id|nora_copy_to
)brace
suffix:semicolon
DECL|function|nora_mtd_read
r_static
r_int
id|nora_mtd_read
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|from
comma
r_int
id|len
comma
r_int
op_star
id|retlen
comma
id|u_char
op_star
id|buf
)paren
(brace
r_return
id|mymtd
op_member_access_from_pointer
id|read
c_func
(paren
id|mymtd
comma
id|from
op_plus
(paren
r_int
r_int
)paren
id|mtd-&gt;priv
comma
id|len
comma
id|retlen
comma
id|buf
)paren
suffix:semicolon
)brace
DECL|function|nora_mtd_write
r_static
r_int
id|nora_mtd_write
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
r_return
id|mymtd
op_member_access_from_pointer
id|write
c_func
(paren
id|mymtd
comma
id|to
op_plus
(paren
r_int
r_int
)paren
id|mtd-&gt;priv
comma
id|len
comma
id|retlen
comma
id|buf
)paren
suffix:semicolon
)brace
DECL|function|nora_mtd_erase
r_static
r_int
id|nora_mtd_erase
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_struct
id|erase_info
op_star
id|instr
)paren
(brace
id|instr-&gt;addr
op_add_assign
(paren
r_int
r_int
)paren
id|mtd-&gt;priv
suffix:semicolon
r_return
id|mymtd
op_member_access_from_pointer
id|erase
c_func
(paren
id|mymtd
comma
id|instr
)paren
suffix:semicolon
)brace
DECL|function|nora_mtd_sync
r_static
r_void
id|nora_mtd_sync
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
(brace
id|mymtd
op_member_access_from_pointer
id|sync
c_func
(paren
id|mymtd
)paren
suffix:semicolon
)brace
DECL|function|nora_mtd_suspend
r_static
r_int
id|nora_mtd_suspend
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
(brace
r_return
id|mymtd
op_member_access_from_pointer
id|suspend
c_func
(paren
id|mymtd
)paren
suffix:semicolon
)brace
DECL|function|nora_mtd_resume
r_static
r_void
id|nora_mtd_resume
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
(brace
id|mymtd
op_member_access_from_pointer
id|resume
c_func
(paren
id|mymtd
)paren
suffix:semicolon
)brace
DECL|variable|nora_mtds
r_static
r_struct
id|mtd_info
id|nora_mtds
(braket
l_int|4
)braket
op_assign
(brace
multiline_comment|/* boot, kernel, ramdisk, fs */
(brace
dot
id|type
op_assign
id|MTD_NORFLASH
comma
dot
id|flags
op_assign
id|MTD_CAP_NORFLASH
comma
dot
id|size
op_assign
l_int|0x60000
comma
dot
id|erasesize
op_assign
l_int|0x20000
comma
dot
id|name
op_assign
l_string|&quot;NORA boot firmware&quot;
comma
dot
id|module
op_assign
id|THIS_MODULE
comma
dot
id|erase
op_assign
id|nora_mtd_erase
comma
dot
id|read
op_assign
id|nora_mtd_read
comma
dot
id|write
op_assign
id|nora_mtd_write
comma
dot
id|suspend
op_assign
id|nora_mtd_suspend
comma
dot
id|resume
op_assign
id|nora_mtd_resume
comma
dot
id|sync
op_assign
id|nora_mtd_sync
comma
)brace
comma
(brace
dot
id|type
op_assign
id|MTD_NORFLASH
comma
dot
id|flags
op_assign
id|MTD_CAP_NORFLASH
comma
dot
id|size
op_assign
l_int|0x0a0000
comma
dot
id|erasesize
op_assign
l_int|0x20000
comma
dot
id|name
op_assign
l_string|&quot;NORA kernel&quot;
comma
dot
id|module
op_assign
id|THIS_MODULE
comma
dot
id|erase
op_assign
id|nora_mtd_erase
comma
dot
id|read
op_assign
id|nora_mtd_read
comma
dot
id|write
op_assign
id|nora_mtd_write
comma
dot
id|suspend
op_assign
id|nora_mtd_suspend
comma
dot
id|resume
op_assign
id|nora_mtd_resume
comma
dot
id|sync
op_assign
id|nora_mtd_sync
comma
dot
id|priv
op_assign
(paren
r_void
op_star
)paren
l_int|0x60000
)brace
comma
(brace
dot
id|type
op_assign
id|MTD_NORFLASH
comma
dot
id|flags
op_assign
id|MTD_CAP_NORFLASH
comma
dot
id|size
op_assign
l_int|0x900000
comma
dot
id|erasesize
op_assign
l_int|0x20000
comma
dot
id|name
op_assign
l_string|&quot;NORA root filesystem&quot;
comma
dot
id|module
op_assign
id|THIS_MODULE
comma
dot
id|erase
op_assign
id|nora_mtd_erase
comma
dot
id|read
op_assign
id|nora_mtd_read
comma
dot
id|write
op_assign
id|nora_mtd_write
comma
dot
id|suspend
op_assign
id|nora_mtd_suspend
comma
dot
id|resume
op_assign
id|nora_mtd_resume
comma
dot
id|sync
op_assign
id|nora_mtd_sync
comma
dot
id|priv
op_assign
(paren
r_void
op_star
)paren
l_int|0x100000
)brace
comma
(brace
dot
id|type
op_assign
id|MTD_NORFLASH
comma
dot
id|flags
op_assign
id|MTD_CAP_NORFLASH
comma
dot
id|size
op_assign
l_int|0x1600000
comma
dot
id|erasesize
op_assign
l_int|0x20000
comma
dot
id|name
op_assign
l_string|&quot;NORA second filesystem&quot;
comma
dot
id|module
op_assign
id|THIS_MODULE
comma
dot
id|erase
op_assign
id|nora_mtd_erase
comma
dot
id|read
op_assign
id|nora_mtd_read
comma
dot
id|write
op_assign
id|nora_mtd_write
comma
dot
id|suspend
op_assign
id|nora_mtd_suspend
comma
dot
id|resume
op_assign
id|nora_mtd_resume
comma
dot
id|sync
op_assign
id|nora_mtd_sync
comma
dot
id|priv
op_assign
(paren
r_void
op_star
)paren
l_int|0xa00000
)brace
)brace
suffix:semicolon
DECL|function|init_nora
r_int
id|__init
id|init_nora
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;nora flash device: %x at %x&bslash;n&quot;
comma
id|WINDOW_SIZE
comma
id|WINDOW_ADDR
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
id|nora_map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mymtd
)paren
(brace
id|mymtd-&gt;module
op_assign
id|THIS_MODULE
suffix:semicolon
id|add_mtd_device
c_func
(paren
op_amp
id|nora_mtds
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|add_mtd_device
c_func
(paren
op_amp
id|nora_mtds
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|add_mtd_device
c_func
(paren
op_amp
id|nora_mtds
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|add_mtd_device
c_func
(paren
op_amp
id|nora_mtds
(braket
l_int|3
)braket
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
DECL|function|cleanup_nora
r_static
r_void
id|__exit
id|cleanup_nora
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
id|del_mtd_device
c_func
(paren
op_amp
id|nora_mtds
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|del_mtd_device
c_func
(paren
op_amp
id|nora_mtds
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|del_mtd_device
c_func
(paren
op_amp
id|nora_mtds
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|del_mtd_device
c_func
(paren
op_amp
id|nora_mtds
(braket
l_int|2
)braket
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
DECL|variable|init_nora
id|module_init
c_func
(paren
id|init_nora
)paren
suffix:semicolon
DECL|variable|cleanup_nora
id|module_exit
c_func
(paren
id|cleanup_nora
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
l_string|&quot;MTD map driver for Nora board&quot;
)paren
suffix:semicolon
eof
