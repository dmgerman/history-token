multiline_comment|/*&n; *&n;  Copyright (c) Eicon Networks, 2002.&n; *&n;  This source file is supplied for the use with&n;  Eicon Networks range of DIVA Server Adapters.&n; *&n;  Eicon File Revision :    2.1&n; *&n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2, or (at your option)&n;  any later version.&n; *&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY&n;  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n;  See the GNU General Public License for more details.&n; *&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef _INC_CAPI20  
DECL|macro|_INC_CAPI20
mdefine_line|#define _INC_CAPI20
multiline_comment|/* operations on message queues                             */
multiline_comment|/* the common device type for CAPI20 drivers */
DECL|macro|FILE_DEVICE_CAPI20
mdefine_line|#define FILE_DEVICE_CAPI20 0x8001
multiline_comment|/* DEVICE_CONTROL codes for user and kernel mode applications */
DECL|macro|CAPI20_CTL_REGISTER
mdefine_line|#define CAPI20_CTL_REGISTER             0x0801
DECL|macro|CAPI20_CTL_RELEASE
mdefine_line|#define CAPI20_CTL_RELEASE              0x0802
DECL|macro|CAPI20_CTL_GET_MANUFACTURER
mdefine_line|#define CAPI20_CTL_GET_MANUFACTURER     0x0805
DECL|macro|CAPI20_CTL_GET_VERSION
mdefine_line|#define CAPI20_CTL_GET_VERSION          0x0806
DECL|macro|CAPI20_CTL_GET_SERIAL
mdefine_line|#define CAPI20_CTL_GET_SERIAL           0x0807
DECL|macro|CAPI20_CTL_GET_PROFILE
mdefine_line|#define CAPI20_CTL_GET_PROFILE          0x0808
multiline_comment|/* INTERNAL_DEVICE_CONTROL codes for kernel mode applicatios only */
DECL|macro|CAPI20_CTL_PUT_MESSAGE
mdefine_line|#define CAPI20_CTL_PUT_MESSAGE          0x0803
DECL|macro|CAPI20_CTL_GET_MESSAGE
mdefine_line|#define CAPI20_CTL_GET_MESSAGE          0x0804
multiline_comment|/* the wrapped codes as required by the system */
DECL|macro|CAPI_CTL_CODE
mdefine_line|#define CAPI_CTL_CODE(f,m)              CTL_CODE(FILE_DEVICE_CAPI20,f,m,FILE_ANY_ACCESS)
DECL|macro|IOCTL_CAPI_REGISTER
mdefine_line|#define IOCTL_CAPI_REGISTER             CAPI_CTL_CODE(CAPI20_CTL_REGISTER,METHOD_BUFFERED)
DECL|macro|IOCTL_CAPI_RELEASE
mdefine_line|#define IOCTL_CAPI_RELEASE              CAPI_CTL_CODE(CAPI20_CTL_RELEASE,METHOD_BUFFERED)
DECL|macro|IOCTL_CAPI_GET_MANUFACTURER
mdefine_line|#define IOCTL_CAPI_GET_MANUFACTURER     CAPI_CTL_CODE(CAPI20_CTL_GET_MANUFACTURER,METHOD_BUFFERED)
DECL|macro|IOCTL_CAPI_GET_VERSION
mdefine_line|#define IOCTL_CAPI_GET_VERSION          CAPI_CTL_CODE(CAPI20_CTL_GET_VERSION,METHOD_BUFFERED)
DECL|macro|IOCTL_CAPI_GET_SERIAL
mdefine_line|#define IOCTL_CAPI_GET_SERIAL           CAPI_CTL_CODE(CAPI20_CTL_GET_SERIAL,METHOD_BUFFERED)
DECL|macro|IOCTL_CAPI_GET_PROFILE
mdefine_line|#define IOCTL_CAPI_GET_PROFILE          CAPI_CTL_CODE(CAPI20_CTL_GET_PROFILE,METHOD_BUFFERED)
DECL|macro|IOCTL_CAPI_PUT_MESSAGE
mdefine_line|#define IOCTL_CAPI_PUT_MESSAGE          CAPI_CTL_CODE(CAPI20_CTL_PUT_MESSAGE,METHOD_BUFFERED)
DECL|macro|IOCTL_CAPI_GET_MESSAGE
mdefine_line|#define IOCTL_CAPI_GET_MESSAGE          CAPI_CTL_CODE(CAPI20_CTL_GET_MESSAGE,METHOD_BUFFERED)
DECL|struct|divas_capi_register_params
r_struct
id|divas_capi_register_params
(brace
DECL|member|MessageBufferSize
id|word
id|MessageBufferSize
suffix:semicolon
DECL|member|maxLogicalConnection
id|word
id|maxLogicalConnection
suffix:semicolon
DECL|member|maxBDataBlocks
id|word
id|maxBDataBlocks
suffix:semicolon
DECL|member|maxBDataLen
id|word
id|maxBDataLen
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|divas_capi_version
r_struct
id|divas_capi_version
(brace
DECL|member|CapiMajor
id|word
id|CapiMajor
suffix:semicolon
DECL|member|CapiMinor
id|word
id|CapiMinor
suffix:semicolon
DECL|member|ManuMajor
id|word
id|ManuMajor
suffix:semicolon
DECL|member|ManuMinor
id|word
id|ManuMinor
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|api_profile_s
r_typedef
r_struct
id|api_profile_s
(brace
DECL|member|Number
id|word
id|Number
suffix:semicolon
DECL|member|Channels
id|word
id|Channels
suffix:semicolon
DECL|member|Global_Options
id|dword
id|Global_Options
suffix:semicolon
DECL|member|B1_Protocols
id|dword
id|B1_Protocols
suffix:semicolon
DECL|member|B2_Protocols
id|dword
id|B2_Protocols
suffix:semicolon
DECL|member|B3_Protocols
id|dword
id|B3_Protocols
suffix:semicolon
DECL|typedef|API_PROFILE
)brace
id|API_PROFILE
suffix:semicolon
multiline_comment|/* ISDN Common API message types                            */
DECL|macro|_ALERT_R
mdefine_line|#define _ALERT_R                        0x8001
DECL|macro|_CONNECT_R
mdefine_line|#define _CONNECT_R                      0x8002
DECL|macro|_CONNECT_I
mdefine_line|#define _CONNECT_I                      0x8202
DECL|macro|_CONNECT_ACTIVE_I
mdefine_line|#define _CONNECT_ACTIVE_I               0x8203
DECL|macro|_DISCONNECT_R
mdefine_line|#define _DISCONNECT_R                   0x8004
DECL|macro|_DISCONNECT_I
mdefine_line|#define _DISCONNECT_I                   0x8204
DECL|macro|_LISTEN_R
mdefine_line|#define _LISTEN_R                       0x8005
DECL|macro|_INFO_R
mdefine_line|#define _INFO_R                         0x8008
DECL|macro|_INFO_I
mdefine_line|#define _INFO_I                         0x8208
DECL|macro|_SELECT_B_REQ
mdefine_line|#define _SELECT_B_REQ                   0x8041
DECL|macro|_FACILITY_R
mdefine_line|#define _FACILITY_R                     0x8080
DECL|macro|_FACILITY_I
mdefine_line|#define _FACILITY_I                     0x8280
DECL|macro|_CONNECT_B3_R
mdefine_line|#define _CONNECT_B3_R                   0x8082
DECL|macro|_CONNECT_B3_I
mdefine_line|#define _CONNECT_B3_I                   0x8282
DECL|macro|_CONNECT_B3_ACTIVE_I
mdefine_line|#define _CONNECT_B3_ACTIVE_I            0x8283
DECL|macro|_DISCONNECT_B3_R
mdefine_line|#define _DISCONNECT_B3_R                0x8084
DECL|macro|_DISCONNECT_B3_I
mdefine_line|#define _DISCONNECT_B3_I                0x8284
DECL|macro|_DATA_B3_R
mdefine_line|#define _DATA_B3_R                      0x8086
DECL|macro|_DATA_B3_I
mdefine_line|#define _DATA_B3_I                      0x8286
DECL|macro|_RESET_B3_R
mdefine_line|#define _RESET_B3_R                     0x8087
DECL|macro|_RESET_B3_I
mdefine_line|#define _RESET_B3_I                     0x8287
DECL|macro|_CONNECT_B3_T90_ACTIVE_I
mdefine_line|#define _CONNECT_B3_T90_ACTIVE_I        0x8288
DECL|macro|_MANUFACTURER_R
mdefine_line|#define _MANUFACTURER_R                 0x80ff
DECL|macro|_MANUFACTURER_I
mdefine_line|#define _MANUFACTURER_I                 0x82ff
multiline_comment|/* OR this to convert a REQUEST to a CONFIRM                */
DECL|macro|CONFIRM
mdefine_line|#define CONFIRM                 0x0100
multiline_comment|/* OR this to convert a INDICATION to a RESPONSE            */
DECL|macro|RESPONSE
mdefine_line|#define RESPONSE                0x0100
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* diehl isdn private MANUFACTURER codes                            */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|_DI_MANU_ID
mdefine_line|#define _DI_MANU_ID             0x44444944
DECL|macro|_DI_ASSIGN_PLCI
mdefine_line|#define _DI_ASSIGN_PLCI         0x0001
DECL|macro|_DI_ADV_CODEC
mdefine_line|#define _DI_ADV_CODEC           0x0002
DECL|macro|_DI_DSP_CTRL
mdefine_line|#define _DI_DSP_CTRL            0x0003
DECL|macro|_DI_SIG_CTRL
mdefine_line|#define _DI_SIG_CTRL            0x0004
DECL|macro|_DI_RXT_CTRL
mdefine_line|#define _DI_RXT_CTRL            0x0005
DECL|macro|_DI_IDI_CTRL
mdefine_line|#define _DI_IDI_CTRL            0x0006
DECL|macro|_DI_CFG_CTRL
mdefine_line|#define _DI_CFG_CTRL            0x0007
DECL|macro|_DI_REMOVE_CODEC
mdefine_line|#define _DI_REMOVE_CODEC        0x0008
DECL|macro|_DI_OPTIONS_REQUEST
mdefine_line|#define _DI_OPTIONS_REQUEST     0x0009
DECL|macro|_DI_SSEXT_CTRL
mdefine_line|#define _DI_SSEXT_CTRL          0x000a
DECL|macro|_DI_NEGOTIATE_B3
mdefine_line|#define _DI_NEGOTIATE_B3        0x000b
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* parameter structures                                             */
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* ALERT-REQUEST                                            */
r_typedef
r_struct
(brace
DECL|member|structs
id|byte
id|structs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Additional Info */
DECL|typedef|_ALT_REQP
)brace
id|_ALT_REQP
suffix:semicolon
multiline_comment|/* ALERT-CONFIRM                                            */
r_typedef
r_struct
(brace
DECL|member|Info
id|word
id|Info
suffix:semicolon
DECL|typedef|_ALT_CONP
)brace
id|_ALT_CONP
suffix:semicolon
multiline_comment|/* CONNECT-REQUEST                                          */
r_typedef
r_struct
(brace
DECL|member|CIP_Value
id|word
id|CIP_Value
suffix:semicolon
DECL|member|structs
id|byte
id|structs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Called party number,&n;                           Called party subaddress,&n;                           Calling party number,&n;                           Calling party subaddress,&n;                           B_protocol,&n;                           BC,&n;                           LLC,&n;                           HLC,&n;                           Additional Info */
DECL|typedef|_CON_REQP
)brace
id|_CON_REQP
suffix:semicolon
multiline_comment|/* CONNECT-CONFIRM                                          */
r_typedef
r_struct
(brace
DECL|member|Info
id|word
id|Info
suffix:semicolon
DECL|typedef|_CON_CONP
)brace
id|_CON_CONP
suffix:semicolon
multiline_comment|/* CONNECT-INDICATION                                       */
r_typedef
r_struct
(brace
DECL|member|CIP_Value
id|word
id|CIP_Value
suffix:semicolon
DECL|member|structs
id|byte
id|structs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Called party number,&n;                           Called party subaddress,&n;                           Calling party number,&n;                           Calling party subaddress,&n;                           BC,&n;                           LLC,&n;                           HLC,&n;                           Additional Info */
DECL|typedef|_CON_INDP
)brace
id|_CON_INDP
suffix:semicolon
multiline_comment|/* CONNECT-RESPONSE                                         */
r_typedef
r_struct
(brace
DECL|member|Accept
id|word
id|Accept
suffix:semicolon
DECL|member|structs
id|byte
id|structs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* B_protocol,&n;                           Connected party number,&n;                           Connected party subaddress,&n;                           LLC */
DECL|typedef|_CON_RESP
)brace
id|_CON_RESP
suffix:semicolon
multiline_comment|/* CONNECT-ACTIVE-INDICATION                                */
r_typedef
r_struct
(brace
DECL|member|structs
id|byte
id|structs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Connected party number,&n;                           Connected party subaddress,&n;                           LLC */
DECL|typedef|_CON_A_INDP
)brace
id|_CON_A_INDP
suffix:semicolon
multiline_comment|/* CONNECT-ACTIVE-RESPONSE                                  */
r_typedef
r_struct
(brace
DECL|member|structs
id|byte
id|structs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* empty */
DECL|typedef|_CON_A_RESP
)brace
id|_CON_A_RESP
suffix:semicolon
multiline_comment|/* DISCONNECT-REQUEST                                       */
r_typedef
r_struct
(brace
DECL|member|structs
id|byte
id|structs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Additional Info */
DECL|typedef|_DIS_REQP
)brace
id|_DIS_REQP
suffix:semicolon
multiline_comment|/* DISCONNECT-CONFIRM                                       */
r_typedef
r_struct
(brace
DECL|member|Info
id|word
id|Info
suffix:semicolon
DECL|typedef|_DIS_CONP
)brace
id|_DIS_CONP
suffix:semicolon
multiline_comment|/* DISCONNECT-INDICATION                                    */
r_typedef
r_struct
(brace
DECL|member|Info
id|word
id|Info
suffix:semicolon
DECL|typedef|_DIS_INDP
)brace
id|_DIS_INDP
suffix:semicolon
multiline_comment|/* DISCONNECT-RESPONSE                                      */
r_typedef
r_struct
(brace
DECL|member|structs
id|byte
id|structs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* empty */
DECL|typedef|_DIS_RESP
)brace
id|_DIS_RESP
suffix:semicolon
multiline_comment|/* LISTEN-REQUEST                                           */
r_typedef
r_struct
(brace
DECL|member|Info_Mask
id|dword
id|Info_Mask
suffix:semicolon
DECL|member|CIP_Mask
id|dword
id|CIP_Mask
suffix:semicolon
DECL|member|structs
id|byte
id|structs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Calling party number,&n;                           Calling party subaddress */
DECL|typedef|_LIS_REQP
)brace
id|_LIS_REQP
suffix:semicolon
multiline_comment|/* LISTEN-CONFIRM                                           */
r_typedef
r_struct
(brace
DECL|member|Info
id|word
id|Info
suffix:semicolon
DECL|typedef|_LIS_CONP
)brace
id|_LIS_CONP
suffix:semicolon
multiline_comment|/* INFO-REQUEST                                             */
r_typedef
r_struct
(brace
DECL|member|structs
id|byte
id|structs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Called party number,&n;                           Additional Info */
DECL|typedef|_INF_REQP
)brace
id|_INF_REQP
suffix:semicolon
multiline_comment|/* INFO-CONFIRM                                             */
r_typedef
r_struct
(brace
DECL|member|Info
id|word
id|Info
suffix:semicolon
DECL|typedef|_INF_CONP
)brace
id|_INF_CONP
suffix:semicolon
multiline_comment|/* INFO-INDICATION                                          */
r_typedef
r_struct
(brace
DECL|member|Number
id|word
id|Number
suffix:semicolon
DECL|member|structs
id|byte
id|structs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Info element */
DECL|typedef|_INF_INDP
)brace
id|_INF_INDP
suffix:semicolon
multiline_comment|/* INFO-RESPONSE                                            */
r_typedef
r_struct
(brace
DECL|member|structs
id|byte
id|structs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* empty */
DECL|typedef|_INF_RESP
)brace
id|_INF_RESP
suffix:semicolon
multiline_comment|/* SELECT-B-REQUEST                                         */
r_typedef
r_struct
(brace
DECL|member|structs
id|byte
id|structs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* B-protocol */
DECL|typedef|_SEL_B_REQP
)brace
id|_SEL_B_REQP
suffix:semicolon
multiline_comment|/* SELECT-B-CONFIRM                                         */
r_typedef
r_struct
(brace
DECL|member|Info
id|word
id|Info
suffix:semicolon
DECL|typedef|_SEL_B_CONP
)brace
id|_SEL_B_CONP
suffix:semicolon
multiline_comment|/* FACILITY-REQUEST */
r_typedef
r_struct
(brace
DECL|member|Selector
id|word
id|Selector
suffix:semicolon
DECL|member|structs
id|byte
id|structs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Facility parameters */
DECL|typedef|_FAC_REQP
)brace
id|_FAC_REQP
suffix:semicolon
multiline_comment|/* FACILITY-CONFIRM STRUCT FOR SUPPLEMENT. SERVICES */
r_typedef
r_struct
(brace
DECL|member|struct_length
id|byte
id|struct_length
suffix:semicolon
DECL|member|function
id|word
id|function
suffix:semicolon
DECL|member|length
id|byte
id|length
suffix:semicolon
DECL|member|SupplementaryServiceInfo
id|word
id|SupplementaryServiceInfo
suffix:semicolon
DECL|member|SupportedServices
id|dword
id|SupportedServices
suffix:semicolon
DECL|typedef|_FAC_CON_STRUCTS
)brace
id|_FAC_CON_STRUCTS
suffix:semicolon
multiline_comment|/* FACILITY-CONFIRM */
r_typedef
r_struct
(brace
DECL|member|Info
id|word
id|Info
suffix:semicolon
DECL|member|Selector
id|word
id|Selector
suffix:semicolon
DECL|member|structs
id|byte
id|structs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Facility parameters */
DECL|typedef|_FAC_CONP
)brace
id|_FAC_CONP
suffix:semicolon
multiline_comment|/* FACILITY-INDICATION */
r_typedef
r_struct
(brace
DECL|member|Selector
id|word
id|Selector
suffix:semicolon
DECL|member|structs
id|byte
id|structs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Facility parameters */
DECL|typedef|_FAC_INDP
)brace
id|_FAC_INDP
suffix:semicolon
multiline_comment|/* FACILITY-RESPONSE */
r_typedef
r_struct
(brace
DECL|member|Selector
id|word
id|Selector
suffix:semicolon
DECL|member|structs
id|byte
id|structs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Facility parameters */
DECL|typedef|_FAC_RESP
)brace
id|_FAC_RESP
suffix:semicolon
multiline_comment|/* CONNECT-B3-REQUEST                                       */
r_typedef
r_struct
(brace
DECL|member|structs
id|byte
id|structs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* NCPI */
DECL|typedef|_CON_B3_REQP
)brace
id|_CON_B3_REQP
suffix:semicolon
multiline_comment|/* CONNECT-B3-CONFIRM                                       */
r_typedef
r_struct
(brace
DECL|member|Info
id|word
id|Info
suffix:semicolon
DECL|typedef|_CON_B3_CONP
)brace
id|_CON_B3_CONP
suffix:semicolon
multiline_comment|/* CONNECT-B3-INDICATION                                    */
r_typedef
r_struct
(brace
DECL|member|structs
id|byte
id|structs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* NCPI */
DECL|typedef|_CON_B3_INDP
)brace
id|_CON_B3_INDP
suffix:semicolon
multiline_comment|/* CONNECT-B3-RESPONSE                                      */
r_typedef
r_struct
(brace
DECL|member|Accept
id|word
id|Accept
suffix:semicolon
DECL|member|structs
id|byte
id|structs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* NCPI */
DECL|typedef|_CON_B3_RESP
)brace
id|_CON_B3_RESP
suffix:semicolon
multiline_comment|/* CONNECT-B3-ACTIVE-INDICATION                             */
r_typedef
r_struct
(brace
DECL|member|structs
id|byte
id|structs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* NCPI */
DECL|typedef|_CON_B3_A_INDP
)brace
id|_CON_B3_A_INDP
suffix:semicolon
multiline_comment|/* CONNECT-B3-ACTIVE-RESPONSE                               */
r_typedef
r_struct
(brace
DECL|member|structs
id|byte
id|structs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* empty */
DECL|typedef|_CON_B3_A_RESP
)brace
id|_CON_B3_A_RESP
suffix:semicolon
multiline_comment|/* DISCONNECT-B3-REQUEST                                    */
r_typedef
r_struct
(brace
DECL|member|structs
id|byte
id|structs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* NCPI */
DECL|typedef|_DIS_B3_REQP
)brace
id|_DIS_B3_REQP
suffix:semicolon
multiline_comment|/* DISCONNECT-B3-CONFIRM                                    */
r_typedef
r_struct
(brace
DECL|member|Info
id|word
id|Info
suffix:semicolon
DECL|typedef|_DIS_B3_CONP
)brace
id|_DIS_B3_CONP
suffix:semicolon
multiline_comment|/* DISCONNECT-B3-INDICATION                                 */
r_typedef
r_struct
(brace
DECL|member|Info
id|word
id|Info
suffix:semicolon
DECL|member|structs
id|byte
id|structs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* NCPI */
DECL|typedef|_DIS_B3_INDP
)brace
id|_DIS_B3_INDP
suffix:semicolon
multiline_comment|/* DISCONNECT-B3-RESPONSE                                   */
r_typedef
r_struct
(brace
DECL|member|structs
id|byte
id|structs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* empty */
DECL|typedef|_DIS_B3_RESP
)brace
id|_DIS_B3_RESP
suffix:semicolon
multiline_comment|/* DATA-B3-REQUEST                                          */
r_typedef
r_struct
(brace
DECL|member|Data
id|dword
id|Data
suffix:semicolon
DECL|member|Data_Length
id|word
id|Data_Length
suffix:semicolon
DECL|member|Number
id|word
id|Number
suffix:semicolon
DECL|member|Flags
id|word
id|Flags
suffix:semicolon
DECL|typedef|_DAT_B3_REQP
)brace
id|_DAT_B3_REQP
suffix:semicolon
multiline_comment|/* DATA-B3-REQUEST 64 BIT Systems                           */
r_typedef
r_struct
(brace
DECL|member|Data
id|dword
id|Data
suffix:semicolon
DECL|member|Data_Length
id|word
id|Data_Length
suffix:semicolon
DECL|member|Number
id|word
id|Number
suffix:semicolon
DECL|member|Flags
id|word
id|Flags
suffix:semicolon
DECL|member|pData
r_void
op_star
id|pData
suffix:semicolon
DECL|typedef|_DAT_B3_REQ64P
)brace
id|_DAT_B3_REQ64P
suffix:semicolon
multiline_comment|/* DATA-B3-CONFIRM                                          */
r_typedef
r_struct
(brace
DECL|member|Number
id|word
id|Number
suffix:semicolon
DECL|member|Info
id|word
id|Info
suffix:semicolon
DECL|typedef|_DAT_B3_CONP
)brace
id|_DAT_B3_CONP
suffix:semicolon
multiline_comment|/* DATA-B3-INDICATION                                       */
r_typedef
r_struct
(brace
DECL|member|Data
id|dword
id|Data
suffix:semicolon
DECL|member|Data_Length
id|word
id|Data_Length
suffix:semicolon
DECL|member|Number
id|word
id|Number
suffix:semicolon
DECL|member|Flags
id|word
id|Flags
suffix:semicolon
DECL|typedef|_DAT_B3_INDP
)brace
id|_DAT_B3_INDP
suffix:semicolon
multiline_comment|/* DATA-B3-INDICATION  64 BIT Systems                       */
r_typedef
r_struct
(brace
DECL|member|Data
id|dword
id|Data
suffix:semicolon
DECL|member|Data_Length
id|word
id|Data_Length
suffix:semicolon
DECL|member|Number
id|word
id|Number
suffix:semicolon
DECL|member|Flags
id|word
id|Flags
suffix:semicolon
DECL|member|pData
r_void
op_star
id|pData
suffix:semicolon
DECL|typedef|_DAT_B3_IND64P
)brace
id|_DAT_B3_IND64P
suffix:semicolon
multiline_comment|/* DATA-B3-RESPONSE                                         */
r_typedef
r_struct
(brace
DECL|member|Number
id|word
id|Number
suffix:semicolon
DECL|typedef|_DAT_B3_RESP
)brace
id|_DAT_B3_RESP
suffix:semicolon
multiline_comment|/* RESET-B3-REQUEST                                         */
r_typedef
r_struct
(brace
DECL|member|structs
id|byte
id|structs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* NCPI */
DECL|typedef|_RES_B3_REQP
)brace
id|_RES_B3_REQP
suffix:semicolon
multiline_comment|/* RESET-B3-CONFIRM                                         */
r_typedef
r_struct
(brace
DECL|member|Info
id|word
id|Info
suffix:semicolon
DECL|typedef|_RES_B3_CONP
)brace
id|_RES_B3_CONP
suffix:semicolon
multiline_comment|/* RESET-B3-INDICATION                                      */
r_typedef
r_struct
(brace
DECL|member|structs
id|byte
id|structs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* NCPI */
DECL|typedef|_RES_B3_INDP
)brace
id|_RES_B3_INDP
suffix:semicolon
multiline_comment|/* RESET-B3-RESPONSE                                        */
r_typedef
r_struct
(brace
DECL|member|structs
id|byte
id|structs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* empty */
DECL|typedef|_RES_B3_RESP
)brace
id|_RES_B3_RESP
suffix:semicolon
multiline_comment|/* CONNECT-B3-T90-ACTIVE-INDICATION                         */
r_typedef
r_struct
(brace
DECL|member|structs
id|byte
id|structs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* NCPI */
DECL|typedef|_CON_B3_T90_A_INDP
)brace
id|_CON_B3_T90_A_INDP
suffix:semicolon
multiline_comment|/* CONNECT-B3-T90-ACTIVE-RESPONSE                           */
r_typedef
r_struct
(brace
DECL|member|Reject
id|word
id|Reject
suffix:semicolon
DECL|member|structs
id|byte
id|structs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* NCPI */
DECL|typedef|_CON_B3_T90_A_RESP
)brace
id|_CON_B3_T90_A_RESP
suffix:semicolon
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* message structure                                                */
multiline_comment|/*------------------------------------------------------------------*/
DECL|typedef|CAPI_MSG
r_typedef
r_struct
id|_API_MSG
id|CAPI_MSG
suffix:semicolon
DECL|typedef|CAPI_MSG_HEADER
r_typedef
r_struct
id|_MSG_HEADER
id|CAPI_MSG_HEADER
suffix:semicolon
DECL|struct|_API_MSG
r_struct
id|_API_MSG
(brace
DECL|struct|_MSG_HEADER
r_struct
id|_MSG_HEADER
(brace
DECL|member|length
id|word
id|length
suffix:semicolon
DECL|member|appl_id
id|word
id|appl_id
suffix:semicolon
DECL|member|command
id|word
id|command
suffix:semicolon
DECL|member|number
id|word
id|number
suffix:semicolon
DECL|member|controller
id|byte
id|controller
suffix:semicolon
DECL|member|plci
id|byte
id|plci
suffix:semicolon
DECL|member|ncci
id|word
id|ncci
suffix:semicolon
DECL|member|header
)brace
id|header
suffix:semicolon
r_union
(brace
DECL|member|alert_req
id|_ALT_REQP
id|alert_req
suffix:semicolon
DECL|member|alert_con
id|_ALT_CONP
id|alert_con
suffix:semicolon
DECL|member|connect_req
id|_CON_REQP
id|connect_req
suffix:semicolon
DECL|member|connect_con
id|_CON_CONP
id|connect_con
suffix:semicolon
DECL|member|connect_ind
id|_CON_INDP
id|connect_ind
suffix:semicolon
DECL|member|connect_res
id|_CON_RESP
id|connect_res
suffix:semicolon
DECL|member|connect_a_ind
id|_CON_A_INDP
id|connect_a_ind
suffix:semicolon
DECL|member|connect_a_res
id|_CON_A_RESP
id|connect_a_res
suffix:semicolon
DECL|member|disconnect_req
id|_DIS_REQP
id|disconnect_req
suffix:semicolon
DECL|member|disconnect_con
id|_DIS_CONP
id|disconnect_con
suffix:semicolon
DECL|member|disconnect_ind
id|_DIS_INDP
id|disconnect_ind
suffix:semicolon
DECL|member|disconnect_res
id|_DIS_RESP
id|disconnect_res
suffix:semicolon
DECL|member|listen_req
id|_LIS_REQP
id|listen_req
suffix:semicolon
DECL|member|listen_con
id|_LIS_CONP
id|listen_con
suffix:semicolon
DECL|member|info_req
id|_INF_REQP
id|info_req
suffix:semicolon
DECL|member|info_con
id|_INF_CONP
id|info_con
suffix:semicolon
DECL|member|info_ind
id|_INF_INDP
id|info_ind
suffix:semicolon
DECL|member|info_res
id|_INF_RESP
id|info_res
suffix:semicolon
DECL|member|select_b_req
id|_SEL_B_REQP
id|select_b_req
suffix:semicolon
DECL|member|select_b_con
id|_SEL_B_CONP
id|select_b_con
suffix:semicolon
DECL|member|facility_req
id|_FAC_REQP
id|facility_req
suffix:semicolon
DECL|member|facility_con
id|_FAC_CONP
id|facility_con
suffix:semicolon
DECL|member|facility_ind
id|_FAC_INDP
id|facility_ind
suffix:semicolon
DECL|member|facility_res
id|_FAC_RESP
id|facility_res
suffix:semicolon
DECL|member|connect_b3_req
id|_CON_B3_REQP
id|connect_b3_req
suffix:semicolon
DECL|member|connect_b3_con
id|_CON_B3_CONP
id|connect_b3_con
suffix:semicolon
DECL|member|connect_b3_ind
id|_CON_B3_INDP
id|connect_b3_ind
suffix:semicolon
DECL|member|connect_b3_res
id|_CON_B3_RESP
id|connect_b3_res
suffix:semicolon
DECL|member|connect_b3_a_ind
id|_CON_B3_A_INDP
id|connect_b3_a_ind
suffix:semicolon
DECL|member|connect_b3_a_res
id|_CON_B3_A_RESP
id|connect_b3_a_res
suffix:semicolon
DECL|member|disconnect_b3_req
id|_DIS_B3_REQP
id|disconnect_b3_req
suffix:semicolon
DECL|member|disconnect_b3_con
id|_DIS_B3_CONP
id|disconnect_b3_con
suffix:semicolon
DECL|member|disconnect_b3_ind
id|_DIS_B3_INDP
id|disconnect_b3_ind
suffix:semicolon
DECL|member|disconnect_b3_res
id|_DIS_B3_RESP
id|disconnect_b3_res
suffix:semicolon
DECL|member|data_b3_req
id|_DAT_B3_REQP
id|data_b3_req
suffix:semicolon
DECL|member|data_b3_req64
id|_DAT_B3_REQ64P
id|data_b3_req64
suffix:semicolon
DECL|member|data_b3_con
id|_DAT_B3_CONP
id|data_b3_con
suffix:semicolon
DECL|member|data_b3_ind
id|_DAT_B3_INDP
id|data_b3_ind
suffix:semicolon
DECL|member|data_b3_ind64
id|_DAT_B3_IND64P
id|data_b3_ind64
suffix:semicolon
DECL|member|data_b3_res
id|_DAT_B3_RESP
id|data_b3_res
suffix:semicolon
DECL|member|reset_b3_req
id|_RES_B3_REQP
id|reset_b3_req
suffix:semicolon
DECL|member|reset_b3_con
id|_RES_B3_CONP
id|reset_b3_con
suffix:semicolon
DECL|member|reset_b3_ind
id|_RES_B3_INDP
id|reset_b3_ind
suffix:semicolon
DECL|member|reset_b3_res
id|_RES_B3_RESP
id|reset_b3_res
suffix:semicolon
DECL|member|connect_b3_t90_a_ind
id|_CON_B3_T90_A_INDP
id|connect_b3_t90_a_ind
suffix:semicolon
DECL|member|connect_b3_t90_a_res
id|_CON_B3_T90_A_RESP
id|connect_b3_t90_a_res
suffix:semicolon
DECL|member|b
id|byte
id|b
(braket
l_int|200
)braket
suffix:semicolon
DECL|member|info
)brace
id|info
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* non-fatal errors                                                 */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|_NCPI_IGNORED
mdefine_line|#define _NCPI_IGNORED           0x0001
DECL|macro|_FLAGS_IGNORED
mdefine_line|#define _FLAGS_IGNORED          0x0002
DECL|macro|_ALERT_IGNORED
mdefine_line|#define _ALERT_IGNORED          0x0003
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* API function error codes                                         */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|GOOD
mdefine_line|#define GOOD                            0x0000
DECL|macro|_TOO_MANY_APPLICATIONS
mdefine_line|#define _TOO_MANY_APPLICATIONS          0x1001
DECL|macro|_BLOCK_TOO_SMALL
mdefine_line|#define _BLOCK_TOO_SMALL                0x1002
DECL|macro|_BUFFER_TOO_BIG
mdefine_line|#define _BUFFER_TOO_BIG                 0x1003
DECL|macro|_MSG_BUFFER_TOO_SMALL
mdefine_line|#define _MSG_BUFFER_TOO_SMALL           0x1004
DECL|macro|_TOO_MANY_CONNECTIONS
mdefine_line|#define _TOO_MANY_CONNECTIONS           0x1005
DECL|macro|_REG_CAPI_BUSY
mdefine_line|#define _REG_CAPI_BUSY                  0x1007
DECL|macro|_REG_RESOURCE_ERROR
mdefine_line|#define _REG_RESOURCE_ERROR             0x1008
DECL|macro|_REG_CAPI_NOT_INSTALLED
mdefine_line|#define _REG_CAPI_NOT_INSTALLED         0x1009
DECL|macro|_WRONG_APPL_ID
mdefine_line|#define _WRONG_APPL_ID                  0x1101
DECL|macro|_BAD_MSG
mdefine_line|#define _BAD_MSG                        0x1102
DECL|macro|_QUEUE_FULL
mdefine_line|#define _QUEUE_FULL                     0x1103
DECL|macro|_GET_NO_MSG
mdefine_line|#define _GET_NO_MSG                     0x1104
DECL|macro|_MSG_LOST
mdefine_line|#define _MSG_LOST                       0x1105
DECL|macro|_WRONG_NOTIFY
mdefine_line|#define _WRONG_NOTIFY                   0x1106
DECL|macro|_CAPI_BUSY
mdefine_line|#define _CAPI_BUSY                      0x1107
DECL|macro|_RESOURCE_ERROR
mdefine_line|#define _RESOURCE_ERROR                 0x1108
DECL|macro|_CAPI_NOT_INSTALLED
mdefine_line|#define _CAPI_NOT_INSTALLED             0x1109
DECL|macro|_NO_EXTERNAL_EQUIPMENT
mdefine_line|#define _NO_EXTERNAL_EQUIPMENT          0x110a
DECL|macro|_ONLY_EXTERNAL_EQUIPMENT
mdefine_line|#define _ONLY_EXTERNAL_EQUIPMENT        0x110b
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* addressing/coding error codes                                    */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|_WRONG_STATE
mdefine_line|#define _WRONG_STATE                    0x2001
DECL|macro|_WRONG_IDENTIFIER
mdefine_line|#define _WRONG_IDENTIFIER               0x2002
DECL|macro|_OUT_OF_PLCI
mdefine_line|#define _OUT_OF_PLCI                    0x2003
DECL|macro|_OUT_OF_NCCI
mdefine_line|#define _OUT_OF_NCCI                    0x2004
DECL|macro|_OUT_OF_LISTEN
mdefine_line|#define _OUT_OF_LISTEN                  0x2005
DECL|macro|_OUT_OF_FAX
mdefine_line|#define _OUT_OF_FAX                     0x2006
DECL|macro|_WRONG_MESSAGE_FORMAT
mdefine_line|#define _WRONG_MESSAGE_FORMAT           0x2007
DECL|macro|_OUT_OF_INTERCONNECT_RESOURCES
mdefine_line|#define _OUT_OF_INTERCONNECT_RESOURCES  0x2008
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* configuration error codes                                        */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|_B1_NOT_SUPPORTED
mdefine_line|#define _B1_NOT_SUPPORTED                    0x3001
DECL|macro|_B2_NOT_SUPPORTED
mdefine_line|#define _B2_NOT_SUPPORTED                    0x3002
DECL|macro|_B3_NOT_SUPPORTED
mdefine_line|#define _B3_NOT_SUPPORTED                    0x3003
DECL|macro|_B1_PARM_NOT_SUPPORTED
mdefine_line|#define _B1_PARM_NOT_SUPPORTED               0x3004
DECL|macro|_B2_PARM_NOT_SUPPORTED
mdefine_line|#define _B2_PARM_NOT_SUPPORTED               0x3005
DECL|macro|_B3_PARM_NOT_SUPPORTED
mdefine_line|#define _B3_PARM_NOT_SUPPORTED               0x3006
DECL|macro|_B_STACK_NOT_SUPPORTED
mdefine_line|#define _B_STACK_NOT_SUPPORTED               0x3007
DECL|macro|_NCPI_NOT_SUPPORTED
mdefine_line|#define _NCPI_NOT_SUPPORTED                  0x3008
DECL|macro|_CIP_NOT_SUPPORTED
mdefine_line|#define _CIP_NOT_SUPPORTED                   0x3009
DECL|macro|_FLAGS_NOT_SUPPORTED
mdefine_line|#define _FLAGS_NOT_SUPPORTED                 0x300a
DECL|macro|_FACILITY_NOT_SUPPORTED
mdefine_line|#define _FACILITY_NOT_SUPPORTED              0x300b
DECL|macro|_DATA_LEN_NOT_SUPPORTED
mdefine_line|#define _DATA_LEN_NOT_SUPPORTED              0x300c
DECL|macro|_RESET_NOT_SUPPORTED
mdefine_line|#define _RESET_NOT_SUPPORTED                 0x300d
DECL|macro|_SUPPLEMENTARY_SERVICE_NOT_SUPPORTED
mdefine_line|#define _SUPPLEMENTARY_SERVICE_NOT_SUPPORTED 0x300e
DECL|macro|_REQUEST_NOT_ALLOWED_IN_THIS_STATE
mdefine_line|#define _REQUEST_NOT_ALLOWED_IN_THIS_STATE   0x3010
DECL|macro|_FACILITY_SPECIFIC_FUNCTION_NOT_SUPP
mdefine_line|#define _FACILITY_SPECIFIC_FUNCTION_NOT_SUPP 0x3011
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* reason codes                                                     */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|_L1_ERROR
mdefine_line|#define _L1_ERROR                       0x3301
DECL|macro|_L2_ERROR
mdefine_line|#define _L2_ERROR                       0x3302
DECL|macro|_L3_ERROR
mdefine_line|#define _L3_ERROR                       0x3303
DECL|macro|_OTHER_APPL_CONNECTED
mdefine_line|#define _OTHER_APPL_CONNECTED           0x3304
DECL|macro|_CAPI_GUARD_ERROR
mdefine_line|#define _CAPI_GUARD_ERROR               0x3305
DECL|macro|_L3_CAUSE
mdefine_line|#define _L3_CAUSE                       0x3400
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* b3 reason codes                                                  */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|_B_CHANNEL_LOST
mdefine_line|#define _B_CHANNEL_LOST                 0x3301
DECL|macro|_B2_ERROR
mdefine_line|#define _B2_ERROR                       0x3302
DECL|macro|_B3_ERROR
mdefine_line|#define _B3_ERROR                       0x3303
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* fax error codes                                                  */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|_FAX_NO_CONNECTION
mdefine_line|#define _FAX_NO_CONNECTION              0x3311
DECL|macro|_FAX_TRAINING_ERROR
mdefine_line|#define _FAX_TRAINING_ERROR             0x3312
DECL|macro|_FAX_REMOTE_REJECT
mdefine_line|#define _FAX_REMOTE_REJECT              0x3313
DECL|macro|_FAX_REMOTE_ABORT
mdefine_line|#define _FAX_REMOTE_ABORT               0x3314
DECL|macro|_FAX_PROTOCOL_ERROR
mdefine_line|#define _FAX_PROTOCOL_ERROR             0x3315
DECL|macro|_FAX_TX_UNDERRUN
mdefine_line|#define _FAX_TX_UNDERRUN                0x3316
DECL|macro|_FAX_RX_OVERFLOW
mdefine_line|#define _FAX_RX_OVERFLOW                0x3317
DECL|macro|_FAX_LOCAL_ABORT
mdefine_line|#define _FAX_LOCAL_ABORT                0x3318
DECL|macro|_FAX_PARAMETER_ERROR
mdefine_line|#define _FAX_PARAMETER_ERROR            0x3319
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* line interconnect error codes                                    */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|_LI_USER_INITIATED
mdefine_line|#define _LI_USER_INITIATED               0x0000
DECL|macro|_LI_LINE_NO_LONGER_AVAILABLE
mdefine_line|#define _LI_LINE_NO_LONGER_AVAILABLE     0x3805
DECL|macro|_LI_INTERCONNECT_NOT_ESTABLISHED
mdefine_line|#define _LI_INTERCONNECT_NOT_ESTABLISHED 0x3806
DECL|macro|_LI_LINES_NOT_COMPATIBLE
mdefine_line|#define _LI_LINES_NOT_COMPATIBLE         0x3807
DECL|macro|_LI2_USER_INITIATED
mdefine_line|#define _LI2_USER_INITIATED              0x0000
DECL|macro|_LI2_PLCI_HAS_NO_BCHANNEL
mdefine_line|#define _LI2_PLCI_HAS_NO_BCHANNEL        0x3800
DECL|macro|_LI2_LINES_NOT_COMPATIBLE
mdefine_line|#define _LI2_LINES_NOT_COMPATIBLE        0x3801
DECL|macro|_LI2_NOT_IN_SAME_INTERCONNECTION
mdefine_line|#define _LI2_NOT_IN_SAME_INTERCONNECTION 0x3802
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* global options                                                   */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|GL_INTERNAL_CONTROLLER_SUPPORTED
mdefine_line|#define GL_INTERNAL_CONTROLLER_SUPPORTED     0x00000001L
DECL|macro|GL_EXTERNAL_EQUIPMENT_SUPPORTED
mdefine_line|#define GL_EXTERNAL_EQUIPMENT_SUPPORTED      0x00000002L
DECL|macro|GL_HANDSET_SUPPORTED
mdefine_line|#define GL_HANDSET_SUPPORTED                 0x00000004L
DECL|macro|GL_DTMF_SUPPORTED
mdefine_line|#define GL_DTMF_SUPPORTED                    0x00000008L
DECL|macro|GL_SUPPLEMENTARY_SERVICES_SUPPORTED
mdefine_line|#define GL_SUPPLEMENTARY_SERVICES_SUPPORTED  0x00000010L
DECL|macro|GL_CHANNEL_ALLOCATION_SUPPORTED
mdefine_line|#define GL_CHANNEL_ALLOCATION_SUPPORTED      0x00000020L
DECL|macro|GL_BCHANNEL_OPERATION_SUPPORTED
mdefine_line|#define GL_BCHANNEL_OPERATION_SUPPORTED      0x00000040L
DECL|macro|GL_LINE_INTERCONNECT_SUPPORTED
mdefine_line|#define GL_LINE_INTERCONNECT_SUPPORTED       0x00000080L
DECL|macro|GL_ECHO_CANCELLER_SUPPORTED
mdefine_line|#define GL_ECHO_CANCELLER_SUPPORTED          0x00000100L
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* protocol selection                                               */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|B1_HDLC
mdefine_line|#define B1_HDLC                 0
DECL|macro|B1_TRANSPARENT
mdefine_line|#define B1_TRANSPARENT          1
DECL|macro|B1_V110_ASYNC
mdefine_line|#define B1_V110_ASYNC           2
DECL|macro|B1_V110_SYNC
mdefine_line|#define B1_V110_SYNC            3
DECL|macro|B1_T30
mdefine_line|#define B1_T30                  4
DECL|macro|B1_HDLC_INVERTED
mdefine_line|#define B1_HDLC_INVERTED        5
DECL|macro|B1_TRANSPARENT_R
mdefine_line|#define B1_TRANSPARENT_R        6
DECL|macro|B1_MODEM_ALL_NEGOTIATE
mdefine_line|#define B1_MODEM_ALL_NEGOTIATE  7
DECL|macro|B1_MODEM_ASYNC
mdefine_line|#define B1_MODEM_ASYNC          8
DECL|macro|B1_MODEM_SYNC_HDLC
mdefine_line|#define B1_MODEM_SYNC_HDLC      9
DECL|macro|B2_X75
mdefine_line|#define B2_X75                  0
DECL|macro|B2_TRANSPARENT
mdefine_line|#define B2_TRANSPARENT          1
DECL|macro|B2_SDLC
mdefine_line|#define B2_SDLC                 2
DECL|macro|B2_LAPD
mdefine_line|#define B2_LAPD                 3
DECL|macro|B2_T30
mdefine_line|#define B2_T30                  4
DECL|macro|B2_PPP
mdefine_line|#define B2_PPP                  5
DECL|macro|B2_TRANSPARENT_NO_CRC
mdefine_line|#define B2_TRANSPARENT_NO_CRC   6
DECL|macro|B2_MODEM_EC_COMPRESSION
mdefine_line|#define B2_MODEM_EC_COMPRESSION 7
DECL|macro|B2_X75_V42BIS
mdefine_line|#define B2_X75_V42BIS           8
DECL|macro|B2_V120_ASYNC
mdefine_line|#define B2_V120_ASYNC           9
DECL|macro|B2_V120_ASYNC_V42BIS
mdefine_line|#define B2_V120_ASYNC_V42BIS    10
DECL|macro|B2_V120_BIT_TRANSPARENT
mdefine_line|#define B2_V120_BIT_TRANSPARENT 11
DECL|macro|B2_LAPD_FREE_SAPI_SEL
mdefine_line|#define B2_LAPD_FREE_SAPI_SEL   12
DECL|macro|B3_TRANSPARENT
mdefine_line|#define B3_TRANSPARENT          0
DECL|macro|B3_T90NL
mdefine_line|#define B3_T90NL                1
DECL|macro|B3_ISO8208
mdefine_line|#define B3_ISO8208              2
DECL|macro|B3_X25_DCE
mdefine_line|#define B3_X25_DCE              3
DECL|macro|B3_T30
mdefine_line|#define B3_T30                  4
DECL|macro|B3_T30_WITH_EXTENSIONS
mdefine_line|#define B3_T30_WITH_EXTENSIONS  5
DECL|macro|B3_RESERVED
mdefine_line|#define B3_RESERVED             6
DECL|macro|B3_MODEM
mdefine_line|#define B3_MODEM                7
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/*  facility definitions                                            */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|SELECTOR_HANDSET
mdefine_line|#define SELECTOR_HANDSET            0
DECL|macro|SELECTOR_DTMF
mdefine_line|#define SELECTOR_DTMF               1
DECL|macro|SELECTOR_V42BIS
mdefine_line|#define SELECTOR_V42BIS             2
DECL|macro|SELECTOR_SU_SERV
mdefine_line|#define SELECTOR_SU_SERV            3
DECL|macro|SELECTOR_POWER_MANAGEMENT
mdefine_line|#define SELECTOR_POWER_MANAGEMENT   4
DECL|macro|SELECTOR_LINE_INTERCONNECT
mdefine_line|#define SELECTOR_LINE_INTERCONNECT  5
DECL|macro|SELECTOR_ECHO_CANCELLER
mdefine_line|#define SELECTOR_ECHO_CANCELLER     6
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/*  supplementary services definitions                              */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|S_GET_SUPPORTED_SERVICES
mdefine_line|#define S_GET_SUPPORTED_SERVICES  0x0000
DECL|macro|S_LISTEN
mdefine_line|#define S_LISTEN                  0x0001
DECL|macro|S_HOLD
mdefine_line|#define S_HOLD                    0x0002
DECL|macro|S_RETRIEVE
mdefine_line|#define S_RETRIEVE                0x0003
DECL|macro|S_SUSPEND
mdefine_line|#define S_SUSPEND                 0x0004
DECL|macro|S_RESUME
mdefine_line|#define S_RESUME                  0x0005
DECL|macro|S_ECT
mdefine_line|#define S_ECT                     0x0006
DECL|macro|S_3PTY_BEGIN
mdefine_line|#define S_3PTY_BEGIN              0x0007
DECL|macro|S_3PTY_END
mdefine_line|#define S_3PTY_END                0x0008
DECL|macro|S_CALL_DEFLECTION
mdefine_line|#define S_CALL_DEFLECTION         0x000d
DECL|macro|S_CALL_FORWARDING_START
mdefine_line|#define S_CALL_FORWARDING_START   0x0009
DECL|macro|S_CALL_FORWARDING_STOP
mdefine_line|#define S_CALL_FORWARDING_STOP    0x000a
DECL|macro|S_INTERROGATE_DIVERSION
mdefine_line|#define S_INTERROGATE_DIVERSION   0x000b /* or interrogate parameters */
DECL|macro|S_INTERROGATE_NUMBERS
mdefine_line|#define S_INTERROGATE_NUMBERS     0x000c
DECL|macro|S_CCBS_REQUEST
mdefine_line|#define S_CCBS_REQUEST            0x000f
DECL|macro|S_CCBS_DEACTIVATE
mdefine_line|#define S_CCBS_DEACTIVATE         0x0010
DECL|macro|S_CCBS_INTERROGATE
mdefine_line|#define S_CCBS_INTERROGATE        0x0011
DECL|macro|S_CCBS_CALL
mdefine_line|#define S_CCBS_CALL               0x0012
DECL|macro|S_MWI_ACTIVATE
mdefine_line|#define S_MWI_ACTIVATE            0x0013
DECL|macro|S_MWI_DEACTIVATE
mdefine_line|#define S_MWI_DEACTIVATE          0x0014
DECL|macro|S_CONF_BEGIN
mdefine_line|#define S_CONF_BEGIN           0x0017
DECL|macro|S_CONF_ADD
mdefine_line|#define S_CONF_ADD                0x0018
DECL|macro|S_CONF_SPLIT
mdefine_line|#define S_CONF_SPLIT           0x0019
DECL|macro|S_CONF_DROP
mdefine_line|#define S_CONF_DROP               0x001a
DECL|macro|S_CONF_ISOLATE
mdefine_line|#define S_CONF_ISOLATE           0x001b
DECL|macro|S_CONF_REATTACH
mdefine_line|#define S_CONF_REATTACH           0x001c
DECL|macro|S_CCBS_ERASECALLLINKAGEID
mdefine_line|#define S_CCBS_ERASECALLLINKAGEID 0x800d
DECL|macro|S_CCBS_STOP_ALERTING
mdefine_line|#define S_CCBS_STOP_ALERTING      0x8012
DECL|macro|S_CCBS_INFO_RETAIN
mdefine_line|#define S_CCBS_INFO_RETAIN        0x8013
DECL|macro|S_MWI_INDICATE
mdefine_line|#define S_MWI_INDICATE            0x8014
DECL|macro|S_CONF_PARTYDISC
mdefine_line|#define S_CONF_PARTYDISC          0x8016
DECL|macro|S_CONF_NOTIFICATION
mdefine_line|#define S_CONF_NOTIFICATION       0x8017
multiline_comment|/* Service Masks */
DECL|macro|MASK_HOLD_RETRIEVE
mdefine_line|#define MASK_HOLD_RETRIEVE        0x00000001
DECL|macro|MASK_TERMINAL_PORTABILITY
mdefine_line|#define MASK_TERMINAL_PORTABILITY 0x00000002
DECL|macro|MASK_ECT
mdefine_line|#define MASK_ECT                  0x00000004
DECL|macro|MASK_3PTY
mdefine_line|#define MASK_3PTY                 0x00000008
DECL|macro|MASK_CALL_FORWARDING
mdefine_line|#define MASK_CALL_FORWARDING      0x00000010
DECL|macro|MASK_CALL_DEFLECTION
mdefine_line|#define MASK_CALL_DEFLECTION      0x00000020
DECL|macro|MASK_MWI
mdefine_line|#define MASK_MWI                  0x00000100
DECL|macro|MASK_CCNR
mdefine_line|#define MASK_CCNR                 0x00000200
DECL|macro|MASK_CONF
mdefine_line|#define MASK_CONF                 0x00000400
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/*  dtmf definitions                                                */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|DTMF_LISTEN_START
mdefine_line|#define DTMF_LISTEN_START     1
DECL|macro|DTMF_LISTEN_STOP
mdefine_line|#define DTMF_LISTEN_STOP      2
DECL|macro|DTMF_DIGITS_SEND
mdefine_line|#define DTMF_DIGITS_SEND      3
DECL|macro|DTMF_SUCCESS
mdefine_line|#define DTMF_SUCCESS          0
DECL|macro|DTMF_INCORRECT_DIGIT
mdefine_line|#define DTMF_INCORRECT_DIGIT  1
DECL|macro|DTMF_UNKNOWN_REQUEST
mdefine_line|#define DTMF_UNKNOWN_REQUEST  2
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/*  line interconnect definitions                                   */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|LI_GET_SUPPORTED_SERVICES
mdefine_line|#define LI_GET_SUPPORTED_SERVICES       0
DECL|macro|LI_REQ_CONNECT
mdefine_line|#define LI_REQ_CONNECT                  1
DECL|macro|LI_REQ_DISCONNECT
mdefine_line|#define LI_REQ_DISCONNECT               2
DECL|macro|LI_IND_CONNECT_ACTIVE
mdefine_line|#define LI_IND_CONNECT_ACTIVE           1
DECL|macro|LI_IND_DISCONNECT
mdefine_line|#define LI_IND_DISCONNECT               2
DECL|macro|LI_FLAG_CONFERENCE_A_B
mdefine_line|#define LI_FLAG_CONFERENCE_A_B          ((dword) 0x00000001L)
DECL|macro|LI_FLAG_CONFERENCE_B_A
mdefine_line|#define LI_FLAG_CONFERENCE_B_A          ((dword) 0x00000002L)
DECL|macro|LI_FLAG_MONITOR_A
mdefine_line|#define LI_FLAG_MONITOR_A               ((dword) 0x00000004L)
DECL|macro|LI_FLAG_MONITOR_B
mdefine_line|#define LI_FLAG_MONITOR_B               ((dword) 0x00000008L)
DECL|macro|LI_FLAG_ANNOUNCEMENT_A
mdefine_line|#define LI_FLAG_ANNOUNCEMENT_A          ((dword) 0x00000010L)
DECL|macro|LI_FLAG_ANNOUNCEMENT_B
mdefine_line|#define LI_FLAG_ANNOUNCEMENT_B          ((dword) 0x00000020L)
DECL|macro|LI_FLAG_MIX_A
mdefine_line|#define LI_FLAG_MIX_A                   ((dword) 0x00000040L)
DECL|macro|LI_FLAG_MIX_B
mdefine_line|#define LI_FLAG_MIX_B                   ((dword) 0x00000080L)
DECL|macro|LI_CONFERENCING_SUPPORTED
mdefine_line|#define LI_CONFERENCING_SUPPORTED       ((dword) 0x00000001L)
DECL|macro|LI_MONITORING_SUPPORTED
mdefine_line|#define LI_MONITORING_SUPPORTED         ((dword) 0x00000002L)
DECL|macro|LI_ANNOUNCEMENTS_SUPPORTED
mdefine_line|#define LI_ANNOUNCEMENTS_SUPPORTED      ((dword) 0x00000004L)
DECL|macro|LI_MIXING_SUPPORTED
mdefine_line|#define LI_MIXING_SUPPORTED             ((dword) 0x00000008L)
DECL|macro|LI_CROSS_CONTROLLER_SUPPORTED
mdefine_line|#define LI_CROSS_CONTROLLER_SUPPORTED   ((dword) 0x00000010L)
DECL|macro|LI2_GET_SUPPORTED_SERVICES
mdefine_line|#define LI2_GET_SUPPORTED_SERVICES      0
DECL|macro|LI2_REQ_CONNECT
mdefine_line|#define LI2_REQ_CONNECT                 1
DECL|macro|LI2_REQ_DISCONNECT
mdefine_line|#define LI2_REQ_DISCONNECT              2
DECL|macro|LI2_IND_CONNECT_ACTIVE
mdefine_line|#define LI2_IND_CONNECT_ACTIVE          1
DECL|macro|LI2_IND_DISCONNECT
mdefine_line|#define LI2_IND_DISCONNECT              2
DECL|macro|LI2_FLAG_INTERCONNECT_A_B
mdefine_line|#define LI2_FLAG_INTERCONNECT_A_B       ((dword) 0x00000001L)
DECL|macro|LI2_FLAG_INTERCONNECT_B_A
mdefine_line|#define LI2_FLAG_INTERCONNECT_B_A       ((dword) 0x00000002L)
DECL|macro|LI2_FLAG_MONITOR_B
mdefine_line|#define LI2_FLAG_MONITOR_B              ((dword) 0x00000004L)
DECL|macro|LI2_FLAG_MIX_B
mdefine_line|#define LI2_FLAG_MIX_B                  ((dword) 0x00000008L)
DECL|macro|LI2_FLAG_MONITOR_X
mdefine_line|#define LI2_FLAG_MONITOR_X              ((dword) 0x00000010L)
DECL|macro|LI2_FLAG_MIX_X
mdefine_line|#define LI2_FLAG_MIX_X                  ((dword) 0x00000020L)
DECL|macro|LI2_FLAG_LOOP_B
mdefine_line|#define LI2_FLAG_LOOP_B                 ((dword) 0x00000040L)
DECL|macro|LI2_FLAG_LOOP_PC
mdefine_line|#define LI2_FLAG_LOOP_PC                ((dword) 0x00000080L)
DECL|macro|LI2_FLAG_LOOP_X
mdefine_line|#define LI2_FLAG_LOOP_X                 ((dword) 0x00000100L)
DECL|macro|LI2_CROSS_CONTROLLER_SUPPORTED
mdefine_line|#define LI2_CROSS_CONTROLLER_SUPPORTED  ((dword) 0x00000001L)
DECL|macro|LI2_ASYMMETRIC_SUPPORTED
mdefine_line|#define LI2_ASYMMETRIC_SUPPORTED        ((dword) 0x00000002L)
DECL|macro|LI2_MONITORING_SUPPORTED
mdefine_line|#define LI2_MONITORING_SUPPORTED        ((dword) 0x00000004L)
DECL|macro|LI2_MIXING_SUPPORTED
mdefine_line|#define LI2_MIXING_SUPPORTED            ((dword) 0x00000008L)
DECL|macro|LI2_REMOTE_MONITORING_SUPPORTED
mdefine_line|#define LI2_REMOTE_MONITORING_SUPPORTED ((dword) 0x00000010L)
DECL|macro|LI2_REMOTE_MIXING_SUPPORTED
mdefine_line|#define LI2_REMOTE_MIXING_SUPPORTED     ((dword) 0x00000020L)
DECL|macro|LI2_B_LOOPING_SUPPORTED
mdefine_line|#define LI2_B_LOOPING_SUPPORTED         ((dword) 0x00000040L)
DECL|macro|LI2_PC_LOOPING_SUPPORTED
mdefine_line|#define LI2_PC_LOOPING_SUPPORTED        ((dword) 0x00000080L)
DECL|macro|LI2_X_LOOPING_SUPPORTED
mdefine_line|#define LI2_X_LOOPING_SUPPORTED         ((dword) 0x00000100L)
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* echo canceller definitions                                       */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|EC_GET_SUPPORTED_SERVICES
mdefine_line|#define EC_GET_SUPPORTED_SERVICES            0
DECL|macro|EC_ENABLE_OPERATION
mdefine_line|#define EC_ENABLE_OPERATION                  1
DECL|macro|EC_DISABLE_OPERATION
mdefine_line|#define EC_DISABLE_OPERATION                 2
DECL|macro|EC_ENABLE_NON_LINEAR_PROCESSING
mdefine_line|#define EC_ENABLE_NON_LINEAR_PROCESSING      0x0001
DECL|macro|EC_DO_NOT_REQUIRE_REVERSALS
mdefine_line|#define EC_DO_NOT_REQUIRE_REVERSALS          0x0002
DECL|macro|EC_DETECT_DISABLE_TONE
mdefine_line|#define EC_DETECT_DISABLE_TONE               0x0004
DECL|macro|EC_ENABLE_ADAPTIVE_PREDELAY
mdefine_line|#define EC_ENABLE_ADAPTIVE_PREDELAY          0x0008
DECL|macro|EC_NON_LINEAR_PROCESSING_SUPPORTED
mdefine_line|#define EC_NON_LINEAR_PROCESSING_SUPPORTED   0x0001
DECL|macro|EC_BYPASS_ON_ANY_2100HZ_SUPPORTED
mdefine_line|#define EC_BYPASS_ON_ANY_2100HZ_SUPPORTED    0x0002
DECL|macro|EC_BYPASS_ON_REV_2100HZ_SUPPORTED
mdefine_line|#define EC_BYPASS_ON_REV_2100HZ_SUPPORTED    0x0004
DECL|macro|EC_ADAPTIVE_PREDELAY_SUPPORTED
mdefine_line|#define EC_ADAPTIVE_PREDELAY_SUPPORTED       0x0008
DECL|macro|EC_BYPASS_INDICATION
mdefine_line|#define EC_BYPASS_INDICATION                 1
DECL|macro|EC_BYPASS_DUE_TO_CONTINUOUS_2100HZ
mdefine_line|#define EC_BYPASS_DUE_TO_CONTINUOUS_2100HZ   1
DECL|macro|EC_BYPASS_DUE_TO_REVERSED_2100HZ
mdefine_line|#define EC_BYPASS_DUE_TO_REVERSED_2100HZ     2
DECL|macro|EC_BYPASS_RELEASED
mdefine_line|#define EC_BYPASS_RELEASED                   3
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* function prototypes                                              */
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/*------------------------------------------------------------------*/
macro_line|#endif /* _INC_CAPI20 */  
eof
