multiline_comment|/*&n; * drivers/video/geode/geodefb.h&n; *   -- Geode framebuffer driver&n; *&n; * Copyright (C) 2005 Arcom Control Systems Ltd.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; */
macro_line|#ifndef __GEODEFB_H__
DECL|macro|__GEODEFB_H__
mdefine_line|#define __GEODEFB_H__
r_struct
id|geodefb_info
suffix:semicolon
DECL|struct|geode_dc_ops
r_struct
id|geode_dc_ops
(brace
DECL|member|set_mode
r_void
(paren
op_star
id|set_mode
)paren
(paren
r_struct
id|fb_info
op_star
)paren
suffix:semicolon
DECL|member|set_palette_reg
r_void
(paren
op_star
id|set_palette_reg
)paren
(paren
r_struct
id|fb_info
op_star
comma
r_int
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|geode_vid_ops
r_struct
id|geode_vid_ops
(brace
DECL|member|set_dclk
r_void
(paren
op_star
id|set_dclk
)paren
(paren
r_struct
id|fb_info
op_star
)paren
suffix:semicolon
DECL|member|configure_display
r_void
(paren
op_star
id|configure_display
)paren
(paren
r_struct
id|fb_info
op_star
)paren
suffix:semicolon
DECL|member|blank_display
r_int
(paren
op_star
id|blank_display
)paren
(paren
r_struct
id|fb_info
op_star
comma
r_int
id|blank_mode
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|geodefb_par
r_struct
id|geodefb_par
(brace
DECL|member|enable_crt
r_int
id|enable_crt
suffix:semicolon
DECL|member|panel_x
r_int
id|panel_x
suffix:semicolon
multiline_comment|/* dimensions of an attached flat panel, non-zero =&gt; enable panel */
DECL|member|panel_y
r_int
id|panel_y
suffix:semicolon
DECL|member|vid_dev
r_struct
id|pci_dev
op_star
id|vid_dev
suffix:semicolon
DECL|member|dc_regs
r_void
id|__iomem
op_star
id|dc_regs
suffix:semicolon
DECL|member|vid_regs
r_void
id|__iomem
op_star
id|vid_regs
suffix:semicolon
DECL|member|dc_ops
r_struct
id|geode_dc_ops
op_star
id|dc_ops
suffix:semicolon
DECL|member|vid_ops
r_struct
id|geode_vid_ops
op_star
id|vid_ops
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* !__GEODEFB_H__ */
eof
