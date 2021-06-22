
 
 
/* Define to prevent recursive inclusion -------------------------------------*/
 
#ifndef __OPENPDMFILTER_H
#define __OPENPDMFILTER_H
 
#ifdef __cplusplus
  extern "C" {
#endif
 
 
/* Includes ------------------------------------------------------------------*/
 
#include <stdint.h>
 
 
/* Definitions ---------------------------------------------------------------*/
 
/*
 * Enable to use a Look-Up Table to improve performances while using more FLASH
 * and RAM memory.
 * Note: Without Look-Up Table up to stereo@16KHz configuration is supported.
 */
#define USE_LUT
 
#define SINCN            3
#define DECIMATION_MAX 128
#ifdef PICO_BUILD
#define FILTER_GAIN     Param->Gain
#else
#define FILTER_GAIN     16
#endif
 
#define HTONS(A) ((((uint16_t)(A) & 0xff00) >> 8) | \
                 (((uint16_t)(A) & 0x00ff) << 8))
#define RoundDiv(a, b)    (((a)>0)?(((a)+(b)/2)/(b)):(((a)-(b)/2)/(b)))
#define SaturaLH(N, L, H) (((N)<(L))?(L):(((N)>(H))?(H):(N)))
 
 
/* Types ---------------------------------------------------------------------*/
 
typedef struct {
  /* Public */
  float LP_HZ;
  float HP_HZ;
  uint16_t Fs;
  uint8_t In_MicChannels;
  uint8_t Out_MicChannels;
  uint8_t Decimation;
  uint8_t MaxVolume;
#ifdef PICO_BUILD
  uint8_t Gain;
#endif
  /* Private */
  uint32_t Coef[SINCN];
  uint16_t FilterLen;
  int64_t OldOut, OldIn, OldZ;
  uint16_t LP_ALFA;
  uint16_t HP_ALFA;
  uint16_t bit[5];
  uint16_t byte;
} TPDMFilter_InitStruct;
 
 
/* Exported functions ------------------------------------------------------- */
 
void Open_PDM_Filter_Init(TPDMFilter_InitStruct *init_struct);
void Open_PDM_Filter_64(uint8_t* data, uint16_t* data_out, uint16_t mic_gain, TPDMFilter_InitStruct *init_struct);
void Open_PDM_Filter_128(uint8_t* data, uint16_t* data_out, uint16_t mic_gain, TPDMFilter_InitStruct *init_struct);
 
#ifdef __cplusplus
}
#endif
 
#endif // __OPENPDMFILTER_H
 
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
 
