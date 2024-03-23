# set conversion sources
set(srcs
  printer_moto.c
  printer_heat.c
  )

set(include_dirs
  ./include
  )

set(COMPONENT_REQUIRES driver)  # due to use SPI and GPIO

idf_component_register(
  SRCS ${srcs}
  INCLUDE_DIRS ${include_dirs}
  REQUIRES ${COMPONENT_REQUIRES}
)
