/**
 * This file is part of the UKHASnet maintained RFM69 library.
 *
 * @file ukhasnet-rfm69.h
 * @addtogroup ukhasnet-rfm69
 * @{
 */

#define RFM_DEBUG Serial

#ifndef __RFM69CONFIG_H__
#define __RFM69CONFIG_H__

#include <UKHASnetRFM69.h>

static const int DIO1_pin = 5; // = Pin D1 on WEMOS D1 mini

static const rfm_reg_t CONFIG[][2] =
{
    { RFM69_REG_01_OPMODE,      RF_OPMODE_SEQUENCER_ON | RF_OPMODE_LISTEN_OFF | RFM69_MODE_STDBY },
    { RFM69_REG_02_DATA_MODUL,  RF_DATAMODUL_DATAMODE_PACKET | RF_DATAMODUL_MODULATIONTYPE_FSK | RF_DATAMODUL_MODULATIONSHAPING_00 },

    { RFM69_REG_03_BITRATE_MSB, 0x3E}, // 2000 bps
    { RFM69_REG_04_BITRATE_LSB, 0x80},

    { RFM69_REG_05_FDEV_MSB,    0x00}, // 12000 hz (24000 hz shift)
    { RFM69_REG_06_FDEV_LSB,    0xC5},

    { RFM69_REG_07_FRF_MSB,     0xD9 }, // 869.5 MHz
    { RFM69_REG_08_FRF_MID,     0x60 }, // calculated: 0x80?
    { RFM69_REG_09_FRF_LSB,     0x12 },

    { RFM69_REG_0B_AFC_CTRL,    RF_AFCLOWBETA_OFF }, // AFC Offset On

    // PA Settings
    // +20dBm formula: Pout=-11+OutputPower[dBmW] (with PA1 and PA2)** and high power PA settings (section 3.3.7 in datasheet)
    // Without extra flags: Pout=-14+OutputPower[dBmW]
    { RFM69_REG_11_PA_LEVEL,    RF_PALEVEL_PA0_ON | RF_PALEVEL_PA1_OFF | RF_PALEVEL_PA2_OFF | 0x1f},  // 10mW
    //{ RFM69_REG_11_PA_LEVEL, RF_PALEVEL_PA0_OFF | RF_PALEVEL_PA1_ON | RF_PALEVEL_PA2_ON | 0x1f},// 50mW

    { RFM69_REG_12_PA_RAMP, RF_PARAMP_500 }, // 500us PA ramp-up (1 bit)

    { RFM69_REG_13_OCP,         RF_OCP_ON | RF_OCP_TRIM_95 },

    { RFM69_REG_18_LNA,         RF_LNA_ZIN_50 }, // 50 ohm for matched antenna, 200 otherwise

    { RFM69_REG_19_RX_BW,       RF_RXBW_DCCFREQ_010 | RF_RXBW_MANT_16 | RF_RXBW_EXP_2}, // Rx Bandwidth: 128KHz

    //{ RFM69_REG_1E_AFC_FEI,     RF_AFCFEI_AFCAUTO_ON | RF_AFCFEI_AFCAUTOCLEAR_ON }, // Automatic AFC on, clear after each packet
    { RFM69_REG_1E_AFC_FEI, RF_AFCFEI_AFCAUTO_OFF | RF_AFCFEI_AFCAUTOCLEAR_OFF }, // Automatic AFC off, clear off after each packet

    { RFM69_REG_25_DIO_MAPPING1, RF_DIOMAPPING1_DIO0_10 | RF_DIOMAPPING1_DIO1_10 },
    { RFM69_REG_26_DIO_MAPPING2, RF_DIOMAPPING2_CLKOUT_OFF }, // Switch off Clkout

    /* receiver timeout:
     * max packet length is 72 octets
     * (3 preamble, 2 sync, 1 length, 64 message, 2 CRC)
     * timeout interrupt is generated (value*16*Tbit) after RSSI interrupt if
     * PayloadReady interrupt doesn't occur so a value of 36 would correspond
     * to the packet duration but not allow for any other delays hence set to
     * 40
     */
    { RFM69_REG_2B_RX_TIMEOUT2, 0xff }, // 510 bytes....

    // { RFM69_REG_2D_PREAMBLE_LSB, RF_PREAMBLESIZE_LSB_VALUE } // default 3 preamble bytes 0xAAAAAA

    //{ RFM69_REG_2E_SYNC_CONFIG, RF_SYNC_OFF | RF_SYNC_FIFOFILL_MANUAL }, // Sync bytes off
    { RFM69_REG_2E_SYNC_CONFIG, RF_SYNC_ON | RF_SYNC_FIFOFILL_AUTO | RF_SYNC_SIZE_2 | RF_SYNC_TOL_0 },
    { RFM69_REG_2F_SYNCVALUE1, 0x2D },
    { RFM69_REG_30_SYNCVALUE2, 0xAA },

    { RFM69_REG_37_PACKET_CONFIG1, RF_PACKET1_FORMAT_FIXED | RF_PACKET1_DCFREE_OFF | RF_PACKET1_CRC_ON | RF_PACKET1_CRCAUTOCLEAR_ON | RF_PACKET1_ADRSFILTERING_OFF },
    { RFM69_REG_38_PAYLOAD_LENGTH, 0 }, // Unlimited length packets; PacketFormat=0 && PayloadLength=0

    //{ RFM69_REG_37_PACKET_CONFIG1, RF_PACKET1_FORMAT_VARIABLE | RF_PACKET1_DCFREE_OFF | RF_PACKET1_CRC_ON | RF_PACKET1_CRCAUTOCLEAR_ON | RF_PACKET1_ADRSFILTERING_OFF },
    //{ RFM69_REG_38_PAYLOAD_LENGTH, RFM69_FIFO_SIZE }, // Full FIFO size for rx packet

    //{ RFM69_REG_3B_AUTOMODES, RF_AUTOMODES_ENTER_FIFONOTEMPTY | RF_AUTOMODES_EXIT_PACKETSENT | RF_AUTOMODES_INTERMEDIATE_TRANSMITTER },
    { RFM69_REG_3C_FIFO_THRESHOLD, RF_FIFOTHRESH_TXSTART_FIFONOTEMPTY | 0x05 }, //TX on FIFO not empty
    { RFM69_REG_3D_PACKET_CONFIG2, RF_PACKET2_RXRESTARTDELAY_2BITS | RF_PACKET2_AUTORXRESTART_ON | RF_PACKET2_AES_OFF }, //RXRESTARTDELAY must match transmitter PA ramp-down time (bitrate dependent)
    { RFM69_REG_6F_TEST_DAGC, RF_DAGC_IMPROVED_LOWBETA0 }, // run DAGC continuously in RX mode, recommended default for AfcLowBetaOn=0
    //{ RFM69_REG_71_TEST_AFC, 0x0E }, //14* 488hz = ~7KHz
    {255, 0}
  };

#endif /* __RFM69CONFIG_H__ */

/**
 * @}
 */
