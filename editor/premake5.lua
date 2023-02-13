include "../Premake/common.lua"
group("Editor")
project "Editor"
location "."
kind "SharedLib"
language "C++"
cppdialect "C++20"

output = "%{cfg.buildcfg}"
solutionDir = ("%{wks.location}" .. "/")
prjName = "%{prj.name}"

targetdir(directory.editorOutput)
objdir(directory.tempOutput .. prjName)
targetname("%{prj.name}_%{cfg.buildcfg}")

debugdir(directory.output)

local en_vendor_source = directory.engine_lib
local ed_vendor_source = directory.editor_lib

local ed_files = os.matchfiles(ed_vendor_source .. "*")
local en_files = os.matchfiles(en_vendor_source .. "*")

if #ed_files > 0 then
    links {
        "Vendor[Editor]"
    }
end

if #en_files > 0 then
    links {
        "Vendor[Engine]"
    }
end
links {
    "Vendor[Global]"
}

if #ed_files > 0 then
    libdirs {
        directory.editor_lib
    }
end

if #en_files > 0 then
    libdirs {
        directory.engine_lib
    }
end
libdirs {
    directory.global_lib
}

includedirs {
    directory.editor_vendor .. "source/",
    directory.engine_vendor .. "source/",
    directory.global_vendor .. "source/",
    "source/"
}

files {
    "source/**.h",
    "source/**.hpp",
    "source/**.cpp"
}

flags {
    "MultiProcessorCompile"
}

include "vendor"

filter "configurations:Debug"
defines "_DEBUG"
runtime "Debug"
symbols "on"

filter "configurations:Release"
defines "_RELEASE"
runtime "Release"
optimize "on"
