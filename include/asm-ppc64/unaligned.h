macro_line|#ifndef __PPC64_UNALIGNED_H
DECL|macro|__PPC64_UNALIGNED_H
mdefine_line|#define __PPC64_UNALIGNED_H
multiline_comment|/*&n; * The PowerPC can do unaligned accesses itself in big endian mode. &n; *&n; * The strange macros are there to make sure these can&squot;t&n; * be misused in a way that makes them not work on other&n; * architectures where unaligned accesses aren&squot;t as simple.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
DECL|macro|get_unaligned
mdefine_line|#define get_unaligned(ptr) (*(ptr))
DECL|macro|put_unaligned
mdefine_line|#define put_unaligned(val, ptr) ((void)( *(ptr) = (val) ))
macro_line|#endif /* __PPC64_UNALIGNED_H */
eof
