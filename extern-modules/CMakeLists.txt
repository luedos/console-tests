cmake_minimum_required (VERSION 3.10)
project (exturn-libraries)

set(ASMJIT_STATIC TRUE)

add_subdirectory(asmjit)
add_subdirectory(distorm)
add_subdirectory(lodepng)
add_subdirectory(lzo)
add_subdirectory(pe-bliss)
#add_subdirectory(xlslib)
add_subdirectory(xlnt)
add_subdirectory(neargye)