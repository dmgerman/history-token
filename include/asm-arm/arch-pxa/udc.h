multiline_comment|/*&n; * linux/include/asm-arm/arch-pxa/udc.h&n; *&n; * This supports machine-specific differences in how the PXA2xx&n; * USB Device Controller (UDC) is wired.&n; *&n; * It is set in linux/arch/arm/mach-pxa/&lt;machine&gt;.c and used in&n; * the probe routine of linux/drivers/usb/gadget/pxa2xx_udc.c&n; */
DECL|struct|pxa2xx_udc_mach_info
r_struct
id|pxa2xx_udc_mach_info
(brace
DECL|member|udc_is_connected
r_int
(paren
op_star
id|udc_is_connected
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* do we see host? */
DECL|member|udc_command
r_void
(paren
op_star
id|udc_command
)paren
(paren
r_int
id|cmd
)paren
suffix:semicolon
DECL|macro|PXA2XX_UDC_CMD_CONNECT
mdefine_line|#define&t;PXA2XX_UDC_CMD_CONNECT&t;&t;0&t;/* let host see us */
DECL|macro|PXA2XX_UDC_CMD_DISCONNECT
mdefine_line|#define&t;PXA2XX_UDC_CMD_DISCONNECT&t;1&t;/* so host won&squot;t see us */
)brace
suffix:semicolon
r_extern
r_void
id|pxa_set_udc_info
c_func
(paren
r_struct
id|pxa2xx_udc_mach_info
op_star
id|info
)paren
suffix:semicolon
eof
