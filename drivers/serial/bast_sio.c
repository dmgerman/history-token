macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/serial.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/arch/map.h&gt;
macro_line|#include &lt;asm/arch/irqs.h&gt;
macro_line|#include &lt;asm/arch/bast-map.h&gt;
macro_line|#include &lt;asm/arch/bast-irq.h&gt;
DECL|function|serial_bast_register
r_static
r_int
id|__init
id|serial_bast_register
c_func
(paren
r_int
r_int
id|port
comma
r_int
r_int
id|irq
)paren
(brace
r_struct
id|serial_struct
id|serial_req
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;BAST: SuperIO serial (%08lx,%d)&bslash;n&quot;
comma
id|port
comma
id|irq
)paren
suffix:semicolon
macro_line|#endif
id|serial_req.flags
op_assign
id|UPF_AUTOPROBE
op_or
id|UPF_RESOURCES
op_or
id|UPF_SHARE_IRQ
suffix:semicolon
id|serial_req.baud_base
op_assign
id|BASE_BAUD
suffix:semicolon
id|serial_req.irq
op_assign
id|irq
suffix:semicolon
id|serial_req.io_type
op_assign
id|UPIO_MEM
suffix:semicolon
id|serial_req.iomap_base
op_assign
id|port
suffix:semicolon
id|serial_req.iomem_base
op_assign
id|ioremap
c_func
(paren
id|port
comma
l_int|0x10
)paren
suffix:semicolon
id|serial_req.iomem_reg_shift
op_assign
l_int|0
suffix:semicolon
r_return
id|register_serial
c_func
(paren
op_amp
id|serial_req
)paren
suffix:semicolon
)brace
DECL|macro|SERIAL_BASE
mdefine_line|#define SERIAL_BASE (S3C2410_CS2 + BAST_PA_SUPERIO)
DECL|function|serial_bast_init
r_static
r_int
id|__init
id|serial_bast_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|machine_is_bast
c_func
(paren
)paren
)paren
(brace
id|serial_bast_register
c_func
(paren
id|SERIAL_BASE
op_plus
l_int|0x2f8
comma
id|IRQ_PCSERIAL1
)paren
suffix:semicolon
id|serial_bast_register
c_func
(paren
id|SERIAL_BASE
op_plus
l_int|0x3f8
comma
id|IRQ_PCSERIAL2
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|serial_bast_exit
r_static
r_void
id|__exit
id|serial_bast_exit
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* todo -&gt; remove both our ports */
)brace
DECL|variable|serial_bast_init
id|module_init
c_func
(paren
id|serial_bast_init
)paren
suffix:semicolon
DECL|variable|serial_bast_exit
id|module_exit
c_func
(paren
id|serial_bast_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Ben Dooks, ben@simtec.co.uk&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;BAST Onboard Serial setup&quot;
)paren
suffix:semicolon
eof
