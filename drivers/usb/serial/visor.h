multiline_comment|/*&n; * USB HandSpring Visor driver&n; *&n; *&t;Copyright (C) 1999, 2000&n; *&t;    Greg Kroah-Hartman (greg@kroah.com)&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; * See Documentation/usb/usb-serial.txt for more information on using this driver&n; * &n; */
macro_line|#ifndef __LINUX_USB_SERIAL_VISOR_H
DECL|macro|__LINUX_USB_SERIAL_VISOR_H
mdefine_line|#define __LINUX_USB_SERIAL_VISOR_H
DECL|macro|HANDSPRING_VENDOR_ID
mdefine_line|#define HANDSPRING_VENDOR_ID&t;&t;0x082d
DECL|macro|HANDSPRING_VISOR_ID
mdefine_line|#define HANDSPRING_VISOR_ID&t;&t;0x0100
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
macro_line|#endif
eof
