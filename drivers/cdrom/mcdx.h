multiline_comment|/*&n; * Definitions for the Mitsumi CDROM interface&n; * Copyright (C) 1995 1996 Heiko Schlittermann &lt;heiko@lotte.sax.de&gt;&n; * VERSION: @VERSION@&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Thanks to&n; *  The Linux Community at all and ...&n; *  Martin Harris (he wrote the first Mitsumi Driver)&n; *  Eberhard Moenkeberg (he gave me much support and the initial kick)&n; *  Bernd Huebner, Ruediger Helsch (Unifix-Software Gmbh, they&n; *      improved the original driver)&n; *  Jon Tombs, Bjorn Ekwall (module support)&n; *  Daniel v. Mosnenck (he sent me the Technical and Programming Reference)&n; *  Gerd Knorr (he lent me his PhotoCD)&n; *  Nils Faerber and Roger E. Wolff (extensively tested the LU portion)&n; *  Andreas Kies (testing the mysterious hang up&squot;s)&n; *  ... somebody forgotten?&n; *  Marcin Dalecki&n; *  &n; */
multiline_comment|/*&n; *&t;The following lines are for user configuration&n; *&t;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; *&t;{0|1} -- 1 if you want the driver detect your drive, may crash and&n; *&t;needs a long time to seek.  The higher the address the longer the&n; *&t;seek.&n; *&n; *  WARNING: AUTOPROBE doesn&squot;t work.&n; */
DECL|macro|MCDX_AUTOPROBE
mdefine_line|#define MCDX_AUTOPROBE 0
multiline_comment|/*&n; *&t;Drive specific settings according to the jumpers on the controller&n; *&t;board(s).&n; *&t;o&t;MCDX_NDRIVES  :  number of used entries of the following table&n; *&t;o&t;MCDX_DRIVEMAP :  table of {i/o base, irq} per controller&n; *&n; *&t;NOTE: I didn&squot;t get a drive at irq 9(2) working.  Not even alone.&n; */
macro_line|#if MCDX_AUTOPROBE == 0
DECL|macro|MCDX_NDRIVES
mdefine_line|#define MCDX_NDRIVES 1
DECL|macro|MCDX_DRIVEMAP
mdefine_line|#define MCDX_DRIVEMAP {&t;&t;&bslash;&n;&t;&t;&t;{0x300, 11},&t;&bslash;&n;&t;&t;&t;{0x304, 05},  &t;&bslash;&n;&t;&t;&t;{0x000, 00},  &t;&bslash;&n;&t;&t;&t;{0x000, 00},  &t;&bslash;&n;&t;&t;&t;{0x000, 00},  &t;&bslash;&n;&t;  &t;}
macro_line|#else
macro_line|#error Autoprobing is not implemented yet.
macro_line|#endif
macro_line|#ifndef MCDX_QUIET
DECL|macro|MCDX_QUIET
mdefine_line|#define MCDX_QUIET   1
macro_line|#endif
macro_line|#ifndef MCDX_DEBUG
DECL|macro|MCDX_DEBUG
mdefine_line|#define MCDX_DEBUG   0
macro_line|#endif
multiline_comment|/* *** make the following line uncommented, if you&squot;re sure,&n; * *** all configuration is done */
multiline_comment|/* #define I_WAS_HERE */
multiline_comment|/*&t;The name of the device */
DECL|macro|MCDX
mdefine_line|#define MCDX &quot;mcdx&quot;&t;
multiline_comment|/* Flags for DEBUGGING */
DECL|macro|INIT
mdefine_line|#define INIT &t;&t;0
DECL|macro|MALLOC
mdefine_line|#define MALLOC &t;&t;0
DECL|macro|IOCTL
mdefine_line|#define IOCTL &t;&t;0
DECL|macro|PLAYTRK
mdefine_line|#define PLAYTRK     0
DECL|macro|SUBCHNL
mdefine_line|#define SUBCHNL     0
DECL|macro|TOCHDR
mdefine_line|#define TOCHDR      0
DECL|macro|MS
mdefine_line|#define MS          0
DECL|macro|PLAYMSF
mdefine_line|#define PLAYMSF     0
DECL|macro|READTOC
mdefine_line|#define READTOC     0
DECL|macro|OPENCLOSE
mdefine_line|#define OPENCLOSE &t;0
DECL|macro|HW
mdefine_line|#define HW&t;&t;    0
DECL|macro|TALK
mdefine_line|#define TALK&t;&t;0
DECL|macro|IRQ
mdefine_line|#define IRQ &t;&t;0
DECL|macro|XFER
mdefine_line|#define XFER &t;&t;0
DECL|macro|REQUEST
mdefine_line|#define REQUEST&t; &t;0
DECL|macro|SLEEP
mdefine_line|#define SLEEP&t;&t;0
multiline_comment|/*&t;The following addresses are taken from the Mitsumi Reference &n; *  and describe the possible i/o range for the controller.&n; */
DECL|macro|MCDX_IO_BEGIN
mdefine_line|#define MCDX_IO_BEGIN&t;((char*) 0x300)&t;/* first base of i/o addr */
DECL|macro|MCDX_IO_END
mdefine_line|#define MCDX_IO_END&t;&t;((char*) 0x3fc)&t;/* last base of i/o addr */
multiline_comment|/*&t;Per controller 4 bytes i/o are needed. */
DECL|macro|MCDX_IO_SIZE
mdefine_line|#define MCDX_IO_SIZE&t;&t;4
multiline_comment|/*&n; *&t;Bits&n; */
multiline_comment|/* The status byte, returned from every command, set if&n; * the description is true */
DECL|macro|MCDX_RBIT_OPEN
mdefine_line|#define MCDX_RBIT_OPEN       0x80&t;/* door is open */
DECL|macro|MCDX_RBIT_DISKSET
mdefine_line|#define MCDX_RBIT_DISKSET    0x40&t;/* disk set (recognised) */
DECL|macro|MCDX_RBIT_CHANGED
mdefine_line|#define MCDX_RBIT_CHANGED    0x20&t;/* disk was changed */
DECL|macro|MCDX_RBIT_CHECK
mdefine_line|#define MCDX_RBIT_CHECK      0x10&t;/* disk rotates, servo is on */
DECL|macro|MCDX_RBIT_AUDIOTR
mdefine_line|#define MCDX_RBIT_AUDIOTR    0x08   /* current track is audio */
DECL|macro|MCDX_RBIT_RDERR
mdefine_line|#define MCDX_RBIT_RDERR      0x04&t;/* read error, refer SENSE KEY */
DECL|macro|MCDX_RBIT_AUDIOBS
mdefine_line|#define MCDX_RBIT_AUDIOBS    0x02&t;/* currently playing audio */
DECL|macro|MCDX_RBIT_CMDERR
mdefine_line|#define MCDX_RBIT_CMDERR     0x01&t;/* command, param or format error */
multiline_comment|/* The I/O Register holding the h/w status of the drive,&n; * can be read at i/o base + 1 */
DECL|macro|MCDX_RBIT_DOOR
mdefine_line|#define MCDX_RBIT_DOOR       0x10&t;/* door is open */
DECL|macro|MCDX_RBIT_STEN
mdefine_line|#define MCDX_RBIT_STEN       0x04&t;/* if 0, i/o base contains drive status */
DECL|macro|MCDX_RBIT_DTEN
mdefine_line|#define MCDX_RBIT_DTEN       0x02&t;/* if 0, i/o base contains data */
multiline_comment|/*&n; *&t;The commands.&n; */
DECL|macro|OPCODE
mdefine_line|#define OPCODE&t;1&t;&t;/* offset of opcode */
DECL|macro|MCDX_CMD_REQUEST_TOC
mdefine_line|#define MCDX_CMD_REQUEST_TOC&t;&t;1, 0x10
DECL|macro|MCDX_CMD_REQUEST_STATUS
mdefine_line|#define MCDX_CMD_REQUEST_STATUS&t;&t;1, 0x40 
DECL|macro|MCDX_CMD_RESET
mdefine_line|#define MCDX_CMD_RESET&t;&t;&t;&t;1, 0x60
DECL|macro|MCDX_CMD_REQUEST_DRIVE_MODE
mdefine_line|#define MCDX_CMD_REQUEST_DRIVE_MODE&t;1, 0xc2
DECL|macro|MCDX_CMD_SET_INTERLEAVE
mdefine_line|#define MCDX_CMD_SET_INTERLEAVE&t;&t;2, 0xc8, 0
DECL|macro|MCDX_CMD_DATAMODE_SET
mdefine_line|#define MCDX_CMD_DATAMODE_SET&t;&t;2, 0xa0, 0
DECL|macro|MCDX_DATAMODE1
mdefine_line|#define MCDX_DATAMODE1&t;&t;0x01
DECL|macro|MCDX_DATAMODE2
mdefine_line|#define MCDX_DATAMODE2&t;&t;0x02
DECL|macro|MCDX_CMD_LOCK_DOOR
mdefine_line|#define MCDX_CMD_LOCK_DOOR&t;&t;2, 0xfe, 0
DECL|macro|READ_AHEAD
mdefine_line|#define READ_AHEAD&t;&t;&t;4&t;/* 8 Sectors (4K) */
multiline_comment|/*&t;Useful macros */
DECL|macro|e_door
mdefine_line|#define e_door(x)&t;&t;((x) &amp; MCDX_RBIT_OPEN)
DECL|macro|e_check
mdefine_line|#define e_check(x)&t;&t;(~(x) &amp; MCDX_RBIT_CHECK)
DECL|macro|e_notset
mdefine_line|#define e_notset(x)&t;&t;(~(x) &amp; MCDX_RBIT_DISKSET)
DECL|macro|e_changed
mdefine_line|#define e_changed(x)&t;((x) &amp; MCDX_RBIT_CHANGED)
DECL|macro|e_audio
mdefine_line|#define e_audio(x)&t;&t;((x) &amp; MCDX_RBIT_AUDIOTR)
DECL|macro|e_audiobusy
mdefine_line|#define e_audiobusy(x)&t;((x) &amp; MCDX_RBIT_AUDIOBS)
DECL|macro|e_cmderr
mdefine_line|#define e_cmderr(x)&t;&t;((x) &amp; MCDX_RBIT_CMDERR)
DECL|macro|e_readerr
mdefine_line|#define e_readerr(x)&t;((x) &amp; MCDX_RBIT_RDERR)
multiline_comment|/**&t;no drive specific */
DECL|macro|MCDX_CDBLK
mdefine_line|#define MCDX_CDBLK&t;2048&t;/* 2048 cooked data each blk */
DECL|macro|MCDX_DATA_TIMEOUT
mdefine_line|#define MCDX_DATA_TIMEOUT&t;(HZ/10)&t;/* 0.1 second */
multiline_comment|/*&n; * Access to the msf array&n; */
DECL|macro|MSF_MIN
mdefine_line|#define MSF_MIN&t;&t;0&t;&t;&t;/* minute */
DECL|macro|MSF_SEC
mdefine_line|#define MSF_SEC&t;&t;1&t;&t;&t;/* second */
DECL|macro|MSF_FRM
mdefine_line|#define MSF_FRM&t;&t;2&t;&t;&t;/* frame  */
multiline_comment|/*&n; * Errors&n; */
DECL|macro|MCDX_E
mdefine_line|#define MCDX_E&t;&t;1&t;&t;&t;/* unspec error */
DECL|macro|MCDX_ST_EOM
mdefine_line|#define MCDX_ST_EOM 0x0100&t;&t;/* end of media */
DECL|macro|MCDX_ST_DRV
mdefine_line|#define MCDX_ST_DRV 0x00ff&t;&t;/* mask to query the drive status */
macro_line|#ifndef I_WAS_HERE
macro_line|#ifndef MODULE
macro_line|#warning You have not edited mcdx.h
macro_line|#warning Perhaps irq and i/o settings are wrong.
macro_line|#endif
macro_line|#endif
multiline_comment|/* ex:set ts=4 sw=4: */
eof
