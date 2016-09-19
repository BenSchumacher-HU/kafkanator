#include "photo_db.h"
#include "quotation_db.h"
#include "mapping_db.h"

#include "boost/program_options.hpp"

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/format.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/attributes/mutable_constant.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/attributes/mutable_constant.hpp>




namespace po = boost::program_options;

int main( int argc, const char* argv[] ) {
  
  
  boost::program_options::options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "produce help message")
    //("inputfile,i", po::value<vector<string>>(), "Inputfile")
    ("input-file,I", po::value< std::vector<std::string> >(),   "Input files in the order: photo, quoation, mapping")
    //("pfile,p", po::value<std::string>(), "Photo Inputfile")
    //("mfile,m ", po::value<std::string>(), "Mapping Inputfile")
  ;
  
  po::positional_options_description p;
  p.add("input-file", -1);

  po::variables_map vm;
  po::store(po::command_line_parser(argc, argv).
          options(desc).positional(p).run(), vm);
  po::notify(vm);
  
  if (vm.count("help")) {
    std::cout << desc;
    exit(EXIT_SUCCESS);
  }
  
  /*
  if (!vm.count("qfile") || !vm.count("pfile") || !vm.count("mfile")) {
    
  }
  */
  if (!vm.count("input-file") || vm["input-file"].as<std::vector<std::string>>().size() != 3) {
    std::cout << "All three input files are needed" << std::endl;
    exit(EXIT_SUCCESS);
  }
   
  
  PhotoDB pDB;  
  PhotoDB pDB2 = PhotoDB::LoadFromFile(vm["input-file"].as<std::vector<std::string>>().at(0));
  pDB2.ListAllPhotos();
  
  
  QuotationDB qDB;  
  QuotationDB qDB2 = QuotationDB::LoadFromFile(vm["input-file"].as<std::vector<std::string>>().at(1));
  qDB2.ListAllQuotations();
  
  MappingDB mDB {&pDB,&qDB};
  MappingDB mDB2 = MappingDB::LoadFromFile(vm["input-file"].as<std::vector<std::string>>().at(2));
  mDB2.ListAllMappings();
}

