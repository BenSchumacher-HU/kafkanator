#ifndef MAPPING_DB_H
#define MAPPING_DB_H

#include <cereal/archives/json.hpp>
#include <cereal/types/list.hpp>

#include <string>
#include <list>

#include "quotation_db.h"
#include "photo_db.h"


class Mapping {
  friend class cereal::access;
  
  public:
    Mapping(){}
    Mapping(unsigned int idPhoto, unsigned int idQuotation, unsigned int precision);
    ~Mapping();
    
    //const unsigned int GetId() const;
    const unsigned int GetIdPhoto() const;
    const unsigned int GetIdQuotation() const;
    const unsigned int GetPrecision() const;
    
  private:
    //unsigned int id_;
    unsigned int idPhoto_;
    unsigned int idQuotation_;
    unsigned int precision_;
    
    template<class Archive>
    void serialize(Archive& archive) {
      archive(CEREAL_NVP(idPhoto_), CEREAL_NVP(idQuotation_), CEREAL_NVP(precision_));
    }
};


class MappingDB {
  friend class cereal::access;
  
  public:
    MappingDB();
    MappingDB(PhotoDB* pDB, QuotationDB* qDB);
    ~MappingDB();
    
    bool AddMapping(unsigned int idPhoto, unsigned int idQuotation, unsigned int precision);
    //bool RemovePhoto(unsigned int id);
    //const std::list<unsigned int> GetIdList() const;
    
    void ListAllMappings() const;
    
    static void WriteIntoFile(MappingDB db, std::string path);    
    static MappingDB LoadFromFile(std::string path);
    
  private:
    unsigned int idCounter_;
    PhotoDB* pDB_;
    QuotationDB* qDB_;
    std::list<Mapping>  mappingSet_;
    
    template<class Archive>
    void serialize(Archive& archive) {
      archive(CEREAL_NVP(idCounter_), CEREAL_NVP(mappingSet_)); 
    }
};

#endif // MAPPING_DB_H
