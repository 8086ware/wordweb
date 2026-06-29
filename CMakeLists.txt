cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 23)

project(wordweb)

add_executable(wordweb
	"src/main.cpp"
)

find_package(wxWidgets REQUIRED COMPONENTS net core base)

if(wxWidgets_USE_FILE) # not defined in CONFIG mode
    include(${wxWidgets_USE_FILE})
endif()

target_link_libraries(wordweb PUBLIC ${wxWidgets_LIBRARIES})
