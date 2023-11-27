
## Let's start!

Have added  github workfow

## How to build the code
1. Create a directory build ( mkdir build)
2. 2 Change directory to build (cd build)

## Release
3. Call cmake ( cmake ..)

## Debug
3. Call cmake with Debug Build type ( cmake -DCMAKE_BUILD_TYPE=Debug ..)
4.  Build the code ( cmake --build .) or make <target name>)

### For debugging:
5. We recommend to use lldb ( due to nice User Interface).
    1. Run lldb together with executable file ( lldb .Main_Components/main_component)
    2. Inside lldb we can call a command "gui" to have User Interface. Run a program with arguments ( run <arg1> <arg2>)  run ../Main_Component/ouput/tsignals.txt. output.txt

![Lines of code](https://tokei.rs/b1/github/The-R4V3N/project_x_the_r4v3n)
