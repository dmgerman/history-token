multiline_comment|/*&n; * fbsysfs.c - framebuffer device class and attributes&n; *&n; * Copyright (c) 2004 James Simmons &lt;jsimmons@infradead.org&gt;&n; * &n; *&t;This program is free software you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
multiline_comment|/*&n; * Note:  currently there&squot;s only stubs for framebuffer_alloc and&n; * framebuffer_release here.  The reson for that is that until all drivers&n; * are converted to use it a sysfsification will open OOPSable races.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/console.h&gt;
multiline_comment|/**&n; * framebuffer_alloc - creates a new frame buffer info structure&n; *&n; * @size: size of driver private data, can be zero&n; * @dev: pointer to the device for this fb, this can be NULL&n; *&n; * Creates a new frame buffer info structure. Also reserves @size bytes&n; * for driver private data (info-&gt;par). info-&gt;par (if any) will be&n; * aligned to sizeof(long).&n; *&n; * Returns the new structure, or NULL if an error occured.&n; *&n; */
DECL|function|framebuffer_alloc
r_struct
id|fb_info
op_star
id|framebuffer_alloc
c_func
(paren
r_int
id|size
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
DECL|macro|BYTES_PER_LONG
mdefine_line|#define BYTES_PER_LONG (BITS_PER_LONG/8)
DECL|macro|PADDING
mdefine_line|#define PADDING (BYTES_PER_LONG - (sizeof(struct fb_info) % BYTES_PER_LONG))
r_int
id|fb_info_size
op_assign
r_sizeof
(paren
r_struct
id|fb_info
)paren
suffix:semicolon
r_struct
id|fb_info
op_star
id|info
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|size
)paren
id|fb_info_size
op_add_assign
id|PADDING
suffix:semicolon
id|p
op_assign
id|kmalloc
c_func
(paren
id|fb_info_size
op_plus
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|p
comma
l_int|0
comma
id|fb_info_size
op_plus
id|size
)paren
suffix:semicolon
id|info
op_assign
(paren
r_struct
id|fb_info
op_star
)paren
id|p
suffix:semicolon
r_if
c_cond
(paren
id|size
)paren
id|info-&gt;par
op_assign
id|p
op_plus
id|fb_info_size
suffix:semicolon
id|info-&gt;device
op_assign
id|dev
suffix:semicolon
r_return
id|info
suffix:semicolon
DECL|macro|PADDING
macro_line|#undef PADDING
DECL|macro|BYTES_PER_LONG
macro_line|#undef BYTES_PER_LONG
)brace
DECL|variable|framebuffer_alloc
id|EXPORT_SYMBOL
c_func
(paren
id|framebuffer_alloc
)paren
suffix:semicolon
multiline_comment|/**&n; * framebuffer_release - marks the structure available for freeing&n; *&n; * @info: frame buffer info structure&n; *&n; * Drop the reference count of the class_device embedded in the&n; * framebuffer info structure.&n; *&n; */
DECL|function|framebuffer_release
r_void
id|framebuffer_release
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
(brace
id|kfree
c_func
(paren
id|info
)paren
suffix:semicolon
)brace
DECL|variable|framebuffer_release
id|EXPORT_SYMBOL
c_func
(paren
id|framebuffer_release
)paren
suffix:semicolon
DECL|function|activate
r_static
r_int
id|activate
c_func
(paren
r_struct
id|fb_info
op_star
id|fb_info
comma
r_struct
id|fb_var_screeninfo
op_star
id|var
)paren
(brace
r_int
id|err
suffix:semicolon
id|var-&gt;activate
op_or_assign
id|FB_ACTIVATE_FORCE
suffix:semicolon
id|acquire_console_sem
c_func
(paren
)paren
suffix:semicolon
id|fb_info-&gt;flags
op_or_assign
id|FBINFO_MISC_USEREVENT
suffix:semicolon
id|err
op_assign
id|fb_set_var
c_func
(paren
id|fb_info
comma
id|var
)paren
suffix:semicolon
id|fb_info-&gt;flags
op_and_assign
op_complement
id|FBINFO_MISC_USEREVENT
suffix:semicolon
id|release_console_sem
c_func
(paren
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mode_string
r_static
r_int
id|mode_string
c_func
(paren
r_char
op_star
id|buf
comma
r_int
r_int
id|offset
comma
r_const
r_struct
id|fb_videomode
op_star
id|mode
)paren
(brace
r_char
id|m
op_assign
l_char|&squot;U&squot;
suffix:semicolon
r_if
c_cond
(paren
id|mode-&gt;flag
op_amp
id|FB_MODE_IS_DETAILED
)paren
id|m
op_assign
l_char|&squot;D&squot;
suffix:semicolon
r_if
c_cond
(paren
id|mode-&gt;flag
op_amp
id|FB_MODE_IS_VESA
)paren
id|m
op_assign
l_char|&squot;V&squot;
suffix:semicolon
r_if
c_cond
(paren
id|mode-&gt;flag
op_amp
id|FB_MODE_IS_STANDARD
)paren
id|m
op_assign
l_char|&squot;S&squot;
suffix:semicolon
r_return
id|snprintf
c_func
(paren
op_amp
id|buf
(braket
id|offset
)braket
comma
id|PAGE_SIZE
op_minus
id|offset
comma
l_string|&quot;%c:%dx%d-%d&bslash;n&quot;
comma
id|m
comma
id|mode-&gt;xres
comma
id|mode-&gt;yres
comma
id|mode-&gt;refresh
)paren
suffix:semicolon
)brace
DECL|function|store_mode
r_static
id|ssize_t
id|store_mode
c_func
(paren
r_struct
id|class_device
op_star
id|class_device
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|fb_info
op_star
id|fb_info
op_assign
(paren
r_struct
id|fb_info
op_star
)paren
id|class_get_devdata
c_func
(paren
id|class_device
)paren
suffix:semicolon
r_char
id|mstr
(braket
l_int|100
)braket
suffix:semicolon
r_struct
id|fb_var_screeninfo
id|var
suffix:semicolon
r_struct
id|fb_modelist
op_star
id|modelist
suffix:semicolon
r_struct
id|fb_videomode
op_star
id|mode
suffix:semicolon
r_struct
id|list_head
op_star
id|pos
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|err
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|var
comma
l_int|0
comma
r_sizeof
(paren
id|var
)paren
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|pos
comma
op_amp
id|fb_info-&gt;modelist
)paren
(brace
id|modelist
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|fb_modelist
comma
id|list
)paren
suffix:semicolon
id|mode
op_assign
op_amp
id|modelist-&gt;mode
suffix:semicolon
id|i
op_assign
id|mode_string
c_func
(paren
id|mstr
comma
l_int|0
comma
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|mstr
comma
id|buf
comma
id|max
c_func
(paren
id|count
comma
id|i
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|var
op_assign
id|fb_info-&gt;var
suffix:semicolon
id|fb_videomode_to_var
c_func
(paren
op_amp
id|var
comma
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|activate
c_func
(paren
id|fb_info
comma
op_amp
id|var
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
id|fb_info-&gt;mode
op_assign
id|mode
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|show_mode
r_static
id|ssize_t
id|show_mode
c_func
(paren
r_struct
id|class_device
op_star
id|class_device
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|fb_info
op_star
id|fb_info
op_assign
(paren
r_struct
id|fb_info
op_star
)paren
id|class_get_devdata
c_func
(paren
id|class_device
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fb_info-&gt;mode
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|mode_string
c_func
(paren
id|buf
comma
l_int|0
comma
id|fb_info-&gt;mode
)paren
suffix:semicolon
)brace
DECL|function|store_modes
r_static
id|ssize_t
id|store_modes
c_func
(paren
r_struct
id|class_device
op_star
id|class_device
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|fb_info
op_star
id|fb_info
op_assign
(paren
r_struct
id|fb_info
op_star
)paren
id|class_get_devdata
c_func
(paren
id|class_device
)paren
suffix:semicolon
id|LIST_HEAD
c_func
(paren
id|old_list
)paren
suffix:semicolon
r_int
id|i
op_assign
id|count
op_div
r_sizeof
(paren
r_struct
id|fb_videomode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_star
r_sizeof
(paren
r_struct
id|fb_videomode
)paren
op_ne
id|count
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|acquire_console_sem
c_func
(paren
)paren
suffix:semicolon
id|list_splice
c_func
(paren
op_amp
id|fb_info-&gt;modelist
comma
op_amp
id|old_list
)paren
suffix:semicolon
id|fb_videomode_to_modelist
c_func
(paren
(paren
r_struct
id|fb_videomode
op_star
)paren
id|buf
comma
id|i
comma
op_amp
id|fb_info-&gt;modelist
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fb_new_modelist
c_func
(paren
id|fb_info
)paren
)paren
(brace
id|fb_destroy_modelist
c_func
(paren
op_amp
id|fb_info-&gt;modelist
)paren
suffix:semicolon
id|list_splice
c_func
(paren
op_amp
id|old_list
comma
op_amp
id|fb_info-&gt;modelist
)paren
suffix:semicolon
)brace
r_else
id|fb_destroy_modelist
c_func
(paren
op_amp
id|old_list
)paren
suffix:semicolon
id|release_console_sem
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|show_modes
r_static
id|ssize_t
id|show_modes
c_func
(paren
r_struct
id|class_device
op_star
id|class_device
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|fb_info
op_star
id|fb_info
op_assign
(paren
r_struct
id|fb_info
op_star
)paren
id|class_get_devdata
c_func
(paren
id|class_device
)paren
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_struct
id|list_head
op_star
id|pos
suffix:semicolon
r_struct
id|fb_modelist
op_star
id|modelist
suffix:semicolon
r_const
r_struct
id|fb_videomode
op_star
id|mode
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
id|list_for_each
c_func
(paren
id|pos
comma
op_amp
id|fb_info-&gt;modelist
)paren
(brace
id|modelist
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|fb_modelist
comma
id|list
)paren
suffix:semicolon
id|mode
op_assign
op_amp
id|modelist-&gt;mode
suffix:semicolon
id|i
op_add_assign
id|mode_string
c_func
(paren
id|buf
comma
id|i
comma
id|mode
)paren
suffix:semicolon
)brace
r_return
id|i
suffix:semicolon
)brace
DECL|function|store_bpp
r_static
id|ssize_t
id|store_bpp
c_func
(paren
r_struct
id|class_device
op_star
id|class_device
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|fb_info
op_star
id|fb_info
op_assign
(paren
r_struct
id|fb_info
op_star
)paren
id|class_get_devdata
c_func
(paren
id|class_device
)paren
suffix:semicolon
r_struct
id|fb_var_screeninfo
id|var
suffix:semicolon
r_char
op_star
op_star
id|last
op_assign
l_int|NULL
suffix:semicolon
r_int
id|err
suffix:semicolon
id|var
op_assign
id|fb_info-&gt;var
suffix:semicolon
id|var.bits_per_pixel
op_assign
id|simple_strtoul
c_func
(paren
id|buf
comma
id|last
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|activate
c_func
(paren
id|fb_info
comma
op_amp
id|var
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|show_bpp
r_static
id|ssize_t
id|show_bpp
c_func
(paren
r_struct
id|class_device
op_star
id|class_device
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|fb_info
op_star
id|fb_info
op_assign
(paren
r_struct
id|fb_info
op_star
)paren
id|class_get_devdata
c_func
(paren
id|class_device
)paren
suffix:semicolon
r_return
id|snprintf
c_func
(paren
id|buf
comma
id|PAGE_SIZE
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|fb_info-&gt;var.bits_per_pixel
)paren
suffix:semicolon
)brace
DECL|function|store_virtual
r_static
id|ssize_t
id|store_virtual
c_func
(paren
r_struct
id|class_device
op_star
id|class_device
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|fb_info
op_star
id|fb_info
op_assign
(paren
r_struct
id|fb_info
op_star
)paren
id|class_get_devdata
c_func
(paren
id|class_device
)paren
suffix:semicolon
r_struct
id|fb_var_screeninfo
id|var
suffix:semicolon
r_char
op_star
id|last
op_assign
l_int|NULL
suffix:semicolon
r_int
id|err
suffix:semicolon
id|var
op_assign
id|fb_info-&gt;var
suffix:semicolon
id|var.xres_virtual
op_assign
id|simple_strtoul
c_func
(paren
id|buf
comma
op_amp
id|last
comma
l_int|0
)paren
suffix:semicolon
id|last
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|last
op_minus
id|buf
op_ge
id|count
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|var.yres_virtual
op_assign
id|simple_strtoul
c_func
(paren
id|last
comma
op_amp
id|last
comma
l_int|0
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;fb: xres %d yres %d&bslash;n&quot;
comma
id|var.xres_virtual
comma
id|var.yres_virtual
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|activate
c_func
(paren
id|fb_info
comma
op_amp
id|var
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|show_virtual
r_static
id|ssize_t
id|show_virtual
c_func
(paren
r_struct
id|class_device
op_star
id|class_device
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|fb_info
op_star
id|fb_info
op_assign
(paren
r_struct
id|fb_info
op_star
)paren
id|class_get_devdata
c_func
(paren
id|class_device
)paren
suffix:semicolon
r_return
id|snprintf
c_func
(paren
id|buf
comma
id|PAGE_SIZE
comma
l_string|&quot;%d,%d&bslash;n&quot;
comma
id|fb_info-&gt;var.xres_virtual
comma
id|fb_info-&gt;var.xres_virtual
)paren
suffix:semicolon
)brace
DECL|function|store_cmap
r_static
id|ssize_t
id|store_cmap
c_func
(paren
r_struct
id|class_device
op_star
id|class_device
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
singleline_comment|//&t;struct fb_info *fb_info = (struct fb_info *)class_get_devdata(class_device);
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|show_cmap
r_static
id|ssize_t
id|show_cmap
c_func
(paren
r_struct
id|class_device
op_star
id|class_device
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|fb_info
op_star
id|fb_info
op_assign
(paren
r_struct
id|fb_info
op_star
)paren
id|class_get_devdata
c_func
(paren
id|class_device
)paren
suffix:semicolon
r_int
r_int
id|offset
op_assign
l_int|0
comma
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fb_info-&gt;cmap.red
op_logical_or
op_logical_neg
id|fb_info-&gt;cmap.blue
op_logical_or
id|fb_info-&gt;cmap.green
op_logical_or
id|fb_info-&gt;cmap.transp
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
id|fb_info-&gt;cmap.len
suffix:semicolon
id|i
op_increment
)paren
(brace
id|offset
op_add_assign
id|snprintf
c_func
(paren
id|buf
comma
id|PAGE_SIZE
op_minus
id|offset
comma
l_string|&quot;%d,%d,%d,%d,%d&bslash;n&quot;
comma
id|i
op_plus
id|fb_info-&gt;cmap.start
comma
id|fb_info-&gt;cmap.red
(braket
id|i
)braket
comma
id|fb_info-&gt;cmap.blue
(braket
id|i
)braket
comma
id|fb_info-&gt;cmap.green
(braket
id|i
)braket
comma
id|fb_info-&gt;cmap.transp
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_return
id|offset
suffix:semicolon
)brace
DECL|function|store_blank
r_static
id|ssize_t
id|store_blank
c_func
(paren
r_struct
id|class_device
op_star
id|class_device
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|fb_info
op_star
id|fb_info
op_assign
(paren
r_struct
id|fb_info
op_star
)paren
id|class_get_devdata
c_func
(paren
id|class_device
)paren
suffix:semicolon
r_char
op_star
id|last
op_assign
l_int|NULL
suffix:semicolon
r_int
id|err
suffix:semicolon
id|acquire_console_sem
c_func
(paren
)paren
suffix:semicolon
id|fb_info-&gt;flags
op_or_assign
id|FBINFO_MISC_USEREVENT
suffix:semicolon
id|err
op_assign
id|fb_blank
c_func
(paren
id|fb_info
comma
id|simple_strtoul
c_func
(paren
id|buf
comma
op_amp
id|last
comma
l_int|0
)paren
)paren
suffix:semicolon
id|fb_info-&gt;flags
op_and_assign
op_complement
id|FBINFO_MISC_USEREVENT
suffix:semicolon
id|release_console_sem
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|show_blank
r_static
id|ssize_t
id|show_blank
c_func
(paren
r_struct
id|class_device
op_star
id|class_device
comma
r_char
op_star
id|buf
)paren
(brace
singleline_comment|//&t;struct fb_info *fb_info = (struct fb_info *)class_get_devdata(class_device);
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|store_console
r_static
id|ssize_t
id|store_console
c_func
(paren
r_struct
id|class_device
op_star
id|class_device
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
singleline_comment|//&t;struct fb_info *fb_info = (struct fb_info *)class_get_devdata(class_device);
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|show_console
r_static
id|ssize_t
id|show_console
c_func
(paren
r_struct
id|class_device
op_star
id|class_device
comma
r_char
op_star
id|buf
)paren
(brace
singleline_comment|//&t;struct fb_info *fb_info = (struct fb_info *)class_get_devdata(class_device);
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|store_cursor
r_static
id|ssize_t
id|store_cursor
c_func
(paren
r_struct
id|class_device
op_star
id|class_device
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
singleline_comment|//&t;struct fb_info *fb_info = (struct fb_info *)class_get_devdata(class_device);
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|show_cursor
r_static
id|ssize_t
id|show_cursor
c_func
(paren
r_struct
id|class_device
op_star
id|class_device
comma
r_char
op_star
id|buf
)paren
(brace
singleline_comment|//&t;struct fb_info *fb_info = (struct fb_info *)class_get_devdata(class_device);
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|store_pan
r_static
id|ssize_t
id|store_pan
c_func
(paren
r_struct
id|class_device
op_star
id|class_device
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|fb_info
op_star
id|fb_info
op_assign
(paren
r_struct
id|fb_info
op_star
)paren
id|class_get_devdata
c_func
(paren
id|class_device
)paren
suffix:semicolon
r_struct
id|fb_var_screeninfo
id|var
suffix:semicolon
r_char
op_star
id|last
op_assign
l_int|NULL
suffix:semicolon
r_int
id|err
suffix:semicolon
id|var
op_assign
id|fb_info-&gt;var
suffix:semicolon
id|var.xoffset
op_assign
id|simple_strtoul
c_func
(paren
id|buf
comma
op_amp
id|last
comma
l_int|0
)paren
suffix:semicolon
id|last
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|last
op_minus
id|buf
op_ge
id|count
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|var.yoffset
op_assign
id|simple_strtoul
c_func
(paren
id|last
comma
op_amp
id|last
comma
l_int|0
)paren
suffix:semicolon
id|acquire_console_sem
c_func
(paren
)paren
suffix:semicolon
id|err
op_assign
id|fb_pan_display
c_func
(paren
id|fb_info
comma
op_amp
id|var
)paren
suffix:semicolon
id|release_console_sem
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|show_pan
r_static
id|ssize_t
id|show_pan
c_func
(paren
r_struct
id|class_device
op_star
id|class_device
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|fb_info
op_star
id|fb_info
op_assign
(paren
r_struct
id|fb_info
op_star
)paren
id|class_get_devdata
c_func
(paren
id|class_device
)paren
suffix:semicolon
r_return
id|snprintf
c_func
(paren
id|buf
comma
id|PAGE_SIZE
comma
l_string|&quot;%d,%d&bslash;n&quot;
comma
id|fb_info-&gt;var.xoffset
comma
id|fb_info-&gt;var.xoffset
)paren
suffix:semicolon
)brace
DECL|variable|class_device_attrs
r_struct
id|class_device_attribute
id|class_device_attrs
(braket
)braket
op_assign
(brace
id|__ATTR
c_func
(paren
id|bits_per_pixel
comma
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|show_bpp
comma
id|store_bpp
)paren
comma
id|__ATTR
c_func
(paren
id|blank
comma
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|show_blank
comma
id|store_blank
)paren
comma
id|__ATTR
c_func
(paren
id|color_map
comma
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|show_cmap
comma
id|store_cmap
)paren
comma
id|__ATTR
c_func
(paren
id|console
comma
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|show_console
comma
id|store_console
)paren
comma
id|__ATTR
c_func
(paren
id|cursor
comma
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|show_cursor
comma
id|store_cursor
)paren
comma
id|__ATTR
c_func
(paren
id|mode
comma
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|show_mode
comma
id|store_mode
)paren
comma
id|__ATTR
c_func
(paren
id|modes
comma
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|show_modes
comma
id|store_modes
)paren
comma
id|__ATTR
c_func
(paren
id|pan
comma
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|show_pan
comma
id|store_pan
)paren
comma
id|__ATTR
c_func
(paren
id|virtual_size
comma
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|show_virtual
comma
id|store_virtual
)paren
comma
)brace
suffix:semicolon
DECL|function|fb_init_class_device
r_int
id|fb_init_class_device
c_func
(paren
r_struct
id|fb_info
op_star
id|fb_info
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
id|class_set_devdata
c_func
(paren
id|fb_info-&gt;class_device
comma
id|fb_info
)paren
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
id|ARRAY_SIZE
c_func
(paren
id|class_device_attrs
)paren
suffix:semicolon
id|i
op_increment
)paren
id|class_device_create_file
c_func
(paren
id|fb_info-&gt;class_device
comma
op_amp
id|class_device_attrs
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fb_cleanup_class_device
r_void
id|fb_cleanup_class_device
c_func
(paren
r_struct
id|fb_info
op_star
id|fb_info
)paren
(brace
r_int
r_int
id|i
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
id|ARRAY_SIZE
c_func
(paren
id|class_device_attrs
)paren
suffix:semicolon
id|i
op_increment
)paren
id|class_device_remove_file
c_func
(paren
id|fb_info-&gt;class_device
comma
op_amp
id|class_device_attrs
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
eof
