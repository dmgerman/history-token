macro_line|#ifndef cpia_h
DECL|macro|cpia_h
mdefine_line|#define cpia_h
multiline_comment|/*&n; * CPiA Parallel Port Video4Linux driver&n; *&n; * Supports CPiA based parallel port Video Camera&squot;s.&n; *&n; * (C) Copyright 1999 Bas Huisman,&n; *                    Peter Pregler,&n; *                    Scott J. Bertin,&n; *                    VLSI Vision Ltd.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
DECL|macro|CPIA_MAJ_VER
mdefine_line|#define CPIA_MAJ_VER&t;0
DECL|macro|CPIA_MIN_VER
mdefine_line|#define CPIA_MIN_VER    7
DECL|macro|CPIA_PATCH_VER
mdefine_line|#define CPIA_PATCH_VER&t;4
DECL|macro|CPIA_PP_MAJ_VER
mdefine_line|#define CPIA_PP_MAJ_VER       0
DECL|macro|CPIA_PP_MIN_VER
mdefine_line|#define CPIA_PP_MIN_VER       7
DECL|macro|CPIA_PP_PATCH_VER
mdefine_line|#define CPIA_PP_PATCH_VER     4
DECL|macro|CPIA_MAX_FRAME_SIZE_UNALIGNED
mdefine_line|#define CPIA_MAX_FRAME_SIZE_UNALIGNED&t;(352 * 288 * 4)   /* CIF at RGB32 */
DECL|macro|CPIA_MAX_FRAME_SIZE
mdefine_line|#define CPIA_MAX_FRAME_SIZE&t;((CPIA_MAX_FRAME_SIZE_UNALIGNED + PAGE_SIZE - 1) &amp; ~(PAGE_SIZE - 1)) /* align above to PAGE_SIZE */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
DECL|struct|cpia_camera_ops
r_struct
id|cpia_camera_ops
(brace
multiline_comment|/* open sets privdata to point to structure for this camera.&n;         * Returns negative value on error, otherwise 0.&n;&t; */
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
r_void
op_star
id|privdata
)paren
suffix:semicolon
multiline_comment|/* Registers callback function cb to be called with cbdata&n;&t; * when an image is ready.  If cb is NULL, only single image grabs&n;&t; * should be used.  cb should immediately call streamRead to read&n;&t; * the data or data may be lost. Returns negative value on error,&n;&t; * otherwise 0.&n;&t; */
DECL|member|registerCallback
r_int
(paren
op_star
id|registerCallback
)paren
(paren
r_void
op_star
id|privdata
comma
r_void
(paren
op_star
id|cb
)paren
(paren
r_void
op_star
id|cbdata
)paren
comma
r_void
op_star
id|cbdata
)paren
suffix:semicolon
multiline_comment|/* transferCmd sends commands to the camera.  command MUST point to&n;&t; * an  8 byte buffer in kernel space. data can be NULL if no extra&n;&t; * data is needed.  The size of the data is given by the last 2&n;&t; * bytes of comand.  data must also point to memory in kernel space.&n;&t; * Returns negative value on error, otherwise 0.&n;&t; */
DECL|member|transferCmd
r_int
(paren
op_star
id|transferCmd
)paren
(paren
r_void
op_star
id|privdata
comma
id|u8
op_star
id|command
comma
id|u8
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/* streamStart initiates stream capture mode.&n;&t; * Returns negative value on error, otherwise 0.&n;&t; */
DECL|member|streamStart
r_int
(paren
op_star
id|streamStart
)paren
(paren
r_void
op_star
id|privdata
)paren
suffix:semicolon
multiline_comment|/* streamStop terminates stream capture mode.&n;&t; * Returns negative value on error, otherwise 0.&n;&t; */
DECL|member|streamStop
r_int
(paren
op_star
id|streamStop
)paren
(paren
r_void
op_star
id|privdata
)paren
suffix:semicolon
multiline_comment|/* streamRead reads a frame from the camera.  buffer points to a&n;         * buffer large enough to hold a complete frame in kernel space.&n;         * noblock indicates if this should be a non blocking read.&n;&t; * Returns the number of bytes read, or negative value on error.&n;         */
DECL|member|streamRead
r_int
(paren
op_star
id|streamRead
)paren
(paren
r_void
op_star
id|privdata
comma
id|u8
op_star
id|buffer
comma
r_int
id|noblock
)paren
suffix:semicolon
multiline_comment|/* close disables the device until open() is called again.&n;&t; * Returns negative value on error, otherwise 0.&n;&t; */
DECL|member|close
r_int
(paren
op_star
id|close
)paren
(paren
r_void
op_star
id|privdata
)paren
suffix:semicolon
multiline_comment|/* If wait_for_stream_ready is non-zero, wait until the streamState&n;&t; * is STREAM_READY before calling streamRead.&n;&t; */
DECL|member|wait_for_stream_ready
r_int
id|wait_for_stream_ready
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cpia_frame
r_struct
id|cpia_frame
(brace
DECL|member|data
id|u8
op_star
id|data
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|width
r_int
id|width
suffix:semicolon
DECL|member|height
r_int
id|height
suffix:semicolon
DECL|member|state
r_volatile
r_int
id|state
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cam_params
r_struct
id|cam_params
(brace
r_struct
(brace
DECL|member|firmwareVersion
id|u8
id|firmwareVersion
suffix:semicolon
DECL|member|firmwareRevision
id|u8
id|firmwareRevision
suffix:semicolon
DECL|member|vcVersion
id|u8
id|vcVersion
suffix:semicolon
DECL|member|vcRevision
id|u8
id|vcRevision
suffix:semicolon
DECL|member|version
)brace
id|version
suffix:semicolon
r_struct
(brace
DECL|member|vendor
id|u16
id|vendor
suffix:semicolon
DECL|member|product
id|u16
id|product
suffix:semicolon
DECL|member|deviceRevision
id|u16
id|deviceRevision
suffix:semicolon
DECL|member|pnpID
)brace
id|pnpID
suffix:semicolon
r_struct
(brace
DECL|member|vpVersion
id|u8
id|vpVersion
suffix:semicolon
DECL|member|vpRevision
id|u8
id|vpRevision
suffix:semicolon
DECL|member|cameraHeadID
id|u16
id|cameraHeadID
suffix:semicolon
DECL|member|vpVersion
)brace
id|vpVersion
suffix:semicolon
r_struct
(brace
DECL|member|systemState
id|u8
id|systemState
suffix:semicolon
DECL|member|grabState
id|u8
id|grabState
suffix:semicolon
DECL|member|streamState
id|u8
id|streamState
suffix:semicolon
DECL|member|fatalError
id|u8
id|fatalError
suffix:semicolon
DECL|member|cmdError
id|u8
id|cmdError
suffix:semicolon
DECL|member|debugFlags
id|u8
id|debugFlags
suffix:semicolon
DECL|member|vpStatus
id|u8
id|vpStatus
suffix:semicolon
DECL|member|errorCode
id|u8
id|errorCode
suffix:semicolon
DECL|member|status
)brace
id|status
suffix:semicolon
r_struct
(brace
DECL|member|brightness
id|u8
id|brightness
suffix:semicolon
DECL|member|contrast
id|u8
id|contrast
suffix:semicolon
DECL|member|saturation
id|u8
id|saturation
suffix:semicolon
DECL|member|colourParams
)brace
id|colourParams
suffix:semicolon
r_struct
(brace
DECL|member|gainMode
id|u8
id|gainMode
suffix:semicolon
DECL|member|expMode
id|u8
id|expMode
suffix:semicolon
DECL|member|compMode
id|u8
id|compMode
suffix:semicolon
DECL|member|centreWeight
id|u8
id|centreWeight
suffix:semicolon
DECL|member|gain
id|u8
id|gain
suffix:semicolon
DECL|member|fineExp
id|u8
id|fineExp
suffix:semicolon
DECL|member|coarseExpLo
id|u8
id|coarseExpLo
suffix:semicolon
DECL|member|coarseExpHi
id|u8
id|coarseExpHi
suffix:semicolon
DECL|member|redComp
id|u8
id|redComp
suffix:semicolon
DECL|member|green1Comp
id|u8
id|green1Comp
suffix:semicolon
DECL|member|green2Comp
id|u8
id|green2Comp
suffix:semicolon
DECL|member|blueComp
id|u8
id|blueComp
suffix:semicolon
DECL|member|exposure
)brace
id|exposure
suffix:semicolon
r_struct
(brace
DECL|member|balanceModeIsAuto
id|u8
id|balanceModeIsAuto
suffix:semicolon
DECL|member|redGain
id|u8
id|redGain
suffix:semicolon
DECL|member|greenGain
id|u8
id|greenGain
suffix:semicolon
DECL|member|blueGain
id|u8
id|blueGain
suffix:semicolon
DECL|member|colourBalance
)brace
id|colourBalance
suffix:semicolon
r_struct
(brace
DECL|member|divisor
id|u8
id|divisor
suffix:semicolon
DECL|member|baserate
id|u8
id|baserate
suffix:semicolon
DECL|member|sensorFps
)brace
id|sensorFps
suffix:semicolon
r_struct
(brace
DECL|member|gain1
id|u8
id|gain1
suffix:semicolon
DECL|member|gain2
id|u8
id|gain2
suffix:semicolon
DECL|member|gain4
id|u8
id|gain4
suffix:semicolon
DECL|member|gain8
id|u8
id|gain8
suffix:semicolon
DECL|member|apcor
)brace
id|apcor
suffix:semicolon
r_struct
(brace
DECL|member|flickerMode
id|u8
id|flickerMode
suffix:semicolon
DECL|member|coarseJump
id|u8
id|coarseJump
suffix:semicolon
DECL|member|allowableOverExposure
id|u8
id|allowableOverExposure
suffix:semicolon
DECL|member|flickerControl
)brace
id|flickerControl
suffix:semicolon
r_struct
(brace
DECL|member|gain1
id|u8
id|gain1
suffix:semicolon
DECL|member|gain2
id|u8
id|gain2
suffix:semicolon
DECL|member|gain4
id|u8
id|gain4
suffix:semicolon
DECL|member|gain8
id|u8
id|gain8
suffix:semicolon
DECL|member|vlOffset
)brace
id|vlOffset
suffix:semicolon
r_struct
(brace
DECL|member|mode
id|u8
id|mode
suffix:semicolon
DECL|member|decimation
id|u8
id|decimation
suffix:semicolon
DECL|member|compression
)brace
id|compression
suffix:semicolon
r_struct
(brace
DECL|member|frTargeting
id|u8
id|frTargeting
suffix:semicolon
DECL|member|targetFR
id|u8
id|targetFR
suffix:semicolon
DECL|member|targetQ
id|u8
id|targetQ
suffix:semicolon
DECL|member|compressionTarget
)brace
id|compressionTarget
suffix:semicolon
r_struct
(brace
DECL|member|yThreshold
id|u8
id|yThreshold
suffix:semicolon
DECL|member|uvThreshold
id|u8
id|uvThreshold
suffix:semicolon
DECL|member|yuvThreshold
)brace
id|yuvThreshold
suffix:semicolon
r_struct
(brace
DECL|member|hysteresis
id|u8
id|hysteresis
suffix:semicolon
DECL|member|threshMax
id|u8
id|threshMax
suffix:semicolon
DECL|member|smallStep
id|u8
id|smallStep
suffix:semicolon
DECL|member|largeStep
id|u8
id|largeStep
suffix:semicolon
DECL|member|decimationHysteresis
id|u8
id|decimationHysteresis
suffix:semicolon
DECL|member|frDiffStepThresh
id|u8
id|frDiffStepThresh
suffix:semicolon
DECL|member|qDiffStepThresh
id|u8
id|qDiffStepThresh
suffix:semicolon
DECL|member|decimationThreshMod
id|u8
id|decimationThreshMod
suffix:semicolon
DECL|member|compressionParams
)brace
id|compressionParams
suffix:semicolon
r_struct
(brace
DECL|member|videoSize
id|u8
id|videoSize
suffix:semicolon
multiline_comment|/* CIF/QCIF */
DECL|member|subSample
id|u8
id|subSample
suffix:semicolon
DECL|member|yuvOrder
id|u8
id|yuvOrder
suffix:semicolon
DECL|member|format
)brace
id|format
suffix:semicolon
r_struct
(brace
DECL|member|colStart
id|u8
id|colStart
suffix:semicolon
multiline_comment|/* skip first 8*colStart pixels */
DECL|member|colEnd
id|u8
id|colEnd
suffix:semicolon
multiline_comment|/* finish at 8*colEnd pixels */
DECL|member|rowStart
id|u8
id|rowStart
suffix:semicolon
multiline_comment|/* skip first 4*rowStart lines */
DECL|member|rowEnd
id|u8
id|rowEnd
suffix:semicolon
multiline_comment|/* finish at 4*rowEnd lines */
DECL|member|roi
)brace
id|roi
suffix:semicolon
DECL|member|ecpTiming
id|u8
id|ecpTiming
suffix:semicolon
DECL|member|streamStartLine
id|u8
id|streamStartLine
suffix:semicolon
)brace
suffix:semicolon
DECL|enum|v4l_camstates
r_enum
id|v4l_camstates
(brace
DECL|enumerator|CPIA_V4L_IDLE
id|CPIA_V4L_IDLE
op_assign
l_int|0
comma
DECL|enumerator|CPIA_V4L_ERROR
id|CPIA_V4L_ERROR
comma
DECL|enumerator|CPIA_V4L_COMMAND
id|CPIA_V4L_COMMAND
comma
DECL|enumerator|CPIA_V4L_GRABBING
id|CPIA_V4L_GRABBING
comma
DECL|enumerator|CPIA_V4L_STREAMING
id|CPIA_V4L_STREAMING
comma
DECL|enumerator|CPIA_V4L_STREAMING_PAUSED
id|CPIA_V4L_STREAMING_PAUSED
comma
)brace
suffix:semicolon
DECL|macro|FRAME_NUM
mdefine_line|#define FRAME_NUM&t;2&t;/* double buffering for now */
DECL|struct|cam_data
r_struct
id|cam_data
(brace
DECL|member|previous
r_struct
id|cam_data
op_star
op_star
id|previous
suffix:semicolon
DECL|member|next
r_struct
id|cam_data
op_star
id|next
suffix:semicolon
DECL|member|busy_lock
r_struct
id|semaphore
id|busy_lock
suffix:semicolon
multiline_comment|/* guard against SMP multithreading */
DECL|member|ops
r_struct
id|cpia_camera_ops
op_star
id|ops
suffix:semicolon
multiline_comment|/* lowlevel driver operations */
DECL|member|lowlevel_data
r_void
op_star
id|lowlevel_data
suffix:semicolon
multiline_comment|/* private data for lowlevel driver */
DECL|member|raw_image
id|u8
op_star
id|raw_image
suffix:semicolon
multiline_comment|/* buffer for raw image data */
DECL|member|decompressed_frame
r_struct
id|cpia_frame
id|decompressed_frame
suffix:semicolon
multiline_comment|/* buffer to hold decompressed frame */
DECL|member|image_size
r_int
id|image_size
suffix:semicolon
multiline_comment|/* sizeof last decompressed image */
DECL|member|open_count
r_int
id|open_count
suffix:semicolon
multiline_comment|/* # of process that have camera open */
multiline_comment|/* camera status */
DECL|member|fps
r_int
id|fps
suffix:semicolon
multiline_comment|/* actual fps reported by the camera */
DECL|member|transfer_rate
r_int
id|transfer_rate
suffix:semicolon
multiline_comment|/* transfer rate from camera in kB/s */
DECL|member|mainsFreq
id|u8
id|mainsFreq
suffix:semicolon
multiline_comment|/* for flicker control */
multiline_comment|/* proc interface */
DECL|member|param_lock
r_struct
id|semaphore
id|param_lock
suffix:semicolon
multiline_comment|/* params lock for this camera */
DECL|member|params
r_struct
id|cam_params
id|params
suffix:semicolon
multiline_comment|/* camera settings */
DECL|member|proc_entry
r_struct
id|proc_dir_entry
op_star
id|proc_entry
suffix:semicolon
multiline_comment|/* /proc/cpia/videoX */
multiline_comment|/* v4l */
DECL|member|video_size
r_int
id|video_size
suffix:semicolon
multiline_comment|/* VIDEO_SIZE_ */
DECL|member|camstate
r_volatile
r_enum
id|v4l_camstates
id|camstate
suffix:semicolon
multiline_comment|/* v4l layer status */
DECL|member|vdev
r_struct
id|video_device
id|vdev
suffix:semicolon
multiline_comment|/* v4l videodev */
DECL|member|vp
r_struct
id|video_picture
id|vp
suffix:semicolon
multiline_comment|/* v4l camera settings */
DECL|member|vw
r_struct
id|video_window
id|vw
suffix:semicolon
multiline_comment|/* v4l capture area */
multiline_comment|/* mmap interface */
DECL|member|curframe
r_int
id|curframe
suffix:semicolon
multiline_comment|/* the current frame to grab into */
DECL|member|frame_buf
id|u8
op_star
id|frame_buf
suffix:semicolon
multiline_comment|/* frame buffer data */
DECL|member|frame
r_struct
id|cpia_frame
id|frame
(braket
id|FRAME_NUM
)braket
suffix:semicolon
multiline_comment|/* FRAME_NUM-buffering, so we need a array */
DECL|member|first_frame
r_int
id|first_frame
suffix:semicolon
DECL|member|mmap_kludge
r_int
id|mmap_kludge
suffix:semicolon
multiline_comment|/* &squot;wrong&squot; byte order for mmap */
DECL|member|cmd_queue
r_volatile
id|u32
id|cmd_queue
suffix:semicolon
multiline_comment|/* queued commands */
)brace
suffix:semicolon
multiline_comment|/* cpia_register_camera is called by low level driver for each camera.&n; * A unique camera number is returned, or a negative value on error */
r_struct
id|cam_data
op_star
id|cpia_register_camera
c_func
(paren
r_struct
id|cpia_camera_ops
op_star
id|ops
comma
r_void
op_star
id|lowlevel
)paren
suffix:semicolon
multiline_comment|/* cpia_unregister_camera is called by low level driver when a camera&n; * is removed.  This must not fail. */
r_void
id|cpia_unregister_camera
c_func
(paren
r_struct
id|cam_data
op_star
id|cam
)paren
suffix:semicolon
multiline_comment|/* raw CIF + 64 byte header + (2 bytes line_length + EOL) per line + 4*EOI +&n; * one byte 16bit DMA alignment&n; */
DECL|macro|CPIA_MAX_IMAGE_SIZE
mdefine_line|#define CPIA_MAX_IMAGE_SIZE ((352*288*2)+64+(288*3)+5)
multiline_comment|/* constant value&squot;s */
DECL|macro|MAGIC_0
mdefine_line|#define MAGIC_0&t;&t;0x19
DECL|macro|MAGIC_1
mdefine_line|#define MAGIC_1&t;&t;0x68
DECL|macro|DATA_IN
mdefine_line|#define DATA_IN&t;&t;0xC0
DECL|macro|DATA_OUT
mdefine_line|#define DATA_OUT&t;0x40
DECL|macro|VIDEOSIZE_QCIF
mdefine_line|#define VIDEOSIZE_QCIF&t;0&t;/* 176x144 */
DECL|macro|VIDEOSIZE_CIF
mdefine_line|#define VIDEOSIZE_CIF&t;1&t;/* 352x288 */
DECL|macro|VIDEOSIZE_SIF
mdefine_line|#define VIDEOSIZE_SIF&t;2&t;/* 320x240 */
DECL|macro|VIDEOSIZE_QSIF
mdefine_line|#define VIDEOSIZE_QSIF&t;3&t;/* 160x120 */
DECL|macro|VIDEOSIZE_48_48
mdefine_line|#define VIDEOSIZE_48_48&t;&t;4 /* where no one has gone before, iconsize! */
DECL|macro|VIDEOSIZE_64_48
mdefine_line|#define VIDEOSIZE_64_48&t;&t;5
DECL|macro|VIDEOSIZE_128_96
mdefine_line|#define VIDEOSIZE_128_96&t;6
DECL|macro|VIDEOSIZE_160_120
mdefine_line|#define VIDEOSIZE_160_120&t;VIDEOSIZE_QSIF
DECL|macro|VIDEOSIZE_176_144
mdefine_line|#define VIDEOSIZE_176_144&t;VIDEOSIZE_QCIF
DECL|macro|VIDEOSIZE_192_144
mdefine_line|#define VIDEOSIZE_192_144&t;7
DECL|macro|VIDEOSIZE_224_168
mdefine_line|#define VIDEOSIZE_224_168&t;8
DECL|macro|VIDEOSIZE_256_192
mdefine_line|#define VIDEOSIZE_256_192&t;9
DECL|macro|VIDEOSIZE_288_216
mdefine_line|#define VIDEOSIZE_288_216&t;10
DECL|macro|VIDEOSIZE_320_240
mdefine_line|#define VIDEOSIZE_320_240&t;VIDEOSIZE_SIF
DECL|macro|VIDEOSIZE_352_288
mdefine_line|#define VIDEOSIZE_352_288&t;VIDEOSIZE_CIF
DECL|macro|VIDEOSIZE_88_72
mdefine_line|#define VIDEOSIZE_88_72&t;&t;11 /* quarter CIF */
DECL|macro|SUBSAMPLE_420
mdefine_line|#define SUBSAMPLE_420&t;0
DECL|macro|SUBSAMPLE_422
mdefine_line|#define SUBSAMPLE_422&t;1
DECL|macro|YUVORDER_YUYV
mdefine_line|#define YUVORDER_YUYV&t;0
DECL|macro|YUVORDER_UYVY
mdefine_line|#define YUVORDER_UYVY&t;1
DECL|macro|NOT_COMPRESSED
mdefine_line|#define NOT_COMPRESSED&t;0
DECL|macro|COMPRESSED
mdefine_line|#define COMPRESSED&t;1
DECL|macro|NO_DECIMATION
mdefine_line|#define NO_DECIMATION&t;0
DECL|macro|DECIMATION_ENAB
mdefine_line|#define DECIMATION_ENAB&t;1
DECL|macro|EOI
mdefine_line|#define EOI&t;&t;0xff&t;/* End Of Image */
DECL|macro|EOL
mdefine_line|#define EOL&t;&t;0xfd&t;/* End Of Line */
DECL|macro|FRAME_HEADER_SIZE
mdefine_line|#define FRAME_HEADER_SIZE&t;64
multiline_comment|/* Image grab modes */
DECL|macro|CPIA_GRAB_SINGLE
mdefine_line|#define CPIA_GRAB_SINGLE&t;0
DECL|macro|CPIA_GRAB_CONTINUOUS
mdefine_line|#define CPIA_GRAB_CONTINUOUS&t;1
multiline_comment|/* Compression parameters */
DECL|macro|CPIA_COMPRESSION_NONE
mdefine_line|#define CPIA_COMPRESSION_NONE&t;0
DECL|macro|CPIA_COMPRESSION_AUTO
mdefine_line|#define CPIA_COMPRESSION_AUTO&t;1
DECL|macro|CPIA_COMPRESSION_MANUAL
mdefine_line|#define CPIA_COMPRESSION_MANUAL&t;2
DECL|macro|CPIA_COMPRESSION_TARGET_QUALITY
mdefine_line|#define CPIA_COMPRESSION_TARGET_QUALITY         0
DECL|macro|CPIA_COMPRESSION_TARGET_FRAMERATE
mdefine_line|#define CPIA_COMPRESSION_TARGET_FRAMERATE       1
multiline_comment|/* Return offsets for GetCameraState */
DECL|macro|SYSTEMSTATE
mdefine_line|#define SYSTEMSTATE&t;0
DECL|macro|GRABSTATE
mdefine_line|#define GRABSTATE&t;1
DECL|macro|STREAMSTATE
mdefine_line|#define STREAMSTATE&t;2
DECL|macro|FATALERROR
mdefine_line|#define FATALERROR&t;3
DECL|macro|CMDERROR
mdefine_line|#define CMDERROR&t;4
DECL|macro|DEBUGFLAGS
mdefine_line|#define DEBUGFLAGS&t;5
DECL|macro|VPSTATUS
mdefine_line|#define VPSTATUS&t;6
DECL|macro|ERRORCODE
mdefine_line|#define ERRORCODE&t;7
multiline_comment|/* SystemState */
DECL|macro|UNINITIALISED_STATE
mdefine_line|#define UNINITIALISED_STATE&t;0
DECL|macro|PASS_THROUGH_STATE
mdefine_line|#define PASS_THROUGH_STATE&t;1
DECL|macro|LO_POWER_STATE
mdefine_line|#define LO_POWER_STATE&t;&t;2
DECL|macro|HI_POWER_STATE
mdefine_line|#define HI_POWER_STATE&t;&t;3
DECL|macro|WARM_BOOT_STATE
mdefine_line|#define WARM_BOOT_STATE&t;&t;4
multiline_comment|/* GrabState */
DECL|macro|GRAB_IDLE
mdefine_line|#define GRAB_IDLE&t;&t;0
DECL|macro|GRAB_ACTIVE
mdefine_line|#define GRAB_ACTIVE&t;&t;1
DECL|macro|GRAB_DONE
mdefine_line|#define GRAB_DONE&t;&t;2
multiline_comment|/* StreamState */
DECL|macro|STREAM_NOT_READY
mdefine_line|#define STREAM_NOT_READY&t;0
DECL|macro|STREAM_READY
mdefine_line|#define STREAM_READY&t;&t;1
DECL|macro|STREAM_OPEN
mdefine_line|#define STREAM_OPEN&t;&t;2
DECL|macro|STREAM_PAUSED
mdefine_line|#define STREAM_PAUSED&t;&t;3
DECL|macro|STREAM_FINISHED
mdefine_line|#define STREAM_FINISHED&t;&t;4
multiline_comment|/* Fatal Error, CmdError, and DebugFlags */
DECL|macro|CPIA_FLAG
mdefine_line|#define CPIA_FLAG&t;  1
DECL|macro|SYSTEM_FLAG
mdefine_line|#define SYSTEM_FLAG&t;  2
DECL|macro|INT_CTRL_FLAG
mdefine_line|#define INT_CTRL_FLAG&t;  4
DECL|macro|PROCESS_FLAG
mdefine_line|#define PROCESS_FLAG&t;  8
DECL|macro|COM_FLAG
mdefine_line|#define COM_FLAG&t; 16
DECL|macro|VP_CTRL_FLAG
mdefine_line|#define VP_CTRL_FLAG&t; 32
DECL|macro|CAPTURE_FLAG
mdefine_line|#define CAPTURE_FLAG&t; 64
DECL|macro|DEBUG_FLAG
mdefine_line|#define DEBUG_FLAG&t;128
multiline_comment|/* VPStatus */
DECL|macro|VP_STATE_OK
mdefine_line|#define VP_STATE_OK&t;&t;&t;0x00
DECL|macro|VP_STATE_FAILED_VIDEOINIT
mdefine_line|#define VP_STATE_FAILED_VIDEOINIT&t;0x01
DECL|macro|VP_STATE_FAILED_AECACBINIT
mdefine_line|#define VP_STATE_FAILED_AECACBINIT&t;0x02
DECL|macro|VP_STATE_AEC_MAX
mdefine_line|#define VP_STATE_AEC_MAX&t;&t;0x04
DECL|macro|VP_STATE_ACB_BMAX
mdefine_line|#define VP_STATE_ACB_BMAX&t;&t;0x08
DECL|macro|VP_STATE_ACB_RMIN
mdefine_line|#define VP_STATE_ACB_RMIN&t;&t;0x10
DECL|macro|VP_STATE_ACB_GMIN
mdefine_line|#define VP_STATE_ACB_GMIN&t;&t;0x20
DECL|macro|VP_STATE_ACB_RMAX
mdefine_line|#define VP_STATE_ACB_RMAX&t;&t;0x40
DECL|macro|VP_STATE_ACB_GMAX
mdefine_line|#define VP_STATE_ACB_GMAX&t;&t;0x80
multiline_comment|/* ErrorCode */
DECL|macro|ERROR_FLICKER_BELOW_MIN_EXP
mdefine_line|#define ERROR_FLICKER_BELOW_MIN_EXP     0x01 /*flicker exposure got below minimum exposure */
DECL|macro|ALOG
mdefine_line|#define ALOG(lineno,fmt,args...) printk(fmt,lineno,##args)
DECL|macro|LOG
mdefine_line|#define LOG(fmt,args...) ALOG((__LINE__),KERN_INFO __FILE__&quot;:&quot;__FUNCTION__&quot;(%d):&quot;fmt,##args)
macro_line|#ifdef _CPIA_DEBUG_
DECL|macro|ADBG
mdefine_line|#define ADBG(lineno,fmt,args...) printk(fmt, jiffies, lineno, ##args)
DECL|macro|DBG
mdefine_line|#define DBG(fmt,args...) ADBG((__LINE__),KERN_DEBUG __FILE__&quot;(%ld):&quot;__FUNCTION__&quot;(%d):&quot;fmt,##args)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(fmn,args...) do {} while(0)
macro_line|#endif
DECL|macro|DEB_BYTE
mdefine_line|#define DEB_BYTE(p)&bslash;&n;  DBG(&quot;%1d %1d %1d %1d %1d %1d %1d %1d &bslash;n&quot;,&bslash;&n;      (p)&amp;0x80?1:0, (p)&amp;0x40?1:0, (p)&amp;0x20?1:0, (p)&amp;0x10?1:0,&bslash;&n;        (p)&amp;0x08?1:0, (p)&amp;0x04?1:0, (p)&amp;0x02?1:0, (p)&amp;0x01?1:0);
DECL|macro|ADD_TO_LIST
mdefine_line|#define ADD_TO_LIST(l, drv) &bslash;&n;  {&bslash;&n;    lock_kernel();&bslash;&n;    (drv)-&gt;next = l;&bslash;&n;    (drv)-&gt;previous = &amp;(l);&bslash;&n;    (l) = drv;&bslash;&n;    unlock_kernel();&bslash;&n;  } while(0)
DECL|macro|REMOVE_FROM_LIST
mdefine_line|#define REMOVE_FROM_LIST(drv) &bslash;&n;  {&bslash;&n;    if ((drv)-&gt;previous != NULL) {&bslash;&n;      lock_kernel();&bslash;&n;      if ((drv)-&gt;next != NULL)&bslash;&n;        (drv)-&gt;next-&gt;previous = (drv)-&gt;previous;&bslash;&n;      *((drv)-&gt;previous) = (drv)-&gt;next;&bslash;&n;      (drv)-&gt;previous = NULL;&bslash;&n;      (drv)-&gt;next = NULL;&bslash;&n;      unlock_kernel();&bslash;&n;    }&bslash;&n;  } while (0)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* cpia_h */
eof
