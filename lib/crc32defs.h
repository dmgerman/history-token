multiline_comment|/*&n; * There are multiple 16-bit CRC polynomials in common use, but this is&n; * *the* standard CRC-32 polynomial, first popularized by Ethernet.&n; * x^32+x^26+x^23+x^22+x^16+x^12+x^11+x^10+x^8+x^7+x^5+x^4+x^2+x^1+x^0&n; */
DECL|macro|CRCPOLY_LE
mdefine_line|#define CRCPOLY_LE 0xedb88320
DECL|macro|CRCPOLY_BE
mdefine_line|#define CRCPOLY_BE 0x04c11db7
multiline_comment|/* How many bits at a time to use.  Requires a table of 4&lt;&lt;CRC_xx_BITS bytes. */
multiline_comment|/* For less performance-sensitive, use 4 */
DECL|macro|CRC_LE_BITS
mdefine_line|#define CRC_LE_BITS 8
DECL|macro|CRC_BE_BITS
mdefine_line|#define CRC_BE_BITS 8
multiline_comment|/*&n; * Little-endian CRC computation.  Used with serial bit streams sent&n; * lsbit-first.  Be sure to use cpu_to_le32() to append the computed CRC.&n; */
macro_line|#if CRC_LE_BITS &gt; 8 || CRC_LE_BITS &lt; 1 || CRC_LE_BITS &amp; CRC_LE_BITS-1
macro_line|# error CRC_LE_BITS must be a power of 2 between 1 and 8
macro_line|#endif
multiline_comment|/*&n; * Big-endian CRC computation.  Used with serial bit streams sent&n; * msbit-first.  Be sure to use cpu_to_be32() to append the computed CRC.&n; */
macro_line|#if CRC_BE_BITS &gt; 8 || CRC_BE_BITS &lt; 1 || CRC_BE_BITS &amp; CRC_BE_BITS-1
macro_line|# error CRC_BE_BITS must be a power of 2 between 1 and 8
macro_line|#endif
eof
