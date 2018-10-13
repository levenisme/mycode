#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
void step1(struct stat sb) {
  char * filetype = NULL;
  switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:
      filetype = "block device";
      break;
    case S_IFCHR:
      filetype = "character special file";
      break;
    case S_IFDIR:
      filetype = "directory";
      break;
    case S_IFIFO:
      filetype = "FIFO/pipe";
      break;
    case S_IFLNK:
      filetype = "symlink";
      break;
    case S_IFREG:
      filetype = "regular file";
      break;
    case S_IFSOCK:
      filetype = "socket";
      break;
    default:
      filetype = "unknown?";
      break;
  }
  printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",
         sb.st_size,
         sb.st_blocks,
         sb.st_blksize,
         filetype);
  if ((S_ISCHR(sb.st_mode) || S_ISBLK(sb.st_mode)) != 0) {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %d,%d\n",
           (long)sb.st_dev,
           (long)sb.st_dev,
           (long)sb.st_ino,
           (long)sb.st_nlink,
           major(sb.st_rdev),
           minor(sb.st_rdev));
  }
  else
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
           (long)sb.st_dev,
           (long)sb.st_dev,
           (long)sb.st_ino,
           (long)sb.st_nlink);
}

char * step2(struct stat sb, int * p) {
  char * s = malloc(11 * sizeof(*s));
  *p = sb.st_mode & ~S_IFMT;
  switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:
      s[0] = 'b';
      break;
    case S_IFCHR:
      s[0] = 'c';
      break;
    case S_IFDIR:
      s[0] = 'd';
      break;
    case S_IFIFO:
      s[0] = 'p';
      break;
    case S_IFLNK:
      s[0] = 'l';
      break;
    case S_IFREG:
      s[0] = '-';
      break;
    case S_IFSOCK:
      s[0] = 's';
      break;
    default:
      s[0] = 0;
      break;
  }
  if ((sb.st_mode & S_IRUSR) != 0)
    s[1] = 'r';
  else
    s[1] = '-';

  if ((sb.st_mode & S_IWUSR) != 0)
    s[2] = 'w';
  else
    s[2] = '-';

  if ((sb.st_mode & S_IXUSR) != 0)
    s[3] = 'x';
  else
    s[3] = '-';

  if ((sb.st_mode & S_IRGRP) != 0)
    s[4] = 'r';
  else
    s[4] = '-';

  if ((sb.st_mode & S_IWGRP) != 0)
    s[5] = 'w';
  else
    s[5] = '-';

  if ((sb.st_mode & S_IXGRP) != 0)
    s[6] = 'x';
  else
    s[6] = '-';

  if ((sb.st_mode & S_IROTH) != 0)
    s[7] = 'r';
  else
    s[7] = '-';

  if ((sb.st_mode & S_IWOTH) != 0)
    s[8] = 'w';
  else
    s[8] = '-';

  if ((sb.st_mode & S_IXOTH) != 0)
    s[9] = 'x';
  else
    s[9] = '-';
  s[10] = '\0';
  return s;
  //  printf("Access: (%04o/%s)\n", per, s);
  //free(s);
}
void step3(struct stat sb, int p, char * str) {
  struct passwd * pwd;
  /* struct passwd * result;
  char * buf;
  size_t bufsize;
  int s;

  bufsize = sysconf(_SC_GETPW_R_SIZE_MAX);
  size_t n = -1;
  if (bufsize == n)  
    bufsize = 16384; 

  buf = malloc(bufsize);
  if (buf == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  s = getpwnam_r(filename, &pwd, buf, bufsize, &result);
  if (result == NULL) {
    if (s == 0)
      printf("Not found\n");
    else {
      // errno = s;
      perror("getpwnam_r");
    }
    exit(EXIT_FAILURE);
  }
  */
  pwd = getpwuid(sb.st_uid);
  struct group * grp;
  grp = getgrgid(sb.st_gid);
  printf("Access: (%04o/%s)  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n",
         p,
         str,
         sb.st_uid,
         pwd->pw_name,
         sb.st_gid,
         grp->gr_name);
  // printf("Name: %s; UID: %ld\n", pwd.pw_gecos, (long)pwd.pw_uid);
}
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t = localtime(when);
  strftime(temp1, 512, "%Y-%m-%d %H:%M:%S", t);
  strftime(temp2, 32, "%z", t);
  snprintf(ans, 128, "%s.%09ld %s", temp1, ns, temp2);
  return ans;
}
void step4(struct stat sb) {
  char * timestr1 = time2str(&sb.st_atime, sb.st_atim.tv_nsec);
  char * timestr2 = time2str(&sb.st_mtime, sb.st_mtim.tv_nsec);
  char * timestr3 = time2str(&sb.st_ctime, sb.st_ctim.tv_nsec);
  printf("Access: %s\n", timestr1);
  printf("Modify: %s\n", timestr2);
  printf("Change: %s\n", timestr3);
  printf(" Birth: -\n");
  free(timestr1);
  free(timestr2);
  free(timestr3);
}

int main(int argc, char ** argv) {
  struct stat sb;
  if (argc <= 1) {
    fprintf(stderr, "stat: missing operand\nTry 'stat --help' for more information.\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 1; argv[i] != NULL; i++) {
    if (lstat(argv[i], &sb) == -1) {
      perror("lstat");
      exit(EXIT_FAILURE);
    }
    if (S_ISLNK(sb.st_mode)) {
      char buf[256];
      buf[readlink(argv[i], buf, 256)] = '\0';
      printf("  File:'%s' -> '%s'\n", argv[i], buf);
    }
    else
      printf("  File: %s\n", argv[i]);
    step1(sb);
    int per = 0;
    int * p = &per;
    char * s = step2(sb, p);
    step3(sb, per, s);
    free(s);
    step4(sb);
  }
  return EXIT_SUCCESS;
}

//This function is for Step 4
