multiline_comment|/*&n; * Zalon 53c7xx device driver.&n; * By Richard Hirst (rhirst@linuxcare.com)&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;../parisc/gsc.h&quot;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
multiline_comment|/*&n; * **      Define the BSD style u_int32 and u_int64 type.&n; * **      Are in fact u_int32_t and u_int64_t :-)&n; * */
DECL|typedef|u_int32
r_typedef
id|u32
id|u_int32
suffix:semicolon
DECL|typedef|u_int64
r_typedef
id|u64
id|u_int64
suffix:semicolon
DECL|typedef|vm_offset_t
r_typedef
id|u_long
id|vm_offset_t
suffix:semicolon
macro_line|#include &quot;zalon.h&quot;
multiline_comment|/* hosts_* are kluges to pass info between the zalon7xx_detected()&n;** and the register_parisc_driver() callbacks.&n;*/
DECL|variable|hosts_tptr
r_static
id|Scsi_Host_Template
op_star
id|hosts_tptr
suffix:semicolon
DECL|variable|hosts_used
r_static
r_int
id|hosts_used
op_assign
l_int|0
suffix:semicolon
DECL|variable|zalon_id
r_static
r_int
id|zalon_id
op_assign
l_int|0
suffix:semicolon
r_extern
r_int
id|zalon_attach
c_func
(paren
id|Scsi_Host_Template
op_star
id|tpnt
comma
r_int
r_int
id|base_addr
comma
r_struct
id|parisc_device
op_star
id|dev
comma
r_int
id|irq_vector
comma
r_int
id|unit
)paren
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
r_static
r_int
id|__init
DECL|function|zalon_scsi_callback
id|zalon_scsi_callback
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
suffix:semicolon
r_int
r_int
id|zalon
op_assign
id|dev-&gt;hpa
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
multiline_comment|/*&n;&t;**  zalon_attach: returns -1 on failure, 0 on success&n;&t;*/
id|hosts_used
op_assign
id|zalon_attach
c_func
(paren
id|hosts_tptr
comma
id|dev-&gt;hpa
op_plus
id|GSC_SCSI_ZALON_OFFSET
comma
id|dev
comma
id|irq
comma
id|zalon_id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hosts_used
op_eq
l_int|0
)paren
id|zalon_id
op_increment
suffix:semicolon
id|hosts_used
op_assign
(paren
id|hosts_used
op_eq
l_int|0
)paren
suffix:semicolon
r_return
(paren
id|hosts_used
op_eq
l_int|0
)paren
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
id|zalon_scsi_callback
comma
)brace
suffix:semicolon
DECL|function|zalon7xx_detect
r_int
id|zalon7xx_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|tpnt
)paren
(brace
multiline_comment|/* &quot;pass&quot; the parameter to the callback functions */
id|hosts_tptr
op_assign
id|tpnt
suffix:semicolon
id|hosts_used
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* claim all zalon cards. */
id|register_parisc_driver
c_func
(paren
op_amp
id|zalon_driver
)paren
suffix:semicolon
multiline_comment|/* Check if any callbacks actually found/claimed anything. */
r_return
(paren
id|hosts_used
op_ne
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#ifdef MODULE
r_extern
r_int
id|ncr53c8xx_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
suffix:semicolon
DECL|function|zalon7xx_release
r_int
id|zalon7xx_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
(brace
id|ncr53c8xx_release
c_func
(paren
id|host
)paren
suffix:semicolon
id|unregister_parisc_driver
c_func
(paren
op_amp
id|zalon_driver
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
eof
