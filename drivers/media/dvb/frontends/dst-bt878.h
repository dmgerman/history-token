multiline_comment|/*&n; * dst-bt878.h: part of the DST driver for the TwinHan DST Frontend&n; *&n; * Copyright (C) 2003 Jamie Honan&n; */
DECL|struct|dst_gpio_enable
r_struct
id|dst_gpio_enable
(brace
DECL|member|mask
id|u32
id|mask
suffix:semicolon
DECL|member|enable
id|u32
id|enable
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dst_gpio_output
r_struct
id|dst_gpio_output
(brace
DECL|member|mask
id|u32
id|mask
suffix:semicolon
DECL|member|highvals
id|u32
id|highvals
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dst_gpio_read
r_struct
id|dst_gpio_read
(brace
DECL|member|value
r_int
r_int
id|value
suffix:semicolon
)brace
suffix:semicolon
DECL|union|dst_gpio_packet
r_union
id|dst_gpio_packet
(brace
DECL|member|enb
r_struct
id|dst_gpio_enable
id|enb
suffix:semicolon
DECL|member|outp
r_struct
id|dst_gpio_output
id|outp
suffix:semicolon
DECL|member|rd
r_struct
id|dst_gpio_read
id|rd
suffix:semicolon
DECL|member|psize
r_int
id|psize
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|DST_IG_ENABLE
mdefine_line|#define DST_IG_ENABLE&t;0
DECL|macro|DST_IG_WRITE
mdefine_line|#define DST_IG_WRITE&t;1
DECL|macro|DST_IG_READ
mdefine_line|#define DST_IG_READ&t;2
DECL|macro|DST_IG_TS
mdefine_line|#define DST_IG_TS       3
r_struct
id|bt878
suffix:semicolon
r_int
id|bt878_device_control
c_func
(paren
r_struct
id|bt878
op_star
id|bt
comma
r_int
r_int
id|cmd
comma
r_union
id|dst_gpio_packet
op_star
id|mp
)paren
suffix:semicolon
r_struct
id|bt878
op_star
id|bt878_find_by_dvb_adap
c_func
(paren
r_struct
id|dvb_adapter
op_star
id|adap
)paren
suffix:semicolon
eof
