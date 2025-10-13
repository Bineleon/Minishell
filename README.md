# Minishell

A small POSIX‑like shell written in C (42 School project). It implements an interactive prompt, pipelines, redirections, environment expansion and a set of **builtins functions**. It also ships with a minimal **garbage collector** to centralize allocations and avoid leaks.

---

## Features

- **Interactive prompt** with history
- **Execute** external commands
- **Pipelines**: `cmd1 | cmd2 | cmd3`
- **Redirections**:
  - Input `< file`
  - Output `> file` (truncate) and `>> file` (append)
  - **Heredoc** `<< DELIM`
- **Environment expansion**: `$HOME`, `$USER`, double‑quoted expansion, and **`$?`** (last exit status)
- **Signals**: proper handling of `Ctrl‑C` / `Ctrl-\`` consistent with Minishell subject
- **Builtins**: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- **Custom memory manager (“garbage collector”)** to simplify mass‑free and reduce leaks
- **Exit** on Ctrl-D (EOF) cleanly closes the shell, just like Bash

---

## Dependencies

- **GNU Readline**
  - Debian/Ubuntu: `sudo apt-get install libreadline-dev`

---

## Build

Use the **Makefile** at the repository root.

```bash
# Build the binary
make

# Run
./minishell

# Common targets
make clean     # remove objects
make fclean    # remove objects + binary
make re        # rebuild from scratch
```
---

## Quick start

```bash
./minishell
minishell> echo "hello $USER"
minishell> ls -la | grep minishell
minishell> cat < input.txt | grep foo > out.txt
minishell> cat << EOF
> line 1
> line 2
> EOF
minishell> echo $?
```

### Pipelines
```bash
minishell> ls -l | grep minishell
```

### Redirections
```bash
minishell> echo "Hello" > hello.txt
minishell> cat < hello.txt
minishell> echo "append" >> file.txt
```

### Variables & quotes
```bash
minishell> echo $HOME
minishell> echo "$USER is here: $HOME"
minishell> echo $?   # last command exit status
```

---

## Builtins

| Command | Description | Examples |
|---|---|---|
| `echo` | Print arguments (supports quotes, `-n` if implemented) | `echo -n "hello"` |
| `cd` | Change directory (with or without arg) | `cd`, `cd ~`, `cd /tmp` |
| `pwd` | Print current directory | `pwd` |
| `export` | Define environment variables | `export KEY=value` |
| `unset` | Remove environment variables | `unset KEY` |
| `env` | Print the current environment | `env` |
| `exit` | Quit the shell (optional code) | `exit`, `exit 2` |

---

## Redirections & Heredoc

- `< file` redirects **stdin** from file.
- `> file` redirects **stdout** to file (truncate).
- `>> file` redirects **stdout** to file (append).
- `<< DELIM` reads until a line matching `DELIM` (Heredoc). Signals are handled during heredoc; `Ctrl‑C` cancels cleanly.

Errors (syntax, file access, etc.) are reported with meaningful messages and proper exit status.

---

## 🧠 Memory Manager (Garbage Collector)

The project uses a **very small custom garbage collector** to make memory management easier and avoid leaks.  
Instead of freeing every `malloc` manually everywhere in the code, all allocations are **tracked automatically** and can be cleaned in one go.

### How it works

- Each time the program allocates memory, it calls the GC instead of plain `malloc`.  
- The GC keeps a list of all allocated pointers.
- You can free:
  - **One pointer**: remove it from the list and free it.
  - **Everything at once**: clear all tracked memory (used at program exit or when resetting a shell state).

### Example usage
```c
gc_mem(MALLOC, size, NULL);   // allocate and track
gc_mem(FREE, 0, ptr);         // free one pointer
gc_mem(FULL_CLEAN, 0, NULL);  // free all tracked memory
```

At the moment, there are **two separate garbage collectors**:
1. One for **general memory** (parser, executor, tokens, strings…)
2. One for **environment variables** (copies of env arrays, export/unset, etc.)

This separation was made because environment data has a **different lifetime**.

---

### Possible improvement

A better design would be to **merge both collectors** into one by adding a **label or flag** to each allocation.  
This would make the code simpler and more flexible, no need for a special GC just for environment variables.

---

## Project layout

```
includes/
  minishell.h          # types, enums (tokens, redirs, etc.), prototypes
  constants.h          # colors/constants
libft/                 # ft_printf, gnl, libft
src/
  main/                # entry point, shell init
  builtins/            # echo, cd, pwd, export, unset, env, exit
  parsing/             # tokenization, quotes, env expansion ($, "$", $?)
  exec/                # exec, pipelines, redirs, heredoc, children
  signal/              # signal handling (Ctrl‑C, Ctrl-\)
  utils/               # errors, helpers, GC (gc_core/env/split/itoa/...)
```

---

## Quick tests

- **Simple**: `echo hello`, `pwd`, `cd .. && pwd`
- **Pipelines**: `cat Makefile | wc -l`
- **Redirs**: `grep -i minishell < README.md > out.txt`
- **Heredoc**: `cat << EOF` … `EOF`
- **Env**: `export FOO=bar && echo $FOO && unset FOO && echo $FOO`
- **Exit status**: `false ; echo $?` → should print `1`

---

## Technical notes

- Token kinds: `WORD`, `PIPE (|)`, `IN (<)`, `OUT (>)`, `HEREDOC (<<)`, `APPEND (>>)`, with proper quote handling `'` / `"`.
- Expansion is applied outside single quotes, with special handling for **`$?`** via an internal `exit_status`.

---

## 👤 Author

**Nelbi Leon**  
42 Paris | [GitHub](https://github.com/Bineleon)

