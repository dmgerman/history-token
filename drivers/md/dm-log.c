multiline_comment|/*&n; * Copyright (C) 2003 Sistina Software&n; *&n; * This file is released under the LGPL.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &quot;dm-log.h&quot;
macro_line|#include &quot;dm-io.h&quot;
r_static
id|LIST_HEAD
c_func
(paren
id|_log_types
)paren
suffix:semicolon
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|_lock
)paren
suffix:semicolon
DECL|function|dm_register_dirty_log_type
r_int
id|dm_register_dirty_log_type
c_func
(paren
r_struct
id|dirty_log_type
op_star
id|type
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|try_module_get
c_func
(paren
id|type-&gt;module
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|_lock
)paren
suffix:semicolon
id|type-&gt;use_count
op_assign
l_int|0
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|type-&gt;list
comma
op_amp
id|_log_types
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dm_unregister_dirty_log_type
r_int
id|dm_unregister_dirty_log_type
c_func
(paren
r_struct
id|dirty_log_type
op_star
id|type
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type-&gt;use_count
)paren
id|DMWARN
c_func
(paren
l_string|&quot;Attempt to unregister a log type that is still in use&quot;
)paren
suffix:semicolon
r_else
(brace
id|list_del
c_func
(paren
op_amp
id|type-&gt;list
)paren
suffix:semicolon
id|module_put
c_func
(paren
id|type-&gt;module
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_type
r_static
r_struct
id|dirty_log_type
op_star
id|get_type
c_func
(paren
r_const
r_char
op_star
id|type_name
)paren
(brace
r_struct
id|dirty_log_type
op_star
id|type
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|_lock
)paren
suffix:semicolon
id|list_for_each_entry
(paren
id|type
comma
op_amp
id|_log_types
comma
id|list
)paren
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|type_name
comma
id|type-&gt;name
)paren
)paren
(brace
id|type-&gt;use_count
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|_lock
)paren
suffix:semicolon
r_return
id|type
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|_lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|put_type
r_static
r_void
id|put_type
c_func
(paren
r_struct
id|dirty_log_type
op_star
id|type
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|_lock
)paren
suffix:semicolon
id|type-&gt;use_count
op_decrement
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|_lock
)paren
suffix:semicolon
)brace
DECL|function|dm_create_dirty_log
r_struct
id|dirty_log
op_star
id|dm_create_dirty_log
c_func
(paren
r_const
r_char
op_star
id|type_name
comma
r_struct
id|dm_target
op_star
id|ti
comma
r_int
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
(brace
r_struct
id|dirty_log_type
op_star
id|type
suffix:semicolon
r_struct
id|dirty_log
op_star
id|log
suffix:semicolon
id|log
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|log
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|log
)paren
r_return
l_int|NULL
suffix:semicolon
id|type
op_assign
id|get_type
c_func
(paren
id|type_name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|type
)paren
(brace
id|kfree
c_func
(paren
id|log
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|log-&gt;type
op_assign
id|type
suffix:semicolon
r_if
c_cond
(paren
id|type
op_member_access_from_pointer
id|ctr
c_func
(paren
id|log
comma
id|ti
comma
id|argc
comma
id|argv
)paren
)paren
(brace
id|kfree
c_func
(paren
id|log
)paren
suffix:semicolon
id|put_type
c_func
(paren
id|type
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|log
suffix:semicolon
)brace
DECL|function|dm_destroy_dirty_log
r_void
id|dm_destroy_dirty_log
c_func
(paren
r_struct
id|dirty_log
op_star
id|log
)paren
(brace
id|log-&gt;type
op_member_access_from_pointer
id|dtr
c_func
(paren
id|log
)paren
suffix:semicolon
id|put_type
c_func
(paren
id|log-&gt;type
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|log
)paren
suffix:semicolon
)brace
multiline_comment|/*-----------------------------------------------------------------&n; * Persistent and core logs share a lot of their implementation.&n; * FIXME: need a reload method to be called from a resume&n; *---------------------------------------------------------------*/
multiline_comment|/*&n; * Magic for persistent mirrors: &quot;MiRr&quot;&n; */
DECL|macro|MIRROR_MAGIC
mdefine_line|#define MIRROR_MAGIC 0x4D695272
multiline_comment|/*&n; * The on-disk version of the metadata.&n; */
DECL|macro|MIRROR_DISK_VERSION
mdefine_line|#define MIRROR_DISK_VERSION 1
DECL|macro|LOG_OFFSET
mdefine_line|#define LOG_OFFSET 2
DECL|struct|log_header
r_struct
id|log_header
(brace
DECL|member|magic
r_uint32
id|magic
suffix:semicolon
multiline_comment|/*&n;&t; * Simple, incrementing version. no backward&n;&t; * compatibility.&n;&t; */
DECL|member|version
r_uint32
id|version
suffix:semicolon
DECL|member|nr_regions
id|sector_t
id|nr_regions
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|log_c
r_struct
id|log_c
(brace
DECL|member|ti
r_struct
id|dm_target
op_star
id|ti
suffix:semicolon
DECL|member|touched
r_int
id|touched
suffix:semicolon
DECL|member|region_size
id|sector_t
id|region_size
suffix:semicolon
DECL|member|region_count
r_int
r_int
id|region_count
suffix:semicolon
DECL|member|sync_count
id|region_t
id|sync_count
suffix:semicolon
DECL|member|bitset_uint32_count
r_int
id|bitset_uint32_count
suffix:semicolon
DECL|member|clean_bits
r_uint32
op_star
id|clean_bits
suffix:semicolon
DECL|member|sync_bits
r_uint32
op_star
id|sync_bits
suffix:semicolon
DECL|member|recovering_bits
r_uint32
op_star
id|recovering_bits
suffix:semicolon
multiline_comment|/* FIXME: this seems excessive */
DECL|member|sync_search
r_int
id|sync_search
suffix:semicolon
multiline_comment|/* Resync flag */
DECL|enum|sync
r_enum
id|sync
(brace
DECL|enumerator|DEFAULTSYNC
id|DEFAULTSYNC
comma
multiline_comment|/* Synchronize if necessary */
DECL|enumerator|NOSYNC
id|NOSYNC
comma
multiline_comment|/* Devices known to be already in sync */
DECL|enumerator|FORCESYNC
id|FORCESYNC
comma
multiline_comment|/* Force a sync to happen */
DECL|member|sync
)brace
id|sync
suffix:semicolon
multiline_comment|/*&n;&t; * Disk log fields&n;&t; */
DECL|member|log_dev
r_struct
id|dm_dev
op_star
id|log_dev
suffix:semicolon
DECL|member|header
r_struct
id|log_header
id|header
suffix:semicolon
DECL|member|header_location
r_struct
id|io_region
id|header_location
suffix:semicolon
DECL|member|disk_header
r_struct
id|log_header
op_star
id|disk_header
suffix:semicolon
DECL|member|bits_location
r_struct
id|io_region
id|bits_location
suffix:semicolon
DECL|member|disk_bits
r_uint32
op_star
id|disk_bits
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * The touched member needs to be updated every time we access&n; * one of the bitsets.&n; */
DECL|function|log_test_bit
r_static
r_inline
r_int
id|log_test_bit
c_func
(paren
r_uint32
op_star
id|bs
comma
r_int
id|bit
)paren
(brace
r_return
id|test_bit
c_func
(paren
id|bit
comma
(paren
r_int
r_int
op_star
)paren
id|bs
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|log_set_bit
r_static
r_inline
r_void
id|log_set_bit
c_func
(paren
r_struct
id|log_c
op_star
id|l
comma
r_uint32
op_star
id|bs
comma
r_int
id|bit
)paren
(brace
id|set_bit
c_func
(paren
id|bit
comma
(paren
r_int
r_int
op_star
)paren
id|bs
)paren
suffix:semicolon
id|l-&gt;touched
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|log_clear_bit
r_static
r_inline
r_void
id|log_clear_bit
c_func
(paren
r_struct
id|log_c
op_star
id|l
comma
r_uint32
op_star
id|bs
comma
r_int
id|bit
)paren
(brace
id|clear_bit
c_func
(paren
id|bit
comma
(paren
r_int
r_int
op_star
)paren
id|bs
)paren
suffix:semicolon
id|l-&gt;touched
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*----------------------------------------------------------------&n; * Header IO&n; *--------------------------------------------------------------*/
DECL|function|header_to_disk
r_static
r_void
id|header_to_disk
c_func
(paren
r_struct
id|log_header
op_star
id|core
comma
r_struct
id|log_header
op_star
id|disk
)paren
(brace
id|disk-&gt;magic
op_assign
id|cpu_to_le32
c_func
(paren
id|core-&gt;magic
)paren
suffix:semicolon
id|disk-&gt;version
op_assign
id|cpu_to_le32
c_func
(paren
id|core-&gt;version
)paren
suffix:semicolon
id|disk-&gt;nr_regions
op_assign
id|cpu_to_le64
c_func
(paren
id|core-&gt;nr_regions
)paren
suffix:semicolon
)brace
DECL|function|header_from_disk
r_static
r_void
id|header_from_disk
c_func
(paren
r_struct
id|log_header
op_star
id|core
comma
r_struct
id|log_header
op_star
id|disk
)paren
(brace
id|core-&gt;magic
op_assign
id|le32_to_cpu
c_func
(paren
id|disk-&gt;magic
)paren
suffix:semicolon
id|core-&gt;version
op_assign
id|le32_to_cpu
c_func
(paren
id|disk-&gt;version
)paren
suffix:semicolon
id|core-&gt;nr_regions
op_assign
id|le64_to_cpu
c_func
(paren
id|disk-&gt;nr_regions
)paren
suffix:semicolon
)brace
DECL|function|read_header
r_static
r_int
id|read_header
c_func
(paren
r_struct
id|log_c
op_star
id|log
)paren
(brace
r_int
id|r
suffix:semicolon
r_int
r_int
id|ebits
suffix:semicolon
id|r
op_assign
id|dm_io_sync_vm
c_func
(paren
l_int|1
comma
op_amp
id|log-&gt;header_location
comma
id|READ
comma
id|log-&gt;disk_header
comma
op_amp
id|ebits
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
r_return
id|r
suffix:semicolon
id|header_from_disk
c_func
(paren
op_amp
id|log-&gt;header
comma
id|log-&gt;disk_header
)paren
suffix:semicolon
multiline_comment|/* New log required? */
r_if
c_cond
(paren
id|log-&gt;sync
op_ne
id|DEFAULTSYNC
op_logical_or
id|log-&gt;header.magic
op_ne
id|MIRROR_MAGIC
)paren
(brace
id|log-&gt;header.magic
op_assign
id|MIRROR_MAGIC
suffix:semicolon
id|log-&gt;header.version
op_assign
id|MIRROR_DISK_VERSION
suffix:semicolon
id|log-&gt;header.nr_regions
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|log-&gt;header.version
op_ne
id|MIRROR_DISK_VERSION
)paren
(brace
id|DMWARN
c_func
(paren
l_string|&quot;incompatible disk log version&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|write_header
r_static
r_inline
r_int
id|write_header
c_func
(paren
r_struct
id|log_c
op_star
id|log
)paren
(brace
r_int
r_int
id|ebits
suffix:semicolon
id|header_to_disk
c_func
(paren
op_amp
id|log-&gt;header
comma
id|log-&gt;disk_header
)paren
suffix:semicolon
r_return
id|dm_io_sync_vm
c_func
(paren
l_int|1
comma
op_amp
id|log-&gt;header_location
comma
id|WRITE
comma
id|log-&gt;disk_header
comma
op_amp
id|ebits
)paren
suffix:semicolon
)brace
multiline_comment|/*----------------------------------------------------------------&n; * Bits IO&n; *--------------------------------------------------------------*/
DECL|function|bits_to_core
r_static
r_inline
r_void
id|bits_to_core
c_func
(paren
r_uint32
op_star
id|core
comma
r_uint32
op_star
id|disk
comma
r_int
id|count
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|count
suffix:semicolon
id|i
op_increment
)paren
id|core
(braket
id|i
)braket
op_assign
id|le32_to_cpu
c_func
(paren
id|disk
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
DECL|function|bits_to_disk
r_static
r_inline
r_void
id|bits_to_disk
c_func
(paren
r_uint32
op_star
id|core
comma
r_uint32
op_star
id|disk
comma
r_int
id|count
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* copy across the clean/dirty bitset */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|count
suffix:semicolon
id|i
op_increment
)paren
id|disk
(braket
id|i
)braket
op_assign
id|cpu_to_le32
c_func
(paren
id|core
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
DECL|function|read_bits
r_static
r_int
id|read_bits
c_func
(paren
r_struct
id|log_c
op_star
id|log
)paren
(brace
r_int
id|r
suffix:semicolon
r_int
r_int
id|ebits
suffix:semicolon
id|r
op_assign
id|dm_io_sync_vm
c_func
(paren
l_int|1
comma
op_amp
id|log-&gt;bits_location
comma
id|READ
comma
id|log-&gt;disk_bits
comma
op_amp
id|ebits
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
r_return
id|r
suffix:semicolon
id|bits_to_core
c_func
(paren
id|log-&gt;clean_bits
comma
id|log-&gt;disk_bits
comma
id|log-&gt;bitset_uint32_count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|write_bits
r_static
r_int
id|write_bits
c_func
(paren
r_struct
id|log_c
op_star
id|log
)paren
(brace
r_int
r_int
id|ebits
suffix:semicolon
id|bits_to_disk
c_func
(paren
id|log-&gt;clean_bits
comma
id|log-&gt;disk_bits
comma
id|log-&gt;bitset_uint32_count
)paren
suffix:semicolon
r_return
id|dm_io_sync_vm
c_func
(paren
l_int|1
comma
op_amp
id|log-&gt;bits_location
comma
id|WRITE
comma
id|log-&gt;disk_bits
comma
op_amp
id|ebits
)paren
suffix:semicolon
)brace
multiline_comment|/*----------------------------------------------------------------&n; * core log constructor/destructor&n; *&n; * argv contains region_size followed optionally by [no]sync&n; *--------------------------------------------------------------*/
DECL|macro|BYTE_SHIFT
mdefine_line|#define BYTE_SHIFT 3
DECL|function|core_ctr
r_static
r_int
id|core_ctr
c_func
(paren
r_struct
id|dirty_log
op_star
id|log
comma
r_struct
id|dm_target
op_star
id|ti
comma
r_int
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
(brace
r_enum
id|sync
id|sync
op_assign
id|DEFAULTSYNC
suffix:semicolon
r_struct
id|log_c
op_star
id|lc
suffix:semicolon
id|sector_t
id|region_size
suffix:semicolon
r_int
r_int
id|region_count
suffix:semicolon
r_int
id|bitset_size
suffix:semicolon
r_if
c_cond
(paren
id|argc
template_param
l_int|2
)paren
(brace
id|DMWARN
c_func
(paren
l_string|&quot;wrong number of arguments to mirror log&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|argc
OG
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;sync&quot;
)paren
)paren
id|sync
op_assign
id|FORCESYNC
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;nosync&quot;
)paren
)paren
id|sync
op_assign
id|NOSYNC
suffix:semicolon
r_else
(brace
id|DMWARN
c_func
(paren
l_string|&quot;unrecognised sync argument to mirror log: %s&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
id|SECTOR_FORMAT
comma
op_amp
id|region_size
)paren
op_ne
l_int|1
)paren
(brace
id|DMWARN
c_func
(paren
l_string|&quot;invalid region size string&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|region_count
op_assign
id|dm_div_up
c_func
(paren
id|ti-&gt;len
comma
id|region_size
)paren
suffix:semicolon
id|lc
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|lc
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lc
)paren
(brace
id|DMWARN
c_func
(paren
l_string|&quot;couldn&squot;t allocate core log&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|lc-&gt;ti
op_assign
id|ti
suffix:semicolon
id|lc-&gt;touched
op_assign
l_int|0
suffix:semicolon
id|lc-&gt;region_size
op_assign
id|region_size
suffix:semicolon
id|lc-&gt;region_count
op_assign
id|region_count
suffix:semicolon
id|lc-&gt;sync
op_assign
id|sync
suffix:semicolon
multiline_comment|/*&n;&t; * Work out how many words we need to hold the bitset.&n;&t; */
id|bitset_size
op_assign
id|dm_round_up
c_func
(paren
id|region_count
comma
r_sizeof
(paren
op_star
id|lc-&gt;clean_bits
)paren
op_lshift
id|BYTE_SHIFT
)paren
suffix:semicolon
id|bitset_size
op_rshift_assign
id|BYTE_SHIFT
suffix:semicolon
id|lc-&gt;bitset_uint32_count
op_assign
id|bitset_size
op_div
l_int|4
suffix:semicolon
id|lc-&gt;clean_bits
op_assign
id|vmalloc
c_func
(paren
id|bitset_size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lc-&gt;clean_bits
)paren
(brace
id|DMWARN
c_func
(paren
l_string|&quot;couldn&squot;t allocate clean bitset&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|lc
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|lc-&gt;clean_bits
comma
op_minus
l_int|1
comma
id|bitset_size
)paren
suffix:semicolon
id|lc-&gt;sync_bits
op_assign
id|vmalloc
c_func
(paren
id|bitset_size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lc-&gt;sync_bits
)paren
(brace
id|DMWARN
c_func
(paren
l_string|&quot;couldn&squot;t allocate sync bitset&quot;
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|lc-&gt;clean_bits
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|lc
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|lc-&gt;sync_bits
comma
(paren
id|sync
op_eq
id|NOSYNC
)paren
ques
c_cond
op_minus
l_int|1
suffix:colon
l_int|0
comma
id|bitset_size
)paren
suffix:semicolon
id|lc-&gt;sync_count
op_assign
(paren
id|sync
op_eq
id|NOSYNC
)paren
ques
c_cond
id|region_count
suffix:colon
l_int|0
suffix:semicolon
id|lc-&gt;recovering_bits
op_assign
id|vmalloc
c_func
(paren
id|bitset_size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lc-&gt;recovering_bits
)paren
(brace
id|DMWARN
c_func
(paren
l_string|&quot;couldn&squot;t allocate sync bitset&quot;
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|lc-&gt;sync_bits
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|lc-&gt;clean_bits
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|lc
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|lc-&gt;recovering_bits
comma
l_int|0
comma
id|bitset_size
)paren
suffix:semicolon
id|lc-&gt;sync_search
op_assign
l_int|0
suffix:semicolon
id|log-&gt;context
op_assign
id|lc
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|core_dtr
r_static
r_void
id|core_dtr
c_func
(paren
r_struct
id|dirty_log
op_star
id|log
)paren
(brace
r_struct
id|log_c
op_star
id|lc
op_assign
(paren
r_struct
id|log_c
op_star
)paren
id|log-&gt;context
suffix:semicolon
id|vfree
c_func
(paren
id|lc-&gt;clean_bits
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|lc-&gt;sync_bits
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|lc-&gt;recovering_bits
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|lc
)paren
suffix:semicolon
)brace
multiline_comment|/*----------------------------------------------------------------&n; * disk log constructor/destructor&n; *&n; * argv contains log_device region_size followed optionally by [no]sync&n; *--------------------------------------------------------------*/
DECL|function|disk_ctr
r_static
r_int
id|disk_ctr
c_func
(paren
r_struct
id|dirty_log
op_star
id|log
comma
r_struct
id|dm_target
op_star
id|ti
comma
r_int
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
(brace
r_int
id|r
suffix:semicolon
r_int
id|size
suffix:semicolon
r_struct
id|log_c
op_star
id|lc
suffix:semicolon
r_struct
id|dm_dev
op_star
id|dev
suffix:semicolon
r_if
c_cond
(paren
id|argc
template_param
l_int|3
)paren
(brace
id|DMWARN
c_func
(paren
l_string|&quot;wrong number of arguments to disk mirror log&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|r
op_assign
id|dm_get_device
c_func
(paren
id|ti
comma
id|argv
(braket
l_int|0
)braket
comma
l_int|0
comma
l_int|0
multiline_comment|/* FIXME */
comma
id|FMODE_READ
op_or
id|FMODE_WRITE
comma
op_amp
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
r_return
id|r
suffix:semicolon
id|r
op_assign
id|core_ctr
c_func
(paren
id|log
comma
id|ti
comma
id|argc
op_minus
l_int|1
comma
id|argv
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
(brace
id|dm_put_device
c_func
(paren
id|ti
comma
id|dev
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
id|lc
op_assign
(paren
r_struct
id|log_c
op_star
)paren
id|log-&gt;context
suffix:semicolon
id|lc-&gt;log_dev
op_assign
id|dev
suffix:semicolon
multiline_comment|/* setup the disk header fields */
id|lc-&gt;header_location.bdev
op_assign
id|lc-&gt;log_dev-&gt;bdev
suffix:semicolon
id|lc-&gt;header_location.sector
op_assign
l_int|0
suffix:semicolon
id|lc-&gt;header_location.count
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * We can&squot;t read less than this amount, even though we&squot;ll&n;&t; * not be using most of this space.&n;&t; */
id|lc-&gt;disk_header
op_assign
id|vmalloc
c_func
(paren
l_int|1
op_lshift
id|SECTOR_SHIFT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lc-&gt;disk_header
)paren
r_goto
id|bad
suffix:semicolon
multiline_comment|/* setup the disk bitset fields */
id|lc-&gt;bits_location.bdev
op_assign
id|lc-&gt;log_dev-&gt;bdev
suffix:semicolon
id|lc-&gt;bits_location.sector
op_assign
id|LOG_OFFSET
suffix:semicolon
id|size
op_assign
id|dm_round_up
c_func
(paren
id|lc-&gt;bitset_uint32_count
op_star
r_sizeof
(paren
r_uint32
)paren
comma
l_int|1
op_lshift
id|SECTOR_SHIFT
)paren
suffix:semicolon
id|lc-&gt;bits_location.count
op_assign
id|size
op_rshift
id|SECTOR_SHIFT
suffix:semicolon
id|lc-&gt;disk_bits
op_assign
id|vmalloc
c_func
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lc-&gt;disk_bits
)paren
(brace
id|vfree
c_func
(paren
id|lc-&gt;disk_header
)paren
suffix:semicolon
r_goto
id|bad
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|bad
suffix:colon
id|dm_put_device
c_func
(paren
id|ti
comma
id|lc-&gt;log_dev
)paren
suffix:semicolon
id|core_dtr
c_func
(paren
id|log
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
DECL|function|disk_dtr
r_static
r_void
id|disk_dtr
c_func
(paren
r_struct
id|dirty_log
op_star
id|log
)paren
(brace
r_struct
id|log_c
op_star
id|lc
op_assign
(paren
r_struct
id|log_c
op_star
)paren
id|log-&gt;context
suffix:semicolon
id|dm_put_device
c_func
(paren
id|lc-&gt;ti
comma
id|lc-&gt;log_dev
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|lc-&gt;disk_header
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|lc-&gt;disk_bits
)paren
suffix:semicolon
id|core_dtr
c_func
(paren
id|log
)paren
suffix:semicolon
)brace
DECL|function|count_bits32
r_static
r_int
id|count_bits32
c_func
(paren
r_uint32
op_star
id|addr
comma
r_int
id|size
)paren
(brace
r_int
id|count
op_assign
l_int|0
comma
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|size
suffix:semicolon
id|i
op_increment
)paren
(brace
id|count
op_add_assign
id|hweight32
c_func
(paren
op_star
(paren
id|addr
op_plus
id|i
)paren
)paren
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|function|disk_resume
r_static
r_int
id|disk_resume
c_func
(paren
r_struct
id|dirty_log
op_star
id|log
)paren
(brace
r_int
id|r
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|log_c
op_star
id|lc
op_assign
(paren
r_struct
id|log_c
op_star
)paren
id|log-&gt;context
suffix:semicolon
r_int
id|size
op_assign
id|lc-&gt;bitset_uint32_count
op_star
r_sizeof
(paren
r_uint32
)paren
suffix:semicolon
multiline_comment|/* read the disk header */
id|r
op_assign
id|read_header
c_func
(paren
id|lc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
r_return
id|r
suffix:semicolon
multiline_comment|/* read the bits */
id|r
op_assign
id|read_bits
c_func
(paren
id|lc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
r_return
id|r
suffix:semicolon
multiline_comment|/* set or clear any new bits */
r_if
c_cond
(paren
id|lc-&gt;sync
op_eq
id|NOSYNC
)paren
r_for
c_loop
(paren
id|i
op_assign
id|lc-&gt;header.nr_regions
suffix:semicolon
id|i
OL
id|lc-&gt;region_count
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* FIXME: amazingly inefficient */
id|log_set_bit
c_func
(paren
id|lc
comma
id|lc-&gt;clean_bits
comma
id|i
)paren
suffix:semicolon
r_else
r_for
c_loop
(paren
id|i
op_assign
id|lc-&gt;header.nr_regions
suffix:semicolon
id|i
OL
id|lc-&gt;region_count
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* FIXME: amazingly inefficient */
id|log_clear_bit
c_func
(paren
id|lc
comma
id|lc-&gt;clean_bits
comma
id|i
)paren
suffix:semicolon
multiline_comment|/* copy clean across to sync */
id|memcpy
c_func
(paren
id|lc-&gt;sync_bits
comma
id|lc-&gt;clean_bits
comma
id|size
)paren
suffix:semicolon
id|lc-&gt;sync_count
op_assign
id|count_bits32
c_func
(paren
id|lc-&gt;clean_bits
comma
id|lc-&gt;bitset_uint32_count
)paren
suffix:semicolon
multiline_comment|/* write the bits */
id|r
op_assign
id|write_bits
c_func
(paren
id|lc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
r_return
id|r
suffix:semicolon
multiline_comment|/* set the correct number of regions in the header */
id|lc-&gt;header.nr_regions
op_assign
id|lc-&gt;region_count
suffix:semicolon
multiline_comment|/* write the new header */
r_return
id|write_header
c_func
(paren
id|lc
)paren
suffix:semicolon
)brace
DECL|function|core_get_region_size
r_static
id|sector_t
id|core_get_region_size
c_func
(paren
r_struct
id|dirty_log
op_star
id|log
)paren
(brace
r_struct
id|log_c
op_star
id|lc
op_assign
(paren
r_struct
id|log_c
op_star
)paren
id|log-&gt;context
suffix:semicolon
r_return
id|lc-&gt;region_size
suffix:semicolon
)brace
DECL|function|core_is_clean
r_static
r_int
id|core_is_clean
c_func
(paren
r_struct
id|dirty_log
op_star
id|log
comma
id|region_t
id|region
)paren
(brace
r_struct
id|log_c
op_star
id|lc
op_assign
(paren
r_struct
id|log_c
op_star
)paren
id|log-&gt;context
suffix:semicolon
r_return
id|log_test_bit
c_func
(paren
id|lc-&gt;clean_bits
comma
id|region
)paren
suffix:semicolon
)brace
DECL|function|core_in_sync
r_static
r_int
id|core_in_sync
c_func
(paren
r_struct
id|dirty_log
op_star
id|log
comma
id|region_t
id|region
comma
r_int
id|block
)paren
(brace
r_struct
id|log_c
op_star
id|lc
op_assign
(paren
r_struct
id|log_c
op_star
)paren
id|log-&gt;context
suffix:semicolon
r_return
id|log_test_bit
c_func
(paren
id|lc-&gt;sync_bits
comma
id|region
)paren
suffix:semicolon
)brace
DECL|function|core_flush
r_static
r_int
id|core_flush
c_func
(paren
r_struct
id|dirty_log
op_star
id|log
)paren
(brace
multiline_comment|/* no op */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|disk_flush
r_static
r_int
id|disk_flush
c_func
(paren
r_struct
id|dirty_log
op_star
id|log
)paren
(brace
r_int
id|r
suffix:semicolon
r_struct
id|log_c
op_star
id|lc
op_assign
(paren
r_struct
id|log_c
op_star
)paren
id|log-&gt;context
suffix:semicolon
multiline_comment|/* only write if the log has changed */
r_if
c_cond
(paren
op_logical_neg
id|lc-&gt;touched
)paren
r_return
l_int|0
suffix:semicolon
id|r
op_assign
id|write_bits
c_func
(paren
id|lc
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|r
)paren
id|lc-&gt;touched
op_assign
l_int|0
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
DECL|function|core_mark_region
r_static
r_void
id|core_mark_region
c_func
(paren
r_struct
id|dirty_log
op_star
id|log
comma
id|region_t
id|region
)paren
(brace
r_struct
id|log_c
op_star
id|lc
op_assign
(paren
r_struct
id|log_c
op_star
)paren
id|log-&gt;context
suffix:semicolon
id|log_clear_bit
c_func
(paren
id|lc
comma
id|lc-&gt;clean_bits
comma
id|region
)paren
suffix:semicolon
)brace
DECL|function|core_clear_region
r_static
r_void
id|core_clear_region
c_func
(paren
r_struct
id|dirty_log
op_star
id|log
comma
id|region_t
id|region
)paren
(brace
r_struct
id|log_c
op_star
id|lc
op_assign
(paren
r_struct
id|log_c
op_star
)paren
id|log-&gt;context
suffix:semicolon
id|log_set_bit
c_func
(paren
id|lc
comma
id|lc-&gt;clean_bits
comma
id|region
)paren
suffix:semicolon
)brace
DECL|function|core_get_resync_work
r_static
r_int
id|core_get_resync_work
c_func
(paren
r_struct
id|dirty_log
op_star
id|log
comma
id|region_t
op_star
id|region
)paren
(brace
r_struct
id|log_c
op_star
id|lc
op_assign
(paren
r_struct
id|log_c
op_star
)paren
id|log-&gt;context
suffix:semicolon
r_if
c_cond
(paren
id|lc-&gt;sync_search
op_ge
id|lc-&gt;region_count
)paren
r_return
l_int|0
suffix:semicolon
r_do
(brace
op_star
id|region
op_assign
id|find_next_zero_bit
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|lc-&gt;sync_bits
comma
id|lc-&gt;region_count
comma
id|lc-&gt;sync_search
)paren
suffix:semicolon
id|lc-&gt;sync_search
op_assign
op_star
id|region
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_star
id|region
op_eq
id|lc-&gt;region_count
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_while
c_loop
(paren
id|log_test_bit
c_func
(paren
id|lc-&gt;recovering_bits
comma
op_star
id|region
)paren
)paren
suffix:semicolon
id|log_set_bit
c_func
(paren
id|lc
comma
id|lc-&gt;recovering_bits
comma
op_star
id|region
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|core_complete_resync_work
r_static
r_void
id|core_complete_resync_work
c_func
(paren
r_struct
id|dirty_log
op_star
id|log
comma
id|region_t
id|region
comma
r_int
id|success
)paren
(brace
r_struct
id|log_c
op_star
id|lc
op_assign
(paren
r_struct
id|log_c
op_star
)paren
id|log-&gt;context
suffix:semicolon
id|log_clear_bit
c_func
(paren
id|lc
comma
id|lc-&gt;recovering_bits
comma
id|region
)paren
suffix:semicolon
r_if
c_cond
(paren
id|success
)paren
(brace
id|log_set_bit
c_func
(paren
id|lc
comma
id|lc-&gt;sync_bits
comma
id|region
)paren
suffix:semicolon
id|lc-&gt;sync_count
op_increment
suffix:semicolon
)brace
)brace
DECL|function|core_get_sync_count
r_static
id|region_t
id|core_get_sync_count
c_func
(paren
r_struct
id|dirty_log
op_star
id|log
)paren
(brace
r_struct
id|log_c
op_star
id|lc
op_assign
(paren
r_struct
id|log_c
op_star
)paren
id|log-&gt;context
suffix:semicolon
r_return
id|lc-&gt;sync_count
suffix:semicolon
)brace
DECL|macro|DMEMIT_SYNC
mdefine_line|#define&t;DMEMIT_SYNC &bslash;&n;&t;if (lc-&gt;sync != DEFAULTSYNC) &bslash;&n;&t;&t;DMEMIT(&quot;%ssync &quot;, lc-&gt;sync == NOSYNC ? &quot;no&quot; : &quot;&quot;)
DECL|function|core_status
r_static
r_int
id|core_status
c_func
(paren
r_struct
id|dirty_log
op_star
id|log
comma
id|status_type_t
id|status
comma
r_char
op_star
id|result
comma
r_int
r_int
id|maxlen
)paren
(brace
r_int
id|sz
op_assign
l_int|0
suffix:semicolon
r_struct
id|log_c
op_star
id|lc
op_assign
id|log-&gt;context
suffix:semicolon
r_switch
c_cond
(paren
id|status
)paren
(brace
r_case
id|STATUSTYPE_INFO
suffix:colon
r_break
suffix:semicolon
r_case
id|STATUSTYPE_TABLE
suffix:colon
id|DMEMIT
c_func
(paren
l_string|&quot;%s %u &quot;
id|SECTOR_FORMAT
l_string|&quot; &quot;
comma
id|log-&gt;type-&gt;name
comma
id|lc-&gt;sync
op_eq
id|DEFAULTSYNC
ques
c_cond
l_int|1
suffix:colon
l_int|2
comma
id|lc-&gt;region_size
)paren
suffix:semicolon
id|DMEMIT_SYNC
suffix:semicolon
)brace
r_return
id|sz
suffix:semicolon
)brace
DECL|function|disk_status
r_static
r_int
id|disk_status
c_func
(paren
r_struct
id|dirty_log
op_star
id|log
comma
id|status_type_t
id|status
comma
r_char
op_star
id|result
comma
r_int
r_int
id|maxlen
)paren
(brace
r_int
id|sz
op_assign
l_int|0
suffix:semicolon
r_char
id|buffer
(braket
l_int|16
)braket
suffix:semicolon
r_struct
id|log_c
op_star
id|lc
op_assign
id|log-&gt;context
suffix:semicolon
r_switch
c_cond
(paren
id|status
)paren
(brace
r_case
id|STATUSTYPE_INFO
suffix:colon
r_break
suffix:semicolon
r_case
id|STATUSTYPE_TABLE
suffix:colon
id|format_dev_t
c_func
(paren
id|buffer
comma
id|lc-&gt;log_dev-&gt;bdev-&gt;bd_dev
)paren
suffix:semicolon
id|DMEMIT
c_func
(paren
l_string|&quot;%s %u %s &quot;
id|SECTOR_FORMAT
l_string|&quot; &quot;
comma
id|log-&gt;type-&gt;name
comma
id|lc-&gt;sync
op_eq
id|DEFAULTSYNC
ques
c_cond
l_int|2
suffix:colon
l_int|3
comma
id|buffer
comma
id|lc-&gt;region_size
)paren
suffix:semicolon
id|DMEMIT_SYNC
suffix:semicolon
)brace
r_return
id|sz
suffix:semicolon
)brace
DECL|variable|_core_type
r_static
r_struct
id|dirty_log_type
id|_core_type
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;core&quot;
comma
dot
id|module
op_assign
id|THIS_MODULE
comma
dot
id|ctr
op_assign
id|core_ctr
comma
dot
id|dtr
op_assign
id|core_dtr
comma
dot
id|get_region_size
op_assign
id|core_get_region_size
comma
dot
id|is_clean
op_assign
id|core_is_clean
comma
dot
id|in_sync
op_assign
id|core_in_sync
comma
dot
id|flush
op_assign
id|core_flush
comma
dot
id|mark_region
op_assign
id|core_mark_region
comma
dot
id|clear_region
op_assign
id|core_clear_region
comma
dot
id|get_resync_work
op_assign
id|core_get_resync_work
comma
dot
id|complete_resync_work
op_assign
id|core_complete_resync_work
comma
dot
id|get_sync_count
op_assign
id|core_get_sync_count
comma
dot
id|status
op_assign
id|core_status
comma
)brace
suffix:semicolon
DECL|variable|_disk_type
r_static
r_struct
id|dirty_log_type
id|_disk_type
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;disk&quot;
comma
dot
id|module
op_assign
id|THIS_MODULE
comma
dot
id|ctr
op_assign
id|disk_ctr
comma
dot
id|dtr
op_assign
id|disk_dtr
comma
dot
id|suspend
op_assign
id|disk_flush
comma
dot
id|resume
op_assign
id|disk_resume
comma
dot
id|get_region_size
op_assign
id|core_get_region_size
comma
dot
id|is_clean
op_assign
id|core_is_clean
comma
dot
id|in_sync
op_assign
id|core_in_sync
comma
dot
id|flush
op_assign
id|disk_flush
comma
dot
id|mark_region
op_assign
id|core_mark_region
comma
dot
id|clear_region
op_assign
id|core_clear_region
comma
dot
id|get_resync_work
op_assign
id|core_get_resync_work
comma
dot
id|complete_resync_work
op_assign
id|core_complete_resync_work
comma
dot
id|get_sync_count
op_assign
id|core_get_sync_count
comma
dot
id|status
op_assign
id|disk_status
comma
)brace
suffix:semicolon
DECL|function|dm_dirty_log_init
r_int
id|__init
id|dm_dirty_log_init
c_func
(paren
r_void
)paren
(brace
r_int
id|r
suffix:semicolon
id|r
op_assign
id|dm_register_dirty_log_type
c_func
(paren
op_amp
id|_core_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
id|DMWARN
c_func
(paren
l_string|&quot;couldn&squot;t register core log&quot;
)paren
suffix:semicolon
id|r
op_assign
id|dm_register_dirty_log_type
c_func
(paren
op_amp
id|_disk_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
(brace
id|DMWARN
c_func
(paren
l_string|&quot;couldn&squot;t register disk type&quot;
)paren
suffix:semicolon
id|dm_unregister_dirty_log_type
c_func
(paren
op_amp
id|_core_type
)paren
suffix:semicolon
)brace
r_return
id|r
suffix:semicolon
)brace
DECL|function|dm_dirty_log_exit
r_void
id|dm_dirty_log_exit
c_func
(paren
r_void
)paren
(brace
id|dm_unregister_dirty_log_type
c_func
(paren
op_amp
id|_disk_type
)paren
suffix:semicolon
id|dm_unregister_dirty_log_type
c_func
(paren
op_amp
id|_core_type
)paren
suffix:semicolon
)brace
DECL|variable|dm_register_dirty_log_type
id|EXPORT_SYMBOL
c_func
(paren
id|dm_register_dirty_log_type
)paren
suffix:semicolon
DECL|variable|dm_unregister_dirty_log_type
id|EXPORT_SYMBOL
c_func
(paren
id|dm_unregister_dirty_log_type
)paren
suffix:semicolon
DECL|variable|dm_create_dirty_log
id|EXPORT_SYMBOL
c_func
(paren
id|dm_create_dirty_log
)paren
suffix:semicolon
DECL|variable|dm_destroy_dirty_log
id|EXPORT_SYMBOL
c_func
(paren
id|dm_destroy_dirty_log
)paren
suffix:semicolon
eof
