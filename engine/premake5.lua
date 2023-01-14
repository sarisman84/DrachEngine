include "../Premake/common.lua"

project "Engine"
location "."
kind "SharedLib"
language  "C++"
cppdialect "C++20"

output = "%{cfg.buildcfg}"
solutionDir = ("%{wks.location}" .. "/")
prjName = "%{prj.name}"

targetdir(directory.engineOutput)
objdir(directory.tempOutput .. prjName)
targetname("%{prj.name}_%{cfg.buildcfg}")

debugdir (directory.engineOutput)

files 
{
    "source/**.h",
    "source/**.hpp",
    "source/**.cpp",
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