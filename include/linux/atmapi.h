multiline_comment|/* atmapi.h - ATM API user space/kernel compatibility */
multiline_comment|/* Written 1999,2000 by Werner Almesberger, EPFL ICA */
macro_line|#ifndef _LINUX_ATMAPI_H
DECL|macro|_LINUX_ATMAPI_H
mdefine_line|#define _LINUX_ATMAPI_H
macro_line|#ifdef __sparc__
multiline_comment|/* such alignment is not required on 32 bit sparcs, but we can&squot;t&n;   figure that we are on a sparc64 while compiling user-space programs. */
DECL|macro|__ATM_API_ALIGN
mdefine_line|#define __ATM_API_ALIGN&t;__attribute__((aligned(8)))
macro_line|#else
DECL|macro|__ATM_API_ALIGN
mdefine_line|#define __ATM_API_ALIGN
macro_line|#endif
multiline_comment|/*&n; * Opaque type for kernel pointers. Note that _ is never accessed. We need&n; * the struct in order hide the array, so that we can make simple assignments&n; * instead of being forced to use memcpy. It also improves error reporting for&n; * code that still assumes that we&squot;re passing unsigned longs.&n; *&n; * Convention: NULL pointers are passed as a field of all zeroes.&n; */
DECL|member|_
DECL|typedef|atm_kptr_t
r_typedef
r_struct
(brace
r_int
r_char
id|_
(braket
l_int|8
)braket
suffix:semicolon
)brace
id|atm_kptr_t
suffix:semicolon
macro_line|#endif
eof
