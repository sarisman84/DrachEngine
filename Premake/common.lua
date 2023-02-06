-- Directories
directory = {}

directory["solution"] = os.realpath("../")
directory["engine"] = os.realpath(directory.solution .. "/engine/")
directory["launcher"] = os.realpath(directory.solution .. "/launcher/")
directory["editor"] = os.realpath(directory.solution .. "/editor/")

directory["engine_lib"] = os.realpath(directory.engine .. "lib/")
directory["editor_lib"] = os.realpath(directory.editor .. "lib/")

directory["engine_vendor"] = directory.engine .. "vendor/"
directory["editor_vendor"] = directory.editor .. "vendor/"

directory["output"] = os.realpath(directory.solution .. "/bin/")
directory["resources"] = directory.output .. "resources/"
directory["engineOutput"] = directory.output .. "engine/"
directory["editorOutput"] = directory.output .. "editor/"
directory["shaderOutput"] = directory.resources .. "shaders/"
directory["tempOutput"] = os.realpath(directory.solution .. "/temp/")
directory["workingDirectory"] = directory.output

-- Helper methods
function fetchVendorInclude(src)
    removefiles {src .. "nlohmann/include/**", src .. "nlohmann/tests/**", src .. "nlohmann/tools/**",
                 src .. "nlohmann/docs/**", src .. "imguizmo/example/**", src .. "imguizmo/vcpkg-example/**",
                 src .. "imgui/examples/**", src .. "imgui/backends/**", src .. "imnodes/example/**",
                 src .. "imnodes/img/**", src .. "imnodes/vcpkg/**", src .. "imnodes/.github/**", src .. "entt/src/**",
                 src .. "entt/test/**", src .. "entt/conan/**"}
    files {src .. "imgui/backends/imgui_impl_dx11.**", src .. "imgui/backends/imgui_impl_win32.**"}
end

