multiline_comment|/*&n; * Copyright (C) Paul Mackerras 1997.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &quot;nonstdio.h&quot;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/* Passed from the linker */
r_extern
r_char
id|__image_begin
comma
id|__image_end
suffix:semicolon
r_extern
r_char
id|__ramdisk_begin
(braket
)braket
comma
id|__ramdisk_end
suffix:semicolon
r_extern
r_char
id|_start
comma
id|_end
suffix:semicolon
r_extern
r_int
id|getprop
c_func
(paren
r_void
op_star
comma
r_const
r_char
op_star
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|heap_max
suffix:semicolon
r_extern
r_void
id|claim
c_func
(paren
r_int
r_int
id|virt
comma
r_int
r_int
id|size
comma
r_int
r_int
id|align
)paren
suffix:semicolon
r_extern
r_void
op_star
id|finddevice
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|flush_cache
c_func
(paren
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|gunzip
c_func
(paren
r_void
op_star
comma
r_int
comma
r_int
r_char
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
id|make_bi_recs
c_func
(paren
r_int
r_int
id|addr
comma
r_char
op_star
id|name
comma
r_int
r_int
id|mach
comma
r_int
r_int
id|progend
)paren
suffix:semicolon
r_extern
r_void
id|pause
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|avail_ram
r_char
op_star
id|avail_ram
suffix:semicolon
DECL|variable|begin_avail
DECL|variable|end_avail
r_char
op_star
id|begin_avail
comma
op_star
id|end_avail
suffix:semicolon
DECL|variable|avail_high
r_char
op_star
id|avail_high
suffix:semicolon
DECL|macro|RAM_START
mdefine_line|#define RAM_START&t;0x00000000
DECL|macro|RAM_END
mdefine_line|#define RAM_END&t;&t;(64&lt;&lt;20)
DECL|macro|BOOT_START
mdefine_line|#define BOOT_START&t;((unsigned long)_start)
DECL|macro|BOOT_END
mdefine_line|#define BOOT_END&t;((unsigned long)(_end + 0xFFF) &amp; ~0xFFF)
DECL|macro|RAM_FREE
mdefine_line|#define RAM_FREE&t;((unsigned long)(_end+0x1000)&amp;~0xFFF)
DECL|macro|PROG_START
mdefine_line|#define PROG_START&t;0x00010000
DECL|macro|PROG_SIZE
mdefine_line|#define PROG_SIZE&t;0x00400000 /* 4MB */
DECL|macro|SCRATCH_SIZE
mdefine_line|#define SCRATCH_SIZE&t;(128 &lt;&lt; 10)
DECL|variable|scratch
r_static
r_char
id|scratch
(braket
id|SCRATCH_SIZE
)braket
suffix:semicolon
multiline_comment|/* 1MB of scratch space for gunzip */
DECL|typedef|kernel_start_t
r_typedef
r_void
(paren
op_star
id|kernel_start_t
)paren
(paren
r_int
comma
r_int
comma
r_void
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_void
DECL|function|chrpboot
id|chrpboot
c_func
(paren
r_int
id|a1
comma
r_int
id|a2
comma
r_void
op_star
id|prom
)paren
(brace
r_int
id|sa
comma
id|len
suffix:semicolon
r_void
op_star
id|dst
suffix:semicolon
r_int
r_char
op_star
id|im
suffix:semicolon
r_int
r_int
id|initrd_size
comma
id|initrd_start
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;chrpboot starting: loaded at 0x%p&bslash;n&bslash;r&quot;
comma
op_amp
id|_start
)paren
suffix:semicolon
id|initrd_size
op_assign
(paren
r_char
op_star
)paren
(paren
op_amp
id|__ramdisk_end
)paren
op_minus
(paren
r_char
op_star
)paren
(paren
op_amp
id|__ramdisk_begin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|initrd_size
)paren
(brace
id|initrd_start
op_assign
(paren
id|RAM_END
op_minus
id|initrd_size
)paren
op_amp
op_complement
l_int|0xFFF
suffix:semicolon
id|a1
op_assign
id|initrd_start
suffix:semicolon
id|a2
op_assign
id|initrd_size
suffix:semicolon
id|claim
c_func
(paren
id|initrd_start
comma
id|RAM_END
op_minus
id|initrd_start
comma
l_int|0
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;initial ramdisk moving 0x%x &lt;- 0x%p (%x bytes)&bslash;n&bslash;r&quot;
comma
id|initrd_start
comma
(paren
r_char
op_star
)paren
(paren
op_amp
id|__ramdisk_begin
)paren
comma
id|initrd_size
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_char
op_star
)paren
id|initrd_start
comma
(paren
r_char
op_star
)paren
(paren
op_amp
id|__ramdisk_begin
)paren
comma
id|initrd_size
)paren
suffix:semicolon
)brace
r_else
(brace
id|initrd_start
op_assign
l_int|0
suffix:semicolon
id|initrd_size
op_assign
l_int|0
suffix:semicolon
id|a2
op_assign
l_int|0xdeadbeef
suffix:semicolon
)brace
id|im
op_assign
(paren
r_char
op_star
)paren
(paren
op_amp
id|__image_begin
)paren
suffix:semicolon
id|len
op_assign
(paren
r_char
op_star
)paren
(paren
op_amp
id|__image_end
)paren
op_minus
(paren
r_char
op_star
)paren
(paren
op_amp
id|__image_begin
)paren
suffix:semicolon
multiline_comment|/* claim 4MB starting at PROG_START */
id|claim
c_func
(paren
id|PROG_START
comma
id|PROG_SIZE
op_minus
id|PROG_START
comma
l_int|0
)paren
suffix:semicolon
id|dst
op_assign
(paren
r_void
op_star
)paren
id|PROG_START
suffix:semicolon
r_if
c_cond
(paren
id|im
(braket
l_int|0
)braket
op_eq
l_int|0x1f
op_logical_and
id|im
(braket
l_int|1
)braket
op_eq
l_int|0x8b
)paren
(brace
id|avail_ram
op_assign
id|scratch
suffix:semicolon
id|begin_avail
op_assign
id|avail_high
op_assign
id|avail_ram
suffix:semicolon
id|end_avail
op_assign
id|scratch
op_plus
r_sizeof
(paren
id|scratch
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;gunzipping (0x%p &lt;- 0x%p:0x%p)...&quot;
comma
id|dst
comma
id|im
comma
id|im
op_plus
id|len
)paren
suffix:semicolon
id|gunzip
c_func
(paren
id|dst
comma
l_int|0x400000
comma
id|im
comma
op_amp
id|len
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;done %u bytes&bslash;n&bslash;r&quot;
comma
id|len
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%u bytes of heap consumed, max in use %u&bslash;n&bslash;r&quot;
comma
id|avail_high
op_minus
id|begin_avail
comma
id|heap_max
)paren
suffix:semicolon
)brace
r_else
(brace
id|memmove
c_func
(paren
id|dst
comma
id|im
comma
id|len
)paren
suffix:semicolon
)brace
id|flush_cache
c_func
(paren
id|dst
comma
id|len
)paren
suffix:semicolon
id|make_bi_recs
c_func
(paren
(paren
(paren
r_int
r_int
)paren
id|dst
op_plus
id|len
)paren
comma
l_string|&quot;chrpboot&quot;
comma
id|_MACH_chrp
comma
(paren
id|PROG_START
op_plus
id|PROG_SIZE
)paren
)paren
suffix:semicolon
id|sa
op_assign
id|PROG_START
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;start address = 0x%x&bslash;n&bslash;r&quot;
comma
id|sa
)paren
suffix:semicolon
(paren
op_star
(paren
id|kernel_start_t
)paren
id|sa
)paren
(paren
id|a1
comma
id|a2
comma
id|prom
comma
id|initrd_start
comma
id|initrd_size
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;returned?&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
id|pause
c_func
(paren
)paren
suffix:semicolon
)brace
eof
