project "CommonTL"
    language "C++"
    cppdialect "C++20"
    kind "StaticLib"
    staticruntime "off"

    targetdir ("%{wks.location}/Binaries/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/Binaries-Int/" .. outputdir .. "/%{prj.name}")

    pchheader "ctlpch.h"
    pchsource "Source/ctlpch.cpp"

    files
    {
        "Source/**.h",
        "Source/**.cpp",
        "Include/**.h"
    }

    includedirs
    {
        "Source",
        "Include"
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