multiline_comment|/*&n;   ataraid.h  Copyright (C) 2001 Red Hat, Inc. All rights reserved.&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2, or (at your option)&n;   any later version.&n;   &n;   You should have received a copy of the GNU General Public License&n;   (for example /usr/src/linux/COPYING); if not, write to the Free&n;   Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  &n;   &n;   Authors: &t;Arjan van de Ven &lt;arjanv@redhat.com&gt;&n;   &t;&t;&n;   &n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/blkpg.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|ATAMAJOR
mdefine_line|#define ATAMAJOR 114
DECL|macro|SHIFT
mdefine_line|#define SHIFT 4
DECL|macro|MINOR_MASK
mdefine_line|#define MINOR_MASK 15
DECL|macro|MAJOR_MASK
mdefine_line|#define MAJOR_MASK 15
multiline_comment|/* raid_device_operations is a light struct block_device_operations with an&n;   added method for make_request */
DECL|struct|raid_device_operations
r_struct
id|raid_device_operations
(brace
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
DECL|member|release
r_int
(paren
op_star
id|release
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|make_request
r_int
(paren
op_star
id|make_request
)paren
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
)brace
suffix:semicolon
DECL|struct|geom
r_struct
id|geom
(brace
DECL|member|heads
r_int
r_char
id|heads
suffix:semicolon
DECL|member|cylinders
r_int
r_int
id|cylinders
suffix:semicolon
DECL|member|sectors
r_int
r_char
id|sectors
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|gendisk
id|ataraid_gendisk
suffix:semicolon
r_extern
r_int
id|ataraid_get_device
c_func
(paren
r_struct
id|raid_device_operations
op_star
id|fops
)paren
suffix:semicolon
r_extern
r_void
id|ataraid_release_device
c_func
(paren
r_int
id|device
)paren
suffix:semicolon
r_extern
r_int
id|get_blocksize
c_func
(paren
id|kdev_t
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|ataraid_register_disk
c_func
(paren
r_int
id|device
comma
r_int
id|size
)paren
suffix:semicolon
eof
