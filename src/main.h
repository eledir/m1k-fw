#ifndef _MAIN_H_
#define _MAIN_H_

#define stringify(x)			#x
#define xstringify(s) stringify(s)
#define SWAP16(x)        ((((x) & 0xff00)>> 8) | (((x) & 0x00ff) << 8))
#define A 0
#define B 1

#define FLASH_TABLE_BASE	IFLASH0_ADDR + IFLASH0_SIZE - IFLASH0_PAGE_SIZE

typedef enum chan_mode{
	DISABLED = 0,
	SVMI = 1,
	SIMV = 2,
} chan_mode;

uint16_t packets_in[2][1024];
uint16_t packets_out[2][512];

typedef enum ch_params {
	i0_dac = 0,
	v0_adc = 1,
	i0_adc = 2,
	p1_simv = 3,
	p2_simv = 4
} ch_params;

uint8_t flash_table[IFLASH0_PAGE_SIZE];

uint8_t serial_number[USB_DEVICE_GET_SERIAL_NAME_LENGTH];
uint8_t slot_offset_in;
uint8_t slot_offset_out;
uint32_t packet_index_in;
uint32_t packet_index_out;
volatile uint32_t packet_index_send_in;
volatile uint32_t packet_index_send_out;
volatile uint16_t start_frame;
volatile bool send_in;
volatile bool send_out;
volatile bool sending_in;
volatile bool sending_out;
volatile bool sent_in;
volatile bool sent_out;
bool current_chan;
volatile bool reset;
bool main_b_vendor_enable;
bool start_timer;

uint8_t ret_data[64];

bool main_vendor_enable(void);

void main_vendor_disable(void);

void main_sof_action(void);

void main_suspend_action(void);

void main_resume_action(void);

bool main_setup_handle(void);
bool msft_string_handle(void);

void init_build_usb_serial_number(void);

void init_hardware(void);
void config_hardware(void);

void write_ad5122(uint32_t ch, uint8_t r1, uint8_t r2);
void write_adm1177(uint8_t* b, uint8_t ct);
void write_ad5663(uint8_t conf, uint16_t data);
void read_adm1177(uint8_t b[], uint8_t c);
void get_sample_ad7682(uint8_t ch, uint8_t *cfg, uint8_t *data);
void set_mode(uint32_t chan, chan_mode m);

void main_vendor_bulk_out_received(udd_ep_status_t status, iram_size_t nb_transfered, udd_ep_id_t ep);
void main_vendor_bulk_in_received(udd_ep_status_t status, iram_size_t nb_transfered, udd_ep_id_t ep);
void main_vendor_bulk_out_received_first(udd_ep_status_t status, iram_size_t nb_transfered, udd_ep_id_t ep);

#endif
