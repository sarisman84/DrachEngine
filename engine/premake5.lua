include "../Premake/common.lua"

group("Engine")
project "Engine"
location "."
kind "SharedLib"
language "C++"
cppdialect "C++20"

output = "%{cfg.buildcfg}"
solutionDir = ("%{wks.location}" .. "/")
prjName = "%{prj.name}"

targetdir(directory.engineOutput)
objdir(directory.tempOutput .. prjName)
targetname("%{prj.name}_%{cfg.buildcfg}")

debugdir(directory.output)
local vendor_source = directory.engine_vendor .. "source/"
local foundFiles = os.matchfiles(vendor_source .. "*")
if #foundFiles > 0 then
    links {"Vendor[Engine]"}
end
links {"d3d11.lib"}



if #foundFiles > 0 then
    libdirs {directory.engine_lib}
end
includedirs {directory.engine_vendor .. "source/", "source/"}

files {"source/**.h", "source/**.hpp", "source/**.cpp", "source/**.hlsl", "source/**.hlsli"}

flags {"MultiProcessorCompile"}

shadermodel("5.0")

local shaderOutput = directory.shaderOutput

filter("files:**.hlsl")
flags("ExcludeFromBuild")
shaderobjectfileoutput(shaderOutput .. "%{file.basename}" .. ".cso")

filter("files:**PS.hlsl")
removeflags("ExcludeFromBuild")
shadertype("Pixel")

filter("files:**VS.hlsl")
removeflags("ExcludeFromBuild")
shadertype("Vertex")

filter("files:**GS.hlsl")
removeflags("ExcludeFromBuild")
shadertype("Geometry")

-- Warnings as errors
shaderoptions({"/WX"})

include "vendor"

filter "configurations:Debug"
defines "_DEBUG"
runtime "Debug"
symbols "on"

filter "configurations:Release"
defines "_RELEASE"
runtime "Release"
optimize "on"
