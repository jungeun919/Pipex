## Mandatory : 리눅스 파이프와 리다이렉션 구현하기
## Bonus : 다중 파이프와 히어독 구현하기

### [개념 정리](https://www.notion.so/dev-jungeun/Pipex-7dc13565963e4d338ec0cf62fa1ffcfd)
* Block/Non-Block, Synchronous/Asynchronous
* Redirection, Here-doc
* 허용함수 정리
* 환경변수 PATH


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

- support << and >> when the first param is "here_doc"
```bash
$> ./pipex here_doc LIMITER cmd cmd1 file
$> cmd << LIMITER | cmd1 >> file
```

```bash
$> ./pipex here_doc limiter "cat" "grep a" outfile
$> cat << limiter | grep a >> outfile
```

## Tester
- [tester1](https://github.com/vfurmane/pipex-tester)
- [tester2](https://github.com/Yoo0lh/pipex_tester_42)
