multiline_comment|/*&t;linux/include/linux/optcd.h - Optics Storage 8000 AT CDROM driver&n;&t;$Id: optcd.h,v 1.2 1996/01/15 18:43:44 root Exp root $&n;&n;&t;Copyright (C) 1995 Leo Spiekman (spiekman@dutette.et.tudelft.nl)&n;&n;&n;&t;Configuration file for linux/drivers/cdrom/optcd.c&n;*/
macro_line|#ifndef _LINUX_OPTCD_H
DECL|macro|_LINUX_OPTCD_H
mdefine_line|#define _LINUX_OPTCD_H
multiline_comment|/* I/O base of drive. Drive uses base to base+2.&n;   This setting can be overridden with the kernel or insmod command&n;   line option &squot;optcd=&lt;portbase&gt;&squot;. Use address of 0 to disable driver. */
DECL|macro|OPTCD_PORTBASE
mdefine_line|#define OPTCD_PORTBASE&t;0x340
multiline_comment|/* enable / disable parts of driver by define / undef */
DECL|macro|MULTISESSION
mdefine_line|#define&t;MULTISESSION&t;&t;/* multisession support (ALPHA) */
multiline_comment|/* Change 0 to 1 to debug various parts of the driver */
DECL|macro|DEBUG_DRIVE_IF
mdefine_line|#define&t;DEBUG_DRIVE_IF&t;0&t;/* Low level drive interface */
DECL|macro|DEBUG_CONV
mdefine_line|#define&t;DEBUG_CONV&t;0&t;/* Address conversions */
DECL|macro|DEBUG_BUFFERS
mdefine_line|#define&t;DEBUG_BUFFERS&t;0&t;/* Buffering and block size conversion */
DECL|macro|DEBUG_REQUEST
mdefine_line|#define&t;DEBUG_REQUEST&t;0&t;/* Request mechanism */
DECL|macro|DEBUG_STATE
mdefine_line|#define&t;DEBUG_STATE&t;0&t;/* State machine */
DECL|macro|DEBUG_TOC
mdefine_line|#define&t;DEBUG_TOC&t;0&t;/* Q-channel and Table of Contents */
DECL|macro|DEBUG_MULTIS
mdefine_line|#define&t;DEBUG_MULTIS&t;0&t;/* Multisession code */
DECL|macro|DEBUG_VFS
mdefine_line|#define&t;DEBUG_VFS&t;0&t;/* VFS interface */
multiline_comment|/* Don&squot;t touch these unless you know what you&squot;re doing. */
multiline_comment|/* Various timeout loop repetition counts. */
DECL|macro|BUSY_TIMEOUT
mdefine_line|#define BUSY_TIMEOUT&t;&t;10000000&t;/* for busy wait */
DECL|macro|FAST_TIMEOUT
mdefine_line|#define FAST_TIMEOUT&t;&t;100000&t;&t;/* ibid. for probing */
DECL|macro|SLEEP_TIMEOUT
mdefine_line|#define SLEEP_TIMEOUT&t;&t;6000&t;&t;/* for timer wait */
DECL|macro|MULTI_SEEK_TIMEOUT
mdefine_line|#define MULTI_SEEK_TIMEOUT&t;1000&t;&t;/* for timer wait */
DECL|macro|READ_TIMEOUT
mdefine_line|#define READ_TIMEOUT&t;&t;6000&t;&t;/* for poll wait */
DECL|macro|STOP_TIMEOUT
mdefine_line|#define STOP_TIMEOUT&t;&t;2000&t;&t;/* for poll wait */
DECL|macro|RESET_WAIT
mdefine_line|#define RESET_WAIT&t;&t;5000&t;&t;/* busy wait at drive reset */
multiline_comment|/* # of buffers for block size conversion. 6 is optimal for my setup (P75),&n;   giving 280 kb/s, with 0.4% CPU usage. Experiment to find your optimal&n;   setting */
DECL|macro|N_BUFS
mdefine_line|#define N_BUFS&t;&t;6
macro_line|#endif _LINUX_OPTCD_H
eof
