env = Environment(CPPPATH=['rlibc/inc'])
env.StaticLibrary('rlibc',['rlibc/src/string.c'])
env.Program('test/test_rlibc/teststrlen.c',LIBS=['rlibc'],LIBPATH='.')