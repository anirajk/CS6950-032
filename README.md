#Compiling predicate code
gcc -c -fPIC predicate.c -lm
#Making an so from predicate
gcc -shared predicate.o -o libpredicate.so -lm
#Rewriting predicate.so to tmpfs
gcc filerewrite.c -o filerewrite
sudo ./filerewrite $PWD/libpredicate.so
#Opening and executing predicate
gcc openpredicate.c -o openpredicate -ldl

