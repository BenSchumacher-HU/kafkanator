#include "make_db.h"


int main( int argc, const char* argv[] ) {
  PhotoDB pDB;
  pDB.AddPhoto("/home/bschumacher/Documents/deutschlandstipendium/Projekt/Fotodatenbank/8566082561_57a0dd0dfd_b.jpg", "");
  pDB.AddPhoto("/home/bschumacher/Documents/deutschlandstipendium/Projekt/Fotodatenbank/9103141654_f78bc1716f_k.jpg", "");
  pDB.AddPhoto("/home/bschumacher/Documents/deutschlandstipendium/Projekt/Fotodatenbank/9648179517_130f37f656_k.jpg", "");
  pDB.AddPhoto("/home/bschumacher/Documents/deutschlandstipendium/Projekt/Fotodatenbank/14691236072_bd9a66cfc3_h.jpg", "");
  pDB.AddPhoto("/home/bschumacher/Documents/deutschlandstipendium/Projekt/Fotodatenbank/14937740692_ec2c6b5922_o.jpg", "");
  pDB.AddPhoto("/home/bschumacher/Documents/deutschlandstipendium/Projekt/Fotodatenbank/15599593585_b0726850cf_k.jpg", "");
  PhotoDB::WriteIntoFile(pDB,"pDB.out");
  pDB.ListAllPhotos();
  
  
  QuotationDB qDB;
  qDB.AddQuotation("Franz Kafka", "Sein Gesicht erschien etwas steif durch einen großen, weißen Vollbart, der erst auf der Brust in seidenartige Ringel ausging.", "");
  qDB.AddQuotation("Franz Kafka", "Sie war sehr dick, ihr Leib schaukelte sich, aber ihr Gesicht hatte eine, natürlich im Verhältnis, fast zarte Bildung.", "");
  qDB.AddQuotation("Franz Kafka", "Sie hatte ein rundes, gleichmäßiges Gesicht, nur die Stirn war ungewöhnlich hoch, aber das konnte auch vielleicht nur an der Frisur liegen, die ihr nicht recht paßte.", "");
  qDB.AddQuotation("Franz Kafka", "[I]ch bestätige bloß nach deinem Gesicht, daß du ein ausgegorener Lump bist.", "");
  qDB.AddQuotation("Franz Kafka", "Sein dunkles, glatt rasiertes, peinlich reines, von roh ausgearbeiteten Muskeln gebildetes Gesicht sah stolz und respekteinflößend aus. Der grelle Schein seiner jetzt immer etwas zusammengezogenen Augen überraschte.", "");
  qDB.AddQuotation("Franz Kafka", "[Das Mädchen] hatte ein puppenförmig gerundetes Gesicht, nicht nur die bleichen Wangen und das Kinn verliefen rund, auch die Schläfen und die Stirnränder.", "");
  qDB.AddQuotation("Franz Kafka", "[S]ah er aber auf, dann erblickte er ein zu diesem dicken Körper gar nicht passendes trockenes, knochiges Gesicht mit starker, seitlich gedrehter Nase, das sich über ihn hinweg mit dem anderen Wächter verständigte.", "");
  qDB.AddQuotation("Franz Kafka", "Er war braun gebrannt wie ein Matrose und hatte ein wildes, frisches Gesicht.", "");
  qDB.AddQuotation("Franz Kafka", "Er hatte nun ihr Gesicht nahe vor sich, es hatte den strengen Ausdruck, wie ihn manche Frauen gerade in ihrer schönsten Jugend haben.", "");
  qDB.AddQuotation("Franz Kafka", "Es war ein großer, etwa vierzigjähriger Mann mit braungebranntem, fleischigem Gesicht.", "");
  QuotationDB::WriteIntoFile(qDB,"qDB.out");
  qDB.ListAllQuotations();
  
  
  MappingDB mDB {&pDB,&qDB};
  mDB.AddMapping(1,1,51);
  MappingDB::WriteIntoFile(mDB,"mDB.out");
  mDB.ListAllMappings();
}
