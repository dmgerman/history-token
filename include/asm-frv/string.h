multiline_comment|/* string.h: FRV string handling&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_STRING_H_
DECL|macro|_ASM_STRING_H_
mdefine_line|#define _ASM_STRING_H_
macro_line|#ifdef __KERNEL__ /* only set these up for kernel code */
DECL|macro|__HAVE_ARCH_MEMSET
mdefine_line|#define __HAVE_ARCH_MEMSET 1
DECL|macro|__HAVE_ARCH_MEMCPY
mdefine_line|#define __HAVE_ARCH_MEMCPY 1
r_extern
r_void
op_star
id|memset
c_func
(paren
r_void
op_star
comma
r_int
comma
id|__kernel_size_t
)paren
suffix:semicolon
r_extern
r_void
op_star
id|memcpy
c_func
(paren
r_void
op_star
comma
r_const
r_void
op_star
comma
id|__kernel_size_t
)paren
suffix:semicolon
macro_line|#else /* KERNEL */
multiline_comment|/*&n; *&t;let user libraries deal with these,&n; *&t;IMHO the kernel has no place defining these functions for user apps&n; */
DECL|macro|__HAVE_ARCH_STRCPY
mdefine_line|#define __HAVE_ARCH_STRCPY 1
DECL|macro|__HAVE_ARCH_STRNCPY
mdefine_line|#define __HAVE_ARCH_STRNCPY 1
DECL|macro|__HAVE_ARCH_STRCAT
mdefine_line|#define __HAVE_ARCH_STRCAT 1
DECL|macro|__HAVE_ARCH_STRNCAT
mdefine_line|#define __HAVE_ARCH_STRNCAT 1
DECL|macro|__HAVE_ARCH_STRCMP
mdefine_line|#define __HAVE_ARCH_STRCMP 1
DECL|macro|__HAVE_ARCH_STRNCMP
mdefine_line|#define __HAVE_ARCH_STRNCMP 1
DECL|macro|__HAVE_ARCH_STRNICMP
mdefine_line|#define __HAVE_ARCH_STRNICMP 1
DECL|macro|__HAVE_ARCH_STRCHR
mdefine_line|#define __HAVE_ARCH_STRCHR 1
DECL|macro|__HAVE_ARCH_STRRCHR
mdefine_line|#define __HAVE_ARCH_STRRCHR 1
DECL|macro|__HAVE_ARCH_STRSTR
mdefine_line|#define __HAVE_ARCH_STRSTR 1
DECL|macro|__HAVE_ARCH_STRLEN
mdefine_line|#define __HAVE_ARCH_STRLEN 1
DECL|macro|__HAVE_ARCH_STRNLEN
mdefine_line|#define __HAVE_ARCH_STRNLEN 1
DECL|macro|__HAVE_ARCH_MEMSET
mdefine_line|#define __HAVE_ARCH_MEMSET 1
DECL|macro|__HAVE_ARCH_MEMCPY
mdefine_line|#define __HAVE_ARCH_MEMCPY 1
DECL|macro|__HAVE_ARCH_MEMMOVE
mdefine_line|#define __HAVE_ARCH_MEMMOVE 1
DECL|macro|__HAVE_ARCH_MEMSCAN
mdefine_line|#define __HAVE_ARCH_MEMSCAN 1
DECL|macro|__HAVE_ARCH_MEMCMP
mdefine_line|#define __HAVE_ARCH_MEMCMP 1
DECL|macro|__HAVE_ARCH_MEMCHR
mdefine_line|#define __HAVE_ARCH_MEMCHR 1
DECL|macro|__HAVE_ARCH_STRTOK
mdefine_line|#define __HAVE_ARCH_STRTOK 1
macro_line|#endif /* KERNEL */
macro_line|#endif /* _ASM_STRING_H_ */
eof
