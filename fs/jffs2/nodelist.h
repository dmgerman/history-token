multiline_comment|/*&n; * JFFS2 -- Journalling Flash File System, Version 2.&n; *&n; * Copyright (C) 2001 Red Hat, Inc.&n; *&n; * Created by David Woodhouse &lt;dwmw2@cambridge.redhat.com&gt;&n; *&n; * The original JFFS, from which the design for JFFS2 was derived,&n; * was designed and implemented by Axis Communications AB.&n; *&n; * The contents of this file are subject to the Red Hat eCos Public&n; * License Version 1.1 (the &quot;Licence&quot;); you may not use this file&n; * except in compliance with the Licence.  You may obtain a copy of&n; * the Licence at http://www.redhat.com/&n; *&n; * Software distributed under the Licence is distributed on an &quot;AS IS&quot;&n; * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.&n; * See the Licence for the specific language governing rights and&n; * limitations under the Licence.&n; *&n; * The Original Code is JFFS2 - Journalling Flash File System, version 2&n; *&n; * Alternatively, the contents of this file may be used under the&n; * terms of the GNU General Public License version 2 (the &quot;GPL&quot;), in&n; * which case the provisions of the GPL are applicable instead of the&n; * above.  If you wish to allow the use of your version of this file&n; * only under the terms of the GPL and not to allow others to use your&n; * version of this file under the RHEPL, indicate your decision by&n; * deleting the provisions above and replace them with the notice and&n; * other provisions required by the GPL.  If you do not delete the&n; * provisions above, a recipient may use your version of this file&n; * under either the RHEPL or the GPL.&n; *&n; * $Id: nodelist.h,v 1.46.2.1 2002/02/23 14:04:44 dwmw2 Exp $&n; * + zlib_init calls from v1.65&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/jffs2_fs_sb.h&gt;
macro_line|#include &lt;linux/jffs2_fs_i.h&gt;
macro_line|#ifndef CONFIG_JFFS2_FS_DEBUG
DECL|macro|CONFIG_JFFS2_FS_DEBUG
mdefine_line|#define CONFIG_JFFS2_FS_DEBUG 2
macro_line|#endif
macro_line|#if CONFIG_JFFS2_FS_DEBUG &gt; 0
DECL|macro|D1
mdefine_line|#define D1(x) x
macro_line|#else
DECL|macro|D1
mdefine_line|#define D1(x)
macro_line|#endif
macro_line|#if CONFIG_JFFS2_FS_DEBUG &gt; 1
DECL|macro|D2
mdefine_line|#define D2(x) x
macro_line|#else
DECL|macro|D2
mdefine_line|#define D2(x)
macro_line|#endif
multiline_comment|/*&n;  This is all we need to keep in-core for each raw node during normal&n;  operation. As and when we do read_inode on a particular inode, we can&n;  scan the nodes which are listed for it and build up a proper map of &n;  which nodes are currently valid. JFFSv1 always used to keep that whole&n;  map in core for each inode.&n;*/
DECL|struct|jffs2_raw_node_ref
r_struct
id|jffs2_raw_node_ref
(brace
DECL|member|next_in_ino
r_struct
id|jffs2_raw_node_ref
op_star
id|next_in_ino
suffix:semicolon
multiline_comment|/* Points to the next raw_node_ref&n;&t;&t;for this inode. If this is the last, it points to the inode_cache&n;&t;&t;for this inode instead. The inode_cache will have NULL in the first&n;&t;&t;word so you know when you&squot;ve got there :) */
DECL|member|next_phys
r_struct
id|jffs2_raw_node_ref
op_star
id|next_phys
suffix:semicolon
singleline_comment|//&t;__u32 ino;
DECL|member|flash_offset
id|__u32
id|flash_offset
suffix:semicolon
DECL|member|totlen
id|__u32
id|totlen
suffix:semicolon
singleline_comment|//&t;__u16 nodetype;
multiline_comment|/* flash_offset &amp; 3 always has to be zero, because nodes are&n;&t;   always aligned at 4 bytes. So we have a couple of extra bits&n;&t;   to play with. So we set the least significant bit to 1 to&n;&t;   signify that the node is obsoleted by later nodes.&n;&t;*/
)brace
suffix:semicolon
multiline_comment|/* &n;   Used for keeping track of deletion nodes &amp;c, which can only be marked&n;   as obsolete when the node which they mark as deleted has actually been &n;   removed from the flash.&n;*/
DECL|struct|jffs2_raw_node_ref_list
r_struct
id|jffs2_raw_node_ref_list
(brace
DECL|member|rew
r_struct
id|jffs2_raw_node_ref
op_star
id|rew
suffix:semicolon
DECL|member|next
r_struct
id|jffs2_raw_node_ref_list
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* For each inode in the filesystem, we need to keep a record of&n;   nlink, because it would be a PITA to scan the whole directory tree&n;   at read_inode() time to calculate it, and to keep sufficient information&n;   in the raw_node_ref (basically both parent and child inode number for &n;   dirent nodes) would take more space than this does. We also keep&n;   a pointer to the first physical node which is part of this inode, too.&n;*/
DECL|struct|jffs2_inode_cache
r_struct
id|jffs2_inode_cache
(brace
DECL|member|scan
r_struct
id|jffs2_scan_info
op_star
id|scan
suffix:semicolon
multiline_comment|/* Used during scan to hold&n;&t;&t;temporary lists of nodes, and later must be set to&n;&t;&t;NULL to mark the end of the raw_node_ref-&gt;next_in_ino&n;&t;&t;chain. */
DECL|member|next
r_struct
id|jffs2_inode_cache
op_star
id|next
suffix:semicolon
DECL|member|nodes
r_struct
id|jffs2_raw_node_ref
op_star
id|nodes
suffix:semicolon
DECL|member|ino
id|__u32
id|ino
suffix:semicolon
DECL|member|nlink
r_int
id|nlink
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|jffs2_scan_info
r_struct
id|jffs2_scan_info
(brace
DECL|member|dents
r_struct
id|jffs2_full_dirent
op_star
id|dents
suffix:semicolon
DECL|member|tmpnodes
r_struct
id|jffs2_tmp_dnode_info
op_star
id|tmpnodes
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n;  Larger representation of a raw node, kept in-core only when the &n;  struct inode for this particular ino is instantiated.&n;*/
DECL|struct|jffs2_full_dnode
r_struct
id|jffs2_full_dnode
(brace
DECL|member|raw
r_struct
id|jffs2_raw_node_ref
op_star
id|raw
suffix:semicolon
DECL|member|ofs
id|__u32
id|ofs
suffix:semicolon
multiline_comment|/* Don&squot;t really need this, but optimisation */
DECL|member|size
id|__u32
id|size
suffix:semicolon
DECL|member|frags
id|__u32
id|frags
suffix:semicolon
multiline_comment|/* Number of fragments which currently refer&n;&t;&t;&t;to this node. When this reaches zero, &n;&t;&t;&t;the node is obsolete.&n;&t;&t;     */
)brace
suffix:semicolon
multiline_comment|/* &n;   Even larger representation of a raw node, kept in-core only while&n;   we&squot;re actually building up the original map of which nodes go where,&n;   in read_inode()&n;*/
DECL|struct|jffs2_tmp_dnode_info
r_struct
id|jffs2_tmp_dnode_info
(brace
DECL|member|next
r_struct
id|jffs2_tmp_dnode_info
op_star
id|next
suffix:semicolon
DECL|member|fn
r_struct
id|jffs2_full_dnode
op_star
id|fn
suffix:semicolon
DECL|member|version
id|__u32
id|version
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|jffs2_full_dirent
r_struct
id|jffs2_full_dirent
(brace
DECL|member|raw
r_struct
id|jffs2_raw_node_ref
op_star
id|raw
suffix:semicolon
DECL|member|next
r_struct
id|jffs2_full_dirent
op_star
id|next
suffix:semicolon
DECL|member|version
id|__u32
id|version
suffix:semicolon
DECL|member|ino
id|__u32
id|ino
suffix:semicolon
multiline_comment|/* == zero for unlink */
DECL|member|nhash
r_int
r_int
id|nhash
suffix:semicolon
DECL|member|type
r_int
r_char
id|type
suffix:semicolon
DECL|member|name
r_int
r_char
id|name
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n;  Fragments - used to build a map of which raw node to obtain &n;  data from for each part of the ino&n;*/
DECL|struct|jffs2_node_frag
r_struct
id|jffs2_node_frag
(brace
DECL|member|next
r_struct
id|jffs2_node_frag
op_star
id|next
suffix:semicolon
DECL|member|node
r_struct
id|jffs2_full_dnode
op_star
id|node
suffix:semicolon
multiline_comment|/* NULL for holes */
DECL|member|size
id|__u32
id|size
suffix:semicolon
DECL|member|ofs
id|__u32
id|ofs
suffix:semicolon
multiline_comment|/* Don&squot;t really need this, but optimisation */
DECL|member|node_ofs
id|__u32
id|node_ofs
suffix:semicolon
multiline_comment|/* offset within the physical node */
)brace
suffix:semicolon
DECL|struct|jffs2_eraseblock
r_struct
id|jffs2_eraseblock
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|bad_count
r_int
id|bad_count
suffix:semicolon
DECL|member|offset
id|__u32
id|offset
suffix:semicolon
multiline_comment|/* of this block in the MTD */
DECL|member|used_size
id|__u32
id|used_size
suffix:semicolon
DECL|member|dirty_size
id|__u32
id|dirty_size
suffix:semicolon
DECL|member|free_size
id|__u32
id|free_size
suffix:semicolon
multiline_comment|/* Note that sector_size - free_size&n;&t;&t;&t;&t;   is the address of the first free space */
DECL|member|first_node
r_struct
id|jffs2_raw_node_ref
op_star
id|first_node
suffix:semicolon
DECL|member|last_node
r_struct
id|jffs2_raw_node_ref
op_star
id|last_node
suffix:semicolon
DECL|member|gc_node
r_struct
id|jffs2_raw_node_ref
op_star
id|gc_node
suffix:semicolon
multiline_comment|/* Next node to be garbage collected */
multiline_comment|/* For deletia. When a dirent node in this eraseblock is&n;&t;   deleted by a node elsewhere, that other node can only &n;&t;   be marked as obsolete when this block is actually erased.&n;&t;   So we keep a list of the nodes to mark as obsolete when&n;&t;   the erase is completed.&n;&t;*/
singleline_comment|// MAYBE&t;struct jffs2_raw_node_ref_list *deletia;
)brace
suffix:semicolon
DECL|macro|ACCT_SANITY_CHECK
mdefine_line|#define ACCT_SANITY_CHECK(c, jeb) do { &bslash;&n;&t;if (jeb-&gt;used_size + jeb-&gt;dirty_size + jeb-&gt;free_size != c-&gt;sector_size) { &bslash;&n;&t;&t;printk(KERN_NOTICE &quot;Eeep. Space accounting for block at 0x%08x is screwed&bslash;n&quot;, jeb-&gt;offset); &bslash;&n;&t;&t;printk(KERN_NOTICE &quot;free 0x%08x + dirty 0x%08x + used %08x != total %08x&bslash;n&quot;, &bslash;&n;&t;&t;jeb-&gt;free_size, jeb-&gt;dirty_size, jeb-&gt;used_size, c-&gt;sector_size); &bslash;&n;&t;&t;BUG(); &bslash;&n;&t;} &bslash;&n;&t;if (c-&gt;used_size + c-&gt;dirty_size + c-&gt;free_size + c-&gt;erasing_size + c-&gt;bad_size != c-&gt;flash_size) { &bslash;&n;&t;&t;printk(KERN_NOTICE &quot;Eeep. Space accounting superblock info is screwed&bslash;n&quot;); &bslash;&n;&t;&t;printk(KERN_NOTICE &quot;free 0x%08x + dirty 0x%08x + used %08x + erasing %08x + bad %08x != total %08x&bslash;n&quot;, &bslash;&n;&t;&t;c-&gt;free_size, c-&gt;dirty_size, c-&gt;used_size, c-&gt;erasing_size, c-&gt;bad_size, c-&gt;flash_size); &bslash;&n;&t;&t;BUG(); &bslash;&n;&t;} &bslash;&n;} while(0)
DECL|macro|ACCT_PARANOIA_CHECK
mdefine_line|#define ACCT_PARANOIA_CHECK(jeb) do { &bslash;&n;&t;&t;__u32 my_used_size = 0; &bslash;&n;&t;&t;struct jffs2_raw_node_ref *ref2 = jeb-&gt;first_node; &bslash;&n;&t;&t;while (ref2) { &bslash;&n;&t;&t;&t;if (!(ref2-&gt;flash_offset &amp; 1)) &bslash;&n;&t;&t;&t;&t;my_used_size += ref2-&gt;totlen; &bslash;&n;&t;&t;&t;ref2 = ref2-&gt;next_phys; &bslash;&n;&t;&t;} &bslash;&n;&t;&t;if (my_used_size != jeb-&gt;used_size) { &bslash;&n;&t;&t;&t;printk(KERN_NOTICE &quot;Calculated used size %08x != stored used size %08x&bslash;n&quot;, my_used_size, jeb-&gt;used_size); &bslash;&n;&t;&t;&t;BUG(); &bslash;&n;&t;&t;} &bslash;&n;&t;} while(0)
DECL|macro|ALLOC_NORMAL
mdefine_line|#define ALLOC_NORMAL&t;0&t;/* Normal allocation */
DECL|macro|ALLOC_DELETION
mdefine_line|#define ALLOC_DELETION&t;1&t;/* Deletion node. Best to allow it */
DECL|macro|ALLOC_GC
mdefine_line|#define ALLOC_GC&t;2&t;/* Space requested for GC. Give it or die */
DECL|macro|JFFS2_RESERVED_BLOCKS_BASE
mdefine_line|#define JFFS2_RESERVED_BLOCKS_BASE 3&t;&t;&t;&t;&t;&t;/* Number of free blocks there must be before we... */
DECL|macro|JFFS2_RESERVED_BLOCKS_WRITE
mdefine_line|#define JFFS2_RESERVED_BLOCKS_WRITE (JFFS2_RESERVED_BLOCKS_BASE + 2)&t;&t;/* ... allow a normal filesystem write */
DECL|macro|JFFS2_RESERVED_BLOCKS_DELETION
mdefine_line|#define JFFS2_RESERVED_BLOCKS_DELETION (JFFS2_RESERVED_BLOCKS_BASE + 1)&t;&t;/* ... allow a normal filesystem deletion */
DECL|macro|JFFS2_RESERVED_BLOCKS_GCTRIGGER
mdefine_line|#define JFFS2_RESERVED_BLOCKS_GCTRIGGER (JFFS2_RESERVED_BLOCKS_BASE + 3)&t;/* ... wake up the GC thread */
DECL|macro|JFFS2_RESERVED_BLOCKS_GCBAD
mdefine_line|#define JFFS2_RESERVED_BLOCKS_GCBAD (JFFS2_RESERVED_BLOCKS_BASE + 1)&t;&t;/* ... pick a block from the bad_list to GC */
DECL|macro|JFFS2_RESERVED_BLOCKS_GCMERGE
mdefine_line|#define JFFS2_RESERVED_BLOCKS_GCMERGE (JFFS2_RESERVED_BLOCKS_BASE)&t;&t;/* ... merge pages when garbage collecting */
DECL|macro|PAD
mdefine_line|#define PAD(x) (((x)+3)&amp;~3)
DECL|function|jffs2_raw_ref_to_inum
r_static
r_inline
r_int
id|jffs2_raw_ref_to_inum
c_func
(paren
r_struct
id|jffs2_raw_node_ref
op_star
id|raw
)paren
(brace
r_while
c_loop
(paren
id|raw-&gt;next_in_ino
)paren
(brace
id|raw
op_assign
id|raw-&gt;next_in_ino
suffix:semicolon
)brace
r_return
(paren
(paren
r_struct
id|jffs2_inode_cache
op_star
)paren
id|raw
)paren
op_member_access_from_pointer
id|ino
suffix:semicolon
)brace
multiline_comment|/* nodelist.c */
id|D1
c_func
(paren
r_void
id|jffs2_print_frag_list
c_func
(paren
r_struct
id|jffs2_inode_info
op_star
id|f
)paren
)paren
suffix:semicolon
r_void
id|jffs2_add_fd_to_list
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_struct
id|jffs2_full_dirent
op_star
r_new
comma
r_struct
id|jffs2_full_dirent
op_star
op_star
id|list
)paren
suffix:semicolon
r_void
id|jffs2_add_tn_to_list
c_func
(paren
r_struct
id|jffs2_tmp_dnode_info
op_star
id|tn
comma
r_struct
id|jffs2_tmp_dnode_info
op_star
op_star
id|list
)paren
suffix:semicolon
r_int
id|jffs2_get_inode_nodes
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
id|ino_t
id|ino
comma
r_struct
id|jffs2_inode_info
op_star
id|f
comma
r_struct
id|jffs2_tmp_dnode_info
op_star
op_star
id|tnp
comma
r_struct
id|jffs2_full_dirent
op_star
op_star
id|fdp
comma
id|__u32
op_star
id|highest_version
comma
id|__u32
op_star
id|latest_mctime
comma
id|__u32
op_star
id|mctime_ver
)paren
suffix:semicolon
r_struct
id|jffs2_inode_cache
op_star
id|jffs2_get_ino_cache
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_int
id|ino
)paren
suffix:semicolon
r_void
id|jffs2_add_ino_cache
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_struct
id|jffs2_inode_cache
op_star
r_new
)paren
suffix:semicolon
r_void
id|jffs2_del_ino_cache
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_struct
id|jffs2_inode_cache
op_star
id|old
)paren
suffix:semicolon
r_void
id|jffs2_free_ino_caches
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
)paren
suffix:semicolon
r_void
id|jffs2_free_raw_node_refs
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
)paren
suffix:semicolon
multiline_comment|/* nodemgmt.c */
r_int
id|jffs2_reserve_space
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
id|__u32
id|minsize
comma
id|__u32
op_star
id|ofs
comma
id|__u32
op_star
id|len
comma
r_int
id|prio
)paren
suffix:semicolon
r_int
id|jffs2_reserve_space_gc
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
id|__u32
id|minsize
comma
id|__u32
op_star
id|ofs
comma
id|__u32
op_star
id|len
)paren
suffix:semicolon
r_int
id|jffs2_add_physical_node_ref
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_struct
id|jffs2_raw_node_ref
op_star
r_new
comma
id|__u32
id|len
comma
r_int
id|dirty
)paren
suffix:semicolon
r_void
id|jffs2_complete_reservation
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
)paren
suffix:semicolon
r_void
id|jffs2_mark_node_obsolete
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_struct
id|jffs2_raw_node_ref
op_star
id|raw
)paren
suffix:semicolon
multiline_comment|/* write.c */
r_struct
id|inode
op_star
id|jffs2_new_inode
(paren
r_struct
id|inode
op_star
id|dir_i
comma
r_int
id|mode
comma
r_struct
id|jffs2_raw_inode
op_star
id|ri
)paren
suffix:semicolon
r_struct
id|jffs2_full_dnode
op_star
id|jffs2_write_dnode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|jffs2_raw_inode
op_star
id|ri
comma
r_const
r_int
r_char
op_star
id|data
comma
id|__u32
id|datalen
comma
id|__u32
id|flash_ofs
comma
id|__u32
op_star
id|writelen
)paren
suffix:semicolon
r_struct
id|jffs2_full_dirent
op_star
id|jffs2_write_dirent
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|jffs2_raw_dirent
op_star
id|rd
comma
r_const
r_int
r_char
op_star
id|name
comma
id|__u32
id|namelen
comma
id|__u32
id|flash_ofs
comma
id|__u32
op_star
id|writelen
)paren
suffix:semicolon
multiline_comment|/* readinode.c */
r_void
id|jffs2_truncate_fraglist
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_struct
id|jffs2_node_frag
op_star
op_star
id|list
comma
id|__u32
id|size
)paren
suffix:semicolon
r_int
id|jffs2_add_full_dnode_to_fraglist
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_struct
id|jffs2_node_frag
op_star
op_star
id|list
comma
r_struct
id|jffs2_full_dnode
op_star
id|fn
)paren
suffix:semicolon
r_int
id|jffs2_add_full_dnode_to_inode
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_struct
id|jffs2_inode_info
op_star
id|f
comma
r_struct
id|jffs2_full_dnode
op_star
id|fn
)paren
suffix:semicolon
r_void
id|jffs2_read_inode
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_void
id|jffs2_clear_inode
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
multiline_comment|/* malloc.c */
r_void
id|jffs2_free_tmp_dnode_info_list
c_func
(paren
r_struct
id|jffs2_tmp_dnode_info
op_star
id|tn
)paren
suffix:semicolon
r_void
id|jffs2_free_full_dirent_list
c_func
(paren
r_struct
id|jffs2_full_dirent
op_star
id|fd
)paren
suffix:semicolon
r_int
id|jffs2_create_slab_caches
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|jffs2_destroy_slab_caches
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|jffs2_full_dirent
op_star
id|jffs2_alloc_full_dirent
c_func
(paren
r_int
id|namesize
)paren
suffix:semicolon
r_void
id|jffs2_free_full_dirent
c_func
(paren
r_struct
id|jffs2_full_dirent
op_star
)paren
suffix:semicolon
r_struct
id|jffs2_full_dnode
op_star
id|jffs2_alloc_full_dnode
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|jffs2_free_full_dnode
c_func
(paren
r_struct
id|jffs2_full_dnode
op_star
)paren
suffix:semicolon
r_struct
id|jffs2_raw_dirent
op_star
id|jffs2_alloc_raw_dirent
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|jffs2_free_raw_dirent
c_func
(paren
r_struct
id|jffs2_raw_dirent
op_star
)paren
suffix:semicolon
r_struct
id|jffs2_raw_inode
op_star
id|jffs2_alloc_raw_inode
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|jffs2_free_raw_inode
c_func
(paren
r_struct
id|jffs2_raw_inode
op_star
)paren
suffix:semicolon
r_struct
id|jffs2_tmp_dnode_info
op_star
id|jffs2_alloc_tmp_dnode_info
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|jffs2_free_tmp_dnode_info
c_func
(paren
r_struct
id|jffs2_tmp_dnode_info
op_star
)paren
suffix:semicolon
r_struct
id|jffs2_raw_node_ref
op_star
id|jffs2_alloc_raw_node_ref
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|jffs2_free_raw_node_ref
c_func
(paren
r_struct
id|jffs2_raw_node_ref
op_star
)paren
suffix:semicolon
r_struct
id|jffs2_node_frag
op_star
id|jffs2_alloc_node_frag
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|jffs2_free_node_frag
c_func
(paren
r_struct
id|jffs2_node_frag
op_star
)paren
suffix:semicolon
r_struct
id|jffs2_inode_cache
op_star
id|jffs2_alloc_inode_cache
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|jffs2_free_inode_cache
c_func
(paren
r_struct
id|jffs2_inode_cache
op_star
)paren
suffix:semicolon
multiline_comment|/* gc.c */
r_int
id|jffs2_garbage_collect_pass
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
)paren
suffix:semicolon
multiline_comment|/* background.c */
r_int
id|jffs2_start_garbage_collect_thread
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
)paren
suffix:semicolon
r_void
id|jffs2_stop_garbage_collect_thread
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
)paren
suffix:semicolon
r_void
id|jffs2_garbage_collect_trigger
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
)paren
suffix:semicolon
multiline_comment|/* dir.c */
r_extern
r_struct
id|file_operations
id|jffs2_dir_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|jffs2_dir_inode_operations
suffix:semicolon
multiline_comment|/* file.c */
r_extern
r_struct
id|file_operations
id|jffs2_file_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|jffs2_file_inode_operations
suffix:semicolon
r_extern
r_struct
id|address_space_operations
id|jffs2_file_address_operations
suffix:semicolon
r_int
id|jffs2_null_fsync
c_func
(paren
r_struct
id|file
op_star
comma
r_struct
id|dentry
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|jffs2_setattr
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|iattr
op_star
id|iattr
)paren
suffix:semicolon
r_int
id|jffs2_do_readpage_nolock
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|page
op_star
id|pg
)paren
suffix:semicolon
r_int
id|jffs2_do_readpage_unlock
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|page
op_star
id|pg
)paren
suffix:semicolon
r_int
id|jffs2_readpage
(paren
r_struct
id|file
op_star
comma
r_struct
id|page
op_star
)paren
suffix:semicolon
r_int
id|jffs2_prepare_write
(paren
r_struct
id|file
op_star
comma
r_struct
id|page
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_int
id|jffs2_commit_write
(paren
r_struct
id|file
op_star
comma
r_struct
id|page
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* ioctl.c */
r_int
id|jffs2_ioctl
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* read.c */
r_int
id|jffs2_read_dnode
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_struct
id|jffs2_full_dnode
op_star
id|fd
comma
r_int
r_char
op_star
id|buf
comma
r_int
id|ofs
comma
r_int
id|len
)paren
suffix:semicolon
multiline_comment|/* compr.c */
r_int
r_char
id|jffs2_compress
c_func
(paren
r_int
r_char
op_star
id|data_in
comma
r_int
r_char
op_star
id|cpage_out
comma
id|__u32
op_star
id|datalen
comma
id|__u32
op_star
id|cdatalen
)paren
suffix:semicolon
r_int
id|jffs2_decompress
c_func
(paren
r_int
r_char
id|comprtype
comma
r_int
r_char
op_star
id|cdata_in
comma
r_int
r_char
op_star
id|data_out
comma
id|__u32
id|cdatalen
comma
id|__u32
id|datalen
)paren
suffix:semicolon
multiline_comment|/* scan.c */
r_int
id|jffs2_scan_medium
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
)paren
suffix:semicolon
multiline_comment|/* build.c */
r_int
id|jffs2_build_filesystem
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
)paren
suffix:semicolon
multiline_comment|/* symlink.c */
r_extern
r_struct
id|inode_operations
id|jffs2_symlink_inode_operations
suffix:semicolon
multiline_comment|/* erase.c */
r_void
id|jffs2_erase_block
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_struct
id|jffs2_eraseblock
op_star
id|jeb
)paren
suffix:semicolon
r_void
id|jffs2_erase_pending_blocks
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
)paren
suffix:semicolon
r_void
id|jffs2_mark_erased_blocks
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
)paren
suffix:semicolon
r_void
id|jffs2_erase_pending_trigger
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
)paren
suffix:semicolon
multiline_comment|/* compr_zlib.c */
r_int
id|jffs2_zlib_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|jffs2_zlib_exit
c_func
(paren
r_void
)paren
suffix:semicolon
eof
