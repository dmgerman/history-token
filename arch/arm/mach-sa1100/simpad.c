multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/simpad.c&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/string.h&gt; 
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/serial_sa1100.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &quot;generic.h&quot;
DECL|variable|cs3_shadow
r_int
id|cs3_shadow
suffix:semicolon
DECL|function|get_cs3_shadow
r_int
id|get_cs3_shadow
c_func
(paren
)paren
(brace
r_return
id|cs3_shadow
suffix:semicolon
)brace
DECL|function|set_cs3_bit
r_void
id|set_cs3_bit
c_func
(paren
r_int
id|value
)paren
(brace
id|cs3_shadow
op_or_assign
id|value
suffix:semicolon
op_star
(paren
id|CS3BUSTYPE
op_star
)paren
(paren
id|CS3_BASE
)paren
op_assign
id|cs3_shadow
suffix:semicolon
)brace
DECL|function|clear_cs3_bit
r_void
id|clear_cs3_bit
c_func
(paren
r_int
id|value
)paren
(brace
id|cs3_shadow
op_and_assign
op_complement
id|value
suffix:semicolon
op_star
(paren
id|CS3BUSTYPE
op_star
)paren
(paren
id|CS3_BASE
)paren
op_assign
id|cs3_shadow
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|fixup_simpad
id|fixup_simpad
c_func
(paren
r_struct
id|machine_desc
op_star
id|desc
comma
r_struct
id|tag
op_star
id|tags
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
macro_line|#ifdef CONFIG_SA1100_SIMPAD_DRAM_64MB /* DRAM */
id|SET_BANK
c_func
(paren
l_int|0
comma
l_int|0xc0000000
comma
l_int|64
op_star
l_int|1024
op_star
l_int|1024
)paren
suffix:semicolon
macro_line|#else
id|SET_BANK
c_func
(paren
l_int|0
comma
l_int|0xc0000000
comma
l_int|32
op_star
l_int|1024
op_star
l_int|1024
)paren
suffix:semicolon
macro_line|#endif
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
id|__phys_to_virt
c_func
(paren
l_int|0xc0800000
)paren
comma
l_int|4
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
id|simpad_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual&t;physical    length&t;domain&t;   r  w  c  b */
(brace
l_int|0xf2800000
comma
l_int|0x4b800000
comma
l_int|0x00800000
comma
id|DOMAIN_IO
comma
l_int|0
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
l_int|0xf1000000
comma
l_int|0x18000000
comma
l_int|0x00100000
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* Paules CS3, write only */
id|LAST_DESC
)brace
suffix:semicolon
DECL|function|simpad_uart_pm
r_static
r_void
id|simpad_uart_pm
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
id|u_int
id|state
comma
id|u_int
id|oldstate
)paren
(brace
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
(paren
id|u_int
)paren
op_amp
id|Ser1UTCR0
)paren
(brace
r_if
c_cond
(paren
id|state
)paren
id|clear_cs3_bit
c_func
(paren
id|RS232_ON
)paren
suffix:semicolon
r_else
id|set_cs3_bit
c_func
(paren
id|RS232_ON
)paren
suffix:semicolon
)brace
)brace
DECL|variable|__initdata
r_static
r_struct
id|sa1100_port_fns
id|simpad_port_fns
id|__initdata
op_assign
(brace
id|pm
suffix:colon
id|simpad_uart_pm
comma
)brace
suffix:semicolon
DECL|function|simpad_map_io
r_static
r_void
id|__init
id|simpad_map_io
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
id|simpad_io_desc
)paren
suffix:semicolon
id|PSPR
op_assign
l_int|0xc0008000
suffix:semicolon
id|GPDR
op_and_assign
op_complement
id|GPIO_GPIO0
suffix:semicolon
id|cs3_shadow
op_assign
(paren
id|EN1
op_or
id|EN0
op_or
id|LED2_ON
op_or
id|DISPLAY_ON
op_or
id|RS232_ON
op_or
id|ENABLE_5V
op_or
id|RESET_SIMCARD
)paren
suffix:semicolon
op_star
(paren
id|CS3BUSTYPE
op_star
)paren
(paren
id|CS3_BASE
)paren
op_assign
id|cs3_shadow
suffix:semicolon
singleline_comment|//It is only possible to register 3 UART in serial_sa1100.c
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
id|set_irq_type
c_func
(paren
id|IRQ_GPIO_UCB1300_IRQ
comma
id|IRQT_RISING
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PROC_FS
DECL|variable|name
r_static
r_char
op_star
id|name
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|function|proc_cs3_read
r_static
r_int
id|proc_cs3_read
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_char
op_star
id|p
op_assign
id|page
suffix:semicolon
r_int
id|len
comma
id|i
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;Chipselect3 : %x&bslash;n&quot;
comma
id|cs3_shadow
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
l_int|15
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|cs3_shadow
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
(brace
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;%s&bslash;t: TRUE &bslash;n&quot;
comma
id|name
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_else
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;%s&bslash;t: FALSE &bslash;n&quot;
comma
id|name
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|len
op_assign
(paren
id|p
op_minus
id|page
)paren
op_minus
id|off
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|len
op_assign
l_int|0
suffix:semicolon
op_star
id|eof
op_assign
(paren
id|len
op_le
id|count
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
op_star
id|start
op_assign
id|page
op_plus
id|off
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|variable|proc_cs3
r_static
r_struct
id|proc_dir_entry
op_star
id|proc_cs3
suffix:semicolon
DECL|function|cs3_init
r_static
r_int
id|__init
id|cs3_init
c_func
(paren
r_void
)paren
(brace
id|proc_cs3
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;cs3&quot;
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|proc_cs3
)paren
id|proc_cs3-&gt;read_proc
op_assign
id|proc_cs3_read
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cs3_exit
r_static
r_int
id|__exit
id|cs3_exit
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|proc_cs3
)paren
id|remove_proc_entry
c_func
(paren
l_string|&quot;cs3&quot;
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|cs3_init
id|__initcall
c_func
(paren
id|cs3_init
)paren
suffix:semicolon
macro_line|#endif 
singleline_comment|// CONFIG_PROC_FS
id|MACHINE_START
c_func
(paren
id|SIMPAD
comma
l_string|&quot;Simpad&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Juergen Messerer&quot;
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
id|FIXUP
c_func
(paren
id|fixup_simpad
)paren
id|MAPIO
c_func
(paren
id|simpad_map_io
)paren
id|INITIRQ
c_func
(paren
id|sa1100_init_irq
)paren
id|MACHINE_END
eof
