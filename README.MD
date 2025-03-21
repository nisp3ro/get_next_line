# 📃 get_next_line 125/100

This is the get_next_line project from the 42 Cursus.  
The aim of this project is to implement a function that reads a file line by line.  
Each call to `get_next_line` returns the next line from the file descriptor, including the newline character if present.

---

## Features

### **Mandatory Part**

- **get_next_line Functionality:**
  - Reads from a file descriptor and returns one line at a time.
  - Handles partial reads and buffers the data between calls.
  - Returns `NULL` when there is no more data or on error.

### **Bonus Part**

- **Multiple File Descriptors:**
  - Supports reading from multiple file descriptors simultaneously.
  - Uses a static array of buffers (indexed by file descriptor) to manage multiple streams.

---

## Usage

Include the header file in your project:

```c
#include "get_next_line.h"
```

Use the function in your code as follows:

```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
    int fd;
    char *line;

    fd = open("test_file.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

Compile your program with the get_next _line files:

```c
cc -Wall -Wextra -Werror main.c get_next_line.c get_next_line_utils.c 
```

For the bonus version (supporting multiple file descriptors), simply use `get_next_line` as usual (compiling with the *_bonus.c files). The implementation internally manages a static buffer for each file descriptor.

---

## Implementation Details

- **Buffering:**  
  Data is read in chunks of `BUFFER_SIZE` bytes. The function manages an internal buffer to store the data between calls until a newline character is found.
  BUFFER_SIZE is 42 by default; you can redefine it at compile time.
  ```c
  cc -Wall -Wextra -Werror main.c get_next_line.c get_next_line_utils.c 
  ```

- **Memory Management:**  
  The function dynamically allocates memory for each line it returns. It is the caller's responsibility to free the memory after usage.

- **Edge Cases:**  
  - When the file descriptor is invalid or an error occurs, `get_next_line` returns `NULL`.
  - When reaching the end-of-file, any remaining data is returned as the last line.

---

## License

This project is part of 42 School curriculum.