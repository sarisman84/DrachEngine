-- Directories
directory = {}

directory["solution"] = os.realpath("../")
directory["engine"] = os.realpath(directory.solution .. "/DrachEngine/")
directory["launcher"] = os.realpath(directory.solution .. "/DrachLauncher/")
directory["editor"] = os.realpath(directory.solution .. "/DrachEditor/")

directory["output"] = os.realpath(directory.solution .. "/bin/")
directory["engineOutput"] = directory.output .. "engine/"
directory["editorOutput"] = directory.output .. "editor/"
directory["tempOutput"] = os.realpath(directory.solution .. "/temp/")
directory["workingDirectory"] = directory.bin

