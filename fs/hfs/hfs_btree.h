multiline_comment|/*&n; * linux/fs/hfs/hfs_btree.h&n; *&n; * Copyright (C) 1995-1997  Paul H. Hargrove&n; * This file may be distributed under the terms of the GNU General Public License.&n; *&n; * This file contains the declarations of the private B-tree&n; * structures and functions.&n; *&n; * &quot;XXX&quot; in a comment is a note to myself to consider changing something.&n; */
macro_line|#ifndef _HFS_BTREE_H
DECL|macro|_HFS_BTREE_H
mdefine_line|#define _HFS_BTREE_H
macro_line|#include &quot;hfs.h&quot;
multiline_comment|/*================ Variable-like macros ================*/
multiline_comment|/* The stickiness of a (struct hfs_bnode) */
DECL|macro|HFS_NOT_STICKY
mdefine_line|#define HFS_NOT_STICKY&t;0
DECL|macro|HFS_STICKY
mdefine_line|#define HFS_STICKY&t;1
multiline_comment|/* The number of hash buckets in a B-tree&squot;s bnode cache */
DECL|macro|HFS_CACHELEN
mdefine_line|#define HFS_CACHELEN&t;17&t;/* primes are best? */
multiline_comment|/*&n; * Legal values for the &squot;ndType&squot; field of a (struct NodeDescriptor)&n; *&n; * Reference: _Inside Macintosh: Files_ p. 2-65&n; */
DECL|macro|ndIndxNode
mdefine_line|#define ndIndxNode&t;0x00&t;/* An internal (index) node */
DECL|macro|ndHdrNode
mdefine_line|#define ndHdrNode&t;0x01&t;/* The tree header node (node 0) */
DECL|macro|ndMapNode
mdefine_line|#define ndMapNode&t;0x02&t;/* Holds part of the bitmap of used nodes */
DECL|macro|ndLeafNode
mdefine_line|#define ndLeafNode&t;0xFF&t;/* A leaf (ndNHeight==1) node */
multiline_comment|/*&n; * Legal values for the bthAtrb field of a (struct BTHdrRec)&n; *&n; * Reference: TN 1150&n; */
DECL|macro|bthBadClose
mdefine_line|#define bthBadClose     0x00000001  /* b-tree not closed properly. not&n;                                       used by hfsplus. */
DECL|macro|bthBigKeys
mdefine_line|#define bthBigKeys      0x00000002  /* key length is u16 instead of u8.&n;&t;&t;&t;&t;       used by hfsplus. */
DECL|macro|bthVarIndxKeys
mdefine_line|#define bthVarIndxKeys  0x00000004  /* variable key length instead of&n;                                       max key length. use din catalog&n;                                       b-tree but not in extents&n;                                       b-tree (hfsplus). */
multiline_comment|/*================ Function-like macros ================*/
multiline_comment|/* Access the cache slot which should contain the desired node */
DECL|macro|bhash
mdefine_line|#define bhash(tree, node) ((tree)-&gt;cache[(node) % HFS_CACHELEN])
multiline_comment|/* round up to multiple of sizeof(hfs_u16) */
DECL|macro|ROUND
mdefine_line|#define ROUND(X) ((X + sizeof(hfs_u16) - 1) &amp; ~(sizeof(hfs_u16)-1))
multiline_comment|/* Refer to the (base-1) array of offsets in a bnode */
DECL|macro|RECTBL
mdefine_line|#define RECTBL(X,N) &bslash;&n;&t;(((hfs_u16 *)(hfs_buffer_data((X)-&gt;buf)+HFS_SECTOR_SIZE))-(N))
multiline_comment|/*================ Private data types ================*/
multiline_comment|/*&n; * struct BTHdrRec&n; *&n; * The B-tree header record&n; *&n; * This data structure is stored in the first node (512-byte block) of&n; * each B-tree file.  It contains important information about the&n; * B-tree.  Most fields vary over the life of the tree and are&n; * indicated by a &squot;V&squot; in the comments.&t;The other fields are fixed for&n; * the life of the tree and are indicated by a &squot;F&squot;.&n; *&n; * Reference: _Inside Macintosh: Files_ pp. 2-68 through 2-69 */
DECL|struct|BTHdrRec
r_struct
id|BTHdrRec
(brace
DECL|member|bthDepth
id|hfs_word_t
id|bthDepth
suffix:semicolon
multiline_comment|/* (V) The number of levels in this B-tree */
DECL|member|bthRoot
id|hfs_lword_t
id|bthRoot
suffix:semicolon
multiline_comment|/* (V) The node number of the root node */
DECL|member|bthNRecs
id|hfs_lword_t
id|bthNRecs
suffix:semicolon
multiline_comment|/* (V) The number of leaf records */
DECL|member|bthFNode
id|hfs_lword_t
id|bthFNode
suffix:semicolon
multiline_comment|/* (V) The number of the first leaf node */
DECL|member|bthLNode
id|hfs_lword_t
id|bthLNode
suffix:semicolon
multiline_comment|/* (V) The number of the last leaf node */
DECL|member|bthNodeSize
id|hfs_word_t
id|bthNodeSize
suffix:semicolon
multiline_comment|/* (F) The number of bytes in a node (=512) */
DECL|member|bthKeyLen
id|hfs_word_t
id|bthKeyLen
suffix:semicolon
multiline_comment|/* (F) The length of a key in an index node */
DECL|member|bthNNodes
id|hfs_lword_t
id|bthNNodes
suffix:semicolon
multiline_comment|/* (V) The total number of nodes */
DECL|member|bthFree
id|hfs_lword_t
id|bthFree
suffix:semicolon
multiline_comment|/* (V) The number of unused nodes */
DECL|member|bthResv1
id|hfs_word_t
id|bthResv1
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|bthClpSiz
id|hfs_lword_t
id|bthClpSiz
suffix:semicolon
multiline_comment|/* (F) clump size. not usually used. */
DECL|member|bthType
id|hfs_byte_t
id|bthType
suffix:semicolon
multiline_comment|/* (F) BTree type */
DECL|member|bthResv2
id|hfs_byte_t
id|bthResv2
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|bthAtrb
id|hfs_lword_t
id|bthAtrb
suffix:semicolon
multiline_comment|/* (F) attributes */
DECL|member|bthResv3
id|hfs_lword_t
id|bthResv3
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Reserved */
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * struct NodeDescriptor&n; *&n; * The B-tree node descriptor.&n; *&n; * This structure begins each node in the B-tree file.&t;It contains&n; * important information about the node&squot;s contents.  &squot;V&squot; and &squot;F&squot; in&n; * the comments indicate fields that are variable or fixed over the&n; * life of a node, where the &squot;life&squot; of a node is defined as the period&n; * between leaving and reentering the free pool.&n; *&n; * Reference: _Inside Macintosh: Files_ p. 2-64&n; */
DECL|struct|NodeDescriptor
r_struct
id|NodeDescriptor
(brace
DECL|member|ndFLink
id|hfs_lword_t
id|ndFLink
suffix:semicolon
multiline_comment|/* (V) Number of the next node at this level */
DECL|member|ndBLink
id|hfs_lword_t
id|ndBLink
suffix:semicolon
multiline_comment|/* (V) Number of the prev node at this level */
DECL|member|ndType
id|hfs_byte_t
id|ndType
suffix:semicolon
multiline_comment|/* (F) The type of node */
DECL|member|ndNHeight
id|hfs_byte_t
id|ndNHeight
suffix:semicolon
multiline_comment|/* (F) The level of this node (leaves=1) */
DECL|member|ndNRecs
id|hfs_word_t
id|ndNRecs
suffix:semicolon
multiline_comment|/* (V) The number of records in this node */
DECL|member|ndResv2
id|hfs_word_t
id|ndResv2
suffix:semicolon
multiline_comment|/* Reserved */
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * typedef hfs_cmpfn&n; *&n; * The type &squot;hfs_cmpfn&squot; is a comparison function taking 2 keys and&n; * returning a positive, negative or zero integer according to the&n; * ordering of the two keys (just like strcmp() does for strings).&n; */
DECL|typedef|hfs_cmpfn
r_typedef
r_int
(paren
op_star
id|hfs_cmpfn
)paren
(paren
r_const
r_void
op_star
comma
r_const
r_void
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * struct hfs_bnode&n; *&n; * An in-core B-tree node&n; *&n; * This structure holds information from the NodeDescriptor in native&n; * byte-order, a pointer to the buffer which contains the actual&n; * node and fields necessary for locking access to the node during&n; * updates.  The use of the locking fields is explained with the&n; * locking functions.&n; */
DECL|struct|hfs_bnode
r_struct
id|hfs_bnode
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* Magic number to guard against&n;&t;&t;&t;&t;&t;wild pointers */
DECL|member|buf
id|hfs_buffer
id|buf
suffix:semicolon
multiline_comment|/* The buffer containing the&n;&t;&t;&t;&t;&t;actual node */
DECL|member|tree
r_struct
id|hfs_btree
op_star
id|tree
suffix:semicolon
multiline_comment|/* The tree to which this node&n;&t;&t;&t;&t;&t;belongs */
DECL|member|prev
r_struct
id|hfs_bnode
op_star
id|prev
suffix:semicolon
multiline_comment|/* Next node in this hash bucket */
DECL|member|next
r_struct
id|hfs_bnode
op_star
id|next
suffix:semicolon
multiline_comment|/* Previous node in this hash&n;&t;&t;&t;&t;&t;bucket */
DECL|member|sticky
r_int
id|sticky
suffix:semicolon
multiline_comment|/* Boolean: non-zero means keep&n;&t;&t;&t;&t;&t;this node in-core (set for&n;&t;&t;&t;&t;&t;root and head) */
DECL|member|node
id|hfs_u32
id|node
suffix:semicolon
multiline_comment|/* Node number */
DECL|member|nodeSize
id|hfs_u16
id|nodeSize
suffix:semicolon
multiline_comment|/* node size */
DECL|member|keyLen
id|hfs_u16
id|keyLen
suffix:semicolon
multiline_comment|/* key length */
multiline_comment|/* locking related fields: */
DECL|member|wqueue
id|hfs_wait_queue
id|wqueue
suffix:semicolon
multiline_comment|/* Wait queue for write access */
DECL|member|rqueue
id|hfs_wait_queue
id|rqueue
suffix:semicolon
multiline_comment|/* Wait queue for read or reserve&n;&t;&t;&t;&t;&t;access */
DECL|member|count
r_int
id|count
suffix:semicolon
multiline_comment|/* Number of processes accessing&n;&t;&t;&t;&t;&t;this node */
DECL|member|resrv
r_int
id|resrv
suffix:semicolon
multiline_comment|/* Boolean, true means a process&n;&t;&t;&t;&t;&t;had placed a &squot;reservation&squot; on&n;&t;&t;&t;&t;&t;this node */
DECL|member|lock
r_int
id|lock
suffix:semicolon
multiline_comment|/* Boolean, true means some&n;&t;&t;&t;&t;&t;process has exclusive access,&n;&t;&t;&t;&t;&t;so KEEP OUT */
multiline_comment|/* fields from the NodeDescriptor in native byte-order: */
DECL|member|ndFLink
id|hfs_u32
id|ndFLink
suffix:semicolon
DECL|member|ndBLink
id|hfs_u32
id|ndBLink
suffix:semicolon
DECL|member|ndNRecs
id|hfs_u16
id|ndNRecs
suffix:semicolon
DECL|member|ndType
id|hfs_u8
id|ndType
suffix:semicolon
DECL|member|ndNHeight
id|hfs_u8
id|ndNHeight
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * struct hfs_btree&n; *&n; * An in-core B-tree.&n; *&n; * This structure holds information from the BTHdrRec, MDB&n; * (superblock) and other information needed to work with the B-tree.&n; */
DECL|struct|hfs_btree
r_struct
id|hfs_btree
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* Magic number to&n;&t;&t;&t;&t;&t;&t;  guard against wild&n;&t;&t;&t;&t;&t;&t;  pointers */
DECL|member|compare
id|hfs_cmpfn
id|compare
suffix:semicolon
multiline_comment|/* Comparison function&n;&t;&t;&t;&t;&t;&t;  for this tree */
DECL|member|head
r_struct
id|hfs_bnode
id|head
suffix:semicolon
multiline_comment|/* in-core copy of node 0 */
DECL|member|root
r_struct
id|hfs_bnode
op_star
id|root
suffix:semicolon
multiline_comment|/* Pointer to the in-core&n;&t;&t;&t;&t;&t;&t;  copy of the root node */
DECL|member|sys_mdb
id|hfs_sysmdb
id|sys_mdb
suffix:semicolon
multiline_comment|/* The &quot;device&quot; holding&n;&t;&t;&t;&t;&t;&t;  the filesystem */
DECL|member|reserved
r_int
id|reserved
suffix:semicolon
multiline_comment|/* bnodes claimed but&n;&t;&t;&t;&t;&t;&t;  not yet used */
r_struct
id|hfs_bnode
multiline_comment|/* The bnode cache */
DECL|member|cache
op_star
id|cache
(braket
id|HFS_CACHELEN
)braket
suffix:semicolon
DECL|member|entry
r_struct
id|hfs_cat_entry
id|entry
suffix:semicolon
multiline_comment|/* Fake catalog entry */
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
DECL|member|dirt
r_int
id|dirt
suffix:semicolon
DECL|member|keySize
r_int
id|keySize
suffix:semicolon
multiline_comment|/* Fields from the BTHdrRec in native byte-order: */
DECL|member|bthRoot
id|hfs_u32
id|bthRoot
suffix:semicolon
DECL|member|bthNRecs
id|hfs_u32
id|bthNRecs
suffix:semicolon
DECL|member|bthFNode
id|hfs_u32
id|bthFNode
suffix:semicolon
DECL|member|bthLNode
id|hfs_u32
id|bthLNode
suffix:semicolon
DECL|member|bthNNodes
id|hfs_u32
id|bthNNodes
suffix:semicolon
DECL|member|bthFree
id|hfs_u32
id|bthFree
suffix:semicolon
DECL|member|bthKeyLen
id|hfs_u16
id|bthKeyLen
suffix:semicolon
DECL|member|bthDepth
id|hfs_u16
id|bthDepth
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*================ Global functions ================*/
multiline_comment|/* Convert a (struct hfs_bnode *) and an index to the value of the&n;   n-th offset in the bnode (N &gt;= 1) to the offset */
DECL|function|bnode_offset
r_extern
r_inline
id|hfs_u16
id|bnode_offset
c_func
(paren
r_const
r_struct
id|hfs_bnode
op_star
id|bnode
comma
r_int
id|n
)paren
(brace
r_return
id|hfs_get_hs
c_func
(paren
id|RECTBL
c_func
(paren
id|bnode
comma
id|n
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Convert a (struct hfs_bnode *) and an index to the size of the&n;   n-th record in the bnode (N &gt;= 1) */
DECL|function|bnode_rsize
r_extern
r_inline
id|hfs_u16
id|bnode_rsize
c_func
(paren
r_const
r_struct
id|hfs_bnode
op_star
id|bnode
comma
r_int
id|n
)paren
(brace
r_return
id|bnode_offset
c_func
(paren
id|bnode
comma
id|n
op_plus
l_int|1
)paren
op_minus
id|bnode_offset
c_func
(paren
id|bnode
comma
id|n
)paren
suffix:semicolon
)brace
multiline_comment|/* Convert a (struct hfs_bnode *) to the offset of the empty part */
DECL|function|bnode_end
r_extern
r_inline
id|hfs_u16
id|bnode_end
c_func
(paren
r_const
r_struct
id|hfs_bnode
op_star
id|bnode
)paren
(brace
r_return
id|bnode_offset
c_func
(paren
id|bnode
comma
id|bnode-&gt;ndNRecs
op_plus
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* Convert a (struct hfs_bnode *) to the number of free bytes it contains */
DECL|function|bnode_freespace
r_extern
r_inline
id|hfs_u16
id|bnode_freespace
c_func
(paren
r_const
r_struct
id|hfs_bnode
op_star
id|bnode
)paren
(brace
r_return
id|HFS_SECTOR_SIZE
op_minus
id|bnode_end
c_func
(paren
id|bnode
)paren
op_minus
(paren
id|bnode-&gt;ndNRecs
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
id|hfs_u16
)paren
suffix:semicolon
)brace
multiline_comment|/* Convert a (struct hfs_bnode *) X and an index N to&n;   the address of the record N in the bnode (N &gt;= 1) */
DECL|function|bnode_datastart
r_extern
r_inline
r_void
op_star
id|bnode_datastart
c_func
(paren
r_const
r_struct
id|hfs_bnode
op_star
id|bnode
)paren
(brace
r_return
(paren
r_void
op_star
)paren
(paren
id|hfs_buffer_data
c_func
(paren
id|bnode-&gt;buf
)paren
op_plus
r_sizeof
(paren
r_struct
id|NodeDescriptor
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Convert a (struct hfs_bnode *) to the address of the empty part */
DECL|function|bnode_dataend
r_extern
r_inline
r_void
op_star
id|bnode_dataend
c_func
(paren
r_const
r_struct
id|hfs_bnode
op_star
id|bnode
)paren
(brace
r_return
(paren
r_void
op_star
)paren
(paren
id|hfs_buffer_data
c_func
(paren
id|bnode-&gt;buf
)paren
op_plus
id|bnode_end
c_func
(paren
id|bnode
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Convert various pointers to address of record&squot;s key */
DECL|function|bnode_key
r_extern
r_inline
r_void
op_star
id|bnode_key
c_func
(paren
r_const
r_struct
id|hfs_bnode
op_star
id|bnode
comma
r_int
id|n
)paren
(brace
r_return
(paren
r_void
op_star
)paren
(paren
id|hfs_buffer_data
c_func
(paren
id|bnode-&gt;buf
)paren
op_plus
id|bnode_offset
c_func
(paren
id|bnode
comma
id|n
)paren
)paren
suffix:semicolon
)brace
DECL|function|belem_key
r_extern
r_inline
r_void
op_star
id|belem_key
c_func
(paren
r_const
r_struct
id|hfs_belem
op_star
id|elem
)paren
(brace
r_return
id|bnode_key
c_func
(paren
id|elem-&gt;bnr.bn
comma
id|elem-&gt;record
)paren
suffix:semicolon
)brace
DECL|function|brec_key
r_extern
r_inline
r_void
op_star
id|brec_key
c_func
(paren
r_const
r_struct
id|hfs_brec
op_star
id|brec
)paren
(brace
r_return
id|belem_key
c_func
(paren
id|brec-&gt;bottom
)paren
suffix:semicolon
)brace
multiline_comment|/* Convert various pointers to the address of a record */
DECL|function|bkey_record
r_extern
r_inline
r_void
op_star
id|bkey_record
c_func
(paren
r_const
r_struct
id|hfs_bkey
op_star
id|key
)paren
(brace
r_return
(paren
r_void
op_star
)paren
id|key
op_plus
id|ROUND
c_func
(paren
id|key-&gt;KeyLen
op_plus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|bnode_record
r_extern
r_inline
r_void
op_star
id|bnode_record
c_func
(paren
r_const
r_struct
id|hfs_bnode
op_star
id|bnode
comma
r_int
id|n
)paren
(brace
r_return
id|bkey_record
c_func
(paren
id|bnode_key
c_func
(paren
id|bnode
comma
id|n
)paren
)paren
suffix:semicolon
)brace
DECL|function|belem_record
r_extern
r_inline
r_void
op_star
id|belem_record
c_func
(paren
r_const
r_struct
id|hfs_belem
op_star
id|elem
)paren
(brace
r_return
id|bkey_record
c_func
(paren
id|belem_key
c_func
(paren
id|elem
)paren
)paren
suffix:semicolon
)brace
DECL|function|brec_record
r_extern
r_inline
r_void
op_star
id|brec_record
c_func
(paren
r_const
r_struct
id|hfs_brec
op_star
id|brec
)paren
(brace
r_return
id|bkey_record
c_func
(paren
id|brec_key
c_func
(paren
id|brec
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*================ Function Prototypes ================*/
multiline_comment|/* balloc.c */
r_extern
r_int
id|hfs_bnode_bitop
c_func
(paren
r_struct
id|hfs_btree
op_star
comma
id|hfs_u32
comma
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|hfs_bnode_ref
id|hfs_bnode_alloc
c_func
(paren
r_struct
id|hfs_btree
op_star
)paren
suffix:semicolon
r_extern
r_int
id|hfs_bnode_free
c_func
(paren
r_struct
id|hfs_bnode_ref
op_star
)paren
suffix:semicolon
r_extern
r_void
id|hfs_btree_extend
c_func
(paren
r_struct
id|hfs_btree
op_star
)paren
suffix:semicolon
multiline_comment|/* bins_del.c */
r_extern
r_void
id|hfs_bnode_update_key
c_func
(paren
r_struct
id|hfs_brec
op_star
comma
r_struct
id|hfs_belem
op_star
comma
r_struct
id|hfs_bnode
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|hfs_bnode_shift_right
c_func
(paren
r_struct
id|hfs_bnode
op_star
comma
r_struct
id|hfs_bnode
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|hfs_bnode_shift_left
c_func
(paren
r_struct
id|hfs_bnode
op_star
comma
r_struct
id|hfs_bnode
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|hfs_bnode_in_brec
c_func
(paren
id|hfs_u32
id|node
comma
r_const
r_struct
id|hfs_brec
op_star
id|brec
)paren
suffix:semicolon
multiline_comment|/* bnode.c */
r_extern
r_void
id|hfs_bnode_read
c_func
(paren
r_struct
id|hfs_bnode
op_star
comma
r_struct
id|hfs_btree
op_star
comma
id|hfs_u32
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|hfs_bnode_relse
c_func
(paren
r_struct
id|hfs_bnode_ref
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|hfs_bnode_ref
id|hfs_bnode_find
c_func
(paren
r_struct
id|hfs_btree
op_star
comma
id|hfs_u32
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|hfs_bnode_lock
c_func
(paren
r_struct
id|hfs_bnode_ref
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|hfs_bnode_delete
c_func
(paren
r_struct
id|hfs_bnode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|hfs_bnode_commit
c_func
(paren
r_struct
id|hfs_bnode
op_star
)paren
suffix:semicolon
multiline_comment|/* brec.c */
r_extern
r_void
id|hfs_brec_lock
c_func
(paren
r_struct
id|hfs_brec
op_star
comma
r_struct
id|hfs_belem
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|hfs_belem
op_star
id|hfs_brec_init
c_func
(paren
r_struct
id|hfs_brec
op_star
comma
r_struct
id|hfs_btree
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|hfs_belem
op_star
id|hfs_brec_next
c_func
(paren
r_struct
id|hfs_brec
op_star
)paren
suffix:semicolon
macro_line|#endif
eof
