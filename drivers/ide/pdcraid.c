multiline_comment|/*&n;   pdcraid.c  Copyright (C) 2001 Red Hat, Inc. All rights reserved.&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2, or (at your option)&n;   any later version.&n;   &n;   You should have received a copy of the GNU General Public License&n;   (for example /usr/src/linux/COPYING); if not, write to the Free&n;   Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  &n;   &n;   Authors: &t;Arjan van de Ven &lt;arjanv@redhat.com&gt;&n;   &t;&t;&n;   Based on work done by S&#xfffd;ren Schmidt for FreeBSD  &n;&n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/blkpg.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;ataraid.h&quot;
r_static
r_int
id|pdcraid_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
r_static
r_int
id|pdcraid_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
r_static
r_int
id|pdcraid_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_static
r_int
id|pdcraid0_make_request
(paren
id|request_queue_t
op_star
id|q
comma
r_int
id|rw
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
r_static
r_int
id|pdcraid1_make_request
(paren
id|request_queue_t
op_star
id|q
comma
r_int
id|rw
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
DECL|struct|disk_dev
r_struct
id|disk_dev
(brace
DECL|member|major
r_int
id|major
suffix:semicolon
DECL|member|minor
r_int
id|minor
suffix:semicolon
DECL|member|device
r_int
id|device
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|devlist
r_static
r_struct
id|disk_dev
id|devlist
(braket
)braket
op_assign
(brace
(brace
id|IDE0_MAJOR
comma
l_int|0
comma
op_minus
l_int|1
)brace
comma
(brace
id|IDE0_MAJOR
comma
l_int|64
comma
op_minus
l_int|1
)brace
comma
(brace
id|IDE1_MAJOR
comma
l_int|0
comma
op_minus
l_int|1
)brace
comma
(brace
id|IDE1_MAJOR
comma
l_int|64
comma
op_minus
l_int|1
)brace
comma
(brace
id|IDE2_MAJOR
comma
l_int|0
comma
op_minus
l_int|1
)brace
comma
(brace
id|IDE2_MAJOR
comma
l_int|64
comma
op_minus
l_int|1
)brace
comma
(brace
id|IDE3_MAJOR
comma
l_int|0
comma
op_minus
l_int|1
)brace
comma
(brace
id|IDE3_MAJOR
comma
l_int|64
comma
op_minus
l_int|1
)brace
comma
(brace
id|IDE4_MAJOR
comma
l_int|0
comma
op_minus
l_int|1
)brace
comma
(brace
id|IDE4_MAJOR
comma
l_int|64
comma
op_minus
l_int|1
)brace
comma
(brace
id|IDE5_MAJOR
comma
l_int|0
comma
op_minus
l_int|1
)brace
comma
(brace
id|IDE5_MAJOR
comma
l_int|64
comma
op_minus
l_int|1
)brace
comma
(brace
id|IDE6_MAJOR
comma
l_int|0
comma
op_minus
l_int|1
)brace
comma
(brace
id|IDE6_MAJOR
comma
l_int|64
comma
op_minus
l_int|1
)brace
comma
)brace
suffix:semicolon
DECL|struct|pdcdisk
r_struct
id|pdcdisk
(brace
DECL|member|device
id|kdev_t
id|device
suffix:semicolon
DECL|member|sectors
r_int
r_int
id|sectors
suffix:semicolon
DECL|member|bdev
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
DECL|member|last_pos
r_int
r_int
id|last_pos
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pdcraid
r_struct
id|pdcraid
(brace
DECL|member|stride
r_int
r_int
id|stride
suffix:semicolon
DECL|member|disks
r_int
r_int
id|disks
suffix:semicolon
DECL|member|sectors
r_int
r_int
id|sectors
suffix:semicolon
DECL|member|geom
r_struct
id|geom
id|geom
suffix:semicolon
DECL|member|disk
r_struct
id|pdcdisk
id|disk
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|cutoff
r_int
r_int
id|cutoff
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|cutoff_disks
r_int
r_int
id|cutoff_disks
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|pdcraid0_ops
r_static
r_struct
id|raid_device_operations
id|pdcraid0_ops
op_assign
(brace
id|open
suffix:colon
id|pdcraid_open
comma
id|release
suffix:colon
id|pdcraid_release
comma
id|ioctl
suffix:colon
id|pdcraid_ioctl
comma
id|make_request
suffix:colon
id|pdcraid0_make_request
)brace
suffix:semicolon
DECL|variable|pdcraid1_ops
r_static
r_struct
id|raid_device_operations
id|pdcraid1_ops
op_assign
(brace
id|open
suffix:colon
id|pdcraid_open
comma
id|release
suffix:colon
id|pdcraid_release
comma
id|ioctl
suffix:colon
id|pdcraid_ioctl
comma
id|make_request
suffix:colon
id|pdcraid1_make_request
)brace
suffix:semicolon
DECL|variable|raid
r_static
r_struct
id|pdcraid
id|raid
(braket
l_int|16
)braket
suffix:semicolon
DECL|function|pdcraid_ioctl
r_static
r_int
id|pdcraid_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_int
r_int
id|minor
suffix:semicolon
r_int
r_int
id|sectors
comma
op_star
id|larg
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
op_logical_or
op_logical_neg
id|inode-&gt;i_rdev
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|minor
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_rshift
id|SHIFT
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|BLKGETSIZE
suffix:colon
multiline_comment|/* Return device size */
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|sectors
op_assign
id|ataraid_gendisk.part
(braket
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
)braket
dot
id|nr_sects
suffix:semicolon
r_if
c_cond
(paren
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_amp
l_int|15
)paren
r_return
id|put_user
c_func
(paren
id|sectors
comma
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|raid
(braket
id|minor
)braket
dot
id|sectors
comma
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HDIO_GETGEO
suffix:colon
(brace
r_struct
id|hd_geometry
op_star
id|loc
op_assign
(paren
r_struct
id|hd_geometry
op_star
)paren
id|arg
suffix:semicolon
r_int
r_int
id|bios_cyl
op_assign
id|raid
(braket
id|minor
)braket
dot
id|geom.cylinders
suffix:semicolon
multiline_comment|/* truncate */
r_if
c_cond
(paren
op_logical_neg
id|loc
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|raid
(braket
id|minor
)braket
dot
id|geom.heads
comma
(paren
id|byte
op_star
)paren
op_amp
id|loc-&gt;heads
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|raid
(braket
id|minor
)braket
dot
id|geom.sectors
comma
(paren
id|byte
op_star
)paren
op_amp
id|loc-&gt;sectors
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|bios_cyl
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|loc-&gt;cylinders
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
(paren
r_int
)paren
id|ataraid_gendisk.part
(braket
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
)braket
dot
id|start_sect
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|loc-&gt;start
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|HDIO_GETGEO_BIG
suffix:colon
(brace
r_struct
id|hd_big_geometry
op_star
id|loc
op_assign
(paren
r_struct
id|hd_big_geometry
op_star
)paren
id|arg
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|loc
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|raid
(braket
id|minor
)braket
dot
id|geom.heads
comma
(paren
id|byte
op_star
)paren
op_amp
id|loc-&gt;heads
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|raid
(braket
id|minor
)braket
dot
id|geom.sectors
comma
(paren
id|byte
op_star
)paren
op_amp
id|loc-&gt;sectors
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|raid
(braket
id|minor
)braket
dot
id|geom.cylinders
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|loc-&gt;cylinders
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
(paren
r_int
)paren
id|ataraid_gendisk.part
(braket
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
)braket
dot
id|start_sect
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|loc-&gt;start
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|BLKROSET
suffix:colon
r_case
id|BLKROGET
suffix:colon
r_case
id|BLKSSZGET
suffix:colon
r_return
id|blk_ioctl
c_func
(paren
id|inode-&gt;i_rdev
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Invalid ioctl &bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|partition_map_normal
r_int
r_int
id|partition_map_normal
c_func
(paren
r_int
r_int
id|block
comma
r_int
r_int
id|partition_off
comma
r_int
r_int
id|partition_size
comma
r_int
id|stride
)paren
(brace
r_return
id|block
op_plus
id|partition_off
suffix:semicolon
)brace
DECL|function|partition_map_linux
r_int
r_int
id|partition_map_linux
c_func
(paren
r_int
r_int
id|block
comma
r_int
r_int
id|partition_off
comma
r_int
r_int
id|partition_size
comma
r_int
id|stride
)paren
(brace
r_int
r_int
id|newblock
suffix:semicolon
id|newblock
op_assign
id|stride
op_minus
(paren
id|partition_off
op_mod
id|stride
)paren
suffix:semicolon
r_if
c_cond
(paren
id|newblock
op_eq
id|stride
)paren
id|newblock
op_assign
l_int|0
suffix:semicolon
id|newblock
op_add_assign
id|block
suffix:semicolon
id|newblock
op_assign
id|newblock
op_mod
id|partition_size
suffix:semicolon
id|newblock
op_add_assign
id|partition_off
suffix:semicolon
r_return
id|newblock
suffix:semicolon
)brace
DECL|variable|funky_remap
r_static
r_int
id|funky_remap
(braket
l_int|8
)braket
op_assign
(brace
l_int|0
comma
l_int|1
comma
l_int|2
comma
l_int|3
comma
l_int|4
comma
l_int|5
comma
l_int|6
comma
l_int|7
)brace
suffix:semicolon
DECL|function|partition_map_linux_raid0_4disk
r_int
r_int
id|partition_map_linux_raid0_4disk
c_func
(paren
r_int
r_int
id|block
comma
r_int
r_int
id|partition_off
comma
r_int
r_int
id|partition_size
comma
r_int
id|stride
)paren
(brace
r_int
r_int
id|newblock
comma
id|temp
comma
id|temp2
suffix:semicolon
id|newblock
op_assign
id|stride
op_minus
(paren
id|partition_off
op_mod
id|stride
)paren
suffix:semicolon
r_if
c_cond
(paren
id|newblock
op_eq
id|stride
)paren
id|newblock
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|block
OL
(paren
id|partition_size
op_div
(paren
l_int|8
op_star
id|stride
)paren
)paren
op_star
l_int|8
op_star
id|stride
)paren
(brace
id|temp
op_assign
id|block
op_mod
id|stride
suffix:semicolon
id|temp2
op_assign
id|block
op_div
id|stride
suffix:semicolon
id|temp2
op_assign
(paren
(paren
id|temp2
op_rshift
l_int|3
)paren
op_lshift
l_int|3
)paren
op_or
(paren
id|funky_remap
(braket
id|temp2
op_amp
l_int|7
)braket
)paren
suffix:semicolon
id|block
op_assign
id|temp2
op_star
id|stride
op_plus
id|temp
suffix:semicolon
)brace
id|newblock
op_add_assign
id|block
suffix:semicolon
id|newblock
op_assign
id|newblock
op_mod
id|partition_size
suffix:semicolon
id|newblock
op_add_assign
id|partition_off
suffix:semicolon
r_return
id|newblock
suffix:semicolon
)brace
DECL|function|pdcraid0_make_request
r_static
r_int
id|pdcraid0_make_request
(paren
id|request_queue_t
op_star
id|q
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
id|rsect
suffix:semicolon
r_int
r_int
id|rsect_left
comma
id|rsect_accum
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|block
suffix:semicolon
r_int
r_int
id|disk
op_assign
l_int|0
comma
id|real_disk
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|device
suffix:semicolon
r_struct
id|pdcraid
op_star
id|thisraid
suffix:semicolon
id|rsect
op_assign
id|bh-&gt;b_rsector
suffix:semicolon
multiline_comment|/* Ok. We need to modify this sector number to a new disk + new sector number. &n;&t; * If there are disks of different sizes, this gets tricky. &n;&t; * Example with 3 disks (1Gb, 4Gb and 5 GB):&n;&t; * The first 3 Gb of the &quot;RAID&quot; are evenly spread over the 3 disks.&n;&t; * Then things get interesting. The next 2Gb (RAID view) are spread across disk 2 and 3&n;&t; * and the last 1Gb is disk 3 only.&n;&t; *&n;&t; * the way this is solved is like this: We have a list of &quot;cutoff&quot; points where everytime&n;&t; * a disk falls out of the &quot;higher&quot; count, we mark the max sector. So once we pass a cutoff&n;&t; * point, we have to divide by one less.&n;&t; */
id|device
op_assign
(paren
id|bh-&gt;b_rdev
op_rshift
id|SHIFT
)paren
op_amp
id|MAJOR_MASK
suffix:semicolon
id|thisraid
op_assign
op_amp
id|raid
(braket
id|device
)braket
suffix:semicolon
r_if
c_cond
(paren
id|thisraid-&gt;stride
op_eq
l_int|0
)paren
id|thisraid-&gt;stride
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Partitions need adding of the start sector of the partition to the requested sector */
id|rsect
op_assign
id|partition_map_normal
c_func
(paren
id|rsect
comma
id|ataraid_gendisk.part
(braket
id|MINOR
c_func
(paren
id|bh-&gt;b_rdev
)paren
)braket
dot
id|start_sect
comma
id|ataraid_gendisk.part
(braket
id|MINOR
c_func
(paren
id|bh-&gt;b_rdev
)paren
)braket
dot
id|nr_sects
comma
id|thisraid-&gt;stride
)paren
suffix:semicolon
multiline_comment|/* Woops we need to split the request to avoid crossing a stride barrier */
r_if
c_cond
(paren
(paren
id|rsect
op_div
id|thisraid-&gt;stride
)paren
op_ne
(paren
(paren
id|rsect
op_plus
(paren
id|bh-&gt;b_size
op_div
l_int|512
)paren
op_minus
l_int|1
)paren
op_div
id|thisraid-&gt;stride
)paren
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|rsect_left
op_assign
id|rsect
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|thisraid-&gt;cutoff_disks
(braket
id|i
)braket
op_eq
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|rsect
OG
id|thisraid-&gt;cutoff
(braket
id|i
)braket
)paren
(brace
multiline_comment|/* we&squot;re in the wrong area so far */
id|rsect_left
op_sub_assign
id|thisraid-&gt;cutoff
(braket
id|i
)braket
suffix:semicolon
id|rsect_accum
op_add_assign
id|thisraid-&gt;cutoff
(braket
id|i
)braket
op_div
id|thisraid-&gt;cutoff_disks
(braket
id|i
)braket
suffix:semicolon
)brace
r_else
(brace
id|block
op_assign
id|rsect_left
op_div
id|thisraid-&gt;stride
suffix:semicolon
id|disk
op_assign
id|block
op_mod
id|thisraid-&gt;cutoff_disks
(braket
id|i
)braket
suffix:semicolon
id|block
op_assign
(paren
id|block
op_div
id|thisraid-&gt;cutoff_disks
(braket
id|i
)braket
)paren
op_star
id|thisraid-&gt;stride
suffix:semicolon
id|rsect
op_assign
id|rsect_accum
op_plus
(paren
id|rsect_left
op_mod
id|thisraid-&gt;stride
)paren
op_plus
id|block
suffix:semicolon
r_break
suffix:semicolon
)brace
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|disk
op_eq
l_int|0
)paren
op_logical_and
(paren
id|thisraid-&gt;disk
(braket
id|i
)braket
dot
id|sectors
OG
id|rsect_accum
)paren
)paren
(brace
id|real_disk
op_assign
id|i
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|disk
OG
l_int|0
)paren
op_logical_and
(paren
id|thisraid-&gt;disk
(braket
id|i
)braket
dot
id|sectors
op_ge
id|rsect_accum
)paren
)paren
(brace
id|disk
op_decrement
suffix:semicolon
)brace
)brace
id|disk
op_assign
id|real_disk
suffix:semicolon
multiline_comment|/*&n;&t; * The new BH_Lock semantics in ll_rw_blk.c guarantee that this&n;&t; * is the only IO operation happening on this bh.&n;&t; */
id|bh-&gt;b_rdev
op_assign
id|thisraid-&gt;disk
(braket
id|disk
)braket
dot
id|device
suffix:semicolon
id|bh-&gt;b_rsector
op_assign
id|rsect
suffix:semicolon
multiline_comment|/*&n;&t; * Let the main block layer submit the IO and resolve recursion:&n;&t; */
r_return
l_int|1
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
DECL|function|pdcraid1_write_request
r_static
r_int
id|pdcraid1_write_request
c_func
(paren
id|request_queue_t
op_star
id|q
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
r_struct
id|buffer_head
op_star
id|bh1
suffix:semicolon
r_struct
id|ataraid_bh_private
op_star
r_private
suffix:semicolon
r_int
id|device
suffix:semicolon
r_int
id|i
suffix:semicolon
id|device
op_assign
(paren
id|bh-&gt;b_rdev
op_rshift
id|SHIFT
)paren
op_amp
id|MAJOR_MASK
suffix:semicolon
r_private
op_assign
id|ataraid_get_private
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
r_private
op_eq
l_int|NULL
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_private
op_member_access_from_pointer
id|parent
op_assign
id|bh
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
r_private
op_member_access_from_pointer
id|count
comma
id|raid
(braket
id|device
)braket
dot
id|disks
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
id|raid
(braket
id|device
)braket
dot
id|disks
suffix:semicolon
id|i
op_increment
)paren
(brace
id|bh1
op_assign
id|ataraid_get_bhead
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* If this ever fails we&squot;re doomed */
r_if
c_cond
(paren
op_logical_neg
id|bh1
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* dupe the bufferhead and update the parts that need to be different */
id|memcpy
c_func
(paren
id|bh1
comma
id|bh
comma
r_sizeof
(paren
op_star
id|bh
)paren
)paren
suffix:semicolon
id|bh1-&gt;b_end_io
op_assign
id|ataraid_end_request
suffix:semicolon
id|bh1-&gt;b_private
op_assign
r_private
suffix:semicolon
id|bh1-&gt;b_rsector
op_add_assign
id|ataraid_gendisk.part
(braket
id|MINOR
c_func
(paren
id|bh-&gt;b_rdev
)paren
)braket
dot
id|start_sect
suffix:semicolon
multiline_comment|/* partition offset */
id|bh1-&gt;b_rdev
op_assign
id|raid
(braket
id|device
)braket
dot
id|disk
(braket
id|i
)braket
dot
id|device
suffix:semicolon
multiline_comment|/* update the last known head position for the drive */
id|raid
(braket
id|device
)braket
dot
id|disk
(braket
id|i
)braket
dot
id|last_pos
op_assign
id|bh1-&gt;b_rsector
op_plus
(paren
id|bh1-&gt;b_size
op_rshift
l_int|9
)paren
suffix:semicolon
id|generic_make_request
c_func
(paren
id|rw
comma
id|bh1
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pdcraid1_read_request
r_static
r_int
id|pdcraid1_read_request
(paren
id|request_queue_t
op_star
id|q
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
id|device
suffix:semicolon
r_int
id|dist
suffix:semicolon
r_int
id|bestsofar
comma
id|bestdist
comma
id|i
suffix:semicolon
r_static
r_int
id|previous
suffix:semicolon
multiline_comment|/* Reads are simple in principle. Pick a disk and go. &n;&t;   Initially I cheat by just picking the one which the last known&n;&t;   head position is closest by.&n;&t;   Later on, online/offline checking and performance needs adding */
id|device
op_assign
(paren
id|bh-&gt;b_rdev
op_rshift
id|SHIFT
)paren
op_amp
id|MAJOR_MASK
suffix:semicolon
id|bh-&gt;b_rsector
op_add_assign
id|ataraid_gendisk.part
(braket
id|MINOR
c_func
(paren
id|bh-&gt;b_rdev
)paren
)braket
dot
id|start_sect
suffix:semicolon
id|bestsofar
op_assign
l_int|0
suffix:semicolon
id|bestdist
op_assign
id|raid
(braket
id|device
)braket
dot
id|disk
(braket
l_int|0
)braket
dot
id|last_pos
op_minus
id|bh-&gt;b_rsector
suffix:semicolon
r_if
c_cond
(paren
id|bestdist
OL
l_int|0
)paren
id|bestdist
op_assign
op_minus
id|bestdist
suffix:semicolon
r_if
c_cond
(paren
id|bestdist
OG
l_int|4095
)paren
id|bestdist
op_assign
l_int|4095
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|raid
(braket
id|device
)braket
dot
id|disks
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dist
op_assign
id|raid
(braket
id|device
)braket
dot
id|disk
(braket
id|i
)braket
dot
id|last_pos
op_minus
id|bh-&gt;b_rsector
suffix:semicolon
r_if
c_cond
(paren
id|dist
OL
l_int|0
)paren
id|dist
op_assign
op_minus
id|dist
suffix:semicolon
r_if
c_cond
(paren
id|dist
OG
l_int|4095
)paren
id|dist
op_assign
l_int|4095
suffix:semicolon
r_if
c_cond
(paren
id|bestdist
op_eq
id|dist
)paren
(brace
multiline_comment|/* it&squot;s a tie; try to do some read balancing */
r_if
c_cond
(paren
(paren
id|previous
OG
id|bestsofar
)paren
op_logical_and
(paren
id|previous
op_le
id|i
)paren
)paren
id|bestsofar
op_assign
id|i
suffix:semicolon
id|previous
op_assign
(paren
id|previous
op_plus
l_int|1
)paren
op_mod
id|raid
(braket
id|device
)braket
dot
id|disks
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|bestdist
OG
id|dist
)paren
(brace
id|bestdist
op_assign
id|dist
suffix:semicolon
id|bestsofar
op_assign
id|i
suffix:semicolon
)brace
)brace
id|bh-&gt;b_rdev
op_assign
id|raid
(braket
id|device
)braket
dot
id|disk
(braket
id|bestsofar
)braket
dot
id|device
suffix:semicolon
id|raid
(braket
id|device
)braket
dot
id|disk
(braket
id|bestsofar
)braket
dot
id|last_pos
op_assign
id|bh-&gt;b_rsector
op_plus
(paren
id|bh-&gt;b_size
op_rshift
l_int|9
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Let the main block layer submit the IO and resolve recursion:&n;&t; */
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|pdcraid1_make_request
r_static
r_int
id|pdcraid1_make_request
(paren
id|request_queue_t
op_star
id|q
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
multiline_comment|/* Read and Write are totally different cases; split them totally here */
r_if
c_cond
(paren
id|rw
op_eq
id|READA
)paren
id|rw
op_assign
id|READ
suffix:semicolon
r_if
c_cond
(paren
id|rw
op_eq
id|READ
)paren
r_return
id|pdcraid1_read_request
c_func
(paren
id|q
comma
id|rw
comma
id|bh
)paren
suffix:semicolon
r_else
r_return
id|pdcraid1_write_request
c_func
(paren
id|q
comma
id|rw
comma
id|bh
)paren
suffix:semicolon
)brace
macro_line|#include &quot;pdcraid.h&quot;
DECL|function|calc_pdcblock_offset
r_static
r_int
r_int
id|calc_pdcblock_offset
(paren
r_int
id|major
comma
r_int
id|minor
)paren
(brace
r_int
r_int
id|lba
op_assign
l_int|0
suffix:semicolon
id|kdev_t
id|dev
suffix:semicolon
id|ide_drive_t
op_star
id|ideinfo
suffix:semicolon
id|dev
op_assign
id|MKDEV
c_func
(paren
id|major
comma
id|minor
)paren
suffix:semicolon
id|ideinfo
op_assign
id|get_info_ptr
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ideinfo
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* first sector of the last cluster */
r_if
c_cond
(paren
id|ideinfo-&gt;head
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ideinfo-&gt;sect
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|lba
op_assign
(paren
id|ideinfo-&gt;capacity
op_div
(paren
id|ideinfo-&gt;head
op_star
id|ideinfo-&gt;sect
)paren
)paren
suffix:semicolon
id|lba
op_assign
id|lba
op_star
(paren
id|ideinfo-&gt;head
op_star
id|ideinfo-&gt;sect
)paren
suffix:semicolon
id|lba
op_assign
id|lba
op_minus
id|ideinfo-&gt;sect
suffix:semicolon
r_return
id|lba
suffix:semicolon
)brace
DECL|function|read_disk_sb
r_static
r_int
id|read_disk_sb
(paren
r_int
id|major
comma
r_int
id|minor
comma
r_int
r_char
op_star
id|buffer
comma
r_int
id|bufsize
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|kdev_t
id|dev
op_assign
id|MKDEV
c_func
(paren
id|major
comma
id|minor
)paren
suffix:semicolon
r_int
r_int
id|sb_offset
suffix:semicolon
r_if
c_cond
(paren
id|blksize_size
(braket
id|major
)braket
op_eq
l_int|NULL
)paren
multiline_comment|/* device doesn&squot;t exist */
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*&n;&t; * Calculate the position of the superblock,&n;&t; * it&squot;s at first sector of the last cylinder&n;&t; */
id|sb_offset
op_assign
id|calc_pdcblock_offset
c_func
(paren
id|major
comma
id|minor
)paren
op_div
l_int|8
suffix:semicolon
multiline_comment|/* The /8 transforms sectors into 4Kb blocks */
r_if
c_cond
(paren
id|sb_offset
op_eq
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|set_blocksize
(paren
id|dev
comma
l_int|4096
)paren
suffix:semicolon
id|bh
op_assign
id|bread
(paren
id|dev
comma
id|sb_offset
comma
l_int|4096
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
(brace
id|memcpy
(paren
id|buffer
comma
id|bh-&gt;b_data
comma
id|bufsize
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;pdcraid: Error reading superblock.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
m_abort
suffix:semicolon
)brace
id|ret
op_assign
l_int|0
suffix:semicolon
m_abort
suffix:colon
r_if
c_cond
(paren
id|bh
)paren
id|brelse
(paren
id|bh
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|calc_sb_csum
r_static
r_int
r_int
id|calc_sb_csum
(paren
r_int
r_int
op_star
id|ptr
)paren
(brace
r_int
r_int
id|sum
suffix:semicolon
r_int
id|count
suffix:semicolon
id|sum
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|count
OL
l_int|511
suffix:semicolon
id|count
op_increment
)paren
id|sum
op_add_assign
op_star
id|ptr
op_increment
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
DECL|variable|cookie
r_static
r_int
id|cookie
op_assign
l_int|0
suffix:semicolon
DECL|function|probedisk
r_static
r_void
id|__init
id|probedisk
c_func
(paren
r_int
id|devindex
comma
r_int
id|device
comma
r_int
id|raidlevel
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|major
comma
id|minor
suffix:semicolon
r_struct
id|promise_raid_conf
op_star
id|prom
suffix:semicolon
r_static
r_int
r_char
id|block
(braket
l_int|4096
)braket
suffix:semicolon
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
r_if
c_cond
(paren
id|devlist
(braket
id|devindex
)braket
dot
id|device
op_ne
op_minus
l_int|1
)paren
multiline_comment|/* already assigned to another array */
r_return
suffix:semicolon
id|major
op_assign
id|devlist
(braket
id|devindex
)braket
dot
id|major
suffix:semicolon
id|minor
op_assign
id|devlist
(braket
id|devindex
)braket
dot
id|minor
suffix:semicolon
r_if
c_cond
(paren
id|read_disk_sb
c_func
(paren
id|major
comma
id|minor
comma
(paren
r_int
r_char
op_star
)paren
op_amp
id|block
comma
r_sizeof
(paren
id|block
)paren
)paren
)paren
r_return
suffix:semicolon
id|prom
op_assign
(paren
r_struct
id|promise_raid_conf
op_star
)paren
op_amp
id|block
(braket
l_int|512
)braket
suffix:semicolon
multiline_comment|/* the checksums must match */
r_if
c_cond
(paren
id|prom-&gt;checksum
op_ne
id|calc_sb_csum
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|prom
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|prom-&gt;raid.type
op_ne
id|raidlevel
)paren
multiline_comment|/* different raidlevel */
r_return
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cookie
op_ne
l_int|0
)paren
op_logical_and
(paren
id|cookie
op_ne
id|prom-&gt;raid.magic_1
)paren
)paren
multiline_comment|/* different array */
r_return
suffix:semicolon
id|cookie
op_assign
id|prom-&gt;raid.magic_1
suffix:semicolon
multiline_comment|/* This looks evil. But basically, we have to search for our adapternumber&n;&t;   in the arraydefinition, both of which are in the superblock */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|i
OL
id|prom-&gt;raid.total_disks
)paren
op_logical_and
(paren
id|i
OL
l_int|8
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|prom-&gt;raid.disk
(braket
id|i
)braket
dot
id|channel
op_eq
id|prom-&gt;raid.channel
)paren
op_logical_and
(paren
id|prom-&gt;raid.disk
(braket
id|i
)braket
dot
id|device
op_eq
id|prom-&gt;raid.device
)paren
)paren
(brace
id|bdev
op_assign
id|bdget
c_func
(paren
id|MKDEV
c_func
(paren
id|major
comma
id|minor
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bdev
op_logical_and
id|blkdev_get
c_func
(paren
id|bdev
comma
id|FMODE_READ
op_or
id|FMODE_WRITE
comma
l_int|0
comma
id|BDEV_RAW
)paren
op_eq
l_int|0
)paren
(brace
id|raid
(braket
id|device
)braket
dot
id|disk
(braket
id|i
)braket
dot
id|bdev
op_assign
id|bdev
suffix:semicolon
)brace
id|raid
(braket
id|device
)braket
dot
id|disk
(braket
id|i
)braket
dot
id|device
op_assign
id|MKDEV
c_func
(paren
id|major
comma
id|minor
)paren
suffix:semicolon
id|raid
(braket
id|device
)braket
dot
id|disk
(braket
id|i
)braket
dot
id|sectors
op_assign
id|prom-&gt;raid.disk_secs
suffix:semicolon
id|raid
(braket
id|device
)braket
dot
id|stride
op_assign
(paren
l_int|1
op_lshift
id|prom-&gt;raid.raid0_shift
)paren
suffix:semicolon
id|raid
(braket
id|device
)braket
dot
id|disks
op_assign
id|prom-&gt;raid.total_disks
suffix:semicolon
id|raid
(braket
id|device
)braket
dot
id|sectors
op_assign
id|prom-&gt;raid.total_secs
suffix:semicolon
id|raid
(braket
id|device
)braket
dot
id|geom.heads
op_assign
id|prom-&gt;raid.heads
op_plus
l_int|1
suffix:semicolon
id|raid
(braket
id|device
)braket
dot
id|geom.sectors
op_assign
id|prom-&gt;raid.sectors
suffix:semicolon
id|raid
(braket
id|device
)braket
dot
id|geom.cylinders
op_assign
id|prom-&gt;raid.cylinders
op_plus
l_int|1
suffix:semicolon
id|devlist
(braket
id|devindex
)braket
dot
id|device
op_assign
id|device
suffix:semicolon
)brace
)brace
)brace
DECL|function|fill_cutoff
r_static
r_void
id|__init
id|fill_cutoff
c_func
(paren
r_int
id|device
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_int
r_int
id|smallest
suffix:semicolon
r_int
r_int
id|bar
suffix:semicolon
r_int
id|count
suffix:semicolon
id|bar
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
id|smallest
op_assign
op_complement
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
l_int|8
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
(paren
id|raid
(braket
id|device
)braket
dot
id|disk
(braket
id|j
)braket
dot
id|sectors
OL
id|smallest
)paren
op_logical_and
(paren
id|raid
(braket
id|device
)braket
dot
id|disk
(braket
id|j
)braket
dot
id|sectors
OG
id|bar
)paren
)paren
id|smallest
op_assign
id|raid
(braket
id|device
)braket
dot
id|disk
(braket
id|j
)braket
dot
id|sectors
suffix:semicolon
id|count
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
l_int|8
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
id|raid
(braket
id|device
)braket
dot
id|disk
(braket
id|j
)braket
dot
id|sectors
op_ge
id|smallest
)paren
id|count
op_increment
suffix:semicolon
id|smallest
op_assign
id|smallest
op_star
id|count
suffix:semicolon
id|bar
op_assign
id|smallest
suffix:semicolon
id|raid
(braket
id|device
)braket
dot
id|cutoff
(braket
id|i
)braket
op_assign
id|smallest
suffix:semicolon
id|raid
(braket
id|device
)braket
dot
id|cutoff_disks
(braket
id|i
)braket
op_assign
id|count
suffix:semicolon
)brace
)brace
DECL|function|pdcraid_init_one
r_static
id|__init
r_int
id|pdcraid_init_one
c_func
(paren
r_int
id|device
comma
r_int
id|raidlevel
)paren
(brace
id|request_queue_t
op_star
id|q
suffix:semicolon
r_int
id|i
comma
id|count
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
l_int|14
suffix:semicolon
id|i
op_increment
)paren
id|probedisk
c_func
(paren
id|i
comma
id|device
comma
id|raidlevel
)paren
suffix:semicolon
r_if
c_cond
(paren
id|raidlevel
op_eq
l_int|0
)paren
id|fill_cutoff
c_func
(paren
id|device
)paren
suffix:semicolon
multiline_comment|/* Initialize the gendisk structure */
id|ataraid_register_disk
c_func
(paren
id|device
comma
id|raid
(braket
id|device
)braket
dot
id|sectors
)paren
suffix:semicolon
id|count
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|raid
(braket
id|device
)braket
dot
id|disk
(braket
id|i
)braket
dot
id|device
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Drive %i is %li Mb (%i / %i) &bslash;n&quot;
comma
id|i
comma
id|raid
(braket
id|device
)braket
dot
id|disk
(braket
id|i
)braket
dot
id|sectors
op_div
l_int|2048
comma
id|MAJOR
c_func
(paren
id|raid
(braket
id|device
)braket
dot
id|disk
(braket
id|i
)braket
dot
id|device
)paren
comma
id|MINOR
c_func
(paren
id|raid
(braket
id|device
)braket
dot
id|disk
(braket
id|i
)braket
dot
id|device
)paren
)paren
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|count
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Raid%i array consists of %i drives. &bslash;n&quot;
comma
id|raidlevel
comma
id|count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
DECL|function|pdcraid_init
r_static
id|__init
r_int
id|pdcraid_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|retval
comma
id|device
comma
id|count
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|cookie
op_assign
l_int|0
suffix:semicolon
id|device
op_assign
id|ataraid_get_device
c_func
(paren
op_amp
id|pdcraid0_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|device
OL
l_int|0
)paren
r_break
suffix:semicolon
id|retval
op_assign
id|pdcraid_init_one
c_func
(paren
id|device
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|ataraid_release_device
c_func
(paren
id|device
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
(brace
id|count
op_increment
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
r_do
(brace
id|cookie
op_assign
l_int|0
suffix:semicolon
id|device
op_assign
id|ataraid_get_device
c_func
(paren
op_amp
id|pdcraid1_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|device
OL
l_int|0
)paren
r_break
suffix:semicolon
id|retval
op_assign
id|pdcraid_init_one
c_func
(paren
id|device
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|ataraid_release_device
c_func
(paren
id|device
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
(brace
id|count
op_increment
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Promise Fasttrak(tm) Softwareraid driver for linux version 0.03beta&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Promise Fasttrak(tm) Softwareraid driver 0.03beta: No raid array found&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|pdcraid_exit
r_static
r_void
id|__exit
id|pdcraid_exit
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|device
suffix:semicolon
r_for
c_loop
(paren
id|device
op_assign
l_int|0
suffix:semicolon
id|device
OL
l_int|16
suffix:semicolon
id|device
op_increment
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
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
id|raid
(braket
id|device
)braket
dot
id|disk
(braket
id|i
)braket
dot
id|bdev
suffix:semicolon
id|raid
(braket
id|device
)braket
dot
id|disk
(braket
id|i
)braket
dot
id|bdev
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|bdev
)paren
id|blkdev_put
c_func
(paren
id|bdev
comma
id|BDEV_RAW
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|raid
(braket
id|device
)braket
dot
id|sectors
)paren
id|ataraid_release_device
c_func
(paren
id|device
)paren
suffix:semicolon
)brace
)brace
DECL|function|pdcraid_open
r_static
r_int
id|pdcraid_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pdcraid_release
r_static
r_int
id|pdcraid_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pdcraid_init
id|module_init
c_func
(paren
id|pdcraid_init
)paren
suffix:semicolon
DECL|variable|pdcraid_exit
id|module_exit
c_func
(paren
id|pdcraid_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
