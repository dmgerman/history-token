multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000,2002-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#include &lt;asm/sn/iograph.h&gt;
macro_line|#include &lt;asm/sn/invent.h&gt;
macro_line|#include &lt;asm/sn/hcl.h&gt;
macro_line|#include &lt;asm/sn/labelcl.h&gt;
macro_line|#include &lt;asm/sn/sn_private.h&gt;
macro_line|#include &lt;asm/sn/klconfig.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
macro_line|#include &lt;asm/sn/pci/pciio.h&gt;
macro_line|#include &lt;asm/sn/pci/pcibr.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xtalk.h&gt;
macro_line|#include &lt;asm/sn/pci/pcibr_private.h&gt;
macro_line|#include &lt;asm/sn/intr.h&gt;
macro_line|#include &lt;asm/sn/ioerror_handling.h&gt;
macro_line|#include &lt;asm/sn/ioerror.h&gt;
macro_line|#include &lt;asm/sn/sn2/shubio.h&gt;
id|error_state_t
id|error_state_get
c_func
(paren
id|vertex_hdl_t
id|v
)paren
suffix:semicolon
id|error_return_code_t
id|error_state_set
c_func
(paren
id|vertex_hdl_t
id|v
comma
id|error_state_t
id|new_state
)paren
suffix:semicolon
multiline_comment|/*&n; * Get the xtalk provider function pointer for the&n; * specified hub.&n; */
multiline_comment|/*ARGSUSED*/
r_int
DECL|function|hub_xp_error_handler
id|hub_xp_error_handler
c_func
(paren
id|vertex_hdl_t
id|hub_v
comma
id|nasid_t
id|nasid
comma
r_int
id|error_code
comma
id|ioerror_mode_t
id|mode
comma
id|ioerror_t
op_star
id|ioerror
)paren
(brace
multiline_comment|/*REFERENCED*/
id|hubreg_t
id|iio_imem
suffix:semicolon
id|vertex_hdl_t
id|xswitch
suffix:semicolon
id|error_state_t
id|e_state
suffix:semicolon
id|cnodeid_t
id|cnode
suffix:semicolon
multiline_comment|/*&n;&t; * Before walking down to the next level, check if&n;&t; * the I/O link is up. If it&squot;s been disabled by the &n;&t; * hub ii for some reason, we can&squot;t even touch the&n;&t; * widget registers.&n;&t; */
id|iio_imem
op_assign
id|REMOTE_HUB_L
c_func
(paren
id|nasid
comma
id|IIO_IMEM
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|iio_imem
op_amp
(paren
id|IIO_IMEM_B0ESD
op_or
id|IIO_IMEM_W0ESD
)paren
)paren
)paren
(brace
multiline_comment|/* &n;&t;&t; * IIO_IMEM_B0ESD getting set, indicates II shutdown&n;&t;&t; * on HUB0 parts.. Hopefully that&squot;s not true for &n;&t;&t; * Hub1 parts..&n;&t;&t; *&n;&t;&t; *&n;&t;&t; * If either one of them is shut down, can&squot;t&n;&t;&t; * go any further.&n;&t;&t; */
r_return
id|IOERROR_XTALKLEVEL
suffix:semicolon
)brace
multiline_comment|/* Get the error state of the hub */
id|e_state
op_assign
id|error_state_get
c_func
(paren
id|hub_v
)paren
suffix:semicolon
id|cnode
op_assign
id|NASID_TO_COMPACT_NODEID
c_func
(paren
id|nasid
)paren
suffix:semicolon
id|xswitch
op_assign
id|NODEPDA
c_func
(paren
id|cnode
)paren
op_member_access_from_pointer
id|basew_xc
suffix:semicolon
multiline_comment|/* Set the error state of the crosstalk device to that of&n;&t; * hub.&n;&t; */
r_if
c_cond
(paren
id|error_state_set
c_func
(paren
id|xswitch
comma
id|e_state
)paren
op_eq
id|ERROR_RETURN_CODE_CANNOT_SET_STATE
)paren
r_return
id|IOERROR_UNHANDLED
suffix:semicolon
multiline_comment|/* Clean the error state of the hub if we are in the action handling&n;&t; * phase.&n;&t; */
r_if
c_cond
(paren
id|e_state
op_eq
id|ERROR_STATE_ACTION
)paren
(paren
r_void
)paren
id|error_state_set
c_func
(paren
id|hub_v
comma
id|ERROR_STATE_NONE
)paren
suffix:semicolon
multiline_comment|/* hand the error off to the switch or the directly&n;&t; * connected crosstalk device.&n;&t; */
r_return
id|xtalk_error_handler
c_func
(paren
id|xswitch
comma
id|error_code
comma
id|mode
comma
id|ioerror
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; * Check if the widget in error has been enabled for PIO accesses&n; */
r_int
DECL|function|is_widget_pio_enabled
id|is_widget_pio_enabled
c_func
(paren
id|ioerror_t
op_star
id|ioerror
)paren
(brace
id|cnodeid_t
id|src_node
suffix:semicolon
id|nasid_t
id|src_nasid
suffix:semicolon
id|hubreg_t
id|ii_iowa
suffix:semicolon
id|xwidgetnum_t
id|widget
suffix:semicolon
id|iopaddr_t
id|p
suffix:semicolon
multiline_comment|/* Get the node where the PIO error occurred */
id|IOERROR_GETVALUE
c_func
(paren
id|p
comma
id|ioerror
comma
id|srcnode
)paren
suffix:semicolon
id|src_node
op_assign
id|p
suffix:semicolon
r_if
c_cond
(paren
id|src_node
op_eq
id|CNODEID_NONE
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Get the nasid for the cnode */
id|src_nasid
op_assign
id|COMPACT_TO_NASID_NODEID
c_func
(paren
id|src_node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|src_nasid
op_eq
id|INVALID_NASID
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Read the Outbound widget access register for this hub */
id|ii_iowa
op_assign
id|REMOTE_HUB_L
c_func
(paren
id|src_nasid
comma
id|IIO_IOWA
)paren
suffix:semicolon
id|IOERROR_GETVALUE
c_func
(paren
id|p
comma
id|ioerror
comma
id|widgetnum
)paren
suffix:semicolon
id|widget
op_assign
id|p
suffix:semicolon
multiline_comment|/* Check if the PIOs to the widget with PIO error have been&n;&t; * enabled.&n;&t; */
r_if
c_cond
(paren
id|ii_iowa
op_amp
id|IIO_IOWA_WIDGET
c_func
(paren
id|widget
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Hub IO error handling.&n; *&n; *&t;Gets invoked for different types of errors found at the hub. &n; *&t;Typically this includes situations from bus error or due to &n; *&t;an error interrupt (mostly generated at the hub).&n; */
r_int
DECL|function|hub_ioerror_handler
id|hub_ioerror_handler
c_func
(paren
id|vertex_hdl_t
id|hub_v
comma
r_int
id|error_code
comma
r_int
id|mode
comma
r_struct
id|io_error_s
op_star
id|ioerror
)paren
(brace
id|hubinfo_t
id|hinfo
suffix:semicolon
multiline_comment|/* Hub info pointer */
id|nasid_t
id|nasid
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*REFERENCED*/
id|iopaddr_t
id|p
suffix:semicolon
id|caddr_t
id|cp
suffix:semicolon
id|IOERROR_DUMP
c_func
(paren
l_string|&quot;hub_ioerror_handler&quot;
comma
id|error_code
comma
id|mode
comma
id|ioerror
)paren
suffix:semicolon
id|hubinfo_get
c_func
(paren
id|hub_v
comma
op_amp
id|hinfo
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hinfo
)paren
(brace
multiline_comment|/* Print an error message and return */
r_goto
id|end
suffix:semicolon
)brace
id|nasid
op_assign
id|hinfo-&gt;h_nasid
suffix:semicolon
r_switch
c_cond
(paren
id|error_code
)paren
(brace
r_case
id|PIO_READ_ERROR
suffix:colon
multiline_comment|/* &n;&t;&t; * Cpu got a bus error while accessing IO space.&n;&t;&t; * hubaddr field in ioerror structure should have&n;&t;&t; * the IO address that caused access error.&n;&t;&t; */
multiline_comment|/*&n;&t;&t; * Identify if  the physical address in hub_error_data&n;&t;&t; * corresponds to small/large window, and accordingly,&n;&t;&t; * get the xtalk address.&n;&t;&t; */
multiline_comment|/*&n;&t;&t; * Evaluate the widget number and the widget address that&n;&t;&t; * caused the error. Use &squot;vaddr&squot; if it&squot;s there.&n;&t;&t; * This is typically true either during probing&n;&t;&t; * or a kernel driver getting into trouble. &n;&t;&t; * Otherwise, use paddr to figure out widget details&n;&t;&t; * This is typically true for user mode bus errors while&n;&t;&t; * accessing I/O space.&n;&t;&t; */
id|IOERROR_GETVALUE
c_func
(paren
id|cp
comma
id|ioerror
comma
id|vaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cp
)paren
(brace
multiline_comment|/* &n;&t;&t;     * If neither in small window nor in large window range,&n;&t;&t;     * outright reject it.&n;&t;&t;     */
id|IOERROR_GETVALUE
c_func
(paren
id|cp
comma
id|ioerror
comma
id|vaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|NODE_SWIN_ADDR
c_func
(paren
id|nasid
comma
(paren
id|paddr_t
)paren
id|cp
)paren
)paren
(brace
id|iopaddr_t
id|hubaddr
suffix:semicolon
id|xwidgetnum_t
id|widgetnum
suffix:semicolon
id|iopaddr_t
id|xtalkaddr
suffix:semicolon
id|IOERROR_GETVALUE
c_func
(paren
id|p
comma
id|ioerror
comma
id|hubaddr
)paren
suffix:semicolon
id|hubaddr
op_assign
id|p
suffix:semicolon
id|widgetnum
op_assign
id|SWIN_WIDGETNUM
c_func
(paren
id|hubaddr
)paren
suffix:semicolon
id|xtalkaddr
op_assign
id|SWIN_WIDGETADDR
c_func
(paren
id|hubaddr
)paren
suffix:semicolon
multiline_comment|/* &n;&t;&t;&t; * differentiate local register vs IO space access&n;&t;&t;&t; */
id|IOERROR_SETVALUE
c_func
(paren
id|ioerror
comma
id|widgetnum
comma
id|widgetnum
)paren
suffix:semicolon
id|IOERROR_SETVALUE
c_func
(paren
id|ioerror
comma
id|xtalkaddr
comma
id|xtalkaddr
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|NODE_BWIN_ADDR
c_func
(paren
id|nasid
comma
(paren
id|paddr_t
)paren
id|cp
)paren
)paren
(brace
multiline_comment|/* &n;&t;&t;&t; * Address corresponds to large window space. &n;&t;&t;&t; * Convert it to xtalk address.&n;&t;&t;&t; */
r_int
id|bigwin
suffix:semicolon
id|hub_piomap_t
id|bw_piomap
suffix:semicolon
id|xtalk_piomap_t
id|xt_pmap
op_assign
l_int|NULL
suffix:semicolon
id|iopaddr_t
id|hubaddr
suffix:semicolon
id|xwidgetnum_t
id|widgetnum
suffix:semicolon
id|iopaddr_t
id|xtalkaddr
suffix:semicolon
id|IOERROR_GETVALUE
c_func
(paren
id|p
comma
id|ioerror
comma
id|hubaddr
)paren
suffix:semicolon
id|hubaddr
op_assign
id|p
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Have to loop to find the correct xtalk_piomap &n;&t;&t;&t; * because the&squot;re not allocated on a one-to-one&n;&t;&t;&t; * basis to the window number.&n;&t;&t;&t; */
r_for
c_loop
(paren
id|bigwin
op_assign
l_int|0
suffix:semicolon
id|bigwin
OL
id|HUB_NUM_BIG_WINDOW
suffix:semicolon
id|bigwin
op_increment
)paren
(brace
id|bw_piomap
op_assign
id|hubinfo_bwin_piomap_get
c_func
(paren
id|hinfo
comma
id|bigwin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bw_piomap-&gt;hpio_bigwin_num
op_eq
(paren
id|BWIN_WINDOWNUM
c_func
(paren
id|hubaddr
)paren
op_minus
l_int|1
)paren
)paren
(brace
id|xt_pmap
op_assign
id|hub_piomap_xt_piomap
c_func
(paren
id|bw_piomap
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|ASSERT
c_func
(paren
id|xt_pmap
)paren
suffix:semicolon
id|widgetnum
op_assign
id|xtalk_pio_target_get
c_func
(paren
id|xt_pmap
)paren
suffix:semicolon
id|xtalkaddr
op_assign
id|xtalk_pio_xtalk_addr_get
c_func
(paren
id|xt_pmap
)paren
op_plus
id|BWIN_WIDGETADDR
c_func
(paren
id|hubaddr
)paren
suffix:semicolon
id|IOERROR_SETVALUE
c_func
(paren
id|ioerror
comma
id|widgetnum
comma
id|widgetnum
)paren
suffix:semicolon
id|IOERROR_SETVALUE
c_func
(paren
id|ioerror
comma
id|xtalkaddr
comma
id|xtalkaddr
)paren
suffix:semicolon
multiline_comment|/* &n;&t;&t;&t; * Make sure that widgetnum doesnot map to hub &n;&t;&t;&t; * register widget number, as we never use&n;&t;&t;&t; * big window to access hub registers. &n;&t;&t;&t; */
id|ASSERT
c_func
(paren
id|widgetnum
op_ne
id|HUB_REGISTER_WIDGET
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|IOERROR_FIELDVALID
c_func
(paren
id|ioerror
comma
id|hubaddr
)paren
)paren
(brace
id|iopaddr_t
id|hubaddr
suffix:semicolon
id|xwidgetnum_t
id|widgetnum
suffix:semicolon
id|iopaddr_t
id|xtalkaddr
suffix:semicolon
id|IOERROR_GETVALUE
c_func
(paren
id|p
comma
id|ioerror
comma
id|hubaddr
)paren
suffix:semicolon
id|hubaddr
op_assign
id|p
suffix:semicolon
r_if
c_cond
(paren
id|BWIN_WINDOWNUM
c_func
(paren
id|hubaddr
)paren
)paren
(brace
r_int
id|window
op_assign
id|BWIN_WINDOWNUM
c_func
(paren
id|hubaddr
)paren
op_minus
l_int|1
suffix:semicolon
id|hubreg_t
id|itte
suffix:semicolon
id|itte
op_assign
(paren
id|hubreg_t
)paren
id|HUB_L
c_func
(paren
id|IIO_ITTE_GET
c_func
(paren
id|nasid
comma
id|window
)paren
)paren
suffix:semicolon
id|widgetnum
op_assign
(paren
id|itte
op_rshift
id|IIO_ITTE_WIDGET_SHIFT
)paren
op_amp
id|IIO_ITTE_WIDGET_MASK
suffix:semicolon
id|xtalkaddr
op_assign
(paren
(paren
(paren
id|itte
op_rshift
id|IIO_ITTE_OFFSET_SHIFT
)paren
op_amp
id|IIO_ITTE_OFFSET_MASK
)paren
op_lshift
id|BWIN_SIZE_BITS
)paren
op_plus
id|BWIN_WIDGETADDR
c_func
(paren
id|hubaddr
)paren
suffix:semicolon
)brace
r_else
(brace
id|widgetnum
op_assign
id|SWIN_WIDGETNUM
c_func
(paren
id|hubaddr
)paren
suffix:semicolon
id|xtalkaddr
op_assign
id|SWIN_WIDGETADDR
c_func
(paren
id|hubaddr
)paren
suffix:semicolon
)brace
id|IOERROR_SETVALUE
c_func
(paren
id|ioerror
comma
id|widgetnum
comma
id|widgetnum
)paren
suffix:semicolon
id|IOERROR_SETVALUE
c_func
(paren
id|ioerror
comma
id|xtalkaddr
comma
id|xtalkaddr
)paren
suffix:semicolon
)brace
r_else
(brace
id|IOERROR_DUMP
c_func
(paren
l_string|&quot;hub_ioerror_handler&quot;
comma
id|error_code
comma
id|mode
comma
id|ioerror
)paren
suffix:semicolon
id|IOERR_PRINTF
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;hub_ioerror_handler: Invalid address passed&quot;
)paren
)paren
suffix:semicolon
r_return
id|IOERROR_INVALIDADDR
suffix:semicolon
)brace
id|IOERROR_GETVALUE
c_func
(paren
id|p
comma
id|ioerror
comma
id|widgetnum
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
)paren
op_eq
id|HUB_REGISTER_WIDGET
)paren
(brace
multiline_comment|/* &n;&t;&t;&t; * Error in accessing Hub local register&n;&t;&t;&t; * This should happen mostly in SABLE mode..&n;&t;&t;&t; */
id|retval
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Make sure that the outbound widget access for this&n;&t;&t;&t; * widget is enabled.&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|is_widget_pio_enabled
c_func
(paren
id|ioerror
)paren
)paren
(brace
r_if
c_cond
(paren
id|error_state_get
c_func
(paren
id|hub_v
)paren
op_eq
id|ERROR_STATE_ACTION
)paren
id|ioerror_dump
c_func
(paren
l_string|&quot;No outbound widget&quot;
l_string|&quot; access - &quot;
comma
id|error_code
comma
id|mode
comma
id|ioerror
)paren
suffix:semicolon
r_return
id|IOERROR_HANDLED
suffix:semicolon
)brace
id|retval
op_assign
id|hub_xp_error_handler
c_func
(paren
id|hub_v
comma
id|nasid
comma
id|error_code
comma
id|mode
comma
id|ioerror
)paren
suffix:semicolon
)brace
id|IOERR_PRINTF
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;hub_ioerror_handler:PIO_READ_ERROR return: %d&quot;
comma
id|retval
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PIO_WRITE_ERROR
suffix:colon
multiline_comment|/*&n;&t;&t; * This hub received an interrupt indicating a widget &n;&t;&t; * attached to this hub got a timeout. &n;&t;&t; * widgetnum field should be filled to indicate the&n;&t;&t; * widget that caused error.&n;&t;&t; *&n;&t;&t; * NOTE: This hub may have nothing to do with this error.&n;&t;&t; * We are here since the widget attached to the xbow &n;&t;&t; * gets its PIOs through this hub.&n;&t;&t; *&n;&t;&t; * There is nothing that can be done at this level. &n;&t;&t; * Just invoke the xtalk error handling mechanism.&n;&t;&t; */
id|IOERROR_GETVALUE
c_func
(paren
id|p
comma
id|ioerror
comma
id|widgetnum
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
)paren
op_eq
id|HUB_REGISTER_WIDGET
)paren
(brace
)brace
r_else
(brace
multiline_comment|/* Make sure that the outbound widget access for this&n;&t;&t;&t; * widget is enabled.&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|is_widget_pio_enabled
c_func
(paren
id|ioerror
)paren
)paren
(brace
r_if
c_cond
(paren
id|error_state_get
c_func
(paren
id|hub_v
)paren
op_eq
id|ERROR_STATE_ACTION
)paren
id|ioerror_dump
c_func
(paren
l_string|&quot;No outbound widget&quot;
l_string|&quot; access - &quot;
comma
id|error_code
comma
id|mode
comma
id|ioerror
)paren
suffix:semicolon
r_return
id|IOERROR_HANDLED
suffix:semicolon
)brace
id|retval
op_assign
id|hub_xp_error_handler
c_func
(paren
id|hub_v
comma
id|nasid
comma
id|error_code
comma
id|mode
comma
id|ioerror
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|DMA_READ_ERROR
suffix:colon
multiline_comment|/* &n;&t;&t; * DMA Read error always ends up generating an interrupt&n;&t;&t; * at the widget level, and never at the hub level. So,&n;&t;&t; * we don&squot;t expect to come here any time&n;&t;&t; */
id|ASSERT
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|retval
op_assign
id|IOERROR_UNHANDLED
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DMA_WRITE_ERROR
suffix:colon
multiline_comment|/*&n;&t;&t; * DMA Write error is generated when a write by an I/O &n;&t;&t; * device could not be completed. Problem is, device is&n;&t;&t; * totally unaware of this problem, and would continue&n;&t;&t; * writing to system memory. So, hub has a way to send&n;&t;&t; * an error interrupt on the first error, and bitbucket&n;&t;&t; * all further write transactions.&n;&t;&t; * Coming here indicates that hub detected one such error,&n;&t;&t; * and we need to handle it.&n;&t;&t; *&n;&t;&t; * Hub interrupt handler would have extracted physaddr, &n;&t;&t; * widgetnum, and widgetdevice from the CRB &n;&t;&t; *&n;&t;&t; * There is nothing special to do here, since gathering&n;&t;&t; * data from crb&squot;s is done elsewhere. Just pass the &n;&t;&t; * error to xtalk layer.&n;&t;&t; */
id|retval
op_assign
id|hub_xp_error_handler
c_func
(paren
id|hub_v
comma
id|nasid
comma
id|error_code
comma
id|mode
comma
id|ioerror
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ASSERT
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_return
id|IOERROR_BADERRORCODE
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If error was not handled, we may need to take certain action&n;&t; * based on the error code.&n;&t; * For e.g. in case of PIO_READ_ERROR, we may need to release the&n;&t; * PIO Read entry table (they are sticky after errors).&n;&t; * Similarly other cases. &n;&t; *&n;&t; * Further Action TBD &n;&t; */
id|end
suffix:colon
r_if
c_cond
(paren
id|retval
op_eq
id|IOERROR_HWGRAPH_LOOKUP
)paren
(brace
multiline_comment|/*&n;&t;&t; * If we get errors very early, we can&squot;t traverse&n;&t;&t; * the path using hardware graph. &n;&t;&t; * To handle this situation, we need a functions&n;&t;&t; * which don&squot;t depend on the hardware graph vertex to &n;&t;&t; * handle errors. This break the modularity of the&n;&t;&t; * existing code. Instead we print out the reason for&n;&t;&t; * not handling error, and return. On return, all the&n;&t;&t; * info collected would be dumped. This should provide &n;&t;&t; * sufficient info to analyse the error.&n;&t;&t; */
id|printk
c_func
(paren
l_string|&quot;Unable to handle IO error: hardware graph not setup&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|macro|INFO_LBL_ERROR_STATE
mdefine_line|#define INFO_LBL_ERROR_STATE    &quot;error_state&quot;
DECL|macro|v_error_state_get
mdefine_line|#define v_error_state_get(v,s)                                          &bslash;&n;(hwgraph_info_get_LBL(v,INFO_LBL_ERROR_STATE, (arbitrary_info_t *)&amp;s))
DECL|macro|v_error_state_set
mdefine_line|#define v_error_state_set(v,s,replace)                                  &bslash;&n;(replace ?                                                              &bslash;&n;hwgraph_info_replace_LBL(v,INFO_LBL_ERROR_STATE,(arbitrary_info_t)s,0) :&bslash;&n;hwgraph_info_add_LBL(v,INFO_LBL_ERROR_STATE, (arbitrary_info_t)s))
DECL|macro|v_error_state_clear
mdefine_line|#define v_error_state_clear(v)                                          &bslash;&n;(hwgraph_info_remove_LBL(v,INFO_LBL_ERROR_STATE,0))
multiline_comment|/*&n; * error_state_get&n; *              Get the state of the vertex.&n; *              Returns ERROR_STATE_INVALID on failure&n; *                      current state otherwise&n; */
id|error_state_t
DECL|function|error_state_get
id|error_state_get
c_func
(paren
id|vertex_hdl_t
id|v
)paren
(brace
id|error_state_t
id|s
suffix:semicolon
multiline_comment|/* Check if we have a valid hwgraph vertex */
r_if
c_cond
(paren
id|v
op_eq
(paren
id|vertex_hdl_t
)paren
l_int|0
)paren
r_return
id|ERROR_STATE_NONE
suffix:semicolon
multiline_comment|/* Get the labelled info hanging off the vertex which corresponds&n;         * to the state.&n;         */
r_if
c_cond
(paren
id|v_error_state_get
c_func
(paren
id|v
comma
id|s
)paren
op_ne
id|GRAPH_SUCCESS
)paren
(brace
r_return
id|ERROR_STATE_NONE
suffix:semicolon
)brace
r_return
id|s
suffix:semicolon
)brace
multiline_comment|/*&n; * error_state_set&n; *              Set the state of the vertex&n; *              Returns ERROR_RETURN_CODE_CANNOT_SET_STATE on failure&n; *                      ERROR_RETURN_CODE_SUCCESS otherwise&n; */
id|error_return_code_t
DECL|function|error_state_set
id|error_state_set
c_func
(paren
id|vertex_hdl_t
id|v
comma
id|error_state_t
id|new_state
)paren
(brace
id|error_state_t
id|old_state
suffix:semicolon
id|boolean_t
id|replace
op_assign
id|B_TRUE
suffix:semicolon
multiline_comment|/* Check if we have a valid hwgraph vertex */
r_if
c_cond
(paren
id|v
op_eq
(paren
id|vertex_hdl_t
)paren
l_int|0
)paren
r_return
id|ERROR_RETURN_CODE_GENERAL_FAILURE
suffix:semicolon
multiline_comment|/* This means that the error state needs to be cleaned */
r_if
c_cond
(paren
id|new_state
op_eq
id|ERROR_STATE_NONE
)paren
(brace
multiline_comment|/* Make sure that we have an error state */
r_if
c_cond
(paren
id|v_error_state_get
c_func
(paren
id|v
comma
id|old_state
)paren
op_eq
id|GRAPH_SUCCESS
)paren
id|v_error_state_clear
c_func
(paren
id|v
)paren
suffix:semicolon
r_return
id|ERROR_RETURN_CODE_SUCCESS
suffix:semicolon
)brace
multiline_comment|/* Check if the state information has been set at least once&n;         * for this vertex.&n;         */
r_if
c_cond
(paren
id|v_error_state_get
c_func
(paren
id|v
comma
id|old_state
)paren
op_ne
id|GRAPH_SUCCESS
)paren
id|replace
op_assign
id|B_FALSE
suffix:semicolon
r_if
c_cond
(paren
id|v_error_state_set
c_func
(paren
id|v
comma
id|new_state
comma
id|replace
)paren
op_ne
id|GRAPH_SUCCESS
)paren
(brace
r_return
id|ERROR_RETURN_CODE_CANNOT_SET_STATE
suffix:semicolon
)brace
r_return
id|ERROR_RETURN_CODE_SUCCESS
suffix:semicolon
)brace
eof
