*This project has been created as part of the 42 curriculum by psmolich, twatson*

# minishell

## Description

minishell is a simplified shell implementation written in C. The goal is to build a functional command-line interpreter that handles a subset of bash behavior — enough to understand how a real shell works under the hood: process creation, file descriptor plumbing, signal handling, and environment management.

What it does:

- Displays a prompt and waits for user input
- Runs executables found via `PATH` or by absolute/relative path
- Supports pipes (`|`) to chain commands together
- Handles input/output redirections (`<`, `>`, `>>`) and here-documents (`<<`)
- Expands environment variables (`$VAR`, `$?`) respecting single and double quote rules
- Reacts to signals (`Ctrl-C`, `Ctrl-\`, `Ctrl-D`) the way bash does, depending on context (idle prompt, running command, or reading a heredoc)
- Implements builtins: `echo -n`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`

It does **not** handle `&&`, `||`, wildcards, backslash escaping, or semicolons. These are outside the project scope and treated as regular characters.

## Architecture

The project is split into two main parts:

**Parsing** takes the raw input string, tokenizes it, handles quote state tracking, performs variable expansion, and produces a structured representation of the pipeline — an array of commands with their arguments and an array of redirections per command.

**Execution** receives that structure and handles forking, piping, redirection setup via `dup2`, builtin dispatch, PATH resolution, and signal mode switching between prompt, child-running, and heredoc states. Stateful builtins (`cd`, `export`, `unset`, `exit`) run in the parent process when they appear as a standalone command; everything else runs in a child.

### Signal modes

The shell switches between three signal contexts depending on what it's doing:

| Mode | When | Ctrl-C | Ctrl-\\ |
|------|------|--------|---------|
| Prompt | Waiting for input | New line, fresh prompt | Ignored |
| Child running | External command executing | Forwarded to child | Forwarded to child |
| Heredoc | Reading heredoc input | Aborts heredoc, returns to prompt | Ignored |

### Builtin strategy

Builtins that modify shell state (`cd`, `export`, `unset`, `exit`) must run in the parent when they appear as a standalone command — otherwise their side effects would be lost in a child process. Output-only builtins (`echo`, `pwd`, `env`) are safe to run in either context. When any builtin appears inside a pipeline, it runs in a child regardless.

## Instructions

### Requirements

- A Unix-like system (tested on Linux / Ubuntu 24)
- `gcc` or `cc`
- `make`
- `readline` library (`libreadline-dev` on Debian/Ubuntu)

### Build

```bash
make
```

This produces the `minishell` executable.

Other targets:

```bash
make clean    # remove object files
make fclean   # remove object files and the executable
make re       # full rebuild
```

### Run

```bash
./minishell
```

You get a prompt. Type commands like you would in bash. `exit` or `Ctrl-D` to quit.

### Example usage

```
MINIsHELL$> echo hello world
hello world
MINIsHELL$> echo hello | cat -e
hello$
MINIsHELL$> cat < infile > outfile
MINIsHELL$> export FOO=bar
MINIsHELL$> echo $FOO
bar
MINIsHELL$> cat << EOF
> line one
> line two
> EOF
line one
line two
MINIsHELL$> exit
```

## Technical notes

- One global variable is used, for storing the received signal number (as required by the subject). Its type is `volatile sig_atomic_t`.
- Memory: the parent process is clean under `valgrind --leak-check=full`. Child processes that call `execve` don't free beforehand since `execve` replaces the process image; on failure paths they clean up before `_exit`. Readline's own internal allocations show as "still reachable" — this is expected and not a leak on our end.
- FD hygiene: pipe file descriptors are initialized to `-1` and checked before closing to avoid double-close issues.
- Every child process terminates with `exit()` or `_exit()` — none are allowed to fall back into the shell loop.

## Resources

**References used during development:**

- [Bash Reference Manual (GNU)](https://www.gnu.org/software/bash/manual/bash.html) — the spec we tested against
- [42 Minishell Guide](https://42-cursus.gitbook.io/guide/3-rank-03/minishell/understand-minishell) — project walkthrough and function reference
- [Precedence Climbing (Eli Bendersky)](https://eli.thegreenplace.net/2012/08/02/parsing-expressions-by-precedence-climbing) — parsing technique reference
- [Linux heredoc guide (Linuxize)](https://linuxize.com/post/bash-heredoc/) — heredoc behavior details
- [Minishell article by m4nnb3ll](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218) — another student's breakdown of the project structure
- [Readline Signal Handling (GNU)](https://docs.rtems.org/releases/4.5.1-pre3/toolsdoc/gdb-5.0-docs/readline/readline00030.html)
- Various YouTube walkthroughs on shell implementation

**Peers:**

We also bounced ideas off fellow 42 students regularly — especially around heredoc edge cases, redirection ordering, and whether our overall design made sense.

**How AI was used:**

We used ChatGPT (OpenAI) and Claude (Anthropic) as learning aids:

- *Concept clarification:* understanding how pipes, signals, and process management work at the syscall level — things like why `execve` doesn't return on success, how `dup2` interacts with file descriptors, or what valgrind's different leak categories mean.
- *Architecture discussion:* talking through design decisions like the parser-to-executor interface, when builtins should run in the parent vs child, and how to structure signal mode switching.
- *Debugging guidance:* when stuck on issues (segfaults, fd leaks, unexpected behavior), we described the symptoms and discussed possible causes to narrow down where to look — especially around memory management and child process cleanup.
- *Documentation:* AI was used to help summarize and organize our joint planning notes and sources into this README.


