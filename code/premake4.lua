--
-- Premake4 script to generate the 3D Tetris Game, T3D
--

-- build doxygen
newaction {
	trigger = "dox",
	description = "Creates doxygen html and latex documentation files",
	execute = function ()
		os.execute("doxygen Doxyfile")
	end
}

-- clean doxygen
newaction {
	trigger = "doxclean",
	description = "Clean doxygen files",
	execute = function ()
		os.execute("rm -r html latex")
	end
}

buildDir = "build"

solution "T3D"
	configurations { "Release", "Debug", "Benjamyn" }
	targetname "t3d"
	buildoptions { "-std=c++11", "-pipe" }

	configuration "Benjamyn"
		buildoptions { "-O2", "-march=corei7" }

	configuration "Debug"
		flags { "ExtraWarnings" , "Symbols" }


project "T3D"
	kind "WindowedApp"
	language "C++"
	includedirs { "include" }
	files { "**.cpp", "**.h" } -- ** means recurse into directories
	links { "glut", "GLU", "GL", "SDL", "SDL_image" }
	location (buildDir)
	objdir (buildDir)
		
project "Test"
	kind "WindowedApp"
	language "C++"
	includedirs { "include" }
	targetname "test"
	files { "src/*.cpp", "include/*.h", "bin/test.cpp" } -- ** means recurse into directories
	links { "glut", "GLU", "GL", "SDL", "SDL_image" }
	location (buildDir)
	objdir (buildDir)

	configuration "Benjamyn"
		buildoptions { "-O2", "-march=corei7" }

	configuration "Debug"
		flags { "ExtraWarnings" , "Symbols" }
		
