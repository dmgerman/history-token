multiline_comment|/* Hey EMACS -*- linux-c -*-&n; *&n; * tiglusb - low level driver for SilverLink cable&n; *&n; * Copyright (C) 2000-2002, Romain Lievin &lt;roms@lpg.ticalc.org&gt;&n; * under the terms of the GNU General Public License.&n; *&n; * Redistribution of this file is permitted under the terms of the GNU&n; * Public License (GPL)&n; */
macro_line|#ifndef _TIGLUSB_H
DECL|macro|_TIGLUSB_H
mdefine_line|#define _TIGLUSB_H
multiline_comment|/*&n; * Max. number of devices supported&n; */
DECL|macro|MAXTIGL
mdefine_line|#define MAXTIGL&t;&t;16
multiline_comment|/*&n; * Max. packetsize for IN and OUT pipes&n; */
DECL|macro|BULK_RCV_MAX
mdefine_line|#define BULK_RCV_MAX&t;32
DECL|macro|BULK_SND_MAX
mdefine_line|#define BULK_SND_MAX&t;32
multiline_comment|/*&n; * The driver context...&n; */
DECL|enumerator|_stopped
DECL|enumerator|_started
DECL|typedef|driver_state_t
r_typedef
r_enum
(brace
id|_stopped
op_assign
l_int|0
comma
id|_started
)brace
id|driver_state_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|dev
r_struct
id|usb_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* USB device handle */
DECL|member|mutex
r_struct
id|semaphore
id|mutex
suffix:semicolon
multiline_comment|/* locks this struct */
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
multiline_comment|/* for timed waits */
DECL|member|remove_ok
id|wait_queue_head_t
id|remove_ok
suffix:semicolon
DECL|member|minor
r_int
id|minor
suffix:semicolon
multiline_comment|/* which minor dev #? */
DECL|member|devfs
id|devfs_handle_t
id|devfs
suffix:semicolon
multiline_comment|/* devfs device */
DECL|member|state
id|driver_state_t
id|state
suffix:semicolon
multiline_comment|/* started/stopped */
DECL|member|opened
r_int
id|opened
suffix:semicolon
multiline_comment|/* tru if open */
DECL|member|remove_pending
r_int
id|remove_pending
suffix:semicolon
DECL|member|rd_buf
r_char
id|rd_buf
(braket
id|BULK_RCV_MAX
)braket
suffix:semicolon
multiline_comment|/* read  buffer */
DECL|member|wr_buf
r_char
id|wr_buf
(braket
id|BULK_SND_MAX
)braket
suffix:semicolon
multiline_comment|/* write buffer */
DECL|typedef|tiglusb_t
DECL|typedef|ptiglusb_t
)brace
id|tiglusb_t
comma
op_star
id|ptiglusb_t
suffix:semicolon
r_extern
id|devfs_handle_t
id|usb_devfs_handle
suffix:semicolon
multiline_comment|/* /dev/usb dir. */
macro_line|#endif
eof
