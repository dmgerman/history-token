multiline_comment|/*&n; *  linux/drivers/video/acornfb.h&n; *&n; *  Copyright (C) 1998,1999 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Frame buffer code for Acorn platforms&n; */
macro_line|#if defined(HAS_VIDC20)
macro_line|#include &lt;asm/hardware/iomd.h&gt;
DECL|macro|VIDC_PALETTE_SIZE
mdefine_line|#define VIDC_PALETTE_SIZE&t;256
DECL|macro|VIDC_NAME
mdefine_line|#define VIDC_NAME&t;&t;&quot;VIDC20&quot;
macro_line|#elif defined(HAS_VIDC)
macro_line|#include &lt;asm/hardware/memc.h&gt;
DECL|macro|VIDC_PALETTE_SIZE
mdefine_line|#define VIDC_PALETTE_SIZE&t;16
DECL|macro|VIDC_NAME
mdefine_line|#define VIDC_NAME&t;&t;&quot;VIDC&quot;
macro_line|#endif
DECL|macro|EXTEND8
mdefine_line|#define EXTEND8(x) ((x)|(x)&lt;&lt;8)
DECL|macro|EXTEND4
mdefine_line|#define EXTEND4(x) ((x)|(x)&lt;&lt;4|(x)&lt;&lt;8|(x)&lt;&lt;12)
DECL|struct|vidc20_palette
r_struct
id|vidc20_palette
(brace
DECL|member|red
id|u_int
id|red
suffix:colon
l_int|8
suffix:semicolon
DECL|member|green
id|u_int
id|green
suffix:colon
l_int|8
suffix:semicolon
DECL|member|blue
id|u_int
id|blue
suffix:colon
l_int|8
suffix:semicolon
DECL|member|ext
id|u_int
id|ext
suffix:colon
l_int|4
suffix:semicolon
DECL|member|unused
id|u_int
id|unused
suffix:colon
l_int|4
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|vidc_palette
r_struct
id|vidc_palette
(brace
DECL|member|red
id|u_int
id|red
suffix:colon
l_int|4
suffix:semicolon
DECL|member|green
id|u_int
id|green
suffix:colon
l_int|4
suffix:semicolon
DECL|member|blue
id|u_int
id|blue
suffix:colon
l_int|4
suffix:semicolon
DECL|member|trans
id|u_int
id|trans
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sbz1
id|u_int
id|sbz1
suffix:colon
l_int|13
suffix:semicolon
DECL|member|reg
id|u_int
id|reg
suffix:colon
l_int|4
suffix:semicolon
DECL|member|sbz2
id|u_int
id|sbz2
suffix:colon
l_int|2
suffix:semicolon
)brace
suffix:semicolon
DECL|union|palette
r_union
id|palette
(brace
DECL|member|vidc20
r_struct
id|vidc20_palette
id|vidc20
suffix:semicolon
DECL|member|vidc
r_struct
id|vidc_palette
id|vidc
suffix:semicolon
DECL|member|p
id|u_int
id|p
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|acornfb_par
r_struct
id|acornfb_par
(brace
DECL|member|screen_base
r_int
r_int
id|screen_base
suffix:semicolon
DECL|member|screen_base_p
r_int
r_int
id|screen_base_p
suffix:semicolon
DECL|member|screen_end
r_int
r_int
id|screen_end
suffix:semicolon
DECL|member|screen_size
r_int
r_int
id|screen_size
suffix:semicolon
DECL|member|dram_size
r_int
r_int
id|dram_size
suffix:semicolon
DECL|member|vram_half_sam
r_int
r_int
id|vram_half_sam
suffix:semicolon
DECL|member|palette_size
r_int
r_int
id|palette_size
suffix:semicolon
DECL|member|montype
r_int
r_int
id|montype
suffix:semicolon
DECL|member|currcon
r_int
r_int
id|currcon
suffix:semicolon
DECL|member|using_vram
r_int
r_int
id|using_vram
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dpms
r_int
r_int
id|dpms
suffix:colon
l_int|1
suffix:semicolon
DECL|member|palette
r_union
id|palette
id|palette
(braket
id|VIDC_PALETTE_SIZE
)braket
suffix:semicolon
r_union
(brace
DECL|member|cfb16
r_int
r_int
id|cfb16
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|cfb32
r_int
r_int
id|cfb32
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|cmap
)brace
id|cmap
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|vidc_timing
r_struct
id|vidc_timing
(brace
DECL|member|h_cycle
id|u_int
id|h_cycle
suffix:semicolon
DECL|member|h_sync_width
id|u_int
id|h_sync_width
suffix:semicolon
DECL|member|h_border_start
id|u_int
id|h_border_start
suffix:semicolon
DECL|member|h_display_start
id|u_int
id|h_display_start
suffix:semicolon
DECL|member|h_display_end
id|u_int
id|h_display_end
suffix:semicolon
DECL|member|h_border_end
id|u_int
id|h_border_end
suffix:semicolon
DECL|member|h_interlace
id|u_int
id|h_interlace
suffix:semicolon
DECL|member|v_cycle
id|u_int
id|v_cycle
suffix:semicolon
DECL|member|v_sync_width
id|u_int
id|v_sync_width
suffix:semicolon
DECL|member|v_border_start
id|u_int
id|v_border_start
suffix:semicolon
DECL|member|v_display_start
id|u_int
id|v_display_start
suffix:semicolon
DECL|member|v_display_end
id|u_int
id|v_display_end
suffix:semicolon
DECL|member|v_border_end
id|u_int
id|v_border_end
suffix:semicolon
DECL|member|control
id|u_int
id|control
suffix:semicolon
multiline_comment|/* VIDC20 only */
DECL|member|pll_ctl
id|u_int
id|pll_ctl
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|modey_params
r_struct
id|modey_params
(brace
DECL|member|y_res
id|u_int
id|y_res
suffix:semicolon
DECL|member|u_margin
id|u_int
id|u_margin
suffix:semicolon
DECL|member|b_margin
id|u_int
id|b_margin
suffix:semicolon
DECL|member|vsync_len
id|u_int
id|vsync_len
suffix:semicolon
DECL|member|vf
id|u_int
id|vf
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|modex_params
r_struct
id|modex_params
(brace
DECL|member|x_res
id|u_int
id|x_res
suffix:semicolon
DECL|member|l_margin
id|u_int
id|l_margin
suffix:semicolon
DECL|member|r_margin
id|u_int
id|r_margin
suffix:semicolon
DECL|member|hsync_len
id|u_int
id|hsync_len
suffix:semicolon
DECL|member|clock
id|u_int
id|clock
suffix:semicolon
DECL|member|hf
id|u_int
id|hf
suffix:semicolon
DECL|member|modey
r_const
r_struct
id|modey_params
op_star
id|modey
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef HAS_VIDC
DECL|macro|VID_CTL_VS_NVSYNC
mdefine_line|#define VID_CTL_VS_NVSYNC&t;(1 &lt;&lt; 3)
DECL|macro|VID_CTL_HS_NHSYNC
mdefine_line|#define VID_CTL_HS_NHSYNC&t;(1 &lt;&lt; 2)
DECL|macro|VID_CTL_24MHz
mdefine_line|#define VID_CTL_24MHz&t;&t;(0)
DECL|macro|VID_CTL_25MHz
mdefine_line|#define VID_CTL_25MHz&t;&t;(1)
DECL|macro|VID_CTL_36MHz
mdefine_line|#define VID_CTL_36MHz&t;&t;(2)
DECL|macro|VIDC_CTRL_INTERLACE
mdefine_line|#define VIDC_CTRL_INTERLACE&t;(1 &lt;&lt; 6)
DECL|macro|VIDC_CTRL_FIFO_0_4
mdefine_line|#define VIDC_CTRL_FIFO_0_4&t;(0 &lt;&lt; 4)
DECL|macro|VIDC_CTRL_FIFO_1_5
mdefine_line|#define VIDC_CTRL_FIFO_1_5&t;(1 &lt;&lt; 4)
DECL|macro|VIDC_CTRL_FIFO_2_6
mdefine_line|#define VIDC_CTRL_FIFO_2_6&t;(2 &lt;&lt; 4)
DECL|macro|VIDC_CTRL_FIFO_3_7
mdefine_line|#define VIDC_CTRL_FIFO_3_7&t;(3 &lt;&lt; 4)
DECL|macro|VIDC_CTRL_1BPP
mdefine_line|#define VIDC_CTRL_1BPP&t;&t;(0 &lt;&lt; 2)
DECL|macro|VIDC_CTRL_2BPP
mdefine_line|#define VIDC_CTRL_2BPP&t;&t;(1 &lt;&lt; 2)
DECL|macro|VIDC_CTRL_4BPP
mdefine_line|#define VIDC_CTRL_4BPP&t;&t;(2 &lt;&lt; 2)
DECL|macro|VIDC_CTRL_8BPP
mdefine_line|#define VIDC_CTRL_8BPP&t;&t;(3 &lt;&lt; 2)
DECL|macro|VIDC_CTRL_DIV3
mdefine_line|#define VIDC_CTRL_DIV3&t;&t;(0 &lt;&lt; 0)
DECL|macro|VIDC_CTRL_DIV2
mdefine_line|#define VIDC_CTRL_DIV2&t;&t;(1 &lt;&lt; 0)
DECL|macro|VIDC_CTRL_DIV1_5
mdefine_line|#define VIDC_CTRL_DIV1_5&t;(2 &lt;&lt; 0)
DECL|macro|VIDC_CTRL_DIV1
mdefine_line|#define VIDC_CTRL_DIV1&t;&t;(3 &lt;&lt; 0)
macro_line|#endif
macro_line|#ifdef HAS_VIDC20
multiline_comment|/*&n; * VIDC20 registers&n; */
DECL|macro|VIDC20_CTRL
mdefine_line|#define VIDC20_CTRL&t;&t;0xe0000000
DECL|macro|VIDC20_CTRL_PIX_VCLK
mdefine_line|#define VIDC20_CTRL_PIX_VCLK&t;(0 &lt;&lt; 0)
DECL|macro|VIDC20_CTRL_PIX_HCLK
mdefine_line|#define VIDC20_CTRL_PIX_HCLK&t;(1 &lt;&lt; 0)
DECL|macro|VIDC20_CTRL_PIX_RCLK
mdefine_line|#define VIDC20_CTRL_PIX_RCLK&t;(2 &lt;&lt; 0)
DECL|macro|VIDC20_CTRL_PIX_CK
mdefine_line|#define VIDC20_CTRL_PIX_CK&t;(0 &lt;&lt; 2)
DECL|macro|VIDC20_CTRL_PIX_CK2
mdefine_line|#define VIDC20_CTRL_PIX_CK2&t;(1 &lt;&lt; 2)
DECL|macro|VIDC20_CTRL_PIX_CK3
mdefine_line|#define VIDC20_CTRL_PIX_CK3&t;(2 &lt;&lt; 2)
DECL|macro|VIDC20_CTRL_PIX_CK4
mdefine_line|#define VIDC20_CTRL_PIX_CK4&t;(3 &lt;&lt; 2)
DECL|macro|VIDC20_CTRL_PIX_CK5
mdefine_line|#define VIDC20_CTRL_PIX_CK5&t;(4 &lt;&lt; 2)
DECL|macro|VIDC20_CTRL_PIX_CK6
mdefine_line|#define VIDC20_CTRL_PIX_CK6&t;(5 &lt;&lt; 2)
DECL|macro|VIDC20_CTRL_PIX_CK7
mdefine_line|#define VIDC20_CTRL_PIX_CK7&t;(6 &lt;&lt; 2)
DECL|macro|VIDC20_CTRL_PIX_CK8
mdefine_line|#define VIDC20_CTRL_PIX_CK8&t;(7 &lt;&lt; 2)
DECL|macro|VIDC20_CTRL_1BPP
mdefine_line|#define VIDC20_CTRL_1BPP&t;(0 &lt;&lt; 5)
DECL|macro|VIDC20_CTRL_2BPP
mdefine_line|#define VIDC20_CTRL_2BPP&t;(1 &lt;&lt; 5)
DECL|macro|VIDC20_CTRL_4BPP
mdefine_line|#define VIDC20_CTRL_4BPP&t;(2 &lt;&lt; 5)
DECL|macro|VIDC20_CTRL_8BPP
mdefine_line|#define VIDC20_CTRL_8BPP&t;(3 &lt;&lt; 5)
DECL|macro|VIDC20_CTRL_16BPP
mdefine_line|#define VIDC20_CTRL_16BPP&t;(4 &lt;&lt; 5)
DECL|macro|VIDC20_CTRL_32BPP
mdefine_line|#define VIDC20_CTRL_32BPP&t;(6 &lt;&lt; 5)
DECL|macro|VIDC20_CTRL_FIFO_NS
mdefine_line|#define VIDC20_CTRL_FIFO_NS&t;(0 &lt;&lt; 8)
DECL|macro|VIDC20_CTRL_FIFO_4
mdefine_line|#define VIDC20_CTRL_FIFO_4&t;(1 &lt;&lt; 8)
DECL|macro|VIDC20_CTRL_FIFO_8
mdefine_line|#define VIDC20_CTRL_FIFO_8&t;(2 &lt;&lt; 8)
DECL|macro|VIDC20_CTRL_FIFO_12
mdefine_line|#define VIDC20_CTRL_FIFO_12&t;(3 &lt;&lt; 8)
DECL|macro|VIDC20_CTRL_FIFO_16
mdefine_line|#define VIDC20_CTRL_FIFO_16&t;(4 &lt;&lt; 8)
DECL|macro|VIDC20_CTRL_FIFO_20
mdefine_line|#define VIDC20_CTRL_FIFO_20&t;(5 &lt;&lt; 8)
DECL|macro|VIDC20_CTRL_FIFO_24
mdefine_line|#define VIDC20_CTRL_FIFO_24&t;(6 &lt;&lt; 8)
DECL|macro|VIDC20_CTRL_FIFO_28
mdefine_line|#define VIDC20_CTRL_FIFO_28&t;(7 &lt;&lt; 8)
DECL|macro|VIDC20_CTRL_INT
mdefine_line|#define VIDC20_CTRL_INT&t;&t;(1 &lt;&lt; 12)
DECL|macro|VIDC20_CTRL_DUP
mdefine_line|#define VIDC20_CTRL_DUP&t;&t;(1 &lt;&lt; 13)
DECL|macro|VIDC20_CTRL_PDOWN
mdefine_line|#define VIDC20_CTRL_PDOWN&t;(1 &lt;&lt; 14)
DECL|macro|VIDC20_ECTL
mdefine_line|#define VIDC20_ECTL&t;&t;0xc0000000
DECL|macro|VIDC20_ECTL_REG
mdefine_line|#define VIDC20_ECTL_REG(x)&t;((x) &amp; 0xf3)
DECL|macro|VIDC20_ECTL_ECK
mdefine_line|#define VIDC20_ECTL_ECK&t;&t;(1 &lt;&lt; 2)
DECL|macro|VIDC20_ECTL_REDPED
mdefine_line|#define VIDC20_ECTL_REDPED&t;(1 &lt;&lt; 8)
DECL|macro|VIDC20_ECTL_GREENPED
mdefine_line|#define VIDC20_ECTL_GREENPED&t;(1 &lt;&lt; 9)
DECL|macro|VIDC20_ECTL_BLUEPED
mdefine_line|#define VIDC20_ECTL_BLUEPED&t;(1 &lt;&lt; 10)
DECL|macro|VIDC20_ECTL_DAC
mdefine_line|#define VIDC20_ECTL_DAC&t;&t;(1 &lt;&lt; 12)
DECL|macro|VIDC20_ECTL_LCDGS
mdefine_line|#define VIDC20_ECTL_LCDGS&t;(1 &lt;&lt; 13)
DECL|macro|VIDC20_ECTL_HRM
mdefine_line|#define VIDC20_ECTL_HRM&t;&t;(1 &lt;&lt; 14)
DECL|macro|VIDC20_ECTL_HS_MASK
mdefine_line|#define VIDC20_ECTL_HS_MASK&t;(3 &lt;&lt; 16)
DECL|macro|VIDC20_ECTL_HS_HSYNC
mdefine_line|#define VIDC20_ECTL_HS_HSYNC&t;(0 &lt;&lt; 16)
DECL|macro|VIDC20_ECTL_HS_NHSYNC
mdefine_line|#define VIDC20_ECTL_HS_NHSYNC&t;(1 &lt;&lt; 16)
DECL|macro|VIDC20_ECTL_HS_CSYNC
mdefine_line|#define VIDC20_ECTL_HS_CSYNC&t;(2 &lt;&lt; 16)
DECL|macro|VIDC20_ECTL_HS_NCSYNC
mdefine_line|#define VIDC20_ECTL_HS_NCSYNC&t;(3 &lt;&lt; 16)
DECL|macro|VIDC20_ECTL_VS_MASK
mdefine_line|#define VIDC20_ECTL_VS_MASK&t;(3 &lt;&lt; 18)
DECL|macro|VIDC20_ECTL_VS_VSYNC
mdefine_line|#define VIDC20_ECTL_VS_VSYNC&t;(0 &lt;&lt; 18)
DECL|macro|VIDC20_ECTL_VS_NVSYNC
mdefine_line|#define VIDC20_ECTL_VS_NVSYNC&t;(1 &lt;&lt; 18)
DECL|macro|VIDC20_ECTL_VS_CSYNC
mdefine_line|#define VIDC20_ECTL_VS_CSYNC&t;(2 &lt;&lt; 18)
DECL|macro|VIDC20_ECTL_VS_NCSYNC
mdefine_line|#define VIDC20_ECTL_VS_NCSYNC&t;(3 &lt;&lt; 18)
DECL|macro|VIDC20_DCTL
mdefine_line|#define VIDC20_DCTL&t;&t;0xf0000000
multiline_comment|/* 0-9 = number of words in scanline */
DECL|macro|VIDC20_DCTL_SNA
mdefine_line|#define VIDC20_DCTL_SNA&t;&t;(1 &lt;&lt; 12)
DECL|macro|VIDC20_DCTL_HDIS
mdefine_line|#define VIDC20_DCTL_HDIS&t;(1 &lt;&lt; 13)
DECL|macro|VIDC20_DCTL_BUS_NS
mdefine_line|#define VIDC20_DCTL_BUS_NS&t;(0 &lt;&lt; 16)
DECL|macro|VIDC20_DCTL_BUS_D31_0
mdefine_line|#define VIDC20_DCTL_BUS_D31_0&t;(1 &lt;&lt; 16)
DECL|macro|VIDC20_DCTL_BUS_D63_32
mdefine_line|#define VIDC20_DCTL_BUS_D63_32&t;(2 &lt;&lt; 16)
DECL|macro|VIDC20_DCTL_BUS_D63_0
mdefine_line|#define VIDC20_DCTL_BUS_D63_0&t;(3 &lt;&lt; 16)
DECL|macro|VIDC20_DCTL_VRAM_DIS
mdefine_line|#define VIDC20_DCTL_VRAM_DIS&t;(0 &lt;&lt; 18)
DECL|macro|VIDC20_DCTL_VRAM_PXCLK
mdefine_line|#define VIDC20_DCTL_VRAM_PXCLK&t;(1 &lt;&lt; 18)
DECL|macro|VIDC20_DCTL_VRAM_PXCLK2
mdefine_line|#define VIDC20_DCTL_VRAM_PXCLK2&t;(2 &lt;&lt; 18)
DECL|macro|VIDC20_DCTL_VRAM_PXCLK4
mdefine_line|#define VIDC20_DCTL_VRAM_PXCLK4&t;(3 &lt;&lt; 18)
macro_line|#endif
eof
