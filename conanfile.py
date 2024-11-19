from conan import ConanFile
from conan.tools.cmake import cmake_layout


class GeckoEngine(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("vulkan-loader/1.3.239.0")
        self.requires("vulkan-validationlayers/1.3.239.0")
        self.requires("glfw/3.4")
        self.requires("glm/cci.20230113")
        self.requires("tinyobjloader/2.0.0-rc10")

    def build_requirements(self):
        self.build_requires("glslang/11.7.0")
        self.build_requires("cmake/3.22.6")

    # def layout(self):
    #     cmake_layout(self)
