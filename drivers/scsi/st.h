macro_line|#ifndef _ST_H
DECL|macro|_ST_H
mdefine_line|#define _ST_H
multiline_comment|/*&n;   $Header: /usr/src/linux/kernel/blk_drv/scsi/RCS/st.h,v 1.1 1992/04/24 18:01:50 root Exp root $&n; */
macro_line|#ifndef _SCSI_H
macro_line|#include &quot;scsi.h&quot;
macro_line|#endif
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
multiline_comment|/* The tape buffer descriptor. */
r_typedef
r_struct
(brace
DECL|member|in_use
r_int
r_char
id|in_use
suffix:semicolon
DECL|member|dma
r_int
r_char
id|dma
suffix:semicolon
multiline_comment|/* DMA-able buffer */
DECL|member|buffer_size
r_int
id|buffer_size
suffix:semicolon
DECL|member|buffer_blocks
r_int
id|buffer_blocks
suffix:semicolon
DECL|member|buffer_bytes
r_int
id|buffer_bytes
suffix:semicolon
DECL|member|read_pointer
r_int
id|read_pointer
suffix:semicolon
DECL|member|writing
r_int
id|writing
suffix:semicolon
DECL|member|midlevel_result
r_int
id|midlevel_result
suffix:semicolon
DECL|member|syscall_result
r_int
id|syscall_result
suffix:semicolon
DECL|member|last_SRpnt
id|Scsi_Request
op_star
id|last_SRpnt
suffix:semicolon
DECL|member|b_data
r_int
r_char
op_star
id|b_data
suffix:semicolon
DECL|member|use_sg
r_int
r_int
id|use_sg
suffix:semicolon
multiline_comment|/* zero or number of segments for this adapter */
DECL|member|sg_segs
r_int
r_int
id|sg_segs
suffix:semicolon
multiline_comment|/* total number of allocated segments */
DECL|member|orig_sg_segs
r_int
r_int
id|orig_sg_segs
suffix:semicolon
multiline_comment|/* number of segments allocated at first try */
DECL|member|sg
r_struct
id|scatterlist
id|sg
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* MUST BE last item */
DECL|typedef|ST_buffer
)brace
id|ST_buffer
suffix:semicolon
multiline_comment|/* The tape mode definition */
r_typedef
r_struct
(brace
DECL|member|defined
r_int
r_char
id|defined
suffix:semicolon
DECL|member|sysv
r_int
r_char
id|sysv
suffix:semicolon
multiline_comment|/* SYS V semantics? */
DECL|member|do_async_writes
r_int
r_char
id|do_async_writes
suffix:semicolon
DECL|member|do_buffer_writes
r_int
r_char
id|do_buffer_writes
suffix:semicolon
DECL|member|do_read_ahead
r_int
r_char
id|do_read_ahead
suffix:semicolon
DECL|member|defaults_for_writes
r_int
r_char
id|defaults_for_writes
suffix:semicolon
DECL|member|default_compression
r_int
r_char
id|default_compression
suffix:semicolon
multiline_comment|/* 0 = don&squot;t touch, etc */
DECL|member|default_density
r_int
id|default_density
suffix:semicolon
multiline_comment|/* Forced density, -1 = no value */
DECL|member|default_blksize
r_int
id|default_blksize
suffix:semicolon
multiline_comment|/* Forced blocksize, -1 = no value */
DECL|typedef|ST_mode
)brace
id|ST_mode
suffix:semicolon
DECL|macro|ST_NBR_MODE_BITS
mdefine_line|#define ST_NBR_MODE_BITS 2
DECL|macro|ST_NBR_MODES
mdefine_line|#define ST_NBR_MODES (1 &lt;&lt; ST_NBR_MODE_BITS)
DECL|macro|ST_MODE_SHIFT
mdefine_line|#define ST_MODE_SHIFT (7 - ST_NBR_MODE_BITS)
DECL|macro|ST_MODE_MASK
mdefine_line|#define ST_MODE_MASK ((ST_NBR_MODES - 1) &lt;&lt; ST_MODE_SHIFT)
DECL|macro|ST_MAX_TAPES
mdefine_line|#define ST_MAX_TAPES (1 &lt;&lt; ST_MODE_SHIFT)
multiline_comment|/* The status related to each partition */
r_typedef
r_struct
(brace
DECL|member|rw
r_int
r_char
id|rw
suffix:semicolon
DECL|member|eof
r_int
r_char
id|eof
suffix:semicolon
DECL|member|at_sm
r_int
r_char
id|at_sm
suffix:semicolon
DECL|member|last_block_valid
r_int
r_char
id|last_block_valid
suffix:semicolon
DECL|member|last_block_visited
id|u32
id|last_block_visited
suffix:semicolon
DECL|member|drv_block
r_int
id|drv_block
suffix:semicolon
multiline_comment|/* The block where the drive head is */
DECL|member|drv_file
r_int
id|drv_file
suffix:semicolon
DECL|typedef|ST_partstat
)brace
id|ST_partstat
suffix:semicolon
DECL|macro|ST_NBR_PARTITIONS
mdefine_line|#define ST_NBR_PARTITIONS 4
multiline_comment|/* The tape drive descriptor */
r_typedef
r_struct
(brace
DECL|member|devt
id|kdev_t
id|devt
suffix:semicolon
DECL|member|device
id|Scsi_Device
op_star
id|device
suffix:semicolon
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
multiline_comment|/* For serialization */
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
multiline_comment|/* For SCSI commands */
DECL|member|buffer
id|ST_buffer
op_star
id|buffer
suffix:semicolon
multiline_comment|/* Drive characteristics */
DECL|member|omit_blklims
r_int
r_char
id|omit_blklims
suffix:semicolon
DECL|member|do_auto_lock
r_int
r_char
id|do_auto_lock
suffix:semicolon
DECL|member|can_bsr
r_int
r_char
id|can_bsr
suffix:semicolon
DECL|member|can_partitions
r_int
r_char
id|can_partitions
suffix:semicolon
DECL|member|two_fm
r_int
r_char
id|two_fm
suffix:semicolon
DECL|member|fast_mteom
r_int
r_char
id|fast_mteom
suffix:semicolon
DECL|member|restr_dma
r_int
r_char
id|restr_dma
suffix:semicolon
DECL|member|scsi2_logical
r_int
r_char
id|scsi2_logical
suffix:semicolon
DECL|member|default_drvbuffer
r_int
r_char
id|default_drvbuffer
suffix:semicolon
multiline_comment|/* 0xff = don&squot;t touch, value 3 bits */
DECL|member|tape_type
r_int
id|tape_type
suffix:semicolon
DECL|member|write_threshold
r_int
id|write_threshold
suffix:semicolon
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
multiline_comment|/* timeout for normal commands */
DECL|member|long_timeout
r_int
id|long_timeout
suffix:semicolon
multiline_comment|/* timeout for commands known to take long time */
multiline_comment|/* Mode characteristics */
DECL|member|modes
id|ST_mode
id|modes
(braket
id|ST_NBR_MODES
)braket
suffix:semicolon
DECL|member|current_mode
r_int
id|current_mode
suffix:semicolon
DECL|member|de_r
id|devfs_handle_t
id|de_r
(braket
id|ST_NBR_MODES
)braket
suffix:semicolon
multiline_comment|/*  Rewind entries     */
DECL|member|de_n
id|devfs_handle_t
id|de_n
(braket
id|ST_NBR_MODES
)braket
suffix:semicolon
multiline_comment|/*  No-rewind entries  */
multiline_comment|/* Status variables */
DECL|member|partition
r_int
id|partition
suffix:semicolon
DECL|member|new_partition
r_int
id|new_partition
suffix:semicolon
DECL|member|nbr_partitions
r_int
id|nbr_partitions
suffix:semicolon
multiline_comment|/* zero until partition support enabled */
DECL|member|ps
id|ST_partstat
id|ps
(braket
id|ST_NBR_PARTITIONS
)braket
suffix:semicolon
DECL|member|dirty
r_int
r_char
id|dirty
suffix:semicolon
DECL|member|ready
r_int
r_char
id|ready
suffix:semicolon
DECL|member|write_prot
r_int
r_char
id|write_prot
suffix:semicolon
DECL|member|drv_write_prot
r_int
r_char
id|drv_write_prot
suffix:semicolon
DECL|member|in_use
r_int
r_char
id|in_use
suffix:semicolon
DECL|member|blksize_changed
r_int
r_char
id|blksize_changed
suffix:semicolon
DECL|member|density_changed
r_int
r_char
id|density_changed
suffix:semicolon
DECL|member|compression_changed
r_int
r_char
id|compression_changed
suffix:semicolon
DECL|member|drv_buffer
r_int
r_char
id|drv_buffer
suffix:semicolon
DECL|member|density
r_int
r_char
id|density
suffix:semicolon
DECL|member|door_locked
r_int
r_char
id|door_locked
suffix:semicolon
DECL|member|autorew_dev
r_int
r_char
id|autorew_dev
suffix:semicolon
multiline_comment|/* auto-rewind device */
DECL|member|rew_at_close
r_int
r_char
id|rew_at_close
suffix:semicolon
multiline_comment|/* rewind necessary at close */
DECL|member|inited
r_int
r_char
id|inited
suffix:semicolon
DECL|member|block_size
r_int
id|block_size
suffix:semicolon
DECL|member|min_block
r_int
id|min_block
suffix:semicolon
DECL|member|max_block
r_int
id|max_block
suffix:semicolon
DECL|member|recover_count
r_int
id|recover_count
suffix:semicolon
multiline_comment|/* From tape opening */
DECL|member|recover_reg
r_int
id|recover_reg
suffix:semicolon
multiline_comment|/* From last status call */
macro_line|#if DEBUG
DECL|member|write_pending
r_int
r_char
id|write_pending
suffix:semicolon
DECL|member|nbr_finished
r_int
id|nbr_finished
suffix:semicolon
DECL|member|nbr_waits
r_int
id|nbr_waits
suffix:semicolon
DECL|member|last_cmnd
r_int
r_char
id|last_cmnd
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|last_sense
r_int
r_char
id|last_sense
(braket
l_int|16
)braket
suffix:semicolon
macro_line|#endif
DECL|typedef|Scsi_Tape
)brace
id|Scsi_Tape
suffix:semicolon
multiline_comment|/* Values of eof */
DECL|macro|ST_NOEOF
mdefine_line|#define&t;ST_NOEOF&t;0
DECL|macro|ST_FM_HIT
mdefine_line|#define ST_FM_HIT       1
DECL|macro|ST_FM
mdefine_line|#define ST_FM           2
DECL|macro|ST_EOM_OK
mdefine_line|#define ST_EOM_OK       3
DECL|macro|ST_EOM_ERROR
mdefine_line|#define ST_EOM_ERROR&t;4
DECL|macro|ST_EOD_1
mdefine_line|#define&t;ST_EOD_1        5
DECL|macro|ST_EOD_2
mdefine_line|#define ST_EOD_2        6
DECL|macro|ST_EOD
mdefine_line|#define ST_EOD&t;&t;7
multiline_comment|/* EOD hit while reading =&gt; ST_EOD_1 =&gt; return zero =&gt; ST_EOD_2 =&gt;&n;   return zero =&gt; ST_EOD, return ENOSPC */
multiline_comment|/* Values of rw */
DECL|macro|ST_IDLE
mdefine_line|#define&t;ST_IDLE&t;&t;0
DECL|macro|ST_READING
mdefine_line|#define&t;ST_READING&t;1
DECL|macro|ST_WRITING
mdefine_line|#define&t;ST_WRITING&t;2
multiline_comment|/* Values of ready state */
DECL|macro|ST_READY
mdefine_line|#define ST_READY&t;0
DECL|macro|ST_NOT_READY
mdefine_line|#define ST_NOT_READY&t;1
DECL|macro|ST_NO_TAPE
mdefine_line|#define ST_NO_TAPE&t;2
multiline_comment|/* Values for door lock state */
DECL|macro|ST_UNLOCKED
mdefine_line|#define ST_UNLOCKED&t;0
DECL|macro|ST_LOCKED_EXPLICIT
mdefine_line|#define ST_LOCKED_EXPLICIT 1
DECL|macro|ST_LOCKED_AUTO
mdefine_line|#define ST_LOCKED_AUTO  2
DECL|macro|ST_LOCK_FAILS
mdefine_line|#define ST_LOCK_FAILS   3
multiline_comment|/* Positioning SCSI-commands for Tandberg, etc. drives */
DECL|macro|QFA_REQUEST_BLOCK
mdefine_line|#define&t;QFA_REQUEST_BLOCK&t;0x02
DECL|macro|QFA_SEEK_BLOCK
mdefine_line|#define&t;QFA_SEEK_BLOCK&t;&t;0x0c
multiline_comment|/* Setting the binary options */
DECL|macro|ST_DONT_TOUCH
mdefine_line|#define ST_DONT_TOUCH  0
DECL|macro|ST_NO
mdefine_line|#define ST_NO          1
DECL|macro|ST_YES
mdefine_line|#define ST_YES         2
macro_line|#endif
eof
