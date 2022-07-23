workspace "CommonTL"
    architecture "x64"
    startproject "Testbed"

    configurations
    {
        "Debug", -- Debug features, logging
        "Release", -- Optimized debug config without debug features
        "Distribution" -- Final distributed configuration
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "CommonTL"

project "Testbed"
    location "Testbed"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
    objdir ("Binaries-Int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/Source",
        "CommonTL/Include",
        "CommonTL/Source"
    }

    links
    {
        "CommonTL"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "CTL_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "CTL_CONFIG_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "CTL_CONFIG_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Distribution"
        defines "CTL_CONFIG_DISTRIBUTION"
        runtime "Release"
        optimize "on"
        