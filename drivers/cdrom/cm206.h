multiline_comment|/* cm206.h Header file for cm206.c.&n;   Copyright (c) 1995 David van Leeuwen &n;*/
macro_line|#ifndef LINUX_CM206_H
DECL|macro|LINUX_CM206_H
mdefine_line|#define LINUX_CM206_H
macro_line|#include &lt;linux/ioctl.h&gt;
multiline_comment|/* First, the cm260 stuff */
multiline_comment|/* The ports and irq used. Although CM206_BASE and CM206_IRQ are defined&n;   below, the values are not used unless autoprobing is turned off and &n;   no LILO boot options or module command line options are given. Change&n;   these values to your own as last resort if autoprobing and options&n;   don&squot;t work. */
DECL|macro|CM206_BASE
mdefine_line|#define CM206_BASE 0x340
DECL|macro|CM206_IRQ
mdefine_line|#define CM206_IRQ 11
DECL|macro|r_data_status
mdefine_line|#define r_data_status (cm206_base)
DECL|macro|r_uart_receive
mdefine_line|#define r_uart_receive (cm206_base+0x2)
DECL|macro|r_fifo_output_buffer
mdefine_line|#define r_fifo_output_buffer (cm206_base+0x4)
DECL|macro|r_line_status
mdefine_line|#define r_line_status (cm206_base+0x6)
DECL|macro|r_data_control
mdefine_line|#define r_data_control (cm206_base+0x8)
DECL|macro|r_uart_transmit
mdefine_line|#define r_uart_transmit (cm206_base+0xa)
DECL|macro|r_test_clock
mdefine_line|#define r_test_clock (cm206_base+0xc)
DECL|macro|r_test_control
mdefine_line|#define r_test_control (cm206_base+0xe)
multiline_comment|/* the data_status flags */
DECL|macro|ds_ram_size
mdefine_line|#define ds_ram_size 0x4000
DECL|macro|ds_toc_ready
mdefine_line|#define ds_toc_ready 0x2000
DECL|macro|ds_fifo_empty
mdefine_line|#define ds_fifo_empty 0x1000
DECL|macro|ds_sync_error
mdefine_line|#define ds_sync_error 0x800
DECL|macro|ds_crc_error
mdefine_line|#define ds_crc_error 0x400
DECL|macro|ds_data_error
mdefine_line|#define ds_data_error 0x200
DECL|macro|ds_fifo_overflow
mdefine_line|#define ds_fifo_overflow 0x100
DECL|macro|ds_data_ready
mdefine_line|#define ds_data_ready 0x80
multiline_comment|/* the line_status flags */
DECL|macro|ls_attention
mdefine_line|#define ls_attention 0x10
DECL|macro|ls_parity_error
mdefine_line|#define ls_parity_error 0x8
DECL|macro|ls_overrun
mdefine_line|#define ls_overrun 0x4
DECL|macro|ls_receive_buffer_full
mdefine_line|#define ls_receive_buffer_full 0x2
DECL|macro|ls_transmitter_buffer_empty
mdefine_line|#define ls_transmitter_buffer_empty 0x1
multiline_comment|/* the data control register flags */
DECL|macro|dc_read_q_channel
mdefine_line|#define dc_read_q_channel 0x4000
DECL|macro|dc_mask_sync_error
mdefine_line|#define dc_mask_sync_error 0x2000
DECL|macro|dc_toc_enable
mdefine_line|#define dc_toc_enable 0x1000
DECL|macro|dc_no_stop_on_error
mdefine_line|#define dc_no_stop_on_error 0x800
DECL|macro|dc_break
mdefine_line|#define dc_break 0x400
DECL|macro|dc_initialize
mdefine_line|#define dc_initialize 0x200
DECL|macro|dc_mask_transmit_ready
mdefine_line|#define dc_mask_transmit_ready 0x100
DECL|macro|dc_flag_enable
mdefine_line|#define dc_flag_enable 0x80
multiline_comment|/* Define the default data control register flags here */
DECL|macro|dc_normal
mdefine_line|#define dc_normal (dc_mask_sync_error | dc_no_stop_on_error | &bslash;&n;&t;&t;   dc_mask_transmit_ready)
multiline_comment|/* now some constants related to the cm206 */
multiline_comment|/* another drive status byte, echoed by the cm206 on most commands */
DECL|macro|dsb_error_condition
mdefine_line|#define dsb_error_condition 0x1
DECL|macro|dsb_play_in_progress
mdefine_line|#define dsb_play_in_progress 0x4
DECL|macro|dsb_possible_media_change
mdefine_line|#define dsb_possible_media_change 0x8
DECL|macro|dsb_disc_present
mdefine_line|#define dsb_disc_present 0x10
DECL|macro|dsb_drive_not_ready
mdefine_line|#define dsb_drive_not_ready 0x20
DECL|macro|dsb_tray_locked
mdefine_line|#define dsb_tray_locked 0x40
DECL|macro|dsb_tray_not_closed
mdefine_line|#define dsb_tray_not_closed 0x80
DECL|macro|dsb_not_useful
mdefine_line|#define dsb_not_useful (dsb_drive_not_ready | dsb_tray_not_closed)
multiline_comment|/* the cm206 command set */
DECL|macro|c_close_tray
mdefine_line|#define c_close_tray 0
DECL|macro|c_lock_tray
mdefine_line|#define c_lock_tray 0x01
DECL|macro|c_unlock_tray
mdefine_line|#define c_unlock_tray 0x04
DECL|macro|c_open_tray
mdefine_line|#define c_open_tray 0x05
DECL|macro|c_seek
mdefine_line|#define c_seek 0x10
DECL|macro|c_read_data
mdefine_line|#define c_read_data 0x20
DECL|macro|c_force_1x
mdefine_line|#define c_force_1x 0x21
DECL|macro|c_force_2x
mdefine_line|#define c_force_2x 0x22
DECL|macro|c_auto_mode
mdefine_line|#define c_auto_mode 0x23
DECL|macro|c_play
mdefine_line|#define c_play 0x30
DECL|macro|c_set_audio_mode
mdefine_line|#define c_set_audio_mode 0x31
DECL|macro|c_read_current_q
mdefine_line|#define c_read_current_q 0x41
DECL|macro|c_stream_q
mdefine_line|#define c_stream_q 0x42
DECL|macro|c_drive_status
mdefine_line|#define c_drive_status 0x50
DECL|macro|c_disc_status
mdefine_line|#define c_disc_status 0x51
DECL|macro|c_audio_status
mdefine_line|#define c_audio_status 0x52
DECL|macro|c_drive_configuration
mdefine_line|#define c_drive_configuration 0x53
DECL|macro|c_read_upc
mdefine_line|#define c_read_upc 0x60
DECL|macro|c_stop
mdefine_line|#define c_stop 0x70
DECL|macro|c_calc_checksum
mdefine_line|#define c_calc_checksum 0xe5
DECL|macro|c_gimme
mdefine_line|#define c_gimme 0xf8
multiline_comment|/* finally, the (error) condition that the drive can be in      *&n; * OK, this is not always an error, but let&squot;s prefix it with e_ */
DECL|macro|e_none
mdefine_line|#define e_none 0
DECL|macro|e_illegal_command
mdefine_line|#define e_illegal_command 0x01
DECL|macro|e_sync
mdefine_line|#define e_sync 0x02
DECL|macro|e_seek
mdefine_line|#define e_seek 0x03
DECL|macro|e_parity
mdefine_line|#define e_parity 0x04
DECL|macro|e_focus
mdefine_line|#define e_focus 0x05
DECL|macro|e_header_sync
mdefine_line|#define e_header_sync 0x06
DECL|macro|e_code_incompatibility
mdefine_line|#define e_code_incompatibility 0x07
DECL|macro|e_reset_done
mdefine_line|#define e_reset_done 0x08
DECL|macro|e_bad_parameter
mdefine_line|#define e_bad_parameter 0x09
DECL|macro|e_radial
mdefine_line|#define e_radial 0x0a
DECL|macro|e_sub_code
mdefine_line|#define e_sub_code 0x0b
DECL|macro|e_no_data_track
mdefine_line|#define e_no_data_track 0x0c
DECL|macro|e_scan
mdefine_line|#define e_scan 0x0d
DECL|macro|e_tray_open
mdefine_line|#define e_tray_open 0x0f
DECL|macro|e_no_disc
mdefine_line|#define e_no_disc 0x10
DECL|macro|e_tray
mdefine_line|#define e_tray stalled 0x11
multiline_comment|/* drive configuration masks */
DECL|macro|dcf_revision_code
mdefine_line|#define dcf_revision_code 0x7
DECL|macro|dcf_transfer_rate
mdefine_line|#define dcf_transfer_rate 0x60
DECL|macro|dcf_motorized_tray
mdefine_line|#define dcf_motorized_tray 0x80
multiline_comment|/* disc status byte */
DECL|macro|cds_multi_session
mdefine_line|#define cds_multi_session 0x2
DECL|macro|cds_all_audio
mdefine_line|#define cds_all_audio 0x8
DECL|macro|cds_xa_mode
mdefine_line|#define cds_xa_mode 0xf0
multiline_comment|/* finally some ioctls for the driver */
DECL|macro|CM206CTL_GET_STAT
mdefine_line|#define CM206CTL_GET_STAT _IO( 0x20, 0 )
DECL|macro|CM206CTL_GET_LAST_STAT
mdefine_line|#define CM206CTL_GET_LAST_STAT _IO( 0x20, 1 )
macro_line|#ifdef STATISTICS
multiline_comment|/* This is an ugly way to guarantee that the names of the statistics&n; * are the same in the code and in the diagnostics program.  */
macro_line|#ifdef __KERNEL__
DECL|macro|x
mdefine_line|#define x(a) st_ ## a
DECL|macro|y
mdefine_line|#define y enum
macro_line|#else
DECL|macro|x
mdefine_line|#define x(a) #a
DECL|macro|y
mdefine_line|#define y char * stats_name[] = 
macro_line|#endif
id|y
(brace
id|x
c_func
(paren
id|interrupt
)paren
comma
id|x
c_func
(paren
id|data_ready
)paren
comma
id|x
c_func
(paren
id|fifo_overflow
)paren
comma
id|x
c_func
(paren
id|data_error
)paren
comma
id|x
c_func
(paren
id|crc_error
)paren
comma
id|x
c_func
(paren
id|sync_error
)paren
comma
id|x
c_func
(paren
id|lost_intr
)paren
comma
id|x
c_func
(paren
id|echo
)paren
comma
id|x
c_func
(paren
id|write_timeout
)paren
comma
id|x
c_func
(paren
id|receive_timeout
)paren
comma
id|x
c_func
(paren
id|read_timeout
)paren
comma
id|x
c_func
(paren
id|dsb_timeout
)paren
comma
id|x
c_func
(paren
id|stop_0xff
)paren
comma
id|x
c_func
(paren
id|back_read_timeout
)paren
comma
id|x
c_func
(paren
id|sector_transferred
)paren
comma
id|x
c_func
(paren
id|read_restarted
)paren
comma
id|x
c_func
(paren
id|read_background
)paren
comma
id|x
c_func
(paren
id|bh
)paren
comma
id|x
c_func
(paren
id|open
)paren
comma
id|x
c_func
(paren
id|ioctl_multisession
)paren
comma
id|x
c_func
(paren
id|attention
)paren
macro_line|#ifdef __KERNEL__
comma
id|x
c_func
(paren
id|last_entry
)paren
macro_line|#endif
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|macro|NR_STATS
mdefine_line|#define NR_STATS st_last_entry
macro_line|#else
DECL|macro|NR_STATS
mdefine_line|#define NR_STATS (sizeof(stats_name)/sizeof(char*))
macro_line|#endif
DECL|macro|y
macro_line|#undef y
DECL|macro|x
macro_line|#undef x
macro_line|#endif /* STATISTICS */
macro_line|#endif /* LINUX_CM206_H */
eof
