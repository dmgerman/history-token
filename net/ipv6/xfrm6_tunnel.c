multiline_comment|/*&n; * Copyright (C)2003,2004 USAGI/WIDE Project&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; * Authors&t;Mitsuru KANDA  &lt;mk@linux-ipv6.org&gt;&n; * &t;&t;YOSHIFUJI Hideaki &lt;yoshfuji@linux-ipv6.org&gt;&n; *&n; * Based on net/ipv4/xfrm4_tunnel.c&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/xfrm.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/xfrm.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;linux/ipv6.h&gt;
macro_line|#include &lt;linux/icmpv6.h&gt;
macro_line|#ifdef CONFIG_IPV6_XFRM6_TUNNEL_DEBUG
DECL|macro|X6TDEBUG
macro_line|# define X6TDEBUG&t;3
macro_line|#else
DECL|macro|X6TDEBUG
macro_line|# define X6TDEBUG&t;1
macro_line|#endif
DECL|macro|X6TPRINTK
mdefine_line|#define X6TPRINTK(fmt, args...)&t;&t;printk(fmt, ## args)
DECL|macro|X6TNOPRINTK
mdefine_line|#define X6TNOPRINTK(fmt, args...)&t;do { ; } while(0)
macro_line|#if X6TDEBUG &gt;= 1
DECL|macro|X6TPRINTK1
macro_line|# define X6TPRINTK1&t;X6TPRINTK
macro_line|#else
DECL|macro|X6TPRINTK1
macro_line|# define X6TPRINTK1&t;X6TNOPRINTK
macro_line|#endif
macro_line|#if X6TDEBUG &gt;= 3
DECL|macro|X6TPRINTK3
macro_line|# define X6TPRINTK3&t;X6TPRINTK
macro_line|#else
DECL|macro|X6TPRINTK3
macro_line|# define X6TPRINTK3&t;X6TNOPRINTK
macro_line|#endif
multiline_comment|/*&n; * xfrm_tunnel_spi things are for allocating unique id (&quot;spi&quot;) &n; * per xfrm_address_t.&n; */
DECL|struct|xfrm6_tunnel_spi
r_struct
id|xfrm6_tunnel_spi
(brace
DECL|member|list_byaddr
r_struct
id|hlist_node
id|list_byaddr
suffix:semicolon
DECL|member|list_byspi
r_struct
id|hlist_node
id|list_byspi
suffix:semicolon
DECL|member|addr
id|xfrm_address_t
id|addr
suffix:semicolon
DECL|member|spi
id|u32
id|spi
suffix:semicolon
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
macro_line|#ifdef XFRM6_TUNNEL_SPI_MAGIC
DECL|member|magic
id|u32
id|magic
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_IPV6_XFRM6_TUNNEL_DEBUG
DECL|macro|XFRM6_TUNNEL_SPI_MAGIC
macro_line|# define XFRM6_TUNNEL_SPI_MAGIC 0xdeadbeef
macro_line|#endif
DECL|variable|xfrm6_tunnel_spi_lock
r_static
id|rwlock_t
id|xfrm6_tunnel_spi_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|xfrm6_tunnel_spi
r_static
id|u32
id|xfrm6_tunnel_spi
suffix:semicolon
DECL|macro|XFRM6_TUNNEL_SPI_MIN
mdefine_line|#define XFRM6_TUNNEL_SPI_MIN&t;1
DECL|macro|XFRM6_TUNNEL_SPI_MAX
mdefine_line|#define XFRM6_TUNNEL_SPI_MAX&t;0xffffffff
DECL|variable|xfrm6_tunnel_spi_kmem
r_static
id|kmem_cache_t
op_star
id|xfrm6_tunnel_spi_kmem
suffix:semicolon
DECL|macro|XFRM6_TUNNEL_SPI_BYADDR_HSIZE
mdefine_line|#define XFRM6_TUNNEL_SPI_BYADDR_HSIZE 256
DECL|macro|XFRM6_TUNNEL_SPI_BYSPI_HSIZE
mdefine_line|#define XFRM6_TUNNEL_SPI_BYSPI_HSIZE 256
DECL|variable|xfrm6_tunnel_spi_byaddr
r_static
r_struct
id|hlist_head
id|xfrm6_tunnel_spi_byaddr
(braket
id|XFRM6_TUNNEL_SPI_BYADDR_HSIZE
)braket
suffix:semicolon
DECL|variable|xfrm6_tunnel_spi_byspi
r_static
r_struct
id|hlist_head
id|xfrm6_tunnel_spi_byspi
(braket
id|XFRM6_TUNNEL_SPI_BYSPI_HSIZE
)braket
suffix:semicolon
macro_line|#ifdef XFRM6_TUNNEL_SPI_MAGIC
DECL|function|x6spi_check_magic
r_static
r_int
id|x6spi_check_magic
c_func
(paren
r_const
r_struct
id|xfrm6_tunnel_spi
op_star
id|x6spi
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|x6spi-&gt;magic
op_ne
id|XFRM6_TUNNEL_SPI_MAGIC
)paren
)paren
(brace
id|X6TPRINTK3
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s(): x6spi object &quot;
l_string|&quot;at %p has corrupted magic %08x &quot;
l_string|&quot;(should be %08x)&bslash;n&quot;
comma
id|name
comma
id|x6spi
comma
id|x6spi-&gt;magic
comma
id|XFRM6_TUNNEL_SPI_MAGIC
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else
DECL|function|x6spi_check_magic
r_static
r_int
r_inline
id|x6spi_check_magic
c_func
(paren
r_const
r_struct
id|xfrm6_tunnel_spi
op_star
id|x6spi
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|macro|X6SPI_CHECK_MAGIC
mdefine_line|#define X6SPI_CHECK_MAGIC(x6spi) x6spi_check_magic((x6spi), __FUNCTION__)
DECL|function|xfrm6_tunnel_spi_hash_byaddr
r_static
r_int
r_inline
id|xfrm6_tunnel_spi_hash_byaddr
c_func
(paren
id|xfrm_address_t
op_star
id|addr
)paren
(brace
r_int
id|h
suffix:semicolon
id|X6TPRINTK3
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s(addr=%p)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|addr
)paren
suffix:semicolon
id|h
op_assign
id|addr-&gt;a6
(braket
l_int|0
)braket
op_xor
id|addr-&gt;a6
(braket
l_int|1
)braket
op_xor
id|addr-&gt;a6
(braket
l_int|2
)braket
op_xor
id|addr-&gt;a6
(braket
l_int|3
)braket
suffix:semicolon
id|h
op_xor_assign
id|h
op_rshift
l_int|16
suffix:semicolon
id|h
op_xor_assign
id|h
op_rshift
l_int|8
suffix:semicolon
id|h
op_and_assign
id|XFRM6_TUNNEL_SPI_BYADDR_HSIZE
op_minus
l_int|1
suffix:semicolon
id|X6TPRINTK3
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s() = %u&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|h
)paren
suffix:semicolon
r_return
id|h
suffix:semicolon
)brace
DECL|function|xfrm6_tunnel_spi_hash_byspi
r_static
r_int
r_inline
id|xfrm6_tunnel_spi_hash_byspi
c_func
(paren
id|u32
id|spi
)paren
(brace
r_return
id|spi
op_mod
id|XFRM6_TUNNEL_SPI_BYSPI_HSIZE
suffix:semicolon
)brace
DECL|function|xfrm6_tunnel_spi_init
r_static
r_int
id|xfrm6_tunnel_spi_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|X6TPRINTK3
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s()&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|xfrm6_tunnel_spi
op_assign
l_int|0
suffix:semicolon
id|xfrm6_tunnel_spi_kmem
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;xfrm6_tunnel_spi&quot;
comma
r_sizeof
(paren
r_struct
id|xfrm6_tunnel_spi
)paren
comma
l_int|0
comma
id|SLAB_HWCACHE_ALIGN
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|xfrm6_tunnel_spi_kmem
)paren
(brace
id|X6TPRINTK1
c_func
(paren
id|KERN_ERR
l_string|&quot;%s(): failed to allocate xfrm6_tunnel_spi_kmem&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|XFRM6_TUNNEL_SPI_BYADDR_HSIZE
suffix:semicolon
id|i
op_increment
)paren
id|INIT_HLIST_HEAD
c_func
(paren
op_amp
id|xfrm6_tunnel_spi_byaddr
(braket
id|i
)braket
)paren
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
id|XFRM6_TUNNEL_SPI_BYSPI_HSIZE
suffix:semicolon
id|i
op_increment
)paren
id|INIT_HLIST_HEAD
c_func
(paren
op_amp
id|xfrm6_tunnel_spi_byspi
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xfrm6_tunnel_spi_fini
r_static
r_void
id|xfrm6_tunnel_spi_fini
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|X6TPRINTK3
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s()&bslash;n&quot;
comma
id|__FUNCTION__
)paren
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
id|XFRM6_TUNNEL_SPI_BYADDR_HSIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|hlist_empty
c_func
(paren
op_amp
id|xfrm6_tunnel_spi_byaddr
(braket
id|i
)braket
)paren
)paren
r_goto
id|err
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|XFRM6_TUNNEL_SPI_BYSPI_HSIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|hlist_empty
c_func
(paren
op_amp
id|xfrm6_tunnel_spi_byspi
(braket
id|i
)braket
)paren
)paren
r_goto
id|err
suffix:semicolon
)brace
id|kmem_cache_destroy
c_func
(paren
id|xfrm6_tunnel_spi_kmem
)paren
suffix:semicolon
id|xfrm6_tunnel_spi_kmem
op_assign
l_int|NULL
suffix:semicolon
r_return
suffix:semicolon
id|err
suffix:colon
id|X6TPRINTK1
c_func
(paren
id|KERN_ERR
l_string|&quot;%s(): table is not empty&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|__xfrm6_tunnel_spi_lookup
r_static
r_struct
id|xfrm6_tunnel_spi
op_star
id|__xfrm6_tunnel_spi_lookup
c_func
(paren
id|xfrm_address_t
op_star
id|saddr
)paren
(brace
r_struct
id|xfrm6_tunnel_spi
op_star
id|x6spi
suffix:semicolon
r_struct
id|hlist_node
op_star
id|pos
suffix:semicolon
id|X6TPRINTK3
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s(saddr=%p)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|saddr
)paren
suffix:semicolon
id|hlist_for_each_entry
c_func
(paren
id|x6spi
comma
id|pos
comma
op_amp
id|xfrm6_tunnel_spi_byaddr
(braket
id|xfrm6_tunnel_spi_hash_byaddr
c_func
(paren
id|saddr
)paren
)braket
comma
id|list_byaddr
)paren
(brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
op_amp
id|x6spi-&gt;addr
comma
id|saddr
comma
r_sizeof
(paren
id|x6spi-&gt;addr
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|X6SPI_CHECK_MAGIC
c_func
(paren
id|x6spi
)paren
suffix:semicolon
id|X6TPRINTK3
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s() = %p(%u)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|x6spi
comma
id|x6spi-&gt;spi
)paren
suffix:semicolon
r_return
id|x6spi
suffix:semicolon
)brace
)brace
id|X6TPRINTK3
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s() = NULL(0)&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|xfrm6_tunnel_spi_lookup
id|u32
id|xfrm6_tunnel_spi_lookup
c_func
(paren
id|xfrm_address_t
op_star
id|saddr
)paren
(brace
r_struct
id|xfrm6_tunnel_spi
op_star
id|x6spi
suffix:semicolon
id|u32
id|spi
suffix:semicolon
id|X6TPRINTK3
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s(saddr=%p)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|saddr
)paren
suffix:semicolon
id|read_lock_bh
c_func
(paren
op_amp
id|xfrm6_tunnel_spi_lock
)paren
suffix:semicolon
id|x6spi
op_assign
id|__xfrm6_tunnel_spi_lookup
c_func
(paren
id|saddr
)paren
suffix:semicolon
id|spi
op_assign
id|x6spi
ques
c_cond
id|x6spi-&gt;spi
suffix:colon
l_int|0
suffix:semicolon
id|read_unlock_bh
c_func
(paren
op_amp
id|xfrm6_tunnel_spi_lock
)paren
suffix:semicolon
r_return
id|spi
suffix:semicolon
)brace
DECL|function|__xfrm6_tunnel_alloc_spi
r_static
id|u32
id|__xfrm6_tunnel_alloc_spi
c_func
(paren
id|xfrm_address_t
op_star
id|saddr
)paren
(brace
id|u32
id|spi
suffix:semicolon
r_struct
id|xfrm6_tunnel_spi
op_star
id|x6spi
suffix:semicolon
r_struct
id|hlist_node
op_star
id|pos
suffix:semicolon
r_int
id|index
suffix:semicolon
id|X6TPRINTK3
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s(saddr=%p)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|saddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xfrm6_tunnel_spi
OL
id|XFRM6_TUNNEL_SPI_MIN
op_logical_or
id|xfrm6_tunnel_spi
op_ge
id|XFRM6_TUNNEL_SPI_MAX
)paren
id|xfrm6_tunnel_spi
op_assign
id|XFRM6_TUNNEL_SPI_MIN
suffix:semicolon
r_else
id|xfrm6_tunnel_spi
op_increment
suffix:semicolon
r_for
c_loop
(paren
id|spi
op_assign
id|xfrm6_tunnel_spi
suffix:semicolon
id|spi
op_le
id|XFRM6_TUNNEL_SPI_MAX
suffix:semicolon
id|spi
op_increment
)paren
(brace
id|index
op_assign
id|xfrm6_tunnel_spi_hash_byspi
c_func
(paren
id|spi
)paren
suffix:semicolon
id|hlist_for_each_entry
c_func
(paren
id|x6spi
comma
id|pos
comma
op_amp
id|xfrm6_tunnel_spi_byspi
(braket
id|index
)braket
comma
id|list_byspi
)paren
(brace
r_if
c_cond
(paren
id|x6spi-&gt;spi
op_eq
id|spi
)paren
r_goto
id|try_next_1
suffix:semicolon
)brace
id|xfrm6_tunnel_spi
op_assign
id|spi
suffix:semicolon
r_goto
id|alloc_spi
suffix:semicolon
id|try_next_1
suffix:colon
suffix:semicolon
)brace
r_for
c_loop
(paren
id|spi
op_assign
id|XFRM6_TUNNEL_SPI_MIN
suffix:semicolon
id|spi
OL
id|xfrm6_tunnel_spi
suffix:semicolon
id|spi
op_increment
)paren
(brace
id|index
op_assign
id|xfrm6_tunnel_spi_hash_byspi
c_func
(paren
id|spi
)paren
suffix:semicolon
id|hlist_for_each_entry
c_func
(paren
id|x6spi
comma
id|pos
comma
op_amp
id|xfrm6_tunnel_spi_byspi
(braket
id|index
)braket
comma
id|list_byspi
)paren
(brace
r_if
c_cond
(paren
id|x6spi-&gt;spi
op_eq
id|spi
)paren
r_goto
id|try_next_2
suffix:semicolon
)brace
id|xfrm6_tunnel_spi
op_assign
id|spi
suffix:semicolon
r_goto
id|alloc_spi
suffix:semicolon
id|try_next_2
suffix:colon
suffix:semicolon
)brace
id|spi
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|alloc_spi
suffix:colon
id|X6TPRINTK3
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s(): allocate new spi for &quot;
l_string|&quot;%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|NIP6
c_func
(paren
op_star
(paren
r_struct
id|in6_addr
op_star
)paren
id|saddr
)paren
)paren
suffix:semicolon
id|x6spi
op_assign
id|kmem_cache_alloc
c_func
(paren
id|xfrm6_tunnel_spi_kmem
comma
id|SLAB_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|x6spi
)paren
(brace
id|X6TPRINTK1
c_func
(paren
id|KERN_ERR
l_string|&quot;%s(): kmem_cache_alloc() failed&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
macro_line|#ifdef XFRM6_TUNNEL_SPI_MAGIC
id|x6spi-&gt;magic
op_assign
id|XFRM6_TUNNEL_SPI_MAGIC
suffix:semicolon
macro_line|#endif
id|memcpy
c_func
(paren
op_amp
id|x6spi-&gt;addr
comma
id|saddr
comma
r_sizeof
(paren
id|x6spi-&gt;addr
)paren
)paren
suffix:semicolon
id|x6spi-&gt;spi
op_assign
id|spi
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|x6spi-&gt;refcnt
comma
l_int|1
)paren
suffix:semicolon
id|hlist_add_head
c_func
(paren
op_amp
id|x6spi-&gt;list_byspi
comma
op_amp
id|xfrm6_tunnel_spi_byspi
(braket
id|index
)braket
)paren
suffix:semicolon
id|index
op_assign
id|xfrm6_tunnel_spi_hash_byaddr
c_func
(paren
id|saddr
)paren
suffix:semicolon
id|hlist_add_head
c_func
(paren
op_amp
id|x6spi-&gt;list_byaddr
comma
op_amp
id|xfrm6_tunnel_spi_byaddr
(braket
id|index
)braket
)paren
suffix:semicolon
id|X6SPI_CHECK_MAGIC
c_func
(paren
id|x6spi
)paren
suffix:semicolon
id|out
suffix:colon
id|X6TPRINTK3
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s() = %u&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|spi
)paren
suffix:semicolon
r_return
id|spi
suffix:semicolon
)brace
DECL|function|xfrm6_tunnel_alloc_spi
id|u32
id|xfrm6_tunnel_alloc_spi
c_func
(paren
id|xfrm_address_t
op_star
id|saddr
)paren
(brace
r_struct
id|xfrm6_tunnel_spi
op_star
id|x6spi
suffix:semicolon
id|u32
id|spi
suffix:semicolon
id|X6TPRINTK3
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s(saddr=%p)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|saddr
)paren
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|xfrm6_tunnel_spi_lock
)paren
suffix:semicolon
id|x6spi
op_assign
id|__xfrm6_tunnel_spi_lookup
c_func
(paren
id|saddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|x6spi
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|x6spi-&gt;refcnt
)paren
suffix:semicolon
id|spi
op_assign
id|x6spi-&gt;spi
suffix:semicolon
)brace
r_else
id|spi
op_assign
id|__xfrm6_tunnel_alloc_spi
c_func
(paren
id|saddr
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|xfrm6_tunnel_spi_lock
)paren
suffix:semicolon
id|X6TPRINTK3
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s() = %u&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|spi
)paren
suffix:semicolon
r_return
id|spi
suffix:semicolon
)brace
DECL|function|xfrm6_tunnel_free_spi
r_void
id|xfrm6_tunnel_free_spi
c_func
(paren
id|xfrm_address_t
op_star
id|saddr
)paren
(brace
r_struct
id|xfrm6_tunnel_spi
op_star
id|x6spi
suffix:semicolon
r_struct
id|hlist_node
op_star
id|pos
comma
op_star
id|n
suffix:semicolon
id|X6TPRINTK3
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s(saddr=%p)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|saddr
)paren
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|xfrm6_tunnel_spi_lock
)paren
suffix:semicolon
id|hlist_for_each_entry_safe
c_func
(paren
id|x6spi
comma
id|pos
comma
id|n
comma
op_amp
id|xfrm6_tunnel_spi_byaddr
(braket
id|xfrm6_tunnel_spi_hash_byaddr
c_func
(paren
id|saddr
)paren
)braket
comma
id|list_byaddr
)paren
(brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
op_amp
id|x6spi-&gt;addr
comma
id|saddr
comma
r_sizeof
(paren
id|x6spi-&gt;addr
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|X6TPRINTK3
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s(): x6spi object &quot;
l_string|&quot;for %04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x &quot;
l_string|&quot;found at %p&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|NIP6
c_func
(paren
op_star
(paren
r_struct
id|in6_addr
op_star
)paren
id|saddr
)paren
comma
id|x6spi
)paren
suffix:semicolon
id|X6SPI_CHECK_MAGIC
c_func
(paren
id|x6spi
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|x6spi-&gt;refcnt
)paren
)paren
(brace
id|hlist_del
c_func
(paren
op_amp
id|x6spi-&gt;list_byaddr
)paren
suffix:semicolon
id|hlist_del
c_func
(paren
op_amp
id|x6spi-&gt;list_byspi
)paren
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|xfrm6_tunnel_spi_kmem
comma
id|x6spi
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
id|write_unlock_bh
c_func
(paren
op_amp
id|xfrm6_tunnel_spi_lock
)paren
suffix:semicolon
)brace
DECL|function|xfrm6_tunnel_check_size
r_int
id|xfrm6_tunnel_check_size
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|mtu
comma
id|ret
op_assign
l_int|0
suffix:semicolon
r_struct
id|dst_entry
op_star
id|dst
op_assign
id|skb-&gt;dst
suffix:semicolon
id|mtu
op_assign
id|dst_pmtu
c_func
(paren
id|dst
)paren
op_minus
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mtu
OL
id|IPV6_MIN_MTU
)paren
id|mtu
op_assign
id|IPV6_MIN_MTU
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
OG
id|mtu
)paren
(brace
id|icmpv6_send
c_func
(paren
id|skb
comma
id|ICMPV6_PKT_TOOBIG
comma
l_int|0
comma
id|mtu
comma
id|skb-&gt;dev
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EMSGSIZE
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|xfrm6_tunnel_output
r_static
r_int
id|xfrm6_tunnel_output
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
op_assign
op_star
id|pskb
suffix:semicolon
r_struct
id|dst_entry
op_star
id|dst
op_assign
id|skb-&gt;dst
suffix:semicolon
r_struct
id|xfrm_state
op_star
id|x
op_assign
id|dst-&gt;xfrm
suffix:semicolon
r_struct
id|ipv6hdr
op_star
id|iph
comma
op_star
id|top_iph
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|xfrm6_tunnel_check_size
c_func
(paren
id|skb
)paren
)paren
op_ne
l_int|0
)paren
r_goto
id|error_nolock
suffix:semicolon
id|iph
op_assign
id|skb-&gt;nh.ipv6h
suffix:semicolon
id|top_iph
op_assign
(paren
r_struct
id|ipv6hdr
op_star
)paren
id|skb_push
c_func
(paren
id|skb
comma
id|x-&gt;props.header_len
)paren
suffix:semicolon
id|top_iph-&gt;version
op_assign
l_int|6
suffix:semicolon
id|top_iph-&gt;priority
op_assign
id|iph-&gt;priority
suffix:semicolon
id|top_iph-&gt;flow_lbl
(braket
l_int|0
)braket
op_assign
id|iph-&gt;flow_lbl
(braket
l_int|0
)braket
suffix:semicolon
id|top_iph-&gt;flow_lbl
(braket
l_int|1
)braket
op_assign
id|iph-&gt;flow_lbl
(braket
l_int|1
)braket
suffix:semicolon
id|top_iph-&gt;flow_lbl
(braket
l_int|2
)braket
op_assign
id|iph-&gt;flow_lbl
(braket
l_int|2
)braket
suffix:semicolon
id|top_iph-&gt;nexthdr
op_assign
id|IPPROTO_IPV6
suffix:semicolon
id|top_iph-&gt;payload_len
op_assign
id|htons
c_func
(paren
id|skb-&gt;len
op_minus
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
)paren
suffix:semicolon
id|top_iph-&gt;hop_limit
op_assign
id|iph-&gt;hop_limit
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|top_iph-&gt;saddr
comma
(paren
r_struct
id|in6_addr
op_star
)paren
op_amp
id|x-&gt;props.saddr
comma
r_sizeof
(paren
r_struct
id|in6_addr
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|top_iph-&gt;daddr
comma
(paren
r_struct
id|in6_addr
op_star
)paren
op_amp
id|x-&gt;id.daddr
comma
r_sizeof
(paren
r_struct
id|in6_addr
)paren
)paren
suffix:semicolon
id|skb-&gt;nh.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|skb-&gt;h.raw
op_assign
id|skb-&gt;nh.raw
op_plus
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
suffix:semicolon
id|x-&gt;curlft.bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|x-&gt;curlft.packets
op_increment
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|x-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb-&gt;dst
op_assign
id|dst_pop
c_func
(paren
id|dst
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EHOSTUNREACH
suffix:semicolon
r_goto
id|error_nolock
suffix:semicolon
)brace
r_return
id|NET_XMIT_BYPASS
suffix:semicolon
id|error_nolock
suffix:colon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|xfrm6_tunnel_input
r_static
r_int
id|xfrm6_tunnel_input
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
comma
r_struct
id|xfrm_decap_state
op_star
id|decap
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pskb_may_pull
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|skb-&gt;mac.raw
op_assign
id|skb-&gt;nh.raw
suffix:semicolon
id|skb-&gt;nh.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|dst_release
c_func
(paren
id|skb-&gt;dst
)paren
suffix:semicolon
id|skb-&gt;dst
op_assign
l_int|NULL
suffix:semicolon
id|skb-&gt;protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_IPV6
)paren
suffix:semicolon
id|skb-&gt;pkt_type
op_assign
id|PACKET_HOST
suffix:semicolon
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|xfrm6_tunnel_handler
r_static
r_struct
id|xfrm6_tunnel
op_star
id|xfrm6_tunnel_handler
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|xfrm6_tunnel_sem
)paren
suffix:semicolon
DECL|function|xfrm6_tunnel_register
r_int
id|xfrm6_tunnel_register
c_func
(paren
r_struct
id|xfrm6_tunnel
op_star
id|handler
)paren
(brace
r_int
id|ret
suffix:semicolon
id|down
c_func
(paren
op_amp
id|xfrm6_tunnel_sem
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|xfrm6_tunnel_handler
op_ne
l_int|NULL
)paren
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|xfrm6_tunnel_handler
op_assign
id|handler
suffix:semicolon
id|up
c_func
(paren
op_amp
id|xfrm6_tunnel_sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|xfrm6_tunnel_deregister
r_int
id|xfrm6_tunnel_deregister
c_func
(paren
r_struct
id|xfrm6_tunnel
op_star
id|handler
)paren
(brace
r_int
id|ret
suffix:semicolon
id|down
c_func
(paren
op_amp
id|xfrm6_tunnel_sem
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|xfrm6_tunnel_handler
op_ne
id|handler
)paren
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|xfrm6_tunnel_handler
op_assign
l_int|NULL
suffix:semicolon
id|up
c_func
(paren
op_amp
id|xfrm6_tunnel_sem
)paren
suffix:semicolon
id|synchronize_net
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|xfrm6_tunnel_rcv
r_static
r_int
id|xfrm6_tunnel_rcv
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
r_int
r_int
op_star
id|nhoffp
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
op_assign
op_star
id|pskb
suffix:semicolon
r_struct
id|xfrm6_tunnel
op_star
id|handler
op_assign
id|xfrm6_tunnel_handler
suffix:semicolon
r_struct
id|xfrm_state
op_star
id|x
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|ipv6hdr
op_star
id|iph
op_assign
id|skb-&gt;nh.ipv6h
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|u32
id|spi
suffix:semicolon
multiline_comment|/* device-like_ip6ip6_handler() */
r_if
c_cond
(paren
id|handler
)paren
(brace
id|err
op_assign
id|handler
op_member_access_from_pointer
id|handler
c_func
(paren
id|pskb
comma
id|nhoffp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
r_goto
id|out
suffix:semicolon
)brace
id|spi
op_assign
id|xfrm6_tunnel_spi_lookup
c_func
(paren
(paren
id|xfrm_address_t
op_star
)paren
op_amp
id|iph-&gt;saddr
)paren
suffix:semicolon
id|x
op_assign
id|xfrm_state_lookup
c_func
(paren
(paren
id|xfrm_address_t
op_star
)paren
op_amp
id|iph-&gt;daddr
comma
id|spi
comma
id|IPPROTO_IPV6
comma
id|AF_INET6
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|x
)paren
r_goto
id|drop
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|x-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|x-&gt;km.state
op_ne
id|XFRM_STATE_VALID
)paren
)paren
r_goto
id|drop_unlock
suffix:semicolon
id|err
op_assign
id|xfrm6_tunnel_input
c_func
(paren
id|x
comma
l_int|NULL
comma
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|drop_unlock
suffix:semicolon
id|x-&gt;curlft.bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|x-&gt;curlft.packets
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|x-&gt;lock
)paren
suffix:semicolon
id|xfrm_state_put
c_func
(paren
id|x
)paren
suffix:semicolon
id|out
suffix:colon
r_return
l_int|0
suffix:semicolon
id|drop_unlock
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|x-&gt;lock
)paren
suffix:semicolon
id|xfrm_state_put
c_func
(paren
id|x
)paren
suffix:semicolon
id|drop
suffix:colon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|xfrm6_tunnel_err
r_static
r_void
id|xfrm6_tunnel_err
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|inet6_skb_parm
op_star
id|opt
comma
r_int
id|type
comma
r_int
id|code
comma
r_int
id|offset
comma
id|__u32
id|info
)paren
(brace
r_struct
id|xfrm6_tunnel
op_star
id|handler
op_assign
id|xfrm6_tunnel_handler
suffix:semicolon
multiline_comment|/* call here first for device-like ip6ip6 err handling */
r_if
c_cond
(paren
id|handler
)paren
(brace
id|handler
op_member_access_from_pointer
id|err_handler
c_func
(paren
id|skb
comma
id|opt
comma
id|type
comma
id|code
comma
id|offset
comma
id|info
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* xfrm6_tunnel native err handling */
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|ICMPV6_DEST_UNREACH
suffix:colon
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
id|ICMPV6_NOROUTE
suffix:colon
r_case
id|ICMPV6_ADM_PROHIBITED
suffix:colon
r_case
id|ICMPV6_NOT_NEIGHBOUR
suffix:colon
r_case
id|ICMPV6_ADDR_UNREACH
suffix:colon
r_case
id|ICMPV6_PORT_UNREACH
suffix:colon
r_default
suffix:colon
id|X6TPRINTK3
c_func
(paren
id|KERN_DEBUG
l_string|&quot;xfrm6_tunnel: Destination Unreach.&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ICMPV6_PKT_TOOBIG
suffix:colon
id|X6TPRINTK3
c_func
(paren
id|KERN_DEBUG
l_string|&quot;xfrm6_tunnel: Packet Too Big.&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ICMPV6_TIME_EXCEED
suffix:colon
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
id|ICMPV6_EXC_HOPLIMIT
suffix:colon
id|X6TPRINTK3
c_func
(paren
id|KERN_DEBUG
l_string|&quot;xfrm6_tunnel: Too small Hoplimit.&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ICMPV6_EXC_FRAGTIME
suffix:colon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ICMPV6_PARAMPROB
suffix:colon
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
id|ICMPV6_HDR_FIELD
suffix:colon
r_break
suffix:semicolon
r_case
id|ICMPV6_UNK_NEXTHDR
suffix:colon
r_break
suffix:semicolon
r_case
id|ICMPV6_UNK_OPTION
suffix:colon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|function|xfrm6_tunnel_init_state
r_static
r_int
id|xfrm6_tunnel_init_state
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
comma
r_void
op_star
id|args
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|x-&gt;props.mode
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|x-&gt;props.header_len
op_assign
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xfrm6_tunnel_destroy
r_static
r_void
id|xfrm6_tunnel_destroy
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
)paren
(brace
id|xfrm6_tunnel_free_spi
c_func
(paren
(paren
id|xfrm_address_t
op_star
)paren
op_amp
id|x-&gt;props.saddr
)paren
suffix:semicolon
)brace
DECL|variable|xfrm6_tunnel_type
r_static
r_struct
id|xfrm_type
id|xfrm6_tunnel_type
op_assign
(brace
dot
id|description
op_assign
l_string|&quot;IP6IP6&quot;
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|proto
op_assign
id|IPPROTO_IPV6
comma
dot
id|init_state
op_assign
id|xfrm6_tunnel_init_state
comma
dot
id|destructor
op_assign
id|xfrm6_tunnel_destroy
comma
dot
id|input
op_assign
id|xfrm6_tunnel_input
comma
dot
id|output
op_assign
id|xfrm6_tunnel_output
comma
)brace
suffix:semicolon
DECL|variable|xfrm6_tunnel_protocol
r_static
r_struct
id|inet6_protocol
id|xfrm6_tunnel_protocol
op_assign
(brace
dot
id|handler
op_assign
id|xfrm6_tunnel_rcv
comma
dot
id|err_handler
op_assign
id|xfrm6_tunnel_err
comma
dot
id|flags
op_assign
id|INET6_PROTO_NOPOLICY
op_or
id|INET6_PROTO_FINAL
comma
)brace
suffix:semicolon
DECL|function|xfrm6_tunnel_init
r_void
id|__init
id|xfrm6_tunnel_init
c_func
(paren
r_void
)paren
(brace
id|X6TPRINTK3
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s()&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xfrm_register_type
c_func
(paren
op_amp
id|xfrm6_tunnel_type
comma
id|AF_INET6
)paren
OL
l_int|0
)paren
(brace
id|X6TPRINTK1
c_func
(paren
id|KERN_ERR
l_string|&quot;xfrm6_tunnel init: can&squot;t add xfrm type&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inet6_add_protocol
c_func
(paren
op_amp
id|xfrm6_tunnel_protocol
comma
id|IPPROTO_IPV6
)paren
OL
l_int|0
)paren
(brace
id|X6TPRINTK1
c_func
(paren
id|KERN_ERR
l_string|&quot;xfrm6_tunnel init(): can&squot;t add protocol&bslash;n&quot;
)paren
suffix:semicolon
id|xfrm_unregister_type
c_func
(paren
op_amp
id|xfrm6_tunnel_type
comma
id|AF_INET6
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|xfrm6_tunnel_spi_init
c_func
(paren
)paren
OL
l_int|0
)paren
(brace
id|X6TPRINTK1
c_func
(paren
id|KERN_ERR
l_string|&quot;xfrm6_tunnel init: failed to initialize spi&bslash;n&quot;
)paren
suffix:semicolon
id|inet6_del_protocol
c_func
(paren
op_amp
id|xfrm6_tunnel_protocol
comma
id|IPPROTO_IPV6
)paren
suffix:semicolon
id|xfrm_unregister_type
c_func
(paren
op_amp
id|xfrm6_tunnel_type
comma
id|AF_INET6
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
DECL|function|xfrm6_tunnel_fini
r_void
id|__exit
id|xfrm6_tunnel_fini
c_func
(paren
r_void
)paren
(brace
id|X6TPRINTK3
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s()&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|xfrm6_tunnel_spi_fini
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inet6_del_protocol
c_func
(paren
op_amp
id|xfrm6_tunnel_protocol
comma
id|IPPROTO_IPV6
)paren
OL
l_int|0
)paren
id|X6TPRINTK1
c_func
(paren
id|KERN_ERR
l_string|&quot;xfrm6_tunnel close: can&squot;t remove protocol&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xfrm_unregister_type
c_func
(paren
op_amp
id|xfrm6_tunnel_type
comma
id|AF_INET6
)paren
OL
l_int|0
)paren
id|X6TPRINTK1
c_func
(paren
id|KERN_ERR
l_string|&quot;xfrm6_tunnel close: can&squot;t remove xfrm type&bslash;n&quot;
)paren
suffix:semicolon
)brace
eof
