macro_line|#ifndef __LINUX_OV511_H
DECL|macro|__LINUX_OV511_H
mdefine_line|#define __LINUX_OV511_H
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
DECL|macro|OV511_DEBUG
mdefine_line|#define OV511_DEBUG&t;/* Turn on debug messages */
macro_line|#ifdef OV511_DEBUG
DECL|macro|PDEBUG
mdefine_line|#define PDEBUG(level, fmt, args...) &bslash;&n;&t;&t;if (debug &gt;= (level)) info(&quot;[%s:%d] &quot; fmt, &bslash;&n;&t;&t;__PRETTY_FUNCTION__, __LINE__ , ## args)
macro_line|#else
DECL|macro|PDEBUG
mdefine_line|#define PDEBUG(level, fmt, args...) do {} while(0)
macro_line|#endif
multiline_comment|/* This macro restricts an int variable to an inclusive range */
DECL|macro|RESTRICT_TO_RANGE
mdefine_line|#define RESTRICT_TO_RANGE(v,mi,ma) { &bslash;&n;&t;if ((v) &lt; (mi)) (v) = (mi); &bslash;&n;&t;else if ((v) &gt; (ma)) (v) = (ma); &bslash;&n;}
multiline_comment|/* --------------------------------- */
multiline_comment|/* DEFINES FOR OV511 AND OTHER CHIPS */
multiline_comment|/* --------------------------------- */
multiline_comment|/* USB IDs */
DECL|macro|VEND_OMNIVISION
mdefine_line|#define VEND_OMNIVISION&t;0x05A9
DECL|macro|PROD_OV511
mdefine_line|#define PROD_OV511&t;0x0511
DECL|macro|PROD_OV511PLUS
mdefine_line|#define PROD_OV511PLUS&t;0xA511
DECL|macro|PROD_OV518
mdefine_line|#define PROD_OV518&t;0x0518
DECL|macro|PROD_OV518PLUS
mdefine_line|#define PROD_OV518PLUS&t;0xA518
DECL|macro|VEND_MATTEL
mdefine_line|#define VEND_MATTEL&t;0x0813
DECL|macro|PROD_ME2CAM
mdefine_line|#define PROD_ME2CAM&t;0x0002
multiline_comment|/* --------------------------------- */
multiline_comment|/*     OV51x REGISTER MNEMONICS      */
multiline_comment|/* --------------------------------- */
multiline_comment|/* Camera interface register numbers */
DECL|macro|R511_CAM_DELAY
mdefine_line|#define R511_CAM_DELAY&t;&t;0x10
DECL|macro|R511_CAM_EDGE
mdefine_line|#define R511_CAM_EDGE&t;&t;0x11
DECL|macro|R511_CAM_PXCNT
mdefine_line|#define R511_CAM_PXCNT&t;&t;0x12
DECL|macro|R511_CAM_LNCNT
mdefine_line|#define R511_CAM_LNCNT&t;&t;0x13
DECL|macro|R511_CAM_PXDIV
mdefine_line|#define R511_CAM_PXDIV&t;&t;0x14
DECL|macro|R511_CAM_LNDIV
mdefine_line|#define R511_CAM_LNDIV&t;&t;0x15
DECL|macro|R511_CAM_UV_EN
mdefine_line|#define R511_CAM_UV_EN&t;&t;0x16
DECL|macro|R511_CAM_LINE_MODE
mdefine_line|#define R511_CAM_LINE_MODE&t;0x17
DECL|macro|R511_CAM_OPTS
mdefine_line|#define R511_CAM_OPTS&t;&t;0x18
multiline_comment|/* Snapshot mode camera interface register numbers */
DECL|macro|R511_SNAP_FRAME
mdefine_line|#define R511_SNAP_FRAME&t;&t;0x19
DECL|macro|R511_SNAP_PXCNT
mdefine_line|#define R511_SNAP_PXCNT&t;&t;0x1A
DECL|macro|R511_SNAP_LNCNT
mdefine_line|#define R511_SNAP_LNCNT&t;&t;0x1B
DECL|macro|R511_SNAP_PXDIV
mdefine_line|#define R511_SNAP_PXDIV&t;&t;0x1C
DECL|macro|R511_SNAP_LNDIV
mdefine_line|#define R511_SNAP_LNDIV&t;&t;0x1D
DECL|macro|R511_SNAP_UV_EN
mdefine_line|#define R511_SNAP_UV_EN&t;&t;0x1E
DECL|macro|R511_SNAP_OPTS
mdefine_line|#define R511_SNAP_OPTS&t;&t;0x1F
multiline_comment|/* DRAM register numbers */
DECL|macro|R511_DRAM_FLOW_CTL
mdefine_line|#define R511_DRAM_FLOW_CTL&t;0x20
DECL|macro|R511_DRAM_ARCP
mdefine_line|#define R511_DRAM_ARCP&t;&t;0x21
DECL|macro|R511_DRAM_MRC
mdefine_line|#define R511_DRAM_MRC&t;&t;0x22
DECL|macro|R511_DRAM_RFC
mdefine_line|#define R511_DRAM_RFC&t;&t;0x23
multiline_comment|/* ISO FIFO register numbers */
DECL|macro|R51x_FIFO_PSIZE
mdefine_line|#define R51x_FIFO_PSIZE&t;&t;0x30&t;/* 2 bytes wide w/ OV518(+) */
DECL|macro|R511_FIFO_OPTS
mdefine_line|#define R511_FIFO_OPTS&t;&t;0x31
multiline_comment|/* Parallel IO register numbers */
DECL|macro|R511_PIO_OPTS
mdefine_line|#define R511_PIO_OPTS&t;&t;0x38
DECL|macro|R511_PIO_DATA
mdefine_line|#define R511_PIO_DATA&t;&t;0x39
DECL|macro|R511_PIO_BIST
mdefine_line|#define R511_PIO_BIST&t;&t;0x3E
DECL|macro|R518_GPIO_IN
mdefine_line|#define R518_GPIO_IN&t;&t;0x55&t;/* OV518(+) only */
DECL|macro|R518_GPIO_OUT
mdefine_line|#define R518_GPIO_OUT&t;&t;0x56&t;/* OV518(+) only */
DECL|macro|R518_GPIO_CTL
mdefine_line|#define R518_GPIO_CTL&t;&t;0x57&t;/* OV518(+) only */
DECL|macro|R518_GPIO_PULSE_IN
mdefine_line|#define R518_GPIO_PULSE_IN&t;0x58&t;/* OV518(+) only */
DECL|macro|R518_GPIO_PULSE_CLEAR
mdefine_line|#define R518_GPIO_PULSE_CLEAR&t;0x59&t;/* OV518(+) only */
DECL|macro|R518_GPIO_PULSE_POL
mdefine_line|#define R518_GPIO_PULSE_POL&t;0x5a&t;/* OV518(+) only */
DECL|macro|R518_GPIO_PULSE_EN
mdefine_line|#define R518_GPIO_PULSE_EN&t;0x5b&t;/* OV518(+) only */
DECL|macro|R518_GPIO_RESET
mdefine_line|#define R518_GPIO_RESET&t;&t;0x5c&t;/* OV518(+) only */
multiline_comment|/* I2C registers */
DECL|macro|R511_I2C_CTL
mdefine_line|#define R511_I2C_CTL&t;&t;0x40
DECL|macro|R518_I2C_CTL
mdefine_line|#define R518_I2C_CTL&t;&t;0x47&t;/* OV518(+) only */
DECL|macro|R51x_I2C_W_SID
mdefine_line|#define R51x_I2C_W_SID&t;&t;0x41
DECL|macro|R51x_I2C_SADDR_3
mdefine_line|#define R51x_I2C_SADDR_3&t;0x42
DECL|macro|R51x_I2C_SADDR_2
mdefine_line|#define R51x_I2C_SADDR_2&t;0x43
DECL|macro|R51x_I2C_R_SID
mdefine_line|#define R51x_I2C_R_SID&t;&t;0x44
DECL|macro|R51x_I2C_DATA
mdefine_line|#define R51x_I2C_DATA&t;&t;0x45
DECL|macro|R51x_I2C_CLOCK
mdefine_line|#define R51x_I2C_CLOCK&t;&t;0x46
DECL|macro|R51x_I2C_TIMEOUT
mdefine_line|#define R51x_I2C_TIMEOUT&t;0x47
multiline_comment|/* I2C snapshot registers */
DECL|macro|R511_SI2C_SADDR_3
mdefine_line|#define R511_SI2C_SADDR_3&t;0x48
DECL|macro|R511_SI2C_DATA
mdefine_line|#define R511_SI2C_DATA&t;&t;0x49
multiline_comment|/* System control registers */
DECL|macro|R51x_SYS_RESET
mdefine_line|#define R51x_SYS_RESET&t;&t;0x50
multiline_comment|/* Reset type definitions */
DECL|macro|OV511_RESET_UDC
mdefine_line|#define &t;OV511_RESET_UDC&t;&t;0x01
DECL|macro|OV511_RESET_I2C
mdefine_line|#define &t;OV511_RESET_I2C&t;&t;0x02
DECL|macro|OV511_RESET_FIFO
mdefine_line|#define &t;OV511_RESET_FIFO&t;0x04
DECL|macro|OV511_RESET_OMNICE
mdefine_line|#define &t;OV511_RESET_OMNICE&t;0x08
DECL|macro|OV511_RESET_DRAM
mdefine_line|#define &t;OV511_RESET_DRAM&t;0x10
DECL|macro|OV511_RESET_CAM_INT
mdefine_line|#define &t;OV511_RESET_CAM_INT&t;0x20
DECL|macro|OV511_RESET_OV511
mdefine_line|#define &t;OV511_RESET_OV511&t;0x40
DECL|macro|OV511_RESET_NOREGS
mdefine_line|#define &t;OV511_RESET_NOREGS&t;0x3F /* All but OV511 &amp; regs */
DECL|macro|OV511_RESET_ALL
mdefine_line|#define &t;OV511_RESET_ALL&t;&t;0x7F
DECL|macro|R511_SYS_CLOCK_DIV
mdefine_line|#define R511_SYS_CLOCK_DIV&t;0x51
DECL|macro|R51x_SYS_SNAP
mdefine_line|#define R51x_SYS_SNAP&t;&t;0x52
DECL|macro|R51x_SYS_INIT
mdefine_line|#define R51x_SYS_INIT         &t;0x53
DECL|macro|R511_SYS_PWR_CLK
mdefine_line|#define R511_SYS_PWR_CLK&t;0x54 /* OV511+/OV518(+) only */
DECL|macro|R511_SYS_LED_CTL
mdefine_line|#define R511_SYS_LED_CTL&t;0x55 /* OV511+ only */
DECL|macro|R511_SYS_USER
mdefine_line|#define R511_SYS_USER&t;&t;0x5E
DECL|macro|R511_SYS_CUST_ID
mdefine_line|#define R511_SYS_CUST_ID&t;0x5F
multiline_comment|/* OmniCE (compression) registers */
DECL|macro|R511_COMP_PHY
mdefine_line|#define R511_COMP_PHY&t;&t;0x70
DECL|macro|R511_COMP_PHUV
mdefine_line|#define R511_COMP_PHUV&t;&t;0x71
DECL|macro|R511_COMP_PVY
mdefine_line|#define R511_COMP_PVY&t;&t;0x72
DECL|macro|R511_COMP_PVUV
mdefine_line|#define R511_COMP_PVUV&t;&t;0x73
DECL|macro|R511_COMP_QHY
mdefine_line|#define R511_COMP_QHY&t;&t;0x74
DECL|macro|R511_COMP_QHUV
mdefine_line|#define R511_COMP_QHUV&t;&t;0x75
DECL|macro|R511_COMP_QVY
mdefine_line|#define R511_COMP_QVY&t;&t;0x76
DECL|macro|R511_COMP_QVUV
mdefine_line|#define R511_COMP_QVUV&t;&t;0x77
DECL|macro|R511_COMP_EN
mdefine_line|#define R511_COMP_EN&t;&t;0x78
DECL|macro|R511_COMP_LUT_EN
mdefine_line|#define R511_COMP_LUT_EN&t;0x79&t;&t;
DECL|macro|R511_COMP_LUT_BEGIN
mdefine_line|#define R511_COMP_LUT_BEGIN&t;0x80
multiline_comment|/* --------------------------------- */
multiline_comment|/*         ALTERNATE NUMBERS         */
multiline_comment|/* --------------------------------- */
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
multiline_comment|/* Alternate numbers for various max packet sizes (OV518(+) only) */
DECL|macro|OV518_ALT_SIZE_0
mdefine_line|#define OV518_ALT_SIZE_0&t;0
DECL|macro|OV518_ALT_SIZE_128
mdefine_line|#define OV518_ALT_SIZE_128&t;1
DECL|macro|OV518_ALT_SIZE_256
mdefine_line|#define OV518_ALT_SIZE_256&t;2
DECL|macro|OV518_ALT_SIZE_384
mdefine_line|#define OV518_ALT_SIZE_384&t;3
DECL|macro|OV518_ALT_SIZE_512
mdefine_line|#define OV518_ALT_SIZE_512&t;4
DECL|macro|OV518_ALT_SIZE_640
mdefine_line|#define OV518_ALT_SIZE_640&t;5
DECL|macro|OV518_ALT_SIZE_768
mdefine_line|#define OV518_ALT_SIZE_768&t;6
DECL|macro|OV518_ALT_SIZE_896
mdefine_line|#define OV518_ALT_SIZE_896&t;7
multiline_comment|/* --------------------------------- */
multiline_comment|/*     OV7610 REGISTER MNEMONICS     */
multiline_comment|/* --------------------------------- */
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
multiline_comment|/* --------------------------------- */
multiline_comment|/*           I2C ADDRESSES           */
multiline_comment|/* --------------------------------- */
DECL|macro|OV7xx0_SID
mdefine_line|#define OV7xx0_SID   0x42
DECL|macro|OV6xx0_SID
mdefine_line|#define OV6xx0_SID   0xC0
DECL|macro|OV8xx0_SID
mdefine_line|#define OV8xx0_SID   0xA0
DECL|macro|KS0127_SID
mdefine_line|#define KS0127_SID   0xD8
DECL|macro|SAA7111A_SID
mdefine_line|#define SAA7111A_SID 0x48
multiline_comment|/* --------------------------------- */
multiline_comment|/*       MISCELLANEOUS DEFINES       */
multiline_comment|/* --------------------------------- */
DECL|macro|I2C_CLOCK_PRESCALER
mdefine_line|#define I2C_CLOCK_PRESCALER &t;0x03
DECL|macro|FRAMES_PER_DESC
mdefine_line|#define FRAMES_PER_DESC&t;&t;10&t;/* FIXME - What should this be? */
DECL|macro|MAX_FRAME_SIZE_PER_DESC
mdefine_line|#define MAX_FRAME_SIZE_PER_DESC&t;993&t;/* For statically allocated stuff */
DECL|macro|PIXELS_PER_SEG
mdefine_line|#define PIXELS_PER_SEG&t;&t;256&t;/* Pixels per segment */
DECL|macro|OV511_ENDPOINT_ADDRESS
mdefine_line|#define OV511_ENDPOINT_ADDRESS&t;1&t;/* Isoc endpoint number */
DECL|macro|OV511_NUMFRAMES
mdefine_line|#define OV511_NUMFRAMES&t;2
macro_line|#if OV511_NUMFRAMES &gt; VIDEO_MAX_FRAME
macro_line|#error &quot;OV511_NUMFRAMES is too high&quot;
macro_line|#endif
DECL|macro|OV511_NUMSBUF
mdefine_line|#define OV511_NUMSBUF&t;&t;2
multiline_comment|/* Control transfers use up to 4 bytes */
DECL|macro|OV511_CBUF_SIZE
mdefine_line|#define OV511_CBUF_SIZE&t;&t;4
multiline_comment|/* Bridge types */
r_enum
(brace
DECL|enumerator|BRG_UNKNOWN
id|BRG_UNKNOWN
comma
DECL|enumerator|BRG_OV511
id|BRG_OV511
comma
DECL|enumerator|BRG_OV511PLUS
id|BRG_OV511PLUS
comma
DECL|enumerator|BRG_OV518
id|BRG_OV518
comma
DECL|enumerator|BRG_OV518PLUS
id|BRG_OV518PLUS
comma
)brace
suffix:semicolon
multiline_comment|/* Bridge classes */
r_enum
(brace
DECL|enumerator|BCL_UNKNOWN
id|BCL_UNKNOWN
comma
DECL|enumerator|BCL_OV511
id|BCL_OV511
comma
DECL|enumerator|BCL_OV518
id|BCL_OV518
comma
)brace
suffix:semicolon
multiline_comment|/* Sensor types */
r_enum
(brace
DECL|enumerator|SEN_UNKNOWN
id|SEN_UNKNOWN
comma
DECL|enumerator|SEN_OV76BE
id|SEN_OV76BE
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
DECL|enumerator|SEN_OV6630
id|SEN_OV6630
comma
DECL|enumerator|SEN_OV6630AE
id|SEN_OV6630AE
comma
DECL|enumerator|SEN_OV6630AF
id|SEN_OV6630AF
comma
DECL|enumerator|SEN_OV8600
id|SEN_OV8600
comma
DECL|enumerator|SEN_KS0127
id|SEN_KS0127
comma
DECL|enumerator|SEN_KS0127B
id|SEN_KS0127B
comma
DECL|enumerator|SEN_SAA7111A
id|SEN_SAA7111A
comma
)brace
suffix:semicolon
singleline_comment|// Not implemented yet
macro_line|#if 0
multiline_comment|/* Sensor classes */
r_enum
(brace
id|SCL_UNKNOWN
comma
id|SCL_OV7610
comma
multiline_comment|/* 7610, 76BE, 7620AE (for now) */
id|SCL_OV7620
comma
id|SCL_OV6620
comma
id|SCL_OV6630
comma
multiline_comment|/* 6630, 6630AE, 6630AF */
id|SCL_OV8600
comma
id|SCL_KS0127
comma
multiline_comment|/* SEN_KS0127, SEN_KS0127B */
id|SCL_SAA7111A
comma
)brace
suffix:semicolon
macro_line|#endif
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
multiline_comment|/* --------- Definition of ioctl interface --------- */
DECL|macro|OV511_INTERFACE_VER
mdefine_line|#define OV511_INTERFACE_VER 101
multiline_comment|/* LED options */
r_enum
(brace
DECL|enumerator|LED_OFF
id|LED_OFF
comma
DECL|enumerator|LED_ON
id|LED_ON
comma
DECL|enumerator|LED_AUTO
id|LED_AUTO
comma
)brace
suffix:semicolon
multiline_comment|/* Raw frame formats */
r_enum
(brace
DECL|enumerator|RAWFMT_INVALID
id|RAWFMT_INVALID
comma
DECL|enumerator|RAWFMT_YUV400
id|RAWFMT_YUV400
comma
DECL|enumerator|RAWFMT_YUV420
id|RAWFMT_YUV420
comma
DECL|enumerator|RAWFMT_YUV422
id|RAWFMT_YUV422
comma
DECL|enumerator|RAWFMT_GBR422
id|RAWFMT_GBR422
comma
)brace
suffix:semicolon
multiline_comment|/* Unsigned short option numbers */
r_enum
(brace
DECL|enumerator|OV511_USOPT_INVALID
id|OV511_USOPT_INVALID
comma
DECL|enumerator|OV511_USOPT_BRIGHT
id|OV511_USOPT_BRIGHT
comma
DECL|enumerator|OV511_USOPT_SAT
id|OV511_USOPT_SAT
comma
DECL|enumerator|OV511_USOPT_HUE
id|OV511_USOPT_HUE
comma
DECL|enumerator|OV511_USOPT_CONTRAST
id|OV511_USOPT_CONTRAST
comma
)brace
suffix:semicolon
multiline_comment|/* Unsigned int option numbers */
r_enum
(brace
DECL|enumerator|OV511_UIOPT_INVALID
id|OV511_UIOPT_INVALID
comma
DECL|enumerator|OV511_UIOPT_POWER_FREQ
id|OV511_UIOPT_POWER_FREQ
comma
DECL|enumerator|OV511_UIOPT_BFILTER
id|OV511_UIOPT_BFILTER
comma
DECL|enumerator|OV511_UIOPT_LED
id|OV511_UIOPT_LED
comma
DECL|enumerator|OV511_UIOPT_DEBUG
id|OV511_UIOPT_DEBUG
comma
DECL|enumerator|OV511_UIOPT_COMPRESS
id|OV511_UIOPT_COMPRESS
comma
)brace
suffix:semicolon
DECL|struct|ov511_ushort_opt
r_struct
id|ov511_ushort_opt
(brace
DECL|member|optnum
r_int
id|optnum
suffix:semicolon
multiline_comment|/* Specific option number */
DECL|member|val
r_int
r_int
id|val
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ov511_uint_opt
r_struct
id|ov511_uint_opt
(brace
DECL|member|optnum
r_int
id|optnum
suffix:semicolon
multiline_comment|/* Specific option number */
DECL|member|val
r_int
r_int
id|val
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ov511_i2c_struct
r_struct
id|ov511_i2c_struct
(brace
DECL|member|slave
r_int
r_char
id|slave
suffix:semicolon
multiline_comment|/* Write slave ID (read ID - 1) */
DECL|member|reg
r_int
r_char
id|reg
suffix:semicolon
multiline_comment|/* Index of register */
DECL|member|value
r_int
r_char
id|value
suffix:semicolon
multiline_comment|/* User sets this w/ write, driver does w/ read */
DECL|member|mask
r_int
r_char
id|mask
suffix:semicolon
multiline_comment|/* Bits to be changed. Not used with read ops */
)brace
suffix:semicolon
multiline_comment|/* ioctls */
DECL|macro|OV511IOC_GINTVER
mdefine_line|#define OV511IOC_GINTVER  _IOR(&squot;v&squot;, BASE_VIDIOCPRIVATE + 0, int)
DECL|macro|OV511IOC_GUSHORT
mdefine_line|#define OV511IOC_GUSHORT _IOWR(&squot;v&squot;, BASE_VIDIOCPRIVATE + 1, &bslash;&n;&t;&t;&t;       struct ov511_ushort_opt)
DECL|macro|OV511IOC_SUSHORT
mdefine_line|#define OV511IOC_SUSHORT  _IOW(&squot;v&squot;, BASE_VIDIOCPRIVATE + 2, &bslash;&n;&t;&t;&t;       struct ov511_ushort_opt)
DECL|macro|OV511IOC_GUINT
mdefine_line|#define OV511IOC_GUINT   _IOWR(&squot;v&squot;, BASE_VIDIOCPRIVATE + 3, &bslash;&n;&t;&t;&t;       struct ov511_uint_opt)
DECL|macro|OV511IOC_SUINT
mdefine_line|#define OV511IOC_SUINT    _IOW(&squot;v&squot;, BASE_VIDIOCPRIVATE + 4, &bslash;&n;&t;&t;&t;       struct ov511_uint_opt)
DECL|macro|OV511IOC_WI2C
mdefine_line|#define OV511IOC_WI2C     _IOW(&squot;v&squot;, BASE_VIDIOCPRIVATE + 5, &bslash;&n;&t;&t;&t;       struct ov511_i2c_struct)
DECL|macro|OV511IOC_RI2C
mdefine_line|#define OV511IOC_RI2C    _IOWR(&squot;v&squot;, BASE_VIDIOCPRIVATE + 6, &bslash;&n;&t;&t;&t;       struct ov511_i2c_struct)
multiline_comment|/* ------------- End IOCTL interface -------------- */
r_struct
id|usb_ov511
suffix:semicolon
multiline_comment|/* Forward declaration */
DECL|struct|ov511_sbuf
r_struct
id|ov511_sbuf
(brace
DECL|member|ov
r_struct
id|usb_ov511
op_star
id|ov
suffix:semicolon
DECL|member|data
r_int
r_char
op_star
id|data
suffix:semicolon
DECL|member|urb
r_struct
id|urb
op_star
id|urb
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|n
r_int
id|n
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
DECL|member|framenum
r_int
id|framenum
suffix:semicolon
multiline_comment|/* Index of this frame */
DECL|member|data
r_int
r_char
op_star
id|data
suffix:semicolon
multiline_comment|/* Frame buffer */
DECL|member|tempdata
r_int
r_char
op_star
id|tempdata
suffix:semicolon
multiline_comment|/* Temp buffer for multi-stage conversions */
DECL|member|rawdata
r_int
r_char
op_star
id|rawdata
suffix:semicolon
multiline_comment|/* Raw camera data buffer */
DECL|member|compbuf
r_int
r_char
op_star
id|compbuf
suffix:semicolon
multiline_comment|/* Temp buffer for decompressor */
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
multiline_comment|/* Height application is expecting */
DECL|member|rawwidth
r_int
id|rawwidth
suffix:semicolon
multiline_comment|/* Actual width of frame sent from camera */
DECL|member|rawheight
r_int
id|rawheight
suffix:semicolon
multiline_comment|/* Actual height of frame sent from camera */
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
DECL|member|compressed
r_int
id|compressed
suffix:semicolon
multiline_comment|/* Is frame compressed? */
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
DECL|member|bytes_recvd
r_int
id|bytes_recvd
suffix:semicolon
multiline_comment|/* Number of image bytes received from camera */
DECL|member|bytes_read
r_int
id|bytes_read
suffix:semicolon
multiline_comment|/* Amount that has been read() */
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
DECL|macro|DECOMP_INTERFACE_VER
mdefine_line|#define DECOMP_INTERFACE_VER 4
multiline_comment|/* Compression module operations */
DECL|struct|ov51x_decomp_ops
r_struct
id|ov51x_decomp_ops
(brace
DECL|member|decomp_400
r_int
(paren
op_star
id|decomp_400
)paren
(paren
r_int
r_char
op_star
comma
r_int
r_char
op_star
comma
r_int
r_char
op_star
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|decomp_420
r_int
(paren
op_star
id|decomp_420
)paren
(paren
r_int
r_char
op_star
comma
r_int
r_char
op_star
comma
r_int
r_char
op_star
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|decomp_422
r_int
(paren
op_star
id|decomp_422
)paren
(paren
r_int
r_char
op_star
comma
r_int
r_char
op_star
comma
r_int
r_char
op_star
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
)brace
suffix:semicolon
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
r_char
op_star
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
DECL|member|minwidth
r_int
id|minwidth
suffix:semicolon
DECL|member|minheight
r_int
id|minheight
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
DECL|member|exposure
r_int
id|exposure
suffix:semicolon
DECL|member|auto_brt
r_int
id|auto_brt
suffix:semicolon
multiline_comment|/* Auto brightness enabled flag */
DECL|member|auto_gain
r_int
id|auto_gain
suffix:semicolon
multiline_comment|/* Auto gain control enabled flag */
DECL|member|auto_exp
r_int
id|auto_exp
suffix:semicolon
multiline_comment|/* Auto exposure enabled flag */
DECL|member|backlight
r_int
id|backlight
suffix:semicolon
multiline_comment|/* Backlight exposure algorithm flag */
DECL|member|mirror
r_int
id|mirror
suffix:semicolon
multiline_comment|/* Image is reversed horizontally */
DECL|member|led_policy
r_int
id|led_policy
suffix:semicolon
multiline_comment|/* LED: off|on|auto; OV511+ only */
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
multiline_comment|/* Serializes user-accessible operations */
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
DECL|member|compress_inited
r_int
id|compress_inited
suffix:semicolon
multiline_comment|/* Are compression params uploaded? */
DECL|member|lightfreq
r_int
id|lightfreq
suffix:semicolon
multiline_comment|/* Power (lighting) frequency */
DECL|member|bandfilt
r_int
id|bandfilt
suffix:semicolon
multiline_comment|/* Banding filter enabled flag */
DECL|member|fbuf
r_int
r_char
op_star
id|fbuf
suffix:semicolon
multiline_comment|/* Videodev buffer area */
DECL|member|tempfbuf
r_int
r_char
op_star
id|tempfbuf
suffix:semicolon
multiline_comment|/* Temporary (intermediate) buffer area */
DECL|member|rawfbuf
r_int
r_char
op_star
id|rawfbuf
suffix:semicolon
multiline_comment|/* Raw camera data buffer area */
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
DECL|member|sbuf
r_struct
id|ov511_sbuf
id|sbuf
(braket
id|OV511_NUMSBUF
)braket
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
multiline_comment|/* Type of bridge (BRG_*) */
DECL|member|bclass
r_int
id|bclass
suffix:semicolon
multiline_comment|/* Class of bridge (BCL_*) */
DECL|member|sensor
r_int
id|sensor
suffix:semicolon
multiline_comment|/* Type of image sensor chip (SEN_*) */
DECL|member|sclass
r_int
id|sclass
suffix:semicolon
multiline_comment|/* Type of image sensor chip (SCL_*) */
DECL|member|packet_size
r_int
id|packet_size
suffix:semicolon
multiline_comment|/* Frame size per isoc desc */
DECL|member|packet_numbering
r_int
id|packet_numbering
suffix:semicolon
multiline_comment|/* Is ISO frame numbering enabled? */
DECL|member|param_lock
r_struct
id|semaphore
id|param_lock
suffix:semicolon
multiline_comment|/* params lock for this camera */
multiline_comment|/* /proc entries, relative to /proc/video/ov511/ */
DECL|member|proc_devdir
r_struct
id|proc_dir_entry
op_star
id|proc_devdir
suffix:semicolon
multiline_comment|/* Per-device proc directory */
DECL|member|proc_info
r_struct
id|proc_dir_entry
op_star
id|proc_info
suffix:semicolon
multiline_comment|/* &lt;minor#&gt;/info entry */
DECL|member|proc_button
r_struct
id|proc_dir_entry
op_star
id|proc_button
suffix:semicolon
multiline_comment|/* &lt;minor#&gt;/button entry */
DECL|member|proc_control
r_struct
id|proc_dir_entry
op_star
id|proc_control
suffix:semicolon
multiline_comment|/* &lt;minor#&gt;/control entry */
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
DECL|member|decomp_ops
r_struct
id|ov51x_decomp_ops
op_star
id|decomp_ops
suffix:semicolon
multiline_comment|/* Stop streaming while changing picture settings */
DECL|member|stop_during_set
r_int
id|stop_during_set
suffix:semicolon
DECL|member|stopped
r_int
id|stopped
suffix:semicolon
multiline_comment|/* Streaming is temporarily paused */
multiline_comment|/* Video decoder stuff */
DECL|member|input
r_int
id|input
suffix:semicolon
multiline_comment|/* Composite, S-VIDEO, etc... */
DECL|member|num_inputs
r_int
id|num_inputs
suffix:semicolon
multiline_comment|/* Number of inputs */
DECL|member|norm
r_int
id|norm
suffix:semicolon
multiline_comment|/* NTSC / PAL / SECAM */
DECL|member|has_decoder
r_int
id|has_decoder
suffix:semicolon
multiline_comment|/* Device has a video decoder */
DECL|member|has_tuner
r_int
id|has_tuner
suffix:semicolon
multiline_comment|/* Device has a TV tuner */
DECL|member|has_audio_proc
r_int
id|has_audio_proc
suffix:semicolon
multiline_comment|/* Device has an audio processor */
DECL|member|freq
r_int
id|freq
suffix:semicolon
multiline_comment|/* Current tuner frequency */
DECL|member|tuner_type
r_int
id|tuner_type
suffix:semicolon
multiline_comment|/* Specific tuner model */
DECL|member|pal
r_int
id|pal
suffix:semicolon
multiline_comment|/* Device is designed for PAL resolution */
multiline_comment|/* I2C interface to kernel */
DECL|member|i2c_lock
r_struct
id|semaphore
id|i2c_lock
suffix:semicolon
multiline_comment|/* Protect I2C controller regs */
DECL|member|primary_i2c_slave
r_int
r_char
id|primary_i2c_slave
suffix:semicolon
multiline_comment|/* I2C write id of sensor */
DECL|member|tuner_i2c_slave
r_int
r_char
id|tuner_i2c_slave
suffix:semicolon
multiline_comment|/* I2C write id of tuner */
DECL|member|audio_i2c_slave
r_int
r_char
id|audio_i2c_slave
suffix:semicolon
multiline_comment|/* I2C write id of audio processor */
multiline_comment|/* Control transaction stuff */
DECL|member|cbuf
r_int
r_char
op_star
id|cbuf
suffix:semicolon
multiline_comment|/* Buffer for payload */
DECL|member|cbuf_lock
r_struct
id|semaphore
id|cbuf_lock
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Used to represent a list of values and their respective symbolic names */
DECL|struct|symbolic_list
r_struct
id|symbolic_list
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
DECL|macro|NOT_DEFINED_STR
mdefine_line|#define NOT_DEFINED_STR &quot;Unknown&quot;
multiline_comment|/* Returns the name of the matching element in the symbolic_list array. The&n; * end of the list must be marked with an element that has a NULL name.&n; */
r_static
r_inline
r_char
op_star
DECL|function|symbolic
id|symbolic
c_func
(paren
r_struct
id|symbolic_list
id|list
(braket
)braket
comma
r_int
id|num
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|list
(braket
id|i
)braket
dot
id|name
op_ne
l_int|NULL
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|list
(braket
id|i
)braket
dot
id|num
op_eq
id|num
)paren
r_return
(paren
id|list
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
r_return
(paren
id|NOT_DEFINED_STR
)paren
suffix:semicolon
)brace
multiline_comment|/* Compression stuff */
DECL|macro|OV511_QUANTABLESIZE
mdefine_line|#define OV511_QUANTABLESIZE&t;64
DECL|macro|OV518_QUANTABLESIZE
mdefine_line|#define OV518_QUANTABLESIZE&t;32
DECL|macro|OV511_YQUANTABLE
mdefine_line|#define OV511_YQUANTABLE { &bslash;&n;&t;0, 1, 1, 2, 2, 3, 3, 4, &bslash;&n;&t;1, 1, 1, 2, 2, 3, 4, 4, &bslash;&n;&t;1, 1, 2, 2, 3, 4, 4, 4, &bslash;&n;&t;2, 2, 2, 3, 4, 4, 4, 4, &bslash;&n;&t;2, 2, 3, 4, 4, 5, 5, 5, &bslash;&n;&t;3, 3, 4, 4, 5, 5, 5, 5, &bslash;&n;&t;3, 4, 4, 4, 5, 5, 5, 5, &bslash;&n;&t;4, 4, 4, 4, 5, 5, 5, 5  &bslash;&n;}
DECL|macro|OV511_UVQUANTABLE
mdefine_line|#define OV511_UVQUANTABLE { &bslash;&n;&t;0, 2, 2, 3, 4, 4, 4, 4, &bslash;&n;&t;2, 2, 2, 4, 4, 4, 4, 4, &bslash;&n;&t;2, 2, 3, 4, 4, 4, 4, 4, &bslash;&n;&t;3, 4, 4, 4, 4, 4, 4, 4, &bslash;&n;&t;4, 4, 4, 4, 4, 4, 4, 4, &bslash;&n;&t;4, 4, 4, 4, 4, 4, 4, 4, &bslash;&n;&t;4, 4, 4, 4, 4, 4, 4, 4, &bslash;&n;&t;4, 4, 4, 4, 4, 4, 4, 4  &bslash;&n;}
DECL|macro|OV518_YQUANTABLE
mdefine_line|#define OV518_YQUANTABLE { &bslash;&n;&t;5, 4, 5, 6, 6, 7, 7, 7, &bslash;&n;&t;5, 5, 5, 5, 6, 7, 7, 7, &bslash;&n;&t;6, 6, 6, 6, 7, 7, 7, 8, &bslash;&n;&t;7, 7, 6, 7, 7, 7, 8, 8  &bslash;&n;}
DECL|macro|OV518_UVQUANTABLE
mdefine_line|#define OV518_UVQUANTABLE { &bslash;&n;&t;6, 6, 6, 7, 7, 7, 7, 7, &bslash;&n;&t;6, 6, 6, 7, 7, 7, 7, 7, &bslash;&n;&t;6, 6, 6, 7, 7, 7, 7, 8, &bslash;&n;&t;7, 7, 7, 7, 7, 7, 8, 8  &bslash;&n;}
macro_line|#endif
eof
