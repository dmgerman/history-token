macro_line|#ifndef _SYSTEMCFG_H
DECL|macro|_SYSTEMCFG_H
mdefine_line|#define _SYSTEMCFG_H
multiline_comment|/* &n; * Copyright (C) 2002 Peter Bergner &lt;bergner@vnet.ibm.com&gt;, IBM&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
multiline_comment|/* Change Activity:&n; * 2002/09/30 : bergner  : Created&n; * End Change Activity &n; */
macro_line|#ifndef __KERNEL__
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;fcntl.h&gt;
macro_line|#include &lt;sys/mman.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#endif
multiline_comment|/*&n; * If the major version changes we are incompatible.&n; * Minor version changes are a hint.&n; */
DECL|macro|SYSTEMCFG_MAJOR
mdefine_line|#define SYSTEMCFG_MAJOR 1
DECL|macro|SYSTEMCFG_MINOR
mdefine_line|#define SYSTEMCFG_MINOR 0
macro_line|#ifndef __ASSEMBLY__
DECL|struct|systemcfg
r_struct
id|systemcfg
(brace
DECL|member|eye_catcher
id|__u8
id|eye_catcher
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Eyecatcher: SYSTEMCFG:PPC64&t;0x00 */
r_struct
(brace
multiline_comment|/* Systemcfg version numbers&t;     */
DECL|member|major
id|__u32
id|major
suffix:semicolon
multiline_comment|/* Major number&t;&t;&t;0x10 */
DECL|member|minor
id|__u32
id|minor
suffix:semicolon
multiline_comment|/* Minor number&t;&t;&t;0x14 */
DECL|member|version
)brace
id|version
suffix:semicolon
DECL|member|platform
id|__u32
id|platform
suffix:semicolon
multiline_comment|/* Platform flags&t;&t;0x18 */
DECL|member|processor
id|__u32
id|processor
suffix:semicolon
multiline_comment|/* Processor type&t;&t;0x1C */
DECL|member|processorCount
id|__u64
id|processorCount
suffix:semicolon
multiline_comment|/* # of physical processors&t;0x20 */
DECL|member|physicalMemorySize
id|__u64
id|physicalMemorySize
suffix:semicolon
multiline_comment|/* Size of real memory(B)&t;0x28 */
DECL|member|tb_orig_stamp
id|__u64
id|tb_orig_stamp
suffix:semicolon
multiline_comment|/* Timebase at boot&t;&t;0x30 */
DECL|member|tb_ticks_per_sec
id|__u64
id|tb_ticks_per_sec
suffix:semicolon
multiline_comment|/* Timebase tics / sec&t;&t;0x38 */
DECL|member|tb_to_xs
id|__u64
id|tb_to_xs
suffix:semicolon
multiline_comment|/* Inverse of TB to 2^20&t;0x40 */
DECL|member|stamp_xsec
id|__u64
id|stamp_xsec
suffix:semicolon
multiline_comment|/*&t;&t;&t;&t;0x48 */
DECL|member|tb_update_count
id|__u64
id|tb_update_count
suffix:semicolon
multiline_comment|/* Timebase atomicity ctr&t;0x50 */
DECL|member|tz_minuteswest
id|__u32
id|tz_minuteswest
suffix:semicolon
multiline_comment|/* Minutes west of Greenwich&t;0x58 */
DECL|member|tz_dsttime
id|__u32
id|tz_dsttime
suffix:semicolon
multiline_comment|/* Type of dst correction&t;0x5C */
DECL|member|dCacheL1Size
id|__u32
id|dCacheL1Size
suffix:semicolon
multiline_comment|/* L1 d-cache size&t;&t;0x60 */
DECL|member|dCacheL1LineSize
id|__u32
id|dCacheL1LineSize
suffix:semicolon
multiline_comment|/* L1 d-cache line size&t;&t;0x64 */
DECL|member|iCacheL1Size
id|__u32
id|iCacheL1Size
suffix:semicolon
multiline_comment|/* L1 i-cache size&t;&t;0x68 */
DECL|member|iCacheL1LineSize
id|__u32
id|iCacheL1LineSize
suffix:semicolon
multiline_comment|/* L1 i-cache line size&t;&t;0x6C */
DECL|member|reserved0
id|__u8
id|reserved0
(braket
l_int|3984
)braket
suffix:semicolon
multiline_comment|/* Reserve rest of page&t;&t;0x70 */
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
r_extern
r_struct
id|systemcfg
op_star
id|systemcfg
suffix:semicolon
macro_line|#else
multiline_comment|/* Processor Version Register (PVR) field extraction */
DECL|macro|PVR_VER
mdefine_line|#define PVR_VER(pvr)  (((pvr) &gt;&gt;  16) &amp; 0xFFFF) /* Version field */
DECL|macro|PVR_REV
mdefine_line|#define PVR_REV(pvr)  (((pvr) &gt;&gt;   0) &amp; 0xFFFF) /* Revison field */
multiline_comment|/* Processor Version Numbers */
DECL|macro|PV_NORTHSTAR
mdefine_line|#define PV_NORTHSTAR    0x0033
DECL|macro|PV_PULSAR
mdefine_line|#define PV_PULSAR       0x0034
DECL|macro|PV_POWER4
mdefine_line|#define PV_POWER4       0x0035
DECL|macro|PV_ICESTAR
mdefine_line|#define PV_ICESTAR      0x0036
DECL|macro|PV_SSTAR
mdefine_line|#define PV_SSTAR        0x0037
DECL|macro|PV_POWER4p
mdefine_line|#define PV_POWER4p      0x0038
DECL|macro|PV_630
mdefine_line|#define PV_630          0x0040
DECL|macro|PV_630p
mdefine_line|#define PV_630p         0x0041
multiline_comment|/* Platforms supported by PPC64 */
DECL|macro|PLATFORM_PSERIES
mdefine_line|#define PLATFORM_PSERIES      0x0100
DECL|macro|PLATFORM_PSERIES_LPAR
mdefine_line|#define PLATFORM_PSERIES_LPAR 0x0101
DECL|macro|PLATFORM_ISERIES_LPAR
mdefine_line|#define PLATFORM_ISERIES_LPAR 0x0201
DECL|function|systemcfg_init
r_static
r_inline
r_volatile
r_struct
id|systemcfg
op_star
id|systemcfg_init
c_func
(paren
r_void
)paren
(brace
r_int
id|fd
op_assign
id|open
c_func
(paren
l_string|&quot;/proc/ppc64/systemcfg&quot;
comma
id|O_RDONLY
)paren
suffix:semicolon
r_volatile
r_struct
id|systemcfg
op_star
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|fd
op_eq
op_minus
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
id|ret
op_assign
id|mmap
c_func
(paren
l_int|0
comma
r_sizeof
(paren
r_struct
id|systemcfg
)paren
comma
id|PROT_READ
comma
id|MAP_SHARED
comma
id|fd
comma
l_int|0
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ret-&gt;version.major
op_ne
id|SYSTEMCFG_MAJOR
op_logical_or
id|ret-&gt;version.minor
OL
id|SYSTEMCFG_MINOR
)paren
(brace
id|munmap
c_func
(paren
(paren
r_void
op_star
)paren
id|ret
comma
r_sizeof
(paren
r_struct
id|systemcfg
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASSEMBLY__ */
DECL|macro|SYSTEMCFG_PAGE
mdefine_line|#define SYSTEMCFG_PAGE      0x5
DECL|macro|SYSTEMCFG_PHYS_ADDR
mdefine_line|#define SYSTEMCFG_PHYS_ADDR (SYSTEMCFG_PAGE&lt;&lt;PAGE_SHIFT)
DECL|macro|SYSTEMCFG_VIRT_ADDR
mdefine_line|#define SYSTEMCFG_VIRT_ADDR (KERNELBASE+SYSTEMCFG_PHYS_ADDR)
macro_line|#endif /* _SYSTEMCFG_H */
eof
