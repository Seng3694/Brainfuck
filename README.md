# Simple Brainfuck Interpreter #

[Brainfuck][1] is an esoteric programming language.

The interpreter can run script files and strings from command line.

This will print `123`:
```
>brainfuck.exe "++++++[>++++++++<-]>+.+.+."
```

This will run the `helloworld.bf` file:
```
>brainfuck.exe helloworld.bf
```

This interpreter does some small optimizations:
- instead of adding 1 or subtracting 1 on each consequent `+`/`-`, this interpreter does add `+1` for each `+` and `-1` for each `-` in a sequence. So `++--+++` will become `+3` (one instruction instead of 7)
- `>` and `<` are handled the same way. Assuming the memory pointer is at zero then `>>><<>>` will move it instantly to 3.
- the `[` and `]` nodes hold pointers to their counterpart so they can jump there instantly instead of searching for it 

Just to visualize this here is a diagram for the following `bf` code:

```Brainfuck
++++++[>++++++++<-]>+.+.+.
```

<br/>

![diagram][2]

This saves some instructions compared to the most naive implementation.

## Build ##

Project uses [CMake][3].

1. Clone:
    ```
    git clone "https://github.com/Seng3694/Brainfuck"
    ```

2. Generate build files:
    ```
    mkdir bin
    cd bin
    cmake -G"YOUR GENERATOR" ..
    ```

3. Build
    ```
    cmake --build . --config Release
    ```

## License ##

This Code is licensed under the MIT License. See [LICENSE][4] for more information.

[1]:https://esolangs.org/wiki/Brainfuck
[2]:resources/diagram.png
[3]:http://www.cmake.org/
[4]:LICENSE