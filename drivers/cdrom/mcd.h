multiline_comment|/*&n; * Definitions for a Mitsumi CD-ROM interface&n; *&n; *&t;Copyright (C) 1992  Martin Harriss&n; *&n; *&t;martin@bdsi.com&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
multiline_comment|/* Increase this if you get lots of timeouts */
DECL|macro|MCD_STATUS_DELAY
mdefine_line|#define MCD_STATUS_DELAY&t;1000
multiline_comment|/* number of times to retry a command before giving up */
DECL|macro|MCD_RETRY_ATTEMPTS
mdefine_line|#define MCD_RETRY_ATTEMPTS      10
multiline_comment|/* port access macro */
DECL|macro|MCDPORT
mdefine_line|#define MCDPORT(x)&t;&t;(mcd_port + (x))
multiline_comment|/* How many sectors to read at 1x when an error at 2x speed occurs. */
multiline_comment|/* You can change this to anything from 2 to 32767, but 30 seems to */
multiline_comment|/* work best for me.  I have found that when the drive has problems */
multiline_comment|/* reading one sector, it will have troubles reading the next few.  */
DECL|macro|SINGLE_HOLD_SECTORS
mdefine_line|#define SINGLE_HOLD_SECTORS 30&t;
DECL|macro|MCMD_2X_READ
mdefine_line|#define MCMD_2X_READ 0xC1&t;/* Double Speed Read DON&squot;T TOUCH! */
multiline_comment|/* status bits */
DECL|macro|MST_CMD_CHECK
mdefine_line|#define MST_CMD_CHECK&t;&t;0x01&t;&t;/* command error */
DECL|macro|MST_BUSY
mdefine_line|#define MST_BUSY&t;&t;0x02&t;&t;/* now playing */
DECL|macro|MST_READ_ERR
mdefine_line|#define MST_READ_ERR&t;&t;0x04&t;&t;/* read error */
DECL|macro|MST_DSK_TYPE
mdefine_line|#define MST_DSK_TYPE&t;&t;0x08
DECL|macro|MST_SERVO_CHECK
mdefine_line|#define MST_SERVO_CHECK&t;&t;0x10
DECL|macro|MST_DSK_CHG
mdefine_line|#define MST_DSK_CHG&t;&t;0x20&t;&t;/* disk removed or changed */
DECL|macro|MST_READY
mdefine_line|#define MST_READY&t;&t;0x40&t;&t;/* disk in the drive */
DECL|macro|MST_DOOR_OPEN
mdefine_line|#define MST_DOOR_OPEN&t;&t;0x80&t;&t;/* door is open */
multiline_comment|/* flag bits */
DECL|macro|MFL_DATA
mdefine_line|#define MFL_DATA&t;&t;0x02&t;&t;/* data available */
DECL|macro|MFL_STATUS
mdefine_line|#define MFL_STATUS&t;&t;0x04&t;&t;/* status available */
multiline_comment|/* commands */
DECL|macro|MCMD_GET_DISK_INFO
mdefine_line|#define MCMD_GET_DISK_INFO&t;0x10&t;&t;/* read info from disk */
DECL|macro|MCMD_GET_Q_CHANNEL
mdefine_line|#define MCMD_GET_Q_CHANNEL&t;0x20&t;&t;/* read info from q channel */
DECL|macro|MCMD_GET_STATUS
mdefine_line|#define MCMD_GET_STATUS&t;&t;0x40
DECL|macro|MCMD_SET_MODE
mdefine_line|#define MCMD_SET_MODE&t;&t;0x50
DECL|macro|MCMD_SOFT_RESET
mdefine_line|#define MCMD_SOFT_RESET&t;&t;0x60
DECL|macro|MCMD_STOP
mdefine_line|#define MCMD_STOP&t;&t;0x70&t;&t;/* stop play */
DECL|macro|MCMD_CONFIG_DRIVE
mdefine_line|#define MCMD_CONFIG_DRIVE&t;0x90
DECL|macro|MCMD_SET_VOLUME
mdefine_line|#define MCMD_SET_VOLUME&t;&t;0xAE&t;&t;/* set audio level */
DECL|macro|MCMD_PLAY_READ
mdefine_line|#define MCMD_PLAY_READ&t;&t;0xC0&t;&t;/* play or read data */
DECL|macro|MCMD_GET_VERSION
mdefine_line|#define MCMD_GET_VERSION  &t;0xDC
DECL|macro|MCMD_EJECT
mdefine_line|#define MCMD_EJECT&t;&t;0xF6            /* eject (FX drive) */
multiline_comment|/* borrowed from hd.c */
DECL|macro|READ_DATA
mdefine_line|#define READ_DATA(port, buf, nr) &bslash;&n;insb(port, buf, nr)
DECL|macro|SET_TIMER
mdefine_line|#define SET_TIMER(func, jifs) &t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;mcd_timer.function = func;&t;&t;&bslash;&n;&t;&t;mod_timer(&amp;mcd_timer, jiffies + jifs);&t;&bslash;&n;&t;} while (0)
DECL|macro|CLEAR_TIMER
mdefine_line|#define CLEAR_TIMER&t;&t;del_timer_async(&amp;mcd_timer);
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
DECL|struct|mcd_Play_msf
r_struct
id|mcd_Play_msf
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
DECL|struct|mcd_DiskInfo
r_struct
id|mcd_DiskInfo
(brace
DECL|member|first
r_int
r_char
id|first
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
)brace
suffix:semicolon
DECL|struct|mcd_Toc
r_struct
id|mcd_Toc
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
