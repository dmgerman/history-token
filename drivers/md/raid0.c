multiline_comment|/*&n;   raid0.c : Multiple Devices driver for Linux&n;             Copyright (C) 1994-96 Marc ZYNGIER&n;&t;     &lt;zyngier@ufr-info-p7.ibp.fr&gt; or&n;&t;     &lt;maz@gloups.fdn.fr&gt;&n;             Copyright (C) 1999, 2000 Ingo Molnar, Red Hat&n;&n;&n;   RAID-0 management functions.&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2, or (at your option)&n;   any later version.&n;   &n;   You should have received a copy of the GNU General Public License&n;   (for example /usr/src/linux/COPYING); if not, write to the Free&n;   Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  &n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/raid/raid0.h&gt;
DECL|macro|MAJOR_NR
mdefine_line|#define MAJOR_NR MD_MAJOR
DECL|macro|MD_DRIVER
mdefine_line|#define MD_DRIVER
DECL|macro|MD_PERSONALITY
mdefine_line|#define MD_PERSONALITY
DECL|function|create_strip_zones
r_static
r_int
id|create_strip_zones
(paren
id|mddev_t
op_star
id|mddev
)paren
(brace
r_int
id|i
comma
id|c
comma
id|j
comma
id|j1
comma
id|j2
suffix:semicolon
r_int
r_int
id|current_offset
comma
id|curr_zone_offset
suffix:semicolon
id|raid0_conf_t
op_star
id|conf
op_assign
id|mddev_to_conf
c_func
(paren
id|mddev
)paren
suffix:semicolon
id|mdk_rdev_t
op_star
id|smallest
comma
op_star
id|rdev1
comma
op_star
id|rdev2
comma
op_star
id|rdev
suffix:semicolon
multiline_comment|/*&n;&t; * The number of &squot;same size groups&squot;&n;&t; */
id|conf-&gt;nr_strip_zones
op_assign
l_int|0
suffix:semicolon
id|ITERATE_RDEV_ORDERED
c_func
(paren
id|mddev
comma
id|rdev1
comma
id|j1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;raid0: looking at %s&bslash;n&quot;
comma
id|partition_name
c_func
(paren
id|rdev1-&gt;dev
)paren
)paren
suffix:semicolon
id|c
op_assign
l_int|0
suffix:semicolon
id|ITERATE_RDEV_ORDERED
c_func
(paren
id|mddev
comma
id|rdev2
comma
id|j2
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;raid0:   comparing %s(%ld) with %s(%ld)&bslash;n&quot;
comma
id|partition_name
c_func
(paren
id|rdev1-&gt;dev
)paren
comma
id|rdev1-&gt;size
comma
id|partition_name
c_func
(paren
id|rdev2-&gt;dev
)paren
comma
id|rdev2-&gt;size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rdev2
op_eq
id|rdev1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;raid0:   END&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rdev2-&gt;size
op_eq
id|rdev1-&gt;size
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Not unique, dont count it as a new&n;&t;&t;&t;&t; * group&n;&t;&t;&t;&t; */
id|printk
c_func
(paren
l_string|&quot;raid0:   EQUAL&bslash;n&quot;
)paren
suffix:semicolon
id|c
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;raid0:   NOT EQUAL&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;raid0:   ==&gt; UNIQUE&bslash;n&quot;
)paren
suffix:semicolon
id|conf-&gt;nr_strip_zones
op_increment
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;raid0: %d zones&bslash;n&quot;
comma
id|conf-&gt;nr_strip_zones
)paren
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;raid0: FINAL %d zones&bslash;n&quot;
comma
id|conf-&gt;nr_strip_zones
)paren
suffix:semicolon
id|conf-&gt;strip_zone
op_assign
id|vmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|strip_zone
)paren
op_star
id|conf-&gt;nr_strip_zones
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|conf-&gt;strip_zone
)paren
r_return
l_int|1
suffix:semicolon
id|conf-&gt;smallest
op_assign
l_int|NULL
suffix:semicolon
id|current_offset
op_assign
l_int|0
suffix:semicolon
id|curr_zone_offset
op_assign
l_int|0
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
id|conf-&gt;nr_strip_zones
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|strip_zone
op_star
id|zone
op_assign
id|conf-&gt;strip_zone
op_plus
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;raid0: zone %d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|zone-&gt;dev_offset
op_assign
id|current_offset
suffix:semicolon
id|smallest
op_assign
l_int|NULL
suffix:semicolon
id|c
op_assign
l_int|0
suffix:semicolon
id|ITERATE_RDEV_ORDERED
c_func
(paren
id|mddev
comma
id|rdev
comma
id|j
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;raid0: checking %s ...&quot;
comma
id|partition_name
c_func
(paren
id|rdev-&gt;dev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rdev-&gt;size
OG
id|current_offset
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; contained as device %d&bslash;n&quot;
comma
id|c
)paren
suffix:semicolon
id|zone-&gt;dev
(braket
id|c
)braket
op_assign
id|rdev
suffix:semicolon
id|c
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|smallest
op_logical_or
(paren
id|rdev-&gt;size
OL
id|smallest-&gt;size
)paren
)paren
(brace
id|smallest
op_assign
id|rdev
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  (%ld) is smallest!.&bslash;n&quot;
comma
id|rdev-&gt;size
)paren
suffix:semicolon
)brace
)brace
r_else
id|printk
c_func
(paren
l_string|&quot; nope.&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|zone-&gt;nb_dev
op_assign
id|c
suffix:semicolon
id|zone-&gt;size
op_assign
(paren
id|smallest-&gt;size
op_minus
id|current_offset
)paren
op_star
id|c
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;raid0: zone-&gt;nb_dev: %d, size: %ld&bslash;n&quot;
comma
id|zone-&gt;nb_dev
comma
id|zone-&gt;size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|conf-&gt;smallest
op_logical_or
(paren
id|zone-&gt;size
OL
id|conf-&gt;smallest-&gt;size
)paren
)paren
id|conf-&gt;smallest
op_assign
id|zone
suffix:semicolon
id|zone-&gt;zone_offset
op_assign
id|curr_zone_offset
suffix:semicolon
id|curr_zone_offset
op_add_assign
id|zone-&gt;size
suffix:semicolon
id|current_offset
op_assign
id|smallest-&gt;size
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;raid0: current zone offset: %ld&bslash;n&quot;
comma
id|current_offset
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;raid0: done.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|raid0_run
r_static
r_int
id|raid0_run
(paren
id|mddev_t
op_star
id|mddev
)paren
(brace
r_int
r_int
id|cur
op_assign
l_int|0
comma
id|i
op_assign
l_int|0
comma
id|size
comma
id|zone0_size
comma
id|nb_zone
suffix:semicolon
id|raid0_conf_t
op_star
id|conf
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|conf
op_assign
id|vmalloc
c_func
(paren
r_sizeof
(paren
id|raid0_conf_t
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|conf
)paren
r_goto
id|out
suffix:semicolon
id|mddev
op_member_access_from_pointer
r_private
op_assign
(paren
r_void
op_star
)paren
id|conf
suffix:semicolon
r_if
c_cond
(paren
id|md_check_ordering
c_func
(paren
id|mddev
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;raid0: disks are not ordered, aborting!&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_free_conf
suffix:semicolon
)brace
r_if
c_cond
(paren
id|create_strip_zones
(paren
id|mddev
)paren
)paren
r_goto
id|out_free_conf
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;raid0 : md_size is %d blocks.&bslash;n&quot;
comma
id|md_size
(braket
id|mdidx
c_func
(paren
id|mddev
)paren
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;raid0 : conf-&gt;smallest-&gt;size is %ld blocks.&bslash;n&quot;
comma
id|conf-&gt;smallest-&gt;size
)paren
suffix:semicolon
id|nb_zone
op_assign
id|md_size
(braket
id|mdidx
c_func
(paren
id|mddev
)paren
)braket
op_div
id|conf-&gt;smallest-&gt;size
op_plus
(paren
id|md_size
(braket
id|mdidx
c_func
(paren
id|mddev
)paren
)braket
op_mod
id|conf-&gt;smallest-&gt;size
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;raid0 : nb_zone is %ld.&bslash;n&quot;
comma
id|nb_zone
)paren
suffix:semicolon
id|conf-&gt;nr_zones
op_assign
id|nb_zone
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;raid0 : Allocating %ld bytes for hash.&bslash;n&quot;
comma
id|nb_zone
op_star
r_sizeof
(paren
r_struct
id|raid0_hash
)paren
)paren
suffix:semicolon
id|conf-&gt;hash_table
op_assign
id|vmalloc
(paren
r_sizeof
(paren
r_struct
id|raid0_hash
)paren
op_star
id|nb_zone
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|conf-&gt;hash_table
)paren
r_goto
id|out_free_zone_conf
suffix:semicolon
id|size
op_assign
id|conf-&gt;strip_zone
(braket
id|cur
)braket
dot
id|size
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|cur
OL
id|conf-&gt;nr_strip_zones
)paren
(brace
id|conf-&gt;hash_table
(braket
id|i
)braket
dot
id|zone0
op_assign
id|conf-&gt;strip_zone
op_plus
id|cur
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If we completely fill the slot&n;&t;&t; */
r_if
c_cond
(paren
id|size
op_ge
id|conf-&gt;smallest-&gt;size
)paren
(brace
id|conf-&gt;hash_table
(braket
id|i
op_increment
)braket
dot
id|zone1
op_assign
l_int|NULL
suffix:semicolon
id|size
op_sub_assign
id|conf-&gt;smallest-&gt;size
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
(brace
r_if
c_cond
(paren
op_increment
id|cur
op_eq
id|conf-&gt;nr_strip_zones
)paren
r_continue
suffix:semicolon
id|size
op_assign
id|conf-&gt;strip_zone
(braket
id|cur
)braket
dot
id|size
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_increment
id|cur
op_eq
id|conf-&gt;nr_strip_zones
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Last dev, set unit1 as NULL&n;&t;&t;&t; */
id|conf-&gt;hash_table
(braket
id|i
)braket
dot
id|zone1
op_assign
l_int|NULL
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Here we use a 2nd dev to fill the slot&n;&t;&t; */
id|zone0_size
op_assign
id|size
suffix:semicolon
id|size
op_assign
id|conf-&gt;strip_zone
(braket
id|cur
)braket
dot
id|size
suffix:semicolon
id|conf-&gt;hash_table
(braket
id|i
op_increment
)braket
dot
id|zone1
op_assign
id|conf-&gt;strip_zone
op_plus
id|cur
suffix:semicolon
id|size
op_sub_assign
(paren
id|conf-&gt;smallest-&gt;size
op_minus
id|zone0_size
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|out_free_zone_conf
suffix:colon
id|vfree
c_func
(paren
id|conf-&gt;strip_zone
)paren
suffix:semicolon
id|conf-&gt;strip_zone
op_assign
l_int|NULL
suffix:semicolon
id|out_free_conf
suffix:colon
id|vfree
c_func
(paren
id|conf
)paren
suffix:semicolon
id|mddev
op_member_access_from_pointer
r_private
op_assign
l_int|NULL
suffix:semicolon
id|out
suffix:colon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|raid0_stop
r_static
r_int
id|raid0_stop
(paren
id|mddev_t
op_star
id|mddev
)paren
(brace
id|raid0_conf_t
op_star
id|conf
op_assign
id|mddev_to_conf
c_func
(paren
id|mddev
)paren
suffix:semicolon
id|vfree
(paren
id|conf-&gt;hash_table
)paren
suffix:semicolon
id|conf-&gt;hash_table
op_assign
l_int|NULL
suffix:semicolon
id|vfree
(paren
id|conf-&gt;strip_zone
)paren
suffix:semicolon
id|conf-&gt;strip_zone
op_assign
l_int|NULL
suffix:semicolon
id|vfree
(paren
id|conf
)paren
suffix:semicolon
id|mddev
op_member_access_from_pointer
r_private
op_assign
l_int|NULL
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * FIXME - We assume some things here :&n; * - requested buffers NEVER bigger than chunk size,&n; * - requested buffers NEVER cross stripes limits.&n; * Of course, those facts may not be valid anymore (and surely won&squot;t...)&n; * Hey guys, there&squot;s some work out there ;-)&n; */
DECL|function|raid0_make_request
r_static
r_int
id|raid0_make_request
(paren
id|mddev_t
op_star
id|mddev
comma
r_int
id|rw
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_int
r_int
id|sect_in_chunk
comma
id|chunksize_bits
comma
id|chunk_size
suffix:semicolon
id|raid0_conf_t
op_star
id|conf
op_assign
id|mddev_to_conf
c_func
(paren
id|mddev
)paren
suffix:semicolon
r_struct
id|raid0_hash
op_star
id|hash
suffix:semicolon
r_struct
id|strip_zone
op_star
id|zone
suffix:semicolon
id|mdk_rdev_t
op_star
id|tmp_dev
suffix:semicolon
r_int
r_int
id|chunk
comma
id|block
comma
id|rsect
suffix:semicolon
id|chunk_size
op_assign
id|mddev-&gt;param.chunk_size
op_rshift
l_int|10
suffix:semicolon
id|chunksize_bits
op_assign
id|ffz
c_func
(paren
op_complement
id|chunk_size
)paren
suffix:semicolon
id|block
op_assign
id|bh-&gt;b_rsector
op_rshift
l_int|1
suffix:semicolon
id|hash
op_assign
id|conf-&gt;hash_table
op_plus
id|block
op_div
id|conf-&gt;smallest-&gt;size
suffix:semicolon
multiline_comment|/* Sanity check */
r_if
c_cond
(paren
id|chunk_size
OL
(paren
id|block
op_mod
id|chunk_size
)paren
op_plus
(paren
id|bh-&gt;b_size
op_rshift
l_int|10
)paren
)paren
r_goto
id|bad_map
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hash
)paren
r_goto
id|bad_hash
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hash-&gt;zone0
)paren
r_goto
id|bad_zone0
suffix:semicolon
r_if
c_cond
(paren
id|block
op_ge
(paren
id|hash-&gt;zone0-&gt;size
op_plus
id|hash-&gt;zone0-&gt;zone_offset
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|hash-&gt;zone1
)paren
r_goto
id|bad_zone1
suffix:semicolon
id|zone
op_assign
id|hash-&gt;zone1
suffix:semicolon
)brace
r_else
id|zone
op_assign
id|hash-&gt;zone0
suffix:semicolon
id|sect_in_chunk
op_assign
id|bh-&gt;b_rsector
op_amp
(paren
(paren
id|chunk_size
op_lshift
l_int|1
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|chunk
op_assign
(paren
id|block
op_minus
id|zone-&gt;zone_offset
)paren
op_div
(paren
id|zone-&gt;nb_dev
op_lshift
id|chunksize_bits
)paren
suffix:semicolon
id|tmp_dev
op_assign
id|zone-&gt;dev
(braket
(paren
id|block
op_rshift
id|chunksize_bits
)paren
op_mod
id|zone-&gt;nb_dev
)braket
suffix:semicolon
id|rsect
op_assign
(paren
(paren
(paren
id|chunk
op_lshift
id|chunksize_bits
)paren
op_plus
id|zone-&gt;dev_offset
)paren
op_lshift
l_int|1
)paren
op_plus
id|sect_in_chunk
suffix:semicolon
multiline_comment|/*&n;&t; * The new BH_Lock semantics in ll_rw_blk.c guarantee that this&n;&t; * is the only IO operation happening on this bh.&n;&t; */
id|bh-&gt;b_rdev
op_assign
id|tmp_dev-&gt;dev
suffix:semicolon
id|bh-&gt;b_rsector
op_assign
id|rsect
suffix:semicolon
multiline_comment|/*&n;&t; * Let the main block layer submit the IO and resolve recursion:&n;&t; */
r_return
l_int|1
suffix:semicolon
id|bad_map
suffix:colon
id|printk
(paren
l_string|&quot;raid0_make_request bug: can&squot;t convert block across chunks or bigger than %dk %ld %d&bslash;n&quot;
comma
id|chunk_size
comma
id|bh-&gt;b_rsector
comma
id|bh-&gt;b_size
op_rshift
l_int|10
)paren
suffix:semicolon
r_goto
id|outerr
suffix:semicolon
id|bad_hash
suffix:colon
id|printk
c_func
(paren
l_string|&quot;raid0_make_request bug: hash==NULL for block %ld&bslash;n&quot;
comma
id|block
)paren
suffix:semicolon
r_goto
id|outerr
suffix:semicolon
id|bad_zone0
suffix:colon
id|printk
(paren
l_string|&quot;raid0_make_request bug: hash-&gt;zone0==NULL for block %ld&bslash;n&quot;
comma
id|block
)paren
suffix:semicolon
r_goto
id|outerr
suffix:semicolon
id|bad_zone1
suffix:colon
id|printk
(paren
l_string|&quot;raid0_make_request bug: hash-&gt;zone1==NULL for block %ld&bslash;n&quot;
comma
id|block
)paren
suffix:semicolon
id|outerr
suffix:colon
id|buffer_IO_error
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|raid0_status
r_static
r_int
id|raid0_status
(paren
r_char
op_star
id|page
comma
id|mddev_t
op_star
id|mddev
)paren
(brace
r_int
id|sz
op_assign
l_int|0
suffix:semicolon
DECL|macro|MD_DEBUG
macro_line|#undef MD_DEBUG
macro_line|#ifdef MD_DEBUG
r_int
id|j
comma
id|k
suffix:semicolon
id|raid0_conf_t
op_star
id|conf
op_assign
id|mddev_to_conf
c_func
(paren
id|mddev
)paren
suffix:semicolon
id|sz
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|sz
comma
l_string|&quot;      &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|conf-&gt;nr_zones
suffix:semicolon
id|j
op_increment
)paren
(brace
id|sz
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|sz
comma
l_string|&quot;[z%d&quot;
comma
id|conf-&gt;hash_table
(braket
id|j
)braket
dot
id|zone0
op_minus
id|conf-&gt;strip_zone
)paren
suffix:semicolon
r_if
c_cond
(paren
id|conf-&gt;hash_table
(braket
id|j
)braket
dot
id|zone1
)paren
id|sz
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|sz
comma
l_string|&quot;/z%d] &quot;
comma
id|conf-&gt;hash_table
(braket
id|j
)braket
dot
id|zone1
op_minus
id|conf-&gt;strip_zone
)paren
suffix:semicolon
r_else
id|sz
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|sz
comma
l_string|&quot;] &quot;
)paren
suffix:semicolon
)brace
id|sz
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|sz
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|conf-&gt;nr_strip_zones
suffix:semicolon
id|j
op_increment
)paren
(brace
id|sz
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|sz
comma
l_string|&quot;      z%d=[&quot;
comma
id|j
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|conf-&gt;strip_zone
(braket
id|j
)braket
dot
id|nb_dev
suffix:semicolon
id|k
op_increment
)paren
id|sz
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|sz
comma
l_string|&quot;%s/&quot;
comma
id|partition_name
c_func
(paren
id|conf-&gt;strip_zone
(braket
id|j
)braket
dot
id|dev
(braket
id|k
)braket
op_member_access_from_pointer
id|dev
)paren
)paren
suffix:semicolon
id|sz
op_decrement
suffix:semicolon
id|sz
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|sz
comma
l_string|&quot;] zo=%d do=%d s=%d&bslash;n&quot;
comma
id|conf-&gt;strip_zone
(braket
id|j
)braket
dot
id|zone_offset
comma
id|conf-&gt;strip_zone
(braket
id|j
)braket
dot
id|dev_offset
comma
id|conf-&gt;strip_zone
(braket
id|j
)braket
dot
id|size
)paren
suffix:semicolon
)brace
macro_line|#endif
id|sz
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|sz
comma
l_string|&quot; %dk chunks&quot;
comma
id|mddev-&gt;param.chunk_size
op_div
l_int|1024
)paren
suffix:semicolon
r_return
id|sz
suffix:semicolon
)brace
DECL|variable|raid0_personality
r_static
id|mdk_personality_t
id|raid0_personality
op_assign
(brace
id|name
suffix:colon
l_string|&quot;raid0&quot;
comma
id|make_request
suffix:colon
id|raid0_make_request
comma
id|run
suffix:colon
id|raid0_run
comma
id|stop
suffix:colon
id|raid0_stop
comma
id|status
suffix:colon
id|raid0_status
comma
)brace
suffix:semicolon
DECL|function|raid0_init
r_static
r_int
id|md__init
id|raid0_init
(paren
r_void
)paren
(brace
r_return
id|register_md_personality
(paren
id|RAID0
comma
op_amp
id|raid0_personality
)paren
suffix:semicolon
)brace
DECL|function|raid0_exit
r_static
r_void
id|raid0_exit
(paren
r_void
)paren
(brace
id|unregister_md_personality
(paren
id|RAID0
)paren
suffix:semicolon
)brace
DECL|variable|raid0_init
id|module_init
c_func
(paren
id|raid0_init
)paren
suffix:semicolon
DECL|variable|raid0_exit
id|module_exit
c_func
(paren
id|raid0_exit
)paren
suffix:semicolon
eof
