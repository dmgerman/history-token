multiline_comment|/* -*- mode: c; c-basic-offset: 8; indent-tabs-mode: nil; -*-&n; * vim:expandtab:shiftwidth=8:tabstop=8:&n; *&n; * Copyright (C) 2001 Cluster File Systems, Inc. &lt;braam@clusterfs.com&gt;&n; *&n; *   This file is part of InterMezzo, http://www.inter-mezzo.org.&n; *&n; *   InterMezzo is free software; you can redistribute it and/or&n; *   modify it under the terms of version 2 of the GNU General Public&n; *   License as published by the Free Software Foundation.&n; *&n; *   InterMezzo is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with InterMezzo; if not, write to the Free Software&n; *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Data structures unpacking/packing macros &amp; inlines&n; *&n; */
macro_line|#ifndef _INTERMEZZO_LIB_H
DECL|macro|_INTERMEZZO_LIB_H
mdefine_line|#define _INTERMEZZO_LIB_H
macro_line|#ifdef __KERNEL__
macro_line|# include &lt;linux/types.h&gt;
macro_line|#else
macro_line|# include &lt;string.h&gt;
macro_line|# include &lt;sys/types.h&gt;
macro_line|#endif
DECL|macro|MIN
macro_line|#undef MIN
DECL|macro|MIN
mdefine_line|#define MIN(a,b) (((a)&lt;(b)) ? (a): (b))
DECL|macro|MAX
macro_line|#undef MAX
DECL|macro|MAX
mdefine_line|#define MAX(a,b) (((a)&gt;(b)) ? (a): (b))
DECL|macro|MKSTR
mdefine_line|#define MKSTR(ptr) ((ptr))? (ptr) : &quot;&quot;
DECL|function|size_round
r_static
r_inline
r_int
id|size_round
(paren
r_int
id|val
)paren
(brace
r_return
(paren
id|val
op_plus
l_int|3
)paren
op_amp
(paren
op_complement
l_int|0x3
)paren
suffix:semicolon
)brace
DECL|function|size_round0
r_static
r_inline
r_int
id|size_round0
c_func
(paren
r_int
id|val
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|val
)paren
r_return
l_int|0
suffix:semicolon
r_return
(paren
id|val
op_plus
l_int|1
op_plus
l_int|3
)paren
op_amp
(paren
op_complement
l_int|0x3
)paren
suffix:semicolon
)brace
DECL|function|round_strlen
r_static
r_inline
r_int
id|round_strlen
c_func
(paren
r_char
op_star
id|fset
)paren
(brace
r_return
id|size_round
c_func
(paren
id|strlen
c_func
(paren
id|fset
)paren
op_plus
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#ifdef __KERNEL__
DECL|macro|NTOH__u32
macro_line|# define NTOH__u32(var) le32_to_cpu(var)
DECL|macro|NTOH__u64
macro_line|# define NTOH__u64(var) le64_to_cpu(var)
DECL|macro|HTON__u32
macro_line|# define HTON__u32(var) cpu_to_le32(var)
DECL|macro|HTON__u64
macro_line|# define HTON__u64(var) cpu_to_le64(var)
macro_line|#else
macro_line|# include &lt;glib.h&gt;
DECL|macro|NTOH__u32
macro_line|# define NTOH__u32(var) GUINT32_FROM_LE(var)
DECL|macro|NTOH__u64
macro_line|# define NTOH__u64(var) GUINT64_FROM_LE(var)
DECL|macro|HTON__u32
macro_line|# define HTON__u32(var) GUINT32_TO_LE(var)
DECL|macro|HTON__u64
macro_line|# define HTON__u64(var) GUINT64_TO_LE(var)
macro_line|#endif
multiline_comment|/* &n; * copy sizeof(type) bytes from pointer to var and move ptr forward.&n; * return EFAULT if pointer goes beyond end&n; */
DECL|macro|UNLOGV
mdefine_line|#define UNLOGV(var,type,ptr,end)                &bslash;&n;do {                                            &bslash;&n;        var = *(type *)ptr;                     &bslash;&n;        ptr += sizeof(type);                    &bslash;&n;        if (ptr &gt; end )                         &bslash;&n;                return -EFAULT;                 &bslash;&n;} while (0)
multiline_comment|/* the following two macros convert to little endian */
multiline_comment|/* type MUST be __u32 or __u64 */
DECL|macro|LUNLOGV
mdefine_line|#define LUNLOGV(var,type,ptr,end)               &bslash;&n;do {                                            &bslash;&n;        var = NTOH##type(*(type *)ptr);         &bslash;&n;        ptr += sizeof(type);                    &bslash;&n;        if (ptr &gt; end )                         &bslash;&n;                return -EFAULT;                 &bslash;&n;} while (0)
multiline_comment|/* now log values */
DECL|macro|LOGV
mdefine_line|#define LOGV(var,type,ptr)                      &bslash;&n;do {                                            &bslash;&n;        *((type *)ptr) = var;                   &bslash;&n;        ptr += sizeof(type);                    &bslash;&n;} while (0)
multiline_comment|/* and in network order */
DECL|macro|LLOGV
mdefine_line|#define LLOGV(var,type,ptr)                     &bslash;&n;do {                                            &bslash;&n;        *((type *)ptr) = HTON##type(var);       &bslash;&n;        ptr += sizeof(type);                    &bslash;&n;} while (0)
multiline_comment|/* &n; * set var to point at (type *)ptr, move ptr forward with sizeof(type)&n; * return from function with EFAULT if ptr goes beyond end&n; */
DECL|macro|UNLOGP
mdefine_line|#define UNLOGP(var,type,ptr,end)                &bslash;&n;do {                                            &bslash;&n;        var = (type *)ptr;                      &bslash;&n;        ptr += sizeof(type);                    &bslash;&n;        if (ptr &gt; end )                         &bslash;&n;                return -EFAULT;                 &bslash;&n;} while (0)
DECL|macro|LOGP
mdefine_line|#define LOGP(var,type,ptr)                      &bslash;&n;do {                                            &bslash;&n;        memcpy(ptr, var, sizeof(type));         &bslash;&n;        ptr += sizeof(type);                    &bslash;&n;} while (0)
multiline_comment|/* &n; * set var to point at (char *)ptr, move ptr forward by size_round(len);&n; * return from function with EFAULT if ptr goes beyond end&n; */
DECL|macro|UNLOGL
mdefine_line|#define UNLOGL(var,type,len,ptr,end)                    &bslash;&n;do {                                                    &bslash;&n;        if (len == 0)                                   &bslash;&n;                var = (type *)0;                        &bslash;&n;        else {                                          &bslash;&n;                var = (type *)ptr;                      &bslash;&n;                ptr += size_round(len * sizeof(type));  &bslash;&n;        }                                               &bslash;&n;        if (ptr &gt; end )                                 &bslash;&n;                return -EFAULT;                         &bslash;&n;} while (0)
DECL|macro|UNLOGL0
mdefine_line|#define UNLOGL0(var,type,len,ptr,end)                           &bslash;&n;do {                                                            &bslash;&n;        UNLOGL(var,type,len+1,ptr,end);                         &bslash;&n;        if ( *((char *)ptr - size_round(len+1) + len) != &squot;&bslash;0&squot;)  &bslash;&n;                        return -EFAULT;                         &bslash;&n;} while (0)
DECL|macro|LOGL
mdefine_line|#define LOGL(var,len,ptr)                               &bslash;&n;do {                                                    &bslash;&n;        size_t __fill = size_round(len);                &bslash;&n;        /* Prevent data leakage. */                     &bslash;&n;        if (__fill &gt; 0)                                 &bslash;&n;                memset((char *)ptr, 0, __fill);         &bslash;&n;        memcpy((char *)ptr, (const char *)var, len);    &bslash;&n;        ptr += __fill;                                  &bslash;&n;} while (0)
DECL|macro|LOGL0
mdefine_line|#define LOGL0(var,len,ptr)                              &bslash;&n;do {                                                    &bslash;&n;        if (!len) break;                                &bslash;&n;        memcpy((char *)ptr, (const char *)var, len);    &bslash;&n;        *((char *)(ptr) + len) = 0;                     &bslash;&n;        ptr += size_round(len + 1);                     &bslash;&n;} while (0)
macro_line|#endif /* _INTERMEZZO_LIB_H */
eof
