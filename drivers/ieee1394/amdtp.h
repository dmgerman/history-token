multiline_comment|/* -*- c-basic-offset: 8 -*- */
macro_line|#ifndef __AMDTP_H
DECL|macro|__AMDTP_H
mdefine_line|#define __AMDTP_H
macro_line|#include &lt;asm/ioctl.h&gt;
macro_line|#include &lt;asm/types.h&gt;
multiline_comment|/* The userspace interface for the Audio &amp; Music Data Transmission&n; * Protocol driver is really simple. First, open /dev/amdtp, use the&n; * ioctl to configure format, rate, dimension and either plug or&n; * channel, then start writing samples.&n; *&n; * The formats supported by the driver are listed below.&n; * AMDTP_FORMAT_RAW corresponds to the AM824 raw format, which can&n; * carry any number of channels, so use this if you&squot;re streaming&n; * multichannel audio.  The AMDTP_FORMAT_IEC958_PCM corresponds to the&n; * AM824 IEC958 encapsulation without the IEC958 data bit set, using&n; * AMDTP_FORMAT_IEC958_AC3 will transmit the samples with the data bit&n; * set, suitable for transmitting compressed AC-3 audio.&n; *&n; * The rate field specifies the transmission rate; supported values are&n; * AMDTP_RATE_32KHZ, AMDTP_RATE_44K1HZ and AMDTP_RATE_48KHZ.&n; *&n; * The dimension field specifies the dimension of the signal, that is,&n; * the number of audio channels.  Only AMDTP_FORMAT_RAW supports&n; * settings greater than 2.  &n; *&n; * The last thing to specify is either the isochronous channel to use&n; * or the output plug to connect to.  If you know what channel the&n; * destination device will listen on, you can specify the channel&n; * directly and use the AMDTP_IOC_CHANNEL ioctl.  However, if the&n; * destination device chooses the channel and uses the IEC61883-1 plug&n; * mechanism, you can specify an output plug to connect to.  The&n; * driver will pick up the channel number from the plug once the&n; * destination device locks the output plug control register.  In this&n; * case set the plug field and use the AMDTP_IOC_PLUG ioctl.&n; *&n; * Having configured the interface, the driver now accepts writes of&n; * regular 16 bit signed little endian samples, with the channels&n; * interleaved.  For example, 4 channels would look like:&n; *&n; *   | sample 0                                      | sample 1    ...&n; *   | ch. 0     | ch. 1     | ch. 2     | ch. 3     | ch. 0     | ...&n; *   | lsb | msb | lsb | msb | lsb | msb | lsb | msb | lsb | msb | ...&n; *&n; */
multiline_comment|/* We use &squot;#&squot; for our ioctl magic number because it&squot;s cool. */
DECL|macro|AMDTP_IOC_CHANNEL
mdefine_line|#define AMDTP_IOC_CHANNEL _IOW(&squot;#&squot;, 0, sizeof (struct amdtp_ioctl))
DECL|macro|AMDTP_IOC_PLUG
mdefine_line|#define AMDTP_IOC_PLUG    _IOW(&squot;#&squot;, 1, sizeof (struct amdtp_ioctl))
DECL|macro|AMDTP_IOC_PING
mdefine_line|#define AMDTP_IOC_PING    _IOW(&squot;#&squot;, 2, sizeof (struct amdtp_ioctl))
DECL|macro|AMDTP_IOC_ZAP
mdefine_line|#define AMDTP_IOC_ZAP     _IO(&squot;#&squot;, 3)
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
DECL|enumerator|AMDTP_RATE_32KHZ
id|AMDTP_RATE_32KHZ
comma
DECL|enumerator|AMDTP_RATE_44K1HZ
id|AMDTP_RATE_44K1HZ
comma
DECL|enumerator|AMDTP_RATE_48KHZ
id|AMDTP_RATE_48KHZ
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
