macro_line|#ifndef __RIVAFB_H
DECL|macro|__RIVAFB_H
mdefine_line|#define __RIVAFB_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;video/vga.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-id.h&gt;
macro_line|#include &lt;linux/i2c-algo-bit.h&gt;
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
multiline_comment|/* I2C */
DECL|macro|DDC_SCL_READ_MASK
mdefine_line|#define DDC_SCL_READ_MASK       (1 &lt;&lt; 2)
DECL|macro|DDC_SCL_WRITE_MASK
mdefine_line|#define DDC_SCL_WRITE_MASK      (1 &lt;&lt; 5)
DECL|macro|DDC_SDA_READ_MASK
mdefine_line|#define DDC_SDA_READ_MASK       (1 &lt;&lt; 3)
DECL|macro|DDC_SDA_WRITE_MASK
mdefine_line|#define DDC_SDA_WRITE_MASK      (1 &lt;&lt; 4)
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
r_struct
id|riva_par
suffix:semicolon
DECL|struct|riva_i2c_chan
r_struct
id|riva_i2c_chan
(brace
DECL|member|par
r_struct
id|riva_par
op_star
id|par
suffix:semicolon
DECL|member|ddc_base
r_int
r_int
id|ddc_base
suffix:semicolon
DECL|member|adapter
r_struct
id|i2c_adapter
id|adapter
suffix:semicolon
DECL|member|algo
r_struct
id|i2c_algo_bit_data
id|algo
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|riva_par
r_struct
id|riva_par
(brace
DECL|member|riva
id|RIVA_HW_INST
id|riva
suffix:semicolon
multiline_comment|/* interface to riva_hw.c */
DECL|member|pseudo_palette
id|u32
id|pseudo_palette
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* default palette */
DECL|member|palette
id|u32
id|palette
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* for Riva128 */
DECL|member|ctrl_base
id|u8
id|__iomem
op_star
id|ctrl_base
suffix:semicolon
multiline_comment|/* virtual control register base addr */
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
macro_line|#ifdef CONFIG_X86
DECL|member|state
r_struct
id|vgastate
id|state
suffix:semicolon
macro_line|#endif
DECL|member|ref_count
id|atomic_t
id|ref_count
suffix:semicolon
DECL|member|EDID
r_int
r_char
op_star
id|EDID
suffix:semicolon
DECL|member|Chipset
r_int
r_int
id|Chipset
suffix:semicolon
DECL|member|forceCRTC
r_int
id|forceCRTC
suffix:semicolon
DECL|member|SecondCRTC
id|Bool
id|SecondCRTC
suffix:semicolon
DECL|member|FlatPanel
r_int
id|FlatPanel
suffix:semicolon
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
DECL|member|bus
r_int
id|bus
suffix:semicolon
DECL|member|cursor_reset
r_int
id|cursor_reset
suffix:semicolon
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
DECL|member|chan
r_struct
id|riva_i2c_chan
id|chan
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
r_void
id|riva_common_setup
c_func
(paren
r_struct
id|riva_par
op_star
)paren
suffix:semicolon
r_int
r_int
id|riva_get_memlen
c_func
(paren
r_struct
id|riva_par
op_star
)paren
suffix:semicolon
r_int
r_int
id|riva_get_maxdclk
c_func
(paren
r_struct
id|riva_par
op_star
)paren
suffix:semicolon
r_void
id|riva_delete_i2c_busses
c_func
(paren
r_struct
id|riva_par
op_star
id|par
)paren
suffix:semicolon
r_void
id|riva_create_i2c_busses
c_func
(paren
r_struct
id|riva_par
op_star
id|par
)paren
suffix:semicolon
r_int
id|riva_probe_i2c_connector
c_func
(paren
r_struct
id|riva_par
op_star
id|par
comma
r_int
id|conn
comma
id|u8
op_star
op_star
id|out_edid
)paren
suffix:semicolon
macro_line|#endif /* __RIVAFB_H */
eof
