macro_line|#ifndef _MC6821_H_
DECL|macro|_MC6821_H_
mdefine_line|#define _MC6821_H_
multiline_comment|/*&n; * This file describes the memery mapping of the MC6821 PIA.&n; * The unions describe overlayed registers. Which of them is used is&n; * determined by bit 2 of the corresponding control register.&n; * this files expects the PIA_REG_PADWIDTH to be defined the numeric&n; * value of the register spacing.&n; *&n; * Data came from MFC-31-Developer Kit (from Ralph Seidel,&n; * zodiac@darkness.gun.de) and Motorola Data Sheet (from &n; * Richard Hirst, srh@gpt.co.uk)&n; *&n; * 6.11.95 copyright Joerg Dorchain (dorchain@mpi-sb.mpg.de)&n; *&n; */
macro_line|#ifndef PIA_REG_PADWIDTH
DECL|macro|PIA_REG_PADWIDTH
mdefine_line|#define PIA_REG_PADWIDTH 255
macro_line|#endif
DECL|struct|pia
r_struct
id|pia
(brace
r_union
(brace
DECL|member|pra
r_volatile
id|u_char
id|pra
suffix:semicolon
DECL|member|ddra
r_volatile
id|u_char
id|ddra
suffix:semicolon
DECL|member|ua
)brace
id|ua
suffix:semicolon
DECL|member|pad1
id|u_char
id|pad1
(braket
id|PIA_REG_PADWIDTH
)braket
suffix:semicolon
DECL|member|cra
r_volatile
id|u_char
id|cra
suffix:semicolon
DECL|member|pad2
id|u_char
id|pad2
(braket
id|PIA_REG_PADWIDTH
)braket
suffix:semicolon
r_union
(brace
DECL|member|prb
r_volatile
id|u_char
id|prb
suffix:semicolon
DECL|member|ddrb
r_volatile
id|u_char
id|ddrb
suffix:semicolon
DECL|member|ub
)brace
id|ub
suffix:semicolon
DECL|member|pad3
id|u_char
id|pad3
(braket
id|PIA_REG_PADWIDTH
)braket
suffix:semicolon
DECL|member|crb
r_volatile
id|u_char
id|crb
suffix:semicolon
DECL|member|pad4
id|u_char
id|pad4
(braket
id|PIA_REG_PADWIDTH
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ppra
mdefine_line|#define ppra ua.pra
DECL|macro|pddra
mdefine_line|#define pddra ua.ddra
DECL|macro|pprb
mdefine_line|#define pprb ub.prb
DECL|macro|pddrb
mdefine_line|#define pddrb ub.ddrb
DECL|macro|PIA_C1_ENABLE_IRQ
mdefine_line|#define PIA_C1_ENABLE_IRQ (1&lt;&lt;0)
DECL|macro|PIA_C1_LOW_TO_HIGH
mdefine_line|#define PIA_C1_LOW_TO_HIGH (1&lt;&lt;1)
DECL|macro|PIA_DDR
mdefine_line|#define PIA_DDR (1&lt;&lt;2)
DECL|macro|PIA_IRQ2
mdefine_line|#define PIA_IRQ2 (1&lt;&lt;6)
DECL|macro|PIA_IRQ1
mdefine_line|#define PIA_IRQ1 (1&lt;&lt;7)
macro_line|#endif
eof
