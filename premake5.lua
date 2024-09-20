workspace "cipher"
configurations { "Debug", "Release" }

-- Place Makefile in the main directory
location "."

project "cipher"
    kind "ConsoleApp"
    language "C"
    targetdir "bin/%{cfg.buildcfg}"

-- Include all source and header files
    files { "src/**.c", "include/**.h" }

-- Include directory for headers
    includedirs { "include" }

-- Debug configuration: include debug symbols and warnings
filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "On"
    buildoptions { "-Wall" }

-- Release configuration: enable optimization
filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "On"
