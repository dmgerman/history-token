multiline_comment|/* $Id: dummy.h,v 1.3 1999/09/21 14:37:41 davem Exp $&n; * drivers/sbus/audio/dummy.h&n; *&n; * Copyright (C) 1998 Derrick J. Brashear (shadow@dementia.org)&n; */
macro_line|#ifndef _DUMMY_H_
DECL|macro|_DUMMY_H_
mdefine_line|#define _DUMMY_H_
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/tqueue.h&gt;
DECL|macro|DUMMY_OUTFILE
mdefine_line|#define DUMMY_OUTFILE &quot;/usr/tmp/dummy.au&quot;
multiline_comment|/* Our structure for each chip */
DECL|struct|dummy_chip
r_struct
id|dummy_chip
(brace
DECL|member|perchip_info
r_struct
id|audio_info
id|perchip_info
suffix:semicolon
DECL|member|playlen
r_int
r_int
id|playlen
suffix:semicolon
DECL|member|tqueue
r_struct
id|tq_struct
id|tqueue
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|DUMMY_MIN_ATEN
mdefine_line|#define DUMMY_MIN_ATEN     (0)
DECL|macro|DUMMY_MAX_ATEN
mdefine_line|#define DUMMY_MAX_ATEN     (31)
DECL|macro|DUMMY_MAX_DEV_ATEN
mdefine_line|#define DUMMY_MAX_DEV_ATEN (63)
DECL|macro|DUMMY_MON_MIN_ATEN
mdefine_line|#define DUMMY_MON_MIN_ATEN         (0)
DECL|macro|DUMMY_MON_MAX_ATEN
mdefine_line|#define DUMMY_MON_MAX_ATEN         (63)
DECL|macro|DUMMY_DEFAULT_PLAYGAIN
mdefine_line|#define DUMMY_DEFAULT_PLAYGAIN     (132)
DECL|macro|DUMMY_DEFAULT_RECGAIN
mdefine_line|#define DUMMY_DEFAULT_RECGAIN      (126)
DECL|macro|DUMMY_MIN_GAIN
mdefine_line|#define DUMMY_MIN_GAIN     (0)
DECL|macro|DUMMY_MAX_GAIN
mdefine_line|#define DUMMY_MAX_GAIN     (15)
DECL|macro|DUMMY_PRECISION
mdefine_line|#define DUMMY_PRECISION    (8)             /* # of bits/sample */
DECL|macro|DUMMY_CHANNELS
mdefine_line|#define DUMMY_CHANNELS     (1)             /* channels/sample */
DECL|macro|DUMMY_RATE
mdefine_line|#define DUMMY_RATE   (8000)                /* default sample rate */
macro_line|#endif /* _DUMMY_H_ */
eof
