#include "mapping_db.h"

#include <iostream>
#include <fstream>


Mapping::Mapping(unsigned int idPhoto, unsigned int idQuotation, unsigned int precision) {
  this->idPhoto_ = idPhoto;
  this->idQuotation_ = idQuotation;
  this->precision_ = precision;
}


Mapping::~Mapping() {}


/*
const unsigned int Mapping::GetId() const{
  return this->id_;
}
*/


const unsigned int Mapping::GetIdPhoto() const {
  return this->idPhoto_;
}


const unsigned int Mapping::GetIdQuotation() const {
  return this->idQuotation_;
}


const unsigned int Mapping::GetPrecision() const {
  return this->precision_;
}



MappingDB::MappingDB() : idCounter_(0), pDB_(new PhotoDB()), qDB_(new QuotationDB()) {}
  


MappingDB::MappingDB(PhotoDB* pDB, QuotationDB* qDB) : idCounter_(0), pDB_(pDB), qDB_(qDB) {}


MappingDB::~MappingDB(){}

    
bool MappingDB::AddMapping(unsigned int idPhoto, unsigned int idQuotation, unsigned int precision = 100) {
  /// \todo Check if id exist
  if(true) {
    Mapping tmp(idPhoto, idQuotation, precision);
    mappingSet_.push_back(tmp);
    return true;
  }
  else {
    return false;
  }
}


void MappingDB::ListAllMappings() const {
  for(auto m : mappingSet_)
    std::cout << "Photo-ID: " << m.GetIdPhoto() << ", Quotation-ID: " << m.GetIdQuotation() << ", precision: " << m.GetPrecision() << std::endl;
}


void MappingDB::WriteIntoFile(MappingDB db, std::string path) { 
  std::stringstream ss;
  cereal::JSONOutputArchive oarchive(ss);
  oarchive(db);
  ss << "\n}";
  
  //std::cout << "Writting:" << std::endl;
  //std::cout << ss.str() << std::endl << std::endl;
  
  std::ofstream outputFile;
  outputFile.open (path);
  outputFile << ss.str();
  outputFile.close();
}


MappingDB MappingDB::LoadFromFile(std::string path) {
  std::ifstream t(path);
  std::stringstream ss;
  ss << t.rdbuf();

  //std::cout << "Reading:" << std::endl;
  //std::cout << ss.str() << std::endl;

  cereal::JSONInputArchive iarchive(ss);
  MappingDB  ret {};
  iarchive(ret);
  
  return ret;
}
