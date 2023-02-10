cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(Raytracing)


option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)


if(WITH_GEANT4_UIVIS)

  find_package(Geant4 REQUIRED ui_all vis_all)

else()

  
  find_package(Geant4 REQUIRED)

endif()



include(${Geant4_USE_FILE})


file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)



add_executable(sim sim.cc ${sources} ${headers})

target_link_libraries(sim ${Geant4_LIBRARIES})

set(EXAMPLEB2A_SCRIPTS
  run.mac
  vis.mac
  )

foreach(_script ${EXAMPLEB2A_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()



install(TARGETS sim DESTINATION bin)
