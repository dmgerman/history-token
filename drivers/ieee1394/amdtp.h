multiline_comment|/* -*- c-basic-offset: 8 -*- */
macro_line|#ifndef __AMDTP_H
DECL|macro|__AMDTP_H
mdefine_line|#define __AMDTP_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &quot;ieee1394-ioctl.h&quot;
multiline_comment|/* The userspace interface for the Audio &amp; Music Data Transmission&n; * Protocol driver is really simple. First, open /dev/amdtp, use the&n; * ioctl to configure format, rate, dimension and either plug or&n; * channel, then start writing samples.&n; *&n; * The formats supported by the driver are listed below.&n; * AMDTP_FORMAT_RAW corresponds to the AM824 raw format, which can&n; * carry any number of channels, so use this if you&squot;re streaming&n; * multichannel audio.  The AMDTP_FORMAT_IEC958_PCM corresponds to the&n; * AM824 IEC958 encapsulation without the IEC958 data bit set, using&n; * AMDTP_FORMAT_IEC958_AC3 will transmit the samples with the data bit&n; * set, suitable for transmitting compressed AC-3 audio.&n; *&n; * The rate field specifies the transmission rate; supported values&n; * are 32000, 44100, 48000, 88200, 96000, 176400 and 192000.&n; *&n; * The dimension field specifies the dimension of the signal, that is,&n; * the number of audio channels.  Only AMDTP_FORMAT_RAW supports&n; * settings greater than 2.  &n; *&n; * The mode field specifies which transmission mode to use. The AMDTP&n; * specifies two different transmission modes: blocking and&n; * non-blocking.  The blocking transmission mode always send a fixed&n; * number of samples, typically 8, 16 or 32.  To exactly match the&n; * transmission rate, the driver alternates between sending empty and&n; * non-empty packets.  In non-blocking mode, the driver transmits as&n; * small packets as possible.  For example, for a transmission rate of&n; * 44100Hz, the driver should send 5 41/80 samples in every cycle, but&n; * this is not possible so instead the driver alternates between&n; * sending 5 and 6 samples.&n; *&n; * The last thing to specify is either the isochronous channel to use&n; * or the output plug to connect to.  If you know what channel the&n; * destination device will listen on, you can specify the channel&n; * directly and use the AMDTP_IOC_CHANNEL ioctl.  However, if the&n; * destination device chooses the channel and uses the IEC61883-1 plug&n; * mechanism, you can specify an output plug to connect to.  The&n; * driver will pick up the channel number from the plug once the&n; * destination device locks the output plug control register.  In this&n; * case set the plug field and use the AMDTP_IOC_PLUG ioctl.&n; *&n; * Having configured the interface, the driver now accepts writes of&n; * regular 16 bit signed little endian samples, with the channels&n; * interleaved.  For example, 4 channels would look like:&n; *&n; *   | sample 0                                      | sample 1    ...&n; *   | ch. 0     | ch. 1     | ch. 2     | ch. 3     | ch. 0     | ...&n; *   | lsb | msb | lsb | msb | lsb | msb | lsb | msb | lsb | msb | ...&n; *&n; */
r_enum
(brace
DECL|enumerator|AMDTP_FORMAT_RAW
id|AMDTP_FORMAT_RAW
comma
DECL|enumerator|AMDTP_FORMAT_IEC958_PCM
id|AMDTP_FORMAT_IEC958_PCM
comma
DECL|enumerator|AMDTP_FORMAT_IEC958_AC3
id|AMDTP_FORMAT_IEC958_AC3
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|AMDTP_MODE_BLOCKING
id|AMDTP_MODE_BLOCKING
comma
DECL|enumerator|AMDTP_MODE_NON_BLOCKING
id|AMDTP_MODE_NON_BLOCKING
comma
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|AMDTP_INPUT_LE16
id|AMDTP_INPUT_LE16
comma
DECL|enumerator|AMDTP_INPUT_BE16
id|AMDTP_INPUT_BE16
comma
)brace
suffix:semicolon
DECL|struct|amdtp_ioctl
r_struct
id|amdtp_ioctl
(brace
DECL|member|format
id|__u32
id|format
suffix:semicolon
DECL|member|rate
id|__u32
id|rate
suffix:semicolon
DECL|member|dimension
id|__u32
id|dimension
suffix:semicolon
DECL|member|mode
id|__u32
id|mode
suffix:semicolon
DECL|member|channel
DECL|member|plug
DECL|member|u
r_union
(brace
id|__u32
id|channel
suffix:semicolon
id|__u32
id|plug
suffix:semicolon
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __AMDTP_H */
eof
