multiline_comment|/* Overhauled routines for dealing with different mmap regions of flash */
multiline_comment|/* $Id: map.h,v 1.45 2004/09/21 14:31:17 bjd Exp $ */
macro_line|#ifndef __LINUX_MTD_MAP_H__
DECL|macro|__LINUX_MTD_MAP_H__
mdefine_line|#define __LINUX_MTD_MAP_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/mtd/compatmac.h&gt;
macro_line|#include &lt;asm/unaligned.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/bug.h&gt;
macro_line|#ifdef CONFIG_MTD_MAP_BANK_WIDTH_1
DECL|macro|map_bankwidth
mdefine_line|#define map_bankwidth(map) 1
DECL|macro|map_bankwidth_is_1
mdefine_line|#define map_bankwidth_is_1(map) (map_bankwidth(map) == 1)
DECL|macro|map_bankwidth_is_large
mdefine_line|#define map_bankwidth_is_large(map) (0)
DECL|macro|map_words
mdefine_line|#define map_words(map) (1)
DECL|macro|MAX_MAP_BANKWIDTH
mdefine_line|#define MAX_MAP_BANKWIDTH 1
macro_line|#else
DECL|macro|map_bankwidth_is_1
mdefine_line|#define map_bankwidth_is_1(map) (0)
macro_line|#endif
macro_line|#ifdef CONFIG_MTD_MAP_BANK_WIDTH_2
macro_line|# ifdef map_bankwidth
DECL|macro|map_bankwidth
macro_line|#  undef map_bankwidth
DECL|macro|map_bankwidth
macro_line|#  define map_bankwidth(map) ((map)-&gt;bankwidth)
macro_line|# else
DECL|macro|map_bankwidth
macro_line|#  define map_bankwidth(map) 2
DECL|macro|map_bankwidth_is_large
macro_line|#  define map_bankwidth_is_large(map) (0)
DECL|macro|map_words
macro_line|#  define map_words(map) (1)
macro_line|# endif
DECL|macro|map_bankwidth_is_2
mdefine_line|#define map_bankwidth_is_2(map) (map_bankwidth(map) == 2)
DECL|macro|MAX_MAP_BANKWIDTH
macro_line|#undef MAX_MAP_BANKWIDTH
DECL|macro|MAX_MAP_BANKWIDTH
mdefine_line|#define MAX_MAP_BANKWIDTH 2
macro_line|#else
DECL|macro|map_bankwidth_is_2
mdefine_line|#define map_bankwidth_is_2(map) (0)
macro_line|#endif
macro_line|#ifdef CONFIG_MTD_MAP_BANK_WIDTH_4
macro_line|# ifdef map_bankwidth
DECL|macro|map_bankwidth
macro_line|#  undef map_bankwidth
DECL|macro|map_bankwidth
macro_line|#  define map_bankwidth(map) ((map)-&gt;bankwidth)
macro_line|# else
DECL|macro|map_bankwidth
macro_line|#  define map_bankwidth(map) 4
DECL|macro|map_bankwidth_is_large
macro_line|#  define map_bankwidth_is_large(map) (0)
DECL|macro|map_words
macro_line|#  define map_words(map) (1)
macro_line|# endif
DECL|macro|map_bankwidth_is_4
mdefine_line|#define map_bankwidth_is_4(map) (map_bankwidth(map) == 4)
DECL|macro|MAX_MAP_BANKWIDTH
macro_line|#undef MAX_MAP_BANKWIDTH
DECL|macro|MAX_MAP_BANKWIDTH
mdefine_line|#define MAX_MAP_BANKWIDTH 4
macro_line|#else
DECL|macro|map_bankwidth_is_4
mdefine_line|#define map_bankwidth_is_4(map) (0)
macro_line|#endif
multiline_comment|/* ensure we never evaluate anything shorted than an unsigned long&n; * to zero, and ensure we&squot;ll never miss the end of an comparison (bjd) */
DECL|macro|map_calc_words
mdefine_line|#define map_calc_words(map) ((map_bankwidth(map) + (sizeof(unsigned long)-1))/ sizeof(unsigned long))
macro_line|#ifdef CONFIG_MTD_MAP_BANK_WIDTH_8
macro_line|# ifdef map_bankwidth
DECL|macro|map_bankwidth
macro_line|#  undef map_bankwidth
DECL|macro|map_bankwidth
macro_line|#  define map_bankwidth(map) ((map)-&gt;bankwidth)
macro_line|#  if BITS_PER_LONG &lt; 64
DECL|macro|map_bankwidth_is_large
macro_line|#   undef map_bankwidth_is_large
DECL|macro|map_bankwidth_is_large
macro_line|#   define map_bankwidth_is_large(map) (map_bankwidth(map) &gt; BITS_PER_LONG/8)
DECL|macro|map_words
macro_line|#   undef map_words
DECL|macro|map_words
macro_line|#   define map_words(map) map_calc_words(map)
macro_line|#  endif
macro_line|# else
DECL|macro|map_bankwidth
macro_line|#  define map_bankwidth(map) 8
DECL|macro|map_bankwidth_is_large
macro_line|#  define map_bankwidth_is_large(map) (BITS_PER_LONG &lt; 64)
DECL|macro|map_words
macro_line|#  define map_words(map) map_calc_words(map)
macro_line|# endif
DECL|macro|map_bankwidth_is_8
mdefine_line|#define map_bankwidth_is_8(map) (map_bankwidth(map) == 8)
DECL|macro|MAX_MAP_BANKWIDTH
macro_line|#undef MAX_MAP_BANKWIDTH
DECL|macro|MAX_MAP_BANKWIDTH
mdefine_line|#define MAX_MAP_BANKWIDTH 8
macro_line|#else
DECL|macro|map_bankwidth_is_8
mdefine_line|#define map_bankwidth_is_8(map) (0)
macro_line|#endif
macro_line|#ifdef CONFIG_MTD_MAP_BANK_WIDTH_16
macro_line|# ifdef map_bankwidth
DECL|macro|map_bankwidth
macro_line|#  undef map_bankwidth
DECL|macro|map_bankwidth
macro_line|#  define map_bankwidth(map) ((map)-&gt;bankwidth)
DECL|macro|map_bankwidth_is_large
macro_line|#  undef map_bankwidth_is_large
DECL|macro|map_bankwidth_is_large
macro_line|#  define map_bankwidth_is_large(map) (map_bankwidth(map) &gt; BITS_PER_LONG/8)
DECL|macro|map_words
macro_line|#  undef map_words
DECL|macro|map_words
macro_line|#  define map_words(map) map_calc_words(map)
macro_line|# else
DECL|macro|map_bankwidth
macro_line|#  define map_bankwidth(map) 16
DECL|macro|map_bankwidth_is_large
macro_line|#  define map_bankwidth_is_large(map) (1)
DECL|macro|map_words
macro_line|#  define map_words(map) map_calc_words(map)
macro_line|# endif
DECL|macro|map_bankwidth_is_16
mdefine_line|#define map_bankwidth_is_16(map) (map_bankwidth(map) == 16)
DECL|macro|MAX_MAP_BANKWIDTH
macro_line|#undef MAX_MAP_BANKWIDTH
DECL|macro|MAX_MAP_BANKWIDTH
mdefine_line|#define MAX_MAP_BANKWIDTH 16
macro_line|#else
DECL|macro|map_bankwidth_is_16
mdefine_line|#define map_bankwidth_is_16(map) (0)
macro_line|#endif
macro_line|#ifdef CONFIG_MTD_MAP_BANK_WIDTH_32
macro_line|# ifdef map_bankwidth
DECL|macro|map_bankwidth
macro_line|#  undef map_bankwidth
DECL|macro|map_bankwidth
macro_line|#  define map_bankwidth(map) ((map)-&gt;bankwidth)
DECL|macro|map_bankwidth_is_large
macro_line|#  undef map_bankwidth_is_large
DECL|macro|map_bankwidth_is_large
macro_line|#  define map_bankwidth_is_large(map) (map_bankwidth(map) &gt; BITS_PER_LONG/8)
DECL|macro|map_words
macro_line|#  undef map_words
DECL|macro|map_words
macro_line|#  define map_words(map) map_calc_words(map)
macro_line|# else
DECL|macro|map_bankwidth
macro_line|#  define map_bankwidth(map) 32
DECL|macro|map_bankwidth_is_large
macro_line|#  define map_bankwidth_is_large(map) (1)
DECL|macro|map_words
macro_line|#  define map_words(map) map_calc_words(map)
macro_line|# endif
DECL|macro|map_bankwidth_is_32
mdefine_line|#define map_bankwidth_is_32(map) (map_bankwidth(map) == 32)
DECL|macro|MAX_MAP_BANKWIDTH
macro_line|#undef MAX_MAP_BANKWIDTH
DECL|macro|MAX_MAP_BANKWIDTH
mdefine_line|#define MAX_MAP_BANKWIDTH 32
macro_line|#else
DECL|macro|map_bankwidth_is_32
mdefine_line|#define map_bankwidth_is_32(map) (0)
macro_line|#endif
macro_line|#ifndef map_bankwidth
macro_line|#error &quot;No bus width supported. What&squot;s the point?&quot;
macro_line|#endif
DECL|function|map_bankwidth_supported
r_static
r_inline
r_int
id|map_bankwidth_supported
c_func
(paren
r_int
id|w
)paren
(brace
r_switch
c_cond
(paren
id|w
)paren
(brace
macro_line|#ifdef CONFIG_MTD_MAP_BANK_WIDTH_1
r_case
l_int|1
suffix:colon
macro_line|#endif
macro_line|#ifdef CONFIG_MTD_MAP_BANK_WIDTH_2
r_case
l_int|2
suffix:colon
macro_line|#endif
macro_line|#ifdef CONFIG_MTD_MAP_BANK_WIDTH_4
r_case
l_int|4
suffix:colon
macro_line|#endif
macro_line|#ifdef CONFIG_MTD_MAP_BANK_WIDTH_8
r_case
l_int|8
suffix:colon
macro_line|#endif
macro_line|#ifdef CONFIG_MTD_MAP_BANK_WIDTH_16
r_case
l_int|16
suffix:colon
macro_line|#endif
macro_line|#ifdef CONFIG_MTD_MAP_BANK_WIDTH_32
r_case
l_int|32
suffix:colon
macro_line|#endif
r_return
l_int|1
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|macro|MAX_MAP_LONGS
mdefine_line|#define MAX_MAP_LONGS ( ((MAX_MAP_BANKWIDTH*8) + BITS_PER_LONG - 1) / BITS_PER_LONG )
r_typedef
r_union
(brace
DECL|member|x
r_int
r_int
id|x
(braket
id|MAX_MAP_LONGS
)braket
suffix:semicolon
DECL|typedef|map_word
)brace
id|map_word
suffix:semicolon
multiline_comment|/* The map stuff is very simple. You fill in your struct map_info with&n;   a handful of routines for accessing the device, making sure they handle&n;   paging etc. correctly if your device needs it. Then you pass it off&n;   to a chip probe routine -- either JEDEC or CFI probe or both -- via&n;   do_map_probe(). If a chip is recognised, the probe code will invoke the&n;   appropriate chip driver (if present) and return a struct mtd_info.&n;   At which point, you fill in the mtd-&gt;module with your own module &n;   address, and register it with the MTD core code. Or you could partition&n;   it and register the partitions instead, or keep it for your own private&n;   use; whatever.&n;   &n;   The mtd-&gt;priv field will point to the struct map_info, and any further&n;   private data required by the chip driver is linked from the &n;   mtd-&gt;priv-&gt;fldrv_priv field. This allows the map driver to get at &n;   the destructor function map-&gt;fldrv_destroy() when it&squot;s tired&n;   of living.&n;*/
DECL|struct|map_info
r_struct
id|map_info
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|phys
r_int
r_int
id|phys
suffix:semicolon
DECL|macro|NO_XIP
mdefine_line|#define NO_XIP (-1UL)
DECL|member|virt
r_void
id|__iomem
op_star
id|virt
suffix:semicolon
DECL|member|cached
r_void
op_star
id|cached
suffix:semicolon
DECL|member|bankwidth
r_int
id|bankwidth
suffix:semicolon
multiline_comment|/* in octets. This isn&squot;t necessarily the width&n;&t;&t;       of actual bus cycles -- it&squot;s the repeat interval&n;&t;&t;      in bytes, before you are talking to the first chip again.&n;&t;&t;      */
macro_line|#ifdef CONFIG_MTD_COMPLEX_MAPPINGS
DECL|member|read
id|map_word
(paren
op_star
id|read
)paren
(paren
r_struct
id|map_info
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|copy_from
r_void
(paren
op_star
id|copy_from
)paren
(paren
r_struct
id|map_info
op_star
comma
r_void
op_star
comma
r_int
r_int
comma
id|ssize_t
)paren
suffix:semicolon
DECL|member|write
r_void
(paren
op_star
id|write
)paren
(paren
r_struct
id|map_info
op_star
comma
r_const
id|map_word
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|copy_to
r_void
(paren
op_star
id|copy_to
)paren
(paren
r_struct
id|map_info
op_star
comma
r_int
r_int
comma
r_const
r_void
op_star
comma
id|ssize_t
)paren
suffix:semicolon
multiline_comment|/* We can perhaps put in &squot;point&squot; and &squot;unpoint&squot; methods, if we really&n;&t;   want to enable XIP for non-linear mappings. Not yet though. */
macro_line|#endif
multiline_comment|/* It&squot;s possible for the map driver to use cached memory in its&n;&t;   copy_from implementation (and _only_ with copy_from).  However,&n;&t;   when the chip driver knows some flash area has changed contents,&n;&t;   it will signal it to the map driver through this routine to let&n;&t;   the map driver invalidate the corresponding cache as needed.&n;&t;   If there is no cache to care about this can be set to NULL. */
DECL|member|inval_cache
r_void
(paren
op_star
id|inval_cache
)paren
(paren
r_struct
id|map_info
op_star
comma
r_int
r_int
comma
id|ssize_t
)paren
suffix:semicolon
multiline_comment|/* set_vpp() must handle being reentered -- enable, enable, disable &n;&t;   must leave it enabled. */
DECL|member|set_vpp
r_void
(paren
op_star
id|set_vpp
)paren
(paren
r_struct
id|map_info
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|map_priv_1
r_int
r_int
id|map_priv_1
suffix:semicolon
DECL|member|map_priv_2
r_int
r_int
id|map_priv_2
suffix:semicolon
DECL|member|fldrv_priv
r_void
op_star
id|fldrv_priv
suffix:semicolon
DECL|member|fldrv
r_struct
id|mtd_chip_driver
op_star
id|fldrv
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mtd_chip_driver
r_struct
id|mtd_chip_driver
(brace
DECL|member|probe
r_struct
id|mtd_info
op_star
(paren
op_star
id|probe
)paren
(paren
r_struct
id|map_info
op_star
id|map
)paren
suffix:semicolon
DECL|member|destroy
r_void
(paren
op_star
id|destroy
)paren
(paren
r_struct
id|mtd_info
op_star
)paren
suffix:semicolon
DECL|member|module
r_struct
id|module
op_star
id|module
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
)brace
suffix:semicolon
r_void
id|register_mtd_chip_driver
c_func
(paren
r_struct
id|mtd_chip_driver
op_star
)paren
suffix:semicolon
r_void
id|unregister_mtd_chip_driver
c_func
(paren
r_struct
id|mtd_chip_driver
op_star
)paren
suffix:semicolon
r_struct
id|mtd_info
op_star
id|do_map_probe
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|map_info
op_star
id|map
)paren
suffix:semicolon
r_void
id|map_destroy
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
suffix:semicolon
DECL|macro|ENABLE_VPP
mdefine_line|#define ENABLE_VPP(map) do { if(map-&gt;set_vpp) map-&gt;set_vpp(map, 1); } while(0)
DECL|macro|DISABLE_VPP
mdefine_line|#define DISABLE_VPP(map) do { if(map-&gt;set_vpp) map-&gt;set_vpp(map, 0); } while(0)
DECL|macro|INVALIDATE_CACHED_RANGE
mdefine_line|#define INVALIDATE_CACHED_RANGE(map, from, size) &bslash;&n;&t;do { if(map-&gt;inval_cache) map-&gt;inval_cache(map, from, size); } while(0)
DECL|function|map_word_equal
r_static
r_inline
r_int
id|map_word_equal
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
id|map_word
id|val1
comma
id|map_word
id|val2
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|map_words
c_func
(paren
id|map
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|val1.x
(braket
id|i
)braket
op_ne
id|val2.x
(braket
id|i
)braket
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|map_word_and
r_static
r_inline
id|map_word
id|map_word_and
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
id|map_word
id|val1
comma
id|map_word
id|val2
)paren
(brace
id|map_word
id|r
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|map_words
c_func
(paren
id|map
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|r.x
(braket
id|i
)braket
op_assign
id|val1.x
(braket
id|i
)braket
op_amp
id|val2.x
(braket
id|i
)braket
suffix:semicolon
)brace
r_return
id|r
suffix:semicolon
)brace
DECL|function|map_word_or
r_static
r_inline
id|map_word
id|map_word_or
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
id|map_word
id|val1
comma
id|map_word
id|val2
)paren
(brace
id|map_word
id|r
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|map_words
c_func
(paren
id|map
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|r.x
(braket
id|i
)braket
op_assign
id|val1.x
(braket
id|i
)braket
op_or
id|val2.x
(braket
id|i
)braket
suffix:semicolon
)brace
r_return
id|r
suffix:semicolon
)brace
DECL|macro|map_word_andequal
mdefine_line|#define map_word_andequal(m, a, b, z) map_word_equal(m, z, map_word_and(m, a, b))
DECL|function|map_word_bitsset
r_static
r_inline
r_int
id|map_word_bitsset
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
id|map_word
id|val1
comma
id|map_word
id|val2
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|map_words
c_func
(paren
id|map
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|val1.x
(braket
id|i
)braket
op_amp
id|val2.x
(braket
id|i
)braket
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|map_word_load
r_static
r_inline
id|map_word
id|map_word_load
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_const
r_void
op_star
id|ptr
)paren
(brace
id|map_word
id|r
suffix:semicolon
r_if
c_cond
(paren
id|map_bankwidth_is_1
c_func
(paren
id|map
)paren
)paren
id|r.x
(braket
l_int|0
)braket
op_assign
op_star
(paren
r_int
r_char
op_star
)paren
id|ptr
suffix:semicolon
r_else
r_if
c_cond
(paren
id|map_bankwidth_is_2
c_func
(paren
id|map
)paren
)paren
id|r.x
(braket
l_int|0
)braket
op_assign
id|get_unaligned
c_func
(paren
(paren
r_uint16
op_star
)paren
id|ptr
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|map_bankwidth_is_4
c_func
(paren
id|map
)paren
)paren
id|r.x
(braket
l_int|0
)braket
op_assign
id|get_unaligned
c_func
(paren
(paren
r_uint32
op_star
)paren
id|ptr
)paren
suffix:semicolon
macro_line|#if BITS_PER_LONG &gt;= 64
r_else
r_if
c_cond
(paren
id|map_bankwidth_is_8
c_func
(paren
id|map
)paren
)paren
id|r.x
(braket
l_int|0
)braket
op_assign
id|get_unaligned
c_func
(paren
(paren
r_uint64
op_star
)paren
id|ptr
)paren
suffix:semicolon
macro_line|#endif
r_else
r_if
c_cond
(paren
id|map_bankwidth_is_large
c_func
(paren
id|map
)paren
)paren
id|memcpy
c_func
(paren
id|r.x
comma
id|ptr
comma
id|map-&gt;bankwidth
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
DECL|function|map_word_load_partial
r_static
r_inline
id|map_word
id|map_word_load_partial
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
id|map_word
id|orig
comma
r_const
r_int
r_char
op_star
id|buf
comma
r_int
id|start
comma
r_int
id|len
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|map_bankwidth_is_large
c_func
(paren
id|map
)paren
)paren
(brace
r_char
op_star
id|dest
op_assign
(paren
r_char
op_star
)paren
op_amp
id|orig
suffix:semicolon
id|memcpy
c_func
(paren
id|dest
op_plus
id|start
comma
id|buf
comma
id|len
)paren
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|i
op_assign
id|start
suffix:semicolon
id|i
OL
id|start
op_plus
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|bitpos
suffix:semicolon
macro_line|#ifdef __LITTLE_ENDIAN
id|bitpos
op_assign
id|i
op_star
l_int|8
suffix:semicolon
macro_line|#else /* __BIG_ENDIAN */
id|bitpos
op_assign
(paren
id|map_bankwidth
c_func
(paren
id|map
)paren
op_minus
l_int|1
op_minus
id|i
)paren
op_star
l_int|8
suffix:semicolon
macro_line|#endif
id|orig.x
(braket
l_int|0
)braket
op_and_assign
op_complement
(paren
l_int|0xff
op_lshift
id|bitpos
)paren
suffix:semicolon
id|orig.x
(braket
l_int|0
)braket
op_or_assign
id|buf
(braket
id|i
)braket
op_lshift
id|bitpos
suffix:semicolon
)brace
)brace
r_return
id|orig
suffix:semicolon
)brace
DECL|function|map_word_ff
r_static
r_inline
id|map_word
id|map_word_ff
c_func
(paren
r_struct
id|map_info
op_star
id|map
)paren
(brace
id|map_word
id|r
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|map_words
c_func
(paren
id|map
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|r.x
(braket
id|i
)braket
op_assign
op_complement
l_int|0UL
suffix:semicolon
)brace
r_return
id|r
suffix:semicolon
)brace
DECL|function|inline_map_read
r_static
r_inline
id|map_word
id|inline_map_read
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_int
r_int
id|ofs
)paren
(brace
id|map_word
id|r
suffix:semicolon
r_if
c_cond
(paren
id|map_bankwidth_is_1
c_func
(paren
id|map
)paren
)paren
id|r.x
(braket
l_int|0
)braket
op_assign
id|__raw_readb
c_func
(paren
id|map-&gt;virt
op_plus
id|ofs
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|map_bankwidth_is_2
c_func
(paren
id|map
)paren
)paren
id|r.x
(braket
l_int|0
)braket
op_assign
id|__raw_readw
c_func
(paren
id|map-&gt;virt
op_plus
id|ofs
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|map_bankwidth_is_4
c_func
(paren
id|map
)paren
)paren
id|r.x
(braket
l_int|0
)braket
op_assign
id|__raw_readl
c_func
(paren
id|map-&gt;virt
op_plus
id|ofs
)paren
suffix:semicolon
macro_line|#if BITS_PER_LONG &gt;= 64
r_else
r_if
c_cond
(paren
id|map_bankwidth_is_8
c_func
(paren
id|map
)paren
)paren
id|r.x
(braket
l_int|0
)braket
op_assign
id|__raw_readq
c_func
(paren
id|map-&gt;virt
op_plus
id|ofs
)paren
suffix:semicolon
macro_line|#endif
r_else
r_if
c_cond
(paren
id|map_bankwidth_is_large
c_func
(paren
id|map
)paren
)paren
id|memcpy_fromio
c_func
(paren
id|r.x
comma
id|map-&gt;virt
op_plus
id|ofs
comma
id|map-&gt;bankwidth
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
DECL|function|inline_map_write
r_static
r_inline
r_void
id|inline_map_write
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_const
id|map_word
id|datum
comma
r_int
r_int
id|ofs
)paren
(brace
r_if
c_cond
(paren
id|map_bankwidth_is_1
c_func
(paren
id|map
)paren
)paren
id|__raw_writeb
c_func
(paren
id|datum.x
(braket
l_int|0
)braket
comma
id|map-&gt;virt
op_plus
id|ofs
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|map_bankwidth_is_2
c_func
(paren
id|map
)paren
)paren
id|__raw_writew
c_func
(paren
id|datum.x
(braket
l_int|0
)braket
comma
id|map-&gt;virt
op_plus
id|ofs
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|map_bankwidth_is_4
c_func
(paren
id|map
)paren
)paren
id|__raw_writel
c_func
(paren
id|datum.x
(braket
l_int|0
)braket
comma
id|map-&gt;virt
op_plus
id|ofs
)paren
suffix:semicolon
macro_line|#if BITS_PER_LONG &gt;= 64
r_else
r_if
c_cond
(paren
id|map_bankwidth_is_8
c_func
(paren
id|map
)paren
)paren
id|__raw_writeq
c_func
(paren
id|datum.x
(braket
l_int|0
)braket
comma
id|map-&gt;virt
op_plus
id|ofs
)paren
suffix:semicolon
macro_line|#endif
r_else
r_if
c_cond
(paren
id|map_bankwidth_is_large
c_func
(paren
id|map
)paren
)paren
id|memcpy_toio
c_func
(paren
id|map-&gt;virt
op_plus
id|ofs
comma
id|datum.x
comma
id|map-&gt;bankwidth
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|inline_map_copy_from
r_static
r_inline
r_void
id|inline_map_copy_from
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_void
op_star
id|to
comma
r_int
r_int
id|from
comma
id|ssize_t
id|len
)paren
(brace
r_if
c_cond
(paren
id|map-&gt;cached
)paren
id|memcpy
c_func
(paren
id|to
comma
(paren
r_char
op_star
)paren
id|map-&gt;cached
op_plus
id|from
comma
id|len
)paren
suffix:semicolon
r_else
id|memcpy_fromio
c_func
(paren
id|to
comma
id|map-&gt;virt
op_plus
id|from
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|inline_map_copy_to
r_static
r_inline
r_void
id|inline_map_copy_to
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_int
r_int
id|to
comma
r_const
r_void
op_star
id|from
comma
id|ssize_t
id|len
)paren
(brace
id|memcpy_toio
c_func
(paren
id|map-&gt;virt
op_plus
id|to
comma
id|from
comma
id|len
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MTD_COMPLEX_MAPPINGS
DECL|macro|map_read
mdefine_line|#define map_read(map, ofs) (map)-&gt;read(map, ofs)
DECL|macro|map_copy_from
mdefine_line|#define map_copy_from(map, to, from, len) (map)-&gt;copy_from(map, to, from, len)
DECL|macro|map_write
mdefine_line|#define map_write(map, datum, ofs) (map)-&gt;write(map, datum, ofs)
DECL|macro|map_copy_to
mdefine_line|#define map_copy_to(map, to, from, len) (map)-&gt;copy_to(map, to, from, len)
r_extern
r_void
id|simple_map_init
c_func
(paren
r_struct
id|map_info
op_star
)paren
suffix:semicolon
DECL|macro|map_is_linear
mdefine_line|#define map_is_linear(map) (map-&gt;phys != NO_XIP)
macro_line|#else
DECL|macro|map_read
mdefine_line|#define map_read(map, ofs) inline_map_read(map, ofs)
DECL|macro|map_copy_from
mdefine_line|#define map_copy_from(map, to, from, len) inline_map_copy_from(map, to, from, len)
DECL|macro|map_write
mdefine_line|#define map_write(map, datum, ofs) inline_map_write(map, datum, ofs)
DECL|macro|map_copy_to
mdefine_line|#define map_copy_to(map, to, from, len) inline_map_copy_to(map, to, from, len)
DECL|macro|simple_map_init
mdefine_line|#define simple_map_init(map) BUG_ON(!map_bankwidth_supported((map)-&gt;bankwidth))
DECL|macro|map_is_linear
mdefine_line|#define map_is_linear(map) (1)
macro_line|#endif /* !CONFIG_MTD_COMPLEX_MAPPINGS */
macro_line|#endif /* __LINUX_MTD_MAP_H__ */
eof
