DECL|macro|SUSBCRequest_SetBaudRateParityAndStopBits
mdefine_line|#define SUSBCRequest_SetBaudRateParityAndStopBits       1
DECL|macro|SUSBCR_SBR_MASK
mdefine_line|#define SUSBCR_SBR_MASK&t;&t;&t;&t;0xFF00
DECL|macro|SUSBCR_SBR_1200
mdefine_line|#define SUSBCR_SBR_1200&t;&t;&t;&t;0x0100
DECL|macro|SUSBCR_SBR_9600
mdefine_line|#define SUSBCR_SBR_9600&t;&t;&t;&t;0x0200
DECL|macro|SUSBCR_SBR_19200
mdefine_line|#define SUSBCR_SBR_19200&t;&t;&t;0x0400
DECL|macro|SUSBCR_SBR_28800
mdefine_line|#define SUSBCR_SBR_28800&t;&t;&t;0x0800
DECL|macro|SUSBCR_SBR_38400
mdefine_line|#define SUSBCR_SBR_38400&t;&t;&t;0x1000
DECL|macro|SUSBCR_SBR_57600
mdefine_line|#define SUSBCR_SBR_57600&t;&t;&t;0x2000
DECL|macro|SUSBCR_SBR_115200
mdefine_line|#define SUSBCR_SBR_115200&t;&t;&t;0x4000
DECL|macro|SUSBCR_SPASB_MASK
mdefine_line|#define SUSBCR_SPASB_MASK&t;&t;&t;0x0070
DECL|macro|SUSBCR_SPASB_NoParity
mdefine_line|#define SUSBCR_SPASB_NoParity&t;&t;&t;0x0010
DECL|macro|SUSBCR_SPASB_OddParity
mdefine_line|#define SUSBCR_SPASB_OddParity&t;&t;&t;0x0020
DECL|macro|SUSBCR_SPASB_EvenParity
mdefine_line|#define SUSBCR_SPASB_EvenParity&t;&t;&t;0x0040
DECL|macro|SUSBCR_SPASB_STPMASK
mdefine_line|#define SUSBCR_SPASB_STPMASK&t;&t;&t;0x0003
DECL|macro|SUSBCR_SPASB_1StopBit
mdefine_line|#define SUSBCR_SPASB_1StopBit&t;&t;&t;0x0001
DECL|macro|SUSBCR_SPASB_2StopBits
mdefine_line|#define SUSBCR_SPASB_2StopBits&t;&t;&t;0x0002
DECL|macro|SUSBCRequest_SetStatusLinesOrQueues
mdefine_line|#define SUSBCRequest_SetStatusLinesOrQueues&t;2
DECL|macro|SUSBCR_SSL_SETRTS
mdefine_line|#define SUSBCR_SSL_SETRTS&t;&t;&t;0x0001
DECL|macro|SUSBCR_SSL_CLRRTS
mdefine_line|#define SUSBCR_SSL_CLRRTS&t;&t;&t;0x0002
DECL|macro|SUSBCR_SSL_SETDTR
mdefine_line|#define SUSBCR_SSL_SETDTR&t;&t;&t;0x0004
DECL|macro|SUSBCR_SSL_CLRDTR
mdefine_line|#define SUSBCR_SSL_CLRDTR&t;&t;&t;0x0010
DECL|macro|SUSBCR_SSL_PURGE_TXABORT
mdefine_line|#define SUSBCR_SSL_PURGE_TXABORT&t;&t;0x0100  
singleline_comment|// Kill the pending/current writes to the comm port.
DECL|macro|SUSBCR_SSL_PURGE_RXABORT
mdefine_line|#define SUSBCR_SSL_PURGE_RXABORT&t;&t;0x0200  
singleline_comment|// Kill the pending/current reads to the comm port.
DECL|macro|SUSBCR_SSL_PURGE_TXCLEAR
mdefine_line|#define SUSBCR_SSL_PURGE_TXCLEAR&t;&t;0x0400  
singleline_comment|// Kill the transmit queue if there.
DECL|macro|SUSBCR_SSL_PURGE_RXCLEAR
mdefine_line|#define SUSBCR_SSL_PURGE_RXCLEAR&t;&t;0x0800  
singleline_comment|// Kill the typeahead buffer if there.
DECL|macro|SUSBCRequest_GetStatusLineState
mdefine_line|#define SUSBCRequest_GetStatusLineState&t;&t;4
DECL|macro|SUSBCR_GSL_RXCHAR
mdefine_line|#define SUSBCR_GSL_RXCHAR&t;&t;&t;0x0001  
singleline_comment|// Any Character received
DECL|macro|SUSBCR_GSL_TXEMPTY
mdefine_line|#define SUSBCR_GSL_TXEMPTY&t;&t;&t;0x0004  
singleline_comment|// Transmitt Queue Empty
DECL|macro|SUSBCR_GSL_CTS
mdefine_line|#define SUSBCR_GSL_CTS&t;&t;&t;&t;0x0008  
singleline_comment|// CTS changed state
DECL|macro|SUSBCR_GSL_DSR
mdefine_line|#define SUSBCR_GSL_DSR&t;&t;&t;&t;0x0010  
singleline_comment|// DSR changed state
DECL|macro|SUSBCR_GSL_RLSD
mdefine_line|#define SUSBCR_GSL_RLSD&t;&t;&t;&t;0x0020  
singleline_comment|// RLSD changed state
DECL|macro|SUSBCR_GSL_BREAK
mdefine_line|#define SUSBCR_GSL_BREAK&t;&t;&t;0x0040  
singleline_comment|// BREAK received
DECL|macro|SUSBCR_GSL_ERR
mdefine_line|#define SUSBCR_GSL_ERR&t;&t;&t;&t;0x0080  
singleline_comment|// Line status error occurred
DECL|macro|SUSBCR_GSL_RING
mdefine_line|#define SUSBCR_GSL_RING&t;&t;&t;&t;0x0100  
singleline_comment|// Ring signal detected
DECL|macro|SUSBCRequest_Misc
mdefine_line|#define SUSBCRequest_Misc&t;&t;&t;8
DECL|macro|SUSBCR_MSC_ResetReader
mdefine_line|#define SUSBCR_MSC_ResetReader&t;&t;&t;0x0001&t;
singleline_comment|// use a predefined reset sequence
DECL|macro|SUSBCR_MSC_ResetAllQueues
mdefine_line|#define SUSBCR_MSC_ResetAllQueues&t;&t;0x0002&t;
singleline_comment|// use a predefined sequence to reset the internal queues
DECL|macro|SUSBCRequest_GetMisc
mdefine_line|#define SUSBCRequest_GetMisc&t;&t;&t;0x10
DECL|macro|SUSBCR_MSC_GetFWVersion
mdefine_line|#define SUSBCR_MSC_GetFWVersion&t;&t;&t;0x0001&t;/* get the firmware version from device,&n;&t;&t;&t;&t;&t;&t;&t;   coded like this 0xHHLLBBPP&n;&t;&t;&t;&t;&t;&t;&t;   with HH = Firmware Version High Byte&n;&t;&t;&t;&t;&t;&t;&t;   LL = Firmware Version Low Byte&n;&t;&t;&t;&t;&t;&t;&t;   BB = Build Number&n;&t;&t;&t;&t;&t;&t;&t;   PP = Further Attributes&n;&t;&t;&t;&t;&t;&t;&t;*/
DECL|macro|SUSBCR_MSC_GetHWVersion
mdefine_line|#define SUSBCR_MSC_GetHWVersion&t;&t;&t;0x0002&t;/* get the hardware version from device&n;&t;&t;&t;&t;&t;&t;&t;   coded like this 0xHHLLPPRR&n;&t;&t;&t;&t;&t;&t;&t;   with HH = Software Version High Byte&n;&t;&t;&t;&t;&t;&t;&t;   LL = Software Version Low Byte&n;&t;&t;&t;&t;&t;&t;&t;   PP = Further Attributes&n;&t;&t;&t;&t;&t;&t;&t;   RR = Reserved for the hardware ID &n;&t;&t;&t;&t;&t;&t;&t;*/
eof
