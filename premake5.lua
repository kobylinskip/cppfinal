workspace "cppfinal"
    configurations { "Debug", "Release" }
    platforms { "Windows-x86_64", "Windows-x86", "Linux-x86_64" }
    location "build"

    language "C++"
    cppdialect "C++11"

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    filter "platforms:Windows-*"
        system "windows"

    filter "platforms:Linux-*"
        system "linux"

    filter "platforms:*-x86_64"
        architecture "x86_64"

    filter "platforms:*-x86"
        architecture "x86"

project "Final Project"
    kind "ConsoleApp"
    targetdir "%{wks.location}/%{prj.name}/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    debugdir "data"

    files { "src/*.h", "src/*.cpp" }
    includedirs { "src" }
