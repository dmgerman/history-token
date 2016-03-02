multiline_comment|/*&n; * USB HandSpring Visor driver&n; *&n; *&t;Copyright (C) 1999 - 2003&n; *&t;    Greg Kroah-Hartman (greg@kroah.com)&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; * See Documentation/usb/usb-serial.txt for more information on using this driver&n; * &n; */
macro_line|#ifndef __LINUX_USB_SERIAL_VISOR_H
DECL|macro|__LINUX_USB_SERIAL_VISOR_H
mdefine_line|#define __LINUX_USB_SERIAL_VISOR_H
DECL|macro|HANDSPRING_VENDOR_ID
mdefine_line|#define HANDSPRING_VENDOR_ID&t;&t;0x082d
DECL|macro|HANDSPRING_VISOR_ID
mdefine_line|#define HANDSPRING_VISOR_ID&t;&t;0x0100
DECL|macro|HANDSPRING_TREO_ID
mdefine_line|#define HANDSPRING_TREO_ID&t;&t;0x0200
DECL|macro|HANDSPRING_TREO600_ID
mdefine_line|#define HANDSPRING_TREO600_ID&t;&t;0x0300
DECL|macro|PALM_VENDOR_ID
mdefine_line|#define PALM_VENDOR_ID&t;&t;&t;0x0830
DECL|macro|PALM_M500_ID
mdefine_line|#define PALM_M500_ID&t;&t;&t;0x0001
DECL|macro|PALM_M505_ID
mdefine_line|#define PALM_M505_ID&t;&t;&t;0x0002
DECL|macro|PALM_M515_ID
mdefine_line|#define PALM_M515_ID&t;&t;&t;0x0003
DECL|macro|PALM_I705_ID
mdefine_line|#define PALM_I705_ID&t;&t;&t;0x0020
DECL|macro|PALM_M125_ID
mdefine_line|#define PALM_M125_ID&t;&t;&t;0x0040
DECL|macro|PALM_M130_ID
mdefine_line|#define PALM_M130_ID&t;&t;&t;0x0050
DECL|macro|PALM_TUNGSTEN_T_ID
mdefine_line|#define PALM_TUNGSTEN_T_ID&t;&t;0x0060
DECL|macro|PALM_TUNGSTEN_Z_ID
mdefine_line|#define PALM_TUNGSTEN_Z_ID&t;&t;0x0031
DECL|macro|PALM_ZIRE_ID
mdefine_line|#define PALM_ZIRE_ID&t;&t;&t;0x0070
DECL|macro|PALM_M100_ID
mdefine_line|#define PALM_M100_ID&t;&t;&t;0x0080
DECL|macro|SONY_VENDOR_ID
mdefine_line|#define SONY_VENDOR_ID&t;&t;&t;0x054C
DECL|macro|SONY_CLIE_3_5_ID
mdefine_line|#define SONY_CLIE_3_5_ID&t;&t;0x0038
DECL|macro|SONY_CLIE_4_0_ID
mdefine_line|#define SONY_CLIE_4_0_ID&t;&t;0x0066
DECL|macro|SONY_CLIE_S360_ID
mdefine_line|#define SONY_CLIE_S360_ID&t;&t;0x0095
DECL|macro|SONY_CLIE_4_1_ID
mdefine_line|#define SONY_CLIE_4_1_ID&t;&t;0x009A
DECL|macro|SONY_CLIE_NX60_ID
mdefine_line|#define SONY_CLIE_NX60_ID&t;&t;0x00DA
DECL|macro|SONY_CLIE_NZ90V_ID
mdefine_line|#define SONY_CLIE_NZ90V_ID&t;&t;0x00E9
DECL|macro|SAMSUNG_VENDOR_ID
mdefine_line|#define SAMSUNG_VENDOR_ID&t;&t;0x04E8
DECL|macro|SAMSUNG_SCH_I330_ID
mdefine_line|#define SAMSUNG_SCH_I330_ID&t;&t;0x8001
DECL|macro|GARMIN_VENDOR_ID
mdefine_line|#define GARMIN_VENDOR_ID&t;&t;0x091E
DECL|macro|GARMIN_IQUE_3600_ID
mdefine_line|#define GARMIN_IQUE_3600_ID&t;&t;0x0004
multiline_comment|/****************************************************************************&n; * Handspring Visor Vendor specific request codes (bRequest values)&n; * A big thank you to Handspring for providing the following information.&n; * If anyone wants the original file where these values and structures came&n; * from, send email to &lt;greg@kroah.com&gt;.&n; ****************************************************************************/
multiline_comment|/****************************************************************************&n; * VISOR_REQUEST_BYTES_AVAILABLE asks the visor for the number of bytes that&n; * are available to be transferred to the host for the specified endpoint.&n; * Currently this is not used, and always returns 0x0001&n; ****************************************************************************/
DECL|macro|VISOR_REQUEST_BYTES_AVAILABLE
mdefine_line|#define VISOR_REQUEST_BYTES_AVAILABLE&t;&t;0x01
multiline_comment|/****************************************************************************&n; * VISOR_CLOSE_NOTIFICATION is set to the device to notify it that the host&n; * is now closing the pipe. An empty packet is sent in response.&n; ****************************************************************************/
DECL|macro|VISOR_CLOSE_NOTIFICATION
mdefine_line|#define VISOR_CLOSE_NOTIFICATION&t;&t;0x02
multiline_comment|/****************************************************************************&n; * VISOR_GET_CONNECTION_INFORMATION is sent by the host during enumeration to&n; * get the endpoints used by the connection.&n; ****************************************************************************/
DECL|macro|VISOR_GET_CONNECTION_INFORMATION
mdefine_line|#define VISOR_GET_CONNECTION_INFORMATION&t;0x03
multiline_comment|/****************************************************************************&n; * VISOR_GET_CONNECTION_INFORMATION returns data in the following format&n; ****************************************************************************/
DECL|struct|visor_connection_info
r_struct
id|visor_connection_info
(brace
DECL|member|num_ports
id|__u16
id|num_ports
suffix:semicolon
r_struct
(brace
DECL|member|port_function_id
id|__u8
id|port_function_id
suffix:semicolon
DECL|member|port
id|__u8
id|port
suffix:semicolon
DECL|member|connections
)brace
id|connections
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* struct visor_connection_info.connection[x].port defines: */
DECL|macro|VISOR_ENDPOINT_1
mdefine_line|#define VISOR_ENDPOINT_1&t;&t;0x01
DECL|macro|VISOR_ENDPOINT_2
mdefine_line|#define VISOR_ENDPOINT_2&t;&t;0x02
multiline_comment|/* struct visor_connection_info.connection[x].port_function_id defines: */
DECL|macro|VISOR_FUNCTION_GENERIC
mdefine_line|#define VISOR_FUNCTION_GENERIC&t;&t;0x00
DECL|macro|VISOR_FUNCTION_DEBUGGER
mdefine_line|#define VISOR_FUNCTION_DEBUGGER&t;&t;0x01
DECL|macro|VISOR_FUNCTION_HOTSYNC
mdefine_line|#define VISOR_FUNCTION_HOTSYNC&t;&t;0x02
DECL|macro|VISOR_FUNCTION_CONSOLE
mdefine_line|#define VISOR_FUNCTION_CONSOLE&t;&t;0x03
DECL|macro|VISOR_FUNCTION_REMOTE_FILE_SYS
mdefine_line|#define VISOR_FUNCTION_REMOTE_FILE_SYS&t;0x04
multiline_comment|/****************************************************************************&n; * PALM_GET_SOME_UNKNOWN_INFORMATION is sent by the host during enumeration to&n; * get some information from the M series devices, that is currently unknown.&n; ****************************************************************************/
DECL|macro|PALM_GET_EXT_CONNECTION_INFORMATION
mdefine_line|#define PALM_GET_EXT_CONNECTION_INFORMATION&t;0x04
multiline_comment|/**&n; * struct palm_ext_connection_info - return data from a PALM_GET_EXT_CONNECTION_INFORMATION request&n; * @num_ports: maximum number of functions/connections in use&n; * @endpoint_numbers_different: will be 1 if in and out endpoints numbers are&n; *&t;different, otherwise it is 0.  If value is 1, then&n; *&t;connections.end_point_info is non-zero.  If value is 0, then&n; *&t;connections.port contains the endpoint number, which is the same for in&n; *&t;and out.&n; * @port_function_id: contains the creator id of the applicaton that opened&n; *&t;this connection.&n; * @port: contains the in/out endpoint number.  Is 0 if in and out endpoint&n; *&t;numbers are different.&n; * @end_point_info: high nubbe is in endpoint and low nibble will indicate out&n; *&t;endpoint.  Is 0 if in and out endpoints are the same.&n; *&n; * The maximum number of connections currently supported is 2&n; */
DECL|struct|palm_ext_connection_info
r_struct
id|palm_ext_connection_info
(brace
DECL|member|num_ports
id|__u8
id|num_ports
suffix:semicolon
DECL|member|endpoint_numbers_different
id|__u8
id|endpoint_numbers_different
suffix:semicolon
DECL|member|reserved1
id|__u16
id|reserved1
suffix:semicolon
r_struct
(brace
DECL|member|port_function_id
id|__u32
id|port_function_id
suffix:semicolon
DECL|member|port
id|__u8
id|port
suffix:semicolon
DECL|member|end_point_info
id|__u8
id|end_point_info
suffix:semicolon
DECL|member|reserved
id|__u16
id|reserved
suffix:semicolon
DECL|member|connections
)brace
id|connections
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
