macro_line|#ifndef __I386_UNALIGNED_H
DECL|macro|__I386_UNALIGNED_H
mdefine_line|#define __I386_UNALIGNED_H
multiline_comment|/*&n; * The i386 can do unaligned accesses itself. &n; *&n; * The strange macros are there to make sure these can&squot;t&n; * be misused in a way that makes them not work on other&n; * architectures where unaligned accesses aren&squot;t as simple.&n; */
multiline_comment|/**&n; * get_unaligned - get value from possibly mis-aligned location&n; * @ptr: pointer to value&n; *&n; * This macro should be used for accessing values larger in size than &n; * single bytes at locations that are expected to be improperly aligned, &n; * e.g. retrieving a u16 value from a location not u16-aligned.&n; *&n; * Note that unaligned accesses can be very expensive on some architectures.&n; */
DECL|macro|get_unaligned
mdefine_line|#define get_unaligned(ptr) (*(ptr))
multiline_comment|/**&n; * put_unaligned - put value to a possibly mis-aligned location&n; * @val: value to place&n; * @ptr: pointer to location&n; *&n; * This macro should be used for placing values larger in size than &n; * single bytes at locations that are expected to be improperly aligned, &n; * e.g. writing a u16 value to a location not u16-aligned.&n; *&n; * Note that unaligned accesses can be very expensive on some architectures.&n; */
DECL|macro|put_unaligned
mdefine_line|#define put_unaligned(val, ptr) ((void)( *(ptr) = (val) ))
macro_line|#endif
eof
