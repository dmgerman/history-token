multiline_comment|/*&n;   md_u.h : user &lt;=&gt; kernel API between Linux raidtools and RAID drivers&n;          Copyright (C) 1998 Ingo Molnar&n;&t;  &n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2, or (at your option)&n;   any later version.&n;   &n;   You should have received a copy of the GNU General Public License&n;   (for example /usr/src/linux/COPYING); if not, write to the Free&n;   Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  &n;*/
macro_line|#ifndef _MD_U_H
DECL|macro|_MD_U_H
mdefine_line|#define _MD_U_H
multiline_comment|/* ioctls */
multiline_comment|/* status */
DECL|macro|RAID_VERSION
mdefine_line|#define RAID_VERSION&t;&t;_IOR (MD_MAJOR, 0x10, mdu_version_t)
DECL|macro|GET_ARRAY_INFO
mdefine_line|#define GET_ARRAY_INFO&t;&t;_IOR (MD_MAJOR, 0x11, mdu_array_info_t)
DECL|macro|GET_DISK_INFO
mdefine_line|#define GET_DISK_INFO&t;&t;_IOR (MD_MAJOR, 0x12, mdu_disk_info_t)
DECL|macro|PRINT_RAID_DEBUG
mdefine_line|#define PRINT_RAID_DEBUG&t;_IO (MD_MAJOR, 0x13)
DECL|macro|RAID_AUTORUN
mdefine_line|#define RAID_AUTORUN&t;&t;_IO (MD_MAJOR, 0x14)
multiline_comment|/* configuration */
DECL|macro|CLEAR_ARRAY
mdefine_line|#define CLEAR_ARRAY&t;&t;_IO (MD_MAJOR, 0x20)
DECL|macro|ADD_NEW_DISK
mdefine_line|#define ADD_NEW_DISK&t;&t;_IOW (MD_MAJOR, 0x21, mdu_disk_info_t)
DECL|macro|HOT_REMOVE_DISK
mdefine_line|#define HOT_REMOVE_DISK&t;&t;_IO (MD_MAJOR, 0x22)
DECL|macro|SET_ARRAY_INFO
mdefine_line|#define SET_ARRAY_INFO&t;&t;_IOW (MD_MAJOR, 0x23, mdu_array_info_t)
DECL|macro|SET_DISK_INFO
mdefine_line|#define SET_DISK_INFO&t;&t;_IO (MD_MAJOR, 0x24)
DECL|macro|WRITE_RAID_INFO
mdefine_line|#define WRITE_RAID_INFO&t;&t;_IO (MD_MAJOR, 0x25)
DECL|macro|UNPROTECT_ARRAY
mdefine_line|#define UNPROTECT_ARRAY&t;&t;_IO (MD_MAJOR, 0x26)
DECL|macro|PROTECT_ARRAY
mdefine_line|#define PROTECT_ARRAY&t;&t;_IO (MD_MAJOR, 0x27)
DECL|macro|HOT_ADD_DISK
mdefine_line|#define HOT_ADD_DISK&t;&t;_IO (MD_MAJOR, 0x28)
DECL|macro|SET_DISK_FAULTY
mdefine_line|#define SET_DISK_FAULTY&t;&t;_IO (MD_MAJOR, 0x29)
DECL|macro|HOT_GENERATE_ERROR
mdefine_line|#define HOT_GENERATE_ERROR&t;_IO (MD_MAJOR, 0x2a)
multiline_comment|/* usage */
DECL|macro|RUN_ARRAY
mdefine_line|#define RUN_ARRAY&t;&t;_IOW (MD_MAJOR, 0x30, mdu_param_t)
DECL|macro|START_ARRAY
mdefine_line|#define START_ARRAY&t;&t;_IO (MD_MAJOR, 0x31)
DECL|macro|STOP_ARRAY
mdefine_line|#define STOP_ARRAY&t;&t;_IO (MD_MAJOR, 0x32)
DECL|macro|STOP_ARRAY_RO
mdefine_line|#define STOP_ARRAY_RO&t;&t;_IO (MD_MAJOR, 0x33)
DECL|macro|RESTART_ARRAY_RW
mdefine_line|#define RESTART_ARRAY_RW&t;_IO (MD_MAJOR, 0x34)
DECL|struct|mdu_version_s
r_typedef
r_struct
id|mdu_version_s
(brace
DECL|member|major
r_int
id|major
suffix:semicolon
DECL|member|minor
r_int
id|minor
suffix:semicolon
DECL|member|patchlevel
r_int
id|patchlevel
suffix:semicolon
DECL|typedef|mdu_version_t
)brace
id|mdu_version_t
suffix:semicolon
DECL|struct|mdu_array_info_s
r_typedef
r_struct
id|mdu_array_info_s
(brace
multiline_comment|/*&n;&t; * Generic constant information&n;&t; */
DECL|member|major_version
r_int
id|major_version
suffix:semicolon
DECL|member|minor_version
r_int
id|minor_version
suffix:semicolon
DECL|member|patch_version
r_int
id|patch_version
suffix:semicolon
DECL|member|ctime
r_int
id|ctime
suffix:semicolon
DECL|member|level
r_int
id|level
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|nr_disks
r_int
id|nr_disks
suffix:semicolon
DECL|member|raid_disks
r_int
id|raid_disks
suffix:semicolon
DECL|member|md_minor
r_int
id|md_minor
suffix:semicolon
DECL|member|not_persistent
r_int
id|not_persistent
suffix:semicolon
multiline_comment|/*&n;&t; * Generic state information&n;&t; */
DECL|member|utime
r_int
id|utime
suffix:semicolon
multiline_comment|/*  0 Superblock update time&t;&t;      */
DECL|member|state
r_int
id|state
suffix:semicolon
multiline_comment|/*  1 State bits (clean, ...)&t;&t;      */
DECL|member|active_disks
r_int
id|active_disks
suffix:semicolon
multiline_comment|/*  2 Number of currently active disks&t;      */
DECL|member|working_disks
r_int
id|working_disks
suffix:semicolon
multiline_comment|/*  3 Number of working disks&t;&t;      */
DECL|member|failed_disks
r_int
id|failed_disks
suffix:semicolon
multiline_comment|/*  4 Number of failed disks&t;&t;      */
DECL|member|spare_disks
r_int
id|spare_disks
suffix:semicolon
multiline_comment|/*  5 Number of spare disks&t;&t;      */
multiline_comment|/*&n;&t; * Personality information&n;&t; */
DECL|member|layout
r_int
id|layout
suffix:semicolon
multiline_comment|/*  0 the array&squot;s physical layout&t;      */
DECL|member|chunk_size
r_int
id|chunk_size
suffix:semicolon
multiline_comment|/*  1 chunk size in bytes&t;&t;      */
DECL|typedef|mdu_array_info_t
)brace
id|mdu_array_info_t
suffix:semicolon
DECL|struct|mdu_disk_info_s
r_typedef
r_struct
id|mdu_disk_info_s
(brace
multiline_comment|/*&n;&t; * configuration/status of one particular disk&n;&t; */
DECL|member|number
r_int
id|number
suffix:semicolon
DECL|member|major
r_int
id|major
suffix:semicolon
DECL|member|minor
r_int
id|minor
suffix:semicolon
DECL|member|raid_disk
r_int
id|raid_disk
suffix:semicolon
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|typedef|mdu_disk_info_t
)brace
id|mdu_disk_info_t
suffix:semicolon
DECL|struct|mdu_start_info_s
r_typedef
r_struct
id|mdu_start_info_s
(brace
multiline_comment|/*&n;&t; * configuration/status of one particular disk&n;&t; */
DECL|member|major
r_int
id|major
suffix:semicolon
DECL|member|minor
r_int
id|minor
suffix:semicolon
DECL|member|raid_disk
r_int
id|raid_disk
suffix:semicolon
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|typedef|mdu_start_info_t
)brace
id|mdu_start_info_t
suffix:semicolon
DECL|struct|mdu_param_s
r_typedef
r_struct
id|mdu_param_s
(brace
DECL|member|personality
r_int
id|personality
suffix:semicolon
multiline_comment|/* 1,2,3,4 */
DECL|member|chunk_size
r_int
id|chunk_size
suffix:semicolon
multiline_comment|/* in bytes */
DECL|member|max_fault
r_int
id|max_fault
suffix:semicolon
multiline_comment|/* unused for now */
DECL|typedef|mdu_param_t
)brace
id|mdu_param_t
suffix:semicolon
macro_line|#endif 
eof
