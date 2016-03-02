multiline_comment|/*======================================================================&n;&n;    Device driver for the PCMCIA control functionality of StrongARM&n;    SA-1100 microprocessors.&n;&n;    The contents of this file are subject to the Mozilla Public&n;    License Version 1.1 (the &quot;License&quot;); you may not use this file&n;    except in compliance with the License. You may obtain a copy of&n;    the License at http://www.mozilla.org/MPL/&n;&n;    Software distributed under the License is distributed on an &quot;AS&n;    IS&quot; basis, WITHOUT WARRANTY OF ANY KIND, either express or&n;    implied. See the License for the specific language governing&n;    rights and limitations under the License.&n;&n;    The initial developer of the original code is John G. Dorsey&n;    &lt;john+@cs.cmu.edu&gt;.  Portions created by John G. Dorsey are&n;    Copyright (C) 1999 John G. Dorsey.  All Rights Reserved.&n;&n;    Alternatively, the contents of this file may be used under the&n;    terms of the GNU Public License version 2 (the &quot;GPL&quot;), in which&n;    case the provisions of the GPL are applicable instead of the&n;    above.  If you wish to allow the use of your version of this file&n;    only under the terms of the GPL and not to allow others to use&n;    your version of this file under the MPL, indicate your decision&n;    by deleting the provisions above and replace them with the notice&n;    and other provisions required by the GPL.  If you do not delete&n;    the provisions above, a recipient may use your version of this&n;    file under either the MPL or the GPL.&n;    &n;======================================================================*/
multiline_comment|/*&n; * Please see linux/Documentation/arm/SA1100/PCMCIA for more information&n; * on the low-level kernel interface.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;pcmcia/version.h&gt;
macro_line|#include &lt;pcmcia/cs_types.h&gt;
macro_line|#include &lt;pcmcia/cs.h&gt;
macro_line|#include &lt;pcmcia/ss.h&gt;
macro_line|#include &quot;sa1100.h&quot;
DECL|variable|sa11x0_pcmcia_hw_init
r_static
r_int
(paren
op_star
id|sa11x0_pcmcia_hw_init
(braket
)braket
)paren
(paren
r_struct
id|device
op_star
id|dev
)paren
op_assign
(brace
macro_line|#ifdef CONFIG_SA1100_ASSABET
id|pcmcia_assabet_init
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SA1100_CERF
id|pcmcia_cerf_init
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SA1100_FLEXANET
id|pcmcia_flexanet_init
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SA1100_FREEBIRD
id|pcmcia_freebird_init
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SA1100_GRAPHICSCLIENT
id|pcmcia_gcplus_init
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SA1100_H3600
id|pcmcia_h3600_init
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SA1100_PANGOLIN
id|pcmcia_pangolin_init
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SA1100_SHANNON
id|pcmcia_shannon_init
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SA1100_SIMPAD
id|pcmcia_simpad_init
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SA1100_STORK
id|pcmcia_stork_init
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SA1100_TRIZEPS
id|pcmcia_trizeps_init
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SA1100_YOPY
id|pcmcia_yopy_init
comma
macro_line|#endif
)brace
suffix:semicolon
DECL|function|sa11x0_drv_pcmcia_probe
r_static
r_int
id|sa11x0_drv_pcmcia_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|i
comma
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/*&n;&t; * Initialise any &quot;on-board&quot; PCMCIA sockets.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ARRAY_SIZE
c_func
(paren
id|sa11x0_pcmcia_hw_init
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ret
op_assign
id|sa11x0_pcmcia_hw_init
(braket
id|i
)braket
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|sa11x0_pcmcia_driver
r_static
r_struct
id|device_driver
id|sa11x0_pcmcia_driver
op_assign
(brace
dot
id|probe
op_assign
id|sa11x0_drv_pcmcia_probe
comma
dot
id|remove
op_assign
id|sa11xx_drv_pcmcia_remove
comma
dot
id|name
op_assign
l_string|&quot;sa11x0-pcmcia&quot;
comma
dot
id|bus
op_assign
op_amp
id|platform_bus_type
comma
dot
id|suspend
op_assign
id|pcmcia_socket_dev_suspend
comma
dot
id|resume
op_assign
id|pcmcia_socket_dev_resume
comma
)brace
suffix:semicolon
multiline_comment|/* sa11x0_pcmcia_init()&n; * ^^^^^^^^^^^^^^^^^^^^&n; *&n; * This routine performs low-level PCMCIA initialization and then&n; * registers this socket driver with Card Services.&n; *&n; * Returns: 0 on success, -ve error code on failure&n; */
DECL|function|sa11x0_pcmcia_init
r_static
r_int
id|__init
id|sa11x0_pcmcia_init
c_func
(paren
r_void
)paren
(brace
r_return
id|driver_register
c_func
(paren
op_amp
id|sa11x0_pcmcia_driver
)paren
suffix:semicolon
)brace
multiline_comment|/* sa11x0_pcmcia_exit()&n; * ^^^^^^^^^^^^^^^^^^^^&n; * Invokes the low-level kernel service to free IRQs associated with this&n; * socket controller and reset GPIO edge detection.&n; */
DECL|function|sa11x0_pcmcia_exit
r_static
r_void
id|__exit
id|sa11x0_pcmcia_exit
c_func
(paren
r_void
)paren
(brace
id|driver_unregister
c_func
(paren
op_amp
id|sa11x0_pcmcia_driver
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;John Dorsey &lt;john+@cs.cmu.edu&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Linux PCMCIA Card Services: SA-11x0 Socket Controller&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;Dual MPL/GPL&quot;
)paren
suffix:semicolon
DECL|variable|sa11x0_pcmcia_init
id|module_init
c_func
(paren
id|sa11x0_pcmcia_init
)paren
suffix:semicolon
DECL|variable|sa11x0_pcmcia_exit
id|module_exit
c_func
(paren
id|sa11x0_pcmcia_exit
)paren
suffix:semicolon
eof
