macro_line|#ifndef _AD1889_H_
DECL|macro|_AD1889_H_
mdefine_line|#define _AD1889_H_
DECL|macro|AD_DSWSMC
mdefine_line|#define AD_DSWSMC&t;0x00&t;/* DMA input wave/syn mixer control */
DECL|macro|AD_DSRAMC
mdefine_line|#define AD_DSRAMC&t;0x02&t;/* DMA output resamp/ADC mixer control */
DECL|macro|AD_DSWADA
mdefine_line|#define AD_DSWADA&t;0x04&t;/* DMA input wave attenuation */
DECL|macro|AD_DSSYDA
mdefine_line|#define AD_DSSYDA&t;0x06&t;/* DMA input syn attentuation */
DECL|macro|AD_DSWAS
mdefine_line|#define AD_DSWAS&t;0x08&t;/* wave input sample rate */
DECL|macro|AD_DSRES
mdefine_line|#define AD_DSRES&t;0x0a&t;/* resampler output sample rate */
DECL|macro|AD_DSCCS
mdefine_line|#define AD_DSCCS&t;0x0c&t;/* chip control/status */
DECL|macro|AD_DMARESBA
mdefine_line|#define AD_DMARESBA&t;0x40&t;/* RES base addr */
DECL|macro|AD_DMARESCA
mdefine_line|#define AD_DMARESCA&t;0x44&t;/* RES current addr */
DECL|macro|AD_DMARESBC
mdefine_line|#define AD_DMARESBC&t;0x48&t;/* RES base cnt */
DECL|macro|AD_DMARESCC
mdefine_line|#define AD_DMARESCC&t;0x4c&t;/* RES current count */
DECL|macro|AD_DMAADCBA
mdefine_line|#define AD_DMAADCBA&t;0x50&t;/* ADC */
DECL|macro|AD_DMAADCCA
mdefine_line|#define AD_DMAADCCA&t;0x54
DECL|macro|AD_DMAADCBC
mdefine_line|#define AD_DMAADCBC&t;0x58
DECL|macro|AD_DMAADCCC
mdefine_line|#define AD_DMAADCCC&t;0x5c
DECL|macro|AD_DMASYNBA
mdefine_line|#define AD_DMASYNBA&t;0x60&t;/* SYN */
DECL|macro|AD_DMASYNCA
mdefine_line|#define AD_DMASYNCA&t;0x64
DECL|macro|AD_DMASYNBC
mdefine_line|#define AD_DMASYNBC&t;0x68
DECL|macro|AD_DMASYNCC
mdefine_line|#define AD_DMASYNCC&t;0x6c
DECL|macro|AD_DMAWAVBA
mdefine_line|#define AD_DMAWAVBA&t;0x70&t;/* WAV */
DECL|macro|AD_DMAWAVCA
mdefine_line|#define AD_DMAWAVCA&t;0x74
DECL|macro|AD_DMAWAVBC
mdefine_line|#define AD_DMAWAVBC&t;0x78
DECL|macro|AD_DMAWAVCC
mdefine_line|#define AD_DMAWAVCC&t;0x7c
DECL|macro|AD_DMARESICC
mdefine_line|#define AD_DMARESICC&t;0x80&t;/* RES interrupt current count */
DECL|macro|AD_DMARESIBC
mdefine_line|#define AD_DMARESIBC&t;0x84&t;/* RES interrupt base count */
DECL|macro|AD_DMAADCICC
mdefine_line|#define AD_DMAADCICC&t;0x88&t;/* ADC interrupt current count */
DECL|macro|AD_DMAADCIBC
mdefine_line|#define AD_DMAADCIBC&t;0x8c&t;/* ADC interrupt base count */
DECL|macro|AD_DMASYNICC
mdefine_line|#define AD_DMASYNICC&t;0x90&t;/* SYN interrupt current count */
DECL|macro|AD_DMASYNIBC
mdefine_line|#define AD_DMASYNIBC&t;0x94&t;/* SYN interrupt base count */
DECL|macro|AD_DMAWAVICC
mdefine_line|#define AD_DMAWAVICC&t;0x98&t;/* WAV interrupt current count */
DECL|macro|AD_DMAWAVIBC
mdefine_line|#define AD_DMAWAVIBC&t;0x9c&t;/* WAV interrupt base count */
DECL|macro|AD_DMARESCTRL
mdefine_line|#define AD_DMARESCTRL&t;0xa0&t;/* RES PCI control/status */
DECL|macro|AD_DMAADCCTRL
mdefine_line|#define AD_DMAADCCTRL&t;0xa8&t;/* ADC PCI control/status */
DECL|macro|AD_DMASYNCTRL
mdefine_line|#define AD_DMASYNCTRL&t;0xb0&t;/* SYN PCI control/status */
DECL|macro|AD_DMAWAVCTRL
mdefine_line|#define AD_DMAWAVCTRL&t;0xb8&t;/* WAV PCI control/status */
DECL|macro|AD_DMADISR
mdefine_line|#define AD_DMADISR&t;0xc0&t;/* PCI DMA intr status */
DECL|macro|AD_DMACHSS
mdefine_line|#define AD_DMACHSS&t;0xc4&t;/* PCI DMA channel stop status */
DECL|macro|AD_GPIOIPC
mdefine_line|#define AD_GPIOIPC&t;0xc8&t;/* IO port ctrl */
DECL|macro|AD_GPIOOP
mdefine_line|#define AD_GPIOOP&t;0xca&t;/* IO output status */
DECL|macro|AD_GPIOIP
mdefine_line|#define AD_GPIOIP&t;0xcc&t;/* IO input status */
multiline_comment|/* AC97 registers, 0x100 - 0x17f; see ac97.h */
DECL|macro|AD_ACIC
mdefine_line|#define AD_ACIC&t;&t;0x180&t;/* AC Link interface ctrl */
multiline_comment|/* OPL3; BAR1 */
DECL|macro|AD_OPLM0AS
mdefine_line|#define AD_OPLM0AS&t;0x00&t;/* Music0 address/status */
DECL|macro|AD_OPLM0DATA
mdefine_line|#define AD_OPLM0DATA&t;0x01&t;/* Music0 data */
DECL|macro|AD_OPLM1A
mdefine_line|#define AD_OPLM1A&t;0x02&t;/* Music1 address */
DECL|macro|AD_OPLM1DATA
mdefine_line|#define AD_OPLM1DATA&t;0x03&t;/* Music1 data */
multiline_comment|/* 0x04-0x0f reserved */
multiline_comment|/* MIDI; BAR2 */
DECL|macro|AD_MIDA
mdefine_line|#define AD_MIDA&t;&t;0x00&t;/* MIDI data */
DECL|macro|AD_MISC
mdefine_line|#define AD_MISC&t;&t;0x01&t;/* MIDI status/cmd */
multiline_comment|/* 0x02-0xff reserved */
DECL|macro|AD_DSIOMEMSIZE
mdefine_line|#define AD_DSIOMEMSIZE&t;512
DECL|macro|AD_OPLMEMSIZE
mdefine_line|#define AD_OPLMEMSIZE&t;16
DECL|macro|AD_MIDIMEMSIZE
mdefine_line|#define AD_MIDIMEMSIZE&t;16
DECL|macro|AD_WAV_STATE
mdefine_line|#define AD_WAV_STATE&t;0
DECL|macro|AD_ADC_STATE
mdefine_line|#define AD_ADC_STATE&t;1
DECL|macro|AD_MAX_STATES
mdefine_line|#define AD_MAX_STATES&t;2
DECL|macro|DMA_SIZE
mdefine_line|#define DMA_SIZE&t;(128*1024)
DECL|macro|DMA_FLAG_MAPPED
mdefine_line|#define DMA_FLAG_MAPPED&t;1
r_struct
id|ad1889_dev
suffix:semicolon
DECL|struct|ad1889_state
r_typedef
r_struct
id|ad1889_state
(brace
DECL|member|card
r_struct
id|ad1889_dev
op_star
id|card
suffix:semicolon
DECL|member|open_mode
id|mode_t
id|open_mode
suffix:semicolon
DECL|struct|dmabuf
r_struct
id|dmabuf
(brace
DECL|member|rate
r_int
r_int
id|rate
suffix:semicolon
DECL|member|fmt
DECL|member|enable
r_int
r_char
id|fmt
comma
id|enable
suffix:semicolon
multiline_comment|/* buf management */
DECL|member|rawbuf_size
r_int
id|rawbuf_size
suffix:semicolon
DECL|member|rawbuf
r_void
op_star
id|rawbuf
suffix:semicolon
DECL|member|dma_handle
id|dma_addr_t
id|dma_handle
suffix:semicolon
multiline_comment|/* mapped address */
DECL|member|dma_len
r_int
r_int
id|dma_len
suffix:semicolon
multiline_comment|/* number of bytes mapped */
multiline_comment|/* indexes into rawbuf for setting up DMA engine */
DECL|member|rd_ptr
DECL|member|wr_ptr
r_volatile
r_int
r_int
id|rd_ptr
comma
id|wr_ptr
suffix:semicolon
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
multiline_comment|/* to wait for buf servicing */
multiline_comment|/* OSS bits */
DECL|member|mapped
r_int
r_int
id|mapped
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ready
r_int
r_int
id|ready
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ossfragshift
r_int
r_int
id|ossfragshift
suffix:semicolon
DECL|member|ossmaxfrags
r_int
id|ossmaxfrags
suffix:semicolon
DECL|member|subdivision
r_int
r_int
id|subdivision
suffix:semicolon
DECL|member|dmabuf
)brace
id|dmabuf
suffix:semicolon
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
DECL|typedef|ad1889_state_t
)brace
id|ad1889_state_t
suffix:semicolon
DECL|struct|ad1889_dev
r_typedef
r_struct
id|ad1889_dev
(brace
DECL|member|regbase
r_void
id|__iomem
op_star
id|regbase
suffix:semicolon
DECL|member|pci
r_struct
id|pci_dev
op_star
id|pci
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|dev_audio
r_int
id|dev_audio
suffix:semicolon
multiline_comment|/* states; one per channel; right now only WAV and ADC */
DECL|member|state
r_struct
id|ad1889_state
id|state
(braket
id|AD_MAX_STATES
)braket
suffix:semicolon
multiline_comment|/* AC97 codec */
DECL|member|ac97_codec
r_struct
id|ac97_codec
op_star
id|ac97_codec
suffix:semicolon
DECL|member|ac97_features
id|u16
id|ac97_features
suffix:semicolon
multiline_comment|/* debugging stuff */
DECL|struct|stats
r_struct
id|stats
(brace
DECL|member|wav_intrs
DECL|member|adc_intrs
r_int
r_int
id|wav_intrs
comma
id|adc_intrs
suffix:semicolon
DECL|member|blocks
DECL|member|underrun
DECL|member|error
r_int
r_int
id|blocks
comma
id|underrun
comma
id|error
suffix:semicolon
DECL|member|stats
)brace
id|stats
suffix:semicolon
DECL|typedef|ad1889_dev_t
)brace
id|ad1889_dev_t
suffix:semicolon
DECL|struct|ad1889_reg
r_typedef
r_struct
id|ad1889_reg
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|offset
r_int
id|offset
suffix:semicolon
DECL|member|width
r_int
id|width
suffix:semicolon
DECL|typedef|ad1889_reg_t
)brace
id|ad1889_reg_t
suffix:semicolon
macro_line|#endif
eof
