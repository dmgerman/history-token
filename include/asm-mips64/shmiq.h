multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Please note that the comments on this file may be out of date&n; * and that they represent what I have figured about the shmiq device&n; * so far in IRIX.&n; *&n; * This also contains some streams and idev bits.&n; *&n; * They may contain errors, please, refer to the source code of the Linux  &n; * kernel for a definitive answer on what we have implemented&n; *&n; * Miguel.&n; */
macro_line|#ifndef _ASM_SHMIQ_H
DECL|macro|_ASM_SHMIQ_H
mdefine_line|#define _ASM_SHMIQ_H
multiline_comment|/* STREAMs ioctls */
DECL|macro|STRIOC
mdefine_line|#define STRIOC    (&squot;S&squot; &lt;&lt; 8)
DECL|macro|I_STR
mdefine_line|#define I_STR     (STRIOC | 010)
DECL|macro|I_PUSH
mdefine_line|#define I_PUSH    (STRIOC | 02)
DECL|macro|I_LINK
mdefine_line|#define I_LINK    (STRIOC | 014)
DECL|macro|I_UNLINK
mdefine_line|#define I_UNLINK  (STRIOC | 015)
multiline_comment|/* Data structure passed on I_STR ioctls */
DECL|struct|strioctl
r_struct
id|strioctl
(brace
DECL|member|ic_cmd
r_int
id|ic_cmd
suffix:semicolon
multiline_comment|/* streams ioctl command */
DECL|member|ic_timout
r_int
id|ic_timout
suffix:semicolon
multiline_comment|/* timeout */
DECL|member|ic_len
r_int
id|ic_len
suffix:semicolon
multiline_comment|/* lenght of data */
DECL|member|ic_dp
r_void
op_star
id|ic_dp
suffix:semicolon
multiline_comment|/* data */
)brace
suffix:semicolon
multiline_comment|/*&n; * For mapping the shared memory input queue, you have to:&n; *&n; * 1. Map /dev/zero for the number of bytes you want to use&n; *    for your shared memory input queue plus the size of the&n; *    sharedMemoryInputQueue structure + 4 (I still have not figured&n; *    what this one is for&n; *&n; * 2. Open /dev/shmiq&n; *&n; * 3. Open /dev/qcntlN N is [0..Nshmiqs]&n; *&n; * 4. Fill a shmiqreq structure.  user_vaddr should point to the return&n; *    address from the /dev/zero mmap.  Arg is the number of shmqevents&n; *    that fit into the /dev/zero region (remember that at the beginning there&n; *    is a sharedMemoryInputQueue header).&n; *&n; * 5. Issue the ioctl (qcntlfd, QIOCATTACH, &amp;your_shmiqreq);&n; */
DECL|struct|shmiqreq
r_struct
id|shmiqreq
(brace
DECL|member|user_vaddr
r_char
op_star
id|user_vaddr
suffix:semicolon
DECL|member|arg
r_int
id|arg
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* map the shmiq into the process address space */
DECL|macro|QIOCATTACH
mdefine_line|#define QIOCATTACH       _IOW(&squot;Q&squot;,1,struct shmiqreq)
multiline_comment|/* remove mappings */
DECL|macro|QIOCDETACH
mdefine_line|#define QIOCDETACH       _IO(&squot;Q&squot;,2)
multiline_comment|/*&n; * A shared memory input queue event.&n; */
DECL|struct|shmqdata
r_struct
id|shmqdata
(brace
DECL|member|device
r_int
r_char
id|device
suffix:semicolon
multiline_comment|/* device major */
DECL|member|which
r_int
r_char
id|which
suffix:semicolon
multiline_comment|/* device minor */
DECL|member|type
r_int
r_char
id|type
suffix:semicolon
multiline_comment|/* event type */
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
multiline_comment|/* little event data */
r_union
(brace
DECL|member|pos
r_int
id|pos
suffix:semicolon
multiline_comment|/* big event data */
DECL|member|ptraxis
r_int
id|ptraxis
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* event data for PTR events */
DECL|member|un
)brace
id|un
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* indetifies the shmiq and the device */
DECL|struct|shmiqlinkid
r_struct
id|shmiqlinkid
(brace
DECL|member|devminor
r_int
r_int
id|devminor
suffix:semicolon
DECL|member|index
r_int
r_int
id|index
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|shmqevent
r_struct
id|shmqevent
(brace
r_union
(brace
DECL|member|time
r_int
id|time
suffix:semicolon
DECL|member|id
r_struct
id|shmiqlinkid
id|id
suffix:semicolon
DECL|member|un
)brace
id|un
suffix:semicolon
DECL|member|data
r_struct
id|shmqdata
id|data
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * sharedMemoryInputQueue: this describes the shared memory input queue.&n; *&n; * head   is the user index into the events, user can modify this one.&n; * tail   is managed by the kernel.&n; * flags  is one of SHMIQ_OVERFLOW or SHMIQ_CORRUPTED&n; *        if OVERFLOW is set it seems ioctl QUIOCSERVICED should be called &n; *        to notify the kernel.&n; * events where the kernel sticks the events.&n; */
DECL|struct|sharedMemoryInputQueue
r_struct
id|sharedMemoryInputQueue
(brace
DECL|member|head
r_volatile
r_int
id|head
suffix:semicolon
multiline_comment|/* user&squot;s index into events */
DECL|member|tail
r_volatile
r_int
id|tail
suffix:semicolon
multiline_comment|/* kernel&squot;s index into events */
DECL|member|flags
r_volatile
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* place for out-of-band data */
DECL|macro|SHMIQ_OVERFLOW
mdefine_line|#define SHMIQ_OVERFLOW  1
DECL|macro|SHMIQ_CORRUPTED
mdefine_line|#define SHMIQ_CORRUPTED 2
DECL|member|events
r_struct
id|shmqevent
id|events
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* input event buffer */
)brace
suffix:semicolon
multiline_comment|/* have to figure this one out */
DECL|macro|QIOCGETINDX
mdefine_line|#define QIOCGETINDX      _IOWR(&squot;Q&squot;, 8, int)
multiline_comment|/* acknowledge shmiq overflow */
DECL|macro|QIOCSERVICED
mdefine_line|#define QIOCSERVICED     _IO(&squot;Q&squot;, 3)
multiline_comment|/* Double indirect I_STR ioctl, yeah, fun fun fun */
DECL|struct|muxioctl
r_struct
id|muxioctl
(brace
DECL|member|index
r_int
id|index
suffix:semicolon
multiline_comment|/* lower stream index */
DECL|member|realcmd
r_int
id|realcmd
suffix:semicolon
multiline_comment|/* the actual command for the subdevice */
)brace
suffix:semicolon
multiline_comment|/* Double indirect ioctl */
DECL|macro|QIOCIISTR
mdefine_line|#define QIOCIISTR        _IOW(&squot;Q&squot;, 7, struct muxioctl)
multiline_comment|/* Cursor ioclts: */
multiline_comment|/* set cursor tracking mode */
DECL|macro|QIOCURSTRK
mdefine_line|#define QIOCURSTRK      _IOW(&squot;Q&squot;, 4, int)
multiline_comment|/* set cursor filter box */
DECL|macro|QIOCURSIGN
mdefine_line|#define QIOCURSIGN      _IOW(&squot;Q&squot;, 5, int [4])
multiline_comment|/* set cursor axes */
DECL|struct|shmiqsetcurs
r_struct
id|shmiqsetcurs
(brace
DECL|member|index
r_int
id|index
suffix:semicolon
DECL|member|axes
r_int
id|axes
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|QIOCSETCURS
mdefine_line|#define QIOCSETCURS     _IOWR(&squot;Q&squot;,  9, struct shmiqsetcurs)
multiline_comment|/* set cursor position */
DECL|struct|shmiqsetcpos
r_struct
id|shmiqsetcpos
(brace
DECL|member|x
r_int
id|x
suffix:semicolon
DECL|member|y
r_int
id|y
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|QIOCSETCPOS
mdefine_line|#define QIOCSETCPOS     _IOWR(&squot;Q&squot;, 10, struct shmiqsetcpos)
multiline_comment|/* get time since last event */
DECL|macro|QIOCGETITIME
mdefine_line|#define QIOCGETITIME    _IOR(&squot;Q&squot;, 11, time_t)
multiline_comment|/* set curent screen */
DECL|macro|QIOCSETSCRN
mdefine_line|#define QIOCSETSCRN     _IOW(&squot;Q&squot;,6,int)
multiline_comment|/* -------------------- iDev stuff -------------------- */
DECL|macro|IDEV_MAX_NAME_LEN
mdefine_line|#define IDEV_MAX_NAME_LEN 15
DECL|macro|IDEV_MAX_TYPE_LEN
mdefine_line|#define IDEV_MAX_TYPE_LEN 15
r_typedef
r_struct
(brace
DECL|member|devName
r_char
id|devName
(braket
id|IDEV_MAX_NAME_LEN
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|devType
r_char
id|devType
(braket
id|IDEV_MAX_TYPE_LEN
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|nButtons
r_int
r_int
id|nButtons
suffix:semicolon
DECL|member|nValuators
r_int
r_int
id|nValuators
suffix:semicolon
DECL|member|nLEDs
r_int
r_int
id|nLEDs
suffix:semicolon
DECL|member|nStrDpys
r_int
r_int
id|nStrDpys
suffix:semicolon
DECL|member|nIntDpys
r_int
r_int
id|nIntDpys
suffix:semicolon
DECL|member|nBells
r_int
r_char
id|nBells
suffix:semicolon
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
DECL|macro|IDEV_HAS_KEYMAP
mdefine_line|#define IDEV_HAS_KEYMAP&t;&t;0x01
DECL|macro|IDEV_HAS_PROXIMITY
mdefine_line|#define IDEV_HAS_PROXIMITY &t;0x02
DECL|macro|IDEV_HAS_PCKBD
mdefine_line|#define IDEV_HAS_PCKBD &t;&t;0x04
DECL|typedef|idevDesc
)brace
id|idevDesc
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|nothing_for_now
r_char
op_star
id|nothing_for_now
suffix:semicolon
DECL|typedef|idevInfo
)brace
id|idevInfo
suffix:semicolon
DECL|macro|IDEV_KEYMAP_NAME_LEN
mdefine_line|#define IDEV_KEYMAP_NAME_LEN 15
r_typedef
r_struct
(brace
DECL|member|name
r_char
id|name
(braket
id|IDEV_KEYMAP_NAME_LEN
op_plus
l_int|1
)braket
suffix:semicolon
DECL|typedef|idevKeymapDesc
)brace
id|idevKeymapDesc
suffix:semicolon
multiline_comment|/* The valuator definition */
r_typedef
r_struct
(brace
DECL|member|hwMinRes
r_int
id|hwMinRes
suffix:semicolon
DECL|member|hwMaxRes
r_int
id|hwMaxRes
suffix:semicolon
DECL|member|hwMinVal
r_int
id|hwMinVal
suffix:semicolon
DECL|member|hwMaxVal
r_int
id|hwMaxVal
suffix:semicolon
DECL|member|possibleModes
r_int
r_char
id|possibleModes
suffix:semicolon
DECL|macro|IDEV_ABSOLUTE
mdefine_line|#define IDEV_ABSOLUTE           0x0
DECL|macro|IDEV_RELATIVE
mdefine_line|#define IDEV_RELATIVE           0x1
DECL|macro|IDEV_EITHER
mdefine_line|#define IDEV_EITHER             0x2
DECL|member|mode
r_int
r_char
id|mode
suffix:semicolon
multiline_comment|/* One of: IDEV_ABSOLUTE, IDEV_RELATIVE */
DECL|member|resolution
r_int
r_int
id|resolution
suffix:semicolon
DECL|member|minVal
r_int
id|minVal
suffix:semicolon
DECL|member|maxVal
r_int
id|maxVal
suffix:semicolon
DECL|typedef|idevValuatorDesc
)brace
id|idevValuatorDesc
suffix:semicolon
multiline_comment|/* This is used to query a specific valuator with the IDEVGETVALUATORDESC ioctl */
r_typedef
r_struct
(brace
DECL|member|valNum
r_int
id|valNum
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|desc
id|idevValuatorDesc
id|desc
suffix:semicolon
DECL|typedef|idevGetSetValDesc
)brace
id|idevGetSetValDesc
suffix:semicolon
DECL|macro|IDEVGETDEVICEDESC
mdefine_line|#define IDEVGETDEVICEDESC&t;_IOWR(&squot;i&squot;, 0,  idevDesc)
DECL|macro|IDEVGETVALUATORDESC
mdefine_line|#define IDEVGETVALUATORDESC     _IOWR(&squot;i&squot;, 1,  idevGetSetValDesc)
DECL|macro|IDEVGETKEYMAPDESC
mdefine_line|#define IDEVGETKEYMAPDESC&t;_IOWR(&squot;i&squot;, 2,  idevKeymapDesc)
DECL|macro|IDEVINITDEVICE
mdefine_line|#define IDEVINITDEVICE&t;&t;_IOW (&squot;i&squot;, 51, unsigned int)
macro_line|#ifdef __KERNEL__
multiline_comment|/* These are only interpreted by SHMIQ-attacheable devices and are internal&n; * to the kernel&n; */
DECL|macro|SHMIQ_OFF
mdefine_line|#define SHMIQ_OFF        _IO(&squot;Q&squot;,1)
DECL|macro|SHMIQ_ON
mdefine_line|#define SHMIQ_ON         _IO(&squot;Q&squot;,2)
r_void
id|shmiq_push_event
(paren
r_struct
id|shmqevent
op_star
id|e
)paren
suffix:semicolon
r_int
id|get_sioc
(paren
r_struct
id|strioctl
op_star
id|sioc
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* _ASM_SHMIQ_H */
eof
