multiline_comment|/*&n; * Definitions for a GoldStar R420 CD-ROM interface&n; *&n; *   Copyright (C) 1995  Oliver Raupach &lt;raupach@nwfs1.rz.fh-hannover.de&gt;&n; *                       Eberhard Moenkeberg &lt;emoenke@gwdg.de&gt;&n; *&n; *  Published under the GPL.&n; *&n; */
multiline_comment|/* The Interface Card default address is 0x340. This will work for most&n;   applications. Address selection is accomplished by jumpers PN801-1 to&n;   PN801-4 on the GoldStar Interface Card.&n;   Appropriate settings are: 0x300, 0x310, 0x320, 0x330, 0x340, 0x350, 0x360&n;   0x370, 0x380, 0x390, 0x3A0, 0x3B0, 0x3C0, 0x3D0, 0x3E0, 0x3F0             */
multiline_comment|/* insert here the I/O port address */
DECL|macro|GSCD_BASE_ADDR
mdefine_line|#define GSCD_BASE_ADDR&t;        0x340
multiline_comment|/* change this to set the dma-channel */
DECL|macro|GSCD_DMA_CHANNEL
mdefine_line|#define GSCD_DMA_CHANNEL        3                  /* not used */ 
multiline_comment|/************** nothing to set up below here *********************/
multiline_comment|/* port access macro */
DECL|macro|GSCDPORT
mdefine_line|#define GSCDPORT(x)&t;&t;(gscd_port + (x))
multiline_comment|/*&n; * commands&n; * the lower nibble holds the command length&n; */
DECL|macro|CMD_STATUS
mdefine_line|#define CMD_STATUS     0x01
DECL|macro|CMD_READSUBQ
mdefine_line|#define CMD_READSUBQ   0x02 /* 1: ?, 2: UPC, 5: ? */
DECL|macro|CMD_SEEK
mdefine_line|#define CMD_SEEK       0x05 /* read_mode M-S-F */
DECL|macro|CMD_READ
mdefine_line|#define CMD_READ       0x07 /* read_mode M-S-F nsec_h nsec_l */
DECL|macro|CMD_RESET
mdefine_line|#define CMD_RESET      0x11
DECL|macro|CMD_SETMODE
mdefine_line|#define CMD_SETMODE    0x15
DECL|macro|CMD_PLAY
mdefine_line|#define CMD_PLAY       0x17 /* M-S-F M-S-F */
DECL|macro|CMD_LOCK_CTL
mdefine_line|#define CMD_LOCK_CTL   0x22 /* 0: unlock, 1: lock */
DECL|macro|CMD_IDENT
mdefine_line|#define CMD_IDENT      0x31
DECL|macro|CMD_SETSPEED
mdefine_line|#define CMD_SETSPEED   0x32 /* 0: auto */ /* ??? */
DECL|macro|CMD_GETMODE
mdefine_line|#define CMD_GETMODE    0x41
DECL|macro|CMD_PAUSE
mdefine_line|#define CMD_PAUSE      0x51
DECL|macro|CMD_READTOC
mdefine_line|#define CMD_READTOC    0x61
DECL|macro|CMD_DISKINFO
mdefine_line|#define CMD_DISKINFO   0x71
DECL|macro|CMD_TRAY_CTL
mdefine_line|#define CMD_TRAY_CTL   0x81
multiline_comment|/*&n; * disk_state:&n; */
DECL|macro|ST_PLAYING
mdefine_line|#define ST_PLAYING&t;0x80
DECL|macro|ST_UNLOCKED
mdefine_line|#define ST_UNLOCKED&t;0x40
DECL|macro|ST_NO_DISK
mdefine_line|#define ST_NO_DISK&t;0x20
DECL|macro|ST_DOOR_OPEN
mdefine_line|#define ST_DOOR_OPEN&t;0x10
DECL|macro|ST_x08
mdefine_line|#define ST_x08  0x08
DECL|macro|ST_x04
mdefine_line|#define ST_x04&t;0x04
DECL|macro|ST_INVALID
mdefine_line|#define ST_INVALID&t;0x02
DECL|macro|ST_x01
mdefine_line|#define ST_x01&t;0x01
multiline_comment|/*&n; * cmd_type:&n; */
DECL|macro|TYPE_INFO
mdefine_line|#define TYPE_INFO&t;0x01
DECL|macro|TYPE_DATA
mdefine_line|#define TYPE_DATA&t;0x02
multiline_comment|/*&n; * read_mode:&n; */
DECL|macro|MOD_POLLED
mdefine_line|#define MOD_POLLED&t;0x80
DECL|macro|MOD_x08
mdefine_line|#define MOD_x08&t;0x08
DECL|macro|MOD_RAW
mdefine_line|#define MOD_RAW&t;0x04
DECL|macro|READ_DATA
mdefine_line|#define READ_DATA(port, buf, nr) insb(port, buf, nr)
DECL|macro|SET_TIMER
mdefine_line|#define SET_TIMER(func, jifs) &bslash;&n;&t;((mod_timer(&amp;gscd_timer, jiffies + jifs)), &bslash;&n;&t;(gscd_timer.function = func))
DECL|macro|CLEAR_TIMER
mdefine_line|#define CLEAR_TIMER&t;&t;del_timer_sync(&amp;gscd_timer)
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
DECL|struct|gscd_Play_msf
r_struct
id|gscd_Play_msf
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
DECL|struct|gscd_DiskInfo
r_struct
id|gscd_DiskInfo
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
DECL|struct|gscd_Toc
r_struct
id|gscd_Toc
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
