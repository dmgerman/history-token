multiline_comment|/*&n; * &n; * Filename: serial.h&n; * &n; * Description: Some general definitions used for serial code &n; * &n; * Author(s): Timothy Stonis&n; * &n; * Copyright 1997, Cobalt Microserver, Inc.&n; */
multiline_comment|/*&n; * Serial port definitions&n; */
DECL|macro|kSCC_Base
mdefine_line|#define kSCC_Base&t;kGal_DevBank1Base
DECL|macro|kHelloWorldMsg
mdefine_line|#define kHelloWorldMsg&t;&quot;Cobalt Networks Diagnostics - &squot;We serve it, you surf it&squot;&bslash;n&bslash;r&quot;
DECL|macro|kSCC_ChanA
mdefine_line|#define kSCC_ChanA&t;0x01
DECL|macro|kSCC_ChanB
mdefine_line|#define kSCC_ChanB&t;0x00
DECL|macro|kSCC_Direct
mdefine_line|#define kSCC_Direct&t;0x02
DECL|macro|kSCC_Command
mdefine_line|#define kSCC_Command&t;0x00
DECL|macro|kSCC_TestVal
mdefine_line|#define kSCC_TestVal&t;0xA5
DECL|macro|kSCC_19200
mdefine_line|#define kSCC_19200&t;0x07&t;/* x32 clock mode, 19200 baud &t;*/
DECL|macro|kSCC_115200
mdefine_line|#define kSCC_115200&t;0x01&t;/* x16 clock mode, 115200 baud &t;*/
DECL|macro|Read8530
mdefine_line|#define Read8530(n)&t;(*((unsigned char *) (kSCC_Base | (n))))
DECL|macro|Write8530
mdefine_line|#define Write8530(x,y)&t;(*((unsigned char *) (kSCC_Base | (x))) = (y))
eof
