multiline_comment|/*&n; * USB device controllers have lots of quirks.  Use these macros in&n; * gadget drivers or other code that needs to deal with them, and which&n; * autoconfigures instead of using early binding to the hardware.&n; *&n; * This could eventually work like the ARM mach_is_*() stuff, driven by&n; * some config file that gets updated as new hardware is supported.&n; *&n; * NOTE:  some of these controller drivers may not be available yet.&n; */
macro_line|#ifdef CONFIG_USB_GADGET_NET2280
DECL|macro|gadget_is_net2280
mdefine_line|#define&t;gadget_is_net2280(g)&t;!strcmp(&quot;net2280&quot;, (g)-&gt;name)
macro_line|#else
DECL|macro|gadget_is_net2280
mdefine_line|#define&t;gadget_is_net2280(g)&t;0
macro_line|#endif
macro_line|#ifdef CONFIG_USB_GADGET_DUMMY_HCD
DECL|macro|gadget_is_dummy
mdefine_line|#define&t;gadget_is_dummy(g)&t;!strcmp(&quot;dummy_udc&quot;, (g)-&gt;name)
macro_line|#else
DECL|macro|gadget_is_dummy
mdefine_line|#define&t;gadget_is_dummy(g)&t;0
macro_line|#endif
macro_line|#ifdef CONFIG_USB_GADGET_PXA2XX
DECL|macro|gadget_is_pxa
mdefine_line|#define&t;gadget_is_pxa(g)&t;!strcmp(&quot;pxa2xx_udc&quot;, (g)-&gt;name)
macro_line|#else
DECL|macro|gadget_is_pxa
mdefine_line|#define&t;gadget_is_pxa(g)&t;0
macro_line|#endif
macro_line|#ifdef CONFIG_USB_GADGET_GOKU
DECL|macro|gadget_is_goku
mdefine_line|#define&t;gadget_is_goku(g)&t;!strcmp(&quot;goku_udc&quot;, (g)-&gt;name)
macro_line|#else
DECL|macro|gadget_is_goku
mdefine_line|#define&t;gadget_is_goku(g)&t;0
macro_line|#endif
macro_line|#ifdef CONFIG_USB_GADGET_SUPERH
DECL|macro|gadget_is_sh
mdefine_line|#define&t;gadget_is_sh(g)&t;&t;!strcmp(&quot;sh_udc&quot;, (g)-&gt;name)
macro_line|#else
DECL|macro|gadget_is_sh
mdefine_line|#define&t;gadget_is_sh(g)&t;&t;0
macro_line|#endif
macro_line|#ifdef CONFIG_USB_GADGET_SA1100
DECL|macro|gadget_is_sa1100
mdefine_line|#define&t;gadget_is_sa1100(g)&t;!strcmp(&quot;sa1100_udc&quot;, (g)-&gt;name)
macro_line|#else
DECL|macro|gadget_is_sa1100
mdefine_line|#define&t;gadget_is_sa1100(g)&t;0
macro_line|#endif
macro_line|#ifdef CONFIG_USB_GADGET_LH7A40X
DECL|macro|gadget_is_lh7a40x
mdefine_line|#define&t;gadget_is_lh7a40x(g)&t;!strcmp(&quot;lh7a40x_udc&quot;, (g)-&gt;name)
macro_line|#else
DECL|macro|gadget_is_lh7a40x
mdefine_line|#define&t;gadget_is_lh7a40x(g)&t;0
macro_line|#endif
macro_line|#ifdef CONFIG_USB_GADGET_MQ11XX
DECL|macro|gadget_is_mq11xx
mdefine_line|#define&t;gadget_is_mq11xx(g)&t;!strcmp(&quot;mq11xx_udc&quot;, (g)-&gt;name)
macro_line|#else
DECL|macro|gadget_is_mq11xx
mdefine_line|#define&t;gadget_is_mq11xx(g)&t;0
macro_line|#endif
macro_line|#ifdef CONFIG_USB_GADGET_OMAP
DECL|macro|gadget_is_omap
mdefine_line|#define&t;gadget_is_omap(g)&t;!strcmp(&quot;omap_udc&quot;, (g)-&gt;name)
macro_line|#else
DECL|macro|gadget_is_omap
mdefine_line|#define&t;gadget_is_omap(g)&t;0
macro_line|#endif
macro_line|#ifdef CONFIG_USB_GADGET_N9604
DECL|macro|gadget_is_n9604
mdefine_line|#define&t;gadget_is_n9604(g)&t;!strcmp(&quot;n9604_udc&quot;, (g)-&gt;name)
macro_line|#else
DECL|macro|gadget_is_n9604
mdefine_line|#define&t;gadget_is_n9604(g)&t;0
macro_line|#endif
macro_line|#ifdef CONFIG_USB_GADGET_PXA27X
DECL|macro|gadget_is_pxa27x
mdefine_line|#define&t;gadget_is_pxa27x(g)&t;!strcmp(&quot;pxa27x_udc&quot;, (g)-&gt;name)
macro_line|#else
DECL|macro|gadget_is_pxa27x
mdefine_line|#define&t;gadget_is_pxa27x(g)&t;0
macro_line|#endif
singleline_comment|// CONFIG_USB_GADGET_AT91RM9200
singleline_comment|// CONFIG_USB_GADGET_SX2
singleline_comment|// CONFIG_USB_GADGET_AU1X00
singleline_comment|// ...
eof
