multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/pfs168.c&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/serial_sa1100.h&gt;
macro_line|#include &quot;generic.h&quot;
macro_line|#include &quot;sa1111.h&quot;
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
multiline_comment|/*&n;&t; * Probe for SA1111.&n;&t; */
id|ret
op_assign
id|sa1111_probe
c_func
(paren
l_int|0x40000000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
multiline_comment|/*&n;&t; * We found it.  Wake the chip up.&n;&t; */
id|sa1111_wake
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The SDRAM configuration of the SA1110 and the SA1111 must&n;&t; * match.  This is very important to ensure that SA1111 accesses&n;&t; * don&squot;t corrupt the SDRAM.  Note that this ungates the SA1111&squot;s&n;&t; * MBGNT signal, so we must have called sa1110_mb_disable()&n;&t; * beforehand.&n;&t; */
id|sa1111_configure_smc
c_func
(paren
l_int|1
comma
id|FExtr
c_func
(paren
id|MDCNFG
comma
id|MDCNFG_SA1110_DRAC0
)paren
comma
id|FExtr
c_func
(paren
id|MDCNFG
comma
id|MDCNFG_SA1110_TDL0
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We only need to turn on DCLK whenever we want to use the&n;&t; * DMA.  It can otherwise be held firmly in the off position.&n;&t; */
id|SKPCR
op_or_assign
id|SKPCR_DCLKEN
suffix:semicolon
multiline_comment|/*&n;&t; * Enable the SA1110 memory bus request and grant signals.&n;&t; */
id|sa1110_mb_enable
c_func
(paren
)paren
suffix:semicolon
id|sa1111_init_irq
c_func
(paren
id|IRQ_GPIO25
)paren
suffix:semicolon
multiline_comment|/* SA1111 IRQ on GPIO 25 */
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pfs168_init
id|__initcall
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
r_static
r_void
id|__init
DECL|function|fixup_pfs168
id|fixup_pfs168
c_func
(paren
r_struct
id|machine_desc
op_star
id|desc
comma
r_struct
id|param_struct
op_star
id|params
comma
r_char
op_star
op_star
id|cmdline
comma
r_struct
id|meminfo
op_star
id|mi
)paren
(brace
id|SET_BANK
c_func
(paren
l_int|0
comma
l_int|0xc0000000
comma
l_int|16
op_star
l_int|1024
op_star
l_int|1024
)paren
suffix:semicolon
id|mi-&gt;nr_banks
op_assign
l_int|1
suffix:semicolon
id|ROOT_DEV
op_assign
id|mk_kdev
c_func
(paren
id|RAMDISK_MAJOR
comma
l_int|0
)paren
suffix:semicolon
id|setup_ramdisk
c_func
(paren
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|8192
)paren
suffix:semicolon
id|setup_initrd
c_func
(paren
l_int|0xc0800000
comma
l_int|3
op_star
l_int|1024
op_star
l_int|1024
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
multiline_comment|/* virtual     physical    length      domain     r  w  c  b */
(brace
l_int|0xe8000000
comma
l_int|0x00000000
comma
l_int|0x02000000
comma
id|DOMAIN_IO
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* Flash bank 0 */
(brace
l_int|0xf0000000
comma
l_int|0x10000000
comma
l_int|0x00001000
comma
id|DOMAIN_IO
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
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
id|DOMAIN_IO
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
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
id|DOMAIN_IO
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
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
id|DOMAIN_IO
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
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
id|DOMAIN_IO
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
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
id|DOMAIN_IO
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
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
id|DOMAIN_IO
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
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
id|DOMAIN_IO
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
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
id|DOMAIN_IO
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
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
id|DOMAIN_IO
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
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
id|DOMAIN_IO
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
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
id|DOMAIN_IO
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
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
id|DOMAIN_IO
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* SA-1111 */
id|LAST_DESC
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
macro_line|#if defined(CONFIG_PFS168_CMDLINE)
id|BOOT_PARAMS
c_func
(paren
l_int|0xc0000100
)paren
macro_line|#endif
id|FIXUP
c_func
(paren
id|fixup_pfs168
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
