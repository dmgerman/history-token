multiline_comment|/*&n; * Zalon 53c7xx device driver.&n; * By Richard Hirst (rhirst@linuxcare.com)&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;../parisc/gsc.h&quot;
macro_line|#include &quot;ncr53c8xx.h&quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Richard Hirst&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Bluefish/Zalon 720 SCSI Driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|macro|GSC_SCSI_ZALON_OFFSET
mdefine_line|#define GSC_SCSI_ZALON_OFFSET 0x800
DECL|macro|IO_MODULE_EIM
mdefine_line|#define IO_MODULE_EIM&t;&t;(1*4)
DECL|macro|IO_MODULE_DC_ADATA
mdefine_line|#define IO_MODULE_DC_ADATA&t;(2*4)
DECL|macro|IO_MODULE_II_CDATA
mdefine_line|#define IO_MODULE_II_CDATA&t;(3*4)
DECL|macro|IO_MODULE_IO_COMMAND
mdefine_line|#define IO_MODULE_IO_COMMAND&t;(12*4)
DECL|macro|IO_MODULE_IO_STATUS
mdefine_line|#define IO_MODULE_IO_STATUS&t;(13*4)
DECL|macro|IOSTATUS_RY
mdefine_line|#define IOSTATUS_RY&t;&t;0x40
DECL|macro|IOSTATUS_FE
mdefine_line|#define IOSTATUS_FE&t;&t;0x80
DECL|macro|IOIIDATA_SMINT5L
mdefine_line|#define IOIIDATA_SMINT5L&t;0x40000000
DECL|macro|IOIIDATA_MINT5EN
mdefine_line|#define IOIIDATA_MINT5EN&t;0x20000000
DECL|macro|IOIIDATA_PACKEN
mdefine_line|#define IOIIDATA_PACKEN&t;&t;0x10000000
DECL|macro|IOIIDATA_PREFETCHEN
mdefine_line|#define IOIIDATA_PREFETCHEN&t;0x08000000
DECL|macro|IOIIDATA_IOII
mdefine_line|#define IOIIDATA_IOII&t;&t;0x00000020
DECL|macro|CMD_RESET
mdefine_line|#define CMD_RESET&t;&t;5
DECL|variable|__initdata
r_static
r_struct
id|ncr_chip
id|zalon720_chip
id|__initdata
op_assign
(brace
dot
id|revision_id
op_assign
l_int|0x0f
comma
dot
id|burst_max
op_assign
l_int|3
comma
dot
id|offset_max
op_assign
l_int|8
comma
dot
id|nr_divisor
op_assign
l_int|4
comma
dot
id|features
op_assign
id|FE_WIDE
op_or
id|FE_DIFF
op_or
id|FE_EHP
op_or
id|FE_MUX
op_or
id|FE_EA
comma
)brace
suffix:semicolon
macro_line|#if 0
multiline_comment|/* FIXME:&n; * Is this function dead code? or is someone planning on using it in the&n; * future.  The clock = (int) pdc_result[16] does not look correct to&n; * me ... I think it should be iodc_data[16].  Since this cause a compile&n; * error with the new encapsulated PDC, I&squot;m not compiling in this function.&n; * - RB&n; */
multiline_comment|/* poke SCSI clock out of iodc data */
r_static
id|u8
id|iodc_data
(braket
l_int|32
)braket
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|64
)paren
)paren
)paren
suffix:semicolon
r_static
r_int
r_int
id|pdc_result
(braket
l_int|32
)braket
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|16
)paren
)paren
)paren
op_assign
initialization_block
suffix:semicolon
r_static
r_int
id|lasi_scsi_clock
c_func
(paren
r_void
op_star
id|hpa
comma
r_int
id|defaultclock
)paren
(brace
r_int
id|clock
comma
id|status
suffix:semicolon
id|status
op_assign
id|pdc_iodc_read
c_func
(paren
op_amp
id|pdc_result
comma
id|hpa
comma
l_int|0
comma
op_amp
id|iodc_data
comma
l_int|32
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
id|PDC_RET_OK
)paren
(brace
id|clock
op_assign
(paren
r_int
)paren
id|pdc_result
(braket
l_int|16
)braket
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: pdc_iodc_read returned %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|status
)paren
suffix:semicolon
id|clock
op_assign
id|defaultclock
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: SCSI clock %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|clock
)paren
suffix:semicolon
r_return
id|clock
suffix:semicolon
)brace
macro_line|#endif
DECL|variable|zalon7xx_template
r_static
r_struct
id|scsi_host_template
id|zalon7xx_template
op_assign
(brace
dot
id|module
op_assign
id|THIS_MODULE
comma
dot
id|proc_name
op_assign
l_string|&quot;zalon7xx&quot;
comma
)brace
suffix:semicolon
r_static
r_int
id|__init
DECL|function|zalon_probe
id|zalon_probe
c_func
(paren
r_struct
id|parisc_device
op_star
id|dev
)paren
(brace
r_struct
id|gsc_irq
id|gsc_irq
suffix:semicolon
id|u32
id|zalon_vers
suffix:semicolon
r_int
id|irq
comma
id|error
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_int
r_int
id|zalon
op_assign
id|dev-&gt;hpa
suffix:semicolon
r_int
r_int
id|io_port
op_assign
id|zalon
op_plus
id|GSC_SCSI_ZALON_OFFSET
suffix:semicolon
r_static
r_int
id|unit
op_assign
l_int|0
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
r_struct
id|ncr_device
id|device
suffix:semicolon
id|__raw_writel
c_func
(paren
id|CMD_RESET
comma
id|zalon
op_plus
id|IO_MODULE_IO_COMMAND
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|__raw_readl
c_func
(paren
id|zalon
op_plus
id|IO_MODULE_IO_STATUS
)paren
op_amp
id|IOSTATUS_RY
)paren
)paren
suffix:semicolon
id|__raw_writel
c_func
(paren
id|IOIIDATA_MINT5EN
op_or
id|IOIIDATA_PACKEN
op_or
id|IOIIDATA_PREFETCHEN
comma
id|zalon
op_plus
id|IO_MODULE_II_CDATA
)paren
suffix:semicolon
multiline_comment|/* XXX: Save the Zalon version for bug workarounds? */
id|zalon_vers
op_assign
id|__raw_readl
c_func
(paren
id|dev-&gt;hpa
op_plus
id|IO_MODULE_II_CDATA
)paren
op_amp
l_int|0x07000000
suffix:semicolon
id|zalon_vers
op_rshift_assign
l_int|24
suffix:semicolon
multiline_comment|/* Setup the interrupts first.&n;&t;** Later on request_irq() will register the handler.&n;&t;*/
id|irq
op_assign
id|gsc_alloc_irq
c_func
(paren
op_amp
id|gsc_irq
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: Zalon vers field is 0x%x, IRQ %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|zalon_vers
comma
id|irq
)paren
suffix:semicolon
id|__raw_writel
c_func
(paren
id|gsc_irq.txn_addr
op_or
id|gsc_irq.txn_data
comma
id|dev-&gt;hpa
op_plus
id|IO_MODULE_EIM
)paren
suffix:semicolon
r_if
c_cond
(paren
id|zalon_vers
op_eq
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: Zalon 1.1 or earlier&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|device
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ncr_device
)paren
)paren
suffix:semicolon
multiline_comment|/* The following three are needed before any other access. */
id|writeb
c_func
(paren
l_int|0x20
comma
id|io_port
op_plus
l_int|0x38
)paren
suffix:semicolon
multiline_comment|/* DCNTL_REG,  EA  */
id|writeb
c_func
(paren
l_int|0x04
comma
id|io_port
op_plus
l_int|0x1b
)paren
suffix:semicolon
multiline_comment|/* CTEST0_REG, EHP */
id|writeb
c_func
(paren
l_int|0x80
comma
id|io_port
op_plus
l_int|0x22
)paren
suffix:semicolon
multiline_comment|/* CTEST4_REG, MUX */
multiline_comment|/* Initialise ncr_device structure with items required by ncr_attach. */
id|device.chip
op_assign
id|zalon720_chip
suffix:semicolon
id|device.host_id
op_assign
l_int|7
suffix:semicolon
id|device.dev
op_assign
op_amp
id|dev-&gt;dev
suffix:semicolon
id|device.slot.base
op_assign
(paren
id|u_long
)paren
id|io_port
suffix:semicolon
id|device.slot.base_c
op_assign
(paren
id|u_long
)paren
id|io_port
suffix:semicolon
id|device.slot.irq
op_assign
id|irq
suffix:semicolon
id|device.differential
op_assign
l_int|2
suffix:semicolon
id|host
op_assign
id|ncr_attach
c_func
(paren
op_amp
id|zalon7xx_template
comma
id|unit
comma
op_amp
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|host
)paren
r_goto
id|fail
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|irq
comma
id|ncr53c8xx_intr
comma
id|SA_SHIRQ
comma
id|dev-&gt;dev.bus_id
comma
id|host
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: irq problem with %d, detaching&bslash;n &quot;
comma
id|dev-&gt;dev.bus_id
comma
id|irq
)paren
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
id|unit
op_increment
suffix:semicolon
id|dev_set_drvdata
c_func
(paren
op_amp
id|dev-&gt;dev
comma
id|host
)paren
suffix:semicolon
id|error
op_assign
id|scsi_add_host
c_func
(paren
id|host
comma
op_amp
id|dev-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|fail_free_irq
suffix:semicolon
id|scsi_scan_host
c_func
(paren
id|host
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|fail_free_irq
suffix:colon
id|free_irq
c_func
(paren
id|irq
comma
id|host
)paren
suffix:semicolon
id|fail
suffix:colon
id|ncr53c8xx_release
c_func
(paren
id|host
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|variable|zalon_tbl
r_static
r_struct
id|parisc_device_id
id|zalon_tbl
(braket
)braket
op_assign
(brace
(brace
id|HPHW_A_DMA
comma
id|HVERSION_REV_ANY_ID
comma
id|HVERSION_ANY_ID
comma
l_int|0x00089
)brace
comma
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|parisc
comma
id|zalon_tbl
)paren
suffix:semicolon
DECL|function|zalon_remove
r_static
r_int
id|__exit
id|zalon_remove
c_func
(paren
r_struct
id|parisc_device
op_star
id|dev
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|host
op_assign
id|dev_get_drvdata
c_func
(paren
op_amp
id|dev-&gt;dev
)paren
suffix:semicolon
r_int
id|irq
op_assign
id|host-&gt;irq
suffix:semicolon
id|scsi_remove_host
c_func
(paren
id|host
)paren
suffix:semicolon
id|ncr53c8xx_release
c_func
(paren
id|host
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|irq
comma
id|host
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|zalon_driver
r_static
r_struct
id|parisc_driver
id|zalon_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;GSC SCSI (Zalon)&quot;
comma
dot
id|id_table
op_assign
id|zalon_tbl
comma
dot
id|probe
op_assign
id|zalon_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|zalon_remove
)paren
comma
)brace
suffix:semicolon
DECL|function|zalon7xx_init
r_static
r_int
id|__init
id|zalon7xx_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
op_assign
id|ncr53c8xx_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|ret
op_assign
id|register_parisc_driver
c_func
(paren
op_amp
id|zalon_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|ncr53c8xx_exit
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|zalon7xx_exit
r_static
r_void
id|__exit
id|zalon7xx_exit
c_func
(paren
r_void
)paren
(brace
id|unregister_parisc_driver
c_func
(paren
op_amp
id|zalon_driver
)paren
suffix:semicolon
)brace
DECL|variable|zalon7xx_init
id|module_init
c_func
(paren
id|zalon7xx_init
)paren
suffix:semicolon
DECL|variable|zalon7xx_exit
id|module_exit
c_func
(paren
id|zalon7xx_exit
)paren
suffix:semicolon
eof
