multiline_comment|/*&n; * Definitions for the FTDI USB Single Port Serial Converter - &n; * known as FTDI_SIO (Serial Input/Output application of the chipset) &n; *&n; * The example I have is known as the USC-1000 which is available from&n; * http://www.dse.co.nz - cat no XH4214 It looks similar to this:&n; * http://www.dansdata.com/usbser.htm but I can&squot;t be sure There are other&n; * USC-1000s which don&squot;t look like my device though so beware!&n; *&n; * The device is based on the FTDI FT8U100AX chip. It has a DB25 on one side, &n; * USB on the other.&n; *&n; * Thanx to FTDI (http://www.ftdi.co.uk) for so kindly providing details&n; * of the protocol required to talk to the device and ongoing assistence&n; * during development.&n; *&n; * Bill Ryder - bryder@sgi.com of Silicon Graphics, Inc.- wrote the &n; * FTDI_SIO implementation.&n; *&n; */
DECL|macro|FTDI_VID
mdefine_line|#define FTDI_VID&t;0x0403&t;/* Vendor Id */
DECL|macro|FTDI_SIO_PID
mdefine_line|#define FTDI_SIO_PID&t;0x8372&t;/* Product Id SIO application of 8U100AX  */
DECL|macro|FTDI_8U232AM_PID
mdefine_line|#define FTDI_8U232AM_PID 0x6001 /* Similar device to SIO above */
DECL|macro|FTDI_NF_RIC_VID
mdefine_line|#define FTDI_NF_RIC_VID&t;0x0DCD&t;/* Vendor Id */
DECL|macro|FTDI_NF_RIC_PID
mdefine_line|#define FTDI_NF_RIC_PID&t;0x0001&t;/* Product Id */
DECL|macro|FTDI_SIO_RESET
mdefine_line|#define FTDI_SIO_RESET &t;&t;0 /* Reset the port */
DECL|macro|FTDI_SIO_MODEM_CTRL
mdefine_line|#define FTDI_SIO_MODEM_CTRL &t;1 /* Set the modem control register */
DECL|macro|FTDI_SIO_SET_FLOW_CTRL
mdefine_line|#define FTDI_SIO_SET_FLOW_CTRL&t;2 /* Set flow control register */
DECL|macro|FTDI_SIO_SET_BAUD_RATE
mdefine_line|#define FTDI_SIO_SET_BAUD_RATE&t;3 /* Set baud rate */
DECL|macro|FTDI_SIO_SET_DATA
mdefine_line|#define FTDI_SIO_SET_DATA&t;4 /* Set the data characteristics of the port */
DECL|macro|FTDI_SIO_GET_MODEM_STATUS
mdefine_line|#define FTDI_SIO_GET_MODEM_STATUS&t;5 /* Retrieve current value of modern status register */
DECL|macro|FTDI_SIO_SET_EVENT_CHAR
mdefine_line|#define FTDI_SIO_SET_EVENT_CHAR&t;6 /* Set the event character */
DECL|macro|FTDI_SIO_SET_ERROR_CHAR
mdefine_line|#define FTDI_SIO_SET_ERROR_CHAR&t;7 /* Set the error character */
multiline_comment|/* Port Identifier Table */
DECL|macro|PIT_DEFAULT
mdefine_line|#define PIT_DEFAULT &t;&t;0 /* SIOA */
DECL|macro|PIT_SIOA
mdefine_line|#define PIT_SIOA&t;&t;1 /* SIOA */
multiline_comment|/* The device this driver is tested with one has only one port */
DECL|macro|PIT_SIOB
mdefine_line|#define PIT_SIOB&t;&t;2 /* SIOB */
DECL|macro|PIT_PARALLEL
mdefine_line|#define PIT_PARALLEL&t;&t;3 /* Parallel */
multiline_comment|/* FTDI_SIO_RESET */
DECL|macro|FTDI_SIO_RESET_REQUEST
mdefine_line|#define FTDI_SIO_RESET_REQUEST FTDI_SIO_RESET
DECL|macro|FTDI_SIO_RESET_REQUEST_TYPE
mdefine_line|#define FTDI_SIO_RESET_REQUEST_TYPE 0x40
DECL|macro|FTDI_SIO_RESET_SIO
mdefine_line|#define FTDI_SIO_RESET_SIO 0
DECL|macro|FTDI_SIO_RESET_PURGE_RX
mdefine_line|#define FTDI_SIO_RESET_PURGE_RX 1
DECL|macro|FTDI_SIO_RESET_PURGE_TX
mdefine_line|#define FTDI_SIO_RESET_PURGE_TX 2
multiline_comment|/*&n; * BmRequestType:  0100 0000B&n; * bRequest:       FTDI_SIO_RESET&n; * wValue:         Control Value &n; *                   0 = Reset SIO&n; *                   1 = Purge RX buffer&n; *                   2 = Purge TX buffer&n; * wIndex:         Port&n; * wLength:        0&n; * Data:           None&n; *&n; * The Reset SIO command has this effect:&n; *&n; *    Sets flow control set to &squot;none&squot;&n; *    Event char = $0D&n; *    Event trigger = disabled&n; *    Purge RX buffer&n; *    Purge TX buffer&n; *    Clear DTR&n; *    Clear RTS&n; *    baud and data format not reset&n; *&n; * The Purge RX and TX buffer commands affect nothing except the buffers&n; *&n;   */
multiline_comment|/* FTDI_SIO_SET_BAUDRATE */
DECL|macro|FTDI_SIO_SET_BAUDRATE_REQUEST_TYPE
mdefine_line|#define FTDI_SIO_SET_BAUDRATE_REQUEST_TYPE 0x40
DECL|macro|FTDI_SIO_SET_BAUDRATE_REQUEST
mdefine_line|#define FTDI_SIO_SET_BAUDRATE_REQUEST 3
multiline_comment|/*&n; * BmRequestType:  0100 0000B&n; * bRequest:       FTDI_SIO_SET_BAUDRATE&n; * wValue:         BaudRate value - see below&n; * wIndex:         Port&n; * wLength:        0&n; * Data:           None&n; */
r_typedef
r_enum
(brace
DECL|enumerator|sio
id|sio
op_assign
l_int|1
comma
DECL|enumerator|F8U232AM
id|F8U232AM
op_assign
l_int|2
comma
DECL|typedef|ftdi_type_t
)brace
id|ftdi_type_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|ftdi_sio_b300
id|ftdi_sio_b300
op_assign
l_int|0
comma
DECL|enumerator|ftdi_sio_b600
id|ftdi_sio_b600
op_assign
l_int|1
comma
DECL|enumerator|ftdi_sio_b1200
id|ftdi_sio_b1200
op_assign
l_int|2
comma
DECL|enumerator|ftdi_sio_b2400
id|ftdi_sio_b2400
op_assign
l_int|3
comma
DECL|enumerator|ftdi_sio_b4800
id|ftdi_sio_b4800
op_assign
l_int|4
comma
DECL|enumerator|ftdi_sio_b9600
id|ftdi_sio_b9600
op_assign
l_int|5
comma
DECL|enumerator|ftdi_sio_b19200
id|ftdi_sio_b19200
op_assign
l_int|6
comma
DECL|enumerator|ftdi_sio_b38400
id|ftdi_sio_b38400
op_assign
l_int|7
comma
DECL|enumerator|ftdi_sio_b57600
id|ftdi_sio_b57600
op_assign
l_int|8
comma
DECL|enumerator|ftdi_sio_b115200
id|ftdi_sio_b115200
op_assign
l_int|9
DECL|typedef|FTDI_SIO_baudrate_t
)brace
id|FTDI_SIO_baudrate_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|ftdi_8U232AM_12MHz_b300
id|ftdi_8U232AM_12MHz_b300
op_assign
l_int|0x09c4
comma
DECL|enumerator|ftdi_8U232AM_12MHz_b600
id|ftdi_8U232AM_12MHz_b600
op_assign
l_int|0x04E2
comma
DECL|enumerator|ftdi_8U232AM_12MHz_b1200
id|ftdi_8U232AM_12MHz_b1200
op_assign
l_int|0x0271
comma
DECL|enumerator|ftdi_8U232AM_12MHz_b2400
id|ftdi_8U232AM_12MHz_b2400
op_assign
l_int|0x4138
comma
DECL|enumerator|ftdi_8U232AM_12MHz_b4800
id|ftdi_8U232AM_12MHz_b4800
op_assign
l_int|0x809c
comma
DECL|enumerator|ftdi_8U232AM_12MHz_b9600
id|ftdi_8U232AM_12MHz_b9600
op_assign
l_int|0xc04e
comma
DECL|enumerator|ftdi_8U232AM_12MHz_b19200
id|ftdi_8U232AM_12MHz_b19200
op_assign
l_int|0x0027
comma
DECL|enumerator|ftdi_8U232AM_12MHz_b38400
id|ftdi_8U232AM_12MHz_b38400
op_assign
l_int|0x4013
comma
DECL|enumerator|ftdi_8U232AM_12MHz_b57600
id|ftdi_8U232AM_12MHz_b57600
op_assign
l_int|0x000d
comma
DECL|enumerator|ftdi_8U232AM_12MHz_b115200
id|ftdi_8U232AM_12MHz_b115200
op_assign
l_int|0x4006
comma
DECL|enumerator|ftdi_8U232AM_12MHz_b230400
id|ftdi_8U232AM_12MHz_b230400
op_assign
l_int|0x8003
comma
DECL|typedef|FTDI_8U232AM_12MHz_baudrate_t
)brace
id|FTDI_8U232AM_12MHz_baudrate_t
suffix:semicolon
multiline_comment|/* Apparently all devices are 48MHz */
r_typedef
r_enum
(brace
DECL|enumerator|ftdi_8U232AM_48MHz_b300
id|ftdi_8U232AM_48MHz_b300
op_assign
l_int|0x2710
comma
DECL|enumerator|ftdi_8U232AM_48MHz_b600
id|ftdi_8U232AM_48MHz_b600
op_assign
l_int|0x1388
comma
DECL|enumerator|ftdi_8U232AM_48MHz_b1200
id|ftdi_8U232AM_48MHz_b1200
op_assign
l_int|0x09c4
comma
DECL|enumerator|ftdi_8U232AM_48MHz_b2400
id|ftdi_8U232AM_48MHz_b2400
op_assign
l_int|0x04e2
comma
DECL|enumerator|ftdi_8U232AM_48MHz_b4800
id|ftdi_8U232AM_48MHz_b4800
op_assign
l_int|0x0271
comma
DECL|enumerator|ftdi_8U232AM_48MHz_b9600
id|ftdi_8U232AM_48MHz_b9600
op_assign
l_int|0x4138
comma
DECL|enumerator|ftdi_8U232AM_48MHz_b19200
id|ftdi_8U232AM_48MHz_b19200
op_assign
l_int|0x809c
comma
DECL|enumerator|ftdi_8U232AM_48MHz_b38400
id|ftdi_8U232AM_48MHz_b38400
op_assign
l_int|0xc04e
comma
DECL|enumerator|ftdi_8U232AM_48MHz_b57600
id|ftdi_8U232AM_48MHz_b57600
op_assign
l_int|0x0034
comma
DECL|enumerator|ftdi_8U232AM_48MHz_b115200
id|ftdi_8U232AM_48MHz_b115200
op_assign
l_int|0x001a
comma
DECL|enumerator|ftdi_8U232AM_48MHz_b230400
id|ftdi_8U232AM_48MHz_b230400
op_assign
l_int|0x000d
comma
DECL|enumerator|ftdi_8U232AM_48MHz_b460800
id|ftdi_8U232AM_48MHz_b460800
op_assign
l_int|0x4006
comma
DECL|enumerator|ftdi_8U232AM_48MHz_b921600
id|ftdi_8U232AM_48MHz_b921600
op_assign
l_int|0x8003
comma
DECL|typedef|FTDI_8U232AM_48MHz_baudrate_t
)brace
id|FTDI_8U232AM_48MHz_baudrate_t
suffix:semicolon
DECL|macro|FTDI_SIO_SET_DATA_REQUEST
mdefine_line|#define FTDI_SIO_SET_DATA_REQUEST FTDI_SIO_SET_DATA
DECL|macro|FTDI_SIO_SET_DATA_REQUEST_TYPE
mdefine_line|#define FTDI_SIO_SET_DATA_REQUEST_TYPE 0x40
DECL|macro|FTDI_SIO_SET_DATA_PARITY_NONE
mdefine_line|#define FTDI_SIO_SET_DATA_PARITY_NONE (0x0 &lt;&lt; 8 )
DECL|macro|FTDI_SIO_SET_DATA_PARITY_ODD
mdefine_line|#define FTDI_SIO_SET_DATA_PARITY_ODD (0x1 &lt;&lt; 8 )
DECL|macro|FTDI_SIO_SET_DATA_PARITY_EVEN
mdefine_line|#define FTDI_SIO_SET_DATA_PARITY_EVEN (0x2 &lt;&lt; 8 )
DECL|macro|FTDI_SIO_SET_DATA_PARITY_MARK
mdefine_line|#define FTDI_SIO_SET_DATA_PARITY_MARK (0x3 &lt;&lt; 8 )
DECL|macro|FTDI_SIO_SET_DATA_PARITY_SPACE
mdefine_line|#define FTDI_SIO_SET_DATA_PARITY_SPACE (0x4 &lt;&lt; 8 )
DECL|macro|FTDI_SIO_SET_DATA_STOP_BITS_1
mdefine_line|#define FTDI_SIO_SET_DATA_STOP_BITS_1 (0x0 &lt;&lt; 11 )
DECL|macro|FTDI_SIO_SET_DATA_STOP_BITS_15
mdefine_line|#define FTDI_SIO_SET_DATA_STOP_BITS_15 (0x1 &lt;&lt; 11 )
DECL|macro|FTDI_SIO_SET_DATA_STOP_BITS_2
mdefine_line|#define FTDI_SIO_SET_DATA_STOP_BITS_2 (0x2 &lt;&lt; 11 )
DECL|macro|FTDI_SIO_SET_BREAK
mdefine_line|#define FTDI_SIO_SET_BREAK (0x1 &lt;&lt; 14)
multiline_comment|/* FTDI_SIO_SET_DATA */
multiline_comment|/*&n; * BmRequestType:  0100 0000B &n; * bRequest:       FTDI_SIO_SET_DATA&n; * wValue:         Data characteristics (see below)&n; * wIndex:         Port&n; * wLength:        0&n; * Data:           No&n; *&n; * Data characteristics&n; *&n; *   B0..7   Number of data bits&n; *   B8..10  Parity&n; *           0 = None&n; *           1 = Odd&n; *           2 = Even&n; *           3 = Mark&n; *           4 = Space&n; *   B11..13 Stop Bits&n; *           0 = 1&n; *           1 = 1.5&n; *           2 = 2&n; *   B14&n; *           1 = TX ON (break)&n; *           0 = TX OFF (normal state)&n; *   B15 Reserved&n; *&n; */
multiline_comment|/* FTDI_SIO_MODEM_CTRL */
DECL|macro|FTDI_SIO_SET_MODEM_CTRL_REQUEST_TYPE
mdefine_line|#define FTDI_SIO_SET_MODEM_CTRL_REQUEST_TYPE 0x40
DECL|macro|FTDI_SIO_SET_MODEM_CTRL_REQUEST
mdefine_line|#define FTDI_SIO_SET_MODEM_CTRL_REQUEST FTDI_SIO_MODEM_CTRL
multiline_comment|/* &n; * BmRequestType:   0100 0000B&n; * bRequest:        FTDI_SIO_MODEM_CTRL&n; * wValue:          ControlValue (see below)&n; * wIndex:          Port&n; * wLength:         0&n; * Data:            None&n; *&n; * NOTE: If the device is in RTS/CTS flow control, the RTS set by this&n; * command will be IGNORED without an error being returned&n; * Also - you can not set DTR and RTS with one control message&n; */
DECL|macro|FTDI_SIO_SET_DTR_MASK
mdefine_line|#define FTDI_SIO_SET_DTR_MASK 0x1
DECL|macro|FTDI_SIO_SET_DTR_HIGH
mdefine_line|#define FTDI_SIO_SET_DTR_HIGH ( 1 | ( FTDI_SIO_SET_DTR_MASK  &lt;&lt; 8))
DECL|macro|FTDI_SIO_SET_DTR_LOW
mdefine_line|#define FTDI_SIO_SET_DTR_LOW  ( 0 | ( FTDI_SIO_SET_DTR_MASK  &lt;&lt; 8))
DECL|macro|FTDI_SIO_SET_RTS_MASK
mdefine_line|#define FTDI_SIO_SET_RTS_MASK 0x2
DECL|macro|FTDI_SIO_SET_RTS_HIGH
mdefine_line|#define FTDI_SIO_SET_RTS_HIGH ( 2 | ( FTDI_SIO_SET_RTS_MASK &lt;&lt; 8 ))
DECL|macro|FTDI_SIO_SET_RTS_LOW
mdefine_line|#define FTDI_SIO_SET_RTS_LOW ( 0 | ( FTDI_SIO_SET_RTS_MASK &lt;&lt; 8 ))
multiline_comment|/*&n; * ControlValue&n; * B0    DTR state&n; *          0 = reset&n; *          1 = set&n; * B1    RTS state&n; *          0 = reset&n; *          1 = set&n; * B2..7 Reserved&n; * B8    DTR state enable&n; *          0 = ignore&n; *          1 = use DTR state&n; * B9    RTS state enable&n; *          0 = ignore&n; *          1 = use RTS state&n; * B10..15 Reserved&n; */
multiline_comment|/* FTDI_SIO_SET_FLOW_CTRL */
DECL|macro|FTDI_SIO_SET_FLOW_CTRL_REQUEST_TYPE
mdefine_line|#define FTDI_SIO_SET_FLOW_CTRL_REQUEST_TYPE 0x40
DECL|macro|FTDI_SIO_SET_FLOW_CTRL_REQUEST
mdefine_line|#define FTDI_SIO_SET_FLOW_CTRL_REQUEST FTDI_SIO_SET_FLOW_CTRL
DECL|macro|FTDI_SIO_DISABLE_FLOW_CTRL
mdefine_line|#define FTDI_SIO_DISABLE_FLOW_CTRL 0x0 
DECL|macro|FTDI_SIO_RTS_CTS_HS
mdefine_line|#define FTDI_SIO_RTS_CTS_HS (0x1 &lt;&lt; 8)
DECL|macro|FTDI_SIO_DTR_DSR_HS
mdefine_line|#define FTDI_SIO_DTR_DSR_HS (0x2 &lt;&lt; 8)
DECL|macro|FTDI_SIO_XON_XOFF_HS
mdefine_line|#define FTDI_SIO_XON_XOFF_HS (0x4 &lt;&lt; 8)
multiline_comment|/*&n; *   BmRequestType:  0100 0000b&n; *   bRequest:       FTDI_SIO_SET_FLOW_CTRL&n; *   wValue:         Xoff/Xon&n; *   wIndex:         Protocol/Port - hIndex is protocl / lIndex is port&n; *   wLength:        0 &n; *   Data:           None&n; *&n; * hIndex protocol is:&n; *   B0 Output handshaking using RTS/CTS&n; *       0 = disabled&n; *       1 = enabled&n; *   B1 Output handshaking using DTR/DSR&n; *       0 = disabled&n; *       1 = enabled&n; *   B2 Xon/Xoff handshaking&n; *       0 = disabled&n; *       1 = enabled&n; *&n; * A value of zero in the hIndex field disables handshaking&n; *&n; * If Xon/Xoff handshaking is specified, the hValue field should contain the XOFF character &n; * and the lValue field contains the XON character.&n; */
multiline_comment|/*&n; * FTDI_SIO_SET_EVENT_CHAR &n; *&n; * Set the special event character for the specified communications port.&n; * If the device sees this character it will immediately return the&n; * data read so far - rather than wait 40ms or until 62 bytes are read&n; * which is what normally happens.&n; */
DECL|macro|FTDI_SIO_SET_EVENT_CHAR_REQUEST
mdefine_line|#define  FTDI_SIO_SET_EVENT_CHAR_REQUEST FTDI_SIO_SET_EVENT_CHAR
DECL|macro|FTDI_SIO_SET_EVENT_CHAR_REQUEST_TYPE
mdefine_line|#define  FTDI_SIO_SET_EVENT_CHAR_REQUEST_TYPE 0x40
multiline_comment|/* &n; *  BmRequestType:   0100 0000b&n; *  bRequest:        FTDI_SIO_SET_EVENT_CHAR&n; *  wValue:          EventChar&n; *  wIndex:          Port&n; *  wLength:         0&n; *  Data:            None&n; *&n; * wValue:&n; *   B0..7   Event Character&n; *   B8      Event Character Processing&n; *             0 = disabled&n; *             1 = enabled&n; *   B9..15  Reserved&n; *&n; */
multiline_comment|/* FTDI_SIO_SET_ERROR_CHAR */
multiline_comment|/* Set the parity error replacement character for the specified communications port */
multiline_comment|/* &n; *  BmRequestType:  0100 0000b&n; *  bRequest:       FTDI_SIO_SET_EVENT_CHAR&n; *  wValue:         Error Char&n; *  wIndex:         Port&n; *  wLength:        0&n; *  Data:           None&n; *&n; *Error Char&n; *  B0..7  Error Character&n; *  B8     Error Character Processing&n; *           0 = disabled&n; *           1 = enabled&n; *  B9..15 Reserved&n; *&n; */
multiline_comment|/* FTDI_SIO_GET_MODEM_STATUS */
multiline_comment|/* Retreive the current value of the modem status register */
DECL|macro|FTDI_SIO_GET_MODEM_STATUS_REQUEST_TYPE
mdefine_line|#define FTDI_SIO_GET_MODEM_STATUS_REQUEST_TYPE 0xc0
DECL|macro|FTDI_SIO_GET_MODEM_STATUS_REQUEST
mdefine_line|#define FTDI_SIO_GET_MODEM_STATUS_REQUEST FTDI_SIO_GET_MODEM_STATUS
DECL|macro|FTDI_SIO_CTS_MASK
mdefine_line|#define FTDI_SIO_CTS_MASK 0x10
DECL|macro|FTDI_SIO_DSR_MASK
mdefine_line|#define FTDI_SIO_DSR_MASK 0x20
DECL|macro|FTDI_SIO_RI_MASK
mdefine_line|#define FTDI_SIO_RI_MASK  0x40
DECL|macro|FTDI_SIO_RLSD_MASK
mdefine_line|#define FTDI_SIO_RLSD_MASK 0x80
multiline_comment|/* &n; *   BmRequestType:   1100 0000b&n; *   bRequest:        FTDI_SIO_GET_MODEM_STATUS&n; *   wValue:          zero&n; *   wIndex:          Port&n; *   wLength:         1&n; *   Data:            Status&n; * &n; * One byte of data is returned &n; * B0..3 0&n; * B4    CTS&n; *         0 = inactive&n; *         1 = active&n; * B5    DSR&n; *         0 = inactive&n; *         1 = active&n; * B6    Ring Indicator (RI)&n; *         0 = inactive&n; *         1 = active&n; * B7    Receive Line Signal Detect (RLSD)&n; *         0 = inactive&n; *         1 = active &n; */
multiline_comment|/* Descriptors returned by the device &n; * &n; *  Device Descriptor&n; * &n; * Offset&t;Field&t;&t;Size&t;Value&t;Description&n; * 0&t;bLength&t;&t;1&t;0x12&t;Size of descriptor in bytes&n; * 1&t;bDescriptorType&t;1&t;0x01&t;DEVICE Descriptor Type&n; * 2&t;bcdUSB&t;&t;2&t;0x0110&t;USB Spec Release Number&n; * 4&t;bDeviceClass&t;1&t;0x00&t;Class Code&n; * 5&t;bDeviceSubClass&t;1&t;0x00&t;SubClass Code&n; * 6&t;bDeviceProtocol&t;1&t;0x00&t;Protocol Code&n; * 7&t;bMaxPacketSize0 1&t;0x08&t;Maximum packet size for endpoint 0&n; * 8&t;idVendor&t;2&t;0x0403&t;Vendor ID&n; * 10&t;idProduct&t;2&t;0x8372&t;Product ID (FTDI_SIO_PID)&n; * 12&t;bcdDevice&t;2&t;0x0001&t;Device release number&n; * 14&t;iManufacturer&t;1&t;0x01&t;Index of man. string desc&n; * 15&t;iProduct&t;1&t;0x02&t;Index of prod string desc&n; * 16&t;iSerialNumber&t;1&t;0x02&t;Index of serial nmr string desc&n; * 17&t;bNumConfigurations 1    0x01&t;Number of possible configurations&n; * &n; * Configuration Descriptor&n; * &n; * Offset&t;Field&t;&t;&t;Size&t;Value&n; * 0&t;bLength&t;&t;&t;1&t;0x09&t;Size of descriptor in bytes&n; * 1&t;bDescriptorType&t;&t;1&t;0x02&t;CONFIGURATION Descriptor Type&n; * 2&t;wTotalLength&t;&t;2&t;0x0020&t;Total length of data&n; * 4&t;bNumInterfaces&t;&t;1&t;0x01&t;Number of interfaces supported&n; * 5&t;bConfigurationValue&t;1&t;0x01&t;Argument for SetCOnfiguration() req&n; * 6&t;iConfiguration&t;&t;1&t;0x02&t;Index of config string descriptor&n; * 7&t;bmAttributes&t;&t;1&t;0x20&t;Config characteristics Remote Wakeup&n; * 8&t;MaxPower&t;&t;1&t;0x1E&t;Max power consumption&n; * &n; * Interface Descriptor&n; * &n; * Offset&t;Field&t;&t;&t;Size&t;Value&n; * 0&t;bLength&t;&t;&t;1&t;0x09&t;Size of descriptor in bytes&n; * 1&t;bDescriptorType&t;&t;1&t;0x04&t;INTERFACE Descriptor Type&n; * 2&t;bInterfaceNumber&t;1&t;0x00&t;Number of interface&n; * 3&t;bAlternateSetting&t;1&t;0x00&t;Value used to select alternate&n; * 4&t;bNumEndpoints&t;&t;1&t;0x02&t;Number of endpoints&n; * 5&t;bInterfaceClass&t;&t;1&t;0xFF&t;Class Code&n; * 6&t;bInterfaceSubClass&t;1&t;0xFF&t;Subclass Code&n; * 7&t;bInterfaceProtocol&t;1&t;0xFF&t;Protocol Code&n; * 8&t;iInterface&t;&t;1&t;0x02&t;Index of interface string description&n; * &n; * IN Endpoint Descriptor&n; * &n; * Offset&t;Field&t;&t;&t;Size&t;Value&n; * 0&t;bLength&t;&t;&t;1&t;0x07&t;Size of descriptor in bytes&n; * 1&t;bDescriptorType&t;&t;1&t;0x05&t;ENDPOINT descriptor type&n; * 2&t;bEndpointAddress&t;1&t;0x82&t;Address of endpoint&n; * 3&t;bmAttributes&t;&t;1&t;0x02&t;Endpoint attributes - Bulk&n; * 4&t;bNumEndpoints&t;&t;2&t;0x0040&t;maximum packet size&n; * 5&t;bInterval&t;&t;1&t;0x00&t;Interval for polling endpoint&n; * &n; * OUT Endpoint Descriptor&n; * &n; * Offset&t;Field&t;&t;&t;Size&t;Value&n; * 0&t;bLength&t;&t;&t;1&t;0x07&t;Size of descriptor in bytes&n; * 1&t;bDescriptorType&t;&t;1&t;0x05&t;ENDPOINT descriptor type&n; * 2&t;bEndpointAddress&t;1&t;0x02&t;Address of endpoint&n; * 3&t;bmAttributes&t;&t;1&t;0x02&t;Endpoint attributes - Bulk&n; * 4&t;bNumEndpoints&t;&t;2&t;0x0040&t;maximum packet size&n; * 5&t;bInterval&t;&t;1&t;0x00&t;Interval for polling endpoint&n; *     &n; * DATA FORMAT&n; * &n; * IN Endpoint&n; * &n; * The device reserves the first two bytes of data on this endpoint to contain the current&n; * values of the modem and line status registers. In the absence of data, the device &n; * generates a message consisting of these two status bytes every 40 ms&n; * &n; * Byte 0: Modem Status&n; * &n; * Offset&t;Description&n; * B0&t;Reserved - must be 1&n; * B1&t;Reserved - must be 0&n; * B2&t;Reserved - must be 0&n; * B3&t;Reserved - must be 0&n; * B4&t;Clear to Send (CTS)&n; * B5&t;Data Set Ready (DSR)&n; * B6&t;Ring Indicator (RI)&n; * B7&t;Receive Line Signal Detect (RLSD)&n; * &n; * Byte 1: Line Status&n; * &n; * Offset&t;Description&n; * B0&t;Data Ready (DR)&n; * B1&t;Overrun Error (OE)&n; * B2&t;Parity Error (PE)&n; * B3&t;Framing Error (FE)&n; * B4&t;Break Interrupt (BI)&n; * B5&t;Transmitter Holding Register (THRE)&n; * B6&t;Transmitter Empty (TEMT)&n; * B7&t;Error in RCVR FIFO&n; * &n; */
DECL|macro|FTDI_RS_DR
mdefine_line|#define FTDI_RS_DR  1
DECL|macro|FTDI_RS_OE
mdefine_line|#define FTDI_RS_OE (1&lt;&lt;1)
DECL|macro|FTDI_RS_PE
mdefine_line|#define FTDI_RS_PE (1&lt;&lt;2)
DECL|macro|FTDI_RS_FE
mdefine_line|#define FTDI_RS_FE (1&lt;&lt;3)
DECL|macro|FTDI_RS_BI
mdefine_line|#define FTDI_RS_BI (1&lt;&lt;4)
DECL|macro|FTDI_RS_THRE
mdefine_line|#define FTDI_RS_THRE (1&lt;&lt;5)
DECL|macro|FTDI_RS_TEMT
mdefine_line|#define FTDI_RS_TEMT (1&lt;&lt;6)
DECL|macro|FTDI_RS_FIFO
mdefine_line|#define FTDI_RS_FIFO  (1&lt;&lt;7)
multiline_comment|/*&n; * OUT Endpoint&n; * &n; * This device reserves the first bytes of data on this endpoint contain the length&n; * and port identifier of the message. For the FTDI USB Serial converter the port &n; * identifier is always 1.&n; * &n; * Byte 0: Line Status&n; * &n; * Offset&t;Description&n; * B0&t;Reserved - must be 1&n; * B1&t;Reserved - must be 0&n; * B2..7&t;Length of message - (not including Byte 0)&n; * &n; */
eof
