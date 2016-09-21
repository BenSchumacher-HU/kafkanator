#include "photo_db.h"

#include <iostream>
#include <fstream>


Photo::Photo(unsigned int id, std::string path, std::string comment) {
  this->id_ = id;
  this->path_ = path;
  this->comment_ = comment;
}


Photo::~Photo() {}

    
const unsigned int Photo::GetId() const{
  return this->id_;
}


const std::string Photo::GetPath() const {
  return this->path_;
}


const std::string Photo::GetComment() const {
  return this->comment_;
}



PhotoDB::PhotoDB() : idCounter_(0) {}


PhotoDB::~PhotoDB(){}

    
unsigned int PhotoDB::AddPhoto(std::string quotation, std::string comment="") {
  Photo tmp(++idCounter_, quotation, comment);
  photoSet_.push_back(tmp);
  return tmp.GetId();
}


bool PhotoDB::RemovePhoto(unsigned int id) {
  for (auto it = photoSet_.begin(); it != photoSet_.end(); ++it) {
    if(it->GetId() == id) {
      photoSet_.erase(it);
      return true;
    }
  }
  return false;
}

void PhotoDB::ListAllPhotos() const {
  for(auto p : photoSet_)
    std::cout << "ID: " << p.GetId() << ", comment: " << p.GetComment() << ", path: " << p.GetPath() << std::endl;
}

std::list<Photo> PhotoDB::GetPhotoList() const {
  return photoSet_;
}


void PhotoDB::WriteIntoFile(PhotoDB db, std::string path) { 
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


PhotoDB PhotoDB::LoadFromFile(std::string path) {
  std::ifstream t(path);
  std::stringstream ss;
  ss << t.rdbuf();

  //std::cout << "Reading:" << std::endl;
  //std::cout << ss.str() << std::endl;

  cereal::JSONInputArchive iarchive(ss);
  PhotoDB ret {};
  iarchive(ret);
  
  return ret;
}
