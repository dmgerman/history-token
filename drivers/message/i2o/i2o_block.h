multiline_comment|/*&n; *&t;Block OSM structures/API&n; *&n; * &t;Copyright (C) 1999-2002&t;Red Hat Software&n; *&n; *&t;Written by Alan Cox, Building Number Three Ltd&n; *&n; *&t;This program is free software; you can redistribute it and/or modify it&n; *&t;under the terms of the GNU General Public License as published by the&n; *&t;Free Software Foundation; either version 2 of the License, or (at your&n; *&t;option) any later version.&n; *&n; *&t;This program is distributed in the hope that it will be useful, but&n; *&t;WITHOUT ANY WARRANTY; without even the implied warranty of&n; *&t;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; *&t;General Public License for more details.&n; *&n; *&t;For the purpose of avoiding doubt the preferred form of the work&n; *&t;for making modifications shall be a standards compliant form such&n; *&t;gzipped tar and not one requiring a proprietary or patent encumbered&n; *&t;tool to unpack.&n; *&n; *&t;Fixes/additions:&n; *&t;&t;Steve Ralston:&n; *&t;&t;&t;Multiple device handling error fixes,&n; *&t;&t;&t;Added a queue depth.&n; *&t;&t;Alan Cox:&n; *&t;&t;&t;FC920 has an rmw bug. Dont or in the end marker.&n; *&t;&t;&t;Removed queue walk, fixed for 64bitness.&n; *&t;&t;&t;Rewrote much of the code over time&n; *&t;&t;&t;Added indirect block lists&n; *&t;&t;&t;Handle 64K limits on many controllers&n; *&t;&t;&t;Don&squot;t use indirects on the Promise (breaks)&n; *&t;&t;&t;Heavily chop down the queue depths&n; *&t;&t;Deepak Saxena:&n; *&t;&t;&t;Independent queues per IOP&n; *&t;&t;&t;Support for dynamic device creation/deletion&n; *&t;&t;&t;Code cleanup&n; *&t;    &t;&t;Support for larger I/Os through merge* functions&n; *&t;&t;&t;(taken from DAC960 driver)&n; *&t;&t;Boji T Kannanthanam:&n; *&t;&t;&t;Set the I2O Block devices to be detected in increasing&n; *&t;&t;&t;order of TIDs during boot.&n; *&t;&t;&t;Search and set the I2O block device that we boot off&n; *&t;&t;&t;from as the first device to be claimed (as /dev/i2o/hda)&n; *&t;&t;&t;Properly attach/detach I2O gendisk structure from the&n; *&t;&t;&t;system gendisk list. The I2O block devices now appear in&n; *&t;&t;&t;/proc/partitions.&n; *&t;&t;Markus Lidel &lt;Markus.Lidel@shadowconnect.com&gt;:&n; *&t;&t;&t;Minor bugfixes for 2.6.&n; */
macro_line|#ifndef I2O_BLOCK_OSM_H
DECL|macro|I2O_BLOCK_OSM_H
mdefine_line|#define I2O_BLOCK_OSM_H
DECL|macro|I2O_BLOCK_RETRY_TIME
mdefine_line|#define I2O_BLOCK_RETRY_TIME HZ/4
DECL|macro|I2O_BLOCK_MAX_OPEN_REQUESTS
mdefine_line|#define I2O_BLOCK_MAX_OPEN_REQUESTS 50
multiline_comment|/* I2O Block OSM mempool struct */
DECL|struct|i2o_block_mempool
r_struct
id|i2o_block_mempool
(brace
DECL|member|slab
id|kmem_cache_t
op_star
id|slab
suffix:semicolon
DECL|member|pool
id|mempool_t
op_star
id|pool
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* I2O Block device descriptor */
DECL|struct|i2o_block_device
r_struct
id|i2o_block_device
(brace
DECL|member|i2o_dev
r_struct
id|i2o_device
op_star
id|i2o_dev
suffix:semicolon
multiline_comment|/* pointer to I2O device */
DECL|member|gd
r_struct
id|gendisk
op_star
id|gd
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* queue lock */
DECL|member|open_queue
r_struct
id|list_head
id|open_queue
suffix:semicolon
multiline_comment|/* list of transfered, but unfinished&n;&t;&t;&t;&t;&t;   requests */
DECL|member|open_queue_depth
r_int
r_int
id|open_queue_depth
suffix:semicolon
multiline_comment|/* number of requests in the queue */
DECL|member|rcache
r_int
id|rcache
suffix:semicolon
multiline_comment|/* read cache flags */
DECL|member|wcache
r_int
id|wcache
suffix:semicolon
multiline_comment|/* write cache flags */
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|power
r_int
id|power
suffix:semicolon
multiline_comment|/* power state */
DECL|member|media_change_flag
r_int
id|media_change_flag
suffix:semicolon
multiline_comment|/* media changed flag */
)brace
suffix:semicolon
multiline_comment|/* I2O Block device request */
DECL|struct|i2o_block_request
r_struct
id|i2o_block_request
(brace
DECL|member|queue
r_struct
id|list_head
id|queue
suffix:semicolon
DECL|member|req
r_struct
id|request
op_star
id|req
suffix:semicolon
multiline_comment|/* corresponding request */
DECL|member|i2o_blk_dev
r_struct
id|i2o_block_device
op_star
id|i2o_blk_dev
suffix:semicolon
multiline_comment|/* I2O block device */
DECL|member|sg_dma_direction
r_int
id|sg_dma_direction
suffix:semicolon
multiline_comment|/* direction of DMA buffer read/write */
DECL|member|sg_nents
r_int
id|sg_nents
suffix:semicolon
multiline_comment|/* number of SG elements */
DECL|member|sg_table
r_struct
id|scatterlist
id|sg_table
(braket
id|I2O_MAX_SEGMENTS
)braket
suffix:semicolon
multiline_comment|/* SG table */
)brace
suffix:semicolon
multiline_comment|/* I2O Block device delayed request */
DECL|struct|i2o_block_delayed_request
r_struct
id|i2o_block_delayed_request
(brace
DECL|member|work
r_struct
id|work_struct
id|work
suffix:semicolon
DECL|member|queue
r_struct
id|request_queue
op_star
id|queue
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
