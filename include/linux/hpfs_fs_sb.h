macro_line|#ifndef _HPFS_FS_SB
DECL|macro|_HPFS_FS_SB
mdefine_line|#define _HPFS_FS_SB
DECL|struct|hpfs_sb_info
r_struct
id|hpfs_sb_info
(brace
DECL|member|sb_root
id|ino_t
id|sb_root
suffix:semicolon
multiline_comment|/* inode number of root dir */
DECL|member|sb_fs_size
r_int
id|sb_fs_size
suffix:semicolon
multiline_comment|/* file system size, sectors */
DECL|member|sb_bitmaps
r_int
id|sb_bitmaps
suffix:semicolon
multiline_comment|/* sector number of bitmap list */
DECL|member|sb_dirband_start
r_int
id|sb_dirband_start
suffix:semicolon
multiline_comment|/* directory band start sector */
DECL|member|sb_dirband_size
r_int
id|sb_dirband_size
suffix:semicolon
multiline_comment|/* directory band size, dnodes */
DECL|member|sb_dmap
r_int
id|sb_dmap
suffix:semicolon
multiline_comment|/* sector number of dnode bit map */
DECL|member|sb_n_free
r_int
id|sb_n_free
suffix:semicolon
multiline_comment|/* free blocks for statfs, or -1 */
DECL|member|sb_n_free_dnodes
r_int
id|sb_n_free_dnodes
suffix:semicolon
multiline_comment|/* free dnodes for statfs, or -1 */
DECL|member|sb_uid
id|uid_t
id|sb_uid
suffix:semicolon
multiline_comment|/* uid from mount options */
DECL|member|sb_gid
id|gid_t
id|sb_gid
suffix:semicolon
multiline_comment|/* gid from mount options */
DECL|member|sb_mode
id|umode_t
id|sb_mode
suffix:semicolon
multiline_comment|/* mode from mount options */
DECL|member|sb_conv
r_int
id|sb_conv
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* crlf-&gt;newline hackery */
DECL|member|sb_eas
r_int
id|sb_eas
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* eas: 0-ignore, 1-ro, 2-rw */
DECL|member|sb_err
r_int
id|sb_err
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* on errs: 0-cont, 1-ro, 2-panic */
DECL|member|sb_chk
r_int
id|sb_chk
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* checks: 0-no, 1-normal, 2-strict */
DECL|member|sb_lowercase
r_int
id|sb_lowercase
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* downcase filenames hackery */
DECL|member|sb_was_error
r_int
id|sb_was_error
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* there was an error, set dirty flag */
DECL|member|sb_chkdsk
r_int
id|sb_chkdsk
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* chkdsk: 0-no, 1-on errs, 2-allways */
DECL|member|sb_rd_fnode
r_int
id|sb_rd_fnode
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* read fnode 0-no 1-dirs 2-all */
DECL|member|sb_rd_inode
r_int
id|sb_rd_inode
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* lookup tells read_inode: 1-read fnode&n;&t;&t;&t;&t;&t;   2-don&squot;t read fnode, file&n;&t;&t;&t;&t;&t;   3-don&squot;t read fnode, direcotry */
DECL|member|sb_iget_q
id|wait_queue_head_t
id|sb_iget_q
suffix:semicolon
DECL|member|sb_cp_table
r_int
r_char
op_star
id|sb_cp_table
suffix:semicolon
multiline_comment|/* code page tables: */
multiline_comment|/* &t;128 bytes uppercasing table &amp; */
multiline_comment|/*&t;128 bytes lowercasing table */
DECL|member|sb_bmp_dir
r_int
op_star
id|sb_bmp_dir
suffix:semicolon
multiline_comment|/* main bitmap directory */
DECL|member|sb_c_bitmap
r_int
id|sb_c_bitmap
suffix:semicolon
multiline_comment|/* current bitmap */
DECL|member|hpfs_creation_de
r_struct
id|semaphore
id|hpfs_creation_de
suffix:semicolon
multiline_comment|/* when creating dirents, nobody else&n;&t;&t;&t;&t;&t;   can alloc blocks */
multiline_comment|/*unsigned sb_mounting : 1;*/
DECL|member|sb_timeshift
r_int
id|sb_timeshift
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
