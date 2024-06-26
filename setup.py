import os
import sys
import subprocess
from setuptools import setup, Extension, Command
from setuptools.command.build_ext import build_ext

class CMakeExtension(Extension):
    def __init__(self, name, sourcedir=''):
        super().__init__(name, sources=[])
        print(sourcedir)
        self.sourcedir = os.path.abspath(sourcedir)

class CMakeBuild(build_ext):
    def run(self):
        try:
            out = subprocess.check_output(['cmake', '--version'])
        except OSError:
            raise RuntimeError("CMake must be installed to build the following extensions: " +
                               ", ".join(e.name for e in self.extensions))

        for ext in self.extensions:
            #print(ext.name)
            self.build_extension(ext)

    def build_extension(self, ext):
        #print (self.get_ext_fullpath(ext.name))
        extdir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))
        # print(extdir)
        cmake_args = ['-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=' + extdir,
                      '-DPYTHON_EXECUTABLE=' + sys.executable,
                      '-DCMAKE_BUILD_TYPE=Release']

        build_args = []

        if not os.path.exists(self.build_temp):
            os.makedirs(self.build_temp)
        subprocess.check_call(['cmake', ext.sourcedir] + cmake_args, cwd=self.build_temp)
        subprocess.check_call(['cmake', '--build', '.'] + build_args, cwd=self.build_temp)

        # Run CTest after building the extension
        subprocess.check_call(['ctest', '--output-on-failure'], cwd=self.build_temp)


class CTestCommand(Command):
    """Custom command to run CTest."""
    user_options = []

    def initialize_options(self):
        pass

    def finalize_options(self):
        pass

    def run(self):
        build_temp = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'build')
        # Run CTest in the build directory
        subprocess.check_call(['ctest', '--output-on-failure'], cwd=build_temp)

class UninstallCommand(Command):
    """Custom uninstall command to remove the package."""
    user_options = []

    def initialize_options(self):
        pass

    def finalize_options(self):
        pass

    def run(self):
        subprocess.check_call([sys.executable, '-m', 'pip', 'uninstall', 'monte_carlo_option_pricer'])


setup(
    name='monte_carlo_option_pricer',
    version='0.0.2',
    author='CodeWithLuke',
    description='A test project using pybind11 and CMake',
    long_description='',
    ext_modules=[CMakeExtension('monte_carlo_option_pricer')],
    cmdclass=dict(build_ext=CMakeBuild,
        uninstall=UninstallCommand
    ),
    zip_safe=False,
)