multiline_comment|/*&n;   linear.c : Multiple Devices driver for Linux&n;              Copyright (C) 1994-96 Marc ZYNGIER&n;&t;      &lt;zyngier@ufr-info-p7.ibp.fr&gt; or&n;&t;      &lt;maz@gloups.fdn.fr&gt;&n;&n;   Linear mode management functions.&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2, or (at your option)&n;   any later version.&n;   &n;   You should have received a copy of the GNU General Public License&n;   (for example /usr/src/linux/COPYING); if not, write to the Free&n;   Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  &n;*/
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
id|j
comma
id|nb_zone
suffix:semicolon
r_int
r_int
id|curr_offset
suffix:semicolon
id|MOD_INC_USE_COUNT
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
l_string|&quot;linear: disks are not ordered, aborting!&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Find the smallest device.&n;&t; */
id|conf-&gt;smallest
op_assign
l_int|NULL
suffix:semicolon
id|curr_offset
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
id|dev_info_t
op_star
id|disk
op_assign
id|conf-&gt;disks
op_plus
id|j
suffix:semicolon
id|disk-&gt;dev
op_assign
id|rdev-&gt;dev
suffix:semicolon
id|disk-&gt;size
op_assign
id|rdev-&gt;size
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
)brace
id|nb_zone
op_assign
id|conf-&gt;nr_zones
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
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
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
id|i
op_assign
l_int|0
suffix:semicolon
id|size
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
id|mddev-&gt;nb_dev
suffix:semicolon
id|j
op_increment
)paren
(brace
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
id|MOD_DEC_USE_COUNT
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
id|MOD_DEC_USE_COUNT
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
id|mddev_t
op_star
id|mddev
comma
r_int
id|rw
comma
r_struct
id|bio
op_star
id|bio
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
r_struct
id|linear_hash
op_star
id|hash
suffix:semicolon
id|dev_info_t
op_star
id|tmp_dev
suffix:semicolon
r_int
id|block
suffix:semicolon
id|block
op_assign
id|bio-&gt;bi_sector
op_rshift
l_int|1
suffix:semicolon
id|hash
op_assign
id|conf-&gt;hash_table
op_plus
(paren
id|block
op_div
id|conf-&gt;smallest-&gt;size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|block
op_ge
(paren
id|hash-&gt;dev0-&gt;size
op_plus
id|hash-&gt;dev0-&gt;offset
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|hash-&gt;dev1
)paren
(brace
id|printk
(paren
l_string|&quot;linear_make_request : hash-&gt;dev1==NULL for block %ld&bslash;n&quot;
comma
id|block
)paren
suffix:semicolon
id|bio_io_error
c_func
(paren
id|bio
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|tmp_dev
op_assign
id|hash-&gt;dev1
suffix:semicolon
)brace
r_else
id|tmp_dev
op_assign
id|hash-&gt;dev0
suffix:semicolon
r_if
c_cond
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
(brace
id|printk
(paren
l_string|&quot;linear_make_request: Block %ld out of bounds on dev %s size %ld offset %ld&bslash;n&quot;
comma
id|block
comma
id|kdevname
c_func
(paren
id|tmp_dev-&gt;dev
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
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|bio-&gt;bi_dev
op_assign
id|tmp_dev-&gt;dev
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
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|linear_status
r_static
r_int
id|linear_status
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
l_string|&quot;[%s&quot;
comma
id|partition_name
c_func
(paren
id|conf-&gt;hash_table
(braket
id|j
)braket
dot
id|dev0-&gt;dev
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
id|sz
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|sz
comma
l_string|&quot;/%s] &quot;
comma
id|partition_name
c_func
(paren
id|conf-&gt;hash_table
(braket
id|j
)braket
dot
id|dev1-&gt;dev
)paren
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
l_string|&quot; %dk rounding&quot;
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
DECL|variable|linear_personality
r_static
id|mdk_personality_t
id|linear_personality
op_assign
(brace
id|name
suffix:colon
l_string|&quot;linear&quot;
comma
id|make_request
suffix:colon
id|linear_make_request
comma
id|run
suffix:colon
id|linear_run
comma
id|stop
suffix:colon
id|linear_stop
comma
id|status
suffix:colon
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
eof
