DECL|macro|IMPD1_OSC1
mdefine_line|#define IMPD1_OSC1&t;0x00
DECL|macro|IMPD1_OSC2
mdefine_line|#define IMPD1_OSC2&t;0x04
DECL|macro|IMPD1_LOCK
mdefine_line|#define IMPD1_LOCK&t;0x08
DECL|macro|IMPD1_LEDS
mdefine_line|#define IMPD1_LEDS&t;0x0c
DECL|macro|IMPD1_INT
mdefine_line|#define IMPD1_INT&t;0x10
DECL|macro|IMPD1_SW
mdefine_line|#define IMPD1_SW&t;0x14
DECL|macro|IMPD1_CTRL
mdefine_line|#define IMPD1_CTRL&t;0x18
DECL|macro|IMPD1_CTRL_DISP_LCD
mdefine_line|#define IMPD1_CTRL_DISP_LCD&t;(0 &lt;&lt; 0)
DECL|macro|IMPD1_CTRL_DISP_VGA
mdefine_line|#define IMPD1_CTRL_DISP_VGA&t;(1 &lt;&lt; 0)
DECL|macro|IMPD1_CTRL_DISP_LCD1
mdefine_line|#define IMPD1_CTRL_DISP_LCD1&t;(2 &lt;&lt; 0)
DECL|macro|IMPD1_CTRL_DISP_ENABLE
mdefine_line|#define IMPD1_CTRL_DISP_ENABLE&t;(1 &lt;&lt; 2)
DECL|macro|IMPD1_CTRL_DISP_MASK
mdefine_line|#define IMPD1_CTRL_DISP_MASK&t;(7 &lt;&lt; 0)
r_struct
id|device
suffix:semicolon
r_void
id|impd1_set_vco
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|vconr
comma
r_int
r_int
id|period
)paren
suffix:semicolon
r_void
id|impd1_tweak_control
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u32
id|mask
comma
id|u32
id|val
)paren
suffix:semicolon
eof
