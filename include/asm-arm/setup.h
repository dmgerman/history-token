multiline_comment|/*&n; *  linux/include/asm/setup.h&n; *&n; *  Copyright (C) 1997-1999 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Structure passed to kernel to tell it about the&n; *  hardware it&squot;s running on.  See linux/Documentation/arm/Setup&n; *  for more info.&n; */
macro_line|#ifndef __ASMARM_SETUP_H
DECL|macro|__ASMARM_SETUP_H
mdefine_line|#define __ASMARM_SETUP_H
multiline_comment|/*&n; * Usage:&n; *  - do not go blindly adding fields, add them at the end&n; *  - when adding fields, don&squot;t rely on the address until&n; *    a patch from me has been released&n; *  - unused fields should be zero (for future expansion)&n; *  - this structure is relatively short-lived - only&n; *    guaranteed to contain useful data in setup_arch()&n; */
DECL|macro|COMMAND_LINE_SIZE
mdefine_line|#define COMMAND_LINE_SIZE 1024
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
multiline_comment|/*&n; * Memory map description&n; */
DECL|macro|NR_BANKS
mdefine_line|#define NR_BANKS 4
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
