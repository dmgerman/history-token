multiline_comment|/* $Id: aztcd.h,v 2.60 1997/11/29 09:51:22 root Exp root $&n; *&n; * Definitions for a AztechCD268 CD-ROM interface&n; *&t;Copyright (C) 1994-98  Werner Zimmermann&n; *&n; *&t;based on Mitsumi CDROM driver by Martin Harriss&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *  History:&t;W.Zimmermann adaption to Aztech CD268-01A Version 1.3&n; *&t;&t;October 1994 Email: Werner.Zimmermann@fht-esslingen.de&n; */
multiline_comment|/* *** change this to set the I/O port address of your CD-ROM drive,&n;       set to &squot;-1&squot;, if you want autoprobing */
DECL|macro|AZT_BASE_ADDR
mdefine_line|#define AZT_BASE_ADDR&t;&t;-1
multiline_comment|/* list of autoprobing addresses (not more than 15), last value must be 0x000&n;   Note: Autoprobing is only enabled, if AZT_BASE_ADDR is set to &squot;-1&squot; ! */
DECL|macro|AZT_BASE_AUTO
mdefine_line|#define AZT_BASE_AUTO &t;&t;{ 0x320, 0x300, 0x310, 0x330, 0x000 }
multiline_comment|/* Uncomment this, if your CDROM is connected to a Soundwave32-soundcard&n;   and configure AZT_BASE_ADDR and AZT_SW32_BASE_ADDR */
multiline_comment|/*#define AZT_SW32 1&n;*/
macro_line|#ifdef AZT_SW32 
DECL|macro|AZT_SW32_BASE_ADDR
mdefine_line|#define AZT_SW32_BASE_ADDR      0x220  /*I/O port base address of your soundcard*/
macro_line|#endif
multiline_comment|/* Set this to 1, if you want your tray to be locked, set to 0 to prevent tray &n;   from locking */
DECL|macro|AZT_ALLOW_TRAY_LOCK
mdefine_line|#define AZT_ALLOW_TRAY_LOCK&t;1
multiline_comment|/*Set this to 1 to allow auto-eject when unmounting a disk, set to 0, if you &n;  don&squot;t want the auto-eject feature*/
DECL|macro|AZT_AUTO_EJECT
mdefine_line|#define AZT_AUTO_EJECT          0
multiline_comment|/*Set this to 1, if you want to use incompatible ioctls for reading in raw and&n;  cooked mode */
DECL|macro|AZT_PRIVATE_IOCTLS
mdefine_line|#define AZT_PRIVATE_IOCTLS      1
multiline_comment|/*Set this to 1, if you want multisession support by the ISO fs. Even if you set &n;  this value to &squot;0&squot; you can use multisession CDs. In that case the drive&squot;s firm-&n;  ware will do the appropriate redirection automatically. The CD will then look&n;  like a single session CD (but nevertheless all data may be read). Please read &n;  chapter &squot;5.1 Multisession support&squot; in README.aztcd for details. Normally it&squot;s &n;  uncritical to leave this setting untouched */
DECL|macro|AZT_MULTISESSION
mdefine_line|#define AZT_MULTISESSION        1
multiline_comment|/*Uncomment this, if you are using a linux kernel version prior to 2.1.0 */
multiline_comment|/*#define AZT_KERNEL_PRIOR_2_1 */
multiline_comment|/*---------------------------------------------------------------------------*/
multiline_comment|/*-----nothing to be configured for normal applications below this line------*/
multiline_comment|/* Increase this if you get lots of timeouts; if you get kernel panic, replace&n;   STEN_LOW_WAIT by STEN_LOW in the source code */
DECL|macro|AZT_STATUS_DELAY
mdefine_line|#define AZT_STATUS_DELAY&t;400       /*for timer wait, STEN_LOW_WAIT*/
DECL|macro|AZT_TIMEOUT
mdefine_line|#define AZT_TIMEOUT&t;&t;8000000   /*for busy wait STEN_LOW, DTEN_LOW*/
DECL|macro|AZT_FAST_TIMEOUT
mdefine_line|#define AZT_FAST_TIMEOUT&t;10000     /*for reading the version string*/
multiline_comment|/* number of times to retry a command before giving up */
DECL|macro|AZT_RETRY_ATTEMPTS
mdefine_line|#define AZT_RETRY_ATTEMPTS&t;3
multiline_comment|/* port access macros */
DECL|macro|CMD_PORT
mdefine_line|#define CMD_PORT&t;&t;azt_port
DECL|macro|DATA_PORT
mdefine_line|#define DATA_PORT&t;&t;azt_port
DECL|macro|STATUS_PORT
mdefine_line|#define STATUS_PORT&t;&t;azt_port+1
DECL|macro|MODE_PORT
mdefine_line|#define MODE_PORT&t;&t;azt_port+2
macro_line|#ifdef  AZT_SW32                
DECL|macro|AZT_SW32_INIT
mdefine_line|#define AZT_SW32_INIT          (unsigned int) (0xFF00 &amp; (AZT_BASE_ADDR*16))
DECL|macro|AZT_SW32_CONFIG_REG
mdefine_line|#define AZT_SW32_CONFIG_REG    AZT_SW32_BASE_ADDR+0x16  /*Soundwave32 Config. Register*/
DECL|macro|AZT_SW32_ID_REG
mdefine_line|#define AZT_SW32_ID_REG        AZT_SW32_BASE_ADDR+0x04  /*Soundwave32 ID Version Register*/
macro_line|#endif
multiline_comment|/* status bits */
DECL|macro|AST_CMD_CHECK
mdefine_line|#define AST_CMD_CHECK&t;&t;0x80&t;&t;/* 1 = command error */
DECL|macro|AST_DOOR_OPEN
mdefine_line|#define AST_DOOR_OPEN&t;&t;0x40&t;&t;/* 1 = door is open */
DECL|macro|AST_NOT_READY
mdefine_line|#define AST_NOT_READY&t;&t;0x20&t;&t;/* 1 = no disk in the drive */
DECL|macro|AST_DSK_CHG
mdefine_line|#define AST_DSK_CHG&t;&t;0x02&t;&t;/* 1 = disk removed or changed */
DECL|macro|AST_MODE
mdefine_line|#define AST_MODE                0x01            /* 0=MODE1, 1=MODE2 */
DECL|macro|AST_MODE_BITS
mdefine_line|#define AST_MODE_BITS&t;&t;0x1C&t;&t;/* Mode Bits */
DECL|macro|AST_INITIAL
mdefine_line|#define AST_INITIAL&t;&t;0x0C&t;&t;/* initial, only valid ... */
DECL|macro|AST_BUSY
mdefine_line|#define AST_BUSY&t;&t;0x04&t;&t;/* now playing, only valid&n;&t;&t;&t;&t;&t;&t;   in combination with mode&n;&t;&t;&t;&t;&t;&t;   bits */
multiline_comment|/* flag bits */
DECL|macro|AFL_DATA
mdefine_line|#define AFL_DATA&t;&t;0x02&t;&t;/* data available if low */
DECL|macro|AFL_STATUS
mdefine_line|#define AFL_STATUS&t;&t;0x04&t;&t;/* status available if low */
DECL|macro|AFL_OP_OK
mdefine_line|#define AFL_OP_OK&t;&t;0x01&t;&t;/* OP_OK command correct*/
DECL|macro|AFL_PA_OK
mdefine_line|#define AFL_PA_OK&t;&t;0x02&t;&t;/* PA_OK parameter correct*/
DECL|macro|AFL_OP_ERR
mdefine_line|#define AFL_OP_ERR&t;&t;0x05&t;&t;/* error in command*/
DECL|macro|AFL_PA_ERR
mdefine_line|#define AFL_PA_ERR&t;&t;0x06&t;&t;/* error in parameters*/
DECL|macro|POLLED
mdefine_line|#define POLLED&t;&t;&t;0x04&t;&t;/* polled mode */
multiline_comment|/* commands */
DECL|macro|ACMD_SOFT_RESET
mdefine_line|#define ACMD_SOFT_RESET&t;&t;0x10&t;&t;/* reset drive */
DECL|macro|ACMD_PLAY_READ
mdefine_line|#define ACMD_PLAY_READ&t;&t;0x20&t;&t;/* read data track in cooked mode */
DECL|macro|ACMD_PLAY_READ_RAW
mdefine_line|#define ACMD_PLAY_READ_RAW      0x21&t;&t;/* reading in raw mode*/
DECL|macro|ACMD_SEEK
mdefine_line|#define ACMD_SEEK               0x30            /* seek msf address*/
DECL|macro|ACMD_SEEK_TO_LEADIN
mdefine_line|#define ACMD_SEEK_TO_LEADIN     0x31&t;&t;/* seek to leadin track*/
DECL|macro|ACMD_GET_ERROR
mdefine_line|#define ACMD_GET_ERROR&t;&t;0x40&t;&t;/* get error code */
DECL|macro|ACMD_GET_STATUS
mdefine_line|#define ACMD_GET_STATUS&t;&t;0x41&t;&t;/* get status */
DECL|macro|ACMD_GET_Q_CHANNEL
mdefine_line|#define ACMD_GET_Q_CHANNEL      0x50&t;&t;/* read info from q channel */
DECL|macro|ACMD_EJECT
mdefine_line|#define ACMD_EJECT&t;&t;0x60&t;&t;/* eject/open tray */
DECL|macro|ACMD_CLOSE
mdefine_line|#define ACMD_CLOSE              0x61            /* close tray */
DECL|macro|ACMD_LOCK
mdefine_line|#define ACMD_LOCK&t;&t;0x71&t;&t;/* lock tray closed */
DECL|macro|ACMD_UNLOCK
mdefine_line|#define ACMD_UNLOCK&t;&t;0x72&t;&t;/* unlock tray */
DECL|macro|ACMD_PAUSE
mdefine_line|#define ACMD_PAUSE&t;&t;0x80&t;&t;/* pause */
DECL|macro|ACMD_STOP
mdefine_line|#define ACMD_STOP&t;&t;0x81&t;&t;/* stop play */
DECL|macro|ACMD_PLAY_AUDIO
mdefine_line|#define ACMD_PLAY_AUDIO&t;&t;0x90&t;&t;/* play audio track */
DECL|macro|ACMD_SET_VOLUME
mdefine_line|#define ACMD_SET_VOLUME&t;&t;0x93&t;&t;/* set audio level */
DECL|macro|ACMD_GET_VERSION
mdefine_line|#define ACMD_GET_VERSION&t;0xA0&t;&t;/* get firmware version */
DECL|macro|ACMD_SET_DISK_TYPE
mdefine_line|#define ACMD_SET_DISK_TYPE&t;0xA1&t;&t;/* set disk data mode */
DECL|macro|MAX_TRACKS
mdefine_line|#define MAX_TRACKS&t;&t;104
DECL|struct|msf
r_struct
id|msf
(brace
DECL|member|min
r_int
r_char
id|min
suffix:semicolon
DECL|member|sec
r_int
r_char
id|sec
suffix:semicolon
DECL|member|frame
r_int
r_char
id|frame
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|azt_Play_msf
r_struct
id|azt_Play_msf
(brace
DECL|member|start
r_struct
id|msf
id|start
suffix:semicolon
DECL|member|end
r_struct
id|msf
id|end
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|azt_DiskInfo
r_struct
id|azt_DiskInfo
(brace
DECL|member|first
r_int
r_char
id|first
suffix:semicolon
DECL|member|next
r_int
r_char
id|next
suffix:semicolon
DECL|member|last
r_int
r_char
id|last
suffix:semicolon
DECL|member|diskLength
r_struct
id|msf
id|diskLength
suffix:semicolon
DECL|member|firstTrack
r_struct
id|msf
id|firstTrack
suffix:semicolon
DECL|member|multi
r_int
r_char
id|multi
suffix:semicolon
DECL|member|nextSession
r_struct
id|msf
id|nextSession
suffix:semicolon
DECL|member|lastSession
r_struct
id|msf
id|lastSession
suffix:semicolon
DECL|member|xa
r_int
r_char
id|xa
suffix:semicolon
DECL|member|audio
r_int
r_char
id|audio
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|azt_Toc
r_struct
id|azt_Toc
(brace
DECL|member|ctrl_addr
r_int
r_char
id|ctrl_addr
suffix:semicolon
DECL|member|track
r_int
r_char
id|track
suffix:semicolon
DECL|member|pointIndex
r_int
r_char
id|pointIndex
suffix:semicolon
DECL|member|trackTime
r_struct
id|msf
id|trackTime
suffix:semicolon
DECL|member|diskTime
r_struct
id|msf
id|diskTime
suffix:semicolon
)brace
suffix:semicolon
eof
