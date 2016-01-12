#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<dlfcn.h>

int main(int argc, char **argv) {
    void *handle;
    char *error;
    bool (*pfunc)(void *);
    bool val;
    int i;
    handle = dlopen("/var/cache/socache/libpredicate.so", RTLD_LAZY);
    
    if (!handle){
    fputs(dlerror(), stderr);
    printf("trouble opening file");
    exit(1);
    }
    
    pfunc = dlsym(handle, "predicate");
    if ((error = dlerror()) != NULL) {
    fputs(error, stderr);
    printf("trouble opening function");
    exit(1);
    }
    for (i=0;i<10;i++){
    val = pfunc(i);
    printf("\n predicate returned %s for %d", val?"true":"false", i);
    }
    return 0;
}
