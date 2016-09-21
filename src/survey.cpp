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


#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/progress.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>



namespace po = boost::program_options;

namespace fs = boost::filesystem;

using namespace cv;

int main( int argc, const char* argv[] ) {
  
  
  boost::program_options::options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "produce help message")
    //("inputfile,i", po::value<vector<string>>(), "Inputfile")
    ("input-file,i", po::value< std::vector<std::string> >(),   "Input files in the order: photo, quoation, mapping")
    //("picture-directory,p", po::value<std::string>(),   "Input picture directory")
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
  
  PhotoDB pDB = PhotoDB::LoadFromFile(vm["input-file"].as<std::vector<std::string>>().at(0));
//   pDB2.ListAllPhotos();
  
  
  QuotationDB qDB = QuotationDB::LoadFromFile(vm["input-file"].as<std::vector<std::string>>().at(1));
//   qDB2.ListAllQuotations();
  
  MappingDB mDB = MappingDB::LoadFromFile(vm["input-file"].as<std::vector<std::string>>().at(2));
//   mDB2.ListAllMappings();

  
  std::list<Photo> tmpFiles = pDB.GetPhotoList();
  std::vector<Photo> files {std::make_move_iterator(std::begin(tmpFiles)), std::make_move_iterator(std::end(tmpFiles))};
  
  for(unsigned int counter = 0; counter < files.size(); ++counter) {
    Mat image;
    unsigned int fileIndex;
    std::string filePath;
    for(unsigned int counter = 0; counter < files.size(); ++counter) {
      // Showing Images      
      srand (time(NULL));
      fileIndex = rand() % files.size();
      filePath = files[fileIndex].GetPath();
      image = imread(filePath, CV_LOAD_IMAGE_COLOR);

      if(!image.data) {
          std::cout <<  "Could not open or find the image at path" << filePath << std::endl ;
          return EXIT_FAILURE;
      }
      std::cout <<  "Showing File at " << filePath << std::endl ;

      namedWindow("Display window", cv::WINDOW_AUTOSIZE );// Create a window for display.
      imshow("Display window", image );                   // Show our image inside it.
      
      
      for(unsigned int i = 1; i <= 3; i++) {
        std::cout << "(" << i << "): " << qDB.GetRandomQuotation().GetExcerpt() <<std::endl;
      }
      
      waitKey(0);
      int n = 0;
      while(n < 1 || n > 3) {
        std::cout <<  "Type a number beween 1 und 3 to choose the fitting quoation" << std::endl;
        std::cin >> n;
      }
      std::cout <<  "You picked " << n << std::endl;
      destroyWindow( "Display window");
    }
  }
}
