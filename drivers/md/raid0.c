multiline_comment|/*&n;   raid0.c : Multiple Devices driver for Linux&n;             Copyright (C) 1994-96 Marc ZYNGIER&n;&t;     &lt;zyngier@ufr-info-p7.ibp.fr&gt; or&n;&t;     &lt;maz@gloups.fdn.fr&gt;&n;             Copyright (C) 1999, 2000 Ingo Molnar, Red Hat&n;&n;&n;   RAID-0 management functions.&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2, or (at your option)&n;   any later version.&n;   &n;   You should have received a copy of the GNU General Public License&n;   (for example /usr/src/linux/COPYING); if not, write to the Free&n;   Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  &n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/raid/raid0.h&gt;
DECL|macro|MAJOR_NR
mdefine_line|#define MAJOR_NR MD_MAJOR
DECL|macro|MD_DRIVER
mdefine_line|#define MD_DRIVER
DECL|macro|MD_PERSONALITY
mdefine_line|#define MD_PERSONALITY
DECL|function|raid0_unplug
r_static
r_void
id|raid0_unplug
c_func
(paren
id|request_queue_t
op_star
id|q
)paren
(brace
id|mddev_t
op_star
id|mddev
op_assign
id|q-&gt;queuedata
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
op_star
id|devlist
op_assign
id|conf-&gt;strip_zone
(braket
l_int|0
)braket
dot
id|dev
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
id|mddev-&gt;raid_disks
suffix:semicolon
id|i
op_increment
)paren
(brace
id|request_queue_t
op_star
id|r_queue
op_assign
id|bdev_get_queue
c_func
(paren
id|devlist
(braket
id|i
)braket
op_member_access_from_pointer
id|bdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r_queue-&gt;unplug_fn
)paren
id|r_queue
op_member_access_from_pointer
id|unplug_fn
c_func
(paren
id|r_queue
)paren
suffix:semicolon
)brace
)brace
DECL|function|raid0_issue_flush
r_static
r_int
id|raid0_issue_flush
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_struct
id|gendisk
op_star
id|disk
comma
id|sector_t
op_star
id|error_sector
)paren
(brace
id|mddev_t
op_star
id|mddev
op_assign
id|q-&gt;queuedata
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
op_star
id|devlist
op_assign
id|conf-&gt;strip_zone
(braket
l_int|0
)braket
dot
id|dev
suffix:semicolon
r_int
id|i
comma
id|ret
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
id|mddev-&gt;raid_disks
op_logical_and
id|ret
op_eq
l_int|0
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|block_device
op_star
id|bdev
op_assign
id|devlist
(braket
id|i
)braket
op_member_access_from_pointer
id|bdev
suffix:semicolon
id|request_queue_t
op_star
id|r_queue
op_assign
id|bdev_get_queue
c_func
(paren
id|bdev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|r_queue-&gt;issue_flush_fn
)paren
id|ret
op_assign
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_else
id|ret
op_assign
id|r_queue
op_member_access_from_pointer
id|issue_flush_fn
c_func
(paren
id|r_queue
comma
id|bdev-&gt;bd_disk
comma
id|error_sector
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
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
suffix:semicolon
id|sector_t
id|current_offset
comma
id|curr_zone_offset
suffix:semicolon
id|sector_t
id|min_spacing
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
r_struct
id|list_head
op_star
id|tmp1
comma
op_star
id|tmp2
suffix:semicolon
r_struct
id|strip_zone
op_star
id|zone
suffix:semicolon
r_int
id|cnt
suffix:semicolon
r_char
id|b
(braket
id|BDEVNAME_SIZE
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * The number of &squot;same size groups&squot;&n;&t; */
id|conf-&gt;nr_strip_zones
op_assign
l_int|0
suffix:semicolon
id|ITERATE_RDEV
c_func
(paren
id|mddev
comma
id|rdev1
comma
id|tmp1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;raid0: looking at %s&bslash;n&quot;
comma
id|bdevname
c_func
(paren
id|rdev1-&gt;bdev
comma
id|b
)paren
)paren
suffix:semicolon
id|c
op_assign
l_int|0
suffix:semicolon
id|ITERATE_RDEV
c_func
(paren
id|mddev
comma
id|rdev2
comma
id|tmp2
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;raid0:   comparing %s(%llu)&quot;
comma
id|bdevname
c_func
(paren
id|rdev1-&gt;bdev
comma
id|b
)paren
comma
(paren
r_int
r_int
r_int
)paren
id|rdev1-&gt;size
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; with %s(%llu)&bslash;n&quot;
comma
id|bdevname
c_func
(paren
id|rdev2-&gt;bdev
comma
id|b
)paren
comma
(paren
r_int
r_int
r_int
)paren
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
multiline_comment|/*&n;&t;&t;&t;&t; * Not unique, don&squot;t count it as a new&n;&t;&t;&t;&t; * group&n;&t;&t;&t;&t; */
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
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|strip_zone
)paren
op_star
id|conf-&gt;nr_strip_zones
comma
id|GFP_KERNEL
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
id|conf-&gt;devlist
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|mdk_rdev_t
op_star
)paren
op_star
id|conf-&gt;nr_strip_zones
op_star
id|mddev-&gt;raid_disks
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|conf-&gt;devlist
)paren
r_return
l_int|1
suffix:semicolon
id|memset
c_func
(paren
id|conf-&gt;strip_zone
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|strip_zone
)paren
op_star
id|conf-&gt;nr_strip_zones
)paren
suffix:semicolon
id|memset
c_func
(paren
id|conf-&gt;devlist
comma
l_int|0
comma
r_sizeof
(paren
id|mdk_rdev_t
op_star
)paren
op_star
id|conf-&gt;nr_strip_zones
op_star
id|mddev-&gt;raid_disks
)paren
suffix:semicolon
multiline_comment|/* The first zone must contain all devices, so here we check that&n;&t; * there is a proper alignment of slots to devices and find them all&n;&t; */
id|zone
op_assign
op_amp
id|conf-&gt;strip_zone
(braket
l_int|0
)braket
suffix:semicolon
id|cnt
op_assign
l_int|0
suffix:semicolon
id|smallest
op_assign
l_int|NULL
suffix:semicolon
id|zone-&gt;dev
op_assign
id|conf-&gt;devlist
suffix:semicolon
id|ITERATE_RDEV
c_func
(paren
id|mddev
comma
id|rdev1
comma
id|tmp1
)paren
(brace
r_int
id|j
op_assign
id|rdev1-&gt;raid_disk
suffix:semicolon
r_if
c_cond
(paren
id|j
OL
l_int|0
op_logical_or
id|j
op_ge
id|mddev-&gt;raid_disks
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;raid0: bad disk number %d - aborting!&bslash;n&quot;
comma
id|j
)paren
suffix:semicolon
r_goto
m_abort
suffix:semicolon
)brace
r_if
c_cond
(paren
id|zone-&gt;dev
(braket
id|j
)braket
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;raid0: multiple devices for %d - aborting!&bslash;n&quot;
comma
id|j
)paren
suffix:semicolon
r_goto
m_abort
suffix:semicolon
)brace
id|zone-&gt;dev
(braket
id|j
)braket
op_assign
id|rdev1
suffix:semicolon
id|blk_queue_stack_limits
c_func
(paren
id|mddev-&gt;queue
comma
id|rdev1-&gt;bdev-&gt;bd_disk-&gt;queue
)paren
suffix:semicolon
multiline_comment|/* as we don&squot;t honour merge_bvec_fn, we must never risk&n;&t;&t; * violating it, so limit -&gt;max_sector to one PAGE, as&n;&t;&t; * a one page request is never in violation.&n;&t;&t; */
r_if
c_cond
(paren
id|rdev1-&gt;bdev-&gt;bd_disk-&gt;queue-&gt;merge_bvec_fn
op_logical_and
id|mddev-&gt;queue-&gt;max_sectors
OG
(paren
id|PAGE_SIZE
op_rshift
l_int|9
)paren
)paren
id|blk_queue_max_sectors
c_func
(paren
id|mddev-&gt;queue
comma
id|PAGE_SIZE
op_rshift
l_int|9
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|smallest
op_logical_or
(paren
id|rdev1-&gt;size
OL
id|smallest-&gt;size
)paren
)paren
id|smallest
op_assign
id|rdev1
suffix:semicolon
id|cnt
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cnt
op_ne
id|mddev-&gt;raid_disks
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;raid0: too few disks (%d of %d) - aborting!&bslash;n&quot;
comma
id|cnt
comma
id|mddev-&gt;raid_disks
)paren
suffix:semicolon
r_goto
m_abort
suffix:semicolon
)brace
id|zone-&gt;nb_dev
op_assign
id|cnt
suffix:semicolon
id|zone-&gt;size
op_assign
id|smallest-&gt;size
op_star
id|cnt
suffix:semicolon
id|zone-&gt;zone_offset
op_assign
l_int|0
suffix:semicolon
id|current_offset
op_assign
id|smallest-&gt;size
suffix:semicolon
id|curr_zone_offset
op_assign
id|zone-&gt;size
suffix:semicolon
multiline_comment|/* now do the other zones */
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|conf-&gt;nr_strip_zones
suffix:semicolon
id|i
op_increment
)paren
(brace
id|zone
op_assign
id|conf-&gt;strip_zone
op_plus
id|i
suffix:semicolon
id|zone-&gt;dev
op_assign
id|conf-&gt;strip_zone
(braket
id|i
op_minus
l_int|1
)braket
dot
id|dev
op_plus
id|mddev-&gt;raid_disks
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
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|cnt
suffix:semicolon
id|j
op_increment
)paren
(brace
r_char
id|b
(braket
id|BDEVNAME_SIZE
)braket
suffix:semicolon
id|rdev
op_assign
id|conf-&gt;strip_zone
(braket
l_int|0
)braket
dot
id|dev
(braket
id|j
)braket
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;raid0: checking %s ...&quot;
comma
id|bdevname
c_func
(paren
id|rdev-&gt;bdev
comma
id|b
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
l_string|&quot;  (%llu) is smallest!.&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
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
l_string|&quot;raid0: zone-&gt;nb_dev: %d, size: %llu&bslash;n&quot;
comma
id|zone-&gt;nb_dev
comma
(paren
r_int
r_int
r_int
)paren
id|zone-&gt;size
)paren
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
l_string|&quot;raid0: current zone offset: %llu&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|current_offset
)paren
suffix:semicolon
)brace
multiline_comment|/* Now find appropriate hash spacing.&n;&t; * We want a number which causes most hash entries to cover&n;&t; * at most two strips, but the hash table must be at most&n;&t; * 1 PAGE.  We choose the smallest strip, or contiguous collection&n;&t; * of strips, that has big enough size.  We never consider the last&n;&t; * strip though as it&squot;s size has no bearing on the efficacy of the hash&n;&t; * table.&n;&t; */
id|conf-&gt;hash_spacing
op_assign
id|curr_zone_offset
suffix:semicolon
id|min_spacing
op_assign
id|curr_zone_offset
suffix:semicolon
id|sector_div
c_func
(paren
id|min_spacing
comma
id|PAGE_SIZE
op_div
r_sizeof
(paren
r_struct
id|strip_zone
op_star
)paren
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
id|conf-&gt;nr_strip_zones
op_minus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
(brace
id|sector_t
id|sz
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
id|i
suffix:semicolon
id|j
OL
id|conf-&gt;nr_strip_zones
op_minus
l_int|1
op_logical_and
id|sz
OL
id|min_spacing
suffix:semicolon
id|j
op_increment
)paren
id|sz
op_add_assign
id|conf-&gt;strip_zone
(braket
id|j
)braket
dot
id|size
suffix:semicolon
r_if
c_cond
(paren
id|sz
op_ge
id|min_spacing
op_logical_and
id|sz
OL
id|conf-&gt;hash_spacing
)paren
id|conf-&gt;hash_spacing
op_assign
id|sz
suffix:semicolon
)brace
id|mddev-&gt;queue-&gt;unplug_fn
op_assign
id|raid0_unplug
suffix:semicolon
id|mddev-&gt;queue-&gt;issue_flush_fn
op_assign
id|raid0_issue_flush
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;raid0: done.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
m_abort
suffix:colon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;raid0_mergeable_bvec -- tell bio layer if a two requests can be merged&n; *&t;@q: request queue&n; *&t;@bio: the buffer head that&squot;s been built up so far&n; *&t;@biovec: the request that could be merged to it.&n; *&n; *&t;Return amount of bytes we can accept at this offset&n; */
DECL|function|raid0_mergeable_bvec
r_static
r_int
id|raid0_mergeable_bvec
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_struct
id|bio
op_star
id|bio
comma
r_struct
id|bio_vec
op_star
id|biovec
)paren
(brace
id|mddev_t
op_star
id|mddev
op_assign
id|q-&gt;queuedata
suffix:semicolon
id|sector_t
id|sector
op_assign
id|bio-&gt;bi_sector
op_plus
id|get_start_sect
c_func
(paren
id|bio-&gt;bi_bdev
)paren
suffix:semicolon
r_int
id|max
suffix:semicolon
r_int
r_int
id|chunk_sectors
op_assign
id|mddev-&gt;chunk_size
op_rshift
l_int|9
suffix:semicolon
r_int
r_int
id|bio_sectors
op_assign
id|bio-&gt;bi_size
op_rshift
l_int|9
suffix:semicolon
id|max
op_assign
(paren
id|chunk_sectors
op_minus
(paren
(paren
id|sector
op_amp
(paren
id|chunk_sectors
op_minus
l_int|1
)paren
)paren
op_plus
id|bio_sectors
)paren
)paren
op_lshift
l_int|9
suffix:semicolon
r_if
c_cond
(paren
id|max
OL
l_int|0
)paren
id|max
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* bio_add cannot handle a negative return */
r_if
c_cond
(paren
id|max
op_le
id|biovec-&gt;bv_len
op_logical_and
id|bio_sectors
op_eq
l_int|0
)paren
r_return
id|biovec-&gt;bv_len
suffix:semicolon
r_else
r_return
id|max
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
id|cur
op_assign
l_int|0
comma
id|i
op_assign
l_int|0
comma
id|nb_zone
suffix:semicolon
id|s64
id|size
suffix:semicolon
id|raid0_conf_t
op_star
id|conf
suffix:semicolon
id|mdk_rdev_t
op_star
id|rdev
suffix:semicolon
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: setting max_sectors to %d, segment boundary to %d&bslash;n&quot;
comma
id|mdname
c_func
(paren
id|mddev
)paren
comma
id|mddev-&gt;chunk_size
op_rshift
l_int|9
comma
(paren
id|mddev-&gt;chunk_size
op_rshift
l_int|1
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|blk_queue_max_sectors
c_func
(paren
id|mddev-&gt;queue
comma
id|mddev-&gt;chunk_size
op_rshift
l_int|9
)paren
suffix:semicolon
id|blk_queue_segment_boundary
c_func
(paren
id|mddev-&gt;queue
comma
(paren
id|mddev-&gt;chunk_size
op_rshift
l_int|1
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|conf
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|raid0_conf_t
)paren
comma
id|GFP_KERNEL
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
id|conf-&gt;strip_zone
op_assign
l_int|NULL
suffix:semicolon
id|conf-&gt;devlist
op_assign
l_int|NULL
suffix:semicolon
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
multiline_comment|/* calculate array device size */
id|mddev-&gt;array_size
op_assign
l_int|0
suffix:semicolon
id|ITERATE_RDEV
c_func
(paren
id|mddev
comma
id|rdev
comma
id|tmp
)paren
id|mddev-&gt;array_size
op_add_assign
id|rdev-&gt;size
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;raid0 : md_size is %llu blocks.&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|mddev-&gt;array_size
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;raid0 : conf-&gt;hash_spacing is %llu blocks.&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|conf-&gt;hash_spacing
)paren
suffix:semicolon
(brace
macro_line|#if __GNUC__ &lt; 3
r_volatile
macro_line|#endif
id|sector_t
id|s
op_assign
id|mddev-&gt;array_size
suffix:semicolon
id|sector_t
id|space
op_assign
id|conf-&gt;hash_spacing
suffix:semicolon
r_int
id|round
suffix:semicolon
id|conf-&gt;preshift
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
r_sizeof
(paren
id|sector_t
)paren
OG
r_sizeof
(paren
r_int
r_int
)paren
)paren
(brace
multiline_comment|/*shift down space and s so that sector_div will work */
r_while
c_loop
(paren
id|space
OG
(paren
id|sector_t
)paren
(paren
op_complement
(paren
r_int
r_int
)paren
l_int|0
)paren
)paren
(brace
id|s
op_rshift_assign
l_int|1
suffix:semicolon
id|space
op_rshift_assign
l_int|1
suffix:semicolon
id|s
op_add_assign
l_int|1
suffix:semicolon
multiline_comment|/* force round-up */
id|conf-&gt;preshift
op_increment
suffix:semicolon
)brace
)brace
id|round
op_assign
id|sector_div
c_func
(paren
id|s
comma
(paren
r_int
r_int
)paren
id|space
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|nb_zone
op_assign
id|s
op_plus
id|round
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;raid0 : nb_zone is %d.&bslash;n&quot;
comma
id|nb_zone
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;raid0 : Allocating %Zd bytes for hash.&bslash;n&quot;
comma
id|nb_zone
op_star
r_sizeof
(paren
r_struct
id|strip_zone
op_star
)paren
)paren
suffix:semicolon
id|conf-&gt;hash_table
op_assign
id|kmalloc
(paren
r_sizeof
(paren
r_struct
id|strip_zone
op_star
)paren
op_star
id|nb_zone
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|conf-&gt;hash_table
)paren
r_goto
id|out_free_conf
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nb_zone
suffix:semicolon
id|i
op_increment
)paren
(brace
id|conf-&gt;hash_table
(braket
id|i
)braket
op_assign
id|conf-&gt;strip_zone
op_plus
id|cur
suffix:semicolon
r_while
c_loop
(paren
id|size
op_le
id|conf-&gt;hash_spacing
)paren
(brace
id|cur
op_increment
suffix:semicolon
id|size
op_add_assign
id|conf-&gt;strip_zone
(braket
id|cur
)braket
dot
id|size
suffix:semicolon
)brace
id|size
op_sub_assign
id|conf-&gt;hash_spacing
suffix:semicolon
)brace
r_if
c_cond
(paren
id|conf-&gt;preshift
)paren
(brace
id|conf-&gt;hash_spacing
op_rshift_assign
id|conf-&gt;preshift
suffix:semicolon
multiline_comment|/* round hash_spacing up so when we divide by it, we&n;&t;&t; * err on the side of too-low, which is safest&n;&t;&t; */
id|conf-&gt;hash_spacing
op_increment
suffix:semicolon
)brace
multiline_comment|/* calculate the max read-ahead size.&n;&t; * For read-ahead of large files to be effective, we need to&n;&t; * readahead at least twice a whole stripe. i.e. number of devices&n;&t; * multiplied by chunk size times 2.&n;&t; * If an individual device has an ra_pages greater than the&n;&t; * chunk size, then we will not drive that device as hard as it&n;&t; * wants.  We consider this a configuration error: a larger&n;&t; * chunksize should be used in that case.&n;&t; */
(brace
r_int
id|stripe
op_assign
id|mddev-&gt;raid_disks
op_star
id|mddev-&gt;chunk_size
op_div
id|PAGE_CACHE_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|mddev-&gt;queue-&gt;backing_dev_info.ra_pages
OL
l_int|2
op_star
id|stripe
)paren
id|mddev-&gt;queue-&gt;backing_dev_info.ra_pages
op_assign
l_int|2
op_star
id|stripe
suffix:semicolon
)brace
id|blk_queue_merge_bvec
c_func
(paren
id|mddev-&gt;queue
comma
id|raid0_mergeable_bvec
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_free_conf
suffix:colon
r_if
c_cond
(paren
id|conf-&gt;strip_zone
)paren
id|kfree
c_func
(paren
id|conf-&gt;strip_zone
)paren
suffix:semicolon
r_if
c_cond
(paren
id|conf-&gt;devlist
)paren
id|kfree
(paren
id|conf-&gt;devlist
)paren
suffix:semicolon
id|kfree
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
id|blk_sync_queue
c_func
(paren
id|mddev-&gt;queue
)paren
suffix:semicolon
multiline_comment|/* the unplug fn references &squot;conf&squot;*/
id|kfree
(paren
id|conf-&gt;hash_table
)paren
suffix:semicolon
id|conf-&gt;hash_table
op_assign
l_int|NULL
suffix:semicolon
id|kfree
(paren
id|conf-&gt;strip_zone
)paren
suffix:semicolon
id|conf-&gt;strip_zone
op_assign
l_int|NULL
suffix:semicolon
id|kfree
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|raid0_make_request
r_static
r_int
id|raid0_make_request
(paren
id|request_queue_t
op_star
id|q
comma
r_struct
id|bio
op_star
id|bio
)paren
(brace
id|mddev_t
op_star
id|mddev
op_assign
id|q-&gt;queuedata
suffix:semicolon
r_int
r_int
id|sect_in_chunk
comma
id|chunksize_bits
comma
id|chunk_size
comma
id|chunk_sects
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
suffix:semicolon
id|sector_t
id|block
comma
id|rsect
suffix:semicolon
r_if
c_cond
(paren
id|bio_data_dir
c_func
(paren
id|bio
)paren
op_eq
id|WRITE
)paren
(brace
id|disk_stat_inc
c_func
(paren
id|mddev-&gt;gendisk
comma
id|writes
)paren
suffix:semicolon
id|disk_stat_add
c_func
(paren
id|mddev-&gt;gendisk
comma
id|write_sectors
comma
id|bio_sectors
c_func
(paren
id|bio
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|disk_stat_inc
c_func
(paren
id|mddev-&gt;gendisk
comma
id|reads
)paren
suffix:semicolon
id|disk_stat_add
c_func
(paren
id|mddev-&gt;gendisk
comma
id|read_sectors
comma
id|bio_sectors
c_func
(paren
id|bio
)paren
)paren
suffix:semicolon
)brace
id|chunk_size
op_assign
id|mddev-&gt;chunk_size
op_rshift
l_int|10
suffix:semicolon
id|chunk_sects
op_assign
id|mddev-&gt;chunk_size
op_rshift
l_int|9
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
id|bio-&gt;bi_sector
op_rshift
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|chunk_sects
OL
(paren
id|bio-&gt;bi_sector
op_amp
(paren
id|chunk_sects
op_minus
l_int|1
)paren
)paren
op_plus
(paren
id|bio-&gt;bi_size
op_rshift
l_int|9
)paren
)paren
)paren
(brace
r_struct
id|bio_pair
op_star
id|bp
suffix:semicolon
multiline_comment|/* Sanity check -- queue functions should prevent this happening */
r_if
c_cond
(paren
id|bio-&gt;bi_vcnt
op_ne
l_int|1
op_logical_or
id|bio-&gt;bi_idx
op_ne
l_int|0
)paren
r_goto
id|bad_map
suffix:semicolon
multiline_comment|/* This is a one page bio that upper layers&n;&t;&t; * refuse to split for us, so we need to split it.&n;&t;&t; */
id|bp
op_assign
id|bio_split
c_func
(paren
id|bio
comma
id|bio_split_pool
comma
id|chunk_sects
op_minus
(paren
id|bio-&gt;bi_sector
op_amp
(paren
id|chunk_sects
op_minus
l_int|1
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|raid0_make_request
c_func
(paren
id|q
comma
op_amp
id|bp-&gt;bio1
)paren
)paren
id|generic_make_request
c_func
(paren
op_amp
id|bp-&gt;bio1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|raid0_make_request
c_func
(paren
id|q
comma
op_amp
id|bp-&gt;bio2
)paren
)paren
id|generic_make_request
c_func
(paren
op_amp
id|bp-&gt;bio2
)paren
suffix:semicolon
id|bio_pair_release
c_func
(paren
id|bp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
(brace
macro_line|#if __GNUC__ &lt; 3
r_volatile
macro_line|#endif
id|sector_t
id|x
op_assign
id|block
op_rshift
id|conf-&gt;preshift
suffix:semicolon
id|sector_div
c_func
(paren
id|x
comma
(paren
r_int
r_int
)paren
id|conf-&gt;hash_spacing
)paren
suffix:semicolon
id|zone
op_assign
id|conf-&gt;hash_table
(braket
id|x
)braket
suffix:semicolon
)brace
r_while
c_loop
(paren
id|block
op_ge
(paren
id|zone-&gt;zone_offset
op_plus
id|zone-&gt;size
)paren
)paren
id|zone
op_increment
suffix:semicolon
id|sect_in_chunk
op_assign
id|bio-&gt;bi_sector
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
(brace
id|sector_t
id|x
op_assign
(paren
id|block
op_minus
id|zone-&gt;zone_offset
)paren
op_rshift
id|chunksize_bits
suffix:semicolon
id|sector_div
c_func
(paren
id|x
comma
id|zone-&gt;nb_dev
)paren
suffix:semicolon
id|chunk
op_assign
id|x
suffix:semicolon
id|BUG_ON
c_func
(paren
id|x
op_ne
(paren
id|sector_t
)paren
id|chunk
)paren
suffix:semicolon
id|x
op_assign
id|block
op_rshift
id|chunksize_bits
suffix:semicolon
id|tmp_dev
op_assign
id|zone-&gt;dev
(braket
id|sector_div
c_func
(paren
id|x
comma
id|zone-&gt;nb_dev
)paren
)braket
suffix:semicolon
)brace
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
id|bio-&gt;bi_bdev
op_assign
id|tmp_dev-&gt;bdev
suffix:semicolon
id|bio-&gt;bi_sector
op_assign
id|rsect
op_plus
id|tmp_dev-&gt;data_offset
suffix:semicolon
multiline_comment|/*&n;&t; * Let the main block layer submit the IO and resolve recursion:&n;&t; */
r_return
l_int|1
suffix:semicolon
id|bad_map
suffix:colon
id|printk
c_func
(paren
l_string|&quot;raid0_make_request bug: can&squot;t convert block across chunks&quot;
l_string|&quot; or bigger than %dk %llu %d&bslash;n&quot;
comma
id|chunk_size
comma
(paren
r_int
r_int
r_int
)paren
id|bio-&gt;bi_sector
comma
id|bio-&gt;bi_size
op_rshift
l_int|10
)paren
suffix:semicolon
id|bio_io_error
c_func
(paren
id|bio
comma
id|bio-&gt;bi_size
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|raid0_status
r_static
r_void
id|raid0_status
(paren
r_struct
id|seq_file
op_star
id|seq
comma
id|mddev_t
op_star
id|mddev
)paren
(brace
DECL|macro|MD_DEBUG
macro_line|#undef MD_DEBUG
macro_line|#ifdef MD_DEBUG
r_int
id|j
comma
id|k
comma
id|h
suffix:semicolon
r_char
id|b
(braket
id|BDEVNAME_SIZE
)braket
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
id|h
op_assign
l_int|0
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
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;      z%d&quot;
comma
id|j
)paren
suffix:semicolon
r_if
c_cond
(paren
id|conf-&gt;hash_table
(braket
id|h
)braket
op_eq
id|conf-&gt;strip_zone
op_plus
id|j
)paren
id|seq_printf
c_func
(paren
l_string|&quot;(h%d)&quot;
comma
id|h
op_increment
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;=[&quot;
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
id|seq_printf
(paren
id|seq
comma
l_string|&quot;%s/&quot;
comma
id|bdevname
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
id|bdev
comma
id|b
)paren
)paren
suffix:semicolon
id|seq_printf
(paren
id|seq
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
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot; %dk chunks&quot;
comma
id|mddev-&gt;chunk_size
op_div
l_int|1024
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|variable|raid0_personality
r_static
id|mdk_personality_t
id|raid0_personality
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;raid0&quot;
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|make_request
op_assign
id|raid0_make_request
comma
dot
id|run
op_assign
id|raid0_run
comma
dot
id|stop
op_assign
id|raid0_stop
comma
dot
id|status
op_assign
id|raid0_status
comma
)brace
suffix:semicolon
DECL|function|raid0_init
r_static
r_int
id|__init
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
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_ALIAS
c_func
(paren
l_string|&quot;md-personality-2&quot;
)paren
suffix:semicolon
multiline_comment|/* RAID0 */
eof
