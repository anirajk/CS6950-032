#include<stdio.h>
#include<libgen.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/mount.h>
#include<errno.h>

void main(int argc, char * argv[]) {
    char *fname, *content, *base;
    FILE *ifp, *ofp;
    size_t len;
    struct stat st = {0};
    const char* src  = "none";
    const char* trgt = "/var/cache/socache";
    const char* type = "tmpfs";
    const unsigned long mntflags = 0;
    const char* opts = "mode=0777,uid=65534";
    fname = (char*)malloc(100*sizeof(char));
    base = (char*)malloc(20*sizeof(char));

    if (stat("/var/cache/socache", &st) == -1) { //Creating socache location if it doesn't exist
        mkdir("/var/cache/socache", 0777);
    }

    int result = umount(trgt);//Unmounting socache if mounted.
    if (result == 0) {
        printf("\nunmount done");
    }
    else{
        printf("\nFailed to unmount:%s [%d]", strerror(errno), errno);
    }
 
    result = mount(src, trgt, type, mntflags, opts); // Mounting socache on tmpfs
    if (result == 0) {
        printf("\nmount done");
    }
    else{
        printf("\nFailed to mount:%s [%d]", strerror(errno), errno);
    }
    
    strcpy(fname, "");
    strcat(fname, "/var/cache/socache/");
    base = basename(argv[1]);
    strcat(fname, base);

    if(access(fname,F_OK) != -1) {// Removing file if it exists.
        unlink(fname);
    }

    ifp = fopen(argv[1], "rb");
    ofp = fopen(fname, "wb+");
    fseek(ifp, 0, SEEK_END);
    len = ftell(ifp);  
    fseek(ifp, 0, SEEK_SET);       
    content = (char*)malloc(len*sizeof(char));

    fread(content, 1, len, ifp); //Rewriting so contents to tmpfs file
    fwrite(content, 1, len, ofp);

    fclose(ifp);
    fclose(ofp);
    printf("\n Rewrote %s to tmpfs\n", fname);
    free(content);
    free(fname);
    
}


