multiline_comment|/*&n; * Copyright (C) 2001 Sistina Software (UK) Limited.&n; *&n; * This file is released under the LGPL.&n; */
macro_line|#ifndef _LINUX_DM_IOCTL_V1_H
DECL|macro|_LINUX_DM_IOCTL_V1_H
mdefine_line|#define _LINUX_DM_IOCTL_V1_H
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|DM_DIR
mdefine_line|#define DM_DIR &quot;mapper&quot;&t;/* Slashes not supported */
DECL|macro|DM_MAX_TYPE_NAME
mdefine_line|#define DM_MAX_TYPE_NAME 16
DECL|macro|DM_NAME_LEN
mdefine_line|#define DM_NAME_LEN 128
DECL|macro|DM_UUID_LEN
mdefine_line|#define DM_UUID_LEN 129
multiline_comment|/*&n; * Implements a traditional ioctl interface to the device mapper.&n; */
multiline_comment|/*&n; * All ioctl arguments consist of a single chunk of memory, with&n; * this structure at the start.  If a uuid is specified any&n; * lookup (eg. for a DM_INFO) will be done on that, *not* the&n; * name.&n; */
DECL|struct|dm_ioctl
r_struct
id|dm_ioctl
(brace
multiline_comment|/*&n;&t; * The version number is made up of three parts:&n;&t; * major - no backward or forward compatibility,&n;&t; * minor - only backwards compatible,&n;&t; * patch - both backwards and forwards compatible.&n;&t; *&n;&t; * All clients of the ioctl interface should fill in the&n;&t; * version number of the interface that they were&n;&t; * compiled with.&n;&t; *&n;&t; * All recognised ioctl commands (ie. those that don&squot;t&n;&t; * return -ENOTTY) fill out this field, even if the&n;&t; * command failed.&n;&t; */
DECL|member|version
r_uint32
id|version
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* in/out */
DECL|member|data_size
r_uint32
id|data_size
suffix:semicolon
multiline_comment|/* total size of data passed in&n;&t;&t;&t;&t; * including this struct */
DECL|member|data_start
r_uint32
id|data_start
suffix:semicolon
multiline_comment|/* offset to start of data&n;&t;&t;&t;&t; * relative to start of this struct */
DECL|member|target_count
r_uint32
id|target_count
suffix:semicolon
multiline_comment|/* in/out */
DECL|member|open_count
r_uint32
id|open_count
suffix:semicolon
multiline_comment|/* out */
DECL|member|flags
r_uint32
id|flags
suffix:semicolon
multiline_comment|/* in/out */
DECL|member|dev
id|__kernel_dev_t
id|dev
suffix:semicolon
multiline_comment|/* in/out */
DECL|member|name
r_char
id|name
(braket
id|DM_NAME_LEN
)braket
suffix:semicolon
multiline_comment|/* device name */
DECL|member|uuid
r_char
id|uuid
(braket
id|DM_UUID_LEN
)braket
suffix:semicolon
multiline_comment|/* unique identifier for&n;&t;&t;&t;&t; * the block device */
)brace
suffix:semicolon
multiline_comment|/*&n; * Used to specify tables.  These structures appear after the&n; * dm_ioctl.&n; */
DECL|struct|dm_target_spec
r_struct
id|dm_target_spec
(brace
DECL|member|status
r_int32
id|status
suffix:semicolon
multiline_comment|/* used when reading from kernel only */
DECL|member|sector_start
r_uint64
id|sector_start
suffix:semicolon
DECL|member|length
r_uint32
id|length
suffix:semicolon
multiline_comment|/*&n;&t; * Offset in bytes (from the start of this struct) to&n;&t; * next target_spec.&n;&t; */
DECL|member|next
r_uint32
id|next
suffix:semicolon
DECL|member|target_type
r_char
id|target_type
(braket
id|DM_MAX_TYPE_NAME
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * Parameter string starts immediately after this object.&n;&t; * Be careful to add padding after string to ensure correct&n;&t; * alignment of subsequent dm_target_spec.&n;&t; */
)brace
suffix:semicolon
multiline_comment|/*&n; * Used to retrieve the target dependencies.&n; */
DECL|struct|dm_target_deps
r_struct
id|dm_target_deps
(brace
DECL|member|count
r_uint32
id|count
suffix:semicolon
DECL|member|dev
id|__kernel_dev_t
id|dev
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* out */
)brace
suffix:semicolon
multiline_comment|/*&n; * If you change this make sure you make the corresponding change&n; * to dm-ioctl.c:lookup_ioctl()&n; */
r_enum
(brace
multiline_comment|/* Top level cmds */
DECL|enumerator|DM_VERSION_CMD
id|DM_VERSION_CMD
op_assign
l_int|0
comma
DECL|enumerator|DM_REMOVE_ALL_CMD
id|DM_REMOVE_ALL_CMD
comma
multiline_comment|/* device level cmds */
DECL|enumerator|DM_DEV_CREATE_CMD
id|DM_DEV_CREATE_CMD
comma
DECL|enumerator|DM_DEV_REMOVE_CMD
id|DM_DEV_REMOVE_CMD
comma
DECL|enumerator|DM_DEV_RELOAD_CMD
id|DM_DEV_RELOAD_CMD
comma
DECL|enumerator|DM_DEV_RENAME_CMD
id|DM_DEV_RENAME_CMD
comma
DECL|enumerator|DM_DEV_SUSPEND_CMD
id|DM_DEV_SUSPEND_CMD
comma
DECL|enumerator|DM_DEV_DEPS_CMD
id|DM_DEV_DEPS_CMD
comma
DECL|enumerator|DM_DEV_STATUS_CMD
id|DM_DEV_STATUS_CMD
comma
multiline_comment|/* target level cmds */
DECL|enumerator|DM_TARGET_STATUS_CMD
id|DM_TARGET_STATUS_CMD
comma
DECL|enumerator|DM_TARGET_WAIT_CMD
id|DM_TARGET_WAIT_CMD
)brace
suffix:semicolon
DECL|macro|DM_IOCTL
mdefine_line|#define DM_IOCTL 0xfd
DECL|macro|DM_VERSION
mdefine_line|#define DM_VERSION       _IOWR(DM_IOCTL, DM_VERSION_CMD, struct dm_ioctl)
DECL|macro|DM_REMOVE_ALL
mdefine_line|#define DM_REMOVE_ALL    _IOWR(DM_IOCTL, DM_REMOVE_ALL_CMD, struct dm_ioctl)
DECL|macro|DM_DEV_CREATE
mdefine_line|#define DM_DEV_CREATE    _IOWR(DM_IOCTL, DM_DEV_CREATE_CMD, struct dm_ioctl)
DECL|macro|DM_DEV_REMOVE
mdefine_line|#define DM_DEV_REMOVE    _IOWR(DM_IOCTL, DM_DEV_REMOVE_CMD, struct dm_ioctl)
DECL|macro|DM_DEV_RELOAD
mdefine_line|#define DM_DEV_RELOAD    _IOWR(DM_IOCTL, DM_DEV_RELOAD_CMD, struct dm_ioctl)
DECL|macro|DM_DEV_SUSPEND
mdefine_line|#define DM_DEV_SUSPEND   _IOWR(DM_IOCTL, DM_DEV_SUSPEND_CMD, struct dm_ioctl)
DECL|macro|DM_DEV_RENAME
mdefine_line|#define DM_DEV_RENAME    _IOWR(DM_IOCTL, DM_DEV_RENAME_CMD, struct dm_ioctl)
DECL|macro|DM_DEV_DEPS
mdefine_line|#define DM_DEV_DEPS      _IOWR(DM_IOCTL, DM_DEV_DEPS_CMD, struct dm_ioctl)
DECL|macro|DM_DEV_STATUS
mdefine_line|#define DM_DEV_STATUS    _IOWR(DM_IOCTL, DM_DEV_STATUS_CMD, struct dm_ioctl)
DECL|macro|DM_TARGET_STATUS
mdefine_line|#define DM_TARGET_STATUS _IOWR(DM_IOCTL, DM_TARGET_STATUS_CMD, struct dm_ioctl)
DECL|macro|DM_TARGET_WAIT
mdefine_line|#define DM_TARGET_WAIT   _IOWR(DM_IOCTL, DM_TARGET_WAIT_CMD, struct dm_ioctl)
DECL|macro|DM_VERSION_MAJOR
mdefine_line|#define DM_VERSION_MAJOR&t;1
DECL|macro|DM_VERSION_MINOR
mdefine_line|#define DM_VERSION_MINOR&t;0
DECL|macro|DM_VERSION_PATCHLEVEL
mdefine_line|#define DM_VERSION_PATCHLEVEL&t;6
DECL|macro|DM_VERSION_EXTRA
mdefine_line|#define DM_VERSION_EXTRA&t;&quot;-ioctl (2002-10-15)&quot;
multiline_comment|/* Status bits */
DECL|macro|DM_READONLY_FLAG
mdefine_line|#define DM_READONLY_FLAG&t;0x00000001
DECL|macro|DM_SUSPEND_FLAG
mdefine_line|#define DM_SUSPEND_FLAG&t;&t;0x00000002
DECL|macro|DM_EXISTS_FLAG
mdefine_line|#define DM_EXISTS_FLAG&t;&t;0x00000004
DECL|macro|DM_PERSISTENT_DEV_FLAG
mdefine_line|#define DM_PERSISTENT_DEV_FLAG&t;0x00000008
multiline_comment|/*&n; * Flag passed into ioctl STATUS command to get table information&n; * rather than current status.&n; */
DECL|macro|DM_STATUS_TABLE_FLAG
mdefine_line|#define DM_STATUS_TABLE_FLAG&t;0x00000010
macro_line|#endif&t;&t;&t;&t;/* _LINUX_DM_IOCTL_H */
eof
