macro_line|#ifndef _FDC_IO_H
DECL|macro|_FDC_IO_H
mdefine_line|#define _FDC_IO_H
multiline_comment|/*&n; *    Copyright (C) 1993-1996 Bas Laarhoven,&n; *              (C) 1996-1997 Claus-Justus Heine.&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; * $Source: /homes/cvs/ftape-stacked/ftape/lowlevel/fdc-io.h,v $&n; * $Revision: 1.3 $&n; * $Date: 1997/10/05 19:18:06 $&n; *&n; *      This file contains the declarations for the low level&n; *      functions that communicate with the floppy disk controller,&n; *      for the QIC-40/80/3010/3020 floppy-tape driver &quot;ftape&quot; for&n; *      Linux.&n; */
macro_line|#include &lt;linux/fdreg.h&gt;
macro_line|#include &quot;../lowlevel/ftape-bsm.h&quot;
DECL|macro|FDC_SK_BIT
mdefine_line|#define FDC_SK_BIT      (0x20)
DECL|macro|FDC_MT_BIT
mdefine_line|#define FDC_MT_BIT      (0x80)
DECL|macro|FDC_READ
mdefine_line|#define FDC_READ        (FD_READ &amp; ~(FDC_SK_BIT | FDC_MT_BIT))
DECL|macro|FDC_WRITE
mdefine_line|#define FDC_WRITE       (FD_WRITE &amp; ~FDC_MT_BIT)
DECL|macro|FDC_READ_DELETED
mdefine_line|#define FDC_READ_DELETED  (0x4c)
DECL|macro|FDC_WRITE_DELETED
mdefine_line|#define FDC_WRITE_DELETED (0x49)
DECL|macro|FDC_VERIFY
mdefine_line|#define FDC_VERIFY        (0x56)
DECL|macro|FDC_READID
mdefine_line|#define FDC_READID      (0x4a)
DECL|macro|FDC_SENSED
mdefine_line|#define FDC_SENSED      (0x04)
DECL|macro|FDC_SENSEI
mdefine_line|#define FDC_SENSEI      (FD_SENSEI)
DECL|macro|FDC_FORMAT
mdefine_line|#define FDC_FORMAT      (FD_FORMAT)
DECL|macro|FDC_RECAL
mdefine_line|#define FDC_RECAL       (FD_RECALIBRATE)
DECL|macro|FDC_SEEK
mdefine_line|#define FDC_SEEK        (FD_SEEK)
DECL|macro|FDC_SPECIFY
mdefine_line|#define FDC_SPECIFY     (FD_SPECIFY)
DECL|macro|FDC_RECALIBR
mdefine_line|#define FDC_RECALIBR    (FD_RECALIBRATE)
DECL|macro|FDC_VERSION
mdefine_line|#define FDC_VERSION     (FD_VERSION)
DECL|macro|FDC_PERPEND
mdefine_line|#define FDC_PERPEND     (FD_PERPENDICULAR)
DECL|macro|FDC_DUMPREGS
mdefine_line|#define FDC_DUMPREGS    (FD_DUMPREGS)
DECL|macro|FDC_LOCK
mdefine_line|#define FDC_LOCK        (FD_LOCK)
DECL|macro|FDC_UNLOCK
mdefine_line|#define FDC_UNLOCK      (FD_UNLOCK)
DECL|macro|FDC_CONFIGURE
mdefine_line|#define FDC_CONFIGURE   (FD_CONFIGURE)
DECL|macro|FDC_DRIVE_SPEC
mdefine_line|#define FDC_DRIVE_SPEC  (0x8e)&t;/* i82078 has this (any others?) */
DECL|macro|FDC_PARTID
mdefine_line|#define FDC_PARTID      (0x18)&t;/* i82078 has this */
DECL|macro|FDC_SAVE
mdefine_line|#define FDC_SAVE        (0x2e)&t;/* i82078 has this (any others?) */
DECL|macro|FDC_RESTORE
mdefine_line|#define FDC_RESTORE     (0x4e)&t;/* i82078 has this (any others?) */
DECL|macro|FDC_STATUS_MASK
mdefine_line|#define FDC_STATUS_MASK (STATUS_BUSY | STATUS_DMA | STATUS_DIR | STATUS_READY)
DECL|macro|FDC_DATA_READY
mdefine_line|#define FDC_DATA_READY  (STATUS_READY)
DECL|macro|FDC_DATA_OUTPUT
mdefine_line|#define FDC_DATA_OUTPUT (STATUS_DIR)
DECL|macro|FDC_DATA_READY_MASK
mdefine_line|#define FDC_DATA_READY_MASK (STATUS_READY | STATUS_DIR)
DECL|macro|FDC_DATA_OUT_READY
mdefine_line|#define FDC_DATA_OUT_READY  (STATUS_READY | STATUS_DIR)
DECL|macro|FDC_DATA_IN_READY
mdefine_line|#define FDC_DATA_IN_READY   (STATUS_READY)
DECL|macro|FDC_BUSY
mdefine_line|#define FDC_BUSY        (STATUS_BUSY)
DECL|macro|FDC_CLK48_BIT
mdefine_line|#define FDC_CLK48_BIT   (0x80)
DECL|macro|FDC_SEL3V_BIT
mdefine_line|#define FDC_SEL3V_BIT   (0x40)
DECL|macro|ST0_INT_MASK
mdefine_line|#define ST0_INT_MASK    (ST0_INTR)
DECL|macro|FDC_INT_NORMAL
mdefine_line|#define FDC_INT_NORMAL  (ST0_INTR &amp; 0x00)
DECL|macro|FDC_INT_ABNORMAL
mdefine_line|#define FDC_INT_ABNORMAL (ST0_INTR &amp; 0x40)
DECL|macro|FDC_INT_INVALID
mdefine_line|#define FDC_INT_INVALID (ST0_INTR &amp; 0x80)
DECL|macro|FDC_INT_READYCH
mdefine_line|#define FDC_INT_READYCH (ST0_INTR &amp; 0xC0)
DECL|macro|ST0_SEEK_END
mdefine_line|#define ST0_SEEK_END    (ST0_SE)
DECL|macro|ST3_TRACK_0
mdefine_line|#define ST3_TRACK_0     (ST3_TZ)
DECL|macro|FDC_RESET_NOT
mdefine_line|#define FDC_RESET_NOT   (0x04)
DECL|macro|FDC_DMA_MODE
mdefine_line|#define FDC_DMA_MODE    (0x08)
DECL|macro|FDC_MOTOR_0
mdefine_line|#define FDC_MOTOR_0     (0x10)
DECL|macro|FDC_MOTOR_1
mdefine_line|#define FDC_MOTOR_1     (0x20)
r_typedef
r_struct
(brace
DECL|member|hook
r_void
(paren
op_star
op_star
id|hook
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* our wedge into the isr */
r_enum
(brace
DECL|enumerator|no_fdc
DECL|enumerator|i8272
DECL|enumerator|i82077
DECL|enumerator|i82077AA
DECL|enumerator|fc10
id|no_fdc
comma
id|i8272
comma
id|i82077
comma
id|i82077AA
comma
id|fc10
comma
DECL|enumerator|i82078
DECL|enumerator|i82078_1
id|i82078
comma
id|i82078_1
DECL|member|type
)brace
id|type
suffix:semicolon
multiline_comment|/* FDC type */
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
multiline_comment|/* FDC irq nr */
DECL|member|dma
r_int
r_int
id|dma
suffix:semicolon
multiline_comment|/* FDC dma channel nr */
DECL|member|sra
id|__u16
id|sra
suffix:semicolon
multiline_comment|/* Status register A (PS/2 only) */
DECL|member|srb
id|__u16
id|srb
suffix:semicolon
multiline_comment|/* Status register B (PS/2 only) */
DECL|member|dor
id|__u16
id|dor
suffix:semicolon
multiline_comment|/* Digital output register */
DECL|member|tdr
id|__u16
id|tdr
suffix:semicolon
multiline_comment|/* Tape Drive Register (82077SL-1 &amp;&n;&t;&t;&t;     82078 only) */
DECL|member|msr
id|__u16
id|msr
suffix:semicolon
multiline_comment|/* Main Status Register */
DECL|member|dsr
id|__u16
id|dsr
suffix:semicolon
multiline_comment|/* Datarate Select Register (8207x only) */
DECL|member|fifo
id|__u16
id|fifo
suffix:semicolon
multiline_comment|/* Data register / Fifo on 8207x */
DECL|member|dir
id|__u16
id|dir
suffix:semicolon
multiline_comment|/* Digital Input Register */
DECL|member|ccr
id|__u16
id|ccr
suffix:semicolon
multiline_comment|/* Configuration Control Register */
DECL|member|dor2
id|__u16
id|dor2
suffix:semicolon
multiline_comment|/* Alternate dor on MACH-2 controller,&n;&t;&t;&t;     also used with FC-10, meaning unknown */
DECL|typedef|fdc_config_info
)brace
id|fdc_config_info
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|fdc_data_rate_250
id|fdc_data_rate_250
op_assign
l_int|2
comma
DECL|enumerator|fdc_data_rate_300
id|fdc_data_rate_300
op_assign
l_int|1
comma
multiline_comment|/* any fdc in default configuration */
DECL|enumerator|fdc_data_rate_500
id|fdc_data_rate_500
op_assign
l_int|0
comma
DECL|enumerator|fdc_data_rate_1000
id|fdc_data_rate_1000
op_assign
l_int|3
comma
DECL|enumerator|fdc_data_rate_2000
id|fdc_data_rate_2000
op_assign
l_int|1
comma
multiline_comment|/* i82078-1: when using Data Rate Table #2 */
DECL|typedef|fdc_data_rate_type
)brace
id|fdc_data_rate_type
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|fdc_idle
id|fdc_idle
op_assign
l_int|0
comma
DECL|enumerator|fdc_reading_data
id|fdc_reading_data
op_assign
id|FDC_READ
comma
DECL|enumerator|fdc_seeking
id|fdc_seeking
op_assign
id|FDC_SEEK
comma
DECL|enumerator|fdc_writing_data
id|fdc_writing_data
op_assign
id|FDC_WRITE
comma
DECL|enumerator|fdc_deleting
id|fdc_deleting
op_assign
id|FDC_WRITE_DELETED
comma
DECL|enumerator|fdc_reading_id
id|fdc_reading_id
op_assign
id|FDC_READID
comma
DECL|enumerator|fdc_recalibrating
id|fdc_recalibrating
op_assign
id|FDC_RECAL
comma
DECL|enumerator|fdc_formatting
id|fdc_formatting
op_assign
id|FDC_FORMAT
comma
DECL|enumerator|fdc_verifying
id|fdc_verifying
op_assign
id|FDC_VERIFY
DECL|typedef|fdc_mode_enum
)brace
id|fdc_mode_enum
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|waiting
id|waiting
op_assign
l_int|0
comma
DECL|enumerator|reading
id|reading
comma
DECL|enumerator|writing
id|writing
comma
DECL|enumerator|formatting
id|formatting
comma
DECL|enumerator|verifying
id|verifying
comma
DECL|enumerator|deleting
id|deleting
comma
DECL|enumerator|done
id|done
comma
DECL|enumerator|error
id|error
comma
DECL|enumerator|mmapped
id|mmapped
comma
DECL|typedef|buffer_state_enum
)brace
id|buffer_state_enum
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|address
id|__u8
op_star
id|address
suffix:semicolon
DECL|member|status
r_volatile
id|buffer_state_enum
id|status
suffix:semicolon
DECL|member|ptr
r_volatile
id|__u8
op_star
id|ptr
suffix:semicolon
DECL|member|bytes
r_volatile
r_int
r_int
id|bytes
suffix:semicolon
DECL|member|segment_id
r_volatile
r_int
r_int
id|segment_id
suffix:semicolon
multiline_comment|/* bitmap for remainder of segment not yet handled.&n;&t; * one bit set for each bad sector that must be skipped.&n;&t; */
DECL|member|bad_sector_map
r_volatile
id|SectorMap
id|bad_sector_map
suffix:semicolon
multiline_comment|/* bitmap with bad data blocks in data buffer.&n;&t; * the errors in this map may be retried.&n;&t; */
DECL|member|soft_error_map
r_volatile
id|SectorMap
id|soft_error_map
suffix:semicolon
multiline_comment|/* bitmap with bad data blocks in data buffer&n;&t; * the errors in this map may not be retried.&n;&t; */
DECL|member|hard_error_map
r_volatile
id|SectorMap
id|hard_error_map
suffix:semicolon
multiline_comment|/* retry counter for soft errors.&n;&t; */
DECL|member|retry
r_volatile
r_int
id|retry
suffix:semicolon
multiline_comment|/* sectors to skip on retry ???&n;&t; */
DECL|member|skip
r_volatile
r_int
r_int
id|skip
suffix:semicolon
multiline_comment|/* nr of data blocks in data buffer&n;&t; */
DECL|member|data_offset
r_volatile
r_int
r_int
id|data_offset
suffix:semicolon
multiline_comment|/* offset in segment for first sector to be handled.&n;&t; */
DECL|member|sector_offset
r_volatile
r_int
r_int
id|sector_offset
suffix:semicolon
multiline_comment|/* size of cluster of good sectors to be handled.&n;&t; */
DECL|member|sector_count
r_volatile
r_int
r_int
id|sector_count
suffix:semicolon
multiline_comment|/* size of remaining part of segment to be handled.&n;&t; */
DECL|member|remaining
r_volatile
r_int
r_int
id|remaining
suffix:semicolon
multiline_comment|/* points to next segment (contiguous) to be handled,&n;&t; * or is zero if no read-ahead is allowed.&n;&t; */
DECL|member|next_segment
r_volatile
r_int
r_int
id|next_segment
suffix:semicolon
multiline_comment|/* flag being set if deleted data was read.&n;&t; */
DECL|member|deleted
r_volatile
r_int
id|deleted
suffix:semicolon
multiline_comment|/* floppy coordinates of first sector in segment */
DECL|member|head
r_volatile
id|__u8
id|head
suffix:semicolon
DECL|member|cyl
r_volatile
id|__u8
id|cyl
suffix:semicolon
DECL|member|sect
r_volatile
id|__u8
id|sect
suffix:semicolon
multiline_comment|/* gap to use when formatting */
DECL|member|gap3
id|__u8
id|gap3
suffix:semicolon
multiline_comment|/* flag set when buffer is mmaped */
DECL|member|mmapped
r_int
id|mmapped
suffix:semicolon
DECL|typedef|buffer_struct
)brace
id|buffer_struct
suffix:semicolon
multiline_comment|/*&n; *      fdc-io.c defined public variables&n; */
r_extern
r_volatile
id|fdc_mode_enum
id|fdc_mode
suffix:semicolon
r_extern
r_int
id|fdc_setup_error
suffix:semicolon
multiline_comment|/* outdated ??? */
r_extern
id|wait_queue_head_t
id|ftape_wait_intr
suffix:semicolon
r_extern
r_int
id|ftape_motor
suffix:semicolon
multiline_comment|/* fdc motor line state */
r_extern
r_volatile
r_int
id|ftape_current_cylinder
suffix:semicolon
multiline_comment|/* track nr FDC thinks we&squot;re on */
r_extern
r_volatile
id|__u8
id|fdc_head
suffix:semicolon
multiline_comment|/* FDC head */
r_extern
r_volatile
id|__u8
id|fdc_cyl
suffix:semicolon
multiline_comment|/* FDC track */
r_extern
r_volatile
id|__u8
id|fdc_sect
suffix:semicolon
multiline_comment|/* FDC sector */
r_extern
id|fdc_config_info
id|fdc
suffix:semicolon
multiline_comment|/* FDC hardware configuration */
r_extern
r_int
r_int
id|ft_fdc_base
suffix:semicolon
r_extern
r_int
r_int
id|ft_fdc_irq
suffix:semicolon
r_extern
r_int
r_int
id|ft_fdc_dma
suffix:semicolon
r_extern
r_int
r_int
id|ft_fdc_threshold
suffix:semicolon
r_extern
r_int
r_int
id|ft_fdc_rate_limit
suffix:semicolon
r_extern
r_int
id|ft_probe_fc10
suffix:semicolon
r_extern
r_int
id|ft_mach2
suffix:semicolon
multiline_comment|/*&n; *      fdc-io.c defined public functions&n; */
r_extern
r_void
id|fdc_catch_stray_interrupts
c_func
(paren
r_int
id|count
)paren
suffix:semicolon
r_extern
r_int
id|fdc_ready_wait
c_func
(paren
r_int
r_int
id|timeout
)paren
suffix:semicolon
r_extern
r_int
id|fdc_command
c_func
(paren
r_const
id|__u8
op_star
id|cmd_data
comma
r_int
id|cmd_len
)paren
suffix:semicolon
r_extern
r_int
id|fdc_result
c_func
(paren
id|__u8
op_star
id|res_data
comma
r_int
id|res_len
)paren
suffix:semicolon
r_extern
r_int
id|fdc_issue_command
c_func
(paren
r_const
id|__u8
op_star
id|out_data
comma
r_int
id|out_count
comma
id|__u8
op_star
id|in_data
comma
r_int
id|in_count
)paren
suffix:semicolon
r_extern
r_int
id|fdc_interrupt_wait
c_func
(paren
r_int
r_int
id|time
)paren
suffix:semicolon
r_extern
r_int
id|fdc_set_seek_rate
c_func
(paren
r_int
id|seek_rate
)paren
suffix:semicolon
r_extern
r_int
id|fdc_seek
c_func
(paren
r_int
id|track
)paren
suffix:semicolon
r_extern
r_int
id|fdc_sense_drive_status
c_func
(paren
r_int
op_star
id|st3
)paren
suffix:semicolon
r_extern
r_void
id|fdc_motor
c_func
(paren
r_int
id|motor
)paren
suffix:semicolon
r_extern
r_void
id|fdc_reset
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|fdc_recalibrate
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fdc_disable
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|fdc_fifo_threshold
c_func
(paren
id|__u8
id|threshold
comma
r_int
op_star
id|fifo_state
comma
r_int
op_star
id|lock_state
comma
r_int
op_star
id|fifo_thr
)paren
suffix:semicolon
r_extern
r_void
id|fdc_wait_calibrate
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|fdc_sense_interrupt_status
c_func
(paren
r_int
op_star
id|st0
comma
r_int
op_star
id|current_cylinder
)paren
suffix:semicolon
r_extern
r_void
id|fdc_save_drive_specs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fdc_restore_drive_specs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|fdc_set_data_rate
c_func
(paren
r_int
id|rate
)paren
suffix:semicolon
r_extern
r_void
id|fdc_set_write_precomp
c_func
(paren
r_int
id|precomp
)paren
suffix:semicolon
r_extern
r_int
id|fdc_release_irq_and_dma
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fdc_release_regions
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|fdc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|fdc_setup_read_write
c_func
(paren
id|buffer_struct
op_star
id|buff
comma
id|__u8
id|operation
)paren
suffix:semicolon
r_extern
r_int
id|fdc_setup_formatting
c_func
(paren
id|buffer_struct
op_star
id|buff
)paren
suffix:semicolon
macro_line|#endif
eof
