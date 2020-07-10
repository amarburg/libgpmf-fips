
#include <memory>
#include <string>
#include <fstream>

using std::string;
using std::ifstream;

#include <libg3logger/g3logger.h>
#include <CLI/CLI.hpp>

#include "gpmf-parser/GPMF_parser.h"

void PrintGPMF(GPMF_stream *ms);


int main(int argc, char *argv[]) {

  libg3logger::G3Logger logger("gpmf_parser");

  CLI::App app{"Simple GPMF Parser"};

  int verbosity = 0;
  app.add_flag("-v", verbosity, "Set logging level to DEBUG");

  string inputFilename("");
  app.add_option("input", inputFilename, "Filename to read sonar data from.");

  CLI11_PARSE(app, argc, argv);

  if( verbosity > 0 ) {
    logger.stderrHandle->call( &ColorStderrSink::setThreshold, DEBUG );
  }
  // } else if (verbosity > 1 ) {
  //   logger.stderrHandle->call( &ColorStderrSink::setThreshold, DEBUG );
  // }

  // Open to the end to read the file length
  ifstream input( inputFilename, std::ios::binary  | std::ios::ate );
  if( !input.is_open() ) {
    LOG(WARNING) << "Could not open file " << inputFilename;
    exit(-1);
  }

  auto size = input.tellg();

  LOG(WARNING) << "Opening: " << inputFilename << " of size " << size;
  CHECK( size > 0 ) << "Got a bad size " << size;

  std::string data(size, '\0');
  input.seekg(0);
  input.read( &data[0], size );

  GPMF_stream gs;
  auto err = GPMF_Init( &gs, (uint32_t *)data.c_str(), size );

  CHECK( err == GPMF_OK ) << "Error while initializing GPMF: " << err;

  do {
    PrintGPMF(&gs);  // printf current GPMF KLV
  } while (GPMF_OK == GPMF_Next(&gs, GPMF_RECURSE_LEVELS));

  return 0;
}
