multiline_comment|/***************************************************************************&n; * API for image sensors connected to the SN9C10x PC Camera Controllers    *&n; *                                                                         *&n; * Copyright (C) 2004 by Luca Risolia &lt;luca.risolia@studio.unibo.it&gt;       *&n; *                                                                         *&n; * This program is free software; you can redistribute it and/or modify    *&n; * it under the terms of the GNU General Public License as published by    *&n; * the Free Software Foundation; either version 2 of the License, or       *&n; * (at your option) any later version.                                     *&n; *                                                                         *&n; * This program is distributed in the hope that it will be useful,         *&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of          *&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *&n; * GNU General Public License for more details.                            *&n; *                                                                         *&n; * You should have received a copy of the GNU General Public License       *&n; * along with this program; if not, write to the Free Software             *&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.               *&n; ***************************************************************************/
macro_line|#ifndef _SN9C102_SENSOR_H_
DECL|macro|_SN9C102_SENSOR_H_
mdefine_line|#define _SN9C102_SENSOR_H_
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/types.h&gt;
r_struct
id|sn9c102_device
suffix:semicolon
r_struct
id|sn9c102_sensor
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n;   OVERVIEW.&n;   This is a small interface that allows you to add support for any CCD/CMOS&n;   image sensors connected to the SN9C10X bridges. The entire API is documented&n;   below. In the most general case, to support a sensor there are three steps&n;   you have to follow:&n;   1) define the main &quot;sn9c102_sensor&quot; structure by setting the basic fields;&n;   2) write a probing function to be called by the core module when the USB&n;      camera is recognized, then add both the USB ids and the name of that&n;      function to the two corresponding tables SENSOR_TABLE and ID_TABLE (see&n;      below);&n;   3) implement the methods that you want/need (and fill the rest of the main&n;      structure accordingly).&n;   &quot;sn9c102_pas106b.c&quot; is an example of all this stuff. Remember that you do&n;   NOT need to touch the source code of the core module for the things to work&n;   properly, unless you find bugs or flaws in it. Finally, do not forget to&n;   read the V4L2 API for completeness.&n;*/
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n;   Probing functions: on success, you must attach the sensor to the camera&n;   by calling sn9c102_attach_sensor() provided below.&n;   To enable the I2C communication, you might need to perform a really basic&n;   initialization of the SN9C10X chip by using the write function declared &n;   ahead.&n;   Functions must return 0 on success, the appropriate error otherwise.&n;*/
r_extern
r_int
id|sn9c102_probe_pas106b
c_func
(paren
r_struct
id|sn9c102_device
op_star
id|cam
)paren
suffix:semicolon
r_extern
r_int
id|sn9c102_probe_pas202bcb
c_func
(paren
r_struct
id|sn9c102_device
op_star
id|cam
)paren
suffix:semicolon
r_extern
r_int
id|sn9c102_probe_tas5110c1b
c_func
(paren
r_struct
id|sn9c102_device
op_star
id|cam
)paren
suffix:semicolon
r_extern
r_int
id|sn9c102_probe_tas5130d1b
c_func
(paren
r_struct
id|sn9c102_device
op_star
id|cam
)paren
suffix:semicolon
multiline_comment|/*&n;   Add the above entries to this table. Be sure to add the entry in the right&n;   place, since, on failure, the next probing routine is called according to &n;   the order of the list below, from top to bottom.&n;*/
DECL|macro|SN9C102_SENSOR_TABLE
mdefine_line|#define SN9C102_SENSOR_TABLE                                                  &bslash;&n;static int (*sn9c102_sensor_table[])(struct sn9c102_device*) = {              &bslash;&n;&t;&amp;sn9c102_probe_pas106b, /* strong detection based on SENSOR ids */    &bslash;&n;&t;&amp;sn9c102_probe_pas202bcb, /* strong detection based on SENSOR ids */  &bslash;&n;&t;&amp;sn9c102_probe_tas5110c1b, /* detection based on USB pid/vid */       &bslash;&n;&t;&amp;sn9c102_probe_tas5130d1b, /* detection based on USB pid/vid */       &bslash;&n;&t;NULL,                                                                 &bslash;&n;};
multiline_comment|/* Attach a probed sensor to the camera. */
r_extern
r_void
id|sn9c102_attach_sensor
c_func
(paren
r_struct
id|sn9c102_device
op_star
id|cam
comma
r_struct
id|sn9c102_sensor
op_star
id|sensor
)paren
suffix:semicolon
multiline_comment|/* Each SN9C10X camera has proper PID/VID identifiers. Add them here in case.*/
DECL|macro|SN9C102_ID_TABLE
mdefine_line|#define SN9C102_ID_TABLE                                                      &bslash;&n;static const struct usb_device_id sn9c102_id_table[] = {                      &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x6001), }, /* TAS5110C1B */                     &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x6005), }, /* TAS5110C1B */                     &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x6009), }, /* PAS106B */                        &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x600d), }, /* PAS106B */                        &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x6024), },                                      &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x6025), }, /* TAS5130D1B and TAS5110C1B */      &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x6028), }, /* PAS202BCB */                      &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x6029), }, /* PAS106B */                        &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x602a), }, /* HV7131[D|E1] */                   &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x602b), }, /* MI-0343 */                        &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x602c), }, /* OV7620 */                         &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x6030), }, /* MI03x */                          &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x6080), },                                      &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x6082), }, /* MI0343 and MI0360 */              &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x6083), }, /* HV7131[D|E1] */                   &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x6088), },                                      &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x608a), },                                      &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x608b), },                                      &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x608c), }, /* HV7131x */                        &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x608e), }, /* CIS-VF10 */                       &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x608f), }, /* OV7630 */                         &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x60a0), },                                      &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x60a2), },                                      &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x60a3), },                                      &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x60a8), }, /* PAS106B */                        &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x60aa), }, /* TAS5130D1B */                     &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x60ab), }, /* TAS5110C1B */                     &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x60ac), },                                      &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x60ae), },                                      &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x60af), }, /* PAS202BCB */                      &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x60b0), },                                      &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x60b2), },                                      &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x60b3), },                                      &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x60b8), },                                      &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x60ba), },                                      &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x60bb), },                                      &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x60bc), },                                      &bslash;&n;&t;{ USB_DEVICE(0x0c45, 0x60be), },                                      &bslash;&n;&t;{ }                                                                   &bslash;&n;};
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n;   Read/write routines: they always return -1 on error, 0 or the read value&n;   otherwise. NOTE that a real read operation is not supported by the SN9C10X&n;   chip for some of its registers. To work around this problem, a pseudo-read&n;   call is provided instead: it returns the last successfully written value &n;   on the register (0 if it has never been written), the usual -1 on error.&n;*/
multiline_comment|/* The &quot;try&quot; I2C I/O versions are used when probing the sensor */
r_extern
r_int
id|sn9c102_i2c_try_write
c_func
(paren
r_struct
id|sn9c102_device
op_star
comma
r_struct
id|sn9c102_sensor
op_star
comma
id|u8
id|address
comma
id|u8
id|value
)paren
suffix:semicolon
r_extern
r_int
id|sn9c102_i2c_try_read
c_func
(paren
r_struct
id|sn9c102_device
op_star
comma
r_struct
id|sn9c102_sensor
op_star
comma
id|u8
id|address
)paren
suffix:semicolon
multiline_comment|/*&n;   This must be used if and only if the sensor doesn&squot;t implement the standard&n;   I2C protocol. There a number of good reasons why you must use the &n;   single-byte versions of this function: do not abuse. It writes n bytes, &n;   from data0 to datan, (registers 0x09 - 0x09+n of SN9C10X chip).&n;*/
r_extern
r_int
id|sn9c102_i2c_try_raw_write
c_func
(paren
r_struct
id|sn9c102_device
op_star
id|cam
comma
r_struct
id|sn9c102_sensor
op_star
id|sensor
comma
id|u8
id|n
comma
id|u8
id|data0
comma
id|u8
id|data1
comma
id|u8
id|data2
comma
id|u8
id|data3
comma
id|u8
id|data4
comma
id|u8
id|data5
)paren
suffix:semicolon
multiline_comment|/* To be used after the sensor struct has been attached to the camera struct */
r_extern
r_int
id|sn9c102_i2c_write
c_func
(paren
r_struct
id|sn9c102_device
op_star
comma
id|u8
id|address
comma
id|u8
id|value
)paren
suffix:semicolon
r_extern
r_int
id|sn9c102_i2c_read
c_func
(paren
r_struct
id|sn9c102_device
op_star
comma
id|u8
id|address
)paren
suffix:semicolon
multiline_comment|/* I/O on registers in the bridge. Could be used by the sensor methods too */
r_extern
r_int
id|sn9c102_write_reg
c_func
(paren
r_struct
id|sn9c102_device
op_star
comma
id|u8
id|value
comma
id|u16
id|index
)paren
suffix:semicolon
r_extern
r_int
id|sn9c102_pread_reg
c_func
(paren
r_struct
id|sn9c102_device
op_star
comma
id|u16
id|index
)paren
suffix:semicolon
multiline_comment|/*&n;   NOTE: there are no debugging functions here. To uniform the output you must&n;   use the dev_info()/dev_warn()/dev_err() macros defined in device.h, already&n;   included here, the argument being the struct device &squot;dev&squot; of the sensor&n;   structure. Do NOT use these macros before the sensor is attached or the&n;   kernel will crash! However you should not need to notify the user about&n;   common errors or other messages, since this is done by the master module.&n;*/
multiline_comment|/*****************************************************************************/
DECL|enum|sn9c102_i2c_frequency
r_enum
id|sn9c102_i2c_frequency
(brace
multiline_comment|/* sensors may support both the frequencies */
DECL|enumerator|SN9C102_I2C_100KHZ
id|SN9C102_I2C_100KHZ
op_assign
l_int|0x01
comma
DECL|enumerator|SN9C102_I2C_400KHZ
id|SN9C102_I2C_400KHZ
op_assign
l_int|0x02
comma
)brace
suffix:semicolon
DECL|enum|sn9c102_i2c_interface
r_enum
id|sn9c102_i2c_interface
(brace
DECL|enumerator|SN9C102_I2C_2WIRES
id|SN9C102_I2C_2WIRES
comma
DECL|enumerator|SN9C102_I2C_3WIRES
id|SN9C102_I2C_3WIRES
comma
)brace
suffix:semicolon
DECL|macro|SN9C102_I2C_SLAVEID_FICTITIOUS
mdefine_line|#define SN9C102_I2C_SLAVEID_FICTITIOUS 0xff
DECL|macro|SN9C102_I2C_SLAVEID_UNAVAILABLE
mdefine_line|#define SN9C102_I2C_SLAVEID_UNAVAILABLE 0x00
DECL|struct|sn9c102_sensor
r_struct
id|sn9c102_sensor
(brace
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
comma
multiline_comment|/* sensor name */
DECL|member|maintainer
id|maintainer
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* name of the mantainer &lt;email&gt; */
multiline_comment|/*&n;&t;   These sensor capabilities must be provided if the SN9C10X controller&n;&t;   needs to communicate through the sensor serial interface by using&n;&t;   at least one of the i2c functions available.&n;&t;*/
DECL|member|frequency
r_enum
id|sn9c102_i2c_frequency
id|frequency
suffix:semicolon
DECL|member|interface
r_enum
id|sn9c102_i2c_interface
id|interface
suffix:semicolon
multiline_comment|/*&n;&t;   These identifiers must be provided if the image sensor implements&n;&t;   the standard I2C protocol.&n;&t;*/
DECL|member|slave_read_id
DECL|member|slave_write_id
id|u8
id|slave_read_id
comma
id|slave_write_id
suffix:semicolon
multiline_comment|/* reg. 0x09 */
multiline_comment|/*&n;&t;   NOTE: Where not noted,most of the functions below are not mandatory.&n;&t;         Set to null if you do not implement them. If implemented,&n;&t;         they must return 0 on success, the proper error otherwise.&n;&t;*/
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_struct
id|sn9c102_device
op_star
id|cam
)paren
suffix:semicolon
multiline_comment|/*&n;&t;   This function is called after the sensor has been attached. &n;&t;   It should be used to initialize the sensor only, but may also&n;&t;   configure part of the SN9C10X chip if necessary. You don&squot;t need to&n;&t;   setup picture settings like brightness, contrast, etc.. here, if&n;&t;   the corrisponding controls are implemented (see below), since &n;&t;   they are adjusted in the core driver by calling the set_ctrl()&n;&t;   method after init(), where the arguments are the default values&n;&t;   specified in the v4l2_queryctrl list of supported controls;&n;&t;   Same suggestions apply for other settings, _if_ the corresponding&n;&t;   methods are present; if not, the initialization must configure the&n;&t;   sensor according to the default configuration structures below.&n;&t;*/
DECL|member|qctrl
r_struct
id|v4l2_queryctrl
id|qctrl
(braket
id|V4L2_CID_LASTP1
op_minus
id|V4L2_CID_BASE
)braket
suffix:semicolon
multiline_comment|/*&n;&t;   Optional list of default controls, defined as indicated in the &n;&t;   V4L2 API. Menu type controls are not handled by this interface.&n;&t;*/
DECL|member|get_ctrl
r_int
(paren
op_star
id|get_ctrl
)paren
(paren
r_struct
id|sn9c102_device
op_star
id|cam
comma
r_struct
id|v4l2_control
op_star
id|ctrl
)paren
suffix:semicolon
DECL|member|set_ctrl
r_int
(paren
op_star
id|set_ctrl
)paren
(paren
r_struct
id|sn9c102_device
op_star
id|cam
comma
r_const
r_struct
id|v4l2_control
op_star
id|ctrl
)paren
suffix:semicolon
multiline_comment|/*&n;&t;   You must implement at least the set_ctrl method if you have defined&n;&t;   the list above. The returned value must follow the V4L2&n;&t;   specifications for the VIDIOC_G|C_CTRL ioctls. V4L2_CID_H|VCENTER&n;&t;   are not supported by this driver, so do not implement them. Also,&n;&t;   you don&squot;t have to check whether the passed values are out of bounds,&n;&t;   given that this is done by the core module.&n;&t;*/
DECL|member|cropcap
r_struct
id|v4l2_cropcap
id|cropcap
suffix:semicolon
multiline_comment|/*&n;&t;   Think the image sensor as a grid of R,G,B monochromatic pixels&n;&t;   disposed according to a particular Bayer pattern, which describes&n;&t;   the complete array of pixels, from (0,0) to (xmax, ymax). We will&n;&t;   use this coordinate system from now on. It is assumed the sensor&n;&t;   chip can be programmed to capture/transmit a subsection of that&n;&t;   array of pixels: we will call this subsection &quot;active window&quot;.&n;&t;   It is not always true that the largest achievable active window can&n;&t;   cover the whole array of pixels. The V4L2 API defines another&n;&t;   area called &quot;source rectangle&quot;, which, in turn, is a subrectangle of&n;&t;   the active window. The SN9C10X chip is always programmed to read the&n;&t;   source rectangle.&n;&t;   The bounds of both the active window and the source rectangle are&n;&t;   specified in the cropcap substructures &squot;bounds&squot; and &squot;defrect&squot;.&n;&t;   By default, the source rectangle should cover the largest possible&n;&t;   area. Again, it is not always true that the largest source rectangle&n;&t;   can cover the entire active window, although it is a rare case for &n;&t;   the hardware we have. The bounds of the source rectangle _must_ be&n;&t;   multiple of 16 and must use the same coordinate system as indicated&n;&t;   before; their centers shall align initially.&n;&t;   If necessary, the sensor chip must be initialized during init() to&n;&t;   set the bounds of the active sensor window; however, by default, it&n;&t;   usually covers the largest achievable area (maxwidth x maxheight)&n;&t;   of pixels, so no particular initialization is needed, if you have&n;&t;   defined the correct default bounds in the structures.&n;&t;   See the V4L2 API for further details.&n;&t;   NOTE: once you have defined the bounds of the active window&n;&t;         (struct cropcap.bounds) you must not change them.anymore.&n;&t;   Only &squot;bounds&squot; and &squot;defrect&squot; fields are mandatory, other fields&n;&t;   will be ignored.&n;&t;*/
DECL|member|set_crop
r_int
(paren
op_star
id|set_crop
)paren
(paren
r_struct
id|sn9c102_device
op_star
id|cam
comma
r_const
r_struct
id|v4l2_rect
op_star
id|rect
)paren
suffix:semicolon
multiline_comment|/*&n;&t;   To be called on VIDIOC_C_SETCROP. The core module always calls a&n;&t;   default routine which configures the appropriate SN9C10X regs (also&n;&t;   scaling), but you may need to override/adjust specific stuff.&n;&t;   &squot;rect&squot; contains width and height values that are multiple of 16: in&n;&t;   case you override the default function, you always have to program&n;&t;   the chip to match those values; on error return the corresponding&n;&t;   error code without rolling back.&n;&t;   NOTE: in case, you must program the SN9C10X chip to get rid of &n;&t;         blank pixels or blank lines at the _start_ of each line or&n;&t;         frame after each HSYNC or VSYNC, so that the image starts with&n;&t;         real RGB data (see regs 0x12, 0x13) (having set H_SIZE and,&n;&t;         V_SIZE you don&squot;t have to care about blank pixels or blank&n;&t;         lines at the end of each line or frame).&n;&t;*/
DECL|member|pix_format
r_struct
id|v4l2_pix_format
id|pix_format
suffix:semicolon
multiline_comment|/*&n;&t;   What you have to define here are: 1) initial &squot;width&squot; and &squot;height&squot; of&n;&t;   the target rectangle 2) the initial &squot;pixelformat&squot;, which can be&n;&t;   either V4L2_PIX_FMT_SN9C10X (for compressed video) or&n;&t;   V4L2_PIX_FMT_SBGGR8 3) &squot;priv&squot;, which we&squot;ll be used to indicate the&n;&t;   number of bits per pixel for uncompressed video, 8 or 9 (despite the&n;&t;   current value of &squot;pixelformat&squot;).&n;&t;   NOTE 1: both &squot;width&squot; and &squot;height&squot; _must_ be either 1/1 or 1/2 or 1/4&n;&t;           of cropcap.defrect.width and cropcap.defrect.height. I&n;&t;           suggest 1/1.&n;&t;   NOTE 2: The initial compression quality is defined by the first bit&n;&t;           of reg 0x17 during the initialization of the image sensor.&n;&t;   NOTE 3: as said above, you have to program the SN9C10X chip to get&n;&t;           rid of any blank pixels, so that the output of the sensor&n;&t;           matches the RGB bayer sequence (i.e. BGBGBG...GRGRGR).&n;&t;*/
DECL|member|dev
r_const
r_struct
id|device
op_star
id|dev
suffix:semicolon
multiline_comment|/*&n;&t;   This is the argument for dev_err(), dev_info() and dev_warn(). It&n;&t;   is used for debugging purposes. You must not access the struct&n;&t;   before the sensor is attached.&n;&t;*/
DECL|member|usbdev
r_const
r_struct
id|usb_device
op_star
id|usbdev
suffix:semicolon
multiline_comment|/*&n;&t;   Points to the usb_device struct after the sensor is attached.&n;&t;   Do not touch unless you know what you are doing.&n;&t;*/
multiline_comment|/*&n;&t;   Do NOT write to the data below, it&squot;s READ ONLY. It is used by the&n;&t;   core module to store successfully updated values of the above&n;&t;   settings, for rollbacks..etc..in case of errors during atomic I/O&n;&t;*/
DECL|member|_qctrl
r_struct
id|v4l2_queryctrl
id|_qctrl
(braket
id|V4L2_CID_LASTP1
op_minus
id|V4L2_CID_BASE
)braket
suffix:semicolon
DECL|member|_rect
r_struct
id|v4l2_rect
id|_rect
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/* Private ioctl&squot;s for control settings supported by some image sensors */
DECL|macro|SN9C102_V4L2_CID_DAC_MAGNITUDE
mdefine_line|#define SN9C102_V4L2_CID_DAC_MAGNITUDE V4L2_CID_PRIVATE_BASE
DECL|macro|SN9C102_V4L2_CID_DAC_SIGN
mdefine_line|#define SN9C102_V4L2_CID_DAC_SIGN V4L2_CID_PRIVATE_BASE + 1
DECL|macro|SN9C102_V4L2_CID_GREEN_BALANCE
mdefine_line|#define SN9C102_V4L2_CID_GREEN_BALANCE V4L2_CID_PRIVATE_BASE + 2
macro_line|#endif /* _SN9C102_SENSOR_H_ */
eof
