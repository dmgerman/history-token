multiline_comment|/*&n; * update the core module control register.&n; */
r_void
id|cm_control
c_func
(paren
id|u32
comma
id|u32
)paren
suffix:semicolon
DECL|macro|CM_CTRL_LED
mdefine_line|#define CM_CTRL_LED&t;&t;&t;(1 &lt;&lt; 0)
DECL|macro|CM_CTRL_nMBDET
mdefine_line|#define CM_CTRL_nMBDET&t;&t;&t;(1 &lt;&lt; 1)
DECL|macro|CM_CTRL_REMAP
mdefine_line|#define CM_CTRL_REMAP&t;&t;&t;(1 &lt;&lt; 2)
DECL|macro|CM_CTRL_RESET
mdefine_line|#define CM_CTRL_RESET&t;&t;&t;(1 &lt;&lt; 3)
multiline_comment|/*&n; * Integrator/AP,PP2 specific&n; */
DECL|macro|CM_CTRL_HIGHVECTORS
mdefine_line|#define CM_CTRL_HIGHVECTORS&t;&t;(1 &lt;&lt; 4)
DECL|macro|CM_CTRL_BIGENDIAN
mdefine_line|#define CM_CTRL_BIGENDIAN&t;&t;(1 &lt;&lt; 5)
DECL|macro|CM_CTRL_FASTBUS
mdefine_line|#define CM_CTRL_FASTBUS&t;&t;&t;(1 &lt;&lt; 6)
DECL|macro|CM_CTRL_SYNC
mdefine_line|#define CM_CTRL_SYNC&t;&t;&t;(1 &lt;&lt; 7)
multiline_comment|/*&n; * ARM926/946/966 Integrator/CP specific&n; */
DECL|macro|CM_CTRL_LCDBIASEN
mdefine_line|#define CM_CTRL_LCDBIASEN&t;&t;(1 &lt;&lt; 8)
DECL|macro|CM_CTRL_LCDBIASUP
mdefine_line|#define CM_CTRL_LCDBIASUP&t;&t;(1 &lt;&lt; 9)
DECL|macro|CM_CTRL_LCDBIASDN
mdefine_line|#define CM_CTRL_LCDBIASDN&t;&t;(1 &lt;&lt; 10)
DECL|macro|CM_CTRL_LCDMUXSEL_MASK
mdefine_line|#define CM_CTRL_LCDMUXSEL_MASK&t;&t;(7 &lt;&lt; 11)
DECL|macro|CM_CTRL_LCDMUXSEL_GENLCD
mdefine_line|#define CM_CTRL_LCDMUXSEL_GENLCD&t;(1 &lt;&lt; 11)
DECL|macro|CM_CTRL_LCDMUXSEL_SHARPLCD1
mdefine_line|#define CM_CTRL_LCDMUXSEL_SHARPLCD1&t;(3 &lt;&lt; 11)
DECL|macro|CM_CTRL_LCDMUXSEL_SHARPLCD2
mdefine_line|#define CM_CTRL_LCDMUXSEL_SHARPLCD2&t;(4 &lt;&lt; 11)
DECL|macro|CM_CTRL_LCDMUXSEL_VGA
mdefine_line|#define CM_CTRL_LCDMUXSEL_VGA&t;&t;(7 &lt;&lt; 11)
DECL|macro|CM_CTRL_LCDEN0
mdefine_line|#define CM_CTRL_LCDEN0&t;&t;&t;(1 &lt;&lt; 14)
DECL|macro|CM_CTRL_LCDEN1
mdefine_line|#define CM_CTRL_LCDEN1&t;&t;&t;(1 &lt;&lt; 15)
DECL|macro|CM_CTRL_STATIC1
mdefine_line|#define CM_CTRL_STATIC1&t;&t;&t;(1 &lt;&lt; 16)
DECL|macro|CM_CTRL_STATIC2
mdefine_line|#define CM_CTRL_STATIC2&t;&t;&t;(1 &lt;&lt; 17)
DECL|macro|CM_CTRL_STATIC
mdefine_line|#define CM_CTRL_STATIC&t;&t;&t;(1 &lt;&lt; 18)
DECL|macro|CM_CTRL_n24BITEN
mdefine_line|#define CM_CTRL_n24BITEN&t;&t;(1 &lt;&lt; 19)
DECL|macro|CM_CTRL_EBIWP
mdefine_line|#define CM_CTRL_EBIWP&t;&t;&t;(1 &lt;&lt; 20)
eof
