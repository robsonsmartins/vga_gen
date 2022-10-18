// ---------------------------------------------------------------------------
// USB EPROM/Flash Programmer
//
// Copyright (2022) Robson Martins
//
// This work is licensed under a Creative Commons Attribution-NonCommercial-
// ShareAlike 4.0 International License.
// ---------------------------------------------------------------------------
/** 
 * @defgroup Firmware Firmware Project
 * @brief    Firmware project for USB EPROM/Flash Programmer.
 */
// ---------------------------------------------------------------------------
/** 
 * @ingroup Firmware
 * @file main.cpp
 * @brief Implementation of the Main Routine.
 *  
 * @author Robson Martins (https://www.robsonmartins.com)
 */
// ---------------------------------------------------------------------------

#include "hardware/gpio.h"
#include "circuits/74hc595.hpp"
#include "hal/multicore.hpp"

/**
 * @brief Main routine.
 * @return Error code (zero if success).
 */
int main();

// ---------------------------------------------------------------------------


#define V_SYNC 0
#define H_SYNC 1

int main() {
    HC595 vga1(5, 2, 3, 4, 0xFF, 40);
    vga1.clear();
    vga1.outputEnable();

    gpio_init(V_SYNC);
    gpio_init(H_SYNC);
    gpio_set_dir(V_SYNC, GPIO_OUT);
    gpio_set_dir(H_SYNC, GPIO_OUT);
    gpio_put(V_SYNC, true);
    gpio_put(H_SYNC, true);


    while (true) {

        uint16_t rgb = 0;

        for (uint16_t line = 0; line < 525; line++) {
            if (line == 0) { gpio_put(V_SYNC, false); }
            if (line == 3) { gpio_put(V_SYNC, true); }
            gpio_put(H_SYNC, false);
            MultiCore::nsleep(3810);
            gpio_put(H_SYNC, true);
            //MultiCore::nsleep(27890);
            vga1.writeWord(rgb);
            rgb++;
            vga1.writeWord(rgb);
            rgb++;
            MultiCore::nsleep(4890);
        }
    }

}

/*
std::queue<int> buffer;

void sleep_ns(uint32_t nsec) {
    busy_wait_at_least_cycles((nsec / 8) - 3);
}

void second_core_entry(MultiCore& core) {
    HC595 vga1(5, 2, 3, 4, 0xFF, 1);

    vga1.clear();
    vga1.outputEnable();
    //vga1.writeByte(0b11111);
    uint16_t rgb = 0;
    
    while (!core.isStopRequested()) {
        if (!buffer.empty()) {
            core.lock();
            buffer.pop();
            core.unlock();
            vga1.writeWord(rgb);
            rgb++;
        }
    }
}

int main() {
    gpio_init(V_SYNC);
    gpio_init(H_SYNC);
    gpio_set_dir(V_SYNC, GPIO_OUT);
    gpio_set_dir(H_SYNC, GPIO_OUT);
    gpio_put(V_SYNC, true);
    gpio_put(H_SYNC, true);

    MultiCore multicore(second_core_entry);
    multicore.launch();

    while (true) {
        for (uint16_t line = 0; line < 525; line++) {
            if (line == 0) { gpio_put(V_SYNC, false); }
            if (line == 3) { gpio_put(V_SYNC, true); }
            gpio_put(H_SYNC, false);
            sleep_ns(3810);
            gpio_put(H_SYNC, true);
            multicore.lock();
            buffer.push(1);
            multicore.unlock();
            sleep_ns(27890);
        }
    }

    return 0;
}
*/
