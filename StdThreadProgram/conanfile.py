from conans import ConanFile, CMake


class JADEConan(ConanFile):

   settings = "os", "compiler", "build_type", "arch"
   requires = "qt/5.15.6"
   generators = "qt", "cmake_find_package", "cmake_paths"
   default_options = {"qt:shared":True, "qt:qtsvg":True, "qt:qttranslations":False}

   def configure(self):
      print("The following packages will be used as a dependency:")
      print(self.requires, "\n")

   def imports(self):
      self.copy("*.dll", src="bin", dst="./") # Copy dlls

   def build(self):
      cmake = CMake(self)
      cmake.configure()
      cmake.build()