multiline_comment|/*&n; * (C) 2002 - 2003 Dominik Brodowski &lt;linux@brodo.de&gt;&n; *&n; *  Licensed under the terms of the GNU GPL License version 2.&n; *&n; *  Library for common functions for Intel SpeedStep v.1 and v.2 support&n; *&n; *  BIG FAT DISCLAIMER: Work in progress code. Possibly *dangerous*&n; */
multiline_comment|/* processors */
DECL|macro|SPEEDSTEP_PROCESSOR_PIII_C_EARLY
mdefine_line|#define SPEEDSTEP_PROCESSOR_PIII_C_EARLY&t;0x00000001  /* Coppermine core */
DECL|macro|SPEEDSTEP_PROCESSOR_PIII_C
mdefine_line|#define SPEEDSTEP_PROCESSOR_PIII_C&t;&t;0x00000002  /* Coppermine core */
DECL|macro|SPEEDSTEP_PROCESSOR_PIII_T
mdefine_line|#define SPEEDSTEP_PROCESSOR_PIII_T &t;&t;0x00000003  /* Tualatin core */
DECL|macro|SPEEDSTEP_PROCESSOR_P4M
mdefine_line|#define SPEEDSTEP_PROCESSOR_P4M&t;&t;&t;0x00000004  /* P4-M with 100 MHz FSB */
multiline_comment|/* speedstep states -- only two of them */
DECL|macro|SPEEDSTEP_HIGH
mdefine_line|#define SPEEDSTEP_HIGH                  0x00000000
DECL|macro|SPEEDSTEP_LOW
mdefine_line|#define SPEEDSTEP_LOW                   0x00000001
multiline_comment|/* detect a speedstep-capable processor */
r_extern
r_int
r_int
id|speedstep_detect_processor
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* detect the current speed (in khz) of the processor */
r_extern
r_int
r_int
id|speedstep_get_processor_frequency
c_func
(paren
r_int
r_int
id|processor
)paren
suffix:semicolon
multiline_comment|/* detect the low and high speeds of the processor. The callback &n; * set_state&quot;&squot;s first argument is either SPEEDSTEP_HIGH or &n; * SPEEDSTEP_LOW; the second argument is zero so that no &n; * cpufreq_notify_transition calls are initiated.&n; */
r_extern
r_int
r_int
id|speedstep_get_freqs
c_func
(paren
r_int
r_int
id|processor
comma
r_int
r_int
op_star
id|low_speed
comma
r_int
r_int
op_star
id|high_speed
comma
r_void
(paren
op_star
id|set_state
)paren
(paren
r_int
r_int
id|state
comma
r_int
r_int
id|notify
)paren
)paren
suffix:semicolon
eof
