multiline_comment|/*&n; * Copyright (C) 2001 Sistina Software (UK) Limited.&n; * Copyright (C) 2004 Red Hat, Inc. All rights reserved.&n; *&n; * This file is released under the LGPL.&n; */
macro_line|#ifndef _LINUX_DEVICE_MAPPER_H
DECL|macro|_LINUX_DEVICE_MAPPER_H
mdefine_line|#define _LINUX_DEVICE_MAPPER_H
r_struct
id|dm_target
suffix:semicolon
r_struct
id|dm_table
suffix:semicolon
r_struct
id|dm_dev
suffix:semicolon
DECL|enumerator|STATUSTYPE_INFO
DECL|enumerator|STATUSTYPE_TABLE
DECL|typedef|status_type_t
r_typedef
r_enum
(brace
id|STATUSTYPE_INFO
comma
id|STATUSTYPE_TABLE
)brace
id|status_type_t
suffix:semicolon
DECL|union|map_info
r_union
id|map_info
(brace
DECL|member|ptr
r_void
op_star
id|ptr
suffix:semicolon
DECL|member|ll
r_int
r_int
r_int
id|ll
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * In the constructor the target parameter will already have the&n; * table, type, begin and len fields filled in.&n; */
DECL|typedef|dm_ctr_fn
r_typedef
r_int
(paren
op_star
id|dm_ctr_fn
)paren
(paren
r_struct
id|dm_target
op_star
id|target
comma
r_int
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
suffix:semicolon
multiline_comment|/*&n; * The destructor doesn&squot;t need to free the dm_target, just&n; * anything hidden ti-&gt;private.&n; */
DECL|typedef|dm_dtr_fn
r_typedef
r_void
(paren
op_star
id|dm_dtr_fn
)paren
(paren
r_struct
id|dm_target
op_star
id|ti
)paren
suffix:semicolon
multiline_comment|/*&n; * The map function must return:&n; * &lt; 0: error&n; * = 0: The target will handle the io by resubmitting it later&n; * &gt; 0: simple remap complete&n; */
DECL|typedef|dm_map_fn
r_typedef
r_int
(paren
op_star
id|dm_map_fn
)paren
(paren
r_struct
id|dm_target
op_star
id|ti
comma
r_struct
id|bio
op_star
id|bio
comma
r_union
id|map_info
op_star
id|map_context
)paren
suffix:semicolon
multiline_comment|/*&n; * Returns:&n; * &lt; 0 : error (currently ignored)&n; * 0   : ended successfully&n; * 1   : for some reason the io has still not completed (eg,&n; *       multipath target might want to requeue a failed io).&n; */
DECL|typedef|dm_endio_fn
r_typedef
r_int
(paren
op_star
id|dm_endio_fn
)paren
(paren
r_struct
id|dm_target
op_star
id|ti
comma
r_struct
id|bio
op_star
id|bio
comma
r_int
id|error
comma
r_union
id|map_info
op_star
id|map_context
)paren
suffix:semicolon
DECL|typedef|dm_suspend_fn
r_typedef
r_void
(paren
op_star
id|dm_suspend_fn
)paren
(paren
r_struct
id|dm_target
op_star
id|ti
)paren
suffix:semicolon
DECL|typedef|dm_resume_fn
r_typedef
r_void
(paren
op_star
id|dm_resume_fn
)paren
(paren
r_struct
id|dm_target
op_star
id|ti
)paren
suffix:semicolon
DECL|typedef|dm_status_fn
r_typedef
r_int
(paren
op_star
id|dm_status_fn
)paren
(paren
r_struct
id|dm_target
op_star
id|ti
comma
id|status_type_t
id|status_type
comma
r_char
op_star
id|result
comma
r_int
r_int
id|maxlen
)paren
suffix:semicolon
DECL|typedef|dm_message_fn
r_typedef
r_int
(paren
op_star
id|dm_message_fn
)paren
(paren
r_struct
id|dm_target
op_star
id|ti
comma
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
suffix:semicolon
r_void
id|dm_error
c_func
(paren
r_const
r_char
op_star
id|message
)paren
suffix:semicolon
multiline_comment|/*&n; * Constructors should call these functions to ensure destination devices&n; * are opened/closed correctly.&n; * FIXME: too many arguments.&n; */
r_int
id|dm_get_device
c_func
(paren
r_struct
id|dm_target
op_star
id|ti
comma
r_const
r_char
op_star
id|path
comma
id|sector_t
id|start
comma
id|sector_t
id|len
comma
r_int
id|mode
comma
r_struct
id|dm_dev
op_star
op_star
id|result
)paren
suffix:semicolon
r_void
id|dm_put_device
c_func
(paren
r_struct
id|dm_target
op_star
id|ti
comma
r_struct
id|dm_dev
op_star
id|d
)paren
suffix:semicolon
multiline_comment|/*&n; * Information about a target type&n; */
DECL|struct|target_type
r_struct
id|target_type
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|module
r_struct
id|module
op_star
id|module
suffix:semicolon
DECL|member|version
r_int
id|version
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ctr
id|dm_ctr_fn
id|ctr
suffix:semicolon
DECL|member|dtr
id|dm_dtr_fn
id|dtr
suffix:semicolon
DECL|member|map
id|dm_map_fn
id|map
suffix:semicolon
DECL|member|end_io
id|dm_endio_fn
id|end_io
suffix:semicolon
DECL|member|suspend
id|dm_suspend_fn
id|suspend
suffix:semicolon
DECL|member|resume
id|dm_resume_fn
id|resume
suffix:semicolon
DECL|member|status
id|dm_status_fn
id|status
suffix:semicolon
DECL|member|message
id|dm_message_fn
id|message
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|io_restrictions
r_struct
id|io_restrictions
(brace
DECL|member|max_sectors
r_int
r_int
id|max_sectors
suffix:semicolon
DECL|member|max_phys_segments
r_int
r_int
id|max_phys_segments
suffix:semicolon
DECL|member|max_hw_segments
r_int
r_int
id|max_hw_segments
suffix:semicolon
DECL|member|hardsect_size
r_int
r_int
id|hardsect_size
suffix:semicolon
DECL|member|max_segment_size
r_int
r_int
id|max_segment_size
suffix:semicolon
DECL|member|seg_boundary_mask
r_int
r_int
id|seg_boundary_mask
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dm_target
r_struct
id|dm_target
(brace
DECL|member|table
r_struct
id|dm_table
op_star
id|table
suffix:semicolon
DECL|member|type
r_struct
id|target_type
op_star
id|type
suffix:semicolon
multiline_comment|/* target limits */
DECL|member|begin
id|sector_t
id|begin
suffix:semicolon
DECL|member|len
id|sector_t
id|len
suffix:semicolon
multiline_comment|/* FIXME: turn this into a mask, and merge with io_restrictions */
DECL|member|split_io
id|sector_t
id|split_io
suffix:semicolon
multiline_comment|/*&n;&t; * These are automatically filled in by&n;&t; * dm_table_get_device.&n;&t; */
DECL|member|limits
r_struct
id|io_restrictions
id|limits
suffix:semicolon
multiline_comment|/* target specific data */
DECL|member|private
r_void
op_star
r_private
suffix:semicolon
multiline_comment|/* Used to provide an error string from the ctr */
DECL|member|error
r_char
op_star
id|error
suffix:semicolon
)brace
suffix:semicolon
r_int
id|dm_register_target
c_func
(paren
r_struct
id|target_type
op_star
id|t
)paren
suffix:semicolon
r_int
id|dm_unregister_target
c_func
(paren
r_struct
id|target_type
op_star
id|t
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _LINUX_DEVICE_MAPPER_H */
eof
