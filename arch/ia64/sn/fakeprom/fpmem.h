multiline_comment|/* &n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000-2001 Silicon Graphics, Inc.  All rights reserved.&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Structure of the mem config of the node as a SN1 MI reg&n; * Medusa supports this reg config.&n; *&n; * BankSize nibble to bank size mapping&n; *&n; *      1 - 64 MB&n; *      2 - 128 MB&n; *      3 - 256 MB&n; *      4 - 512 MB&n; *      5 - 1024 MB (1GB)&n; */
DECL|macro|MBSHIFT
mdefine_line|#define MBSHIFT&t;&t;&t;&t;20
macro_line|#ifdef CONFIG_IA64_SGI_SN1
DECL|struct|node_memmap_s
r_typedef
r_struct
id|node_memmap_s
(brace
DECL|member|b0
r_int
r_int
id|b0
suffix:colon
l_int|1
comma
multiline_comment|/* 0 bank 0 present */
DECL|member|b1
id|b1
suffix:colon
l_int|1
comma
multiline_comment|/* 1 bank 1 present */
DECL|member|r01
id|r01
suffix:colon
l_int|2
comma
multiline_comment|/* 2-3 reserved */
DECL|member|b01size
id|b01size
suffix:colon
l_int|4
comma
multiline_comment|/* 4-7 Size of bank 0 and 1 */
DECL|member|b2
id|b2
suffix:colon
l_int|1
comma
multiline_comment|/* 8 bank 2 present */
DECL|member|b3
id|b3
suffix:colon
l_int|1
comma
multiline_comment|/* 9 bank 3 present */
DECL|member|r23
id|r23
suffix:colon
l_int|2
comma
multiline_comment|/* 10-11 reserved */
DECL|member|b23size
id|b23size
suffix:colon
l_int|4
comma
multiline_comment|/* 12-15 Size of bank 2 and 3 */
DECL|member|b4
id|b4
suffix:colon
l_int|1
comma
multiline_comment|/* 16 bank 4 present */
DECL|member|b5
id|b5
suffix:colon
l_int|1
comma
multiline_comment|/* 17 bank 5 present */
DECL|member|r45
id|r45
suffix:colon
l_int|2
comma
multiline_comment|/* 18-19 reserved */
DECL|member|b45size
id|b45size
suffix:colon
l_int|4
comma
multiline_comment|/* 20-23 Size of bank 4 and 5 */
DECL|member|b6
id|b6
suffix:colon
l_int|1
comma
multiline_comment|/* 24 bank 6 present */
DECL|member|b7
id|b7
suffix:colon
l_int|1
comma
multiline_comment|/* 25 bank 7 present */
DECL|member|r67
id|r67
suffix:colon
l_int|2
comma
multiline_comment|/* 26-27 reserved */
DECL|member|b67size
id|b67size
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 28-31 Size of bank 6 and 7 */
DECL|typedef|node_memmap_t
)brace
id|node_memmap_t
suffix:semicolon
multiline_comment|/* Support the medusa hack for 8M/16M/32M nodes */
DECL|macro|SN1_BANK_SIZE_SHIFT
mdefine_line|#define SN1_BANK_SIZE_SHIFT&t;&t;(MBSHIFT+6)     /* 64 MB */
DECL|macro|BankSizeBytes
mdefine_line|#define BankSizeBytes(bsize)            ((bsize&lt;6) ? (1&lt;&lt;((bsize-1)+SN1_BANK_SIZE_SHIFT)) :&bslash;&n;                                         (1&lt;&lt;((bsize-9)+MBSHIFT)))
macro_line|#else
DECL|struct|node_memmap_s
r_typedef
r_struct
id|node_memmap_s
(brace
DECL|member|b0size
r_int
r_int
id|b0size
suffix:colon
l_int|3
comma
multiline_comment|/* 0-2   bank 0 size */
DECL|member|b0dou
id|b0dou
suffix:colon
l_int|1
comma
multiline_comment|/* 3     bank 0 is 2-sided */
DECL|member|ena0
id|ena0
suffix:colon
l_int|1
comma
multiline_comment|/* 4     bank 0 enabled */
DECL|member|r0
id|r0
suffix:colon
l_int|3
comma
multiline_comment|/* 5-7   reserved */
DECL|member|b1size
id|b1size
suffix:colon
l_int|3
comma
multiline_comment|/* 8-10  bank 1 size */
DECL|member|b1dou
id|b1dou
suffix:colon
l_int|1
comma
multiline_comment|/* 11    bank 1 is 2-sided */
DECL|member|ena1
id|ena1
suffix:colon
l_int|1
comma
multiline_comment|/* 12    bank 1 enabled */
DECL|member|r1
id|r1
suffix:colon
l_int|3
comma
multiline_comment|/* 13-15 reserved */
DECL|member|b2size
id|b2size
suffix:colon
l_int|3
comma
multiline_comment|/* 16-18 bank 2 size */
DECL|member|b2dou
id|b2dou
suffix:colon
l_int|1
comma
multiline_comment|/* 19    bank 1 is 2-sided */
DECL|member|ena2
id|ena2
suffix:colon
l_int|1
comma
multiline_comment|/* 20    bank 2 enabled */
DECL|member|r2
id|r2
suffix:colon
l_int|3
comma
multiline_comment|/* 21-23 reserved */
DECL|member|b3size
id|b3size
suffix:colon
l_int|3
comma
multiline_comment|/* 24-26 bank 3 size */
DECL|member|b3dou
id|b3dou
suffix:colon
l_int|1
comma
multiline_comment|/* 27    bank 3 is 2-sided */
DECL|member|ena3
id|ena3
suffix:colon
l_int|1
comma
multiline_comment|/* 28    bank 3 enabled */
DECL|member|r3
id|r3
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* 29-31 reserved */
DECL|typedef|node_memmap_t
)brace
id|node_memmap_t
suffix:semicolon
DECL|macro|SN2_BANK_SIZE_SHIFT
mdefine_line|#define SN2_BANK_SIZE_SHIFT&t;&t;(MBSHIFT+6)     /* 64 MB */
DECL|macro|BankSizeBytes
mdefine_line|#define BankSizeBytes(bsize)            (1UL&lt;&lt;((bsize)+SN2_BANK_SIZE_SHIFT))
macro_line|#endif
DECL|struct|sn_memmap_s
r_typedef
r_struct
id|sn_memmap_s
(brace
DECL|member|nasid
r_int
id|nasid
suffix:semicolon
DECL|member|cpuconfig
r_int
id|cpuconfig
suffix:semicolon
DECL|member|node_memmap
id|node_memmap_t
id|node_memmap
suffix:semicolon
DECL|typedef|sn_memmap_t
)brace
id|sn_memmap_t
suffix:semicolon
DECL|struct|sn_config_s
r_typedef
r_struct
id|sn_config_s
(brace
DECL|member|cpus
r_int
id|cpus
suffix:semicolon
DECL|member|nodes
r_int
id|nodes
suffix:semicolon
DECL|member|memmap
id|sn_memmap_t
id|memmap
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* start of array */
DECL|typedef|sn_config_t
)brace
id|sn_config_t
suffix:semicolon
r_extern
r_void
id|build_init
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|build_efi_memmap
c_func
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|GetNumNodes
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|GetNumCpus
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|IsCpuPresent
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|GetNasid
c_func
(paren
r_int
)paren
suffix:semicolon
eof
