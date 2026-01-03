#ifndef BUZZER_H
#define BUZZER_H

#include <stdint.h>

// Proje kisitlamalarina göre frekans tanimlari [cite: 96, 100]
#define FREQ_TURN_VALID    1000  // Geçerli dönüs sesi (Hz)
#define FREQ_TURN_INVALID  2500  // Geçersiz dönüs sesi (Hz)
#define FREQ_LOST_1        400   // Oyun kaybetme melodisi ton 1
#define FREQ_LOST_2        300
#define FREQ_LOST_3        200

// Fonksiyon Prototipleri
void Buzzer_Init(void);
void Buzzer_Play(uint32_t freq, uint32_t duration_ms);
void Buzzer_PlayGameOver(void);

#endif