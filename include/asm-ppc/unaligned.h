macro_line|#ifdef __KERNEL__
macro_line|#ifndef __PPC_UNALIGNED_H
DECL|macro|__PPC_UNALIGNED_H
mdefine_line|#define __PPC_UNALIGNED_H
multiline_comment|/*&n; * The PowerPC can do unaligned accesses itself in big endian mode. &n; *&n; * The strange macros are there to make sure these can&squot;t&n; * be misused in a way that makes them not work on other&n; * architectures where unaligned accesses aren&squot;t as simple.&n; */
DECL|macro|get_unaligned
mdefine_line|#define get_unaligned(ptr) (*(ptr))
DECL|macro|put_unaligned
mdefine_line|#define put_unaligned(val, ptr) ((void)( *(ptr) = (val) ))
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
eof
