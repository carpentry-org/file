# file

A simple file abstraction for Carp.

## Installation

You can obtain this library like so:

```clojure
(load "git@github.com:carpentry-org/file.carp@0.0.1")
```

## Usage

The main type involved in working with this library is `File`, naturally. All
file operations depend on the file being opened.

```clojure
(File.open "example.txt") ; => a File you can write to
(File.open-with "example.txt" "a") ; => a File you append to
```

The file permissions follow the [file modes](https://www.tutorialspoint.com/c_standard_library/c_function_fopen.htm)
in UNIX. The default is `"w+"`, or writing/reading. Generally, files have a
`name`, `mode`, and `file` property; you can read safely from them, but writing
to them directly is discouraged.

Before you end your operations on the file, it is good practice to close the
file again. In Carp, we do this using `close`.

```clojure
(close f)
```

You can `read` from the file—or `read-all`, if you don’t care about length—,
`write` to it, `remove` it, or `rewind` the file buffer.

```clojure
(write &f "hi")
(rewind &f)
(IO.println &(read-all &f))
```

You can also ask about the modes of the file, using the functions `readable?`,
`writable?`, or `binary-mode?`.

And that’s about it!

<hr/>

Have fun!
