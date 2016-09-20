
set(BOOST_FLAGS -lboost_program_options -lboost_log -lpthread  -lboost_thread -lboost_system -lboost_filesystem)


add_compile_options(-DBOOST_LOG_DYN_LINK)

set(LIB_FILES photo_db.cpp  quotation_db.cpp mapping_db.cpp)

add_library(db_lib ${LIB_FILES})

target_include_directories(db_lib PUBLIC ${CEREAL_DIR})


add_executable(make_db make_db.cpp)
target_link_libraries(make_db db_lib ${BOOST_FLAGS})




SET(GCC_COVERAGE_LINK_FLAGS "pkg-config opencv --cflags --libs ")


find_package(OpenCV REQUIRED)
add_executable(db_keeper db_keeper.cpp)
target_link_libraries(db_keeper db_lib ${BOOST_FLAGS} ${OpenCV_LIBS})


add_executable(survey survey.cpp)
target_link_libraries(survey db_lib ${BOOST_FLAGS} ${OpenCV_LIBS} )
