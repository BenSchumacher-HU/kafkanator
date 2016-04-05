#include "quotation_db.h"

#include <iostream>
#include <fstream>


Quotation::Quotation(unsigned int id, std::string author, std::string excerpt, std::string comment) {
  this->id_ = id;
  this->author_ = author;
  this->excerpt_ = excerpt;
  this->comment_ = comment;
}


Quotation::~Quotation() {}

    
const unsigned int Quotation::GetId() const{
  return this->id_;
}


const std::string Quotation::GetAuthor() const {
  return this->author_;
}


const std::string Quotation::GetExcerpt() const {
  return this->excerpt_;
}


const std::string Quotation::GetComment() const {
  return this->comment_;
}


QuotationDB::QuotationDB() : idCounter_(0) {}


QuotationDB::~QuotationDB(){}

    
unsigned int QuotationDB::AddQuotation(std::string author, std::string excerpt, std::string comment="") {
  Quotation tmp(++idCounter_, author, excerpt, comment);
  quotationSet_.push_back(tmp);
  return tmp.GetId();
}


bool QuotationDB::RemoveQuotation(unsigned int id) {
  for (auto it = quotationSet_.begin(); it != quotationSet_.end(); ++it) {
    if(it->GetId() == id) {
      quotationSet_.erase(it);
      return true;
    }
  }
  return false;
}

void QuotationDB::ListAllQuotations() const {
  for(auto q : quotationSet_)
    std::cout << "ID: " << q.GetId() << ", author: " << q.GetAuthor() << ", excerpt: " << q.GetExcerpt() << ", comment: " << q.GetComment() << std::endl;
}


void QuotationDB::WriteIntoFile(QuotationDB db, std::string path) { 
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


QuotationDB QuotationDB::LoadFromFile(std::string path) {
  std::ifstream t(path);
  std::stringstream ss;
  ss << t.rdbuf();

  //std::cout << "Reading:" << std::endl;
  //std::cout << ss.str() << std::endl;

  cereal::JSONInputArchive iarchive(ss);
  QuotationDB ret {};
  iarchive(ret);
  
  return ret;
}
