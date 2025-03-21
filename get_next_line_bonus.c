#include "get_next_line_bonus.h"

/**
 * @brief Frees a string and sets its pointer to NULL.
 *
 * Frees the memory pointed to by *str, sets the pointer to NULL,
 * and returns NULL.
 *
 * @param str Pointer to the pointer to be freed.
 * @return char* Always returns NULL.
 */
char *ft_free(char **str)
{
    free(*str);
    *str = NULL;
    return (NULL);
}

/**
 * @brief Updates the saved buffer by removing the extracted line.
 *
 * Finds the first newline character in the saved buffer, creates a new string
 * containing the remainder of the buffer (after the newline), frees the old buffer,
 * and returns the new saved buffer.
 *
 * If no newline is found or there are no characters after the newline, the saved
 * buffer is freed and NULL is returned.
 *
 * @param save The saved buffer containing data read from a file.
 * @return char* The updated saved buffer, or NULL if no further data exists.
 */
char *ft_subs_line_from_save(char *save)
{
    char *newsave;
    char *ptr;
    int len;

    ptr = ft_strchr(save, '\n');
    if (!ptr)
    {
        newsave = NULL;
        return (ft_free(&save));
    }
    else
        len = (ptr - save) + 1;
    if (!save[len])
        return (ft_free(&save));
    newsave = ft_substr(save, len, ft_strlen(save) - len);
    ft_free(&save);
    if (!newsave)
        return (NULL);
    return (newsave);
}

/**
 * @brief Extracts a line (up to and including the newline) from the saved buffer.
 *
 * Searches for the first newline in the saved buffer and returns a new string
 * containing characters from the start of the buffer up to and including the newline.
 *
 * @param save The saved buffer containing data read from a file.
 * @return char* A new string representing the next line, or NULL on failure.
 */
char *ft_get_line(char *save)
{
    char *line;
    char *ptr;
    int len;

    ptr = ft_strchr(save, '\n');
    len = (ptr - save) + 1;
    line = ft_substr(save, 0, len);
    if (!line)
        return (NULL);
    return (line);
}

/**
 * @brief Reads from the file descriptor until a newline is encountered.
 *
 * Allocates a temporary buffer and reads data from the file descriptor in chunks of
 * BUFFER_SIZE until a newline is found or the end-of-file is reached. The newly read data
 * is concatenated to the saved buffer.
 *
 * @param fd The file descriptor to read from.
 * @param save The current saved buffer (may be NULL).
 * @return char* The updated saved buffer with the new data appended, or NULL on error.
 */
char *ft_read_till_n(int fd, char *save)
{
    int readed;
    char *buffer;

    readed = 1;
    buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return (ft_free(&save));
    buffer[0] = '\0';
    while (readed > 0 && !ft_strchr(buffer, '\n'))
    {
        readed = read(fd, buffer, BUFFER_SIZE);
        if (readed > 0)
        {
            buffer[readed] = '\0';
            save = ft_strjoin_modded(save, buffer);
        }
    }
    free(buffer);
    if (readed == -1)
        return (ft_free(&save));
    return (save);
}

/**
 * @brief Retrieves the next line from a file descriptor.
 *
 * This function reads from the file descriptor until it encounters a newline character.
 * It uses a static array of buffers (indexed by file descriptor) to support multiple files.
 * The function returns the next line (including the newline) from the file, or NULL if no
 * more data is available or on error.
 *
 * @param fd The file descriptor to read from.
 * @return char* The next line from the file descriptor, or NULL if there is no more data.
 */
char *get_next_line(int fd)
{
    static char *save[1024];
    char *line;

    if (fd < 0 || fd >= 1024)
        return (NULL);
    if ((save[fd] && !ft_strchr(save[fd], '\n')) || !save[fd])
        save[fd] = ft_read_till_n(fd, save[fd]);
    if (!save[fd])
        return (NULL);
    line = ft_get_line(save[fd]);
    if (!line)
        return (ft_free(&save[fd]));
    save[fd] = ft_subs_line_from_save(save[fd]);
    return (line);
}
