multiline_comment|/*&n; *  linux/drivers/ide/ide_modes.h&n; *&n; *  Copyright (C) 1996  Linus Torvalds, Igor Abramov, and Mark Lord&n; */
macro_line|#ifndef _IDE_MODES_H
DECL|macro|_IDE_MODES_H
mdefine_line|#define _IDE_MODES_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Shared data/functions for determining best PIO mode for an IDE drive.&n; */
macro_line|#ifdef CONFIG_BLK_DEV_IDE_MODES
multiline_comment|/*&n; * Standard (generic) timings for PIO modes, from ATA2 specification.&n; * These timings are for access to the IDE data port register *only*.&n; * Some drives may specify a mode, while also specifying a different&n; * value for cycle_time (from drive identification data).&n; */
DECL|struct|ide_pio_timings_s
r_typedef
r_struct
id|ide_pio_timings_s
(brace
DECL|member|setup_time
r_int
id|setup_time
suffix:semicolon
multiline_comment|/* Address setup (ns) minimum */
DECL|member|active_time
r_int
id|active_time
suffix:semicolon
multiline_comment|/* Active pulse (ns) minimum */
DECL|member|cycle_time
r_int
id|cycle_time
suffix:semicolon
multiline_comment|/* Cycle time (ns) minimum = (setup + active + recovery) */
DECL|typedef|ide_pio_timings_t
)brace
id|ide_pio_timings_t
suffix:semicolon
DECL|struct|ide_pio_data_s
r_typedef
r_struct
id|ide_pio_data_s
(brace
DECL|member|pio_mode
id|byte
id|pio_mode
suffix:semicolon
DECL|member|use_iordy
id|byte
id|use_iordy
suffix:semicolon
DECL|member|overridden
id|byte
id|overridden
suffix:semicolon
DECL|member|blacklisted
id|byte
id|blacklisted
suffix:semicolon
DECL|member|cycle_time
r_int
r_int
id|cycle_time
suffix:semicolon
DECL|typedef|ide_pio_data_t
)brace
id|ide_pio_data_t
suffix:semicolon
r_extern
r_int
id|ide_scan_pio_blacklist
(paren
r_char
op_star
id|model
)paren
suffix:semicolon
r_extern
id|byte
id|ide_get_best_pio_mode
(paren
id|ide_drive_t
op_star
id|drive
comma
id|byte
id|mode_wanted
comma
id|byte
id|max_mode
comma
id|ide_pio_data_t
op_star
id|d
)paren
suffix:semicolon
r_extern
r_const
id|ide_pio_timings_t
id|ide_pio_timings
(braket
l_int|6
)braket
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
