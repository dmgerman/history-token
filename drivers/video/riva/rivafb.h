macro_line|#ifndef __RIVAFB_H
DECL|macro|__RIVAFB_H
mdefine_line|#define __RIVAFB_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
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
r_typedef
r_struct
(brace
DECL|member|red
DECL|member|green
DECL|member|blue
DECL|member|transp
r_int
r_char
id|red
comma
id|green
comma
id|blue
comma
id|transp
suffix:semicolon
DECL|typedef|riva_cfb8_cmap_t
)brace
id|riva_cfb8_cmap_t
suffix:semicolon
r_struct
id|rivafb_info
suffix:semicolon
DECL|struct|rivafb_info
r_struct
id|rivafb_info
(brace
DECL|member|info
r_struct
id|fb_info
id|info
suffix:semicolon
multiline_comment|/* kernel framebuffer info */
DECL|member|riva
id|RIVA_HW_INST
id|riva
suffix:semicolon
multiline_comment|/* interface to riva_hw.c */
DECL|member|drvr_name
r_const
r_char
op_star
id|drvr_name
suffix:semicolon
multiline_comment|/* Riva hardware board type */
DECL|member|ctrl_base_phys
r_int
r_int
id|ctrl_base_phys
suffix:semicolon
multiline_comment|/* physical control register base addr */
DECL|member|fb_base_phys
r_int
r_int
id|fb_base_phys
suffix:semicolon
multiline_comment|/* physical framebuffer base addr */
DECL|member|ctrl_base
id|caddr_t
id|ctrl_base
suffix:semicolon
multiline_comment|/* virtual control register base addr */
DECL|member|fb_base
id|caddr_t
id|fb_base
suffix:semicolon
multiline_comment|/* virtual framebuffer base addr */
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
DECL|member|disp
r_struct
id|display
id|disp
suffix:semicolon
DECL|member|currcon
r_int
id|currcon
suffix:semicolon
DECL|member|currcon_display
r_struct
id|display
op_star
id|currcon_display
suffix:semicolon
DECL|member|next
r_struct
id|rivafb_info
op_star
id|next
suffix:semicolon
DECL|member|pd
r_struct
id|pci_dev
op_star
id|pd
suffix:semicolon
multiline_comment|/* pointer to board&squot;s pci info */
DECL|member|base0_region_size
r_int
id|base0_region_size
suffix:semicolon
multiline_comment|/* size of control register region */
DECL|member|base1_region_size
r_int
id|base1_region_size
suffix:semicolon
multiline_comment|/* size of framebuffer region */
DECL|member|cursor
r_struct
id|riva_cursor
op_star
id|cursor
suffix:semicolon
DECL|member|dispsw
r_struct
id|display_switch
id|dispsw
suffix:semicolon
DECL|member|palette
id|riva_cfb8_cmap_t
id|palette
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* VGA DAC palette cache */
macro_line|#if defined(FBCON_HAS_CFB16) || defined(FBCON_HAS_CFB32)
r_union
(brace
macro_line|#ifdef FBCON_HAS_CFB16
DECL|member|cfb16
id|u_int16_t
id|cfb16
(braket
l_int|16
)braket
suffix:semicolon
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB32
DECL|member|cfb32
id|u_int32_t
id|cfb32
(braket
l_int|16
)braket
suffix:semicolon
macro_line|#endif
DECL|member|con_cmap
)brace
id|con_cmap
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* FBCON_HAS_CFB16 | FBCON_HAS_CFB32 */
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
