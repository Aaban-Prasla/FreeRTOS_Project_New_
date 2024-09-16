//
// Created by Keijo Länsikunnas on 10.9.2024.
//

#ifndef RP2040_FREERTOS_IRQ_PICOI2C_H
#define RP2040_FREERTOS_IRQ_PICOI2C_H
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "hardware/i2c.h"
#include "Fmutex.h"

class PicoI2C {
public:
    PicoI2C(int busnr);
    uint write(uint8_t addr, const uint8_t *buffer, uint length);
    uint read(uint8_t addr, uint8_t *buffer, uint length);
    uint transaction(uint8_t addr, const uint8_t *wbuffer, uint wlength, uint8_t *rbuffer, uint rlength);
private:
    void isr();
    i2c_inst *i2c;
    int irqn;
    TaskHandle_t task;
    Fmutex access;

    static void i2c0_irq(void);
    static void i2c1_irq(void);
    static PicoI2C *i2c0_instance;
    static PicoI2C *i2c1_instance;
};


#endif //RP2040_FREERTOS_IRQ_PICOI2C_H