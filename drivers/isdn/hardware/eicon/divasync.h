multiline_comment|/*&n; *&n;  Copyright (c) Eicon Networks, 2002.&n; *&n;  This source file is supplied for the use with&n;  Eicon Networks range of DIVA Server Adapters.&n; *&n;  Eicon File Revision :    2.1&n; *&n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2, or (at your option)&n;  any later version.&n; *&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY&n;  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n;  See the GNU General Public License for more details.&n; *&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef __DIVA_SYNC__H  
DECL|macro|__DIVA_SYNC__H
mdefine_line|#define __DIVA_SYNC__H
DECL|macro|IDI_SYNC_REQ_REMOVE
mdefine_line|#define IDI_SYNC_REQ_REMOVE             0x00
DECL|macro|IDI_SYNC_REQ_GET_NAME
mdefine_line|#define IDI_SYNC_REQ_GET_NAME           0x01
DECL|macro|IDI_SYNC_REQ_GET_SERIAL
mdefine_line|#define IDI_SYNC_REQ_GET_SERIAL         0x02
DECL|macro|IDI_SYNC_REQ_SET_POSTCALL
mdefine_line|#define IDI_SYNC_REQ_SET_POSTCALL       0x03
DECL|macro|IDI_SYNC_REQ_GET_XLOG
mdefine_line|#define IDI_SYNC_REQ_GET_XLOG           0x04
DECL|macro|IDI_SYNC_REQ_GET_FEATURES
mdefine_line|#define IDI_SYNC_REQ_GET_FEATURES       0x05
multiline_comment|/* Added for DIVA USB support */
DECL|macro|IDI_SYNC_REQ_USB_REGISTER
mdefine_line|#define IDI_SYNC_REQ_USB_REGISTER       0x06
DECL|macro|IDI_SYNC_REQ_USB_RELEASE
mdefine_line|#define IDI_SYNC_REQ_USB_RELEASE        0x07
DECL|macro|IDI_SYNC_REQ_USB_ADD_DEVICE
mdefine_line|#define IDI_SYNC_REQ_USB_ADD_DEVICE     0x08
DECL|macro|IDI_SYNC_REQ_USB_START_DEVICE
mdefine_line|#define IDI_SYNC_REQ_USB_START_DEVICE   0x09
DECL|macro|IDI_SYNC_REQ_USB_STOP_DEVICE
mdefine_line|#define IDI_SYNC_REQ_USB_STOP_DEVICE    0x0A
DECL|macro|IDI_SYNC_REQ_USB_REMOVE_DEVICE
mdefine_line|#define IDI_SYNC_REQ_USB_REMOVE_DEVICE  0x0B
multiline_comment|/* Added for Diva Server Monitor */
DECL|macro|IDI_SYNC_REQ_GET_CARDTYPE
mdefine_line|#define IDI_SYNC_REQ_GET_CARDTYPE       0x0C
DECL|macro|IDI_SYNC_REQ_GET_DBG_XLOG
mdefine_line|#define IDI_SYNC_REQ_GET_DBG_XLOG       0x0D
DECL|macro|IDI_SYNC_REQ_GET_LINE_IDX
mdefine_line|#define IDI_SYNC_REQ_GET_LINE_IDX   0x0E
DECL|macro|DIVA_USB
mdefine_line|#define DIVA_USB
DECL|macro|DIVA_USB_REQ
mdefine_line|#define DIVA_USB_REQ                    0xAC
DECL|macro|DIVA_USB_TEST
mdefine_line|#define DIVA_USB_TEST                   0xAB
DECL|macro|DIVA_USB_ADD_ADAPTER
mdefine_line|#define DIVA_USB_ADD_ADAPTER            0xAC
DECL|macro|DIVA_USB_REMOVE_ADAPTER
mdefine_line|#define DIVA_USB_REMOVE_ADAPTER         0xAD
multiline_comment|/******************************************************************************/
DECL|macro|IDI_SYNC_REQ_SERIAL_HOOK
mdefine_line|#define IDI_SYNC_REQ_SERIAL_HOOK        0x80
DECL|macro|IDI_SYNC_REQ_XCHANGE_STATUS
mdefine_line|#define IDI_SYNC_REQ_XCHANGE_STATUS     0x81
DECL|macro|IDI_SYNC_REQ_USB_HOOK
mdefine_line|#define IDI_SYNC_REQ_USB_HOOK           0x82
DECL|macro|IDI_SYNC_REQ_PORTDRV_HOOK
mdefine_line|#define IDI_SYNC_REQ_PORTDRV_HOOK       0x83
DECL|macro|IDI_SYNC_REQ_SLI
mdefine_line|#define IDI_SYNC_REQ_SLI           (0x84)   /*  SLI request from 3signal modem drivers */
DECL|macro|IDI_SYNC_REQ_RECONFIGURE
mdefine_line|#define IDI_SYNC_REQ_RECONFIGURE        0x85
DECL|macro|IDI_SYNC_REQ_RESET
mdefine_line|#define IDI_SYNC_REQ_RESET              0x86
DECL|macro|IDI_SYNC_REQ_LOCK_85X
mdefine_line|#define IDI_SYNC_REQ_LOCK_85X                   0x88
DECL|macro|IDI_SYNC_REQ_GET_85X_EXT_PORT_TYPE
mdefine_line|#define IDI_SYNC_REQ_GET_85X_EXT_PORT_TYPE      0xA0
DECL|macro|IDI_SYNC_REQ_DIPORT_GET_85X_TX_CTRL_FN
mdefine_line|#define IDI_SYNC_REQ_DIPORT_GET_85X_TX_CTRL_FN  0x98
multiline_comment|/******************************************************************************/
DECL|macro|IDI_SYNC_REQ_XDI_GET_EXTENDED_FEATURES
mdefine_line|#define IDI_SYNC_REQ_XDI_GET_EXTENDED_FEATURES  0x92
multiline_comment|/*&n;   To receive XDI features:&n;   1. set &squot;buffer_length_in_bytes&squot; to length of you buffer&n;   2. set &squot;features&squot; to pointer to your buffer&n;   3. issue synchronous request to XDI&n;   4. Check that feature &squot;DIVA_XDI_EXTENDED_FEATURES_VALID&squot; is present&n;      after call. This feature does indicate that your request&n;      was processed and XDI does support this synchronous request&n;   5. if on return bit 31 (0x80000000) in &squot;buffer_length_in_bytes&squot; is&n;      set then provided buffer was too small, and bits 30-0 does&n;      contain necessary length of buffer.&n;      in this case only features that do find place in the buffer&n;      are indicated to caller&n;*/
DECL|struct|_diva_xdi_get_extended_xdi_features
r_typedef
r_struct
id|_diva_xdi_get_extended_xdi_features
(brace
DECL|member|buffer_length_in_bytes
id|dword
id|buffer_length_in_bytes
suffix:semicolon
DECL|member|features
id|byte
op_star
id|features
suffix:semicolon
DECL|typedef|diva_xdi_get_extended_xdi_features_t
)brace
id|diva_xdi_get_extended_xdi_features_t
suffix:semicolon
multiline_comment|/*&n;   features[0]&n;  */
DECL|macro|DIVA_XDI_EXTENDED_FEATURES_VALID
mdefine_line|#define DIVA_XDI_EXTENDED_FEATURES_VALID          0x01
DECL|macro|DIVA_XDI_EXTENDED_FEATURE_CMA
mdefine_line|#define DIVA_XDI_EXTENDED_FEATURE_CMA             0x02
DECL|macro|DIVA_XDI_EXTENDED_FEATURE_SDRAM_BAR
mdefine_line|#define DIVA_XDI_EXTENDED_FEATURE_SDRAM_BAR       0x04
DECL|macro|DIVA_XDI_EXTENDED_FEATURE_CAPI_PRMS
mdefine_line|#define DIVA_XDI_EXTENDED_FEATURE_CAPI_PRMS       0x08
DECL|macro|DIVA_XDI_EXTENDED_FEATURE_NO_CANCEL_RC
mdefine_line|#define DIVA_XDI_EXTENDED_FEATURE_NO_CANCEL_RC    0x10
DECL|macro|DIVA_XDI_EXTENDED_FEATURE_RX_DMA
mdefine_line|#define DIVA_XDI_EXTENDED_FEATURE_RX_DMA          0x20
DECL|macro|DIVA_XDI_EXTENDED_FEATURES_MAX_SZ
mdefine_line|#define DIVA_XDI_EXTENDED_FEATURES_MAX_SZ    1
multiline_comment|/******************************************************************************/
DECL|macro|IDI_SYNC_REQ_XDI_GET_ADAPTER_SDRAM_BAR
mdefine_line|#define IDI_SYNC_REQ_XDI_GET_ADAPTER_SDRAM_BAR   0x93
DECL|struct|_diva_xdi_get_adapter_sdram_bar
r_typedef
r_struct
id|_diva_xdi_get_adapter_sdram_bar
(brace
DECL|member|bar
id|dword
id|bar
suffix:semicolon
DECL|typedef|diva_xdi_get_adapter_sdram_bar_t
)brace
id|diva_xdi_get_adapter_sdram_bar_t
suffix:semicolon
multiline_comment|/******************************************************************************/
DECL|macro|IDI_SYNC_REQ_XDI_GET_CAPI_PARAMS
mdefine_line|#define IDI_SYNC_REQ_XDI_GET_CAPI_PARAMS   0x94
multiline_comment|/*&n;  CAPI Parameters will be written in the caller&squot;s buffer&n;  */
DECL|struct|_diva_xdi_get_capi_parameters
r_typedef
r_struct
id|_diva_xdi_get_capi_parameters
(brace
DECL|member|structure_length
id|dword
id|structure_length
suffix:semicolon
DECL|member|flag_dynamic_l1_down
id|byte
id|flag_dynamic_l1_down
suffix:semicolon
DECL|member|group_optimization_enabled
id|byte
id|group_optimization_enabled
suffix:semicolon
DECL|typedef|diva_xdi_get_capi_parameters_t
)brace
id|diva_xdi_get_capi_parameters_t
suffix:semicolon
multiline_comment|/******************************************************************************/
DECL|macro|IDI_SYNC_REQ_XDI_GET_LOGICAL_ADAPTER_NUMBER
mdefine_line|#define IDI_SYNC_REQ_XDI_GET_LOGICAL_ADAPTER_NUMBER   0x95
multiline_comment|/*&n;  Get logical adapter number, as assigned by XDI&n;  &squot;controller&squot; is starting with zero &squot;sub&squot; controller number&n;  in case of one adapter that supports multiple interfaces&n;  &squot;controller&squot; is zero for Master adapter (and adapter that supports&n;  only one interface)&n;  */
DECL|struct|_diva_xdi_get_logical_adapter_number
r_typedef
r_struct
id|_diva_xdi_get_logical_adapter_number
(brace
DECL|member|logical_adapter_number
id|dword
id|logical_adapter_number
suffix:semicolon
DECL|member|controller
id|dword
id|controller
suffix:semicolon
DECL|typedef|diva_xdi_get_logical_adapter_number_s_t
)brace
id|diva_xdi_get_logical_adapter_number_s_t
suffix:semicolon
multiline_comment|/******************************************************************************/
DECL|macro|IDI_SYNC_REQ_UP1DM_OPERATION
mdefine_line|#define IDI_SYNC_REQ_UP1DM_OPERATION   0x96
multiline_comment|/******************************************************************************/
DECL|macro|IDI_SYNC_REQ_DMA_DESCRIPTOR_OPERATION
mdefine_line|#define IDI_SYNC_REQ_DMA_DESCRIPTOR_OPERATION 0x97
DECL|macro|IDI_SYNC_REQ_DMA_DESCRIPTOR_ALLOC
mdefine_line|#define IDI_SYNC_REQ_DMA_DESCRIPTOR_ALLOC     0x01
DECL|macro|IDI_SYNC_REQ_DMA_DESCRIPTOR_FREE
mdefine_line|#define IDI_SYNC_REQ_DMA_DESCRIPTOR_FREE      0x02
DECL|struct|_diva_xdi_dma_descriptor_operation
r_typedef
r_struct
id|_diva_xdi_dma_descriptor_operation
(brace
DECL|member|operation
r_int
id|operation
suffix:semicolon
DECL|member|descriptor_number
r_int
id|descriptor_number
suffix:semicolon
DECL|member|descriptor_address
r_void
op_star
id|descriptor_address
suffix:semicolon
DECL|member|descriptor_magic
id|dword
id|descriptor_magic
suffix:semicolon
DECL|typedef|diva_xdi_dma_descriptor_operation_t
)brace
id|diva_xdi_dma_descriptor_operation_t
suffix:semicolon
multiline_comment|/******************************************************************************/
DECL|macro|IDI_SYNC_REQ_DIDD_REGISTER_ADAPTER_NOTIFY
mdefine_line|#define IDI_SYNC_REQ_DIDD_REGISTER_ADAPTER_NOTIFY   0x01
DECL|macro|IDI_SYNC_REQ_DIDD_REMOVE_ADAPTER_NOTIFY
mdefine_line|#define IDI_SYNC_REQ_DIDD_REMOVE_ADAPTER_NOTIFY     0x02
DECL|macro|IDI_SYNC_REQ_DIDD_ADD_ADAPTER
mdefine_line|#define IDI_SYNC_REQ_DIDD_ADD_ADAPTER               0x03
DECL|macro|IDI_SYNC_REQ_DIDD_REMOVE_ADAPTER
mdefine_line|#define IDI_SYNC_REQ_DIDD_REMOVE_ADAPTER            0x04
DECL|macro|IDI_SYNC_REQ_DIDD_READ_ADAPTER_ARRAY
mdefine_line|#define IDI_SYNC_REQ_DIDD_READ_ADAPTER_ARRAY        0x05
DECL|struct|_diva_didd_adapter_notify
r_typedef
r_struct
id|_diva_didd_adapter_notify
(brace
DECL|member|handle
id|dword
id|handle
suffix:semicolon
multiline_comment|/* Notification handle */
DECL|member|callback
r_void
op_star
id|callback
suffix:semicolon
DECL|member|context
r_void
op_star
id|context
suffix:semicolon
DECL|typedef|diva_didd_adapter_notify_t
)brace
id|diva_didd_adapter_notify_t
suffix:semicolon
DECL|struct|_diva_didd_add_adapter
r_typedef
r_struct
id|_diva_didd_add_adapter
(brace
DECL|member|descriptor
r_void
op_star
id|descriptor
suffix:semicolon
DECL|typedef|diva_didd_add_adapter_t
)brace
id|diva_didd_add_adapter_t
suffix:semicolon
DECL|struct|_diva_didd_remove_adapter
r_typedef
r_struct
id|_diva_didd_remove_adapter
(brace
DECL|member|p_request
id|IDI_CALL
id|p_request
suffix:semicolon
DECL|typedef|diva_didd_remove_adapter_t
)brace
id|diva_didd_remove_adapter_t
suffix:semicolon
DECL|struct|_diva_didd_read_adapter_array
r_typedef
r_struct
id|_diva_didd_read_adapter_array
(brace
DECL|member|buffer
r_void
op_star
id|buffer
suffix:semicolon
DECL|member|length
id|dword
id|length
suffix:semicolon
DECL|typedef|diva_didd_read_adapter_array_t
)brace
id|diva_didd_read_adapter_array_t
suffix:semicolon
multiline_comment|/******************************************************************************/
DECL|macro|IDI_SYNC_REQ_XDI_GET_STREAM
mdefine_line|#define IDI_SYNC_REQ_XDI_GET_STREAM    0x91
DECL|macro|DIVA_XDI_SYNCHRONOUS_SERVICE
mdefine_line|#define DIVA_XDI_SYNCHRONOUS_SERVICE   0x01
DECL|macro|DIVA_XDI_DMA_SERVICE
mdefine_line|#define DIVA_XDI_DMA_SERVICE           0x02
DECL|macro|DIVA_XDI_AUTO_SERVICE
mdefine_line|#define DIVA_XDI_AUTO_SERVICE          0x03
DECL|macro|DIVA_ISTREAM_COMPLETE_NOTIFY
mdefine_line|#define DIVA_ISTREAM_COMPLETE_NOTIFY   0
DECL|macro|DIVA_ISTREAM_COMPLETE_READ
mdefine_line|#define DIVA_ISTREAM_COMPLETE_READ     1
DECL|macro|DIVA_ISTREAM_COMPLETE_WRITE
mdefine_line|#define DIVA_ISTREAM_COMPLETE_WRITE    2
DECL|struct|_diva_xdi_stream_interface
r_typedef
r_struct
id|_diva_xdi_stream_interface
(brace
DECL|member|Id
r_int
r_char
id|Id
suffix:semicolon
multiline_comment|/* filled by XDI client */
DECL|member|provided_service
r_int
r_char
id|provided_service
suffix:semicolon
multiline_comment|/* filled by XDI        */
DECL|member|requested_service
r_int
r_char
id|requested_service
suffix:semicolon
multiline_comment|/* filled by XDI Client */
DECL|member|xdi_context
r_void
op_star
id|xdi_context
suffix:semicolon
multiline_comment|/* filled by XDI     */
DECL|member|client_context
r_void
op_star
id|client_context
suffix:semicolon
multiline_comment|/* filled by XDI client */
DECL|member|write
r_int
(paren
op_star
id|write
)paren
(paren
r_void
op_star
id|context
comma
r_int
id|Id
comma
r_void
op_star
id|data
comma
r_int
id|length
comma
r_int
id|final
comma
id|byte
id|usr1
comma
id|byte
id|usr2
)paren
suffix:semicolon
DECL|member|read
r_int
(paren
op_star
id|read
)paren
(paren
r_void
op_star
id|context
comma
r_int
id|Id
comma
r_void
op_star
id|data
comma
r_int
id|max_length
comma
r_int
op_star
id|final
comma
id|byte
op_star
id|usr1
comma
id|byte
op_star
id|usr2
)paren
suffix:semicolon
DECL|member|complete
r_int
(paren
op_star
id|complete
)paren
(paren
r_void
op_star
id|client_context
comma
r_int
id|Id
comma
r_int
id|what
comma
r_void
op_star
id|data
comma
r_int
id|length
comma
r_int
op_star
id|final
)paren
suffix:semicolon
DECL|typedef|diva_xdi_stream_interface_t
)brace
id|diva_xdi_stream_interface_t
suffix:semicolon
multiline_comment|/******************************************************************************/
multiline_comment|/*&n; * IDI_SYNC_REQ_SERIAL_HOOK - special interface for the DIVA Mobile card&n; */
r_typedef
r_struct
DECL|member|LineState
(brace
r_int
r_char
id|LineState
suffix:semicolon
multiline_comment|/* Modem line state (STATUS_R) */
DECL|macro|SERIAL_GSM_CELL
mdefine_line|#define SERIAL_GSM_CELL 0x01   /* GSM or CELL cable attached  */
DECL|member|CardState
r_int
r_char
id|CardState
suffix:semicolon
multiline_comment|/* PCMCIA card state (0 = down) */
DECL|member|IsdnState
r_int
r_char
id|IsdnState
suffix:semicolon
multiline_comment|/* ISDN layer 1 state (0 = down)*/
DECL|member|HookState
r_int
r_char
id|HookState
suffix:semicolon
multiline_comment|/* current logical hook state */
DECL|macro|SERIAL_ON_HOOK
mdefine_line|#define SERIAL_ON_HOOK 0x02   /* set in DIVA CTRL_R register */
DECL|typedef|SERIAL_STATE
)brace
id|SERIAL_STATE
suffix:semicolon
DECL|typedef|SERIAL_INT_CB
r_typedef
r_int
(paren
op_star
id|SERIAL_INT_CB
)paren
(paren
r_void
op_star
id|Context
)paren
suffix:semicolon
DECL|typedef|SERIAL_DPC_CB
r_typedef
r_int
(paren
op_star
id|SERIAL_DPC_CB
)paren
(paren
r_void
op_star
id|Context
)paren
suffix:semicolon
DECL|typedef|SERIAL_I_SYNC
r_typedef
r_int
r_char
(paren
op_star
id|SERIAL_I_SYNC
)paren
(paren
r_void
op_star
id|Context
)paren
suffix:semicolon
r_typedef
r_struct
(brace
multiline_comment|/* &squot;Req&squot; and &squot;Rc&squot; must be at the same place as in the ENTITY struct */
DECL|member|Req
r_int
r_char
id|Req
suffix:semicolon
multiline_comment|/* request (must be always 0) */
DECL|member|Rc
r_int
r_char
id|Rc
suffix:semicolon
multiline_comment|/* return code (is the request) */
DECL|member|Function
r_int
r_char
id|Function
suffix:semicolon
multiline_comment|/* private function code  */
DECL|macro|SERIAL_HOOK_ATTACH
mdefine_line|#define SERIAL_HOOK_ATTACH 0x81
DECL|macro|SERIAL_HOOK_STATUS
mdefine_line|#define SERIAL_HOOK_STATUS 0x82
DECL|macro|SERIAL_HOOK_I_SYNC
mdefine_line|#define SERIAL_HOOK_I_SYNC 0x83
DECL|macro|SERIAL_HOOK_NOECHO
mdefine_line|#define SERIAL_HOOK_NOECHO 0x84
DECL|macro|SERIAL_HOOK_RING
mdefine_line|#define SERIAL_HOOK_RING 0x85
DECL|macro|SERIAL_HOOK_DETACH
mdefine_line|#define SERIAL_HOOK_DETACH 0x8f
DECL|member|Flags
r_int
r_char
id|Flags
suffix:semicolon
multiline_comment|/* function refinements   */
multiline_comment|/* parameters passed by the the ATTACH request      */
DECL|member|InterruptHandler
id|SERIAL_INT_CB
id|InterruptHandler
suffix:semicolon
multiline_comment|/* called on each interrupt  */
DECL|member|DeferredHandler
id|SERIAL_DPC_CB
id|DeferredHandler
suffix:semicolon
multiline_comment|/* called on hook state changes */
DECL|member|HandlerContext
r_void
op_star
id|HandlerContext
suffix:semicolon
multiline_comment|/* context for both handlers */
multiline_comment|/* return values for both the ATTACH and the STATUS request   */
DECL|member|IoBase
r_int
r_int
id|IoBase
suffix:semicolon
multiline_comment|/* IO port assigned to UART  */
DECL|member|State
id|SERIAL_STATE
id|State
suffix:semicolon
multiline_comment|/* parameters and return values for the I_SYNC function    */
DECL|member|SyncFunction
id|SERIAL_I_SYNC
id|SyncFunction
suffix:semicolon
multiline_comment|/* to be called synchronized */
DECL|member|SyncContext
r_void
op_star
id|SyncContext
suffix:semicolon
multiline_comment|/* context for this function */
DECL|member|SyncResult
r_int
r_char
id|SyncResult
suffix:semicolon
multiline_comment|/* return value of function  */
DECL|typedef|SERIAL_HOOK
)brace
id|SERIAL_HOOK
suffix:semicolon
multiline_comment|/*&n; * IDI_SYNC_REQ_XCHANGE_STATUS - exchange the status between IDI and WMP&n; * IDI_SYNC_REQ_RECONFIGURE - reconfiguration of IDI from WMP&n; */
r_typedef
r_struct
(brace
multiline_comment|/* &squot;Req&squot; and &squot;Rc&squot; must be at the same place as in the ENTITY struct */
DECL|member|Req
r_int
r_char
id|Req
suffix:semicolon
multiline_comment|/* request (must be always 0) */
DECL|member|Rc
r_int
r_char
id|Rc
suffix:semicolon
multiline_comment|/* return code (is the request) */
DECL|macro|DRIVER_STATUS_BOOT
mdefine_line|#define DRIVER_STATUS_BOOT  0xA1
DECL|macro|DRIVER_STATUS_INIT_DEV
mdefine_line|#define DRIVER_STATUS_INIT_DEV 0xA2
DECL|macro|DRIVER_STATUS_RUNNING
mdefine_line|#define DRIVER_STATUS_RUNNING 0xA3
DECL|macro|DRIVER_STATUS_SHUTDOWN
mdefine_line|#define DRIVER_STATUS_SHUTDOWN 0xAF
DECL|macro|DRIVER_STATUS_TRAPPED
mdefine_line|#define DRIVER_STATUS_TRAPPED 0xAE
DECL|member|wmpStatus
r_int
r_char
id|wmpStatus
suffix:semicolon
multiline_comment|/* exported by WMP              */
DECL|member|idiStatus
r_int
r_char
id|idiStatus
suffix:semicolon
multiline_comment|/* exported by IDI              */
DECL|member|wizProto
r_int
r_int
id|wizProto
suffix:semicolon
multiline_comment|/* from WMP registry to IDI     */
multiline_comment|/* the cardtype value is defined by cardtype.h */
DECL|member|cardType
r_int
r_int
id|cardType
suffix:semicolon
multiline_comment|/* from IDI registry to WMP     */
DECL|member|nt2
r_int
r_int
id|nt2
suffix:semicolon
multiline_comment|/* from IDI registry to WMP     */
DECL|member|permanent
r_int
r_int
id|permanent
suffix:semicolon
multiline_comment|/* from IDI registry to WMP     */
DECL|member|stableL2
r_int
r_int
id|stableL2
suffix:semicolon
multiline_comment|/* from IDI registry to WMP     */
DECL|member|tei
r_int
r_int
id|tei
suffix:semicolon
multiline_comment|/* from IDI registry to WMP     */
DECL|macro|CRC4_MASK
mdefine_line|#define CRC4_MASK   0x00000003
DECL|macro|L1_TRISTATE_MASK
mdefine_line|#define L1_TRISTATE_MASK 0x00000004
DECL|macro|WATCHDOG_MASK
mdefine_line|#define WATCHDOG_MASK  0x00000008
DECL|macro|NO_ORDER_CHECK_MASK
mdefine_line|#define NO_ORDER_CHECK_MASK 0x00000010
DECL|macro|LOW_CHANNEL_MASK
mdefine_line|#define LOW_CHANNEL_MASK 0x00000020
DECL|macro|NO_HSCX30_MASK
mdefine_line|#define NO_HSCX30_MASK  0x00000040
DECL|macro|MODE_MASK
mdefine_line|#define MODE_MASK   0x00000080
DECL|macro|SET_BOARD
mdefine_line|#define SET_BOARD   0x00001000
DECL|macro|SET_CRC4
mdefine_line|#define SET_CRC4   0x00030000
DECL|macro|SET_L1_TRISTATE
mdefine_line|#define SET_L1_TRISTATE  0x00040000
DECL|macro|SET_WATCHDOG
mdefine_line|#define SET_WATCHDOG  0x00080000
DECL|macro|SET_NO_ORDER_CHECK
mdefine_line|#define SET_NO_ORDER_CHECK 0x00100000
DECL|macro|SET_LOW_CHANNEL
mdefine_line|#define SET_LOW_CHANNEL  0x00200000
DECL|macro|SET_NO_HSCX30
mdefine_line|#define SET_NO_HSCX30  0x00400000
DECL|macro|SET_MODE
mdefine_line|#define SET_MODE   0x00800000
DECL|macro|SET_PROTO
mdefine_line|#define SET_PROTO   0x02000000
DECL|macro|SET_CARDTYPE
mdefine_line|#define SET_CARDTYPE  0x04000000
DECL|macro|SET_NT2
mdefine_line|#define SET_NT2    0x08000000
DECL|macro|SET_PERMANENT
mdefine_line|#define SET_PERMANENT  0x10000000
DECL|macro|SET_STABLEL2
mdefine_line|#define SET_STABLEL2  0x20000000
DECL|macro|SET_TEI
mdefine_line|#define SET_TEI    0x40000000
DECL|macro|SET_NUMBERLEN
mdefine_line|#define SET_NUMBERLEN  0x80000000
DECL|member|Flag
r_int
r_int
id|Flag
suffix:semicolon
multiline_comment|/* |31-Type-16|15-Mask-0| */
DECL|member|NumberLen
r_int
r_int
id|NumberLen
suffix:semicolon
multiline_comment|/* reconfiguration: union is empty */
r_union
(brace
r_struct
(brace
multiline_comment|/* possible reconfiguration, but ... ; SET_BOARD */
DECL|member|SerialNumber
r_int
r_int
id|SerialNumber
suffix:semicolon
DECL|member|pCardname
r_char
op_star
id|pCardname
suffix:semicolon
multiline_comment|/* di_defs.h: BOARD_NAME_LENGTH */
DECL|member|board
)brace
id|board
suffix:semicolon
r_struct
(brace
multiline_comment|/* reset: need resources */
DECL|member|pRawResources
r_void
op_star
id|pRawResources
suffix:semicolon
DECL|member|pXlatResources
r_void
op_star
id|pXlatResources
suffix:semicolon
DECL|member|res
)brace
id|res
suffix:semicolon
r_struct
(brace
multiline_comment|/* reconfiguration: wizProto == PROTTYPE_RBSCAS */
DECL|macro|GLARE_RESOLVE_MASK
mdefine_line|#define GLARE_RESOLVE_MASK 0x00000001
DECL|macro|DID_MASK
mdefine_line|#define DID_MASK   0x00000002
DECL|macro|BEARER_CAP_MASK
mdefine_line|#define BEARER_CAP_MASK  0x0000000c
DECL|macro|SET_GLARE_RESOLVE
mdefine_line|#define SET_GLARE_RESOLVE 0x00010000
DECL|macro|SET_DID
mdefine_line|#define SET_DID    0x00020000
DECL|macro|SET_BEARER_CAP
mdefine_line|#define SET_BEARER_CAP  0x000c0000
DECL|member|Flag
r_int
r_int
id|Flag
suffix:semicolon
multiline_comment|/* |31-Type-16|15-VALUE-0| */
DECL|member|DigitTimeout
r_int
r_int
id|DigitTimeout
suffix:semicolon
DECL|member|AnswerDelay
r_int
r_int
id|AnswerDelay
suffix:semicolon
DECL|member|rbs
)brace
id|rbs
suffix:semicolon
r_struct
(brace
multiline_comment|/* reconfiguration: wizProto == PROTTYPE_QSIG */
DECL|macro|CALL_REF_LENGTH1_MASK
mdefine_line|#define CALL_REF_LENGTH1_MASK 0x00000001
DECL|macro|BRI_CHANNEL_ID_MASK
mdefine_line|#define BRI_CHANNEL_ID_MASK  0x00000002
DECL|macro|SET_CALL_REF_LENGTH
mdefine_line|#define SET_CALL_REF_LENGTH  0x00010000
DECL|macro|SET_BRI_CHANNEL_ID
mdefine_line|#define SET_BRI_CHANNEL_ID  0x00020000
DECL|member|Flag
r_int
r_int
id|Flag
suffix:semicolon
multiline_comment|/* |31-Type-16|15-VALUE-0| */
DECL|member|qsig
)brace
id|qsig
suffix:semicolon
r_struct
(brace
multiline_comment|/* reconfiguration: NumberLen != 0 */
DECL|macro|SET_SPID1
mdefine_line|#define SET_SPID1   0x00010000
DECL|macro|SET_NUMBER1
mdefine_line|#define SET_NUMBER1   0x00020000
DECL|macro|SET_SUBADDRESS1
mdefine_line|#define SET_SUBADDRESS1  0x00040000
DECL|macro|SET_SPID2
mdefine_line|#define SET_SPID2   0x00100000
DECL|macro|SET_NUMBER2
mdefine_line|#define SET_NUMBER2   0x00200000
DECL|macro|SET_SUBADDRESS2
mdefine_line|#define SET_SUBADDRESS2  0x00400000
DECL|macro|MASK_SET
mdefine_line|#define MASK_SET   0xffff0000
DECL|member|Flag
r_int
r_int
id|Flag
suffix:semicolon
multiline_comment|/* |31-Type-16|15-Channel-0| */
DECL|member|pBuffer
r_int
r_char
op_star
id|pBuffer
suffix:semicolon
multiline_comment|/* number value */
DECL|member|isdnNo
)brace
id|isdnNo
suffix:semicolon
)brace
DECL|member|parms
id|parms
suffix:semicolon
DECL|typedef|isdnProps
)brace
id|isdnProps
suffix:semicolon
multiline_comment|/*&n; * IDI_SYNC_REQ_PORTDRV_HOOK - signal plug/unplug (Award Cardware only)&n; */
DECL|typedef|PORTDRV_HOOK_CB
r_typedef
r_void
(paren
op_star
id|PORTDRV_HOOK_CB
)paren
(paren
r_void
op_star
id|Context
comma
r_int
id|Plug
)paren
suffix:semicolon
r_typedef
r_struct
(brace
multiline_comment|/* &squot;Req&squot; and &squot;Rc&squot; must be at the same place as in the ENTITY struct */
DECL|member|Req
r_int
r_char
id|Req
suffix:semicolon
multiline_comment|/* request (must be always 0) */
DECL|member|Rc
r_int
r_char
id|Rc
suffix:semicolon
multiline_comment|/* return code (is the request) */
DECL|member|Function
r_int
r_char
id|Function
suffix:semicolon
multiline_comment|/* private function code  */
DECL|member|Flags
r_int
r_char
id|Flags
suffix:semicolon
multiline_comment|/* function refinements   */
DECL|member|Callback
id|PORTDRV_HOOK_CB
id|Callback
suffix:semicolon
multiline_comment|/* to be called on plug/unplug */
DECL|member|Context
r_void
op_star
id|Context
suffix:semicolon
multiline_comment|/* context for callback   */
DECL|member|Info
r_int
r_int
id|Info
suffix:semicolon
multiline_comment|/* more info if needed   */
DECL|typedef|PORTDRV_HOOK
)brace
id|PORTDRV_HOOK
suffix:semicolon
multiline_comment|/*  Codes for the &squot;Rc&squot; element in structure below. */
DECL|macro|SLI_INSTALL
mdefine_line|#define SLI_INSTALL     (0xA1)
DECL|macro|SLI_UNINSTALL
mdefine_line|#define SLI_UNINSTALL   (0xA2)
DECL|typedef|SLIENTRYPOINT
r_typedef
r_int
(paren
op_star
id|SLIENTRYPOINT
)paren
(paren
r_void
op_star
id|p3SignalAPI
comma
r_void
op_star
id|pContext
)paren
suffix:semicolon
r_typedef
r_struct
(brace
multiline_comment|/* &squot;Req&squot; and &squot;Rc&squot; must be at the same place as in the ENTITY struct */
DECL|member|Req
r_int
r_char
id|Req
suffix:semicolon
multiline_comment|/* request (must be always 0)   */
DECL|member|Rc
r_int
r_char
id|Rc
suffix:semicolon
multiline_comment|/* return code (is the request) */
DECL|member|Function
r_int
r_char
id|Function
suffix:semicolon
multiline_comment|/* private function code        */
DECL|member|Flags
r_int
r_char
id|Flags
suffix:semicolon
multiline_comment|/* function refinements         */
DECL|member|Callback
id|SLIENTRYPOINT
id|Callback
suffix:semicolon
multiline_comment|/* to be called on plug/unplug  */
DECL|member|Context
r_void
op_star
id|Context
suffix:semicolon
multiline_comment|/* context for callback         */
DECL|member|Info
r_int
r_int
id|Info
suffix:semicolon
multiline_comment|/* more info if needed          */
DECL|typedef|SLIENTRYPOINT_REQ
)brace
id|SLIENTRYPOINT_REQ
suffix:semicolon
multiline_comment|/******************************************************************************/
multiline_comment|/*&n; *  Definitions for DIVA USB&n; */
DECL|typedef|USB_SEND_REQ
r_typedef
r_int
(paren
op_star
id|USB_SEND_REQ
)paren
(paren
r_int
r_char
id|PipeIndex
comma
r_int
r_char
id|Type
comma
r_void
op_star
id|Data
comma
r_int
id|sizeData
)paren
suffix:semicolon
DECL|typedef|USB_START_DEV
r_typedef
r_int
(paren
op_star
id|USB_START_DEV
)paren
(paren
r_void
op_star
id|Adapter
comma
r_void
op_star
id|Ipac
)paren
suffix:semicolon
multiline_comment|/* called from WDM */
DECL|typedef|USB_RECV_NOTIFY
r_typedef
r_void
(paren
op_star
id|USB_RECV_NOTIFY
)paren
(paren
r_void
op_star
id|Ipac
comma
r_void
op_star
id|msg
)paren
suffix:semicolon
DECL|typedef|USB_XMIT_NOTIFY
r_typedef
r_void
(paren
op_star
id|USB_XMIT_NOTIFY
)paren
(paren
r_void
op_star
id|Ipac
comma
r_int
r_char
id|PipeIndex
)paren
suffix:semicolon
multiline_comment|/******************************************************************************/
multiline_comment|/*&n; * Parameter description for synchronous requests.&n; *&n; * Sorry, must repeat some parts of di_defs.h here because&n; * they are not defined for all operating environments&n; */
r_typedef
r_union
DECL|member|Entity
(brace
id|ENTITY
id|Entity
suffix:semicolon
r_struct
(brace
multiline_comment|/* &squot;Req&squot; and &squot;Rc&squot; are at the same place as in the ENTITY struct */
DECL|member|Req
r_int
r_char
id|Req
suffix:semicolon
multiline_comment|/* request (must be always 0) */
DECL|member|Rc
r_int
r_char
id|Rc
suffix:semicolon
multiline_comment|/* return code (is the request) */
DECL|member|Request
)brace
id|Request
suffix:semicolon
r_struct
DECL|member|Req
(brace
r_int
r_char
id|Req
suffix:semicolon
multiline_comment|/* request (must be always 0) */
DECL|member|Rc
r_int
r_char
id|Rc
suffix:semicolon
multiline_comment|/* return code (0x01)   */
DECL|member|name
r_int
r_char
id|name
(braket
id|BOARD_NAME_LENGTH
)braket
suffix:semicolon
DECL|member|GetName
)brace
id|GetName
suffix:semicolon
r_struct
DECL|member|Req
(brace
r_int
r_char
id|Req
suffix:semicolon
multiline_comment|/* request (must be always 0) */
DECL|member|Rc
r_int
r_char
id|Rc
suffix:semicolon
multiline_comment|/* return code (0x02)   */
DECL|member|serial
r_int
r_int
id|serial
suffix:semicolon
multiline_comment|/* serial number    */
DECL|member|GetSerial
)brace
id|GetSerial
suffix:semicolon
r_struct
DECL|member|Req
(brace
r_int
r_char
id|Req
suffix:semicolon
multiline_comment|/* request (must be always 0) */
DECL|member|Rc
r_int
r_char
id|Rc
suffix:semicolon
multiline_comment|/* return code (0x02)   */
DECL|member|lineIdx
r_int
r_int
id|lineIdx
suffix:semicolon
multiline_comment|/* line, 0 if card has only one */
DECL|member|GetLineIdx
)brace
id|GetLineIdx
suffix:semicolon
r_struct
DECL|member|Req
(brace
r_int
r_char
id|Req
suffix:semicolon
multiline_comment|/* request (must be always 0) */
DECL|member|Rc
r_int
r_char
id|Rc
suffix:semicolon
multiline_comment|/* return code (0x02)   */
DECL|member|cardtype
r_int
r_int
id|cardtype
suffix:semicolon
multiline_comment|/* card type        */
DECL|member|GetCardType
)brace
id|GetCardType
suffix:semicolon
r_struct
DECL|member|command
(brace
r_int
r_int
id|command
suffix:semicolon
multiline_comment|/* command = 0x0300 */
DECL|member|dummy
r_int
r_int
id|dummy
suffix:semicolon
multiline_comment|/* not used */
DECL|member|callback
id|IDI_CALL
id|callback
suffix:semicolon
multiline_comment|/* routine to call back */
DECL|member|contxt
id|ENTITY
op_star
id|contxt
suffix:semicolon
multiline_comment|/* ptr to entity to use */
DECL|member|PostCall
)brace
id|PostCall
suffix:semicolon
r_struct
DECL|member|Req
(brace
r_int
r_char
id|Req
suffix:semicolon
multiline_comment|/* request (must be always 0) */
DECL|member|Rc
r_int
r_char
id|Rc
suffix:semicolon
multiline_comment|/* return code (0x04)   */
DECL|member|pcm
r_int
r_char
id|pcm
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* buffer (a pc_maint struct) */
DECL|member|GetXlog
)brace
id|GetXlog
suffix:semicolon
r_struct
DECL|member|Req
(brace
r_int
r_char
id|Req
suffix:semicolon
multiline_comment|/* request (must be always 0) */
DECL|member|Rc
r_int
r_char
id|Rc
suffix:semicolon
multiline_comment|/* return code (0x05)   */
DECL|member|features
r_int
r_int
id|features
suffix:semicolon
multiline_comment|/* feature defines see below */
DECL|member|GetFeatures
)brace
id|GetFeatures
suffix:semicolon
DECL|member|SerialHook
id|SERIAL_HOOK
id|SerialHook
suffix:semicolon
multiline_comment|/* Added for DIVA USB */
r_struct
DECL|member|Req
(brace
r_int
r_char
id|Req
suffix:semicolon
DECL|member|Rc
r_int
r_char
id|Rc
suffix:semicolon
DECL|member|UsbSendRequest
id|USB_SEND_REQ
id|UsbSendRequest
suffix:semicolon
multiline_comment|/* function in Diva Usb WDM driver in usb_os.c, */
multiline_comment|/* called from usb_drv.c to send a message to our device */
multiline_comment|/* eg UsbSendRequest (USB_PIPE_SIGNAL, USB_IPAC_START, 0, 0) ; */
DECL|member|usb_recv
id|USB_RECV_NOTIFY
id|usb_recv
suffix:semicolon
multiline_comment|/* called from usb_os.c to pass a received message and ptr to IPAC */
multiline_comment|/* on to usb_drv.c by a call to usb_recv(). */
DECL|member|usb_xmit
id|USB_XMIT_NOTIFY
id|usb_xmit
suffix:semicolon
multiline_comment|/* called from usb_os.c in DivaUSB.sys WDM to indicate a completed transmit */
multiline_comment|/* to usb_drv.c by a call to usb_xmit(). */
DECL|member|UsbStartDevice
id|USB_START_DEV
id|UsbStartDevice
suffix:semicolon
multiline_comment|/* Start the USB Device, in usb_os.c */
DECL|member|callback
id|IDI_CALL
id|callback
suffix:semicolon
multiline_comment|/* routine to call back */
DECL|member|contxt
id|ENTITY
op_star
id|contxt
suffix:semicolon
multiline_comment|/* ptr to entity to use */
DECL|member|ipac_ptr
r_void
op_star
op_star
id|ipac_ptr
suffix:semicolon
multiline_comment|/* pointer to struct IPAC in VxD */
DECL|member|Usb_Msg_old
)brace
id|Usb_Msg_old
suffix:semicolon
multiline_comment|/* message used by WDM and VXD to pass pointers of function and IPAC* */
r_struct
DECL|member|Req
(brace
r_int
r_char
id|Req
suffix:semicolon
DECL|member|Rc
r_int
r_char
id|Rc
suffix:semicolon
DECL|member|pUsbSendRequest
id|USB_SEND_REQ
id|pUsbSendRequest
suffix:semicolon
multiline_comment|/* function in Diva Usb WDM driver in usb_os.c, */
multiline_comment|/* called from usb_drv.c to send a message to our device */
multiline_comment|/* eg UsbSendRequest (USB_PIPE_SIGNAL, USB_IPAC_START, 0, 0) ; */
DECL|member|p_usb_recv
id|USB_RECV_NOTIFY
id|p_usb_recv
suffix:semicolon
multiline_comment|/* called from usb_os.c to pass a received message and ptr to IPAC */
multiline_comment|/* on to usb_drv.c by a call to usb_recv(). */
DECL|member|p_usb_xmit
id|USB_XMIT_NOTIFY
id|p_usb_xmit
suffix:semicolon
multiline_comment|/* called from usb_os.c in DivaUSB.sys WDM to indicate a completed transmit */
multiline_comment|/* to usb_drv.c by a call to usb_xmit().*/
DECL|member|ipac_ptr
r_void
op_star
id|ipac_ptr
suffix:semicolon
multiline_comment|/* &amp;Diva.ipac pointer to struct IPAC in VxD */
DECL|member|Usb_Msg
)brace
id|Usb_Msg
suffix:semicolon
DECL|member|PortdrvHook
id|PORTDRV_HOOK
id|PortdrvHook
suffix:semicolon
DECL|member|sliEntryPointReq
id|SLIENTRYPOINT_REQ
id|sliEntryPointReq
suffix:semicolon
r_struct
(brace
DECL|member|Req
r_int
r_char
id|Req
suffix:semicolon
DECL|member|Rc
r_int
r_char
id|Rc
suffix:semicolon
DECL|member|info
id|diva_xdi_stream_interface_t
id|info
suffix:semicolon
DECL|member|xdi_stream_info
)brace
id|xdi_stream_info
suffix:semicolon
r_struct
(brace
DECL|member|Req
r_int
r_char
id|Req
suffix:semicolon
DECL|member|Rc
r_int
r_char
id|Rc
suffix:semicolon
DECL|member|info
id|diva_xdi_get_extended_xdi_features_t
id|info
suffix:semicolon
DECL|member|xdi_extended_features
)brace
id|xdi_extended_features
suffix:semicolon
r_struct
(brace
DECL|member|Req
r_int
r_char
id|Req
suffix:semicolon
DECL|member|Rc
r_int
r_char
id|Rc
suffix:semicolon
DECL|member|info
id|diva_xdi_get_adapter_sdram_bar_t
id|info
suffix:semicolon
DECL|member|xdi_sdram_bar
)brace
id|xdi_sdram_bar
suffix:semicolon
r_struct
(brace
DECL|member|Req
r_int
r_char
id|Req
suffix:semicolon
DECL|member|Rc
r_int
r_char
id|Rc
suffix:semicolon
DECL|member|info
id|diva_xdi_get_capi_parameters_t
id|info
suffix:semicolon
DECL|member|xdi_capi_prms
)brace
id|xdi_capi_prms
suffix:semicolon
r_struct
(brace
DECL|member|e
id|ENTITY
id|e
suffix:semicolon
DECL|member|info
id|diva_didd_adapter_notify_t
id|info
suffix:semicolon
DECL|member|didd_notify
)brace
id|didd_notify
suffix:semicolon
r_struct
(brace
DECL|member|e
id|ENTITY
id|e
suffix:semicolon
DECL|member|info
id|diva_didd_add_adapter_t
id|info
suffix:semicolon
DECL|member|didd_add_adapter
)brace
id|didd_add_adapter
suffix:semicolon
r_struct
(brace
DECL|member|e
id|ENTITY
id|e
suffix:semicolon
DECL|member|info
id|diva_didd_remove_adapter_t
id|info
suffix:semicolon
DECL|member|didd_remove_adapter
)brace
id|didd_remove_adapter
suffix:semicolon
r_struct
(brace
DECL|member|e
id|ENTITY
id|e
suffix:semicolon
DECL|member|info
id|diva_didd_read_adapter_array_t
id|info
suffix:semicolon
DECL|member|didd_read_adapter_array
)brace
id|didd_read_adapter_array
suffix:semicolon
r_struct
(brace
DECL|member|Req
r_int
r_char
id|Req
suffix:semicolon
DECL|member|Rc
r_int
r_char
id|Rc
suffix:semicolon
DECL|member|info
id|diva_xdi_get_logical_adapter_number_s_t
id|info
suffix:semicolon
DECL|member|xdi_logical_adapter_number
)brace
id|xdi_logical_adapter_number
suffix:semicolon
r_struct
(brace
DECL|member|Req
r_int
r_char
id|Req
suffix:semicolon
DECL|member|Rc
r_int
r_char
id|Rc
suffix:semicolon
DECL|member|info
id|diva_xdi_dma_descriptor_operation_t
id|info
suffix:semicolon
DECL|member|xdi_dma_descriptor_operation
)brace
id|xdi_dma_descriptor_operation
suffix:semicolon
DECL|typedef|IDI_SYNC_REQ
)brace
id|IDI_SYNC_REQ
suffix:semicolon
multiline_comment|/******************************************************************************/
macro_line|#endif /* __DIVA_SYNC__H */  
eof
