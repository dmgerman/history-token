multiline_comment|/*          Definitions for DigiBoard ditty(1) command.                 */
macro_line|#if !defined(TIOCMODG)
DECL|macro|TIOCMODG
mdefine_line|#define&t;TIOCMODG&t;((&squot;d&squot;&lt;&lt;8) | 250)&t;&t;/* get modem ctrl state&t;*/
DECL|macro|TIOCMODS
mdefine_line|#define&t;TIOCMODS&t;((&squot;d&squot;&lt;&lt;8) | 251)&t;&t;/* set modem ctrl state&t;*/
macro_line|#endif
macro_line|#if !defined(TIOCMSET)
DECL|macro|TIOCMSET
mdefine_line|#define&t;TIOCMSET&t;((&squot;d&squot;&lt;&lt;8) | 252)&t;&t;/* set modem ctrl state&t;*/
DECL|macro|TIOCMGET
mdefine_line|#define&t;TIOCMGET&t;((&squot;d&squot;&lt;&lt;8) | 253)&t;&t;/* set modem ctrl state&t;*/
macro_line|#endif
macro_line|#if !defined(TIOCMBIC)
DECL|macro|TIOCMBIC
mdefine_line|#define&t;TIOCMBIC&t;((&squot;d&squot;&lt;&lt;8) | 254)&t;&t;/* set modem ctrl state */
DECL|macro|TIOCMBIS
mdefine_line|#define&t;TIOCMBIS&t;((&squot;d&squot;&lt;&lt;8) | 255)&t;&t;/* set modem ctrl state */
macro_line|#endif
macro_line|#if !defined(TIOCSDTR)
DECL|macro|TIOCSDTR
mdefine_line|#define&t;TIOCSDTR&t;((&squot;e&squot;&lt;&lt;8) | 0)&t;&t;/* set DTR&t;&t;*/
DECL|macro|TIOCCDTR
mdefine_line|#define&t;TIOCCDTR&t;((&squot;e&squot;&lt;&lt;8) | 1)&t;&t;/* clear DTR&t;&t;*/
macro_line|#endif
multiline_comment|/************************************************************************&n; * Ioctl command arguments for DIGI parameters.&n; ************************************************************************/
DECL|macro|DIGI_GETA
mdefine_line|#define DIGI_GETA&t;((&squot;e&squot;&lt;&lt;8) | 94)&t;&t;/* Read params&t;&t;*/
DECL|macro|DIGI_SETA
mdefine_line|#define DIGI_SETA&t;((&squot;e&squot;&lt;&lt;8) | 95)&t;&t;/* Set params&t;&t;*/
DECL|macro|DIGI_SETAW
mdefine_line|#define DIGI_SETAW&t;((&squot;e&squot;&lt;&lt;8) | 96)&t;&t;/* Drain &amp; set params&t;*/
DECL|macro|DIGI_SETAF
mdefine_line|#define DIGI_SETAF&t;((&squot;e&squot;&lt;&lt;8) | 97)&t;&t;/* Drain, flush &amp; set params */
DECL|macro|DIGI_GETFLOW
mdefine_line|#define&t;DIGI_GETFLOW&t;((&squot;e&squot;&lt;&lt;8) | 99)&t;&t;/* Get startc/stopc flow */
multiline_comment|/* control characters &t; */
DECL|macro|DIGI_SETFLOW
mdefine_line|#define&t;DIGI_SETFLOW&t;((&squot;e&squot;&lt;&lt;8) | 100)&t;&t;/* Set startc/stopc flow */
multiline_comment|/* control characters&t; */
DECL|macro|DIGI_GETAFLOW
mdefine_line|#define&t;DIGI_GETAFLOW&t;((&squot;e&squot;&lt;&lt;8) | 101)&t;&t;/* Get Aux. startc/stopc */
multiline_comment|/* flow control chars &t; */
DECL|macro|DIGI_SETAFLOW
mdefine_line|#define&t;DIGI_SETAFLOW&t;((&squot;e&squot;&lt;&lt;8) | 102)&t;&t;/* Set Aux. startc/stopc */
multiline_comment|/* flow control chars&t; */
DECL|struct|digiflow_struct
r_struct
id|digiflow_struct
(brace
DECL|member|startc
r_int
r_char
id|startc
suffix:semicolon
multiline_comment|/* flow cntl start char&t;*/
DECL|member|stopc
r_int
r_char
id|stopc
suffix:semicolon
multiline_comment|/* flow cntl stop char&t;*/
)brace
suffix:semicolon
DECL|typedef|digiflow_t
r_typedef
r_struct
id|digiflow_struct
id|digiflow_t
suffix:semicolon
multiline_comment|/************************************************************************&n; * Values for digi_flags &n; ************************************************************************/
DECL|macro|DIGI_IXON
mdefine_line|#define DIGI_IXON&t;0x0001&t;&t;/* Handle IXON in the FEP&t;*/
DECL|macro|DIGI_FAST
mdefine_line|#define DIGI_FAST&t;0x0002&t;&t;/* Fast baud rates&t;&t;*/
DECL|macro|RTSPACE
mdefine_line|#define RTSPACE&t;&t;0x0004&t;&t;/* RTS input flow control&t;*/
DECL|macro|CTSPACE
mdefine_line|#define CTSPACE&t;&t;0x0008&t;&t;/* CTS output flow control&t;*/
DECL|macro|DSRPACE
mdefine_line|#define DSRPACE&t;&t;0x0010&t;&t;/* DSR output flow control&t;*/
DECL|macro|DCDPACE
mdefine_line|#define DCDPACE&t;&t;0x0020&t;&t;/* DCD output flow control&t;*/
DECL|macro|DTRPACE
mdefine_line|#define DTRPACE&t;&t;0x0040&t;&t;/* DTR input flow control&t;*/
DECL|macro|DIGI_FORCEDCD
mdefine_line|#define DIGI_FORCEDCD&t;0x0100&t;&t;/* Force carrier&t;&t;*/
DECL|macro|DIGI_ALTPIN
mdefine_line|#define&t;DIGI_ALTPIN&t;0x0200&t;&t;/* Alternate RJ-45 pin config&t;*/
DECL|macro|DIGI_AIXON
mdefine_line|#define&t;DIGI_AIXON&t;0x0400&t;&t;/* Aux flow control in fep&t;*/
multiline_comment|/************************************************************************&n; * Structure used with ioctl commands for DIGI parameters.&n; ************************************************************************/
DECL|struct|digi_struct
r_struct
id|digi_struct
(brace
DECL|member|digi_flags
r_int
r_int
id|digi_flags
suffix:semicolon
multiline_comment|/* Flags (see above)&t;*/
)brace
suffix:semicolon
DECL|typedef|digi_t
r_typedef
r_struct
id|digi_struct
id|digi_t
suffix:semicolon
eof
