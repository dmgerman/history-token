macro_line|#ifndef CYPRESS_M8_H
DECL|macro|CYPRESS_M8_H
mdefine_line|#define CYPRESS_M8_H
multiline_comment|/* definitions and function prototypes used for the cypress USB to Serial controller */
multiline_comment|/* For sending our feature buffer - controlling serial communication states */
multiline_comment|/* Linux HID has no support for serial devices so we do this through the driver */
DECL|macro|HID_REQ_GET_REPORT
mdefine_line|#define HID_REQ_GET_REPORT 0x01
DECL|macro|HID_REQ_SET_REPORT
mdefine_line|#define HID_REQ_SET_REPORT 0x09
multiline_comment|/* List other cypress USB to Serial devices here, and add them to the id_table */
multiline_comment|/* DeLorme Earthmate USB - a GPS device */
DECL|macro|VENDOR_ID_DELORME
mdefine_line|#define&t;VENDOR_ID_DELORME&t;&t; 0x1163
DECL|macro|PRODUCT_ID_EARTHMATEUSB
mdefine_line|#define PRODUCT_ID_EARTHMATEUSB&t;&t; 0x0100
multiline_comment|/* Cypress HID-&gt;COM RS232 Adapter */
DECL|macro|VENDOR_ID_CYPRESS
mdefine_line|#define VENDOR_ID_CYPRESS&t;&t; 0x04b4
DECL|macro|PRODUCT_ID_CYPHIDCOM
mdefine_line|#define PRODUCT_ID_CYPHIDCOM&t;&t; 0x5500
multiline_comment|/* End of device listing */
multiline_comment|/* Used for setting / requesting serial line settings */
DECL|macro|CYPRESS_SET_CONFIG
mdefine_line|#define CYPRESS_SET_CONFIG 0x01
DECL|macro|CYPRESS_GET_CONFIG
mdefine_line|#define CYPRESS_GET_CONFIG 0x02
multiline_comment|/* Used for throttle control */
DECL|macro|THROTTLED
mdefine_line|#define THROTTLED 0x1
DECL|macro|ACTUALLY_THROTTLED
mdefine_line|#define ACTUALLY_THROTTLED 0x2
multiline_comment|/* chiptypes - used in case firmware differs from the generic form ... offering&n; * &t;different baud speeds/etc.&n; */
DECL|macro|CT_EARTHMATE
mdefine_line|#define CT_EARTHMATE&t;0x01
DECL|macro|CT_CYPHIDCOM
mdefine_line|#define CT_CYPHIDCOM&t;0x02
DECL|macro|CT_GENERIC
mdefine_line|#define CT_GENERIC&t;0x0F
multiline_comment|/* End of chiptype definitions */
multiline_comment|/* RS-232 serial data communication protocol definitions */
multiline_comment|/* these are sent / read at byte 0 of the input/output hid reports */
multiline_comment|/* You can find these values defined in the CY4601 USB to Serial design notes */
DECL|macro|CONTROL_DTR
mdefine_line|#define CONTROL_DTR &t;0x20&t;/* data terminal ready - flow control - host to device */
DECL|macro|UART_DSR
mdefine_line|#define UART_DSR&t;0x20&t;/* data set ready - flow control - device to host */
DECL|macro|CONTROL_RTS
mdefine_line|#define CONTROL_RTS &t;0x10&t;/* request to send - flow control - host to device */
DECL|macro|UART_CTS
mdefine_line|#define UART_CTS&t;0x10&t;/* clear to send - flow control - device to host */
DECL|macro|UART_RI
mdefine_line|#define&t;UART_RI&t;&t;0x10&t;/* ring indicator - modem - device to host */ 
DECL|macro|UART_CD
mdefine_line|#define UART_CD&t;&t;0x40&t;/* carrier detect - modem - device to host */
DECL|macro|CYP_ERROR
mdefine_line|#define CYP_ERROR &t;0x08&t;/* received from input report - device to host */
multiline_comment|/* Note - the below has nothing to to with the &quot;feature report&quot; reset */
DECL|macro|CONTROL_RESET
mdefine_line|#define CONTROL_RESET&t;0x08  &t;/* sent with output report - host to device */
multiline_comment|/* End of RS-232 protocol definitions */
macro_line|#endif /* CYPRESS_M8_H */
eof
