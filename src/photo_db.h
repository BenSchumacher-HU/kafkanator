#ifndef PHOTO_DB_H
#define PHOTO_DB_H

#include <cereal/archives/json.hpp>
#include <cereal/types/list.hpp>

#include <string>
#include <list>


class Photo {
  friend class cereal::access;
  
  public:
    Photo(){}
    Photo(unsigned int id, std::string path, std::string comment);
    ~Photo();
    
    const unsigned int GetId() const;
    const std::string GetPath() const;
    const std::string GetComment() const;
    
  private:
    unsigned int id_;
    std::string path_;
    std::string comment_;
    
    template<class Archive>
    void serialize(Archive& archive) {
      archive(CEREAL_NVP(id_), CEREAL_NVP(path_), CEREAL_NVP(comment_));
    }
};


class PhotoDB {
  friend class cereal::access;
  
  public:        
    PhotoDB();
    ~PhotoDB();
    
    unsigned int AddPhoto(std::string quotation, std::string comment);
    bool RemovePhoto(unsigned int id);
    std::list<Photo> GetPhotoList() const;
    
    void ListAllPhotos() const;
    
    static void WriteIntoFile(PhotoDB db, std::string path);    
    static PhotoDB LoadFromFile(std::string path);
    
  private:
    unsigned int idCounter_;
    std::list<Photo>  photoSet_;
    
    template<class Archive>
    void serialize(Archive& archive) {
      archive(CEREAL_NVP(idCounter_), CEREAL_NVP(photoSet_)); 
    }
};

#endif // PHOTO_DB_H
