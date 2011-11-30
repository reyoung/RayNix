import os
env = Environment(CPPPATH=['rlibc/inc'])
env.StaticLibrary('lib/rlibc',[Glob('rlibc/src/*.c')])
os.system('''echo '#/bin/bash'>check.sh ''');
for testFile in Glob('test/test_rlibc/*.c'):
	fn = 'bin/test/'+testFile.name.split('.')[0]
	env.Program(fn,testFile,LIBS=['rlibc'],LIBPATH='lib')
	os.system("echo '" +fn+"'>>check.sh");
	os.system("echo 'retv=$?' >> check.sh")
	os.system("echo 'if [ $retv -ne \"0\" ]' >> check.sh");
	os.system("echo 'then' >> check.sh");
	os.system("echo '    echo '"+fn+"'+\"ErrorCode $retv\"' >> check.sh")
	os.system("echo 'fi' >> check.sh");