multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2002 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_SYSTEMINFO_H
DECL|macro|_ASM_IA64_SN_SYSTEMINFO_H
mdefine_line|#define _ASM_IA64_SN_SYSTEMINFO_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif
DECL|macro|MAX_SERIAL_SIZE
mdefine_line|#define MAX_SERIAL_SIZE 16
DECL|struct|module_info_s
r_typedef
r_struct
id|module_info_s
(brace
DECL|member|serial_num
r_uint64
id|serial_num
suffix:semicolon
DECL|member|mod_num
r_int
id|mod_num
suffix:semicolon
DECL|member|serial_str
r_char
id|serial_str
(braket
id|MAX_SERIAL_SIZE
)braket
suffix:semicolon
DECL|typedef|module_info_t
)brace
id|module_info_t
suffix:semicolon
multiline_comment|/*&n; * Commands to sysinfo()&n; */
DECL|macro|SI_SYSNAME
mdefine_line|#define SI_SYSNAME&t;&t;1&t;/* return name of operating system */
DECL|macro|SI_HOSTNAME
mdefine_line|#define SI_HOSTNAME&t;&t;2&t;/* return name of node */
DECL|macro|SI_RELEASE
mdefine_line|#define SI_RELEASE &t;&t;3&t;/* return release of operating system */
DECL|macro|SI_VERSION
mdefine_line|#define SI_VERSION&t;&t;4&t;/* return version field of utsname */
DECL|macro|SI_MACHINE
mdefine_line|#define SI_MACHINE&t;&t;5&t;/* return kind of machine */
DECL|macro|SI_ARCHITECTURE
mdefine_line|#define SI_ARCHITECTURE&t;&t;6&t;/* return instruction set arch */
DECL|macro|SI_HW_SERIAL
mdefine_line|#define SI_HW_SERIAL&t;&t;7&t;/* return hardware serial number */
DECL|macro|SI_HW_PROVIDER
mdefine_line|#define SI_HW_PROVIDER&t;&t;8&t;/* return hardware manufacturer */
DECL|macro|SI_SRPC_DOMAIN
mdefine_line|#define SI_SRPC_DOMAIN&t;&t;9&t;/* return secure RPC domain */
DECL|macro|SI_INITTAB_NAME
mdefine_line|#define SI_INITTAB_NAME&t;       10&t;/* return name of inittab file used */
DECL|macro|_MIPS_SI_VENDOR
mdefine_line|#define _MIPS_SI_VENDOR&t;&t;100&t;/* return system provider */
DECL|macro|_MIPS_SI_OS_PROVIDER
mdefine_line|#define _MIPS_SI_OS_PROVIDER&t;101&t;/* return OS manufacturer */
DECL|macro|_MIPS_SI_OS_NAME
mdefine_line|#define _MIPS_SI_OS_NAME&t;102&t;/* return OS name */
DECL|macro|_MIPS_SI_HW_NAME
mdefine_line|#define _MIPS_SI_HW_NAME&t;103&t;/* return system name */
DECL|macro|_MIPS_SI_NUM_PROCESSORS
mdefine_line|#define _MIPS_SI_NUM_PROCESSORS&t;104&t;/* return number of processors */
DECL|macro|_MIPS_SI_HOSTID
mdefine_line|#define _MIPS_SI_HOSTID&t;&t;105&t;/* return hostid */
DECL|macro|_MIPS_SI_OSREL_MAJ
mdefine_line|#define _MIPS_SI_OSREL_MAJ&t;106&t;/* return OS major release number */
DECL|macro|_MIPS_SI_OSREL_MIN
mdefine_line|#define _MIPS_SI_OSREL_MIN&t;107&t;/* return OS minor release number */
DECL|macro|_MIPS_SI_OSREL_PATCH
mdefine_line|#define _MIPS_SI_OSREL_PATCH&t;108&t;/* return OS release number */
DECL|macro|_MIPS_SI_PROCESSORS
mdefine_line|#define _MIPS_SI_PROCESSORS&t;109&t;/* return CPU revison id */
DECL|macro|_MIPS_SI_AVAIL_PROCESSORS
mdefine_line|#define _MIPS_SI_AVAIL_PROCESSORS 110&t;/* return number of available processors */
DECL|macro|_MIPS_SI_SERIAL
mdefine_line|#define&t;_MIPS_SI_SERIAL&t;&t;111
multiline_comment|/*&n; * These commands are unpublished interfaces to sysinfo().&n; */
DECL|macro|SI_SET_HOSTNAME
mdefine_line|#define SI_SET_HOSTNAME&t;&t;258&t;/* set name of node */
multiline_comment|/*  -unpublished option */
DECL|macro|SI_SET_SRPC_DOMAIN
mdefine_line|#define SI_SET_SRPC_DOMAIN&t;265&t;/* set secure RPC domain */
multiline_comment|/* -unpublished option */
macro_line|#if !defined(__KERNEL__)
r_int
id|sysinfo
c_func
(paren
r_int
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|get_num_modules
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|get_module_info
c_func
(paren
r_int
comma
id|module_info_t
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif
macro_line|#endif /* _ASM_IA64_SN_SYSTEMINFO_H */
eof
