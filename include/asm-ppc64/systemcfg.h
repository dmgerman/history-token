macro_line|#ifndef _SYSTEMCFG_H
DECL|macro|_SYSTEMCFG_H
mdefine_line|#define _SYSTEMCFG_H
multiline_comment|/* &n; * Copyright (C) 2002 Peter Bergner &lt;bergner@vnet.ibm.com&gt;, IBM&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
multiline_comment|/* Change Activity:&n; * 2002/09/30 : bergner  : Created&n; * End Change Activity &n; */
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
multiline_comment|/* next four are no longer used except to be exported to /proc */
DECL|member|dcache_size
id|__u32
id|dcache_size
suffix:semicolon
multiline_comment|/* L1 d-cache size&t;&t;0x60 */
DECL|member|dcache_line_size
id|__u32
id|dcache_line_size
suffix:semicolon
multiline_comment|/* L1 d-cache line size&t;&t;0x64 */
DECL|member|icache_size
id|__u32
id|icache_size
suffix:semicolon
multiline_comment|/* L1 i-cache size&t;&t;0x68 */
DECL|member|icache_line_size
id|__u32
id|icache_line_size
suffix:semicolon
multiline_comment|/* L1 i-cache line size&t;&t;0x6C */
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
r_extern
r_struct
id|systemcfg
op_star
id|systemcfg
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* _SYSTEMCFG_H */
eof
