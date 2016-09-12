cmake_minimum_required(VERSION 3.6)

project(cppSamples)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${cppSamples_SOURCE_DIR}/cmake")

set(buildC11 0)
set(buildBoost 1)
set(buildCuda 0)
set(buildIntelTBB 0)
set(buildOpenCL 0)
set(buildOpenMP 0)
set(buildVulkan 0)
set(buildStd 0)


####### buid c11
if(${buildC11})

set(c11folder source/c11)
#SEE https://cmake.org/cmake/help/v3.6/prop_gbl/CMAKE_CXX_KNOWN_FEATURES.html#prop_gbl:CMAKE_CXX_KNOWN_FEATURES
#auto_type
add_executable(auto_type ${c11folder}/auto_type.cpp)
target_compile_features(auto_type PRIVATE cxx_auto_type)
#constexpr
add_executable(constexpr ${c11folder}/constexpr.cpp)
target_compile_features(constexpr PRIVATE cxx_constexpr)
#rang_for
add_executable(rang_for ${c11folder}/rang_for.cpp)
target_compile_features(rang_for PRIVATE cxx_range_for)
#final
add_executable(final ${c11folder}/final.cpp)
target_compile_features(final PRIVATE cxx_final)
#override
add_executable(override ${c11folder}/override.cpp)
target_compile_features(override PRIVATE cxx_override)
#strong_enums
add_executable(strong_enums ${c11folder}/strong_enums.cpp)
target_compile_features(strong_enums PRIVATE cxx_strong_enums)
#lambdas
add_executable(lambdas ${c11folder}/lambdas.cpp)
target_compile_features(lambdas PRIVATE cxx_lambdas)
#static_assert
add_executable(static_assert ${c11folder}/static_assert.cpp)
target_compile_features(static_assert PRIVATE cxx_static_assert)

