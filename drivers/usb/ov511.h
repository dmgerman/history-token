macro_line|#ifndef __LINUX_OV511_H
DECL|macro|__LINUX_OV511_H
mdefine_line|#define __LINUX_OV511_H
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
DECL|macro|OV511_DEBUG
mdefine_line|#define OV511_DEBUG&t;/* Turn on debug messages */
macro_line|#ifdef OV511_DEBUG
DECL|macro|PDEBUG
macro_line|#  define PDEBUG(level, fmt, args...) &bslash;&n;if (debug &gt;= level) info(&quot;[&quot; __PRETTY_FUNCTION__ &quot;:%d] &quot; fmt, __LINE__ , ## args)
macro_line|#else
DECL|macro|PDEBUG
macro_line|#  define PDEBUG(level, fmt, args...) do {} while(0)
macro_line|#endif
multiline_comment|/* Camera interface register numbers */
DECL|macro|OV511_REG_CAMERA_DELAY_MODE
mdefine_line|#define OV511_REG_CAMERA_DELAY_MODE&t;&t;0x10
DECL|macro|OV511_REG_CAMERA_EDGE_MODE
mdefine_line|#define OV511_REG_CAMERA_EDGE_MODE&t;&t;0x11
DECL|macro|OV511_REG_CAMERA_CLAMPED_PIXEL_NUM
mdefine_line|#define OV511_REG_CAMERA_CLAMPED_PIXEL_NUM&t;0x12
DECL|macro|OV511_REG_CAMERA_CLAMPED_LINE_NUM
mdefine_line|#define OV511_REG_CAMERA_CLAMPED_LINE_NUM&t;0x13
DECL|macro|OV511_REG_CAMERA_PIXEL_DIVISOR
mdefine_line|#define OV511_REG_CAMERA_PIXEL_DIVISOR&t;&t;0x14
DECL|macro|OV511_REG_CAMERA_LINE_DIVISOR
mdefine_line|#define OV511_REG_CAMERA_LINE_DIVISOR&t;&t;0x15
DECL|macro|OV511_REG_CAMERA_DATA_INPUT_SELECT
mdefine_line|#define OV511_REG_CAMERA_DATA_INPUT_SELECT&t;0x16
DECL|macro|OV511_REG_CAMERA_RESERVED_LINE_MODE
mdefine_line|#define OV511_REG_CAMERA_RESERVED_LINE_MODE&t;0x17
DECL|macro|OV511_REG_CAMERA_BITMASK
mdefine_line|#define OV511_REG_CAMERA_BITMASK&t;&t;0x18
multiline_comment|/* Snapshot mode camera interface register numbers */
DECL|macro|OV511_REG_SNAP_CAPTURED_FRAME
mdefine_line|#define OV511_REG_SNAP_CAPTURED_FRAME&t;&t;0x19
DECL|macro|OV511_REG_SNAP_CLAMPED_PIXEL_NUM
mdefine_line|#define OV511_REG_SNAP_CLAMPED_PIXEL_NUM&t;0x1A
DECL|macro|OV511_REG_SNAP_CLAMPED_LINE_NUM
mdefine_line|#define OV511_REG_SNAP_CLAMPED_LINE_NUM&t;&t;0x1B
DECL|macro|OV511_REG_SNAP_PIXEL_DIVISOR
mdefine_line|#define OV511_REG_SNAP_PIXEL_DIVISOR&t;&t;0x1C
DECL|macro|OV511_REG_SNAP_LINE_DIVISOR
mdefine_line|#define OV511_REG_SNAP_LINE_DIVISOR&t;&t;0x1D
DECL|macro|OV511_REG_SNAP_DATA_INPUT_SELECT
mdefine_line|#define OV511_REG_SNAP_DATA_INPUT_SELECT&t;0x1E
DECL|macro|OV511_REG_SNAP_BITMASK
mdefine_line|#define OV511_REG_SNAP_BITMASK&t;&t;&t;0x1F
multiline_comment|/* DRAM register numbers */
DECL|macro|OV511_REG_DRAM_ENABLE_FLOW_CONTROL
mdefine_line|#define OV511_REG_DRAM_ENABLE_FLOW_CONTROL&t;0x20
DECL|macro|OV511_REG_DRAM_READ_CYCLE_PREDICT
mdefine_line|#define OV511_REG_DRAM_READ_CYCLE_PREDICT&t;0x21
DECL|macro|OV511_REG_DRAM_MANUAL_READ_CYCLE
mdefine_line|#define OV511_REG_DRAM_MANUAL_READ_CYCLE&t;0x22
DECL|macro|OV511_REG_DRAM_REFRESH_COUNTER
mdefine_line|#define OV511_REG_DRAM_REFRESH_COUNTER&t;&t;0x23
multiline_comment|/* ISO FIFO register numbers */
DECL|macro|OV511_REG_FIFO_PACKET_SIZE
mdefine_line|#define OV511_REG_FIFO_PACKET_SIZE&t;&t;0x30
DECL|macro|OV511_REG_FIFO_BITMASK
mdefine_line|#define OV511_REG_FIFO_BITMASK&t;&t;&t;0x31
multiline_comment|/* PIO register numbers */
DECL|macro|OV511_REG_PIO_BITMASK
mdefine_line|#define OV511_REG_PIO_BITMASK&t;&t;&t;0x38
DECL|macro|OV511_REG_PIO_DATA_PORT
mdefine_line|#define OV511_REG_PIO_DATA_PORT&t;&t;&t;0x39
DECL|macro|OV511_REG_PIO_BIST
mdefine_line|#define OV511_REG_PIO_BIST&t;&t;&t;0x3E
multiline_comment|/* I2C register numbers */
DECL|macro|OV511_REG_I2C_CONTROL
mdefine_line|#define OV511_REG_I2C_CONTROL&t;&t;&t;0x40
DECL|macro|OV511_REG_I2C_SLAVE_ID_WRITE
mdefine_line|#define OV511_REG_I2C_SLAVE_ID_WRITE&t;&t;0x41
DECL|macro|OV511_REG_I2C_SUB_ADDRESS_3_BYTE
mdefine_line|#define OV511_REG_I2C_SUB_ADDRESS_3_BYTE&t;0x42
DECL|macro|OV511_REG_I2C_SUB_ADDRESS_2_BYTE
mdefine_line|#define OV511_REG_I2C_SUB_ADDRESS_2_BYTE&t;0x43
DECL|macro|OV511_REG_I2C_SLAVE_ID_READ
mdefine_line|#define OV511_REG_I2C_SLAVE_ID_READ&t;&t;0x44
DECL|macro|OV511_REG_I2C_DATA_PORT
mdefine_line|#define OV511_REG_I2C_DATA_PORT&t;&t;&t;0x45
DECL|macro|OV511_REG_I2C_CLOCK_PRESCALER
mdefine_line|#define OV511_REG_I2C_CLOCK_PRESCALER&t;&t;0x46
DECL|macro|OV511_REG_I2C_TIME_OUT_COUNTER
mdefine_line|#define OV511_REG_I2C_TIME_OUT_COUNTER&t;&t;0x47
multiline_comment|/* I2C snapshot register numbers */
DECL|macro|OV511_REG_I2C_SNAP_SUB_ADDRESS
mdefine_line|#define OV511_REG_I2C_SNAP_SUB_ADDRESS&t;&t;0x48
DECL|macro|OV511_REG_I2C_SNAP_DATA_PORT
mdefine_line|#define OV511_REG_I2C_SNAP_DATA_PORT&t;&t;0x49
multiline_comment|/* System control register numbers */
DECL|macro|OV511_REG_SYSTEM_RESET
mdefine_line|#define OV511_REG_SYSTEM_RESET&t;&t;&t;0x50
DECL|macro|OV511_RESET_UDC
mdefine_line|#define &t;OV511_RESET_UDC&t;&t;&t;0x01
DECL|macro|OV511_RESET_I2C
mdefine_line|#define &t;OV511_RESET_I2C&t;&t;&t;0x02
DECL|macro|OV511_RESET_FIFO
mdefine_line|#define &t;OV511_RESET_FIFO&t;&t;0x04
DECL|macro|OV511_RESET_OMNICE
mdefine_line|#define &t;OV511_RESET_OMNICE&t;&t;0x08
DECL|macro|OV511_RESET_DRAM_INTF
mdefine_line|#define &t;OV511_RESET_DRAM_INTF&t;&t;0x10
DECL|macro|OV511_RESET_CAMERA_INTF
mdefine_line|#define &t;OV511_RESET_CAMERA_INTF&t;&t;0x20
DECL|macro|OV511_RESET_OV511
mdefine_line|#define &t;OV511_RESET_OV511&t;&t;0x40
DECL|macro|OV511_RESET_NOREGS
mdefine_line|#define &t;OV511_RESET_NOREGS&t;&t;0x3F /* All but OV511 &amp; regs */
DECL|macro|OV511_RESET_ALL
mdefine_line|#define &t;OV511_RESET_ALL&t;&t;&t;0x7F
DECL|macro|OV511_REG_SYSTEM_CLOCK_DIVISOR
mdefine_line|#define OV511_REG_SYSTEM_CLOCK_DIVISOR&t;&t;0x51
DECL|macro|OV511_REG_SYSTEM_SNAPSHOT
mdefine_line|#define OV511_REG_SYSTEM_SNAPSHOT&t;&t;0x52
DECL|macro|OV511_REG_SYSTEM_INIT
mdefine_line|#define OV511_REG_SYSTEM_INIT         &t;&t;0x53
DECL|macro|OV511_REG_SYSTEM_PWR_CLK
mdefine_line|#define OV511_REG_SYSTEM_PWR_CLK&t;&t;0x54&t;/* OV511+ only */
DECL|macro|OV511_REG_SYSTEM_LED_CTL
mdefine_line|#define OV511_REG_SYSTEM_LED_CTL&t;&t;0x55&t;/* OV511+ only */
DECL|macro|OV511_REG_SYSTEM_USER_DEFINED
mdefine_line|#define OV511_REG_SYSTEM_USER_DEFINED&t;&t;0x5E
DECL|macro|OV511_REG_SYSTEM_CUSTOM_ID
mdefine_line|#define OV511_REG_SYSTEM_CUSTOM_ID&t;&t;0x5F
multiline_comment|/* OmniCE register numbers */
DECL|macro|OV511_OMNICE_PREDICTION_HORIZ_Y
mdefine_line|#define OV511_OMNICE_PREDICTION_HORIZ_Y&t;&t;0x70
DECL|macro|OV511_OMNICE_PREDICTION_HORIZ_UV
mdefine_line|#define OV511_OMNICE_PREDICTION_HORIZ_UV&t;0x71
DECL|macro|OV511_OMNICE_PREDICTION_VERT_Y
mdefine_line|#define OV511_OMNICE_PREDICTION_VERT_Y&t;&t;0x72
DECL|macro|OV511_OMNICE_PREDICTION_VERT_UV
mdefine_line|#define OV511_OMNICE_PREDICTION_VERT_UV&t;&t;0x73
DECL|macro|OV511_OMNICE_QUANTIZATION_HORIZ_Y
mdefine_line|#define OV511_OMNICE_QUANTIZATION_HORIZ_Y&t;0x74
DECL|macro|OV511_OMNICE_QUANTIZATION_HORIZ_UV
mdefine_line|#define OV511_OMNICE_QUANTIZATION_HORIZ_UV&t;0x75
DECL|macro|OV511_OMNICE_QUANTIZATION_VERT_Y
mdefine_line|#define OV511_OMNICE_QUANTIZATION_VERT_Y&t;0x76
DECL|macro|OV511_OMNICE_QUANTIZATION_VERT_UV
mdefine_line|#define OV511_OMNICE_QUANTIZATION_VERT_UV&t;0x77
DECL|macro|OV511_OMNICE_ENABLE
mdefine_line|#define OV511_OMNICE_ENABLE&t;&t;&t;0x78
DECL|macro|OV511_OMNICE_LUT_ENABLE
mdefine_line|#define OV511_OMNICE_LUT_ENABLE&t;&t;&t;0x79&t;&t;
DECL|macro|OV511_OMNICE_Y_LUT_BEGIN
mdefine_line|#define OV511_OMNICE_Y_LUT_BEGIN&t;&t;0x80
DECL|macro|OV511_OMNICE_Y_LUT_END
mdefine_line|#define OV511_OMNICE_Y_LUT_END&t;&t;&t;0x9F
DECL|macro|OV511_OMNICE_UV_LUT_BEGIN
mdefine_line|#define OV511_OMNICE_UV_LUT_BEGIN&t;&t;0xA0
DECL|macro|OV511_OMNICE_UV_LUT_END
mdefine_line|#define OV511_OMNICE_UV_LUT_END&t;&t;&t;0xBF
multiline_comment|/* Alternate numbers for various max packet sizes (OV511 only) */
DECL|macro|OV511_ALT_SIZE_992
mdefine_line|#define OV511_ALT_SIZE_992&t;0
DECL|macro|OV511_ALT_SIZE_993
mdefine_line|#define OV511_ALT_SIZE_993&t;1
DECL|macro|OV511_ALT_SIZE_768
mdefine_line|#define OV511_ALT_SIZE_768&t;2
DECL|macro|OV511_ALT_SIZE_769
mdefine_line|#define OV511_ALT_SIZE_769&t;3
DECL|macro|OV511_ALT_SIZE_512
mdefine_line|#define OV511_ALT_SIZE_512&t;4
DECL|macro|OV511_ALT_SIZE_513
mdefine_line|#define OV511_ALT_SIZE_513&t;5
DECL|macro|OV511_ALT_SIZE_257
mdefine_line|#define OV511_ALT_SIZE_257&t;6
DECL|macro|OV511_ALT_SIZE_0
mdefine_line|#define OV511_ALT_SIZE_0&t;7
multiline_comment|/* Alternate numbers for various max packet sizes (OV511+ only) */
DECL|macro|OV511PLUS_ALT_SIZE_0
mdefine_line|#define OV511PLUS_ALT_SIZE_0&t;0
DECL|macro|OV511PLUS_ALT_SIZE_33
mdefine_line|#define OV511PLUS_ALT_SIZE_33&t;1
DECL|macro|OV511PLUS_ALT_SIZE_129
mdefine_line|#define OV511PLUS_ALT_SIZE_129&t;2
DECL|macro|OV511PLUS_ALT_SIZE_257
mdefine_line|#define OV511PLUS_ALT_SIZE_257&t;3
DECL|macro|OV511PLUS_ALT_SIZE_385
mdefine_line|#define OV511PLUS_ALT_SIZE_385&t;4
DECL|macro|OV511PLUS_ALT_SIZE_513
mdefine_line|#define OV511PLUS_ALT_SIZE_513&t;5
DECL|macro|OV511PLUS_ALT_SIZE_769
mdefine_line|#define OV511PLUS_ALT_SIZE_769&t;6
DECL|macro|OV511PLUS_ALT_SIZE_961
mdefine_line|#define OV511PLUS_ALT_SIZE_961&t;7
multiline_comment|/* OV7610 registers */
DECL|macro|OV7610_REG_GAIN
mdefine_line|#define OV7610_REG_GAIN          0x00&t;/* gain setting (5:0) */
DECL|macro|OV7610_REG_BLUE
mdefine_line|#define OV7610_REG_BLUE          0x01&t;/* blue channel balance */
DECL|macro|OV7610_REG_RED
mdefine_line|#define OV7610_REG_RED           0x02&t;/* red channel balance */
DECL|macro|OV7610_REG_SAT
mdefine_line|#define OV7610_REG_SAT           0x03&t;/* saturation */
multiline_comment|/* 04 reserved */
DECL|macro|OV7610_REG_CNT
mdefine_line|#define OV7610_REG_CNT           0x05&t;/* Y contrast */
DECL|macro|OV7610_REG_BRT
mdefine_line|#define OV7610_REG_BRT           0x06&t;/* Y brightness */
multiline_comment|/* 08-0b reserved */
DECL|macro|OV7610_REG_BLUE_BIAS
mdefine_line|#define OV7610_REG_BLUE_BIAS     0x0C&t;/* blue channel bias (5:0) */
DECL|macro|OV7610_REG_RED_BIAS
mdefine_line|#define OV7610_REG_RED_BIAS      0x0D&t;/* read channel bias (5:0) */
DECL|macro|OV7610_REG_GAMMA_COEFF
mdefine_line|#define OV7610_REG_GAMMA_COEFF   0x0E&t;/* gamma settings */
DECL|macro|OV7610_REG_WB_RANGE
mdefine_line|#define OV7610_REG_WB_RANGE      0x0F&t;/* AEC/ALC/S-AWB settings */
DECL|macro|OV7610_REG_EXP
mdefine_line|#define OV7610_REG_EXP           0x10&t;/* manual exposure setting */
DECL|macro|OV7610_REG_CLOCK
mdefine_line|#define OV7610_REG_CLOCK         0x11&t;/* polarity/clock prescaler */
DECL|macro|OV7610_REG_COM_A
mdefine_line|#define OV7610_REG_COM_A         0x12&t;/* misc common regs */
DECL|macro|OV7610_REG_COM_B
mdefine_line|#define OV7610_REG_COM_B         0x13&t;/* misc common regs */
DECL|macro|OV7610_REG_COM_C
mdefine_line|#define OV7610_REG_COM_C         0x14&t;/* misc common regs */
DECL|macro|OV7610_REG_COM_D
mdefine_line|#define OV7610_REG_COM_D         0x15&t;/* misc common regs */
DECL|macro|OV7610_REG_FIELD_DIVIDE
mdefine_line|#define OV7610_REG_FIELD_DIVIDE  0x16&t;/* field interval/mode settings */
DECL|macro|OV7610_REG_HWIN_START
mdefine_line|#define OV7610_REG_HWIN_START    0x17&t;/* horizontal window start */
DECL|macro|OV7610_REG_HWIN_END
mdefine_line|#define OV7610_REG_HWIN_END      0x18&t;/* horizontal window end */
DECL|macro|OV7610_REG_VWIN_START
mdefine_line|#define OV7610_REG_VWIN_START    0x19&t;/* vertical window start */
DECL|macro|OV7610_REG_VWIN_END
mdefine_line|#define OV7610_REG_VWIN_END      0x1A&t;/* vertical window end */
DECL|macro|OV7610_REG_PIXEL_SHIFT
mdefine_line|#define OV7610_REG_PIXEL_SHIFT   0x1B&t;/* pixel shift */
DECL|macro|OV7610_REG_ID_HIGH
mdefine_line|#define OV7610_REG_ID_HIGH       0x1C&t;/* manufacturer ID MSB */
DECL|macro|OV7610_REG_ID_LOW
mdefine_line|#define OV7610_REG_ID_LOW        0x1D&t;/* manufacturer ID LSB */
multiline_comment|/* 0e-0f reserved */
DECL|macro|OV7610_REG_COM_E
mdefine_line|#define OV7610_REG_COM_E         0x20&t;/* misc common regs */
DECL|macro|OV7610_REG_YOFFSET
mdefine_line|#define OV7610_REG_YOFFSET       0x21&t;/* Y channel offset */
DECL|macro|OV7610_REG_UOFFSET
mdefine_line|#define OV7610_REG_UOFFSET       0x22&t;/* U channel offset */
multiline_comment|/* 23 reserved */
DECL|macro|OV7610_REG_ECW
mdefine_line|#define OV7610_REG_ECW           0x24&t;/* Exposure white level for AEC */
DECL|macro|OV7610_REG_ECB
mdefine_line|#define OV7610_REG_ECB           0x25&t;/* Exposure black level for AEC */
DECL|macro|OV7610_REG_COM_F
mdefine_line|#define OV7610_REG_COM_F         0x26&t;/* misc settings */
DECL|macro|OV7610_REG_COM_G
mdefine_line|#define OV7610_REG_COM_G         0x27&t;/* misc settings */
DECL|macro|OV7610_REG_COM_H
mdefine_line|#define OV7610_REG_COM_H         0x28&t;/* misc settings */
DECL|macro|OV7610_REG_COM_I
mdefine_line|#define OV7610_REG_COM_I         0x29&t;/* misc settings */
DECL|macro|OV7610_REG_FRAMERATE_H
mdefine_line|#define OV7610_REG_FRAMERATE_H   0x2A&t;/* frame rate MSB + misc */
DECL|macro|OV7610_REG_FRAMERATE_L
mdefine_line|#define OV7610_REG_FRAMERATE_L   0x2B&t;/* frame rate LSB */
DECL|macro|OV7610_REG_ALC
mdefine_line|#define OV7610_REG_ALC           0x2C&t;/* Auto Level Control settings */
DECL|macro|OV7610_REG_COM_J
mdefine_line|#define OV7610_REG_COM_J         0x2D&t;/* misc settings */
DECL|macro|OV7610_REG_VOFFSET
mdefine_line|#define OV7610_REG_VOFFSET       0x2E&t;/* V channel offset adjustment */
DECL|macro|OV7610_REG_ARRAY_BIAS
mdefine_line|#define OV7610_REG_ARRAY_BIAS&t; 0x2F&t;/* Array bias -- don&squot;t change */
multiline_comment|/* 30-32 reserved */
DECL|macro|OV7610_REG_YGAMMA
mdefine_line|#define OV7610_REG_YGAMMA        0x33&t;/* misc gamma settings (7:6) */
DECL|macro|OV7610_REG_BIAS_ADJUST
mdefine_line|#define OV7610_REG_BIAS_ADJUST   0x34&t;/* misc bias settings */
DECL|macro|OV7610_REG_COM_L
mdefine_line|#define OV7610_REG_COM_L         0x35&t;/* misc settings */
multiline_comment|/* 36-37 reserved */
DECL|macro|OV7610_REG_COM_K
mdefine_line|#define OV7610_REG_COM_K         0x38&t;/* misc registers */
DECL|macro|SCRATCH_BUF_SIZE
mdefine_line|#define SCRATCH_BUF_SIZE 512
DECL|macro|FRAMES_PER_DESC
mdefine_line|#define FRAMES_PER_DESC&t;&t;10&t;/* FIXME - What should this be? */
DECL|macro|FRAME_SIZE_PER_DESC
mdefine_line|#define FRAME_SIZE_PER_DESC&t;993&t;/* FIXME - Deprecated */
DECL|macro|MAX_FRAME_SIZE_PER_DESC
mdefine_line|#define MAX_FRAME_SIZE_PER_DESC&t;993&t;/* For statically allocated stuff */
DECL|macro|OV511_ENDPOINT_ADDRESS
mdefine_line|#define OV511_ENDPOINT_ADDRESS 1&t;/* Isoc endpoint number */
singleline_comment|// CAMERA SPECIFIC
singleline_comment|// FIXME - these can vary between specific models
DECL|macro|OV7610_I2C_WRITE_ID
mdefine_line|#define OV7610_I2C_WRITE_ID 0x42
DECL|macro|OV7610_I2C_READ_ID
mdefine_line|#define OV7610_I2C_READ_ID  0x43
DECL|macro|OV6xx0_I2C_WRITE_ID
mdefine_line|#define OV6xx0_I2C_WRITE_ID 0xC0
DECL|macro|OV6xx0_I2C_READ_ID
mdefine_line|#define OV6xx0_I2C_READ_ID  0xC1
DECL|macro|OV511_I2C_CLOCK_PRESCALER
mdefine_line|#define OV511_I2C_CLOCK_PRESCALER 0x03
multiline_comment|/* Prototypes */
r_int
id|usb_ov511_reg_read
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
r_char
id|reg
)paren
suffix:semicolon
r_int
id|usb_ov511_reg_write
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
r_char
id|reg
comma
r_int
r_char
id|value
)paren
suffix:semicolon
multiline_comment|/* Bridge types */
r_enum
(brace
DECL|enumerator|BRG_OV511
id|BRG_OV511
comma
DECL|enumerator|BRG_OV511PLUS
id|BRG_OV511PLUS
comma
)brace
suffix:semicolon
multiline_comment|/* Sensor types */
r_enum
(brace
DECL|enumerator|SEN_UNKNOWN
id|SEN_UNKNOWN
comma
DECL|enumerator|SEN_OV7610
id|SEN_OV7610
comma
DECL|enumerator|SEN_OV7620
id|SEN_OV7620
comma
DECL|enumerator|SEN_OV7620AE
id|SEN_OV7620AE
comma
DECL|enumerator|SEN_OV6620
id|SEN_OV6620
comma
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|STATE_SCANNING
id|STATE_SCANNING
comma
multiline_comment|/* Scanning for start */
DECL|enumerator|STATE_HEADER
id|STATE_HEADER
comma
multiline_comment|/* Parsing header */
DECL|enumerator|STATE_LINES
id|STATE_LINES
comma
multiline_comment|/* Parsing lines */
)brace
suffix:semicolon
multiline_comment|/* Buffer states */
r_enum
(brace
DECL|enumerator|BUF_NOT_ALLOCATED
id|BUF_NOT_ALLOCATED
comma
DECL|enumerator|BUF_ALLOCATED
id|BUF_ALLOCATED
comma
DECL|enumerator|BUF_PEND_DEALLOC
id|BUF_PEND_DEALLOC
comma
multiline_comment|/* ov511-&gt;buf_timer is set */
)brace
suffix:semicolon
r_struct
id|usb_device
suffix:semicolon
DECL|struct|ov511_sbuf
r_struct
id|ov511_sbuf
(brace
DECL|member|data
r_char
op_star
id|data
suffix:semicolon
DECL|member|urb
id|urb_t
op_star
id|urb
suffix:semicolon
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|FRAME_UNUSED
id|FRAME_UNUSED
comma
multiline_comment|/* Unused (no MCAPTURE) */
DECL|enumerator|FRAME_READY
id|FRAME_READY
comma
multiline_comment|/* Ready to start grabbing */
DECL|enumerator|FRAME_GRABBING
id|FRAME_GRABBING
comma
multiline_comment|/* In the process of being grabbed into */
DECL|enumerator|FRAME_DONE
id|FRAME_DONE
comma
multiline_comment|/* Finished grabbing, but not been synced yet */
DECL|enumerator|FRAME_ERROR
id|FRAME_ERROR
comma
multiline_comment|/* Something bad happened while processing */
)brace
suffix:semicolon
DECL|struct|ov511_regvals
r_struct
id|ov511_regvals
(brace
r_enum
(brace
DECL|enumerator|OV511_DONE_BUS
id|OV511_DONE_BUS
comma
DECL|enumerator|OV511_REG_BUS
id|OV511_REG_BUS
comma
DECL|enumerator|OV511_I2C_BUS
id|OV511_I2C_BUS
comma
DECL|member|bus
)brace
id|bus
suffix:semicolon
DECL|member|reg
r_int
r_char
id|reg
suffix:semicolon
DECL|member|val
r_int
r_char
id|val
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ov511_frame
r_struct
id|ov511_frame
(brace
DECL|member|data
r_char
op_star
id|data
suffix:semicolon
multiline_comment|/* Frame buffer */
DECL|member|depth
r_int
id|depth
suffix:semicolon
multiline_comment|/* Bytes per pixel */
DECL|member|width
r_int
id|width
suffix:semicolon
multiline_comment|/* Width application is expecting */
DECL|member|height
r_int
id|height
suffix:semicolon
multiline_comment|/* Height */
DECL|member|hdrwidth
r_int
id|hdrwidth
suffix:semicolon
multiline_comment|/* Width the frame actually is */
DECL|member|hdrheight
r_int
id|hdrheight
suffix:semicolon
multiline_comment|/* Height */
DECL|member|sub_flag
r_int
id|sub_flag
suffix:semicolon
multiline_comment|/* Sub-capture mode for this frame? */
DECL|member|format
r_int
r_int
id|format
suffix:semicolon
multiline_comment|/* Format for this frame */
DECL|member|segsize
r_int
id|segsize
suffix:semicolon
multiline_comment|/* How big is each segment from the camera? */
DECL|member|grabstate
r_volatile
r_int
id|grabstate
suffix:semicolon
multiline_comment|/* State of grabbing */
DECL|member|scanstate
r_int
id|scanstate
suffix:semicolon
multiline_comment|/* State of scanning */
DECL|member|curline
r_int
id|curline
suffix:semicolon
multiline_comment|/* Line of frame we&squot;re working on */
DECL|member|curpix
r_int
id|curpix
suffix:semicolon
DECL|member|segment
r_int
id|segment
suffix:semicolon
multiline_comment|/* Segment from the incoming data */
DECL|member|scanlength
r_int
id|scanlength
suffix:semicolon
multiline_comment|/* uncompressed, raw data length of frame */
DECL|member|bytes_read
r_int
id|bytes_read
suffix:semicolon
multiline_comment|/* amount of scanlength that has been read from *data */
DECL|member|wq
id|wait_queue_head_t
id|wq
suffix:semicolon
multiline_comment|/* Processes waiting */
DECL|member|snapshot
r_int
id|snapshot
suffix:semicolon
multiline_comment|/* True if frame was a snapshot */
)brace
suffix:semicolon
DECL|macro|OV511_NUMFRAMES
mdefine_line|#define OV511_NUMFRAMES&t;2
DECL|macro|OV511_NUMSBUF
mdefine_line|#define OV511_NUMSBUF&t;2
DECL|struct|usb_ov511
r_struct
id|usb_ov511
(brace
DECL|member|vdev
r_struct
id|video_device
id|vdev
suffix:semicolon
multiline_comment|/* Device structure */
DECL|member|dev
r_struct
id|usb_device
op_star
id|dev
suffix:semicolon
DECL|member|customid
r_int
id|customid
suffix:semicolon
DECL|member|desc
r_int
id|desc
suffix:semicolon
DECL|member|iface
r_int
r_char
id|iface
suffix:semicolon
multiline_comment|/* Determined by sensor type */
DECL|member|maxwidth
r_int
id|maxwidth
suffix:semicolon
DECL|member|maxheight
r_int
id|maxheight
suffix:semicolon
DECL|member|brightness
r_int
id|brightness
suffix:semicolon
DECL|member|colour
r_int
id|colour
suffix:semicolon
DECL|member|contrast
r_int
id|contrast
suffix:semicolon
DECL|member|hue
r_int
id|hue
suffix:semicolon
DECL|member|whiteness
r_int
id|whiteness
suffix:semicolon
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
DECL|member|user
r_int
id|user
suffix:semicolon
multiline_comment|/* user count for exclusive use */
DECL|member|streaming
r_int
id|streaming
suffix:semicolon
multiline_comment|/* Are we streaming Isochronous? */
DECL|member|grabbing
r_int
id|grabbing
suffix:semicolon
multiline_comment|/* Are we grabbing? */
DECL|member|compress
r_int
id|compress
suffix:semicolon
multiline_comment|/* Should the next frame be compressed? */
DECL|member|fbuf
r_char
op_star
id|fbuf
suffix:semicolon
multiline_comment|/* Videodev buffer area */
DECL|member|sub_flag
r_int
id|sub_flag
suffix:semicolon
multiline_comment|/* Pix Array subcapture on flag */
DECL|member|subx
r_int
id|subx
suffix:semicolon
multiline_comment|/* Pix Array subcapture x offset */
DECL|member|suby
r_int
id|suby
suffix:semicolon
multiline_comment|/* Pix Array subcapture y offset */
DECL|member|subw
r_int
id|subw
suffix:semicolon
multiline_comment|/* Pix Array subcapture width */
DECL|member|subh
r_int
id|subh
suffix:semicolon
multiline_comment|/* Pix Array subcapture height */
DECL|member|curframe
r_int
id|curframe
suffix:semicolon
multiline_comment|/* Current receiving sbuf */
DECL|member|frame
r_struct
id|ov511_frame
id|frame
(braket
id|OV511_NUMFRAMES
)braket
suffix:semicolon
DECL|member|cursbuf
r_int
id|cursbuf
suffix:semicolon
multiline_comment|/* Current receiving sbuf */
DECL|member|sbuf
r_struct
id|ov511_sbuf
id|sbuf
(braket
id|OV511_NUMSBUF
)braket
suffix:semicolon
multiline_comment|/* Scratch space from the Isochronous pipe */
DECL|member|scratch
r_int
r_char
id|scratch
(braket
id|SCRATCH_BUF_SIZE
)braket
suffix:semicolon
DECL|member|scratchlen
r_int
id|scratchlen
suffix:semicolon
DECL|member|wq
id|wait_queue_head_t
id|wq
suffix:semicolon
multiline_comment|/* Processes waiting */
DECL|member|snap_enabled
r_int
id|snap_enabled
suffix:semicolon
multiline_comment|/* Snapshot mode enabled */
DECL|member|bridge
r_int
id|bridge
suffix:semicolon
multiline_comment|/* Type of bridge (OV511 or OV511+) */
DECL|member|sensor
r_int
id|sensor
suffix:semicolon
multiline_comment|/* Type of image sensor chip */
DECL|member|packet_size
r_int
id|packet_size
suffix:semicolon
multiline_comment|/* Frame size per isoc desc */
multiline_comment|/* proc interface */
DECL|member|param_lock
r_struct
id|semaphore
id|param_lock
suffix:semicolon
multiline_comment|/* params lock for this camera */
DECL|member|proc_entry
r_struct
id|proc_dir_entry
op_star
id|proc_entry
suffix:semicolon
multiline_comment|/* /proc/ov511/videoX */
multiline_comment|/* Framebuffer/sbuf management */
DECL|member|buf_state
r_int
id|buf_state
suffix:semicolon
DECL|member|buf_lock
r_struct
id|semaphore
id|buf_lock
suffix:semicolon
DECL|member|buf_timer
r_struct
id|timer_list
id|buf_timer
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cam_list
r_struct
id|cam_list
(brace
DECL|member|id
r_int
id|id
suffix:semicolon
DECL|member|description
r_char
op_star
id|description
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|palette_list
r_struct
id|palette_list
(brace
DECL|member|num
r_int
id|num
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mode_list
r_struct
id|mode_list
(brace
DECL|member|width
r_int
id|width
suffix:semicolon
DECL|member|height
r_int
id|height
suffix:semicolon
DECL|member|color
r_int
id|color
suffix:semicolon
multiline_comment|/* 0=grayscale, 1=color */
DECL|member|pxcnt
id|u8
id|pxcnt
suffix:semicolon
multiline_comment|/* pixel counter */
DECL|member|lncnt
id|u8
id|lncnt
suffix:semicolon
multiline_comment|/* line counter */
DECL|member|pxdv
id|u8
id|pxdv
suffix:semicolon
multiline_comment|/* pixel divisor */
DECL|member|lndv
id|u8
id|lndv
suffix:semicolon
multiline_comment|/* line divisor */
DECL|member|m420
id|u8
id|m420
suffix:semicolon
DECL|member|common_A
id|u8
id|common_A
suffix:semicolon
DECL|member|common_L
id|u8
id|common_L
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
