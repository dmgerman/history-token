macro_line|#ifndef _MSDOS_FS_SB
DECL|macro|_MSDOS_FS_SB
mdefine_line|#define _MSDOS_FS_SB
multiline_comment|/*&n; * MS-DOS file system in-core superblock data&n; */
DECL|struct|fat_mount_options
r_struct
id|fat_mount_options
(brace
DECL|member|fs_uid
id|uid_t
id|fs_uid
suffix:semicolon
DECL|member|fs_gid
id|gid_t
id|fs_gid
suffix:semicolon
DECL|member|fs_fmask
r_int
r_int
id|fs_fmask
suffix:semicolon
DECL|member|fs_dmask
r_int
r_int
id|fs_dmask
suffix:semicolon
DECL|member|codepage
r_int
r_int
id|codepage
suffix:semicolon
multiline_comment|/* Codepage for shortname conversions */
DECL|member|iocharset
r_char
op_star
id|iocharset
suffix:semicolon
multiline_comment|/* Charset used for filename input/display */
DECL|member|shortname
r_int
r_int
id|shortname
suffix:semicolon
multiline_comment|/* flags for shortname display/create rule */
DECL|member|name_check
r_int
r_char
id|name_check
suffix:semicolon
multiline_comment|/* r = relaxed, n = normal, s = strict */
DECL|member|quiet
r_int
id|quiet
suffix:colon
l_int|1
comma
multiline_comment|/* set = fake successful chmods and chowns */
DECL|member|showexec
id|showexec
suffix:colon
l_int|1
comma
multiline_comment|/* set = only set x bit for com/exe/bat */
DECL|member|sys_immutable
id|sys_immutable
suffix:colon
l_int|1
comma
multiline_comment|/* set = system files are immutable */
DECL|member|dotsOK
id|dotsOK
suffix:colon
l_int|1
comma
multiline_comment|/* set = hidden and system files are named &squot;.filename&squot; */
DECL|member|isvfat
id|isvfat
suffix:colon
l_int|1
comma
multiline_comment|/* 0=no vfat long filename support, 1=vfat support */
DECL|member|utf8
id|utf8
suffix:colon
l_int|1
comma
multiline_comment|/* Use of UTF8 character set (Default) */
DECL|member|unicode_xlate
id|unicode_xlate
suffix:colon
l_int|1
comma
multiline_comment|/* create escape sequences for unhandled Unicode */
DECL|member|numtail
id|numtail
suffix:colon
l_int|1
comma
multiline_comment|/* Does first alias have a numeric &squot;~1&squot; type tail? */
DECL|member|atari
id|atari
suffix:colon
l_int|1
comma
multiline_comment|/* Use Atari GEMDOS variation of MS-DOS fs */
DECL|member|nocase
id|nocase
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Does this need case conversion? 0=need case conversion*/
)brace
suffix:semicolon
DECL|macro|FAT_CACHE_NR
mdefine_line|#define FAT_CACHE_NR&t;8 /* number of FAT cache */
DECL|struct|fat_cache
r_struct
id|fat_cache
(brace
DECL|member|start_cluster
r_int
id|start_cluster
suffix:semicolon
multiline_comment|/* first cluster of the chain. */
DECL|member|file_cluster
r_int
id|file_cluster
suffix:semicolon
multiline_comment|/* cluster number in the file. */
DECL|member|disk_cluster
r_int
id|disk_cluster
suffix:semicolon
multiline_comment|/* cluster number on disk. */
DECL|member|next
r_struct
id|fat_cache
op_star
id|next
suffix:semicolon
multiline_comment|/* next cache entry */
)brace
suffix:semicolon
DECL|struct|msdos_sb_info
r_struct
id|msdos_sb_info
(brace
DECL|member|cluster_size
r_int
r_int
id|cluster_size
suffix:semicolon
multiline_comment|/* sectors/cluster */
DECL|member|cluster_bits
r_int
r_int
id|cluster_bits
suffix:semicolon
multiline_comment|/* sectors/cluster */
DECL|member|fats
DECL|member|fat_bits
r_int
r_char
id|fats
comma
id|fat_bits
suffix:semicolon
multiline_comment|/* number of FATs, FAT bits (12 or 16) */
DECL|member|fat_start
r_int
r_int
id|fat_start
suffix:semicolon
DECL|member|fat_length
r_int
r_int
id|fat_length
suffix:semicolon
multiline_comment|/* FAT start &amp; length (sec.) */
DECL|member|dir_start
r_int
r_int
id|dir_start
suffix:semicolon
DECL|member|dir_entries
r_int
r_int
id|dir_entries
suffix:semicolon
multiline_comment|/* root dir start &amp; entries */
DECL|member|data_start
r_int
r_int
id|data_start
suffix:semicolon
multiline_comment|/* first data sector */
DECL|member|clusters
r_int
r_int
id|clusters
suffix:semicolon
multiline_comment|/* number of clusters */
DECL|member|root_cluster
r_int
r_int
id|root_cluster
suffix:semicolon
multiline_comment|/* first cluster of the root directory */
DECL|member|fsinfo_sector
r_int
r_int
id|fsinfo_sector
suffix:semicolon
multiline_comment|/* FAT32 fsinfo offset from start of disk */
DECL|member|fat_lock
r_struct
id|semaphore
id|fat_lock
suffix:semicolon
DECL|member|prev_free
r_int
id|prev_free
suffix:semicolon
multiline_comment|/* previously returned free cluster number */
DECL|member|free_clusters
r_int
id|free_clusters
suffix:semicolon
multiline_comment|/* -1 if undefined */
DECL|member|options
r_struct
id|fat_mount_options
id|options
suffix:semicolon
DECL|member|nls_disk
r_struct
id|nls_table
op_star
id|nls_disk
suffix:semicolon
multiline_comment|/* Codepage used on disk */
DECL|member|nls_io
r_struct
id|nls_table
op_star
id|nls_io
suffix:semicolon
multiline_comment|/* Charset used for input and display */
DECL|member|dir_ops
r_void
op_star
id|dir_ops
suffix:semicolon
multiline_comment|/* Opaque; default directory operations */
DECL|member|dir_per_block
r_int
id|dir_per_block
suffix:semicolon
multiline_comment|/* dir entries per block */
DECL|member|dir_per_block_bits
r_int
id|dir_per_block_bits
suffix:semicolon
multiline_comment|/* log2(dir_per_block) */
DECL|member|cache_lock
id|spinlock_t
id|cache_lock
suffix:semicolon
DECL|member|cache_array
DECL|member|cache
r_struct
id|fat_cache
id|cache_array
(braket
id|FAT_CACHE_NR
)braket
comma
op_star
id|cache
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
