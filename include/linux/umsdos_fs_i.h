macro_line|#ifndef UMSDOS_FS_I_H
DECL|macro|UMSDOS_FS_I_H
mdefine_line|#define UMSDOS_FS_I_H
macro_line|#ifndef _LINUX_TYPES_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/msdos_fs_i.h&gt;
macro_line|#include &lt;linux/pipe_fs_i.h&gt;
multiline_comment|/* #Specification: strategy / in memory inode&n; * Here is the information specific to the inode of the UMSDOS file&n; * system. This information is added to the end of the standard struct&n; * inode. Each file system has its own extension to struct inode,&n; * so do the umsdos file system.&n; * &n; * The strategy is to have the umsdos_inode_info as a superset of&n; * the msdos_inode_info, since most of the time the job is done&n; * by the msdos fs code.&n; * &n; * So we duplicate the msdos_inode_info, and add our own info at the&n; * end.&n; * &n; * The offset in this EMD file of the entry: pos&n; * &n; * For directory, we have dir_locking_info to help synchronise&n; * file creation and file lookup. See also msdos_fs_i.h for more &n; * information about msdos_inode_info.&n; * &n; * Special file and fifo do have an inode which correspond to an&n; * empty MSDOS file.&n; * &n; * symlink are processed mostly like regular file. The content is the&n; * link.&n; * &n; * The UMSDOS specific extension is placed after the union.&n; */
DECL|struct|dir_locking_info
r_struct
id|dir_locking_info
(brace
DECL|member|p
id|wait_queue_head_t
id|p
suffix:semicolon
DECL|member|looking
r_int
r_int
id|looking
suffix:semicolon
multiline_comment|/* How many process doing a lookup */
DECL|member|creating
r_int
r_int
id|creating
suffix:semicolon
multiline_comment|/* Is there any creation going on here&n;&t;&t;&t;&t; *  Only one at a time, although one&n;&t;&t;&t;&t; *  may recursively lock, so it is a counter&n;&t;&t;&t;&t; */
DECL|member|pid
r_int
id|pid
suffix:semicolon
multiline_comment|/* pid of the process owning the creation&n;&t;&t;&t;&t; * lock */
)brace
suffix:semicolon
DECL|struct|umsdos_inode_info
r_struct
id|umsdos_inode_info
(brace
DECL|member|msdos_info
r_struct
id|msdos_inode_info
id|msdos_info
suffix:semicolon
DECL|member|dir_info
r_struct
id|dir_locking_info
id|dir_info
suffix:semicolon
DECL|member|i_patched
r_int
id|i_patched
suffix:semicolon
multiline_comment|/* Inode has been patched */
DECL|member|i_is_hlink
r_int
id|i_is_hlink
suffix:semicolon
multiline_comment|/* Resolved hardlink inode? */
DECL|member|pos
id|off_t
id|pos
suffix:semicolon
multiline_comment|/* Entry offset in the emd_owner file */
)brace
suffix:semicolon
macro_line|#endif
eof
