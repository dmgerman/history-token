multiline_comment|/*&n;   linear.c : Multiple Devices driver for Linux&n;&t;      Copyright (C) 1994-96 Marc ZYNGIER&n;&t;      &lt;zyngier@ufr-info-p7.ibp.fr&gt; or&n;&t;      &lt;maz@gloups.fdn.fr&gt;&n;&n;   Linear mode management functions.&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2, or (at your option)&n;   any later version.&n;   &n;   You should have received a copy of the GNU General Public License&n;   (for example /usr/src/linux/COPYING); if not, write to the Free&n;   Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  &n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/raid/md.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/raid/linear.h&gt;
DECL|macro|MAJOR_NR
mdefine_line|#define MAJOR_NR MD_MAJOR
DECL|macro|MD_DRIVER
mdefine_line|#define MD_DRIVER
DECL|macro|MD_PERSONALITY
mdefine_line|#define MD_PERSONALITY
multiline_comment|/*&n; * find which device holds a particular offset &n; */
DECL|function|which_dev
r_static
r_inline
id|dev_info_t
op_star
id|which_dev
c_func
(paren
id|mddev_t
op_star
id|mddev
comma
id|sector_t
id|sector
)paren
(brace
r_struct
id|linear_hash
op_star
id|hash
suffix:semicolon
id|linear_conf_t
op_star
id|conf
op_assign
id|mddev_to_conf
c_func
(paren
id|mddev
)paren
suffix:semicolon
id|sector_t
id|block
op_assign
id|sector
op_rshift
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * sector_div(a,b) returns the remainer and sets a to a/b&n;&t; */
(paren
r_void
)paren
id|sector_div
c_func
(paren
id|block
comma
id|conf-&gt;smallest-&gt;size
)paren
suffix:semicolon
id|hash
op_assign
id|conf-&gt;hash_table
op_plus
id|block
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sector
op_rshift
l_int|1
)paren
op_ge
(paren
id|hash-&gt;dev0-&gt;size
op_plus
id|hash-&gt;dev0-&gt;offset
)paren
)paren
r_return
id|hash-&gt;dev1
suffix:semicolon
r_else
r_return
id|hash-&gt;dev0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;linear_mergeable_bvec -- tell bio layer if a two requests can be merged&n; *&t;@q: request queue&n; *&t;@bio: the buffer head that&squot;s been built up so far&n; *&t;@biovec: the request that could be merged to it.&n; *&n; *&t;Return amount of bytes we can take at this offset&n; */
DECL|function|linear_mergeable_bvec
r_static
r_int
id|linear_mergeable_bvec
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
id|dev_info_t
op_star
id|dev0
suffix:semicolon
r_int
r_int
id|maxsectors
comma
id|bio_sectors
op_assign
id|bio-&gt;bi_size
op_rshift
l_int|9
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
id|dev0
op_assign
id|which_dev
c_func
(paren
id|mddev
comma
id|sector
)paren
suffix:semicolon
id|maxsectors
op_assign
(paren
id|dev0-&gt;size
op_lshift
l_int|1
)paren
op_minus
(paren
id|sector
op_minus
(paren
id|dev0-&gt;offset
op_lshift
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|maxsectors
OL
id|bio_sectors
)paren
id|maxsectors
op_assign
l_int|0
suffix:semicolon
r_else
id|maxsectors
op_sub_assign
id|bio_sectors
suffix:semicolon
r_if
c_cond
(paren
id|maxsectors
op_le
(paren
id|PAGE_SIZE
op_rshift
l_int|9
)paren
op_logical_and
id|bio_sectors
op_eq
l_int|0
)paren
r_return
id|biovec-&gt;bv_len
suffix:semicolon
multiline_comment|/* The bytes available at this offset could be really big,&n;&t; * so we cap at 2^31 to avoid overflow */
r_if
c_cond
(paren
id|maxsectors
OG
(paren
l_int|1
op_lshift
(paren
l_int|31
op_minus
l_int|9
)paren
)paren
)paren
r_return
l_int|1
op_lshift
l_int|31
suffix:semicolon
r_return
id|maxsectors
op_lshift
l_int|9
suffix:semicolon
)brace
DECL|function|linear_unplug
r_static
r_void
id|linear_unplug
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
id|linear_conf_t
op_star
id|conf
op_assign
id|mddev_to_conf
c_func
(paren
id|mddev
)paren
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
id|conf-&gt;disks
(braket
id|i
)braket
dot
id|rdev-&gt;bdev
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
DECL|function|linear_issue_flush
r_static
r_int
id|linear_issue_flush
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
id|linear_conf_t
op_star
id|conf
op_assign
id|mddev_to_conf
c_func
(paren
id|mddev
)paren
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
id|conf-&gt;disks
(braket
id|i
)braket
dot
id|rdev-&gt;bdev
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
DECL|function|linear_run
r_static
r_int
id|linear_run
(paren
id|mddev_t
op_star
id|mddev
)paren
(brace
id|linear_conf_t
op_star
id|conf
suffix:semicolon
r_struct
id|linear_hash
op_star
id|table
suffix:semicolon
id|mdk_rdev_t
op_star
id|rdev
suffix:semicolon
r_int
id|size
comma
id|i
comma
id|nb_zone
comma
id|cnt
suffix:semicolon
r_int
r_int
id|curr_offset
suffix:semicolon
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
id|conf
op_assign
id|kmalloc
(paren
r_sizeof
(paren
op_star
id|conf
)paren
op_plus
id|mddev-&gt;raid_disks
op_star
r_sizeof
(paren
id|dev_info_t
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
id|memset
c_func
(paren
id|conf
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|conf
)paren
op_plus
id|mddev-&gt;raid_disks
op_star
r_sizeof
(paren
id|dev_info_t
)paren
)paren
suffix:semicolon
id|mddev
op_member_access_from_pointer
r_private
op_assign
id|conf
suffix:semicolon
multiline_comment|/*&n;&t; * Find the smallest device.&n;&t; */
id|conf-&gt;smallest
op_assign
l_int|NULL
suffix:semicolon
id|cnt
op_assign
l_int|0
suffix:semicolon
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
(brace
r_int
id|j
op_assign
id|rdev-&gt;raid_disk
suffix:semicolon
id|dev_info_t
op_star
id|disk
op_assign
id|conf-&gt;disks
op_plus
id|j
suffix:semicolon
r_if
c_cond
(paren
id|j
template_param
id|mddev-&gt;raid_disks
op_logical_or
id|disk-&gt;rdev
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;linear: disk numbering problem. Aborting!&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|disk-&gt;rdev
op_assign
id|rdev
suffix:semicolon
id|blk_queue_stack_limits
c_func
(paren
id|mddev-&gt;queue
comma
id|rdev-&gt;bdev-&gt;bd_disk-&gt;queue
)paren
suffix:semicolon
multiline_comment|/* as we don&squot;t honour merge_bvec_fn, we must never risk&n;&t;&t; * violating it, so limit -&gt;max_sector to one PAGE, as&n;&t;&t; * a one page request is never in violation.&n;&t;&t; */
r_if
c_cond
(paren
id|rdev-&gt;bdev-&gt;bd_disk-&gt;queue-&gt;merge_bvec_fn
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
id|disk-&gt;size
op_assign
id|rdev-&gt;size
suffix:semicolon
id|mddev-&gt;array_size
op_add_assign
id|rdev-&gt;size
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|conf-&gt;smallest
op_logical_or
(paren
id|disk-&gt;size
OL
id|conf-&gt;smallest-&gt;size
)paren
)paren
id|conf-&gt;smallest
op_assign
id|disk
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
l_string|&quot;linear: not enough drives present. Aborting!&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * This code was restructured to work around a gcc-2.95.3 internal&n;&t; * compiler error.  Alter it with care.&n;&t; */
(brace
id|sector_t
id|sz
suffix:semicolon
r_int
id|round
suffix:semicolon
r_int
r_int
id|base
suffix:semicolon
id|sz
op_assign
id|mddev-&gt;array_size
suffix:semicolon
id|base
op_assign
id|conf-&gt;smallest-&gt;size
suffix:semicolon
id|round
op_assign
id|sector_div
c_func
(paren
id|sz
comma
id|base
)paren
suffix:semicolon
id|nb_zone
op_assign
id|conf-&gt;nr_zones
op_assign
id|sz
op_plus
(paren
id|round
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
id|conf-&gt;hash_table
op_assign
id|kmalloc
(paren
r_sizeof
(paren
r_struct
id|linear_hash
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
id|out
suffix:semicolon
multiline_comment|/*&n;&t; * Here we generate the linear hash table&n;&t; */
id|table
op_assign
id|conf-&gt;hash_table
suffix:semicolon
id|size
op_assign
l_int|0
suffix:semicolon
id|curr_offset
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
id|cnt
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dev_info_t
op_star
id|disk
op_assign
id|conf-&gt;disks
op_plus
id|i
suffix:semicolon
id|disk-&gt;offset
op_assign
id|curr_offset
suffix:semicolon
id|curr_offset
op_add_assign
id|disk-&gt;size
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
l_int|0
)paren
(brace
id|table
(braket
op_minus
l_int|1
)braket
dot
id|dev1
op_assign
id|disk
suffix:semicolon
)brace
id|size
op_add_assign
id|disk-&gt;size
suffix:semicolon
r_while
c_loop
(paren
id|size
OG
l_int|0
)paren
(brace
id|table-&gt;dev0
op_assign
id|disk
suffix:semicolon
id|table-&gt;dev1
op_assign
l_int|NULL
suffix:semicolon
id|size
op_sub_assign
id|conf-&gt;smallest-&gt;size
suffix:semicolon
id|table
op_increment
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|table
op_minus
id|conf-&gt;hash_table
op_ne
id|nb_zone
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|blk_queue_merge_bvec
c_func
(paren
id|mddev-&gt;queue
comma
id|linear_mergeable_bvec
)paren
suffix:semicolon
id|mddev-&gt;queue-&gt;unplug_fn
op_assign
id|linear_unplug
suffix:semicolon
id|mddev-&gt;queue-&gt;issue_flush_fn
op_assign
id|linear_issue_flush
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out
suffix:colon
r_if
c_cond
(paren
id|conf
)paren
id|kfree
c_func
(paren
id|conf
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|linear_stop
r_static
r_int
id|linear_stop
(paren
id|mddev_t
op_star
id|mddev
)paren
(brace
id|linear_conf_t
op_star
id|conf
op_assign
id|mddev_to_conf
c_func
(paren
id|mddev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|conf-&gt;hash_table
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|conf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|linear_make_request
r_static
r_int
id|linear_make_request
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
id|dev_info_t
op_star
id|tmp_dev
suffix:semicolon
id|sector_t
id|block
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
id|tmp_dev
op_assign
id|which_dev
c_func
(paren
id|mddev
comma
id|bio-&gt;bi_sector
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
op_logical_neg
id|tmp_dev
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;linear_make_request: hash-&gt;dev1==NULL for block %llu&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|block
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
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|block
op_ge
(paren
id|tmp_dev-&gt;size
op_plus
id|tmp_dev-&gt;offset
)paren
op_logical_or
id|block
OL
id|tmp_dev-&gt;offset
)paren
)paren
(brace
r_char
id|b
(braket
id|BDEVNAME_SIZE
)braket
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;linear_make_request: Block %llu out of bounds on &quot;
l_string|&quot;dev %s size %ld offset %ld&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|block
comma
id|bdevname
c_func
(paren
id|tmp_dev-&gt;rdev-&gt;bdev
comma
id|b
)paren
comma
id|tmp_dev-&gt;size
comma
id|tmp_dev-&gt;offset
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
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|bio-&gt;bi_sector
op_plus
(paren
id|bio-&gt;bi_size
op_rshift
l_int|9
)paren
OG
(paren
id|tmp_dev-&gt;offset
op_plus
id|tmp_dev-&gt;size
)paren
op_lshift
l_int|1
)paren
)paren
(brace
multiline_comment|/* This bio crosses a device boundary, so we have to&n;&t;&t; * split it.&n;&t;&t; */
r_struct
id|bio_pair
op_star
id|bp
suffix:semicolon
id|bp
op_assign
id|bio_split
c_func
(paren
id|bio
comma
id|bio_split_pool
comma
(paren
id|bio-&gt;bi_sector
op_plus
(paren
id|bio-&gt;bi_size
op_rshift
l_int|9
)paren
op_minus
(paren
id|tmp_dev-&gt;offset
op_plus
id|tmp_dev-&gt;size
)paren
)paren
op_lshift
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|linear_make_request
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
id|linear_make_request
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
id|bio-&gt;bi_bdev
op_assign
id|tmp_dev-&gt;rdev-&gt;bdev
suffix:semicolon
id|bio-&gt;bi_sector
op_assign
id|bio-&gt;bi_sector
op_minus
(paren
id|tmp_dev-&gt;offset
op_lshift
l_int|1
)paren
op_plus
id|tmp_dev-&gt;rdev-&gt;data_offset
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|linear_status
r_static
r_void
id|linear_status
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
suffix:semicolon
id|linear_conf_t
op_star
id|conf
op_assign
id|mddev_to_conf
c_func
(paren
id|mddev
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
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
r_char
id|b
(braket
id|BDEVNAME_SIZE
)braket
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;[%s&quot;
comma
id|bdevname
c_func
(paren
id|conf-&gt;hash_table
(braket
id|j
)braket
dot
id|dev0-&gt;rdev-&gt;bdev
comma
id|b
)paren
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
id|dev1
)paren
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;/%s] &quot;
comma
id|bdevname
c_func
(paren
id|conf-&gt;hash_table
(braket
id|j
)braket
dot
id|dev1-&gt;rdev-&gt;bdev
comma
id|b
)paren
)paren
suffix:semicolon
r_else
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;] &quot;
)paren
suffix:semicolon
)brace
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot; %dk rounding&quot;
comma
id|mddev-&gt;chunk_size
op_div
l_int|1024
)paren
suffix:semicolon
)brace
DECL|variable|linear_personality
r_static
id|mdk_personality_t
id|linear_personality
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;linear&quot;
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|make_request
op_assign
id|linear_make_request
comma
dot
id|run
op_assign
id|linear_run
comma
dot
id|stop
op_assign
id|linear_stop
comma
dot
id|status
op_assign
id|linear_status
comma
)brace
suffix:semicolon
DECL|function|linear_init
r_static
r_int
id|__init
id|linear_init
(paren
r_void
)paren
(brace
r_return
id|register_md_personality
(paren
id|LINEAR
comma
op_amp
id|linear_personality
)paren
suffix:semicolon
)brace
DECL|function|linear_exit
r_static
r_void
id|linear_exit
(paren
r_void
)paren
(brace
id|unregister_md_personality
(paren
id|LINEAR
)paren
suffix:semicolon
)brace
DECL|variable|linear_init
id|module_init
c_func
(paren
id|linear_init
)paren
suffix:semicolon
DECL|variable|linear_exit
id|module_exit
c_func
(paren
id|linear_exit
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
l_string|&quot;md-personality-1&quot;
)paren
suffix:semicolon
multiline_comment|/* LINEAR */
eof
