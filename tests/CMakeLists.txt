file(GLOB sources CONFIGURE_DEPENDS "*.cpp")
foreach(source ${sources})
  get_filename_component(name ${source} NAME_WE)
  add_executable(${name} ${source})
endforeach()

target_link_libraries(test_utf PRIVATE utf8cpp)

target_link_libraries(test_minibpe PUBLIC benchmark::benchmark)