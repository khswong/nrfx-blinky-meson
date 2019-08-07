project('blink', 'c')

nrfx_include = [
  'nrfx',
  'nrfx/mdk',
  'nrfx/hal',
  'nrfx/drivers',
  'nrfx/drivers/include',
  'CMSIS/CMSIS/Include',
]

nrfx_sources = files([
  'nrfx/mdk/gcc_startup_nrf51.S',
  'nrfx/mdk/system_nrf51.c',
  'nrfx/drivers/src/nrfx_adc.c',
  'nrfx/drivers/src/nrfx_clock.c',
  'nrfx/drivers/src/nrfx_comp.c',
  'nrfx/drivers/src/nrfx_dppi.c',
  #'nrfx/drivers/src/nrfx_gpiote.c',
  'nrfx/drivers/src/nrfx_i2s.c',
  'nrfx/drivers/src/nrfx_lpcomp.c',
  'nrfx/drivers/src/nrfx_nfct.c',
  'nrfx/drivers/src/nrfx_pdm.c',
  'nrfx/drivers/src/nrfx_power.c',
  'nrfx/drivers/src/nrfx_ppi.c',
  'nrfx/drivers/src/nrfx_pwm.c',
  'nrfx/drivers/src/nrfx_qdec.c',
  'nrfx/drivers/src/nrfx_qspi.c',
  'nrfx/drivers/src/nrfx_rng.c',
  'nrfx/drivers/src/nrfx_rtc.c',
  'nrfx/drivers/src/nrfx_saadc.c',
  'nrfx/drivers/src/nrfx_spi.c',
  'nrfx/drivers/src/nrfx_spim.c',
  'nrfx/drivers/src/nrfx_spis.c',
  'nrfx/drivers/src/nrfx_swi.c',
  'nrfx/drivers/src/nrfx_systick.c',
  'nrfx/drivers/src/nrfx_timer.c',
  'nrfx/drivers/src/nrfx_twi.c',
  'nrfx/drivers/src/nrfx_twim.c',
  'nrfx/drivers/src/nrfx_twis.c',
  'nrfx/drivers/src/nrfx_uart.c',
  'nrfx/drivers/src/nrfx_uarte.c',
  'nrfx/drivers/src/nrfx_usbd.c',
  'nrfx/drivers/src/nrfx_usbd_errata.h',
  'nrfx/drivers/src/nrfx_wdt.c',
  'nrfx/drivers/src/prs/nrfx_prs.c',
])

# For some reason _start from newlib's crt0 causes a hard fault. All it does is
# clear BSS, which the nrf linker script can do for us. Turn that on then just
# jump to main instead of _start.
c_args = [
  '-DNRF51',
  '-D__STARTUP_CLEAR_BSS=1',
  '-D__START=main',
]

link_args = [
  '-Wl,-L' + join_paths(meson.current_source_dir(), 'nrfx/mdk'),
  '-Wl,-T' + join_paths(meson.current_source_dir(), 'nrfx/mdk/nrf51_xxaa.ld'),
]

# nrfx needs to have the full project includes in order to see nrfx_config.h
# and nrfx_glue.h, so we just build with all the includes all the time.
project_include = include_directories(nrfx_include + ['include'])

nrfx = static_library('nrfx', nrfx_sources,
  c_args: c_args,
  include_directories: project_include,
)

blink_sources = [
  'src/blink.c',
]

blink = executable('blink.elf',
  blink_sources,
  include_directories: project_include,
  c_args: c_args,
  link_with: nrfx,
  link_args: link_args,
)
