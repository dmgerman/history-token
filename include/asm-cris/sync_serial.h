multiline_comment|/*  &n; * ioctl defines for synchrnous serial port driver&n; *&n; * Copyright (c) 2001 Axis Communications AB&n; * &n; * Author: Mikael Starvik &n; *&n; */
macro_line|#ifndef SYNC_SERIAL_H
DECL|macro|SYNC_SERIAL_H
mdefine_line|#define SYNC_SERIAL_H
macro_line|#include &lt;linux/ioctl.h&gt;
DECL|macro|SSP_SPEED
mdefine_line|#define SSP_SPEED      _IOR(&squot;S&squot;, 0, unsigned int)
DECL|macro|SSP_MODE
mdefine_line|#define SSP_MODE       _IOR(&squot;S&squot;, 1, unsigned int)
DECL|macro|SSP_FRAME_SYNC
mdefine_line|#define SSP_FRAME_SYNC _IOR(&squot;S&squot;, 2, unsigned int)
DECL|macro|SSP_IPOLARITY
mdefine_line|#define SSP_IPOLARITY  _IOR(&squot;S&squot;, 3, unsigned int)
DECL|macro|SSP_OPOLARITY
mdefine_line|#define SSP_OPOLARITY  _IOR(&squot;S&squot;, 4, unsigned int)
DECL|macro|SSP_SPI
mdefine_line|#define SSP_SPI        _IOR(&squot;S&squot;, 5, unsigned int)
multiline_comment|/* Values for SSP_SPEED */
DECL|macro|SSP150
mdefine_line|#define SSP150        0
DECL|macro|SSP300
mdefine_line|#define SSP300        1
DECL|macro|SSP600
mdefine_line|#define SSP600        2
DECL|macro|SSP1200
mdefine_line|#define SSP1200       3  
DECL|macro|SSP2400
mdefine_line|#define SSP2400       4
DECL|macro|SSP4800
mdefine_line|#define SSP4800       5
DECL|macro|SSP9600
mdefine_line|#define SSP9600       6
DECL|macro|SSP19200
mdefine_line|#define SSP19200      7
DECL|macro|SSP28800
mdefine_line|#define SSP28800      8
DECL|macro|SSP57600
mdefine_line|#define SSP57600      9
DECL|macro|SSP115200
mdefine_line|#define SSP115200    10
DECL|macro|SSP230400
mdefine_line|#define SSP230400    11
DECL|macro|SSP460800
mdefine_line|#define SSP460800    12
DECL|macro|SSP921600
mdefine_line|#define SSP921600    13
DECL|macro|SSP3125000
mdefine_line|#define SSP3125000   14
DECL|macro|CODEC
mdefine_line|#define CODEC        15
DECL|macro|FREQ_4MHz
mdefine_line|#define FREQ_4MHz   0
DECL|macro|FREQ_2MHz
mdefine_line|#define FREQ_2MHz   1
DECL|macro|FREQ_1MHz
mdefine_line|#define FREQ_1MHz   2
DECL|macro|FREQ_512kHz
mdefine_line|#define FREQ_512kHz 3
DECL|macro|FREQ_256kHz
mdefine_line|#define FREQ_256kHz 4
DECL|macro|FREQ_128kHz
mdefine_line|#define FREQ_128kHz 5
DECL|macro|FREQ_64kHz
mdefine_line|#define FREQ_64kHz  6
DECL|macro|FREQ_32kHz
mdefine_line|#define FREQ_32kHz  7
multiline_comment|/* Used by application to set CODEC divider, word rate and frame rate */
DECL|macro|CODEC_VAL
mdefine_line|#define CODEC_VAL(freq, word, frame) (CODEC | (freq &lt;&lt; 8) | (word &lt;&lt; 16) | (frame &lt;&lt; 28))
multiline_comment|/* Used by driver to extract speed */
DECL|macro|GET_SPEED
mdefine_line|#define GET_SPEED(x) (x &amp; 0xff)
DECL|macro|GET_FREQ
mdefine_line|#define GET_FREQ(x) ((x &amp; 0xff00) &gt;&gt; 8)
DECL|macro|GET_WORD_RATE
mdefine_line|#define GET_WORD_RATE(x) (((x &amp; 0x0fff0000) &gt;&gt; 16) - 1)
DECL|macro|GET_FRAME_RATE
mdefine_line|#define GET_FRAME_RATE(x) (((x &amp; 0xf0000000) &gt;&gt; 28) - 1)
multiline_comment|/* Values for SSP_MODE */
DECL|macro|MASTER_OUTPUT
mdefine_line|#define MASTER_OUTPUT 0
DECL|macro|SLAVE_OUTPUT
mdefine_line|#define SLAVE_OUTPUT  1
DECL|macro|MASTER_INPUT
mdefine_line|#define MASTER_INPUT  2
DECL|macro|SLAVE_INPUT
mdefine_line|#define SLAVE_INPUT   3
DECL|macro|MASTER_BIDIR
mdefine_line|#define MASTER_BIDIR  4
DECL|macro|SLAVE_BIDIR
mdefine_line|#define SLAVE_BIDIR   5
multiline_comment|/* Values for SSP_FRAME_SYNC */
DECL|macro|NORMAL_SYNC
mdefine_line|#define NORMAL_SYNC                1
DECL|macro|EARLY_SYNC
mdefine_line|#define EARLY_SYNC                 2
DECL|macro|BIT_SYNC
mdefine_line|#define BIT_SYNC                   4
DECL|macro|WORD_SYNC
mdefine_line|#define WORD_SYNC                  8
DECL|macro|EXTENDED_SYNC
mdefine_line|#define EXTENDED_SYNC           0x10
DECL|macro|SYNC_OFF
mdefine_line|#define SYNC_OFF                0x20
DECL|macro|SYNC_ON
mdefine_line|#define SYNC_ON                 0x40
DECL|macro|WORD_SIZE_8
mdefine_line|#define WORD_SIZE_8             0x80
DECL|macro|WORD_SIZE_12
mdefine_line|#define WORD_SIZE_12           0x100
DECL|macro|WORD_SIZE_16
mdefine_line|#define WORD_SIZE_16           0x200
DECL|macro|WORD_SIZE_24
mdefine_line|#define WORD_SIZE_24           0x300
DECL|macro|WORD_SIZE_32
mdefine_line|#define WORD_SIZE_32           0x800
DECL|macro|BIT_ORDER_LSB
mdefine_line|#define BIT_ORDER_LSB         0x1000
DECL|macro|BIT_ORDER_MSB
mdefine_line|#define BIT_ORDER_MSB         0x2000
DECL|macro|FLOW_CONTROL_ENABLE
mdefine_line|#define FLOW_CONTROL_ENABLE   0x4000
DECL|macro|FLOW_CONTROL_DISABLE
mdefine_line|#define FLOW_CONTROL_DISABLE  0x8000
DECL|macro|CLOCK_GATED
mdefine_line|#define CLOCK_GATED          0x10000
DECL|macro|CLOCK_NOT_GATED
mdefine_line|#define CLOCK_NOT_GATED      0x20000
multiline_comment|/* Values for SSP_IPOLARITY and SSP_OPOLARITY */
DECL|macro|CLOCK_NORMAL
mdefine_line|#define CLOCK_NORMAL         1
DECL|macro|CLOCK_INVERT
mdefine_line|#define CLOCK_INVERT         2
DECL|macro|FRAME_NORMAL
mdefine_line|#define FRAME_NORMAL         4
DECL|macro|FRAME_INVERT
mdefine_line|#define FRAME_INVERT         8
DECL|macro|STATUS_NORMAL
mdefine_line|#define STATUS_NORMAL      0x10
DECL|macro|STATUS_INVERT
mdefine_line|#define STATUS_INVERT      0x20
multiline_comment|/* Values for SSP_SPI */
DECL|macro|SPI_MASTER
mdefine_line|#define SPI_MASTER           0
DECL|macro|SPI_SLAVE
mdefine_line|#define SPI_SLAVE            1  
macro_line|#endif
eof
