
fips_begin_app( gpmf_parser cmdline )
  fips_files( gpmf_parser.cpp GPMF_print.cpp )

  fips_deps( gpmf g3logger )

  fips_include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
  )

fips_end_app()
