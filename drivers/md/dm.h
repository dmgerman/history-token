multiline_comment|/*&n; * Internal header file for device mapper&n; *&n; * Copyright (C) 2001, 2002 Sistina Software&n; *&n; * This file is released under the LGPL.&n; */
macro_line|#ifndef DM_INTERNAL_H
DECL|macro|DM_INTERNAL_H
mdefine_line|#define DM_INTERNAL_H
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/device-mapper.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
DECL|macro|DM_NAME
mdefine_line|#define DM_NAME &quot;device-mapper&quot;
DECL|macro|DMWARN
mdefine_line|#define DMWARN(f, x...) printk(KERN_WARNING DM_NAME &quot;: &quot; f &quot;&bslash;n&quot; , ## x)
DECL|macro|DMERR
mdefine_line|#define DMERR(f, x...) printk(KERN_ERR DM_NAME &quot;: &quot; f &quot;&bslash;n&quot; , ## x)
DECL|macro|DMINFO
mdefine_line|#define DMINFO(f, x...) printk(KERN_INFO DM_NAME &quot;: &quot; f &quot;&bslash;n&quot; , ## x)
multiline_comment|/*&n; * FIXME: I think this should be with the definition of sector_t&n; * in types.h.&n; */
macro_line|#ifdef CONFIG_LBD
DECL|macro|SECTOR_FORMAT
mdefine_line|#define SECTOR_FORMAT &quot;%Lu&quot;
macro_line|#else
DECL|macro|SECTOR_FORMAT
mdefine_line|#define SECTOR_FORMAT &quot;%lu&quot;
macro_line|#endif
DECL|macro|SECTOR_SHIFT
mdefine_line|#define SECTOR_SHIFT 9
r_extern
r_struct
id|block_device_operations
id|dm_blk_dops
suffix:semicolon
multiline_comment|/*&n; * List of devices that a metadevice uses and should open/close.&n; */
DECL|struct|dm_dev
r_struct
id|dm_dev
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
DECL|member|mode
r_int
id|mode
suffix:semicolon
DECL|member|bdev
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|dm_table
suffix:semicolon
r_struct
id|mapped_device
suffix:semicolon
multiline_comment|/*-----------------------------------------------------------------&n; * Functions for manipulating a struct mapped_device.&n; * Drop the reference with dm_put when you finish with the object.&n; *---------------------------------------------------------------*/
r_int
id|dm_create
c_func
(paren
r_struct
id|mapped_device
op_star
op_star
id|md
)paren
suffix:semicolon
r_int
id|dm_create_with_minor
c_func
(paren
r_int
r_int
id|minor
comma
r_struct
id|mapped_device
op_star
op_star
id|md
)paren
suffix:semicolon
multiline_comment|/*&n; * Reference counting for md.&n; */
r_void
id|dm_get
c_func
(paren
r_struct
id|mapped_device
op_star
id|md
)paren
suffix:semicolon
r_void
id|dm_put
c_func
(paren
r_struct
id|mapped_device
op_star
id|md
)paren
suffix:semicolon
multiline_comment|/*&n; * A device can still be used while suspended, but I/O is deferred.&n; */
r_int
id|dm_suspend
c_func
(paren
r_struct
id|mapped_device
op_star
id|md
)paren
suffix:semicolon
r_int
id|dm_resume
c_func
(paren
r_struct
id|mapped_device
op_star
id|md
)paren
suffix:semicolon
multiline_comment|/*&n; * The device must be suspended before calling this method.&n; */
r_int
id|dm_swap_table
c_func
(paren
r_struct
id|mapped_device
op_star
id|md
comma
r_struct
id|dm_table
op_star
id|t
)paren
suffix:semicolon
multiline_comment|/*&n; * Drop a reference on the table when you&squot;ve finished with the&n; * result.&n; */
r_struct
id|dm_table
op_star
id|dm_get_table
c_func
(paren
r_struct
id|mapped_device
op_star
id|md
)paren
suffix:semicolon
multiline_comment|/*&n; * Event functions.&n; */
r_uint32
id|dm_get_event_nr
c_func
(paren
r_struct
id|mapped_device
op_star
id|md
)paren
suffix:semicolon
r_int
id|dm_add_wait_queue
c_func
(paren
r_struct
id|mapped_device
op_star
id|md
comma
id|wait_queue_t
op_star
id|wq
comma
r_uint32
id|event_nr
)paren
suffix:semicolon
r_void
id|dm_remove_wait_queue
c_func
(paren
r_struct
id|mapped_device
op_star
id|md
comma
id|wait_queue_t
op_star
id|wq
)paren
suffix:semicolon
multiline_comment|/*&n; * Info functions.&n; */
r_struct
id|gendisk
op_star
id|dm_disk
c_func
(paren
r_struct
id|mapped_device
op_star
id|md
)paren
suffix:semicolon
r_int
id|dm_suspended
c_func
(paren
r_struct
id|mapped_device
op_star
id|md
)paren
suffix:semicolon
multiline_comment|/*-----------------------------------------------------------------&n; * Functions for manipulating a table.  Tables are also reference&n; * counted.&n; *---------------------------------------------------------------*/
r_int
id|dm_table_create
c_func
(paren
r_struct
id|dm_table
op_star
op_star
id|result
comma
r_int
id|mode
comma
r_int
id|num_targets
)paren
suffix:semicolon
r_void
id|dm_table_get
c_func
(paren
r_struct
id|dm_table
op_star
id|t
)paren
suffix:semicolon
r_void
id|dm_table_put
c_func
(paren
r_struct
id|dm_table
op_star
id|t
)paren
suffix:semicolon
r_int
id|dm_table_add_target
c_func
(paren
r_struct
id|dm_table
op_star
id|t
comma
r_const
r_char
op_star
id|type
comma
id|sector_t
id|start
comma
id|sector_t
id|len
comma
r_char
op_star
id|params
)paren
suffix:semicolon
r_int
id|dm_table_complete
c_func
(paren
r_struct
id|dm_table
op_star
id|t
)paren
suffix:semicolon
r_void
id|dm_table_event_callback
c_func
(paren
r_struct
id|dm_table
op_star
id|t
comma
r_void
(paren
op_star
id|fn
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|context
)paren
suffix:semicolon
r_void
id|dm_table_event
c_func
(paren
r_struct
id|dm_table
op_star
id|t
)paren
suffix:semicolon
id|sector_t
id|dm_table_get_size
c_func
(paren
r_struct
id|dm_table
op_star
id|t
)paren
suffix:semicolon
r_struct
id|dm_target
op_star
id|dm_table_get_target
c_func
(paren
r_struct
id|dm_table
op_star
id|t
comma
r_int
r_int
id|index
)paren
suffix:semicolon
r_struct
id|dm_target
op_star
id|dm_table_find_target
c_func
(paren
r_struct
id|dm_table
op_star
id|t
comma
id|sector_t
id|sector
)paren
suffix:semicolon
r_void
id|dm_table_set_restrictions
c_func
(paren
r_struct
id|dm_table
op_star
id|t
comma
r_struct
id|request_queue
op_star
id|q
)paren
suffix:semicolon
r_int
r_int
id|dm_table_get_num_targets
c_func
(paren
r_struct
id|dm_table
op_star
id|t
)paren
suffix:semicolon
r_struct
id|list_head
op_star
id|dm_table_get_devices
c_func
(paren
r_struct
id|dm_table
op_star
id|t
)paren
suffix:semicolon
r_int
id|dm_table_get_mode
c_func
(paren
r_struct
id|dm_table
op_star
id|t
)paren
suffix:semicolon
r_void
id|dm_table_suspend_targets
c_func
(paren
r_struct
id|dm_table
op_star
id|t
)paren
suffix:semicolon
r_void
id|dm_table_resume_targets
c_func
(paren
r_struct
id|dm_table
op_star
id|t
)paren
suffix:semicolon
multiline_comment|/*-----------------------------------------------------------------&n; * A registry of target types.&n; *---------------------------------------------------------------*/
r_int
id|dm_target_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|dm_target_exit
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|target_type
op_star
id|dm_get_target_type
c_func
(paren
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_void
id|dm_put_target_type
c_func
(paren
r_struct
id|target_type
op_star
id|t
)paren
suffix:semicolon
multiline_comment|/*-----------------------------------------------------------------&n; * Useful inlines.&n; *---------------------------------------------------------------*/
DECL|function|array_too_big
r_static
r_inline
r_int
id|array_too_big
c_func
(paren
r_int
r_int
id|fixed
comma
r_int
r_int
id|obj
comma
r_int
r_int
id|num
)paren
(brace
r_return
(paren
id|num
OG
(paren
id|ULONG_MAX
op_minus
id|fixed
)paren
op_div
id|obj
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * ceiling(n / size) * size&n; */
DECL|function|dm_round_up
r_static
r_inline
r_int
r_int
id|dm_round_up
c_func
(paren
r_int
r_int
id|n
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|r
op_assign
id|n
op_mod
id|size
suffix:semicolon
r_return
id|n
op_plus
(paren
id|r
ques
c_cond
(paren
id|size
op_minus
id|r
)paren
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Ceiling(n / size)&n; */
DECL|function|dm_div_up
r_static
r_inline
r_int
r_int
id|dm_div_up
c_func
(paren
r_int
r_int
id|n
comma
r_int
r_int
id|size
)paren
(brace
r_return
id|dm_round_up
c_func
(paren
id|n
comma
id|size
)paren
op_div
id|size
suffix:semicolon
)brace
multiline_comment|/*&n; * The device-mapper can be driven through one of two interfaces;&n; * ioctl or filesystem, depending which patch you have applied.&n; */
r_int
id|dm_interface_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|dm_interface_exit
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Targets for linear and striped mappings&n; */
r_int
id|dm_linear_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|dm_linear_exit
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|dm_stripe_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|dm_stripe_exit
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
