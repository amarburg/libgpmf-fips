cmake_minimum_required(VERSION 3.5)
if( NOT FIPS_IMPORT )
	cmake_minimum_required(VERSION 3.5)

	get_filename_component(FIPS_ROOT_DIR "../fips" ABSOLUTE)
	include("${FIPS_ROOT_DIR}/cmake/fips.cmake")

	fips_setup(PROJECT gpmf)
endif()

#list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

## C++ flags applied to all builds
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

fips_begin_module( gpmf )

	#fips_src( lib *.cpp )
	#fips_src( thirdparty/gpmf-write/  NO_RECURSE )
	#fips_src( thirdparty/gpmf-parser/ NO_RECURSE )
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
