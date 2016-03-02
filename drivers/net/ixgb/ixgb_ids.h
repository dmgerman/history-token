multiline_comment|/*******************************************************************************&n;&n;  &n;  Copyright(c) 1999 - 2003 Intel Corporation. All rights reserved.&n;  &n;  This program is free software; you can redistribute it and/or modify it &n;  under the terms of the GNU General Public License as published by the Free &n;  Software Foundation; either version 2 of the License, or (at your option) &n;  any later version.&n;  &n;  This program is distributed in the hope that it will be useful, but WITHOUT &n;  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or &n;  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for &n;  more details.&n;  &n;  You should have received a copy of the GNU General Public License along with&n;  this program; if not, write to the Free Software Foundation, Inc., 59 &n;  Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n;  &n;  The full GNU General Public License is included in this distribution in the&n;  file called LICENSE.&n;  &n;  Contact Information:&n;  Linux NICS &lt;linux.nics@intel.com&gt;&n;  Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497&n;*******************************************************************************/
macro_line|#ifndef _IXGB_IDS_H_
DECL|macro|_IXGB_IDS_H_
mdefine_line|#define _IXGB_IDS_H_
multiline_comment|/**********************************************************************&n;** The Device and Vendor IDs for 10 Gigabit MACs&n;**********************************************************************/
DECL|macro|INTEL_VENDOR_ID
mdefine_line|#define INTEL_VENDOR_ID         0x8086
DECL|macro|INTEL_SUBVENDOR_ID
mdefine_line|#define INTEL_SUBVENDOR_ID      0x8086
DECL|macro|IXGB_DEVICE_ID_82597EX
mdefine_line|#define IXGB_DEVICE_ID_82597EX &t;0x1048
DECL|macro|IXGB_SUBDEVICE_ID_A11F
mdefine_line|#define IXGB_SUBDEVICE_ID_A11F  0xA11F&t;/* Adapter-OEM-1310nm-Fiber */
DECL|macro|IXGB_SUBDEVICE_ID_A01F
mdefine_line|#define IXGB_SUBDEVICE_ID_A01F&t;0xA01F&t;/* Adapter-Retail-1310nm-Fiber */
macro_line|#endif&t;&t;&t;&t;/* #ifndef _IXGB_IDS_H_ */
multiline_comment|/* End of File */
eof
