multiline_comment|/*&n; * dm-snapshot.c&n; *&n; * Copyright (C) 2001-2002 Sistina Software (UK) Limited.&n; *&n; * This file is released under the GPL.&n; */
macro_line|#ifndef DM_SNAPSHOT_H
DECL|macro|DM_SNAPSHOT_H
mdefine_line|#define DM_SNAPSHOT_H
macro_line|#include &quot;dm.h&quot;
macro_line|#include &lt;linux/blkdev.h&gt;
DECL|struct|exception_table
r_struct
id|exception_table
(brace
DECL|member|hash_mask
r_uint32
id|hash_mask
suffix:semicolon
DECL|member|table
r_struct
id|list_head
op_star
id|table
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * The snapshot code deals with largish chunks of the disk at a&n; * time. Typically 64k - 256k.&n; */
multiline_comment|/* FIXME: can we get away with limiting these to a uint32_t ? */
DECL|typedef|chunk_t
r_typedef
id|sector_t
id|chunk_t
suffix:semicolon
multiline_comment|/*&n; * An exception is used where an old chunk of data has been&n; * replaced by a new one.&n; */
DECL|struct|exception
r_struct
id|exception
(brace
DECL|member|hash_list
r_struct
id|list_head
id|hash_list
suffix:semicolon
DECL|member|old_chunk
id|chunk_t
id|old_chunk
suffix:semicolon
DECL|member|new_chunk
id|chunk_t
id|new_chunk
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Abstraction to handle the meta/layout of exception stores (the&n; * COW device).&n; */
DECL|struct|exception_store
r_struct
id|exception_store
(brace
multiline_comment|/*&n;&t; * Destroys this object when you&squot;ve finished with it.&n;&t; */
DECL|member|destroy
r_void
(paren
op_star
id|destroy
)paren
(paren
r_struct
id|exception_store
op_star
id|store
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The target shouldn&squot;t read the COW device until this is&n;&t; * called.&n;&t; */
DECL|member|read_metadata
r_int
(paren
op_star
id|read_metadata
)paren
(paren
r_struct
id|exception_store
op_star
id|store
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Find somewhere to store the next exception.&n;&t; */
DECL|member|prepare_exception
r_int
(paren
op_star
id|prepare_exception
)paren
(paren
r_struct
id|exception_store
op_star
id|store
comma
r_struct
id|exception
op_star
id|e
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Update the metadata with this exception.&n;&t; */
DECL|member|commit_exception
r_void
(paren
op_star
id|commit_exception
)paren
(paren
r_struct
id|exception_store
op_star
id|store
comma
r_struct
id|exception
op_star
id|e
comma
r_void
(paren
op_star
id|callback
)paren
(paren
r_void
op_star
comma
r_int
id|success
)paren
comma
r_void
op_star
id|callback_context
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The snapshot is invalid, note this in the metadata.&n;&t; */
DECL|member|drop_snapshot
r_void
(paren
op_star
id|drop_snapshot
)paren
(paren
r_struct
id|exception_store
op_star
id|store
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Return how full the snapshot is.&n;&t; */
DECL|member|fraction_full
r_void
(paren
op_star
id|fraction_full
)paren
(paren
r_struct
id|exception_store
op_star
id|store
comma
id|sector_t
op_star
id|numerator
comma
id|sector_t
op_star
id|denominator
)paren
suffix:semicolon
DECL|member|snap
r_struct
id|dm_snapshot
op_star
id|snap
suffix:semicolon
DECL|member|context
r_void
op_star
id|context
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dm_snapshot
r_struct
id|dm_snapshot
(brace
DECL|member|lock
r_struct
id|rw_semaphore
id|lock
suffix:semicolon
DECL|member|table
r_struct
id|dm_table
op_star
id|table
suffix:semicolon
DECL|member|origin
r_struct
id|dm_dev
op_star
id|origin
suffix:semicolon
DECL|member|cow
r_struct
id|dm_dev
op_star
id|cow
suffix:semicolon
multiline_comment|/* List of snapshots per Origin */
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* Size of data blocks saved - must be a power of 2 */
DECL|member|chunk_size
id|chunk_t
id|chunk_size
suffix:semicolon
DECL|member|chunk_mask
id|chunk_t
id|chunk_mask
suffix:semicolon
DECL|member|chunk_shift
id|chunk_t
id|chunk_shift
suffix:semicolon
multiline_comment|/* You can&squot;t use a snapshot if this is 0 (e.g. if full) */
DECL|member|valid
r_int
id|valid
suffix:semicolon
DECL|member|have_metadata
r_int
id|have_metadata
suffix:semicolon
multiline_comment|/* Used for display of table */
DECL|member|type
r_char
id|type
suffix:semicolon
multiline_comment|/* The last percentage we notified */
DECL|member|last_percent
r_int
id|last_percent
suffix:semicolon
DECL|member|pending
r_struct
id|exception_table
id|pending
suffix:semicolon
DECL|member|complete
r_struct
id|exception_table
id|complete
suffix:semicolon
multiline_comment|/* The on disk metadata handler */
DECL|member|store
r_struct
id|exception_store
id|store
suffix:semicolon
DECL|member|kcopyd_client
r_struct
id|kcopyd_client
op_star
id|kcopyd_client
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Used by the exception stores to load exceptions hen&n; * initialising.&n; */
r_int
id|dm_add_exception
c_func
(paren
r_struct
id|dm_snapshot
op_star
id|s
comma
id|chunk_t
id|old
comma
id|chunk_t
r_new
)paren
suffix:semicolon
multiline_comment|/*&n; * Constructor and destructor for the default persistent&n; * store.&n; */
r_int
id|dm_create_persistent
c_func
(paren
r_struct
id|exception_store
op_star
id|store
comma
r_uint32
id|chunk_size
)paren
suffix:semicolon
r_int
id|dm_create_transient
c_func
(paren
r_struct
id|exception_store
op_star
id|store
comma
r_struct
id|dm_snapshot
op_star
id|s
comma
r_int
id|blocksize
)paren
suffix:semicolon
multiline_comment|/*&n; * Return the number of sectors in the device.&n; */
DECL|function|get_dev_size
r_static
r_inline
id|sector_t
id|get_dev_size
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
)paren
(brace
r_return
id|bdev-&gt;bd_inode-&gt;i_size
op_rshift
id|SECTOR_SHIFT
suffix:semicolon
)brace
DECL|function|sector_to_chunk
r_static
r_inline
id|chunk_t
id|sector_to_chunk
c_func
(paren
r_struct
id|dm_snapshot
op_star
id|s
comma
id|sector_t
id|sector
)paren
(brace
r_return
(paren
id|sector
op_amp
op_complement
id|s-&gt;chunk_mask
)paren
op_rshift
id|s-&gt;chunk_shift
suffix:semicolon
)brace
DECL|function|chunk_to_sector
r_static
r_inline
id|sector_t
id|chunk_to_sector
c_func
(paren
r_struct
id|dm_snapshot
op_star
id|s
comma
id|chunk_t
id|chunk
)paren
(brace
r_return
id|chunk
op_lshift
id|s-&gt;chunk_shift
suffix:semicolon
)brace
DECL|function|bdev_equal
r_static
r_inline
r_int
id|bdev_equal
c_func
(paren
r_struct
id|block_device
op_star
id|lhs
comma
r_struct
id|block_device
op_star
id|rhs
)paren
(brace
multiline_comment|/*&n;&t; * There is only ever one instance of a particular block&n;&t; * device so we can compare pointers safely.&n;&t; */
r_return
id|lhs
op_eq
id|rhs
suffix:semicolon
)brace
macro_line|#endif
eof
