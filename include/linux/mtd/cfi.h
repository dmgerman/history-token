multiline_comment|/* Common Flash Interface structures &n; * See http://support.intel.com/design/flash/technote/index.htm&n; * $Id: cfi.h,v 1.35 2003/05/28 15:37:32 dwmw2 Exp $&n; */
macro_line|#ifndef __MTD_CFI_H__
DECL|macro|__MTD_CFI_H__
mdefine_line|#define __MTD_CFI_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/mtd/flashchip.h&gt;
macro_line|#include &lt;linux/mtd/cfi_endian.h&gt;
multiline_comment|/*&n; * You can optimize the code size and performance by defining only &n; * the geometry(ies) available on your hardware.&n; * CFIDEV_INTERLEAVE_n, where  represents the interleave (number of chips to fill the bus width)&n; * CFIDEV_BUSWIDTH_n, where n is the bus width in bytes (1, 2, 4 or 8 bytes)&n; *&n; * By default, all (known) geometries are supported.&n; */
macro_line|#ifndef CONFIG_MTD_CFI_GEOMETRY
multiline_comment|/* The default case - support all but 64-bit, which has&n;   a performance penalty */
DECL|macro|CFIDEV_INTERLEAVE_1
mdefine_line|#define CFIDEV_INTERLEAVE_1 (1)
DECL|macro|CFIDEV_INTERLEAVE_2
mdefine_line|#define CFIDEV_INTERLEAVE_2 (2)
DECL|macro|CFIDEV_INTERLEAVE_4
mdefine_line|#define CFIDEV_INTERLEAVE_4 (4)
DECL|macro|CFIDEV_BUSWIDTH_1
mdefine_line|#define CFIDEV_BUSWIDTH_1 (1)
DECL|macro|CFIDEV_BUSWIDTH_2
mdefine_line|#define CFIDEV_BUSWIDTH_2 (2)
DECL|macro|CFIDEV_BUSWIDTH_4
mdefine_line|#define CFIDEV_BUSWIDTH_4 (4)
DECL|typedef|cfi_word
r_typedef
id|__u32
id|cfi_word
suffix:semicolon
macro_line|#else
multiline_comment|/* Explicitly configured buswidth/interleave support */
macro_line|#ifdef CONFIG_MTD_CFI_I1
DECL|macro|CFIDEV_INTERLEAVE_1
mdefine_line|#define CFIDEV_INTERLEAVE_1 (1)
macro_line|#endif
macro_line|#ifdef CONFIG_MTD_CFI_I2
DECL|macro|CFIDEV_INTERLEAVE_2
mdefine_line|#define CFIDEV_INTERLEAVE_2 (2)
macro_line|#endif
macro_line|#ifdef CONFIG_MTD_CFI_I4
DECL|macro|CFIDEV_INTERLEAVE_4
mdefine_line|#define CFIDEV_INTERLEAVE_4 (4)
macro_line|#endif
macro_line|#ifdef CONFIG_MTD_CFI_I8
DECL|macro|CFIDEV_INTERLEAVE_8
mdefine_line|#define CFIDEV_INTERLEAVE_8 (8)
macro_line|#endif
macro_line|#ifdef CONFIG_MTD_CFI_B1
DECL|macro|CFIDEV_BUSWIDTH_1
mdefine_line|#define CFIDEV_BUSWIDTH_1 (1)
macro_line|#endif
macro_line|#ifdef CONFIG_MTD_CFI_B2
DECL|macro|CFIDEV_BUSWIDTH_2
mdefine_line|#define CFIDEV_BUSWIDTH_2 (2)
macro_line|#endif
macro_line|#ifdef CONFIG_MTD_CFI_B4
DECL|macro|CFIDEV_BUSWIDTH_4
mdefine_line|#define CFIDEV_BUSWIDTH_4 (4)
macro_line|#endif
macro_line|#ifdef CONFIG_MTD_CFI_B8
DECL|macro|CFIDEV_BUSWIDTH_8
mdefine_line|#define CFIDEV_BUSWIDTH_8 (8)
macro_line|#endif
multiline_comment|/* pick the largest necessary */
macro_line|#ifdef CONFIG_MTD_CFI_B8
DECL|typedef|cfi_word
r_typedef
id|__u64
id|cfi_word
suffix:semicolon
multiline_comment|/* This only works if asm/io.h is included first */
macro_line|#ifndef __raw_readll
DECL|macro|__raw_readll
mdefine_line|#define __raw_readll(addr)&t;(*(volatile __u64 *)(addr))
macro_line|#endif
macro_line|#ifndef __raw_writell
DECL|macro|__raw_writell
mdefine_line|#define __raw_writell(v, addr)&t;(*(volatile __u64 *)(addr) = (v))
macro_line|#endif
DECL|macro|CFI_WORD_64
mdefine_line|#define CFI_WORD_64
macro_line|#else  /* CONFIG_MTD_CFI_B8 */
multiline_comment|/* All others can use 32-bits. It&squot;s probably more efficient than&n;   the smaller types anyway */
DECL|typedef|cfi_word
r_typedef
id|__u32
id|cfi_word
suffix:semicolon
macro_line|#endif /* CONFIG_MTD_CFI_B8 */
macro_line|#endif
multiline_comment|/*&n; * The following macros are used to select the code to execute:&n; *   cfi_buswidth_is_*()&n; *   cfi_interleave_is_*()&n; *   [where * is either 1, 2, 4, or 8]&n; * Those macros should be used with &squot;if&squot; statements.  If only one of few&n; * geometry arrangements are selected, they expand to constants thus allowing&n; * the compiler (most of them being 0) to optimize away all the unneeded code,&n; * while still validating the syntax (which is not possible with embedded &n; * #if ... #endif constructs).&n; * The exception to this is the 64-bit versions, which need an extension&n; * to the cfi_word type, and cause compiler warnings about shifts being&n; * out of range.&n; */
macro_line|#ifdef CFIDEV_INTERLEAVE_1
macro_line|# ifdef CFIDEV_INTERLEAVE
DECL|macro|CFIDEV_INTERLEAVE
macro_line|#  undef CFIDEV_INTERLEAVE
DECL|macro|CFIDEV_INTERLEAVE
macro_line|#  define CFIDEV_INTERLEAVE (cfi-&gt;interleave)
macro_line|# else
DECL|macro|CFIDEV_INTERLEAVE
macro_line|#  define CFIDEV_INTERLEAVE CFIDEV_INTERLEAVE_1
macro_line|# endif
DECL|macro|cfi_interleave_is_1
macro_line|# define cfi_interleave_is_1() (CFIDEV_INTERLEAVE == CFIDEV_INTERLEAVE_1)
macro_line|#else
DECL|macro|cfi_interleave_is_1
macro_line|# define cfi_interleave_is_1() (0)
macro_line|#endif
macro_line|#ifdef CFIDEV_INTERLEAVE_2
macro_line|# ifdef CFIDEV_INTERLEAVE
DECL|macro|CFIDEV_INTERLEAVE
macro_line|#  undef CFIDEV_INTERLEAVE
DECL|macro|CFIDEV_INTERLEAVE
macro_line|#  define CFIDEV_INTERLEAVE (cfi-&gt;interleave)
macro_line|# else
DECL|macro|CFIDEV_INTERLEAVE
macro_line|#  define CFIDEV_INTERLEAVE CFIDEV_INTERLEAVE_2
macro_line|# endif
DECL|macro|cfi_interleave_is_2
macro_line|# define cfi_interleave_is_2() (CFIDEV_INTERLEAVE == CFIDEV_INTERLEAVE_2)
macro_line|#else
DECL|macro|cfi_interleave_is_2
macro_line|# define cfi_interleave_is_2() (0)
macro_line|#endif
macro_line|#ifdef CFIDEV_INTERLEAVE_4
macro_line|# ifdef CFIDEV_INTERLEAVE
DECL|macro|CFIDEV_INTERLEAVE
macro_line|#  undef CFIDEV_INTERLEAVE
DECL|macro|CFIDEV_INTERLEAVE
macro_line|#  define CFIDEV_INTERLEAVE (cfi-&gt;interleave)
macro_line|# else
DECL|macro|CFIDEV_INTERLEAVE
macro_line|#  define CFIDEV_INTERLEAVE CFIDEV_INTERLEAVE_4
macro_line|# endif
DECL|macro|cfi_interleave_is_4
macro_line|# define cfi_interleave_is_4() (CFIDEV_INTERLEAVE == CFIDEV_INTERLEAVE_4)
macro_line|#else
DECL|macro|cfi_interleave_is_4
macro_line|# define cfi_interleave_is_4() (0)
macro_line|#endif
macro_line|#ifdef CFIDEV_INTERLEAVE_8
macro_line|# ifdef CFIDEV_INTERLEAVE
DECL|macro|CFIDEV_INTERLEAVE
macro_line|#  undef CFIDEV_INTERLEAVE
DECL|macro|CFIDEV_INTERLEAVE
macro_line|#  define CFIDEV_INTERLEAVE (cfi-&gt;interleave)
macro_line|# else
DECL|macro|CFIDEV_INTERLEAVE
macro_line|#  define CFIDEV_INTERLEAVE CFIDEV_INTERLEAVE_8
macro_line|# endif
DECL|macro|cfi_interleave_is_8
macro_line|# define cfi_interleave_is_8() (CFIDEV_INTERLEAVE == CFIDEV_INTERLEAVE_8)
macro_line|#else
DECL|macro|cfi_interleave_is_8
macro_line|# define cfi_interleave_is_8() (0)
macro_line|#endif
macro_line|#ifndef CFIDEV_INTERLEAVE
macro_line|#error You must define at least one interleave to support!
macro_line|#endif
macro_line|#ifdef CFIDEV_BUSWIDTH_1
macro_line|# ifdef CFIDEV_BUSWIDTH
DECL|macro|CFIDEV_BUSWIDTH
macro_line|#  undef CFIDEV_BUSWIDTH
DECL|macro|CFIDEV_BUSWIDTH
macro_line|#  define CFIDEV_BUSWIDTH (map-&gt;buswidth)
macro_line|# else
DECL|macro|CFIDEV_BUSWIDTH
macro_line|#  define CFIDEV_BUSWIDTH CFIDEV_BUSWIDTH_1
macro_line|# endif
DECL|macro|cfi_buswidth_is_1
macro_line|# define cfi_buswidth_is_1() (CFIDEV_BUSWIDTH == CFIDEV_BUSWIDTH_1)
macro_line|#else
DECL|macro|cfi_buswidth_is_1
macro_line|# define cfi_buswidth_is_1() (0)
macro_line|#endif
macro_line|#ifdef CFIDEV_BUSWIDTH_2
macro_line|# ifdef CFIDEV_BUSWIDTH
DECL|macro|CFIDEV_BUSWIDTH
macro_line|#  undef CFIDEV_BUSWIDTH
DECL|macro|CFIDEV_BUSWIDTH
macro_line|#  define CFIDEV_BUSWIDTH (map-&gt;buswidth)
macro_line|# else
DECL|macro|CFIDEV_BUSWIDTH
macro_line|#  define CFIDEV_BUSWIDTH CFIDEV_BUSWIDTH_2
macro_line|# endif
DECL|macro|cfi_buswidth_is_2
macro_line|# define cfi_buswidth_is_2() (CFIDEV_BUSWIDTH == CFIDEV_BUSWIDTH_2)
macro_line|#else
DECL|macro|cfi_buswidth_is_2
macro_line|# define cfi_buswidth_is_2() (0)
macro_line|#endif
macro_line|#ifdef CFIDEV_BUSWIDTH_4
macro_line|# ifdef CFIDEV_BUSWIDTH
DECL|macro|CFIDEV_BUSWIDTH
macro_line|#  undef CFIDEV_BUSWIDTH
DECL|macro|CFIDEV_BUSWIDTH
macro_line|#  define CFIDEV_BUSWIDTH (map-&gt;buswidth)
macro_line|# else
DECL|macro|CFIDEV_BUSWIDTH
macro_line|#  define CFIDEV_BUSWIDTH CFIDEV_BUSWIDTH_4
macro_line|# endif
DECL|macro|cfi_buswidth_is_4
macro_line|# define cfi_buswidth_is_4() (CFIDEV_BUSWIDTH == CFIDEV_BUSWIDTH_4)
macro_line|#else
DECL|macro|cfi_buswidth_is_4
macro_line|# define cfi_buswidth_is_4() (0)
macro_line|#endif
macro_line|#ifdef CFIDEV_BUSWIDTH_8
macro_line|# ifdef CFIDEV_BUSWIDTH
DECL|macro|CFIDEV_BUSWIDTH
macro_line|#  undef CFIDEV_BUSWIDTH
DECL|macro|CFIDEV_BUSWIDTH
macro_line|#  define CFIDEV_BUSWIDTH (map-&gt;buswidth)
macro_line|# else
DECL|macro|CFIDEV_BUSWIDTH
macro_line|#  define CFIDEV_BUSWIDTH CFIDEV_BUSWIDTH_8
macro_line|# endif
DECL|macro|cfi_buswidth_is_8
macro_line|# define cfi_buswidth_is_8() (CFIDEV_BUSWIDTH == CFIDEV_BUSWIDTH_8)
macro_line|#else
DECL|macro|cfi_buswidth_is_8
macro_line|# define cfi_buswidth_is_8() (0)
macro_line|#endif
macro_line|#ifndef CFIDEV_BUSWIDTH
macro_line|#error You must define at least one bus width to support!
macro_line|#endif
multiline_comment|/* NB: these values must represents the number of bytes needed to meet the &n; *     device type (x8, x16, x32).  Eg. a 32 bit device is 4 x 8 bytes. &n; *     These numbers are used in calculations.&n; */
DECL|macro|CFI_DEVICETYPE_X8
mdefine_line|#define CFI_DEVICETYPE_X8  (8 / 8)
DECL|macro|CFI_DEVICETYPE_X16
mdefine_line|#define CFI_DEVICETYPE_X16 (16 / 8)
DECL|macro|CFI_DEVICETYPE_X32
mdefine_line|#define CFI_DEVICETYPE_X32 (32 / 8)
DECL|macro|CFI_DEVICETYPE_X64
mdefine_line|#define CFI_DEVICETYPE_X64 (64 / 8)
multiline_comment|/* NB: We keep these structures in memory in HOST byteorder, except&n; * where individually noted.&n; */
multiline_comment|/* Basic Query Structure */
DECL|struct|cfi_ident
r_struct
id|cfi_ident
(brace
DECL|member|qry
id|__u8
id|qry
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|P_ID
id|__u16
id|P_ID
suffix:semicolon
DECL|member|P_ADR
id|__u16
id|P_ADR
suffix:semicolon
DECL|member|A_ID
id|__u16
id|A_ID
suffix:semicolon
DECL|member|A_ADR
id|__u16
id|A_ADR
suffix:semicolon
DECL|member|VccMin
id|__u8
id|VccMin
suffix:semicolon
DECL|member|VccMax
id|__u8
id|VccMax
suffix:semicolon
DECL|member|VppMin
id|__u8
id|VppMin
suffix:semicolon
DECL|member|VppMax
id|__u8
id|VppMax
suffix:semicolon
DECL|member|WordWriteTimeoutTyp
id|__u8
id|WordWriteTimeoutTyp
suffix:semicolon
DECL|member|BufWriteTimeoutTyp
id|__u8
id|BufWriteTimeoutTyp
suffix:semicolon
DECL|member|BlockEraseTimeoutTyp
id|__u8
id|BlockEraseTimeoutTyp
suffix:semicolon
DECL|member|ChipEraseTimeoutTyp
id|__u8
id|ChipEraseTimeoutTyp
suffix:semicolon
DECL|member|WordWriteTimeoutMax
id|__u8
id|WordWriteTimeoutMax
suffix:semicolon
DECL|member|BufWriteTimeoutMax
id|__u8
id|BufWriteTimeoutMax
suffix:semicolon
DECL|member|BlockEraseTimeoutMax
id|__u8
id|BlockEraseTimeoutMax
suffix:semicolon
DECL|member|ChipEraseTimeoutMax
id|__u8
id|ChipEraseTimeoutMax
suffix:semicolon
DECL|member|DevSize
id|__u8
id|DevSize
suffix:semicolon
DECL|member|InterfaceDesc
id|__u16
id|InterfaceDesc
suffix:semicolon
DECL|member|MaxBufWriteSize
id|__u16
id|MaxBufWriteSize
suffix:semicolon
DECL|member|NumEraseRegions
id|__u8
id|NumEraseRegions
suffix:semicolon
DECL|member|EraseRegionInfo
id|__u32
id|EraseRegionInfo
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Not host ordered */
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Extended Query Structure for both PRI and ALT */
DECL|struct|cfi_extquery
r_struct
id|cfi_extquery
(brace
DECL|member|pri
id|__u8
id|pri
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|MajorVersion
id|__u8
id|MajorVersion
suffix:semicolon
DECL|member|MinorVersion
id|__u8
id|MinorVersion
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Vendor-Specific PRI for Intel/Sharp Extended Command Set (0x0001) */
DECL|struct|cfi_pri_intelext
r_struct
id|cfi_pri_intelext
(brace
DECL|member|pri
id|__u8
id|pri
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|MajorVersion
id|__u8
id|MajorVersion
suffix:semicolon
DECL|member|MinorVersion
id|__u8
id|MinorVersion
suffix:semicolon
DECL|member|FeatureSupport
id|__u32
id|FeatureSupport
suffix:semicolon
DECL|member|SuspendCmdSupport
id|__u8
id|SuspendCmdSupport
suffix:semicolon
DECL|member|BlkStatusRegMask
id|__u16
id|BlkStatusRegMask
suffix:semicolon
DECL|member|VccOptimal
id|__u8
id|VccOptimal
suffix:semicolon
DECL|member|VppOptimal
id|__u8
id|VppOptimal
suffix:semicolon
DECL|member|NumProtectionFields
id|__u8
id|NumProtectionFields
suffix:semicolon
DECL|member|ProtRegAddr
id|__u16
id|ProtRegAddr
suffix:semicolon
DECL|member|FactProtRegSize
id|__u8
id|FactProtRegSize
suffix:semicolon
DECL|member|UserProtRegSize
id|__u8
id|UserProtRegSize
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|cfi_pri_query
r_struct
id|cfi_pri_query
(brace
DECL|member|NumFields
id|__u8
id|NumFields
suffix:semicolon
DECL|member|ProtField
id|__u32
id|ProtField
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Not host ordered */
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|cfi_bri_query
r_struct
id|cfi_bri_query
(brace
DECL|member|PageModeReadCap
id|__u8
id|PageModeReadCap
suffix:semicolon
DECL|member|NumFields
id|__u8
id|NumFields
suffix:semicolon
DECL|member|ConfField
id|__u32
id|ConfField
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Not host ordered */
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|P_ID_NONE
mdefine_line|#define P_ID_NONE 0
DECL|macro|P_ID_INTEL_EXT
mdefine_line|#define P_ID_INTEL_EXT 1
DECL|macro|P_ID_AMD_STD
mdefine_line|#define P_ID_AMD_STD 2
DECL|macro|P_ID_INTEL_STD
mdefine_line|#define P_ID_INTEL_STD 3
DECL|macro|P_ID_AMD_EXT
mdefine_line|#define P_ID_AMD_EXT 4
DECL|macro|P_ID_MITSUBISHI_STD
mdefine_line|#define P_ID_MITSUBISHI_STD 256
DECL|macro|P_ID_MITSUBISHI_EXT
mdefine_line|#define P_ID_MITSUBISHI_EXT 257
DECL|macro|P_ID_RESERVED
mdefine_line|#define P_ID_RESERVED 65535
DECL|macro|CFI_MODE_CFI
mdefine_line|#define CFI_MODE_CFI&t;1
DECL|macro|CFI_MODE_JEDEC
mdefine_line|#define CFI_MODE_JEDEC&t;0
DECL|struct|cfi_private
r_struct
id|cfi_private
(brace
DECL|member|cmdset
id|__u16
id|cmdset
suffix:semicolon
DECL|member|cmdset_priv
r_void
op_star
id|cmdset_priv
suffix:semicolon
DECL|member|interleave
r_int
id|interleave
suffix:semicolon
DECL|member|device_type
r_int
id|device_type
suffix:semicolon
DECL|member|cfi_mode
r_int
id|cfi_mode
suffix:semicolon
multiline_comment|/* Are we a JEDEC device pretending to be CFI? */
DECL|member|addr_unlock1
r_int
id|addr_unlock1
suffix:semicolon
DECL|member|addr_unlock2
r_int
id|addr_unlock2
suffix:semicolon
DECL|member|fast_prog
r_int
id|fast_prog
suffix:semicolon
DECL|member|cmdset_setup
r_struct
id|mtd_info
op_star
(paren
op_star
id|cmdset_setup
)paren
(paren
r_struct
id|map_info
op_star
)paren
suffix:semicolon
DECL|member|cfiq
r_struct
id|cfi_ident
op_star
id|cfiq
suffix:semicolon
multiline_comment|/* For now only one. We insist that all devs&n;&t;&t;&t;&t;  must be of the same type. */
DECL|member|mfr
DECL|member|id
r_int
id|mfr
comma
id|id
suffix:semicolon
DECL|member|numchips
r_int
id|numchips
suffix:semicolon
DECL|member|chipshift
r_int
r_int
id|chipshift
suffix:semicolon
multiline_comment|/* Because they&squot;re of the same type */
DECL|member|im_name
r_const
r_char
op_star
id|im_name
suffix:semicolon
multiline_comment|/* inter_module name for cmdset_setup */
DECL|member|chips
r_struct
id|flchip
id|chips
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* per-chip data structure for each chip */
)brace
suffix:semicolon
DECL|macro|MAX_CFI_CHIPS
mdefine_line|#define MAX_CFI_CHIPS 8 /* Entirely arbitrary to avoid realloc() */
multiline_comment|/*&n; * Returns the command address according to the given geometry.&n; */
DECL|function|cfi_build_cmd_addr
r_static
r_inline
id|__u32
id|cfi_build_cmd_addr
c_func
(paren
id|__u32
id|cmd_ofs
comma
r_int
id|interleave
comma
r_int
id|type
)paren
(brace
r_return
(paren
id|cmd_ofs
op_star
id|type
)paren
op_star
id|interleave
suffix:semicolon
)brace
multiline_comment|/*&n; * Transforms the CFI command for the given geometry (bus width &amp; interleave.&n; */
DECL|function|cfi_build_cmd
r_static
r_inline
id|cfi_word
id|cfi_build_cmd
c_func
(paren
id|u_char
id|cmd
comma
r_struct
id|map_info
op_star
id|map
comma
r_struct
id|cfi_private
op_star
id|cfi
)paren
(brace
id|cfi_word
id|val
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cfi_buswidth_is_1
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* 1 x8 device */
id|val
op_assign
id|cmd
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cfi_buswidth_is_2
c_func
(paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|cfi_interleave_is_1
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* 1 x16 device in x16 mode */
id|val
op_assign
id|cpu_to_cfi16
c_func
(paren
id|cmd
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cfi_interleave_is_2
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* 2 (x8, x16 or x32) devices in x8 mode */
id|val
op_assign
id|cpu_to_cfi16
c_func
(paren
(paren
id|cmd
op_lshift
l_int|8
)paren
op_or
id|cmd
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|cfi_buswidth_is_4
c_func
(paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|cfi_interleave_is_1
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* 1 x32 device in x32 mode */
id|val
op_assign
id|cpu_to_cfi32
c_func
(paren
id|cmd
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cfi_interleave_is_2
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* 2 x16 device in x16 mode */
id|val
op_assign
id|cpu_to_cfi32
c_func
(paren
(paren
id|cmd
op_lshift
l_int|16
)paren
op_or
id|cmd
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cfi_interleave_is_4
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* 4 (x8, x16 or x32) devices in x8 mode */
id|val
op_assign
(paren
id|cmd
op_lshift
l_int|16
)paren
op_or
id|cmd
suffix:semicolon
id|val
op_assign
id|cpu_to_cfi32
c_func
(paren
(paren
id|val
op_lshift
l_int|8
)paren
op_or
id|val
)paren
suffix:semicolon
)brace
macro_line|#ifdef CFI_WORD_64
)brace
r_else
r_if
c_cond
(paren
id|cfi_buswidth_is_8
c_func
(paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|cfi_interleave_is_1
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* 1 x64 device in x64 mode */
id|val
op_assign
id|cpu_to_cfi64
c_func
(paren
id|cmd
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cfi_interleave_is_2
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* 2 x32 device in x32 mode */
id|val
op_assign
id|cmd
suffix:semicolon
id|val
op_assign
id|cpu_to_cfi64
c_func
(paren
(paren
id|val
op_lshift
l_int|32
)paren
op_or
id|val
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cfi_interleave_is_4
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* 4 (x16, x32 or x64) devices in x16 mode */
id|val
op_assign
(paren
id|cmd
op_lshift
l_int|16
)paren
op_or
id|cmd
suffix:semicolon
id|val
op_assign
id|cpu_to_cfi64
c_func
(paren
(paren
id|val
op_lshift
l_int|32
)paren
op_or
id|val
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cfi_interleave_is_8
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* 8 (x8, x16 or x32) devices in x8 mode */
id|val
op_assign
(paren
id|cmd
op_lshift
l_int|8
)paren
op_or
id|cmd
suffix:semicolon
id|val
op_assign
(paren
id|val
op_lshift
l_int|16
)paren
op_or
id|val
suffix:semicolon
id|val
op_assign
(paren
id|val
op_lshift
l_int|32
)paren
op_or
id|val
suffix:semicolon
id|val
op_assign
id|cpu_to_cfi64
c_func
(paren
id|val
)paren
suffix:semicolon
)brace
macro_line|#endif /* CFI_WORD_64 */
)brace
r_return
id|val
suffix:semicolon
)brace
DECL|macro|CMD
mdefine_line|#define CMD(x)  cfi_build_cmd((x), map, cfi)
multiline_comment|/*&n; * Read a value according to the bus width.&n; */
DECL|function|cfi_read
r_static
r_inline
id|cfi_word
id|cfi_read
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
id|__u32
id|addr
)paren
(brace
r_if
c_cond
(paren
id|cfi_buswidth_is_1
c_func
(paren
)paren
)paren
(brace
r_return
id|map_read8
c_func
(paren
id|map
comma
id|addr
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cfi_buswidth_is_2
c_func
(paren
)paren
)paren
(brace
r_return
id|map_read16
c_func
(paren
id|map
comma
id|addr
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cfi_buswidth_is_4
c_func
(paren
)paren
)paren
(brace
r_return
id|map_read32
c_func
(paren
id|map
comma
id|addr
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cfi_buswidth_is_8
c_func
(paren
)paren
)paren
(brace
r_return
id|map_read64
c_func
(paren
id|map
comma
id|addr
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Write a value according to the bus width.&n; */
DECL|function|cfi_write
r_static
r_inline
r_void
id|cfi_write
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
id|cfi_word
id|val
comma
id|__u32
id|addr
)paren
(brace
r_if
c_cond
(paren
id|cfi_buswidth_is_1
c_func
(paren
)paren
)paren
(brace
id|map_write8
c_func
(paren
id|map
comma
id|val
comma
id|addr
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cfi_buswidth_is_2
c_func
(paren
)paren
)paren
(brace
id|map_write16
c_func
(paren
id|map
comma
id|val
comma
id|addr
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cfi_buswidth_is_4
c_func
(paren
)paren
)paren
(brace
id|map_write32
c_func
(paren
id|map
comma
id|val
comma
id|addr
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cfi_buswidth_is_8
c_func
(paren
)paren
)paren
(brace
id|map_write64
c_func
(paren
id|map
comma
id|val
comma
id|addr
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Sends a CFI command to a bank of flash for the given geometry.&n; *&n; * Returns the offset in flash where the command was written.&n; * If prev_val is non-null, it will be set to the value at the command address,&n; * before the command was written.&n; */
DECL|function|cfi_send_gen_cmd
r_static
r_inline
id|__u32
id|cfi_send_gen_cmd
c_func
(paren
id|u_char
id|cmd
comma
id|__u32
id|cmd_addr
comma
id|__u32
id|base
comma
r_struct
id|map_info
op_star
id|map
comma
r_struct
id|cfi_private
op_star
id|cfi
comma
r_int
id|type
comma
id|cfi_word
op_star
id|prev_val
)paren
(brace
id|cfi_word
id|val
suffix:semicolon
id|__u32
id|addr
op_assign
id|base
op_plus
id|cfi_build_cmd_addr
c_func
(paren
id|cmd_addr
comma
id|CFIDEV_INTERLEAVE
comma
id|type
)paren
suffix:semicolon
id|val
op_assign
id|cfi_build_cmd
c_func
(paren
id|cmd
comma
id|map
comma
id|cfi
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prev_val
)paren
op_star
id|prev_val
op_assign
id|cfi_read
c_func
(paren
id|map
comma
id|addr
)paren
suffix:semicolon
id|cfi_write
c_func
(paren
id|map
comma
id|val
comma
id|addr
)paren
suffix:semicolon
r_return
id|addr
op_minus
id|base
suffix:semicolon
)brace
DECL|function|cfi_read_query
r_static
r_inline
id|__u8
id|cfi_read_query
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
id|__u32
id|addr
)paren
(brace
r_if
c_cond
(paren
id|cfi_buswidth_is_1
c_func
(paren
)paren
)paren
(brace
r_return
id|map_read8
c_func
(paren
id|map
comma
id|addr
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cfi_buswidth_is_2
c_func
(paren
)paren
)paren
(brace
r_return
id|cfi16_to_cpu
c_func
(paren
id|map_read16
c_func
(paren
id|map
comma
id|addr
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cfi_buswidth_is_4
c_func
(paren
)paren
)paren
(brace
r_return
id|cfi32_to_cpu
c_func
(paren
id|map_read32
c_func
(paren
id|map
comma
id|addr
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cfi_buswidth_is_8
c_func
(paren
)paren
)paren
(brace
r_return
id|cfi64_to_cpu
c_func
(paren
id|map_read64
c_func
(paren
id|map
comma
id|addr
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|cfi_udelay
r_static
r_inline
r_void
id|cfi_udelay
c_func
(paren
r_int
id|us
)paren
(brace
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,2,0)
r_int
r_int
id|t
op_assign
id|us
op_star
id|HZ
op_div
l_int|1000000
suffix:semicolon
r_if
c_cond
(paren
id|t
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|t
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
id|udelay
c_func
(paren
id|us
)paren
suffix:semicolon
id|cond_resched
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|cfi_spin_lock
r_static
r_inline
r_void
id|cfi_spin_lock
c_func
(paren
id|spinlock_t
op_star
id|mutex
)paren
(brace
id|spin_lock_bh
c_func
(paren
id|mutex
)paren
suffix:semicolon
)brace
DECL|function|cfi_spin_unlock
r_static
r_inline
r_void
id|cfi_spin_unlock
c_func
(paren
id|spinlock_t
op_star
id|mutex
)paren
(brace
id|spin_unlock_bh
c_func
(paren
id|mutex
)paren
suffix:semicolon
)brace
macro_line|#endif /* __MTD_CFI_H__ */
eof
