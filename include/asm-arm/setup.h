multiline_comment|/*&n; *  linux/include/asm/setup.h&n; *&n; *  Copyright (C) 1997-1999 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Structure passed to kernel to tell it about the&n; *  hardware it&squot;s running on.  See linux/Documentation/arm/Setup&n; *  for more info.&n; *&n; * NOTE:&n; *  This file contains two ways to pass information from the boot&n; *  loader to the kernel. The old struct param_struct is deprecated,&n; *  but it will be kept in the kernel for 5 years from now&n; *  (2001). This will allow boot loaders to convert to the new struct&n; *  tag way.&n; */
macro_line|#ifndef __ASMARM_SETUP_H
DECL|macro|__ASMARM_SETUP_H
mdefine_line|#define __ASMARM_SETUP_H
multiline_comment|/*&n; * Usage:&n; *  - do not go blindly adding fields, add them at the end&n; *  - when adding fields, don&squot;t rely on the address until&n; *    a patch from me has been released&n; *  - unused fields should be zero (for future expansion)&n; *  - this structure is relatively short-lived - only&n; *    guaranteed to contain useful data in setup_arch()&n; */
DECL|macro|COMMAND_LINE_SIZE
mdefine_line|#define COMMAND_LINE_SIZE 1024
multiline_comment|/* This is the old deprecated way to pass parameters to the kernel */
DECL|struct|param_struct
r_struct
id|param_struct
(brace
r_union
(brace
r_struct
(brace
DECL|member|page_size
r_int
r_int
id|page_size
suffix:semicolon
multiline_comment|/*  0 */
DECL|member|nr_pages
r_int
r_int
id|nr_pages
suffix:semicolon
multiline_comment|/*  4 */
DECL|member|ramdisk_size
r_int
r_int
id|ramdisk_size
suffix:semicolon
multiline_comment|/*  8 */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* 12 */
DECL|macro|FLAG_READONLY
mdefine_line|#define FLAG_READONLY&t;1
DECL|macro|FLAG_RDLOAD
mdefine_line|#define FLAG_RDLOAD&t;4
DECL|macro|FLAG_RDPROMPT
mdefine_line|#define FLAG_RDPROMPT&t;8
DECL|member|rootdev
r_int
r_int
id|rootdev
suffix:semicolon
multiline_comment|/* 16 */
DECL|member|video_num_cols
r_int
r_int
id|video_num_cols
suffix:semicolon
multiline_comment|/* 20 */
DECL|member|video_num_rows
r_int
r_int
id|video_num_rows
suffix:semicolon
multiline_comment|/* 24 */
DECL|member|video_x
r_int
r_int
id|video_x
suffix:semicolon
multiline_comment|/* 28 */
DECL|member|video_y
r_int
r_int
id|video_y
suffix:semicolon
multiline_comment|/* 32 */
DECL|member|memc_control_reg
r_int
r_int
id|memc_control_reg
suffix:semicolon
multiline_comment|/* 36 */
DECL|member|sounddefault
r_int
r_char
id|sounddefault
suffix:semicolon
multiline_comment|/* 40 */
DECL|member|adfsdrives
r_int
r_char
id|adfsdrives
suffix:semicolon
multiline_comment|/* 41 */
DECL|member|bytes_per_char_h
r_int
r_char
id|bytes_per_char_h
suffix:semicolon
multiline_comment|/* 42 */
DECL|member|bytes_per_char_v
r_int
r_char
id|bytes_per_char_v
suffix:semicolon
multiline_comment|/* 43 */
DECL|member|pages_in_bank
r_int
r_int
id|pages_in_bank
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 44 */
DECL|member|pages_in_vram
r_int
r_int
id|pages_in_vram
suffix:semicolon
multiline_comment|/* 60 */
DECL|member|initrd_start
r_int
r_int
id|initrd_start
suffix:semicolon
multiline_comment|/* 64 */
DECL|member|initrd_size
r_int
r_int
id|initrd_size
suffix:semicolon
multiline_comment|/* 68 */
DECL|member|rd_start
r_int
r_int
id|rd_start
suffix:semicolon
multiline_comment|/* 72 */
DECL|member|system_rev
r_int
r_int
id|system_rev
suffix:semicolon
multiline_comment|/* 76 */
DECL|member|system_serial_low
r_int
r_int
id|system_serial_low
suffix:semicolon
multiline_comment|/* 80 */
DECL|member|system_serial_high
r_int
r_int
id|system_serial_high
suffix:semicolon
multiline_comment|/* 84 */
DECL|member|mem_fclk_21285
r_int
r_int
id|mem_fclk_21285
suffix:semicolon
multiline_comment|/* 88 */
DECL|member|s
)brace
id|s
suffix:semicolon
DECL|member|unused
r_char
id|unused
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|u1
)brace
id|u1
suffix:semicolon
r_union
(brace
DECL|member|paths
r_char
id|paths
(braket
l_int|8
)braket
(braket
l_int|128
)braket
suffix:semicolon
r_struct
(brace
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
DECL|member|n
r_char
id|n
(braket
l_int|1024
op_minus
r_sizeof
(paren
r_int
r_int
)paren
)braket
suffix:semicolon
DECL|member|s
)brace
id|s
suffix:semicolon
DECL|member|u2
)brace
id|u2
suffix:semicolon
DECL|member|commandline
r_char
id|commandline
(braket
id|COMMAND_LINE_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * The new way of passing information: a list of tagged entries&n; */
multiline_comment|/* The list ends with an ATAG_NONE node. */
DECL|macro|ATAG_NONE
mdefine_line|#define ATAG_NONE&t;0x00000000
DECL|struct|tag_header
r_struct
id|tag_header
(brace
DECL|member|size
id|u32
id|size
suffix:semicolon
DECL|member|tag
id|u32
id|tag
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The list must start with an ATAG_CORE node */
DECL|macro|ATAG_CORE
mdefine_line|#define ATAG_CORE&t;0x54410001
DECL|struct|tag_core
r_struct
id|tag_core
(brace
DECL|member|flags
id|u32
id|flags
suffix:semicolon
multiline_comment|/* bit 0 = read-only */
DECL|member|pagesize
id|u32
id|pagesize
suffix:semicolon
DECL|member|rootdev
id|u32
id|rootdev
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* it is allowed to have multiple ATAG_MEM nodes */
DECL|macro|ATAG_MEM
mdefine_line|#define ATAG_MEM&t;&t;0x54410002
DECL|struct|tag_mem32
r_struct
id|tag_mem32
(brace
DECL|member|size
id|u32
id|size
suffix:semicolon
DECL|member|start
id|u32
id|start
suffix:semicolon
multiline_comment|/* physical start address */
)brace
suffix:semicolon
multiline_comment|/* VGA text type displays */
DECL|macro|ATAG_VIDEOTEXT
mdefine_line|#define ATAG_VIDEOTEXT&t;0x54410003
DECL|struct|tag_videotext
r_struct
id|tag_videotext
(brace
DECL|member|x
id|u8
id|x
suffix:semicolon
DECL|member|y
id|u8
id|y
suffix:semicolon
DECL|member|video_page
id|u16
id|video_page
suffix:semicolon
DECL|member|video_mode
id|u8
id|video_mode
suffix:semicolon
DECL|member|video_cols
id|u8
id|video_cols
suffix:semicolon
DECL|member|video_ega_bx
id|u16
id|video_ega_bx
suffix:semicolon
DECL|member|video_lines
id|u8
id|video_lines
suffix:semicolon
DECL|member|video_isvga
id|u8
id|video_isvga
suffix:semicolon
DECL|member|video_points
id|u16
id|video_points
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* describes how the ramdisk will be used in kernel */
DECL|macro|ATAG_RAMDISK
mdefine_line|#define ATAG_RAMDISK&t;0x54410004
DECL|struct|tag_ramdisk
r_struct
id|tag_ramdisk
(brace
DECL|member|flags
id|u32
id|flags
suffix:semicolon
multiline_comment|/* bit 0 = load, bit 1 = prompt */
DECL|member|size
id|u32
id|size
suffix:semicolon
multiline_comment|/* decompressed ramdisk size in _kilo_ bytes */
DECL|member|start
id|u32
id|start
suffix:semicolon
multiline_comment|/* starting block of floppy-based RAM disk image */
)brace
suffix:semicolon
multiline_comment|/* describes where the compressed ramdisk image lives */
DECL|macro|ATAG_INITRD
mdefine_line|#define ATAG_INITRD&t;0x54410005
DECL|struct|tag_initrd
r_struct
id|tag_initrd
(brace
DECL|member|start
id|u32
id|start
suffix:semicolon
multiline_comment|/* physical start address */
DECL|member|size
id|u32
id|size
suffix:semicolon
multiline_comment|/* size of compressed ramdisk image in bytes */
)brace
suffix:semicolon
multiline_comment|/* board serial number. &quot;64 bits should be enough for everybody&quot; */
DECL|macro|ATAG_SERIAL
mdefine_line|#define ATAG_SERIAL&t;0x54410006
DECL|struct|tag_serialnr
r_struct
id|tag_serialnr
(brace
DECL|member|low
id|u32
id|low
suffix:semicolon
DECL|member|high
id|u32
id|high
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* board revision */
DECL|macro|ATAG_REVISION
mdefine_line|#define ATAG_REVISION&t;0x54410007
DECL|struct|tag_revision
r_struct
id|tag_revision
(brace
DECL|member|rev
id|u32
id|rev
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* initial values for vesafb-type framebuffers. see struct screen_info&n; * in include/linux/tty.h&n; */
DECL|macro|ATAG_VIDEOLFB
mdefine_line|#define ATAG_VIDEOLFB&t;0x54410008
DECL|struct|tag_videolfb
r_struct
id|tag_videolfb
(brace
DECL|member|lfb_width
id|u16
id|lfb_width
suffix:semicolon
DECL|member|lfb_height
id|u16
id|lfb_height
suffix:semicolon
DECL|member|lfb_depth
id|u16
id|lfb_depth
suffix:semicolon
DECL|member|lfb_linelength
id|u16
id|lfb_linelength
suffix:semicolon
DECL|member|lfb_base
id|u32
id|lfb_base
suffix:semicolon
DECL|member|lfb_size
id|u32
id|lfb_size
suffix:semicolon
DECL|member|red_size
id|u8
id|red_size
suffix:semicolon
DECL|member|red_pos
id|u8
id|red_pos
suffix:semicolon
DECL|member|green_size
id|u8
id|green_size
suffix:semicolon
DECL|member|green_pos
id|u8
id|green_pos
suffix:semicolon
DECL|member|blue_size
id|u8
id|blue_size
suffix:semicolon
DECL|member|blue_pos
id|u8
id|blue_pos
suffix:semicolon
DECL|member|rsvd_size
id|u8
id|rsvd_size
suffix:semicolon
DECL|member|rsvd_pos
id|u8
id|rsvd_pos
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* command line: &bslash;0 terminated string */
DECL|macro|ATAG_CMDLINE
mdefine_line|#define ATAG_CMDLINE&t;0x54410009
DECL|struct|tag_cmdline
r_struct
id|tag_cmdline
(brace
DECL|member|cmdline
r_char
id|cmdline
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* this is the minimum size */
)brace
suffix:semicolon
multiline_comment|/* acorn RiscPC specific information */
DECL|macro|ATAG_ACORN
mdefine_line|#define ATAG_ACORN&t;0x41000101
DECL|struct|tag_acorn
r_struct
id|tag_acorn
(brace
DECL|member|memc_control_reg
id|u32
id|memc_control_reg
suffix:semicolon
DECL|member|vram_pages
id|u32
id|vram_pages
suffix:semicolon
DECL|member|sounddefault
id|u8
id|sounddefault
suffix:semicolon
DECL|member|adfsdrives
id|u8
id|adfsdrives
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* footbridge memory clock, see arch/arm/mach-footbridge/arch.c */
DECL|macro|ATAG_MEMCLK
mdefine_line|#define ATAG_MEMCLK&t;0x41000402
DECL|struct|tag_memclk
r_struct
id|tag_memclk
(brace
DECL|member|fmemclk
id|u32
id|fmemclk
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tag
r_struct
id|tag
(brace
DECL|member|hdr
r_struct
id|tag_header
id|hdr
suffix:semicolon
r_union
(brace
DECL|member|core
r_struct
id|tag_core
id|core
suffix:semicolon
DECL|member|mem
r_struct
id|tag_mem32
id|mem
suffix:semicolon
DECL|member|videotext
r_struct
id|tag_videotext
id|videotext
suffix:semicolon
DECL|member|ramdisk
r_struct
id|tag_ramdisk
id|ramdisk
suffix:semicolon
DECL|member|initrd
r_struct
id|tag_initrd
id|initrd
suffix:semicolon
DECL|member|serialnr
r_struct
id|tag_serialnr
id|serialnr
suffix:semicolon
DECL|member|revision
r_struct
id|tag_revision
id|revision
suffix:semicolon
DECL|member|videolfb
r_struct
id|tag_videolfb
id|videolfb
suffix:semicolon
DECL|member|cmdline
r_struct
id|tag_cmdline
id|cmdline
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Acorn specific&n;&t;&t; */
DECL|member|acorn
r_struct
id|tag_acorn
id|acorn
suffix:semicolon
multiline_comment|/*&n;&t;&t; * DC21285 specific&n;&t;&t; */
DECL|member|memclk
r_struct
id|tag_memclk
id|memclk
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tagtable
r_struct
id|tagtable
(brace
DECL|member|tag
id|u32
id|tag
suffix:semicolon
DECL|member|parse
r_int
(paren
op_star
id|parse
)paren
(paren
r_const
r_struct
id|tag
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|__tag
mdefine_line|#define __tag __attribute__((unused, __section__(&quot;.taglist&quot;)))
DECL|macro|__tagtable
mdefine_line|#define __tagtable(tag, fn) &bslash;&n;static struct tagtable __tagtable_##fn __tag = { tag, fn }
DECL|macro|tag_member_present
mdefine_line|#define tag_member_present(tag,member)&t;&t;&t;&t;&bslash;&n;&t;((unsigned long)(&amp;((struct tag *)0L)-&gt;member + 1)&t;&bslash;&n;&t;&t;&lt;= (tag)-&gt;hdr.size * 4)
DECL|macro|tag_next
mdefine_line|#define tag_next(t)&t;((struct tag *)((u32 *)(t) + (t)-&gt;hdr.size))
DECL|macro|tag_size
mdefine_line|#define tag_size(type)&t;((sizeof(struct tag_header) + sizeof(struct type)) &gt;&gt; 2)
DECL|macro|for_each_tag
mdefine_line|#define for_each_tag(t,base)&t;&t;&bslash;&n;&t;for (t = base; t-&gt;hdr.size; t = tag_next(t))
multiline_comment|/*&n; * Memory map description&n; */
DECL|macro|NR_BANKS
mdefine_line|#define NR_BANKS 8
DECL|struct|meminfo
r_struct
id|meminfo
(brace
DECL|member|nr_banks
r_int
id|nr_banks
suffix:semicolon
DECL|member|end
r_int
r_int
id|end
suffix:semicolon
r_struct
(brace
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|node
r_int
id|node
suffix:semicolon
DECL|member|bank
)brace
id|bank
(braket
id|NR_BANKS
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|meminfo
id|meminfo
suffix:semicolon
macro_line|#endif
eof
