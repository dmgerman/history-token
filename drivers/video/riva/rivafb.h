macro_line|#ifndef __RIVAFB_H
DECL|macro|__RIVAFB_H
mdefine_line|#define __RIVAFB_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;video/fbcon.h&gt;
macro_line|#include &lt;video/fbcon-cfb4.h&gt;
macro_line|#include &lt;video/fbcon-cfb8.h&gt;
macro_line|#include &lt;video/fbcon-cfb16.h&gt;
macro_line|#include &lt;video/fbcon-cfb32.h&gt;
macro_line|#include &quot;riva_hw.h&quot;
multiline_comment|/* GGI compatibility macros */
DECL|macro|NUM_SEQ_REGS
mdefine_line|#define NUM_SEQ_REGS&t;&t;0x05
DECL|macro|NUM_CRT_REGS
mdefine_line|#define NUM_CRT_REGS&t;&t;0x41
DECL|macro|NUM_GRC_REGS
mdefine_line|#define NUM_GRC_REGS&t;&t;0x09
DECL|macro|NUM_ATC_REGS
mdefine_line|#define NUM_ATC_REGS&t;&t;0x15
multiline_comment|/* holds the state of the VGA core and extended Riva hw state from riva_hw.c.&n; * From KGI originally. */
DECL|struct|riva_regs
r_struct
id|riva_regs
(brace
DECL|member|attr
id|u8
id|attr
(braket
id|NUM_ATC_REGS
)braket
suffix:semicolon
DECL|member|crtc
id|u8
id|crtc
(braket
id|NUM_CRT_REGS
)braket
suffix:semicolon
DECL|member|gra
id|u8
id|gra
(braket
id|NUM_GRC_REGS
)braket
suffix:semicolon
DECL|member|seq
id|u8
id|seq
(braket
id|NUM_SEQ_REGS
)braket
suffix:semicolon
DECL|member|misc_output
id|u8
id|misc_output
suffix:semicolon
DECL|member|ext
id|RIVA_HW_STATE
id|ext
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MAX_CURS
mdefine_line|#define MAX_CURS                32
DECL|struct|riva_cursor
r_struct
id|riva_cursor
(brace
DECL|member|enable
r_int
id|enable
suffix:semicolon
DECL|member|on
r_int
id|on
suffix:semicolon
DECL|member|vbl_cnt
r_int
id|vbl_cnt
suffix:semicolon
DECL|member|last_slice_moves
DECL|member|prev_slice_moves
r_int
id|last_slice_moves
comma
id|prev_slice_moves
suffix:semicolon
DECL|member|blink_rate
r_int
id|blink_rate
suffix:semicolon
r_struct
(brace
DECL|member|x
DECL|member|y
id|u16
id|x
comma
id|y
suffix:semicolon
DECL|member|pos
DECL|member|size
)brace
id|pos
comma
id|size
suffix:semicolon
DECL|member|image
r_int
r_int
id|image
(braket
id|MAX_CURS
op_star
id|MAX_CURS
)braket
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
op_star
id|timer
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* describes the state of a Riva board */
DECL|struct|riva_par
r_struct
id|riva_par
(brace
DECL|member|riva
id|RIVA_HW_INST
id|riva
suffix:semicolon
multiline_comment|/* interface to riva_hw.c */
DECL|member|ram_amount
r_int
id|ram_amount
suffix:semicolon
multiline_comment|/* amount of RAM on card, in bytes */
DECL|member|dclk_max
r_int
id|dclk_max
suffix:semicolon
multiline_comment|/* max DCLK */
DECL|member|initial_state
r_struct
id|riva_regs
id|initial_state
suffix:semicolon
multiline_comment|/* initial startup video mode */
DECL|member|current_state
r_struct
id|riva_regs
id|current_state
suffix:semicolon
DECL|member|cursor
r_struct
id|riva_cursor
op_star
id|cursor
suffix:semicolon
DECL|member|ctrl_base
id|caddr_t
id|ctrl_base
suffix:semicolon
multiline_comment|/* Virtual control register base addr */
macro_line|#ifdef CONFIG_MTRR
DECL|member|vram
DECL|member|vram_valid
DECL|member|mtrr
r_struct
(brace
r_int
id|vram
suffix:semicolon
r_int
id|vram_valid
suffix:semicolon
)brace
id|mtrr
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
macro_line|#endif /* __RIVAFB_H */
eof
