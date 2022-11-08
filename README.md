## Mandatory
```bash
$> ./pipex file1 cmd1 cmd2 file2
$> < file1 cmd1 | cmd2 > file2
```

```bash
$> ./pipex infile "ls -l" "wc -l" outfile
$> < infile ls -l | wc -l > outfile

$> ./pipex infile "cat" "grep hello" outfile
$> < infile cat | grep hello > outfile

$> ./pipex /dev/urandom "ls -al" "cat" outfile
$> < /dev/urandom ls -al | cat > outfile
```

## Bonus
- multiple pipe
```bash
$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
$> < file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
```

```bash
$> ./pipex infile "cat" "grep hello" "wc -l" outfile
$> < infile cat | grep hello | wc -l > outfile
```
