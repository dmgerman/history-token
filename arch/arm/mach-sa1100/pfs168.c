multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/pfs168.c&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/serial_sa1100.h&gt;
macro_line|#include &quot;generic.h&quot;
DECL|variable|sa1111_resources
r_static
r_struct
id|resource
id|sa1111_resources
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
(brace
dot
id|start
op_assign
l_int|0x40000000
comma
dot
id|end
op_assign
l_int|0x40001fff
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(braket
l_int|1
)braket
op_assign
(brace
dot
id|start
op_assign
id|IRQ_GPIO25
comma
dot
id|end
op_assign
id|IRQ_GPIO25
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|sa1111_dmamask
r_static
id|u64
id|sa1111_dmamask
op_assign
l_int|0xffffffffUL
suffix:semicolon
DECL|variable|sa1111_device
r_static
r_struct
id|platform_device
id|sa1111_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;sa1111&quot;
comma
dot
id|id
op_assign
l_int|0
comma
dot
id|dev
op_assign
(brace
dot
id|dma_mask
op_assign
op_amp
id|sa1111_dmamask
comma
dot
id|coherent_dma_mask
op_assign
l_int|0xffffffff
comma
)brace
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|sa1111_resources
)paren
comma
dot
id|resource
op_assign
id|sa1111_resources
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|platform_device
op_star
id|devices
(braket
)braket
id|__initdata
op_assign
(brace
op_amp
id|sa1111_device
comma
)brace
suffix:semicolon
DECL|function|pfs168_init
r_static
r_int
id|__init
id|pfs168_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|machine_is_pfs168
c_func
(paren
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/*&n;&t; * Ensure that the memory bus request/grant signals are setup,&n;&t; * and the grant is held in its inactive state&n;&t; */
id|sa1110_mb_disable
c_func
(paren
)paren
suffix:semicolon
r_return
id|platform_add_devices
c_func
(paren
id|devices
comma
id|ARRAY_SIZE
c_func
(paren
id|devices
)paren
)paren
suffix:semicolon
)brace
DECL|variable|pfs168_init
id|arch_initcall
c_func
(paren
id|pfs168_init
)paren
suffix:semicolon
DECL|function|pfs168_init_irq
r_static
r_void
id|__init
id|pfs168_init_irq
c_func
(paren
r_void
)paren
(brace
id|sa1100_init_irq
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Need to register these as rising edge interrupts&n;&t; * for standard 16550 serial driver support.&n;&t; */
id|set_GPIO_IRQ_edge
c_func
(paren
id|GPIO_GPIO
c_func
(paren
l_int|19
)paren
comma
id|GPIO_RISING_EDGE
)paren
suffix:semicolon
id|set_GPIO_IRQ_edge
c_func
(paren
id|GPIO_GPIO
c_func
(paren
l_int|20
)paren
comma
id|GPIO_RISING_EDGE
)paren
suffix:semicolon
id|set_GPIO_IRQ_edge
c_func
(paren
id|GPIO_GPIO
c_func
(paren
l_int|25
)paren
comma
id|GPIO_RISING_EDGE
)paren
suffix:semicolon
id|set_GPIO_IRQ_edge
c_func
(paren
id|GPIO_UCB1300_IRQ
comma
id|GPIO_RISING_EDGE
)paren
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|pfs168_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual     physical    length      type */
(brace
l_int|0xf0000000
comma
l_int|0x10000000
comma
l_int|0x00001000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* 16C752 DUART port A (COM5) */
(brace
l_int|0xf0001000
comma
l_int|0x10800000
comma
l_int|0x00001000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* 16C752 DUART port B (COM6) */
(brace
l_int|0xf0002000
comma
l_int|0x11000000
comma
l_int|0x00001000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* COM1 RTS control (SYSC1RTS) */
(brace
l_int|0xf0003000
comma
l_int|0x11400000
comma
l_int|0x00001000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* Status LED control (SYSLED) */
(brace
l_int|0xf0004000
comma
l_int|0x11800000
comma
l_int|0x00001000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* DTMF code read (SYSDTMF) */
(brace
l_int|0xf0005000
comma
l_int|0x11c00000
comma
l_int|0x00001000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* LCD configure, enable (SYSLCDDE) */
(brace
l_int|0xf0006000
comma
l_int|0x12000000
comma
l_int|0x00001000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* COM1 DSR and motion sense (SYSC1DSR) */
(brace
l_int|0xf0007000
comma
l_int|0x12800000
comma
l_int|0x00001000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* COM3 xmit enable (SYSC3TEN) */
(brace
l_int|0xf0008000
comma
l_int|0x13000000
comma
l_int|0x00001000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* Control register A (SYSCTLA) */
(brace
l_int|0xf0009000
comma
l_int|0x13800000
comma
l_int|0x00001000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* Control register B (SYSCTLB) */
(brace
l_int|0xf000a000
comma
l_int|0x18000000
comma
l_int|0x00001000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* SMC91C96 */
(brace
l_int|0xf2800000
comma
l_int|0x4b800000
comma
l_int|0x00800000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* MQ200 */
(brace
l_int|0xf4000000
comma
l_int|0x40000000
comma
l_int|0x00100000
comma
id|MT_DEVICE
)brace
multiline_comment|/* SA-1111 */
)brace
suffix:semicolon
DECL|function|pfs168_map_io
r_static
r_void
id|__init
id|pfs168_map_io
c_func
(paren
r_void
)paren
(brace
id|sa1100_map_io
c_func
(paren
)paren
suffix:semicolon
id|iotable_init
c_func
(paren
id|pfs168_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|pfs168_io_desc
)paren
)paren
suffix:semicolon
id|sa1100_register_uart
c_func
(paren
l_int|0
comma
l_int|3
)paren
suffix:semicolon
id|sa1100_register_uart
c_func
(paren
l_int|1
comma
l_int|1
)paren
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|PFS168
comma
l_string|&quot;Tulsa&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0xc0000000
comma
l_int|0x80000000
comma
l_int|0xf8000000
)paren
id|BOOT_PARAMS
c_func
(paren
l_int|0xc0000100
)paren
id|MAPIO
c_func
(paren
id|pfs168_map_io
)paren
id|INITIRQ
c_func
(paren
id|pfs168_init_irq
)paren
id|MACHINE_END
eof
