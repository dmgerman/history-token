macro_line|#ifndef _TAS_IOCTL_H_
DECL|macro|_TAS_IOCTL_H_
mdefine_line|#define _TAS_IOCTL_H_
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/soundcard.h&gt;
DECL|macro|TAS_READ_EQ
mdefine_line|#define TAS_READ_EQ              _SIOR(&squot;t&squot;,0,struct tas_biquad_ctrl_t)
DECL|macro|TAS_WRITE_EQ
mdefine_line|#define TAS_WRITE_EQ             _SIOW(&squot;t&squot;,0,struct tas_biquad_ctrl_t)
DECL|macro|TAS_READ_EQ_LIST
mdefine_line|#define TAS_READ_EQ_LIST         _SIOR(&squot;t&squot;,1,struct tas_biquad_ctrl_t)
DECL|macro|TAS_WRITE_EQ_LIST
mdefine_line|#define TAS_WRITE_EQ_LIST        _SIOW(&squot;t&squot;,1,struct tas_biquad_ctrl_t)
DECL|macro|TAS_READ_EQ_FILTER_COUNT
mdefine_line|#define TAS_READ_EQ_FILTER_COUNT  _SIOR(&squot;t&squot;,2,int)
DECL|macro|TAS_READ_EQ_CHANNEL_COUNT
mdefine_line|#define TAS_READ_EQ_CHANNEL_COUNT _SIOR(&squot;t&squot;,3,int)
DECL|macro|TAS_READ_DRCE
mdefine_line|#define TAS_READ_DRCE            _SIOR(&squot;t&squot;,4,struct tas_drce_ctrl_t)
DECL|macro|TAS_WRITE_DRCE
mdefine_line|#define TAS_WRITE_DRCE           _SIOW(&squot;t&squot;,4,struct tas_drce_ctrl_t)
DECL|macro|TAS_READ_DRCE_CAPS
mdefine_line|#define TAS_READ_DRCE_CAPS       _SIOR(&squot;t&squot;,5,int)
DECL|macro|TAS_READ_DRCE_MIN
mdefine_line|#define TAS_READ_DRCE_MIN        _SIOR(&squot;t&squot;,6,int)
DECL|macro|TAS_READ_DRCE_MAX
mdefine_line|#define TAS_READ_DRCE_MAX        _SIOR(&squot;t&squot;,7,int)
macro_line|#endif
eof
