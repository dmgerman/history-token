multiline_comment|/*&n; * Copyright (C) Paul Mackerras 1997.&n; *&n; * Updates for PPC64 by Todd Inglett, Dave Engebretsen &amp; Peter Bergner.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &quot;ppc32-types.h&quot;
macro_line|#include &quot;zlib.h&quot;
macro_line|#include &lt;linux/elf.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
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
r_void
id|printk
c_func
(paren
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_void
id|printf
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_int
id|sprintf
c_func
(paren
r_char
op_star
id|buf
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
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
r_void
op_star
id|claim
c_func
(paren
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
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
r_void
id|pause
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
m_exit
(paren
r_void
)paren
suffix:semicolon
r_int
r_int
id|strlen
c_func
(paren
r_const
r_char
op_star
id|s
)paren
suffix:semicolon
r_void
op_star
id|memmove
c_func
(paren
r_void
op_star
id|dest
comma
r_const
r_void
op_star
id|src
comma
r_int
r_int
id|n
)paren
suffix:semicolon
r_void
op_star
id|memcpy
c_func
(paren
r_void
op_star
id|dest
comma
r_const
r_void
op_star
id|src
comma
r_int
r_int
id|n
)paren
suffix:semicolon
r_static
r_struct
id|bi_record
op_star
id|make_bi_recs
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|macro|RAM_START
mdefine_line|#define RAM_START&t;0x00000000
DECL|macro|RAM_END
mdefine_line|#define RAM_END&t;&t;(64&lt;&lt;20)
multiline_comment|/* Value picked to match that used by yaboot */
DECL|macro|PROG_START
mdefine_line|#define PROG_START&t;0x01400000
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
DECL|variable|heap_use
r_int
r_int
id|heap_use
suffix:semicolon
DECL|variable|heap_max
r_int
r_int
id|heap_max
suffix:semicolon
r_extern
r_char
id|_start
(braket
)braket
suffix:semicolon
r_extern
r_char
id|_vmlinux_start
(braket
)braket
suffix:semicolon
r_extern
r_char
id|_vmlinux_end
(braket
)braket
suffix:semicolon
r_extern
r_char
id|_sysmap_start
(braket
)braket
suffix:semicolon
r_extern
r_char
id|_sysmap_end
(braket
)braket
suffix:semicolon
r_extern
r_char
id|_initrd_start
(braket
)braket
suffix:semicolon
r_extern
r_char
id|_initrd_end
(braket
)braket
suffix:semicolon
r_extern
r_int
r_int
id|vmlinux_filesize
suffix:semicolon
r_extern
r_int
r_int
id|vmlinux_memsize
suffix:semicolon
DECL|struct|addr_range
r_struct
id|addr_range
(brace
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|memsize
r_int
r_int
id|memsize
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|vmlinux
r_struct
id|addr_range
id|vmlinux
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|vmlinuz
r_struct
id|addr_range
id|vmlinuz
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|sysmap
r_struct
id|addr_range
id|sysmap
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|initrd
r_struct
id|addr_range
id|initrd
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|scratch
r_static
r_char
id|scratch
(braket
l_int|128
op_lshift
l_int|10
)braket
suffix:semicolon
multiline_comment|/* 128kB of scratch space for gunzip */
DECL|typedef|kernel_entry_t
r_typedef
r_void
(paren
op_star
id|kernel_entry_t
)paren
(paren
r_int
r_int
comma
r_int
r_int
comma
r_void
op_star
comma
r_struct
id|bi_record
op_star
)paren
suffix:semicolon
DECL|variable|prom
r_int
(paren
op_star
id|prom
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|variable|chosen_handle
r_void
op_star
id|chosen_handle
suffix:semicolon
DECL|variable|stdin
r_void
op_star
id|stdin
suffix:semicolon
DECL|variable|stdout
r_void
op_star
id|stdout
suffix:semicolon
DECL|variable|stderr
r_void
op_star
id|stderr
suffix:semicolon
r_void
DECL|function|start
id|start
c_func
(paren
r_int
r_int
id|a1
comma
r_int
r_int
id|a2
comma
r_void
op_star
id|promptr
)paren
(brace
r_int
r_int
id|i
comma
id|claim_addr
comma
id|claim_size
suffix:semicolon
r_struct
id|bi_record
op_star
id|bi_recs
suffix:semicolon
id|kernel_entry_t
id|kernel_entry
suffix:semicolon
id|Elf64_Ehdr
op_star
id|elf64
suffix:semicolon
id|Elf64_Phdr
op_star
id|elf64ph
suffix:semicolon
id|prom
op_assign
(paren
r_int
(paren
op_star
)paren
(paren
r_void
op_star
)paren
)paren
id|promptr
suffix:semicolon
id|chosen_handle
op_assign
id|finddevice
c_func
(paren
l_string|&quot;/chosen&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chosen_handle
op_eq
(paren
r_void
op_star
)paren
op_minus
l_int|1
)paren
m_exit
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|getprop
c_func
(paren
id|chosen_handle
comma
l_string|&quot;stdout&quot;
comma
op_amp
id|stdout
comma
r_sizeof
(paren
id|stdout
)paren
)paren
op_ne
l_int|4
)paren
m_exit
(paren
)paren
suffix:semicolon
id|stderr
op_assign
id|stdout
suffix:semicolon
r_if
c_cond
(paren
id|getprop
c_func
(paren
id|chosen_handle
comma
l_string|&quot;stdin&quot;
comma
op_amp
id|stdin
comma
r_sizeof
(paren
id|stdin
)paren
)paren
op_ne
l_int|4
)paren
m_exit
(paren
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;zImage starting: loaded at 0x%x&bslash;n&bslash;r&quot;
comma
(paren
r_int
)paren
id|_start
)paren
suffix:semicolon
macro_line|#if 0
id|sysmap.size
op_assign
(paren
r_int
r_int
)paren
(paren
id|_sysmap_end
op_minus
id|_sysmap_start
)paren
suffix:semicolon
id|sysmap.memsize
op_assign
id|sysmap.size
suffix:semicolon
r_if
c_cond
(paren
id|sysmap.size
OG
l_int|0
)paren
(brace
id|sysmap.addr
op_assign
(paren
id|RAM_END
op_minus
id|sysmap.size
)paren
op_amp
op_complement
l_int|0xFFF
suffix:semicolon
id|claim
c_func
(paren
id|sysmap.addr
comma
id|RAM_END
op_minus
id|sysmap.addr
comma
l_int|0
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;initial ramdisk moving 0x%lx &lt;- 0x%lx (%lx bytes)&bslash;n&bslash;r&quot;
comma
id|sysmap.addr
comma
(paren
r_int
r_int
)paren
id|_sysmap_start
comma
id|sysmap.size
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|sysmap.addr
comma
(paren
r_void
op_star
)paren
id|_sysmap_start
comma
id|sysmap.size
)paren
suffix:semicolon
)brace
macro_line|#endif
id|initrd.size
op_assign
(paren
r_int
r_int
)paren
(paren
id|_initrd_end
op_minus
id|_initrd_start
)paren
suffix:semicolon
id|initrd.memsize
op_assign
id|initrd.size
suffix:semicolon
r_if
c_cond
(paren
id|initrd.size
OG
l_int|0
)paren
(brace
id|initrd.addr
op_assign
(paren
id|RAM_END
op_minus
id|initrd.size
)paren
op_amp
op_complement
l_int|0xFFF
suffix:semicolon
id|a1
op_assign
id|a2
op_assign
l_int|0
suffix:semicolon
id|claim
c_func
(paren
id|initrd.addr
comma
id|RAM_END
op_minus
id|initrd.addr
comma
l_int|0
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;initial ramdisk moving 0x%lx &lt;- 0x%lx (%lx bytes)&bslash;n&bslash;r&quot;
comma
id|initrd.addr
comma
(paren
r_int
r_int
)paren
id|_initrd_start
comma
id|initrd.size
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|initrd.addr
comma
(paren
r_void
op_star
)paren
id|_initrd_start
comma
id|initrd.size
)paren
suffix:semicolon
)brace
id|vmlinuz.addr
op_assign
(paren
r_int
r_int
)paren
id|_vmlinux_start
suffix:semicolon
id|vmlinuz.size
op_assign
(paren
r_int
r_int
)paren
(paren
id|_vmlinux_end
op_minus
id|_vmlinux_start
)paren
suffix:semicolon
id|vmlinux.addr
op_assign
(paren
r_int
r_int
)paren
(paren
r_void
op_star
)paren
op_minus
l_int|1
suffix:semicolon
id|vmlinux.size
op_assign
id|PAGE_ALIGN
c_func
(paren
id|vmlinux_filesize
)paren
suffix:semicolon
id|vmlinux.memsize
op_assign
id|vmlinux_memsize
suffix:semicolon
id|claim_size
op_assign
id|vmlinux.memsize
multiline_comment|/* PPPBBB: + fudge for bi_recs */
suffix:semicolon
r_for
c_loop
(paren
id|claim_addr
op_assign
id|PROG_START
suffix:semicolon
id|claim_addr
op_le
id|PROG_START
op_star
l_int|8
suffix:semicolon
id|claim_addr
op_add_assign
l_int|0x100000
)paren
(brace
macro_line|#ifdef DEBUG
id|printf
c_func
(paren
l_string|&quot;    trying: 0x%08lx&bslash;n&bslash;r&quot;
comma
id|claim_addr
)paren
suffix:semicolon
macro_line|#endif
id|vmlinux.addr
op_assign
(paren
r_int
r_int
)paren
id|claim
c_func
(paren
id|claim_addr
comma
id|claim_size
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_void
op_star
)paren
id|vmlinux.addr
op_ne
(paren
r_void
op_star
)paren
op_minus
l_int|1
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
r_void
op_star
)paren
id|vmlinux.addr
op_eq
(paren
r_void
op_star
)paren
op_minus
l_int|1
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;claim error, can&squot;t allocate kernel memory&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
m_exit
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* PPPBBB: should kernel always be gziped? */
r_if
c_cond
(paren
op_star
(paren
r_int
r_int
op_star
)paren
id|vmlinuz.addr
op_eq
l_int|0x1f8b
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
l_string|&quot;gunzipping (0x%lx &lt;- 0x%lx:0x%0lx)...&quot;
comma
id|vmlinux.addr
comma
id|vmlinuz.addr
comma
id|vmlinuz.addr
op_plus
id|vmlinuz.size
)paren
suffix:semicolon
id|gunzip
c_func
(paren
(paren
r_void
op_star
)paren
id|vmlinux.addr
comma
id|vmlinux.size
comma
(paren
r_int
r_char
op_star
)paren
id|vmlinuz.addr
comma
(paren
r_int
op_star
)paren
op_amp
id|vmlinuz.size
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;done %lu bytes&bslash;n&bslash;r&quot;
comma
id|vmlinuz.size
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%u bytes of heap consumed, max in use %u&bslash;n&bslash;r&quot;
comma
(paren
r_int
)paren
(paren
id|avail_high
op_minus
id|begin_avail
)paren
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
(paren
r_void
op_star
)paren
id|vmlinux.addr
comma
(paren
r_void
op_star
)paren
id|vmlinuz.addr
comma
id|vmlinuz.size
)paren
suffix:semicolon
)brace
multiline_comment|/* Skip over the ELF header */
id|elf64
op_assign
(paren
id|Elf64_Ehdr
op_star
)paren
id|vmlinux.addr
suffix:semicolon
r_if
c_cond
(paren
id|elf64-&gt;e_ident
(braket
id|EI_MAG0
)braket
op_ne
id|ELFMAG0
op_logical_or
id|elf64-&gt;e_ident
(braket
id|EI_MAG1
)braket
op_ne
id|ELFMAG1
op_logical_or
id|elf64-&gt;e_ident
(braket
id|EI_MAG2
)braket
op_ne
id|ELFMAG2
op_logical_or
id|elf64-&gt;e_ident
(braket
id|EI_MAG3
)braket
op_ne
id|ELFMAG3
op_logical_or
id|elf64-&gt;e_ident
(braket
id|EI_CLASS
)braket
op_ne
id|ELFCLASS64
op_logical_or
id|elf64-&gt;e_ident
(braket
id|EI_DATA
)braket
op_ne
id|ELFDATA2MSB
op_logical_or
id|elf64-&gt;e_type
op_ne
id|ET_EXEC
op_logical_or
id|elf64-&gt;e_machine
op_ne
id|EM_PPC64
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;Error: not a valid PPC64 ELF file!&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
m_exit
(paren
)paren
suffix:semicolon
)brace
id|elf64ph
op_assign
(paren
id|Elf64_Phdr
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|elf64
op_plus
(paren
r_int
r_int
)paren
id|elf64-&gt;e_phoff
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
(paren
r_int
r_int
)paren
id|elf64-&gt;e_phnum
suffix:semicolon
id|i
op_increment
comma
id|elf64ph
op_increment
)paren
(brace
r_if
c_cond
(paren
id|elf64ph-&gt;p_type
op_eq
id|PT_LOAD
op_logical_and
id|elf64ph-&gt;p_offset
op_ne
l_int|0
)paren
r_break
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
id|printf
c_func
(paren
l_string|&quot;... skipping 0x%lx bytes of ELF header&bslash;n&bslash;r&quot;
comma
(paren
r_int
r_int
)paren
id|elf64ph-&gt;p_offset
)paren
suffix:semicolon
macro_line|#endif
id|vmlinux.addr
op_add_assign
(paren
r_int
r_int
)paren
id|elf64ph-&gt;p_offset
suffix:semicolon
id|vmlinux.size
op_sub_assign
(paren
r_int
r_int
)paren
id|elf64ph-&gt;p_offset
suffix:semicolon
id|flush_cache
c_func
(paren
(paren
r_void
op_star
)paren
id|vmlinux.addr
comma
id|vmlinux.memsize
)paren
suffix:semicolon
id|bi_recs
op_assign
id|make_bi_recs
c_func
(paren
id|vmlinux.addr
op_plus
id|vmlinux.memsize
)paren
suffix:semicolon
id|kernel_entry
op_assign
(paren
id|kernel_entry_t
)paren
id|vmlinux.addr
suffix:semicolon
macro_line|#ifdef DEBUG
id|printf
c_func
(paren
l_string|&quot;kernel:&bslash;n&bslash;r&quot;
l_string|&quot;        entry addr = 0x%lx&bslash;n&bslash;r&quot;
l_string|&quot;        a1         = 0x%lx,&bslash;n&bslash;r&quot;
l_string|&quot;        a2         = 0x%lx,&bslash;n&bslash;r&quot;
l_string|&quot;        prom       = 0x%lx,&bslash;n&bslash;r&quot;
l_string|&quot;        bi_recs    = 0x%lx,&bslash;n&bslash;r&quot;
comma
(paren
r_int
r_int
)paren
id|kernel_entry
comma
id|a1
comma
id|a2
comma
(paren
r_int
r_int
)paren
id|prom
comma
(paren
r_int
r_int
)paren
id|bi_recs
)paren
suffix:semicolon
macro_line|#endif
id|kernel_entry
c_func
(paren
id|a1
comma
id|a2
comma
id|prom
comma
id|bi_recs
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;Error: Linux kernel returned to zImage bootloader!&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
m_exit
(paren
)paren
suffix:semicolon
)brace
r_static
r_struct
id|bi_record
op_star
DECL|function|make_bi_recs
id|make_bi_recs
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_struct
id|bi_record
op_star
id|bi_recs
suffix:semicolon
r_struct
id|bi_record
op_star
id|rec
suffix:semicolon
id|bi_recs
op_assign
id|rec
op_assign
id|bi_rec_init
c_func
(paren
id|addr
)paren
suffix:semicolon
id|rec
op_assign
id|bi_rec_alloc
c_func
(paren
id|rec
comma
l_int|2
)paren
suffix:semicolon
id|rec-&gt;tag
op_assign
id|BI_FIRST
suffix:semicolon
multiline_comment|/* rec-&gt;data[0] = ...;&t;# Written below before return */
multiline_comment|/* rec-&gt;data[1] = ...;&t;# Written below before return */
id|rec
op_assign
id|bi_rec_alloc_bytes
c_func
(paren
id|rec
comma
id|strlen
c_func
(paren
l_string|&quot;chrpboot&quot;
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|rec-&gt;tag
op_assign
id|BI_BOOTLOADER_ID
suffix:semicolon
id|sprintf
c_func
(paren
(paren
r_char
op_star
)paren
id|rec-&gt;data
comma
l_string|&quot;chrpboot&quot;
)paren
suffix:semicolon
id|rec
op_assign
id|bi_rec_alloc
c_func
(paren
id|rec
comma
l_int|2
)paren
suffix:semicolon
id|rec-&gt;tag
op_assign
id|BI_MACHTYPE
suffix:semicolon
id|rec-&gt;data
(braket
l_int|0
)braket
op_assign
id|PLATFORM_PSERIES
suffix:semicolon
id|rec-&gt;data
(braket
l_int|1
)braket
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|initrd.size
OG
l_int|0
)paren
(brace
id|rec
op_assign
id|bi_rec_alloc
c_func
(paren
id|rec
comma
l_int|2
)paren
suffix:semicolon
id|rec-&gt;tag
op_assign
id|BI_INITRD
suffix:semicolon
id|rec-&gt;data
(braket
l_int|0
)braket
op_assign
id|initrd.addr
suffix:semicolon
id|rec-&gt;data
(braket
l_int|1
)braket
op_assign
id|initrd.size
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sysmap.size
OG
l_int|0
)paren
(brace
id|rec
op_assign
id|bi_rec_alloc
c_func
(paren
id|rec
comma
l_int|2
)paren
suffix:semicolon
id|rec-&gt;tag
op_assign
id|BI_SYSMAP
suffix:semicolon
id|rec-&gt;data
(braket
l_int|0
)braket
op_assign
(paren
r_int
r_int
)paren
id|sysmap.addr
suffix:semicolon
id|rec-&gt;data
(braket
l_int|1
)braket
op_assign
(paren
r_int
r_int
)paren
id|sysmap.size
suffix:semicolon
)brace
id|rec
op_assign
id|bi_rec_alloc
c_func
(paren
id|rec
comma
l_int|1
)paren
suffix:semicolon
id|rec-&gt;tag
op_assign
id|BI_LAST
suffix:semicolon
id|rec-&gt;data
(braket
l_int|0
)braket
op_assign
(paren
id|bi_rec_field
)paren
id|bi_recs
suffix:semicolon
multiline_comment|/* Save the _end_ address of the bi_rec&squot;s in the first bi_rec&n;&t; * data field for easy access by the kernel.&n;&t; */
id|bi_recs-&gt;data
(braket
l_int|0
)braket
op_assign
(paren
id|bi_rec_field
)paren
id|rec
suffix:semicolon
id|bi_recs-&gt;data
(braket
l_int|1
)braket
op_assign
(paren
id|bi_rec_field
)paren
id|rec
op_plus
id|rec-&gt;size
op_minus
(paren
id|bi_rec_field
)paren
id|bi_recs
suffix:semicolon
r_return
id|bi_recs
suffix:semicolon
)brace
DECL|struct|memchunk
r_struct
id|memchunk
(brace
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|pad
r_int
r_int
id|pad
suffix:semicolon
DECL|member|next
r_struct
id|memchunk
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|freechunks
r_static
r_struct
id|memchunk
op_star
id|freechunks
suffix:semicolon
DECL|function|zalloc
r_void
op_star
id|zalloc
c_func
(paren
r_void
op_star
id|x
comma
r_int
id|items
comma
r_int
id|size
)paren
(brace
r_void
op_star
id|p
suffix:semicolon
r_struct
id|memchunk
op_star
op_star
id|mpp
comma
op_star
id|mp
suffix:semicolon
id|size
op_mul_assign
id|items
suffix:semicolon
id|size
op_assign
id|_ALIGN
c_func
(paren
id|size
comma
r_sizeof
(paren
r_struct
id|memchunk
)paren
)paren
suffix:semicolon
id|heap_use
op_add_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
id|heap_use
OG
id|heap_max
)paren
id|heap_max
op_assign
id|heap_use
suffix:semicolon
r_for
c_loop
(paren
id|mpp
op_assign
op_amp
id|freechunks
suffix:semicolon
(paren
id|mp
op_assign
op_star
id|mpp
)paren
op_ne
l_int|0
suffix:semicolon
id|mpp
op_assign
op_amp
id|mp-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|mp-&gt;size
op_eq
id|size
)paren
(brace
op_star
id|mpp
op_assign
id|mp-&gt;next
suffix:semicolon
r_return
id|mp
suffix:semicolon
)brace
)brace
id|p
op_assign
id|avail_ram
suffix:semicolon
id|avail_ram
op_add_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
id|avail_ram
OG
id|avail_high
)paren
id|avail_high
op_assign
id|avail_ram
suffix:semicolon
r_if
c_cond
(paren
id|avail_ram
OG
id|end_avail
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;oops... out of memory&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
id|pause
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|p
suffix:semicolon
)brace
DECL|function|zfree
r_void
id|zfree
c_func
(paren
r_void
op_star
id|x
comma
r_void
op_star
id|addr
comma
r_int
id|nb
)paren
(brace
r_struct
id|memchunk
op_star
id|mp
op_assign
id|addr
suffix:semicolon
id|nb
op_assign
id|_ALIGN
c_func
(paren
id|nb
comma
r_sizeof
(paren
r_struct
id|memchunk
)paren
)paren
suffix:semicolon
id|heap_use
op_sub_assign
id|nb
suffix:semicolon
r_if
c_cond
(paren
id|avail_ram
op_eq
id|addr
op_plus
id|nb
)paren
(brace
id|avail_ram
op_assign
id|addr
suffix:semicolon
r_return
suffix:semicolon
)brace
id|mp-&gt;size
op_assign
id|nb
suffix:semicolon
id|mp-&gt;next
op_assign
id|freechunks
suffix:semicolon
id|freechunks
op_assign
id|mp
suffix:semicolon
)brace
DECL|macro|HEAD_CRC
mdefine_line|#define HEAD_CRC&t;2
DECL|macro|EXTRA_FIELD
mdefine_line|#define EXTRA_FIELD&t;4
DECL|macro|ORIG_NAME
mdefine_line|#define ORIG_NAME&t;8
DECL|macro|COMMENT
mdefine_line|#define COMMENT&t;&t;0x10
DECL|macro|RESERVED
mdefine_line|#define RESERVED&t;0xe0
DECL|macro|DEFLATED
mdefine_line|#define DEFLATED&t;8
DECL|function|gunzip
r_void
id|gunzip
c_func
(paren
r_void
op_star
id|dst
comma
r_int
id|dstlen
comma
r_int
r_char
op_star
id|src
comma
r_int
op_star
id|lenp
)paren
(brace
id|z_stream
id|s
suffix:semicolon
r_int
id|r
comma
id|i
comma
id|flags
suffix:semicolon
multiline_comment|/* skip header */
id|i
op_assign
l_int|10
suffix:semicolon
id|flags
op_assign
id|src
(braket
l_int|3
)braket
suffix:semicolon
r_if
c_cond
(paren
id|src
(braket
l_int|2
)braket
op_ne
id|DEFLATED
op_logical_or
(paren
id|flags
op_amp
id|RESERVED
)paren
op_ne
l_int|0
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;bad gzipped data&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
m_exit
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|EXTRA_FIELD
)paren
op_ne
l_int|0
)paren
id|i
op_assign
l_int|12
op_plus
id|src
(braket
l_int|10
)braket
op_plus
(paren
id|src
(braket
l_int|11
)braket
op_lshift
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|ORIG_NAME
)paren
op_ne
l_int|0
)paren
r_while
c_loop
(paren
id|src
(braket
id|i
op_increment
)braket
op_ne
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|COMMENT
)paren
op_ne
l_int|0
)paren
r_while
c_loop
(paren
id|src
(braket
id|i
op_increment
)braket
op_ne
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|HEAD_CRC
)paren
op_ne
l_int|0
)paren
id|i
op_add_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
op_star
id|lenp
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;gunzip: ran out of data in header&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
m_exit
(paren
)paren
suffix:semicolon
)brace
id|s.zalloc
op_assign
id|zalloc
suffix:semicolon
id|s.zfree
op_assign
id|zfree
suffix:semicolon
id|r
op_assign
id|inflateInit2
c_func
(paren
op_amp
id|s
comma
op_minus
id|MAX_WBITS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_ne
id|Z_OK
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;inflateInit2 returned %d&bslash;n&bslash;r&quot;
comma
id|r
)paren
suffix:semicolon
m_exit
(paren
)paren
suffix:semicolon
)brace
id|s.next_in
op_assign
id|src
op_plus
id|i
suffix:semicolon
id|s.avail_in
op_assign
op_star
id|lenp
op_minus
id|i
suffix:semicolon
id|s.next_out
op_assign
id|dst
suffix:semicolon
id|s.avail_out
op_assign
id|dstlen
suffix:semicolon
id|r
op_assign
id|inflate
c_func
(paren
op_amp
id|s
comma
id|Z_FINISH
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_ne
id|Z_OK
op_logical_and
id|r
op_ne
id|Z_STREAM_END
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;inflate returned %d msg: %s&bslash;n&bslash;r&quot;
comma
id|r
comma
id|s.msg
)paren
suffix:semicolon
m_exit
(paren
)paren
suffix:semicolon
)brace
op_star
id|lenp
op_assign
id|s.next_out
op_minus
(paren
r_int
r_char
op_star
)paren
id|dst
suffix:semicolon
id|inflateEnd
c_func
(paren
op_amp
id|s
)paren
suffix:semicolon
)brace
eof
