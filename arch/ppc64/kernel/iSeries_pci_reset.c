multiline_comment|/************************************************************************/
multiline_comment|/* File iSeries_pci_reset.c created by Allan Trautman on Mar 21 2001.   */
multiline_comment|/************************************************************************/
multiline_comment|/* This code supports the pci interface on the IBM iSeries systems.     */
multiline_comment|/* Copyright (C) 20yy  &lt;Allan H Trautman&gt; &lt;IBM Corp&gt;                    */
multiline_comment|/*                                                                      */
multiline_comment|/* This program is free software; you can redistribute it and/or modify */
multiline_comment|/* it under the terms of the GNU General Public License as published by */
multiline_comment|/* the Free Software Foundation; either version 2 of the License, or    */
multiline_comment|/* (at your option) any later version.                                  */
multiline_comment|/*                                                                      */
multiline_comment|/* This program is distributed in the hope that it will be useful,      */
multiline_comment|/* but WITHOUT ANY WARRANTY; without even the implied warranty of       */
multiline_comment|/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        */
multiline_comment|/* GNU General Public License for more details.                         */
multiline_comment|/*                                                                      */
multiline_comment|/* You should have received a copy of the GNU General Public License    */
multiline_comment|/* along with this program; if not, write to the:                       */
multiline_comment|/* Free Software Foundation, Inc.,                                      */
multiline_comment|/* 59 Temple Place, Suite 330,                                          */
multiline_comment|/* Boston, MA  02111-1307  USA                                          */
multiline_comment|/************************************************************************/
multiline_comment|/* Change Activity:                                                     */
multiline_comment|/*   Created, March 20, 2001                                            */
multiline_comment|/*   April 30, 2001, Added return codes on functions.                   */
multiline_comment|/*   September 10, 2001, Ported to ppc64.                               */
multiline_comment|/* End Change Activity                                                  */
multiline_comment|/************************************************************************/
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/init.h&gt;
macro_line|#include &lt;asm/iSeries/HvCallPci.h&gt;
macro_line|#include &lt;asm/iSeries/HvTypes.h&gt;
macro_line|#include &lt;asm/iSeries/mf.h&gt;
macro_line|#include &lt;asm/flight_recorder.h&gt;
macro_line|#include &lt;asm/pci.h&gt;
macro_line|#include &lt;asm/iSeries/iSeries_pci.h&gt;
macro_line|#include &quot;pci.h&quot;
multiline_comment|/************************************************************************/
multiline_comment|/* Interface to toggle the reset line                                   */
multiline_comment|/* Time is in .1 seconds, need for seconds.                             */
multiline_comment|/************************************************************************/
DECL|function|iSeries_Device_ToggleReset
r_int
id|iSeries_Device_ToggleReset
c_func
(paren
r_struct
id|pci_dev
op_star
id|PciDev
comma
r_int
id|AssertTime
comma
r_int
id|DelayTime
)paren
(brace
r_int
r_int
id|AssertDelay
comma
id|WaitDelay
suffix:semicolon
r_struct
id|iSeries_Device_Node
op_star
id|DeviceNode
op_assign
(paren
r_struct
id|iSeries_Device_Node
op_star
)paren
id|PciDev-&gt;sysdata
suffix:semicolon
r_if
c_cond
(paren
id|DeviceNode
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI: Pci Reset Failed, Device Node not found for pci_dev %p&bslash;n&quot;
comma
id|PciDev
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/********************************************************************&n;&t; * Set defaults, Assert is .5 second, Wait is 3 seconds.&n;&t; ********************************************************************/
r_if
c_cond
(paren
id|AssertTime
op_eq
l_int|0
)paren
id|AssertDelay
op_assign
(paren
l_int|5
op_star
id|HZ
)paren
op_div
l_int|10
suffix:semicolon
r_else
id|AssertDelay
op_assign
(paren
id|AssertTime
op_star
id|HZ
)paren
op_div
l_int|10
suffix:semicolon
r_if
c_cond
(paren
id|WaitDelay
op_eq
l_int|0
)paren
id|WaitDelay
op_assign
(paren
l_int|30
op_star
id|HZ
)paren
op_div
l_int|10
suffix:semicolon
r_else
id|WaitDelay
op_assign
(paren
id|DelayTime
op_star
id|HZ
)paren
op_div
l_int|10
suffix:semicolon
multiline_comment|/********************************************************************&n;&t; * Assert reset&n;&t; ********************************************************************/
id|DeviceNode-&gt;ReturnCode
op_assign
id|HvCallPci_setSlotReset
c_func
(paren
id|ISERIES_BUS
c_func
(paren
id|DeviceNode
)paren
comma
l_int|0x00
comma
id|DeviceNode-&gt;AgentId
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|DeviceNode-&gt;ReturnCode
op_eq
l_int|0
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|AssertDelay
)paren
suffix:semicolon
multiline_comment|/* Sleep for the time     */
id|DeviceNode-&gt;ReturnCode
op_assign
id|HvCallPci_setSlotReset
c_func
(paren
id|ISERIES_BUS
c_func
(paren
id|DeviceNode
)paren
comma
l_int|0x00
comma
id|DeviceNode-&gt;AgentId
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/***************************************************************&n;   &t;&t; * Wait for device to reset&n;&t;&t; ***************************************************************/
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|WaitDelay
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|DeviceNode-&gt;ReturnCode
op_eq
l_int|0
)paren
(brace
id|PCIFR
c_func
(paren
l_string|&quot;Slot 0x%04X.%02 Reset&bslash;n&quot;
comma
id|ISERIES_BUS
c_func
(paren
id|DeviceNode
)paren
comma
id|DeviceNode-&gt;AgentId
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;PCI: Slot 0x%04X.%02X Reset Failed, RCode: %04X&bslash;n&quot;
comma
id|ISERIES_BUS
c_func
(paren
id|DeviceNode
)paren
comma
id|DeviceNode-&gt;AgentId
comma
id|DeviceNode-&gt;ReturnCode
)paren
suffix:semicolon
id|PCIFR
c_func
(paren
l_string|&quot;Slot 0x%04X.%02X Reset Failed, RCode: %04X&bslash;n&quot;
comma
id|ISERIES_BUS
c_func
(paren
id|DeviceNode
)paren
comma
id|DeviceNode-&gt;AgentId
comma
id|DeviceNode-&gt;ReturnCode
)paren
suffix:semicolon
)brace
r_return
id|DeviceNode-&gt;ReturnCode
suffix:semicolon
)brace
eof
