multiline_comment|/*&n; *  linux/drivers/ide/ide_cd.h&n; *&n; *  Copyright (C) 1996-98  Erik Andersen&n; *  Copyright (C) 1998-2000 Jens Axboe&n; */
macro_line|#ifndef _IDE_CD_H
DECL|macro|_IDE_CD_H
mdefine_line|#define _IDE_CD_H
macro_line|#include &lt;linux/cdrom.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
multiline_comment|/* Turn this on to have the driver print out the meanings of the&n;   ATAPI error codes.  This will use up additional kernel-space&n;   memory, though. */
macro_line|#ifndef VERBOSE_IDE_CD_ERRORS
DECL|macro|VERBOSE_IDE_CD_ERRORS
mdefine_line|#define VERBOSE_IDE_CD_ERRORS 1
macro_line|#endif
multiline_comment|/* Turning this on will remove code to work around various nonstandard&n;   ATAPI implementations.  If you know your drive follows the standard,&n;   this will give you a slightly smaller kernel. */
macro_line|#ifndef STANDARD_ATAPI
DECL|macro|STANDARD_ATAPI
mdefine_line|#define STANDARD_ATAPI 0
macro_line|#endif
multiline_comment|/* Turning this on will disable the door-locking functionality.&n;   This is apparently needed for supermount. */
macro_line|#ifndef NO_DOOR_LOCKING
DECL|macro|NO_DOOR_LOCKING
mdefine_line|#define NO_DOOR_LOCKING 0
macro_line|#endif
multiline_comment|/************************************************************************/
DECL|macro|SECTOR_BITS
mdefine_line|#define SECTOR_BITS &t;&t;9
DECL|macro|SECTOR_SIZE
mdefine_line|#define SECTOR_SIZE&t;&t;(1 &lt;&lt; SECTOR_BITS)
DECL|macro|SECTORS_PER_FRAME
mdefine_line|#define SECTORS_PER_FRAME&t;(CD_FRAMESIZE &gt;&gt; SECTOR_BITS)
DECL|macro|SECTOR_BUFFER_SIZE
mdefine_line|#define SECTOR_BUFFER_SIZE&t;(CD_FRAMESIZE * 32)
DECL|macro|SECTORS_BUFFER
mdefine_line|#define SECTORS_BUFFER&t;&t;(SECTOR_BUFFER_SIZE &gt;&gt; SECTOR_BITS)
DECL|macro|SECTORS_MAX
mdefine_line|#define SECTORS_MAX&t;&t;(131072 &gt;&gt; SECTOR_BITS)
DECL|macro|BLOCKS_PER_FRAME
mdefine_line|#define BLOCKS_PER_FRAME&t;(CD_FRAMESIZE / BLOCK_SIZE)
DECL|macro|MIN
mdefine_line|#define MIN(a,b) ((a) &lt; (b) ? (a) : (b))
multiline_comment|/* special command codes for strategy routine. */
DECL|macro|PACKET_COMMAND
mdefine_line|#define PACKET_COMMAND        4315
DECL|macro|REQUEST_SENSE_COMMAND
mdefine_line|#define REQUEST_SENSE_COMMAND 4316
DECL|macro|RESET_DRIVE_COMMAND
mdefine_line|#define RESET_DRIVE_COMMAND   4317
multiline_comment|/* Configuration flags.  These describe the capabilities of the drive.&n;   They generally do not change after initialization, unless we learn&n;   more about the drive from stuff failing. */
DECL|struct|ide_cd_config_flags
r_struct
id|ide_cd_config_flags
(brace
DECL|member|drq_interrupt
id|__u8
id|drq_interrupt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Device sends an interrupt when ready&n;&t;&t;&t;&t;&t;for a packet command. */
DECL|member|no_doorlock
id|__u8
id|no_doorlock
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive cannot lock the door. */
DECL|member|no_eject
id|__u8
id|no_eject
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive cannot eject the disc. */
DECL|member|nec260
id|__u8
id|nec260
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive is a pre-1.2 NEC 260 drive. */
DECL|member|playmsf_as_bcd
id|__u8
id|playmsf_as_bcd
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* PLAYMSF command takes BCD args. */
DECL|member|tocaddr_as_bcd
id|__u8
id|tocaddr_as_bcd
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* TOC addresses are in BCD. */
DECL|member|toctracks_as_bcd
id|__u8
id|toctracks_as_bcd
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* TOC track numbers are in BCD. */
DECL|member|subchan_as_bcd
id|__u8
id|subchan_as_bcd
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Subchannel info is in BCD. */
DECL|member|is_changer
id|__u8
id|is_changer
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive is a changer. */
DECL|member|cd_r
id|__u8
id|cd_r
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can write to CD-R media . */
DECL|member|cd_rw
id|__u8
id|cd_rw
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can write to CD-R/W media . */
DECL|member|dvd
id|__u8
id|dvd
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive is a DVD-ROM */
DECL|member|dvd_r
id|__u8
id|dvd_r
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can write DVD-R */
DECL|member|dvd_ram
id|__u8
id|dvd_ram
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can write DVD-RAM */
DECL|member|test_write
id|__u8
id|test_write
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can fake writes */
DECL|member|supp_disc_present
id|__u8
id|supp_disc_present
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Changer can report exact contents&n;&t;&t;&t;&t;&t;of slots. */
DECL|member|limit_nframes
id|__u8
id|limit_nframes
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive does not provide data in&n;&t;&t;&t;&t;&t;multiples of SECTOR_SIZE when more&n;&t;&t;&t;&t;&t;than one interrupt is needed. */
DECL|member|seeking
id|__u8
id|seeking
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Seeking in progress */
DECL|member|audio_play
id|__u8
id|audio_play
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* can do audio related commands */
DECL|member|close_tray
id|__u8
id|close_tray
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* can close the tray */
DECL|member|writing
id|__u8
id|writing
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* pseudo write in progress */
DECL|member|reserved
id|__u8
id|reserved
suffix:colon
l_int|3
suffix:semicolon
DECL|member|max_speed
id|byte
id|max_speed
suffix:semicolon
multiline_comment|/* Max speed of the drive */
)brace
suffix:semicolon
DECL|macro|CDROM_CONFIG_FLAGS
mdefine_line|#define CDROM_CONFIG_FLAGS(drive) (&amp;(((struct cdrom_info *)(drive-&gt;driver_data))-&gt;config_flags))
multiline_comment|/* State flags.  These give information about the current state of the&n;   drive, and will change during normal operation. */
DECL|struct|ide_cd_state_flags
r_struct
id|ide_cd_state_flags
(brace
DECL|member|media_changed
id|__u8
id|media_changed
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Driver has noticed a media change. */
DECL|member|toc_valid
id|__u8
id|toc_valid
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Saved TOC information is current. */
DECL|member|door_locked
id|__u8
id|door_locked
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* We think that the drive door is locked. */
DECL|member|writing
id|__u8
id|writing
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* the drive is currently writing */
DECL|member|reserved
id|__u8
id|reserved
suffix:colon
l_int|4
suffix:semicolon
DECL|member|current_speed
id|byte
id|current_speed
suffix:semicolon
multiline_comment|/* Current speed of the drive */
)brace
suffix:semicolon
DECL|macro|CDROM_STATE_FLAGS
mdefine_line|#define CDROM_STATE_FLAGS(drive) (&amp;(((struct cdrom_info *)(drive-&gt;driver_data))-&gt;state_flags))
DECL|struct|packet_command
r_struct
id|packet_command
(brace
DECL|member|buffer
r_char
op_star
id|buffer
suffix:semicolon
DECL|member|buflen
r_int
id|buflen
suffix:semicolon
DECL|member|stat
r_int
id|stat
suffix:semicolon
DECL|member|quiet
r_int
id|quiet
suffix:semicolon
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
DECL|member|sense
r_struct
id|request_sense
op_star
id|sense
suffix:semicolon
DECL|member|c
r_int
r_char
id|c
(braket
l_int|12
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Structure of a MSF cdrom address. */
DECL|struct|atapi_msf
r_struct
id|atapi_msf
(brace
DECL|member|reserved
id|byte
id|reserved
suffix:semicolon
DECL|member|minute
id|byte
id|minute
suffix:semicolon
DECL|member|second
id|byte
id|second
suffix:semicolon
DECL|member|frame
id|byte
id|frame
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Space to hold the disk TOC. */
DECL|macro|MAX_TRACKS
mdefine_line|#define MAX_TRACKS 99
DECL|struct|atapi_toc_header
r_struct
id|atapi_toc_header
(brace
DECL|member|toc_length
r_int
r_int
id|toc_length
suffix:semicolon
DECL|member|first_track
id|byte
id|first_track
suffix:semicolon
DECL|member|last_track
id|byte
id|last_track
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|atapi_toc_entry
r_struct
id|atapi_toc_entry
(brace
DECL|member|reserved1
id|byte
id|reserved1
suffix:semicolon
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|adr
id|__u8
id|adr
suffix:colon
l_int|4
suffix:semicolon
DECL|member|control
id|__u8
id|control
suffix:colon
l_int|4
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|control
id|__u8
id|control
suffix:colon
l_int|4
suffix:semicolon
DECL|member|adr
id|__u8
id|adr
suffix:colon
l_int|4
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|track
id|byte
id|track
suffix:semicolon
DECL|member|reserved2
id|byte
id|reserved2
suffix:semicolon
r_union
(brace
DECL|member|lba
r_int
id|lba
suffix:semicolon
DECL|member|msf
r_struct
id|atapi_msf
id|msf
suffix:semicolon
DECL|member|addr
)brace
id|addr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|atapi_toc
r_struct
id|atapi_toc
(brace
DECL|member|last_session_lba
r_int
id|last_session_lba
suffix:semicolon
DECL|member|xa_flag
r_int
id|xa_flag
suffix:semicolon
DECL|member|capacity
r_int
r_int
id|capacity
suffix:semicolon
DECL|member|hdr
r_struct
id|atapi_toc_header
id|hdr
suffix:semicolon
DECL|member|ent
r_struct
id|atapi_toc_entry
id|ent
(braket
id|MAX_TRACKS
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* One extra for the leadout. */
)brace
suffix:semicolon
multiline_comment|/* This structure is annoyingly close to, but not identical with,&n;   the cdrom_subchnl structure from cdrom.h. */
DECL|struct|atapi_cdrom_subchnl
r_struct
id|atapi_cdrom_subchnl
(brace
DECL|member|acdsc_reserved
id|u_char
id|acdsc_reserved
suffix:semicolon
DECL|member|acdsc_audiostatus
id|u_char
id|acdsc_audiostatus
suffix:semicolon
DECL|member|acdsc_length
id|u_short
id|acdsc_length
suffix:semicolon
DECL|member|acdsc_format
id|u_char
id|acdsc_format
suffix:semicolon
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|acdsc_ctrl
id|u_char
id|acdsc_ctrl
suffix:colon
l_int|4
suffix:semicolon
DECL|member|acdsc_adr
id|u_char
id|acdsc_adr
suffix:colon
l_int|4
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|acdsc_adr
id|u_char
id|acdsc_adr
suffix:colon
l_int|4
suffix:semicolon
DECL|member|acdsc_ctrl
id|u_char
id|acdsc_ctrl
suffix:colon
l_int|4
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|acdsc_trk
id|u_char
id|acdsc_trk
suffix:semicolon
DECL|member|acdsc_ind
id|u_char
id|acdsc_ind
suffix:semicolon
r_union
(brace
DECL|member|msf
r_struct
id|atapi_msf
id|msf
suffix:semicolon
DECL|member|lba
r_int
id|lba
suffix:semicolon
DECL|member|acdsc_absaddr
)brace
id|acdsc_absaddr
suffix:semicolon
r_union
(brace
DECL|member|msf
r_struct
id|atapi_msf
id|msf
suffix:semicolon
DECL|member|lba
r_int
id|lba
suffix:semicolon
DECL|member|acdsc_reladdr
)brace
id|acdsc_reladdr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* This should probably go into cdrom.h along with the other&n; * generic stuff now in the Mt. Fuji spec.&n; */
DECL|struct|atapi_capabilities_page
r_struct
id|atapi_capabilities_page
(brace
DECL|member|header
r_struct
id|mode_page_header
id|header
suffix:semicolon
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|parameters_saveable
id|__u8
id|parameters_saveable
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved1
id|__u8
id|reserved1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|page_code
id|__u8
id|page_code
suffix:colon
l_int|6
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|page_code
id|__u8
id|page_code
suffix:colon
l_int|6
suffix:semicolon
DECL|member|reserved1
id|__u8
id|reserved1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|parameters_saveable
id|__u8
id|parameters_saveable
suffix:colon
l_int|1
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|page_length
id|byte
id|page_length
suffix:semicolon
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|reserved2
id|__u8
id|reserved2
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Drive supports reading of DVD-RAM discs */
DECL|member|dvd_ram_read
id|__u8
id|dvd_ram_read
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive supports reading of DVD-R discs */
DECL|member|dvd_r_read
id|__u8
id|dvd_r_read
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive supports reading of DVD-ROM discs */
DECL|member|dvd_rom
id|__u8
id|dvd_rom
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive supports reading CD-R discs with addressing method 2 */
DECL|member|method2
id|__u8
id|method2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved in 1.2 */
multiline_comment|/* Drive can read from CD-R/W (CD-E) discs (orange book, part III) */
DECL|member|cd_rw_read
id|__u8
id|cd_rw_read
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved in 1.2 */
multiline_comment|/* Drive supports read from CD-R discs (orange book, part II) */
DECL|member|cd_r_read
id|__u8
id|cd_r_read
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved in 1.2 */
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
multiline_comment|/* Drive supports read from CD-R discs (orange book, part II) */
DECL|member|cd_r_read
id|__u8
id|cd_r_read
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved in 1.2 */
multiline_comment|/* Drive can read from CD-R/W (CD-E) discs (orange book, part III) */
DECL|member|cd_rw_read
id|__u8
id|cd_rw_read
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved in 1.2 */
multiline_comment|/* Drive supports reading CD-R discs with addressing method 2 */
DECL|member|method2
id|__u8
id|method2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive supports reading of DVD-ROM discs */
DECL|member|dvd_rom
id|__u8
id|dvd_rom
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive supports reading of DVD-R discs */
DECL|member|dvd_r_read
id|__u8
id|dvd_r_read
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive supports reading of DVD-RAM discs */
DECL|member|dvd_ram_read
id|__u8
id|dvd_ram_read
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved2
id|__u8
id|reserved2
suffix:colon
l_int|2
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|reserved3
id|__u8
id|reserved3
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Drive can write DVD-RAM discs */
DECL|member|dvd_ram_write
id|__u8
id|dvd_ram_write
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can write DVD-R discs */
DECL|member|dvd_r_write
id|__u8
id|dvd_r_write
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved3a
id|__u8
id|reserved3a
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can fake writes */
DECL|member|test_write
id|__u8
id|test_write
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can write to CD-R/W (CD-E) discs (orange book, part III) */
DECL|member|cd_rw_write
id|__u8
id|cd_rw_write
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved in 1.2 */
multiline_comment|/* Drive supports write to CD-R discs (orange book, part II) */
DECL|member|cd_r_write
id|__u8
id|cd_r_write
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved in 1.2 */
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
multiline_comment|/* Drive can write to CD-R discs (orange book, part II) */
DECL|member|cd_r_write
id|__u8
id|cd_r_write
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved in 1.2 */
multiline_comment|/* Drive can write to CD-R/W (CD-E) discs (orange book, part III) */
DECL|member|cd_rw_write
id|__u8
id|cd_rw_write
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved in 1.2 */
multiline_comment|/* Drive can fake writes */
DECL|member|test_write
id|__u8
id|test_write
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved3a
id|__u8
id|reserved3a
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can write DVD-R discs */
DECL|member|dvd_r_write
id|__u8
id|dvd_r_write
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can write DVD-RAM discs */
DECL|member|dvd_ram_write
id|__u8
id|dvd_ram_write
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved3
id|__u8
id|reserved3
suffix:colon
l_int|2
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|reserved4
id|__u8
id|reserved4
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can read multisession discs. */
DECL|member|multisession
id|__u8
id|multisession
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can read mode 2, form 2 data. */
DECL|member|mode2_form2
id|__u8
id|mode2_form2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can read mode 2, form 1 (XA) data. */
DECL|member|mode2_form1
id|__u8
id|mode2_form1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive supports digital output on port 2. */
DECL|member|digport2
id|__u8
id|digport2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive supports digital output on port 1. */
DECL|member|digport1
id|__u8
id|digport1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can deliver a composite audio/video data stream. */
DECL|member|composite
id|__u8
id|composite
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive supports audio play operations. */
DECL|member|audio_play
id|__u8
id|audio_play
suffix:colon
l_int|1
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
multiline_comment|/* Drive supports audio play operations. */
DECL|member|audio_play
id|__u8
id|audio_play
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can deliver a composite audio/video data stream. */
DECL|member|composite
id|__u8
id|composite
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive supports digital output on port 1. */
DECL|member|digport1
id|__u8
id|digport1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive supports digital output on port 2. */
DECL|member|digport2
id|__u8
id|digport2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can read mode 2, form 1 (XA) data. */
DECL|member|mode2_form1
id|__u8
id|mode2_form1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can read mode 2, form 2 data. */
DECL|member|mode2_form2
id|__u8
id|mode2_form2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can read multisession discs. */
DECL|member|multisession
id|__u8
id|multisession
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved4
id|__u8
id|reserved4
suffix:colon
l_int|1
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|reserved5
id|__u8
id|reserved5
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can return Media Catalog Number (UPC) info. */
DECL|member|upc
id|__u8
id|upc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can return International Standard Recording Code info. */
DECL|member|isrc
id|__u8
id|isrc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive supports C2 error pointers. */
DECL|member|c2_pointers
id|__u8
id|c2_pointers
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* R-W data will be returned deinterleaved and error corrected. */
DECL|member|rw_corr
id|__u8
id|rw_corr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Subchannel reads can return combined R-W information. */
DECL|member|rw_supported
id|__u8
id|rw_supported
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can continue a read cdda operation from a loss of streaming.*/
DECL|member|cdda_accurate
id|__u8
id|cdda_accurate
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can read Red Book audio data. */
DECL|member|cdda
id|__u8
id|cdda
suffix:colon
l_int|1
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
multiline_comment|/* Drive can read Red Book audio data. */
DECL|member|cdda
id|__u8
id|cdda
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can continue a read cdda operation from a loss of streaming.*/
DECL|member|cdda_accurate
id|__u8
id|cdda_accurate
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Subchannel reads can return combined R-W information. */
DECL|member|rw_supported
id|__u8
id|rw_supported
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* R-W data will be returned deinterleaved and error corrected. */
DECL|member|rw_corr
id|__u8
id|rw_corr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive supports C2 error pointers. */
DECL|member|c2_pointers
id|__u8
id|c2_pointers
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can return International Standard Recording Code info. */
DECL|member|isrc
id|__u8
id|isrc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can return Media Catalog Number (UPC) info. */
DECL|member|upc
id|__u8
id|upc
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved5
id|__u8
id|reserved5
suffix:colon
l_int|1
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
multiline_comment|/* Drive mechanism types. */
DECL|member|mechtype
id|mechtype_t
id|mechtype
suffix:colon
l_int|3
suffix:semicolon
DECL|member|reserved6
id|__u8
id|reserved6
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can eject a disc or changer cartridge. */
DECL|member|eject
id|__u8
id|eject
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* State of prevent/allow jumper. */
DECL|member|prevent_jumper
id|__u8
id|prevent_jumper
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Present state of door lock. */
DECL|member|lock_state
id|__u8
id|lock_state
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can lock the door. */
DECL|member|lock
id|__u8
id|lock
suffix:colon
l_int|1
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
multiline_comment|/* Drive can lock the door. */
DECL|member|lock
id|__u8
id|lock
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Present state of door lock. */
DECL|member|lock_state
id|__u8
id|lock_state
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* State of prevent/allow jumper. */
DECL|member|prevent_jumper
id|__u8
id|prevent_jumper
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can eject a disc or changer cartridge. */
DECL|member|eject
id|__u8
id|eject
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved6
id|__u8
id|reserved6
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive mechanism types. */
DECL|member|mechtype
id|mechtype_t
id|mechtype
suffix:colon
l_int|3
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|reserved7
id|__u8
id|reserved7
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* Drive supports software slot selection. */
DECL|member|sss
id|__u8
id|sss
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved in 1.2 */
multiline_comment|/* Changer can report exact contents of slots. */
DECL|member|disc_present
id|__u8
id|disc_present
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved in 1.2 */
multiline_comment|/* Audio for each channel can be muted independently. */
DECL|member|separate_mute
id|__u8
id|separate_mute
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Audio level for each channel can be controlled independently. */
DECL|member|separate_volume
id|__u8
id|separate_volume
suffix:colon
l_int|1
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
multiline_comment|/* Audio level for each channel can be controlled independently. */
DECL|member|separate_volume
id|__u8
id|separate_volume
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Audio for each channel can be muted independently. */
DECL|member|separate_mute
id|__u8
id|separate_mute
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Changer can report exact contents of slots. */
DECL|member|disc_present
id|__u8
id|disc_present
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved in 1.2 */
multiline_comment|/* Drive supports software slot selection. */
DECL|member|sss
id|__u8
id|sss
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved in 1.2 */
DECL|member|reserved7
id|__u8
id|reserved7
suffix:colon
l_int|4
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
multiline_comment|/* Note: the following four fields are returned in big-endian form. */
multiline_comment|/* Maximum speed (in kB/s). */
DECL|member|maxspeed
r_int
r_int
id|maxspeed
suffix:semicolon
multiline_comment|/* Number of discrete volume levels. */
DECL|member|n_vol_levels
r_int
r_int
id|n_vol_levels
suffix:semicolon
multiline_comment|/* Size of cache in drive, in kB. */
DECL|member|buffer_size
r_int
r_int
id|buffer_size
suffix:semicolon
multiline_comment|/* Current speed (in kB/s). */
DECL|member|curspeed
r_int
r_int
id|curspeed
suffix:semicolon
DECL|member|pad
r_char
id|pad
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|atapi_mechstat_header
r_struct
id|atapi_mechstat_header
(brace
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|fault
id|__u8
id|fault
suffix:colon
l_int|1
suffix:semicolon
DECL|member|changer_state
id|__u8
id|changer_state
suffix:colon
l_int|2
suffix:semicolon
DECL|member|curslot
id|__u8
id|curslot
suffix:colon
l_int|5
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
id|__u8
id|curslot
suffix:colon
l_int|5
suffix:semicolon
id|__u8
id|changer_state
suffix:colon
l_int|2
suffix:semicolon
id|__u8
id|fault
suffix:colon
l_int|1
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|mech_state
id|__u8
id|mech_state
suffix:colon
l_int|3
suffix:semicolon
DECL|member|door_open
id|__u8
id|door_open
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved1
id|__u8
id|reserved1
suffix:colon
l_int|4
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|reserved1
id|__u8
id|reserved1
suffix:colon
l_int|4
suffix:semicolon
DECL|member|door_open
id|__u8
id|door_open
suffix:colon
l_int|1
suffix:semicolon
DECL|member|mech_state
id|__u8
id|mech_state
suffix:colon
l_int|3
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|curlba
id|byte
id|curlba
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|nslots
id|byte
id|nslots
suffix:semicolon
DECL|member|slot_tablelen
id|__u16
id|slot_tablelen
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|atapi_slot
r_struct
id|atapi_slot
(brace
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|disc_present
id|__u8
id|disc_present
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved1
id|__u8
id|reserved1
suffix:colon
l_int|6
suffix:semicolon
DECL|member|change
id|__u8
id|change
suffix:colon
l_int|1
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
id|__u8
id|change
suffix:colon
l_int|1
suffix:semicolon
id|__u8
id|reserved1
suffix:colon
l_int|6
suffix:semicolon
id|__u8
id|disc_present
suffix:colon
l_int|1
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|reserved2
id|byte
id|reserved2
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|atapi_changer_info
r_struct
id|atapi_changer_info
(brace
DECL|member|hdr
r_struct
id|atapi_mechstat_header
id|hdr
suffix:semicolon
DECL|member|slots
r_struct
id|atapi_slot
id|slots
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Extra per-device info for cdrom drives. */
DECL|struct|cdrom_info
r_struct
id|cdrom_info
(brace
multiline_comment|/* Buffer for table of contents.  NULL if we haven&squot;t allocated&n;&t;   a TOC buffer for this device yet. */
DECL|member|toc
r_struct
id|atapi_toc
op_star
id|toc
suffix:semicolon
DECL|member|sector_buffered
r_int
r_int
id|sector_buffered
suffix:semicolon
DECL|member|nsectors_buffered
r_int
r_int
id|nsectors_buffered
suffix:semicolon
DECL|member|buffer
r_int
r_char
op_star
id|buffer
suffix:semicolon
multiline_comment|/* The result of the last successful request sense command&n;&t;   on this device. */
DECL|member|sense_data
r_struct
id|request_sense
id|sense_data
suffix:semicolon
DECL|member|request_sense_request
r_struct
id|request
id|request_sense_request
suffix:semicolon
DECL|member|request_sense_pc
r_struct
id|packet_command
id|request_sense_pc
suffix:semicolon
DECL|member|dma
r_int
id|dma
suffix:semicolon
DECL|member|cmd
r_int
id|cmd
suffix:semicolon
DECL|member|last_block
r_int
r_int
id|last_block
suffix:semicolon
DECL|member|start_seek
r_int
r_int
id|start_seek
suffix:semicolon
multiline_comment|/* Buffer to hold mechanism status and changer slot table. */
DECL|member|changer_info
r_struct
id|atapi_changer_info
op_star
id|changer_info
suffix:semicolon
DECL|member|config_flags
r_struct
id|ide_cd_config_flags
id|config_flags
suffix:semicolon
DECL|member|state_flags
r_struct
id|ide_cd_state_flags
id|state_flags
suffix:semicolon
multiline_comment|/* Per-device info needed by cdrom.c generic driver. */
DECL|member|devinfo
r_struct
id|cdrom_device_info
id|devinfo
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/****************************************************************************&n; * Descriptions of ATAPI error codes.&n; */
DECL|macro|ARY_LEN
mdefine_line|#define ARY_LEN(a) ((sizeof(a) / sizeof(a[0])))
multiline_comment|/* This stuff should be in cdrom.h, since it is now generic... */
multiline_comment|/* ATAPI sense keys (from table 140 of ATAPI 2.6) */
DECL|macro|NO_SENSE
mdefine_line|#define NO_SENSE                0x00
DECL|macro|RECOVERED_ERROR
mdefine_line|#define RECOVERED_ERROR         0x01
DECL|macro|NOT_READY
mdefine_line|#define NOT_READY               0x02
DECL|macro|MEDIUM_ERROR
mdefine_line|#define MEDIUM_ERROR            0x03
DECL|macro|HARDWARE_ERROR
mdefine_line|#define HARDWARE_ERROR          0x04
DECL|macro|ILLEGAL_REQUEST
mdefine_line|#define ILLEGAL_REQUEST         0x05
DECL|macro|UNIT_ATTENTION
mdefine_line|#define UNIT_ATTENTION          0x06
DECL|macro|DATA_PROTECT
mdefine_line|#define DATA_PROTECT            0x07
DECL|macro|ABORTED_COMMAND
mdefine_line|#define ABORTED_COMMAND         0x0b
DECL|macro|MISCOMPARE
mdefine_line|#define MISCOMPARE              0x0e
multiline_comment|/* This stuff should be in cdrom.h, since it is now generic... */
macro_line|#if VERBOSE_IDE_CD_ERRORS
multiline_comment|/* The generic packet command opcodes for CD/DVD Logical Units,&n; * From Table 57 of the SFF8090 Ver. 3 (Mt. Fuji) draft standard. */
r_const
r_struct
(brace
DECL|member|packet_command
r_int
r_int
id|packet_command
suffix:semicolon
DECL|member|text
r_const
r_char
op_star
r_const
id|text
suffix:semicolon
DECL|variable|packet_command_texts
)brace
id|packet_command_texts
(braket
)braket
op_assign
(brace
(brace
id|GPCMD_TEST_UNIT_READY
comma
l_string|&quot;Test Unit Ready&quot;
)brace
comma
(brace
id|GPCMD_REQUEST_SENSE
comma
l_string|&quot;Request Sense&quot;
)brace
comma
(brace
id|GPCMD_FORMAT_UNIT
comma
l_string|&quot;Format Unit&quot;
)brace
comma
(brace
id|GPCMD_INQUIRY
comma
l_string|&quot;Inquiry&quot;
)brace
comma
(brace
id|GPCMD_START_STOP_UNIT
comma
l_string|&quot;Start/Stop Unit&quot;
)brace
comma
(brace
id|GPCMD_PREVENT_ALLOW_MEDIUM_REMOVAL
comma
l_string|&quot;Prevent/Allow Medium Removal&quot;
)brace
comma
(brace
id|GPCMD_READ_FORMAT_CAPACITIES
comma
l_string|&quot;Read Format Capacities&quot;
)brace
comma
(brace
id|GPCMD_READ_CDVD_CAPACITY
comma
l_string|&quot;Read Cd/Dvd Capacity&quot;
)brace
comma
(brace
id|GPCMD_READ_10
comma
l_string|&quot;Read 10&quot;
)brace
comma
(brace
id|GPCMD_WRITE_10
comma
l_string|&quot;Write 10&quot;
)brace
comma
(brace
id|GPCMD_SEEK
comma
l_string|&quot;Seek&quot;
)brace
comma
(brace
id|GPCMD_WRITE_AND_VERIFY_10
comma
l_string|&quot;Write and Verify 10&quot;
)brace
comma
(brace
id|GPCMD_VERIFY_10
comma
l_string|&quot;Verify 10&quot;
)brace
comma
(brace
id|GPCMD_FLUSH_CACHE
comma
l_string|&quot;Flush Cache&quot;
)brace
comma
(brace
id|GPCMD_READ_SUBCHANNEL
comma
l_string|&quot;Read Subchannel&quot;
)brace
comma
(brace
id|GPCMD_READ_TOC_PMA_ATIP
comma
l_string|&quot;Read Table of Contents&quot;
)brace
comma
(brace
id|GPCMD_READ_HEADER
comma
l_string|&quot;Read Header&quot;
)brace
comma
(brace
id|GPCMD_PLAY_AUDIO_10
comma
l_string|&quot;Play Audio 10&quot;
)brace
comma
(brace
id|GPCMD_GET_CONFIGURATION
comma
l_string|&quot;Get Configuration&quot;
)brace
comma
(brace
id|GPCMD_PLAY_AUDIO_MSF
comma
l_string|&quot;Play Audio MSF&quot;
)brace
comma
(brace
id|GPCMD_PLAYAUDIO_TI
comma
l_string|&quot;Play Audio TrackIndex&quot;
)brace
comma
(brace
id|GPCMD_GET_EVENT_STATUS_NOTIFICATION
comma
l_string|&quot;Get Event Status Notification&quot;
)brace
comma
(brace
id|GPCMD_PAUSE_RESUME
comma
l_string|&quot;Pause/Resume&quot;
)brace
comma
(brace
id|GPCMD_STOP_PLAY_SCAN
comma
l_string|&quot;Stop Play/Scan&quot;
)brace
comma
(brace
id|GPCMD_READ_DISC_INFO
comma
l_string|&quot;Read Disc Info&quot;
)brace
comma
(brace
id|GPCMD_READ_TRACK_RZONE_INFO
comma
l_string|&quot;Read Track Rzone Info&quot;
)brace
comma
(brace
id|GPCMD_RESERVE_RZONE_TRACK
comma
l_string|&quot;Reserve Rzone Track&quot;
)brace
comma
(brace
id|GPCMD_SEND_OPC
comma
l_string|&quot;Send OPC&quot;
)brace
comma
(brace
id|GPCMD_MODE_SELECT_10
comma
l_string|&quot;Mode Select 10&quot;
)brace
comma
(brace
id|GPCMD_REPAIR_RZONE_TRACK
comma
l_string|&quot;Repair Rzone Track&quot;
)brace
comma
(brace
id|GPCMD_MODE_SENSE_10
comma
l_string|&quot;Mode Sense 10&quot;
)brace
comma
(brace
id|GPCMD_CLOSE_TRACK
comma
l_string|&quot;Close Track&quot;
)brace
comma
(brace
id|GPCMD_BLANK
comma
l_string|&quot;Blank&quot;
)brace
comma
(brace
id|GPCMD_SEND_EVENT
comma
l_string|&quot;Send Event&quot;
)brace
comma
(brace
id|GPCMD_SEND_KEY
comma
l_string|&quot;Send Key&quot;
)brace
comma
(brace
id|GPCMD_REPORT_KEY
comma
l_string|&quot;Report Key&quot;
)brace
comma
(brace
id|GPCMD_LOAD_UNLOAD
comma
l_string|&quot;Load/Unload&quot;
)brace
comma
(brace
id|GPCMD_SET_READ_AHEAD
comma
l_string|&quot;Set Read-ahead&quot;
)brace
comma
(brace
id|GPCMD_READ_12
comma
l_string|&quot;Read 12&quot;
)brace
comma
(brace
id|GPCMD_GET_PERFORMANCE
comma
l_string|&quot;Get Performance&quot;
)brace
comma
(brace
id|GPCMD_SEND_DVD_STRUCTURE
comma
l_string|&quot;Send DVD Structure&quot;
)brace
comma
(brace
id|GPCMD_READ_DVD_STRUCTURE
comma
l_string|&quot;Read DVD Structure&quot;
)brace
comma
(brace
id|GPCMD_SET_STREAMING
comma
l_string|&quot;Set Streaming&quot;
)brace
comma
(brace
id|GPCMD_READ_CD_MSF
comma
l_string|&quot;Read CD MSF&quot;
)brace
comma
(brace
id|GPCMD_SCAN
comma
l_string|&quot;Scan&quot;
)brace
comma
(brace
id|GPCMD_SET_SPEED
comma
l_string|&quot;Set Speed&quot;
)brace
comma
(brace
id|GPCMD_PLAY_CD
comma
l_string|&quot;Play CD&quot;
)brace
comma
(brace
id|GPCMD_MECHANISM_STATUS
comma
l_string|&quot;Mechanism Status&quot;
)brace
comma
(brace
id|GPCMD_READ_CD
comma
l_string|&quot;Read CD&quot;
)brace
comma
)brace
suffix:semicolon
multiline_comment|/* From Table 303 of the SFF8090 Ver. 3 (Mt. Fuji) draft standard. */
DECL|variable|sense_key_texts
r_const
r_char
op_star
r_const
id|sense_key_texts
(braket
l_int|16
)braket
op_assign
(brace
l_string|&quot;No sense data&quot;
comma
l_string|&quot;Recovered error&quot;
comma
l_string|&quot;Not ready&quot;
comma
l_string|&quot;Medium error&quot;
comma
l_string|&quot;Hardware error&quot;
comma
l_string|&quot;Illegal request&quot;
comma
l_string|&quot;Unit attention&quot;
comma
l_string|&quot;Data protect&quot;
comma
l_string|&quot;(reserved)&quot;
comma
l_string|&quot;(reserved)&quot;
comma
l_string|&quot;(reserved)&quot;
comma
l_string|&quot;Aborted command&quot;
comma
l_string|&quot;(reserved)&quot;
comma
l_string|&quot;(reserved)&quot;
comma
l_string|&quot;Miscompare&quot;
comma
l_string|&quot;(reserved)&quot;
comma
)brace
suffix:semicolon
multiline_comment|/* From Table 304 of the SFF8090 Ver. 3 (Mt. Fuji) draft standard. */
r_const
r_struct
(brace
DECL|member|asc_ascq
r_int
r_int
id|asc_ascq
suffix:semicolon
DECL|member|text
r_const
r_char
op_star
r_const
id|text
suffix:semicolon
DECL|variable|sense_data_texts
)brace
id|sense_data_texts
(braket
)braket
op_assign
(brace
(brace
l_int|0x000000
comma
l_string|&quot;No additional sense information&quot;
)brace
comma
(brace
l_int|0x000011
comma
l_string|&quot;Play operation in progress&quot;
)brace
comma
(brace
l_int|0x000012
comma
l_string|&quot;Play operation paused&quot;
)brace
comma
(brace
l_int|0x000013
comma
l_string|&quot;Play operation successfully completed&quot;
)brace
comma
(brace
l_int|0x000014
comma
l_string|&quot;Play operation stopped due to error&quot;
)brace
comma
(brace
l_int|0x000015
comma
l_string|&quot;No current audio status to return&quot;
)brace
comma
(brace
l_int|0x010c0a
comma
l_string|&quot;Write error - padding blocks added&quot;
)brace
comma
(brace
l_int|0x011700
comma
l_string|&quot;Recovered data with no error correction applied&quot;
)brace
comma
(brace
l_int|0x011701
comma
l_string|&quot;Recovered data with retries&quot;
)brace
comma
(brace
l_int|0x011702
comma
l_string|&quot;Recovered data with positive head offset&quot;
)brace
comma
(brace
l_int|0x011703
comma
l_string|&quot;Recovered data with negative head offset&quot;
)brace
comma
(brace
l_int|0x011704
comma
l_string|&quot;Recovered data with retries and/or CIRC applied&quot;
)brace
comma
(brace
l_int|0x011705
comma
l_string|&quot;Recovered data using previous sector ID&quot;
)brace
comma
(brace
l_int|0x011800
comma
l_string|&quot;Recovered data with error correction applied&quot;
)brace
comma
(brace
l_int|0x011801
comma
l_string|&quot;Recovered data with error correction and retries applied&quot;
)brace
comma
(brace
l_int|0x011802
comma
l_string|&quot;Recovered data - the data was auto-reallocated&quot;
)brace
comma
(brace
l_int|0x011803
comma
l_string|&quot;Recovered data with CIRC&quot;
)brace
comma
(brace
l_int|0x011804
comma
l_string|&quot;Recovered data with L-EC&quot;
)brace
comma
(brace
l_int|0x015d00
comma
l_string|&quot;Failure prediction threshold exceeded - Predicted logical unit failure&quot;
)brace
comma
(brace
l_int|0x015d01
comma
l_string|&quot;Failure prediction threshold exceeded - Predicted media failure&quot;
)brace
comma
(brace
l_int|0x015dff
comma
l_string|&quot;Failure prediction threshold exceeded - False&quot;
)brace
comma
(brace
l_int|0x017301
comma
l_string|&quot;Power calibration area almost full&quot;
)brace
comma
(brace
l_int|0x020400
comma
l_string|&quot;Logical unit not ready - cause not reportable&quot;
)brace
comma
multiline_comment|/* Following is misspelled in ATAPI 2.6, _and_ in Mt. Fuji */
(brace
l_int|0x020401
comma
l_string|&quot;Logical unit not ready - in progress [sic] of becoming ready&quot;
)brace
comma
(brace
l_int|0x020402
comma
l_string|&quot;Logical unit not ready - initializing command required&quot;
)brace
comma
(brace
l_int|0x020403
comma
l_string|&quot;Logical unit not ready - manual intervention required&quot;
)brace
comma
(brace
l_int|0x020404
comma
l_string|&quot;Logical unit not ready - format in progress&quot;
)brace
comma
(brace
l_int|0x020407
comma
l_string|&quot;Logical unit not ready - operation in progress&quot;
)brace
comma
(brace
l_int|0x020408
comma
l_string|&quot;Logical unit not ready - long write in progress&quot;
)brace
comma
(brace
l_int|0x020600
comma
l_string|&quot;No reference position found (media may be upside down)&quot;
)brace
comma
(brace
l_int|0x023000
comma
l_string|&quot;Incompatible medium installed&quot;
)brace
comma
(brace
l_int|0x023a00
comma
l_string|&quot;Medium not present&quot;
)brace
comma
(brace
l_int|0x025300
comma
l_string|&quot;Media load or eject failed&quot;
)brace
comma
(brace
l_int|0x025700
comma
l_string|&quot;Unable to recover table of contents&quot;
)brace
comma
(brace
l_int|0x030300
comma
l_string|&quot;Peripheral device write fault&quot;
)brace
comma
(brace
l_int|0x030301
comma
l_string|&quot;No write current&quot;
)brace
comma
(brace
l_int|0x030302
comma
l_string|&quot;Excessive write errors&quot;
)brace
comma
(brace
l_int|0x030c00
comma
l_string|&quot;Write error&quot;
)brace
comma
(brace
l_int|0x030c01
comma
l_string|&quot;Write error - Recovered with auto reallocation&quot;
)brace
comma
(brace
l_int|0x030c02
comma
l_string|&quot;Write error - auto reallocation failed&quot;
)brace
comma
(brace
l_int|0x030c03
comma
l_string|&quot;Write error - recommend reassignment&quot;
)brace
comma
(brace
l_int|0x030c04
comma
l_string|&quot;Compression check miscompare error&quot;
)brace
comma
(brace
l_int|0x030c05
comma
l_string|&quot;Data expansion occurred during compress&quot;
)brace
comma
(brace
l_int|0x030c06
comma
l_string|&quot;Block not compressible&quot;
)brace
comma
(brace
l_int|0x030c07
comma
l_string|&quot;Write error - recovery needed&quot;
)brace
comma
(brace
l_int|0x030c08
comma
l_string|&quot;Write error - recovery failed&quot;
)brace
comma
(brace
l_int|0x030c09
comma
l_string|&quot;Write error - loss of streaming&quot;
)brace
comma
(brace
l_int|0x031100
comma
l_string|&quot;Unrecovered read error&quot;
)brace
comma
(brace
l_int|0x031106
comma
l_string|&quot;CIRC unrecovered error&quot;
)brace
comma
(brace
l_int|0x033101
comma
l_string|&quot;Format command failed&quot;
)brace
comma
(brace
l_int|0x033200
comma
l_string|&quot;No defect spare location available&quot;
)brace
comma
(brace
l_int|0x033201
comma
l_string|&quot;Defect list update failure&quot;
)brace
comma
(brace
l_int|0x035100
comma
l_string|&quot;Erase failure&quot;
)brace
comma
(brace
l_int|0x037200
comma
l_string|&quot;Session fixation error&quot;
)brace
comma
(brace
l_int|0x037201
comma
l_string|&quot;Session fixation error writin lead-in&quot;
)brace
comma
(brace
l_int|0x037202
comma
l_string|&quot;Session fixation error writin lead-out&quot;
)brace
comma
(brace
l_int|0x037300
comma
l_string|&quot;CD control error&quot;
)brace
comma
(brace
l_int|0x037302
comma
l_string|&quot;Power calibration area is full&quot;
)brace
comma
(brace
l_int|0x037303
comma
l_string|&quot;Power calibration area error&quot;
)brace
comma
(brace
l_int|0x037304
comma
l_string|&quot;Program memory area / RMA update failure&quot;
)brace
comma
(brace
l_int|0x037305
comma
l_string|&quot;Program memory area / RMA is full&quot;
)brace
comma
(brace
l_int|0x037306
comma
l_string|&quot;Program memory area / RMA is (almost) full&quot;
)brace
comma
(brace
l_int|0x040200
comma
l_string|&quot;No seek complete&quot;
)brace
comma
(brace
l_int|0x040300
comma
l_string|&quot;Write fault&quot;
)brace
comma
(brace
l_int|0x040900
comma
l_string|&quot;Track following error&quot;
)brace
comma
(brace
l_int|0x040901
comma
l_string|&quot;Tracking servo failure&quot;
)brace
comma
(brace
l_int|0x040902
comma
l_string|&quot;Focus servo failure&quot;
)brace
comma
(brace
l_int|0x040903
comma
l_string|&quot;Spindle servo failure&quot;
)brace
comma
(brace
l_int|0x041500
comma
l_string|&quot;Random positioning error&quot;
)brace
comma
(brace
l_int|0x041501
comma
l_string|&quot;Mechanical positioning or changer error&quot;
)brace
comma
(brace
l_int|0x041502
comma
l_string|&quot;Positioning error detected by read of medium&quot;
)brace
comma
(brace
l_int|0x043c00
comma
l_string|&quot;Mechanical positioning or changer error&quot;
)brace
comma
(brace
l_int|0x044000
comma
l_string|&quot;Diagnostic failure on component (ASCQ)&quot;
)brace
comma
(brace
l_int|0x044400
comma
l_string|&quot;Internal CD/DVD logical unit failure&quot;
)brace
comma
(brace
l_int|0x04b600
comma
l_string|&quot;Media load mechanism failed&quot;
)brace
comma
(brace
l_int|0x051a00
comma
l_string|&quot;Parameter list length error&quot;
)brace
comma
(brace
l_int|0x052000
comma
l_string|&quot;Invalid command operation code&quot;
)brace
comma
(brace
l_int|0x052100
comma
l_string|&quot;Logical block address out of range&quot;
)brace
comma
(brace
l_int|0x052102
comma
l_string|&quot;Invalid address for write&quot;
)brace
comma
(brace
l_int|0x052400
comma
l_string|&quot;Invalid field in command packet&quot;
)brace
comma
(brace
l_int|0x052600
comma
l_string|&quot;Invalid field in parameter list&quot;
)brace
comma
(brace
l_int|0x052601
comma
l_string|&quot;Parameter not supported&quot;
)brace
comma
(brace
l_int|0x052602
comma
l_string|&quot;Parameter value invalid&quot;
)brace
comma
(brace
l_int|0x052700
comma
l_string|&quot;Write protected media&quot;
)brace
comma
(brace
l_int|0x052c00
comma
l_string|&quot;Command sequence error&quot;
)brace
comma
(brace
l_int|0x052c03
comma
l_string|&quot;Current program area is not empty&quot;
)brace
comma
(brace
l_int|0x052c04
comma
l_string|&quot;Current program area is empty&quot;
)brace
comma
(brace
l_int|0x053001
comma
l_string|&quot;Cannot read medium - unknown format&quot;
)brace
comma
(brace
l_int|0x053002
comma
l_string|&quot;Cannot read medium - incompatible format&quot;
)brace
comma
(brace
l_int|0x053900
comma
l_string|&quot;Saving parameters not supported&quot;
)brace
comma
(brace
l_int|0x054e00
comma
l_string|&quot;Overlapped commands attempted&quot;
)brace
comma
(brace
l_int|0x055302
comma
l_string|&quot;Medium removal prevented&quot;
)brace
comma
(brace
l_int|0x055500
comma
l_string|&quot;System resource failure&quot;
)brace
comma
(brace
l_int|0x056300
comma
l_string|&quot;End of user area encountered on this track&quot;
)brace
comma
(brace
l_int|0x056400
comma
l_string|&quot;Illegal mode for this track or incompatible medium&quot;
)brace
comma
(brace
l_int|0x056f00
comma
l_string|&quot;Copy protection key exchange failure - Authentication failure&quot;
)brace
comma
(brace
l_int|0x056f01
comma
l_string|&quot;Copy protection key exchange failure - Key not present&quot;
)brace
comma
(brace
l_int|0x056f02
comma
l_string|&quot;Copy protection key exchange failure - Key not established&quot;
)brace
comma
(brace
l_int|0x056f03
comma
l_string|&quot;Read of scrambled sector without authentication&quot;
)brace
comma
(brace
l_int|0x056f04
comma
l_string|&quot;Media region code is mismatched to logical unit&quot;
)brace
comma
(brace
l_int|0x056f05
comma
l_string|&quot;Drive region must be permanent / region reset count error&quot;
)brace
comma
(brace
l_int|0x057203
comma
l_string|&quot;Session fixation error - incomplete track in session&quot;
)brace
comma
(brace
l_int|0x057204
comma
l_string|&quot;Empty or partially written reserved track&quot;
)brace
comma
(brace
l_int|0x057205
comma
l_string|&quot;No more RZONE reservations are allowed&quot;
)brace
comma
(brace
l_int|0x05bf00
comma
l_string|&quot;Loss of streaming&quot;
)brace
comma
(brace
l_int|0x062800
comma
l_string|&quot;Not ready to ready transition, medium may have changed&quot;
)brace
comma
(brace
l_int|0x062900
comma
l_string|&quot;Power on, reset or hardware reset occurred&quot;
)brace
comma
(brace
l_int|0x062a00
comma
l_string|&quot;Parameters changed&quot;
)brace
comma
(brace
l_int|0x062a01
comma
l_string|&quot;Mode parameters changed&quot;
)brace
comma
(brace
l_int|0x062e00
comma
l_string|&quot;Insufficient time for operation&quot;
)brace
comma
(brace
l_int|0x063f00
comma
l_string|&quot;Logical unit operating conditions have changed&quot;
)brace
comma
(brace
l_int|0x063f01
comma
l_string|&quot;Microcode has been changed&quot;
)brace
comma
(brace
l_int|0x065a00
comma
l_string|&quot;Operator request or state change input (unspecified)&quot;
)brace
comma
(brace
l_int|0x065a01
comma
l_string|&quot;Operator medium removal request&quot;
)brace
comma
(brace
l_int|0x0bb900
comma
l_string|&quot;Play operation aborted&quot;
)brace
comma
multiline_comment|/* Here we use 0xff for the key (not a valid key) to signify&n;&t; * that these can have _any_ key value associated with them... */
(brace
l_int|0xff0401
comma
l_string|&quot;Logical unit is in process of becoming ready&quot;
)brace
comma
(brace
l_int|0xff0400
comma
l_string|&quot;Logical unit not ready, cause not reportable&quot;
)brace
comma
(brace
l_int|0xff0402
comma
l_string|&quot;Logical unit not ready, initializing command required&quot;
)brace
comma
(brace
l_int|0xff0403
comma
l_string|&quot;Logical unit not ready, manual intervention required&quot;
)brace
comma
(brace
l_int|0xff0500
comma
l_string|&quot;Logical unit does not respond to selection&quot;
)brace
comma
(brace
l_int|0xff0800
comma
l_string|&quot;Logical unit communication failure&quot;
)brace
comma
(brace
l_int|0xff0802
comma
l_string|&quot;Logical unit communication parity error&quot;
)brace
comma
(brace
l_int|0xff0801
comma
l_string|&quot;Logical unit communication time-out&quot;
)brace
comma
(brace
l_int|0xff2500
comma
l_string|&quot;Logical unit not supported&quot;
)brace
comma
(brace
l_int|0xff4c00
comma
l_string|&quot;Logical unit failed self-configuration&quot;
)brace
comma
(brace
l_int|0xff3e00
comma
l_string|&quot;Logical unit has not self-configured yet&quot;
)brace
comma
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif /* _IDE_CD_H */
eof
