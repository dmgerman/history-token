multiline_comment|/* -*- linux-c -*- ------------------------------------------------------- *&n; *&n; *   Copyright 2003 H. Peter Anvin - All Rights Reserved&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation, Inc., 53 Temple Place Ste 330,&n; *   Bostom MA 02111-1307, USA; either version 2 of the License, or&n; *   (at your option) any later version; incorporated herein by reference.&n; *&n; * ----------------------------------------------------------------------- */
macro_line|#ifndef LINUX_RAID_RAID6_H
DECL|macro|LINUX_RAID_RAID6_H
mdefine_line|#define LINUX_RAID_RAID6_H
macro_line|#ifdef __KERNEL__
multiline_comment|/* Set to 1 to use kernel-wide empty_zero_page */
DECL|macro|RAID6_USE_EMPTY_ZERO_PAGE
mdefine_line|#define RAID6_USE_EMPTY_ZERO_PAGE 0
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/mempool.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/raid/md.h&gt;
macro_line|#include &lt;linux/raid/raid5.h&gt;
DECL|typedef|raid6_conf_t
r_typedef
id|raid5_conf_t
id|raid6_conf_t
suffix:semicolon
multiline_comment|/* Same configuration */
multiline_comment|/* Additional compute_parity mode -- updates the parity w/o LOCKING */
DECL|macro|UPDATE_PARITY
mdefine_line|#define UPDATE_PARITY&t;4
multiline_comment|/* We need a pre-zeroed page... if we don&squot;t want to use the kernel-provided&n;   one define it here */
macro_line|#if RAID6_USE_EMPTY_ZERO_PAGE
DECL|macro|raid6_empty_zero_page
macro_line|# define raid6_empty_zero_page empty_zero_page
macro_line|#else
r_extern
r_const
r_char
id|raid6_empty_zero_page
(braket
id|PAGE_SIZE
)braket
suffix:semicolon
macro_line|#endif
macro_line|#else /* ! __KERNEL__ */
multiline_comment|/* Used for testing in user space */
macro_line|#include &lt;stddef.h&gt;
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;inttypes.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;sys/mman.h&gt;
DECL|typedef|u8
r_typedef
r_uint8
id|u8
suffix:semicolon
DECL|typedef|u16
r_typedef
r_uint16
id|u16
suffix:semicolon
DECL|typedef|u32
r_typedef
r_uint32
id|u32
suffix:semicolon
DECL|typedef|u64
r_typedef
r_uint64
id|u64
suffix:semicolon
macro_line|#ifndef PAGE_SIZE
DECL|macro|PAGE_SIZE
macro_line|# define PAGE_SIZE 4096
macro_line|#endif
r_extern
r_const
r_char
id|raid6_empty_zero_page
(braket
id|PAGE_SIZE
)braket
suffix:semicolon
DECL|macro|__init
mdefine_line|#define __init
DECL|macro|__exit
mdefine_line|#define __exit
DECL|macro|preempt_enable
mdefine_line|#define preempt_enable()
DECL|macro|preempt_disable
mdefine_line|#define preempt_disable()
macro_line|#endif /* __KERNEL__ */
multiline_comment|/* Change this from BITS_PER_LONG if there is something better... */
macro_line|#if BITS_PER_LONG == 64
DECL|macro|NBYTES
macro_line|# define NBYTES(x) ((x) * 0x0101010101010101UL)
DECL|macro|NSIZE
macro_line|# define NSIZE  8
DECL|macro|NSHIFT
macro_line|# define NSHIFT 3
DECL|macro|NSTRING
macro_line|# define NSTRING &quot;64&quot;
DECL|typedef|unative_t
r_typedef
id|u64
id|unative_t
suffix:semicolon
macro_line|#else
DECL|macro|NBYTES
macro_line|# define NBYTES(x) ((x) * 0x01010101U)
DECL|macro|NSIZE
macro_line|# define NSIZE  4
DECL|macro|NSHIFT
macro_line|# define NSHIFT 2
DECL|macro|NSTRING
macro_line|# define NSTRING &quot;32&quot;
DECL|typedef|unative_t
r_typedef
id|u32
id|unative_t
suffix:semicolon
macro_line|#endif
multiline_comment|/* Routine choices */
DECL|struct|raid6_calls
r_struct
id|raid6_calls
(brace
DECL|member|gen_syndrome
r_void
(paren
op_star
id|gen_syndrome
)paren
(paren
r_int
comma
r_int
comma
r_void
op_star
op_star
)paren
suffix:semicolon
DECL|member|valid
r_int
(paren
op_star
id|valid
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Returns 1 if this routine set is usable */
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* Name of this routine set */
DECL|member|prefer
r_int
id|prefer
suffix:semicolon
multiline_comment|/* Has special performance attribute */
)brace
suffix:semicolon
multiline_comment|/* Selected algorithm */
r_extern
r_struct
id|raid6_calls
id|raid6_call
suffix:semicolon
multiline_comment|/* Algorithm list */
r_extern
r_const
r_struct
id|raid6_calls
op_star
r_const
id|raid6_algos
(braket
)braket
suffix:semicolon
r_int
id|raid6_select_algo
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Return values from chk_syndrome */
DECL|macro|RAID6_OK
mdefine_line|#define RAID6_OK&t;0
DECL|macro|RAID6_P_BAD
mdefine_line|#define RAID6_P_BAD&t;1
DECL|macro|RAID6_Q_BAD
mdefine_line|#define RAID6_Q_BAD&t;2
DECL|macro|RAID6_PQ_BAD
mdefine_line|#define RAID6_PQ_BAD&t;3
multiline_comment|/* Galois field tables */
r_extern
r_const
id|u8
id|raid6_gfmul
(braket
l_int|256
)braket
(braket
l_int|256
)braket
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|256
)paren
)paren
)paren
suffix:semicolon
r_extern
r_const
id|u8
id|raid6_gfexp
(braket
l_int|256
)braket
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|256
)paren
)paren
)paren
suffix:semicolon
r_extern
r_const
id|u8
id|raid6_gfinv
(braket
l_int|256
)braket
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|256
)paren
)paren
)paren
suffix:semicolon
r_extern
r_const
id|u8
id|raid6_gfexi
(braket
l_int|256
)braket
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|256
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Recovery routines */
r_void
id|raid6_2data_recov
c_func
(paren
r_int
id|disks
comma
r_int
id|bytes
comma
r_int
id|faila
comma
r_int
id|failb
comma
r_void
op_star
op_star
id|ptrs
)paren
suffix:semicolon
r_void
id|raid6_datap_recov
c_func
(paren
r_int
id|disks
comma
r_int
id|bytes
comma
r_int
id|faila
comma
r_void
op_star
op_star
id|ptrs
)paren
suffix:semicolon
r_void
id|raid6_dual_recov
c_func
(paren
r_int
id|disks
comma
r_int
id|bytes
comma
r_int
id|faila
comma
r_int
id|failb
comma
r_void
op_star
op_star
id|ptrs
)paren
suffix:semicolon
multiline_comment|/* Some definitions to allow code to be compiled for testing in userspace */
macro_line|#ifndef __KERNEL__
DECL|macro|jiffies
macro_line|# define jiffies&t;raid6_jiffies()
DECL|macro|printk
macro_line|# define printk &t;printf
DECL|macro|GFP_KERNEL
macro_line|# define GFP_KERNEL&t;0
DECL|macro|__get_free_pages
macro_line|# define __get_free_pages(x,y)&t;((unsigned long)mmap(NULL, PAGE_SIZE &lt;&lt; (y), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, 0, 0))
DECL|macro|free_pages
macro_line|# define free_pages(x,y)&t;munmap((void *)(x), (y)*PAGE_SIZE)
DECL|function|cpu_relax
r_static
r_inline
r_void
id|cpu_relax
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Nothing */
)brace
DECL|macro|HZ
macro_line|#undef  HZ
DECL|macro|HZ
mdefine_line|#define HZ 1000
DECL|function|raid6_jiffies
r_static
r_inline
r_uint32
id|raid6_jiffies
c_func
(paren
r_void
)paren
(brace
r_struct
id|timeval
id|tv
suffix:semicolon
id|gettimeofday
c_func
(paren
op_amp
id|tv
comma
l_int|NULL
)paren
suffix:semicolon
r_return
id|tv.tv_sec
op_star
l_int|1000
op_plus
id|tv.tv_usec
op_div
l_int|1000
suffix:semicolon
)brace
macro_line|#endif /* ! __KERNEL__ */
macro_line|#endif /* LINUX_RAID_RAID6_H */
eof
