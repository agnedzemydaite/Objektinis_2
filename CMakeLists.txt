cmake_minimum_required(VERSION 3.25)
project(Studentai)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Versijos pasirinkimas
option(USE_VECTOR "Naudoti vektoriaus versiją" OFF)
option(USE_LIST "Naudoti sąrašo versiją" OFF)
option(USE_VECTOR_CLASS "Naudoti vektoriaus klasės versiją" OFF)

# Patikrina ar gerai pasirinkta versija
if(NOT USE_VECTOR AND NOT USE_LIST AND NOT USE_VECTOR_CLASS)
    message(FATAL_ERROR "Pasirinkite vieną versiją: -DUSE_VECTOR=ON arba -DUSE_LIST=ON arba -DUSE_VECTOR_CLASS=ON")
endif()

if(USE_VECTOR)
    file(GLOB SOURCE_FILES "vector_versija/*.cpp")
    set(INCLUDE_DIR "vector_versija")
elseif(USE_LIST)
    file(GLOB SOURCE_FILES "list_versija/*.cpp")
    set(INCLUDE_DIR "list_versija")
elseif(USE_VECTOR_CLASS)
    file(GLOB SOURCE_FILES "vector_class_versija/*.cpp")
    set(INCLUDE_DIR "vector_class_versija")
endif()

# Nenaudojame main testavimo programai
list(FILTER SOURCE_FILES EXCLUDE REGEX "main\\.cpp$")

# Pagrindinė programa
add_executable(Studentai ${SOURCE_FILES} ${INCLUDE_DIR}/main.cpp)
target_include_directories(Studentai PRIVATE ${INCLUDE_DIR})

# Google Test

enable_testing()

# Google Test biblioteka iš GitHub
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)
include(GoogleTest)

file(GLOB TEST_SOURCES "testai/*.cpp")

# Testavimo programa (be main.cpp)
add_executable(testavimas ${TEST_SOURCES} ${SOURCE_FILES})

target_include_directories(testavimas PRIVATE ${INCLUDE_DIR})

# Sulinkina Google Test bibliotekas su testavimo programa
target_link_libraries(testavimas
    GTest::gtest
    GTest::gtest_main
)
gtest_discover_tests(testavimas
    DISCOVERY_MODE PRE_TEST
    PROPERTIES
        ENVIRONMENT "GTEST_COLOR=1"
)
