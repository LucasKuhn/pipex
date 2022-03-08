# pipex
Ecole 42 | C program chaining pipes

```sh
# EX
./pipex infile "cat" "wc -l" outfile
# EQUIVALENTE BASH
< infile cat | wc -l > outfile
```

```sh
< infile echo 'hello 42' | tr '42' 'FT' > outfile 
```