# include <stdlib.h> // Malloc and Free
# include <unistd.h> // Write
# include <unistd.h> // access execve pipe
# include <stdio.h> // perror
# include <string.h> // strerror
# include <stdlib.h> // exit
# include <fcntl.h> // open
#include <errno.h> // perror -------->>>>> CAN I ?

int		pipex(char **argv, char **envp);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *str);
size_t	ft_strlcat(char *dst, const char *src, size_t max_size);
