multiline_comment|/**&n; * @file oprofile_stats.h&n; *&n; * @remark Copyright 2002 OProfile authors&n; * @remark Read the file COPYING&n; *&n; * @author John Levon&n; */
macro_line|#ifndef OPROFILE_STATS_H
DECL|macro|OPROFILE_STATS_H
mdefine_line|#define OPROFILE_STATS_H
macro_line|#include &lt;asm/atomic.h&gt;
DECL|struct|oprofile_stat_struct
r_struct
id|oprofile_stat_struct
(brace
DECL|member|sample_lost_no_mm
id|atomic_t
id|sample_lost_no_mm
suffix:semicolon
DECL|member|sample_lost_no_mapping
id|atomic_t
id|sample_lost_no_mapping
suffix:semicolon
DECL|member|bt_lost_no_mapping
id|atomic_t
id|bt_lost_no_mapping
suffix:semicolon
DECL|member|event_lost_overflow
id|atomic_t
id|event_lost_overflow
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|oprofile_stat_struct
id|oprofile_stats
suffix:semicolon
multiline_comment|/* reset all stats to zero */
r_void
id|oprofile_reset_stats
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|super_block
suffix:semicolon
r_struct
id|dentry
suffix:semicolon
multiline_comment|/* create the stats/ dir */
r_void
id|oprofile_create_stats_files
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|dentry
op_star
id|root
)paren
suffix:semicolon
macro_line|#endif /* OPROFILE_STATS_H */
eof
