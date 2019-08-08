This is a meson driven build of nrfx for the nRF51822. An example for blinking
an LED on the BBC micro:bit is included.

# Requirements

 - meson (tested with 0.49.2)
 - ninja (tested with 1.8.2)
 - GNU Arm Embedded Toolchain (tested with gcc-arm-none-eabi-8-2018-q4-major)

# Build

    git submodule init
    git submodule update
    meson --cross-file=cross_file.txt build
    ninja -C build

# Debug

    openocd -f /usr/share/openocd/scripts/interface/cmsis-dap.cfg \
            -f /usr/share/openocd/target/nrf51.cfg &

    arm-none-eabi-gdb build/blinky.elf
    target remote localhost:3333
    monitor reset halt
    load
    monitor reset
