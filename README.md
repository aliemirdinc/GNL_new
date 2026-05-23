*This project has been created as part of the 42 curriculum by aldinc.*

# Get Next Line

## Description
The **Get Next Line (GNL)** project is designed to create a function that reads a single line from a file descriptor (`fd`), allowing it to be called repeatedly to read a file line by line until the End of File (EOF) is reached. This project serves as a crucial building block in the 42 curriculum, introducing developers to the robust use of `static variables`, memory allocation, and file I/O operations in C.

## Instructions

To compile and use the `get_next_line` function in your projects, simply include the header and compile your files with the `get_next_line` source files:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 my_project.c get_next_line.c get_next_line_utils.c
```
*Note: You can change the `BUFFER_SIZE` macro to any desired integer to test its efficiency.*

For the bonus features (multiple file descriptors handling), compile with the bonus files:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 my_project.c get_next_line_bonus.c get_next_line_utils_bonus.c
```

### Usage Examples (Main Templates)

**1. Reading from an Existing File**
This template demonstrates how to open an existing file and print its contents line by line using `get_next_line`.
```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
    int     fd;
    char    *line;

    fd = open("trial1.txt", O_RDONLY);
    if (fd < 0)
    {
        printf("Error opening file\n");
        return (1);
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

**2. Creating, Writing, and Reading a File**
This template creates a new file, writes some text into it, closes it, reopens it for reading, and prints the output using `get_next_line`.
```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

int main(void)
{
    int     fd;
    char    *line;

    // 1. Create and write to a file
    fd = open("test_output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0)
        return (1);
    write(fd, "Hello, 42!\n", 11);
    write(fd, "This is Get Next Line.\n", 23);
    write(fd, "Testing file creation and reading.\n", 35);
    close(fd);

    // 2. Open and read the file
    fd = open("test_output.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    
    printf("--- File Contents ---\n");
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

**3. Reading Multiple Files Simultaneously (Bonus)**
This template demonstrates how the bonus version of `get_next_line` can manage multiple file descriptors at once without losing track of their reading state.
```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line_bonus.h"

int main(void)
{
    int     fd1, fd2, fd3;
    char    *line;

    // 1. Create 3 files and write some text
    fd1 = open("file1.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    fd2 = open("file2.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    fd3 = open("file3.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    
    if (fd1 < 0 || fd2 < 0 || fd3 < 0)
        return (1);

    write(fd1, "File 1 - Line 1\nFile 1 - Line 2\n", 32);
    write(fd2, "File 2 - Line 1\nFile 2 - Line 2\n", 32);
    write(fd3, "File 3 - Line 1\nFile 3 - Line 2\n", 32);
    
    close(fd1);
    close(fd2);
    close(fd3);

    // 2. Open them for reading
    fd1 = open("file1.txt", O_RDONLY);
    fd2 = open("file2.txt", O_RDONLY);
    fd3 = open("file3.txt", O_RDONLY);
    
    if (fd1 < 0 || fd2 < 0 || fd3 < 0)
        return (1);

    // 3. Read alternately to demonstrate static array
    printf("--- First Round ---\n");
    
    line = get_next_line(fd1);
    if (line != NULL)
    {
        printf("FD1: %s", line);
        free(line);
    }

    line = get_next_line(fd2);
    if (line != NULL)
    {
        printf("FD2: %s", line);
        free(line);
    }

    line = get_next_line(fd3);
    if (line != NULL)
    {
        printf("FD3: %s", line);
        free(line);
    }

    printf("--- Second Round ---\n");
    
    line = get_next_line(fd1);
    if (line != NULL)
    {
        printf("FD1: %s", line);
        free(line);
    }

    line = get_next_line(fd2);
    if (line != NULL)
    {
        printf("FD2: %s", line);
        free(line);
    }

    line = get_next_line(fd3);
    if (line != NULL)
    {
        printf("FD3: %s", line);
        free(line);
    }

    close(fd1);
    close(fd2);
    close(fd3);
    return (0);
}
```

## Resources
- 42 Curriculum Documentation
- `man read`
- `man malloc`
- `man free`

**AI Usage Statement:**
AI was used in this project to review the code structure against the strict 42 Norm v3 requirements. It assisted in identifying structural deviations such as inline declarations and `for` loops, refactoring the algorithm into a more unique and memory-leak-safe form, ensuring adherence to the 25-line limit per function, and generating this compliant README.md file in accordance with Chapter V of the project subject.

## Algorithm Justification
The chosen algorithm relies on the concept of an "accumulation buffer" via a single `static char *storage`.
1. **Reading**: The function reads from the file descriptor into a temporary buffer in chunks of `BUFFER_SIZE` bytes. The new chunk is concatenated (`ft_strjoin`) to the `storage` static variable until a newline character `\n` is found or `read` returns 0 (EOF).
2. **Extraction**: Once the data is accumulated, `ft_extract_line` determines the exact position of the newline. It dynamically allocates just enough memory to hold the line (including the newline itself).
3. **Storage Updating**: The remaining part of the string (characters following the newline) is saved back into the static `storage` pointer for the next function call. If EOF is reached, memory is thoroughly cleaned up, avoiding any dangling pointers or memory leaks.

For the **Bonus** part, the `storage` variable is transformed into a static array of pointers (`static char *storage[MAX_FD]`). This allows the function to keep track of multiple reading instances asynchronously, indexing the array directly using the file descriptor as the key.
