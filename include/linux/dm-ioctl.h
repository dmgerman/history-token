multiline_comment|/*&n; * Copyright (C) 2001 - 2003 Sistina Software (UK) Limited.&n; * Copyright (C) 2004 Red Hat, Inc. All rights reserved.&n; *&n; * This file is released under the LGPL.&n; */
macro_line|#ifndef _LINUX_DM_IOCTL_V4_H
DECL|macro|_LINUX_DM_IOCTL_V4_H
mdefine_line|#define _LINUX_DM_IOCTL_V4_H
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|DM_DIR
mdefine_line|#define DM_DIR &quot;mapper&quot;&t;&t;/* Slashes not supported */
DECL|macro|DM_MAX_TYPE_NAME
mdefine_line|#define DM_MAX_TYPE_NAME 16
DECL|macro|DM_NAME_LEN
mdefine_line|#define DM_NAME_LEN 128
DECL|macro|DM_UUID_LEN
mdefine_line|#define DM_UUID_LEN 129
multiline_comment|/*&n; * A traditional ioctl interface for the device mapper.&n; *&n; * Each device can have two tables associated with it, an&n; * &squot;active&squot; table which is the one currently used by io passing&n; * through the device, and an &squot;inactive&squot; one which is a table&n; * that is being prepared as a replacement for the &squot;active&squot; one.&n; *&n; * DM_VERSION:&n; * Just get the version information for the ioctl interface.&n; *&n; * DM_REMOVE_ALL:&n; * Remove all dm devices, destroy all tables.  Only really used&n; * for debug.&n; *&n; * DM_LIST_DEVICES:&n; * Get a list of all the dm device names.&n; *&n; * DM_DEV_CREATE:&n; * Create a new device, neither the &squot;active&squot; or &squot;inactive&squot; table&n; * slots will be filled.  The device will be in suspended state&n; * after creation, however any io to the device will get errored&n; * since it will be out-of-bounds.&n; *&n; * DM_DEV_REMOVE:&n; * Remove a device, destroy any tables.&n; *&n; * DM_DEV_RENAME:&n; * Rename a device.&n; *&n; * DM_SUSPEND:&n; * This performs both suspend and resume, depending which flag is&n; * passed in.&n; * Suspend: This command will not return until all pending io to&n; * the device has completed.  Further io will be deferred until&n; * the device is resumed.&n; * Resume: It is no longer an error to issue this command on an&n; * unsuspended device.  If a table is present in the &squot;inactive&squot;&n; * slot, it will be moved to the active slot, then the old table&n; * from the active slot will be _destroyed_.  Finally the device&n; * is resumed.&n; *&n; * DM_DEV_STATUS:&n; * Retrieves the status for the table in the &squot;active&squot; slot.&n; *&n; * DM_DEV_WAIT:&n; * Wait for a significant event to occur to the device.  This&n; * could either be caused by an event triggered by one of the&n; * targets of the table in the &squot;active&squot; slot, or a table change.&n; *&n; * DM_TABLE_LOAD:&n; * Load a table into the &squot;inactive&squot; slot for the device.  The&n; * device does _not_ need to be suspended prior to this command.&n; *&n; * DM_TABLE_CLEAR:&n; * Destroy any table in the &squot;inactive&squot; slot (ie. abort).&n; *&n; * DM_TABLE_DEPS:&n; * Return a set of device dependencies for the &squot;active&squot; table.&n; *&n; * DM_TABLE_STATUS:&n; * Return the targets status for the &squot;active&squot; table.&n; *&n; * DM_TARGET_MSG:&n; * Pass a message string to the target at a specific offset of a device.&n; */
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
r_int32
id|open_count
suffix:semicolon
multiline_comment|/* out */
DECL|member|flags
r_uint32
id|flags
suffix:semicolon
multiline_comment|/* in/out */
DECL|member|event_nr
r_uint32
id|event_nr
suffix:semicolon
multiline_comment|/* in/out */
DECL|member|padding
r_uint32
id|padding
suffix:semicolon
DECL|member|dev
r_uint64
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
DECL|member|sector_start
r_uint64
id|sector_start
suffix:semicolon
DECL|member|length
r_uint64
id|length
suffix:semicolon
DECL|member|status
r_int32
id|status
suffix:semicolon
multiline_comment|/* used when reading from kernel only */
multiline_comment|/*&n;&t; * Location of the next dm_target_spec.&n;&t; * - When specifying targets on a DM_TABLE_LOAD command, this value is&n;&t; *   the number of bytes from the start of the &quot;current&quot; dm_target_spec&n;&t; *   to the start of the &quot;next&quot; dm_target_spec.&n;&t; * - When retrieving targets on a DM_TABLE_STATUS command, this value&n;&t; *   is the number of bytes from the start of the first dm_target_spec&n;&t; *   (that follows the dm_ioctl struct) to the start of the &quot;next&quot;&n;&t; *   dm_target_spec.&n;&t; */
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
multiline_comment|/* Array size */
DECL|member|padding
r_uint32
id|padding
suffix:semicolon
multiline_comment|/* unused */
DECL|member|dev
r_uint64
id|dev
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* out */
)brace
suffix:semicolon
multiline_comment|/*&n; * Used to get a list of all dm devices.&n; */
DECL|struct|dm_name_list
r_struct
id|dm_name_list
(brace
DECL|member|dev
r_uint64
id|dev
suffix:semicolon
DECL|member|next
r_uint32
id|next
suffix:semicolon
multiline_comment|/* offset to the next record from&n;&t;&t;&t;&t;   the _start_ of this */
DECL|member|name
r_char
id|name
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Used to retrieve the target versions&n; */
DECL|struct|dm_target_versions
r_struct
id|dm_target_versions
(brace
DECL|member|next
r_uint32
id|next
suffix:semicolon
DECL|member|version
r_uint32
id|version
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Used to pass message to a target&n; */
DECL|struct|dm_target_msg
r_struct
id|dm_target_msg
(brace
DECL|member|sector
r_uint64
id|sector
suffix:semicolon
multiline_comment|/* Device sector */
DECL|member|message
r_char
id|message
(braket
l_int|0
)braket
suffix:semicolon
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
DECL|enumerator|DM_LIST_DEVICES_CMD
id|DM_LIST_DEVICES_CMD
comma
multiline_comment|/* device level cmds */
DECL|enumerator|DM_DEV_CREATE_CMD
id|DM_DEV_CREATE_CMD
comma
DECL|enumerator|DM_DEV_REMOVE_CMD
id|DM_DEV_REMOVE_CMD
comma
DECL|enumerator|DM_DEV_RENAME_CMD
id|DM_DEV_RENAME_CMD
comma
DECL|enumerator|DM_DEV_SUSPEND_CMD
id|DM_DEV_SUSPEND_CMD
comma
DECL|enumerator|DM_DEV_STATUS_CMD
id|DM_DEV_STATUS_CMD
comma
DECL|enumerator|DM_DEV_WAIT_CMD
id|DM_DEV_WAIT_CMD
comma
multiline_comment|/* Table level cmds */
DECL|enumerator|DM_TABLE_LOAD_CMD
id|DM_TABLE_LOAD_CMD
comma
DECL|enumerator|DM_TABLE_CLEAR_CMD
id|DM_TABLE_CLEAR_CMD
comma
DECL|enumerator|DM_TABLE_DEPS_CMD
id|DM_TABLE_DEPS_CMD
comma
DECL|enumerator|DM_TABLE_STATUS_CMD
id|DM_TABLE_STATUS_CMD
comma
multiline_comment|/* Added later */
DECL|enumerator|DM_LIST_VERSIONS_CMD
id|DM_LIST_VERSIONS_CMD
comma
DECL|enumerator|DM_TARGET_MSG_CMD
id|DM_TARGET_MSG_CMD
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * The dm_ioctl struct passed into the ioctl is just the header&n; * on a larger chunk of memory.  On x86-64 and other&n; * architectures the dm-ioctl struct will be padded to an 8 byte&n; * boundary so the size will be different, which would change the&n; * ioctl code - yes I really messed up.  This hack forces these&n; * architectures to have the correct ioctl code.&n; */
macro_line|#ifdef CONFIG_COMPAT
DECL|typedef|ioctl_struct
r_typedef
r_char
id|ioctl_struct
(braket
l_int|308
)braket
suffix:semicolon
DECL|macro|DM_VERSION_32
mdefine_line|#define DM_VERSION_32       _IOWR(DM_IOCTL, DM_VERSION_CMD, ioctl_struct)
DECL|macro|DM_REMOVE_ALL_32
mdefine_line|#define DM_REMOVE_ALL_32    _IOWR(DM_IOCTL, DM_REMOVE_ALL_CMD, ioctl_struct)
DECL|macro|DM_LIST_DEVICES_32
mdefine_line|#define DM_LIST_DEVICES_32  _IOWR(DM_IOCTL, DM_LIST_DEVICES_CMD, ioctl_struct)
DECL|macro|DM_DEV_CREATE_32
mdefine_line|#define DM_DEV_CREATE_32    _IOWR(DM_IOCTL, DM_DEV_CREATE_CMD, ioctl_struct)
DECL|macro|DM_DEV_REMOVE_32
mdefine_line|#define DM_DEV_REMOVE_32    _IOWR(DM_IOCTL, DM_DEV_REMOVE_CMD, ioctl_struct)
DECL|macro|DM_DEV_RENAME_32
mdefine_line|#define DM_DEV_RENAME_32    _IOWR(DM_IOCTL, DM_DEV_RENAME_CMD, ioctl_struct)
DECL|macro|DM_DEV_SUSPEND_32
mdefine_line|#define DM_DEV_SUSPEND_32   _IOWR(DM_IOCTL, DM_DEV_SUSPEND_CMD, ioctl_struct)
DECL|macro|DM_DEV_STATUS_32
mdefine_line|#define DM_DEV_STATUS_32    _IOWR(DM_IOCTL, DM_DEV_STATUS_CMD, ioctl_struct)
DECL|macro|DM_DEV_WAIT_32
mdefine_line|#define DM_DEV_WAIT_32      _IOWR(DM_IOCTL, DM_DEV_WAIT_CMD, ioctl_struct)
DECL|macro|DM_TABLE_LOAD_32
mdefine_line|#define DM_TABLE_LOAD_32    _IOWR(DM_IOCTL, DM_TABLE_LOAD_CMD, ioctl_struct)
DECL|macro|DM_TABLE_CLEAR_32
mdefine_line|#define DM_TABLE_CLEAR_32   _IOWR(DM_IOCTL, DM_TABLE_CLEAR_CMD, ioctl_struct)
DECL|macro|DM_TABLE_DEPS_32
mdefine_line|#define DM_TABLE_DEPS_32    _IOWR(DM_IOCTL, DM_TABLE_DEPS_CMD, ioctl_struct)
DECL|macro|DM_TABLE_STATUS_32
mdefine_line|#define DM_TABLE_STATUS_32  _IOWR(DM_IOCTL, DM_TABLE_STATUS_CMD, ioctl_struct)
DECL|macro|DM_LIST_VERSIONS_32
mdefine_line|#define DM_LIST_VERSIONS_32 _IOWR(DM_IOCTL, DM_LIST_VERSIONS_CMD, ioctl_struct)
DECL|macro|DM_TARGET_MSG_32
mdefine_line|#define DM_TARGET_MSG_32    _IOWR(DM_IOCTL, DM_TARGET_MSG_CMD, ioctl_struct)
macro_line|#endif
DECL|macro|DM_IOCTL
mdefine_line|#define DM_IOCTL 0xfd
DECL|macro|DM_VERSION
mdefine_line|#define DM_VERSION       _IOWR(DM_IOCTL, DM_VERSION_CMD, struct dm_ioctl)
DECL|macro|DM_REMOVE_ALL
mdefine_line|#define DM_REMOVE_ALL    _IOWR(DM_IOCTL, DM_REMOVE_ALL_CMD, struct dm_ioctl)
DECL|macro|DM_LIST_DEVICES
mdefine_line|#define DM_LIST_DEVICES  _IOWR(DM_IOCTL, DM_LIST_DEVICES_CMD, struct dm_ioctl)
DECL|macro|DM_DEV_CREATE
mdefine_line|#define DM_DEV_CREATE    _IOWR(DM_IOCTL, DM_DEV_CREATE_CMD, struct dm_ioctl)
DECL|macro|DM_DEV_REMOVE
mdefine_line|#define DM_DEV_REMOVE    _IOWR(DM_IOCTL, DM_DEV_REMOVE_CMD, struct dm_ioctl)
DECL|macro|DM_DEV_RENAME
mdefine_line|#define DM_DEV_RENAME    _IOWR(DM_IOCTL, DM_DEV_RENAME_CMD, struct dm_ioctl)
DECL|macro|DM_DEV_SUSPEND
mdefine_line|#define DM_DEV_SUSPEND   _IOWR(DM_IOCTL, DM_DEV_SUSPEND_CMD, struct dm_ioctl)
DECL|macro|DM_DEV_STATUS
mdefine_line|#define DM_DEV_STATUS    _IOWR(DM_IOCTL, DM_DEV_STATUS_CMD, struct dm_ioctl)
DECL|macro|DM_DEV_WAIT
mdefine_line|#define DM_DEV_WAIT      _IOWR(DM_IOCTL, DM_DEV_WAIT_CMD, struct dm_ioctl)
DECL|macro|DM_TABLE_LOAD
mdefine_line|#define DM_TABLE_LOAD    _IOWR(DM_IOCTL, DM_TABLE_LOAD_CMD, struct dm_ioctl)
DECL|macro|DM_TABLE_CLEAR
mdefine_line|#define DM_TABLE_CLEAR   _IOWR(DM_IOCTL, DM_TABLE_CLEAR_CMD, struct dm_ioctl)
DECL|macro|DM_TABLE_DEPS
mdefine_line|#define DM_TABLE_DEPS    _IOWR(DM_IOCTL, DM_TABLE_DEPS_CMD, struct dm_ioctl)
DECL|macro|DM_TABLE_STATUS
mdefine_line|#define DM_TABLE_STATUS  _IOWR(DM_IOCTL, DM_TABLE_STATUS_CMD, struct dm_ioctl)
DECL|macro|DM_LIST_VERSIONS
mdefine_line|#define DM_LIST_VERSIONS _IOWR(DM_IOCTL, DM_LIST_VERSIONS_CMD, struct dm_ioctl)
DECL|macro|DM_TARGET_MSG
mdefine_line|#define DM_TARGET_MSG&t; _IOWR(DM_IOCTL, DM_TARGET_MSG_CMD, struct dm_ioctl)
DECL|macro|DM_VERSION_MAJOR
mdefine_line|#define DM_VERSION_MAJOR&t;4
DECL|macro|DM_VERSION_MINOR
mdefine_line|#define DM_VERSION_MINOR&t;3
DECL|macro|DM_VERSION_PATCHLEVEL
mdefine_line|#define DM_VERSION_PATCHLEVEL&t;0
DECL|macro|DM_VERSION_EXTRA
mdefine_line|#define DM_VERSION_EXTRA&t;&quot;-ioctl (2004-09-30)&quot;
multiline_comment|/* Status bits */
DECL|macro|DM_READONLY_FLAG
mdefine_line|#define DM_READONLY_FLAG&t;(1 &lt;&lt; 0) /* In/Out */
DECL|macro|DM_SUSPEND_FLAG
mdefine_line|#define DM_SUSPEND_FLAG&t;&t;(1 &lt;&lt; 1) /* In/Out */
DECL|macro|DM_PERSISTENT_DEV_FLAG
mdefine_line|#define DM_PERSISTENT_DEV_FLAG&t;(1 &lt;&lt; 3) /* In */
multiline_comment|/*&n; * Flag passed into ioctl STATUS command to get table information&n; * rather than current status.&n; */
DECL|macro|DM_STATUS_TABLE_FLAG
mdefine_line|#define DM_STATUS_TABLE_FLAG&t;(1 &lt;&lt; 4) /* In */
multiline_comment|/*&n; * Flags that indicate whether a table is present in either of&n; * the two table slots that a device has.&n; */
DECL|macro|DM_ACTIVE_PRESENT_FLAG
mdefine_line|#define DM_ACTIVE_PRESENT_FLAG   (1 &lt;&lt; 5) /* Out */
DECL|macro|DM_INACTIVE_PRESENT_FLAG
mdefine_line|#define DM_INACTIVE_PRESENT_FLAG (1 &lt;&lt; 6) /* Out */
multiline_comment|/*&n; * Indicates that the buffer passed in wasn&squot;t big enough for the&n; * results.&n; */
DECL|macro|DM_BUFFER_FULL_FLAG
mdefine_line|#define DM_BUFFER_FULL_FLAG&t;(1 &lt;&lt; 8) /* Out */
macro_line|#endif&t;&t;&t;&t;/* _LINUX_DM_IOCTL_H */
eof
