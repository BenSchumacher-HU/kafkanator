#ifndef QUOTATION_DB_H
#define QUOTATION_DB_H

#include <cereal/archives/json.hpp>
#include <cereal/types/list.hpp>

#include <string>
#include <list>


class Quotation {
  friend class cereal::access;
  
  public:
    Quotation(){};
    Quotation(unsigned int id, std::string author, std::string excerpt, std::string comment);
    ~Quotation();
    
    const unsigned int GetId() const;
    const std::string GetAuthor() const;
    const std::string GetExcerpt() const;
    const std::string GetComment() const;
    
  private:
    unsigned int id_;
    std::string author_;
    std::string excerpt_;
    std::string comment_;
    
    template<class Archive>
    void serialize(Archive& archive) {
      archive(CEREAL_NVP(id_), CEREAL_NVP(author_), CEREAL_NVP(excerpt_), CEREAL_NVP(comment_));
    }
};


class QuotationDB {
  friend class cereal::access;
  
  public:                              
    QuotationDB();                      
    ~QuotationDB();
    
    unsigned int AddQuotation(std::string author, std::string excerpt, std::string comment);
    bool RemoveQuotation(unsigned int id);
    
    void ListAllQuotations() const;
    
    static void WriteIntoFile(QuotationDB db, std::string path);
    static QuotationDB LoadFromFile(std::string path);


  private:
    unsigned int idCounter_;
    std::list<Quotation> quotationSet_;
    
    template<class Archive>
    void serialize(Archive& archive) {
      archive(CEREAL_NVP(idCounter_), CEREAL_NVP(quotationSet_)); 
    }
};

#endif // QUOTATIONDB_H
