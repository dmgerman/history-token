multiline_comment|/*&n; * JFFS -- Journalling Flash File System, Linux implementation.&n; *&n; * Copyright (C) 1999, 2000  Axis Communications AB.&n; *&n; * Created by Finn Hakansson &lt;finn@axis.com&gt;.&n; *&n; * This is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * $Id: jffs.h,v 1.11 2000/08/04 12:46:34 dwmw2 Exp $&n; *&n; * Ported to Linux 2.3.x and MTD:&n; * Copyright (C) 2000  Alexander Larsson (alex@cendio.se), Cendio Systems AB&n; *&n; */
macro_line|#ifndef __LINUX_JFFS_H__
DECL|macro|__LINUX_JFFS_H__
mdefine_line|#define __LINUX_JFFS_H__
DECL|macro|JFFS_VERSION_STRING
mdefine_line|#define JFFS_VERSION_STRING &quot;1.0&quot;
multiline_comment|/* This is a magic number that is used as an identification number for&n;   this file system.  It is written to the super_block structure.  */
DECL|macro|JFFS_MAGIC_SB_BITMASK
mdefine_line|#define JFFS_MAGIC_SB_BITMASK 0x07c0  /* 1984 */
multiline_comment|/* This is a magic number that every on-flash raw inode begins with.  */
DECL|macro|JFFS_MAGIC_BITMASK
mdefine_line|#define JFFS_MAGIC_BITMASK 0x34383931 /* &quot;1984&quot; */
multiline_comment|/* These two bitmasks are the valid ones for the flash memories we have&n;   for the moment.  */
DECL|macro|JFFS_EMPTY_BITMASK
mdefine_line|#define JFFS_EMPTY_BITMASK 0xffffffff
DECL|macro|JFFS_DIRTY_BITMASK
mdefine_line|#define JFFS_DIRTY_BITMASK 0x00000000
multiline_comment|/* This is the inode number of the root node.  */
DECL|macro|JFFS_MIN_INO
mdefine_line|#define JFFS_MIN_INO 1
multiline_comment|/* How many slots in the file hash table should we have?  */
DECL|macro|JFFS_HASH_SIZE
mdefine_line|#define JFFS_HASH_SIZE 40
multiline_comment|/* Don&squot;t use more than 254 bytes as the maximum allowed length of a file&squot;s&n;   name due to errors that could occur during the scanning of the flash&n;   memory. In fact, a name length of 255 or 0xff, could be the result of&n;   an uncompleted write.  For instance, if a raw inode is written to the&n;   flash memory and there is a power lossage just before the length of&n;   the name is written, the length 255 would be interpreted as an illegal&n;   value.  */
DECL|macro|JFFS_MAX_NAME_LEN
mdefine_line|#define JFFS_MAX_NAME_LEN 254
multiline_comment|/* Commands for ioctl().  */
DECL|macro|JFFS_IOCTL_MAGIC
mdefine_line|#define JFFS_IOCTL_MAGIC &squot;t&squot;
DECL|macro|JFFS_PRINT_HASH
mdefine_line|#define JFFS_PRINT_HASH _IO(JFFS_IOCTL_MAGIC, 90)
DECL|macro|JFFS_PRINT_TREE
mdefine_line|#define JFFS_PRINT_TREE _IO(JFFS_IOCTL_MAGIC, 91)
DECL|macro|JFFS_GET_STATUS
mdefine_line|#define JFFS_GET_STATUS _IO(JFFS_IOCTL_MAGIC, 92)
multiline_comment|/* XXX: This is something that we should try to get rid of in the future.  */
DECL|macro|JFFS_MODIFY_INODE
mdefine_line|#define JFFS_MODIFY_INODE 0x01
DECL|macro|JFFS_MODIFY_NAME
mdefine_line|#define JFFS_MODIFY_NAME  0x02
DECL|macro|JFFS_MODIFY_DATA
mdefine_line|#define JFFS_MODIFY_DATA  0x04
DECL|macro|JFFS_MODIFY_EXIST
mdefine_line|#define JFFS_MODIFY_EXIST 0x08
r_struct
id|jffs_control
suffix:semicolon
multiline_comment|/* The JFFS raw inode structure: Used for storage on physical media.  */
multiline_comment|/* Perhaps the uid, gid, atime, mtime and ctime members should have&n;   more space due to future changes in the Linux kernel. Anyhow, since&n;   a user of this filesystem probably have to fix a large number of&n;   other things, we have decided to not be forward compatible.  */
DECL|struct|jffs_raw_inode
r_struct
id|jffs_raw_inode
(brace
DECL|member|magic
id|__u32
id|magic
suffix:semicolon
multiline_comment|/* A constant magic number.  */
DECL|member|ino
id|__u32
id|ino
suffix:semicolon
multiline_comment|/* Inode number.  */
DECL|member|pino
id|__u32
id|pino
suffix:semicolon
multiline_comment|/* Parent&squot;s inode number.  */
DECL|member|version
id|__u32
id|version
suffix:semicolon
multiline_comment|/* Version number.  */
DECL|member|mode
id|__u32
id|mode
suffix:semicolon
multiline_comment|/* The file&squot;s type or mode.  */
DECL|member|uid
id|__u16
id|uid
suffix:semicolon
multiline_comment|/* The file&squot;s owner.  */
DECL|member|gid
id|__u16
id|gid
suffix:semicolon
multiline_comment|/* The file&squot;s group.  */
DECL|member|atime
id|__u32
id|atime
suffix:semicolon
multiline_comment|/* Last access time.  */
DECL|member|mtime
id|__u32
id|mtime
suffix:semicolon
multiline_comment|/* Last modification time.  */
DECL|member|ctime
id|__u32
id|ctime
suffix:semicolon
multiline_comment|/* Creation time.  */
DECL|member|offset
id|__u32
id|offset
suffix:semicolon
multiline_comment|/* Where to begin to write.  */
DECL|member|dsize
id|__u32
id|dsize
suffix:semicolon
multiline_comment|/* Size of the node&squot;s data.  */
DECL|member|rsize
id|__u32
id|rsize
suffix:semicolon
multiline_comment|/* How much are going to be replaced?  */
DECL|member|nsize
id|__u8
id|nsize
suffix:semicolon
multiline_comment|/* Name length.  */
DECL|member|nlink
id|__u8
id|nlink
suffix:semicolon
multiline_comment|/* Number of links.  */
DECL|member|spare
id|__u8
id|spare
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* For future use.  */
DECL|member|rename
id|__u8
id|rename
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Rename to a name of an already existing file?  */
DECL|member|deleted
id|__u8
id|deleted
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Has this file been deleted?  */
DECL|member|accurate
id|__u8
id|accurate
suffix:semicolon
multiline_comment|/* The inode is obsolete if accurate == 0.  */
DECL|member|dchksum
id|__u32
id|dchksum
suffix:semicolon
multiline_comment|/* Checksum for the data.  */
DECL|member|nchksum
id|__u16
id|nchksum
suffix:semicolon
multiline_comment|/* Checksum for the name.  */
DECL|member|chksum
id|__u16
id|chksum
suffix:semicolon
multiline_comment|/* Checksum for the raw inode.  */
)brace
suffix:semicolon
multiline_comment|/* Define the offset of the accurate byte in struct jffs_raw_inode.  */
DECL|macro|JFFS_RAW_INODE_ACCURATE_OFFSET
mdefine_line|#define JFFS_RAW_INODE_ACCURATE_OFFSET (sizeof(struct jffs_raw_inode) &bslash;&n;&t;&t;&t;&t;&t;- 2 * sizeof(__u32) - sizeof(__u8))
multiline_comment|/* Define the offset of the chksum member in struct jffs_raw_inode.  */
DECL|macro|JFFS_RAW_INODE_CHKSUM_OFFSET
mdefine_line|#define JFFS_RAW_INODE_CHKSUM_OFFSET (sizeof(struct jffs_raw_inode) &bslash;&n;&t;&t;&t;&t;      - sizeof(__u16))
multiline_comment|/* Define the offset of the dchksum member in struct jffs_raw_inode.  */
DECL|macro|JFFS_RAW_INODE_DCHKSUM_OFFSET
mdefine_line|#define JFFS_RAW_INODE_DCHKSUM_OFFSET (sizeof(struct jffs_raw_inode)   &bslash;&n;&t;&t;&t;&t;       - sizeof(__u16) - sizeof(__u16) &bslash;&n;&t;&t;&t;&t;       - sizeof(__u32))
multiline_comment|/* The RAM representation of the node.  The names of pointers to&n;   jffs_nodes are very often just called `n&squot; in the source code.  */
DECL|struct|jffs_node
r_struct
id|jffs_node
(brace
DECL|member|ino
id|__u32
id|ino
suffix:semicolon
multiline_comment|/* Inode number.  */
DECL|member|version
id|__u32
id|version
suffix:semicolon
multiline_comment|/* Version number.  */
DECL|member|data_offset
id|__u32
id|data_offset
suffix:semicolon
multiline_comment|/* Logic location of the data to insert.  */
DECL|member|data_size
id|__u32
id|data_size
suffix:semicolon
multiline_comment|/* The amount of data this node inserts.  */
DECL|member|removed_size
id|__u32
id|removed_size
suffix:semicolon
multiline_comment|/* The amount of data that this node removes.  */
DECL|member|fm_offset
id|__u32
id|fm_offset
suffix:semicolon
multiline_comment|/* Physical location of the data in the actual&n;&t;&t;&t;       flash memory data chunk.  */
DECL|member|name_size
id|__u8
id|name_size
suffix:semicolon
multiline_comment|/* Size of the name.  */
DECL|member|fm
r_struct
id|jffs_fm
op_star
id|fm
suffix:semicolon
multiline_comment|/* Physical memory information.  */
DECL|member|version_prev
r_struct
id|jffs_node
op_star
id|version_prev
suffix:semicolon
DECL|member|version_next
r_struct
id|jffs_node
op_star
id|version_next
suffix:semicolon
DECL|member|range_prev
r_struct
id|jffs_node
op_star
id|range_prev
suffix:semicolon
DECL|member|range_next
r_struct
id|jffs_node
op_star
id|range_next
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The RAM representation of a file (plain files, directories,&n;   links, etc.).  Pointers to jffs_files are normally named `f&squot;&n;   in the JFFS source code.  */
DECL|struct|jffs_file
r_struct
id|jffs_file
(brace
DECL|member|ino
id|__u32
id|ino
suffix:semicolon
multiline_comment|/* Inode number.  */
DECL|member|pino
id|__u32
id|pino
suffix:semicolon
multiline_comment|/* Parent&squot;s inode number.  */
DECL|member|mode
id|__u32
id|mode
suffix:semicolon
multiline_comment|/* file_type, mode  */
DECL|member|uid
id|__u16
id|uid
suffix:semicolon
multiline_comment|/* owner  */
DECL|member|gid
id|__u16
id|gid
suffix:semicolon
multiline_comment|/* group  */
DECL|member|atime
id|__u32
id|atime
suffix:semicolon
multiline_comment|/* Last access time.  */
DECL|member|mtime
id|__u32
id|mtime
suffix:semicolon
multiline_comment|/* Last modification time.  */
DECL|member|ctime
id|__u32
id|ctime
suffix:semicolon
multiline_comment|/* Creation time.  */
DECL|member|nsize
id|__u8
id|nsize
suffix:semicolon
multiline_comment|/* Name length.  */
DECL|member|nlink
id|__u8
id|nlink
suffix:semicolon
multiline_comment|/* Number of links.  */
DECL|member|deleted
id|__u8
id|deleted
suffix:semicolon
multiline_comment|/* Has this file been deleted?  */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* The name of this file; NULL-terminated.  */
DECL|member|size
id|__u32
id|size
suffix:semicolon
multiline_comment|/* The total size of the file&squot;s data.  */
DECL|member|highest_version
id|__u32
id|highest_version
suffix:semicolon
multiline_comment|/* The highest version number of this file.  */
DECL|member|c
r_struct
id|jffs_control
op_star
id|c
suffix:semicolon
DECL|member|parent
r_struct
id|jffs_file
op_star
id|parent
suffix:semicolon
multiline_comment|/* Reference to the parent directory.  */
DECL|member|children
r_struct
id|jffs_file
op_star
id|children
suffix:semicolon
multiline_comment|/* Always NULL for plain files.  */
DECL|member|sibling_prev
r_struct
id|jffs_file
op_star
id|sibling_prev
suffix:semicolon
multiline_comment|/* Siblings in the same directory.  */
DECL|member|sibling_next
r_struct
id|jffs_file
op_star
id|sibling_next
suffix:semicolon
DECL|member|hash
r_struct
id|list_head
id|hash
suffix:semicolon
multiline_comment|/* hash list.  */
DECL|member|range_head
r_struct
id|jffs_node
op_star
id|range_head
suffix:semicolon
multiline_comment|/* The final data.  */
DECL|member|range_tail
r_struct
id|jffs_node
op_star
id|range_tail
suffix:semicolon
multiline_comment|/* The first data.  */
DECL|member|version_head
r_struct
id|jffs_node
op_star
id|version_head
suffix:semicolon
multiline_comment|/* The youngest node.  */
DECL|member|version_tail
r_struct
id|jffs_node
op_star
id|version_tail
suffix:semicolon
multiline_comment|/* The oldest node.  */
)brace
suffix:semicolon
multiline_comment|/* This is just a definition of a simple list used for keeping track of&n;   files deleted due to a rename.  This list is only used during the&n;   mounting of the file system and only if there have been rename operations&n;   earlier.  */
DECL|struct|jffs_delete_list
r_struct
id|jffs_delete_list
(brace
DECL|member|ino
id|__u32
id|ino
suffix:semicolon
DECL|member|next
r_struct
id|jffs_delete_list
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* A struct for the overall file system control.  Pointers to&n;   jffs_control structs are named `c&squot; in the source code.  */
DECL|struct|jffs_control
r_struct
id|jffs_control
(brace
DECL|member|sb
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
multiline_comment|/* Reference to the VFS super block.  */
DECL|member|root
r_struct
id|jffs_file
op_star
id|root
suffix:semicolon
multiline_comment|/* The root directory file.  */
DECL|member|hash
r_struct
id|list_head
op_star
id|hash
suffix:semicolon
multiline_comment|/* Hash table for finding files by ino.  */
DECL|member|fmc
r_struct
id|jffs_fmcontrol
op_star
id|fmc
suffix:semicolon
multiline_comment|/* Flash memory control structure.  */
DECL|member|hash_len
id|__u32
id|hash_len
suffix:semicolon
multiline_comment|/* The size of the hash table.  */
DECL|member|next_ino
id|__u32
id|next_ino
suffix:semicolon
multiline_comment|/* Next inode number to use for new files.  */
DECL|member|building_fs
id|__u16
id|building_fs
suffix:semicolon
multiline_comment|/* Is the file system being built right now?  */
DECL|member|delete_list
r_struct
id|jffs_delete_list
op_star
id|delete_list
suffix:semicolon
multiline_comment|/* Track deleted files.  */
DECL|member|thread_pid
id|pid_t
id|thread_pid
suffix:semicolon
multiline_comment|/* GC thread&squot;s PID */
DECL|member|gc_task
r_struct
id|task_struct
op_star
id|gc_task
suffix:semicolon
multiline_comment|/* GC task struct */
DECL|member|gc_thread_sem
r_struct
id|semaphore
id|gc_thread_sem
suffix:semicolon
multiline_comment|/* GC thread exit mutex */
DECL|member|gc_minfree_threshold
id|__u32
id|gc_minfree_threshold
suffix:semicolon
multiline_comment|/* GC trigger thresholds */
DECL|member|gc_maxdirty_threshold
id|__u32
id|gc_maxdirty_threshold
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Used to inform about flash status.  */
DECL|struct|jffs_flash_status
r_struct
id|jffs_flash_status
(brace
DECL|member|size
id|__u32
id|size
suffix:semicolon
DECL|member|used
id|__u32
id|used
suffix:semicolon
DECL|member|dirty
id|__u32
id|dirty
suffix:semicolon
DECL|member|begin
id|__u32
id|begin
suffix:semicolon
DECL|member|end
id|__u32
id|end
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* This stuff could be used for finding memory leaks.  */
DECL|macro|JFFS_MEMORY_DEBUG
mdefine_line|#define JFFS_MEMORY_DEBUG 0
macro_line|#if defined(JFFS_MEMORY_DEBUG) &amp;&amp; JFFS_MEMORY_DEBUG
r_extern
r_int
id|no_jffs_file
suffix:semicolon
r_extern
r_int
id|no_jffs_node
suffix:semicolon
r_extern
r_int
id|no_jffs_control
suffix:semicolon
r_extern
r_int
id|no_jffs_raw_inode
suffix:semicolon
r_extern
r_int
id|no_jffs_node_ref
suffix:semicolon
r_extern
r_int
id|no_jffs_fm
suffix:semicolon
r_extern
r_int
id|no_jffs_fmcontrol
suffix:semicolon
r_extern
r_int
id|no_hash
suffix:semicolon
r_extern
r_int
id|no_name
suffix:semicolon
DECL|macro|DJM
mdefine_line|#define DJM(x) x
macro_line|#else
DECL|macro|DJM
mdefine_line|#define DJM(x)
macro_line|#endif
macro_line|#endif /* __LINUX_JFFS_H__ */
eof
