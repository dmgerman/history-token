macro_line|#ifndef _LINUX_XD_H
DECL|macro|_LINUX_XD_H
mdefine_line|#define _LINUX_XD_H
multiline_comment|/*&n; * This file contains the definitions for the IO ports and errors etc. for XT hard disk controllers (at least the DTC 5150X).&n; *&n; * Author: Pat Mackinlay, pat@it.com.au&n; * Date: 29/09/92&n; *&n; * Revised: 01/01/93, ...&n; *&n; * Ref: DTC 5150X Controller Specification (thanks to Kevin Fowler, kevinf@agora.rain.com)&n; * Also thanks to: Salvador Abreu, Dave Thaler, Risto Kankkunen and Wim Van Dorst.&n; */
multiline_comment|/* XT hard disk controller registers */
DECL|macro|XD_DATA
mdefine_line|#define XD_DATA&t;&t;(xd_iobase + 0x00)&t;/* data RW register */
DECL|macro|XD_RESET
mdefine_line|#define XD_RESET&t;(xd_iobase + 0x01)&t;/* reset WO register */
DECL|macro|XD_STATUS
mdefine_line|#define XD_STATUS&t;(xd_iobase + 0x01)&t;/* status RO register */
DECL|macro|XD_SELECT
mdefine_line|#define XD_SELECT&t;(xd_iobase + 0x02)&t;/* select WO register */
DECL|macro|XD_JUMPER
mdefine_line|#define XD_JUMPER&t;(xd_iobase + 0x02)&t;/* jumper RO register */
DECL|macro|XD_CONTROL
mdefine_line|#define XD_CONTROL&t;(xd_iobase + 0x03)&t;/* DMAE/INTE WO register */
DECL|macro|XD_RESERVED
mdefine_line|#define XD_RESERVED&t;(xd_iobase + 0x03)&t;/* reserved */
multiline_comment|/* XT hard disk controller commands (incomplete list) */
DECL|macro|CMD_TESTREADY
mdefine_line|#define CMD_TESTREADY&t;0x00&t;/* test drive ready */
DECL|macro|CMD_RECALIBRATE
mdefine_line|#define CMD_RECALIBRATE&t;0x01&t;/* recalibrate drive */
DECL|macro|CMD_SENSE
mdefine_line|#define CMD_SENSE&t;0x03&t;/* request sense */
DECL|macro|CMD_FORMATDRV
mdefine_line|#define CMD_FORMATDRV&t;0x04&t;/* format drive */
DECL|macro|CMD_VERIFY
mdefine_line|#define CMD_VERIFY&t;0x05&t;/* read verify */
DECL|macro|CMD_FORMATTRK
mdefine_line|#define CMD_FORMATTRK&t;0x06&t;/* format track */
DECL|macro|CMD_FORMATBAD
mdefine_line|#define CMD_FORMATBAD&t;0x07&t;/* format bad track */
DECL|macro|CMD_READ
mdefine_line|#define CMD_READ&t;0x08&t;/* read */
DECL|macro|CMD_WRITE
mdefine_line|#define CMD_WRITE&t;0x0A&t;/* write */
DECL|macro|CMD_SEEK
mdefine_line|#define CMD_SEEK&t;0x0B&t;/* seek */
multiline_comment|/* Controller specific commands */
DECL|macro|CMD_DTCSETPARAM
mdefine_line|#define CMD_DTCSETPARAM&t;0x0C&t;/* set drive parameters (DTC 5150X &amp; CX only?) */
DECL|macro|CMD_DTCGETECC
mdefine_line|#define CMD_DTCGETECC&t;0x0D&t;/* get ecc error length (DTC 5150X only?) */
DECL|macro|CMD_DTCREADBUF
mdefine_line|#define CMD_DTCREADBUF&t;0x0E&t;/* read sector buffer (DTC 5150X only?) */
DECL|macro|CMD_DTCWRITEBUF
mdefine_line|#define CMD_DTCWRITEBUF 0x0F&t;/* write sector buffer (DTC 5150X only?) */
DECL|macro|CMD_DTCREMAPTRK
mdefine_line|#define CMD_DTCREMAPTRK&t;0x11&t;/* assign alternate track (DTC 5150X only?) */
DECL|macro|CMD_DTCGETPARAM
mdefine_line|#define CMD_DTCGETPARAM&t;0xFB&t;/* get drive parameters (DTC 5150X only?) */
DECL|macro|CMD_DTCSETSTEP
mdefine_line|#define CMD_DTCSETSTEP&t;0xFC&t;/* set step rate (DTC 5150X only?) */
DECL|macro|CMD_DTCSETGEOM
mdefine_line|#define CMD_DTCSETGEOM&t;0xFE&t;/* set geometry data (DTC 5150X only?) */
DECL|macro|CMD_DTCGETGEOM
mdefine_line|#define CMD_DTCGETGEOM&t;0xFF&t;/* get geometry data (DTC 5150X only?) */
DECL|macro|CMD_ST11GETGEOM
mdefine_line|#define CMD_ST11GETGEOM 0xF8&t;/* get geometry data (Seagate ST11R/M only?) */
DECL|macro|CMD_WDSETPARAM
mdefine_line|#define CMD_WDSETPARAM&t;0x0C&t;/* set drive parameters (WD 1004A27X only?) */
DECL|macro|CMD_XBSETPARAM
mdefine_line|#define CMD_XBSETPARAM&t;0x0C&t;/* set drive parameters (XEBEC only?) */
multiline_comment|/* Bits for command status byte */
DECL|macro|CSB_ERROR
mdefine_line|#define CSB_ERROR&t;0x02&t;/* error */
DECL|macro|CSB_LUN
mdefine_line|#define CSB_LUN&t;&t;0x20&t;/* logical Unit Number */
multiline_comment|/* XT hard disk controller status bits */
DECL|macro|STAT_READY
mdefine_line|#define STAT_READY&t;0x01&t;/* controller is ready */
DECL|macro|STAT_INPUT
mdefine_line|#define STAT_INPUT&t;0x02&t;/* data flowing from controller to host */
DECL|macro|STAT_COMMAND
mdefine_line|#define STAT_COMMAND&t;0x04&t;/* controller in command phase */
DECL|macro|STAT_SELECT
mdefine_line|#define STAT_SELECT&t;0x08&t;/* controller is selected */
DECL|macro|STAT_REQUEST
mdefine_line|#define STAT_REQUEST&t;0x10&t;/* controller requesting data */
DECL|macro|STAT_INTERRUPT
mdefine_line|#define STAT_INTERRUPT&t;0x20&t;/* controller requesting interrupt */
multiline_comment|/* XT hard disk controller control bits */
DECL|macro|PIO_MODE
mdefine_line|#define PIO_MODE&t;0x00&t;/* control bits to set for PIO */
DECL|macro|DMA_MODE
mdefine_line|#define DMA_MODE&t;0x03&t;/* control bits to set for DMA &amp; interrupt */
DECL|macro|XD_MAXDRIVES
mdefine_line|#define XD_MAXDRIVES&t;2&t;/* maximum 2 drives */
DECL|macro|XD_TIMEOUT
mdefine_line|#define XD_TIMEOUT&t;HZ&t;/* 1 second timeout */
DECL|macro|XD_RETRIES
mdefine_line|#define XD_RETRIES&t;4&t;/* maximum 4 retries */
DECL|macro|DEBUG
macro_line|#undef DEBUG&t;&t;&t;/* define for debugging output */
macro_line|#ifdef DEBUG
DECL|macro|DEBUG_STARTUP
mdefine_line|#define DEBUG_STARTUP&t;/* debug driver initialisation */
DECL|macro|DEBUG_OVERRIDE
mdefine_line|#define DEBUG_OVERRIDE&t;/* debug override geometry detection */
DECL|macro|DEBUG_READWRITE
mdefine_line|#define DEBUG_READWRITE&t;/* debug each read/write command */
DECL|macro|DEBUG_OTHER
mdefine_line|#define DEBUG_OTHER&t;/* debug misc. interrupt/DMA stuff */
DECL|macro|DEBUG_COMMAND
mdefine_line|#define DEBUG_COMMAND&t;/* debug each controller command */
macro_line|#endif /* DEBUG */
multiline_comment|/* this structure defines the XT drives and their types */
r_typedef
r_struct
(brace
DECL|member|heads
id|u_char
id|heads
suffix:semicolon
DECL|member|cylinders
id|u_short
id|cylinders
suffix:semicolon
DECL|member|sectors
id|u_char
id|sectors
suffix:semicolon
DECL|member|control
id|u_char
id|control
suffix:semicolon
DECL|typedef|XD_INFO
)brace
id|XD_INFO
suffix:semicolon
multiline_comment|/* this structure is returned to the HDIO_GETGEO ioctl */
r_typedef
r_struct
(brace
DECL|member|heads
id|__u8
id|heads
suffix:semicolon
DECL|member|sectors
id|__u8
id|sectors
suffix:semicolon
DECL|member|cylinders
id|__u8
id|cylinders
suffix:semicolon
DECL|member|start
id|__u32
id|start
suffix:semicolon
DECL|typedef|XD_GEOMETRY
)brace
id|XD_GEOMETRY
suffix:semicolon
multiline_comment|/* this structure defines a ROM BIOS signature */
r_typedef
r_struct
(brace
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
DECL|member|string
r_const
r_char
op_star
id|string
suffix:semicolon
DECL|member|init_controller
r_void
(paren
op_star
id|init_controller
)paren
(paren
r_int
r_int
id|address
)paren
suffix:semicolon
DECL|member|init_drive
r_void
(paren
op_star
id|init_drive
)paren
(paren
id|u_char
id|drive
)paren
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|typedef|XD_SIGNATURE
)brace
id|XD_SIGNATURE
suffix:semicolon
macro_line|#ifndef MODULE
r_static
r_int
id|xd_manual_geo_init
(paren
r_char
op_star
id|command
)paren
suffix:semicolon
macro_line|#endif /* MODULE */
r_static
id|u_char
id|xd_detect
(paren
id|u_char
op_star
id|controller
comma
r_int
r_int
op_star
id|address
)paren
suffix:semicolon
r_static
id|u_char
id|xd_initdrives
(paren
r_void
(paren
op_star
id|init_drive
)paren
(paren
id|u_char
id|drive
)paren
)paren
suffix:semicolon
r_static
r_void
id|xd_geninit
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|xd_open
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
r_static
r_void
id|do_xd_request
(paren
id|request_queue_t
op_star
id|q
)paren
suffix:semicolon
r_static
r_int
id|xd_ioctl
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_static
r_int
id|xd_release
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
r_static
r_int
id|xd_reread_partitions
(paren
id|kdev_t
id|dev
)paren
suffix:semicolon
r_static
r_int
id|xd_readwrite
(paren
id|u_char
id|operation
comma
id|u_char
id|drive
comma
r_char
op_star
id|buffer
comma
id|u_int
id|block
comma
id|u_int
id|count
)paren
suffix:semicolon
r_static
r_void
id|xd_recalibrate
(paren
id|u_char
id|drive
)paren
suffix:semicolon
r_static
r_void
id|xd_interrupt_handler
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_static
id|u_char
id|xd_setup_dma
(paren
id|u_char
id|opcode
comma
id|u_char
op_star
id|buffer
comma
id|u_int
id|count
)paren
suffix:semicolon
r_static
id|u_char
op_star
id|xd_build
(paren
id|u_char
op_star
id|cmdblk
comma
id|u_char
id|command
comma
id|u_char
id|drive
comma
id|u_char
id|head
comma
id|u_short
id|cylinder
comma
id|u_char
id|sector
comma
id|u_char
id|count
comma
id|u_char
id|control
)paren
suffix:semicolon
r_static
r_void
id|xd_wakeup
(paren
r_int
r_int
id|unused
)paren
suffix:semicolon
r_static
r_void
id|xd_watchdog
(paren
r_int
r_int
id|unused
)paren
suffix:semicolon
r_static
r_inline
id|u_char
id|xd_waitport
(paren
id|u_short
id|port
comma
id|u_char
id|flags
comma
id|u_char
id|mask
comma
id|u_long
id|timeout
)paren
suffix:semicolon
r_static
id|u_int
id|xd_command
(paren
id|u_char
op_star
id|command
comma
id|u_char
id|mode
comma
id|u_char
op_star
id|indata
comma
id|u_char
op_star
id|outdata
comma
id|u_char
op_star
id|sense
comma
id|u_long
id|timeout
)paren
suffix:semicolon
multiline_comment|/* card specific setup and geometry gathering code */
r_static
r_void
id|xd_dtc_init_controller
(paren
r_int
r_int
id|address
)paren
suffix:semicolon
r_static
r_void
id|xd_dtc5150cx_init_drive
(paren
id|u_char
id|drive
)paren
suffix:semicolon
r_static
r_void
id|xd_dtc_init_drive
(paren
id|u_char
id|drive
)paren
suffix:semicolon
r_static
r_void
id|xd_wd_init_controller
(paren
r_int
r_int
id|address
)paren
suffix:semicolon
r_static
r_void
id|xd_wd_init_drive
(paren
id|u_char
id|drive
)paren
suffix:semicolon
r_static
r_void
id|xd_seagate_init_controller
(paren
r_int
r_int
id|address
)paren
suffix:semicolon
r_static
r_void
id|xd_seagate_init_drive
(paren
id|u_char
id|drive
)paren
suffix:semicolon
r_static
r_void
id|xd_omti_init_controller
(paren
r_int
r_int
id|address
)paren
suffix:semicolon
r_static
r_void
id|xd_omti_init_drive
(paren
id|u_char
id|drive
)paren
suffix:semicolon
r_static
r_void
id|xd_xebec_init_controller
(paren
r_int
r_int
id|address
)paren
suffix:semicolon
r_static
r_void
id|xd_xebec_init_drive
(paren
id|u_char
id|drive
)paren
suffix:semicolon
r_static
r_void
id|xd_setparam
(paren
id|u_char
id|command
comma
id|u_char
id|drive
comma
id|u_char
id|heads
comma
id|u_short
id|cylinders
comma
id|u_short
id|rwrite
comma
id|u_short
id|wprecomp
comma
id|u_char
id|ecc
)paren
suffix:semicolon
r_static
r_void
id|xd_override_init_drive
(paren
id|u_char
id|drive
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_XD_H */
eof
