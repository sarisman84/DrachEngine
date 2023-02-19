include "../Premake/common.lua"
include "../Premake/vendor_common.lua"
print("Building Global Vendor")

local source = os.realpath(directory.global_vendor .. "source\\")

project "Vendor[Global]"
location "."
kind "StaticLib"
language "C++"
cppdialect "C++20"

output = "%{cfg.buildcfg}"
solutionDir = ("%{wks.location}" .. "/")
prjName = "%{prj.name}"

targetdir(directory.global_lib)
objdir(directory.tempOutput .. prjName)
debugdir(directory.global_lib)

targetname("%{prj.name}_%{cfg.buildcfg}")

importLibraries(directory.global_vendor .. "source/")

libdirs {
    directory.global_lib,
    source .. "../util/vcpkg/packages/freetype_**/lib/"
}

defines {
    "_CONSOLE"
}

filter "configurations:Debug"
defines {
    "_DEBUG"
}
runtime "Debug"
symbols "on"
filter "configurations:Release"
defines "_RELEASE"
runtime "Release"
optimize "on"
filter "configurations:Retail"
defines "_RETAIL"
runtime "Release"
optimize "on"

filter "system:windows"
kind "StaticLib"
staticruntime "off"
symbols "On"
systemversion "latest"
-- warnings "Extra"
-- conformanceMode "On"
-- buildoptions { "/permissive" }
flags { --	"FatalWarnings", -- would be both compile and lib, the original didn't set lib
    --	"FatalCompileWarnings",
    "MultiProcessorCompile"
}
links {
    "DXGI",
    "dxguid"
}
defines {
    "_WIN32_WINNT=0x0601"
}

