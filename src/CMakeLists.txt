
set(BOOST_FLAGS -lboost_program_options -lboost_log -lpthread  -lboost_thread -lboost_system)


add_compile_options(-DBOOST_LOG_DYN_LINK)

set(LIB_FILES photo_db.cpp  quotation_db.cpp mapping_db.cpp)

add_library(db_lib ${LIB_FILES})

target_include_directories(db_lib PUBLIC ${CEREAL_DIR})


add_executable(test_main test_main.cpp)
target_link_libraries(test_main db_lib ${BOOST_FLAGS})

add_executable(db_keeper db_keeper.cpp)
target_link_libraries(db_keeper db_lib ${BOOST_FLAGS})
