#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define pint pid_t
#include <sys/wait.h>

int main(){
	struct stat sb;
	int t;
	char filename[100];
	scanf("%s",filename);
	t = stat(filename,&sb);
	t = stat(filename,&sb);
	if(t){
		printf("ERROR.\n");
		return 1;
	}
	else{
		printf("%d dev id\n", sb.st_dev);
		printf("%d inode number\n", sb.st_ino );
		printf("%d perm\n",sb.st_mode );
		printf("%d hard links\n", sb.st_mode);
		printf("%d st_uid\n",sb.st_uid );
		printf("%d st_gid\n",sb.st_gid );
		printf("%d st_rdev\n",sb.st_rdev );
		printf("%d st_size\n",sb.st_size );
		printf("%d st_blksize\n",sb.st_blksize );
		printf("%d st_blocks\n",sb.st_blocks );
		printf("%d st_ctime\n",sb.st_ctime );
		printf("%d st_atime\n",sb.st_atime );
		printf("%d st_mtime\n",sb.st_mtime );
	}
	return 0;
}