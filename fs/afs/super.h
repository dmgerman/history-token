multiline_comment|/* super.h: AFS filesystem internal private data&n; *&n; * Copyright (c) 2002 Red Hat, Inc. All rights reserved.&n; *&n; * This software may be freely redistributed under the terms of the&n; * GNU General Public License.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Authors: David Woodhouse &lt;dwmw2@cambridge.redhat.com&gt;&n; *          David Howells &lt;dhowells@redhat.com&gt;&n; *&n; */
macro_line|#ifndef _LINUX_AFS_SUPER_H
DECL|macro|_LINUX_AFS_SUPER_H
mdefine_line|#define _LINUX_AFS_SUPER_H
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &quot;server.h&quot;
macro_line|#ifdef __KERNEL__
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * AFS superblock private data&n; * - there&squot;s one superblock per volume&n; */
DECL|struct|afs_super_info
r_struct
id|afs_super_info
(brace
DECL|member|volume
r_struct
id|afs_volume
op_star
id|volume
suffix:semicolon
multiline_comment|/* volume record */
DECL|member|rwparent
r_char
id|rwparent
suffix:semicolon
multiline_comment|/* T if parent is R/W AFS volume */
)brace
suffix:semicolon
DECL|function|AFS_FS_S
r_static
r_inline
r_struct
id|afs_super_info
op_star
id|AFS_FS_S
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_return
id|sb-&gt;s_fs_info
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_AFS_SUPER_H */
eof