#all feature
#add_executable(allfeature ${c11folder}/allfeature.cpp)
#target_compile_features(allfeature PRIVATE cxx_aggregate_default_initializers)
#target_compile_features(allfeature PRIVATE cxx_alias_templates)
#target_compile_features(allfeature PRIVATE cxx_alignas)
#target_compile_features(allfeature PRIVATE cxx_alignof)
#target_compile_features(allfeature PRIVATE cxx_attributes)
#target_compile_features(allfeature PRIVATE cxx_attribute_deprecated)
#target_compile_features(allfeature PRIVATE cxx_auto_type)
#target_compile_features(allfeature PRIVATE cxx_binary_literals)
#target_compile_features(allfeature PRIVATE cxx_constexpr)
#target_compile_features(allfeature PRIVATE cxx_contextual_conversions)
#target_compile_features(allfeature PRIVATE cxx_decltype_incomplete_return_types)
#target_compile_features(allfeature PRIVATE cxx_decltype)
#target_compile_features(allfeature PRIVATE cxx_decltype_auto)
#target_compile_features(allfeature PRIVATE cxx_default_function_template_args)
#target_compile_features(allfeature PRIVATE cxx_defaulted_functions)
#target_compile_features(allfeature PRIVATE cxx_defaulted_move_initializers)
#target_compile_features(allfeature PRIVATE cxx_delegating_constructors)
#target_compile_features(allfeature PRIVATE cxx_deleted_functions)
#target_compile_features(allfeature PRIVATE cxx_digit_separators)
#target_compile_features(allfeature PRIVATE cxx_enum_forward_declarations)
#target_compile_features(allfeature PRIVATE cxx_explicit_conversions)
#target_compile_features(allfeature PRIVATE cxx_extended_friend_declarations)
#target_compile_features(allfeature PRIVATE cxx_extern_templates)
#target_compile_features(allfeature PRIVATE cxx_final)
#target_compile_features(allfeature PRIVATE cxx_func_identifier)
#target_compile_features(allfeature PRIVATE cxx_generalized_initializers)
#target_compile_features(allfeature PRIVATE cxx_generic_lambdas)
#target_compile_features(allfeature PRIVATE cxx_inheriting_constructors)
#target_compile_features(allfeature PRIVATE cxx_inline_namespaces)
#target_compile_features(allfeature PRIVATE cxx_lambdas)
#target_compile_features(allfeature PRIVATE cxx_lambda_init_captures)
#target_compile_features(allfeature PRIVATE cxx_local_type_template_args)
#target_compile_features(allfeature PRIVATE cxx_long_long_type)
#target_compile_features(allfeature PRIVATE cxx_noexcept)
#target_compile_features(allfeature PRIVATE cxx_nonstatic_member_init)
#target_compile_features(allfeature PRIVATE cxx_nullptr)
#target_compile_features(allfeature PRIVATE cxx_override)
#target_compile_features(allfeature PRIVATE cxx_range_for)
#target_compile_features(allfeature PRIVATE cxx_raw_string_literals)
#target_compile_features(allfeature PRIVATE cxx_reference_qualified_functions)
#target_compile_features(allfeature PRIVATE cxx_relaxed_constexpr)
#target_compile_features(allfeature PRIVATE cxx_return_type_deduction)
#target_compile_features(allfeature PRIVATE cxx_right_angle_brackets)
#target_compile_features(allfeature PRIVATE cxx_rvalue_references)
#target_compile_features(allfeature PRIVATE cxx_sizeof_member)
#target_compile_features(allfeature PRIVATE cxx_static_assert)
#target_compile_features(allfeature PRIVATE cxx_strong_enums)
#target_compile_features(allfeature PRIVATE cxx_thread_local)
#target_compile_features(allfeature PRIVATE cxx_trailing_return_types)
#target_compile_features(allfeature PRIVATE cxx_unicode_literals)
#target_compile_features(allfeature PRIVATE cxx_uniform_initialization)
#target_compile_features(allfeature PRIVATE cxx_unrestricted_unions)
#target_compile_features(allfeature PRIVATE cxx_user_literals)
#target_compile_features(allfeature PRIVATE cxx_variable_templates)
#target_compile_features(allfeature PRIVATE cxx_variadic_macros)
#target_compile_features(allfeature PRIVATE cxx_variadic_templates)
#target_compile_features(allfeature PRIVATE cxx_template_template_parameters)

#multi thread
add_executable(thread  ${c11folder}/thread/thread.cpp)
target_compile_features(thread PRIVATE cxx_thread_local)

endif()


#######  opencl
if(${buildOpenCL})
find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIRS} source/openCL)
add_executable(openCL  source/openCL/openCL.cpp )
add_executable(clinfo source/opencL/clinfo.c source/openCL/getopt_long.c)
target_link_libraries(openCL ${OpenCL_LIBRARIES})
target_link_libraries(clinfo ${OpenCL_LIBRARIES})
target_compile_features(openCL PRIVATE cxx_auto_type)
endif()

########  openMP
if(${buildOpenMP})
find_package(OpenMP REQUIRED) 
if(OPENMP_FOUND)  
message("OPENMP FOUND")  
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")  
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")  
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")  
endif()  
add_executable(OpenMP  source/OpenMP/OpenMP.cpp)
endif()

###########  tbb
if(${buildIntelTBB})
find_package(TBB REQUIRED)
endif()

###########  vulkan
if(${buildVulkan})
find_package(Vulkan REQUIRED)
endif()

###########  cuda
if(${buildCuda})
find_package(CUDA REQUIRED)
endif()

#######boost
if(${buildBoost})
if (WIN32 AND MSVC)
    set(ENV{BOOST_ROOT} "D:/Develop/Source/boost_1_61_0") 
    set(ENV{BOOST_LIBRARYDIR} "D:/Develop/Source/boost_1_61_0/bin.v2/libs")
endif()
find_package(Boost REQUIRED COMPONENTS filesystem)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
add_executable(fileSystem source/boost/fileSystem.cpp)
target_link_libraries(fileSystem ${Boost_LIBRARIES})
endif()
endif()


##########std


#########opengl
find_package(OpenGL REQUIRED)


##########vtk

