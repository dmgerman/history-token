macro_line|#ifndef _AMIFD_H
DECL|macro|_AMIFD_H
mdefine_line|#define _AMIFD_H
multiline_comment|/* Definitions for the Amiga floppy driver */
macro_line|#include &lt;linux/fd.h&gt;
DECL|macro|FD_MAX_UNITS
mdefine_line|#define FD_MAX_UNITS    4&t;/* Max. Number of drives */
DECL|macro|FLOPPY_MAX_SECTORS
mdefine_line|#define FLOPPY_MAX_SECTORS&t;22&t;/* Max. Number of sectors per track */
macro_line|#ifndef ASSEMBLER
DECL|struct|fd_data_type
r_struct
id|fd_data_type
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* description of data type */
DECL|member|sects
r_int
id|sects
suffix:semicolon
multiline_comment|/* sectors per track */
macro_line|#ifdef __STDC__
DECL|member|read_fkt
r_int
(paren
op_star
id|read_fkt
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|member|write_fkt
r_void
(paren
op_star
id|write_fkt
)paren
(paren
r_int
)paren
suffix:semicolon
macro_line|#else
DECL|member|read_fkt
r_int
(paren
op_star
id|read_fkt
)paren
(paren
)paren
suffix:semicolon
multiline_comment|/* read whole track */
DECL|member|write_fkt
r_void
(paren
op_star
id|write_fkt
)paren
(paren
)paren
suffix:semicolon
multiline_comment|/* write whole track */
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/*&n;** Floppy type descriptions&n;*/
DECL|struct|fd_drive_type
r_struct
id|fd_drive_type
(brace
DECL|member|code
r_int
r_int
id|code
suffix:semicolon
multiline_comment|/* code returned from drive */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* description of drive */
DECL|member|tracks
r_int
r_int
id|tracks
suffix:semicolon
multiline_comment|/* number of tracks */
DECL|member|heads
r_int
r_int
id|heads
suffix:semicolon
multiline_comment|/* number of heads */
DECL|member|read_size
r_int
r_int
id|read_size
suffix:semicolon
multiline_comment|/* raw read size for one track */
DECL|member|write_size
r_int
r_int
id|write_size
suffix:semicolon
multiline_comment|/* raw write size for one track */
DECL|member|sect_mult
r_int
r_int
id|sect_mult
suffix:semicolon
multiline_comment|/* sectors and gap multiplier (HD = 2) */
DECL|member|precomp1
r_int
r_int
id|precomp1
suffix:semicolon
multiline_comment|/* start track for precomp 1 */
DECL|member|precomp2
r_int
r_int
id|precomp2
suffix:semicolon
multiline_comment|/* start track for precomp 2 */
DECL|member|step_delay
r_int
r_int
id|step_delay
suffix:semicolon
multiline_comment|/* time (in ms) for delay after step */
DECL|member|settle_time
r_int
r_int
id|settle_time
suffix:semicolon
multiline_comment|/* time to settle after dir change */
DECL|member|side_time
r_int
r_int
id|side_time
suffix:semicolon
multiline_comment|/* time needed to change sides */
)brace
suffix:semicolon
DECL|struct|amiga_floppy_struct
r_struct
id|amiga_floppy_struct
(brace
DECL|member|type
r_struct
id|fd_drive_type
op_star
id|type
suffix:semicolon
multiline_comment|/* type of floppy for this unit */
DECL|member|dtype
r_struct
id|fd_data_type
op_star
id|dtype
suffix:semicolon
multiline_comment|/* type of floppy for this unit */
DECL|member|track
r_int
id|track
suffix:semicolon
multiline_comment|/* current track (-1 == unknown) */
DECL|member|trackbuf
r_int
r_char
op_star
id|trackbuf
suffix:semicolon
multiline_comment|/* current track (kmaloc()&squot;d */
DECL|member|blocks
r_int
id|blocks
suffix:semicolon
multiline_comment|/* total # blocks on disk */
DECL|member|changed
r_int
id|changed
suffix:semicolon
multiline_comment|/* true when not known */
DECL|member|disk
r_int
id|disk
suffix:semicolon
multiline_comment|/* disk in drive (-1 == unknown) */
DECL|member|motor
r_int
id|motor
suffix:semicolon
multiline_comment|/* true when motor is at speed */
DECL|member|busy
r_int
id|busy
suffix:semicolon
multiline_comment|/* true when drive is active */
DECL|member|dirty
r_int
id|dirty
suffix:semicolon
multiline_comment|/* true when trackbuf is not on disk */
DECL|member|status
r_int
id|status
suffix:semicolon
multiline_comment|/* current error code for unit */
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
