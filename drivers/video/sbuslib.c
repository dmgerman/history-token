multiline_comment|/* sbuslib.c: Helper library for SBUS framebuffer drivers.&n; *&n; * Copyright (C) 2003 David S. Miller (davem@redhat.com)&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/fbio.h&gt;
macro_line|#include &quot;sbuslib.h&quot;
DECL|function|sbusfb_fill_var
r_void
id|sbusfb_fill_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|prom_node
comma
r_int
id|bpp
)paren
(brace
id|memset
c_func
(paren
id|var
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|var
)paren
)paren
suffix:semicolon
id|var-&gt;xres
op_assign
id|prom_getintdefault
c_func
(paren
id|prom_node
comma
l_string|&quot;width&quot;
comma
l_int|1152
)paren
suffix:semicolon
id|var-&gt;yres
op_assign
id|prom_getintdefault
c_func
(paren
id|prom_node
comma
l_string|&quot;height&quot;
comma
l_int|900
)paren
suffix:semicolon
id|var-&gt;xres_virtual
op_assign
id|var-&gt;xres
suffix:semicolon
id|var-&gt;yres_virtual
op_assign
id|var-&gt;yres
suffix:semicolon
id|var-&gt;bits_per_pixel
op_assign
id|bpp
suffix:semicolon
)brace
DECL|variable|sbusfb_fill_var
id|EXPORT_SYMBOL
c_func
(paren
id|sbusfb_fill_var
)paren
suffix:semicolon
DECL|function|sbusfb_mmapsize
r_static
r_int
r_int
id|sbusfb_mmapsize
c_func
(paren
r_int
id|size
comma
r_int
r_int
id|fbsize
)paren
(brace
r_if
c_cond
(paren
id|size
op_eq
id|SBUS_MMAP_EMPTY
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|size
op_ge
l_int|0
)paren
r_return
id|size
suffix:semicolon
r_return
id|fbsize
op_star
(paren
op_minus
id|size
)paren
suffix:semicolon
)brace
DECL|function|sbusfb_mmap_helper
r_int
id|sbusfb_mmap_helper
c_func
(paren
r_struct
id|sbus_mmap_map
op_star
id|map
comma
r_int
r_int
id|physbase
comma
r_int
r_int
id|fbsize
comma
r_int
r_int
id|iospace
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_int
r_int
id|size
comma
id|page
comma
id|r
comma
id|map_size
suffix:semicolon
r_int
r_int
id|map_offset
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|off
suffix:semicolon
r_int
id|i
suffix:semicolon
id|size
op_assign
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_pgoff
OG
(paren
op_complement
l_int|0UL
op_rshift
id|PAGE_SHIFT
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|off
op_assign
id|vma-&gt;vm_pgoff
op_lshift
id|PAGE_SHIFT
suffix:semicolon
multiline_comment|/* To stop the swapper from even considering these pages */
id|vma-&gt;vm_flags
op_or_assign
(paren
id|VM_SHM
op_or
id|VM_IO
op_or
id|VM_LOCKED
)paren
suffix:semicolon
multiline_comment|/* Each page, see which map applies */
r_for
c_loop
(paren
id|page
op_assign
l_int|0
suffix:semicolon
id|page
OL
id|size
suffix:semicolon
)paren
(brace
id|map_size
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|map
(braket
id|i
)braket
dot
id|size
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|map
(braket
id|i
)braket
dot
id|voff
op_eq
id|off
op_plus
id|page
)paren
(brace
id|map_size
op_assign
id|sbusfb_mmapsize
c_func
(paren
id|map
(braket
id|i
)braket
dot
id|size
comma
id|fbsize
)paren
suffix:semicolon
macro_line|#ifdef __sparc_v9__
DECL|macro|POFF_MASK
mdefine_line|#define POFF_MASK&t;(PAGE_MASK|0x1UL)
macro_line|#else
mdefine_line|#define POFF_MASK&t;(PAGE_MASK)
macro_line|#endif&t;&t;&t;&t;
id|map_offset
op_assign
(paren
id|physbase
op_plus
id|map
(braket
id|i
)braket
dot
id|poff
)paren
op_amp
id|POFF_MASK
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|map_size
)paren
(brace
id|page
op_add_assign
id|PAGE_SIZE
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|page
op_plus
id|map_size
OG
id|size
)paren
id|map_size
op_assign
id|size
op_minus
id|page
suffix:semicolon
id|r
op_assign
id|io_remap_page_range
c_func
(paren
id|vma
comma
id|vma-&gt;vm_start
op_plus
id|page
comma
id|map_offset
comma
id|map_size
comma
id|vma-&gt;vm_page_prot
comma
id|iospace
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|page
op_add_assign
id|map_size
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sbusfb_mmap_helper
id|EXPORT_SYMBOL
c_func
(paren
id|sbusfb_mmap_helper
)paren
suffix:semicolon
DECL|function|sbusfb_ioctl_helper
r_int
id|sbusfb_ioctl_helper
c_func
(paren
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
comma
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|type
comma
r_int
id|fb_depth
comma
r_int
r_int
id|fb_size
)paren
(brace
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|FBIOGTYPE
suffix:colon
(brace
r_struct
id|fbtype
id|__user
op_star
id|f
op_assign
(paren
r_struct
id|fbtype
id|__user
op_star
)paren
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|type
comma
op_amp
id|f-&gt;fb_type
)paren
op_logical_or
id|__put_user
c_func
(paren
id|info-&gt;var.yres
comma
op_amp
id|f-&gt;fb_height
)paren
op_logical_or
id|__put_user
c_func
(paren
id|info-&gt;var.xres
comma
op_amp
id|f-&gt;fb_width
)paren
op_logical_or
id|__put_user
c_func
(paren
id|fb_depth
comma
op_amp
id|f-&gt;fb_depth
)paren
op_logical_or
id|__put_user
c_func
(paren
l_int|0
comma
op_amp
id|f-&gt;fb_cmsize
)paren
op_logical_or
id|__put_user
c_func
(paren
id|fb_size
comma
op_amp
id|f-&gt;fb_cmsize
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|FBIOPUTCMAP_SPARC
suffix:colon
(brace
r_struct
id|fbcmap
id|__user
op_star
id|c
op_assign
(paren
r_struct
id|fbcmap
id|__user
op_star
)paren
id|arg
suffix:semicolon
r_struct
id|fb_cmap
id|cmap
suffix:semicolon
id|u16
id|red
comma
id|green
comma
id|blue
suffix:semicolon
r_int
r_char
id|__user
op_star
id|ured
suffix:semicolon
r_int
r_char
id|__user
op_star
id|ugreen
suffix:semicolon
r_int
r_char
id|__user
op_star
id|ublue
suffix:semicolon
r_int
id|index
comma
id|count
comma
id|i
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|index
comma
op_amp
id|c-&gt;index
)paren
op_logical_or
id|__get_user
c_func
(paren
id|count
comma
op_amp
id|c-&gt;count
)paren
op_logical_or
id|__get_user
c_func
(paren
id|ured
comma
op_amp
id|c-&gt;red
)paren
op_logical_or
id|__get_user
c_func
(paren
id|ugreen
comma
op_amp
id|c-&gt;green
)paren
op_logical_or
id|__get_user
c_func
(paren
id|ublue
comma
op_amp
id|c-&gt;blue
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|cmap.len
op_assign
l_int|1
suffix:semicolon
id|cmap.red
op_assign
op_amp
id|red
suffix:semicolon
id|cmap.green
op_assign
op_amp
id|green
suffix:semicolon
id|cmap.blue
op_assign
op_amp
id|blue
suffix:semicolon
id|cmap.transp
op_assign
l_int|NULL
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
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|red
comma
op_amp
id|ured
(braket
id|i
)braket
)paren
op_logical_or
id|get_user
c_func
(paren
id|green
comma
op_amp
id|ugreen
(braket
id|i
)braket
)paren
op_logical_or
id|get_user
c_func
(paren
id|blue
comma
op_amp
id|ublue
(braket
id|i
)braket
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|cmap.start
op_assign
id|index
op_plus
id|i
suffix:semicolon
id|err
op_assign
id|fb_set_cmap
c_func
(paren
op_amp
id|cmap
comma
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|FBIOGETCMAP_SPARC
suffix:colon
(brace
r_struct
id|fbcmap
id|__user
op_star
id|c
op_assign
(paren
r_struct
id|fbcmap
id|__user
op_star
)paren
id|arg
suffix:semicolon
r_int
r_char
id|__user
op_star
id|ured
suffix:semicolon
r_int
r_char
id|__user
op_star
id|ugreen
suffix:semicolon
r_int
r_char
id|__user
op_star
id|ublue
suffix:semicolon
r_struct
id|fb_cmap
op_star
id|cmap
op_assign
op_amp
id|info-&gt;cmap
suffix:semicolon
r_int
id|index
comma
id|count
comma
id|i
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|index
comma
op_amp
id|c-&gt;index
)paren
op_logical_or
id|__get_user
c_func
(paren
id|count
comma
op_amp
id|c-&gt;count
)paren
op_logical_or
id|__get_user
c_func
(paren
id|ured
comma
op_amp
id|c-&gt;red
)paren
op_logical_or
id|__get_user
c_func
(paren
id|ugreen
comma
op_amp
id|c-&gt;green
)paren
op_logical_or
id|__get_user
c_func
(paren
id|ublue
comma
op_amp
id|c-&gt;blue
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|index
op_plus
id|count
OG
id|cmap-&gt;len
)paren
r_return
op_minus
id|EINVAL
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
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|cmap-&gt;red
(braket
id|index
op_plus
id|i
)braket
comma
op_amp
id|ured
(braket
id|i
)braket
)paren
op_logical_or
id|put_user
c_func
(paren
id|cmap-&gt;green
(braket
id|index
op_plus
id|i
)braket
comma
op_amp
id|ugreen
(braket
id|i
)braket
)paren
op_logical_or
id|put_user
c_func
(paren
id|cmap-&gt;blue
(braket
id|index
op_plus
id|i
)braket
comma
op_amp
id|ublue
(braket
id|i
)braket
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
suffix:semicolon
)brace
DECL|variable|sbusfb_ioctl_helper
id|EXPORT_SYMBOL
c_func
(paren
id|sbusfb_ioctl_helper
)paren
suffix:semicolon
eof
