macro_line|#ifndef _FTAPE_CTL_H
DECL|macro|_FTAPE_CTL_H
mdefine_line|#define _FTAPE_CTL_H
multiline_comment|/*&n; * Copyright (C) 1993-1996 Bas Laarhoven,&n; *           (C) 1996-1997 Claus-Justus Heine.&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; * $Source: /homes/cvs/ftape-stacked/ftape/lowlevel/ftape-ctl.h,v $&n; * $Revision: 1.2 $&n; * $Date: 1997/10/05 19:18:09 $&n; *&n; *      This file contains the non-standard IOCTL related definitions&n; *      for the QIC-40/80/3010/3020 floppy-tape driver &quot;ftape&quot; for&n; *      Linux.&n; */
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/mtio.h&gt;
macro_line|#include &lt;linux/ftape-vendors.h&gt;
macro_line|#include &quot;../lowlevel/ftape-rw.h&quot;
macro_line|#include &lt;linux/ftape-header-segment.h&gt;
r_typedef
r_struct
(brace
DECL|member|used
r_int
id|used
suffix:semicolon
multiline_comment|/* any reading or writing done */
multiline_comment|/* isr statistics */
DECL|member|id_am_errors
r_int
r_int
id|id_am_errors
suffix:semicolon
multiline_comment|/* id address mark not found */
DECL|member|id_crc_errors
r_int
r_int
id|id_crc_errors
suffix:semicolon
multiline_comment|/* crc error in id address mark */
DECL|member|data_am_errors
r_int
r_int
id|data_am_errors
suffix:semicolon
multiline_comment|/* data address mark not found */
DECL|member|data_crc_errors
r_int
r_int
id|data_crc_errors
suffix:semicolon
multiline_comment|/* crc error in data field */
DECL|member|overrun_errors
r_int
r_int
id|overrun_errors
suffix:semicolon
multiline_comment|/* fdc access timing problem */
DECL|member|no_data_errors
r_int
r_int
id|no_data_errors
suffix:semicolon
multiline_comment|/* sector not found */
DECL|member|retries
r_int
r_int
id|retries
suffix:semicolon
multiline_comment|/* number of tape retries */
multiline_comment|/* ecc statistics */
DECL|member|crc_errors
r_int
r_int
id|crc_errors
suffix:semicolon
multiline_comment|/* crc error in data */
DECL|member|crc_failures
r_int
r_int
id|crc_failures
suffix:semicolon
multiline_comment|/* bad data without crc error */
DECL|member|ecc_failures
r_int
r_int
id|ecc_failures
suffix:semicolon
multiline_comment|/* failed to correct */
DECL|member|corrected
r_int
r_int
id|corrected
suffix:semicolon
multiline_comment|/* total sectors corrected */
multiline_comment|/* general statistics */
DECL|member|rewinds
r_int
r_int
id|rewinds
suffix:semicolon
multiline_comment|/* number of tape rewinds */
DECL|member|defects
r_int
r_int
id|defects
suffix:semicolon
multiline_comment|/* bad sectors due to media defects */
DECL|typedef|history_record
)brace
id|history_record
suffix:semicolon
multiline_comment|/* this structure contains * ALL * information that we want&n; * our child modules to know about, but don&squot;t want them to&n; * modify. &n; */
r_typedef
r_struct
(brace
multiline_comment|/*  vendor information */
DECL|member|fti_drive_type
id|vendor_struct
id|fti_drive_type
suffix:semicolon
multiline_comment|/*  data rates */
DECL|member|fti_used_data_rate
r_int
r_int
id|fti_used_data_rate
suffix:semicolon
DECL|member|fti_drive_max_rate
r_int
r_int
id|fti_drive_max_rate
suffix:semicolon
DECL|member|fti_fdc_max_rate
r_int
r_int
id|fti_fdc_max_rate
suffix:semicolon
multiline_comment|/*  drive selection, either FTAPE_SEL_A/B/C/D */
DECL|member|fti_drive_sel
r_int
id|fti_drive_sel
suffix:semicolon
multiline_comment|/*  flags set after decode the drive and tape status   */
DECL|member|fti_formatted
r_int
r_int
id|fti_formatted
suffix:colon
l_int|1
suffix:semicolon
DECL|member|fti_no_tape
r_int
r_int
id|fti_no_tape
suffix:colon
l_int|1
suffix:semicolon
DECL|member|fti_write_protected
r_int
r_int
id|fti_write_protected
suffix:colon
l_int|1
suffix:semicolon
DECL|member|fti_new_tape
r_int
r_int
id|fti_new_tape
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*  values of last queried drive/tape status and error */
DECL|member|fti_last_error
id|ft_drive_error
id|fti_last_error
suffix:semicolon
DECL|member|fti_last_status
id|ft_drive_status
id|fti_last_status
suffix:semicolon
multiline_comment|/*  cartridge geometry */
DECL|member|fti_tracks_per_tape
r_int
r_int
id|fti_tracks_per_tape
suffix:semicolon
DECL|member|fti_segments_per_track
r_int
r_int
id|fti_segments_per_track
suffix:semicolon
multiline_comment|/*  location of header segments, etc. */
DECL|member|fti_used_header_segment
r_int
id|fti_used_header_segment
suffix:semicolon
DECL|member|fti_header_segment_1
r_int
id|fti_header_segment_1
suffix:semicolon
DECL|member|fti_header_segment_2
r_int
id|fti_header_segment_2
suffix:semicolon
DECL|member|fti_first_data_segment
r_int
id|fti_first_data_segment
suffix:semicolon
DECL|member|fti_last_data_segment
r_int
id|fti_last_data_segment
suffix:semicolon
multiline_comment|/*  the format code as stored in the header segment  */
DECL|member|fti_format_code
id|ft_format_type
id|fti_format_code
suffix:semicolon
multiline_comment|/*  the following is the sole reason for the ftape_set_status() call */
DECL|member|fti_qic_std
r_int
r_int
id|fti_qic_std
suffix:semicolon
multiline_comment|/*  is tape running? */
DECL|member|fti_runner_status
r_volatile
r_enum
id|runner_status_enum
id|fti_runner_status
suffix:semicolon
multiline_comment|/*  is tape reading/writing/verifying/formatting/deleting */
DECL|member|fti_state
id|buffer_state_enum
id|fti_state
suffix:semicolon
multiline_comment|/*  flags fatal hardware error */
DECL|member|fti_failure
r_int
r_int
id|fti_failure
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*  history record */
DECL|member|fti_history
id|history_record
id|fti_history
suffix:semicolon
DECL|typedef|ftape_info
)brace
id|ftape_info
suffix:semicolon
multiline_comment|/* vendor information */
DECL|macro|ft_drive_type
mdefine_line|#define ft_drive_type          ftape_status.fti_drive_type
multiline_comment|/*  data rates */
DECL|macro|ft_data_rate
mdefine_line|#define ft_data_rate           ftape_status.fti_used_data_rate
DECL|macro|ft_drive_max_rate
mdefine_line|#define ft_drive_max_rate      ftape_status.fti_drive_max_rate
DECL|macro|ft_fdc_max_rate
mdefine_line|#define ft_fdc_max_rate        ftape_status.fti_fdc_max_rate
multiline_comment|/*  drive selection, either FTAPE_SEL_A/B/C/D */
DECL|macro|ft_drive_sel
mdefine_line|#define ft_drive_sel           ftape_status.fti_drive_sel
multiline_comment|/*  flags set after decode the drive and tape status   */
DECL|macro|ft_formatted
mdefine_line|#define ft_formatted           ftape_status.fti_formatted
DECL|macro|ft_no_tape
mdefine_line|#define ft_no_tape             ftape_status.fti_no_tape
DECL|macro|ft_write_protected
mdefine_line|#define ft_write_protected     ftape_status.fti_write_protected
DECL|macro|ft_new_tape
mdefine_line|#define ft_new_tape            ftape_status.fti_new_tape
multiline_comment|/*  values of last queried drive/tape status and error */
DECL|macro|ft_last_error
mdefine_line|#define ft_last_error          ftape_status.fti_last_error
DECL|macro|ft_last_status
mdefine_line|#define ft_last_status         ftape_status.fti_last_status
multiline_comment|/*  cartridge geometry */
DECL|macro|ft_tracks_per_tape
mdefine_line|#define ft_tracks_per_tape     ftape_status.fti_tracks_per_tape
DECL|macro|ft_segments_per_track
mdefine_line|#define ft_segments_per_track  ftape_status.fti_segments_per_track
multiline_comment|/*  the format code as stored in the header segment  */
DECL|macro|ft_format_code
mdefine_line|#define ft_format_code         ftape_status.fti_format_code
multiline_comment|/*  the qic status as returned by report drive configuration */
DECL|macro|ft_qic_std
mdefine_line|#define ft_qic_std             ftape_status.fti_qic_std
DECL|macro|ft_used_header_segment
mdefine_line|#define ft_used_header_segment ftape_status.fti_used_header_segment
DECL|macro|ft_header_segment_1
mdefine_line|#define ft_header_segment_1    ftape_status.fti_header_segment_1
DECL|macro|ft_header_segment_2
mdefine_line|#define ft_header_segment_2    ftape_status.fti_header_segment_2
DECL|macro|ft_first_data_segment
mdefine_line|#define ft_first_data_segment  ftape_status.fti_first_data_segment
DECL|macro|ft_last_data_segment
mdefine_line|#define ft_last_data_segment   ftape_status.fti_last_data_segment
multiline_comment|/*  is tape running? */
DECL|macro|ft_runner_status
mdefine_line|#define ft_runner_status       ftape_status.fti_runner_status
multiline_comment|/*  is tape reading/writing/verifying/formatting/deleting */
DECL|macro|ft_driver_state
mdefine_line|#define ft_driver_state        ftape_status.fti_state
multiline_comment|/*  flags fatal hardware error */
DECL|macro|ft_failure
mdefine_line|#define ft_failure             ftape_status.fti_failure
multiline_comment|/*  history record */
DECL|macro|ft_history
mdefine_line|#define ft_history             ftape_status.fti_history
multiline_comment|/*&n; *      ftape-ctl.c defined global vars.&n; */
r_extern
id|ftape_info
id|ftape_status
suffix:semicolon
r_extern
r_int
id|ftape_segments_per_head
suffix:semicolon
r_extern
r_int
id|ftape_segments_per_cylinder
suffix:semicolon
r_extern
r_int
id|ftape_init_drive_needed
suffix:semicolon
multiline_comment|/*&n; *      ftape-ctl.c defined global functions.&n; */
r_extern
r_int
id|ftape_mmap
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
)paren
suffix:semicolon
r_extern
r_int
id|ftape_enable
c_func
(paren
r_int
id|drive_selection
)paren
suffix:semicolon
r_extern
r_void
id|ftape_disable
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ftape_seek_to_bot
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ftape_seek_to_eot
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ftape_abort_operation
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ftape_calc_timeouts
c_func
(paren
r_int
r_int
id|qic_std
comma
r_int
r_int
id|data_rate
comma
r_int
r_int
id|tape_len
)paren
suffix:semicolon
r_extern
r_int
id|ftape_calibrate_data_rate
c_func
(paren
r_int
r_int
id|qic_std
)paren
suffix:semicolon
r_extern
r_int
id|ftape_init_drive
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_const
id|ftape_info
op_star
id|ftape_get_status
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
