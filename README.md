# CSMA-CD-timing
The program simulates network with <i>N</i> hosts sending frames. The output of program is timecode when each station <b>begun</b> succesful transmition of frame.
## Build
### Using meson
```
meson setup builddir
cd builddir
meson compile # ... or if meson < 0.5.5, use ninja
```
### Using pure gcc
```
gcc *.c
```
## Run 
If you have used meson run with `./csmacd` otherwise use `./a.out`.
### Arguments
* `--help` - shows help message
* `-n` - number of stations(default: 5)
* `--frame-size` - size of frame(default: 1518)
* `--max-attempt` - how many station can retry before stopping(default: 10)
### Example of results
```
$ ./csmacd -n 10 --max-attempt 16
[*]:Program starting...
[*]:Built with Apple LLVM 12.0.0 (clang-1200.0.32.21) at Nov 27 2020 14:50:55
[+]:Station with 4 has finished transmitting data
[+]:Station with 7 has finished transmitting data
[+]:Station with 9 has finished transmitting data
[+]:Station with 1 has finished transmitting data
[+]:Station with 2 has finished transmitting data
[+]:Station with 6 has finished transmitting data
[+]:Station with 5 has finished transmitting data
[+]:Station with 3 has finished transmitting data
[+]:Station with 0 has finished transmitting data
[+]:Station with 8 has finished transmitting data
[+]:Finished simulation successfully.
ID                       Timecode  
0                        625920.000000µs
1                        234188.800000µs
2                        312064.000000µs
3                        546867.200000µs
4                        307.200000µs
5                        468787.200000µs
6                        390604.800000µs
7                        78182.400000µs
8                        703692.800000µs
9                        156108.800000µs
```    

Also in such table instead of timecode can be string `FAILED` which means that station exceeded it's attempts to send frame
## License
Licensed under GNU/GPL 3.0 due to usage of open-source components from [ddos2](https://github.com/Andrewerr/ddos2)
