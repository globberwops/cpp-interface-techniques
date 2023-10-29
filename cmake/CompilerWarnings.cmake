include_guard()

function(ADD_COMPILER_WARNINGS TARGET)
  set(COMPILER_WARNINGS)
  if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    list(
      APPEND
      COMPILER_WARNINGS
      /w14242
      /w14254
      /w14263
      /w14265
      /w14287
      /w14296
      /w14311
      /w14545
      /w14546
      /w14547
      /w14549
      /w14555
      /w14619
      /w14640
      /w14826
      /w14905
      /w14906
      /w14928
      /W4
      /we4289
      /WX)
  elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    list(
      APPEND
      COMPILER_WARNINGS
      -pedantic
      -Wall
      -Wcast-align
      -Wconversion
      -Wdouble-promotion
      -Wextra
      -Wformat=2
      -Wimplicit-fallthrough
      -Wmisleading-indentation
      -Wnon-virtual-dtor
      -Wnull-dereference
      -Wold-style-cast
      -Woverloaded-virtual
      -Wshadow
      -Wsign-conversion
      -Wunused
      -Werror)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
      list(APPEND COMPILER_WARNINGS -Wduplicated-branches -Wduplicated-cond -Wlogical-op -Wuseless-cast)
    endif()
  endif()

  target_compile_options(${TARGET} PRIVATE ${COMPILER_WARNINGS})
endfunction()
