multiline_comment|/*&n; * $Id: cfi_endian.h,v 1.10 2001/06/18 11:00:46 abz Exp $&n; *&n; */
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#ifndef CONFIG_MTD_CFI_ADV_OPTIONS
DECL|macro|CFI_HOST_ENDIAN
mdefine_line|#define CFI_HOST_ENDIAN
macro_line|#else
macro_line|#ifdef CONFIG_MTD_CFI_NOSWAP
DECL|macro|CFI_HOST_ENDIAN
mdefine_line|#define CFI_HOST_ENDIAN
macro_line|#endif
macro_line|#ifdef CONFIG_MTD_CFI_LE_BYTE_SWAP
DECL|macro|CFI_LITTLE_ENDIAN
mdefine_line|#define CFI_LITTLE_ENDIAN
macro_line|#endif
macro_line|#ifdef CONFIG_MTD_CFI_BE_BYTE_SWAP
DECL|macro|CFI_BIG_ENDIAN
mdefine_line|#define CFI_BIG_ENDIAN
macro_line|#endif
macro_line|#endif
macro_line|#if defined(CFI_LITTLE_ENDIAN)
DECL|macro|cpu_to_cfi8
mdefine_line|#define cpu_to_cfi8(x) (x)
DECL|macro|cfi8_to_cpu
mdefine_line|#define cfi8_to_cpu(x) (x)
DECL|macro|cpu_to_cfi16
mdefine_line|#define cpu_to_cfi16(x) cpu_to_le16(x)
DECL|macro|cpu_to_cfi32
mdefine_line|#define cpu_to_cfi32(x) cpu_to_le32(x)
DECL|macro|cfi16_to_cpu
mdefine_line|#define cfi16_to_cpu(x) le16_to_cpu(x)
DECL|macro|cfi32_to_cpu
mdefine_line|#define cfi32_to_cpu(x) le32_to_cpu(x)
macro_line|#elif defined (CFI_BIG_ENDIAN)
DECL|macro|cpu_to_cfi8
mdefine_line|#define cpu_to_cfi8(x) (x)
DECL|macro|cfi8_to_cpu
mdefine_line|#define cfi8_to_cpu(x) (x)
DECL|macro|cpu_to_cfi16
mdefine_line|#define cpu_to_cfi16(x) cpu_to_be16(x)
DECL|macro|cpu_to_cfi32
mdefine_line|#define cpu_to_cfi32(x) cpu_to_be32(x)
DECL|macro|cfi16_to_cpu
mdefine_line|#define cfi16_to_cpu(x) be16_to_cpu(x)
DECL|macro|cfi32_to_cpu
mdefine_line|#define cfi32_to_cpu(x) be32_to_cpu(x)
macro_line|#elif defined (CFI_HOST_ENDIAN)
DECL|macro|cpu_to_cfi8
mdefine_line|#define cpu_to_cfi8(x) (x)
DECL|macro|cfi8_to_cpu
mdefine_line|#define cfi8_to_cpu(x) (x)
DECL|macro|cpu_to_cfi16
mdefine_line|#define cpu_to_cfi16(x) (x)
DECL|macro|cpu_to_cfi32
mdefine_line|#define cpu_to_cfi32(x) (x)
DECL|macro|cfi16_to_cpu
mdefine_line|#define cfi16_to_cpu(x) (x)
DECL|macro|cfi32_to_cpu
mdefine_line|#define cfi32_to_cpu(x) (x)
macro_line|#else
macro_line|#error No CFI endianness defined
macro_line|#endif
eof
