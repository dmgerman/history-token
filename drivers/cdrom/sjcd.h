multiline_comment|/*&n; * Definitions for a Sanyo CD-ROM interface.&n; *&n; *   Copyright (C) 1995  Vadim V. Model&n; *                                       model@cecmow.enet.dec.com&n; *                                       vadim@rbrf.msk.su&n; *                                       vadim@ipsun.ras.ru&n; *                       Eric van der Maarel&n; *                                       H.T.M.v.d.Maarel@marin.nl&n; *&n; *  This information is based on mcd.c from M. Harriss and sjcd102.lst from&n; *  E. Moenkeberg.&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __SJCD_H__
DECL|macro|__SJCD_H__
mdefine_line|#define __SJCD_H__
multiline_comment|/*&n; * Change this to set the I/O port address as default. More flexibility&n; * come with setup implementation.&n; */
DECL|macro|SJCD_BASE_ADDR
mdefine_line|#define SJCD_BASE_ADDR      0x340
multiline_comment|/*&n; * Change this to set the irq as default. Really SANYO do not use interrupts&n; * at all.&n; */
DECL|macro|SJCD_INTR_NR
mdefine_line|#define SJCD_INTR_NR        0
multiline_comment|/*&n; * Change this to set the dma as default value. really SANYO does not use&n; * direct memory access at all.&n; */
DECL|macro|SJCD_DMA_NR
mdefine_line|#define SJCD_DMA_NR         0
multiline_comment|/*&n; * Macros which allow us to find out the status of the drive.&n; */
DECL|macro|SJCD_STATUS_AVAILABLE
mdefine_line|#define SJCD_STATUS_AVAILABLE( x ) (((x)&amp;0x02)==0)
DECL|macro|SJCD_DATA_AVAILABLE
mdefine_line|#define SJCD_DATA_AVAILABLE( x )   (((x)&amp;0x01)==0)
multiline_comment|/*&n; * Port access macro. Three ports are available: S-data port (command port),&n; * status port (read only) and D-data port (read only).&n; */
DECL|macro|SJCDPORT
mdefine_line|#define SJCDPORT( x )       ( sjcd_base + ( x ) )
DECL|macro|SJCD_STATUS_PORT
mdefine_line|#define SJCD_STATUS_PORT    SJCDPORT( 1 )
DECL|macro|SJCD_S_DATA_PORT
mdefine_line|#define SJCD_S_DATA_PORT    SJCDPORT( 0 )
DECL|macro|SJCD_COMMAND_PORT
mdefine_line|#define SJCD_COMMAND_PORT   SJCDPORT( 0 )
DECL|macro|SJCD_D_DATA_PORT
mdefine_line|#define SJCD_D_DATA_PORT    SJCDPORT( 2 )
multiline_comment|/*&n; * Drive info bits. Drive info available as first (mandatory) byte of&n; * command completion status.&n; */
DECL|macro|SST_NOT_READY
mdefine_line|#define SST_NOT_READY       0x10        /* no disk in the drive (???) */
DECL|macro|SST_MEDIA_CHANGED
mdefine_line|#define SST_MEDIA_CHANGED   0x20        /* disk is changed */
DECL|macro|SST_DOOR_OPENED
mdefine_line|#define SST_DOOR_OPENED     0x40        /* door is open */
multiline_comment|/* commands */
DECL|macro|SCMD_EJECT_TRAY
mdefine_line|#define SCMD_EJECT_TRAY     0xD0        /* eject tray if not locked */
DECL|macro|SCMD_LOCK_TRAY
mdefine_line|#define SCMD_LOCK_TRAY      0xD2        /* lock tray when in */
DECL|macro|SCMD_UNLOCK_TRAY
mdefine_line|#define SCMD_UNLOCK_TRAY    0xD4        /* unlock tray when in */
DECL|macro|SCMD_CLOSE_TRAY
mdefine_line|#define SCMD_CLOSE_TRAY     0xD6        /* load tray in */
DECL|macro|SCMD_RESET
mdefine_line|#define SCMD_RESET          0xFA        /* soft reset */
DECL|macro|SCMD_GET_STATUS
mdefine_line|#define SCMD_GET_STATUS     0x80
DECL|macro|SCMD_GET_VERSION
mdefine_line|#define SCMD_GET_VERSION    0xCC
DECL|macro|SCMD_DATA_READ
mdefine_line|#define SCMD_DATA_READ      0xA0        /* are the same, depend on mode&amp;args */
DECL|macro|SCMD_SEEK
mdefine_line|#define SCMD_SEEK           0xA0
DECL|macro|SCMD_PLAY
mdefine_line|#define SCMD_PLAY           0xA0
DECL|macro|SCMD_GET_QINFO
mdefine_line|#define SCMD_GET_QINFO      0xA8
DECL|macro|SCMD_SET_MODE
mdefine_line|#define SCMD_SET_MODE       0xC4
DECL|macro|SCMD_MODE_PLAY
mdefine_line|#define SCMD_MODE_PLAY      0xE0
DECL|macro|SCMD_MODE_COOKED
mdefine_line|#define SCMD_MODE_COOKED    (0xF8 &amp; ~0x20)
DECL|macro|SCMD_MODE_RAW
mdefine_line|#define SCMD_MODE_RAW       0xF9
DECL|macro|SCMD_MODE_x20_BIT
mdefine_line|#define SCMD_MODE_x20_BIT   0x20        /* What is it for ? */
DECL|macro|SCMD_SET_VOLUME
mdefine_line|#define SCMD_SET_VOLUME     0xAE
DECL|macro|SCMD_PAUSE
mdefine_line|#define SCMD_PAUSE          0xE0
DECL|macro|SCMD_STOP
mdefine_line|#define SCMD_STOP           0xE0
DECL|macro|SCMD_GET_DISK_INFO
mdefine_line|#define SCMD_GET_DISK_INFO  0xAA
multiline_comment|/*&n; * Some standard arguments for SCMD_GET_DISK_INFO.&n; */
DECL|macro|SCMD_GET_1_TRACK
mdefine_line|#define SCMD_GET_1_TRACK    0xA0    /* get the first track information */
DECL|macro|SCMD_GET_L_TRACK
mdefine_line|#define SCMD_GET_L_TRACK    0xA1    /* get the last track information */
DECL|macro|SCMD_GET_D_SIZE
mdefine_line|#define SCMD_GET_D_SIZE     0xA2    /* get the whole disk information */
multiline_comment|/*&n; * Borrowed from hd.c. Allows to optimize multiple port read commands.&n; */
DECL|macro|S_READ_DATA
mdefine_line|#define S_READ_DATA( port, buf, nr )      insb( port, buf, nr )
multiline_comment|/*&n; * We assume that there are no audio disks with TOC length more than this&n; * number (I personally have never seen disks with more than 20 fragments).&n; */
DECL|macro|SJCD_MAX_TRACKS
mdefine_line|#define SJCD_MAX_TRACKS&t;&t;100
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
DECL|struct|sjcd_hw_disk_info
r_struct
id|sjcd_hw_disk_info
(brace
DECL|member|track_control
r_int
r_char
id|track_control
suffix:semicolon
DECL|member|track_no
r_int
r_char
id|track_no
suffix:semicolon
DECL|member|x
DECL|member|y
DECL|member|z
r_int
r_char
id|x
comma
id|y
comma
id|z
suffix:semicolon
r_union
(brace
DECL|member|track_no
r_int
r_char
id|track_no
suffix:semicolon
DECL|member|track_msf
r_struct
id|msf
id|track_msf
suffix:semicolon
DECL|member|un
)brace
id|un
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sjcd_hw_qinfo
r_struct
id|sjcd_hw_qinfo
(brace
DECL|member|track_control
r_int
r_char
id|track_control
suffix:semicolon
DECL|member|track_no
r_int
r_char
id|track_no
suffix:semicolon
DECL|member|x
r_int
r_char
id|x
suffix:semicolon
DECL|member|rel
r_struct
id|msf
id|rel
suffix:semicolon
DECL|member|abs
r_struct
id|msf
id|abs
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sjcd_play_msf
r_struct
id|sjcd_play_msf
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
DECL|struct|sjcd_disk_info
r_struct
id|sjcd_disk_info
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
DECL|member|disk_length
r_struct
id|msf
id|disk_length
suffix:semicolon
DECL|member|first_track
r_struct
id|msf
id|first_track
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sjcd_toc
r_struct
id|sjcd_toc
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
DECL|member|point_index
r_int
r_char
id|point_index
suffix:semicolon
DECL|member|track_time
r_struct
id|msf
id|track_time
suffix:semicolon
DECL|member|disk_time
r_struct
id|msf
id|disk_time
suffix:semicolon
)brace
suffix:semicolon
macro_line|#if defined( SJCD_GATHER_STAT )
DECL|struct|sjcd_stat
r_struct
id|sjcd_stat
(brace
DECL|member|ticks
r_int
id|ticks
suffix:semicolon
DECL|member|tticks
r_int
id|tticks
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|idle_ticks
r_int
id|idle_ticks
suffix:semicolon
DECL|member|start_ticks
r_int
id|start_ticks
suffix:semicolon
DECL|member|mode_ticks
r_int
id|mode_ticks
suffix:semicolon
DECL|member|read_ticks
r_int
id|read_ticks
suffix:semicolon
DECL|member|data_ticks
r_int
id|data_ticks
suffix:semicolon
DECL|member|stop_ticks
r_int
id|stop_ticks
suffix:semicolon
DECL|member|stopping_ticks
r_int
id|stopping_ticks
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
