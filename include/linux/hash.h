macro_line|#ifndef _LINUX_HASH_H
DECL|macro|_LINUX_HASH_H
mdefine_line|#define _LINUX_HASH_H
multiline_comment|/* Fast hashing routine for a long.&n;   (C) 2002 William Lee Irwin III, IBM */
multiline_comment|/*&n; * Knuth recommends primes in approximately golden ratio to the maximum&n; * integer representable by a machine word for multiplicative hashing.&n; * Chuck Lever verified the effectiveness of this technique:&n; * http://www.citi.umich.edu/techreports/reports/citi-tr-00-1.pdf&n; *&n; * These primes are chosen to be bit-sparse, that is operations on&n; * them can use shifts and additions instead of multiplications for&n; * machines where multiplications are slow.&n; */
macro_line|#if BITS_PER_LONG == 32
multiline_comment|/* 2^31 + 2^29 - 2^25 + 2^22 - 2^19 - 2^16 + 1 */
DECL|macro|GOLDEN_RATIO_PRIME
mdefine_line|#define GOLDEN_RATIO_PRIME 0x9e370001UL
macro_line|#elif BITS_PER_LONG == 64
multiline_comment|/*  2^63 + 2^61 - 2^57 + 2^54 - 2^51 - 2^18 + 1 */
DECL|macro|GOLDEN_RATIO_PRIME
mdefine_line|#define GOLDEN_RATIO_PRIME 0x9e37fffffffc0001UL
macro_line|#else
macro_line|#error Define GOLDEN_RATIO_PRIME for your wordsize.
macro_line|#endif
DECL|function|hash_long
r_static
r_inline
r_int
r_int
id|hash_long
c_func
(paren
r_int
r_int
id|val
comma
r_int
r_int
id|bits
)paren
(brace
r_int
r_int
id|hash
op_assign
id|val
suffix:semicolon
macro_line|#if BITS_PER_LONG == 64
multiline_comment|/*  Sigh, gcc can&squot;t optimise this alone like it does for 32 bits. */
r_int
r_int
id|n
op_assign
id|hash
suffix:semicolon
id|n
op_lshift_assign
l_int|18
suffix:semicolon
id|hash
op_sub_assign
id|n
suffix:semicolon
id|n
op_lshift_assign
l_int|33
suffix:semicolon
id|hash
op_sub_assign
id|n
suffix:semicolon
id|n
op_lshift_assign
l_int|3
suffix:semicolon
id|hash
op_add_assign
id|n
suffix:semicolon
id|n
op_lshift_assign
l_int|3
suffix:semicolon
id|hash
op_sub_assign
id|n
suffix:semicolon
id|n
op_lshift_assign
l_int|4
suffix:semicolon
id|hash
op_add_assign
id|n
suffix:semicolon
id|n
op_lshift_assign
l_int|2
suffix:semicolon
id|hash
op_add_assign
id|n
suffix:semicolon
macro_line|#else
multiline_comment|/* On some cpus multiply is faster, on others gcc will do shifts */
id|hash
op_mul_assign
id|GOLDEN_RATIO_PRIME
suffix:semicolon
macro_line|#endif
multiline_comment|/* High bits are more random, so use them. */
r_return
id|hash
op_rshift
(paren
id|BITS_PER_LONG
op_minus
id|bits
)paren
suffix:semicolon
)brace
DECL|function|hash_ptr
r_static
r_inline
r_int
r_int
id|hash_ptr
c_func
(paren
r_void
op_star
id|ptr
comma
r_int
r_int
id|bits
)paren
(brace
r_return
id|hash_long
c_func
(paren
(paren
r_int
r_int
)paren
id|ptr
comma
id|bits
)paren
suffix:semicolon
)brace
macro_line|#endif /* _LINUX_HASH_H */
eof
