#include "photo_db.h"
#include "quotation_db.h"
#include "mapping_db.h"



int main( int argc, const char* argv[] ) {
  
  PhotoDB pDB;
  pDB.AddPhoto("testpath", "testcomment");
  pDB.ListAllPhotos();
  PhotoDB::WriteIntoFile(pDB,"pDB.out");
  
  PhotoDB pDB2 = PhotoDB::LoadFromFile("pDB.out");
  pDB2.ListAllPhotos();
  
  
  QuotationDB qDB;
  qDB.AddQuotation("testauthor", "testexcerpt", "testcomment");
  qDB.ListAllQuotations();
  QuotationDB::WriteIntoFile(qDB,"qDB.out");
  
  QuotationDB qDB2 = QuotationDB::LoadFromFile("qDB.out");
  qDB2.ListAllQuotations();
  
  
  MappingDB mDB {&pDB,&qDB};
  mDB.AddMapping(1,1,51);
  MappingDB::WriteIntoFile(mDB,"mDB.out");
  mDB.ListAllMappings();
  
  MappingDB mDB2 = MappingDB::LoadFromFile("mDB.out");
  mDB2.ListAllMappings();


  /*
  std::stringstream ss;
  //ss << "{\"value0\": {\"id_\": 10,\"path_\": \"p1\",\"comment_\": \"c1\"}";
  
  {
    cereal::JSONOutputArchive oarchive(ss);
    
    Photo p {10, "p1", "c1"};
    
    oarchive(p);
  }
  
  //std::cout << ss.str() << std::endl;
  
  {
    cereal::JSONInputArchive iarchive(ss);
    
    Photo p2 {};
    
    iarchive(p2);
  }
  
  //db = PhotoDB::LoadFromFile("keks");
  
  //db.ListAllPhotos();
  */
}