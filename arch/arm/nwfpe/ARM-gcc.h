multiline_comment|/*&n;-------------------------------------------------------------------------------&n;One of the macros `BIGENDIAN&squot; or `LITTLEENDIAN&squot; must be defined.&n;-------------------------------------------------------------------------------&n;*/
DECL|macro|LITTLEENDIAN
mdefine_line|#define LITTLEENDIAN
multiline_comment|/*&n;-------------------------------------------------------------------------------&n;The macro `BITS64&squot; can be defined to indicate that 64-bit integer types are&n;supported by the compiler.&n;-------------------------------------------------------------------------------&n;*/
DECL|macro|BITS64
mdefine_line|#define BITS64
multiline_comment|/*&n;-------------------------------------------------------------------------------&n;Each of the following `typedef&squot;s defines the most convenient type that holds&n;integers of at least as many bits as specified.  For example, `uint8&squot; should&n;be the most convenient type that can hold unsigned integers of as many as&n;8 bits.  The `flag&squot; type must be able to hold either a 0 or 1.  For most&n;implementations of C, `flag&squot;, `uint8&squot;, and `int8&squot; should all be `typedef&squot;ed&n;to the same as `int&squot;.&n;-------------------------------------------------------------------------------&n;*/
DECL|typedef|flag
r_typedef
r_char
id|flag
suffix:semicolon
DECL|typedef|uint8
r_typedef
r_int
r_char
id|uint8
suffix:semicolon
DECL|typedef|int8
r_typedef
r_int
r_char
id|int8
suffix:semicolon
DECL|typedef|uint16
r_typedef
r_int
id|uint16
suffix:semicolon
DECL|typedef|int16
r_typedef
r_int
id|int16
suffix:semicolon
DECL|typedef|uint32
r_typedef
r_int
r_int
id|uint32
suffix:semicolon
DECL|typedef|int32
r_typedef
r_int
r_int
id|int32
suffix:semicolon
macro_line|#ifdef BITS64
DECL|typedef|bits64
r_typedef
r_int
r_int
r_int
r_int
id|bits64
suffix:semicolon
DECL|typedef|sbits64
r_typedef
r_int
r_int
r_int
r_int
id|sbits64
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;-------------------------------------------------------------------------------&n;Each of the following `typedef&squot;s defines a type that holds integers&n;of _exactly_ the number of bits specified.  For instance, for most&n;implementation of C, `bits16&squot; and `sbits16&squot; should be `typedef&squot;ed to&n;`unsigned short int&squot; and `signed short int&squot; (or `short int&squot;), respectively.&n;-------------------------------------------------------------------------------&n;*/
DECL|typedef|bits8
r_typedef
r_int
r_char
id|bits8
suffix:semicolon
DECL|typedef|sbits8
r_typedef
r_int
r_char
id|sbits8
suffix:semicolon
DECL|typedef|bits16
r_typedef
r_int
r_int
r_int
id|bits16
suffix:semicolon
DECL|typedef|sbits16
r_typedef
r_int
r_int
r_int
id|sbits16
suffix:semicolon
DECL|typedef|bits32
r_typedef
r_int
r_int
id|bits32
suffix:semicolon
DECL|typedef|sbits32
r_typedef
r_int
r_int
id|sbits32
suffix:semicolon
macro_line|#ifdef BITS64
DECL|typedef|uint64
r_typedef
r_int
r_int
r_int
r_int
id|uint64
suffix:semicolon
DECL|typedef|int64
r_typedef
r_int
r_int
r_int
r_int
id|int64
suffix:semicolon
macro_line|#endif
macro_line|#ifdef BITS64
multiline_comment|/*&n;-------------------------------------------------------------------------------&n;The `LIT64&squot; macro takes as its argument a textual integer literal and if&n;necessary ``marks&squot;&squot; the literal as having a 64-bit integer type.  For&n;example, the Gnu C Compiler (`gcc&squot;) requires that 64-bit literals be&n;appended with the letters `LL&squot; standing for `long long&squot;, which is `gcc&squot;s&n;name for the 64-bit integer type.  Some compilers may allow `LIT64&squot; to be&n;defined as the identity macro:  `#define LIT64( a ) a&squot;.&n;-------------------------------------------------------------------------------&n;*/
DECL|macro|LIT64
mdefine_line|#define LIT64( a ) a##LL
macro_line|#endif
multiline_comment|/*&n;-------------------------------------------------------------------------------&n;The macro `INLINE&squot; can be used before functions that should be inlined.  If&n;a compiler does not support explicit inlining, this macro should be defined&n;to be `static&squot;.&n;-------------------------------------------------------------------------------&n;*/
DECL|macro|INLINE
mdefine_line|#define INLINE extern __inline__
multiline_comment|/* For use as a GCC soft-float library we need some special function names. */
macro_line|#ifdef __LIBFLOAT__
multiline_comment|/* Some 32-bit ops can be mapped straight across by just changing the name. */
DECL|macro|float32_add
mdefine_line|#define float32_add&t;&t;&t;__addsf3
DECL|macro|float32_sub
mdefine_line|#define float32_sub&t;&t;&t;__subsf3
DECL|macro|float32_mul
mdefine_line|#define float32_mul&t;&t;&t;__mulsf3
DECL|macro|float32_div
mdefine_line|#define float32_div&t;&t;&t;__divsf3
DECL|macro|int32_to_float32
mdefine_line|#define int32_to_float32&t;&t;__floatsisf
DECL|macro|float32_to_int32_round_to_zero
mdefine_line|#define float32_to_int32_round_to_zero&t;__fixsfsi
DECL|macro|float32_to_uint32_round_to_zero
mdefine_line|#define float32_to_uint32_round_to_zero&t;__fixunssfsi
multiline_comment|/* These ones go through the glue code.  To avoid namespace pollution&n;   we rename the internal functions too.  */
DECL|macro|float32_eq
mdefine_line|#define float32_eq&t;&t;&t;___float32_eq
DECL|macro|float32_le
mdefine_line|#define float32_le&t;&t;&t;___float32_le
DECL|macro|float32_lt
mdefine_line|#define float32_lt&t;&t;&t;___float32_lt
multiline_comment|/* All the 64-bit ops have to go through the glue, so we pull the same&n;   trick.  */
DECL|macro|float64_add
mdefine_line|#define float64_add&t;&t;&t;___float64_add
DECL|macro|float64_sub
mdefine_line|#define float64_sub&t;&t;&t;___float64_sub
DECL|macro|float64_mul
mdefine_line|#define float64_mul&t;&t;&t;___float64_mul
DECL|macro|float64_div
mdefine_line|#define float64_div&t;&t;&t;___float64_div
DECL|macro|int32_to_float64
mdefine_line|#define int32_to_float64&t;&t;___int32_to_float64
DECL|macro|float64_to_int32_round_to_zero
mdefine_line|#define float64_to_int32_round_to_zero&t;___float64_to_int32_round_to_zero
DECL|macro|float64_to_uint32_round_to_zero
mdefine_line|#define float64_to_uint32_round_to_zero&t;___float64_to_uint32_round_to_zero
DECL|macro|float64_to_float32
mdefine_line|#define float64_to_float32&t;&t;___float64_to_float32
DECL|macro|float32_to_float64
mdefine_line|#define float32_to_float64&t;&t;___float32_to_float64
DECL|macro|float64_eq
mdefine_line|#define float64_eq&t;&t;&t;___float64_eq
DECL|macro|float64_le
mdefine_line|#define float64_le&t;&t;&t;___float64_le
DECL|macro|float64_lt
mdefine_line|#define float64_lt&t;&t;&t;___float64_lt
macro_line|#if 0
mdefine_line|#define float64_add&t;&t;&t;__adddf3
mdefine_line|#define float64_sub&t;&t;&t;__subdf3
mdefine_line|#define float64_mul&t;&t;&t;__muldf3
mdefine_line|#define float64_div&t;&t;&t;__divdf3
mdefine_line|#define int32_to_float64&t;&t;__floatsidf
mdefine_line|#define float64_to_int32_round_to_zero&t;__fixdfsi
mdefine_line|#define float64_to_uint32_round_to_zero&t;__fixunsdfsi
mdefine_line|#define float64_to_float32&t;&t;__truncdfsf2
mdefine_line|#define float32_to_float64&t;&t;__extendsfdf2
macro_line|#endif
macro_line|#endif
eof
