include "../Premake/common.lua"

project "Launcher"
location "."
kind "WindowedApp"
language  "C++"
cppdialect "C++20"

output = "%{cfg.buildcfg}"
solutionDir = ("%{wks.location}" .. "/")
prjName = "%{prj.name}"

targetdir(directory.output)
objdir(directory.tempOutput .. prjName)
targetname("%{prj.name}_%{cfg.buildcfg}")

debugdir (directory.workingDirectory)
dependson
{
    "Editor",
    "Engine"
}
files 
{
    "source/**.h",
    "source/**.hpp",
    "source/**.cpp",

    "**.aps",
    "**.h",
    "**.rc"
}

flags {
    "MultiProcessorCompile"
}

filter "configurations:Debug"
defines "_DEBUG"
runtime "Debug"
symbols "on"

filter "configurations:Release"
defines "_RELEASE"
runtime "Release"
optimize "on"


