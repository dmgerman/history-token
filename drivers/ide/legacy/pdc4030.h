multiline_comment|/*&n; *  linux/drivers/ide/legacy/pdc4030.h&n; *&n; *  Copyright (C) 1995-1998  Linus Torvalds &amp; authors&n; */
multiline_comment|/*&n; * Principal author: Peter Denison &lt;peterd@pnd-pc.demon.co.uk&gt;&n; */
macro_line|#ifndef IDE_PROMISE_H
DECL|macro|IDE_PROMISE_H
mdefine_line|#define IDE_PROMISE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef CONFIG_BLK_DEV_PDC4030
macro_line|# ifdef _IDE_DISK
DECL|macro|IS_PDC4030_DRIVE
macro_line|# define IS_PDC4030_DRIVE (0)&t;/* auto-NULLs out pdc4030 code */
id|ide_startstop_t
id|promise_rw_disk
c_func
(paren
id|ide_drive_t
op_star
comma
r_struct
id|request
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|function|promise_rw_disk
id|ide_startstop_t
id|promise_rw_disk
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
r_struct
id|request
op_star
id|rq
comma
r_int
r_int
id|block
)paren
(brace
r_return
id|ide_stopped
suffix:semicolon
)brace
macro_line|# endif /* _IDE_DISK */
macro_line|#else /* CONFIG_BLK_DEV_PDC4030 */
macro_line|# ifdef _IDE_DISK
DECL|macro|IS_PDC4030_DRIVE
macro_line|#  define IS_PDC4030_DRIVE (HWIF(drive)-&gt;chipset == ide_pdc4030)
id|ide_startstop_t
id|promise_rw_disk
c_func
(paren
id|ide_drive_t
op_star
comma
r_struct
id|request
op_star
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|# endif /* _IDE_DISK */
macro_line|#endif /* CONFIG_BLK_DEV_PDC4030 */
macro_line|#ifdef __PROMISE_4030
DECL|macro|PROMISE_EXTENDED_COMMAND
mdefine_line|#define&t;PROMISE_EXTENDED_COMMAND&t;0xF0
DECL|macro|PROMISE_READ
mdefine_line|#define&t;PROMISE_READ&t;&t;&t;0xF2
DECL|macro|PROMISE_WRITE
mdefine_line|#define&t;PROMISE_WRITE&t;&t;&t;0xF3
multiline_comment|/* Extended commands - main command code = 0xf0 */
DECL|macro|PROMISE_GET_CONFIG
mdefine_line|#define&t;PROMISE_GET_CONFIG&t;&t;0x10
DECL|macro|PROMISE_IDENTIFY
mdefine_line|#define&t;PROMISE_IDENTIFY&t;&t;0x20
DECL|struct|translation_mode
r_struct
id|translation_mode
(brace
DECL|member|cyl
id|u16
id|cyl
suffix:semicolon
DECL|member|head
id|u8
id|head
suffix:semicolon
DECL|member|sect
id|u8
id|sect
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dc_ident
r_struct
id|dc_ident
(brace
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|unknown1
id|u8
id|unknown1
suffix:semicolon
DECL|member|hw_revision
id|u8
id|hw_revision
suffix:semicolon
DECL|member|firmware_major
id|u8
id|firmware_major
suffix:semicolon
DECL|member|firmware_minor
id|u8
id|firmware_minor
suffix:semicolon
DECL|member|bios_address
id|u8
id|bios_address
suffix:semicolon
DECL|member|irq
id|u8
id|irq
suffix:semicolon
DECL|member|unknown2
id|u8
id|unknown2
suffix:semicolon
DECL|member|cache_mem
id|u16
id|cache_mem
suffix:semicolon
DECL|member|unknown3
id|u16
id|unknown3
suffix:semicolon
DECL|member|id
id|u8
id|id
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|info
id|u16
id|info
suffix:semicolon
DECL|member|current_tm
r_struct
id|translation_mode
id|current_tm
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|pad
id|u8
id|pad
(braket
id|SECTOR_WORDS
op_star
l_int|4
op_minus
l_int|32
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __PROMISE_4030 */
macro_line|#endif /* IDE_PROMISE_H */
eof
