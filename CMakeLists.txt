# get IDF version for comparison
set(idf_version "${IDF_VERSION_MAJOR}.${IDF_VERSION_MINOR}")

# set conversion sources
set(srcs
  printer_ctrl.c
  printer_moto.c
  printer_heat.c
  )

set(include_dirs
  ./include
  )

set(COMPONENT_REQUIRES driver)

idf_component_register(
  SRCS ${srcs}
  INCLUDE_DIRS ${include_dirs}
  REQUIRES ${COMPONENT_REQUIRES}  # due to include of driver/gpio.h in esp_camera.h
)
