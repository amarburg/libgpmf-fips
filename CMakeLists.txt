cmake_minimum_required(VERSION 3.5)

if( FIPS_CONFIG AND NOT FIPS_IMPORT )
	cmake_minimum_required(VERSION 3.5)

	get_filename_component(FIPS_ROOT_DIR "../fips" ABSOLUTE)
	include("${FIPS_ROOT_DIR}/cmake/fips.cmake")

	fips_setup(PROJECT serdp_common)

else()
  find_package(catkin QUIET)
endif()

#list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

## C++ flags applied to all builds
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if (FIPS_CONFIG)

	fips_begin_module( gpmf )
		fips_src( thirdparty/gpmf-write/)
		fips_src( thirdparty/gpmf-parser/)


	  fips_include_directories(
			${CMAKE_SOURCE_DIR}/thirdparty
	 	)
	fips_end_module()


	if( NOT FIPS_IMPORT )

		fips_begin_app( parser-demo cmdline )
		  fips_src( thirdparty/gpmf-parser/demo/ )
		  fips_deps( gpmf )
		fips_end_app()

		fips_begin_app( writer-demo cmdline )
		  fips_src( thirdparty/gpmf-write/demo/ )
		  fips_deps( gpmf )
		fips_end_app()

		# Tools not quite ready yet...
	  add_subdirectory("tools/")
		#add_subdirectory("demo/")

		if( FIPS_UNITTESTS )
				 gtest_begin( gpmf )
				     fips_src( test/unit/ )
				     fips_deps( gpmf )
				gtest_end()
		endif()

	  fips_finish()
	endif()

else()
    project(gpmf)

    find_package(catkin REQUIRED COMPONENTS)
     
    catkin_package(
        LIBRARIES gpmf_LIB
        INCLUDE_DIRS thirdparty

    )

    include_directories(
      ${catkin_INCLUDE_DIRS}
      thirdparty
      )

    file(GLOB gpmf_SRCS
     	  thirdparty/gpmf-write/*.c
          thirdparty/gpmf-parser/*.c
    )

    add_library(gpmf_LIB ${gpmf_SRCS})
    target_link_libraries(gpmf_LIB ${catkin_LIBRARIES})


    install(TARGETS gpmf_LIB
          ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
          LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
          RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})

    ## Install headers
    install(DIRECTORY thirdparty/
        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
        FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h"
        PATTERN ".git" EXCLUDE)
endif()
